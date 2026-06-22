#include "elementos_de_cg.h"
#include "ppm_lib.h"
#include <stdio.h>

#include <math.h>


int main() {

    frame_buffer_rgb_t frame_buffer = init_frame_buffer(1000, 1000);

    camera_t camera = camera_init((camera_init_params) {
        .look_from = (vetor_3D_t) {.x = 0, .y=0, .z =0},
        .look_at = (vetor_3D_t) {.x = 0, .y=0, .z = -1},
        .up = (vetor_3D_t) {.x = 0, .y=1, .z = 0.0},

        .plano_de_proj_w = 1,
        .plano_de_proj_h = 1,
        .distancia_focal = 1
    });


    esfera_t esfera = (esfera_t) {
        .origem = (vetor_3D_t) {.x = -1.0, .y = -1.0, .z = -10.0},
        .raio = 2,
        .material = (material_t) {
            .ka = (RGB_t){.r = 0.1, .g = 0.1, .b = 0.1},
            .kd = (RGB_t){.r = 0.0, .g = 0.9, .b = 0.9},
            .ks = (RGB_t){.r = 1.0, .g = 1.0, .b = 1.0},
            .n = 30
        }
    };


    luz_t luz = (luz_t) {
        .origem = (vetor_3D_t) {.x = 3.0, .y = 3.0, .z = -2.5},
        .cor = (RGB_t) {.r = 1.0, .g = 1.0, .b = 1.0}
    };

    RGB_t luz_ambiente = (RGB_t) {.r = 1.0, .g = 1.0, .b = 1.0};

    printf("origem da camera:\n");
    vetor_3D_print(camera.look_from);

    printf("xyz da base da camera:\n");
    vetor_3D_print(camera.x_base);
    vetor_3D_print(camera.y_base);
    vetor_3D_print(camera.z_base);



    vetor_3D_t look_from_look_at_ = vetor_3D_escala(camera.z_base, -1);
    printf("vetor direção do olho da camera\n");
    vetor_3D_print(look_from_look_at_);

    printf("origem da esfera\n");
    vetor_3D_print(esfera.origem);

    interseccoes_t intersecs = intersec_raio_esfera(camera.look_from, look_from_look_at_, esfera);

    printf("qtd de intersecs: %d", intersecs.qtd);
    renderiza_esfera(camera, esfera, luz, luz_ambiente, frame_buffer);


    export_to_ppm(frame_buffer.BUFFER, frame_buffer.width, frame_buffer.height, "fileeee.ppm");
}
