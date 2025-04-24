/****************************************************************************
** Meta object code from reading C++ file 'flash.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../qt_diagnostic/flash/flash.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'flash.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_flash_t {
    QByteArrayData data[25];
    char stringdata0[272];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_flash_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_flash_t qt_meta_stringdata_flash = {
    {
QT_MOC_LITERAL(0, 0, 5), // "flash"
QT_MOC_LITERAL(1, 6, 10), // "emitString"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 3), // "str"
QT_MOC_LITERAL(4, 22, 8), // "emitStop"
QT_MOC_LITERAL(5, 31, 12), // "emitDataSize"
QT_MOC_LITERAL(6, 44, 4), // "size"
QT_MOC_LITERAL(7, 49, 12), // "sequencelist"
QT_MOC_LITERAL(8, 62, 10), // "phyRequest"
QT_MOC_LITERAL(9, 73, 10), // "funRequest"
QT_MOC_LITERAL(10, 84, 5), // "seeds"
QT_MOC_LITERAL(11, 90, 4), // "keys"
QT_MOC_LITERAL(12, 95, 10), // "EraseFlash"
QT_MOC_LITERAL(13, 106, 15), // "downloadRequest"
QT_MOC_LITERAL(14, 122, 8), // "download"
QT_MOC_LITERAL(15, 131, 8), // "checkCRC"
QT_MOC_LITERAL(16, 140, 8), // "waitTime"
QT_MOC_LITERAL(17, 149, 30), // "verifyCertificateBidirectional"
QT_MOC_LITERAL(18, 180, 16), // "ProofOfOwnership"
QT_MOC_LITERAL(19, 197, 18), // "downloadRequestHex"
QT_MOC_LITERAL(20, 216, 11), // "downloadHex"
QT_MOC_LITERAL(21, 228, 4), // "next"
QT_MOC_LITERAL(22, 233, 9), // "writeDate"
QT_MOC_LITERAL(23, 243, 16), // "readVersionASCII"
QT_MOC_LITERAL(24, 260, 11) // "sendMsgData"

    },
    "flash\0emitString\0\0str\0emitStop\0"
    "emitDataSize\0size\0sequencelist\0"
    "phyRequest\0funRequest\0seeds\0keys\0"
    "EraseFlash\0downloadRequest\0download\0"
    "checkCRC\0waitTime\0verifyCertificateBidirectional\0"
    "ProofOfOwnership\0downloadRequestHex\0"
    "downloadHex\0next\0writeDate\0readVersionASCII\0"
    "sendMsgData"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_flash[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       1,   36, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,
       4,    0,   32,    2, 0x06 /* Public */,
       5,    1,   33,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,

 // enums: name, alias, flags, count, data
       7,    7, 0x0,   17,   41,

 // enum data: key, value
       8, uint(flash::phyRequest),
       9, uint(flash::funRequest),
      10, uint(flash::seeds),
      11, uint(flash::keys),
      12, uint(flash::EraseFlash),
      13, uint(flash::downloadRequest),
      14, uint(flash::download),
      15, uint(flash::checkCRC),
      16, uint(flash::waitTime),
      17, uint(flash::verifyCertificateBidirectional),
      18, uint(flash::ProofOfOwnership),
      19, uint(flash::downloadRequestHex),
      20, uint(flash::downloadHex),
      21, uint(flash::next),
      22, uint(flash::writeDate),
      23, uint(flash::readVersionASCII),
      24, uint(flash::sendMsgData),

       0        // eod
};

void flash::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<flash *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->emitString((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->emitStop(); break;
        case 2: _t->emitDataSize((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (flash::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&flash::emitString)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (flash::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&flash::emitStop)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (flash::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&flash::emitDataSize)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject flash::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_flash.data,
    qt_meta_data_flash,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *flash::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *flash::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_flash.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int flash::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void flash::emitString(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void flash::emitStop()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void flash::emitDataSize(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
