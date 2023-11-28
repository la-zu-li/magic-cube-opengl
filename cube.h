#ifndef CUBE_H
#define CUBE_H

#include <glm/glm.hpp>
#include "face.h"

/* 
 *  Peça cúbica do cubo mágico.
*/

class Cube
{
private:
    glm::vec4 center; // centroide do cubo
    float l; // tamanho do lado do cubo

public:
    Face faces[6]; // uma textura para cada face
    
    Cube();
    Cube(float edge_length);
    
    glm::vec4 getCenter();
    void setFaces();
    void printFaces();
    
    void rotate(glm::vec3 axis); // rotaciona o cubo 90 graus em sentido antihorário
    void translate(float x, float y, float z);

    void display();
};

#endif // CUBE_H