// Common Header
#ifndef _H_COMMON_
#define _H_COMMON_

// Platform : Windows
#ifdef IDE_VS2008
	// disable deprecation warning
	#pragma warning(disable:4995)

	//#ifdef _DEBUG
		#define _AGK_ERROR_CHECK
	//#endif

	#include <windows.h>
	#include <stdio.h>
	#include <gl\gl.h>								// Header File For The OpenGL32 Library
	#include <gl\glu.h>								// Header File For The GLu32 Library.
	#include "..\..\platform\windows\Source\glext.h"
	#include <WinSock.h>
	#include <math.h>
	#include <cassert>
	#include <sys/types.h>
	#include <sys/stat.h>
	#include <wininet.h>
	#include <time.h>

	#ifndef GL_CLAMP_TO_EDGE
		#define GL_CLAMP_TO_EDGE  0x812F
	#endif

	#ifdef LoadImage
		#undef LoadImage
	#endif

	#ifdef SendMessage
		#undef SendMessage
	#endif

	#ifdef GetMessage
		#undef GetMessage
	#endif
	
	#ifndef glOrthof	
		#define glOrthof glOrtho
	#endif

	#ifndef glClearDepthf	
		#define glClearDepthf glClearDepth
	#endif

	#ifndef _EXPORT_
		#define _EXPORT_ 
	#endif

	#define STDCALL __stdcall

	#define USE_BOX2D

	#ifndef INT64
		#define INT64 __int64
	#endif
#endif

// Platform : Samsung BADA
#ifdef IDE_BADA

	// 050411 for some reason DWORD and LONGLONG stopped compiling on the Mac (for iOS)?!?
	#define DWORD UINT
	#define LONGLONG UINT
	#define LPSTR char*

	//#ifdef _DEBUG
		#define _AGK_ERROR_CHECK
	//#endif

	#include <FBase.h>
	#include <FMedia.h>
	#include <FApp.h>
	#include <FBase.h>
	#include <FGraphics.h>
	#include <FSystem.h>
	#include <FGraphicsOpengl.h>
	#include <FUi.h>
	#include <FUix.h>
	#include <FIoDirectory.h>
	#include <FNet.h>
	#include <FBaseRtThreadThread.h>
	#include <FIoFile.h>
	#include <FTextUtf8Encoding.h>
	#include <FUiCtrlKeypad.h>
	#include <stdio.h>
	#include <math.h>	
	#include <stdarg.h>
	#include <FUiCtrlPopup.h>

	using namespace Osp::App;
	using namespace Osp::Base;
	using namespace Osp::System;
	using namespace Osp::Graphics;
	using namespace Osp::Graphics::Opengl;
	using namespace Osp::Ui;
	using namespace Osp::Ui::Controls;
	using namespace Osp::Uix;
	using namespace Osp::Media;
	using namespace Osp::Base::Runtime;
	using namespace Osp::Base::Utility;
	using namespace Osp::Io;
	using namespace Osp::Net;
	using namespace Osp::Net::Sockets;

	#define USE_BOX2D

	#ifndef _EXPORT_
		#define _EXPORT_ 
	#endif

	#define sprintf(a,...)    snprintf(a,1024,__VA_ARGS__)
	#define vsprintf(a,...)    vsnprintf(a,1024,__VA_ARGS__)

	#define STDCALL

	#define MAX_PATH 1024

	#ifndef INT64
		#define INT64 int
	#endif
#endif

// Platform : Apple iPhone / iPad
#ifdef IDE_XCODE

	// 050411 for some reason DWORD and LONGLONG stopped compiling on the Mac (for iOS)?!?
	#define DWORD UINT
	#define LONGLONG UINT
	#define LPSTR char*

	//#ifdef DEBUG
		#define _AGK_ERROR_CHECK
	//#endif

	#import <Availability.h>
	#import <Foundation/Foundation.h>
	#import <UIKit/UIKit.h>
	#import <QuartzCore/QuartzCore.h>
	#import <OpenGLES/EAGL.h>
	#import <OpenGLES/ES1/gl.h>
	#import <OpenGLES/ES1/glext.h>
	#import <OpenGLES/EAGLDrawable.h>
	#import <AudioToolbox/AudioToolbox.h>
	#import <AVFoundation/AVFoundation.h>
	#import <OpenAL/al.h>
	#import <OpenAL/alc.h>

	#include "string.h"
	#include <math.h>
	#include <netinet/in.h>
	#include <netinet/tcp.h>	
	#include <unistd.h>
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <arpa/inet.h>
	#include <sys/ioctl.h>
	#include <sys/stat.h>

	#define USE_BOX2D

	#ifndef _EXPORT_
		#define _EXPORT_ 
	#endif

	#define INVALID_SOCKET -1
	#define SOCKET_ERROR -1
	#define STDCALL

	#define MAX_PATH PATH_MAX

	#ifndef INT64
		#define INT64 __int64_t
	#endif
#endif

