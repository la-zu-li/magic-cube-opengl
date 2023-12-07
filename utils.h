#ifndef UTILS_H
#define UTILS_H

#include <glm/glm.hpp>
#include "config.h"
#include "cube.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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

// converte coordenadas de janela para coordenadas de mundo
glm::vec2 windowToWorldCoordinates(int x_window, int y_window)
{
    y_window = window_h - y_window;

    float y_norm = float(y_window) / float(window_h);
    float x_norm = float(x_window) / float(window_w);

    float world_height = world_ymax - world_ymin;
    float y_world = world_ymin + y_norm*world_height;
    float world_width = world_xmax - world_xmin;
    float x_world = world_xmin + x_norm*world_width;

    return glm::vec2(x_world, y_world);
}

unsigned loadTexture(const char *filepath)
{
    unsigned tex_id;
    int width, height, n_channels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *image = stbi_load(filepath, &width, &height, &n_channels, 0); //qtd de pixels na largura e altura preenchidas automaticamente
    if(image == NULL) //verifica se o carregamento da imagem ocorreu com sucesso
        std::cout << "Erro, Imagem não carregada" << std::endl;

    glEnable(GL_TEXTURE_2D);              //habilitando o uso de texturas
    glGenTextures(1, &tex_id);            //gerando um objeto textura na máquina OpenGL
    glBindTexture(GL_TEXTURE_2D, tex_id); //ativando o objeto textura recém criado

    //parâmetros da textura caso coordenadas além do intervalo [0,1] seja utilizado
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT); //repetição espelhada no eixo S
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT); //repetição espelhada no eixo T

    //parâmetros da textura para filtragem quando tamanho de pixel e texel sejam diferentes (interpolação linear em ambos os casos)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //magnificação - quando um texel cobre vários pixels
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //minificação - quando muitos texels cabem em um único pixel

    //parâmetros da textura para indicar se a textura deve-se combinar ou substituir a atual cor do objeto
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE); //GL_REPLACE = substitui, GL_COMBINE = combina (ou multiplica)

    //envio dos dados da textura para o OpenGL
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGB,
                 width,            //largura da textura
                 height,           //altura da textura (carregadas automaticamente pela função da biblioteca)
                 0,
                 GL_RGB,           //formato da cor da textura
                 GL_UNSIGNED_BYTE, //tipos de dados de cada texel da textura
                 image);           //ponteiro para os dados da textura

    glBindTexture(GL_TEXTURE_2D, 0); //desativando o objeto textura criado (ativa apenas quando for usar em algum objeto)

    stbi_image_free(image); //memória RAM pode ser liberada pois a imagem foi enviada ao OpenGL (memória gráfica)

    return tex_id; //retornando o identificador da textura (sem ele não há como acessar a textura carregada)
}

void rotateFaceIndices(Cube face1[3][3], Cube face2[3][3])
{
    face2[0][0] = face1[0][2];
    face2[1][0] = face1[0][1];
    face2[2][0] = face1[0][0];
    face2[2][1] = face1[1][0];
    face2[2][2] = face1[2][0];
    face2[1][2] = face1[2][1];
    face2[0][2] = face1[2][2];
    face2[0][1] = face1[1][2];
    face2[1][1] = face1[1][1];
}
#endif // UTILS_H