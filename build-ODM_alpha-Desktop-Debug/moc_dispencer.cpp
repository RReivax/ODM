/****************************************************************************
** Meta object code from reading C++ file 'dispencer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ODM_alpha/dispencer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dispencer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_odm__Dispencer_t {
    QByteArrayData data[5];
    char stringdata0[57];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_odm__Dispencer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_odm__Dispencer_t qt_meta_stringdata_odm__Dispencer = {
    {
QT_MOC_LITERAL(0, 0, 14), // "odm::Dispencer"
QT_MOC_LITERAL(1, 15, 11), // "requestData"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 11), // "processData"
QT_MOC_LITERAL(4, 40, 16) // "QVector<data_id>"

    },
    "odm::Dispencer\0requestData\0\0processData\0"
    "QVector<data_id>"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_odm__Dispencer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   25,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 4,    2,

       0        // eod
};

void odm::Dispencer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Dispencer *_t = static_cast<Dispencer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->requestData(); break;
        case 1: _t->processData((*reinterpret_cast< QVector<data_id>(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Dispencer::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Dispencer::requestData)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject odm::Dispencer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_odm__Dispencer.data,
      qt_meta_data_odm__Dispencer,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *odm::Dispencer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *odm::Dispencer::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_odm__Dispencer.stringdata0))
        return static_cast<void*>(const_cast< Dispencer*>(this));
    return QObject::qt_metacast(_clname);
}

int odm::Dispencer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void odm::Dispencer::requestData()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