// Platform : Mac
#ifdef IDE_MAC

	//#ifdef DEBUG
		#define _AGK_ERROR_CHECK
	//#endif

	#import <Cocoa/Cocoa.h>

	#include <stdio.h>
	#include <stdlib.h>
	#include <stdarg.h>
	#include <string.h>
	#include <math.h>
	#include "../../platform/mac/GLFW/glfw.h"
	#include <sys/time.h>
	#include <OpenAL/al.h>
	#include <OpenAL/alc.h>
	#include <mach/mach_time.h>
	#include <mach-o/dyld.h>
	#include <netinet/in.h>
	#include <netinet/tcp.h>	
	#include <sys/param.h>
	#include <unistd.h>
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <arpa/inet.h>
	#include <sys/ioctl.h>
	#include <sys/stat.h>

	#define USE_BOX2D

	#ifndef _EXPORT_
		#define _EXPORT_ 
	#endif

	#ifndef glOrthof	
		#define glOrthof glOrtho
	#endif

	#ifndef glClearDepthf	
		#define glClearDepthf glClearDepth
	#endif

	#define INVALID_SOCKET -1
	#define SOCKET_ERROR -1
	#define STDCALL
	#define MAX_PATH 1024

	// these are used in interpreter, can replace them if need be
	#define DWORD UINT
	#define LONGLONG UINT
	#define LPSTR char*

	#ifndef INT64
		#define INT64 int
	#endif

#endif

// Platform : Nackle
#ifdef IDE_NACKLE
	
#endif

// Platform : MeeGo
#ifdef IDE_MEEGO

	#include <stdio.h>
	#include <stdlib.h>
	#include <stdarg.h>
	#include <string.h>
	#include <math.h>
	#include <cassert>

	#include <QtGui>
	#include <QtOpenGL>
	#include <QGLWidget>
	#include <QtNetwork>

	#define _AGK_ERROR_CHECK
	//#define USE_BOX2D //included in .PRO file(s)

	// these are used in interpreter, can replace them if need be
        #define DWORD unsigned long // conflicts with UINT (insigned int) because of Print ( DWORD )
	#define LONGLONG unsigned int
	#define HWND unsigned int
	#define LPSTR char*

	#ifndef _EXPORT_
		#define _EXPORT_
	#endif

	#define STDCALL

	#define MAX_PATH 512

	#ifndef INT64
		#define INT64 int
	#endif

#endif

#ifdef IDE_ANDROID
	#define _AGK_ERROR_CHECK

	#include <stdio.h>
	#include <string.h>
	#include <jni.h>
	#include <stdlib.h>
	#include <math.h>
	#include <netinet/in.h>
	#include <netinet/tcp.h>	
	#include <unistd.h>
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <arpa/inet.h>
	#include <sys/ioctl.h>
	#include <sys/stat.h>
	#include <fcntl.h>
	#include <unistd.h>
	#include <pthread.h>

	#include <EGL/egl.h>
	#include <GLES/gl.h>

	#define USE_BOX2D

	#ifndef _EXPORT_
		#define _EXPORT_
	#endif

	#define MAX_PATH 512
	#define INVALID_SOCKET -1
	#define SOCKET_ERROR -1
	#define STDCALL

	// these are used in interpreter, can replace them if need be
	#define DWORD UINT
	#define LONGLONG UINT
	#define LPSTR char*

	#define INT64 int
#endif

#ifdef IDE_BLACKBERRY
	#define _AGK_ERROR_CHECK

	#include <EGL/egl.h>
	#include <screen/screen.h>
	#include <sys/platform.h>
	#include <GLES/gl.h>
	#include <GLES/glext.h>

	#include <ctype.h>
	#include <unistd.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <sys/keycodes.h>
	#include <assert.h>
	#include <bps/accelerometer.h>
	#include <bps/navigator.h>
	#include <bps/screen.h>
	#include <bps/bps.h>
	#include <bps/event.h>
	#include <bps/orientation.h>
	#include <bps/virtualkeyboard.h>
	#include <math.h>
	#include <time.h>
	#include <screen/screen.h>

	#include <netinet/in.h>
	#include <netinet/tcp.h>
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <arpa/inet.h>
	#include <sys/ioctl.h>
	#include <sys/stat.h>
	#include <fcntl.h>
	#include <pthread.h>
	#include <stdarg.h>

	// Open AL
	#include <AL/al.h>
	#include <AL/alc.h>

	// Media Player
	#include <bps/mmrenderer.h>

	#define USE_BOX2D

	#ifndef _EXPORT_
		#define _EXPORT_
	#endif

	#define MAX_PATH 512
	#define INVALID_SOCKET -1
	#define SOCKET_ERROR -1
	#define STDCALL

	// these are used in interpreter, can replace them if need be
	#define DWORD UINT
	#define LONGLONG UINT
	#define LPSTR char*

	#ifndef INT64
		#define INT64 int
	#endif
#endif

// Other Platforms : XBOX, Android, WinMobile7 (not part of common architecture)

#endif // _H_COMMON_
