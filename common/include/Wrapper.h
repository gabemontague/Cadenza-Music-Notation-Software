// Wrapper Header
#ifndef _H_WRAPPER_
#define _H_WRAPPER_

// Includes
#include "Common.h"
#include "AGK.h"

#ifdef LoadImage
#undef LoadImage
#endif

#ifdef PlaySound
#undef PlaySound
#endif

#define AGK_MAX_VIRTUAL_BUTTONS 12

#define AGK_FLAG_PORTRAIT			0x00000001
#define AGK_FLAG_PORTRAIT2			0x00000002
#define AGK_FLAG_LANDSCAPE			0x00000004
#define AGK_FLAG_LANDSCAPE2			0x00000008

// GDK Class
namespace AGK
{
	class cFileEntry
	{
		protected:
			uString m_sReal;
			uString m_sLowercase;
			cFileEntry *m_pNext;

			static cHashedList<cFileEntry> g_cFileList;
			static void TraverseDirectory( const char* dir );

		public:
			cFileEntry() { m_pNext = UNDEF; }
			~cFileEntry() {}

			static void InitFileList();
			static void AddNewFile( const char *szFullPath );
			static void ConvertToReal( uString &path );
			static void ClearAll();
	};
	
	class cDirectoryItem
	{
		public:
			uString m_sItem;
			cDirectoryItem *m_pNext;

			cDirectoryItem() { m_pNext = 0; }
			~cDirectoryItem() { }
	};

	class agk
	{
		private:
			// this prevents the creation of an instance of this class by other classes.
			agk();

			friend class cText;
			friend class cSprite;
			friend class cImage;
			friend class Physics;
			friend class cNetCon;
			friend class AGKSocket;
			friend class AGKPacket;
			friend class cFile;
			friend class cMusicMgr;
			friend class cSpriteMgr;
			friend class cParticleEmitter;
			friend class cSoundMgr;
			friend class cVirtualButton;
			friend class cVirtualJoystick;
			friend class cEditBox;
			friend class ZipFile;

		public:

			// *********************
			// internal PUBLIC variables
			// *********************

			// Remote Debugging globals
			static bool m_bTriggerBreakPointNow;
			
		protected:

			// *********************
			// internal variables
			// *********************

			// calculated viewport dimensions
			/*
			static float m_iViewportX;
			static float m_iViewportY;
			static float m_iViewportWidth;
			static float m_iViewportHeight;
			*/
		
			static int m_iTargetViewportX;
			static int m_iTargetViewportY;
			static int m_iTargetViewportWidth;
			static int m_iTargetViewportHeight;

			static int m_iScissorX;
			static int m_iScissorY;
			static int m_iScissorWidth;
			static int m_iScissorHeight;
			static bool m_bScissorUser;
			static bool m_bScissorEnabled;

			// app start time in seconds
			static double m_fTimeStart; 
			// current app time in seconds
			static double m_fTimeCurr;
			// time current frame started in seconds
			static double m_fTimeFrameStart;
			static double m_fTimeLimitFrameStart;
			// time spent processing the last frame in seconds 
			static float m_fTimeDelta; 
			static UINT m_iTimeMilliseconds;
			static float m_fFps;

			// width and height of the device (current state of device target) (i.e. desktop resolution)
			static int m_iRealDeviceWidth;
			static int m_iRealDeviceHeight;

			// current render target size that may not be equal to the device size.
			static int m_iRenderWidth;
			static int m_iRenderHeight;
			static int m_iFakeRenderWidth;
			static int m_iFakeRenderHeight;
		
			// width and height of the workspace (display), as requested by the user in InitGL()
			static int m_iDisplayWidth;
			static int m_iDisplayHeight;
			static float m_iDisplayExtraX;
			static float m_iDisplayExtraY;
			static float m_fDisplayAspect;
			static int m_iDisplayIsLandscape;
			static bool m_bUsingDisplayAspect;
			static bool m_bUsingDeviceAspect;
			static float m_fStretchValue;
			static bool m_bClearDepth;
			static bool m_bClearColor;
			static int m_iResolutionMode;
			static int m_iOrientation;
			static float m_fCurrentAngle;
			static float m_fTargetAngle;
			static UINT m_bAGKFlags;
			static UINT m_iTransitionMode;
			static UINT m_iDefaultMagFilter;
			static UINT m_iDefaultMinFilter;
			static UINT m_iDefaultWrapU;
			static UINT m_iDefaultWrapV;
			static uString m_sAppName;
			static uString m_sCL;
			static UINT m_iClearColor;
			static UINT m_iBorderColor;
			static float m_fAlphaTestThreashold;
			static bool m_bSortCreated;
			static bool m_bIsCapturing;
			static UINT m_iUncollectedCaptureImage;
            static bool m_bIsChoosing;
            static cImage* m_pUncollectedChosenImage;

			static UINT m_iPulleySprite1;
			static UINT m_iPulleySprite2;
			static float m_iPulleyRatio;
			static int m_iPulleyColConnected;
			
			static int m_iResumed;

			// input variables
			// mouse
			static cMouse *m_pMouse[ 4 ];

			// accelerometer
			static float m_fAccelX;
			static float m_fAccelY;
			static float m_fAccelZ;
			static float m_fFakeAccelX;
			static float m_fFakeAccelY;

			// keyboard
			static unsigned char m_iPrevKeyDown[ 256 ];
			static unsigned char m_iKeyDown[ 256 ];
			static unsigned int m_iLastKey;

			// joystick
			static cJoystick* m_pJoystick[ 4 ];
			static cVirtualJoystick *m_pVirtualJoystick[ 4 ];

			// virtual buttons
			static cVirtualButton *m_pVirtualButton[ AGK_MAX_VIRTUAL_BUTTONS ];

			// pointer state
			static int m_iLastPointerDown;
			static int m_iPointerDown;

			// AGK joystick
			static float m_fFakeJoystickX;
			static float m_fFakeJoystickY;
			static float m_fJoystickDeadZone;

			// text input variables
			static bool m_bInputStartedPrev;
			static bool m_bInputStarted;
			static bool m_bInputCancelled;
			static uString m_sCurrInput;
			static int m_iLastChar;
			static int m_iCurrChar;
			static float m_fCursorBlinkDelay;
			static UINT m_iInputMaxChars;
			static uString m_sInputLabel;
			
			// single music manager for agk functions
			static cMusicMgr m_cMusicMgr;
			static int m_iDeviceVolume;

			// directory variables
			static cDirectoryItem *m_pCurrentDirectories;
			static cDirectoryItem *m_pCurrentFiles;

			static cDirectoryItem *m_pCurrentDirectoryIter;
			static cDirectoryItem *m_pCurrentFileIter;

			// date/time variables
			static int m_pMonthDays[ 12 ];

			// advert variables
			static uString m_sAdMobCode;
			static uString m_sInneractiveCode;
			static uString m_sAdClientID;
			static uString m_sInneractiveURL;
			static uString m_sInneractiveImage;
			static cImage *m_pAdImage;
			static cSprite *m_pAdSprite;
			static cHTTPConnection *pHTTPInneractive;
			static float m_fAdStartTime;
			static int m_iInneractiveStage;
			static float m_fAdX;
			static float m_fAdY;
			static float m_fAdWidth;
			static int m_iAdHorz;
			static int m_iAdVert;
            static int m_iAdTest;

			// 3D variables
			static float m_fFOV;
			static float m_fNear;
			static float m_fFar;
			static int m_iProjMatrixMode;

			// ***********************
			// internal functions
			// ***********************
			static void PlatformSetDevicePtr( void* ptr );
			static void PlatformInitGL( void *ptr );
			static void PlatformDestroyGL( void );
			static void PlatformInitFilePaths();
			static void RecalculateDisplay();
			static void PlatformBindDefaultFramebuffer();
			static void PlatformSync();
			static void PlatformClearScreen();
			static void PlatformClearDepthBuffer();
			static void PlatformFlush();
			static void PlatformUpdateDeviceSize();
			static void PlatformCleanUp();
			static void PlatformDeviceVolume();
			static void PlatformUpdateTime();
			static void PlatformResetTime();
			static void PlatformReportError( const uString &sMsg );
			static void PlatformSetViewport( int x, int y, int width, int height );
			static void PlatformCompleteInputInit();
			static void PlatformStartTextInput( const char *sInitial );
			static void PlatformUpdateTextInput();
			static void PlatformDrawTextInput();
			static void PlatformMessage( const char* msg );
			static void PlatformSetProjectionMatrix();
			static void PlatformSet3DProjectionMatrix();
			static void PlatformPrepareDebugDraw();
			static void PlatformEndDebugDraw();
			static void PlatformPrepareDefaultDraw();
			static void PlatformPrepare2DStates();
			static void PlatformPrepare3DStates();
			static void PlatformUpdateWritePath();
			static void PlatformRestoreWritePath();
			static void PlatformScissor( int x, int y, int width, int height );
			static bool PlatformShowCaptureScreen();
			static void PlatformHideCaptureScreen();
            static void PlatformShowChooseScreen();
			static bool PlatformChooseFile( uString &out, const char *ext );
			static void PlatformResumed();
			static int PlatformGetAdPortal();
			static void PlatformSetOrientationAllowed( int p, int p2, int l, int l2 );

