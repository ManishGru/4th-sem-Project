#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H
#include "glad.h"
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/rotate_vector.hpp"
#include "glm/gtx/vector_angle.hpp"

#include "shaderClass.h"
// #include "../src/cell.cpp"
class Camera
{
public:
    glm::vec3 Position,lastPosition,lastOrientation;
    glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 Yaxis = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 Xaxis = glm::vec3(1.0f, 0.0f, 0.0f);
    glm::vec3 Zaxis = glm::vec3(0.0f, 0.0f, 1.0f);
    float FOVdeg, nearPlane, farPlane;
    bool firstClick = true;
    int width;
    int height;
    float speed = 0.01f;
    float sensitivity = 100.0f;
    bool V_pressed = false;
    bool V_released = true;// key debouncing
        glm::mat4 view;
    glm::mat4 projection;
    
    Camera(int width, int height, glm::vec3 position, float FOVdeg, float nearPlane, float farPlane);
    void Matrix(Shader &shader, const char *uniform);
    void Inputs(GLFWwindow *window,uint8_t walls);

    void Rotate(GLfloat degrees, glm::vec3 axis);

    glm::vec3 getPos();
    glm::mat4 get_view();
    glm::mat4 get_projection();
    void change_orientation();
};

#endif