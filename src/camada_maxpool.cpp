#ifndef BIBLIOTECAS
#define BIBLIOTECAS
#include "iniciarBiblio.h"
#endif
#include "iniciarPool.h"

Mat camadaMaxPool(Mat in){
    int lOut = (in.rows-2)/2;
    int cOut = (in.cols-2)/2;
    int contPosOut = 0;
    unsigned char maxIp, maxJp, maior, valoresComparar;

    uchar vetOutPool [lOut*cOut];

    for(int i = 1; i < in.rows-1; i=i+2){
        for(int j = 1; j < in.cols-1; j=j+2){
            maxIp = i+tamMaxPool;
            maxJp = j+tamMaxPool;

            if((maxIp > in.rows) or (maxJp > in.cols)){
                break;
            }

            maior = in.at<uchar>(i,j);

            for(int ipool = i; ipool < maxIp; ipool++){
                for(int jpool = j; jpool < maxJp; jpool++){
                    valoresComparar = in.at<uchar>(ipool,jpool);

                    if(valoresComparar > maior){
                        maior = valoresComparar;
                    }
                }
            }
            // printf("%d ", maior);
            vetOutPool[contPosOut] = maior;
            
            contPosOut++;
        }
    }
    
    Mat out(lOut,cOut, CV_8UC1);
    out.data = vetOutPool;

    // cout << "resultDentro" << endl << out << endl;

    return out.clone();
}