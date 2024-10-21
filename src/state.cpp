#include "state.hpp"
#include "callback.hpp"
#include "global.hpp"
#include <GLUT/glut.h>

using namespace std::chrono;

static void set_home_callback();
static void set_stage_callback();
static void set_answer_callback();

void change_state(State state)
{
    g_state = state;
    switch (state)
    {
    case STATE_HOME:
        set_home_callback();
        break;
    case STATE_STAGE:
        remaining_time = 5.0;
        g_time = high_resolution_clock::now();
        set_stage_callback();
        break;
    case STATE_ANSWER:
        set_answer_callback();
    default:
        break;
    }
}

static void set_home_callback()
{
    glutDisplayFunc(display_home);
    glutKeyboardFunc(keyboard_home);
    glutMouseFunc(mouse_home);
    glutMotionFunc(motion_home);
    glutPassiveMotionFunc(motion_home);
    glutIdleFunc(idle_home);
}

static void set_stage_callback()
{
    glutDisplayFunc(display_stage);
    glutKeyboardFunc(keyboard_stage);
    glutMouseFunc(mouse_stage);
    glutMotionFunc(motion_stage);
    glutPassiveMotionFunc(motion_stage);
    glutIdleFunc(idle_stage);
}

static void set_answer_callback()
{
    glutDisplayFunc(display_answer);
    glutKeyboardFunc(keyboard_answer);
    glutMouseFunc(mouse_answer);
    glutMotionFunc(motion_answer);
    glutPassiveMotionFunc(motion_answer);
    glutIdleFunc(idle_answer);
}