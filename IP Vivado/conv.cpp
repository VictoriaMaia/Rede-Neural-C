#include "convHard.h"
#include "iniciarConv.h"

//void convLineBuffer(hls::stream<float> &inputStream, float outputStream[2704]){
void convLineBuffer(hls::stream<float> &inputStream, float outputStream[totalResultadoConv]){
#pragma HLS INTERFACE axis port=inputStream
//#pragma HLS INTERFACE axis port=outputStream
#pragma HLS INTERFACE ap_memory port=outputStream
#pragma HLS INTERFACE s_axilite port=return bundle=CTRL_BUS //dizer que acabou

	hls::LineBuffer<tamFiltro, ColunasImg, float> LB;

	int linha = 0;
	int coluna = 0;

	int linhaResult = 0;
	int colunaResult = 0;

	int pixelCalculado = 0;

	float pixelLido;
	float val;

	float valorFinal[QntFiltros];
	for(int i = 0; i < QntFiltros; i++){
		valorFinal[i] = 0;
	}

	int posicaoSalvar;

	for(int pixel = 0; pixel < (LinhasImg*ColunasImg); pixel++){
	#pragma HLS PIPELINE
		pixelLido = inputStream.read();
		LB.shift_up(coluna);
		LB.insert_top(pixelLido, coluna);

		if ((linha >= tamFiltro-1) && (coluna >= tamFiltro-1)){
//			li todos os pixels necessarios para preencher uma janela válida
//			calculando as convoluções
			for(int linhaKernel = 0; linhaKernel < tamFiltro; linhaKernel++){
				for(int colunaKernel = 0; colunaKernel < tamFiltro; colunaKernel++){
					val = LB.getval(linhaKernel, colunaKernel+pixelCalculado);
//					para acessar o valor do kernel dado o filtro
//					((linha * qnt_coluna_Kernel) + coluna) + ( tam_total_Kernel * filtro )
					for(int filtro = 0; filtro < QntFiltros; filtro++){
						valorFinal[filtro] += kernelConv[((linhaKernel*tamFiltro)+colunaKernel)+(tamTotalFiltro*filtro)] * val;
					}
				}
			}

//			somando o valor de bias e salvando o resultado da convolucao
			for(int resultFiltro = 0; resultFiltro < QntFiltros; resultFiltro++){
				valorFinal[resultFiltro] += conv_bias[resultFiltro];
	//			para salvar o valor no devido lugar do vetor de saida
	//			sendo qnt_colunas_Resultado = colunasImagem - 2
	//			sendo total_Resultado = linhasImagem-2 * colunasImagem-2 (retirando a borda da imagem)
	//			((linha * qnt_colunas_Resultado) + coluna) + (total_Resultado*filtro)
				posicaoSalvar = ((linhaResult * (ColunasImg-2)) + colunaResult) + (totalRConv*resultFiltro);
//				printf("Valor final pos[%d][%d] (%d) do filtro %d = %f\n", linhaResult, colunaResult, posicaoSalvar, resultFiltro, valorFinal[resultFiltro]);
				outputStream[posicaoSalvar] = valorFinal[resultFiltro];
				valorFinal[resultFiltro] = 0;
			}

			pixelCalculado++;
	//		andar na matriz de saida 26*26
			if(colunaResult < ColunasImg-3){
				colunaResult++;
			}
			else{
				linhaResult++;
				colunaResult = 0;
			}
		}

//		andar na imagem
		if (coluna < ColunasImg-1){
			coluna++;
		}
		else{
			linha++;
			coluna = 0;
			pixelCalculado = 0;
		}
	}
}
