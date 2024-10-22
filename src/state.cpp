#include "state.hpp"
#include "callback.hpp"
#include "global.hpp"
#include <GLUT/glut.h>
#include <random>

using namespace std::chrono;

static void set_home_callback();
static void set_stage_callback();
static void set_answer_callback();
static void set_result_callback();
static float getRandomFloat(float min, float max);
static void init_position(GLfloat (*position)[3]);

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
        g_shape = rand() % 9;
        init_position(&object_position);
        init_position(&light_position);
        set_stage_callback();
        break;
    case STATE_ANSWER:
        set_answer_callback();
        break;
    case STATE_RESULT:
        set_result_callback();
        break;
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

static void set_result_callback()
{
    glutDisplayFunc(display_result);
    glutKeyboardFunc(keyboard_result);
    glutMouseFunc(mouse_result);
    glutMotionFunc(motion_result);
    glutPassiveMotionFunc(motion_result);
    glutIdleFunc(idle_result);
}

float getRandomFloat(float min, float max)
{
    // 乱数エンジン (std::mt19937: メルセンヌ・ツイスタ)
    std::random_device rd;  // ハードウェア乱数生成器をシードに使う
    std::mt19937 gen(rd()); // 乱数生成エンジン

    // 指定した範囲内のfloat型の乱数を生成する分布
    std::uniform_real_distribution<float> dis(min, max);

    // 乱数を生成して返す
    return dis(gen);
}

static void init_position(GLfloat (*position)[3])
{
    for (int i = 0; i < 3; i++)
    {
        (*position)[i] = getRandomFloat(-3.0, 3.0);
    }
}