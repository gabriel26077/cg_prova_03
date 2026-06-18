#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define LARGURA 800
#define ALTURA 800

int main() {
    // Abre o arquivo para escrita no modo de texto (.ppm)
    FILE *arquivo = fopen("imagem_interessante.ppm", "w");
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo!\n");
        return 1;
    }

    // Escreve o cabeçalho do formato PPM
    // P3: Formato de texto colorido
    // 800 800: Dimensões da imagem
    // 255: Valor máximo para cada canal de cor (RGB)
    fprintf(arquivo, "P3\n");
    fprintf(arquivo, "%d %d\n", LARGURA, ALTURA);
    fprintf(arquivo, "255\n");

    // Loop para gerar cada pixel da imagem
    for (int y = 0; y < ALTURA; y++) {
        for (int x = 0; x < LARGURA; x++) {
            
            // Normaliza as coordenadas x e y para o intervalo de -1.0 a 1.0
            double nx = (double)x / LARGURA * 2.0 - 1.0;
            double ny = (double)y / ALTURA * 2.0 - 1.0;

            // Calcula a distância do pixel atual até o centro da imagem (0,0)
            double raio = sqrt(nx * nx + ny * ny);

            // Equações matemáticas para gerar padrões complexos de ondas e interferências
            double valor1 = sin(nx * 5.0 + sin(ny * 3.0));
            double valor2 = cos(ny * 5.0 + cos(nx * 3.0));
            double valor3 = sin(raio * 12.0 - 2.0);

            // Combina os valores e mapeia para o intervalo de 0.0 a 1.0
            double padrao = (valor1 + valor2 + valor3) / 3.0;
            padrao = (padrao + 1.0) / 2.0; // Ajusta de [-1, 1] para [0, 1]

            // Define os canais de cor (RGB) baseando-se no padrão calculado
            // Multiplicamos por frequências diferentes para criar variações psicodélicas
            int r = (int)((sin(padrao * M_PI * 2.0) * 0.5 + 0.5) * 255);
            int g = (int)((sin(padrao * M_PI * 4.0 + M_PI/3.0) * 0.5 + 0.5) * 255);
            int b = (int)((cos(padrao * M_PI * 3.0 + M_PI/1.5) * 0.5 + 0.5) * 255);

            // Garante que os valores fiquem estritamente entre 0 e 255
            if (r < 0) r = 0; if (r > 255) r = 255;
            if (g < 0) g = 0; if (g > 255) g = 255;
            if (b < 0) b = 0; if (b > 255) b = 255;

            // Grava os valores RGB textuais separados por espaço no arquivo
            fprintf(arquivo, "%d %d %d ", r, g, b);
        }
        // Quebra de linha ao final de cada fileira de pixels (opcional, melhora a leitura do texto)
        fprintf(arquivo, "\n");
    }

    // Fecha o arquivo
    fclose(arquivo);
    printf("Imagem 'imagem_interessante.ppm' gerada com sucesso!\n");

    return 0;
}