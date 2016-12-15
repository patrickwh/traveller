#ifndef CITYTITLEFRAME_H
#define CITYTITLEFRAME_H

#include <QFrame>
#include <QHBoxLayout>
#include <QEvent>
#include "ttextlabel.h"
#include "tbutton.h"
#include "stylesheetceator.h"


class CityTitleFrame : public QFrame
{
    Q_OBJECT
private:
    int tripid;
    int dayid;
    int cityid;
    QString tcolor;
public:
    explicit CityTitleFrame(int tid,int did,int cid,QString tc, QWidget *parent = 0);
    TTextLabel* cityName;
    TButton* deleteb;
    QHBoxLayout* lay;
    QHash<QString,QString> style;
    void changeColor(QString tc);
signals:
    void cityItemDeleteClickedSig(int,int);
    void cityItemFrameDoubleClickedSig(int,int);
public slots:

protected:
    void enterEvent(QEvent* event) Q_DECL_OVERRIDE;
    void leaveEvent(QEvent* event) Q_DECL_OVERRIDE;
    void mouseDoubleClickEvent(QMouseEvent* e) Q_DECL_OVERRIDE;
private slots:
    void deleteClickedSlot(bool c);
};

#endif // CITYTITLEFRAME_H
