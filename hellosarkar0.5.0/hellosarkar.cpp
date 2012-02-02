#include "hellosarkar.h"

#include <QtNetwork/QHttp>
#include <QUrl>
#include <QString>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
//#include <iostream>
#include <QtNetwork/QNetworkAccessManager>
#include <QObject>
//#include <QSysInfo>

hellosarkar::hellosarkar(QWidget *parent) :
    QMainWindow(parent)
{
    setUpVariables();
    createGUI();
}

hellosarkar::~hellosarkar()
{
}

void hellosarkar::setUpVariables()
{
    #ifdef Q_OS_SYMBIAN
        dbLocation = "E:/hellosarkar/HelloSarkar.db";
        osVersion = "Symbian";
    #elif defined(Q_WS_MAEMO_5) || defined(Q_WS_MAEMO_6)
        dbLocation = "/home/user/.hellosarkar/HelloSarkar.db";
        osVersion = "Maemo/Meego";
    #else
        dbLocation = "C:/myqt/hellosarkar/hellosarkar0.4.0/HelloSarkar.db";
        osVersion = "Qt/Others";
    #endif

    compPostURLString = "http://apps.mobilenepal.net/hellosarkar/public/complain/receive";
    compPostURL = QUrl(compPostURLString);//change the server
    db = QSqlDatabase::addDatabase("QSQLITE");//dbLocation
    db.setDatabaseName(dbLocation);
    errString = "";

//    if(!db.open())
//    {
//        QMessageBox::information(this,"","Unable to establish database connection");
//    }
//    else
//    {
//        QSqlQuery query;
//        if(query.exec("CREATE TABLE complains(complain_id_local INT PRIMARY KEY, date TEXT, name TEXT, complain_type TEXT, district NUMERIC, address TEXT, complain_text TEXT, mobile_info TEXT, mobile_number TEXT, gps TEXT, complain_status TEXT, complain_id_remote TEXT)"))
//        {
//            QMessageBox::information(this, "","Database table created.");
//        }
//        else
//        {
//            QMessageBox::information(this, "","Database not table created.");
//        }
//    }
}

void hellosarkar::setOrientation(ScreenOrientation orientation)
{
#if defined(Q_OS_SYMBIAN)
    // If the version of Qt on the device is < 4.7.2, that attribute won't work
    if (orientation != ScreenOrientationAuto) {
        const QStringList v = QString::fromAscii(qVersion()).split(QLatin1Char('.'));
        if (v.count() == 3 && (v.at(0).toInt() << 16 | v.at(1).toInt() << 8 | v.at(2).toInt()) < 0x040702) {
            qWarning("Screen orientation locking only supported with Qt 4.7.2 and above");
            return;
        }
    }
#endif // Q_OS_SYMBIAN

    Qt::WidgetAttribute attribute;
    switch (orientation) {
#if QT_VERSION < 0x040702
    // Qt < 4.7.2 does not yet have the Qt::WA_*Orientation attributes
    case ScreenOrientationLockPortrait:
        attribute = static_cast<Qt::WidgetAttribute>(128);
        break;
    case ScreenOrientationLockLandscape:
        attribute = static_cast<Qt::WidgetAttribute>(129);
        break;
    default:
    case ScreenOrientationAuto:
        attribute = static_cast<Qt::WidgetAttribute>(130);
        break;
#else // QT_VERSION < 0x040702
    case ScreenOrientationLockPortrait:
        attribute = Qt::WA_LockPortraitOrientation;
        break;
    case ScreenOrientationLockLandscape:
        attribute = Qt::WA_LockLandscapeOrientation;
        break;
    default:
    case ScreenOrientationAuto:
        attribute = Qt::WA_AutoOrientation;
        break;
#endif // QT_VERSION < 0x040702
    };
    setAttribute(attribute, true);
}

void hellosarkar::showExpanded()
{
#ifdef Q_OS_SYMBIAN
    showFullScreen();
#elif defined(Q_WS_MAEMO_5) || defined(Q_WS_MAEMO_6)
    showMaximized();
#else
    show();
#endif
}

