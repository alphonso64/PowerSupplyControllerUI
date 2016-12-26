/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[22];
    char stringdata[316];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 12),
QT_MOC_LITERAL(2, 24, 0),
QT_MOC_LITERAL(3, 25, 22),
QT_MOC_LITERAL(4, 48, 13),
QT_MOC_LITERAL(5, 62, 16),
QT_MOC_LITERAL(6, 79, 14),
QT_MOC_LITERAL(7, 94, 16),
QT_MOC_LITERAL(8, 111, 8),
QT_MOC_LITERAL(9, 120, 7),
QT_MOC_LITERAL(10, 128, 8),
QT_MOC_LITERAL(11, 137, 10),
QT_MOC_LITERAL(12, 148, 11),
QT_MOC_LITERAL(13, 160, 12),
QT_MOC_LITERAL(14, 173, 14),
QT_MOC_LITERAL(15, 188, 17),
QT_MOC_LITERAL(16, 206, 15),
QT_MOC_LITERAL(17, 222, 15),
QT_MOC_LITERAL(18, 238, 11),
QT_MOC_LITERAL(19, 250, 21),
QT_MOC_LITERAL(20, 272, 18),
QT_MOC_LITERAL(21, 291, 24)
    },
    "MainWindow\0recordStatus\0\0"
    "actionGroupButtonClick\0setPowerValue\0"
    "manualStartClick\0autoStartClick\0"
    "recordStartClick\0timerOut\0display\0"
    "fileOpen\0fileParsed\0autoProcess\0"
    "fileRecorded\0setButtonClick\0"
    "manualButtonClick\0autoButtonClick\0"
    "infoButtonClick\0errorHandle\0"
    "softUpdateButtonClick\0restartButtonClick\0"
    "firmwarepdateButtonClick"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  114,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,  115,    2, 0x08 /* Private */,
       4,    1,  118,    2, 0x08 /* Private */,
       5,    1,  121,    2, 0x08 /* Private */,
       6,    0,  124,    2, 0x08 /* Private */,
       7,    1,  125,    2, 0x08 /* Private */,
       8,    0,  128,    2, 0x08 /* Private */,
       9,    0,  129,    2, 0x08 /* Private */,
      10,    0,  130,    2, 0x08 /* Private */,
      11,    0,  131,    2, 0x08 /* Private */,
      12,    0,  132,    2, 0x08 /* Private */,
      13,    0,  133,    2, 0x08 /* Private */,
      14,    0,  134,    2, 0x08 /* Private */,
      15,    0,  135,    2, 0x08 /* Private */,
      16,    0,  136,    2, 0x08 /* Private */,
      17,    0,  137,    2, 0x08 /* Private */,
      18,    1,  138,    2, 0x08 /* Private */,
      19,    0,  141,    2, 0x08 /* Private */,
      20,    0,  142,    2, 0x08 /* Private */,
      21,    0,  143,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->recordStatus(); break;
        case 1: _t->actionGroupButtonClick((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->setPowerValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->manualStartClick((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->autoStartClick(); break;
        case 5: _t->recordStartClick((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->timerOut(); break;
        case 7: _t->display(); break;
        case 8: _t->fileOpen(); break;
        case 9: _t->fileParsed(); break;
        case 10: _t->autoProcess(); break;
        case 11: _t->fileRecorded(); break;
        case 12: _t->setButtonClick(); break;
        case 13: _t->manualButtonClick(); break;
        case 14: _t->autoButtonClick(); break;
        case 15: _t->infoButtonClick(); break;
        case 16: _t->errorHandle((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: _t->softUpdateButtonClick(); break;
        case 18: _t->restartButtonClick(); break;
        case 19: _t->firmwarepdateButtonClick(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::recordStatus)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, 0, 0}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 20)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 20)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 20;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::recordStatus()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
