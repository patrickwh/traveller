#include <QApplication>
#include "travellermodel.h"
#include "travellermainwindow.h"
#include "travellercontroller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TravellerModel* model = new TravellerModel();
    TravellerMainWindow* view = new TravellerMainWindow();
    TravellerController* controller= new TravellerController(model,view);
    controller->initialization();
    view->initialization();  
    view->show();
    return a.exec();
}
