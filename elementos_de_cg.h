#ifndef ALGELIN_H
#define ALGELIN_H

#define BUFFER_INTERSECCOES_SIZE 12

typedef struct vetor_3D_t {
    float x;
    float y;
    float z;
} vetor_3D_t;

typedef struct cor_t {
    float r;
    float g;
    float b;
} cor_t;

typedef struct esfera_t {
    vetor_3D_t origem;
    float raio;
    cor_t cor;
} esfera_t;


typedef struct interseccoes_t {
    int qtd;
    vetor_3D_t vetores[BUFFER_INTERSECCOES_SIZE];
} interseccoes_t;



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



#endif


