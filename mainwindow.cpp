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
    QString ChromeVersion = ("C2.1.22.784");

    CodeCreator c(PlatformGameAccountId, InstallationId, ChromeVersion, "from_ram.p12");
    qDebug() << c.CreateCode();
}

MainWindow::~MainWindow()
{
    delete ui;
}
