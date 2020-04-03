#ifndef BIBLIOTECAS
#define BIBLIOTECAS
#include "iniciarBiblio.h"
#endif
#include "iniciarConv.h"

Mat camadaConvolucao(Mat image_in, int ind_filtro){
    Mat image_out;
    
    filter2D(image_in, image_out, -1, kernelConv[ind_filtro]);
    
    add(image_out, conv_bias[ind_filtro], image_out);
    
    // cout << endl << endl << "########## CONV ###########" << endl << endl;
    // cout << image_out << endl;

    // if (image_in.rows != LinhasImg || image_in.cols != ColunasImg){
    //     resize(image_in, image_out, Size(LinhasImg, ColunasImg));
    // }
    // else{
    //     image_out = image_in; 
    // }

    return image_out;
}
