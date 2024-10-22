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

static void init_textures();
static void load_texture(const string image_path, int index);

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
    init_textures();
}

static void init_textures()
{
    load_texture("images/home.png", HOME_TEXTURE_ID);
    load_texture("images/answer.png", ANSWER_TEXTURE_ID);
    load_texture("images/result.png", RESULT_TEXTURE_ID);
}

static void load_texture(const string image_path, int index)
{
    // OpenCVで画像を読み込み
    images[index] = cv::imread(image_path);
    if (images[index].empty())
    {
        std::cerr << "Failed to load image: " << image_path << std::endl;
        return;
    }

    // OpenCVのBGRフォーマットをRGBに変換
    cv::cvtColor(images[index], images[index], cv::COLOR_BGR2RGB);

    // テクスチャの生成
    glGenTextures(1, &textureIDs[index]);
    glBindTexture(GL_TEXTURE_2D, textureIDs[index]);

    // テクスチャパラメータの設定
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // 画像データをOpenGLのテクスチャに転送
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, images[index].cols, images[index].rows, 0, GL_RGB, GL_UNSIGNED_BYTE, images[index].data);
}