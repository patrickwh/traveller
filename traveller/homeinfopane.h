#ifndef HOMEINFOPANE_H
#define HOMEINFOPANE_H

#include <QVBoxLayout>
#include <QFrame>
#include "ttextlabel.h"
#include <QCalendarWidget>
#include "tcombowithaddfield.h"

class HomeInfoPane : public QFrame
{
    Q_OBJECT
public:
    explicit HomeInfoPane(QWidget *parent = 0);
    QCalendarWidget* startDatePicker;
    TComboWithAddField* country;
    TComboWithAddField* city;

signals:

public slots:

};

#endif // HOMEINFOPANE_H
