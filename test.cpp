#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include <iostream>
#include <map>

struct Character
{
    GLuint TextureID;       // グリフのテクスチャID
    int Width, Height;      // グリフのサイズ
    int BearingX, BearingY; // グリフの位置調整
    GLuint Advance;         // 次の文字までの距離
};

std::map<GLchar, Character> Characters;

GLuint shaderProgram;
const char *vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec4 vertex; // <vec2 pos, vec2 tex>
out vec2 TexCoords;

uniform mat4 projection;

void main()
{
    gl_Position = projection * vec4(vertex.xy, 0.0, 1.0);
    TexCoords = vertex.zw;
}
)";

const char *fragmentShaderSource = R"(
#version 330 core
in vec2 TexCoord;
out vec4 color;
uniform sampler2D text;
uniform vec3 textColor;

void main()
{
    color = vec4(textColor, 1.0) * texture(text, TexCoord);
}
)";

void checkOpenGLError(const char *functionName)
{
    GLenum error;
    while ((error = glGetError()) != GL_NO_ERROR)
    {
        std::cerr << "OpenGL error in " << functionName << ": " << error << std::endl;
    }
}

void checkShaderCompilation(GLuint shader)
{
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        GLint length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        char *log = new char[length];
        glGetShaderInfoLog(shader, length, NULL, log);
        std::cerr << "ERROR::SHADER::COMPILATION_FAILED\n"
                  << log << std::endl;
        delete[] log;
    }
}

void checkProgramLinking(GLuint program)
{
    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        GLint length;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
        char *log = new char[length];
        glGetProgramInfoLog(program, length, NULL, log);
        std::cerr << "ERROR::PROGRAM::LINKING_FAILED\n"
                  << log << std::endl;
        delete[] log;
    }
}

void setupShaders()
{
    // バーテックスシェーダーのコンパイル
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // エラーチェック
    GLint success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        GLint length;
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &length);
        char *log = new char[length];
        glGetShaderInfoLog(vertexShader, length, NULL, log);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                  << log << std::endl;
        delete[] log;
        return;
    }

    // フラグメントシェーダーのコンパイル
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // エラーチェック
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        GLint length;
        glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &length);
        char *log = new char[length];
        glGetShaderInfoLog(fragmentShader, length, NULL, log);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                  << log << std::endl;
        delete[] log;
        return;
    }

    // シェーダープログラムの作成
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    // アトリビュートの設定
    glBindAttribLocation(shaderProgram, 0, "position");
    glBindAttribLocation(shaderProgram, 1, "texCoord");

    glLinkProgram(shaderProgram);
    checkProgramLinking(shaderProgram);

    // シェーダーのクリーンアップ
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void LoadFont(const char *fontPath)
{
    FT_Library ft;
    if (FT_Init_FreeType(&ft))
    {
        std::cerr << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        return;
    }

    FT_Face face;
    if (FT_New_Face(ft, fontPath, 0, &face))
    {
        std::cerr << "ERROR::FREETYPE: Failed to load font" << std::endl;
        FT_Done_FreeType(ft);
        return;
    }

    FT_Set_Pixel_Sizes(face, 0, 48); // フォントサイズを設定

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // テクスチャの行のアライメントを1に設定

    for (GLubyte c = 0; c < 128; c++)
    {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cerr << "ERROR::FREETYPE: Failed to load Glyph" << std::endl;
            continue;
        }

        GLuint texture;
        glGenTextures(1, &texture);
        checkOpenGLError("glGenTextures");
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer);

        checkOpenGLError("glTexImage2D"); // エラーチェック

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        Character character = {
            texture,
            static_cast<int>(face->glyph->bitmap.width),
            static_cast<int>(face->glyph->bitmap.rows),
            face->glyph->bitmap_left,
            face->glyph->bitmap_top,
            static_cast<GLuint>(face->glyph->advance.x)};
        Characters.insert(std::pair<GLchar, Character>(c, character));
    }

    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}

void RenderText(std::string text, float x, float y, float scale)
{
    glUseProgram(shaderProgram); // シェーダープログラムを使用する

    // テキストの色を設定
    glUniform3f(glGetUniformLocation(shaderProgram, "textColor"), 1.0f, 1.0f, 1.0f); // 白色に設定

    for (auto c : text)
    {
        Character ch = Characters[c];

        float xpos = x + ch.BearingX * scale;
        float ypos = y - (ch.Height - ch.BearingY) * scale;

        float w = ch.Width * scale;
        float h = ch.Height * scale;

        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f);
        glVertex2f(xpos, ypos);
        glTexCoord2f(1.0f, 1.0f);
        glVertex2f(xpos + w, ypos);
        glTexCoord2f(1.0f, 0.0f);
        glVertex2f(xpos + w, ypos + h);
        glTexCoord2f(0.0f, 0.0f);
        glVertex2f(xpos, ypos + h);
        glEnd();

        x += (ch.Advance >> 6) * scale;
    }
    glBindTexture(GL_TEXTURE_2D, 0);
}

int main()
{
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // OpenGLバージョンの指定
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "OpenGL Text Rendering", NULL, NULL);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    glewInit();

    LoadFont("/Library/Fonts/Arial Unicode.ttf");

    setupShaders();

    while (!glfwWindowShouldClose(window))
    {
        glEnable(GL_BLEND);
        glClear(GL_COLOR_BUFFER_BIT);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        RenderText("abc", 10.0f, 10.0f, 1.0f);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
