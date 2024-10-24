#include "global.hpp"
#include "callback.hpp"
#include "state.hpp"
#include <GLUT/glut.h>
#include <cmath>
#include <chrono>

using namespace std::chrono;

static void renderTextureFullScreen(int texture_id);
static double generateOscillatingValue();

void idle_home()
{
    g_highlight = generateOscillatingValue();
    glutPostRedisplay();
}

void idle_stage()
{
    auto now = high_resolution_clock::now();
    auto elapsed = duration<double>(now - g_time).count();
    remaining_time = TIME_LIMIT - elapsed;

    if (remaining_time < 0.0)
    {
        change_state(STATE_ANSWER);
    }
    glutPostRedisplay();
}

void idle_answer()
{
    renderTextureFullScreen(textureIDs[ANSWER_TEXTURE_ID]);
    glutPostRedisplay();
}

void idle_result()
{
    glutPostRedisplay();
}

static void renderTextureFullScreen(int texture_id)
{
    // ウィンドウのサイズに合わせてビューポートを設定
    int width = glutGet(GLUT_WINDOW_WIDTH);
    int height = glutGet(GLUT_WINDOW_HEIGHT);
    glViewport(0, 0, width, height);

    // 2D描画の準備
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 1, 0, 1, -1, 1); // ウィンドウ全体を使うための座標系
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // テクスチャを描画
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(0.0f, 1.0f); // 左上
    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(1.0f, 1.0f); // 右上
    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(1.0f, 0.0f); // 右下
    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(0.0f, 0.0f); // 左下
    glEnd();

    glDisable(GL_TEXTURE_2D);

    glutSwapBuffers(); // ダブルバッファの切り替え
}

double generateOscillatingValue()
{
    // 現在の時刻をミリ秒単位で取得
    auto now = steady_clock::now().time_since_epoch();
    auto ms = duration_cast<milliseconds>(now).count();

    // 1秒周期で -1 から 1 の範囲で変動する値を生成
    double t = (ms % 1000) / 1000.0;             // 0 ~ 1 の間を繰り返す
    double oscillation = std::sin(2 * M_PI * t); // sin(2πt)で周期を表現

    // -1 ~ 1 の範囲を 0.4 ~ 0.6 の範囲にマッピング
    return 0.5 + 0.1 * oscillation;
}