void hellosarkar::createGUI()
{
    mainWidget=new QWidget(this);
    mainWidget->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Expanding);

    //add top menu bar
    topMenuBar=new QWidget(mainWidget);
    //topMenuBar->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    leName = new QLineEdit(mainWidget);
    cboCompType = new QComboBox(mainWidget);
    cboCompType->setEditable(true);
    addComplainTypes();
    cboCompType->setCurrentIndex(-1);
    cboDistrict = new QComboBox(mainWidget);
    cboDistrict->setEditable(true);
    addDistricts();
    cboDistrict->setCurrentIndex(-1);
    dtDate = new QDateTimeEdit(QDate::currentDate(),mainWidget);
    dtDate->setDisplayFormat("yyyy/MM/dd");
    leDetailedAdd = new QLineEdit(mainWidget);

    lblComplain = new QLabel("Complain*: ", mainWidget);

    ptComplain = new QPlainTextEdit(mainWidget);
    btnSubmit = new QPushButton("Submit",mainWidget);
    btnCancel = new QPushButton("Cancel",mainWidget);
    //btnSubmit->setText(tr("Submit"));
    //btnSubmit->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);

    frmLayout = new QFormLayout();
    frmLayout->addRow(tr("Name:"), leName);
    frmLayout->addRow(tr("Category*:"), cboCompType);
    frmLayout->addRow(tr("District*:"), cboDistrict);
    frmLayout->addRow(tr("Detail Address*:"), leDetailedAdd);
    frmLayout->addRow(tr("&Date*:"), dtDate);

    buttonBox = new QDialogButtonBox(Qt::Horizontal);
    buttonBox->addButton(btnSubmit, QDialogButtonBox::ActionRole);
    buttonBox->addButton(btnCancel, QDialogButtonBox::RejectRole);

    vbLayout = new QVBoxLayout(mainWidget);
    vbLayout->addLayout(frmLayout);
    vbLayout->addWidget(lblComplain);
    vbLayout->addWidget(ptComplain);
    //vbLayout->addWidget(btnSubmit);
    vbLayout->addWidget(buttonBox);




//    frmLayout->addChildWidget(lblComplain);
//    frmLayout->addChildWidget(ptComplain);
//    frmLayout->addChildLayout(btnSubmit);
    //frmLayout->addRow(tr("&Complains:"), ptComplain);
    //frmLayout->addRow(tr("&Submit"), btnSubmit);



    createActions();
    createMenus();
    //mainWidget->setLayout(vbwholeUI);

    //vbLayout = new QVBoxLayout(mainWidget);



    //vbLayout->addLayout(frmLayout);
    //vbLayout->addWidget(lblComplain);
    //vbLayout->addWidget(ptComplain);
    //vbLayout->addWidget(btnSubmit);
    //mainWidget->setLayout(vbLayout);


    //frmLayout->addRow(tr("&Complain*:"), ptComplain);
    //frmLayout->addWidget(btnSubmit);
    //mainWidget->setLayout(frmLayout);

    setCentralWidget(mainWidget);
    setWindowTitle(tr("Hello Sarkar"));
    //setMinimumSize(240,240);
//    resize(800,480);
}

void hellosarkar::addComplainTypes()
{
    int i = 0;
    QFile xmlFile(":/categories.xml");
    if (!xmlFile.open(QIODevice::ReadOnly)) {
        qDebug()<<"Error while opening complain categories from xml.";
        return;
    }

    QXmlStreamReader* xmlReader = new QXmlStreamReader(&xmlFile);

    //Parse the XML until we reach end of it
    while(!xmlReader->atEnd() && !xmlReader->hasError()) {
            // Read next element
            QXmlStreamReader::TokenType token = xmlReader->readNext();
            //If token is just StartDocument - go to next
            if(token == QXmlStreamReader::StartDocument) {
                    continue;
            }
            //If token is StartElement - read it
            if(token == QXmlStreamReader::StartElement) {
                    if(xmlReader->name() == "categories") {
                            continue;
                    }

                    if(xmlReader->name() == "category") {
                        compCode[i] = xmlReader->attributes().value("code").toString();
                        compList[i] = xmlReader->readElementText();
                        cboCompType->addItem(compList[i]);
                        qDebug()<<"Category: " << compList[i] << " Code: " << compCode[i];
                        i +=1;
                    }
            }
    }

    if(xmlReader->hasError()) {
            qDebug()<<"Error reading categories xml: "<<xmlReader->errorString();
            return;
    }

    //close reader and flush file
    xmlReader->clear();
    xmlFile.close();
}

