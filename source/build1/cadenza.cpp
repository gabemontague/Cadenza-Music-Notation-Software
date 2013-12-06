// Project: Music Structure Template
// File: cadenza.cpp	
// by Gabe Montague © 2013

#include "cadenza.h"
#include <string.h>
using namespace AGK;
app App;

#include "global.h"

// UTILITY
void LoadSounds( void )
{
    sndTick = agk::LoadSound( "drip.wav" );
    sndNote[0] = agk::LoadSound("C4.wav" );
    sndNote[1] = agk::LoadSound("D4.wav" );
    sndNote[2] = agk::LoadSound("E4.wav" );
    sndNote[3] = agk::LoadSound("F4.wav" );
    sndNote[4] = agk::LoadSound("G4.wav" );
    sndNote[5] = agk::LoadSound("A4.wav" );
    sndNote[6] = agk::LoadSound("B4.wav" );
    sndNote[7] = agk::LoadSound("C5.wav" );
    sndNote[8] = agk::LoadSound("D5.wav" );
    sndNote[9] = agk::LoadSound("E5.wav" );
    sndNote[10] = agk::LoadSound("F5.wav" );
    sndNote[11] = agk::LoadSound("G5.wav" );
}
void LoadImagesSprites( void )
{
	// Preload images
	fontCentury = agk::LoadImage( "fontDefault.png" );
	
	// Preloads images into sprites for lag-less cloning
	
	int img = agk::LoadImage( "page.jpg" );
	sprPage = agk::CreateSprite( img );
	agk::SetSpritePosition( sprPage, -10000, -10000 );
	
	img = agk::LoadImage( "line.jpg" );
	sprLine = agk::CreateSprite( img );
	agk::SetSpritePosition( sprLine, -10000, -10000 );
	
	img = agk::LoadImage( "tabbgchrome.png" );
	sprTabBG = agk::CreateSprite( img );
	agk::SetSpritePosition( sprTabBG, -10000, -10000 );
	
	img = agk::LoadImage("noteheadSolid.png");
	sprNoteHeadSolid = agk::CreateSprite( img );
	agk::SetSpritePosition( sprNoteHeadSolid, -10000, -10000 );
	
	img = agk::LoadImage("noteheadHalf.png");
	sprNoteHeadHalf = agk::CreateSprite( img );
	agk::SetSpritePosition( sprNoteHeadHalf, -10000, -10000 );
	
	img = agk::LoadImage("noteheadWhole.png");
	sprNoteHeadWhole = agk::CreateSprite( img );
	agk::SetSpritePosition( sprNoteHeadWhole, -10000, -10000 );
	
	img = agk::LoadImage("noteheadDoubleWhole.png");
	sprNoteHeadDoubleWhole = agk::CreateSprite( img );
	agk::SetSpritePosition( sprNoteHeadDoubleWhole, -10000, -10000 );
	
	img = agk::LoadImage("drawLine.png");
	sprDraw = agk::CreateSprite( img );
	agk::SetSpritePosition( sprDraw, -10000, -10000 );
	
	img = agk::LoadImage("drawLinePivot.png");
	sprDrawPivot = agk::CreateSprite( img );
	agk::SetSpritePosition( sprDrawPivot, -10000, -10000 );
	
	// Playhead
	playHeadID = agk::CloneSprite( sprLine );
	agk::SetSpriteColor( playHeadID, 204, 102, 255, 255 );
	agk::SetSpriteDepth( playHeadID, 9 );
}
void Error( NSString* string )
{
	NSAlert *alert = [[[NSAlert alloc] init] autorelease];
	[alert setAlertStyle:NSCriticalAlertStyle];
	[alert setMessageText:string];
	[alert runModal];
	
	if( exitOnError ) exit( 0 );
}
unsigned int sound[512] = {0};
unsigned int numPlaying = 0;
void UpdatePlayHead( double timeTarget )
{
	// Cycle through pages
	for( int a = 0; a < tbPtr->numPages; a++ )
	{
		for( int b = 0; b < pgPtr( a )->numStaffSystems; b++ )
		{
			staffSystem* target = ssPtr( a, b );
			if( target->timeStart < timeTarget && target->timeEnd > timeTarget )
			{
				// We have found the staff system
				tbPtr->playHeadPage = a;
				tbPtr->playHeadSS = b;
				for( int c = 0; c < target->numBarLines; c++ )
				{
					if( target->barLinePtr[c]->time > timeTarget )
					{
						// We have reached the first one that is passed.
						float rightX = target->barLinePtr[c]->x;
						float leftX = target->barLinePtr[c-1]->x;
						double rightTime = target->barLinePtr[c]->time;
						double leftTime = target->barLinePtr[c-1]->time;
						
						// LERP between the two barlines
						float percentage = ( timeTarget - leftTime ) / ( rightTime - leftTime );
						float newX = leftX + ( rightX - leftX ) * percentage;
						
						agk::SetSpritePosition( playHeadID, newX, target->y );
						agk::SetSpriteScale( playHeadID, 1, target->height );
						agk::SetSpriteColor( playHeadID, 204, 0, 204, 255 );
						
                        // Play a note
                        if(percentage <= tabPtr[currentTab]->playHeadSpeed)
                        {
                            // Check if there is a note to play
                            if(target->barLinePtr[c-1]->numNotes > 0)
                            {
                                // There is. Stop previous sounds.
                                if(numPlaying > 0)
                                {
                                    for (int ii = 0; ii < numPlaying; ii++ )
                                    {
                                        agk::StopSound(sound[ii]);
                                    }
                                    numPlaying = 0;
                                }
                                
                                // Add new sounds
                                for (int d = 0; d < target->barLinePtr[c-1]->numNotes; d++)
                                {
                                    note * currentNote = target->barLinePtr[c-1]->notePtr[d];
                                    if(currentNote->pitchLetter == 21) sound[numPlaying] = sndNote[0];
                                    if(currentNote->pitchLetter == 22) sound[numPlaying] = sndNote[1];
                                    if(currentNote->pitchLetter == 23) sound[numPlaying] = sndNote[2];
                                    if(currentNote->pitchLetter == 24) sound[numPlaying] = sndNote[3];
                                    if(currentNote->pitchLetter == 25) sound[numPlaying] = sndNote[4];
                                    if(currentNote->pitchLetter == 26) sound[numPlaying] = sndNote[5];
                                    if(currentNote->pitchLetter == 27) sound[numPlaying] = sndNote[6];
                                    if(currentNote->pitchLetter == 28) sound[numPlaying] = sndNote[7];
                                    if(currentNote->pitchLetter == 29) sound[numPlaying] = sndNote[8];
                                    if(currentNote->pitchLetter == 30) sound[numPlaying] = sndNote[9];
                                    if(currentNote->pitchLetter == 31) sound[numPlaying] = sndNote[10];
                                    if(currentNote->pitchLetter == 32) sound[numPlaying] = sndNote[11];
                                    agk::PlaySound(sound[numPlaying]);
                                    numPlaying++;
                                }
                            }
                        }
                        
						break;
					}
				}
				break;
			}
		}
	}
}
float Distance( float x1, float y1, float x2, float y2 )
{
	return ( agk::Sqrt( ( x1 - x2 ) * ( x1 - x2 ) + ( y1 - y2 ) * ( y1 - y2 ) ) );
}
float DistanceSqr( float x1, float y1, float x2, float y2 )
{
	// Returns the sqare of the distance (the dot product of the difference vector) in order to be slightly faster in comparisons
	return ( ( x1 - x2 ) * ( x1 - x2 ) + ( y1 - y2 ) * ( y1 - y2 ) );
}

// NOTE
void NewNote( int pageNum, int ssNum, int barLineNum, int staveNum, noteLetterEnum letter, char octaveNum, noteAccidentalEnum accidentalName )
{	
	unsigned int sprID = -1;
	
	ACConvert( pageNum, ssNum, barLineNum );
	
	// Create the object
	const int numNotesLocal = blPtr( pageNum, ssNum, barLineNum )->numNotes;
	note* target = blPtr( pageNum, ssNum, barLineNum)->notePtr[numNotesLocal] = new note;
	blPtr( pageNum, ssNum, barLineNum )->numNotes++;
	
	// Set the object's initial values
	// Tell the new object its parents
	target->parentPtr = blPtr( pageNum, ssNum, barLineNum );
	target->parentStavePtr = svPtr( pageNum, ssNum, staveNum );
	target->letterName = letter;
	target->accidental = accidentalName;
	target->octave = octaveNum;
	target->spriteID = -1;
	target->size = noteSize * lineSpacing / 8;
	target->pitchLetter = target->octave * 7 + target->letterName;
	target->x = target->parentPtr->x - target->size / 0.4f * 5;
	target->noteHeadType = SOLID;
	target->clef = TREBLE;
	target->y = target->parentStavePtr->y + CalculateNoteRelativePositionY( target->clef, target->pitchLetter, target->size, target->noteHeadType );
	
	// Create image
	switch( target->noteHeadType )
	{
		case SOLID:
			sprID = target->spriteID = agk::CloneSprite( sprNoteHeadSolid );
			break;
		case HALF:
			sprID = target->spriteID = agk::CloneSprite( sprNoteHeadHalf );
			break;
		case WHOLE:
			sprID = target->spriteID = agk::CloneSprite( sprNoteHeadWhole );
			break;
		case DOUBLEWHOLE:
			sprID = target->spriteID = agk::CloneSprite( sprNoteHeadDoubleWhole );
			break;
	}
	agk::SetSpriteDepth( sprID, 50 );

	agk::SetSpriteOffset( sprID, 0.5, 0.5 );
	agk::SetSpriteScale( sprID, target->size, target->size );
	agk::SetSpritePosition( sprID, target->x, target->y );
	
	returnPage = pageNum;
	returnSS = ssNum;
	returnBarLine = barLineNum;
	returnStave = staveNum;
	returnNote = numNotesLocal;
}
float CalculateNoteRelativePositionY( clefEnum clef, int pitchLetter, float ntSize, noteHeadTypeEnum type )
{
	float returnVal = -1;
	int offsetPitchLetter;
	
	switch( clef )
	{
		case TREBLE:
			offsetPitchLetter = 31;
			break;
		case BASS:
			offsetPitchLetter = 19;
			break;
		case ALTO:
			offsetPitchLetter = 25;
			break;
		case TENOR:
			offsetPitchLetter = 23;
			break;
		case TREBLE_SUB:
			offsetPitchLetter = 24;
			break;
		case TREBLE_SUPER:
			offsetPitchLetter = 38;
			break;
		case BASS_SUB:
			offsetPitchLetter = 5;
			break;
		case BASS_SUPER:
			offsetPitchLetter = 26;
			break;
		case FRENCH_VIOLIN:
			offsetPitchLetter = 33;
			break;
		case BARITONE_C:
			offsetPitchLetter = 21;
			break;
		case MEZZO_SOPRANO:
			offsetPitchLetter = 27;
			break;
		case SOPRANO:
			offsetPitchLetter = 29;
			break;
		case BARITONE_F:
			offsetPitchLetter = 21;
			break;
	}
	
	// Offset
	returnVal = -1 - (( pitchLetter - offsetPitchLetter ) * lineSpacing / 2 + 4.77f * ntSize / 0.4f );
	if( type == DOUBLEWHOLE ) returnVal -= 2.5f;
	
	return returnVal;
}
int CalculateNotePitchLetter( clefEnum clef, float y, float ntSize, noteHeadTypeEnum type )
{
	float returnVal = -1;
	int offsetPitchLetter;
	
	if( type == DOUBLEWHOLE ) returnVal += 2.5f;
	
	switch( clef )
	{
		case TREBLE:
			offsetPitchLetter = 31;
			break;
		case BASS:
			offsetPitchLetter = 19;
			break;
		case ALTO:
			offsetPitchLetter = 25;
			break;
		case TENOR:
			offsetPitchLetter = 23;
			break;
		case TREBLE_SUB:
			offsetPitchLetter = 24;
			break;
		case TREBLE_SUPER:
			offsetPitchLetter = 38;
			break;
		case BASS_SUB:
			offsetPitchLetter = 5;
			break;
		case BASS_SUPER:
			offsetPitchLetter = 26;
			break;
		case FRENCH_VIOLIN:
			offsetPitchLetter = 33;
			break;
		case BARITONE_C:
			offsetPitchLetter = 21;
			break;
		case MEZZO_SOPRANO:
			offsetPitchLetter = 27;
			break;
		case SOPRANO:
			offsetPitchLetter = 29;
			break;
		case BARITONE_F:
			offsetPitchLetter = 21;
			break;
	}
	
	// Offset
	returnVal = round( ( ( -y - 1 ) - 4.77f * ntSize / 0.4f ) * 2 / lineSpacing + offsetPitchLetter );
	
	return returnVal;
}
void CorrectNotePosition( int pageNum, int ssNum, int barLineNum, int noteNum )
{
	ACConvert( pageNum, ssNum, barLineNum );
	
	// Error checking
	if( pageNum >= tbPtr->numPages ) Error( @"Error in function CorrectNotePosition: page does not exist." );
	if( ssNum >= pgPtr( pageNum )->numStaffSystems ) Error( @"Error in function CorrectNotePosition: staff system does not exist." );
	if( barLineNum >= ssPtr( pageNum, ssNum )->numBarLines ) Error( @"Error in function CorrectNotePosition: bar line does not exist." );
	if( noteNum >= blPtr( pageNum, ssNum, barLineNum )->numNotes ) Error( @"Error in function CorrectNotePosition: note does not exist." );
	
	note* target = ntPtr( pageNum, ssNum, barLineNum, noteNum );
	
	if( target != NULL )
	{
		target->x = target->parentPtr->x - target->size / 0.4f * 5;
		target->y = target->parentStavePtr->y + CalculateNoteRelativePositionY( target->clef, target->pitchLetter, target->size, target->noteHeadType );
		agk::SetSpritePosition( target->spriteID, target->x, target->y );
	}
	else Error( @"Error in function CorrectNotePosition: note pointer is blank!" );
}
void DeleteNote( int pageNum, int ssNum, int barLineNum, int noteNum )
{
	ACConvert( pageNum, ssNum, barLineNum );
	
	// Error checking
	if( pageNum >= tbPtr->numPages ) Error( @"Error in function DeleteNote: page does not exist." );
	if( ssNum >= pgPtr( pageNum )->numStaffSystems ) Error( @"Error in function DeleteNote: staff system does not exist." );
	if( barLineNum >= ssPtr( pageNum, ssNum )->numBarLines ) Error( @"Error in function DeleteNote: bar line does not exist." );
	if( noteNum >= blPtr( pageNum, ssNum, barLineNum )->numNotes ) Error( @"Error in function DeleteNote: note does not exist." );
	
	note* target = ntPtr( pageNum, ssNum, barLineNum, noteNum );
	
	if( target != NULL )
	{
		// Delete connnection with parent
		target->parentPtr->numNotes--;
		
		// Delete the sprites associated
		agk::DeleteSprite( target->spriteID );
		
		// Free from memory
		delete target;
		
		// This creates a NULL gap in the bar line's array of note objects, so shift everything down
		for( int a = barLineNum; a < MAX_NOTE_PER_BARLINE - 1; a++ )
		{
			blPtr( pageNum, ssNum, barLineNum )->notePtr[a] = blPtr( pageNum, ssNum, barLineNum )->notePtr[a+1];
			if( blPtr( pageNum, ssNum, barLineNum )->notePtr[a+1] == NULL ) break;
		}
	}
	else Error( @"Error in function DeleteNote: note pointer is blank!" );
}

