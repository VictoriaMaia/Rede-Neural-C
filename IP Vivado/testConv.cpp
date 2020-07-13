#include "convHard.h"
#include <hls_opencv.h>
using namespace cv;

//#include <iostream>

#define INPUT_IMAGE "imageTest0.jpg"

int main(){
//	LEITURA DA IMAGEM
//	cv::Mat in = (cv::Mat_<float>(4,5) << 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20);
	printf("Lendo imagem %s\n", INPUT_IMAGE);
	Mat imagemLida = imread(INPUT_IMAGE, CV_LOAD_IMAGE_GRAYSCALE);
	Mat in;
	imagemLida.convertTo(in, CV_32FC1);
	in = in/255;

//	CRIAÇÃO DO INPUTSTREAM
	hls::stream<float> inputStream;
	hls::stream<float> outputStream; // valor das 4 convoluções

//	vetor de saida contendo o resultado das convoluções tem tamanho
//	(qnt_linhas - 2) * (qnt_colunas - 2) * qnt_filtros = 2704
//	printf("O fitro de saída tem tamanho : %d\n", ((imagemLida.rows-2)*(imagemLida.cols-2)*4));
//	float result_convs[((imagemLida.rows-2)*(imagemLida.cols-2)*4)];
	float result_convs[totalResultadoConv];



	for(int linha = 0; linha <imagemLida.rows; linha++){
		for(int coluna = 0; coluna < imagemLida.cols; coluna++){
			inputStream << in.at<float>(linha, coluna);
		}
	}

//	CHAMANDO AS CONVOLUÇÕES
	printf("Começando as convoluções\n");
//	void convLineBuffer(hls::stream<float> &inputStream, hls::stream<float> &outputStream);
//	convLineBuffer(inputStream, outputStream);
	convLineBuffer(inputStream, result_convs);
	printf("Convoluções terminaram\n");

	int totalPixelsResultConv = (imagemLida.rows-2) * (imagemLida.cols-2);

//	imprimindo resultado da conv0
	for(int i = 0; i < 4; i++){
		printf("Filtro %d\n", i);
		for(int linha = 0; linha <imagemLida.rows-2; linha++){
			for(int coluna = 0; coluna < imagemLida.cols-2; coluna++){
				std::cout << result_convs[((linha *(imagemLida.cols-2) + coluna) + totalPixelsResultConv*i)] << " , ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
//	std::cout << "Imprimindo resposta\n";
//	for(int linha = 0; linha <imagemLida.rows-2; linha++){
//		for(int coluna = 0; coluna < imagemLida.cols-2; coluna++){
//			std::cout << outputStream.read() << " , ";
//		}
//		std::cout << std::endl;
//	}



	return 0;
}