void hellosarkar::addDistricts()
{
    int i = 0;
    QFile xmlFile(":/districts.xml");
    if (!xmlFile.open(QIODevice::ReadOnly)) {
                    qDebug()<<"Error while opening districts xml.";
                    return;
            }

    QXmlStreamReader* xmlReader = new QXmlStreamReader(&xmlFile);

    //Parse the XML until we reach end of it
    while(!xmlReader->atEnd() && !xmlReader->hasError()) {
        // Read next element
        QXmlStreamReader::TokenType token = xmlReader->readNext();
        //If token is just StartDocument - go to next
        if(token == QXmlStreamReader::StartDocument) {
                continue;
        }
        //If token is StartElement - read it
        if(token == QXmlStreamReader::StartElement) {
                    if(xmlReader->name() == "districts") {
                            continue;
                    }

                    if(xmlReader->name() == "district") {
                        distCode[i] = xmlReader->attributes().value("code").toString().toInt();
                        distList[i] = xmlReader->readElementText();
                        cboDistrict->addItem(distList[i]);
                        qDebug()<<"Name: " <<distList[i]<<" Code: " <<distCode[i] ;
                        i +=1;
                    }
            }
    }

    if(xmlReader->hasError()) {
        qDebug()<<"Error while parsing district xml."<<xmlReader->errorString();
        return;
    }

    //close reader and flush file
    xmlReader->clear();
    xmlFile.close();
}

void hellosarkar::createActions()
{
    actHistory=new QAction(tr("&History"),this);
    actHistory->setShortcut(tr("Ctrl+H"));
    connect(actHistory, SIGNAL(triggered()), this, SLOT(showHistory()));

    actSettings=new QAction(tr("Se&ttings"),this);
    actSettings->setShortcut(tr("Ctrl+T"));
    connect(actSettings, SIGNAL(triggered()), this, SLOT(showSettings()));

    actAbout=new QAction(tr("A&bout HelloSarkar"),this);
    actAbout->setShortcut(tr("Ctrl+B"));
    connect(actAbout, SIGNAL(triggered()), this, SLOT(showAbout()));

    actAboutQt=new QAction(tr("&About Qt."),this);
    actAboutQt->setShortcut(tr("Ctrl+Q"));
    connect(actAboutQt, SIGNAL(triggered()), this, SLOT(showAboutQt()));

    connect(btnSubmit,SIGNAL(clicked()), this, SLOT(submitComplain()));
    connect(btnCancel,SIGNAL(clicked()), this, SLOT(clearForm()));
}

void hellosarkar::createMenus()
{
    hsMenu = menuBar()->addMenu(tr("&Menu"));
    hsMenu->addAction(actHistory);
    hsMenu->addAction(actSettings);
    hsMenu->addAction(actAbout);
    hsMenu->addAction(actAboutQt);
}

void hellosarkar::submitComplain()
{
    if(!validatefields())
    {
        qDebug()<<"Value validation failed. Data will not be processed";
        QMessageBox::information(this,"Error!", errString);
        return;
    }
    else
    {
        QByteArray postData;
        QString pname="name="+ leName->text()+"&";//distCode
        QString pCompType="complain_type="+ compCode[cboCompType->currentIndex()] +"&";
        QString pDistrict = "district_id=" + QString::number(distCode[cboDistrict->currentIndex()]) +"&";
        QString pAddress = "address="+ leDetailedAdd->text() + "&";
        QString pComplain = "complain_text="+ptComplain->toPlainText() + "&";
        QString pDate = "date="+ dtDate->date().toString("yyyy/MM/dd") + "&";
        QString pMobile = "mobile=' '&";
        QString pGPS = "gps=' ' &";
        QString pMobileInfo = "mobile_info=" + osVersion;

        postData.append(pname);
        postData.append(pCompType);
        postData.append(pDistrict);
        postData.append(pAddress);
        postData.append(pComplain);
        postData.append(pDate);
        postData.append(pMobile);
        postData.append(pGPS);
        postData.append(pMobileInfo);

        ntManager = new QNetworkAccessManager;
        connect(ntManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(networkRequestFinished(QNetworkReply*)));

        ntCurrentRequest = QNetworkRequest(compPostURL);
        ntCurrentRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

        ntCurrentReply = ntManager->post(ntCurrentRequest, postData);
        connect(ntCurrentReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(networkReplyError()));
        connect(ntCurrentReply, SIGNAL(metaDataChanged()), this, SLOT(serverReply()));
    }
}

