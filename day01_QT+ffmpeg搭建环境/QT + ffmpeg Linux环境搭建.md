# QT + ffmpeg Linux环境搭建

1. 安装sdl库

   - 源码下载(ffmplay底层使用该库实现渲染)

     ``` 
     https://www.libsdl.org/git.php
     ```

   - 编译+安装

     ``` sh
     tar -zxvf SDL2-2.0.14.tar.gz
     cd SDL2-2.0.14/
     ./configure --prefix=$PWD/_instal
     udo make && sudo make install
     ```
     
   - 设置环境变量

     ```
     在/etc/profile文件中加入：
     
     export PATH=$PATH:/home/fly/workSpace/SDL2/SDL2-2.0.14/_install/lib
     ```

2. x264安装

   ```shell
   git clone https://code.videolan.org/videolan/x264.git
   cd x264
   ./configure --enable-shared --enable-static --disable-asm
   sudo make ; sudo make install
   ```

3. 安装ffmpeg

   ```shell
   ./configure --enable-gpl --enable-shared --enable-libx264 --disable-x86asm
   sudo make ; sudo make install
   
   # 配置环境变量
   export PATH=“/usr/local/bin:$PATH”
   source /etc/profile
   ```

   ````shell
   # 问题解决
   ./ffmpeg: error while loading shared libraries: libx264.so.138: cannot open shared object file: No such file or directory
   
   sudo vim /etc/ld.so.conf
   # 添加
   /usr/local/lib
   # 生效
   sudo ldconfig
   ````

4. QT + FFmpeg使用

   ```makefile
   # 04_ffmpeg_example_7_24.pro
   # 添加ffmpeg库以及头文件目录
   
   QT       += core gui
   
   greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
   
   CONFIG += c++11
   
   # The following define makes your compiler emit warnings if you use
   # any Qt feature that has been marked deprecated (the exact warnings
   # depend on your compiler). Please consult the documentation of the
   # deprecated API in order to know how to port your code away from it.
   DEFINES += QT_DEPRECATED_WARNINGS
   
   # You can also make your code fail to compile if it uses deprecated APIs.
   # In order to do so, uncomment the following line.
   # You can also select to disable deprecated APIs only up to a certain version of Qt.
   #DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
   
   TARGET = helloFFmpeg
   TEMPLATE = app
   
   # ffmpeg
   FFMPEG_INCLUDE  = /usr/local/include
   FFMPEG_LIB      = /usr/local/lib
   
   SOURCES += \
       main.cpp \
       mainwindow.cpp
   
   HEADERS += \
       mainwindow.h
   
   INCLUDEPATH +=  $$FFMPEG_INCLUDE
   
   LIBS += $$FFMPEG_LIB/libavcodec.so      \
           $$FFMPEG_LIB/libavdevice.so     \
           $$FFMPEG_LIB/libavfilter.so     \
           $$FFMPEG_LIB/libavformat.so     \
           $$FFMPEG_LIB/libavutil.so       \
           $$FFMPEG_LIB/libswresample.so   \
           $$FFMPEG_LIB/libswscale.so      \
           $$FFMPEG_LIB/libpostproc.so
   
   # Default rules for deployment.
   qnx: target.path = /tmp/$${TARGET}/bin
   else: unix:!android: target.path = /opt/$${TARGET}/bin
   !isEmpty(target.path): INSTALLS += target
   ```

   - 头文件增加接口打印当前ffmepeg版本--printVersionFFmpeg

   ```c++
   // 头文件，增加例子
   #ifndef MAINWINDOW_H
   #define MAINWINDOW_H
   
   #include <QMainWindow>
   
   class MainWindow : public QMainWindow
   {
       Q_OBJECT
   
   public:
       MainWindow(QWidget *parent = nullptr);
       ~MainWindow();
   
       int printVersionFFmpeg();
   };
   #endif // MAINWINDOW_H
   ```

   - cpp文件中增加printVersionFFmpeg实现主题

   ```c++
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
   ```

   - 程序运行结果

   ```tex
   version is:3875172
   ```

   

   