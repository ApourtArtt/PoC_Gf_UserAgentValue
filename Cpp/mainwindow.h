#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QByteArray CreateCode(QString PlatformGameAccountId, QString InstallationId, QString ChromeVersion);

private:
    Ui::MainWindow *ui;

    QByteArray generatePassword();
    QByteArray getHashedPassword(QString InstallationId);
    void updateFinalCode();

    QByteArray sha256(QByteArray input);
    QByteArray sha1(QByteArray input);


    bool IsFirstDigitEven(QString InstallationId);
};
#endif // MAINWINDOW_H
