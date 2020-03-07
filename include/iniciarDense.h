typedef struct Neuronio{
    vector <float> pesos;
    float bias;
} neuronio;


vector <string> camadasRede = {"relu", "relu", "softmax"};
vector <int> qntNeuronioCamada = {6, 4, 3};


#define qntTotalNeuronios 13

// {{},{{vet},bias}}
neuronio vet_Neuronios [qntTotalNeuronios] = {{{1,1,2,3},3},{{-1,-1.5,1,3},3},{{0,0.05,5,5.1},2},{{-3,-1.65,3,2},1},{{1,2,1,1},4},{{0,0.5,1,1.6},2},{{0,0.5,0.6,-0.7,0.9,3},1},{{1,1,-3,-2,1.1,1.5},1},{{0.4,0.9,-1.2,-1.5,2,1},2},{{1,2,1,-1,-2,3},1},{{0,0,0,0},2.0},{{0,0,0,0},1.0},{{0,0,0,0},0.1}};

