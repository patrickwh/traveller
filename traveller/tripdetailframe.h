#ifndef TRIPDETAILFRAME_H
#define TRIPDETAILFRAME_H

#include <QFrame>
#include <QVBoxLayout>
#include "triptitleframe.h"
#include "daylistframe.h"


class TripDetailFrame : public QFrame
{
    Q_OBJECT
public:
    TripDetailFrame(QString color);
    ~TripDetailFrame();
    TripTitleFrame* titlef;
    DayListFrame* listf;
    QVBoxLayout* lay;
};

#endif // TRIPDETAILFRAME_H
