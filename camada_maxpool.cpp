// maxpool
    // Mat inC0 = (Mat_<uchar>(5,5) << 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    // Mat inC1 = (Mat_<uchar>(5,5) << 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    // Mat inC2 = (Mat_<uchar>(5,5) << 0, 255, 0, 255, 0, 0, 0, 0, 0, 0, 0, 255, 0, 255, 0, 0, 0, 0, 0, 0, 0, 255, 0, 255, 0);

    // Mat in;

    // vector <Mat> entrada;

    // entrada.push_back(inC0);
    // entrada.push_back(inC1);
    // entrada.push_back(inC2);
    
    // merge(entrada, in);

    int tam = (in.rows-1) * (in.cols-1);
    // cout << tam << endl;
    int tamMaxPool = 2;
    int contPosOut = 0;
    unsigned char maxIp, maxJp, maiorC0, maiorC1, maiorC2;
    Vec3b valoresMat, valoresComparar;

    uchar vetOutPoolC0 [tam];
    uchar vetOutPoolC1 [tam];
    uchar vetOutPoolC2 [tam];

    for(int i = 0; i < in.rows; i++){
        for(int j = 0; j < in.cols; j++){
            maxIp = i+tamMaxPool;
            maxJp = j+tamMaxPool;
            if((maxIp > in.rows) or (maxJp > in.cols)){
                break;
            }
            valoresMat = in.at<cv::Vec3b>(i,j);
            // cout << "Valores lidos da matriz :\n" << valoresMat << endl;
            maiorC0 = valoresMat[0];
            maiorC1 = valoresMat[1];
            maiorC2 = valoresMat[2];
            // maior = matriz[i][j];
            for(int ipool = i; ipool < maxIp; ipool++){
                for(int jpool = j; jpool < maxJp; jpool++){
                    // cout << "Sendo ipool = " << ipool << " e jpool = " << jpool << endl;
                    valoresComparar = in.at<cv::Vec3b>(ipool,jpool);
                    // cout << "valores a comparar : " << endl << valoresComparar << endl;
                    if(valoresComparar[0] > maiorC0){
                        maiorC0 = valoresComparar[0];
                    }
                    if(valoresComparar[1] > maiorC1){
                        maiorC1 = valoresComparar[1];
                    }
                    if(valoresComparar[2] > maiorC2){
                        maiorC2 = valoresComparar[2];
                    }
                    // if(matriz[ipool][jpool] > maior){
                    //     maior = matriz[ipool][jpool];
                    // }
                }
            }
            // cout << "Maiores encontrados : \n";
            // printf("C0 = %d\n", maiorC0);
            // printf("C1 = %d\n", maiorC1);
            // printf("C2 = %d\n", maiorC2);
            
            vetOutPoolC0[contPosOut] = maiorC0;
            vetOutPoolC1[contPosOut] = maiorC1;
            vetOutPoolC2[contPosOut] = maiorC2;


            // printf("C0 = %d na pos %d\n", vetOutPoolC0[contPosOut], contPosOut);
            // printf("C1 = %d na pos %d\n", vetOutPoolC1[contPosOut], contPosOut);
            // printf("C2 = %d na pos %d\n", vetOutPoolC2[contPosOut], contPosOut);
            
            contPosOut++;

            // matOut.push_back(maior);
            // cout << "maior foi : ";
            // printf("%d \n", maior);
        }
        // break;
    }
    // cout << endl << endl;
    // for (int i = 0; i < tam; i++){
    //     printf("C0 = %d\n", vetOutPoolC0[i]);
    // }
    
    // for (int i = 0; i < tam; i++){
    //     printf("C1 = %d\n", vetOutPoolC1[i]);
    // }

    // for (int i = 0; i < tam; i++){
    //     printf("C2 = %d\n", vetOutPoolC2[i]);        
    // }
    

    Mat outPool;
    Mat outPoolC0(in.rows-1,in.cols-1, CV_8UC1);
    Mat outPoolC1(in.rows-1,in.cols-1, CV_8UC1);
    Mat outPoolC2(in.rows-1,in.cols-1, CV_8UC1);
    outPoolC0.data = vetOutPoolC0;
    outPoolC1.data = vetOutPoolC1;
    outPoolC2.data = vetOutPoolC2;
    vector <Mat> saida;

    saida.push_back(outPoolC0);
    saida.push_back(outPoolC1);
    saida.push_back(outPoolC2);

    merge(saida, outPool);
    
    
    namedWindow("Imagem de entrada Teste", WINDOW_AUTOSIZE);
    imshow("Imagem de entrada Teste", in);    

    namedWindow("Imagem de saida maxpool", WINDOW_AUTOSIZE);
    imshow("Imagem de saida maxpool", outPool);    
