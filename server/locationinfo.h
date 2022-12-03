#ifndef LOCATIONINFO_H
#define LOCATIONINFO_H

#include <QObject>
#include <QWebEngineView>
#include <QMessageBox>
#include <QWebChannel>

class WebClass : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString someattribute MEMBER m_someattribute)
public slots:
    void jscallme()
    {
        QMessageBox::information(NULL,"jscallme","I'm called by js!");
    }
    void setsomeattribute(QString attr)
    {
        m_someattribute=attr;
       emit someattributeChanged(m_someattribute);
    }
signals:
    void someattributeChanged(QString & attr);
private:
    QString m_someattribute;
};

#endif // LOCATIONINFO_H
