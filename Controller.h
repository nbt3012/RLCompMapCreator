#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QDebug>
#include <QFile>

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QString outputFile= "", QObject *parent = nullptr);

    Q_INVOKABLE void setJson(QString json) {
        if (output !="")
        {
            QFile inputFile(output);
            if (inputFile.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text))
            {
                qDebug() << output;
                QTextStream out(&inputFile);
               out << json;
            }
            inputFile.close();

        }
        qDebug() << json;
    }

    void setOutputFile(QString out) {
        output = out;
    }
private:
    QString output;

signals:

};

#endif // CONTROLLER_H
