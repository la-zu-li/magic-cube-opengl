#ifndef FACE_H
#define FACE_H

#include <glm/glm.hpp>

/* 
 *  Face quadrada de uma peça do cubo mágico.
 *  a ordem dos vértices se encontra definida da seguinte forma:
 *  
 *  0---1
 *  |   |
 *  3---2
 *  
*/
class Face
{
private:
    glm::vec4 vr[4]; // vértices da face
    glm::vec2 tx[4]; // coordenadas de textura para aquela face
    float l;
    bool is_tex; // Se verdadeiro, a face tem textura.
    unsigned tex; // Qual textura aquela face deve exibir
public:
    
    Face(glm::vec4 points[4]);

    void setTex(glm::vec2 tx_coords[4], unsigned tex);
    glm::vec4 *getVertices();
    void printVertices();
    void transform(glm::mat4 transform_matrix);
    void displayTex();
};

#endif // FACE_H