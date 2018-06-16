#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickStyle>
#include <QFontDatabase>
#include <QDebug>

#include "mynetwork.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    QQuickStyle::setStyle("Material");
    //QFontDatabase::addApplicationFont(QString::fromLatin1(":/Lato-Light.ttf"));
    //app.setFont(QFont("Lato Light", 20));

    QQmlApplicationEngine engine;

    MyNetwork myNetwork ;
    engine.rootContext()->setContextProperty("myNetwork", &myNetwork);


    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
