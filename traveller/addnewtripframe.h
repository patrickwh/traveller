#ifndef ADDNEWTRIPFRAME_H
#define ADDNEWTRIPFRAME_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QFont>
#include <QPalette>
#include "commoncolor.h"
#include "homeinfopane.h"
#include "tbutton.h"
#include "newdaypane.h"
#include <QScrollArea>

class AddNewTripFrame : public QWidget
{
    Q_OBJECT
public:
    explicit AddNewTripFrame(QWidget *parent = 0);
    ~AddNewTripFrame();
    HomeInfoPane* homeInfoPane;
    TButton* addNewDayB;
    TButton* saveAllB;
    TButton* cancel;

signals:

public slots:
};

#endif // ADDNEWTRIPFRAME_H
