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

#include <locale.h>

#include "cube.h"
#include "cube.cpp"
#include "config.h"

unsigned textures[6];

Cube cube[3][3][3];
clock_t timer;

int umavez = 1;

// corta as texturas propriamente para colocar em cada face
void loadTexturesOnFaces(Cube cube[3][3][3], unsigned tx[6])
{
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            glm::vec2 tx_coords[4] = {
                glm::vec2((float)(i  )/3, (float)(j+1)/3),
                glm::vec2((float)(i+1)/3, (float)(j+1)/3),
                glm::vec2((float)(i+1)/3, (float)(j  )/3),
                glm::vec2((float)(i  )/3, (float)(j  )/3)
            };

            cube[i][ j ][ 2 ].faces[0].setTex(tx_coords, tx[0]); // face 0 - gemstone
            cube[i][ 0 ][ j ].faces[1].setTex(tx_coords, tx[1]); // face 1 - lava
            cube[2][ j ][2-i].faces[2].setTex(tx_coords, tx[2]); // face 2 - leaves
            cube[0][ j ][ i ].faces[3].setTex(tx_coords, tx[3]); // face 3 - roses
            cube[i][ 2 ][2-j].faces[4].setTex(tx_coords, tx[4]); // face 4 - water
            cube[i][2-j][ 0 ].faces[5].setTex(tx_coords, tx[5]); // face 5 - sky
        }
    }
}

// coloca uma cor em cada face do cubo mágico
void loadColorsOnFaces(Cube cube[3][3][3], glm::vec3 colors[6])
{
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            cube[i][ j ][ 2 ].faces[0].setColor(colors[0]); // face 0 vermelho 
            cube[i][ 0 ][ j ].faces[1].setColor(colors[1]); // face 1 amarelo
            cube[2][ j ][2-i].faces[2].setColor(colors[2]); // face 2 verde
            cube[0][ j ][ i ].faces[3].setColor(colors[3]); // face 3 ciano
            cube[i][ 2 ][2-j].faces[4].setColor(colors[4]); // face 4 azul
            cube[i][2-j][ 0 ].faces[5].setColor(colors[5]); // face 5 magenta
        }
    }
}

void rotateCamera(unsigned int key, glm::vec4 *cam_pos)
{
    switch (key)
    {
    case 'z':
        *cam_pos = R_CAM_X * (*cam_pos);
        break;
    case 'x':
        *cam_pos = R_CAM_Y * (*cam_pos);
        break;
    case 'c':
        *cam_pos = R_CAM_Z * (*cam_pos);
        break;
    default:
        break;
    }
}

void rotateLightSource(unsigned int key, glm::vec4 *light_pos)
{
    switch (key)
    {
    case 'j':
        *light_pos = R_CAM_X * (*light_pos);
        break;
    case 'k':
        *light_pos = R_CAM_Y * (*light_pos);
        break;
    case 'l':
        *light_pos = R_CAM_Z * (*light_pos);
        break;
    default:
        break;
    }
}
 
void rotateMagicCube(unsigned int key, Cube cube[3][3][3])
{
    Cube aux_face1 [3][3];
    Cube aux_face2 [3][3];
    switch (key)
    {
    case '1': // face 0
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                cube[i][j][2].rotate(glm::vec3( 0, 0, 1));
                aux_face1[i][j] = cube[i][j][2];
            }
        }
        rotateFaceIndices(aux_face1, aux_face2);
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                cube[i][j][2] = aux_face2[i][j];
            }
        }
        break;
    case '2': // face 1
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                cube[i][0][j].rotate(glm::vec3( 0,-1, 0));
                aux_face1[i][j] = cube[i][0][j];
            }
        }
        rotateFaceIndices(aux_face1, aux_face2);
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                cube[i][0][j] = aux_face2[i][j];
            }
        }
        break;
    case '3': // face 2
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                cube[2][j][2-i].rotate(glm::vec3( 1, 0, 0));
                aux_face1[i][j] = cube[2][j][2-i];
            }
        }
        rotateFaceIndices(aux_face1, aux_face2);
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                cube[2][j][2-i] = aux_face2[i][j];
            }
        }
        break;
    case '4': // face 3
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                cube[0][j][i].rotate(glm::vec3(-1, 0, 0));
                aux_face1[i][j] = cube[0][j][i];
            }
        }
        rotateFaceIndices(aux_face1, aux_face2);
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                cube[0][j][i] = aux_face2[i][j];
            }
        }
        break;
    case '5': // face 4
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                cube[i][2][2-j].rotate(glm::vec3( 0, 1, 0));
                aux_face1[i][j] = cube[i][2][2-j];
            }
        }
        rotateFaceIndices(aux_face1, aux_face2);
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                cube[i][2][2-j] = aux_face2[i][j];
            }
        }
        break;
    case '6': // face 5
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                cube[i][2-j][0].rotate(glm::vec3( 0, 0,-1));
                aux_face1[i][j] = cube[i][2-j][0];
            }
        }
        rotateFaceIndices(aux_face1, aux_face2);
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                cube[i][2-j][0] = aux_face2[i][j];
            }
        }
        break;
    default:
        break;
    }
    
}

