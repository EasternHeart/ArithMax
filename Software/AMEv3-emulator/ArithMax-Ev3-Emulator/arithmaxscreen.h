#ifndef ARITHMAXSCREEN_H
#define ARITHMAXSCREEN_H

#include <QWidget>
#include <QQueue>

class QArithMaxScreen : public QWidget
{
    Q_OBJECT
public:
    explicit QArithMaxScreen(QWidget *parent = 0);
    unsigned char ScreenData[12][31]; //96x31x1 bit
    //int lastkey;
    //int aKeyPressed;
    QQueue<int> keys;
    bool keysLocked;
    
signals:
    
protected:
    void paintEvent ( QPaintEvent * event );
    void keyPressEvent ( QKeyEvent * event );
    void keyReleaseEvent(QKeyEvent *);
public slots:

};

#endif // ARITHMAXSCREEN_H
