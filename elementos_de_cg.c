#include "./elementos_de_cg.h"
#include <math.h>
#include <stdio.h>

// retorna p1 + p2
vetor_3D_t vetor_3D_soma(vetor_3D_t v1, vetor_3D_t v2){
    return (vetor_3D_t) {
        .x = v1.x + v2.x,
        .y = v1.y + v2.y,
        .z = v1.z + v2.z,
    };
}


vetor_3D_t vetor_3D_menos(vetor_3D_t v) {
    return (vetor_3D_t) {
        .x = -v.x,
        .y = -v.y,
        .z = -v.z
    };
}


vetor_3D_t vetor_3D_subtrai(vetor_3D_t v1, vetor_3D_t v2) {
    return vetor_3D_soma(v1, vetor_3D_menos(v2));
}


vetor_3D_t vetor_3D_escala(vetor_3D_t v, float k) {
    return (vetor_3D_t) {
        .x = v.x * k,
        .y = v.y * k,
        .z = v.z * k
    };
}


float vetor_3D_produto_escalar(vetor_3D_t v1, vetor_3D_t v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}


vetor_3D_t vetor_3D_produto_vetorial(vetor_3D_t v1, vetor_3D_t v2) {
    return (vetor_3D_t) {
        .x = v1.y * v2.z - v1.z * v2.y,
        .y = v1.z * v2.x - v1.x * v2.z,
        .z = v1.x * v2.y - v1.y * v2.x
    };
}


float vetor_3D_norma(vetor_3D_t v) {
    return sqrt(vetor_3D_produto_escalar(v,v));
}


vetor_3D_t vetor_3D_versor(vetor_3D_t v) {
    return vetor_3D_escala(v, 1.0f / vetor_3D_norma(v));
}

void vetor_3D_print(vetor_3D_t v) {
    printf("type object: <vetor_3D>\n");
    printf("(%f, %f, %f)\n", v.x, v.y, v.z);
}




interseccoes_t intersec_raio_esfera(vetor_3D_t origem_raio, vetor_3D_t direcao_raio, esfera_t esfera) {

    interseccoes_t interseccoes;
    interseccoes.qtd = 0;

    vetor_3D_t direcao_raio_normalizada = vetor_3D_versor(direcao_raio);
    vetor_3D_t origem_esfera = esfera.origem;
    vetor_3D_t vetor_origem_raio_origem_esfera = vetor_3D_subtrai(origem_raio, origem_esfera);

    float A = vetor_3D_produto_escalar(direcao_raio_normalizada, direcao_raio_normalizada);
    float B = 2 * vetor_3D_produto_escalar(vetor_origem_raio_origem_esfera, direcao_raio_normalizada);
    float C = vetor_3D_produto_escalar(vetor_origem_raio_origem_esfera, vetor_origem_raio_origem_esfera) - (esfera.raio * esfera.raio);

    float DELTA = B*B - 4 * A * C;

    if(DELTA < 0)
    {
        return interseccoes;
    }

    if(DELTA > 0){
        float t1, t2;

        t1 = (-B - sqrt(DELTA)) / (2*A);
        t2 = (-B + sqrt(DELTA)) / (2*A);

        if(t1 > t2){
            float temp = t1;
            t1 = t2;
            t2 = temp;
        }

        interseccoes.vetores[0] = vetor_3D_soma(origem_raio, vetor_3D_escala(direcao_raio_normalizada, t1));
        interseccoes.vetores[1] = vetor_3D_soma(origem_raio, vetor_3D_escala(direcao_raio_normalizada, t2));
        interseccoes.qtd = 2;

        return interseccoes;
    }
    
    interseccoes.vetores[0] = vetor_3D_soma(origem_raio, vetor_3D_escala(direcao_raio_normalizada, -B/(2*A)));
    interseccoes.qtd = 1;
    return interseccoes;
}
