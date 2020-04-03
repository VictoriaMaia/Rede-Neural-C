#ifndef BIBLIOTECAS
#define BIBLIOTECAS
#include "iniciarBiblio.h"
#endif
#include "iniciarPool.h"

vector <float> camadaMaxPool(Mat in){
    // int lOut = (in.rows-2)/2;
    // int cOut = (in.cols-2)/2;
    // int contPosOut = 0;
    float maxIp, maxJp, maior, valoresComparar;

    // uchar vetOutPool [lOut*cOut];
    vector <float> vetOutPool;

    for(int i = 1; i < in.rows-1; i=i+2){
        for(int j = 1; j < in.cols-1; j=j+2){
            maxIp = i+tamMaxPool;
            maxJp = j+tamMaxPool;

            if((maxIp > in.rows) or (maxJp > in.cols)){
                break;
            }

            // maior = in.at<float>(i,j);
            maior = 0;

            for(int ipool = i; ipool < maxIp; ipool++){
                for(int jpool = j; jpool < maxJp; jpool++){
                    valoresComparar = in.at<float>(ipool,jpool);

                    if(valoresComparar > maior){
                        maior = valoresComparar;
                    }
                }
            }
            // printf("%d ", maior);
            // vetOutPool[contPosOut] = maior;
            vetOutPool.push_back(maior);
            
            // contPosOut++;
        }
    }
    
    // Mat out(lOut,cOut, CV_8UC1);
    // out.data = vetOutPool;

    // cout << "resultDentro" << endl << out << endl;

    return vetOutPool;
    // return out.clone();
}