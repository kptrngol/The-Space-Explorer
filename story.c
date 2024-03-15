#include "story.h"

// define story vairable initial values
storyPhase currentStoryPhase = PROLOGUE; 

void SyPrintDialogue(storyPhase *currentStoryPhase, char dialogueData[PHASE][VERSE_NR][VERS_MAX_LENGTH])
{
    switch((*currentStoryPhase))
    {
        case PROLOGUE:
            // DrawText(TextFormat("boost st.: %d", dialogueData[0][0]), screenWidth-(MeasureText("boostcooldown st.",16))-100, 160, 16, GRAY);
            break;
        default:
    }
}

char dialogueData[PHASE][VERSE_NR][VERS_MAX_LENGTH] = 
{
    {
        {
            "Potwierdzam zakończenie procedury zejścia do przestrzenii eksploatacji. Czy aktywować tryb wspomaganego sterowania manualnego?"
        },
        {
            "Aktywuj sterowanie manualne, 10% asysty"
        }
    },
    {
        {

            "Namierzyłem niezidentyfikowany sygnał po przeciwnej stronie planety: 256 tysięcy kilometrów do kontaktu"
        }
    }
};

