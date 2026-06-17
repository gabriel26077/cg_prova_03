#include "./elementos_de_cg.h"
#include <stdio.h>
#include <math.h>

void print_teste(const char* descricao, vetor_3D_t origem, vetor_3D_t direcao, esfera_t esfera) {
    printf("==================================================\n");
    printf("TESTE: %s\n", descricao);
    printf("Esfera: Centro = (%.2f, %.2f, %.2f), Raio = %.2f\n", 
           esfera.origem.x, esfera.origem.y, esfera.origem.z, esfera.raio);
    printf("Raio:   Origem = (%.2f, %.2f, %.2f), Direcao = (%.2f, %.2f, %.2f)\n", 
           origem.x, origem.y, origem.z, direcao.x, direcao.y, direcao.z);
    
    interseccoes_t inters = intersec_raio_esfera(origem, direcao, esfera);
    
    printf("Resultados: Qtd Intersecoes = %d\n", inters.qtd);
    for (int i = 0; i < inters.qtd; i++) {
        printf("  Ponto %d: (%.4f, %.4f, %.4f)\n", 
               i + 1, inters.vetores[i].x, inters.vetores[i].y, inters.vetores[i].z);
    }
    printf("==================================================\n\n");
}

int main() {
    printf("Executando testes para intersec_raio_esfera...\n\n");

    // Esfera comum para os testes na origem (0,0,0) com raio 2.0
    esfera_t esfera = {
        .origem = { .x = 0.0f, .y = 0.0f, .z = 0.0f },
        .raio = 2.0f,
        .cor = { .r = 1.0f, .g = 0.0f, .b = 0.0f }
    };

    // Caso 1: O raio aponta direto para o centro da esfera, cruzando-a (espera-se 2 interseções)
    vetor_3D_t origem_1 = { .x = 0.0f, .y = 0.0f, .z = 5.0f };
    vetor_3D_t direcao_1 = { .x = 0.0f, .y = 0.0f, .z = -1.0f };
    print_teste("Raio atravessando a esfera pelo centro (2 intersecoes esperadas)", 
                origem_1, direcao_1, esfera);

    // Caso 2: O raio passa raspando (tangente) na borda da esfera (espera-se 1 interseção)
    vetor_3D_t origem_2 = { .x = 2.0f, .y = 0.0f, .z = 5.0f };
    vetor_3D_t direcao_2 = { .x = 0.0f, .y = 0.0f, .z = -1.0f };
    print_teste("Raio tangente a esfera (1 intersecao esperada)", 
                origem_2, direcao_2, esfera);

    // Caso 3: O raio erra completamente a esfera (espera-se 0 interseções)
    vetor_3D_t origem_3 = { .x = 3.0f, .y = 0.0f, .z = 5.0f };
    vetor_3D_t direcao_3 = { .x = 0.0f, .y = 0.0f, .z = -1.0f };
    print_teste("Raio que erra a esfera completamente (0 intersecoes esperadas)", 
                origem_3, direcao_3, esfera);

    // Caso 4: Esfera deslocada para (10, 10, 10), raio de 5.0, e raio passando pelo centro
    esfera_t esfera_deslocada = {
        .origem = { .x = 10.0f, .y = 10.0f, .z = 10.0f },
        .raio = 5.0f,
        .cor = { .r = 0.0f, .g = 1.0f, .b = 0.0f }
    };
    vetor_3D_t origem_4 = { .x = 10.0f, .y = 10.0f, .z = 0.0f };
    vetor_3D_t direcao_4 = { .x = 0.0f, .y = 0.0f, .z = 1.0f };
    print_teste("Esfera deslocada em (10,10,10) - Raio pelo centro (2 intersecoes esperadas)", 
                origem_4, direcao_4, esfera_deslocada);

    return 0;
}
