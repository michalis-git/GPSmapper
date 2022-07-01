#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include<QWebEnginePage>
#include<QTimer>
#include<QDir>
#include<QSqlQuery>
#include<QMessageBox>
#include <QWebChannel>
#include <QStringLiteral>
#include "preferencesdialog.h"

MainWindow::MainWindow(QWidget *parent, QString nmeaFilePath1, QString dbFilePath1) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
  ui->setupUi(this);

  //Opens the specified DB file after 3 seconds
  dbNamePublic = dbFilePath1;
  openDB();
  connect(&timer2, SIGNAL(timeout()), this, SLOT(getDBentries()));
  timer2.start(4000);

  //Opens and reads the specified NMEA file every 2 seconds
  filePathPublic = nmeaFilePath1;
  qDebug() << filePathPublic;
  QTimer *timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(getNMEAcoords()));
  timer->start(2000);

  //Operations of Buttons
  connect(ui->recordButton,   &QPushButton::clicked, this, &MainWindow::recordDialogOpens);
  connect(ui->queryButton,    &QPushButton::clicked, this, &MainWindow::queryDialogOpens);
  connect(ui->findMeButton,   &QPushButton::clicked, this, &MainWindow::onFindMeButtonClicked);
  connect(ui->settingsButton, &QPushButton::clicked, this, &MainWindow::onSettingsClicked);
  connect(ui->exitButton,     &QPushButton::clicked, this, &MainWindow::onExitClicked);
  //    connect(ui->webView->page(), SIGNAL(javaScriptWindowObjectCleared()),
  //               this, SLOT(populateJavaScriptWindowObject()));

  QWebEnginePage *page = ui->widget->page();
  populateJavaScriptWindowObject();
  page->load(QUrl(QUrl::fromLocalFile("/Users/mikeo/Developer/personal/mapper/resrcs/GoogleMapsWebView-1.html")));
//  page->load(QUrl(":/new/prefix1/GoogleMapsWebView-1.html"));
  connect(page, &QWebEnginePage::loadFinished, this, &MainWindow::populateJavaScriptWindowObject);

  num = -1;
}

void MainWindow::populateJavaScriptWindowObject() {
  qDebug() << "populateJavaScriptWindowObject";
  QWebEnginePage *page = ui->widget->page();
  m_channel = new QWebChannel(page);
  page->setWebChannel(m_channel);
  m_channel->registerObject(QString("JSobject"), this);
}

//Opens the DB file
void MainWindow::openDB() {
  // Find QSLite driver
  db = QSqlDatabase::addDatabase("QSQLITE");

  //    #ifdef Q_OS_WIN
  QString path = QDir::toNativeSeparators(dbNamePublic);
  db.setDatabaseName(path);
  //    #else
  // NOTE: File exists in the application private folder, in Symbian Qt implementation
  //    db.setDatabaseName("mapper_db_0113");
  //    #endif

  // Open databasee
  if (!db.open()) {
    QMessageBox::critical(this, tr("My Application"),
                          tr("Failed to open database"),
                          QMessageBox::Ok);
  } else {
    emit dbIsOpen();
  }
}

//Reads and gets ALL the rows of the DB file
void MainWindow::getDBentries() {
  int id, catNum = 0;
  QSqlQuery query(QString("SELECT ROWID from location order by ROWID DESC limit 1"));
  if (query.next())
    catNum = query.value(0).toInt();
  query.clear();

  QString locE,locN;
  for (id = 1; id <= catNum; id++) {
    query = QSqlQuery(QString("select * from location where id = %1").arg(id));
    if (query.first()) {
      QString locationID = query.value(0).toString();
      QString locationE = query.value(1).toString();
      QString locationN = query.value(2).toString();
      QString locationH = query.value(3).toString();
      QString locationAdrs = query.value(4).toString();
      QString locationCmnts = query.value(5).toString();
      QString locationCat = query.value(6).toString();
      insertMarker(locationID, locationE, locationN, locationH, locationAdrs, locationCmnts, locationCat);
      locE = locationE;
      locN = locationN;
    }
  }
  timer2.stop();
  onInitZoomClicked(locE,locN);
}

//Pans and Zooms the map on the last Point stored in the DB file
void MainWindow::onInitZoomClicked(QString locE, QString locN) {
  QString command = QString("InitZoom(%1,%2);").arg(locE).arg(locN);
  sendToGMaps(command);
}

//Pans the map on the user's location.
void MainWindow::onFindMeButtonClicked() {
  QString command = ("FindMe(" + strN + "," + strE + ");");
  sendToGMaps(command);
}

