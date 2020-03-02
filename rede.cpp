#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
// #include "camada_convolucional.h"
// #include "camada_maxpool.h"
#include "camada_densa.h"

using namespace cv;
using namespace std;


int main( int argc, char** argv ){
    Mat in = (Mat_<uchar>(2,2) << 1,2,3,4);
    iniar_pesos();
    camadas_densas(in);
    














    // if( argc != 2){
    //     cout << "Precisa de apenas uma imagem para o código funcionar" << endl;
    //     return -1;
    // }

    // Mat in = imread(argv[1], CV_LOAD_IMAGE_COLOR);
    // if(! in.data){
    //     cout <<  "Could not open or find the image" << std::endl ;
    //     return -1;
    // }

    // namedWindow("Imagem de entrada", WINDOW_AUTOSIZE);
    // imshow("Imagem de entrada", in);    

    // // convolução

    // Mat outConv;
    // outConv = camadaConvolucao(in);

    // namedWindow("Imagem de saida convolução", WINDOW_AUTOSIZE);
    // imshow("Imagem de saida convolução", outConv);    

    // maxpool
    // Mat outPool = camadaMaxPool(in);
    
    // namedWindow("Imagem de saida max pool", WINDOW_AUTOSIZE);
    // imshow("Imagem de saida max pool", outPool);    



    // waitKey(0);                 
    // destroyAllWindows();                     
    return 0;
}