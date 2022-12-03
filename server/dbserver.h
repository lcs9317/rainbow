#ifndef DBSERVER_H
#define DBSERVER_H

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <stdlib.h>

typedef struct Point{
    double x;
    double y;
}Point;

typedef struct Line{
    Point p1;
    Point p2;
}Line;

double** send_coordinate();
double ** current_coordinate();
int ccw(Point , Point , Point );
int comparator(Point , Point );
void swap(Point* , Point*);
bool LineIntersection(Line , Line );
double length(double , double, double , double );
bool iscrash(double *, double*);
bool crash(double *, double*,bool);
void coordinate_code();

#endif // DBSERVER_H
