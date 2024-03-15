#ifndef STORY_H
#define STORY_H

#define PHASE 10
#define VERSE_NR 100
#define VERS_MAX_LENGTH 500


// obiekt enum zawierający kolejne etapy gry

typedef enum StoryPhase 
{
    PROLOGUE,
    ACT1,
    ACT2,
    ACT3,
    EPILOGUE
}storyPhase;

extern storyPhase currentStoryPhase;

// funkcja sprawdzająca warunki kolejnych etapów gry w game loopie

void SyPrintDialogue(storyPhase (*currentStoryPhase), char dialogueData[PHASE][VERSE_NR][VERS_MAX_LENGTH]);

// tablica zawierająca kolejne dialogi para: etap i  

extern char dialogueData[PHASE][VERSE_NR][VERS_MAX_LENGTH];


#endif