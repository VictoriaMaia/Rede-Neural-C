def savePesos(modelManualMenor):

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
    iniciar_conv_h.write(str(modelManualMenor.weights[1].numpy()[j+1])+"};\n")

    # KERNEL
    array4D = modelManualMenor.weights[0]
    for camada in range(array4D.shape[2]):
        iniciar_conv_h.write("Mat kernelConv ["+str(array4D.shape[3])+"] = {")        
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
    # iniciar_conv_h.close()

    # iniciar_conv_h = open('iniciarConv.h', 'r')
    # for i in iniciar_conv_h:
    #     print(i, end='')

    iniciar_conv_h.close()
    ######################################### 
    ########### CAMADA MAXPOOL ##############
    #########################################
    iniciar_pool_h = open('iniciarPool.h', 'w')

    # COLOCAR DEPOIS OS DOIS TAMANHOS!!!!!
    iniciar_pool_h.write("#define tamMaxPool "+ str(arqInfoRede['layers'][1]['config']['pool_size'][0])+"\n")

    # TESTAR SE O ARQUIVO ESTA CORRETO
    # iniciar_pool_h.close()

    # iniciar_pool_h = open('iniciarPool.h', 'r')
    # for i in iniciar_pool_h:
    #     print(i, end='')

    iniciar_pool_h.close()
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
    iniciar_dense_h.write("#define qntTotalNeuronios " + str(qntNeurorio) + "\n")

    # INICIALIZAÇÃO DOS NEURONIOS
    iniciar_dense_h.write("neuronio vet_Neuronios [qntTotalNeuronios] = {")
    # {{},{{vet},bias}}
    for i in range(2,len(modelManualMenor.weights), 2):
    #     iniciar_dense_h.write("{") #tupla
        bias = modelManualMenor.weights[i+1].numpy()
    #     print(bias)
        valores = modelManualMenor.weights[i].numpy()
        qntColunas = int(modelManualMenor.weights[i].shape.dims[1].value)
        if (i == (len(modelManualMenor.weights)-2)): #ultima camada
            # print(i)
            for col in range(qntColunas-1): #percorrer as colunas
                iniciar_dense_h.write("{{") #vetor
                for lin in range(int(modelManualMenor.weights[i].shape.dims[0].value)-1):
                    iniciar_dense_h.write(str(valores[lin][col])+",")
                iniciar_dense_h.write(str(valores[lin+1][col])+"},"+str(bias[col])+"},") #vetor e tupla

            iniciar_dense_h.write("{{") #vetor
            for lin in range(int(modelManualMenor.weights[i].shape.dims[0].value)-1):
                iniciar_dense_h.write(str(valores[lin][qntColunas-1])+",")
            iniciar_dense_h.write(str(valores[lin+1][qntColunas-1])+"},"+str(bias[qntColunas-1])+"}};\n") #vetor e tupla e vetorzao
        else:
            for col in range(qntColunas): #percorrer as colunas
                iniciar_dense_h.write("{{") #vetor
                for lin in range(int(modelManualMenor.weights[i].shape.dims[0].value)-1):
                    iniciar_dense_h.write(str(valores[lin][col])+",")
    #                 iniciar_dense_h.write(str(1.05)+",")
                iniciar_dense_h.write(str(valores[lin+1][col])+"},"+str(bias[col])+"},") #vetor e tupla
    #             iniciar_dense_h.write(str(1.05)+"},"+str(5.4)+"},")

    iniciar_dense_h.close()
    # TESTAR SE O ARQUIVO ESTA CORRETO
    # iniciar_dense_h.close()

    # iniciar_dense_h = open('iniciarDense.h', 'r')
    # for i in iniciar_dense_h:
    #     print(i, end='')
