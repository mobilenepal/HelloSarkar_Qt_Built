#ifndef HISTORY_H
#define HISTORY_H

#include <QMainWindow>
#include <QtGui>

QT_BEGIN_NAMESPACE
class QDialogButtonBox;
class QPushButton;
class QSqlTableModel;
QT_END_NAMESPACE

class history : public QMainWindow
{
    Q_OBJECT
public:
    explicit history(QWidget *parent = 0);
    void createGUI();

//    QPushButton *submitButton;
//    QPushButton *revertButton;
//    QPushButton *quitButton;
    QPushButton *btnDetail;
    QPushButton *btnUpdateStatus;
    QPushButton *btnDeleteRecord;
    QDialogButtonBox *buttonBox;
    QSqlTableModel *model;
    QWidget *mainWidget;
    QTableView *view;

signals:

private slots:
//    void submit();
    void updateRecord();
    void delRecord();
    void viewDetail();
};

#endif // HISTORY_H
