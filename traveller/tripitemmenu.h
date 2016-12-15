#ifndef TRIPITEMMENU_H
#define TRIPITEMMENU_H

#include <QMenu>
#include <QAction>
#include <QHash>
#include <QIcon>
#include "stylesheetceator.h"
#include "staticdata.h"


class TripItemMenu : public QMenu
{
    Q_OBJECT
public:
    TripItemMenu(QWidget *parent = Q_NULLPTR);
    QHash<QString,QString> style;
    QAction* editAct;
    QAction* deleteAct;

};

#endif // TRIPITEMMENU_H
