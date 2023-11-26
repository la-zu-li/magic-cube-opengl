#ifndef CONFIG_H
#define CONFIG_H

/*
 * Este arquivo contém algumas variáveis globais de configuração do puzzle
*/

// altura e largura da janela
int window_h = 500;
int window_w = 1000;

// limites das coordenadas de mundo projetadas
float world_xmin = -40.0f; 
float world_xmax =  40.0f; 
float world_ymin = -20.0f; 
float world_ymax =  20.0f;

float world_w = world_xmax-world_xmin;
float world_h = world_ymax-world_ymin;

// configurações do cubo mágico
float magic_cube_edge = 30.0f; // tamanho da aresta do cubo mágico
float piece_edge_length = magic_cube_edge / 3.0; // lado da peça quadrada

// define o caminho das texturas que serão utilizadas nas faces
char *texts_filepath[6] = {
    "textures/gemstone.jpg",
    "textures/lava.jpg",
    "textures/leaves.jpg",
    "textures/roses.jpg",
    "textures/water.jpg",
    "textures/sky.jpg"
};

#endif // CONFIG_H