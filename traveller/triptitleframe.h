#ifndef TRIPTITLEFRAME_H
#define TRIPTITLEFRAME_H

#include <QFrame>
#include <QGridLayout>
#include <QHash>
#include "ttextlabel.h"
#include "stylesheetceator.h"
#include "tbutton.h"

class TripTitleFrame : public QFrame
{
    Q_OBJECT
public:
    TripTitleFrame(QString color);
    ~TripTitleFrame();
    QGridLayout* lay;
    TTextLabel* name;
    TTextLabel* namel;
    TTextLabel* from;
    TTextLabel* froml;
    TTextLabel* date;
    TTextLabel* datel;
    TButton* returnBack;
    QHash<QString,QString> style;
    void changeColor(QString color);
signals:
    void tripTitleFrameDoubleClickedSig();
protected:
    void mouseDoubleClickEvent(QMouseEvent *event)  Q_DECL_OVERRIDE;
};

#endif // TRIPTITLEFRAME_H
