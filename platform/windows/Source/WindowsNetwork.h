#ifndef _H_NETWORK_WIN
#define _H_NETWORK_WIN

#include "Common.h"

namespace AGK
{
	class cLock 
	{
		protected:
			CRITICAL_SECTION m_cs;

		public:
			cLock()
			{
				InitializeCriticalSection( &m_cs );
			}

			~cLock()
			{
				DeleteCriticalSection( &m_cs );
			}

			bool Acquire()
			{
				EnterCriticalSection( &m_cs );
				return true;
			}

			void Release()
			{
				LeaveCriticalSection( &m_cs );
			}
	};

	class cThreadEvent
	{
		protected:
			HANDLE m_event;

		public:
			cThreadEvent( int initial=0 )
			{
				if ( initial != 0 ) initial = 1;
				m_event = CreateEvent( NULL, FALSE, initial, NULL );
			}

			~cThreadEvent()
			{
				if ( m_event ) CloseHandle( m_event );
			}

			bool Wait()
			{
				WaitForSingleObject( m_event, INFINITE );
				return true;
			}

			void Notify()
			{
				SetEvent( m_event );
			}
	};

	class AGKPacket
	{
		protected:
			char m_Buffer[ AGK_NET_PACKET_SIZE ];
			UINT m_iPtr;

		public:

			AGKPacket();
			~AGKPacket(){};
			void Copy( const AGKPacket *fromPacket );

			void AddData( const char* s, UINT length );
			void AddString( const char *s );
			void AddChar( char c );
			void AddUInt( UINT u );
			void AddInt( int i );
			void AddFloat( float f );

			UINT GetPos() const;
			void SetPos( UINT pos );
			const char* GetBuffer() const { return m_Buffer; }
			char* GetRaw(){ return m_Buffer; }

			UINT	GetData( char* data, UINT length );
			int		GetString( uString &s );		
			char	GetChar();						
			int		GetInt();						
			UINT	GetUInt();						
			float	GetFloat();					
	};

	class AGKSocket : public AGKThread
	{
		public:
			AGKSocket *m_pNext;

		protected:
			SOCKET m_client;
			char m_szIP[ 40 ];
			UINT m_port;
			volatile bool m_bConnected;
			volatile bool m_bConnecting;
			bool m_bDisconnected;
			UINT m_iTimeout;

			volatile float m_fProgress;
			volatile bool m_bResult;
			
			char m_sendBuffer[ 1400 ];
			UINT m_iSendWritePtr;
						
			UINT Run();

			void Reset();

		public:

			AGKSocket();
			AGKSocket( SOCKET s );
			~AGKSocket();

			const char *GetRemoteIP() { return m_szIP; }

			bool Flush();
			void Close( bool bGraceful=true );
			bool GetDisconnected() { return m_bDisconnected; }

			bool Connect( const char* IP, UINT port, UINT timeout=3000 );
			bool IsConnected() { return m_bConnected; }
			bool IsConnecting() { return m_bConnecting; }
			float GetProgress() { return m_fProgress; }

			void SetTimeout( int iLength );
			
			bool SendFile( const char* szFilename );
			bool SendData( const char* s, int length );
			bool SendString( const char *s );
			bool SendChar( char c );
			bool SendUInt( UINT u );
			bool SendInt( int i );
			bool SendFloat( float f );

			// if this is zero the recv commands will block
			int GetBytes();
			
			int		RecvData( char* data, int length ); // blocks
			int		RecvString( uString &s );			// blocks
			char	RecvChar();							// blocks
			int		RecvInt();							// blocks
			UINT	RecvUInt();							// blocks
			float	RecvFloat();						// blocks			
	};

	class UDPManager
	{
		protected:
			SOCKET m_socket;
			UINT m_port;

		public:
			UDPManager( UINT port );
			~UDPManager();

			bool SendPacket( const char *IP, const AGKPacket *packet ); // does not block
			bool RecvPacket( char *fromIP, AGKPacket *packet );  // does not block
	};

	// wil listen for new connections until stopped
	class cNetworkListener : public AGKThread
	{
		protected:
			SOCKET m_socket;
			UINT m_port;
			cLock m_lock;

			AGKSocket* volatile m_pConnections;

			UINT Run();

		public:
			cNetworkListener();
			~cNetworkListener();

			AGKSocket* GetNewConnection();
			void AcceptConnections( UINT port );
			void Stop();
	};

	// will wait forever for broadcast packets until Stop() is called
	class BroadcastListener
	{
		protected:
			SOCKET m_socket;
			sockaddr_in addr;
			//char m_data[1500];
			//char m_from[45];
			//void (*callback)(int, const char*, const char*);

			//UINT Run();

		public:
			BroadcastListener();
			~BroadcastListener();

			void Close();

			bool SetListenPort( UINT port );
			bool ReceivedBroadcast();
			bool GetPacket( AGKPacket &packet, UINT &fromPort, char *fromIP );
	};

	// will broadcast a packet a regular intervals until stopped.
	class Broadcaster : public AGKThread
	{
		protected:
			//char m_data[1400];
			AGKPacket m_packet;
			//UINT m_size;
			UINT m_interval;
			int m_max;
			UINT m_port;

			UINT Run();

		public:

			Broadcaster();
			~Broadcaster() {};

			// sets the data that will be broadcast every interval milliseconds for a maximum of max broadcasts (0=forever)
			// start with Start() and stop with Stop()
			//void SetData( UINT port, const char* buf, UINT length, UINT interval, int max=0 );
			void SetData( UINT port, const AGKPacket *packet, UINT interval, int max=0 );
	};

	class cHTTPConnection : public AGKThread
	{
		protected:
			static HINTERNET m_hInet;

			char *m_sURL;
			HINTERNET m_hInetConnect;
			int m_iSecure;
			volatile bool m_bConnected;
			
			char* volatile m_szResponse;
			float volatile m_fProgress;
			char m_szContentType[50];

			bool m_bSaveToFile;
			uString m_szServerFile;
			uString m_szLocalFile;
			uString m_szUploadFile;
			uString m_szPostData;

			char* SendRequestInternal();
			char* SendFileInternal();
			UINT Run();

		public:
			cHTTPConnection();
			~cHTTPConnection();

			void Stop();

			bool SetHost( const char *szHost, int iSecure, const char *szUser=0, const char *szPass=0 );
			void Close();

			float GetProgress() { return m_fProgress; }

			// caller must delete returned pointer
			char* SendRequest( const char *szServerFile, const char *szPostData=0 ); //blocks
			bool SendRequestASync( const char *szServerFile, const char *szPostData=0 ); //does not block
			bool SendFile( const char *szServerFile, const char *szPostData, const char *szLocalFile ); //does not block

			int GetResponseReady();
			const char* GetResponse(); // caller must NOT delete returned pointer
			const char* GetContentType();

			bool DownloadFile( const char *szServerFile, const char *szLocalFile, const char *szPostData=0 ); //does not block
			bool DownloadComplete();
	};
}

#endif