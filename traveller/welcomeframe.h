#ifndef WELCOMEFRAME_H
#define WELCOMEFRAME_H

#include <QWidget>
#include <QGridLayout>
#include "tripframe.h"
#include "tpalette.h"
#include "staticdata.h"

class WelcomeFrame : public QWidget
{
    Q_OBJECT
public:
    explicit WelcomeFrame(QWidget *parent = 0);
    QGridLayout* layout;
    int m;

signals:

public slots:
};

#endif // WELCOMEFRAME_H
