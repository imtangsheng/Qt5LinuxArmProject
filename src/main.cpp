#include <QApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QSysInfo>
#include <QDebug>
#include <iostream>
#include "version.h"
#include "ui/mainwindow.h"
int main(int argc, char *argv[])
{
    // 强制启用所有调试输出
    //qputenv("QT_LOGGING_RULES", APP_NAME".debug=true");
    //qputenv("QT_MESSAGE_PATTERN", "[%{time hh:mm:ss}] %{message}");

    QApplication app(argc, argv);

    QCoreApplication::setApplicationName("Server");
    QCoreApplication::setApplicationVersion("1.0");
    QCommandLineParser parser;
    parser.setApplicationDescription("Sockets Server");
    parser.addHelpOption();
    QCommandLineOption portOption(QStringList() << "p" << "port",
    QCoreApplication::translate("main", "Port for server [default: 8080]."),
    QCoreApplication::translate("main", "port"), QLatin1String("8080"));
    parser.addOption(portOption);
    parser.process(app);
    int port = parser.value(portOption).toInt();
    // 打印详细的版本信息
    qDebug() << "========================================";
    qDebug() << "软件信息:";
    qDebug() << "----------------------------------------";
    qInfo() << "软件名称:" << AppName;
    qInfo() << "软件版本:" << AppVersion;
    qDebug().noquote() << "编译时间:" << __DATE__ << __TIME__;
    qDebug() << "----------------------------------------";
    qDebug() << "Qt 版本:" << QT_VERSION;
    qDebug() << "C++ 版本:" << __cplusplus;
    qDebug() << "----------------------------------------";
    qDebug() << "系统信息:";
    // 基础系统信息
    qDebug() << "操作系统:" << QSysInfo::prettyProductName();
    qDebug() << "内核版本:" << QSysInfo::kernelVersion();
    qDebug() << "系统架构:" << QSysInfo::currentCpuArchitecture();
    qDebug() << "主机名称:" << QSysInfo::machineHostName();
    qDebug() << "产品类型:" << QSysInfo::productType();
    qDebug() << "产品版本:" << QSysInfo::productVersion();
    qDebug() << "========================================";
    qDebug() << "";
    std::cout << "Sockets server listening on port: " << port << std::endl;
    qDebug() << "----------------------------------------";
    // 测试标准输出是否工作
    MainWindow w;
    w.show();
    return app.exec();
}
