#include "mainwindow.h"
#include <iostream>

extern "C"
{
    #include <libavcodec/avcodec.h>
    #include <libavformat/avformat.h>
    #include <libavfilter/avfilter.h>
}

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
}

MainWindow::~MainWindow()
{
}

int MainWindow::printVersionFFmpeg()
{
    unsigned version = avcodec_version();
    cout << "version is:" << version << endl;
    return 0;
}
