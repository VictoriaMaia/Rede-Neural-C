#ifndef BIBLIOTECAS
#define BIBLIOTECAS
#include "iniciarBiblio.h"
#endif
#include "iniciarDense.h"

void iniar_pesos(){
    // c0 com 6 neuronios
    vet_Neuronios[0].bias = 3;
    vet_Neuronios[0].pesos = {1,1,2,3};
    vet_Neuronios[1].bias = 3;
    vet_Neuronios[1].pesos = {-1,-1.5,1,3};
    vet_Neuronios[2].bias = 2;
    vet_Neuronios[2].pesos = {0,0.05,5,5.1};
    vet_Neuronios[3].bias = 1;
    vet_Neuronios[3].pesos = {-3,-1.65,3,2};
    vet_Neuronios[4].bias = 4;
    vet_Neuronios[4].pesos = {1,2,1,1};
    vet_Neuronios[5].bias = 2;
    vet_Neuronios[5].pesos = {0,0.5,1,1.6};
    
    // c1 com 4 neuronios
    vet_Neuronios[6].bias = 1;
    vet_Neuronios[6].pesos = {0,0.5,0.6,-0.7,0.9,3};
    vet_Neuronios[7].bias = 1;
    vet_Neuronios[7].pesos = {1,1,-3,-2,1.1,1.5};
    vet_Neuronios[8].bias = 2;
    vet_Neuronios[8].pesos = {0.4,0.9,-1.2,-1.5,2,1};
    vet_Neuronios[9].bias = 1;
    vet_Neuronios[9].pesos = {1,2,1,-1,-2,3};

    // c2 com 3 neuronios
    vet_Neuronios[10].bias = 2.0;
    vet_Neuronios[10].pesos = {0,0,0,0};
    vet_Neuronios[11].bias = 1.0;
    vet_Neuronios[11].pesos = {0,0,0,0};
    vet_Neuronios[12].bias = 0.1;
    vet_Neuronios[12].pesos = {0,0,0,0};

}


float somatorio_camada_0(vector <uchar> entrada, neuronio neuro){
    float result_somatorio = 0;

    for (unsigned int i = 0; i < entrada.size(); i++){
        // cout << entrada[i] << " * " << neuro.pesos[i] << " = " << entrada[i] * neuro.pesos[i] << endl; 
        result_somatorio += entrada[i] * neuro.pesos[i];
        // cout < < "entrada[" << i << "] = " << entrada[i] 
        //      << "peso [" << i << "] = " << peso[i]
        //      << "resul : " << result_somatorio << endl;
    }
    // cout << "soma : " << result_somatorio << " + " << neuro.bias << endl;
    result_somatorio += neuro.bias;
    // cout << "Resultado final : " << result_somatorio << endl;
    // cout << result_somatorio;


    return result_somatorio;
}

float somatorio(vector <float> entrada, neuronio neuro){
    float result_somatorio = 0;

    for (unsigned int i = 0; i < entrada.size(); i++){
        // cout << entrada[i] << " * " << neuro.pesos[i] << " = " << entrada[i] * neuro.pesos[i] << endl; 
        result_somatorio += entrada[i] * neuro.pesos[i];
        // cout < < "entrada[" << i << "] = " << entrada[i] 
        //      << "peso [" << i << "] = " << peso[i]
        //      << "resul : " << result_somatorio << endl;
    }
    // cout << "soma : " << result_somatorio << " + " << neuro.bias << endl;
    result_somatorio += neuro.bias;
    // cout << "Resultado final : " << result_somatorio << endl;
    // cout << result_somatorio;

    
    return result_somatorio;
}

float func_ativacao(float valor_in, int camada){
    // função de ativação que pega apenas valores positivos
    // os valores negativos são arredondados para zero
    // RELU = max(0, x)
    if (camadasRede[camada] == "relu"){
        // cout << "sua func é relu" << endl;
        // cout << "v: " << valor_in << " c: " << camada << endl;
        if(valor_in < 0){
            return 0;
        }else{
            return valor_in;
        }
    }
}

