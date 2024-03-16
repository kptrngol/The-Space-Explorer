#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include "story.h"
#include "game.h"


storyPhase currentStoryPhase = NONE;
int bookmark = 0;  
float dialogueT = 0.000f;


void SyStoryPhaseSwitch(storyPhase (*currentStoryPhase),int playerDistance)
{
    if((playerDistance>200)&&(playerDistance< 50000))
    {

        (*currentStoryPhase)= PROLOGUE;
    } else 
    {
        (*currentStoryPhase)= NONE;
    }
}

void SyPrintDialogue(storyPhase *currentStoryPhase, char dialogueData[PHASE][VERSE_NR][VERS_MAX_LENGTH])
{

    switch((*currentStoryPhase))
    {
        case NONE:
            break;
        case PROLOGUE:
            // sizeof(dialogueData[0])/sizeof(dialogueData[0][0])
            if (bookmark == 3)
            {
                currentStoryPhase = NONE;
                break;
            }

            DrawText(TextFormat("%s", dialogueData[1][bookmark]),(GetMonitorWidth(0))/2-((MeasureText(TextFormat("%s", dialogueData[1][bookmark]),24))/2), GetMonitorHeight(0)-116, 24, WHITE);
            if((dialogueT) < (*(dialogueTime[1][bookmark])))
            {
                (dialogueT) += GetFrameTime();
            } else
            {
                ++bookmark;
                dialogueT = 0;
            }

            break;
        default:
    }
        
}

char dialogueData[PHASE][VERSE_NR][VERS_MAX_LENGTH] = 
{
    {
    },
    {
        {
            "|Ship AI|: I confirm completion of the descent procedure into exploitation space. Shall I activate assisted manual control mode?"
        },
        {
            "|Joseph|: Yes, Activate manual control with 10% assistance. Also, activate accelerated turnaround system."
        },
        {
            "|Ship AI|: Warning, operating in exploitation space carries a higher collision probability. Increasing energy to the frontal shield."
        }

    },
    {
        {

            "test"
        }
    }
};


int dialogueTime[PHASE][VERSE_NR][1] = 
{
    {
    },
    {
        {
            8
        },
        {
            6
        },
        {
            8
        }
        
    },
    {
        {

            5
        }

    }
};

