#include "global.hpp"
#include "callback.hpp"

static void increment_difficulty();
static void decrement_difficulty();
static void increment_choose();
static void decrement_choose();

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

void special_answer(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_DOWN:
        increment_choose();
        break;
    case GLUT_KEY_UP:
        decrement_choose();
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

static void increment_choose()
{
    g_choose = (g_choose + 1) % 9;
}

static void decrement_choose()
{
    g_choose = (g_choose + 8) % 9;
}