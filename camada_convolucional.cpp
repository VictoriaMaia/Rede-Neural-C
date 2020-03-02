#include "camada_convolucional.h"
#include "iniciarConv.h"

Mat camadaConvolucao(Mat image_in){
    vector <Mat> canais (3);
    vector <Mat> canaisResultado (3);
 
    Mat image_out = image_in;

    // if (image_in.rows != LinhasImg || image_in.cols != ColunasImg){
    //     resize(image_in, image_out, Size(LinhasImg, ColunasImg));
    // }
    // else{
    //     image_out = image_in; 
    // }

    for (int i = 0 ; i < QntFiltros; i++){
        split(image_out, canais); //BGR

        filter2D(canais[0], canaisResultado[0], -1, kernelConv_Camada_0[i]);
        filter2D(canais[1], canaisResultado[1], -1, kernelConv_Camada_1[i]);
        filter2D(canais[2], canaisResultado[2], -1, kernelConv_Camada_2[i]);

        merge(canaisResultado, image_out);

        add(image_out, conv_bias[i], image_out);
    }

    return image_out;
}
