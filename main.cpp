#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QStringList>
#include <QFile>
#include "QDebug"
#include "Controller.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    Controller contl;

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    QString map = "[[550,-1,-1,-2,-2,-2,-2,150,0,0,0,-3,-2,400,-3,650,-2,-1,0,0,0],[350,-1,-1,-2,0,0,-2,-2,-2,-1,0,-3,-3,-2,300,-2,-1,650,-2,-1,0],[-1,-1,450,-2,0,0,0,0,0,0,0,0,0,-3,-3,-3,-1,-1,-3,0,0],[-1,-1,-2,-2,0,-3,-2,0,0,-3,-3,-3,0,0,0,0,0,0,-3,0,150],[0,0,-2,0,-3,-3,-3,0,-1,-2,400,-3,-3,0,-2,0,-1,0,-3,0,0],[0,200,-2,0,-3,250,-1,0,0,-1,-2,-3,-2,0,-1,300,-1,0,-3,-1,0],[-3,-3,-2,0,-3,-3,-3,0,0,0,0,-3,-3,-3,-2,-2,-2,0,-2,-2,0],[-1,-3,-2,0,0,-2,0,0,-3,-3,-3,-3,150,-3,0,0,0,0,-2,200,0],[800,-3,-2,-3,450,-2,0,-3,-3,200,-1,250,-1,-3,0,-1,-1,0,0,0,0]]";
    QFile inputFile(argv[1]);
    if (argc >= 2 && inputFile.open(QIODevice::ReadOnly))
    {
        contl.setOutputFile(argv[1]);
       QTextStream in(&inputFile);
       while (!in.atEnd())
       {
          map = in.readLine();
       }
       inputFile.close();
       qDebug() << map;
    }

    engine.rootContext()->setContextProperty("loadedMap", map);
    engine.rootContext()->setContextProperty("CONTROLLER", &contl);
    engine.load(url);

    return app.exec();
}
