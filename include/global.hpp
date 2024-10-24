#pragma once

#include <string>
#include <GLUT/glut.h>
#include <opencv2/core/core.hpp>

using namespace std;
using namespace std::chrono;
using namespace cv;

enum State
{
    STATE_HOME,
    STATE_STAGE,
    STATE_ANSWER,
    STATE_RESULT
};

enum Difficulty
{
    EASY,
    NORMAL,
    HARD
};

constexpr const int WINDOW_X = 1000;
constexpr const int WINDOW_Y = 1000;
constexpr const char *WINDOWNAME = "GAME";
constexpr const double TIME_LIMIT = 10.0;
constexpr const int HOME_TEXTURE_ID = 0;
constexpr const int ANSWER_TEXTURE_ID = 1;
constexpr const int RESULT_TEXTURE_ID = 2;

extern int g_shape;
// extern long g_difficulty;
extern double g_highlight;
extern double g_angle1;
extern double g_angle2;
extern double g_distance;
extern double remaining_time;
extern bool g_isLeftButtonOn;
extern bool g_isRightButtonOn;
extern bool g_isCorrect;
extern State g_state;
extern steady_clock::time_point g_time;
extern GLfloat light_position[3];
extern GLfloat object_position[3];
extern GLuint textureIDs[100];
extern Mat images[100];
extern Difficulty g_difficulty;
