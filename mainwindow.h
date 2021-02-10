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

private slots:
    void on_le_platform_textChanged(const QString &arg1);
    void on_le_instal_textChanged(const QString &arg1);
    void on_le_chrome_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;

    void updateFinalCode();
};
#endif // MAINWINDOW_H