			static void UpdateAd();
			static void DrawAd();
			
			static void CreateDefaultImage( const char* filename, UINT size, UINT* pData );
			static bool GetDeviceCanRotate();
			static bool GetAGKShouldRotate();
			static bool GetDeviceHasSplash();

			static UINT PlatformLittleEndian( UINT u );
			static int PlatformLittleEndian( int i );
			static UINT PlatformLocalEndian( UINT u );
			static int PlatformLocalEndian( int i );

			static void UpdatePhysicsWalls();
			static void ParseCurrentDirectory();
			static void ResetScissor();
		
			//static void ConvertMediaPath( uString &sPath );

			static cHashedList<cImage> m_cImageList;
			static cHashedList<cSprite> m_cSpriteList;
			static cHashedList<cText> m_cTextList;
			static cHashedList<b2Joint> m_cJointList;
			static cHashedList<cForce> m_cForceList;
			static cHashedList<cFile> m_cFileList;
			static cHashedList<cNetwork> m_cNetworkList;
			static cHashedList<cNetworkMessage> m_cNetMessageList;
			static cHashedList<cHTTPConnection> m_cHTTPList;
			static cHashedList<BroadcastListener> m_cBroadcastListenerList;
			static cHashedList<cParticleEmitter> m_cParticleEmitterList;
			static cHashedList<cEditBox> m_cEditBoxList;
			static cHashedList<ZipFile> m_cZipFileList;
			//static cHashedList<cObject3D> m_cObject3DList;

			static cSpriteMgr m_cSpriteMgr;

			// error variables
			static int m_iErrorMode;
			static uString m_sLastError;
			static bool m_bErrorOccurred;
			static cLock *m_kErrorLock;
			static void(*m_fWarningCallback)(const char*); 
			static void(*m_fErrorCallback)(const char*);

			// misc variables
			static cText *m_pPrintText;
			static uString m_cPrintStr;
			static char m_szConvStr[ 20 ]; // string used to temporarily hold floats and ints converted to strings
			static bool m_bGenerateMipmaps;
			static cSprite *m_pLastColCheck;
			static cSprite *m_pLastColCheck2;
			static UINT m_iRandSeed;
			static float m_fViewOffsetX;
			static float m_fViewOffsetY;
			static float m_fViewZoom;
			static int m_iViewZoomMode;
			static cSprite *m_pSplashSprite;
			static bool m_bFirstSync;
			static float m_fSyncTime;
			static int m_iSyncMode;
			static bool m_bOrientationSet;
			static int m_iCurrentOrientationMode;

			static uString m_sCurrentDir;
			static uString m_sOrigSetDir;

#ifdef USE_BOX2D
			static b2World *m_phyWorld;
			static b2Body *m_phyGroundBody;

			static b2Body *groundBodyBottom;
			static b2Body *groundBodyRight;
			static b2Body *groundBodyLeft;
			static b2Body *groundBodyTop;

			static float m_phyScale;
			static bool m_bDrawDebug;
			static int m_iVelIterations;
			static int m_iPosIterations;
			static bool m_bPhysicsStepped;
			static b2Contact *m_pContactIter;
			static cSprite *m_pSpriteContactIter;

			static int m_iMaxPolygonPoints;
#endif

			// benchmarking
			static float m_fUpdateTime;
			static float m_fPhysicsTime;
			static float m_fDrawingSetupTime;
			static float m_f3DDrawingSetupTime;
			static float m_fDrawingTime;

		public:
        
            static void PlatformGetFullPathWrite( uString &inout );
            static void PlatformGetFullPathRead( uString &inout );
			static void PlatformCreatePath( uString path );
		
			// *********************************
			// public items, not for general use
			// *********************************

			// opening a file from the local file store (no absolute paths)
			//static FILE* Platformfopen( const uString &sPath );

			static void SetAppName( const char* name );
			static void RestoreWriteDir( void );
			static void MasterReset();

			// internal public functions, called by automated processes on the device
			static void SetResolutionMode( int mode );
			static void InitGL( void* ptr );
			static void DestroyGL( void );
			static void UpdatePtr( void* ptr );
			static void UpdatePtr2( void* ptr ); // does minimal amount of changes
			static void ResetAllStates ( void );
			static void CleanUp();
		
			static void OrientationChanged( int mode );
			static int CanOrientationChange( int mode );
			static void SetOrientationMatrix();

			static void Resumed( int mode=1 );

			// touch input commands, the device stub file will need to call these to notify the AGK about input events
			static void TouchPressed(UINT ID, int x, int y);
			static void TouchMoved(UINT ID, int x, int y);
			static void TouchReleased(UINT ID, int x, int y);
		
			static void MouseLeftButton(UINT ID, int state);
			static void MouseRightButton(UINT ID, int state);
			static void MouseMove(UINT ID, int x, int y);
		
			static void SetMultiTouchExist( bool bFlag );
			static void SetMouseExist( bool bFlag );
			static void SetJoystickExist( bool bFlag );
			static void SetKeyboardExist( bool bFlag );
			static void SetAccelerometerExist( bool bFlag );
			static void Accelerometer( float x, float y, float z );

			static void KeyDown( UINT index );
			static void KeyUp( UINT index );
			static void CharDown( UINT c );
		
			static void JoystickAxis( void* pDevice, int stick, int axis, float value );
			static void JoystickButton( void* pDevice, int button, int state );
			
			// input related functions
			static float DeviceToScreenX( int x );
			static float DeviceToScreenY( int y );
			static int ScreenToDeviceX( float x );
			static int ScreenToDeviceY( float y );
			static float ViewportToScreenX( int x );
			static float ViewportToScreenY( int y );
			static int ScreenToViewportX( float x );
			static int ScreenToViewportY( float y );
			static float RotatePointX( float x, float y );
			static float RotatePointY( float x, float y );

			static float ScreenToWorldX( float x );
			static float ScreenToWorldY( float y );
			static float WorldToScreenX( float x );
			static float WorldToScreenY( float y );

			static float GetStretchValue() { return m_fStretchValue; }

			// tell the AGK about the current device volume (if, as in the case of Samsung, the AGK is required to handle this itself)
			static void DeviceVolume( int vol );
			static int GetDeviceVolume() { return m_iDeviceVolume; }

			// sound input commands, the device stub file will need to call these to notify the GDK about sound events
			static void HandleMusicEvents( UINT lParam );

#ifdef USE_BOX2D
			static float PhyToWorldX( float value ) { return value / m_phyScale; }
			static float PhyToWorldY( float value ) { return (value * m_fStretchValue) / m_phyScale; }
			static float WorldToPhyX( float value ) { return value * m_phyScale; }
			static float WorldToPhyY( float value ) { return (value / m_fStretchValue) * m_phyScale; }

			static void ClearJoint( b2Joint *pJoint );
#endif

		public:

			// *************************
			// public items
			// *************************

			// override values
			static bool m_bHasAccelerometer;
			static bool m_bHasMultiTouch;
			static bool m_bHasKeyboard;
			static bool m_bHasMouse;
			static bool m_bHasJoystick;
			static uString m_FakeDeviceName;
			
