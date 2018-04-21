#include <QtWidgets>

#include "window.hpp"
#include <qtmosquitto.hpp>

int main(int argc, char** argv)
{
  QApplication app(argc, argv);
  QtMosquittoApp mapp;
  
  Window win;
  win.show();
  win.doConnect();
 
  return app.exec();
}