// BARLINE
void NewBarLine( int pageNum, int ssNum, float xPos, double timePos, bool visible, barLineModeEnum mode )
{
	ACConvert( pageNum, ssNum );
	
	int lineID = -1;

	// Create the object
	const int numBarLinesLocal = ssPtr( pageNum, ssNum )->numBarLines;
	barLine* target = ssPtr( pageNum, ssNum )->barLinePtr[numBarLinesLocal] = new barLine;
	ssPtr( pageNum, ssNum )->numBarLines++;
	
	// Set the object's initial values
	// Tell the new object its parent
	target->parentPtr = ssPtr( pageNum, ssNum );
	target->x = xPos;
	target->xLocal = xPos - target->parentPtr->x;
	target->time = timePos;
	target->visibility = visible;
	target->barLineMode = mode;
	target->numNotes = 0;
	target->spriteID = -1;
	for( int a = 0; a < MAX_NOTE_PER_BARLINE; a++ ) target->notePtr[a] = NULL;
	
	// Create line if its visible
	if( visible )
	{
		lineID = target->spriteID = agk::CloneSprite( sprLine );
		const staffSystem* parent = target->parentPtr;

		agk::SetSpritePosition( lineID, target->x, parent->y );
		
		agk::SetSpriteDepth( target->spriteID, 60 );

		// Use the SS height method to calculate the height of the barline
		agk::SetSpriteScale( lineID, 1, parent->height );
		
		// (Debug) color coding
		if( target->barLineMode == BAR ) agk::SetSpriteColor( lineID, 0, 0, 0, 255 );
		if( target->barLineMode == SUBDIV ) agk::SetSpriteColor( lineID, 200, 200, 200, 255 );
		if( target->barLineMode == SS_BEGIN ) agk::SetSpriteColor( lineID, 0, 200, 0, 255 );
		if( target->barLineMode == SS_END ) agk::SetSpriteColor( lineID, 0, 0, 0, 255 );
	}
	
	returnPage = pageNum;
	returnSS = ssNum;
	returnBarLine = numBarLinesLocal;
}
void NewBarLineSplitStaffSystem( int pageNum, int ssNum, float xPos )
{
	ACConvert( pageNum, ssNum );
	
	staffSystem* ssTarget = ssPtr( pageNum, ssNum );
	
	if( xPos < ssTarget->barLinePtr[0]->x + barOffset ) Error( @"Error in function NewBarLineSplitStaffSystem: new bar line is too far to the left." );
	
	// Cycle through and find the spot where it goes
	const int iterations = ssTarget->numBarLines;
	int a = 0;
	bool reachedEnd = false;

	for( a = 0; a < iterations; a++ )
	{
		barLine* target = ssTarget->barLinePtr[a];
		
		// Check if the cycler has passed the spot where the new bar line will go.
		if( target->x > xPos )
		{
			// Must account for crammed spacing
			if( target->x - xPos < barOffset ) xPos -= barOffset * 2;

			reachedEnd = true;
			break;
		}
	}
	
	if( !reachedEnd ) Error( @"Error in function NewBarLineSplitStaffSystem: new bar line is too far to the right." );
	
	// Variable 'a' now holds the the barLine number that is the first one past where the new will go
	double newTime = ssTarget->barLinePtr[a]->time; // The barline's new time will be the old one's
	
	// Start with this first one past and shift everything up
	ssTarget->numBarLines += 1;
	for( int b = iterations - 1; b >= a ; b-- )
	{
		ssTarget->barLinePtr[b+1] = ssTarget->barLinePtr[b];
	
		// Shift the time up by 1 measure
		ssTarget->barLinePtr[b+1]->time += 1;
	}
	
	// In order to create the new barLine at a custom position, we fool the function by temporarily setting numBarLines to something else
	int oldNumBarLine = ssTarget->numBarLines;
	ssTarget->numBarLines = a;
	NewBarLine( pageNum, ssNum, xPos, newTime, true,  BAR );
	ssTarget->numBarLines = oldNumBarLine;
	
	// Update parent SS
	ssTarget->duration += 1;
	ssTarget->timeEnd += 1;
	
	// Shift the time of all future SS's
	for( int a = pageNum; a < tbPtr->numPages; a++ )
	{
		for( int b = a == pageNum ? ssNum + 1 : 0; b <  tbPtr->pagePtr[a]->numStaffSystems; b++ )
		{
			ShiftStaffSystemTime( a, b, 1 );
		}
	}
}
void NewBarLineSplitStaffSystemPercent( int pageNum, int ssNum, float percent )
{
	ACConvert( pageNum, ssNum );
	
	staffSystem* ssTarget = ssPtr( pageNum, ssNum );
	
	float xPos = ssTarget->x + ssTarget->width * percent / 100;

	NewBarLineSplitStaffSystem( pageNum, ssNum, xPos );
}
void NewBarLineSplitMeasure( int pageNum, int ssNum, float xPos, double timeFromLast )
{
	ACConvert( pageNum, ssNum );
	
	staffSystem* ssTarget = ssPtr( pageNum, ssNum );
	
	if( xPos < ssTarget->x ) Error( @"Error in function NewBarLineSplitMeasure: new bar line is too far to the left." );
	
	// Cycle through and find the spot where it goes
	const int iterations = ssTarget->numBarLines;
	int a = 0;
	int closestBarLine = -1;
	float minDst = 1000000;
	bool snapAbort = false; // Becomes true when a snap can be performed instead of actually creating a new bar line
	bool needNewSSBegin = false; // True if a new SS begin needs to be created (not snapped)
	
	for( a = 0; a < iterations; a++ )
	{
		barLine* target = ssTarget->barLinePtr[a];
		
		// Check if the cycler has passed the spot where the new bar line will go and is the closest yet.
		if( target->x - xPos < minDst && target->x - xPos > 0 )
		{
			// Must account for crammed spacing
			if( target->x - xPos < MIN_SUBDIV_SPACING ) xPos -= MIN_SUBDIV_SPACING;
			if( a != 0 )
			{
				if( xPos - ssTarget->barLinePtr[a - 1]->x < MIN_SUBDIV_SPACING ) xPos += MIN_SUBDIV_SPACING;
			}
			minDst = target->x - xPos;
			closestBarLine = a;
		}
	}
	
	if( closestBarLine == -1 ) Error( @"Error in function NewBarLineSplitMeasure: new bar line is too far to the right." );
	
	// Variable 'closestBarLine' and 'a' now hold the the barLine number that is the first one past where the new will go
	a = closestBarLine;
	
	
	
	// Determine if SS_BEGIN bar line snapping may be used
	// Check if a blank default SS_BEGIN bar line exists to the immediate right.
	if( ssTarget->barLinePtr[a]->barLineMode == SS_BEGIN && ssTarget->barLinePtr[a]->numNotes == 0 )
	{
		snapAbort = true;
	}
	
	// Check if a blank default SS_BEGIN bar line exists to the immediate left.
	if( ssTarget->barLinePtr[a]->barLineMode != SS_BEGIN && !snapAbort )
	{
		if( ssTarget->barLinePtr[a - 1]->barLineMode == SS_BEGIN && ssTarget->barLinePtr[a - 1]->numNotes == 0 ) snapAbort = true;
	}
	
	// Start with this first one past and shift everything up if needed (except time)
	if( !snapAbort )
	{
		ssTarget->numBarLines++;
		for( int b = iterations - 1; b >= a ; b-- )
		{
			ssTarget->barLinePtr[b+1] = ssTarget->barLinePtr[b];
			
			// Check if a blank default SS_BEGIN bar line exists to the immediate left
			if( ssTarget->barLinePtr[b+1]->barLineMode == SS_BEGIN )
			{
				// We have dropped a barLine before the SS_START in this case, but cannot snap it
				if( ssTarget->barLinePtr[b+1]->barLineMode == SUBDIV )
				agk::SetSpriteColor( ssTarget->barLinePtr[b+1]->spriteID, 200, 200, 200, 255 );
				needNewSSBegin = true;
			}
		}
		
		// Shift time values up until you run into a bar or an end line
		bool shiftingUpTime = true;
		for( int b = a + 1; b < iterations + 1; b++ )
		{
			if( ssTarget->barLinePtr[b]->barLineMode == SS_END || ssTarget->barLinePtr[b]->barLineMode == BAR ) shiftingUpTime = false;
			if( shiftingUpTime ) ssTarget->barLinePtr[b]->time += timeFromLast;
		}
	
		// Make the new bar line if we can't snap to avoid it
		double newTime;
		if( needNewSSBegin ) newTime = ssTarget->timeStart;
		else
		{
			newTime = ssTarget->barLinePtr[a-1]->time + timeFromLast;
			if( ssTarget->barLinePtr[a-1]->barLineMode == BAR )
			{
				// If it's follwing a bar, then get rid of timeFromLast
				newTime = ssTarget->barLinePtr[a-1]->time -= timeFromLast;
			}
		}
		
		// In order to create the new barLine at a custom position, we fool the function by temporarily setting numBarLines to something else
		int oldNumBarLine = ssTarget->numBarLines;
		ssTarget->numBarLines = a;
		NewBarLine( pageNum, ssNum, xPos, newTime, showSubBarLines,  needNewSSBegin ? SS_BEGIN : SUBDIV );
		ssTarget->numBarLines = oldNumBarLine;
		returnBarLine = a;
	}
	
	// Snap to avoid having to make a new bar line
	if( snapAbort )
	{
		returnBarLine = 0;
		MoveBarLine( pageNum, ssNum, 0, xPos );
	}
	returnPage = pageNum;
	returnSS = ssNum;
}
void NewBarLineSplitMeasurePercent( int pageNum, int ssNum, int measureNum, float percent, double timeFromLast )
{
    // DEVELOP MORE: This assumes that the first 2 arguments are ac
	ConvertGlobalMeasureToLocal( measureNum );
	int barLineNum = returnBarLine;
	pageNum = returnPage;
	ssNum = returnSS;
	ConvertGlobalMeasureToLocal( measureNum + 1 );
	int nextBarLineNum = returnBarLine; // Holds next measure barLine, not
	//if( nextBarLineNum != 0 ) nextBarLineNum--;

	float xPos;

	staffSystem* ssTarget = ssPtr( pageNum, ssNum );
	
	if( returnSS != ssNum ) nextBarLineNum = ssTarget->numBarLines - 1;
	
	barLine* target = blPtr( pageNum, ssNum, barLineNum );
	barLine* nextTarget = blPtr( pageNum, ssNum, nextBarLineNum );
	
	xPos = target->x + ( nextTarget->x - target->x ) * percent / 100;
    
	NewBarLineSplitMeasure( pageNum, ssNum, xPos, timeFromLast );
}
void MoveBarLine( int pageNum, int ssNum, int barLineNum, float xPos )
{
	ACConvert( pageNum, ssNum, barLineNum );
	
	// Error checking
	if( pageNum >= tbPtr->numPages ) Error( @"Error in function MoveBarLine: page does not exist." );
	if( ssNum >= pgPtr( pageNum )->numStaffSystems ) Error( @"Error in function MoveBarLine: staff system does not exist." );
	if( barLineNum >= ssPtr( pageNum, ssNum )->numBarLines ) Error( @"Error in function MoveBarLine: bar line does not exist." );
	
	barLine* target = blPtr( pageNum, ssNum, barLineNum );
	
	if( target != NULL )
	{
		target->x = xPos;
		target->xLocal = xPos - target->parentPtr->x;
		agk::SetSpritePosition( target->spriteID, target->x, target->parentPtr->y );
		
		// Move the child notes
		for( int a = 0; a < target->numNotes; a++ )
		{
			CorrectNotePosition( pageNum, ssNum, barLineNum, a );
		}
	}
	else Error( @"Error in function MoveBarLine: barLine pointer is blank!" );
}
void CorrectBarLinePosition( int pageNum, int ssNum, int barLineNum )
{
	ACConvert( pageNum, ssNum, barLineNum );
	
	// Error checking
	if( pageNum >= tbPtr->numPages ) Error( @"Error in function CorrectBarLinePosition: page does not exist." );
	if( ssNum >= pgPtr( pageNum )->numStaffSystems ) Error( @"Error in function CorrectBarLinePosition: staff system does not exist." );
	if( barLineNum >= ssPtr( pageNum, ssNum )->numBarLines ) Error( @"Error in function CorrectBarLinePosition: bar line does not exist." );
	
	barLine* target = blPtr( pageNum, ssNum, barLineNum );
	
	if( target != NULL )
	{
		target->x = target->parentPtr->x + target-> xLocal;
		agk::SetSpritePosition( target->spriteID, target->x, target->parentPtr->y );
		
		// Move the child notes
		for( int a = 0; a < target->numNotes; a++ )
		{
			CorrectNotePosition( pageNum, ssNum, barLineNum, a );
		}
	}
	else Error( @"Error in function CorrectBarLinePosition: barLine pointer is blank!" );
}
void DeleteBarLine( int pageNum, int ssNum, int barLineNum )
{
	ACConvert( pageNum, ssNum, barLineNum );
	
	// Error checking
	if( pageNum >= tbPtr->numPages ) Error( @"Error in function DeleteBarLine: page does not exist." );
	if( ssNum >= pgPtr( pageNum )->numStaffSystems ) Error( @"Error in function DeleteBarLine: staff system does not exist." );
	if( barLineNum >= ssPtr( pageNum, ssNum )->numBarLines ) Error( @"Error in function DeleteBarLine: bar line does not exist." );
	
	barLine* target = blPtr( pageNum, ssNum, barLineNum );
	
	if( target != NULL )
	{		
		// Delete all children
		int iterations = target->numNotes;
		for( int a = 0; a < iterations; a++ )
		{
			DeleteNote( pageNum, ssNum, barLineNum, 0 );
		}
		
		// Delete connnection with parent
		target->parentPtr->numBarLines--;
		
		// Delete the sprites associated
		if( target->visibility )
		{
			agk::DeleteSprite( target->spriteID );
		}
		
		// Free from memory
		delete target;
		
		// This creates a NULL gap in the SS's array of barLine objects, so shift everything down
		for( int a = barLineNum; a < MAX_BARLINE_PER_STAFF_SYSTEM - 1; a++ )
		{
			ssPtr( pageNum, ssNum )->barLinePtr[a] = ssPtr( pageNum, ssNum )->barLinePtr[a+1];
			if( ssPtr( pageNum, ssNum )->barLinePtr[a+1] == NULL ) break;
		}
	}
	else Error( @"Error in function DeleteBarLine: barLine pointer is blank!" );
}
// STAVE
void NewStave( int pageNum, int ssNum )
{
	ACConvert( pageNum, ssNum );
	
	const int numStavesLocal = ssPtr( pageNum, ssNum )->numStaves;
	
	// If adding one to be coupled, update frontier
	if( numStavesLocal > 0 )
	{
		ssPtr( pageNum, ssNum )->virgin = false;
		if( ( tbPtr->frontierSS < ssNum && tbPtr->frontierPage == pageNum ) || ( pageNum > tbPtr->frontierPage ) )
		{
			tbPtr->frontierSS = ssNum;
			tbPtr->frontierPage = pageNum;
		}
	}
	
	// Create the object
	stave* target = ssPtr( pageNum, ssNum )->stavePtr[numStavesLocal] = new stave;
	ssPtr( pageNum, ssNum )->numStaves++;
	
	// Set the text object's initial values
	// Tell the new object its parent
	target->parentPtr = ssPtr( pageNum, ssNum );
	target->y = target->parentPtr->y + numStavesLocal * intraStaveSpacing;
	target->yLocal = target->y - target->parentPtr->y;
	
	// Create staff lines
	for( int a = 0; a < 5; a++ )
	{
		int tempID;
		tempID = target->spriteID[a] = agk::CloneSprite( sprLine );
		agk::SetSpritePosition( tempID, target->parentPtr->x, target->y + a * lineSpacing );
		agk::SetSpriteScale( tempID, target->parentPtr->width, 1 );
		agk::SetSpriteColor( tempID, 0, 0, 0, 255 );
		agk::SetSpriteDepth( tempID, 75 );
	}
	
	UpdateStaffSystemHeight( pageNum, ssNum );
	
	returnPage = pageNum;
	returnSS = ssNum;
	returnBarLine = numStavesLocal;
}
void MoveStave( int pageNum, int ssNum, int staveNum, float yPos )
{
	ACConvert( pageNum, ssNum );
	
	// Error checking
	if( pageNum >= tbPtr->numPages ) Error( @"Error in function MoveStave: page does not exist." );
	if( ssNum >= pgPtr( pageNum )->numStaffSystems ) Error( @"Error in function MoveStave: staff system does not exist." );
	if( staveNum >= ssPtr( pageNum, ssNum )->numStaves ) Error( @"Error in function MoveStave: stave does not exist." );
	
	stave* target = svPtr( pageNum, ssNum, staveNum );
	
	if( target != NULL )
	{
		target->y = yPos;
		target->yLocal = target->y - target->parentPtr->y;
		
		// Update staff lines
		for( int a = 0; a < 5; a++ )
		{
			int tempID;
			tempID = target->spriteID[a];
			agk::SetSpritePosition( tempID, target->parentPtr->x, target->y + a * lineSpacing );
			agk::SetSpriteScale( tempID, target->parentPtr->width, 1 );
		}
	}
	else Error( @"Error in function MoveStave: stave pointer is blank!" );
}
void DeleteStave( int pageNum, int ssNum, int staveNum )
{
	ACConvert( pageNum, ssNum );
	
	// Error checking
	if( pageNum >= tbPtr->numPages ) Error( @"Error in function DeleteStave: page does not exist." );
	if( ssNum >= pgPtr( pageNum )->numStaffSystems ) Error( @"Error in function DeleteStave: staff system does not exist." );
	if( staveNum >= ssPtr( pageNum, ssNum )->numStaves ) Error( @"Error in function DeleteStave: stave does not exist." );
	
	stave* target = svPtr( pageNum, ssNum, staveNum );
	
	if( target != NULL )
	{
		// Delete connnection with parent
		target->parentPtr->numStaves--;
		
		// Delete the sprites associated
		for( int a = 0; a < 5; a++ )
		{
			agk::DeleteSprite( target->spriteID[a] );
		}
		
		// Free from memory
		delete target;
		
		// This creates a NULL gap in the SS's array of stave objects, so shift everything down
		for( int a = staveNum; a < MAX_STAVE_PER_STAFF_SYSTEM - 1; a++ )
		{
			ssPtr( pageNum, ssNum )->stavePtr[a] = ssPtr( pageNum, ssNum )->stavePtr[a+1];
			if( ssPtr( pageNum, ssNum )->stavePtr[a+1] == NULL ) break;
		}
		
		//UpdateStaffSystemHeight( pageNum, ssNum );
	}
	else Error( @"Error in function DeleteStave: stave pointer is blank!" );
}