void MainWindow::onSettingsClicked() {
  m_preferencesDialog = new PreferencesDialog;
  m_preferencesDialog->show();
  m_preferencesDialog->activateWindow();
}

//Draws a marker on the map.
void MainWindow::insertMarker(QString id,
                              QString E, QString N, QString H,
                              QString adrs, QString cmnts, QString cat) {
  num++;
  QString catName;
  QString queryText = QString("SELECT * FROM category WHERE catID=%1;").arg(cat);
  QSqlQuery query(queryText);
  if (query.next())
    catName = query.value(1).toString();
  query.clear();

  QString xyStr = (E + ", " + N);
  QString cat1 = QString("Category: %1").arg(catName);
  QString command = QString("DrawMarker((%1),(%2),(%3),('%4'),('%5'),('%6'),('%7'),('%8'),(%9))")
                        .arg(E).arg(N).arg(id).arg(xyStr).arg(H).arg(adrs).arg(cmnts).arg(cat1).arg(num);
  sendToGMaps(command);
}

//Moves the user's marker on the map, according to the received coordinates (every 2 seconds).
void MainWindow::setMe(QString strN, QString strE) {
  QString command = "MoveMe(" + strN + "," + strE +");";
  sendToGMaps(command);
}

//Reads the NMEA file and gets the user's location.
void MainWindow::getNMEAcoords() {
  QFile data(filePathPublic);
  if (data.open(QFile::ReadOnly)) {
    QString str = data.readAll();
    QString strN1 = str.right(54);
    strN = strN1.left(9);
    QString strE1 = str.right(41);
    strE = strE1.left(9);
    QString strH1 = str.right(321);
    strH = strH1.left(5);
    QString strEmin = strE.right(7);
    QString strEdeg = strE1.left(2);
    QString strNmin = strN.right(7);
    QString strNdeg = strN1.left(2);
    double Edeg = strEdeg.toDouble();
    double Emin = strEmin.toDouble();
    double Ndeg = strNdeg.toDouble();
    double Nmin = strNmin.toDouble();
    EdegDec = Edeg + (Emin/60);
    NdegDec = Ndeg + (Nmin/60);
    strE = QString("%1").arg(EdegDec, 0, 'f', 8);
    strN = QString("%1").arg(NdegDec, 0, 'f', 8);

    ui->positionLineEdit->setText(strE + ", " + strN);
    setMe(strN, strE);

    data.close();
  }
}

//Creates the Record Dialog.
void MainWindow::recordDialogOpens()
{
  my_recordDialog = new recordDialog;
  QStringList strList = getCategories();
  my_recordDialog->getData(strN,strE,strH,strList);
  connect(my_recordDialog, SIGNAL(sendData(QString,QString,QString,QString,QString,QString)),
          this, SLOT(getData(QString,QString,QString,QString,QString,QString)));
  my_recordDialog->show();
  my_recordDialog->activateWindow();
}

//Creates the Query Dialog.
void MainWindow::queryDialogOpens() {
  my_queryDialog = new queryDialog;
  QStringList strList = getCategories();
  my_queryDialog->getData(strList);
  connect(my_queryDialog, SIGNAL(sendCatQuery(QStringList)),
          this, SLOT(getCatQuery(QStringList)));
  my_queryDialog->show();
  my_queryDialog->activateWindow();
}

//Creates Edit Dialog.
void MainWindow::onEditClicked(QString idStr) {
  my_editDialog = new editDialog;
  QSqlQuery query = QSqlQuery(QString("select * from location where id = %1").arg(idStr));
  if(query.first()) {
    QString x = query.value(1).toString();
    QString y = query.value(2).toString();
    QString h = query.value(3).toString();
    QString adr = query.value(4).toString();
    QString com = query.value(5).toString();
    QString cat = query.value(6).toString();
    QStringList strList = getCategories();
    my_editDialog->getData(idStr,x,y,h,adr,com,cat,strList);
  }

  connect(my_editDialog, SIGNAL(sendEditedData(QString,QString,QString,QString,QString,QString,QString)),
          this, SLOT(getEditedData(QString,QString,QString,QString,QString,QString,QString)));
  my_editDialog->show();
  my_editDialog->activateWindow();
  QString command1 = ("RemoveMarker('25');");
  sendToGMaps(command1);
}

//Gets the categories from the DB and sends them to the Dialogs.
QStringList MainWindow::getCategories() {
  qDebug() << "getCategories";
  int id, catNum = 0;
  QSqlQuery query(QString("SELECT ROWID from category order by ROWID DESC limit 1"));
  if (query.next()) {
    catNum = query.value(0).toInt();
  } else {
    qDebug() << query.result();
  }
  query.clear();

  QStringList strList;
  for (id = 1; id <= catNum; id++) {
    query = QSqlQuery(QString("select * from category where catID = %1").arg(id));
    if (query.first()) {
      QString catName = query.value(1).toString();
      strList.append(catName);
    }
  }
  return strList;
}

