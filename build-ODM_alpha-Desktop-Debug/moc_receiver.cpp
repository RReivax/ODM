/****************************************************************************
** Meta object code from reading C++ file 'receiver.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ODM_alpha/receiver.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'receiver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_odm__Receiver_t {
    QByteArrayData data[15];
    char stringdata0[181];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_odm__Receiver_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_odm__Receiver_t qt_meta_stringdata_odm__Receiver = {
    {
QT_MOC_LITERAL(0, 0, 13), // "odm::Receiver"
QT_MOC_LITERAL(1, 14, 12), // "transferData"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 20), // "QVector<QJsonObject>"
QT_MOC_LITERAL(4, 49, 14), // "endOfReception"
QT_MOC_LITERAL(5, 64, 16), // "noDataToTransfer"
QT_MOC_LITERAL(6, 81, 12), // "dataReceived"
QT_MOC_LITERAL(7, 94, 11), // "startServer"
QT_MOC_LITERAL(8, 106, 9), // "newClient"
QT_MOC_LITERAL(9, 116, 12), // "disconnected"
QT_MOC_LITERAL(10, 129, 10), // "readSocket"
QT_MOC_LITERAL(11, 140, 10), // "InitClient"
QT_MOC_LITERAL(12, 151, 11), // "prepareData"
QT_MOC_LITERAL(13, 163, 9), // "stackData"
QT_MOC_LITERAL(14, 173, 7) // "toStack"

    },
    "odm::Receiver\0transferData\0\0"
    "QVector<QJsonObject>\0endOfReception\0"
    "noDataToTransfer\0dataReceived\0startServer\0"
    "newClient\0disconnected\0readSocket\0"
    "InitClient\0prepareData\0stackData\0"
    "toStack"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_odm__Receiver[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x06 /* Public */,
       4,    0,   72,    2, 0x06 /* Public */,
       5,    0,   73,    2, 0x06 /* Public */,
       6,    1,   74,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   77,    2, 0x0a /* Public */,
       8,    0,   78,    2, 0x0a /* Public */,
       9,    0,   79,    2, 0x0a /* Public */,
      10,    0,   80,    2, 0x0a /* Public */,
      11,    0,   81,    2, 0x0a /* Public */,
      12,    0,   82,    2, 0x0a /* Public */,
      13,    1,   83,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,   14,

       0        // eod
};

void odm::Receiver::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Receiver *_t = static_cast<Receiver *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->transferData((*reinterpret_cast< QVector<QJsonObject>(*)>(_a[1]))); break;
        case 1: _t->endOfReception(); break;
        case 2: _t->noDataToTransfer(); break;
        case 3: _t->dataReceived((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 4: _t->startServer(); break;
        case 5: _t->newClient(); break;
        case 6: _t->disconnected(); break;
        case 7: _t->readSocket(); break;
        case 8: _t->InitClient(); break;
        case 9: _t->prepareData(); break;
        case 10: _t->stackData((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<QJsonObject> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Receiver::*_t)(QVector<QJsonObject> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Receiver::transferData)) {
                *result = 0;
            }
        }
        {
            typedef void (Receiver::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Receiver::endOfReception)) {
                *result = 1;
            }
        }
        {
            typedef void (Receiver::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Receiver::noDataToTransfer)) {
                *result = 2;
            }
        }
        {
            typedef void (Receiver::*_t)(QByteArray );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Receiver::dataReceived)) {
                *result = 3;
            }
        }
    }
}

const QMetaObject odm::Receiver::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_odm__Receiver.data,
      qt_meta_data_odm__Receiver,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *odm::Receiver::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *odm::Receiver::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_odm__Receiver.stringdata0))
        return static_cast<void*>(const_cast< Receiver*>(this));
    return QObject::qt_metacast(_clname);
}

int odm::Receiver::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void odm::Receiver::transferData(QVector<QJsonObject> _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void odm::Receiver::endOfReception()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void odm::Receiver::noDataToTransfer()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void odm::Receiver::dataReceived(QByteArray _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
