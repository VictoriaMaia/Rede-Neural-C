#ifndef BIBLIOTECAS
#define BIBLIOTECAS
#include "iniciarBiblio.h"
#endif

#include "iniciarFuncs.h"



int main( int argc, char** argv ){
    // Mat in = (Mat_<uchar>(6,6) << 10,10,10,10,10,10,10,4,1,5,2,10,10,1,2,9,0,10,10,2,2,6,4,10,10,3,1,0,3,10,10,10,10,10,10,10);
    // camadas_densas(in);
    // vector <uchar> vet0 = {1};
    // vector <uchar> vet1 = {2};
    // vector <uchar> vet2 = {3};
    // vector <uchar> vet3 = {4};
    // vector <uchar> flatten;

    // flatten.insert(flatten.end(), vet0.begin(), vet0.end());
    // flatten.insert(flatten.end(), vet1.begin(), vet1.end());
    // flatten.insert(flatten.end(), vet2.begin(), vet2.end());
    // flatten.insert(flatten.end(), vet3.begin(), vet3.end());
    // for (int i = 0; i < flatten.size(); i++){
    //     printf("%d ", flatten[i]);
    // }
    // cout << endl;


    if( argc != 2){
        cout << "Precisa de apenas uma imagem para o código funcionar" << endl;
        return -1;
    }

    // Mat in = imread(argv[1], CV_LOAD_IMAGE_COLOR);
    Mat in = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
    if(! in.data){
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }

    // namedWindow("Imagem de entrada", WINDOW_AUTOSIZE);
    // imshow("Imagem de entrada", in);    

    // convolução
    vector <Mat> resultado_convolucao;
    resultado_convolucao.push_back(camadaConvolucao(in, 0));
    resultado_convolucao.push_back(camadaConvolucao(in, 1));
    resultado_convolucao.push_back(camadaConvolucao(in, 2));
    resultado_convolucao.push_back(camadaConvolucao(in, 3));

    // cout << "testeConv " << resultado_convolucao[0].size() << endl;

    namedWindow("Imagem de saida filtro0", WINDOW_AUTOSIZE);
    imshow("Imagem de saida filtro0", resultado_convolucao[0]);    

    namedWindow("Imagem de saida filtro1", WINDOW_AUTOSIZE);
    imshow("Imagem de saida filtro1", resultado_convolucao[1]);    

    namedWindow("Imagem de saida filtro2", WINDOW_AUTOSIZE);
    imshow("Imagem de saida filtro2", resultado_convolucao[2]);    

    namedWindow("Imagem de saida filtro3", WINDOW_AUTOSIZE);
    imshow("Imagem de saida filtro3", resultado_convolucao[3]);    


    // // maxpool
    vector <Mat> resultado_pool;
    resultado_pool.push_back(camadaMaxPool(resultado_convolucao[0]));
    resultado_pool.push_back(camadaMaxPool(resultado_convolucao[1]));
    resultado_pool.push_back(camadaMaxPool(resultado_convolucao[2]));
    resultado_pool.push_back(camadaMaxPool(resultado_convolucao[3]));
    

    //  vector <uchar> flatten;

    // flatten.insert(flatten.end(), vet0.begin(), vet0.end());
    // flatten.insert(flatten.end(), vet1.begin(), vet1.end());
    // flatten.insert(flatten.end(), vet2.begin(), vet2.end());
    // flatten.insert(flatten.end(), vet3.begin(), vet3.end());
    // for (int i = 0; i < flatten.size(); i++){
    //     printf("%d ", flatten[i]);
    // }
    // cout << endl;


    namedWindow("Imagem de saida pool0", WINDOW_AUTOSIZE);
    imshow("Imagem de saida pool0", resultado_pool[0]);    

    namedWindow("Imagem de saida pool1", WINDOW_AUTOSIZE);
    imshow("Imagem de saida pool1", resultado_pool[1]);    

    namedWindow("Imagem de saida pool2", WINDOW_AUTOSIZE);
    imshow("Imagem de saida pool2", resultado_pool[2]);    

    namedWindow("Imagem de saida pool3", WINDOW_AUTOSIZE);
    imshow("Imagem de saida pool3", resultado_pool[3]);    


    // // cout << "resultTustus" << endl << resultado_pool[0].size() << endl;



    waitKey(0);                 
    destroyAllWindows();                     
    return 0;
}