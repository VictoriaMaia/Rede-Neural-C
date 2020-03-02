#ifndef CAMADA_DENSA
#define CAMADA_DENSA

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
// #include "iniciar_pesos.h"

using namespace cv;
using namespace std;

// void camadas_densas();
void iniar_pesos();
void camadas_densas(Mat in);
// vector <float> camada_densa0(Mat in);
// vector <float> camada_densa(vector <float> vetEntrada, int neuronioBegin, int neuronioEnd, int camada);

#endif