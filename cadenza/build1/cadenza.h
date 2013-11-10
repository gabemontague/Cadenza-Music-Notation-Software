// Project: Music Structure Template
// File: cadenza.h	
// by Gabe Montague © 2013

#ifndef _H_APP
#define _H_APP

// Link to AGK libraries
#include "agk.h"

// Global values for the app
class app
{
	public:

		// main vars
		unsigned int m_DeviceWidth;
		unsigned int m_DeviceHeight;

	public:

		// constructor
		app() { memset ( this, 0, sizeof(app)); }

		// main app functions
		void Begin( void );
		void Loop( void );
		void End( void );
};

extern app App;

#endif

// Allow us to use the LoadImage function name
#ifdef LoadImage
 #undef LoadImage
#endif
