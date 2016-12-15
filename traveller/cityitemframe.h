#ifndef CITYITEMFRAME_H
#define CITYITEMFRAME_H

#include <QWidget>
#include <QVBoxLayout>
#include <QMouseEvent>
#include "ttextlabel.h"
#include "staticdata.h"
#include "citytitleframe.h"
#include "eventitemframe.h"

class CityItemFrame : public QWidget
{
    Q_OBJECT

private:
    int tripid;
    int dayid;
    int cityid;
    QString tcolor;
public:
    explicit CityItemFrame(int tid,int did,int cid,QString tc, QWidget *parent = 0);
    ~CityItemFrame();
    CityTitleFrame* title;
    QVBoxLayout* lay;
    QWidget* events;
    QVBoxLayout* eventsLay;
    void changeColor(QString tc);
public slots:
};

#endif // CITYITEMFRAME_H