			// core functions
			static int GetDeviceWidth();
			static int GetRealDeviceWidth();
			static void SetFakeDeviceWidth(int iWidth);
			static int GetDeviceHeight();
			static int GetRealDeviceHeight();
			static void SetFakeDeviceHeight(int iHeight);
			static void SetVSync( int mode );
			static void SetSyncRate( float fps, int mode );
			static void SetVirtualResolution( int iWidth, int iHeight );
			static void SetDisplayAspect( float aspect );
			static int GetVirtualWidth();
			static int GetVirtualHeight();
			static float GetScreenBoundsLeft();
			static float GetScreenBoundsRight();
			static float GetScreenBoundsTop();
			static float GetScreenBoundsBottom();
			static float GetDisplayAspect();
			static int GetOrientation();
			static int GetResumed();
			static char* GetDeviceName();
			static void GetDeviceName( uString &sString );
			static void SetFakeDeviceName( char* pNewDeviceName );
			static char* GetAppName();
			static char* GetCL();
			static void GetAppName( uString &sString );
			static void SetWindowTitle( const char* szTitle );
			static void UpdateDeviceSize(UINT w=0, UINT h=0);
			static void StepPhysics( float time );
			static void Sync();
			static void Break();
			static void Update( float time=0 );
			static void Render();
			static void Render3D();
			static void Swap();
			static void ClearScreen();
			static void ClearDepthBuffer();
			static void Sleep( UINT milliseconds );
			static float Timer();
			static void ResetTimer();
			static float GetRunTime();
			static int GetSeconds();
			static float GetFrameTime();
			static UINT GetMilliseconds();

			// math functions
			static void SetRandomSeed( UINT seed );
			static UINT Random( );
			static UINT Random( UINT from, UINT to );
			static int RandomSign( int value );
			static float Sin( float a );
			static float Cos( float a );
			static float Tan( float a );
			static float SinRad( float a );
			static float CosRad( float a );
			static float TanRad( float a );
			static float ASin( float a );
			static float ACos( float a );
			static float ATan( float a );
			static float ATanFull( float x, float y );
			static float ASinRad( float a );
			static float ACosRad( float a );
			static float ATanRad( float a );
			static float ATanFullRad( float x, float y );
			static int Trunc( float a );
			static int Floor( float a );
			static int Ceil( float a );
			static int Round( float a );
			static float Sqrt( float a );
			static float Abs( float a );
			static int Mod( int a, int b );
			static float FMod( float a, float b );

			// control functions
			static void SetAlphaTestThreshold( UINT threshold );
			static void SetGenerateMipmaps( int generate );
			static void SetOrientationAllowed( int portrait, int portrait2, int landscape, int landscape2 );
			static void SetTransitionMode( int mode );
			static void SetSortTextures( int sort );
			static void SetSortDepth( int sort );
			static void SetSortTransparentDepth( int sort );
			static void SetSortCreated( int sort );
			static float ScreenFPS();
			static void EnableClearDepth( UINT clear );
			static void EnableClearColor( UINT clear );
			static void SetBorderColor( UINT red, UINT green, UINT blue );
			static void SetClearColor( UINT red, UINT green, UINT blue );
			static void BindDefaultFramebuffer();
			static void SetDefaultMagFilter( UINT filter );
			static void SetDefaultMinFilter( UINT filter );
			static void SetDefaultWrapU( UINT mode );
			static void SetDefaultWrapV( UINT mode );
			static void SetViewOffset( float x, float y );
			static void SetViewZoom( float zoom );
			static void SetViewZoomMode( int mode );
			static float GetViewOffsetX();
			static float GetViewOffsetY();
			static float GetViewZoom();
			static void SetScissor( float x, float y, float x2, float y2 );
			
			// functions that fail call this function
			static void Error( const uString &sMsg );
			static void Warning( const uString &sMsg );
			static void SetErrorMode( int mode );
			static int GetLastError( uString &sOut );
			static char* GetLastError();
			static int GetErrorOccurred();
			static void SetWarningCallback( void(*callback)(const char*) );
			static void SetErrorCallback( void(*callback)(const char*) );

			static void Message( const char* msg );
			
			// image functions
			static cImage* GetImagePtr ( UINT iImageIndex );
			static void LoadImage ( UINT iImageIndex, const char* sImageFilename, int bBlackToAlpha );
			static UINT LoadImage ( const char* sImageFilename, int bBlackToAlpha );
			static void LoadImage ( UINT iImageIndex, const char* sImageFilename );
			static UINT LoadImage ( const char* sImageFilename );
			static void LoadSubImage ( UINT iImageIndex, UINT iParentIndex, const char* sImageFilename );
			static UINT LoadSubImage ( UINT iParentIndex, const char* sImageFilename );
			static UINT GetImageExists ( UINT iImageIndex );
			static void DeleteImage ( UINT iImageIndex );
			static float GetImageWidth ( UINT iImageIndex );
			static float GetImageHeight ( UINT iImageIndex );
			static void SetImageMinFilter( UINT iImageIndex, UINT mode );
			static void SetImageMagFilter( UINT iImageIndex, UINT mode );
			static void SetImageWrapU( UINT iImageIndex, UINT mode );
			static void SetImageWrapV( UINT iImageIndex, UINT mode );
			static void SetImageMask( UINT iDstImage, UINT iSrcImage, int dst, int src, int x, int y );
			static void SaveImage( UINT iImageIndex, const char* filename );
			static void CopyImage( UINT newImage, UINT fromImage, int x, int y, int width, int height );
			static UINT CopyImage( UINT fromImage, int x, int y, int width, int height );
			static UINT GetImage( float x, float y, float width, float height );
			static void GetImage( UINT imageID, float x, float y, float width, float height );
			static char* GetImageFilename( UINT imageID );

            static UINT ChooseImage();
            static UINT ShowChooseImageScreen();
            static void ChooseInternal(int value);
            static UINT GetChosenImage();
            static UINT IsChoosingImage();
		
            static UINT ShowImageCaptureScreen();
			static void CaptureImage();
            static void CaptureInternal(int value);
			static void CancelCapture();
			static UINT GetCapturedImage();
			static UINT IsCapturingImage();
        
			static char* DecodeQRCode( UINT image );
			static UINT EncodeQRCode( const char* text, int errormode );
        
			static void PrintImage( UINT image, float size );
			
			// sprite functions
			static cSprite* GetSpritePtr ( UINT iSpriteIndex );
			static UINT GetSpriteImageID ( UINT iSpriteIndex );
			static UINT CreateSprite ( UINT iImageIndex );
			static UINT LoadSprite ( const char* imagefile );
			static void CreateSprite ( UINT iSpriteIndex, UINT iImageIndex );
			static void LoadSprite ( UINT iSpriteIndex, const char* imagefile );
			static void CreateDummySprite ( UINT iSpriteIndex );
			static UINT CreateDummySprite ( );
			static void CloneSprite( UINT iSpriteIndex, UINT iOtherSprite );
			static UINT CloneSprite( UINT iOtherSprite );
			static void DeleteSprite ( UINT iSpriteIndex );
			static void SetSpritePosition ( UINT iSpriteIndex, float fX, float fY );
			static void SetSpritePositionByOffset ( UINT iSpriteIndex, float fX, float fY );
			static void SetSpriteX ( UINT iSpriteIndex, float fX );
			static void SetSpriteY ( UINT iSpriteIndex, float fY );
			static void SetSpriteAngle ( UINT iSpriteIndex, float fAng );
			static void SetSpriteAngleRad ( UINT iSpriteIndex, float fAng );
			static void SetSpriteDepth ( UINT iSpriteIndex, int iDepth );
			static void SetSpriteFlip ( UINT iSpriteIndex, int horz, int vert );
			static void SetSpriteSnap ( UINT iSpriteIndex, int snap );
			static void SetSpriteVisible ( UINT iSpriteIndex, int bVisible );
			static void SetSpriteActive ( UINT iSpriteIndex, int bActive );
			static void SetSpriteImage ( UINT iSpriteIndex, UINT iImageIndex );
			static void SetSpriteImage ( UINT iSpriteIndex, UINT iImageIndex, int bUpdateShape );
			static void SetSpriteUV ( UINT iSpriteIndex, float u1, float v1, float u2, float v2, float u3, float v3, float u4, float v4 );
			static void ResetSpriteUV( UINT iSpriteIndex );
			
			static UINT GetSpriteExists ( UINT iSpriteIndex );
			static float GetSpriteX ( UINT iSpriteIndex );
			static float GetSpriteY ( UINT iSpriteIndex );
			static float GetSpriteXByOffset ( UINT iSpriteIndex );
			static float GetSpriteYByOffset ( UINT iSpriteIndex );
			static float GetSpriteWidth ( UINT iSpriteIndex );
			static float GetSpriteHeight ( UINT iSpriteIndex );
			static float GetSpriteAngle ( UINT iSpriteIndex );
			static float GetSpriteAngleRad ( UINT iSpriteIndex );
			static int GetSpriteHitTest ( UINT iSpriteIndex, float x, float y );
			static int GetSpriteDepth( UINT iSpriteIndex );
			static UINT GetSpriteColorRed( UINT iSpriteIndex );
			static UINT GetSpriteColorGreen( UINT iSpriteIndex );
			static UINT GetSpriteColorBlue( UINT iSpriteIndex );
			static UINT GetSpriteColorAlpha( UINT iSpriteIndex );
			static int GetSpritePlaying( UINT iSpriteIndex );
			static int GetSpriteVisible( UINT iSpriteIndex );
			static int GetSpriteActive( UINT iSpriteIndex );
			static int GetSpriteGroup( UINT iSpriteIndex );

