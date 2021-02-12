#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "codecreator.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString PlatformGameAccountId = "bd87095a-6dd2-469c-9718-d14d1114e737";//("94d05b8e-31c0-4feb-92f6-c10084146208");
    QString InstallationId = "a1a73c4e-7aa0-4d03-a54c-220bd0b378ce";//("06cae5e5-a4c2-4056-858b-1cb4fcc44a74");
    QString ChromeVersion = ("2.1.22.784");

    CodeCreator c(PlatformGameAccountId, InstallationId, ChromeVersion, "from_ram.p12");
    qDebug() << c.ValidateEndpoint();
    qDebug() << c.CreateCode();
}

MainWindow::~MainWindow()
{
    delete ui;
}
