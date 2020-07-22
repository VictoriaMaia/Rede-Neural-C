#ifndef BIBLIOTECAS
#define BIBLIOTECAS
#include "iniciarBiblio.h"
#endif
#include "iniciarPool.h"

vector <float> camadaMaxPool(Mat in){
   float maxIp, maxJp, maior, valoresComparar;

    vector <float> vetOutPool;

    for(int i = 1; i < in.rows-1; i=i+2){
        for(int j = 1; j < in.cols-1; j=j+2){
            maxIp = i+tamMaxPool;
            maxJp = j+tamMaxPool;

            if((maxIp > in.rows) or (maxJp > in.cols)){
                break;
            }
           
            maior = 0;

            for(int ipool = i; ipool < maxIp; ipool++){
                for(int jpool = j; jpool < maxJp; jpool++){
                    valoresComparar = in.at<float>(ipool,jpool);

                    if(valoresComparar > maior){
                        maior = valoresComparar;
                    }
                }
            }
            vetOutPool.push_back(maior);
        }
    }
   

    return vetOutPool;
}