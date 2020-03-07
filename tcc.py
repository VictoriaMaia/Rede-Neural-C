# Classes
# - 0 ceu/agua
# - 1 plano
# - 2 vegetação
# - 3 obstaculo

from keras import optimizers, regularizers
from keras import layers
from keras import models
from keras.preprocessing.image import ImageDataGenerator
from keras.applications import InceptionV3
from keras.applications import VGG16
from keras.models import Sequential
from keras.layers import Dense, Flatten, Conv2D, MaxPooling2D
from keras.utils import to_categorical
from keras.layers.recurrent import LSTM
from keras.utils import np_utils

from sklearn.model_selection import StratifiedKFold

import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import os
import cv2
from time import time
from IPython.display import FileLink

from sklearn.metrics import confusion_matrix


def plot_confusion_matrix(y_true, y_pred, classes,
                          normalize=False,
                          title=None,
                          cmap=plt.cm.Blues):
    """
    This function prints and plots the confusion matrix.
    Normalization can be applied by setting `normalize=True`.
    """
    if not title:
        if normalize:
            title = 'Normalized confusion matrix'
        else:
            title = 'Confusion matrix, without normalization'

    # Compute confusion matrix
    cm = confusion_matrix(y_true, y_pred)
    # Only use the labels that appear in the data
#     classes = classes[unique_labels(y_true, y_pred)]
#     if normalize:
#         cm = cm.astype('float') / cm.sum(axis=1)[:, np.newaxis]
#         print("Normalized confusion matrix")
#     else:
#         print('Confusion matrix, without normalization')

#     print(cm)

    fig, ax = plt.subplots()
    im = ax.imshow(cm, interpolation='nearest', cmap=cmap)
    ax.figure.colorbar(im, ax=ax)
    # We want to show all ticks...
    ax.set(xticks=np.arange(cm.shape[1]),
           yticks=np.arange(cm.shape[0]),
           # ... and label them with the respective list entries
           xticklabels=classes, yticklabels=classes,
           title=title,
           ylabel='Label verdadeira',
           xlabel='Label predita')

    # Rotate the tick labels and set their alignment.
    plt.setp(ax.get_xticklabels(), rotation=45, ha="right",
             rotation_mode="anchor")

    # Loop over data dimensions and create text annotations.
    fmt = '.2f' if normalize else 'd'
    thresh = cm.max() / 2.
    for i in range(cm.shape[0]):
        for j in range(cm.shape[1]):
            ax.text(j, i, format(cm[i, j], fmt),
                    ha="center", va="center",
                    color="white" if cm[i, j] > thresh else "black")
    fig.tight_layout()
    
    return ax



print(os.listdir("../dataSet/datas/Dados"))

data_dir = "../dataSet/datas/Dados"

RESOLUTION = 100
# quantidade de imagens utilizadas para treinar simultaneamente
BATCH_SIZE = 10
N_EPOCHS = 1000

# Carregando Dataset
datagen = ImageDataGenerator(rescale=1.0/255, validation_split=0.1)

train_generator = datagen.flow_from_directory(
        data_dir,
        target_size=(RESOLUTION, RESOLUTION),
        batch_size=BATCH_SIZE,
        class_mode='categorical', subset="training")


# Carregando Dataset de Validação
# val_datagen = ImageDataGenerator(rescale=1.0/255, validation_split=0.2)
val_generator = datagen.flow_from_directory(
        data_dir,
        target_size=(RESOLUTION, RESOLUTION),
        batch_size=BATCH_SIZE,
        class_mode='categorical', subset="validation")

N_TRAIN = 9428
N_VAL = 1046

modelManualMenor = Sequential()

#convolutional layers
# Conv2D(quantidade de filtros usados, tamanho do extrator de features, dimensão das imagens, função de ativação)
modelManualMenor.add(Conv2D(4, (3,3), input_shape=(100, 100, 3), activation='relu'))
modelManualMenor.add(MaxPooling2D(pool_size = (2,2)))
modelManualMenor.add(Flatten())

#hidden layers
modelManualMenor.add(Dense(10, activation='relu'))
modelManualMenor.add(Dense(8, activation='relu'))
modelManualMenor.add(Dense(6, activation='relu'))
# a ultima camada deve ter o número de classes do problema (4)
modelManualMenor.add(Dense(4, activation='softmax'))

