#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
//#include <QtWebView>
#include <QGraphicsView>
#include <QSqlError>
#include <QSqlDatabase>
#include <QTimer>
#include <QNetworkReply>
#include "recorddialog.h"
#include "querydialog.h"
#include "editdialog.h"


class QWebChannel;
namespace Ui {
class MainWindow;
}

class PreferencesDialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent, QString nmeaFilePath1, QString dbFilePath1);
    ~MainWindow();
    QString strE, strN, strH, filePathPublic, dbNamePublic;
    int met;
    int num;
    QTimer timer2;
    double EdegDec,NdegDec;

signals:
    void printMe();
    void dbIsOpen();

private:
    Ui::MainWindow *ui;
    recordDialog *my_recordDialog;
    queryDialog *my_queryDialog;
    PreferencesDialog *m_preferencesDialog;
    editDialog *my_editDialog;
    QWebChannel *m_channel;
    void geoCode(QString);
    void replyFinished(QNetworkReply);
    void loadCoordinates();
    QString NMEAfilepath, dbFilePath, dbPath;
    void setMe(QString, QString);
    void openDB();
    QStringList getCategories();

    QSqlDatabase db;
    int insertRowToDB(QString x, QString y, QString h, QString adrs, QString cmnts, QString id);
    void insertMarker(QString id, QString x, QString y, QString h, QString adrs, QString cmnts, QString cat);
    void getSingleRow(int id);
    void sendToGMaps(QString command);


private slots:
    void getNMEAcoords();
    void recordDialogOpens();
    void queryDialogOpens();
    void onFindMeButtonClicked();
    void onSettingsClicked();
    void onExitClicked();
    void getData(QString E, QString N, QString H, QString adrs, QString cmnts, QString id);
    void getCatQuery(QStringList catList);
    void onInitZoomClicked(QString locationE, QString locationN);
    void getDBentries();
    void getEditedData(QString idStr, QString x, QString y, QString h, QString adr, QString com, QString cat);
    void editRowOfDB(QString idStr, QString x, QString y, QString h, QString adr, QString com, QString cat);

public slots:
    void populateJavaScriptWindowObject();
    Q_INVOKABLE void onEditClicked(QString idStr);
    Q_INVOKABLE void removeRowFromDB(QString j);
};

#endif // MAINWINDOW_H