// STAFF SYSTEM
void NewStaffSystem( int pageNum, float xPos, float yPos )
{
	const int numStaffSystemsLocal = pgPtr( pageNum )->numStaffSystems;
	staffSystem* target = pgPtr( pageNum )->staffSystemPtr[numStaffSystemsLocal] = new staffSystem;
	pgPtr( pageNum )->numStaffSystems++;
	
	// Set the text object's initial values
	// Tell the new object its parent
	target->parentPtr = pgPtr( pageNum );
	target->x = xPos;
	target->xLocal = xPos - target->parentPtr->x;
	target->y = yPos;
	target->yLocal = yPos - target->parentPtr->y;
	target->width = target->parentPtr->x + pageWidth - pageMarginX - target->x;
	target->height = staveHeight;
	// Find the place in time of the staff system
	if( pageNum == 0 ) target->timeStart = numStaffSystemsLocal;
	else
	{
		int lastSSOnPrev = tbPtr->pagePtr[pageNum - 1]->numStaffSystems - 1;
		target->timeStart = numStaffSystemsLocal + tbPtr->pagePtr[pageNum - 1]->staffSystemPtr[lastSSOnPrev]->timeEnd;
	}
	target->duration = 1;
	target->timeEnd = target->timeStart + target->duration;
	target->numStaves = 0;
	target->numBarLines = 0;
	target->virgin = true;
	for( int a = 0; a < MAX_STAVE_PER_STAFF_SYSTEM; a++ ) target->stavePtr[a] = NULL;
	for( int a = 0; a < MAX_BARLINE_PER_STAFF_SYSTEM; a++ ) target->barLinePtr[a] = NULL;
	
	target->startLineSpriteID = agk::CloneSprite( sprLine );
	agk::SetSpritePosition( target->startLineSpriteID, target->x, target->y );
	agk::SetSpriteColor( target->startLineSpriteID, 0, 0, 0, 255 );
	agk::SetSpriteScale( target->startLineSpriteID, 1, target->height );
	
	// Populate with a single stave
	NewStave( pageNum, numStaffSystemsLocal );
	
	// Populate with barlines
	NewBarLine( pageNum, numStaffSystemsLocal, target->x + barOffset, target->timeStart, showSubBarLines, SS_BEGIN );
	NewBarLine( pageNum, numStaffSystemsLocal, target->x + target->width, target->timeEnd, true, SS_END );
	
	returnPage = pageNum;
	returnSS = numStaffSystemsLocal;
}
void MoveStaffSystem( int pageNum, int ssNum, float xPos, float yPos )
{
	ACConvert( pageNum, ssNum );
	
	// Error checking
	if( pageNum >= tbPtr->numPages ) Error( @"Error in function MoveStaffSystem: page does not exist." );
	if( ssNum >= pgPtr( pageNum )->numStaffSystems ) Error( @"Error in function MoveStaffSystem: staff system does not exist." );
	
	staffSystem* target = ssPtr( pageNum, ssNum );
	
	if( target != NULL )
	{
		target->x = xPos;
		target->y = yPos;
		
		target->xLocal = xPos - target->parentPtr->x;
		target->yLocal = yPos - target->parentPtr->y;
		
		// Move children staves
		for( int a = 0; a < target->numStaves; a++ )
		{
			MoveStave( pageNum, ssNum, a, yPos + target->stavePtr[a]->yLocal );
		}
		
		// Move children bar lines
		for( int a = 0; a < target->numBarLines; a++ )
		{
			CorrectBarLinePosition( pageNum, ssNum, a );
		}
		// Move sprites
		agk::SetSpritePosition( target->startLineSpriteID, target->x, target->y );
		agk::SetSpriteScale( target->startLineSpriteID, 1, target->height );
	}
	else Error( @"Error in function MoveStaffSystem: staffSystem pointer is blank!" );
}
void ShiftStaffSystemTime( int pageNum, int ssNum, float relativeShift )
{
	ACConvert( pageNum, ssNum );
	
	// Error checking
	if( pageNum >= tbPtr->numPages ) Error( @"Error in function ShiftStaffSystemTime: page does not exist." );
	if( ssNum >= pgPtr( pageNum )->numStaffSystems ) Error( @"Error in function ShiftStaffSystemTime: staff system does not exist." );
	
	staffSystem* target = ssPtr( pageNum, ssNum );
	
	if( target != NULL )
	{
		target->timeStart += relativeShift;
		target->timeEnd += relativeShift;
		
		// Shift children bar lines
		for( int a = 0; a < target->numBarLines; a++ )
		{
			target->barLinePtr[a]->time += relativeShift;
		}
	}
	else Error( @"Error in function ShiftStaffSystemTime: staffSystem pointer is blank!" );
}
void PushStaffSystemToNext( int pageNum, int ssNumStart )
{
	// Pushes all staff systems on a page including and after ssNumStart to the next page
	
	// Error checking
	if( pageNum >= tbPtr->numPages ) Error( @"Error in function PushStaffSystemToNext: page does not exist." );
	if( ssNumStart >= pgPtr( pageNum )->numStaffSystems ) Error( @"Error in function PushStaffSystemToNext: start staff system does not exist." );
	
	// If needed, create the new page to push to
	if( pageNum == tbPtr->numPages - 1 )
	{
		NewPage();
		ArrangePages();
	}
	
	int numToBePushed = pgPtr( pageNum )->numStaffSystems - ssNumStart;

	// Make room for them on the next page's SS pointer array
	if( tbPtr->pagePtr[pageNum + 1]->numStaffSystems > 0 )
	{
		for( int a = tbPtr->pagePtr[pageNum + 1]->numStaffSystems - 1; a >= 0; a-- )
		{
			tbPtr->pagePtr[pageNum + 1]->staffSystemPtr[a + numToBePushed] = 
			tbPtr->pagePtr[pageNum + 1]->staffSystemPtr[a];
		}
	}
	tbPtr->pagePtr[pageNum + 1]->numStaffSystems += numToBePushed;
	
	// Copy last SS's to new page
	for( int a = 0; a < numToBePushed; a++ )
	{
		tbPtr->pagePtr[pageNum + 1]->staffSystemPtr[a] = 
		pgPtr( pageNum )->staffSystemPtr[a + ssNumStart];
		
		// Delete the pointers on the earlier page
		pgPtr( pageNum )->staffSystemPtr[a + ssNumStart] = NULL;
		
		// Set the new parent
		tbPtr->pagePtr[pageNum + 1]->staffSystemPtr[a]->parentPtr = tbPtr->pagePtr[pageNum + 1];
		
		// Move them physically (will most likely cause a messy next page if not followed by an arrange function)
		MoveStaffSystem( pageNum + 1, a,
			tbPtr->pagePtr[pageNum + 1]->x + pageMarginX,
			tbPtr->pagePtr[pageNum + 1]->y + pageMarginY + 10 * a);
	}
	pgPtr( pageNum )->numStaffSystems -= numToBePushed;
}
void PushStaffSystemToPrevious( int pageNum, int ssNumLast )
{
	// Error checking
	if( pageNum >= tbPtr->numPages ) Error( @"Error in function PushStaffSystemToPrevious: page does not exist." );
	if( ssNumLast >= pgPtr( pageNum )->numStaffSystems ) Error( @"Error in function PushStaffSystemToPrevious: staff system does not exist." );
	
	if( pageNum > 0 )
	{
		int numSSEarlier = tbPtr->pagePtr[pageNum - 1]->numStaffSystems;
		
		// Tell the proceeding page it's new number of staff system's to manage
		tbPtr->pagePtr[pageNum - 1]->numStaffSystems += ssNumLast + 1;
		
		// Add the duplicates on to the end of the preceeding page
		for( int a = 0; a < ssNumLast + 1; a++ )
		{
			tbPtr->pagePtr[pageNum - 1]->staffSystemPtr[a + numSSEarlier ] =
				pgPtr( pageNum )->staffSystemPtr[a];
			
			// Set the new parent
			tbPtr->pagePtr[pageNum - 1]->staffSystemPtr[a + numSSEarlier]->parentPtr = tbPtr->pagePtr[pageNum - 1];
			
			// Move them physically (will most likely cause a messy previous page if not followed by an arrange function)
			MoveStaffSystem( pageNum - 1, a + numSSEarlier,
				tbPtr->pagePtr[pageNum - 1]->x + pageMarginX,
				tbPtr->pagePtr[pageNum - 1]->y + pageMarginY + 10 * ( a + numSSEarlier ) );
		}
		
		// Shift all pointers on the later page down
		for( int a = 0; a < MAX_STAFF_SYSTEM_PER_PAGE - 1; a++ )
		{
			pgPtr( pageNum )->staffSystemPtr[a] =
			pgPtr( pageNum )->staffSystemPtr[a + ssNumLast + 1];
			if( pgPtr( pageNum )->staffSystemPtr[a + ssNumLast + 1] == NULL ) break;
		}
		pgPtr( pageNum )->numStaffSystems -= ssNumLast + 1;
	}
	else Error( @"Error in function PushStaffSystemToPrevious: Cannot push back a staff system that is on page one." );
}
void PushStaffSystemBackToPage( int pageNum, int destPageNum )
{
	// This function takes a page's staff systems and deposits all of them on a destination page
	// Note that this function only pushes back, not forward
	
	// Error checking
	if( pageNum >= tbPtr->numPages ) Error( @"Error in function PushStaffSystemBackToPage: page does not exist." );
	if( destPageNum >= tbPtr->numPages ) Error( @"Error in function PushStaffSystemBackToPage: destination page does not exist." );
	
	if( pageNum > 0 )
	{
		int ssNumLast = pgPtr( pageNum )->numStaffSystems - 1;
		int numSSEarlier = tbPtr->pagePtr[destPageNum]->numStaffSystems;
		
		// Tell the proceeding page it's new number of staff system's to manage
		tbPtr->pagePtr[destPageNum]->numStaffSystems += ssNumLast + 1;
		
		// Add  duplicates on to the end of the target page
		for( int a = 0; a < ssNumLast + 1; a++ )
		{
			tbPtr->pagePtr[destPageNum]->staffSystemPtr[a + numSSEarlier ] =
			pgPtr( pageNum )->staffSystemPtr[a];
			
			// Set the new parent
			tbPtr->pagePtr[destPageNum]->staffSystemPtr[a + numSSEarlier]->parentPtr = tbPtr->pagePtr[destPageNum];
			
			// Move them physically (will most likely cause a messy previous page if not followed by an arrange function)
			MoveStaffSystem( destPageNum, a + numSSEarlier,
				tbPtr->pagePtr[destPageNum]->x + pageMarginX,
				tbPtr->pagePtr[destPageNum]->y + pageMarginY + 10 * ( a + numSSEarlier ) );
		}
		
		// Fill the source page with NULL pointers to staff systems
		for( int a = 0; a < MAX_STAFF_SYSTEM_PER_PAGE - 1; a++ )
		{
			if( pgPtr( pageNum )->staffSystemPtr[a] == NULL ) break;
			pgPtr( pageNum )->staffSystemPtr[a] = NULL;
		}
		pgPtr( pageNum )->numStaffSystems = 0;
	}
	else Error( @"Error in function PushStaffSystemBackToPage: Cannot push back a staff system that is on page one." );
}
int ArrangeStaffSystemsOnPage( int pageNum, int ssNumStart )
{
	// Description: This function spaces out staff systems on a given page.
	// It returns a value of the number of staff-systems that must be pushed to the next page.
	// This function assumes that unused SS's have been destroyed already
	
	// Error checking
	if( pageNum >= tbPtr->numPages ) Error( @"Error in function ArrangeStaffSystemsOnPage: page does not exist." );
	if( ssNumStart >= pgPtr( pageNum )->numStaffSystems ) Error( @"Error in function ArrangeStaffSystemsOnPage: staff system does not exist." );
	
	float yPos = pgPtr( pageNum )->staffSystemPtr[ssNumStart]->y;
	float height2 = 0;
	staffSystem* target;
	int firstSSOffBottom = -1;
	
	// Space out the starting page
	for( int a = ssNumStart; a < pgPtr( pageNum )->numStaffSystems; a++ )
	{
		target = pgPtr( pageNum )->staffSystemPtr[a];
		
		MoveStaffSystem( pageNum, a, target->x, yPos);
		
		// Calculate the height of the current staff system (equal to the y position of the last stave + stave height - y position of target)
		//height = target->stavePtr[target->numStaves - 1]->y + staveHeight - target->y;
		height2 = target->height;
		
		// Get the first one off the bottom
		if( target->y + height2 > pgPtr( pageNum )->y + pageHeight - pageMarginY )
		{
			if( firstSSOffBottom == -1 ) firstSSOffBottom = a;
		}
		
		// Increase the yPosition to spac
		yPos += height2 + staffSystemSpacing;
	}
	
	// Return the first staff system that is off the page
	return firstSSOffBottom;
}
void ArrangeStaffSystems( int pageNumStart, int ssNumStart )
{
	// Error checking
	if( pageNumStart >= tbPtr->numPages ) Error( @"Error in function ArrangeStaffSystems: page does not exist." );
	if( ssNumStart >= tbPtr->pagePtr[ssNumStart]->numStaffSystems ) Error( @"Error in function ArrangeStaffSystems: staff system does not exist." );
	
	int systems;
	
	DeleteBlankStaffSystems();
	
	// Parent all the following page SS's under the first page that is arrange
	for( int a = pageNumStart + 1; a < tbPtr->numPages; a++ )
	{
		PushStaffSystemBackToPage( a, pageNumStart );
	}
	
	for( int a = pageNumStart; a < MAX_PAGES; a++ )
	{
		// First verify that the page and first SS on the page are valid
		if( tbPtr->pagePtr[a] == NULL )
		{
			// We need a new frontier SS
			tbPtr->frontierPage = a - 1;
			tbPtr->frontierSS = tbPtr->pagePtr[a-1]->numStaffSystems - 1;
			break;
		}
		if( tbPtr->pagePtr[a]->numStaffSystems == 0 )
		{
			// We need a new frontier SS
			tbPtr->frontierPage = a - 1;
			tbPtr->frontierSS = tbPtr->pagePtr[a-1]->numStaffSystems - 1;
			break;
		}
		
		// Do the starting page
		if( a == pageNumStart ) systems = ArrangeStaffSystemsOnPage( a, ssNumStart );
		else systems = ArrangeStaffSystemsOnPage( a, 0 );
		
		if( systems != -1 )
		{
			// Systems need to be pushed on to the next page
			PushStaffSystemToNext( a, systems );
		}
	}

	PopulateBlankStaffSystems();
}
void PopulateBlankStaffSystems( void )
{
	// Do the first page
	const int lastStave = tbPtr->pagePtr[tbPtr->frontierPage]->staffSystemPtr[tbPtr->frontierSS]->numStaves - 1;
	for( float y = tbPtr->pagePtr[tbPtr->frontierPage]->staffSystemPtr[tbPtr->frontierSS]->stavePtr[lastStave]->y + staveHeight + staffSystemSpacing;
		y < tbPtr->pagePtr[tbPtr->frontierPage]->y + pageHeight - pageMarginY;
		y += staffSystemSpacing + staveHeight )
	{
		NewStaffSystem( tbPtr->frontierPage, tbPtr->pagePtr[tbPtr->frontierPage]->x + pageMarginX, y );
	}
	
	// Do subsequent pages (if they exist)
	if( tbPtr->frontierPage + 1 <= tbPtr->numPages - 1 )
	{
		for( int a = tbPtr->frontierPage + 1; a < tbPtr->numPages; a++ )
		{
			for( float y = tbPtr->pagePtr[a]->y + pageMarginY;
				y < tbPtr->pagePtr[a]->y + pageHeight - pageMarginY;
				y += staffSystemSpacing + staveHeight )
			{
				NewStaffSystem( a, tbPtr->pagePtr[a]->x + pageMarginX, y );
			}
		}
	}
}
void DeleteBlankStaffSystems( void )
{
	// Simply cycle through all and delete unused
	for( int a = 0; a < tbPtr->numPages; a++ )
	{
		int b = 0;
		while( true )
		{
			if( tbPtr->pagePtr[a]->staffSystemPtr[b] == NULL ) break;
			if( tbPtr->pagePtr[a]->staffSystemPtr[b]->virgin )
			{
					DeleteStaffSystem( a, b );
			}
			else b++;
		}
	}
}
void UpdateStaffSystemHeight( int pageNum, int ssNum )
{
	ACConvert( pageNum, ssNum );
	
	// Error checking
	if( pageNum >= tbPtr->numPages ) Error( @"Error in function UpdateStaffSystemHeight: page does not exist." );
	if( ssNum >= pgPtr( pageNum )->numStaffSystems ) Error( @"Error in function UpdateStaffSystemHeight: staff system does not exist." );
	
	staffSystem* target = ssPtr( pageNum, ssNum );
	
	if( target != NULL )
	{
		// Calculate the height of the current staff system (equal to the y position of the last stave + stave height - y position of target)
		target->height = target->stavePtr[target->numStaves - 1]->y + staveHeight - target->y;
		
		// Update bar lines to be the correct length
		for( int a = 0; a < target->numBarLines; a++ )
		{
			agk::SetSpriteScale( target->barLinePtr[a]->spriteID, 1, target->height );
		}
		
		// Update sprites
		agk::SetSpriteScale( target->startLineSpriteID, 1, target->height );
	}
	else Error( @"Error in function UpdateStaffSystemHeight: staff system pointer is blank!" );
}
void DeleteStaffSystem( int pageNum, int ssNum )
{
	ACConvert( pageNum, ssNum );
	
	// Error checking
	if( pageNum >= tbPtr->numPages ) Error( @"Error in function DeleteStaffSystem: page does not exist." );
	if( ssNum >= pgPtr( pageNum )->numStaffSystems ) Error( @"Error in function DeleteStaffSystem: staff system does not exist." );
	
	staffSystem* target = ssPtr( pageNum, ssNum );
	
	if( target != NULL )
	{
		// Shift future staff systems back in time to accomodate
		for( int a = pageNum; a < tbPtr->numPages; a++ )
		{
			for( int b = a == pageNum ? ssNum + 1 : 0; b <  tbPtr->pagePtr[a]->numStaffSystems; b++ )
			{
				ShiftStaffSystemTime( a, b, -(target->duration) );
			}
		}
		
		// Delete all children
		int iterations = target->numStaves;
		for( int a = 0; a < iterations; a++ )
		{
			DeleteStave( pageNum, ssNum, 0 );
		}
		iterations = target->numBarLines;
		for( int a = 0; a < iterations; a++ )
		{
			DeleteBarLine( pageNum, ssNum, 0 );
		}
		
		// Delete sprite
		agk::DeleteSprite( target->startLineSpriteID );
		
		// Free from memory
		delete target;
		
		// This creates a NULL gap in the page's array of SS objects, so shift everything down
		for( int a = ssNum; a < MAX_STAFF_SYSTEM_PER_PAGE - 1; a++ )
		{
			pgPtr( pageNum )->staffSystemPtr[a] = pgPtr( pageNum )->staffSystemPtr[a+1];
			if( pgPtr( pageNum )->staffSystemPtr[a+1] == NULL ) break;
		}
		
		// Delete connnection with parent
		target->parentPtr->numStaffSystems--;
	}
	else Error( @"Error in function DeleteStaffSystem: staff system pointer is blank!" );
}

