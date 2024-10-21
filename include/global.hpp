#pragma once

#include <string>

using namespace std;

enum State
{
    STATE_HOME,
    STATE_STAGE
};

constexpr const int WINDOW_X = 1000;
constexpr const int WINDOW_Y = 1000;
constexpr const char *WINDOWNAME = "GAME";

extern double g_angle1;
extern double g_angle2;
extern double g_distance;
extern bool g_isLeftButtonOn;
extern bool g_isRightButtonOn;
extern State g_state;
extern time_t g_time;