modelManualMenor.compile(loss='categorical_crossentropy', optimizer=optimizers.Adam(lr=1e-4), metrics=['acc'])

history = modelManualMenor.fit_generator(
    train_generator,
    steps_per_epoch=(N_TRAIN // BATCH_SIZE),
    epochs= N_EPOCHS,
    validation_data=val_generator,
    validation_steps=(N_VAL // BATCH_SIZE)
)

acc = history.history['acc']
val_acc = history.history['val_acc']
loss = history.history['loss']
val_loss = history.history['val_loss']

epochs = range(1, len(acc) + 1)

plt.figure(figsize=[15,5])
plt.subplot(121)
plt.plot(epochs, acc, 'g.-', label='Acurácia do Conjunto de Treino')
plt.plot(epochs, val_acc, 'r.-', label='Acurácia do Conjunto de  Validação')
plt.title('Treino e Validação da Acurácia Modelo Simples Menor')
plt.xlabel('Épocas')
plt.ylabel('Acurácia')
plt.legend(loc='best')

plt.subplot(122)
plt.plot(epochs, loss, 'g.-', label='Log loss do Conjunto de Treino')
plt.plot(epochs, val_loss, 'r.-', label='Log loss do Conjunto de Validação')
plt.title('Treino e Validação log loss Modelo Simples Menor')
plt.xlabel('Épocas')
plt.ylabel('Log Loss')
plt.legend(loc='best')
plt.show()

Y_pred = modelManualMenor.predict_generator(val_generator, len(val_generator))
y_pred = np.argmax(Y_pred, axis=1)

target_names = ['vegetacao', 'aguaCeu', 'obstaculo', 'plano']
plot_confusion_matrix(val_generator.classes, y_pred, classes=target_names, title='Matriz de Confusão')
plt.show()

arqInfoRede = modelManualMenor.get_config()

######################################### 
######## CAMADA CONVOLUCIONAL ###########
#########################################
iniciar_conv_h = open('iniciarConv.h', 'w')

# INFORMAÇÕES ÚTEIS
iniciar_conv_h.write("#define LinhasImg "+ str(arqInfoRede['layers'][0]['config']['batch_input_shape'][1])+"\n")
iniciar_conv_h.write("#define ColunasImg "+ str(arqInfoRede['layers'][0]['config']['batch_input_shape'][2])+"\n")
iniciar_conv_h.write("#define QntFiltros "+ str(arqInfoRede['layers'][0]['config']['filters'])+"\n")
# iniciar_conv_h.write("#define linhasFiltro "+ str(arqInfoRede['layers'][0]['config']['kernel_size'][0])+"\n")
# iniciar_conv_h.write("#define colunasFiltro "+ str(arqInfoRede['layers'][0]['config']['kernel_size'][1])+"\n")

# BIAS
name = "conv_bias"
iniciar_conv_h.write("float "+name+" ["+str(modelManualMenor.weights[1].shape.dims[0].value)+"] = {")
for j in range(modelManualMenor.weights[1].shape.dims[0].value - 1):
    iniciar_conv_h.write(str(modelManualMenor.weights[1].numpy()[j])+",")
iniciar_conv_h.write(str(modelManualMenor.weights[1].numpy()[j])+"};\n")

# KERNEL
array4D = modelManualMenor.weights[0]
for camada in range(array4D.shape[2]):
    iniciar_conv_h.write("Mat kernelConv_Camada_"+str(camada)+" ["+str(array4D.shape[3])+"] = {")        
    for filtro in range(array4D.shape[3]):
        iniciar_conv_h.write("(Mat_<float>("+str(array4D.shape[0])+","+str(array4D.shape[1])+") <<")
        for i in range(array4D.shape[0]):
            for j in range(array4D.shape[1]-1):
                iniciar_conv_h.write(str(array4D[i][j][camada][filtro].numpy())+",")
            if i+1 == int(array4D.shape[0]) and filtro == (int(array4D.shape[3])-1):
                iniciar_conv_h.write(str(array4D[i][j+1][camada][filtro].numpy())+")};\n")
            elif i+1 == int(array4D.shape[0]):
                iniciar_conv_h.write(str(array4D[i][j+1][camada][filtro].numpy())+"),")
            else:
                iniciar_conv_h.write(str(array4D[i][j+1][camada][filtro].numpy())+",")

# TESTAR SE O ARQUIVO ESTA CORRETO
iniciar_conv_h.close()

iniciar_conv_h = open('iniciarConv.h', 'r')
for i in iniciar_conv_h:
    print(i, end='')

######################################### 
########### CAMADA MAXPOOL ##############
#########################################
iniciar_pool_h = open('iniciarPool.h', 'w')

# COLOCAR DEPOIS OS DOIS TAMANHOS!!!!!
iniciar_pool_h.write("int tamMaxPool ="+ str(arqInfoRede['layers'][1]['config']['pool_size'][0])+"\n")

# TESTAR SE O ARQUIVO ESTA CORRETO
iniciar_pool_h.close()

iniciar_pool_h = open('iniciarPool.h', 'r')
for i in iniciar_pool_h:
    print(i, end='')


######################################### 
############ CAMADA DENSE ###############
#########################################
iniciar_dense_h = open('iniciarDense.h', 'w')

# STRUCT NEURONIO 
iniciar_dense_h.write("typedef struct Neuronio{\n    vector <float> pesos;\n    float bias;\n} neuronio;\n\n")

# VETOR FUNÇÕES DE ATIVAÇÃO
iniciar_dense_h.write("vector <string> camadasRede = {")

for i in range(3, len(arqInfoRede['layers'])-1): #só as camadas densas
    iniciar_dense_h.write("\""+arqInfoRede['layers'][i]['config']['activation']+"\",")
iniciar_dense_h.write("\""+arqInfoRede['layers'][len(arqInfoRede['layers'])-1]['config']['activation']+"\"};\n")

# VETOR QUANTIDADE DE NEURONIOS
qntNeurorio = 0
iniciar_dense_h.write("vector <int> qntNeuronioCamada = {")

for i in range(3, len(arqInfoRede['layers'])-1): #só as camadas densas
    qntNeurorio += arqInfoRede['layers'][i]['config']['units']
    iniciar_dense_h.write(str(arqInfoRede['layers'][i]['config']['units'])+", ")
qntNeurorio += arqInfoRede['layers'][len(arqInfoRede['layers'])-1]['config']['units']
iniciar_dense_h.write(str(arqInfoRede['layers'][len(arqInfoRede['layers'])-1]['config']['units'])+"};\n\n")

# QUANTIDADE TOTAL DE NEURONIOS
iniciar_dense_h.write("#define qntTotalNeuronios " + str(qntNeurorio))

# INICIALIZAÇÃO DOS NEURONIOS
iniciar_dense_h.write("neuronio vet_Neuronios [qntTotalNeuronios] = {")
# {{},{{vet},bias}}
for i in range(8,len(modelManualMenor.weights), 2):
    bias = modelManualMenor.weights[i+1].numpy()
    valores = modelManualMenor.weights[i].numpy()
    qntColunas = int(modelManualMenor.weights[i].shape.dims[1].value)
    for col in range(qntColunas-1): #percorrer as colunas
        iniciar_dense_h.write("{{") #vetor
        for lin in range(int(modelManualMenor.weights[i].shape.dims[0].value)-1):
            iniciar_dense_h.write(str(valores[lin][col])+",")
        iniciar_dense_h.write(str(valores[lin+1][col])+"},"+str(bias[col])+"},") #vetor e tupla
    
    iniciar_dense_h.write("{{") #vetor
    for lin in range(int(modelManualMenor.weights[i].shape.dims[0].value)-1):
        iniciar_dense_h.write(str(valores[lin][qntColunas-1])+",")
    iniciar_dense_h.write(str(valores[lin+1][qntColunas-1])+"},"+str(bias[qntColunas-1])+"}};\n") #vetor e tupla e vetorzao



# TESTAR SE O ARQUIVO ESTA CORRETO
iniciar_dense_h.close()

iniciar_dense_h = open('iniciarDense.h', 'r')
for i in iniciar_dense_h:
    print(i, end='')
