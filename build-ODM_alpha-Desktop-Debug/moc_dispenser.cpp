/****************************************************************************
** Meta object code from reading C++ file 'dispenser.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ODM_alpha/dispenser.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dispenser.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_odm__Dispenser_t {
    QByteArrayData data[9];
    char stringdata0[120];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_odm__Dispenser_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_odm__Dispenser_t qt_meta_stringdata_odm__Dispenser = {
    {
QT_MOC_LITERAL(0, 0, 14), // "odm::Dispenser"
QT_MOC_LITERAL(1, 15, 11), // "requestData"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 13), // "dispenseState"
QT_MOC_LITERAL(4, 42, 21), // "QVector<QVariantMap>*"
QT_MOC_LITERAL(5, 64, 15), // "QReadWriteLock*"
QT_MOC_LITERAL(6, 80, 11), // "processData"
QT_MOC_LITERAL(7, 92, 16), // "QVector<data_id>"
QT_MOC_LITERAL(8, 109, 10) // "shareState"

    },
    "odm::Dispenser\0requestData\0\0dispenseState\0"
    "QVector<QVariantMap>*\0QReadWriteLock*\0"
    "processData\0QVector<data_id>\0shareState"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_odm__Dispenser[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,
       3,    2,   35,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   40,    2, 0x0a /* Public */,
       8,    0,   43,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4, 0x80000000 | 5,    2,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 7,    2,
    QMetaType::Void,

       0        // eod
};

void odm::Dispenser::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Dispenser *_t = static_cast<Dispenser *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->requestData(); break;
        case 1: _t->dispenseState((*reinterpret_cast< QVector<QVariantMap>*(*)>(_a[1])),(*reinterpret_cast< QReadWriteLock*(*)>(_a[2]))); break;
        case 2: _t->processData((*reinterpret_cast< QVector<data_id>(*)>(_a[1]))); break;
        case 3: _t->shareState(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Dispenser::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Dispenser::requestData)) {
                *result = 0;
            }
        }
        {
            typedef void (Dispenser::*_t)(QVector<QVariantMap> * , QReadWriteLock * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Dispenser::dispenseState)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject odm::Dispenser::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_odm__Dispenser.data,
      qt_meta_data_odm__Dispenser,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *odm::Dispenser::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *odm::Dispenser::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_odm__Dispenser.stringdata0))
        return static_cast<void*>(const_cast< Dispenser*>(this));
    return QObject::qt_metacast(_clname);
}

int odm::Dispenser::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void odm::Dispenser::requestData()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void odm::Dispenser::dispenseState(QVector<QVariantMap> * _t1, QReadWriteLock * _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
