#ifndef ADDNEWEVENTWINDOW_H
#define ADDNEWEVENTWINDOW_H

#include <QDialog>
#include <QDesktopWidget>
#include <QApplication>
#include "staticdata.h"
#include "stylesheetceator.h"
#include "tcombowithcost.h"
#include "tbutton.h"

class AddNewEventWindow:public QDialog
{
    Q_OBJECT
private:
    int type;
public:
    AddNewEventWindow(QWidget* parent,int type = AddNewEventWindow::TYPE_ADD);
    ~AddNewEventWindow();
    TComboWithCost* event;
    TComboWithCost* transport;
    QVBoxLayout* lay;
    QGridLayout* glay;
    QHash<QString,QString> style;
    TButton* save;
    TButton* cancle;
    QWidget* buttonGroup;
    const static int TYPE_ADD = 0;
    const static int TYPE_UPDATE = 1;
    const static int SAVE_AND_EXIT = 0;
    const static int CANCLE_AND_EXIT = 1;
signals:
    void windowClosedSig(int,int);
public slots:
    void saveAndExitSlot();
    void cancleAndExitSlot();
    void closePermittedSlot();
};

#endif // ADDNEWEVENTWINDOW_H
