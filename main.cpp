/*
 * Trabalho de Computação Gráfica 2
 * Trabalho desenvolvido para a disciplina de Computação Gráfica,
 * do curso de Ciência da Computação, na Universidade Federal do Ceará, Campus Russas.
 * 
 * O trabalho se trata de um cubo mágico 3D jogável,
 * desenvolvido em C++ com o auxílio das bibliotecas openGL, glut e GLM.
 *
 * Equipe:
 *
 *  - Clayver Rodrigues de Morais, matrícula 494097
 *  - Isaac Emanuel Costa de Andrade, matrícula 493661
*/

#include <GL/glut.h>
#include <glm/glm.hpp>

#include <cstdlib>
#include <ctime>

#include <vector>
#include <random>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "cube.h"
#include "cube.cpp"
#include "config.h"

// TODO: resolver problema da ordem de exibição das faces
unsigned textures[6];

Cube cube[3][3][3];
Cube c;

glm::vec4 cam_pos = glm::vec4(0, 0, 20, 1);

// converte coordenadas de janela pra coordenadas de mundo
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

// realiza movimentos aleatórios com o cubo // UNFINISHED
void shuffle_cube(Cube cube[3][3][3], unsigned n_iterations)
{
    // configura a geração de números aleatórios
    std::random_device rd; // usado para inicializar o gerador de números
    std::mt19937 rng(rd()); // usa a engine de Mersenne-Twister para gerar os números
    std::uniform_int_distribution<int> rand_move(0,5);

    for(int i=0; i<n_iterations; i++)
    {
        int random_face = rand_move(rng);
        // TODO: lógica para mover face aleatória do cubo
    }
}

// corta as texturas propriamente para colocar em cada face
void load_textures_on_faces(Cube cube[3][3][3], unsigned tx[6])
{
    for(int i; i<3; i++)
    {
        for(int j; j<3; j++)
        {
            glm::vec2 tx_coords[4] = {
                glm::vec2((float)(i  )/3, (float)(j+1)/3),
                glm::vec2((float)(i+1)/3, (float)(j+1)/3),
                glm::vec2((float)(i+1)/3, (float)(j  )/3),
                glm::vec2((float)(i  )/3, (float)(j  )/3)
            };

            cube[i][ j ][ 2 ].faces[0].setTex(tx_coords, tx[0]); // face 0
            cube[i][ 0 ][ j ].faces[1].setTex(tx_coords, tx[1]); // face 1
            cube[2][ j ][2-i].faces[2].setTex(tx_coords, tx[2]); // face 2
            cube[0][ j ][ i ].faces[3].setTex(tx_coords, tx[3]); // face 3
            cube[i][ 2 ][2-j].faces[4].setTex(tx_coords, tx[4]); // face 4
            cube[i][2-j][ 0 ].faces[5].setTex(tx_coords, tx[5]); // face 5
        }
    }
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
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); //GL_REPLACE = substitui, GL_COMBINE = combina (ou multiplica)

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

// Função que cria todas as peças
void gameStart()
{
    // for(int i=0; i<s; i++)
    // {
    //     for(int j=0; j<s; j++)
    //     {
    //         glm::vec2 fit_pos;
    //         fit_pos.x = board_pos.x+l*i + l/2;
    //         fit_pos.y = board_pos.y+l*j + l/2;

    //         glm::vec2 tx_coords[4];
    //         tx_coords[0] = glm::vec2((float)(i  )/s, (float)(j+1)/s);
    //         tx_coords[1] = glm::vec2((float)(i+1)/s, (float)(j+1)/s);
    //         tx_coords[2] = glm::vec2((float)(i+1)/s, (float)(j  )/s);
    //         tx_coords[3] = glm::vec2((float)(i  )/s, (float)(j  )/s);

    //         pieces.push_back(Piece(l, fit_pos, tx_coords));

    //         int id = sizeof_square_grid*i + j;
    //         priority_order.push_back(id);
    //     }
    // }

    // Inicializa as coordenadas de cada peça do cubo mágico
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            for(int k=0; k<3; k++)
            {
                float l = piece_edge_length;
                cube[i][j][k] = Cube(l);
                
                float x = -l + i*l;
                float y = -l + j*l;
                float z = -l + k*l;
                cube[i][j][k].translate(x,y,z);
            }
        }
    }

    // Carrega todas as texturas
    for(int i=0; i<6; i++)
    {
        textures[i] = loadTexture(texts_filepath[i]);
    }
    load_textures_on_faces(cube, textures);

    c = Cube(piece_edge_length);
    
    glm::vec3 colors[6] = {
        glm::vec3(1.0, 0.0, 0.0), // vermelho - 0
        glm::vec3(1.0, 1.0, 0.0), // amarelo  - 1
        glm::vec3(0.0, 1.0, 0.0), // verde    - 2
        glm::vec3(0.0, 1.0, 1.0), // ciano    - 3
        glm::vec3(0.0, 0.0, 1.0), // azul     - 4
        glm::vec3(1.0, 0.0, 1.0)  // magenta  - 5
    };

    for(int i=0; i<6; i++)
    {
        glm::vec2 coords[4] = {
            glm::vec2(0,1),
            glm::vec2(1,1),
            glm::vec2(1,0),
            glm::vec2(0,0)
        };
        c.faces[i].setTex(coords, textures[i]);
        c.faces[i].setColor(colors[i]);
    }
}

