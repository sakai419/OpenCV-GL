#include "callback.hpp"
#include "global.hpp"
#include "state.hpp"
#include <stdlib.h>

void keyboard_home(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'q':
    case 'Q':
    case '\033':
        exit(0);
        break;
    case 10:
    case 13:
        change_state(STATE_STAGE);
        break;
    default:
        break;
    }
}

void keyboard_stage(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'q':
    case 'Q':
    case '\033':
        exit(0);
        break;
    default:
        break;
    }
}

void keyboard_answer(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 10:
    case 13:
        if (g_choose == g_shape)
        {
            g_isCorrect = true;
        }
        else
        {
            g_isCorrect = false;
        }
        change_state(STATE_RESULT);
        break;
    case 'q':
    case 'Q':
    case '\033':
        exit(0);
        break;
    default:
        break;
    }
}

void keyboard_result(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'q':
    case 'Q':
    case '\033':
        exit(0);
        break;
    case 'h':
    case 'H':
        change_state(STATE_HOME);
        break;
    default:
        break;
    }
}