			static float GetSpriteXFromPixel( UINT iSpriteIndex, int x );
			static float GetSpriteYFromPixel( UINT iSpriteIndex, int y );
			static int GetSpritePixelFromX( UINT iSpriteIndex, float x );
			static int GetSpritePixelFromY( UINT iSpriteIndex, float y );

			static void SetSpriteSize( UINT iSpriteIndex, float width=-1, float height=-1 );
			static void SetSpriteAnimation( UINT iSpriteIndex, int iFrameWidth, int iFrameHeight, int iFrameCount );
			static void AddSpriteAnimationFrame( UINT iSpriteIndex, UINT iImageIndex );
			static void ClearSpriteAnimationFrames( UINT iSpriteIndex );
			static void SetSpriteSpeed( UINT iSpriteIndex, float fFps );
			static void PlaySprite( UINT iSpriteIndex );
			static void PlaySprite( UINT iSpriteIndex, float fFps );
			static void PlaySprite( UINT iSpriteIndex, float fFps, int iLoop );
			static void PlaySprite( UINT iSpriteIndex, float fFps, int iLoop, int iFromFrame, int iToFrame );
			static void StopSprite( UINT iSpriteIndex );
			static void ResumeSprite( UINT iSpriteIndex );
			static void SetSpriteFrame( UINT iSpriteIndex, int iFrame );
			static int GetSpriteCurrentFrame( UINT iSpriteIndex );
			static int GetSpriteFrameCount( UINT iSpriteIndex );
			static void SetSpriteTransparency( UINT iSpriteIndex, int mode );
			static void SetSpriteOffset( UINT iSpriteIndex, float x, float y );
			static void SetSpriteColor( UINT iSpriteIndex, int iRed, int iGreen, int iBlue, int iAlpha );
			static void SetSpriteColorRed( UINT iSpriteIndex, int iRed );
			static void SetSpriteColorGreen( UINT iSpriteIndex, int iGreen );
			static void SetSpriteColorBlue( UINT iSpriteIndex, int iBlue );
			static void SetSpriteColorAlpha( UINT iSpriteIndex, int iAlpha );
			static void SetSpriteUVBorder( UINT iSpriteIndex, float border );
			static void SetSpriteUVOffset( UINT iSpriteIndex, float u, float v );
			static void SetSpriteUVScale( UINT iSpriteIndex, float scaleU, float scaleV );
			static void FixSpriteToScreen( UINT iSpriteIndex, int mode );

			static void SetSpriteScale( UINT iSpriteIndex, float x, float y );
			static void SetSpriteScaleByOffset( UINT iSpriteIndex, float x, float y );
			static void SetSpriteScissor( UINT iSpriteIndex, float x, float y, float x2, float y2 );

			static void SetSpriteGroup( UINT iSpriteIndex, int group );
			static void SetSpriteCategoryBits( UINT iSpriteIndex, UINT categories );
			static void SetSpriteCategoryBit( UINT iSpriteIndex, UINT category, int flag );
			static void SetSpriteCollideBits( UINT iSpriteIndex, UINT mask );
			static void SetSpriteCollideBit( UINT iSpriteIndex, UINT category, int flag );

			static void DrawSprite( UINT iSpriteIndex );

			// physics commands
#ifdef USE_BOX2D
			static void SetPhysicsScale( float scale );
			static void SetPhysicsGravity( float x, float y );
			static void SetPhysicsDebugOn();
			static void SetPhysicsDebugOff();
			static void SetPhysicsMaxPolygonPoints( int points );
			static b2World* GetPhysicsWorld();

			static void SetPhysicsWallTop( int mode );
			static void SetPhysicsWallLeft( int mode );
			static void SetPhysicsWallRight( int mode );
			static void SetPhysicsWallBottom( int mode );
			
			// global forces
			static UINT CreatePhysicsForce( float x, float y, float power, float limit, float range, int fade );
			static void DeletePhysicsForce( UINT iForceIndex );
			static void SetPhysicsForcePosition( UINT iForceIndex, float x, float y );
			static void SetPhysicsForcePower( UINT iForceIndex, float power );
			static void SetPhysicsForceRange( UINT iForceIndex, float range );

			// sprites
			static void SetSpriteShape( UINT iSpriteIndex, int shape=3 );
			static void SetSpriteShapeBox( UINT iSpriteIndex, float x, float y, float x2, float y2, float angle=0 );
			static void SetSpriteShapeCircle( UINT iSpriteIndex, float x, float y, float radius );
			static void SetSpriteShapePolygon( UINT iSpriteIndex, UINT numPoints, UINT index, float x, float y );
			
			static void AddSpriteShapeBox( UINT iSpriteIndex, float x, float y, float x2, float y2, float angle=0 );
			static void AddSpriteShapeCircle( UINT iSpriteIndex, float x, float y, float radius );
			static void AddSpriteShapePolygon( UINT iSpriteIndex, UINT numPoints, UINT index, float x, float y );
			static void ClearSpriteShapes( UINT iSpriteIndex );

			static void SetSpritePhysicsCOM( UINT iSpriteIndex, float x, float y );
			static void CalculateSpritePhysicsCOM( UINT iSpriteIndex );

			static void SetSpritePhysicsOn( UINT iSpriteIndex, int mode=2 );
			static void SetSpritePhysicsOff( UINT iSpriteIndex );
			static void SetSpritePhysicsDelete( UINT iSpriteIndex );
			static void SetSpritePhysicsFriction( UINT iSpriteIndex, float friction );
			static void SetSpritePhysicsRestitution( UINT iSpriteIndex, float restitution );
			static void SetSpritePhysicsCanRotate( UINT iSpriteIndex, int rotate );
			static void SetSpritePhysicsVelocity( UINT iSpriteIndex, float vx, float vy );
			static void SetSpritePhysicsAngularVelocity( UINT iSpriteIndex, float va );
			static void SetSpritePhysicsDamping( UINT iSpriteIndex, float damp );
			static void SetSpritePhysicsAngularDamping( UINT iSpriteIndex, float damp );
			static void SetSpritePhysicsIsBullet( UINT iSpriteIndex, int bullet );
			static void SetSpritePhysicsMass( UINT iSpriteIndex, float mass );
			static void SetSpritePhysicsIsSensor( UINT iSpriteIndex, int sensor );
			
			static void SetSpritePhysicsForce( UINT iSpriteIndex, float x, float y, float vx, float vy );
			static void SetSpritePhysicsTorque( UINT iSpriteIndex, float torque );
			static void SetSpritePhysicsImpulse( UINT iSpriteIndex, float x, float y, float vx, float vy );
			static void SetSpritePhysicsAngularImpulse( UINT iSpriteIndex, float impulse );

			static float GetSpritePhysicsVelocityX( UINT iSpriteIndex );
			static float GetSpritePhysicsVelocityY( UINT iSpriteIndex );
			static float GetSpritePhysicsAngularVelocity( UINT iSpriteIndex );
			static float GetSpritePhysicsMass( UINT iSpriteIndex );

			// joints
			static void DeleteJoint( UINT iJointIndex );
			static int GetJointExists( UINT iJointIndex );
			static void CreateDistanceJoint( UINT iJointIndex, cSprite *pSprite1, cSprite *pSprite2, float x, float y, float x2, float y2, int colConnected=0 );
			static void CreateRevoluteJoint( UINT iJointIndex, cSprite *pSprite1, cSprite *pSprite2, float x, float y, int colConnected=0 );
			static void CreatePrismaticJoint( UINT iJointIndex, cSprite *pSprite1, cSprite *pSprite2, float x, float y, float vx, float vy, int colConnected=0 );
			static void CreatePulleyJoint( UINT iJointIndex, cSprite *pSprite1, cSprite *pSprite2, float gnd1x, float gnd1y, float gnd2x, float gnd2y, float a1x, float a1y, float a2x, float a2y, float ratio, int colConnected=0 );
			static void CreateMouseJoint( UINT iJointIndex, cSprite *pSprite1, float x, float y, float maxForce );
			static void CreateLineJoint( UINT iJointIndex, cSprite *pSprite1, cSprite *pSprite2, float x, float y, float vx, float vy, int colConnected=0 );
			static void CreateWeldJoint( UINT iJointIndex, cSprite *pSprite1, cSprite *pSprite2, float x, float y, int colConnected=0 );
			
