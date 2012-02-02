#ifndef HELLOSARKAR_H
#define HELLOSARKAR_H

#include "history.h"
#include <QtGui>
#include <QtNetwork/QNetworkReply>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

QT_BEGIN_NAMESPACE
class QMenu;
class QPushButton;
class QLabel;
class QLineEdit;
class QPlainTextEdit;
class QDateTime;
class QAction;
class QActionGroup;
class QSqlDatabase;
class QSqlError;
class QSqlQuery;
QT_END_NAMESPACE



class hellosarkar : public QMainWindow
{
    Q_OBJECT
public:
    enum ScreenOrientation {
        ScreenOrientationLockPortrait,
        ScreenOrientationLockLandscape,
        ScreenOrientationAuto
    };

    explicit hellosarkar(QWidget *parent = 0);
    virtual ~hellosarkar();

    void setOrientation(ScreenOrientation orientation);
    void showExpanded();

    QString distList[75];
    int distCode[75];

    QString compList[999];
    QString compCode[999];

    QWidget *mainWidget;
    QWidget *topMenuBar;
    QMenu *hsMenu;
    QAction *actSettings;
    QAction *actHistory;
    QAction *actAbout;
    QAction *actAboutQt;

    QFormLayout *frmLayout;
    QVBoxLayout *vbLayout;
    QLabel *lblComplain;

    QLineEdit *leName;
    QComboBox *cboCompType;
    QComboBox *cboDistrict;
    QLineEdit *leDetailedAdd;
    QLineEdit *leComplain;
    QPlainTextEdit *ptComplain;
    QDateTimeEdit *dtDate;

    QDialogButtonBox *buttonBox;
    QPushButton *btnSubmit;
    QPushButton *btnCancel;

    QString dbLocation;
    QString compPostURLString;

    QNetworkAccessManager* ntManager;
    QNetworkRequest ntCurrentRequest;
    QNetworkReply* ntCurrentReply;

    QString osVersion;
    QString errString;

    void setUpVariables();
    void createGUI();
    void addDistricts();
    void addComplainTypes();
    int getMaxID();
    QUrl compPostURL;
    bool validatefields();

    QSqlDatabase db;//dbLocation

signals:

public slots:
    void createActions();
    void createMenus();
    void submitComplain();
    void networkRequestFinished(QNetworkReply*);
    void networkReplyError();
    void serverReply();
    void saveToDb(QString remoteCode);
    void showAbout();
    void showHistory();
    void showSettings();
    void showAboutQt();
    void clearForm();
};

#endif // HELLOSARKAR_H
