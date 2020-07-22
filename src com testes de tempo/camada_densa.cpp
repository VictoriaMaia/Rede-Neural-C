#ifndef BIBLIOTECAS
#define BIBLIOTECAS
#include "iniciarBiblio.h"
#endif

#include "iniciarDense.h"

extern double timeDenses[4];

double somatorio_camada_0(vector <double> entrada, neuronio neuro){
    double result_somatorio = 0;
    for (unsigned int i = 0; i < entrada.size(); i++){
        result_somatorio += entrada[i] * neuro.pesos[i];        
    }
    result_somatorio += neuro.bias;

    if(result_somatorio < 0){
        return 0;
    }else{
        return result_somatorio;
    }
  
    // return result_somatorio;
}



double somatorio(vector <double> entrada, neuronio neuro){
    double result_somatorio = 0;

    for (unsigned int i = 0; i < entrada.size(); i++){
        result_somatorio += entrada[i] * neuro.pesos[i];
    }
    
    result_somatorio += neuro.bias;

    if(result_somatorio < 0){
        return 0;
    }else{
        return result_somatorio;
    }
    
    // return result_somatorio;
}

// double func_ativacao(double valor_in, int camada){
    // função de ativação que pega apenas valores positivos
    // os valores negativos são arredondados para zero
    // RELU = max(0, x)
    // if (camadasRede[camada] == "relu"){
    // if(valor_in < 0){
    //     return 0;
    // }else{
    //     return valor_in;
    // }
    // }
// }

// função de ativação que transforma valores em probabilidades
// SOFTMAX = S(y_i) = e^(y_i) / SUM(e^(yj))
// calcula os expoentes com todas as entradas e divide esse valor
// com o resultado da soma de todos os expoentes calculados
// void camada_SOFTMAX(neuronio *n){
vector <double> funcao_softmax(vector <double> valores){
    vector <double> expoentes;
    vector <double> result;
    double soma = 0;

    for (unsigned int i = 0; i < valores.size(); i++){
        expoentes.push_back(exp(valores[i]));
        soma += exp(valores[i]);
    }
    
    for (unsigned int i = 0; i < valores.size(); i++){
        result.push_back(expoentes[i]/soma);
    }

    return result;
} 


vector <double> camada_densa0(vector <double> vet_in){
    vector <double> vet_resultado;

    for (int neuro = 0; neuro < qntNeuronioCamada[0]; neuro++){
        vet_resultado.push_back(somatorio_camada_0(vet_in, vet_Neuronios[neuro]));    
    }
    
    return vet_resultado;
}

vector <double> camada_densa(vector <double> vetEntrada, int neuronioBegin, int neuronioEnd, int camada){
    vector <double> vet_resultado;
    
    for (int neuro = neuronioBegin; neuro < neuronioEnd; neuro++){
        vet_resultado.push_back(somatorio(vetEntrada, vet_Neuronios[neuro]));
    }

    return vet_resultado;
}

void camadas_densas(vector <double> in){
    vector <double> vetResult;
    vector <double> vetResultUltimaCamada;
    

    auto startDense = chrono::high_resolution_clock::now();
    vetResult = camada_densa0(in);

    auto endDense = chrono::high_resolution_clock::now(); 
    timeDenses[0] += chrono::duration_cast<chrono::nanoseconds>(endDense - startDense).count();

    int neuroBegin, neuroEnd;

    for (unsigned int camada = 1; camada < (qntNeuronioCamada.size()-1); camada++){
        neuroBegin = 0;
            for (unsigned int i = 0; i < camada; i++){
                neuroBegin += qntNeuronioCamada[i];
            }
            neuroEnd = neuroBegin+(qntNeuronioCamada[camada]);
            
            startDense = chrono::high_resolution_clock::now();
            
            vetResult = camada_densa(vetResult, neuroBegin, neuroEnd, camada);

            endDense = chrono::high_resolution_clock::now(); 
            timeDenses[camada] += chrono::duration_cast<chrono::nanoseconds>(endDense - startDense).count();
    }

    // a última camada é diferentona!
    // executa o somatorio, e pega os valores de todos os neuronios da camada...
    neuroBegin = 0;
    for (unsigned int i = 0; i < qntNeuronioCamada.size()-1; i++){
        neuroBegin += qntNeuronioCamada[i];
    }
    neuroEnd = qntTotalNeuronios;

    startDense = chrono::high_resolution_clock::now();
    
    for (int neuronio = neuroBegin; neuronio < neuroEnd; neuronio++){
        vetResultUltimaCamada.push_back(somatorio(vetResult, vet_Neuronios[neuronio]));
    }

    vetResultUltimaCamada = funcao_softmax(vetResultUltimaCamada);

    endDense = chrono::high_resolution_clock::now(); 
    timeDenses[3] += chrono::duration_cast<chrono::nanoseconds>(endDense - startDense).count();
    
    // mostrando a predição
    int posicaoMaior = 0;
    double maior = vetResultUltimaCamada[0];

    for (unsigned int neuronio = 0; neuronio < vetResultUltimaCamada.size(); neuronio++){
        if(vetResultUltimaCamada[neuronio] > maior){
            posicaoMaior = neuronio;
            maior = vetResultUltimaCamada[neuronio];
        }
        // cout << vetResultUltimaCamada[neuronio] << " ";
    }
    cout << "\npredição : " << posicaoMaior;
    // cout << endl;

}