			static void CreateDistanceJoint( UINT iJointIndex, UINT iSpriteIndex1, UINT iSpriteIndex2, float x, float y, float x2, float y2, int colConnected=0 );
			static void CreateRevoluteJoint( UINT iJointIndex, UINT iSpriteIndex1, UINT iSpriteIndex2, float x, float y, int colConnected=0 );
			static void CreatePrismaticJoint( UINT iJointIndex, UINT iSpriteIndex1, UINT iSpriteIndex2, float x, float y, float vx, float vy, int colConnected=0 );
			static void CreatePulleyJoint( UINT iJointIndex, UINT iSpriteIndex1, UINT iSpriteIndex2, float gnd1x, float gnd1y, float gnd2x, float gnd2y, float a1x, float a1y, float a2x, float a2y, float ratio, int colConnected=0 );
			static void CreateMouseJoint( UINT iJointIndex, UINT iSpriteIndex1, float x, float y, float maxForce );
			static void CreateLineJoint( UINT iJointIndex, UINT iSpriteIndex1, UINT iSpriteIndex2, float x, float y, float vx, float vy, int colConnected=0 );
			static void CreateWeldJoint( UINT iJointIndex, UINT iSpriteIndex1, UINT iSpriteIndex2, float x, float y, int colConnected=0 );

			// special joint that joins two joints
			static void CreateGearJoint( UINT iJointIndex, UINT iJoint1, UINT iJoint2, float ratio );

			// returns joint ID
			static UINT CreateDistanceJoint( cSprite *pSprite1, cSprite *pSprite2, float x, float y, float x2, float y2, int colConnected=0 );
			static UINT CreateRevoluteJoint( cSprite *pSprite1, cSprite *pSprite2, float x, float y, int colConnected=0 );
			static UINT CreatePrismaticJoint( cSprite *pSprite1, cSprite *pSprite2, float x, float y, float vx, float vy, int colConnected=0 );
			static UINT CreatePulleyJoint( cSprite *pSprite1, cSprite *pSprite2, float gnd1x, float gnd1y, float gnd2x, float gnd2y, float a1x, float a1y, float a2x, float a2y, float ratio, int colConnected=0 );
			static UINT CreateMouseJoint( cSprite *pSprite1, float x, float y, float maxForce );
			static UINT CreateLineJoint( cSprite *pSprite1, cSprite *pSprite2, float x, float y, float vx, float vy, int colConnected=0 );
			static UINT CreateWeldJoint( cSprite *pSprite1, cSprite *pSprite2, float x, float y, int colConnected=0 );
			
			static UINT CreateDistanceJoint( UINT iSpriteIndex1, UINT iSpriteIndex2, float x, float y, float x2, float y2, int colConnected=0 );
			static UINT CreateRevoluteJoint( UINT iSpriteIndex1, UINT iSpriteIndex2, float x, float y, int colConnected=0 );
			static UINT CreatePrismaticJoint( UINT iSpriteIndex1, UINT iSpriteIndex2, float x, float y, float vx, float vy, int colConnected=0 );
			static UINT CreatePulleyJoint( UINT iSpriteIndex1, UINT iSpriteIndex2, float gnd1x, float gnd1y, float gnd2x, float gnd2y, float a1x, float a1y, float a2x, float a2y, float ratio, int colConnected=0 );
			static UINT CreateMouseJoint( UINT iSpriteIndex1, float x, float y, float maxForce );
			static UINT CreateLineJoint( UINT iSpriteIndex1, UINT iSpriteIndex2, float x, float y, float vx, float vy, int colConnected=0 );
			static UINT CreateWeldJoint( UINT iSpriteIndex1, UINT iSpriteIndex2, float x, float y, int colConnected=0 );

			static void CreatePulleyJoint2( UINT iSpriteIndex1, UINT iSpriteIndex2, float ratio, int colConnected=0 );
			static UINT FinishPulleyJoint( float gnd1x, float gnd1y, float gnd2x, float gnd2y, float a1x, float a1y, float a2x, float a2y );

			// special joint that joins two joints
			static UINT CreateGearJoint( UINT iJoint1, UINT iJoint2, float ratio );

			static void SetJointLimitOn( UINT iJointIndex, float lowerLimit, float upperLimit );
			static void SetJointLimitOff( UINT iJointIndex );
			static void SetJointMotorOn( UINT iJointIndex, float speed, float maxForce );
			static void SetJointMotorOff( UINT iJointIndex );
			static void SetJointMouseTarget( UINT iJointIndex, float x, float y );

			static float GetJointReactionForceX( UINT iJointIndex );
			static float GetJointReactionForceY( UINT iJointIndex );
			static float GetJointReactionTorque( UINT iJointIndex );

			// ray casts
			static int PhysicsRayCast( float x, float y, float x2, float y2 );
			static int PhysicsRayCastGroup( int group, float x, float y, float x2, float y2 );
			static int PhysicsRayCastCategory( UINT category, float x, float y, float x2, float y2 );

			static int SpriteRayCast( float x, float y, float x2, float y2 );
			static int SpriteRayCastGroup( int group, float x, float y, float x2, float y2 );
			static int SpriteRayCastCategory( UINT category, float x, float y, float x2, float y2 );

			static int SpriteRayCastSingle( UINT sprite, float x, float y, float x2, float y2 );
			static int SpriteRayCastSingle( cSprite* sprite, float x, float y, float x2, float y2 );
			
			// ray cast return
			static UINT GetRayCastSpriteID( );
			static cSprite* GetRayCastSprite( );
			static float GetRayCastX();
			static float GetRayCastY();
			static float GetRayCastNormalX();
			static float GetRayCastNormalY();
			static float GetRayCastFraction();

			// non physics collision functions
			static int GetSpriteInBox( UINT iSprite1, float x1, float y1, float x2, float y2 );
			static int GetSpriteInCircle( UINT iSprite1, float x1, float y1, float radius );
			static int GetSpriteCollision( UINT iSprite1, UINT iSprite2 );

			static int GetSpriteHit( float x, float y );
			static int GetSpriteHitGroup( int group, float x, float y );
			static int GetSpriteHitCategory( UINT category, float x, float y );

			// non physics distance functions
			static float GetSpriteDistance( UINT iSprite1, UINT iSprite2 );
			static float GetSpriteDistancePoint1X( );
			static float GetSpriteDistancePoint1Y( );
			static float GetSpriteDistancePoint2X( );
			static float GetSpriteDistancePoint2Y( );

			// physics collision functions
			static int GetFirstContact();
			static int GetNextContact();
			static float GetContactWorldX();
			static float GetContactWorldY();
			static UINT GetContactSpriteID1();
			static UINT GetContactSpriteID2();
			static cSprite* GetContactSprite1();
			static cSprite* GetContactSprite2();

			// body contacts
			static int GetSpriteFirstContact( UINT iSprite1 );
			static int GetSpriteNextContact( );
			static float GetSpriteContactWorldX( );
			static float GetSpriteContactWorldY( );
			static UINT GetSpriteContactSpriteID2( );
			static cSprite* GetSpriteContactSprite2( );

			static int GetPhysicsCollision( UINT iSprite1, UINT iSprite2 );
			static float GetPhysicsCollisionX( );
			static float GetPhysicsCollisionY( );
			static float GetPhysicsCollisionWorldX( );
			static float GetPhysicsCollisionWorldY( );
#endif

			// particle commands
			static void CreateParticles( UINT ID, float x, float y );
			static UINT CreateParticles( float x, float y );
			static int GetParticlesExists( UINT ID );
			static void DeleteParticles( UINT ID );
			static void SetParticlesPosition( UINT ID, float x, float y );
			static void SetParticlesDepth( UINT ID, int depth );
			static void SetParticlesFrequency( UINT ID, float freq );
			static void SetParticlesStartZone( UINT ID, float x1, float y1, float x2, float y2 );
			static void SetParticlesDirection( UINT ID, float vx, float vy );
			static void SetParticlesVelocityRange( UINT ID, float v1, float v2 );
			static void SetParticlesAngle( UINT ID, float angle );
			static void SetParticlesAngleRad( UINT ID, float angle );
			static void SetParticlesSize( UINT ID, float size );
			static void SetParticlesLife( UINT ID, float time );
			static void SetParticlesMax( UINT ID, int max );
			static void ResetParticleCount( UINT ID );
			static void SetParticlesImage( UINT ID, UINT imageID );
			static void SetParticlesColorInterpolation( UINT ID, int mode );
			static void SetParticlesVisible( UINT ID, int visible );
			static void SetParticlesActive( UINT ID, int active );

