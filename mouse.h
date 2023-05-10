#ifndef MOUSE_H
#define MOUSE_H
#include <QWidget>
#include<QAbstractButton>

class Mouse : public QAbstractButton
{
    Q_OBJECT
public:
    explicit Mouse(QWidget *parent = nullptr);
    void setBackImage(QString path,int lvl = 0);

signals:

public slots:
    void flyUpImage();

private:
    QTimer *timer;
    QImage img;
    int upFlags;
    int yPos;
    int rate;

    void mousePressEvent(QMouseEvent *e);
    void paintEvent(QPaintEvent *);
};

#endif // MOUSE_H