//Gets data from the Record Dialog.
void MainWindow::getData(QString E, QString N, QString H,
                         QString adrs, QString cmnts, QString id) {
  insertRowToDB(E,N,H,adrs,cmnts,id);
}

//Gets data from the Edit Dialog.
void MainWindow::getEditedData(QString idStr,
                               QString x, QString y, QString h,
                               QString adr, QString com, QString cat) {
  editRowOfDB(idStr, x,y,h,adr,com,cat);
  QString command = QString("RemoveMarker(%1);").arg(idStr);
  sendToGMaps(command);
  insertMarker(idStr, x,y,h,adr,com,cat);
}

//Gets the data from Query Dialog and makes a query to the DB.
void MainWindow::getCatQuery(QStringList catList) {
  num = -1;
  int listLength = catList.count();
  int i;

  QString catStr = "";
  for(i=0; i<listLength; i++) {
    catStr.append(QString("'%1',").arg(catList.value(i)));
  }
  catStr = catStr.left(catStr.length() - 1);

  QString command = QString("ClearMap()");
  sendToGMaps(command);

  QString queryText = QString("SELECT * FROM location AS L JOIN category AS C ON L.cat=C.catid WHERE C.name IN (%1);").arg(catStr);
  QSqlQuery query = QSqlQuery(queryText);
  while(query.next()) {
    QString id = query.value(0).toString();
    QString E = query.value(1).toString();
    QString N = query.value(2).toString();
    QString H = query.value(3).toString();
    QString adrs = query.value(4).toString();
    QString cmnts = query.value(5).toString();
    QString cat = query.value(6).toString();
    if (cat == "3")
      qDebug() << cat << E << N;

    insertMarker(id,E,N,H,adrs,cmnts,cat);
  }
  query.clear();
}

//Edits the specified row of the DB and updates the specified marker on the map.
void MainWindow::editRowOfDB(QString idStr, QString x, QString y, QString h, QString adr, QString com, QString cat) {
  if (db.isOpen()) {
    QSqlQuery query;
    QString queryText = QString("UPDATE location SET x = '%2', y = '%3', h = '%4', address ='%5',comments = '%6' WHERE id = '%1'")
                            .arg(idStr).arg(x).arg(y).arg(h).arg(adr).arg(com);
    qDebug() << "update: " << queryText;
    query.exec(queryText);
    query.clear();
  }
}

//Inserts a new row in the DB.
int MainWindow::insertRowToDB(QString E, QString N, QString H, QString adrs, QString cmnts, QString catID) {
  int newId = -1;
  bool ret = false;

  if (db.isOpen()) {
    // NULL = is the keyword for the autoincrement to generate next value
    QSqlQuery query;
    ret = query.exec(QString("insert into location values(NULL, '%1', '%2', %3, '%4', '%5', %6)")
                         .arg(E).arg(N).arg(H).arg(adrs).arg(cmnts).arg(catID));

    // Get database given autoincrement value
    if (ret) {
      newId = query.lastInsertId().toInt();
    }

  }
  QString idStr = QString::number(newId);
  insertMarker(idStr, E, N, H, adrs, cmnts, catID);
  return newId;
}

void MainWindow::removeRowFromDB(QString j) {
  if (db.isOpen()) {
    QSqlQuery query;
    QString queryText = QString("DELETE FROM location WHERE id = '%1'").arg(j);
    qDebug() << "delete: " << queryText;
    query.exec(queryText);
    query.clear();
  }
}

#include <QWebEngineSettings>

void MainWindow::sendToGMaps(QString command) {
  //  qDebug() << "command: " << command;
  QWebEngineView *webView = ui->widget;
  webView->settings()->setAttribute(QWebEngineSettings::JavascriptEnabled, true);
  webView->settings()->setAttribute(QWebEngineSettings::AutoLoadImages, true);
  webView->settings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);

  QWebEnginePage *page = webView->page();
  page->runJavaScript(command, [](const QVariant &result) {
    //    qDebug()  << "result: " << result.toString();
  });
}

void MainWindow::onExitClicked() {
  int ret = QMessageBox::warning(this, tr("My Application"),
                                 tr("Are you sure you want to exit?"),
                                 QMessageBox::Ok | QMessageBox::Cancel);

  if (ret == QMessageBox::Ok)
    this->close();

}

MainWindow::~MainWindow() {
  delete ui;
}
