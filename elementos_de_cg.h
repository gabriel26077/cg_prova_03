#ifndef ALGELIN_H
#define ALGELIN_H

#include "shared.h"

#define BUFFER_INTERSECCOES_SIZE 12

typedef struct vetor_3D_t {
    float x;
    float y;
    float z;
} vetor_3D_t;


typedef struct material_t {
    RGB_t ka;  // Coeficiente/cor ambiente (como o objeto reflete a luz de fundo)
    RGB_t kd;  // Coeficiente/cor difusa (a cor "base" ou "cor de giz" do objeto)
    RGB_t ks;  // Coeficiente/cor especular (o brilho, geralmente branco [1,1,1] ou cinza)
    float n;   // Expoente especular (shininess / polimento)
} material_t;


typedef struct esfera_t {
    vetor_3D_t origem;
    float raio;
    material_t material;
} esfera_t;


typedef struct interseccoes_t {
    int qtd;
    vetor_3D_t vetores[BUFFER_INTERSECCOES_SIZE];
} interseccoes_t;


typedef struct camera_t {

    //dados definidos pelo usuário
    vetor_3D_t look_from;
    vetor_3D_t look_at;
    vetor_3D_t up;
    float plano_de_proj_w;
    float plano_de_proj_h;
    
    float distancia_focal;

    //

    // vetores de base calulados
    // posteriormente
    vetor_3D_t x_base;
    vetor_3D_t y_base;
    vetor_3D_t z_base;
} camera_t;

typedef struct camera_init_params {
    vetor_3D_t look_from;
    vetor_3D_t look_at;
    vetor_3D_t up;
    float plano_de_proj_w;
    float plano_de_proj_h;
    float distancia_focal;
}camera_init_params;

camera_t camera_init(camera_init_params params);


typedef struct luz_t {
    vetor_3D_t origem;
    RGB_t  cor;
} luz_t;



typedef struct frame_buffer_rgb_t {
    RGB_t* BUFFER;
    int width;
    int height;
} frame_buffer_rgb_t;

frame_buffer_rgb_t init_frame_buffer(int width, int height);

// retorna v1 + v2
vetor_3D_t vetor_3D_soma(vetor_3D_t v1, vetor_3D_t v2);

// retorna -v
vetor_3D_t vetor_3D_menos(vetor_3D_t v);

// retorna v1 - v2
vetor_3D_t vetor_3D_subtrai(vetor_3D_t v1, vetor_3D_t v2);

// retorna um vetor escalado por um fator k
vetor_3D_t vetor_3D_escala(vetor_3D_t v, float k);

// retorna o produto escalar v1 e v2
float vetor_3D_produto_escalar(vetor_3D_t v1, vetor_3D_t v2);

// produto vetorial v1 x v2
vetor_3D_t vetor_3D_produto_vetorial(vetor_3D_t v1, vetor_3D_t v2);

// retorna a nroma do vetor v
float vetor_3D_norma(vetor_3D_t v);

// retorna o vetor v normalizado
vetor_3D_t vetor_3D_versor(vetor_3D_t v);

void vetor_3D_print(vetor_3D_t v);


//////////////////////////// raio esfera

interseccoes_t intersec_raio_esfera(vetor_3D_t origem_raio, vetor_3D_t direcao, esfera_t esfera);

void renderiza_esfera(camera_t camera, esfera_t esfera, luz_t luz,  RGB_t luz_ambiente, frame_buffer_rgb_t buffer);


#endif


