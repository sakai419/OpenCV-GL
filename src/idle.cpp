#include "global.hpp"
#include "callback.hpp"
#include "state.hpp"
#include <GLUT/glut.h>
#include <cmath>
#include <chrono>
#include <random>

using namespace std::chrono;

bool done = false;

static void init_object_position(GLfloat (*position)[3]);
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

    if (remaining_time < 5.0 && !done && g_difficulty == HARD)
    {
        done = true;
        init_object_position(&object_position);
    }
    else if (remaining_time < 0.0)
    {
        change_state(STATE_ANSWER);
    }
    glutPostRedisplay();
}

void idle_answer()
{
    g_highlight = generateOscillatingValue() + 0.3;
    glutPostRedisplay();
}

void idle_result()
{
    glutPostRedisplay();
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

float getRandomFloat(float min, float max)
{
    // 乱数エンジン (std::mt19937: メルセンヌ・ツイスタ)
    std::random_device rd;  // ハードウェア乱数生成器をシードに使う
    std::mt19937 gen(rd()); // 乱数生成エンジン

    // 指定した範囲内のfloat型の乱数を生成する分布
    std::uniform_real_distribution<float> dis(min, max);

    // 乱数を生成して返す
    return dis(gen);
}

static void init_object_position(GLfloat (*position)[3])
{
    for (int i = 0; i < 3; i++)
    {
        (*position)[i] = getRandomFloat(-2.0, 2.0);
    }
}