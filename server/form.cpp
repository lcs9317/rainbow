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




Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    double ** coor;
    coor = send_coordinate();
    bool **result;
    int len = 0;
    ui->setupUi(this);



    QWebEngineSettings::globalSettings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);

    ui->webView->setUrl(QUrl("qrc:/html/google_maps.html"));

    connect(ui->webView->page(), SIGNAL(loadFinished(bool)), this, SLOT(webView(bool)));

    ui->CrashWarning->setText("lists\n");
    ui->CrashWarning->setText("what?");
    ui->CrashWarning->append("wow");
    ui->CrashWarning->append("ok");
    result = crashing();
    for(int i = 0; coor[i][0] < 0; i++ )
        len+= 1;
    for(int i= 0; i < len - 1; i++)
        for(int j = i + 1; j < len; j++)
            if(result[i][j] == 1)
                ui->CrashWarning->append(QString("%1 and %2 can crash").arg(i).arg(j));

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
    out << str2 + str + "initialize();";
    java = str2 + str + "initialize();";
    ui->webView->page()->runJavaScript(java);



}

bool** Form::crashing() {
    double ** coordinate;
    int len = 0;

    bool **result;
    coordinate = send_coordinate();
    for(int i = 0; coordinate[i][0] < 0; i++)
        len += 1;
    result = new bool*[len];
    for(int i = 0; i < len ; i++)
        result[i] = new bool[len];
    for(int i = 0; i < len - 1; i++) {
        for(int j = i + 1; j < len; j++){
            if(coordinate[i][0] == coordinate[j][0])
                continue;
            else {
                result[i][j] = iscrash(coordinate[i],coordinate[j]);
                if(result[i][j] == 1){
                    result[i][j] = crash(coordinate[i],coordinate[j],result[i][j]);

                }

            }
        }
    }
    return result;
}

void Form::CrashWarning()
{

    QTextEdit *textedit = new QTextEdit;

    textedit->setText("This is crashWarning text lists");

}



