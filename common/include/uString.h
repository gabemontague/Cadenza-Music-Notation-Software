// String Header
#ifndef _H_USTRING_
#define _H_USTRING_

#include "Common.h"

namespace AGK
{
	class _EXPORT_ uString
	{
		protected:
			char* m_pData;
			UINT m_iLength; //length of the current string, cached for speed
			UINT m_iTotalLength; //length of the array holding the string, might have room for more data
		
			void Reset();
		
		public:
			uString();
			uString( const uString &szString );
			uString( const char* szString, UINT initialLength=0 ); //can define a longer array than the data given
			~uString();
		
			void SetStr( const char* szString );
			inline void SetStr( const uString &szString ) { SetStr( szString.GetStr() ); }
			inline const char* GetStr() const { if ( !m_pData || m_iLength == 0 ) return ""; else return m_pData; }
			inline UINT GetLength() const { return m_iLength; }

			uString& Prepend( const char* szString );
			inline uString& Prepend( const uString &szString ) { return Prepend( szString.GetStr() ); }

			uString& Append( char c );
			uString& Append( int num );
			uString& Append( UINT num );
			uString& Append( float num );
			uString& Append( const char* szString );
			uString& AppendN( const char* szString, UINT length ); // adds a null terminator to the internal string when done

			uString& InsertCharAt( UINT index, char c );
			uString& DeleteCharAt( UINT index );

			uString& Format( const char* szString, ... ); //same format as sprintf

			uString& Strip( const char* tokens ); //removes all characters in "tokens" from the string
			uString& Trim( const char* tokens ); //removes all characters in "tokens" from the ends of the string
			uString& Replace( char find, char replace ); //replaces all instances of "find" with "replace"
			uString& ReplaceStr( const char* find, const char* replace ); //replaces all instances of "find" with "replace"
			uString& Upper( ); //converts to upper case
			uString& Lower( ); //converts to lower case

			char CharAt( UINT index ) const;
			int Find( char cFind ) const; //finds the first instance of the character and returns its index
			int RevFind( char cFind ) const; //finds the last instance of the character and returns its index
			void Trunc( char cFind ); //removes all characters after the last occurance of cFind, including that character
			void Trunc2( int count ); //removes the last count characters from the string
			int FindStr( const char* str ) const;
			int Count( char find ); // counts the occurances of the given character

			int ToInt() const;
			float ToFloat() const;

			int CountTokens( const char* delimit );
			char* GetToken( const char* delimit, int index );
			
			inline int CompareTo( const uString &pTo ) const { return CompareTo( pTo.GetStr() ); }
			int CompareTo( const char* szTo ) const;

			inline uString& operator =( const char* str ) { this->SetStr(str); return *this; }
			inline uString& operator +=( const char* str ) { this->Append(str); return *this; }
			inline uString& operator +=( UINT u ) { this->Append(u); return *this; }
			inline uString& operator +=( int i ) { this->Append(i); return *this; }
			inline uString& operator +=( float f ) { this->Append(f); return *this; }
			inline uString& operator +=( const uString& str ) { if ( &str!=this ) this->Append(str); return *this; }
			inline bool operator ==( const uString& str ) const { return this->CompareTo(str) == 0; }
			inline bool operator !=( const uString& str ) const { return this->CompareTo(str) != 0; }
			inline operator const char *() const { if ( !m_pData || m_iLength == 0 ) return ""; else return m_pData; }
		
			void SubString( uString &output, int start, int length=-1 ) const;
	};
}

#endif
