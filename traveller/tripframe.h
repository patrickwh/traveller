#ifndef TRIPFRAME_H
#define TRIPFRAME_H

#include <QFrame>
#include <QMargins>
#include <QVBoxLayout>
#include <QHash>
#include <QMouseEvent>
#include <QPoint>
#include "ttextlabel.h"
#include "commoncolor.h"
#include "tpalette.h"
#include "staticdata.h"
#include "stylesheetceator.h"

class TripFrame : public QFrame
{
    Q_OBJECT
private:
    QString tcolor;
public:
    TripFrame(int id,QString themeColor=StaticData::LIGHT_BLUE,QWidget* parent = nullptr);
    ~TripFrame();
    TTextLabel* date;
    TTextLabel* name;
    QVBoxLayout* layout;
    QHash<QString,QString> style;
    int id;
    void changeColor(QString color);
protected:
    void mouseDoubleClickEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void enterEvent(QEvent *event) Q_DECL_OVERRIDE;
    void leaveEvent(QEvent *event) Q_DECL_OVERRIDE;
signals:
    void tripClickedSig(int);
    void tripRightClickedSig(int,QPoint);
};

#endif // TRIPFRAME_H