// PAGE TEXT
int NewPageText( int pageNum, float xPos, float yPos, char tText[MAX_PAGETEXT_LENGTH] )
{
	int newID;
	const int numPageTextsLocal = pgPtr( pageNum )->numPageTexts;
	pageText* target = pgPtr( pageNum )->pageTextPtr[numPageTextsLocal] = new pageText;
	pgPtr( pageNum )->numPageTexts++;

	// Set the object's initial values
	// Tell the new object its parent
	target->parentPtr = pgPtr( pageNum );
	target->textID = newID = agk::CreateText( tText );
	target->eEditable = true;
	target->x = xPos;
	target->xLocal = xPos - target->parentPtr->x;
	target->y = yPos;
	target->yLocal = yPos - target->parentPtr->y;

	agk::SetTextPosition( newID, xPos, yPos );
	agk::SetTextColor( newID, 0, 0, 0, 255 );
	agk::SetTextFontImage( newID, fontCentury );
	agk::SetTextSpacing( newID, -6 );
	agk::SetTextSize( newID, 22 );
	
	return newID;
}
void DeletePageText( int pageNum, int textNum )
{
	// Error checking
	if( pageNum >= tbPtr->numPages ) Error( @"Error in function DeletePageText: page does not exist." );
	if( textNum >= pgPtr( pageNum )->numPageTexts ) Error( @"Error in function DeletePageText: page text object does not exist." );
	
	pageText* target = ptPtr( pageNum, textNum );
	
	if( target != NULL )
	{
		// Delete sprite
		agk::DeleteText( target->textID );
		
		// Delete connnection with parent
		target->parentPtr->numPageTexts--;
		
		// Free from memory
		delete target;
		
		// This creates a NULL gap in the page's array of text objects, so shift everything down
		for( int a = textNum; a < MAX_PAGETEXT_PER_PAGE - 1; a++ )
		{
			pgPtr( pageNum )->pageTextPtr[a] = pgPtr( pageNum )->pageTextPtr[a+1];
			if( pgPtr( pageNum )->pageTextPtr[a+1] == NULL ) break;
		}
	}
	else Error( @"Error in function DeletePageText: page text pointer is blank!" );
}

