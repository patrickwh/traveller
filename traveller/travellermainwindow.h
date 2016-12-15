#ifndef TRAVELLERMAINWINDOW_H
#define TRAVELLERMAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QFrame>
#include <QLayout>
#include <QDesktopWidget>
#include <QWidget>
#include <QVBoxLayout>
#include "welcomeframe.h"
#include "addnewtripframe.h"
#include "staticdata.h"

namespace Ui {
class TravellerMainWindow;
}

class TravellerMainWindow : public QMainWindow
{
    Q_OBJECT
    // The Q_OBJECT macro is expanded by the preprocessor to declare
    // several member functions that are implemented by the moc;

public:
    explicit TravellerMainWindow(QWidget *parent = 0);
    ~TravellerMainWindow();
    void initialization();
    Ui::TravellerMainWindow *ui;
    QTabWidget *tabPane;
    WelcomeFrame *welconf;
    AddNewTripFrame *addnewf;

private:

signals:
    void getCountryListSig();
    void getCityListSig(QString country,int id);
    void registerComboGroupSig(TComboWithAddField* combo);
};

#endif // TRAVELLERMAINWINDOW_H
