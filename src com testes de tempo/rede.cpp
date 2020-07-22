#ifndef BIBLIOTECAS
#define BIBLIOTECAS
#include "iniciarBiblio.h"
#endif

#include "iniciarFuncs.h"
// #include <chrono>
// #include <valgrind/callgrind.h>

double timeDenses[4];

int main( int argc, char** argv ){
    timeDenses[0] = 0;
    timeDenses[1] = 0;
    timeDenses[2] = 0;
    timeDenses[3] = 0;


    FILE *fp;
    char str[24];
    const char* filename = "imagensTestMNIST.txt";
 
    fp = fopen(filename, "r");
    if (fp == NULL){
        printf("Could not open file %s",filename);
        return 1;
    }

    double timeConv = 0;
    double timePool = 0;
    // double timeDense = 0;
    double time_taken;

    // if( argc != 2){
    //     cout << "Precisa de apenas uma imagem para o código funcionar" << endl;
    //     return -1;
    // }
    
    // Mat entrada = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
    // cout << str ;
    while (fgets(str, 24, fp) != NULL){        
        fgetc(fp);
        Mat entrada = imread(str, CV_LOAD_IMAGE_GRAYSCALE);

        if(! entrada.data){
            cout <<  "Could not open or find the image" << str << endl ;
            return -1;
        }

        // cout << entrada << endl;

        Mat in;
        entrada.convertTo(in, CV_32FC1);

        in = in/255;

        // convolução
        vector <Mat> resultado_convolucao;
        
        auto startConv = chrono::high_resolution_clock::now();

        resultado_convolucao.push_back(camadaConvolucao(in, 0));
        resultado_convolucao.push_back(camadaConvolucao(in, 1));
        resultado_convolucao.push_back(camadaConvolucao(in, 2));
        resultado_convolucao.push_back(camadaConvolucao(in, 3));
        
        auto endConv = chrono::high_resolution_clock::now(); 


        // maxpool e flatten
        vector <float> result_pool0, result_pool1, result_pool2, result_pool3;
        vector <double> flatten;

        auto startPool = chrono::high_resolution_clock::now();

        result_pool0 = camadaMaxPool(resultado_convolucao[0]);
        result_pool1 = camadaMaxPool(resultado_convolucao[1]);
        result_pool2 = camadaMaxPool(resultado_convolucao[2]);
        result_pool3 = camadaMaxPool(resultado_convolucao[3]);

        auto endPool = chrono::high_resolution_clock::now(); 

        for(unsigned int i = 0; i < result_pool0.size(); i++){
            flatten.push_back(result_pool0[i]);
            flatten.push_back(result_pool1[i]);
            flatten.push_back(result_pool2[i]);
            flatten.push_back(result_pool3[i]);
        }
    
        // auto startDense = chrono::high_resolution_clock::now();
        
        camadas_densas(flatten);
        
        // auto endDense = chrono::high_resolution_clock::now(); 
        
        // time_taken *= 1e-9;         
        time_taken =  chrono::duration_cast<chrono::nanoseconds>(endConv - startConv).count();
        // cout << "Tempo da convolução total : " << time_taken << " nanosegundos" << endl;
        timeConv += time_taken;
        
        time_taken =  chrono::duration_cast<chrono::nanoseconds>(endPool - startPool).count();
        // cout << "Tempo da maxpool total : " << time_taken << " nanosegundos" << endl;
        timePool += time_taken;

        // time_taken =  chrono::duration_cast<chrono::nanoseconds>(endDense - startDense).count();
        // cout << "Tempo das camadas densas total : " << time_taken << " nanosegundos" << endl;
        // timeDense += time_taken;   

    }

    cout << "Tempo da convolução total : " << timeConv*(1e-6) << " milisegundos" << endl;
    cout << "Tempo da maxpool total : " << timePool*(1e-6) << " milisegundos" << endl;
    // cout << "Tempo das camadas densas total : " << timeDense*(1e-6) << " milisegundos" << endl;
    cout << "Tempo das camadas densas0 total : " << timeDenses[0]*(1e-6) << " milisegundos" << endl;
    cout << "Tempo das camadas densas1 total : " << timeDenses[1]*(1e-6) << " milisegundos" << endl;
    cout << "Tempo das camadas densas2 total : " << timeDenses[2]*(1e-6) << " milisegundos" << endl;
    cout << "Tempo das camadas densas3 total : " << timeDenses[3]*(1e-6) << " milisegundos" << endl;

    // cout << "Tempo da convolução total : " << timeConv << " nanosegundos" << endl;
    // cout << "Tempo da maxpool total : " << timePool << " nanosegundos" << endl;
    // // cout << "Tempo das camadas densas total : " << timeDense*1e-9 << " segundos" << endl;
    // cout << "Tempo das camadas densas0 total : " << timeDenses[0] << " nanosegundos" << endl;
    // cout << "Tempo das camadas densas1 total : " << timeDenses[1] << " nanosegundos" << endl;
    // cout << "Tempo das camadas densas2 total : " << timeDenses[2] << " nanosegundos" << endl;
    // cout << "Tempo das camadas densas3 total : " << timeDenses[3] << " nanosegundos" << endl;

    fclose(fp);

    return 0;
}