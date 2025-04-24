/****************************************************************************
** Meta object code from reading C++ file 'chart_base.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../qt_diagnostic/otx/class_Charts/chart_base.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'chart_base.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Chart_Base_t {
    QByteArrayData data[19];
    char stringdata0[212];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Chart_Base_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Chart_Base_t qt_meta_stringdata_Chart_Base = {
    {
QT_MOC_LITERAL(0, 0, 10), // "Chart_Base"
QT_MOC_LITERAL(1, 11, 13), // "sendThisClass"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 11), // "Chart_Base*"
QT_MOC_LITERAL(4, 38, 1), // "x"
QT_MOC_LITERAL(5, 40, 1), // "y"
QT_MOC_LITERAL(6, 42, 17), // "setTypeChangeSize"
QT_MOC_LITERAL(7, 60, 9), // "ORIENTION"
QT_MOC_LITERAL(8, 70, 1), // "i"
QT_MOC_LITERAL(9, 72, 21), // "setTypeCreateMagPoint"
QT_MOC_LITERAL(10, 94, 1), // "d"
QT_MOC_LITERAL(11, 96, 11), // "showMagSize"
QT_MOC_LITERAL(12, 108, 11), // "hideMagSize"
QT_MOC_LITERAL(13, 120, 11), // "showMagOnly"
QT_MOC_LITERAL(14, 132, 11), // "hideMagOnly"
QT_MOC_LITERAL(15, 144, 20), // "setTypeChangeTextPos"
QT_MOC_LITERAL(16, 165, 22), // "CHART_LABEL_MOUSE_TYPE"
QT_MOC_LITERAL(17, 188, 1), // "t"
QT_MOC_LITERAL(18, 190, 21) // "CHART_TEXT_MOUSE_TYPE"

    },
    "Chart_Base\0sendThisClass\0\0Chart_Base*\0"
    "x\0y\0setTypeChangeSize\0ORIENTION\0i\0"
    "setTypeCreateMagPoint\0d\0showMagSize\0"
    "hideMagSize\0showMagOnly\0hideMagOnly\0"
    "setTypeChangeTextPos\0CHART_LABEL_MOUSE_TYPE\0"
    "t\0CHART_TEXT_MOUSE_TYPE"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Chart_Base[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   59,    2, 0x06 /* Public */,
       6,    1,   66,    2, 0x06 /* Public */,
       9,    3,   69,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    0,   76,    2, 0x0a /* Public */,
      12,    0,   77,    2, 0x0a /* Public */,
      13,    0,   78,    2, 0x0a /* Public */,
      14,    0,   79,    2, 0x0a /* Public */,
      15,    3,   80,    2, 0x0a /* Public */,
      15,    3,   87,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int, QMetaType::Int,    2,    4,    5,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 7, QMetaType::Int,    2,   10,    8,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 16, QMetaType::Int, QMetaType::Int,   17,    4,    5,
    QMetaType::Void, 0x80000000 | 18, QMetaType::Int, QMetaType::Int,   17,    4,    5,

       0        // eod
};

void Chart_Base::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Chart_Base *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendThisClass((*reinterpret_cast< Chart_Base*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 1: _t->setTypeChangeSize((*reinterpret_cast< ORIENTION(*)>(_a[1]))); break;
        case 2: _t->setTypeCreateMagPoint((*reinterpret_cast< Chart_Base*(*)>(_a[1])),(*reinterpret_cast< ORIENTION(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 3: _t->showMagSize(); break;
        case 4: _t->hideMagSize(); break;
        case 5: _t->showMagOnly(); break;
        case 6: _t->hideMagOnly(); break;
        case 7: _t->setTypeChangeTextPos((*reinterpret_cast< CHART_LABEL_MOUSE_TYPE(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 8: _t->setTypeChangeTextPos((*reinterpret_cast< CHART_TEXT_MOUSE_TYPE(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Chart_Base* >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Chart_Base* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Chart_Base::*)(Chart_Base * , int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Chart_Base::sendThisClass)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Chart_Base::*)(ORIENTION );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Chart_Base::setTypeChangeSize)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Chart_Base::*)(Chart_Base * , ORIENTION , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Chart_Base::setTypeCreateMagPoint)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Chart_Base::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_Chart_Base.data,
    qt_meta_data_Chart_Base,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Chart_Base::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Chart_Base::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Chart_Base.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Chart_Base::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void Chart_Base::sendThisClass(Chart_Base * _t1, int _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Chart_Base::setTypeChangeSize(ORIENTION _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Chart_Base::setTypeCreateMagPoint(Chart_Base * _t1, ORIENTION _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