// PAGE
void NewPage( void )
{	
	page* target = tbPtr->pagePtr[tbPtr->numPages] = new page;
	tbPtr->currentPage = tbPtr->numPages;
	tbPtr->numPages++;
	
	// Set the new object's initial values
	// Sets the parent
	target->parentPtr = tbPtr;
	target->x = 0;
	target->y = 0;
	target->numPageTexts = 0;
	target->numStaffSystems = 0;
	for( int a = 0; a < MAX_PAGETEXT_PER_PAGE; a++ ) target->pageTextPtr[a] = NULL;
	for( int a = 0; a < MAX_STAFF_SYSTEM_PER_PAGE; a++ ) target->staffSystemPtr[a] = NULL;
	
	// Create its sprite
	target->spriteID = agk::CloneSprite( sprPage );
	agk::SetSpriteScale( target->spriteID, pageWidth, pageHeight );
	agk::SetSpriteDepth( target->spriteID, 100 );
	
	ArrangePages();
	
	// Title, composer, copyright
	if( tbPtr->currentPage == 0 )
	{
		// The first page was created
		int newText = NewPageText( 0, pageWidth / 2, 65, title );
		agk::SetTextAlignment( newText, 1 );
		agk::SetTextSize( newText, 32 );
		newText = NewPageText( 0, pageWidth - pageMarginX, 100, composer );
		agk::SetTextAlignment( newText, 2 );
		copyright[0] = char( 169 ); // Set the first character to the copyright symbol
		newText = NewPageText( 0, pageWidth / 2, pageHeight - 50, copyright );
		agk::SetTextAlignment( newText, 1 );
		
		// Populate with staff systems
		for( float y = tbPtr->pagePtr[0]->y + firstPageSSHeight, i = 0;
			y < tbPtr->pagePtr[0]->y + pageHeight - pageMarginY;
			y += staffSystemSpacing + staveHeight, i++ )
		{
			if( i == 0 ) NewStaffSystem( 0, pageMarginX + firstPageSSIndendation, y );
			else NewStaffSystem( 0, pageMarginX, y );
		}
	}
	else 
	{
		// Put title in header
		int newText = NewPageText( tbPtr->currentPage, tbPtr->pagePtr[tbPtr->currentPage]->x + pageWidth / 2,
			tbPtr->pagePtr[tbPtr->currentPage]->y + 40, title );
		agk::SetTextAlignment( newText, 1 );

		// Page number
		float xOff;
		xOff = ( tbPtr->currentPage % 2 == 0 ) ? pageWidth - pageMarginX - 3 : pageMarginX + 3;
		newText = NewPageText( tbPtr->currentPage, tbPtr->pagePtr[tbPtr->currentPage]->x + xOff,
			tbPtr->pagePtr[tbPtr->currentPage]->y + 40, agk::Str( tbPtr->currentPage + 1, 0 ) );
		agk::SetTextAlignment( newText, 1 );
		
		for( float y = tbPtr->pagePtr[tbPtr->currentPage]->y + pageMarginY;
			y < tbPtr->pagePtr[tbPtr->currentPage]->y + pageHeight - pageMarginY;
			y += staffSystemSpacing + staveHeight )
		{
			NewStaffSystem( tbPtr->currentPage, tbPtr->pagePtr[tbPtr->currentPage]->x + pageMarginX, y );
		}
	}
}
void MovePage( int pageNum, float xPos, float yPos )
{
	// Error checking
	if( pageNum >= tbPtr->numPages ) Error( @"Error in function MovePage: page does not exist." );
	
	page* target = pgPtr( pageNum );
	
	if( target != NULL )
	{
		// Move the page itself
		int ID = target->spriteID;
		
		agk::SetSpritePosition( ID, xPos, yPos );
		target->x = xPos;
		target->y = yPos;
		
		// Move children pageTexts
		for( int a = 0; a < target->numPageTexts; a++ )
		{
			ID = target->pageTextPtr[a]->textID;
			target->pageTextPtr[a]->x = xPos + target->pageTextPtr[a]->xLocal;
			target->pageTextPtr[a]->y = yPos + target->pageTextPtr[a]->yLocal;
			agk::SetTextPosition( ID, target->pageTextPtr[a]->x, target->pageTextPtr[a]->y );
		}

		// Move children staff systems
		for( int a = 0; a < target->numStaffSystems; a++ )
		{
			MoveStaffSystem( pageNum, a, xPos + target->staffSystemPtr[a]->xLocal, yPos + target->staffSystemPtr[a]->yLocal );
		}
	}
	else Error( @"Error in function MovePage: page pointer is blank!" );
}
void ArrangePages( void )
{
	float paddingWidth = pageWidth + pagePadding;
	float paddingHeight = pageHeight + pagePadding;
	switch( tbPtr->pageView )
	{
		case SPREAD:
			for( int a = 0; a < tbPtr->numPages; a++ ) { MovePage( a, a * paddingWidth, 0 ); }
			break;
		case COLUMN:
			for( int a = 0; a < tbPtr->numPages; a++ ) { MovePage( a, 0, a * paddingHeight ); }
			break;
		case DOUBLE_COLUMN:
			for( int a = 0; a < tbPtr->numPages; a++ )
			{
				if( a % 2 == 0 ) MovePage( a, 0, a * paddingHeight / 2 );
				else MovePage( a, paddingWidth, ( a - 1 ) * paddingHeight / 2 );
				// else agk::SetSpritePosition( pagePtr[a]->spriteID, pageWidth, ( a - 1 ) * pageHeight / 2 );
			}
			break;
	}
}
void HidePage( int pageNum )
{
	// Error checking
	if( pageNum >= tbPtr->numPages ) Error( @"Error in function HidePage: page does not exist." );
	
	page* target = pgPtr( pageNum );
	
	if( target != NULL )
	{
		agk::SetSpriteVisible( target->spriteID, false );
		
		for( int a = 0; a < target->numPageTexts; a++ )
		{
			agk::SetTextVisible( target->pageTextPtr[a]->textID, false );
		}
		for( int a = 0; a < target->numStaffSystems; a++ )
		{
			for( int b = 0; b < target->staffSystemPtr[a]->numStaves; b++ )
			{
				for( int c = 0; c < 5; c++ )
				{
					agk::SetSpriteVisible( target->staffSystemPtr[a]->stavePtr[b]->spriteID[c], false );
				}
			}
			for( int b = 0; b < target->staffSystemPtr[a]->numBarLines; b++ )
			{
				if( target->staffSystemPtr[a]->barLinePtr[b]->visibility ) agk::SetSpriteVisible( target->staffSystemPtr[a]->barLinePtr[b]->spriteID, false );
				
				for( int c = 0; c < target->staffSystemPtr[a]->barLinePtr[b]->numNotes; c++ )
				{
					agk::SetSpriteVisible( target->staffSystemPtr[a]->barLinePtr[b]->notePtr[c]->spriteID, false );
				}
			}
			
			// Hide sprites
			agk::SetSpriteVisible( target->staffSystemPtr[a]->startLineSpriteID, false );
		}
	}
	else Error( @"Error in function HidePage: page pointer is blank!" );
}
void ShowPage( int pageNum )
{
	// Error checking
	if( pageNum >= tbPtr->numPages ) Error( @"Error in function ShowPage: page does not exist." );
	
	page* target = pgPtr( pageNum );
	
	if( target != NULL )
	{
		agk::SetSpriteVisible( target->spriteID, true );
		
		for( int a = 0; a < target->numPageTexts; a++ )
		{
			agk::SetTextVisible( target->pageTextPtr[a]->textID, true );
		}
		for( int a = 0; a < target->numStaffSystems; a++ )
		{
			for( int b = 0; b < target->staffSystemPtr[a]->numStaves; b++ )
			{
				for( int c = 0; c < 5; c++ )
				{
					agk::SetSpriteVisible( target->staffSystemPtr[a]->stavePtr[b]->spriteID[c], true );
				}
			}
			for( int b = 0; b < target->staffSystemPtr[a]->numBarLines; b++ )
			{
				if( target->staffSystemPtr[a]->barLinePtr[b]->visibility ) agk::SetSpriteVisible( target->staffSystemPtr[a]->barLinePtr[b]->spriteID, true );
				
				for( int c = 0; c < target->staffSystemPtr[a]->barLinePtr[b]->numNotes; c++ )
				{
					agk::SetSpriteVisible( target->staffSystemPtr[a]->barLinePtr[b]->notePtr[c]->spriteID, true );
				}
			}
			// Show sprites
			agk::SetSpriteVisible( target->staffSystemPtr[a]->startLineSpriteID, true );
		}
	}
	else Error( @"Error in function ShowPage: page pointer is blank!" );
}
void DeletePage( void )
{
	page* target = tbPtr->pagePtr[tbPtr->numPages - 1];
	
	if( target != NULL )
	{
		// Delete children
		int iterations = target->numPageTexts;
		for( int a = 0; a < iterations; a++ )
		{
			DeletePageText( tbPtr->numPages - 1, 0 );
		}
		iterations = target->numStaffSystems;
		for( int a = 0; a < iterations; a++ )
		{
			DeleteStaffSystem( tbPtr->numPages - 1, 0 );
		}
		
		if( tbPtr->currentPage == tbPtr->numPages - 1 ) tbPtr->currentPage--;
		
		// Delete sprite
		agk::DeleteSprite( target->spriteID );
		
		// Delete connnection with parent
		tbPtr->numPages--;
		
		// Free from memory
		delete target;
	}
	else Error( @"Error in function DeletePage: cannot delete the only page left." );
}