			static float GetParticlesX( UINT ID );
			static float GetParticlesY( UINT ID );
			static int GetParticlesDepth( UINT ID );
			static int GetParticlesVisible( UINT ID );
			static int GetParticlesActive( UINT ID );
			static float GetParticlesFrequency( UINT ID );
			static float GetParticlesDirectionX( UINT ID );
			static float GetParticlesDirectionY( UINT ID );
			static float GetParticlesAngle( UINT ID );
			static float GetParticlesAngleRad( UINT ID );
			static float GetParticlesSize( UINT ID );
			static float GetParticlesLife( UINT ID );
			static int GetParticlesMaxReached( UINT ID );

			static void AddParticlesForce( UINT ID, float starttime, float endtime, float x, float y );
			static void ClearParticlesForces( UINT ID );
			static void AddParticlesColorKeyFrame( UINT ID, float time, UINT red, UINT green, UINT blue, UINT alpha );
			static void ClearParticlesColors( UINT ID );
			static void FixParticlesToScreen( UINT ID, int mode );

			static void UpdateParticles( UINT ID, float time );

			// text commands
			static void SetTextDefaultFontImage( UINT iImageID );
			static void SetTextDefaultExtendedFontImage( UINT iImageID );
			static void SetTextDefaultMinFilter( UINT mode );
			static void SetTextDefaultMagFilter( UINT mode );

			static void CreateText( UINT iTextIndex, const char *string );
			static UINT CreateText( const char *string );
			static void DeleteText( UINT iTextIndex );
			static void SetTextString( UINT iTextIndex, const char *string );
			static void SetTextPosition( UINT iTextIndex, float fX, float fY );
			static void SetTextX( UINT iTextIndex, float fX );
			static void SetTextY( UINT iTextIndex, float fY );
			static void SetTextSize( UINT iTextIndex, float fSize );
			static void SetTextSpacing( UINT iTextIndex, float fSpacing );
			static void SetTextLineSpacing( UINT iTextIndex, float fSpacing );
			static void SetTextDepth( UINT iTextIndex, int iDepth );
			static void SetTextVisible( UINT iTextIndex, int bVisible );
			static void SetTextAlignment( UINT iTextIndex, int mode );
			static void SetTextColor( UINT iTextIndex, UINT iRed, UINT iGreen, UINT iBlue, UINT iAlpha=255 );
			static void SetTextColorRed( UINT iTextIndex, UINT iRed );
			static void SetTextColorGreen( UINT iTextIndex, UINT iGreen );
			static void SetTextColorBlue( UINT iTextIndex, UINT iBlue );
			static void SetTextColorAlpha( UINT iTextIndex, UINT iAlpha );
			static void SetTextFontImage( UINT iTextIndex, UINT iImageID );
			static void SetTextExtendedFontImage( UINT iTextIndex, UINT iImageID );
			static void FixTextToScreen( UINT iTextIndex, int mode );
			static void SetTextMaxWidth( UINT iTextIndex, float width );
			static void SetTextScissor( UINT iTextIndex, float x, float y, float x2, float y2 );
			
			static UINT GetTextColorRed( UINT iTextIndex );
			static UINT GetTextColorGreen( UINT iTextIndex );
			static UINT GetTextColorBlue( UINT iTextIndex );
			static UINT GetTextColorAlpha( UINT iTextIndex );
			static UINT GetTextExists( UINT iTextIndex );
			static float GetTextX( UINT iTextIndex );
			static float GetTextY( UINT iTextIndex );
			static UINT GetTextLength( UINT iTextIndex );
			static float GetTextTotalWidth( UINT iTextIndex );
			static float GetTextTotalHeight( UINT iTextIndex );
			static int GetTextHitTest( UINT iTextIndex, float x, float y );
			static int GetTextVisible( UINT iTextIndex );
			static int GetTextDepth( UINT iTextIndex );
			static float GetTextSize( UINT iTextIndex );
			static char* GetTextString( UINT iTextIndex );
			static float GetTextSpacing( UINT iTextIndex );
			static float GetTextLineSpacing( UINT iTextIndex );
			
			static void SetTextCharPosition( UINT iTextIndex, UINT iCharIndex, float x, float y );
			static void SetTextCharX( UINT iTextIndex, UINT iCharIndex, float x );
			static void SetTextCharY( UINT iTextIndex, UINT iCharIndex, float y );
			static void SetTextCharAngle( UINT iTextIndex, UINT iCharIndex, float angle );
			static void SetTextCharAngleRad( UINT iTextIndex, UINT iCharIndex, float angle );
			static void SetTextCharColor( UINT iTextIndex, UINT iCharIndex, UINT red, UINT green, UINT blue, UINT alpha );
			static void SetTextCharColorRed( UINT iTextIndex, UINT iCharIndex, UINT red );
			static void SetTextCharColorGreen( UINT iTextIndex, UINT iCharIndex, UINT green );
			static void SetTextCharColorBlue( UINT iTextIndex, UINT iCharIndex, UINT blue );
			static void SetTextCharColorAlpha( UINT iTextIndex, UINT iCharIndex, UINT alpha );
			
			static float GetTextCharX( UINT iTextIndex, UINT iCharIndex );
			static float GetTextCharY( UINT iTextIndex, UINT iCharIndex );
			static float GetTextCharAngle( UINT iTextIndex, UINT iCharIndex );
			static float GetTextCharAngleRad( UINT iTextIndex, UINT iCharIndex );
			static UINT GetTextCharColorRed( UINT iTextIndex, UINT iCharIndex );
			static UINT GetTextCharColorGreen( UINT iTextIndex, UINT iCharIndex );
			static UINT GetTextCharColorBlue( UINT iTextIndex, UINT iCharIndex );
			static UINT GetTextCharColorAlpha( UINT iTextIndex, UINT iCharIndex );

			// print commands
			static void Print( const uString &string );
			static void Print( const char* szString );
			static void Print( int i );
			static void Print( UINT u );
			static void Print( float f );
			static void PrintC( const uString &string );
			static void PrintC( const char* szString );
			static void PrintC( int i );
			static void PrintC( UINT u );
			static void PrintC( float f );
			static void SetPrintSize( float fSize );
			static float GetPrintSize( void ) { return m_pPrintText->GetSize(); } // 251011
			static void SetPrintSpacing( float fSpacing );
			static void SetPrintColor( UINT iRed, UINT iGreen, UINT iBlue );
			static void SetPrintColor( UINT iRed, UINT iGreen, UINT iBlue, UINT iAlpha );

			// raw input commands
			static int GetAccelerometerExists();
			static int GetMultiTouchExists();
			static int GetMouseExists();
			static int GetKeyboardExists();
			static int GetJoystickExists();
			static int GetCameraExists();

			// touch commands
			static UINT GetRawTouchCount( int bIncludeUnknown=0 );
			static UINT GetRawFirstTouchEvent( int bIncludeUnknown=0 );
			static UINT GetRawNextTouchEvent( );
			static int GetRawTouchType( UINT iIndex );
			static float GetRawTouchStartX( UINT iIndex );
			static float GetRawTouchStartY( UINT iIndex );
			static float GetRawTouchCurrentX( UINT iIndex );
			static float GetRawTouchCurrentY( UINT iIndex );
			static float GetRawTouchLastX( UINT iIndex );
			static float GetRawTouchLastY( UINT iIndex );
			static int GetRawTouchReleased( UINT iIndex );
			static void SetRawTouchValue( UINT iIndex, int value );
			static int GetRawTouchValue( UINT iIndex );
			static float GetRawTouchTime( UINT iIndex );

			// mouse
			static float GetRawMouseX();
			static float GetRawMouseY();
			static int GetRawMouseLeftPressed();
			static int GetRawMouseLeftState();
			static int GetRawMouseLeftReleased();
			static int GetRawMouseRightPressed();
			static int GetRawMouseRightState();
			static int GetRawMouseRightReleased();
			static void SetRawMouseVisible( int visible );
		
			// accelerometer
			static void FixOrientationByDefault();
			static float GetRawAccelX();
			static float GetRawAccelY();
			static float GetRawAccelZ();

			// joystick
			static void CompleteRawJoystickDetection();
			static int GetRawJoystickExists( UINT index );
			static float GetRawJoystickX( UINT index );
			static float GetRawJoystickY( UINT index );
			static float GetRawJoystickZ( UINT index );
			static float GetRawJoystickRX( UINT index );
			static float GetRawJoystickRY( UINT index );
			static float GetRawJoystickRZ( UINT index );
			static int GetRawJoystickButtonPressed( UINT index, UINT button );
			static int GetRawJoystickButtonState( UINT index, UINT button );
			static int GetRawJoystickButtonReleased( UINT index, UINT button );
			static void SetRawJoystickDeadZone( float threshold );

