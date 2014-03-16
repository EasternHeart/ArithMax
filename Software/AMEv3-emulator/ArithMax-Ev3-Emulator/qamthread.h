#ifndef QAMTHREAD_H
#define QAMTHREAD_H

#include <QThread>
#include "arithmaxscreen.h"

class QAMThread : public QThread
{
    Q_OBJECT
public:
    explicit QAMThread(QArithMaxScreen *s, QObject *parent = 0);
    
protected:
    void run();

signals:
    void UpdateScreen();
    
public slots:

public:
    QArithMaxScreen *screen;
    void US();
};

extern QAMThread *amtinst;
extern "C" {extern unsigned char *ScreenBuffer; }

#endif // QAMTHREAD_H