bool hellosarkar::validatefields()
{
    //if(leName->text().isEmpty()) return false;
    if(leName->text().length() > 15)
    {
        errString = "Name too long, maximum character is 15.";
        return false;
    }
    else if(cboCompType->currentIndex() == -1)
    {
        errString = "Select Complain Category first.";
        return false;
    }
    else if(cboDistrict->currentIndex() == -1)
    {
        errString = "Select District first.";
        return false;
    }
    else if(leDetailedAdd->text().isEmpty())
    {
        errString = "Type detail address first.";
        return false;
    }
    else if(leDetailedAdd->text().length() > 50)
    {
        errString = "Address too long, maximum character is 50.";
        return false;
    }
    else if(ptComplain->toPlainText().isEmpty())
    {
        errString = "Type complain first.";
        return false;
    }
    else if(ptComplain->toPlainText().length() > 500)
    {
        errString = "Complain too long, maximum character is 500.";
        return false;
    }
    return true;
}

void hellosarkar::networkRequestFinished(QNetworkReply*)
{
    //ntCurrentReply->deleteLater();//probably required for something to work, not sure though
    qDebug()<<"Network Request Complete.";
    QVariant statusCode = ntCurrentReply->attribute( QNetworkRequest::HttpStatusCodeAttribute );

    int status = statusCode.toInt();
    QString reason = "";
    QString myCodeString = " ";
    qDebug()<<"Status Code: " << status;
    if ( status != 200 )
    {
        if(status == 503)
        {
            qDebug()<<"Service Unavailable. Try again later. Data will be saved in database for sending later.";
            QMessageBox::information(this,"Service unavailable.", "Service currently unavailable, please try again later. Data will be saved in local database.");
        }
        else if(status == 400)
        {
            qDebug()<<"Something is wrong, complain not registered.";
            QMessageBox::information(this, "Something went wrong", "Something went wrong, complain is not registered. Data will be saved in local database.");
        }
        else
        {
            qDebug()<<"Something is wrong, complain not registered.";
            QMessageBox::information(this, "Something went wrong", "Something went wrong, complain is not registered. Data will be saved in local database.");
        }
        reason = ntCurrentReply->attribute( QNetworkRequest::HttpReasonPhraseAttribute ).toString();
        qDebug()<<"Reason: "<<reason<<" Status Code: "<<QString::number(status);
    }
    else
    {
        QByteArray myCodeByete = ntCurrentReply->readAll();
        myCodeString = QString::fromUtf8(myCodeByete);
        qDebug()<<"Success! Complain submitted successfully. Reply code is: " << myCodeString << " Reason: " << reason;
        QMessageBox::information(this,"Success","Complain submitted successfully.");
    }
    saveToDb(myCodeString);//save to local database, code is already received.
}

void hellosarkar::networkReplyError()
{
    qDebug()<<"Something went wrong: " << ntCurrentReply->errorString();
    //QMessageBox::information(this,"Network reply error!", ntCurrentReply->errorString() + ". Data will be saved locally though.");
}

void hellosarkar::serverReply()//UNUSED AS OF NOW //Occurs when metadata from server is changed
{
    //Same as networkRequestFinished
    //Both serverReply and networkRequestFinished will execute together, but if any case is found when one of those is not executed more precise handling of situation will be required.
    qDebug()<<"Server Reply received, meta data changed";
}

