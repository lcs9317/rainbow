#include "dbserver.h"
#include <math.h>
#include <QDebug>
#include <QWebEngineSettings>
#include <QWebEngineView>
#include <QtWebEngineWidgets>
#include <QMessageBox>
#include <QFrame>
#include <QtWebView>
#include <QUrl>
#include <QJSEngine>
#include "dbserver.h"
#include <QWebEngineScript>
#include <QFile>
#include <iostream>
#include <fstream>
#include <stdio.h>



double** send_coordinate() {
    std::ifstream ifs;
    double** coordinate = new double*[100];
    int j;

    for(int i = 0; i < 100; i++)
            coordinate[i] = new double[6];


    ifs.open("../output.txt", std::ios::out | std::ios::in);

    for(int i = 0; i < 100; i ++) {
        for(j = 0; j< 6; j++)
             ifs >> coordinate[i][j];
    }

    return coordinate;
}

int ccw(Point p1, Point p2, Point p3){
    int cross_product = (p2.x - p1.x)*(p3.y - p1.y) - (p3.x - p1.x)*(p2.y - p1.y);

    if (cross_product > 0){
        return 1;
    }
    else if (cross_product < 0){
        return -1;
    }
    else{
        return 0;
    }
}

int comparator(Point left, Point right){
    int ret;
    if(left.x == right.x){
        ret = (left.y <= right.y);
    }
    else{
        ret = (left.x <= right.x);
    }
    return ret;
}

void swap(Point* p1, Point* p2){
    Point temp;
    temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

bool LineIntersection(Line l1, Line l2){
    bool ret;
    int l1_l2 = ccw(l1.p1, l1.p2, l2.p1) * ccw(l1.p1, l1.p2, l2.p2);
    int l2_l1 = ccw(l2.p1, l2.p2, l1.p1) * ccw(l2.p1, l2.p2, l1.p2);

    if(l1_l2 == 0 && l2_l1 == 0){
        if(comparator(l1.p2, l1.p1)) swap(&l1.p1, &l1.p2);

        if(comparator(l2.p2, l2.p1)) swap(&l2.p1, &l2.p2);

        ret = (comparator(l2.p1, l1.p2)) && (comparator(l1.p1, l2.p2));
    }
    else{
        ret = (l1_l2 <= 0) && (l2_l1 <= 0);
    }
    return ret;
}

int iscrash(double *coordinate, double* coordinate2) {
    int iscrash = 0;
    Line l1, l2;
    double coordinate_result = 0;
    coordinate_result = coordinate[0] - coordinate2[0];
    if(coordinate_result > 0.00005 && coordinate_result < -0.00005)
        return 0;


    l1.p1.x = coordinate[4];
    l1.p1.y = coordinate[5];
    l1.p2.x = coordinate[2];
    l1.p2.y = coordinate[3];

    l2.p1.x = coordinate2[4];
    l2.p1.y = coordinate2[5];
    l2.p2.x = coordinate2[2];
    l2.p2.y = coordinate2[3];

    iscrash = LineIntersection(l1,l2);


    return iscrash;
}
double length(double x1, double y1, double x2, double y2){
    double result;
    result = sqrt((pow((y2 - y1),2)+pow((x2 - x1),2)));
    return result;

}
double crash(double *coordinate, double *coordinate2, bool can_crash) {

    double result = 0;
    double x1, x2, y1, y2;
    double a1,a2, b1, b2;
    double crash_coor[2];
    double length_result[2];

    x1 = coordinate[4];
    y1 = coordinate[5];
    x2 = coordinate[2];
    y2 = coordinate[3];
    a1 = (y2 - y1)/(x2-x1);
    b1 = y1 - (y2 - y1)/(x2 - x1)*x1;
    x1 = coordinate2[4];
    y1 = coordinate2[5];
    x2 = coordinate2[2];
    y2 = coordinate2[3];
    a2 = (y2 - y1)/(x2-x1);
    b2 = y1 - (y2 - y1)/(x2 - x1)*x1;
    crash_coor[0] = (b1 - b2)/(a2 - a1);
    crash_coor[1] = -1*a1*(b2 - b1)/(a2 - a1) + b1;
    length_result[0] = length(coordinate[2],coordinate[3],crash_coor[0],crash_coor[1]);
    length_result[1] = length(crash_coor[0],crash_coor[1],coordinate2[2],coordinate2[3]);
    result = length_result[0] > length_result[1] ? length_result[0] - length_result[1] : length_result[1] - length_result[0];

    if(can_crash && result < 0.04 && length_result[0] < 1 )
        return 1;
    else
        return 0;

}

void coordinate_code() {
    double **coordinate;

    std::ifstream ifs;
    std::ifstream ofs;

    QFile file("../untitled4/coordinate_input.txt");
    if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate)){
        file.close();
    }
    QTextStream out(&file);
    QString str1;
    QString str2;
    QString str3;
    QString str4;
    QString jsstr;
    QString str5;
    int i;

    coordinate = send_coordinate();


    for(i = 0; i< 100; i++)
        if(coordinate[i][0] < 0)
            break;

    str1 = "function createPath(rows, columns) { \nvar arr = new Array(rows); \nfor (var i = 0; i < rows; i++) { \narr[i] = new Array(columns);\n}\nreturn arr;\n}";
    out << str1;
    for(i = 0; coordinate[i][0] > 0; i++){
        str2 = QString("var start%1 = {lat: %2, lng: %3};\n").arg(i + 1).arg(QString::number(coordinate[i][4],'g',10)).arg(QString::number(coordinate[i][5],'g',10));
        out << str2;
    }
    str5 =QString("\nvar polylinePath = createPath(%1,2);\n").arg(i) + QString("var polyline = new Array(%1);\n").arg(i) + QString("var marker = new Array(%1);\n").arg(i);
    out << str5;
    str2 = QString::fromUtf8("\n function pathlist (){ \n polylinePath = [ \n");
    out << str2;
    for(i = 0; coordinate[i][0] > 0; i++){
        if (i == 1 && coordinate[i+1][0] < 0)
        {
        str3 = QString::fromUtf8("[new google.maps.LatLng(%1, %2),\n").arg(QString::number(coordinate[i][4],'g',10)).arg(QString::number(coordinate[i][5],'g',10));
        str4 = QString::fromUtf8("new google.maps.LatLng(%1, %2)]\n").arg(QString::number(coordinate[i][2],'g',10)).arg(QString::number(coordinate[i][3],'g',10));
        jsstr = str3 + str4;
        out << jsstr;
            break;
        }
        str3 = QString::fromUtf8("[new google.maps.LatLng(%1, %2),\n").arg(QString::number(coordinate[i][4],'g',10)).arg(QString::number(coordinate[i][5],'g',10));
        str4 = QString::fromUtf8("new google.maps.LatLng(%1, %2)]\n").arg(QString::number(coordinate[i][2],'g',10)).arg(QString::number(coordinate[i][3],'g',10));

    jsstr =str3 + str4;
    out << jsstr;
    if(coordinate[i + 1][0] < 0 && i >= 2)
        break;
    else
        out << ",\n";


    }

    out << "\n]\n\n";
    out << "\n} \n";

    out << "var map;\nvar i = 0;\n";
    out << "\n\n";



    }



