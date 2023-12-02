#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <GL/gl.h>

#include <iostream>
#include <cstdlib>
#include <cmath>

#include "utils.h"
#include "cube.h"
#include "config.h"
#include "face.h"
#include "face.cpp"

// cria um cubo centralizado na origem, raio 1

/*
 * Esquema de criação do cubo:
 * A face 1 está virada para o eixo Z positivo
 *      ---
 *     | 5 |
 *      ---
 *     | 4 |
 *  --- --- ---
 * | 3 | 0 | 2 |
 *  --- --- ---
 *     | 1 |
 *      ---
*/
void Cube::setFaces()
{
    float k = 0.5;

    // face frontal
    glm::vec4 vertices_0[4] = {
        glm::vec4(-k, k, k, 1.0f),
        glm::vec4( k, k, k, 1.0f),
        glm::vec4( k,-k, k, 1.0f),
        glm::vec4(-k,-k, k, 1.0f)
    };
    this->faces[0] = Face(vertices_0);
    
    // face de baixo
    glm::vec4 vertices_1[4] = {
        glm::vec4(-k,-k, k, 1.0f),
        glm::vec4( k,-k, k, 1.0f),
        glm::vec4( k,-k,-k, 1.0f),
        glm::vec4(-k,-k,-k, 1.0f)
    };
    this->faces[1] = Face(vertices_1);

    // face da direita
    glm::vec4 vertices_2[4] = {
        glm::vec4( k, k, k, 1.0f),
        glm::vec4( k, k,-k, 1.0f),
        glm::vec4( k,-k,-k, 1.0f),
        glm::vec4( k,-k, k, 1.0f)
    };
    this->faces[2] = Face(vertices_2);

    // face da esquerda
    glm::vec4 vertices_3[4] = {
        glm::vec4(-k, k,-k, 1.0f),
        glm::vec4(-k, k, k, 1.0f),
        glm::vec4(-k,-k, k, 1.0f),
        glm::vec4(-k,-k,-k, 1.0f)
    };
    this->faces[3] = Face(vertices_3);

    // face de cima
    glm::vec4 vertices_4[4] = {
        glm::vec4(-k, k,-k, 1.0f),
        glm::vec4( k, k,-k, 1.0f),
        glm::vec4( k, k, k, 1.0f),
        glm::vec4(-k, k, k, 1.0f)
    };
    this->faces[4] = Face(vertices_4);

    // face de trás
    glm::vec4 vertices_5[4] = {
        glm::vec4(-k,-k,-k, 1.0f),
        glm::vec4( k,-k,-k, 1.0f),
        glm::vec4( k, k,-k, 1.0f),
        glm::vec4(-k, k,-k, 1.0f)
    };
    this->faces[5] = Face(vertices_5);
}

Cube::Cube()
{

}

Cube::Cube(float edge_length)
{
    this->setFaces();

    glm::mat3 S = glm::scale(I, glm::vec3(edge_length, edge_length, edge_length));

    for(int i=0; i<6; i++)
    {
        this->faces[i].transform(S);
    }

    this->l = edge_length;
}

glm::vec4 Cube::getCenter()
{
    return this->center;
}

void Cube::printFaces()
{
    for(int i=0; i<6; i++)
    {
        std::cout << "Face n_" << i << std::endl;
        this->faces[i].printVertices();
    }
}

void Cube::rotate(glm::vec3 axis)
{
    glm::mat4 R = glm::rotate(I, (float) glm::radians(90.0), axis);

    for(int i=0; i<6; i++)
    { 
        this->faces[i].transform(R);
    }
    this->center = R * this->center;
}

void Cube::translate(float x, float y, float z)
{
    glm::mat4 T = glm::translate(I, glm::vec3(x,y,z));

    for(int i=0; i<6; i++)
    {
        this->faces[i].transform(T);
    }
    this->center = T * this->center;
}

void Cube::display(bool use_texture=true)
{   
    if(use_texture)
        for(int i=0; i<6; i++)
            this->faces[i].displayTex();
    else
        for(int i=0; i<6; i++)
            this->faces[i].displayColor();
}