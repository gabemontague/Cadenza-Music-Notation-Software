// Project: Music Structure Template
// File: global.h	
// by Gabe Montague © 2013

#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#define PROGRAM_TITLE "Cadenza"
#define MAX_DRAW 2047

float printVal = -256;
bool exitOnError = false;

// User interaction variables
float clickStartX = -1;
float clickStartY = -1;
float clickStartViewX = -1;
float clickStartViewY = -1;
float viewMargin = 1000;
int zoomTimer = 0;
float mouseX;
float mouseY;
float mouseXPrev;
float mouseYPrev;
float mouseAngle;
float mouseDistance;

// The current screen mode enum
enum appScreenEnum{ LAUNCHER, MAIN, PREFERENCES } appScreen = MAIN;

// Automatic calculation of page, SS, etc.
const int ac = -1;

#define MAX_TABS 31
#define MAX_PAGES 511 // Per tab
#define MAX_GESTURES 10 // Per tab
#define MAX_PAGETEXT_PER_PAGE 255
#define MAX_PAGETEXT_LENGTH 255
#define MAX_STAFF_SYSTEM_PER_PAGE 31
#define MAX_STAVE_PER_STAFF_SYSTEM 255
#define MAX_BARLINE_PER_STAFF_SYSTEM 127
#define MAX_FILENAME_LENGTH 63
#define MAX_NOTE_PER_BARLINE 127
#define MIN_SUBDIV_SPACING 5

// Project-specific variables:
char title[MAX_PAGETEXT_LENGTH] = "My Score";
char composer[MAX_PAGETEXT_LENGTH] = "Gabe Montague";
char copyright[MAX_PAGETEXT_LENGTH] = " 2013";

// Preferences
const float textTabMargin = 40;
const float tabBarHeight = 22;
const float tabPadding = 10;
bool tabBarOK = true; // Has to do with color

const float pageWidth = 850;
const float pageHeight = 1100;
const float pagePadding = 20;
const float pageMarginX = 65;
const float pageMarginY = 80;
const float firstPageSSIndendation = 50;
const float firstPageSSHeight = 200;

const float staffSystemSpacing = 100;

const float intraStaveSpacing = 85;
const float lineSpacing = 8; // The space between the lines
const float staveHeight = 4 * lineSpacing; // The height of the stave

const float barOffset = 16; // The space between a barline and the first note
const bool showSubBarLines = true;

const float noteSize = 0.4f; // Scale value, not absolute

const int bgColR = 128;
const int bgColG = 128;
const int bgColB = 130;

//const int bgColR = 151;
//const int bgColG = 151;
//const int bgColB = 151;
//const int bgGrad = 0;

const float drawThickness = 0.5f;

// Sprite templates
unsigned int playHeadID;
unsigned int fontCentury;
unsigned int sprPage;
unsigned int sprLine;
unsigned int sprTabBG;
unsigned int sprNoteHeadSolid;
unsigned int sprNoteHeadHalf;
unsigned int sprNoteHeadWhole;
unsigned int sprNoteHeadDoubleWhole;
unsigned int sprDraw;
unsigned int sprDrawPivot;

// Misc
enum clefEnum { TREBLE, BASS, ALTO, TENOR, TREBLE_SUB, TREBLE_SUPER, BASS_SUB, BASS_SUPER, FRENCH_VIOLIN, BARITONE_C, MEZZO_SOPRANO, SOPRANO, BARITONE_F };

//*****************************************************************************
// Classes

struct note;
struct barLine;
struct stave;
struct staffSystem;
struct pageText;
struct page;
struct tab;
struct gesture;

// NOTE OBJECT
enum noteLetterEnum{ nC, nD, nE, nF, nG, nA, nB };
enum noteAccidentalEnum{ naSHARP, naDOUBLESHARP, naFLAT, naDOUBLEFLAT, naNATURAL, naNONE, naNATURALSHARP, naNATURALFLAT };
enum noteHeadTypeEnum{ SOLID, HALF, WHOLE, DOUBLEWHOLE };
struct note
{
	// Parents
	barLine* parentPtr;
	stave* parentStavePtr;
	
	// Position
	float x;
	float y;
	
	// Letter name
	noteLetterEnum letterName;
	
	// Accidental
	noteAccidentalEnum accidental;
	
	// Octave
	char octave;
	
	// Pitch
	int pitchLetter;
	
	// Size
	float size;
	
	// Clef
	clefEnum clef;
	
	// Notehead type
	noteHeadTypeEnum noteHeadType;
	
	// Sprite
	unsigned int spriteID;
};

// BARLINE OBJECT
enum barLineModeEnum{ SS_BEGIN, SS_END, BAR, SUBDIV };
struct barLine
{
	// Note: barLine objects are mostly invisible, representing an X-time relationship point
	