// TAB
void NewTab( typeEnum tType )
{
	// Hide the currently active tab
	if( tabPtr[currentTab] != NULL ) HideTabContent( currentTab );
	
	tabPtr[numTabs] = new tab;
	currentTab = numTabs;
	numTabs++;
	
	// Set initial tab values
	tabPtr[currentTab]->type = tType;
	tabPtr[currentTab]->pageView = SPREAD;
	tabPtr[currentTab]->frontierSS = 0;
	tabPtr[currentTab]->frontierPage = 0;
	tabPtr[currentTab]->numPages = 0;
	tabPtr[currentTab]->viewX = -pagePadding;
	tabPtr[currentTab]->viewY = -pagePadding - tabBarHeight;
	tabPtr[currentTab]->viewZoom = 1;
	tabPtr[currentTab]->playHeadPosition = 0;
    tabPtr[currentTab]->playHeadSpeed = 0.00f;
	tabPtr[currentTab]->numGestures = 0;
	for( int a = 0; a < MAX_GESTURES; a++ ) tabPtr[currentTab]->gesturePtr[a] = NULL;
	for( int a = 0; a < MAX_TABS; a++ ) tabPtr[currentTab]->pagePtr[a] = NULL;
	
	// Populate the tab with children
	switch ( tType )
	{
		case MUSIC_FULL:
			strcpy( tabPtr[currentTab]->name, "Score");
			agk::SetViewOffset( tabPtr[currentTab]->viewX, tabPtr[currentTab]->viewY );
			agk::SetViewZoom( 1 );
			agk::SetClearColor( bgColR, bgColG, bgColB );
			NewPage();
			NewPage();
			NewPage();
			NewPage();
			break;
		case TEXT:
		{
			strcpy( tabPtr[currentTab]->name, "Notes");
			agk::SetViewOffset( 0, 0 );
			agk::SetViewZoom( 1 );
			agk::SetClearColor( 255, 255, 250 );
			
			// Populate with an edit box
			tabPtr[currentTab]->ebID = agk::CreateEditBox( );
			agk::SetEditBoxPosition( tabPtr[currentTab]->ebID, textTabMargin, textTabMargin + tabBarHeight );
			agk::SetEditBoxSize( tabPtr[currentTab]->ebID, App.m_DeviceWidth - textTabMargin * 2, App.m_DeviceHeight - textTabMargin * 2 - tabBarHeight );
			agk::SetEditBoxBackgroundColor( tabPtr[currentTab]->ebID, 255, 255, 250, 255 );
			agk::SetEditBoxBorderColor( tabPtr[currentTab]->ebID, 200, 200, 200, 200 );
			agk::SetEditBoxCursorColor( tabPtr[currentTab]->ebID, 0, 0, 0 );
			agk::SetEditBoxMultiLine( tabPtr[currentTab]->ebID, true );
			agk::SetEditBoxTextSize( tabPtr[currentTab]->ebID, 24 );
			//agk::SetEditBoxFontImage( tabPtr[currentTab]->ebID, fontCentury );
		}
		default:
			break;
	}
	
	// Create the tab text at the top
	int newID = tabPtr[currentTab]->barTextID = agk::CreateText( tabPtr[currentTab]->name );
	agk::SetTextColor( newID, 255, 255, 255, 255 );
	agk::SetTextPosition( newID, 5, 3 );
	agk::FixTextToScreen( newID, true );
	agk::SetTextDepth( newID, 5 );
	agk::SetTextSize( newID, 18 );
	ArrangeTabBar();
}
void ArrangeTabBar( void )
{
	float xPos = tabPadding;
	for( int a = 0; a < numTabs; a++ )
	{
		agk::SetTextPosition( tabPtr[a]->barTextID, xPos, 2 );
		xPos += agk::GetTextTotalWidth( tabPtr[a]->barTextID ) + tabPadding;
		if( a != currentTab ) agk::SetTextColor( tabPtr[a]->barTextID, 120, 120, 120, 255 );
		else agk::SetTextColor( tabPtr[a]->barTextID, 255, 255, 255, 255 );
	}
}
void HideTabContent( int tabNum )
{
	tab* target = tabPtr[tabNum];
    if(tabPtr[currentTab] == NULL) return;
	
	int tempCurrentTab = currentTab;
	currentTab = tabNum;
	
	// Here is were we hide all visible components of the tab
	// Not any yet
	
	switch( target->type )
	{
		case MUSIC_FULL:
			agk::SetSpriteVisible( playHeadID, false );
			for( int a = 0; a < target->numPages; a++ )
			{
				HidePage( a );
			}
			break;
		case TEXT:
			agk::SetEditBoxVisible( tabPtr[currentTab]->ebID, false );
			agk::SetEditBoxFocus( tabPtr[currentTab]->ebID, false );
			agk::SetEditBoxActive( tabPtr[currentTab]->ebID, false );
			break;
		default:
			break;
	}
	
	currentTab = tempCurrentTab;
	
	// Save the view
	tabPtr[currentTab]->viewX = agk::GetViewOffsetX();
	tabPtr[currentTab]->viewY = agk::GetViewOffsetY();
	tabPtr[currentTab]->viewZoom = agk::GetViewZoom();
}
void ShowTabContent( int tabNum )
{
    tab* target = tabPtr[tabNum];
    
    if(target == NULL) return; // This shouldn't happen.
    if( tabNum == -1 ) return; // This shouldn't happen.
	
	int tempCurrentTab = currentTab;
	currentTab = tabNum;
	
	// Here is were we hide all visible components of the tab
	// Not any yet
	
	switch( target->type )
	{
		case MUSIC_FULL:
			agk::SetSpriteVisible( playHeadID, true );
			for( int a = 0; a < target->numPages; a++ )
			{
				ShowPage( a );
				agk::SetViewOffset( tabPtr[currentTab]->viewX, tabPtr[currentTab]->viewY );
				agk::SetViewZoom( tabPtr[currentTab]->viewZoom );
				agk::SetClearColor( bgColR, bgColG, bgColB );
			}
			break;
		case TEXT:
			agk::SetEditBoxVisible( tabPtr[currentTab]->ebID, true );
			agk::SetEditBoxActive( tabPtr[currentTab]->ebID, true );
			agk::SetViewOffset( 0, 0 );
			agk::SetViewZoom( 1 );
			agk::SetClearColor( 255, 255, 250 );
			break;
		default:
			break;
	}
	
	currentTab = tempCurrentTab;
}
void SwitchTab( int tabNum )
{
	if( tabNum != currentTab )
	{
        ClearGestures();
		HideTabContent( currentTab );
		currentTab = tabNum;
		ShowTabContent( currentTab );
		ArrangeTabBar();
	}
}
void DeleteTab( int tabNum )
{	
	// ASK FOR SAVE HERE
    
    ClearGestures();
    
	// Hide the current page
	HideTabContent( tabNum );
	
	tab* target = tabPtr[tabNum];
	
	// Shift up?
	bool shiftUp = tabNum == 0;
	
	int tempCurrentTab = currentTab;
	currentTab = tabNum;
	
	// Delete children
	switch( target->type )
	{
		case MUSIC_FULL:
			for( int a = 0; a < target->numPages; a++ )
			{
				DeletePage();
			}
			break;
		case TEXT:
			agk::DeleteEditBox( target->ebID );
		default:
			break;
	}
	
	// Delete text
	agk::DeleteText( target->barTextID );
	
	// Free from memory
	delete target;
    
    if(numTabs == 1) return; // The last tab gets closed only when the program has ended.
	
	currentTab = tempCurrentTab;
	
	// Move tabs
	if( tabNum + 1 == numTabs ) // If the end tab was deleted
	{
		if( currentTab == tabNum ) // If it was the current tab
		{
			if( !shiftUp ) currentTab--;
			ShowTabContent( currentTab );
		}
	}
	if( tabNum + 1 < numTabs ) // If a middle tab was deleted
	{
		bool showAtEnd = false;
		if( currentTab <= tabNum ) // If it was the current tab or an earlier tab
		{
			if( !shiftUp ) currentTab--;
			showAtEnd = true;
		}
		
		// Shift
		for( int a = tabNum; a < MAX_TABS - 1; a++ )
		{
			tabPtr[a] = tabPtr[a+1];
			if( tabPtr[a+1] == NULL ) break;
		}
		
		if( showAtEnd ) ShowTabContent( currentTab );
	}
	
	// Delete connnection with global
	numTabs--;
	
	ArrangeTabBar();
}

