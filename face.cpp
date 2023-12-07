#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <GL/gl.h>

#include <iostream>

#include "face.h"
#include "utils.h"
#include "config.h"

Face::Face()
{
    // :D
}

Face::Face(glm::vec4 points[4])
{
    for (int i=0; i<4; i++)
    {
        this->vr[i] = points[i];
    }
    this->color = glm::vec3(1.0, 1.0, 1.0);
}

void Face::setTex(glm::vec2 tx_coords[4], unsigned tex)
{
    this->is_tex = true;
    this->tex = tex;
    for(int i=0; i<4; i++)
    {
        this->tx[i] = tx_coords[i];
    }
}

glm::vec4 *Face::getVertices()
{
    return this->vr;
}

void Face::printVertices()
{
    std::cout << glm::to_string(this->vr[0]) << " " << glm::to_string(this->vr[1]) << std::endl;
    std::cout << glm::to_string(this->vr[3]) << " " << glm::to_string(this->vr[2]) << std::endl;
}

void Face::setNormal()
{
    glm::vec4 a = this->vr[2] - this->vr[1];
    glm::vec4 b = this->vr[0] - this->vr[1];
    this->normal = glm::cross(glm::vec3(b), glm::vec3(a));
}

void Face::transform(glm::mat4 M)
{
    for(int i=0; i<4; i++)
    {
        vr[i] = M * vr[i];
    }
    this->setNormal();
}

void Face::displayGrid()
{
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    for(int i=0; i<4; i++) 
    {
        glVertex3fv(glm::value_ptr(this->vr[i]));
    }
    glEnd();
}

void Face::displayTex()
{
    glNormal3fv(glm::value_ptr(this->normal));
    glColor3f(1.0, 1.0, 1.0);
    glBindTexture(GL_TEXTURE_2D, this->tex);
    glBegin(GL_TRIANGLE_FAN);
    for(int i=0; i<4; i++) 
    {
    	glTexCoord2fv(glm::value_ptr(this->tx[i]));
    	glVertex3fv(glm::value_ptr(this->vr[i]));
    }
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);

    // this->displayGrid();
}

void Face::setColor(glm::vec3 color)
{
    this->is_color = true;
    this->color = color;
}

void Face::displayColor()
{
    glNormal3fv(glm::value_ptr(this->normal));
    glColor3fv(glm::value_ptr(this->color));
    glBegin(GL_TRIANGLE_FAN);
    
    for(int i=0; i<4; i++)
    {
    	glVertex3fv(glm::value_ptr(this->vr[i]));
    }
    glEnd();

    // this->displayGrid();
}