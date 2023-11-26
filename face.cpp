#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <GL/gl.h>

#include <iostream>

#include "face.h"
#include "utils.h"
#include "config.h"

Face::Face(glm::vec4 points[4])
{
    for (int i=0; i<4; i++)
    {
        this->vr[i] = points[i];
    }
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

void Face::transform(glm::mat4 M)
{
    for(int i=0; i<4; i++)
    {
        vr[i] = M * vr[i];
    }
}

void Face::displayTex()
{
    if(!this->is_tex) return;
    
    glBindTexture(GL_TEXTURE_2D, this->tex);
    glBegin(GL_QUADS);
    for(int i=0; i<4; i++)
    {
    	glTexCoord2fv(glm::value_ptr(this->tx[i]));
    	glVertex3fv(glm::value_ptr(this->vr[i]));
    }
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
}