#include <hls_video.h>
#define totalResultadoConv 2704

void convLineBuffer(hls::stream<float> &inputStream, float outputStream[totalResultadoConv]);
