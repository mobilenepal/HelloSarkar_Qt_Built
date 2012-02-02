#include "history.h"
#include <QtSql>

history::history(QWidget *parent) :
    QMainWindow(parent)
{
    createGUI();
    //loadData();
    #ifdef Q_WS_MAEMO_5
        setAttribute(Qt::WA_Maemo5StackedWindow);
    #endif
}

void history::createGUI()
{
    mainWidget = new QWidget(this);
    mainWidget->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Expanding);
    setCentralWidget(mainWidget);

    model = new QSqlTableModel(mainWidget);
    model->setTable("complains");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);

    model->select();

    //hiding or removing columns that are not required
    model->removeColumns(2,4);
    model->removeColumns(3,3);

    //renaming the headers for cleaner look
    model->setHeaderData(0, Qt::Horizontal, tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, tr("Date"));
    model->setHeaderData(2, Qt::Horizontal, tr("Complain"));
    model->setHeaderData(3, Qt::Horizontal, tr("Status"));
    model->setHeaderData(4, Qt::Horizontal, tr("Code"));

    view = new QTableView;

    view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //view->setSelectionMode(QAbstractItemView::MultiSelection);
    view->setSelectionMode(QAbstractItemView::SingleSelection);
    view->setSelectionBehavior(QAbstractItemView::SelectRows);

    view->setModel(model);
    view->resizeColumnsToContents();

    btnDetail = new QPushButton(tr("Detail"));
    btnUpdateStatus = new QPushButton(tr("Update Status"));
    btnDeleteRecord = new QPushButton(tr("Delete"));

    connect(btnDetail, SIGNAL(clicked()), this, SLOT(viewDetail()));
    connect(btnUpdateStatus, SIGNAL(clicked()), this, SLOT(updateRecord()));
    connect(btnDeleteRecord, SIGNAL(clicked()), this, SLOT(delRecord()));

//    submitButton = new QPushButton(tr("Submit"));
//    submitButton->setDefault(true);
//    revertButton = new QPushButton(tr("&Revert"));
//    quitButton = new QPushButton(tr("Quit"));

    buttonBox = new QDialogButtonBox(Qt::Horizontal);
    buttonBox->addButton(btnDetail, QDialogButtonBox::ActionRole);
    buttonBox->addButton(btnUpdateStatus, QDialogButtonBox::ActionRole);
    buttonBox->addButton(btnDeleteRecord, QDialogButtonBox::ActionRole);

//    buttonBox->addButton(submitButton, QDialogButtonBox::ActionRole);
//    buttonBox->addButton(revertButton, QDialogButtonBox::ActionRole);
//    buttonBox->addButton(quitButton, QDialogButtonBox::RejectRole);

//    connect(submitButton, SIGNAL(clicked()), this, SLOT(submit()));
//    connect(revertButton, SIGNAL(clicked()), model, SLOT(revertAll()));
//    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));

    QVBoxLayout *mainLayout = new QVBoxLayout(mainWidget);
    mainLayout->addWidget(view);
    mainLayout->addWidget(buttonBox);
    //setLayout(mainLayout);

    setWindowTitle(tr("Complain History"));
}

//Update record from web, update the status
void history::updateRecord()
{
}

//Update record from web, update the status, for small screen issue
void history::viewDetail()
{
    QMessageBox::information(this,"Detail Information", model->data(model->index(view->currentIndex().row(), 3)).toString());
}

void history::delRecord()
{
    if(model->removeRow(view->currentIndex().row(), QModelIndex()))
    {
        if(model->database().transaction())
        {
            if (model->submitAll())
            {
                if(model->database().commit())
                {
                    QMessageBox::information(this,"Success", "Record deleted successfully.");
                }
                else
                {
                    QMessageBox::information(this,"Failed", "Failed to delete record from database.");
                }
            }
            else
            {
                QMessageBox::information(this,"Failed", "Failed to delete record from database1.");
            }
        }
        else
        {
            QMessageBox::information(this,"Failed", "Failed to delete record from database2.");
        }
    }
    else
    {
        QMessageBox::information(this,"Failed", "Failed to delete record.");
    }

        //    if(model->rowCount()>0)
//    {
//        int locID = model->data(model->index(view->currentIndex().row(), 2)).toInt();
//        QString test = model->data(model->index(view->currentIndex().row(), 2)).toString();
//        //QString dlURL = model->data(model->index(curDownloadIndex, 0, QModelIndex()),Qt::DisplayRole).toString();
//        //model->removeRow(dTable->currentIndex().row(), QModelIndex());

//        QSqlQuery query;
//        if(!query.exec("DELETE FROM complains WHERE complain_id_local = '" + QString::number(locID)+"'"))
//        {
//            QMessageBox::information(this,"Failed!","Unable to delete the data.");
//        }
//        else
//        {
//            model->removeRow(view->currentIndex().row(), QModelIndex());
//        }
//    }
}

//Enable this funtion as well as corresponding button to enable updating edited data on the go
//void history::submit()
//{
//    model->database().transaction();
//    if (model->submitAll()) {
//        model->database().commit();
//    } else {
//        model->database().rollback();
//        QMessageBox::warning(this, tr("Error"),
//                             tr("The database reported an error: %1")
//                             .arg(model->lastError().text()));
//    }
//}