// função de ativação que transforma valores em probabilidades
// SOFTMAX = S(y_i) = e^(y_i) / SUM(e^(yj))
// calcula os expoentes com todas as entradas e divide esse valor
// com o resultado da soma de todos os expoentes calculados
// void camada_SOFTMAX(neuronio *n){
vector <float> funcao_softmax(vector <float> valores){
    vector <float> expoentes, result;
    float soma = 0;

    for (unsigned int i = 0; i < valores.size(); i++){
        expoentes.push_back(exp(valores[i]));
        soma += exp(valores[i]);
        // cout << "valor" << valores[i] << " exp: " << exp(valores[i]) << endl;
    }
    // cout << "Soma: " << soma << endl;
    // cout.precision(2);
    for (unsigned int i = 0; i < valores.size(); i++){
        result.push_back(expoentes[i]/soma);
        // cout << expoentes[i]/soma << endl;
    }
    return result;
} 


vector <float> camada_densa0(Mat in){
    vector <uchar> vet_in;
    
    if (in.isContinuous()){
        vet_in.assign(in.data, (in.data + in.total()));
    }else{
        for (int i = 0; i < in.rows; ++i){
            vet_in.insert(vet_in.end(), in.ptr(i), in.ptr(i)+in.cols);
        }
    }

    vector <float> vet_resultado;
    for (int neuro = 0; neuro < qntNeuronioCamada[0]; neuro++){
        vet_resultado.push_back(func_ativacao(somatorio_camada_0(vet_in, vet_Neuronios[neuro]), 0));
    }

    return vet_resultado;
}

vector <float> camada_densa(vector <float> vetEntrada, int neuronioBegin, int neuronioEnd, int camada){
    vector <float> vet_resultado;
    
    for (int neuro = neuronioBegin; neuro < neuronioEnd; neuro++){
        vet_resultado.push_back(func_ativacao(somatorio(vetEntrada, vet_Neuronios[neuro]), camada));
    }

    return vet_resultado;
}

void camadas_densas(Mat in){
    vector <float> vetResult;
    vector <float> vetResultUltimaCamada;
    
    vetResult = camada_densa0(in);
    
    // cout << "VetResult da camada 0" << endl;
    // for (unsigned int i = 0; i < vetResult.size(); i++){
    //     cout << vetResult[i] << " ";
    // }
    // cout << endl;

    int neuroBegin, neuroEnd;

    for (unsigned int camada = 1; camada < (qntNeuronioCamada.size()-1); camada++){
        neuroBegin = 0;
            for (unsigned int i = 0; i < camada; i++){
                neuroBegin += qntNeuronioCamada[i];
            }
            neuroEnd = neuroBegin+(qntNeuronioCamada[camada]);
            // cout << "Camada " << camada << ": " << neuroBegin << " até " << neuroEnd << endl;
            vetResult = camada_densa(vetResult, neuroBegin, neuroEnd, camada);
            // cout << "VetResult da camada "<< camada << endl;
            // for (unsigned int i = 0; i < vetResult.size(); i++){
            //     cout << vetResult[i] << " ";
            // }
            // cout << endl;
    }

    // a última camada é diferentona!
    // executa o somatorio, e pega os valores de todos os neuronios da camada...
    neuroBegin = 0;
    for (unsigned int i = 0; i < qntNeuronioCamada.size()-1; i++){
        neuroBegin += qntNeuronioCamada[i];
    }
    neuroEnd = qntTotalNeuronios;
    // cout << "B: " << neuroBegin << " E: " << neuroEnd << endl;

    for (int neuronio = neuroBegin; neuronio < neuroEnd; neuronio++){
        vetResultUltimaCamada.push_back(somatorio(vetResult, vet_Neuronios[neuronio]));
    }

    // cout << "vetResult ultima camada " << endl;
    // for (int neuronio = 0; neuronio < vetResultUltimaCamada.size(); neuronio++){
    //     cout << vetResultUltimaCamada[neuronio] << " ";
    // }
    // cout << endl;
    vetResultUltimaCamada = funcao_softmax(vetResultUltimaCamada);
    
    cout << "Saida da rede: " << endl;
    cout.precision(2);
    for (unsigned int neuronio = 0; neuronio < vetResultUltimaCamada.size(); neuronio++){
        cout << vetResultUltimaCamada[neuronio] << " ";
    }
    cout << endl;

}