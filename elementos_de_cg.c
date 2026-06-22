#include "./elementos_de_cg.h"
#include <math.h>
#include <stdio.h>
#include<stdlib.h>

#define MY_PI 3.1415926535

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
    printf("<vetor_3D>: ");
    printf("(%.2f, %.2f, %.2f)\n", v.x, v.y, v.z);
}




interseccoes_t intersec_raio_esfera(vetor_3D_t origem_raio, vetor_3D_t direcao_raio, esfera_t esfera) {

    interseccoes_t interseccoes;
    interseccoes.qtd = 0;

    vetor_3D_t direcao_raio_normalizada = vetor_3D_versor(direcao_raio);
    vetor_3D_t origem_esfera = esfera.origem;
    vetor_3D_t vetor_origem_esfera_origem_raio = vetor_3D_subtrai(origem_raio, origem_esfera);

    float A = vetor_3D_produto_escalar(direcao_raio_normalizada, direcao_raio_normalizada);
    float B = 2 * vetor_3D_produto_escalar(vetor_origem_esfera_origem_raio, direcao_raio_normalizada);
    float C = vetor_3D_produto_escalar(vetor_origem_esfera_origem_raio, vetor_origem_esfera_origem_raio) - (esfera.raio * esfera.raio);

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

        if(t1 < 0 && t2 < 0) {
            return interseccoes;
        }

        if(t1 < 0 && t2 > 0) {
            interseccoes.qtd = 1;
            interseccoes.vetores[0] = vetor_3D_soma(origem_raio, vetor_3D_escala(direcao_raio_normalizada, t2));
            return interseccoes;
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



static float graus_to_radiano(float graus){
    return ( MY_PI / 180 ) * graus;
}


camera_t camera_init(camera_init_params params) {
    camera_t aux;
    aux.look_from = params.look_from;
    aux.look_at = params.look_at;
    aux.up = params.up;
    
    aux.plano_de_proj_h = params.plano_de_proj_h;
    aux.plano_de_proj_w =  params.plano_de_proj_w;
    aux.distancia_focal = params.distancia_focal;


    vetor_3D_t look_from_look_at = vetor_3D_subtrai(params.look_at, params.look_from);

    vetor_3D_t z_base = vetor_3D_escala(vetor_3D_versor(look_from_look_at), -1.0);
    vetor_3D_t x_base = vetor_3D_produto_vetorial(params.up, z_base);
    vetor_3D_t y_base = vetor_3D_produto_vetorial(z_base, x_base);

    aux.x_base = vetor_3D_versor(x_base);
    aux.y_base = vetor_3D_versor(y_base);
    aux.z_base = vetor_3D_versor(z_base);

    return aux;
}


frame_buffer_rgb_t init_frame_buffer(int width, int height) {
    RGB_t *BUFFER = malloc(width*height*sizeof(RGB_t));

    return (frame_buffer_rgb_t) {
        .BUFFER = BUFFER,
        .width = width,
        .height = height
    };
}

void renderiza_esfera(camera_t camera, esfera_t esfera, luz_t luz, RGB_t luz_ambiente,  frame_buffer_rgb_t buffer) {
    int _PX_W = buffer.width;
    int _PX_H = buffer.height;

    float plano_w = camera.plano_de_proj_w;
    float plano_h = camera.plano_de_proj_h;

    float dx = plano_w / (float)_PX_W;
    float dy = plano_h / (float)_PX_H;


    vetor_3D_t look_d = vetor_3D_escala(camera.z_base, camera.distancia_focal);
    look_d = vetor_3D_escala(look_d, -1);


    for(int i = 0; i < _PX_W; i++) {
        for(int j = 0; j < _PX_H; j++) {
            
            // Calculando a posição relativa ao centro do plano de projeção
            // Adicionamos 0.5 para pegar o centro do pixel
            float x_offset = (j + 0.5f) * dx - (plano_w / 2.0f);
            float y_offset = (plano_h / 2.0f) - (i + 0.5f) * dy; // Sinal invertido dependendo do seu sistema de coordenadas

            // Vetores deslocamento no plano da câmera
            vetor_3D_t dif_centro_x = vetor_3D_escala(camera.x_base, x_offset);
            vetor_3D_t dif_centro_y = vetor_3D_escala(camera.y_base, y_offset);
            
            // Raio final: (Distância Focal no eixo Z) + (Deslocamento no plano XY)
            vetor_3D_t raio_direcao = vetor_3D_soma(look_d, vetor_3D_soma(dif_centro_x, dif_centro_y));
            
            raio_direcao = vetor_3D_versor(raio_direcao);

            interseccoes_t intersecs = intersec_raio_esfera(camera.look_from, raio_direcao, esfera);

            if( intersecs.qtd > 0) {

                vetor_3D_t ponto_intersec = intersecs.vetores[0];
                vetor_3D_t origem_observador = camera.look_from; // poderia pegar dinamicamente


                // --- 1. GEOMETRIA (Cálculo dos Vetores Unitários) ---
                vetor_3D_t O = vetor_3D_subtrai(origem_observador, ponto_intersec);
                O = vetor_3D_versor(O);

                vetor_3D_t N = vetor_3D_subtrai(ponto_intersec, esfera.origem);
                N = vetor_3D_versor(N);

                vetor_3D_t L = vetor_3D_subtrai(luz.origem, ponto_intersec);
                L = vetor_3D_versor(L);


                // --- 2. CÁLCULO DO VETOR DE REFLEXÃO R ---
                float dot_NL = vetor_3D_produto_escalar(N, L);
                if (dot_NL < 0.0) dot_NL = 0.0;
                vetor_3D_t N_escalado = vetor_3D_escala(N, 2.0 * dot_NL);
                vetor_3D_t R = vetor_3D_subtrai(N_escalado, L);
                R = vetor_3D_versor(R);

                //Agora temos O N L R


                // --- 3. CÁLCULO DO FATOR ESPECULAR (De onde ele vem!) ---
                float dot_RO = vetor_3D_produto_escalar(R, O);
                if (dot_RO < 0.0) dot_RO = 0.0;
                float fator_especular = pow(dot_RO, esfera.material.n);


                RGB_t cor_final;

                float termo_difuso_r = esfera.material.kd.r * dot_NL;
                float termo_especular_r = esfera.material.ks.r * fator_especular;
                cor_final.r = (luz_ambiente.r * esfera.material.ka.r) + luz.cor.r * (termo_difuso_r + termo_especular_r);

                float termo_difuso_g = esfera.material.kd.g * dot_NL;
                float termo_especular_g = esfera.material.ks.g * fator_especular;
                cor_final.g = (luz_ambiente.g * esfera.material.ka.g) + luz.cor.g * (termo_difuso_g + termo_especular_g);



                float termo_difuso_b = esfera.material.kd.b * dot_NL;
                float termo_especular_b = esfera.material.ks.b * fator_especular;
                cor_final.b = (luz_ambiente.b * esfera.material.ka.b) + luz.cor.b * (termo_difuso_b + termo_especular_b);

                if(cor_final.r > 1.0) cor_final.r = 1.0;
                if(cor_final.g > 1.0) cor_final.g = 1.0;
                if(cor_final.b > 1.0) cor_final.b = 1.0;


                buffer.BUFFER[i*buffer.width + j] = cor_final;
            }
        }
    }

}