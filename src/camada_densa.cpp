#ifndef BIBLIOTECAS
#define BIBLIOTECAS
#include "iniciarBiblio.h"
#endif

#include "iniciarDense.h"


double somatorio_camada_0(vector <double> entrada, neuronio neuro){
    double result_somatorio = 0;
    // cout << "WW: " << neuro.pesos[0] << endl;
    // int cont = 0;
    // cout << "$$$$$$$$$$$$$$$$" << endl;
    cout << endl << endl << "#############################################" << endl << endl;
    for (unsigned int i = 0; i < entrada.size(); i++){
        // printf("entrada[i] %d", entrada[i]); 
        cout << "E:" << entrada[i];
        cout << " * " << neuro.pesos[i] << " = " << entrada[i] * neuro.pesos[i] << endl; 
        // cont++;
        // if (cont == 10) break;
        result_somatorio += entrada[i] * neuro.pesos[i];
        // printf("entrada[%d] %d",i, entrada[i]); 
        // cout  << " peso [" << i << "] = " << neuro.pesos[i]
        cout << " resul : " << result_somatorio << endl;
    }
    // cout << "$$$$$$$$$$$$$$$$" << endl;
    // cout << "soma : " << result_somatorio << " + " << neuro.bias << endl;
    result_somatorio += neuro.bias;
    // cout << "Resultado final : " << result_somatorio << endl;
    // cout << result_somatorio;


    return result_somatorio;
}

double somatorio(vector <double> entrada, neuronio neuro){
    double result_somatorio = 0;

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

double func_ativacao(double valor_in, int camada){
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
vector <double> funcao_softmax(vector <double> valores){
    vector <double> expoentes;
    vector <double> result;
    double soma = 0;

    for (unsigned int i = 0; i < valores.size(); i++){
        expoentes.push_back(exp(valores[i]));
        soma += exp(valores[i]);
        cout << "valor " << valores[i] << " exp: " << exp(valores[i]) << endl;
    }
    // cout << "Soma: " << soma << endl;
    // cout.precision(2);
    for (unsigned int i = 0; i < valores.size(); i++){
        result.push_back(expoentes[i]/soma);
        // cout << expoentes[i]/soma << endl;
    }
    return result;
} 


vector <double> camada_densa0(vector <double> vet_in){
    // vector <uchar> vet_in;
    
    // if (in.isContinuous()){
    //     vet_in.assign(in.data, (in.data + in.total()));
    // }else{
    //     for (int i = 0; i < in.rows; ++i){
    //         vet_in.insert(vet_in.end(), in.ptr(i), in.ptr(i)+in.cols);
    //     }
    // }

    // cout << "########" << endl;
    vector <double> vet_resultado;
    for (int neuro = 0; neuro < qntNeuronioCamada[0]; neuro++){
        // cout << "ff" << vet_Neuronios[0].pesos[9999] << endl;
        // break;
        vet_resultado.push_back(func_ativacao(somatorio_camada_0(vet_in, vet_Neuronios[neuro]), 0));
        cout << vet_resultado[neuro] << endl;
        
    }
    // cout << "########" << endl;

    return vet_resultado;
}

vector <double> camada_densa(vector <double> vetEntrada, int neuronioBegin, int neuronioEnd, int camada){
    vector <double> vet_resultado;
    
    for (int neuro = neuronioBegin; neuro < neuronioEnd; neuro++){
        vet_resultado.push_back(func_ativacao(somatorio(vetEntrada, vet_Neuronios[neuro]), camada));
        // cout << vet_resultado[neuro]<< endl;
    }

    return vet_resultado;
}

void camadas_densas(vector <double> in){
    vector <double> vetResult;
    vector <double> vetResultUltimaCamada;
    
    // cout << vet_Neuronios[0].pesos[0] << endl;
    vetResult = camada_densa0(in);

    // vetResult = {3.2691195, 3.6873474, 0, 1.7306606, 0.51309276, 2.105507, 0, 0, 3.3548365, 3.8776755};

    cout << "VetResult da camada 0" << endl;
    for (unsigned int i = 0; i < vetResult.size(); i++){
        cout << vetResult[i] << " ";
    }
    cout << endl;

    int neuroBegin, neuroEnd;

    for (unsigned int camada = 1; camada < (qntNeuronioCamada.size()-1); camada++){
        neuroBegin = 0;
            for (unsigned int i = 0; i < camada; i++){
                neuroBegin += qntNeuronioCamada[i];
            }
            neuroEnd = neuroBegin+(qntNeuronioCamada[camada]);
            // cout << "Camada " << camada << ": " << neuroBegin << " até " << neuroEnd << endl;
            vetResult = camada_densa(vetResult, neuroBegin, neuroEnd, camada);
            cout << "VetResult da camada "<< camada << endl;
            for (unsigned int i = 0; i < vetResult.size(); i++){
                cout << vetResult[i] << " ";
            }
            cout << endl;
    }

    // a última camada é diferentona!
    // executa o somatorio, e pega os valores de todos os neuronios da camada...
    neuroBegin = 0;
    for (unsigned int i = 0; i < qntNeuronioCamada.size()-1; i++){
        neuroBegin += qntNeuronioCamada[i];
    }
    neuroEnd = qntTotalNeuronios;
    // cout << "B: " << neuroBegin << " E: " << neuroEnd << endl;

    // cout << "tamanho vetResultUltimaCamada " << vetResultUltimaCamada.size() << endl;
    // cout << "vetResult ultima camada antes do somatorio" << endl;
    // for (int neuronio = 0; neuronio < vetResultUltimaCamada.size(); neuronio++){
    //     cout << vetResultUltimaCamada[neuronio] << " ";
    // }
    // cout << endl;

    for (int neuronio = neuroBegin; neuronio < neuroEnd; neuronio++){
        vetResultUltimaCamada.push_back(somatorio(vetResult, vet_Neuronios[neuronio]));
    }

    // cout << "vetResult ultima camada " << endl;
    // for (int neuronio = 0; neuronio < vetResultUltimaCamada.size(); neuronio++){
    //     cout << vetResultUltimaCamada[neuronio] << " ";
    // }
    // cout << endl;
    vetResultUltimaCamada = funcao_softmax(vetResultUltimaCamada);
    
    // cout << "Saida da rede: " << endl;
    // cout.precision(2);

    int posicaoMaior = 0;
    double maior = vetResultUltimaCamada[0];

    for (unsigned int neuronio = 0; neuronio < vetResultUltimaCamada.size(); neuronio++){
        if(vetResultUltimaCamada[neuronio] > maior){
            posicaoMaior = neuronio;
            maior = vetResultUltimaCamada[neuronio];
        }
        cout << vetResultUltimaCamada[neuronio] << " ";
    }
    cout << "\npredição : " << posicaoMaior;
    cout << endl;

}


// ############# DENSE 1 ###############
// [[3.2691195  3.6873474  0.         1.7306606  0.51309276 2.105507
//   0.         0.         3.3548365  3.8776755 ]]
// ############# DENSE 2 ###############
// [[0.         0.         0.         0.         0.         0.
//   0.         0.09155777]]
// ############# DENSE 3 ###############
// [[0.         0.13398263 0.10755999 0.00393601 0.         0.        ]]
// ############# DENSE 4 ###############
// [[0.1119302  0.08221734 0.10013808 0.10311933 0.11225008 0.08869211
//   0.10368744 0.10004014 0.08550791 0.11241733]]