### TCC 2 - GERADOR DE ARQUITETURA SOC DE REDES NEURAIS CONVOLUCIONAIS PARA A EXECUÇÃO EM FPGAS

Este repositório contém os arquivos de código implementados para o desenvolvimento do meu TCC. Onde:
  
  - *IP Vivado* contém os arquivos da camada convolucional ao qual foi gerado o IP utilizando o programa Vivado HLS 2016.4
  - *Implementação C* contém os arquivos da CNN implementada em C++. Arquivos em
      - *src* contendo os arquivos com as instruções para a execução de cada camada da rede
      - *src com testes de tempo* contém os mesmos arquivos de *src* porém com o uso da biblioteca *chrono* para a execução do profiling
      - *include* os arquivos cabeçalhos gerados pelo scrip "inicializando.py"   
  - *TccMnist.ipynb* possui o código da CNN desenvolvida em python. Caso não consiga visualizar com o git, é possível visualizar utilizando o [jupyter](https://nbviewer.jupyter.org/github/VictoriaMaia/Rede-Neural-C/blob/master/TccMnist.ipynb)
  - *inicializando.py* contém as instruções para gerar os arquivos cabeçalho contendo as informações da rede implementada em python. Esses arquivos gerados são necessários para o código C++ da rede ser executada.  
  - *tcc.py*, código de teste do TCC1.

