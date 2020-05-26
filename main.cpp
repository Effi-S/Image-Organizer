#include "mainwindow.h"
#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    try {
        QApplication a(argc, argv);
        MainWindow w;
        w.show();
          return a.exec();

    } catch (QException &e) {
        std::cout<<"Qt Exception:" <<e.what() << std::endl;

    } catch (std::exception & e ){
         std::cout << "Error: " << e.what() <<std::endl;
     } catch (...) {

     std::cout << "!!! unknown error !!!" << std::endl;
     }

 return 0;
}