void hellosarkar::saveToDb(QString remoteCode)
{
    //QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");//dbLocation
    //db.setDatabaseName(dbLocation);

    if (db.open()) {
        //Get maximum localcomplainid first
        int maxID = getMaxID()+1;//to be obtained by query

        //Insert data first
        QString pLocalCompID = QString::number(maxID);
        QString pDate = dtDate->date().toString("yyyy/MM/dd");
        QString pname= leName->text();
        QString pCompType= compCode[cboCompType->currentIndex()];
        QString pDistrict = QString::number(distCode[cboDistrict->currentIndex()]);
        QString pAddress = leDetailedAdd->text();
        QString pComplain = ptComplain->toPlainText();
        QString pMobileInfo = osVersion;
        QString pMobile = "9841000000 fake number";//mobilenumber to be read from api later
        QString pGPS = "234234.234233, 1234.542212 fake coordinates";
        QString pCompStatus = "na";
        QString pRemoteComplainID = remoteCode;//" " when nothing is received

        QSqlQuery insertQuery(db);
        //complain_id_local INT PRIMARY KEY, date TEXT, name TEXT, complain_type TEXT, district NUMERIC, address TEXT, complain_text TEXT, mobile_info TEXT, mobile_number TEXT, gps TEXT, complain_status TEXT, complain_id_remote TEXT
        //if(!insertQuery.exec("INSERT INTO complains VALUES('"+pRemoteComplainID+"','"+pMobileInfo+"','"+pname+"','"+pCompType+"','"+pDistrict+"','"+pAddress+"','"+pComplain+"','"+pDate+"',"+pMobile+",'"+pGPS+"',"+pLocalCompID+",'"+pCompStatus+"')"))
        if(!insertQuery.exec("INSERT INTO complains VALUES("+pLocalCompID+",'"+pDate+"','"+pname+"','"+pCompType+"',"+pDistrict+",'"+pAddress+"','"+pComplain+"','"+pMobileInfo+"','"+pMobile+"','"+pGPS+"','"+pCompStatus+"','"+pRemoteComplainID+"')"))
        {
            qCritical() << "Error occured while saving data in local database." << insertQuery.lastError();
            QMessageBox::information(this,"Failed!","Failed to save data in local database.");
        }
        else
        {
            qDebug() << "Data Saved in local database.";
           QMessageBox::information(this,"Success!","Data saved in local db Successfully.");
           clearForm();
        }

    } else {
        qCritical() << "Error while opening database connection."<< db.lastError();
        QMessageBox::information(this,"Error!","Could not establish connection with local database.");
    }
    db.close();
}

int hellosarkar::getMaxID()
{
    int maxID = -1;//in case query returns nothing -1 will be returned
    QSqlQuery query("SELECT MAX(complain_id_local) FROM complains");
    while (query.next()) {
        maxID = query.value(0).toInt();//if no data at all 0 will be returned
    }
    return maxID;
}

void hellosarkar::clearForm()
{
    leName->clear();
    leDetailedAdd->clear();
    ptComplain->clear();
    cboCompType->setCurrentIndex(-1);
    cboDistrict->setCurrentIndex(-1);
}

void hellosarkar::showHistory()
{
    history *historyWin = new history(this);
    historyWin->showNormal();
}

void hellosarkar::showSettings()
{
}

void hellosarkar::showAbout()
{
    QMessageBox::about(this,"About Hello Sarkar Application:", "Prime minister Dr. Babu Ram Bhatterai of Nepal has started new program/initiative for Nepali people to submit complains to Government of Nepal using telephone and/or text message. Hello Sarkar is an app developed to ease submission of complains to Government of Nepal. The application is currently in development phase and the data is stored in private server. This application has been developed by members of www.mobilenepal.net and is in no way official application for submitting complains to the government. \n\r\n\rQt version developed by: Krishna Prasad Shrestha (joseph9560@yahoo.com) \n\r\n\rConcept and Planning by MobileNepal.net members. \n\rCopyright: MobileNepal");
}

void hellosarkar::showAboutQt()
{
    QMessageBox::aboutQt(this,"About Qt");
}
