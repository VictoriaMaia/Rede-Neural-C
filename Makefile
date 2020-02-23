INCLUDE_DIR = -I/usr/local/include/opencv 
LIBS = -lopencv_highgui -lopencv_core -lopencv_imgcodecs -lopencv_imgproc
FLAGS = -Wall -std=c++14
GCC = g++

all:
	$(GCC) $(FLAGS) rede.cpp -o app $(INCLUDE_DIR) $(LIBS)
