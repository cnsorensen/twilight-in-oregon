// game.cpp

#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "plot.h"

//#include "person.h"
//#include "persons.h"
//#include "place.h"

Game :: Game()
: m_title("")
{
}

Game :: Game(char* title)
: m_title(title)
{
}

Game :: ~Game()
{
}

// setters and getters
int Game :: SetTitle(char* title)
{
    m_title = title;
    return 1;
}

char* Game :: GetTitle(void)
{
    return m_title;
}

// functions
void Game :: Run()
{
    for(int i = 0; i < 5; i++)
    {
        PLOTS[i]();
    }

    return;
}

int Game :: PrintTitle(TextColor tc)
{
    // FIXME: add some animation?
    fprintf(stdout, "%s%s\n", tc, m_title);
    return 1;
}

void Game :: LoadGame(char* fileName)
{
    int i;
    int val;
    FILE* gameFile;

    // open file
    gameFile = fopen(fileName, "r");

    // check if file opened
    if(!gameFile)
    {
        fprintf(stdout, "%s%s - Unable to open file %s", TC_RED, 
                __PRETTY_FUNCTION__, fileName);
        return;
    }

    // grab values from file
    val = -1;
    for(int i = 0; i < 5; i++)
    {
        fscanf(gameFile, "%d", &val);

        PLOT_FLAGS[i] = val;

        if(feof(gameFile))
        {
            fprintf(stdout, "%s%s - Invalid file %s", TC_RED,
                    __PRETTY_FUNCTION__, fileName);
            return;
        }

        // debugging
        fprintf(stdout, "%d ", val);
    }

    // get sat points
    fscanf(gameFile, "%d", &val);
    SARAHG_SAT = val;

    // debugging
    fprintf(stdout, "%d\n", val);

    // close gamefile
    fclose(gameFile);

    return;
}

void Game :: SaveGame(void)
{
    int i;
    int val;
    FILE* gameFile;

    // open file
    gameFile = fopen("file.service", "w");

    // check if file opened
    if(!gameFile)
    {
        fprintf(stdout, "%s%s - Unable to open file %s", TC_RED, 
                __PRETTY_FUNCTION__, "gamesave.txt");
        return;
    }

    // grab values from file
    val = -1;
    for(int i = 0; i < 5; i++)
    {
        val = PLOT_FLAGS[i];
        fprintf(gameFile, "%d\n", val);
    }

    // put sat points
    SARAHG_SAT = val;
    fprintf(gameFile, "%d\n", &val);

    // debugging
    fprintf(stdout, "%d\n", val);

    // close gamefile
    fclose(gameFile);

    return;
}
