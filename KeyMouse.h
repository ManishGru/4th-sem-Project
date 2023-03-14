
#include <iostream>
#include <iosfwd>
#include <sstream>
#include <fstream>
#include <cerrno>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <glm/common.hpp>
#include <glm/gtc/matrix_transform.hpp>


using namespace glm;

class Control
{
public:
    Control(GLFWwindow *);
    void computeMatrices();
    mat4 getProjectionMatrix();
    mat4 getViewMatrix();

private:
    GLFWwindow *window;
    vec3 position;
    float horizontalAngle;
    float verticalAngle;
    float initialFoV;
    float speed;
    float mouseSpeed;
    mat4 ProjectionMatrix;
    mat4 ViewMatrix;

    // vec3 direction, right, up;
};

Control::Control(GLFWwindow *win)
{
    this->window = win;
    position = vec3(3, 4, 3);
    horizontalAngle = 3.14f;
    verticalAngle = 0.0f;
    initialFoV = 45.0f;
    speed = 0.000003f;
    mouseSpeed = 0.0005f;
}
void Control::computeMatrices()
{
    static double prevTime = glfwGetTime();
    double currTime = glfwGetTime();
    double dt = currTime - prevTime;

    double xpos, ypos;
    int width, height;
    glfwGetCursorPos(window, &xpos, &ypos);
    glfwGetWindowSize(window, &width, &height);
    glfwSetCursorPos(window, width / 2, height / 2);

    horizontalAngle += mouseSpeed * dt * float(width / 2 - xpos);
    verticalAngle += mouseSpeed * dt * float(height / 2 - ypos);

    vec3 direction(
        cos(verticalAngle) * sin(horizontalAngle),
        sin(verticalAngle),
        cos(verticalAngle) * cos(horizontalAngle));
    vec3 right = vec3(sin(horizontalAngle - 3.14f / 2.0f),
                      0,
                      cos(horizontalAngle - 3.14f / 2.0f));

    vec3 up = cross(right, direction);

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        position += direction * float(dt * speed);
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        position -= direction * float(dt * speed);
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        position += right * float(dt * speed);
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        position -= right * float(dt * speed);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        position -= up * float(dt * speed);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        position += up * float(dt * speed);
    }
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
    {
        position += vec3(.1 * cos(dt), 0, .1 * sin(dt));
    }
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
    {
        position = vec3(.1 * cos(dt), 0, .1 * sin(dt));
    }

    if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)
    {
        position = vec3(4, 3, 3);
        direction = vec3(-4, -3, -3);
        right = vec3(4, 3, 3);
        up = vec3(0, 1, 0);
    }
    // float FoV = initialFoV - 5*glfwSetScrollCallback(window, )

    ProjectionMatrix = perspective(radians(initialFoV), float(width) / float(height), 0.1f, 100.0f);

    ViewMatrix = lookAt(position,
                        position + direction,
                        up);
}
mat4 Control::getProjectionMatrix()
{
    return ProjectionMatrix;
}
mat4 Control::getViewMatrix()
{
    return ViewMatrix;
}
