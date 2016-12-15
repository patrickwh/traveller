#ifndef ADDNEWCITYWINDOW_H
#define ADDNEWCITYWINDOW_H

#include <QDialog>
#include <QDesktopWidget>
#include <QApplication>
#include "staticdata.h"
#include "stylesheetceator.h"
#include "tcombowithcost.h"
#include "tbutton.h"
#include "tcombowithaddfield.h"

class AddNewCityWindow : public QDialog
{
    Q_OBJECT
private:
    int type;
public:
    AddNewCityWindow(QWidget* parent,int type = AddNewCityWindow::TYPE_ADD);
    QHash<QString,QString> style;
    TButton* save;
    TButton* cancle;
    QVBoxLayout* lay;
    QGridLayout* glay;
    QWidget* buttonGroup;
    TComboWithAddField* country;
    TComboWithAddField* city;
    const static int SAVE_AND_EXIT = 1;
    const static int CANCLE_AND_EXIT = 2;
    const static int TYPE_ADD = 3;
    const static int TYPE_UPDATE = 4;
    int getType();
signals:
    void closeAddCityWindowSig(int,int);
private slots:
    void saveAndExitSlot();
    void cancleAndExitSlot();
public slots:
    void windowClosePermittedSlot();
};

#endif // ADDNEWCITYWINDOW_H
