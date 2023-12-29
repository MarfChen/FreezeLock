#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QCheckBox>
//#include <iostream>
#include <QMainWindow>
#include <QMessageBox>
#include <windows.h>
#include <QImage>
#include <QLabel>
#include <stdlib.h>
#include <stdio.h>
#include <QPushButton>
#include <QSettings>
//#pragma comment(linker,"/subsystem:\"windows\"  /entry:\"mainCRTStartup\"" )

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



public slots:
    void onClickCheckbox(int argc);
    void onClickButton1();
    void onClickButton2();
    void onClickButton3();

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
