#ifndef CONFIG_H
#define CONFIG_H

#include <cstring>

/*
 * Este arquivo contém algumas variáveis globais de configuração do puzzle
*/

// altura e largura da janela
int window_h = 500;
int window_w = 1000;

float aspect_ratio = float(window_w) / float(window_h);
                
// limites das coordenadas de mundo projetadas
float world_xmin = -40.0f; 
float world_xmax =  40.0f; 
float world_ymin = -20.0f; 
float world_ymax =  20.0f; 
float world_zmin = -40.0f; 
float world_zmax =  40.0f;

float world_w = world_xmax-world_xmin;
float world_h = world_ymax-world_ymin;

// configurações do cubo mágico
float magic_cube_edge = 30.0f; // tamanho da aresta do cubo mágico
float piece_edge_length = magic_cube_edge / 3.0; // lado da peça quadrada
unsigned n_iterations_shuffle = 100;

// configurações da câmera
glm::vec4 cam_pos = glm::vec4(30, 30, 100, 1); // posição da câmera
float cam_speed = 1.0f; // velocidade de scroll

// configurações de iluminação

//  - luz 0
glm::vec4 l0_pos  = glm::vec4(0, 0, 80, 1);  // posição da fonte de luz R,G,B
glm::vec3 l0_amb  = glm::vec3(0.05, 0.05, 0.05);  // componente ambiente da luz R,G,B
glm::vec3 l0_dif  = glm::vec3(0.01, 0.01, 0.01);  // componente difusa da luz R,G,B
glm::vec3 l0_spec = glm::vec3(0.01, 0.01, 0.01); // componente especular da luz R,G,B

//  - luz 1
glm::vec4 l1_pos  = glm::vec4(0, 30, 0, 1);  // posição da fonte de luz R,G,B
glm::vec3 l1_amb  = glm::vec3(0.0, 0.0, 0.0);  // componente ambiente da luz R,G,B
glm::vec3 l1_dif  = glm::vec3(1.0, 1.0, 1.0);  // componente difusa da luz R,G,B
glm::vec3 l1_spec = glm::vec3(0.0, 0.0, 0.0); // componente especular da luz R,G,B

//  - material
glm::vec3 mat_amb   = glm::vec3(0.5, 0.5, 0.5);
glm::vec3 mat_dif   = glm::vec3(0.5, 0.5, 0.5);
glm::vec3 mat_spec  = glm::vec3(0.3, 0.3, 0.3);
glm::vec3 mat_shine = glm::vec3(65);

// variável que indica em quantos pequenos quadradinhos será dividido cada face do cubo.
// o objetivo é obter um resultado mais interessante para a iluminação
unsigned fragments = 10;

// define o caminho das texturas que serão utilizadas nas faces

const char *cube_texts_filepaths[6] = {
    "textures/texture1/face1.jpg",
    "textures/texture1/face2.jpg",
    "textures/texture1/face3.jpg",
    "textures/texture1/face4.jpg",
    "textures/texture1/face5.jpg",
    "textures/texture1/face6.jpg"
};
const char *background_text1 = "textures/background1.jpg";

#endif // CONFIG_H