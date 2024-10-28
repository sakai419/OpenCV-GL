#include "callback.hpp"
#include "global.hpp"
#include <GLUT/glut.h>
#include <cmath>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::chrono;

const float white[] = {1.0, 1.0, 1.0};
const float yellow[] = {1.0, 1.0, 0.0};

const string dif_list[] = {
    "Easy",
    "Normal",
    "Hard",
};

const string shape_list[] = {
    "Tetrahedron",
    "Cube",
    "Octahedron",
    "Dodecahedron",
    "Icosahedron",
    "Sphere",
    "Cone",
    "Torus",
    "Teapot",
};

static void drawTextOverlay(string text, int x, int y, float scale, const float color[3]);
static void renderStrokeText(string text, float x, float y, float scale);

static void draw_difficulty();
static void draw_random_shape(int rand);

void display_home()
{
    glClear(GL_COLOR_BUFFER_BIT);

    drawTextOverlay("Choose difficulty", -400, 100, 0.5, white);
    draw_difficulty();

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
    glTranslatef(object_position[0], object_position[1], object_position[2]);
    glColor3f(0.0, 0.0, 0.0);
    draw_random_shape(g_shape);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(light_position[0], light_position[1], light_position[2]);
    glColor3f(1.0, 1.0, 1.0);
    switch (g_difficulty)
    {
    case EASY:
        glutSolidSphere(0.6, 20, 20);
        break;
    case NORMAL:
        glutSolidSphere(0.5, 20, 20);
        break;
    case HARD:
        glutSolidSphere(0.5, 20, 20);
        break;
    default:
        break;
    }
    glPopMatrix();

    drawTextOverlay(to_string(remaining_time), -490, 450, 0.3, white);

    if (remaining_time < 5.0 && g_difficulty == HARD)
    {
        drawTextOverlay("Object Moved!!!", -490, 400, 0.3, yellow);
    }

    glFlush();
    glDisable(GL_DEPTH_TEST);
    glutSwapBuffers();
}

void display_answer()
{
    glutSwapBuffers();
}

void display_result()
{
    glClear(GL_COLOR_BUFFER_BIT);

    if (g_isCorrect)
    {
        drawTextOverlay("Correct!", -400, 100, 0.5, white);
    }
    else
    {
        drawTextOverlay("Incorrect!", -400, 100, 0.5, white);
        drawTextOverlay("The correct answer is " + shape_list[g_shape], -400, 0, 0.3, white);
    }

    drawTextOverlay("Press 'h' to home", -200, -100, 0.3, white);
    drawTextOverlay("Press 'q' to quit", -200, -200, 0.3, white);

    glutSwapBuffers();
}

static void drawTextOverlay(string text, int x, int y, float scale, const float color[3])
{
    x = (int)x * ((double)WINDOW_X / 1000);
    y = (int)y * ((double)WINDOW_X / 1000);
    scale *= ((double)WINDOW_X / 1000);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();                                                       // 現在の投影行列を保存
    glLoadIdentity();                                                     // 単位行列にリセット
    gluOrtho2D(-WINDOW_X / 2, WINDOW_X / 2, -WINDOW_Y / 2, WINDOW_Y / 2); // 画面サイズに合わせて正投影を設定

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();   // 現在のモデルビュー行列を保存
    glLoadIdentity(); // 単位行列にリセット

    // 文字を表示する座標（画面の左上からのオフセット）
    glColor3f(color[0], color[1], color[2]); // 白色で描画
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

static void draw_difficulty()
{
    for (int i = 0; i < 3; ++i)
    {
        if (i == g_difficulty % 3)
        {
            drawTextOverlay(dif_list[i] + " <-", -400, -100 * i, g_highlight, yellow);
        }
        else
        {
            drawTextOverlay(dif_list[i], -400, -100 * i, 0.3, white);
        }
    }
}

static void draw_random_shape(int rand)
{
    switch (rand)
    {
    case 0:
        glutSolidTetrahedron();
        break;
    case 1:
        glutSolidCube(1.0);
        break;
    case 2:
        glutSolidOctahedron();
        break;
    case 3:
        glutSolidDodecahedron();
        break;
    case 4:
        glutSolidIcosahedron();
        break;
    case 5:
        glutSolidSphere(1.0, 20, 20);
        break;
    case 6:
        glutSolidCone(1.0, 2.0, 20, 20);
        break;
    case 7:
        glutSolidTorus(0.5, 1.0, 20, 20);
        break;
    case 8:
        glutSolidTeapot(1.0);
        break;
    default:
        break;
    }
}