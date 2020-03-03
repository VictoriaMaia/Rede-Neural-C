vector <string> camadasRede = {"relu", "relu", "softmax"};
vector <int> qntNeuronioCamada = {6, 4, 3};

// kernel[pesos][neuronio]
// float dense_1_kernel[5][4] = {{1,2,3,4},{1,2,3,4},{1,2,3,4},{1,2,3,4},{2,3,4,5}};
// float dense_1_bias [4] = {9,8,7,6};
// float dense_2_kernel[4][2] = {{-2,-3},{2,3},{-1,3},{1,-4}};
// float dense_2_bias [2] = {5,-5};


typedef struct Neuronio{
    vector <float> pesos;
    float bias;
} neuronio;

#define qntTotalNeuronios 13

neuronio vet_Neuronios [qntTotalNeuronios];
