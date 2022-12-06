#include "form.h"
#include "ui_form.h"
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
#include <time.h>
#include <windows.h>
#include <QTimer>
#include "aws.h"




Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{

    QTimer *timer = new QTimer(this);
    QTimer *timer2 = new QTimer(this);
    QTimer *timer3 = new QTimer(this);
    timer->start(30000);
    timer2->start(15000);
    timer3->start(10000);
    ui->setupUi(this);



    QWebEngineSettings::globalSettings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);

    ui->webView->setUrl(QUrl("qrc:/html/google_maps.html"));

    connect(ui->webView->page(), SIGNAL(loadFinished(bool)), this, SLOT(webView(bool)));
    connect(timer, SIGNAL(timeout()),this,SLOT(webView2()));

    connect(timer3, SIGNAL(timeout()), this , SLOT(CrashWarning()));
    connect(timer2, SIGNAL(timeout()),this, SLOT(awsdb()));




}

Form::~Form()
{
    delete ui;
}

void Form::webView(bool ok) {


    QFile file2("../untitled4/coordinate_input.txt");
    if(!file2.open(QIODevice::ReadOnly))
        qDebug() << "error";
    QFile file3("../untitled4/coordinate_output.txt");
    if(!file3.open(QIODevice::ReadWrite))
        qDebug() << "error";
    QFile file("../untitled4/coordinate.js");
    if(!file.open(QIODevice::ReadOnly))
        qDebug() << "error";
    QString str;
    QString str2;

    QTextStream out(&file3);
    QString java;
    str2 = file2.readAll();
    str = file.readAll();
    java = str2 + str + "color_initialize();" + "pathlist();" +"initialize(); " ;
    ui->webView->page()->runJavaScript(java);



}

int Form::webView2() {


    QFile file2("../untitled4/coordinate_input.txt");
    if(!file2.open(QIODevice::ReadOnly))
        qDebug() << "error";
    QFile file3("../untitled4/coordinate_output.txt");
    if(!file3.open(QIODevice::ReadWrite))
        qDebug() << "error";
    QFile file("../untitled4/coordinate.js");
    if(!file.open(QIODevice::ReadOnly))
        qDebug() << "error";
    QString str;
    QString str2;

    QTextStream out(&file3);
    QString java;
    str2 = file2.readAll();
    str = file.readAll();
    java = str2 + str + "pathlist();" +"initialize();" ;
    ui->webView->page()->runJavaScript(java);


    return 0;
}

bool** Form::crashing() {
    double ** coordinate;
    int len = 0;
    bool **result;
    double result2;
    coordinate = send_coordinate();

    for(int i = 0; coordinate[i][0] > 0; i++)
        len += 1;
    result = new bool*[len];
    for(int i = 0; i < len ; i++)
        result[i] = new bool[len];
    for(int i = 0; i < len - 1; i++) {
        for(int j = i + 1; j < len; j++){

            if(coordinate[i][0] != coordinate[j][0]){
                result[i][j] = 0;
                continue;
            }
            else {
                result[i][j] = iscrash(coordinate[i],coordinate[j]);

                if(result[i][j] != 0){
                    result2 = crash(coordinate[i],coordinate[j],result[i][j]);
                    if(result2 != 0){
                        result[i][j] = 1;
                    }
                    else {
                        result[i][j] = 0;
                    }
                }

            }
        }
    }
    return result;
}

void Form::CrashWarning()
{

    double ** coor;
    bool **result;
    coor = send_coordinate();
    result = crashing();
    int len = 0;
        for(int i = 0; coor[i][0] > 0; i++ )
            len+= 1;

        for(int i= 0; i < len - 1; i++)
            for(int j = i + 1; j < len;  j++){
                if(result[i][j] != 0){

                    ui->CrashWarning->append(QString("%1 and %2 can crash").arg(i).arg(j));
                }
            }
    delete result;
}

void Form::awsdb() {
    droneDB();
    coordinate_code();

}

