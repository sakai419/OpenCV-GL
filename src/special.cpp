#include "global.hpp"
#include "callback.hpp"

static void increment_difficulty();
static void decrement_difficulty();

void special_home(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_DOWN:
        increment_difficulty();
        break;
    case GLUT_KEY_UP:
        decrement_difficulty();
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

static void increment_difficulty()
{
    if (g_difficulty == EASY)
    {
        g_difficulty = NORMAL;
    }
    else if (g_difficulty == NORMAL)
    {
        g_difficulty = HARD;
    }
    else
    {
        g_difficulty = EASY;
    }
}

static void decrement_difficulty()
{
    if (g_difficulty == EASY)
    {
        g_difficulty = HARD;
    }
    else if (g_difficulty == NORMAL)
    {
        g_difficulty = EASY;
    }
    else
    {
        g_difficulty = NORMAL;
    }
}