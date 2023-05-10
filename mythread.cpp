#include "mythread.h"

MyThread::MyThread(QObject *parent) : QThread(parent)
{
    qsrand(time(nullptr));
    mode = FMODE;
    delayms = 1000*1000;
}

void MyThread::stopMyThead()
{
    stopFlags = 0;
}

void MyThread::changeMode(MyThread::GMode mode)
{
    if(mode == this->mode)
    {
        return;
    }
    switch (mode) {
    case FMODE:
        delayms = 2000*2000;

    case MMODE:
        delayms = 1500*1000;

    case HMODE:
        delayms = 1000* 900;

    case HENTAIMODE:
        delayms = 1000*800;
        break;
    }
}

void MyThread::run()
{
    stopFlags = 1;
    int curindex = 0;
    int index = 0;
    while(stopFlags)
    {
        index = qrand() % 9;
        if(index != curindex)
        {
            emit myChangeIndex(index);
            curindex = index;
        }
        usleep(delayms);
    }
}
