#include "welcomeDialog.h"
#include <QApplication>
#include <QSettings>

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  QSettings settings;
  QString nmeaPath = settings.value("NmeaPath").toString();
  QString dbPath   = settings.value("DbPath").toString();
  MainWindow mainWindow(0, nmeaPath, dbPath);

  WelcomeDialog w;
  if (nmeaPath.isEmpty() || dbPath.isEmpty()) {
    w.show();
  } else {
    mainWindow.show();
    mainWindow.activateWindow();
  }

  return a.exec();
}
