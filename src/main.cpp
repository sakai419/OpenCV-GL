#include "init.hpp"
#include <GLUT/glut.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv)
{
    srand(time(NULL));
    init_GL(argc, argv);
    init();
    glutMainLoop();
}