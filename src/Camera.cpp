#include "../inc/Camera.h"

Camera::Camera(int width, int height, glm::vec3 position, float FOVdeg, float nearPlane, float farPlane)
{
    this->width = width;
    this->height = height;
    Position = position;
    this->FOVdeg = FOVdeg;
    this->nearPlane = nearPlane;
    this->farPlane = farPlane;
}

void Camera::Matrix(Shader &shader, const char *uniform)
{
    // std::cout << Orientation.x << "  " << Orientation.y << "  " << Orientation.z << std::endl;
    // std::cout << Position.x << "  " << Position.y << "  " << Position.z << std::endl;

    view = glm::lookAt(Position, Position + Orientation, Yaxis); // form where to look at, what to look at , up vector
    projection = glm::perspective(glm::radians(FOVdeg), (float)(width / height), nearPlane, farPlane);
    ortho_projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);
    glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(projection * view));
}

void Camera::Inputs(GLFWwindow *window, uint8_t walls)
{

    if (!V_pressed)
    {
        // std::cout<<Position.x<<"   "<<Position.z<<std::endl;
        float leftDistance = fabs(Position.x - floor(Position.x / 2) * 2.0f);
        float topDistance = fabs(Position.z - floor(Position.z / 2) * 2.0f);
        float rightDistance = fabs(Position.x - (floor(Position.x / 2) + 1) * 2.0f);
        float bottomDistance = fabs(Position.z - (floor(Position.z / 2) + 1) * 2.0f);
        // top left corner wall
        if (topDistance < 0.4 && leftDistance < 0.4)
        {
            if (topDistance > leftDistance)
            {
                Position.z = floor(Position.z / 2) * 2 + 0.4;
            }
            else if (topDistance < leftDistance)
            {
                Position.x = floor(Position.x / 2) * 2 + 0.4;
            }
            else if (topDistance = leftDistance)
            {
                Position.x = floor(Position.x / 2) * 2 + 0.4;
                Position.z = floor(Position.z / 2) * 2 + 0.4;
            }
        }
        if (topDistance < 0.4 && rightDistance < 0.4)
        {
            if (topDistance > rightDistance)
            {
                Position.z = floor(Position.z / 2) * 2 + 0.4;
            }
            else if (topDistance < rightDistance)
            {
                Position.x = (floor(Position.x / 2) + 1) * 2 - 0.4;
            }
            else if (topDistance = rightDistance)
            {
                Position.x = (floor(Position.x / 2) + 1) * 2 - 0.4;
                Position.z = floor(Position.z / 2) * 2 + 0.4;
            }
        }
        if (bottomDistance < 0.4 && leftDistance < 0.4)
        {
            if (bottomDistance > leftDistance)
            {
                Position.z = (floor(Position.z / 2) + 1) * 2 - 0.4;
            }
            else if (bottomDistance < leftDistance)
            {
                Position.x = floor(Position.x / 2) * 2 + 0.4;
            }
            else if (bottomDistance = leftDistance)
            {
                Position.x = floor(Position.x / 2) * 2 + 0.4;
                Position.z = (floor(Position.z / 2) + 1) * 2 - 0.4;
            }
        }
        if (bottomDistance < 0.4 && rightDistance < 0.4)
        {
            if (bottomDistance > rightDistance)
            {
                Position.z = (floor(Position.z / 2) + 1) * 2 - 0.4;
            }
            else if (bottomDistance < rightDistance)
            {
                Position.x = (floor(Position.x / 2) + 1) * 2 - 0.4;
            }
            else if (bottomDistance = rightDistance)
            {
                Position.x = (floor(Position.x / 2) + 1) * 2 - 0.4;
                Position.z = (floor(Position.z / 2) + 1) * 2 - 0.4;
            }
        }

        // left
        if ((walls & 0x02) != 0)
        {
            if (Position.x < floor(Position.x / 2) * 2 + 0.4f)
            {
                Position.x = floor(Position.x / 2) * 2 + 0.4f;
            }
        }

        // top
        if ((walls & 0x01) != 0)
        {
            if (Position.z < floor(Position.z / 2) * 2 + 0.4f)
            {
                Position.z = floor(Position.z / 2) * 2 + 0.4f;
            }
        }

        // right
        if ((walls & 0x08) != 0)
        {
            if (Position.x > (floor(Position.x / 2) + 1) * 2 - 0.4)
            {
                Position.x = (floor(Position.x / 2) + 1) * 2 - 0.4;
            }
        }

        // bottom
        if ((walls & 0x04) != 0)
        {

            if (Position.z > (floor(Position.z / 2) + 1) * 2 - 0.4)
            {
                Position.z = (floor(Position.z / 2) + 1) * 2 - 0.4;
            }
        }
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        Position += speed * glm::vec3(Orientation.x, 0, Orientation.z);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        Position += speed * -glm::normalize(glm::cross(Orientation, Yaxis));
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        Position += speed * -glm::vec3(Orientation.x, 0, Orientation.z);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        Position += speed * glm::normalize(glm::cross(Orientation, Yaxis));
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        speed = 0.5f;
    }
    else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
    {
        speed = 0.1f;
    }
    // if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    // {
    // Hides mouse cursor

    // Prevents camera from jumping on the first click
    // if (firstClick)
    // {
    //     glfwSetCursorPos(window, (width / 2), (height / 2));
    //     firstClick = false;
    // }

    // Stores the coordinates of the cursor
    double mouseX;
    double mouseY;
    // Fetches the coordinates of the cursor
    glfwGetCursorPos(window, &mouseX, &mouseY);
    glfwSetCursorPos(window, width / 2, height / 2);

    // Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
    // and then "transforms" them into degrees
    float rotX = sensitivity * (float)(mouseY - (height / 2)) / height;
    float rotY = sensitivity * (float)(mouseX - (width / 2)) / width;

    // Calculates upcoming vertical change in the Orientation
    glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(rotX), glm::normalize(glm::cross(Orientation, Yaxis)));

    // Decides whether or not the next vertical Orientation is legal or not
    if (fabs(glm::angle(newOrientation, Yaxis) - glm::radians(90.0f)) <= glm::radians(85.0f))
    {
        Orientation = newOrientation;
    }

    // Rotates the Orientation left and right
    Orientation = glm::rotate(Orientation, glm::radians(rotY), Yaxis);

    // Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around
    // glfwSetCursorPos(window, (width / 2), (height / 2));

