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
    case 's':
    case 'S':
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