#pragma once

#include <string>

using namespace std;
using namespace std::chrono;

enum State
{
    STATE_HOME,
    STATE_STAGE,
    STATE_ANSWER
};

constexpr const int WINDOW_X = 1000;
constexpr const int WINDOW_Y = 1000;
constexpr const char *WINDOWNAME = "GAME";

extern double g_angle1;
extern double g_angle2;
extern double g_distance;
extern double remaining_time;
extern bool g_isLeftButtonOn;
extern bool g_isRightButtonOn;
extern State g_state;
extern steady_clock::time_point g_time;
