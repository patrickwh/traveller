#ifndef TCOMBOWITHCOST_H
#define TCOMBOWITHCOST_H

#include <QWidget>
#include <QGridLayout>
#include <QDoubleValidator>
#include "ttextlabel.h"
#include "tcombobox.h"
#include "tlineedit.h"


class TComboWithCost : public QWidget
{
    Q_OBJECT
public:
    explicit TComboWithCost(int type = 0);
    TComboBox* type;
    TLineEdit* name;
    TComboBox* currency;
    TLineEdit* amount;
    QDoubleValidator* costValildator;

    const static int TYPE_DEST = 0;
    const static int TYPE_TRANS = 1;

signals:

public slots:
};

#endif // TCOMBOWITHCOST_H
