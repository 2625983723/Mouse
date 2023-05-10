#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMessageBox>
#include <QPainter>
#include<QTimer>
#include<QSound>
#include <QMouseEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    bgimg.load(":/new/images/000.jpg");
    setFixedSize(550,500);
    initMusic();
    initgame();
    start();
    stop();

    myThread = new MyThread(this);
    connect(myThread,&MyThread::myChangeIndex,
            this,&MainWindow::myChanegeMousePos);
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),
            this,SLOT(changeTimer()));
}

MainWindow::~MainWindow()
{
    delete ui;
    myThread->stopMyThead();
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QRect source(0,0,bgimg.width(),bgimg.height());
    QRect target(0,0,width(),height());
    painter.drawImage(target,bgimg,source);
}

void MainWindow::on_actionaboutgame_triggered()
{
    QMessageBox::about(this,"关于","此游戏出自一位帅哥的神手");
}

void MainWindow::initgame()
{
    curentIndex = 0;
    pressIndex = curentIndex + 1;
    currentLevel = 0;

    stringVector.append(":/new/images/mouse1.png");
    stringVector.append(":/new/images/mouse2.png");
    stringVector.append(":/new/images/mouse3.png");
    stringVector.append(":/new/images/mouse4.png");
    stringVector.append(":/new/images/u03.png");

    ui->ptn0->setGeometry(91, 64, 85, 80);
    ui->ptn1->setGeometry(220, 61, 85, 80);
    ui->ptn2->setGeometry(355, 67, 85, 80);
    ui->ptn3->setGeometry(72, 160, 85, 80);
    ui->ptn4->setGeometry(221, 160, 85, 80);
    ui->ptn5->setGeometry(358, 158, 85, 80);
    ui->ptn6->setGeometry(69, 270, 85, 80);
    ui->ptn7->setGeometry(223, 265, 85, 80);
    ui->ptn8->setGeometry(372, 265, 85, 80);
    btngrp = new QButtonGroup(this);
    btngrp->addButton(ui->ptn0,0);
    btngrp->addButton(ui->ptn1,1);
    btngrp->addButton(ui->ptn2,2);
    btngrp->addButton(ui->ptn3,3);
    btngrp->addButton(ui->ptn4,4);
    btngrp->addButton(ui->ptn5,5);
    btngrp->addButton(ui->ptn6,6);
    btngrp->addButton(ui->ptn7,7);
    btngrp->addButton(ui->ptn8,8);
    connect(btngrp,SIGNAL(buttonClicked(int)),
            this,SLOT(slotHandleBtn(int)));
    QStringList downList;
    downList.append(":/new/images/1.png");
    downList.append(":/new/images/1-2.png");
    downList.append(":/new/images/1-3.png");
    downList.append(":/new/images/2-1.png");
    downList.append(":/new/images/2-2.png");
    downList.append(":/new/images/2-3.png");
    downList.append(":/new/images/3-1.png");
    downList.append(":/new/images/3-2.png");
    downList.append(":/new/images/3-3.png");
    for(int i = 0; i < 9; i++)
    {
        labelDown[i] = new QLabel(this);
        labelDown[i]->setPixmap(QPixmap(downList[i]));
        labelDown[i]->setScaledContents(true);
    }

    {
        labelDown[0]->setGeometry(89,180,95,45);
        labelDown[1]->setGeometry(220,179,95,45);
        labelDown[2]->setGeometry(354,183,95,35);
        labelDown[3]->setGeometry(72,277,95,45);
        labelDown[4]->setGeometry(218,277,95,45);
        labelDown[5]->setGeometry(358,276,95,45);
        labelDown[6]->setGeometry(65,378,95,45);
        labelDown[7]->setGeometry(221,384,95,45);
        labelDown[8]->setGeometry(367,383,95,45);
    }
}

void MainWindow::start()
{
    ui->actionstart->setEnabled(false);
    ui->actionstop->setEnabled(true);
    ui->actionfmode->setEnabled(true);
     ui->actionmmode->setEnabled(false);
      ui->actionhmode->setEnabled(false);
       ui->actionhentaimode->setEnabled(false);
       ui->centralWidget->setEnabled(true);
}

void MainWindow::stop()
{
    if(ui->lcdNumber_2->intValue() == 0)
    {
        ui->actionstart->setEnabled(true);
    }
    ui->actionstop->setEnabled(false);
    ui->actionfmode->setEnabled(true);
     ui->actionmmode->setEnabled(true);
      ui->actionhmode->setEnabled(true);
       ui->actionhentaimode->setEnabled(true);
       ui->centralWidget->setEnabled(false);
}

