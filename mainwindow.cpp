#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QByteArray>
#include <QCryptographicHash>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_le_platform_textChanged(const QString &arg1)
{
    QCryptographicHash crypt(QCryptographicHash::Algorithm::Sha1);
    crypt.addData(arg1.toLatin1(), arg1.size());
    ui->tb_platform->setText(crypt.result().toHex());
    updateFinalCode();
}

void MainWindow::on_le_instal_textChanged(const QString &arg1)
{
    QCryptographicHash crypt(QCryptographicHash::Algorithm::Sha256);
    crypt.addData(arg1.toLatin1(), arg1.size());
    ui->tb_instal->setText(crypt.result().toHex());
    updateFinalCode();
}

void MainWindow::on_le_chrome_textChanged(const QString &arg1)
{
    QCryptographicHash crypt(QCryptographicHash::Algorithm::Sha1);
    crypt.addData(arg1.toLatin1(), arg1.size());
    ui->tb_chrome->setText(crypt.result().toHex());
    updateFinalCode();
}

void MainWindow::updateFinalCode()
{
    // encryptionKey + sha1(chromeVersion).toHex()
    QString append1 = ui->le_encryptionKey->text() + ui->tb_chrome->toPlainText();
    // append1 + sha256(installationId).toHex()
    QString append2 = append1 + ui->tb_instal->toPlainText();
    // append2 + sha1(platformGameUserId).toHex()
    QString append3 = append2 + ui->tb_platform->toPlainText();
    // Sha256(append3).toHex()
    QCryptographicHash crypt(QCryptographicHash::Algorithm::Sha256);
    crypt.addData(append3.toLatin1(), append3.size());
    QString result = crypt.result().toHex();



    ui->le_finalcode->setText(result);
}
