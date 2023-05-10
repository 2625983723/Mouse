#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QMediaPlayer>
#include<QMediaPlaylist>
#include<QLabel>
#include<QButtonGroup>
#include<mythread.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent*);
    void initMusic();
    void initgame();
    void start();
    void stop();
    void clearnMouse();
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

private slots:
    void on_actionaboutgame_triggered();

    void on_action_QT_triggered();

    void on_musicNext_triggered();

    void on_music1_triggered();

    void on_music2_triggered();

    void myChanegeMousePos(int pos);
    void changeTimer();
    void slotHandleBtn(int index);

    void on_actionstart_triggered();

    void on_actionstop_triggered();

    void on_actionreset_triggered();

    void on_actionexit_triggered();

    void on_actionfmode_triggered();

    void on_actionmmode_triggered();

    void on_actionhmode_triggered();

    void on_actionhentaimode_triggered();

private:
    Ui::MainWindow *ui;   
    QImage bgimg;
    int MusicIndex;
    QMediaPlayer player;
    QMediaPlaylist playlist;
    int curentIndex;
    int pressIndex;
    int currentLevel;
    QVector<QString> stringVector;
    QLabel*labelDown[9];
    QButtonGroup*btngrp;
    MyThread *myThread;
    QTimer *timer;

};

#endif // MAINWINDOW_H
