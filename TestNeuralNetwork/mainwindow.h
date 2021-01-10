#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QJsonObject>
#include <QDateTime>
#include <QThread>
#include <QRect>
#include <QJsonDocument>
#include <QElapsedTimer>
#include <QDebug>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <string>
#include <map>
#include "python.h"
#include "numpy/arrayobject.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    int interPython();


public Q_SLOTS:

};
#endif // MAINWINDOW_H
