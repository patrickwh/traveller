#ifndef TCOMBOWITHADDFIELD_H
#define TCOMBOWITHADDFIELD_H

#include <QWidget>
#include "ttextlabel.h"
#include "tcombobox.h"
#include "tlineedit.h"
#include "tbutton.h"
#include <QGridLayout>
#include <QMessageBox>
#include "commoncolor.h"

class TComboWithAddField : public QWidget
{
    Q_OBJECT

private:

public:
    int id;
    TComboWithAddField(QString text,QString hint,int id);
    TComboBox* combo;
    TLineEdit* edit;
    TButton* add;
signals:
    void addCountrySigToController(QString);
    void addCitySigToCintroller(QString,int);
    void getCitySig(QString,int);
public slots:
    void addButtonClicked();
    void comboChangedSlot(QString str);
};

#endif // TCOMBOWITHADDFIELD_H
