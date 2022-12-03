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
    ui->setupUi(this);


    QWebEngineSettings::globalSettings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);

    ui->webView->setUrl(QUrl("qrc:/html/google_maps.html"));
    connect(ui->textEdit,SIGNAL(),this,SLOT(CrashWarning()));
    connect(ui->webView->page(), SIGNAL(loadFinished(bool)), this, SLOT(webView(bool)));



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



void Form::CrashWarning()
{   QTextEdit text;
    text.setText("this is crash warning messages\n");

}

