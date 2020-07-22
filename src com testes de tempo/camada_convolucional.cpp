#ifndef BIBLIOTECAS
#define BIBLIOTECAS
#include "iniciarBiblio.h"
#endif
#include "iniciarConv.h"

Mat camadaConvolucao(Mat image_in, int ind_filtro){
    Mat image_out;
    image_in.copyTo(image_out);
    float result = 0;

    for(int i = 0; i < 28; i++){
        for(int j = 0; j < 28; j++){
            if(((i+2) < 28) && ((j+2) < 28)){
                
                for(int iK = 0; iK < 3; iK++){
                    for(int jK = 0; jK < 3; jK++){
                        result += image_in.at<float>(i+iK,j+jK) * kernelConv[ind_filtro].at<float>(iK,jK);                        
                    }
                }       
                result += conv_bias[ind_filtro];

                image_out.at<float>(i+1,j+1) = result;
                result = 0;            
            }            
        }
    }
    
    // filter2D(image_in, image_out, -1, kernelConv[ind_filtro]);
    
    // add(image_out, conv_bias[ind_filtro], image_out);
    
    return image_out;
}
