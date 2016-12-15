#ifndef EVENTITEMFRAME_H
#define EVENTITEMFRAME_H

#include <QFrame>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QIcon>
#include <QDebug>
#include <QMargins>
#include "ttextlabel.h"
#include "staticdata.h"
#include "tbutton.h"

class EventItemFrame : public QFrame
{
    Q_OBJECT
private:
    int tripid;
    int dayid;
    int cityid;
    int eventid;
    QString tcolor;
public:
    EventItemFrame(int tid,int did,int cid,int eid,QString tc);
    ~EventItemFrame();
    QVBoxLayout* infolay;
    QHBoxLayout* lay;
    TTextLabel* event;
    TTextLabel* transport;
    TButton* deleteb;
    QHash<QString,QString> style;
    QWidget* info;
    void changeColor(QString tc);
protected:
    void mouseDoubleClickEvent(QMouseEvent* e) Q_DECL_OVERRIDE;
    void enterEvent(QEvent *event) Q_DECL_OVERRIDE;
    void leaveEvent(QEvent *event) Q_DECL_OVERRIDE;
signals:
    void eventFrameDoubleClickedSig(int ,int ,int);
    void deleteEventClickedSig(int, int, int);
private slots:
    void deleteClickedSlot(bool c);
};

#endif // EVENTITEMFRAME_H
