#include "init.hpp"
#include <GLUT/glut.h>

int main(int argc, char **argv)
{
    init_GL(argc, argv);
    init();
    glutMainLoop();
}