void MainWindow::clearnMouse()
{
    Mouse *curMouse = dynamic_cast<Mouse *>(btngrp->button(curentIndex));
    if(!curMouse)
    {
        return;
    }
    curMouse->setBackImage(" ");
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    e->accept();
    if(curentIndex == pressIndex) {
        QSound::play(":/new/audio/hit.wav");
        QCursor my(QPixmap(":/new/images/hitOn.png"),0, 30);
        ui->centralWidget->setCursor(my);
        clearnMouse();
        curentIndex = 10;
    } else {
        QSound::play(":/new/audio/nohit.wav");
        QCursor my(QPixmap(":/new/images/bt002.png"), 0, 30);
        ui->centralWidget->setCursor(my);
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    e->accept();
    QCursor my(QPixmap(":/new/images/bt001.png"), 0, 30);
    ui->centralWidget->setCursor(my);
}


void MainWindow::on_action_QT_triggered()
{
    QMessageBox::aboutQt(this);
}

void MainWindow::initMusic()
{
    MusicIndex = 0;
    playlist.addMedia(QUrl("C:/Users/Ehcsep/Desktop/QT_Project/Mouse/audio/music1.mp3"));
    playlist.addMedia(QUrl("C:/Users/Ehcsep/Desktop/QT_Project/Mouse/audio/music2.mp3"));
    playlist.setCurrentIndex(MusicIndex);
    player.setPlaylist(&playlist);
    player.setVolume(30);
    player.play();
    playlist.setPlaybackMode(QMediaPlaylist::Loop);
}

void MainWindow::on_musicNext_triggered()
{
    playlist.next();
}

void MainWindow::on_music1_triggered()
{
    MusicIndex = 0;
    playlist.setCurrentIndex(MusicIndex);
}

void MainWindow::on_music2_triggered()
{
    MusicIndex = 0;
    playlist.setCurrentIndex(MusicIndex+1);
}

void MainWindow::myChanegeMousePos(int pos)
{
    Mouse *curMouse = dynamic_cast<Mouse *>(btngrp->button(pos));
    if(!curMouse)
    {
        return;
    }
    clearnMouse();
    int mou = 0;
    mou = qrand() % 5;
    curMouse->setBackImage(stringVector.at(mou),currentLevel);
    curentIndex = pos;
}

void MainWindow::changeTimer()
{
    int val = ui->lcdNumber->intValue();
    if(val == 0)
    {
       QSound::play(":/new/audio/lowend.wav");
       QMessageBox::information(this,"游戏结束",
                                QString("你的分数为%1").arg(ui->lcdNumber_2->intValue()));
       on_actionstop_triggered();
       ui->statusBar->showMessage("游戏结束");
       return;
    }
    ui->lcdNumber->display(--val);
}

void MainWindow::slotHandleBtn(int index)
{
   pressIndex = index;
   if(curentIndex > 8 || curentIndex<0) return;
   if(index == curentIndex)
   {
       int val = ui->lcdNumber_2->intValue();
       ui->lcdNumber_2->display(++val);
   }
}

void MainWindow::on_actionstart_triggered()
{
    timer->start(1000);
    myThread->start();
    start();
    ui->statusBar->showMessage("开始");

}

void MainWindow::on_actionstop_triggered()
{
    clearnMouse();
    curentIndex = 0;
    pressIndex = curentIndex + 1;
    timer->stop();
    myThread->stopMyThead();
    stop();
    update();
    ui->statusBar->showMessage("游戏结束");
}

void MainWindow::on_actionreset_triggered()
{
    if(myThread->isRunning() || timer->isActive())
    {
        myThread->stopMyThead();
        timer->stop();
    }
    ui->lcdNumber->display(30);
    ui->lcdNumber_2->display(0);
    stop();
    clearnMouse();
    ui->statusBar->showMessage("重置");
}

void MainWindow::on_actionexit_triggered()
{
    on_actionstop_triggered();
    if(myThread->isRunning()) myThread->terminate();
    if(timer->isActive()) timer->stop();
    this->close();
}

void MainWindow::on_actionfmode_triggered()
{
        myThread->changeMode(MyThread::FMODE);
        currentLevel = MyThread::FMODE;
        QMessageBox::information(this, "等级", "初级模式");
}

void MainWindow::on_actionmmode_triggered()
{
    myThread->changeMode(MyThread::MMODE);
    currentLevel = MyThread::MMODE;
    QMessageBox::information(this, "等级", "普通模式");
}

void MainWindow::on_actionhmode_triggered()
{
    myThread->changeMode(MyThread::HMODE);
    currentLevel = MyThread::HMODE;
    QMessageBox::information(this, "等级", "困难模式");
}

void MainWindow::on_actionhentaimode_triggered()
{
    myThread->changeMode(MyThread::HENTAIMODE);
    currentLevel = MyThread::HENTAIMODE;
    QMessageBox::information(this, "等级", "极难模式");
}
