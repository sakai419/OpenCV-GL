#pragma once

#include <string>
#include <GLUT/glut.h>

using namespace std;
using namespace std::chrono;

enum State
{
    STATE_HOME,
    STATE_STAGE,
    STATE_ANSWER
};

constexpr const int WINDOW_X = 500;
constexpr const int WINDOW_Y = 500;
constexpr const char *WINDOWNAME = "GAME";
constexpr const double TIME_LIMIT = 10.0;

extern int g_shape;
extern double g_angle1;
extern double g_angle2;
extern double g_distance;
extern double remaining_time;
extern bool g_isLeftButtonOn;
extern bool g_isRightButtonOn;
extern State g_state;
extern steady_clock::time_point g_time;
extern GLfloat light_position[3];
extern GLfloat object_position[3];