// Gesture
void NewGesture( void )
{
	gesture* target = tbPtr->gesturePtr[tbPtr->numGestures] = new gesture;
	tbPtr->numGestures++;
	
	// Set the new object's initial values
	// Sets the parent
	target->parentPtr = tbPtr;
	for( int a = 0; a < MAX_DRAW; a++ )
	{
		target->numDraws = 0;
		target->numPoints = 0;
		target->pointID[a] = NULL;
		target->drawID[a] = NULL;
		target->pageNum = -1;
		target->minX = -1;
		target->minY = -1;
		target->maxX = -1;
		target->maxY = -1;
		target->x = -1;
		target->y = -1;
		target->xStart = -1;
		target->yStart = -1;
		target->xEnd = -1;
		target->yEnd = -1;
		target->width = 0;
		target->height = 0;
		target->length = 0;
	}
}
void RecognizeGesture( void )
{
	// Determine the start point and end point here
    
    // Get the nearest objects, store them in return values
    ConvertPointToNearestAll( gsPtrActive->x, gsPtrActive->y );
	
	// Is approximately the size of a notehead?
	if( gsPtrActive->width > lineSpacing * 0.35f && gsPtrActive->height > lineSpacing * 0.66f &&
	   gsPtrActive->width < lineSpacing * 2.7f && gsPtrActive->height < lineSpacing * 2.7f )
	{
        // NOTE that the below code makes use of returnX, which is the nearest instance of X
		// Is this notehead lined up with a valid staff system?
		if( gsPtrActive->x > ssPtr( returnPage, returnSS )->x && gsPtrActive->x < ssPtr( returnPage, returnSS )->x + ssPtr( returnPage, returnSS )->width )
		{
			
			// Is this note part of a subdivision bar line that already exists? If so snap.
			if( barLineDistance < 14 )
			{
				NewNote( gsPtrActive->pageNum, returnSS, returnBarLine, returnStave, nC, 2, naNONE );
				note* target = ntPtr( gsPtrActive->pageNum, returnSS, returnBarLine, returnNote );
				
				float relY = gsPtrActive->y - svPtr( gsPtrActive->pageNum, returnSS, returnStave )->y - 16.5f * target->size;
				int pitch = CalculateNotePitchLetter( target->clef, relY, target->size, SOLID );
				target->pitchLetter = pitch;
				CorrectNotePosition( gsPtrActive->pageNum, returnSS, returnBarLine, returnNote );
				
				MoveBarLine( gsPtrActive->pageNum, returnSS, returnBarLine, gsPtrActive->x );
			}
			else
			{
				float defaultDuration = 0.25f;
				NewBarLineSplitMeasure( gsPtrActive->pageNum, returnSS, gsPtrActive->x, defaultDuration );
				NewNote( gsPtrActive->pageNum, returnSS, returnBarLine, returnStave, nC, 2, naNONE );
				note* target = ntPtr( gsPtrActive->pageNum, returnSS, returnBarLine, returnNote );
				
				float relY = gsPtrActive->y - svPtr( gsPtrActive->pageNum, returnSS, returnStave )->y - 16.5f * target->size;
				int pitch = CalculateNotePitchLetter( target->clef, relY, target->size, SOLID );
				target->pitchLetter = pitch;
				CorrectNotePosition( gsPtrActive->pageNum, returnSS, returnBarLine, returnNote );
			}
		}
	}
    
    // Is approximately the size of a bar line?
    if(returnPage == -1 || returnSS == -1) return;
    const float nearestSSHeight = ssPtr( returnPage, returnSS )->height;
    if( gsPtrActive->width < 32 && gsPtrActive->height > nearestSSHeight - 10 && gsPtrActive->height < nearestSSHeight + 32 )
    {
        NewBarLineSplitStaffSystem( returnPage, returnSS, gsPtrActive->x );
    }
}
void ClearGestures( void )
{
    if( tabPtr[currentTab] == NULL ) return;
	for( int a = 0; a < tbPtr->numGestures; a++ )
	{
		gesture* target = gsPtr( a );
		
		// Delete the child objects
		for( int b = 0; b < target->numDraws; b++ )
		{
			agk::DeleteSprite( target->drawID[b] );
		}
		target->numDraws = 0;
		for( int b = 0; b < target->numPoints; b++ )
		{
			agk::DeleteSprite( target->pointID[b] );
		}
		target->numPoints = 0;
		
		gsPtr( a ) = NULL;
		
		delete target;
	}
	tbPtr->numGestures = 0;
}

// CONVERSION
int ConvertPointToPage( float x, float y )
{
	// Returns the page number

	// Check for collision with pages
	for( int a = 0; a < tbPtr->numPages; a++ )
	{
		page* target = pgPtr( a );
		if( x > target->x && x < target->x + pageWidth && y > target->y && y < target->y + pageHeight )
		{
			return a;
		}
	}
	return -1;
}
int ConvertPointToNearestAll( float x, float y )
{
	// Note: Name is not entirely true. Does not calculate distance for pages, but returns -1 if not part of page
	
	returnPage = -1;
	returnSS = -1;
	returnBarLine = -1;
	returnStave = -1;
	
	ssDistance = 1000000;
	barLineDistance = 1000000;
	staveDistance = 1000000;
	
	// Check for collision with pages
	for( int a = 0; a < tbPtr->numPages; a++ )
	{
		page* target = pgPtr( a );
		if( x > target->x && x < target->x + pageWidth && y > target->y && y < target->y + pageHeight )
		{
			returnPage = a;
			
			// Check for nearest SS on page
			float dst;
			for( int b = 0; b < pgPtr( a )->numStaffSystems; b++ )
			{
				dst = abs( ssPtr( a, b )->y + ssPtr( a, b )->height / 2 - y ); // Distance to the middle of the SS
				if( dst < ssDistance )
				{
					ssDistance = dst;
					returnSS = b;
				}
			}
			
			// Checks for nearest bar line in the SS
			for( int b = 0; b < ssPtr( a, returnSS )->numBarLines; b++ )
			{
				dst = abs( blPtr( a, returnSS, b )->x - x );
				
				// No bar lines or end SS's. Only subbarlines
				if( blPtr( a, returnSS, b )->barLineMode == BAR ) continue;
				if( blPtr( a, returnSS, b )->barLineMode == SS_END ) continue;
				
				if( dst < barLineDistance )
				{
					barLineDistance = dst;
					returnBarLine = b;
				}
			}
			
			// Checks for nearest stave in the SS
			for( int b = 0; b < ssPtr( a, returnSS )->numStaves; b++ )
			{
				// No need for distance formula; 1 dimension only
				dst = abs( svPtr( a, returnSS, b )->y + staveHeight / 2 - y ); // Checks from middle of stave
				
				if( dst < staveDistance )
				{
					staveDistance = dst;
					returnStave = b;
				}
			}
			
			return returnPage;
		}
	}
	return -1;
}
int ConvertGlobalSSToLocal( int ssNumGlobal )
{
	int c = 0;
	
	for( int a = 0; a < tbPtr->numPages; a++ )
	{
		for( int b = 0; b < tbPtr->pagePtr[a]->numStaffSystems; b++ )
		{
			if( c == ssNumGlobal )
			{
				returnPage = a;
				returnSS = b;
				return a;
				break;
			}
			c++;
		}
	}
	Error( @"Error in function ConvertGlobalSSToLocal: Staff system number is beyond the number of staff systems." );
	return -1;
}
int ConvertLocalSSToGlobal( int pageNum, int ssNum )
{
	int c = -1;
	
	for( int a = 0; a < pageNum; a++ )
	{
		for( int b = 0; b < tbPtr->pagePtr[a]->numStaffSystems; b++ )
		{
			c++;
		}
	}
	c += ssNum + 1;
	return c;
}
int ConvertGlobalBarLineToLocal( int barLineNumGlobal )
{
	int d = 0;
	
	for( int a = 0; a < tbPtr->numPages; a++ )
	{
		for( int b = 0; b < tbPtr->pagePtr[a]->numStaffSystems; b++ )
		{
			for( int c =  0; c < tbPtr->pagePtr[a]->staffSystemPtr[b]->numBarLines; c++ )
			{
				if( d == barLineNumGlobal )
				{
					returnPage = a;
					returnSS = b;
					returnBarLine = c;
					return a;
					break;
				}
				d++;
			}
		}
	}
	Error( @"Error in function ConvertGlobalBarLineToLocal: Bar line number is beyond the number of bar lines." );
	return -1;
}
int ConvertGlobalMeasureToLocal( int measureNumGlobal )
{
	int d = 0;
	
	//measureNumGlobal--;
	
	for( int a = 0; a < tbPtr->numPages; a++ )
	{
		for( int b = 0; b < tbPtr->pagePtr[a]->numStaffSystems; b++ )
		{
			for( int c =  0; c < tbPtr->pagePtr[a]->staffSystemPtr[b]->numBarLines; c++ )
			{
				// Only count bars
				if( tbPtr->pagePtr[a]->staffSystemPtr[b]->barLinePtr[c]->barLineMode == SS_BEGIN ||
				   tbPtr->pagePtr[a]->staffSystemPtr[b]->barLinePtr[c]->barLineMode == BAR )
				{
					if( d == measureNumGlobal )
					{
						returnPage = a;
						returnSS = b;
						if( tbPtr->pagePtr[a]->staffSystemPtr[b]->barLinePtr[c]->barLineMode == BAR ||
                           tbPtr->pagePtr[a]->staffSystemPtr[b]->barLinePtr[c]->barLineMode == SS_BEGIN ) returnBarLine = c;
						else returnBarLine = c;
						return a;
						break;
					}
					d++;
				}
			}
		}
	}
	Error( @"Error in function ConvertGlobalMeasureToLocal: Measure number is beyond the number of measures." );
	return -1;
}
void ACConvert( int &pageNum, int &ssNum, int &barLineNum )
{
	// Local-global conversion
	if( pageNum == ac )
	{		
		if( ssNum == ac )
		{
			// Global measure
			if( barLineNum >= 0 ) ConvertGlobalBarLineToLocal( barLineNum );
			else ConvertGlobalMeasureToLocal( -barLineNum );
			pageNum = returnPage;
			ssNum = returnSS;
			barLineNum = returnBarLine;
		}
		else
		{
			// Global SS
			ConvertGlobalSSToLocal( ssNum );
			pageNum = returnPage;
			ssNum = returnSS;
		}
	}
}
void ACConvert( int &pageNum, int &ssNum )
{
	// Local-global conversion
	if( pageNum == ac )
	{		
		// Global SS
		ConvertGlobalSSToLocal( ssNum );
		pageNum = returnPage;
		ssNum = returnSS;
	}
}

