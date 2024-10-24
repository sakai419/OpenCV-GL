#include "global.hpp"
#include <GLUT/glut.h>
#include <opencv2/core/core.hpp>

int g_shape = 0;
double g_highlight = 0.5;
double g_angle1 = 0.0;
double g_angle2 = 0.0;
double g_distance = 30.0;
double remaining_time = 0.0;
bool g_isLeftButtonOn = false;
bool g_isRightButtonOn = false;
bool g_isCorrect = false;
State g_state = STATE_HOME;
Difficulty g_difficulty = EASY;
auto g_time = high_resolution_clock::now();
GLfloat light_position[3] = {0.0, 0.0, 0.0};
GLfloat object_position[3] = {0.0, 0.0, 0.0};
GLuint textureIDs[100];
cv::Mat images[100];