// realiza movimentos aleatórios com o cubo
void shuffle_cube(Cube cube[3][3][3], unsigned n_iterations)
{
    const char *keys = "123456";
    for (int i=0; i<n_iterations; i++)
    {
    	int r = rand() % 6;
    	rotateMagicCube(keys[r],cube);
	}
}

// Função que cria todas as peças
void gameStart()
{
    glm::vec3 colors[6] = {
        glm::vec3(1.0, 0.0, 0.0), // vermelho - 0
        glm::vec3(1.0, 1.0, 0.0), // amarelo  - 1
        glm::vec3(0.0, 1.0, 0.0), // verde    - 2
        glm::vec3(0.0, 1.0, 1.0), // ciano    - 3
        glm::vec3(0.0, 0.0, 1.0), // azul     - 4
        glm::vec3(1.0, 0.0, 1.0)  // magenta  - 5
    };

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
        textures[i] = loadTexture(cube_texts_filepaths[i]);
    }
    loadTexturesOnFaces(cube, textures);
    loadColorsOnFaces(cube, colors);
    if(umavez == 1)
    {
        shuffle_cube(cube, n_iterations_shuffle);
    	umavez = 0;
	}
}

void openglStart()
{
    glEnable(GL_DEPTH_TEST); 
    glEnable(GL_TEXTURE_2D);
    glLineWidth(2.0);
    //glEnable(GL_MULTISAMPLE); // habilita um tipo de antialiasing (melhora serrilhado)
}

void lightingStart()
{
    glEnable(GL_LIGHTING); // habilita iluminação

    glEnable(GL_LIGHT0); // habilita duas das oito fontes de luz disponíveis
    glEnable(GL_LIGHT1);

    // propriedades da fonte de luz 0
    glLightfv(GL_LIGHT0, GL_POSITION, glm::value_ptr(l0_pos));
    glLightfv(GL_LIGHT0, GL_AMBIENT , glm::value_ptr(l0_amb));
    glLightfv(GL_LIGHT0, GL_DIFFUSE , glm::value_ptr(l0_dif));
    glLightfv(GL_LIGHT0, GL_SPECULAR, glm::value_ptr(l0_spec));

    //propriedades da fonte de luz 1
    // glLightfv(GL_LIGHT1, GL_POSITION, glm::value_ptr(l1_pos));
    // glLightfv(GL_LIGHT1, GL_AMBIENT , glm::value_ptr(l1_amb));
    // glLightfv(GL_LIGHT1, GL_DIFFUSE , glm::value_ptr(l1_dif));
    // glLightfv(GL_LIGHT1, GL_SPECULAR, glm::value_ptr(l1_spec));
    
    //propriedades do material do objeto
    glMaterialfv(GL_FRONT, GL_AMBIENT  , glm::value_ptr(mat_amb));
    glMaterialfv(GL_FRONT, GL_DIFFUSE  , glm::value_ptr(mat_dif));
    glMaterialfv(GL_FRONT, GL_SPECULAR , glm::value_ptr(mat_spec));
    glMaterialfv(GL_FRONT, GL_SHININESS, glm::value_ptr(mat_shine));
}

void windowResize(int width, int height){
    window_w = width;
    window_h = height;

    glViewport(0, 0, width, height);
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{   
    rotateCamera(key, &cam_pos);
    rotateLightSource(key, &l0_pos);
    glLightfv(GL_LIGHT0, GL_POSITION, glm::value_ptr(l0_pos));
    rotateMagicCube(key, cube);

    glutPostRedisplay();
}

// Função que desenha no frame buffer
void display()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //sempre antes de desenhar qualquer coisa, deve-se limpar o Frame Buffer 
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glm::mat4 proj_matrix = glm::perspective(45.0f, aspect_ratio, 0.1f, 500.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(proj_matrix));
    glm::mat4 cam_matrix = glm::lookAt(glm::vec3(cam_pos), glm::vec3(0), glm::vec3(0,1,0));
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(glm::value_ptr(cam_matrix));

    timer = clock();
    // display_axis();
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
    timer = clock()/2;
    system(CLEAR);
	printf("Tempo percorrido: %f segundos",((float)timer)/CLOCKS_PER_SEC);

    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc,argv);                         // inicializar a biblioteca GLUT
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);  // configuraçoes do frame buffer (um frame buffer com três canais de cor: RGB)
    glutInitWindowPosition(200,200);              // posição do canto superior esquerdo da janela com relação a tela
    glutInitWindowSize(window_w,window_h);        // resolução da janela (framebuffer)
    glutCreateWindow("Magic Cube");               // cria a janela (a string aparece na barra de titulo da janela)
	clock_t timer;
	timer = clock();	
	
    lightingStart();
    openglStart();
    //shuffle_cube(cube,1000);
    gameStart();
    
    glutReshapeFunc(windowResize); // tratamento do redimensionamento da janela
    glutKeyboardFunc(keyboard);
    // glutMouseFunc(mouseClick);     // tratamento do mouse
    // glutMotionFunc(mouseDrag);
    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}