#ifndef UTILS_H
#define UTILS_H

#include <glm/glm.hpp>
#include "config.h"

glm::mat4 I = glm::mat4(1.0f);

// matrizes de rotação da câmera
glm::mat4 R_CAM_Y = glm::rotate(I, (float) glm::radians(cam_speed), glm::vec3(0,1,0));
glm::mat4 R_CAM_X = glm::rotate(I, (float) glm::radians(cam_speed), glm::vec3(1,0,0));
glm::mat4 R_CAM_Z = glm::rotate(I, (float) glm::radians(cam_speed), glm::vec3(0,0,1));

void display_axis()
{
    glBegin(GL_LINES);
    glColor3f(0.3, 0.0, 0.0);
    glVertex3f(0,0,0);
    glVertex3f(100,0,0);
    glColor3f(0.0, 0.3, 0.0);
    glVertex3f(0,0,0);
    glVertex3f(0,100,0);
    glColor3f(0.0, 0.0, 0.3);
    glVertex3f(0,0,0);
    glVertex3f(0,0,100);
    glEnd();
}

#endif // UTILS_H