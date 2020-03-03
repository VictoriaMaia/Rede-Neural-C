#ifndef BIBLIOTECAS
#define BIBLIOTECAS
#include "iniciarBiblio.h"
#endif
#include "iniciarPool.h"

Mat camadaMaxPool(Mat in){
    int tam = (in.rows-1) * (in.cols-1);
    int contPosOut = 0;
    unsigned char maxIp, maxJp, maiorC0, maiorC1, maiorC2;
    Vec3b valoresMat, valoresComparar;

    uchar vetOutPoolC0 [tam];
    uchar vetOutPoolC1 [tam];
    uchar vetOutPoolC2 [tam];

    for(int i = 0; i < in.rows; i++){
        for(int j = 0; j < in.cols; j++){
            maxIp = i+tamMaxPool;
            maxJp = j+tamMaxPool;
            if((maxIp > in.rows) or (maxJp > in.cols)){
                break;
            }
            valoresMat = in.at<cv::Vec3b>(i,j);

            maiorC0 = valoresMat[0];
            maiorC1 = valoresMat[1];
            maiorC2 = valoresMat[2];

            for(int ipool = i; ipool < maxIp; ipool++){
                for(int jpool = j; jpool < maxJp; jpool++){
                    valoresComparar = in.at<cv::Vec3b>(ipool,jpool);

                    if(valoresComparar[0] > maiorC0){
                        maiorC0 = valoresComparar[0];
                    }
                    if(valoresComparar[1] > maiorC1){
                        maiorC1 = valoresComparar[1];
                    }
                    if(valoresComparar[2] > maiorC2){
                        maiorC2 = valoresComparar[2];
                    }
                }
            }
            vetOutPoolC0[contPosOut] = maiorC0;
            vetOutPoolC1[contPosOut] = maiorC1;
            vetOutPoolC2[contPosOut] = maiorC2;

            contPosOut++;
        }
    }

    Mat outPool;
    Mat outPoolC0(in.rows-1,in.cols-1, CV_8UC1);
    Mat outPoolC1(in.rows-1,in.cols-1, CV_8UC1);
    Mat outPoolC2(in.rows-1,in.cols-1, CV_8UC1);

    outPoolC0.data = vetOutPoolC0;
    outPoolC1.data = vetOutPoolC1;
    outPoolC2.data = vetOutPoolC2;

    vector <Mat> saida;

    saida.push_back(outPoolC0);
    saida.push_back(outPoolC1);
    saida.push_back(outPoolC2);

    merge(saida, outPool);

    return outPool;
}