#ifndef ADDNEWTRIPWINDOW_H
#define ADDNEWTRIPWINDOW_H

#include <QDialog>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QDesktopWidget>
#include <QApplication>
#include "homeinfopane.h"
#include "staticdata.h"
#include "stylesheetceator.h"
#include "tbutton.h"

class AddNewTripWindow : public QDialog
{
    Q_OBJECT
public:
    AddNewTripWindow(QWidget* parent,int type = StaticData::ADD_NEW_WINDOW);
    ~AddNewTripWindow();
    QGridLayout* glay;
    QVBoxLayout* lay;
    HomeInfoPane* hip;
    TButton* save;
    TButton* cancle;
    QWidget* buttonGroup;
    QWidget* nameAndColor;
    TComboBox* colorCombo;
    TTextLabel* namel;
    TTextLabel* colorl;
    TLineEdit* name;
    QGridLayout* nameAndColorLay;
    QHash<QString,QString> style;

private:
    int type;
signals:
    void windowClosed(int,int);
private slots:
    void saveClickedSlot();
    void cancleClickedSlot();
    void closePermittedSlot();
};

#endif // ADDNEWTRIPWINDOW_H
