#include <GL/glew.h>
#include "Camera.h"
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <gtx/rotate_vector.hpp>
#include <gtx/vector_angle.hpp>
#include <iostream>







void Camera::Init(int Height, int Width, Vector3 Pos)
{
}

void Camera::Matrix(CamMat& Set)
{
    glm::mat4x4 View(1.0f);
    glm::mat4x4 Proj(1.0f);

    View = glm::lookAt(Position, Position + Orientation, Up);
    Proj = glm::perspective(
          glm::radians((float)Fov)
        , (float)(Width / Height)
        , NearPlane
        , FarPlane);

    Set.Proj = Proj;
    Set.View = View;
    Set.CamPos = Position;
    if (!FreezeOri) Set.CamDir = Orientation;

}

void Camera::Inputs(GLFWwindow* Window)
{

    
    //std::cout << "Input Pos : x " << Position.x << " y " << Position.y << " z " << Position.z <<  "\n";
    DF_MAP_KEY_INPUT(Window, GLFW_KEY_W) Position += Orientation * Speed;
    DF_MAP_KEY_INPUT(Window, GLFW_KEY_A) Position += Speed * -glm::normalize(glm::cross(Orientation,Up));
    DF_MAP_KEY_INPUT(Window, GLFW_KEY_S) Position += -Orientation * Speed;
    DF_MAP_KEY_INPUT(Window, GLFW_KEY_D) Position += Speed * glm::normalize(glm::cross(Orientation, Up));
    DF_MAP_KEY_INPUT(Window, GLFW_KEY_Q) Position += Speed * Up;
    DF_MAP_KEY_INPUT(Window, GLFW_KEY_E) Position += Speed * -Up;
    DF_MAP_KEY_INPUT(Window, GLFW_KEY_ENTER) Position = Vector3(0, 4, -3);
    DF_MAP_KEY_INPUT(Window, GLFW_KEY_DOWN) Speed -= 0.00001;
    DF_MAP_KEY_INPUT(Window, GLFW_KEY_UP) Speed += 0.00001;
    Speed = std::max<float>(0, Speed);

    if (glfwGetMouseButton(Window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
        glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
       
        double M_X, M_Y;
        glfwGetCursorPos(Window, &M_X, &M_Y);


        double DMX = M_X - (Width / 2), DMY = M_Y - (Height / 2);
        
 
        float Rot_X = (Sensitvity/100) * DMY;
        float Rot_Y = (Sensitvity/100) * DMX;
        //std::cout << Rot_X << " " << Rot_Y << "\n";

        Vector3 N_O = glm::rotate(Orientation, glm::radians(-Rot_X), glm::normalize(glm::cross(Orientation, Up)));

        if (!(glm::angle(N_O, Up) <= glm::radians(5.0f) or (glm::angle(N_O, -Up) <= glm::radians(5.0f)))) {
            Orientation = N_O;
        }

        Orientation = glm::rotate(Orientation,glm::radians(-Rot_Y),Up);

        glfwSetCursorPos(Window, (Width / 2), (Height / 2));

    }
    else if (glfwGetMouseButton(Window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE) {
        glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        FirstClick = true;
    }

}