void openglStart()
{
    glClearColor(0.0, 0.0, 0.0, 1.0); //indica qual cor sera usada para limpar o frame buffer (normalmente usa uma cor de background)

    glEnable(GL_DEPTH_TEST);  // habilitando a remoção de faces que estejam atrás de outras (remoção de faces traseiras)
    glDepthFunc(GL_LESS);
    glDepthMask(GL_TRUE);
    // glEnable(GL_MULTISAMPLE); // habilita um tipo de antialiasing (melhora serrilhado)
    glEnable(GL_TEXTURE_2D);
}

void windowResize(int width, int height){
    window_w = width;
    window_h = height;

    glViewport(0, 0, width, height);
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    // Rotação das faces
    case 'z':
        c.rotate(glm::vec3(1,0,0));
        break;
    case 'x':
        c.rotate(glm::vec3(0,1,0));
        break;
    case 'c':
        c.rotate(glm::vec3(0,0,1));
        break;

    // Rotação da câmera
    case 'e':
        cam_pos = R_CAM_X * cam_pos;
        break;
    case 'r':
        cam_pos = R_CAM_Y * cam_pos;
        break;
    case 't':
        cam_pos = R_CAM_Z * cam_pos;
        break;
    default:
        break;
    }

    glutPostRedisplay();
}

// Função que desenha no frame buffer
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //sempre antes de desenhar qualquer coisa, deve-se limpar o Frame Buffer 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(world_xmin, world_xmax, world_ymin, world_ymax, world_zmin, world_zmax);

    glMatrixMode(GL_MODELVIEW);
    glm::mat4 cam_matrix = glm::lookAt(glm::vec3(cam_pos), glm::vec3(0), glm::vec3(0,1,0));
    glLoadMatrixf(glm::value_ptr(cam_matrix));

    display_axis();
    // exibe o cubo mágico
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            for(int k=0; k<3; k++)
            {
                cube[i][j][k].display();
            }
        }
    }

    // c.display();
    glFlush();  // Todas as instruções anteriores apenas indicaram o que deve ser feito. Essa é a ordem pra GPU redesenhar com as informações enviadas
}

int main(int argc, char** argv)
{
    glutInit(&argc,argv);                         // inicializar a biblioteca GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  // configuraçoes do frame buffer (um frame buffer com três canais de cor: RGB)
    glutInitWindowPosition(200,200);              // posição do canto superior esquerdo da janela com relação a tela
    glutInitWindowSize(window_w,window_h);        // resolução da janela (framebuffer)
    glutCreateWindow("Magic Cube");                   // cria a janela (a string aparece na barra de titulo da janela)

    openglStart();
    gameStart();
    // shuffle_cube(1000);

    glutDisplayFunc(display);
    glutReshapeFunc(windowResize); // tratamento do redimensionamento da janela
    glutKeyboardFunc(keyboard);
    // glutMouseFunc(mouseClick);     // tratamento do mouse
    // glutMotionFunc(mouseDrag);

    glutMainLoop();

    return 0;
}