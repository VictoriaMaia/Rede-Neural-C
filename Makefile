INCLUDE_DIR = -I/usr/local/include/opencv
LIBS = -lopencv_highgui -lopencv_core -lopencv_imgcodecs -lopencv_imgproc
FLAGS = -Wall -std=c++14
GCC = g++
ARCHIVES = camada_densa.cpp rede.cpp

all:
	$(GCC) $(FLAGS) $(ARCHIVES) -o app $(INCLUDE_DIR) $(LIBS)
