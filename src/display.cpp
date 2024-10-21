#include "callback.hpp"
#include "global.hpp"
#include <GLUT/glut.h>
#include <cmath>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::chrono;

static void draw_pyramid();
static void drawTextOverlay(string text, int x, int y, float scale);
static void renderStrokeText(string text, float x, float y, float scale);

void display_home()
{
    glClear(GL_COLOR_BUFFER_BIT);

    drawTextOverlay("Welcome to the game", -400, 100, 0.5);
    drawTextOverlay("Press 's' to start", -200, 0, 0.3);
    drawTextOverlay("Press 'q' to quit", -200, -100, 0.3);

    glutSwapBuffers();
}

void display_stage()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30.0, 1.0, 0.1, 100);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    if (cos(g_angle2) > 0)
    {
        gluLookAt(g_distance * cos(g_angle2) * sin(g_angle1),
                  g_distance * sin(g_angle2),
                  g_distance * cos(g_angle2) * cos(g_angle1),
                  0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    }
    else
    {
        gluLookAt(g_distance * cos(g_angle2) * sin(g_angle1),
                  g_distance * sin(g_angle2),
                  g_distance * cos(g_angle2) * cos(g_angle1),
                  0.0, 0.0, 0.0, 0.0, -1.0, 0.0);
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    glPushMatrix();
    glRotatef(-30, 0.0, 0.0, 1.0);
    glTranslatef(-1.0, 3.0, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    glutWireTeapot(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, -2.0, 0.0);
    draw_pyramid();
    glPopMatrix();

    drawTextOverlay(to_string(remaining_time), -WINDOW_X / 2 + 10, WINDOW_Y / 2 - 50, 0.3);

    glFlush();
    glDisable(GL_DEPTH_TEST);
    glutSwapBuffers();
}

void display_answer()
{
    glClear(GL_COLOR_BUFFER_BIT);

    drawTextOverlay("Select the correct shape", -400, 100, 0.5);

    glutSwapBuffers();
}

static void draw_pyramid()
{
    GLdouble pointO[] = {0.0, 1.0, 0.0};
    GLdouble pointA[] = {1.5, -1.0, 1.5};
    GLdouble pointB[] = {-1.5, -1.0, 1.5};
    GLdouble pointC[] = {-1.5, -1.0, -1.5};
    GLdouble pointD[] = {1.5, -1.0, -1.5};

    glColor3d(1.0, 0.0, 0.0);
    glBegin(GL_TRIANGLES);
    glVertex3dv(pointO);
    glVertex3dv(pointA);
    glVertex3dv(pointB);
    glEnd();

    glColor3d(1.0, 1.0, 0.0);
    glBegin(GL_TRIANGLES);
    glVertex3dv(pointO);
    glVertex3dv(pointB);
    glVertex3dv(pointC);
    glEnd();

    glColor3d(0.0, 1.0, 1.0);
    glBegin(GL_TRIANGLES);
    glVertex3dv(pointO);
    glVertex3dv(pointC);
    glVertex3dv(pointD);
    glEnd();

    glColor3d(1.0, 0.0, 1.0);
    glBegin(GL_TRIANGLES);
    glVertex3dv(pointO);
    glVertex3dv(pointD);
    glVertex3dv(pointA);
    glEnd();

    glColor3d(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3dv(pointA);
    glVertex3dv(pointB);
    glVertex3dv(pointC);
    glVertex3dv(pointD);
    glEnd();
}

static void drawTextOverlay(string text, int x, int y, float scale)
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();                                                       // 現在の投影行列を保存
    glLoadIdentity();                                                     // 単位行列にリセット
    gluOrtho2D(-WINDOW_X / 2, WINDOW_X / 2, -WINDOW_Y / 2, WINDOW_Y / 2); // 画面サイズに合わせて正投影を設定

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();   // 現在のモデルビュー行列を保存
    glLoadIdentity(); // 単位行列にリセット

    // 文字を表示する座標（画面の左上からのオフセット）
    glColor3f(1.0, 1.0, 1.0); // 白色で描画
    renderStrokeText(text, x, y, scale);

    glPopMatrix(); // モデルビュー行列を元に戻す
    glMatrixMode(GL_PROJECTION);
    glPopMatrix(); // 投影行列を元に戻す
    glMatrixMode(GL_MODELVIEW);
}

static void renderStrokeText(string text, float x, float y, float scale)
{
    glPushMatrix();
    glTranslatef(x, y, 0.0f);      // 表示位置を設定
    glScalef(scale, scale, scale); // フォントのサイズを変更

    for (int i = 0; i < text.size(); i++)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, text[i]);
    }

    glPopMatrix();
}