if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
{
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    firstClick = true;
}
if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
{
    V_released = false;
}
if (glfwGetKey(window, GLFW_KEY_V) == GLFW_RELEASE)
{
    if (V_released == false)
    {
        if (!V_pressed)
        {
            lastPosition = Position;
            lastOrientation = Orientation;
            Position = glm::vec3(-10.0f, 2.0f, -10.0f);
            Orientation = glm::vec3(1.0f, 0.0f, 1.0f);
        }
        else
        {
            Position = lastPosition;
            Orientation = lastOrientation;
        }
        V_pressed = !V_pressed;
    }
    V_released = true;
}
}
void Camera::Rotate(GLfloat degree, glm::vec3 axis)
{
    Orientation = glm::rotate(Orientation, glm::radians(degree), axis);
}

void Camera::change_orientation()
{
    Orientation = glm::vec3(0.00104305f, -4.0f, -0.089938f);
}

void display_4x4(std::string tag, glm::mat4 m4)
{
    std::cout << tag << '\n';
    for (int col = 0; col < 4; ++col)
    {
        std::cout << "| ";
        for (int row = 0; row < 4; ++row)
        {
            std::cout << m4[row][col] << '\t';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

glm::vec3 Camera::getPos()
{
    return Position;
}
glm::mat4 Camera::get_view()
{
    return view;
}
glm::mat4 Camera::get_projection()
{
    return projection;
}