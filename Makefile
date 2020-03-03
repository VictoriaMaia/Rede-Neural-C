INCLUDE_DIR = -Iinclude/ -I/usr/local/include/opencv 
LIBS = -lopencv_highgui -lopencv_core -lopencv_imgcodecs -lopencv_imgproc
FLAGS = -Wall -std=c++14
GCC = g++
ARCHIVES = src/camada_convolucional.cpp src/camada_maxpool.cpp src/camada_densa.cpp src/rede.cpp

all:
	$(GCC) $(FLAGS) $(ARCHIVES) -o app $(INCLUDE_DIR) $(LIBS)
