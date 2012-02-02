/****************************************************************************
** Meta object code from reading C++ file 'hellosarkar.h'
**
** Created: Sat Dec 3 02:25:25 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../hellosarkar.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'hellosarkar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_hellosarkar[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x0a,
      29,   12,   12,   12, 0x0a,
      43,   12,   12,   12, 0x0a,
      60,   12,   12,   12, 0x0a,
      99,   12,   12,   12, 0x0a,
     119,   12,   12,   12, 0x0a,
     144,  133,   12,   12, 0x0a,
     162,   12,   12,   12, 0x0a,
     174,   12,   12,   12, 0x0a,
     188,   12,   12,   12, 0x0a,
     203,   12,   12,   12, 0x0a,
     217,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_hellosarkar[] = {
    "hellosarkar\0\0createActions()\0createMenus()\0"
    "submitComplain()\0"
    "networkRequestFinished(QNetworkReply*)\0"
    "networkReplyError()\0serverReply()\0"
    "remoteCode\0saveToDb(QString)\0showAbout()\0"
    "showHistory()\0showSettings()\0showAboutQt()\0"
    "clearForm()\0"
};

const QMetaObject hellosarkar::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_hellosarkar,
      qt_meta_data_hellosarkar, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &hellosarkar::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *hellosarkar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *hellosarkar::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_hellosarkar))
        return static_cast<void*>(const_cast< hellosarkar*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int hellosarkar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: createActions(); break;
        case 1: createMenus(); break;
        case 2: submitComplain(); break;
        case 3: networkRequestFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 4: networkReplyError(); break;
        case 5: serverReply(); break;
        case 6: saveToDb((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: showAbout(); break;
        case 8: showHistory(); break;
        case 9: showSettings(); break;
        case 10: showAboutQt(); break;
        case 11: clearForm(); break;
        default: ;
        }
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
