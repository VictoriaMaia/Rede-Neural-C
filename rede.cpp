#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

#define QntFiltros 2

float bias [2] = {50,50};

// SobelY,SobelX
vector <Mat> kernels {(Mat_<int>(3,3) << -1, -2, -1, 0, 0, 0, 1, 2, 1),(Mat_<int>(3,3) << -1, 0, 1, -2, 0, 2, -1, 0, 1)};
 
Mat camandaConvolucao(Mat image_in){
    vector <Mat> canais (3);
    vector <Mat> canaisResultado (3);
    Mat image_out = image_in;

    
    for (int i = 0 ; i < QntFiltros; i++){
        split(image_out, canais); //BGR

        filter2D(canais[0], canaisResultado[0], -1, kernels[i]);
        filter2D(canais[1], canaisResultado[1], -1, kernels[i]);
        filter2D(canais[2], canaisResultado[2], -1, kernels[i]);

        merge(canaisResultado, image_out);

        add(image_out, bias[i], image_out);
    }

    return image_out;
}


int main( int argc, char** argv ){
    if( argc != 2){
        cout << "Precisa de apenas uma imagem para o código funcionar" << endl;
        return -1;
    }

    Mat in = imread(argv[1], CV_LOAD_IMAGE_COLOR);
    if(! in.data){
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }

    namedWindow("Imagem de entrada", WINDOW_AUTOSIZE);
    imshow("Imagem de entrada", in);    

    Mat Out;
    Out = camandaConvolucao(in);

    namedWindow("Imagem de saida", WINDOW_AUTOSIZE);
    imshow("Imagem de saida", Out);    


    waitKey(0);                 
    destroyAllWindows();                     
    return 0;
}