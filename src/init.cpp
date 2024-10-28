#include "global.hpp"
#include "init.hpp"
#include "callback.hpp"
#include "state.hpp"
#include <iostream>
#include <GLUT/glut.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace std::chrono;
using namespace cv;

void init_GL(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_X, WINDOW_Y);
    glutCreateWindow(WINDOWNAME);
}

void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    change_state(STATE_HOME);
}