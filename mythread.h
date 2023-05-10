#ifndef MYTHREAD_H
#define MYTHREAD_H
#include <QObject>
#include <QThread>

class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(QObject *parent = nullptr);
    enum GMode
    {
        FMODE = 1,
        MMODE = 2,
        HMODE = 3,
        HENTAIMODE = 4

    };
    void stopMyThead();
    void changeMode(GMode mode);


signals:
void myChangeIndex(int index);

private:
   void  run() ;
   int stopFlags;
   GMode mode;
   int delayms;

public slots:

};

#endif // MYTHREAD_H
