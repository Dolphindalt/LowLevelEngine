#include "src/renderer/opengl/OpenGLShader.h"

#include <src/debugging/logging.h>
#include <src/debugging/assertions.h>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include "src/containers/io/fileio.h"

using glm::value_ptr;
using std::string;

GLuint OpenGLShader::load(const char *vertexPath, const char *fragmentPath)
{
    GLuint vs_id = glCreateShader(GL_VERTEX_SHADER);
    GLuint fs_id = glCreateShader(GL_FRAGMENT_SHADER);
    ASSERT(vs_id != 0);
    ASSERT(fs_id != 0);
    string vs_code, fs_code;
    if (!syncReadFileToStringBuffer(vertexPath, vs_code))
    {
        ERROR_LOG("Failed to load vertex shader: %s", vertexPath);
    }
    if (!syncReadFileToStringBuffer(fragmentPath, fs_code))
    {
        ERROR_LOG("Failed to load fragment shader: %s", fragmentPath);
    }

    ASSERT(vs_code.size() != 0);
    ASSERT(fs_code.size() != 0);

    OpenGLShader::compile(vs_code.c_str(), vs_id);
    OpenGLShader::compile(fs_code.c_str(), fs_id);

    GLuint shader_id = glCreateProgram();
    glAttachShader(shader_id, vs_id);
    glAttachShader(shader_id, fs_id);
    glLinkProgram(shader_id);

    GLint result = false;
    int errorLength;
    glGetProgramiv(shader_id, GL_LINK_STATUS, &result);
    glGetProgramiv(shader_id, GL_INFO_LOG_LENGTH, &errorLength);

    if (errorLength > 0 && result == GL_FALSE)
    {
        char msg[errorLength + 1];
        glGetProgramInfoLog(shader_id, errorLength, NULL, &msg[0]);
        ERROR_LOG("%s", msg);
    }

    glDetachShader(shader_id, vs_id);
    glDetachShader(shader_id, fs_id);
    glDeleteShader(fs_id);
    glDeleteShader(vs_id);

    ASSERT(shader_id > 0);

    return shader_id;
}

void OpenGLShader::compile(const char *src, GLuint &id)
{
    GLint result = GL_FALSE;
    int errorLength;
    glShaderSource(id, 1, &src, NULL);
    glCompileShader(id);
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &errorLength);
    if (errorLength > 0 && result == GL_FALSE)
    {
        char msg[errorLength + 1];
        glGetShaderInfoLog(id, errorLength, NULL, &msg[0]);
        WARNING_LOG("%s", msg);
    }
}

void OpenGLShader::destroy() const
{
    glDeleteShader(this->shader_id);
}

OpenGLShader::OpenGLShader(string vertexPath, string fragmentPath)
: vertexPath(vertexPath), fragmentPath(fragmentPath), 
    shader_id(OpenGLShader::load(vertexPath.c_str(), fragmentPath.c_str()))
{

}

OpenGLShader::~OpenGLShader()
{
    this->destroy();
}

void OpenGLShader::use() const
{
    glUseProgram(this->shader_id);
}

void OpenGLShader::stop() const
{
    glUseProgram(0);
}

void OpenGLShader::setActiveUniformLocation(const char *name)
{
    this->activeUniformLocation = glGetUniformLocation(this->shader_id, name);
}

void OpenGLShader::loadMat4(const mat4 mat) const
{
    glUniformMatrix4fv(this->activeUniformLocation, 1, GL_FALSE, value_ptr(mat));
}

void OpenGLShader::loadVec3(const vec3 vec) const
{
    glUniform3f(this->activeUniformLocation, vec.x, vec.y, vec.z);
}

void OpenGLShader::loadVec2(const vec2 vec) const
{
    glUniform2f(this->activeUniformLocation, vec.x, vec.y);
}

void OpenGLShader::loadFloat(const float fp) const
{
    glUniform1f(this->activeUniformLocation, fp);
}