			// virtual joysticks
			static void AddVirtualJoystick( UINT index, float x, float y, float size );
			static void DeleteVirtualJoystick( UINT index );
			static int GetVirtualJoystickExists( UINT index );
			static float GetVirtualJoystickX( UINT index );
			static float GetVirtualJoystickY( UINT index );
			static void SetVirtualJoystickAlpha( UINT index, UINT alpha1, UINT alpha2 );
			static void SetVirtualJoystickPosition( UINT index, float x, float y );
			static void SetVirtualJoystickSize( UINT index, float size );
			static void SetVirtualJoystickActive( UINT index, int active );
			static void SetVirtualJoystickVisible( UINT index, int visible );
			static void SetVirtualJoystickImageInner( UINT index, UINT imageID );
			static void SetVirtualJoystickImageOuter( UINT index, UINT imageID );
			static void SetVirtualJoystickDeadZone( float threshold );
			
			// virtual buttons
			static void AddVirtualButton( UINT index, float x, float y, float size );
			static void DeleteVirtualButton( UINT index );
			static int GetVirtualButtonExists( UINT index );
			static int GetVirtualButtonPressed( UINT index );
			static int GetVirtualButtonReleased( UINT index );
			static int GetVirtualButtonState( UINT index );
			static void SetVirtualButtonColor( UINT index, UINT red, UINT green, UINT blue );
			static void SetVirtualButtonAlpha( UINT index, UINT alpha );
			static void SetVirtualButtonPosition( UINT index, float x, float y );
			static void SetVirtualButtonSize( UINT index, float size );
			static void SetVirtualButtonActive( UINT index, int active );
			static void SetVirtualButtonVisible( UINT index, int visible );
			static void SetVirtualButtonImageUp( UINT index, UINT imageID );
			static void SetVirtualButtonImageDown( UINT index, UINT imageID );
			static void SetVirtualButtonText( UINT index, const char *str );

			// keyboard
			static int GetRawKeyPressed( UINT key );
			static int GetRawKeyState( UINT key );
			static int GetRawKeyReleased( UINT key );
			static int GetRawLastKey();
		
			// AGK emulated input commands
			static int GetPointerPressed();
			static int GetPointerState();
			static int GetPointerReleased();
			static int GetPointerGesture();
			static float GetPointerX();
			static float GetPointerY();

			static float GetDirectionX();
			static float GetDirectionY();
			static float GetDirectionAngle();
			static float GetDirectionSpeed();

			static float GetJoystickX();
			static float GetJoystickY();
			static void SetJoystickScreenPosition( float x, float y, float size );
			static void SetJoystickDeadZone( float threshold );

			static int GetButtonPressed( UINT index );
			static int GetButtonState( UINT index );
			static int GetButtonReleased( UINT index );
			static void SetButtonScreenPosition( UINT index, float x, float y, float size );

			// text input
			static void StartTextInput( );
            static void StartTextInput( const char* initial );
			static void StopTextInput( );
			static int GetTextInputState();
			static int GetTextInputCompleted();
			static int GetTextInputCancelled();
			static char* GetTextInput();
			static int GetTextInput( uString &out );
			static UINT GetPrevChar();
			static UINT GetLastChar();
			static void SetCursorBlinkTime( float seconds );
			static void SetTextInputMaxChars( int max=0 );
			static void SetTextInputLabel( const char* str );

			// edit boxes
			static void CreateEditBox( UINT index );
			static UINT CreateEditBox();
			static int GetEditBoxExists( UINT index );
			static void DeleteEditBox( UINT index );
			static int GetEditBoxHasFocus( UINT index );
			static UINT GetCurrentEditBox();
			static void SetEditBoxPosition( UINT index, float x, float y );
			static void SetEditBoxSize( UINT index, float width, float height );
			static void SetEditBoxDepth( UINT index, int depth );
			static void SetEditBoxBorderSize( UINT index, float size );
			static void SetEditBoxBorderColor( UINT index, UINT red, UINT green, UINT blue, UINT alpha );
			static void SetEditBoxBackgroundColor( UINT index, UINT red, UINT green, UINT blue, UINT alpha );
			static void SetEditBoxText( UINT index, const char *str ); // 120212 - paul notice, how a command name which is contained in another similar command MUST be placed first!!
			static void SetEditBoxTextColor( UINT index, UINT red, UINT green, UINT blue );
			static void SetEditBoxCursorColor( UINT index, UINT red, UINT green, UINT blue );
			static void SetEditBoxFontImage( UINT index, UINT image );
			static void SetEditBoxTextSize( UINT index, float size );
			static void SetEditBoxFocus( UINT index, int iActive );
			static void SetEditBoxActive( UINT index, int iActive );
			static void SetEditBoxVisible( UINT index, int iActive );
			static void SetEditBoxBorderImage( UINT index, UINT image );
			static void SetEditBoxBackgroundImage( UINT index, UINT image );
			static void SetEditBoxCursorBlinkTime( UINT index, float time );
			static void SetEditBoxCursorWidth( UINT index, float width );
			static void SetEditBoxMaxChars( UINT index, UINT max );
			static void SetEditBoxMaxLines( UINT index, UINT max );
			static void SetEditBoxMultiLine( UINT index, int mulitline );
			static void SetEditBoxScissor( UINT index, float x, float y, float x2, float y2 );
			static void FixEditBoxToScreen( UINT index, int fix );
			static char* GetEditBoxText( UINT index );
			static float GetEditBoxX( UINT index );
			static float GetEditBoxY( UINT index );
			static float GetEditBoxWidth( UINT index );
			static float GetEditBoxHeight( UINT index );
			static int GetEditBoxChanged( UINT index );
			static int GetEditBoxActive( UINT index );
			static int GetEditBoxVisible( UINT index );
			static int GetEditBoxLines( UINT index );

			// sound comands
			static void LoadSound( UINT iID, const char* sImageFilename );
			static UINT LoadSound( const char* sImageFilename );
			static void LoadSound( UINT iID, const uString &sFile );
			static UINT LoadSound( const uString &sFile );
			static void PlaySound( UINT iID );
			static void PlaySound( UINT iID, int iVol );
			static void PlaySound( UINT iID, int iVol, int iLoop );
			static void PlaySound( UINT iID, int iVol, int iLoop, int iPriority );
			static void StopSound( UINT iID );
			static void DeleteSound( UINT iID );
			static UINT GetSoundInstances( UINT iID );
			static UINT GetSoundsPlaying( UINT iID );
			static void SetSoundSystemVolume( int iVol );
			static UINT GetSoundExists( UINT iID );

			// music comands
			static UINT LoadMusic( const char* sFile );
			static void LoadMusic( UINT iID, const char* sFile );
			static void SetMusicFileVolume( UINT ID, int vol );
			static void PlayMusic( );
			static void PlayMusic( UINT iID );
			static void PlayMusic( UINT iID, int bLoop );
			static void PlayMusic( UINT iID, int bLoop, UINT iStartID, UINT iEndID );
			static void PauseMusic( );
			static void ResumeMusic( );
			static void StopMusic( );
			static void DeleteMusic( UINT iID );
			static int GetMusicPlaying();
			static void SetMusicSystemVolume( int iVol );
			static UINT GetMusicExists( UINT iID );

			// file system commands
			static void SetRawWritePath( const char *str );
			static char* GetWritePath();

			static char* ChooseRawFile( const char* ext );

			static int GetFileExists( const char *szFile );
			static void DeleteFile( const char *szFile );
			
			static UINT OpenToWrite( const char *szFile, int append );
			static void OpenToWrite( UINT ID, const char *szFile, int append );
			static UINT OpenToWrite( const char *szFile );
			static void OpenToWrite( UINT ID, const char *szFile );			
			
			static UINT OpenToRead( const char *szFile );
			static void OpenToRead( UINT ID, const char *szFile );

			static int FileIsOpen( UINT ID );
			static void CloseFile( UINT iFileID );
			static int FileEOF( UINT iFileID );
			static int GetFileSize( UINT iFileID );
			
			static void WriteInteger( UINT iFileID, int i );
			static void WriteFloat( UINT iFileID, float f );
			static void WriteString( UINT iFileID, const char* str );
			static void WriteLine( UINT iFileID, const char* str );

