#ifndef GLSHADERS_H
#define GLSHADERS_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>

using glm::mat4;
using glm::vec3;
using glm::vec2;
using std::string;

class OpenGLShader
{
private:
    string vertexPath;
    string fragmentPath;
    GLuint shader_id;
    GLuint activeUniformLocation;

    static GLuint load(const char *vertexPath, const char *fragmentPath);
    static void compile(const char *src, GLuint &id);
    inline void destroy() const;
public:
    explicit OpenGLShader(string vertexPath, string fragmentPath);
    ~OpenGLShader();

    inline void use() const;
    inline void stop() const;
    void setActiveUniformLocation(const char *name);
    void loadMat4(const mat4 mat) const;
    void loadVec3(const vec3 vec) const;
    void loadVec2(const vec2 vec) const;
    void loadFloat(const float fp) const;
};

#endif