#ifndef ADDTRIPBUTTONFRAME_H
#define ADDTRIPBUTTONFRAME_H

#include <QFrame>
#include <QVBoxLayout>
#include <QHash>
#include "ttextlabel.h"
#include "staticdata.h"
#include "stylesheetceator.h"

class AddTripButtonFrame : public QFrame
{
    Q_OBJECT
public:
    AddTripButtonFrame(QWidget* parent = nullptr);
    ~AddTripButtonFrame();
    QHash<QString,QString> style;
protected:
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
signals:
    void addTripFrameClickedSig();
};

#endif // ADDTRIPBUTTONFRAME_H
