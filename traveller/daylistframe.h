#ifndef DAYLISTFRAME_H
#define DAYLISTFRAME_H

#include <QFrame>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QScrollBar>

class DayListFrame : public QFrame
{
    Q_OBJECT
public:
    DayListFrame();
    ~DayListFrame();
    QScrollArea* scroll;
    QWidget* listf;
    QHBoxLayout* lay;
    QVBoxLayout* mainLay;
};

#endif // DAYLISTFRAME_H
