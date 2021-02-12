#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "codecreator.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QString PlatformGameAccountId = "...";
    QString InstallationId = "...";
    QString ChromeVersion = ("2.1.22.784");

    CodeCreator c(PlatformGameAccountId, InstallationId, ChromeVersion, "cert.p12");
    qDebug() << c.ValidateEndpoint("... (random uuid)");
    qDebug() << c.CreateCode();
}

MainWindow::~MainWindow()
{
    delete ui;
}
