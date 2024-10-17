#include "callback.hpp"
#include <stdlib.h>

void keyboard(unsigned char key, int x, int y)
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