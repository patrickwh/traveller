#ifndef DAYTITLEFRAME_H
#define DAYTITLEFRAME_H

#include <QFrame>
#include <QHBoxLayout>
#include "tbutton.h"
#include "ttextlabel.h"

class DayTitleFrame : public QFrame
{
    Q_OBJECT
private:
    int tripid;
    int dayid;
public:
    DayTitleFrame(int tid,int did,QWidget *parent = 0);
    TTextLabel* date;
    TButton* deleteb;
    QHBoxLayout* lay;
    QHash<QString,QString> style;
signals:
    void dayDeleteClickedSig(int);
protected:
    void enterEvent(QEvent* event) Q_DECL_OVERRIDE;
    void leaveEvent(QEvent* event) Q_DECL_OVERRIDE;
private slots:
    void deleteClickedSlot(bool c);
};

#endif // DAYTITLEFRAME_H