	// Parent
	staffSystem* parentPtr;
	
	// Time
	double time;
	
	// Position
	float x;
	float xLocal;
	
	// Visible
	bool visibility;
	
	// Whether or not it marks the end/beginning of a staffSystem
	barLineModeEnum barLineMode;
	
	unsigned int spriteID;
	
	// Note children
	int numNotes;
	note* notePtr[MAX_NOTE_PER_BARLINE];
};

// STAVE OBJECT
struct stave
{
	// Parent
	staffSystem* parentPtr;
	
	// Position
	float y;
	float yLocal;
	
	// Sprites
	unsigned int spriteID[5];
};

// STAFF-SYSTEM OBJECT
struct staffSystem
{
	// Parent
	page* parentPtr;
	
	// Time
	double timeStart; // Time should be an unsigned long of the number of measures
	double timeEnd;
	double duration;
	
	// Position
	float x;
	float xLocal;
	float y;
	float yLocal;
	
	// Dimensions
	float width;
	float height;
	
	// Whether or not it is uncoupled and unwritten-upon
	bool virgin;
	
	// It's start-line sprite
	unsigned int startLineSpriteID;
	
	// Stave children
	int numStaves;
	stave* stavePtr[MAX_STAVE_PER_STAFF_SYSTEM];
	
	// Bar line children
	int numBarLines;
	barLine* barLinePtr[MAX_BARLINE_PER_STAFF_SYSTEM];
};

// PAGE TEXT OBJECT
struct pageText
{
	// Parent
	page* parentPtr;
	
	// Text object
	unsigned int textID;
	
	// Position
	float x;
	float xLocal;
	float y;
	float yLocal;
	
	// Editable
	bool eEditable;
};

// PAGE OBJECT
struct page
{
	// Parent
	tab* parentPtr;
	
	// Position
	float x;
	float y;
	
	// Sprite
	unsigned int spriteID;
	
	// Pointer to child pageText objects
	int numPageTexts;
	pageText* pageTextPtr[MAX_PAGETEXT_PER_PAGE];
	
	// Pointer to child staffSystem objects
	int numStaffSystems;
	staffSystem* staffSystemPtr[MAX_STAFF_SYSTEM_PER_PAGE];
};

// TAB OBJECT
enum typeEnum{ MUSIC_FULL, MUSIC_FREE, TEXT, DRAWING };
enum pageViewEnum{ SPREAD, COLUMN, DOUBLE_COLUMN };
struct tab
{
	// Name
	char name [MAX_FILENAME_LENGTH];
	
	// The type of data that the tab holds
	typeEnum type;
	
	// The page view mode
	pageViewEnum pageView;
	
	// Pointer to child page objects
	int numPages;
	int currentPage;
	int frontierSS;
	int frontierPage;
	double playHeadPosition;
    double playHeadSpeed;
	int playHeadPage;
	int playHeadSS;
	page* pagePtr[MAX_PAGES];
	
	// Gesture objects
	int numGestures;
	gesture* gesturePtr[MAX_GESTURES];
	
	// Editbox ID
	unsigned int ebID;
	
	// Bar info
	unsigned int barTextID;
	
	// View position, zoom
	float viewX;
	float viewY;
	float viewZoom;
};

// GESTURE OBJECT
struct gesture
{
	// Parent
	tab* parentPtr;
	
	// Children sprites
	unsigned int drawID[MAX_DRAW];
	unsigned int pointID[MAX_DRAW];
	int numDraws;
	int numPoints;
	
	// Page
	int pageNum;
	
	// Recognition information
	float minX;
	float minY;
	float maxX;
	float maxY;
	
	float x;
	float y;
	float xStart;
	float yStart;
	float xEnd;
	float yEnd;
	
	float width;
	float height;
	float length;
};

//*****************************************************************************

// Note
void NewNote( int pageNum, int ssNum, int barLineNum, int staveNum, noteLetterEnum letter, char octaveNum, noteAccidentalEnum accidentalName );
float CalculateNoteRelativePositionY( clefEnum clef, int pitchLetter, float ntSize, noteHeadTypeEnum type );
int CalculateNotePitchLetter( clefEnum clef, float y, float ntSize, noteHeadTypeEnum type );
void CorrectNotePosition( int pageNum, int ssNum, int barLineNum, int noteNum );
void DeleteNote( int pageNum, int ssNum, int barLineNum, int noteNum );

