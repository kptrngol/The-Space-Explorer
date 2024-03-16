#ifndef STORY_H
#define STORY_H

#define PHASE 10
#define VERSE_NR 100
#define VERS_MAX_LENGTH 500

// Determine story phase and aligned dialogues

typedef enum StoryPhase 
{
    NONE,
    PROLOGUE,
    ACT1,
    ACT2,
    ACT3,
    EPILOGUE
}storyPhase;

extern storyPhase currentStoryPhase;
extern int bookmark; 
extern float dialogueT;

// Change story phases as player progress through map
void SyStoryPhaseSwitch(storyPhase (*currentStoryPhase),int playerDistance);


// Print dialogues
void SyPrintDialogue(storyPhase (*currentStoryPhase), char dialogueData[PHASE][VERSE_NR][VERS_MAX_LENGTH]);

extern char dialogueData[PHASE][VERSE_NR][VERS_MAX_LENGTH];
extern int dialogueTime[PHASE][VERSE_NR][1];

#endif