// GENERAL
void MainCreateNew( void )
{    
	// Creates a new project
	NewTab( MUSIC_FULL );
	NewTab( MUSIC_FULL );
	NewTab( TEXT );
	SwitchTab( 0 );
	
	// Construct a sample document using code
	int ss = 0;
	
	NewStave( ac, ss );
	NewStave( ac, ss );
    
	ss++;
	NewStave( ac, ss );
	NewStave( ac, ss );
	
	ss++;
	NewStave( ac, ss );
	NewStave( ac, ss );
	
	ss++;
	NewStave( ac, ss );
	NewStave( ac, ss );
	
	ss++;
	NewStave( ac, ss );
	
	ss++;
	NewStave( ac, ss );
	
	ss++;
	NewStave( ac, ss );
	NewStave( ac, ss );

	ArrangeStaffSystems( 0,  0 );
    
    //NewBarLineSplitMeasurePercent( 0, 0, 0, 50.0f, 0.5 );
}
void ViewControl( void )
{
	if( agk::GetRawMouseRightPressed() == 1 )
	{
		clickStartX = agk::GetPointerX();
		clickStartY = agk::GetPointerY();
		clickStartViewX = agk::GetViewOffsetX();
		clickStartViewY = agk::GetViewOffsetY();
	}
	if( agk::GetRawMouseRightState() == 1 )
	{
		float newX = clickStartViewX + ( clickStartX - agk::GetPointerX() ) / agk::GetViewZoom();
		float newY = clickStartViewY + ( clickStartY - agk::GetPointerY() ) / agk::GetViewZoom();
		
		agk::SetViewOffset( newX, newY );
		ViewControlLimitView();
	}
	if( agk::GetRawKeyPressed( 187 ) )
	{
		zoomTimer = 0;
		agk::SetViewOffset( agk::ScreenToWorldX(  agk::GetPointerX() ) - App.m_DeviceWidth / 2, agk::ScreenToWorldY(  agk::GetPointerY() ) -  App.m_DeviceHeight/ 2 );
		ViewControlLimitView();
		if( agk::GetViewZoom() < 3 )
		agk::SetViewZoom( agk::GetViewZoom() + 0.2 );
	}
	if( agk::GetRawKeyPressed( 189 ) )
	{
		zoomTimer = 0;
		agk::SetViewOffset( agk::ScreenToWorldX(  agk::GetPointerX() ) - App.m_DeviceWidth / 2, agk::ScreenToWorldY(  agk::GetPointerY() ) -  App.m_DeviceHeight/ 2 );
		ViewControlLimitView();
		if( agk::GetViewZoom() > 0.4 )
		agk::SetViewZoom( agk::GetViewZoom() - 0.2 );
	}
	if( agk::GetRawKeyState( 187 ) && zoomTimer == 30 )
	{
		zoomTimer = 29;
		if( agk::GetViewZoom() < 3 )
			agk::SetViewZoom( agk::GetViewZoom() + 0.04 );
	}
	if( agk::GetRawKeyState( 189 ) && zoomTimer == 30 )
	{
		zoomTimer = 29;
		if( agk::Abs( agk::GetViewZoom() - 1.0 ) < 0.1f )
		{
			agk::SetViewZoom( 1.0 );
			zoomTimer = 0;
			return;
		}
		if( agk::GetViewZoom() > 0.4 )
			agk::SetViewZoom( agk::GetViewZoom() - 0.04 );
	}
	zoomTimer++;
}
void ViewControlLimitView( void )
{
	float newX = agk::GetViewOffsetX();
	float newY = agk::GetViewOffsetY();
	
	// Limit the view
	newX = ( newX < viewMargin / -2 ) ? viewMargin / -2 : newX;
	newY = ( newY < viewMargin / -2 ) ? viewMargin / -2 : newY;
	
	// Depending on the view mode the upper bounds of the view will be different
	switch ( tbPtr->pageView )
	{
		case SPREAD:
			newX = ( newX > ( tbPtr->numPages * ( pageWidth + pagePadding ) + viewMargin / 2 - App.m_DeviceWidth ) )
			? ( tbPtr->numPages * ( pageWidth + pagePadding ) + viewMargin / 2 - App.m_DeviceWidth ) : newX;
			newY = ( newY > pageHeight + viewMargin / 2 - App.m_DeviceHeight )
			? pageHeight + viewMargin / 2 - App.m_DeviceHeight : newY;
			break;
		case COLUMN:
			newX = ( newX > ( pageWidth + viewMargin / 2 - App.m_DeviceWidth ) )
			? ( pageWidth + viewMargin / 2 - App.m_DeviceWidth ) : newX;
			newY = ( newY > ( tbPtr->numPages * ( pageHeight + pagePadding ) + viewMargin / 2 - App.m_DeviceHeight ) )
			? ( tbPtr->numPages * ( pageHeight + pagePadding ) + viewMargin / 2 - App.m_DeviceHeight ) : newY;
			break;
		case DOUBLE_COLUMN:
			newX = ( newX > ( pageWidth * 2 + pagePadding + viewMargin / 2 - App.m_DeviceWidth ) )
			? ( pageWidth * 2 + pagePadding + viewMargin / 2 - App.m_DeviceWidth ) : newX;
			int localNumPages;
			if( ( tbPtr->numPages % 2 ) == 0 ) localNumPages = tbPtr->numPages;
			else localNumPages = tbPtr->numPages + 1;
			newY = ( newY > ( localNumPages / 2 * ( pageHeight + pagePadding ) + viewMargin / 2 - App.m_DeviceHeight ) )
			? ( localNumPages / 2 * ( pageHeight + pagePadding ) + viewMargin / 2 - App.m_DeviceHeight ) : newY;
			break;
		default:
			break;
	}
	agk::SetViewOffset( newX, newY );
}
void TabControl( void )
{
	if( agk::GetRawKeyPressed( 223 ) )
	{
		if( agk::GetRawKeyState( 17 ) )
		{
			int currentTabTemp = currentTab + 1;
			if( currentTabTemp == numTabs ) currentTabTemp = 0;
			SwitchTab( currentTabTemp );
		}
	}
	if( agk::GetRawKeyPressed( 87 ) )
	{
		if( agk::GetRawKeyState( 17 ) )
		{
			if( numTabs > 1 ) DeleteTab( currentTab );
		}
	}
	
	if( agk::GetRawMouseY() <= tabBarHeight )
	{
		float x = agk::GetPointerX();
		float xMin = tabPadding;
		float xMax = tabPadding;
		tabBarOK = false;
			
		for( int a = 0; a < numTabs; a++ )
		{
			if( a != currentTab ) agk::SetTextColor( tabPtr[a]->barTextID, 120, 120, 120, 255 );

			xMax += agk::GetTextTotalWidth( tabPtr[a]->barTextID ) + tabPadding;
			if( x > xMin && x < xMax )
			{
				if( agk::GetRawMouseLeftPressed() ) SwitchTab( a );
				else if( a != currentTab ) agk::SetTextColor( tabPtr[a]->barTextID, 100, 100, 100, 255 );
			}
			xMin += agk::GetTextTotalWidth( tabPtr[a]->barTextID ) + tabPadding;
		}
	}
	if( agk::GetRawMouseY() > tabBarHeight && !tabBarOK )
	{
		ArrangeTabBar();
		tabBarOK = true;
	}

}
void DrawOnPage( void )
{
    // Temporary
    if( agk::GetPointerY() > tabBarHeight )
    {
        mouseXPrev = mouseX;
        mouseYPrev = mouseY;
        mouseX = agk::ScreenToWorldX( agk::GetPointerX() );
        mouseY = agk::ScreenToWorldY( agk::GetPointerY() );
        mouseDistance = Distance( mouseX, mouseY, mouseXPrev, mouseYPrev );
        if( mouseDistance >= 2 )mouseAngle = agk::ATanFull( mouseX - mouseXPrev, mouseY - mouseYPrev ) + 90;
        
        if( agk::GetPointerState() )
        {
            if( agk::GetPointerPressed() )
            {
                mouseXPrev = mouseX;
                mouseYPrev = mouseY;
                mouseDistance = 0;
                
                NewGesture();
                
                gsPtrActive->pageNum = ConvertPointToPage( mouseX, mouseY );
                gsPtrActive->minX = mouseX;
                gsPtrActive->maxX = mouseX;
                gsPtrActive->minY = mouseY;
                gsPtrActive->maxY = mouseY;
                gsPtrActive->xStart = mouseX;
                gsPtrActive->yStart = mouseY;
            }
            
            if( gsPtrActive->numPoints >= MAX_DRAW - 1 ) return;
            
            int spriteID;
            
            // Clamp the position to the page
            if( gsPtrActive->pageNum != -1 )
            {
                page* target = pgPtr( gsPtrActive->pageNum );
                
                if( mouseX < target->x ) mouseX = target->x;
                if( mouseX > target->x + pageWidth ) mouseX = target->x + pageWidth;
                if( mouseY < target->y ) mouseY = target->y;
                if( mouseY > target->y + pageHeight ) mouseY = target->y + pageHeight;
                mouseDistance = Distance( mouseX, mouseY, mouseXPrev, mouseYPrev );
                if( mouseDistance >= 2 )mouseAngle = agk::ATanFull( mouseX - mouseXPrev, mouseY - mouseYPrev ) + 90;
            }
            
            spriteID = gsPtrActive->pointID[gsPtrActive->numPoints] = agk::CloneSprite( sprDrawPivot );
            agk::SetSpritePosition( spriteID, mouseX - 4, mouseY - 4);
            agk::SetSpriteOffset( spriteID, 4, 4 );
            agk::SetSpriteScaleByOffset( spriteID, 1 * drawThickness, 1 * drawThickness );
            agk::SetSpriteAngle( spriteID, mouseAngle );
            
            gsPtrActive->numPoints++;
            
            // Make connecting lines
            spriteID = gsPtrActive->drawID[gsPtrActive->numDraws] = agk::CloneSprite( sprDraw );
            agk::SetSpritePosition( spriteID, ( mouseX + mouseXPrev ) / 2 - 4, ( mouseY + mouseYPrev ) / 2 - 4 );
            agk::SetSpriteOffset( spriteID, 4, 4 );
            agk::SetSpriteAngle( spriteID, mouseAngle );
            agk::SetSpriteScaleByOffset( spriteID, mouseDistance * 0.125f, 1 * drawThickness );
            
            // Update the gesture object
            gsPtrActive->numDraws++;
            gsPtrActive->length += mouseDistance;
            if( mouseX < gsPtrActive->minX ) gsPtrActive->minX = mouseX;
            if( mouseX > gsPtrActive->maxX ) gsPtrActive->maxX = mouseX;
            if( mouseY < gsPtrActive->minY ) gsPtrActive->minY = mouseY;
            if( mouseY > gsPtrActive->maxY ) gsPtrActive->maxY = mouseY;
        }
        
        // Finish gesture if released
        if( agk::GetPointerReleased() )
        {
            // Finish the gesture variables
            gsPtrActive->x = ( gsPtrActive->minX + gsPtrActive->maxX ) / 2;
            gsPtrActive->y = ( gsPtrActive->minY + gsPtrActive->maxY ) / 2;
            
            gsPtrActive->width = gsPtrActive->maxX - gsPtrActive->minX;
            gsPtrActive->height = gsPtrActive->maxY - gsPtrActive->minY;
            
            gsPtrActive->xEnd = mouseX;
            gsPtrActive->yEnd = mouseY;
            
            RecognizeGesture();
            ClearGestures();
        }
    }
}
void MainShortcutsControl( void )
{
	// Home
	if( agk::GetRawKeyPressed( 36 ) )
	{
		tbPtr->playHeadPosition = 0.001f;
	}
	// Page up NOW up
	if( agk::GetRawKeyPressed( /*33*/ 38 ) )
	{
		if( agk::GetRawKeyState( 17 ) )
		{
			if( tbPtr->pageView == DOUBLE_COLUMN ) tbPtr->pageView = SPREAD;
			else
			{
				if( tbPtr->pageView == COLUMN ) tbPtr->pageView = DOUBLE_COLUMN;
				if( tbPtr->pageView == SPREAD ) tbPtr->pageView = COLUMN;	
			}
			ArrangePages();
			ViewControlLimitView();
		}
        else if( !( tbPtr->playHeadPage == 0 && tbPtr->playHeadSS == 0 ) )
		{
			int placeHolder = ac;
			int globalSS = ConvertLocalSSToGlobal( tbPtr->playHeadPage, tbPtr->playHeadSS ) - 1;
			ACConvert( placeHolder, globalSS );
			tbPtr->playHeadPosition = ssPtr( returnPage, returnSS )->timeStart + 0.001f;
            UpdatePlayHead( tbPtr->playHeadPosition );
		}
	}
	// Page down NOW down
	if( agk::GetRawKeyPressed( /*34*/ 40 ) )
	{
		if( agk::GetRawKeyState( 17 ) )
		{
			if( tbPtr->pageView == SPREAD ) tbPtr->pageView = DOUBLE_COLUMN;
			else
			{
				if( tbPtr->pageView == COLUMN ) tbPtr->pageView = SPREAD;	
				if( tbPtr->pageView == DOUBLE_COLUMN ) tbPtr->pageView = COLUMN;
			}
			ArrangePages();
			ViewControlLimitView();
		}
        else if( !( tbPtr->playHeadPage == tbPtr->numPages - 1 && tbPtr->playHeadSS > pgPtr( tbPtr->numPages - 1 )->numStaffSystems - 2 ) )
		{
			int placeHolder = ac;
			int globalSS = ConvertLocalSSToGlobal( tbPtr->playHeadPage, tbPtr->playHeadSS ) + 1;
			ACConvert( placeHolder, globalSS );
			tbPtr->playHeadPosition = ssPtr( returnPage, returnSS )->timeStart + 0.001f;
            UpdatePlayHead( tbPtr->playHeadPosition );
		}
	}
    // Space bar
	if( agk::GetRawKeyPressed( 32 ) )
	{
        if( currentTab[tabPtr]->playHeadSpeed == 0 )
        {
            currentTab[tabPtr]->playHeadSpeed = 0.01f; // DEVELOP MORE: get rid of literal in future.
        }
        else
        {
            currentTab[tabPtr]->playHeadSpeed = 0;
            
            // There is. Stop previous sounds.
            if(numPlaying > 0)
            {
                for (int ii = 0; ii < numPlaying; ii++ )
                {
                    agk::StopSound(sound[ii]);
                }
                numPlaying = 0;
            }
        }
	}
}
void AppForceExit ( void );
void app::Begin( void )
{
    // Use device resolution
    agk::SetVirtualResolution ( m_DeviceWidth, m_DeviceHeight );
	agk::SetWindowTitle( PROGRAM_TITLE );
	agk::SetClearColor( bgColR, bgColG, bgColB );
	agk::SetSyncRate( 60, 1 );
	agk::SetViewZoomMode( 1 );
    
	LoadImagesSprites();
    LoadSounds();
	
	// Set up tabs
	int tabBar = agk::CloneSprite( sprTabBG );
	agk::SetSpritePosition( tabBar, 0, 0 );
	agk::SetSpriteSize( tabBar, App.m_DeviceWidth, tabBarHeight );
	agk::FixSpriteToScreen( tabBar, true );
	agk::SetSpriteDepth( tabBar, 6 );
	
	// Creates a new project 
	MainCreateNew();
}
void app::Loop ( void )
{
	switch ( appScreen )
	{
		case LAUNCHER:					break;
		case MAIN:
			if( tbPtr->type == MUSIC_FULL || tbPtr->type == MUSIC_FREE )
			{
				ViewControl();
				UpdatePlayHead( tbPtr->playHeadPosition );
				tbPtr->playHeadPosition += tbPtr->playHeadSpeed;
				DrawOnPage();
				MainShortcutsControl();
			}
			TabControl();
			break;
		case PREFERENCES:				break;
	}
    
	if( printVal != -256 ) agk::Print( printVal );
    agk::Sync();
}
void app::End ( void )
{
    // Free the allocated memory
    for (int i = 0; i < numTabs; i++ )
    {
        DeleteTab(i);
    }
}