// Bar line
void NewBarLine( int pageNum, int ssNum, float xPos, double timePos, bool visible, barLineModeEnum mode );
void NewBarLineSplitStaffSystem( int pageNum, int ssNum, float xPos );
void NewBarLineSplitStaffSystemPercent( int pageNum, int ssNum, float percent );
void NewBarLineSplitMeasure( int pageNum, int ssNum, float xPos, double timeFromLast );
void NewBarLineSplitMeasurePercent( int pageNum, int ssNum, int measureNum, float percent, double timeFromLast );
void MoveBarLine( int pageNum, int ssNum, int barLineNum, float xPos );
void CorrectBarLinePosition( int pageNum, int ssNum, int barLineNum );
void DeleteBarLine( int pageNum, int ssNum, int barLineNum );

// Stave
void NewStave( int pageNum, int ssNum );
void MoveStave( int pageNum, int ssNum, int staveNum, float yPos );
void DeleteStave( int pageNum, int ssNum, int staveNum );

// Staff system
void NewStaffSystem( int pageNum, float xPos, float yPos );
void MoveStaffSystem( int pageNum, int ssNum, float xPos, float yPos );
void ShiftStaffSystemTime( int pageNum, int ssNum, float relativeShift );
void PushStaffSystemToNext( int pageNum, int ssNumStart );
void PushStaffSystemToPrevious( int pageNum, int ssNumLast );
void PushStaffSystemBackToPage( int pageNum, int destPageNum );
int ArrangeStaffSystemsOnPage( int pageNum, int ssNumStart );
void ArrangeStaffSystems( int pageNumStart, int ssNumStart );
void PopulateBlankStaffSystems( void );
void DeleteBlankStaffSystems( void );
void UpdateStaffSystemHeight( int pageNum, int ssNum );
void DeleteStaffSystem( int pageNum, int ssNum );

// Page text
int NewPageText( int pageNum, float xPos, float yPos, char tText[MAX_PAGETEXT_LENGTH] );
void DeletePageText( int pageNum, int textNum );

// Page
void NewPage( void );
void MovePage( int pageNum, float xPos, float yPos );
void ArrangePages( void );
void HidePage( int pageNum );
void ShowPage( int pageNum );
void DeletePage( void );

// Tab
int currentTab; // Note: First page is 0
tab* tabPtr[MAX_TABS];
int numTabs = 0;

void NewTab( typeEnum tType );
void HideTabContent( int tabNum );
void ShowTabContent( int tabNum );
void SwitchTab( int tabNum );
void ArrangeTabBar( void );
void DeleteTab( int tabNum );

// Gesture
void NewGesture( void );
void RecognizeGesture( void );
void ClearGestures( void );

// Pointer macros
#define tbPtr tabPtr[currentTab]
#define gsPtr(a) (tabPtr[currentTab]->gesturePtr[a])
#define pgPtr(a) (tabPtr[currentTab]->pagePtr[a])
#define ssPtr(a,b) (tabPtr[currentTab]->pagePtr[a]->staffSystemPtr[b])
#define ptPtr(a,b) (tabPtr[currentTab]->pagePtr[a]->pageTextPtr[b])
#define blPtr(a,b,c) (tabPtr[currentTab]->pagePtr[a]->staffSystemPtr[b]->barLinePtr[c])
#define svPtr(a,b,c) (tabPtr[currentTab]->pagePtr[a]->staffSystemPtr[b]->stavePtr[c])
#define ntPtr(a,b,c,d) (tabPtr[currentTab]->pagePtr[a]->staffSystemPtr[b]->barLinePtr[c]->notePtr[d])

#define gsPtrActive (tabPtr[currentTab]->gesturePtr[tabPtr[currentTab]->numGestures - 1])

// Conversion functions
int returnPage;
int returnSS;
int returnBarLine;
int returnStave;
int returnNote;

float barLineDistance;
float ssDistance;
float staveDistance;

int ConvertPointToPage( float x, float y );
int ConvertPointToNearestAll( float x, float y );
int ConvertGlobalSSToLocal( int ssNumGlobal );
int ConvertLocalSSToGlobal( int pageNum, int ssNum );
int ConvertGlobalBarLineToLocal( int barLineNumGlobal );
int ConvertGlobalMeasureToLocal( int measureNumGlobal );

void ACConvert( int &pageNum, int &ssNum );
void ACConvert( int &pageNum, int &ssNum, int &barLineNum );

// Misc
void MainCreateNew( void );
void LoadImagesSprites( void );
void Error( NSString* string );
void UpdatePlayHead( double timeTarget );
float Distance( float x1, float y1, float x2, float y2 );
float DistanceSqr( float x1, float y1, float x2, float y2 );

// Control
void ViewControl( void );
void ViewControlLimitView( void );
void TabControl( void );
void DrawOnPage( void ); 
void MainShortcutsControl( void );

#endif