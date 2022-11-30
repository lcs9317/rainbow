#include "dbserver.h"

double** send_coordinate() {
    std::ifstream ifs;
    double** coordinate = new double*[100];
    int j;

    for(int i = 0; i < 100; i++)
            coordinate[i] = new double[4];


    ifs.open("../output.txt", std::ios::out | std::ios::in);

    for(int i = 0; i < 100; i ++) {
        for(j = 0; j< 4; j++)
             ifs >> coordinate[i][j];
    }
    std::cout << coordinate[0][0] << " / " <<coordinate[0][1] << " / " <<coordinate[0][2] << " / " <<coordinate[0][3] << std::endl;

    return coordinate;
}