			static int ReadInteger( UINT iFileID );
			static float ReadFloat( UINT iFileID );
			static char* ReadString( UINT iFileID );
			static char* ReadLine( UINT iFileID );

			// directory commands
			static int SetCurrentDir( const char* );
			static char* GetCurrentDir();
			static int SetFolder( const char* );
			static char* GetFolder();

			static int MakeFolder( const char* );
			static void DeleteFolder( const char* );
			
			static char* GetFirstFolder();
			static char* GetNextFolder();

			static char* GetFirstFile();
			static char* GetNextFile();

			// broadcast commands
			static UINT CreateBroadcastListener( UINT port );
			static void DeleteBroadcastListener( UINT iID );
			static UINT GetBroadcastMessage( UINT iID );

			// network commands
			static UINT HostNetwork( const char *szNetworkName, const char *szMyName, UINT port );
			static void SetNetworkNoMoreClients( UINT iNetID );

			static UINT JoinNetwork( const char *szNetworkName, const char *szMyName );
			static UINT JoinNetwork( const char *szIP, UINT port, const char *szMyName );

			static UINT IsNetworkActive( UINT iNetID );

			static void CloseNetwork( UINT iNetID );
			static void SetNetworkLatency( UINT iNetID, UINT latency );

			static UINT GetNetworkMyClientID( UINT iNetID );
			static UINT GetNetworkNumClients( UINT iNetID );
			static UINT GetNetworkFirstClient( UINT iNetID );
			static UINT GetNetworkNextClient( UINT iNetID );

			static UINT GetNetworkClientDisconnected( UINT iNetID, UINT client );
			static void DeleteNetworkClient( UINT iNetID, UINT client );
			static char* GetNetworkClientName( UINT iNetID, UINT client );
			static float GetNetworkClientPing( UINT iNetID, UINT client );
			static UINT GetNetworkServerID( UINT iNetID );
			
			static void SetNetworkLocalInteger( UINT iNetID, const char *name, int i );
			static void SetNetworkLocalInteger( UINT iNetID, const char *name, int i, int mode );
			static void SetNetworkLocalFloat( UINT iNetID, const char *name, float f );
			static void SetNetworkLocalFloat( UINT iNetID, const char *name, float f, int mode );
			static int GetNetworkClientInteger( UINT iNetID, UINT client, const char *name );
			static float GetNetworkClientFloat( UINT iNetID, UINT client, const char *name );

			static UINT CreateNetworkMessage( );
			static void AddNetworkMessageInteger( UINT iMsgID, int value );
			static void AddNetworkMessageFloat( UINT iMsgID, float value );
			static void AddNetworkMessageString( UINT iMsgID, const char *value );
			static char* GetNetworkMessageFromIP( UINT iMsgID );
			static UINT GetNetworkMessageFromClient( UINT iMsgID );
			static int GetNetworkMessageInteger( UINT iMsgID );
			static float GetNetworkMessageFloat( UINT iMsgID );
			static char* GetNetworkMessageString( UINT iMsgID );
			static void DeleteNetworkMessage( UINT iMsgID );

			static void SendNetworkMessage( UINT iNetID, UINT toClient, UINT iMsgID );
			static UINT GetNetworkMessage( UINT iNetID );
			
			static void SetNetworkClientUserData( UINT iNetID, UINT client, UINT index, int value );
			static int GetNetworkClientUserData( UINT iNetID, UINT client, UINT index );

			// HTTP commands
			static UINT CreateHTTPConnection();
			static void DeleteHTTPConnection( UINT iHTTP );

			static UINT SetHTTPHost( UINT iHTTP, const char *szHost, int iSecure );
			static UINT SetHTTPHost( UINT iHTTP, const char *szHost, int iSecure, const char *szUser, const char *szPass );
			static void CloseHTTPConnection( UINT iHTTP );
			
			static char* SendHTTPRequest( UINT iHTTP, const char *szServerFile ); //blocks
			static char* SendHTTPRequest( UINT iHTTP, const char *szServerFile, const char *szPostData ); //blocks
			static int SendHTTPRequestASync( UINT iHTTP, const char *szServerFile ); //does not block
			static int SendHTTPRequestASync( UINT iHTTP, const char *szServerFile, const char *szPostData ); //does not block
			static int SendHTTPFile( UINT iHTTP, const char *szServerFile, const char *szPostData, const char *szLocalFile ); //does not block
			static char* GetHTTPResponse( UINT iHTTP ); // 120112 - notice the shorter command goes first (for AGK compiler)
			static int GetHTTPResponseReady( UINT iHTTP );
			static const char* GetHTTPResponseC( UINT iHTTP );
			static int GetHTTPFile( UINT iHTTP, const char *szServerFile, const char *szLocalFile ); //does not block
			static int GetHTTPFile( UINT iHTTP, const char *szServerFile, const char *szLocalFile, const char *szPostData ); //does not block
			static int GetHTTPFileComplete( UINT iHTTP );
			static float GetHTTPFileProgress( UINT iHTTP );
        
            static void OpenBrowser( const char* url );
		
			// string commands
			static char* Str( int value );
			static char* Str( float value );
			static char* Str( float value, UINT decimals );
			static char* Bin( int i );
			static char* Hex( int i );
			static int Val( const char* str );
			static int Val( const char* str, int base );
			static float ValFloat( const char* str );
			static char* Left ( const char* str, UINT count );
			static char* Right ( const char* str, UINT count );
			static char* Mid ( const char* str, UINT count, int length );
			static UINT Asc ( const char* str );
			static UINT Len ( const char* str );
			static char* Chr ( UINT iCharValue );
			static char* Lower ( const char* str );
			static char* Upper ( const char* str );
			static char* Spaces ( UINT count );
			static int CountStringTokens( const char* str, const char* delimit );
			static char* GetStringToken( const char* str, const char* delimit, int token );

			// benchmarking
			static UINT GetManagedSpriteCount();
			static UINT GetManagedSpriteSortedCount();
			static UINT GetManagedSpriteDrawnCount();
			static UINT GetPixelsDrawn();
			static UINT GetManagedSpriteDrawCalls();

			static UINT GetParticleDrawnPointCount();
			static UINT GetParticleDrawnQuadCount();

			static float GetUpdateTime();
			static float GetPhysicsTime();
			static float GetDrawingSetupTime();
			static float GetDrawingTime();

			// date/time
			static int GetYearFromUnix64( INT64 unixtime, int* daysinyear=0 );
			static int GetMonthFromUnix64( INT64 unixtime );
			static int GetDayFromUnix64( INT64 unixtime );
			static int GetHoursFromUnix64( INT64 unixtime );
			static int GetMinutesFromUnix64( INT64 unixtime );
			static int GetSecondsFromUnix64( INT64 unixtime );
			static INT64 GetUnixFromDate64( int year, int month, int days, int hours, int minutes, int seconds );
			static INT64 GetUnixTime64();

			// tier 1 does not support 64 bit values, dates above 2038 will overflow
			static int GetYearFromUnix32( int unixtime, int* daysinyear=0 );
			static int GetYearFromUnix( int unixtime ); // 090112 - T1 not allowed - int* daysinyear=0 );
			static int GetMonthFromUnix( int unixtime );
			static int GetDaysFromUnix( int unixtime );
			static int GetHoursFromUnix( int unixtime );
			static int GetMinutesFromUnix( int unixtime );
			static int GetSecondsFromUnix( int unixtime );
			static int GetUnixFromDate( int year, int month, int days, int hours, int minutes, int seconds );
			static int GetUnixTime();

			static int GetLeapYear( int year );
			static char* GetCurrentDate();
			static char* GetCurrentTime();
			static int GetDayOfWeek();

			// adverts
			static void SetInneractiveDetails( const char* szCode );
			static void CreateAdvert( int type, int horz, int vert, int test );
			static void SetAdvertPosition( float x, float y, float width );
			static void SetAdvertLocation( int horz, int vert, float width );
			static void DeleteAdvert( );

			// zip functions
			static void CreateZip( UINT zipID, const char* filename );
			static UINT CreateZip( const char* filename );
			static void AddZipEntry( UINT zipID, const char* path, const char* zipPath );
			static void CloseZip( UINT zipID );

			static void ExtractZip( const char* zipfilename, const char* path );

			// memblock functions
			static UINT CreateMemblock( UINT size );
			static void CreateMemblock( UINT memID, UINT size );
			static int GetMemblockExists( UINT memID );
			static void DeleteMemblock( UINT memID );

			// 3d objects
			static void CreateObjectBox( UINT objID, float width, float height, float length );
			static UINT CreateObjectBox( float width, float height, float length );
	};
}

#endif
