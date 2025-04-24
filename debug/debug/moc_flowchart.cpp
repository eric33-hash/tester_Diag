/****************************************************************************
** Meta object code from reading C++ file 'flowchart.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../qt_diagnostic/otx/flowchart.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'flowchart.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_FlowChart_t {
    QByteArrayData data[52];
    char stringdata0[691];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FlowChart_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FlowChart_t qt_meta_stringdata_FlowChart = {
    {
QT_MOC_LITERAL(0, 0, 9), // "FlowChart"
QT_MOC_LITERAL(1, 10, 14), // "sendChartStyle"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 5), // "QPen&"
QT_MOC_LITERAL(4, 32, 2), // "qp"
QT_MOC_LITERAL(5, 35, 7), // "QBrush&"
QT_MOC_LITERAL(6, 43, 2), // "qb"
QT_MOC_LITERAL(7, 46, 13), // "sendLineStyle"
QT_MOC_LITERAL(8, 60, 15), // "LINE_HEAD_TYPE&"
QT_MOC_LITERAL(9, 76, 17), // "startLineHeadType"
QT_MOC_LITERAL(10, 94, 15), // "endLineHeadType"
QT_MOC_LITERAL(11, 110, 12), // "disableStyle"
QT_MOC_LITERAL(12, 123, 17), // "updateWindowTitle"
QT_MOC_LITERAL(13, 141, 6), // "setPen"
QT_MOC_LITERAL(14, 148, 8), // "setBrush"
QT_MOC_LITERAL(15, 157, 12), // "setLineWidth"
QT_MOC_LITERAL(16, 170, 1), // "i"
QT_MOC_LITERAL(17, 172, 17), // "setLineStartStyle"
QT_MOC_LITERAL(18, 190, 15), // "setLineEndStyle"
QT_MOC_LITERAL(19, 206, 19), // "setMousePressedFlag"
QT_MOC_LITERAL(20, 226, 16), // "MOUSE_EVENT_TYPE"
QT_MOC_LITERAL(21, 243, 13), // "setPaintChart"
QT_MOC_LITERAL(22, 257, 13), // "setSelecChart"
QT_MOC_LITERAL(23, 271, 11), // "Chart_Base*"
QT_MOC_LITERAL(24, 283, 4), // "data"
QT_MOC_LITERAL(25, 288, 18), // "setPaintChart_Rect"
QT_MOC_LITERAL(26, 307, 21), // "setPaintChart_Diamond"
QT_MOC_LITERAL(27, 329, 23), // "setPaintChart_RoundRect"
QT_MOC_LITERAL(28, 353, 21), // "setPaintChart_Ellipse"
QT_MOC_LITERAL(29, 375, 18), // "setPaintChart_Line"
QT_MOC_LITERAL(30, 394, 23), // "setPaintChart_trapezoid"
QT_MOC_LITERAL(31, 418, 19), // "resetPaintChartType"
QT_MOC_LITERAL(32, 438, 22), // "setPaintChart_RectSelf"
QT_MOC_LITERAL(33, 461, 25), // "setPaintChart_DiamondSelf"
QT_MOC_LITERAL(34, 487, 17), // "setTypeChangeSize"
QT_MOC_LITERAL(35, 505, 9), // "ORIENTION"
QT_MOC_LITERAL(36, 515, 21), // "setTypeCreateMagPoint"
QT_MOC_LITERAL(37, 537, 2), // "cb"
QT_MOC_LITERAL(38, 540, 1), // "d"
QT_MOC_LITERAL(39, 542, 13), // "openChartFile"
QT_MOC_LITERAL(40, 556, 4), // "path"
QT_MOC_LITERAL(41, 561, 13), // "saveChartFile"
QT_MOC_LITERAL(42, 575, 11), // "ECU_SERVICE"
QT_MOC_LITERAL(43, 587, 3), // "ecu"
QT_MOC_LITERAL(44, 591, 12), // "newChartFile"
QT_MOC_LITERAL(45, 604, 10), // "getSysTime"
QT_MOC_LITERAL(46, 615, 10), // "insertDiag"
QT_MOC_LITERAL(47, 626, 14), // "pugi::xml_node"
QT_MOC_LITERAL(48, 641, 6), // "m_char"
QT_MOC_LITERAL(49, 648, 10), // "actionNode"
QT_MOC_LITERAL(50, 659, 16), // "insertDiagnostic"
QT_MOC_LITERAL(51, 676, 14) // "metaDataNode_1"

    },
    "FlowChart\0sendChartStyle\0\0QPen&\0qp\0"
    "QBrush&\0qb\0sendLineStyle\0LINE_HEAD_TYPE&\0"
    "startLineHeadType\0endLineHeadType\0"
    "disableStyle\0updateWindowTitle\0setPen\0"
    "setBrush\0setLineWidth\0i\0setLineStartStyle\0"
    "setLineEndStyle\0setMousePressedFlag\0"
    "MOUSE_EVENT_TYPE\0setPaintChart\0"
    "setSelecChart\0Chart_Base*\0data\0"
    "setPaintChart_Rect\0setPaintChart_Diamond\0"
    "setPaintChart_RoundRect\0setPaintChart_Ellipse\0"
    "setPaintChart_Line\0setPaintChart_trapezoid\0"
    "resetPaintChartType\0setPaintChart_RectSelf\0"
    "setPaintChart_DiamondSelf\0setTypeChangeSize\0"
    "ORIENTION\0setTypeCreateMagPoint\0cb\0d\0"
    "openChartFile\0path\0saveChartFile\0"
    "ECU_SERVICE\0ecu\0newChartFile\0getSysTime\0"
    "insertDiag\0pugi::xml_node\0m_char\0"
    "actionNode\0insertDiagnostic\0metaDataNode_1"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FlowChart[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      30,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,  164,    2, 0x06 /* Public */,
       7,    3,  169,    2, 0x06 /* Public */,
      11,    0,  176,    2, 0x06 /* Public */,
      12,    1,  177,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      13,    1,  180,    2, 0x0a /* Public */,
      14,    1,  183,    2, 0x0a /* Public */,
      15,    1,  186,    2, 0x0a /* Public */,
      17,    1,  189,    2, 0x0a /* Public */,
      18,    1,  192,    2, 0x0a /* Public */,
      19,    1,  195,    2, 0x0a /* Public */,
      21,    0,  198,    2, 0x0a /* Public */,
      22,    3,  199,    2, 0x0a /* Public */,
      21,    1,  206,    2, 0x0a /* Public */,
      25,    0,  209,    2, 0x0a /* Public */,
      26,    0,  210,    2, 0x0a /* Public */,
      27,    0,  211,    2, 0x0a /* Public */,
      28,    0,  212,    2, 0x0a /* Public */,
      29,    0,  213,    2, 0x0a /* Public */,
      30,    0,  214,    2, 0x0a /* Public */,
      31,    0,  215,    2, 0x0a /* Public */,
      32,    1,  216,    2, 0x0a /* Public */,
      33,    1,  219,    2, 0x0a /* Public */,
      34,    1,  222,    2, 0x0a /* Public */,
      36,    3,  225,    2, 0x0a /* Public */,
      39,    1,  232,    2, 0x0a /* Public */,
      41,    1,  235,    2, 0x0a /* Public */,
      44,    0,  238,    2, 0x0a /* Public */,
      45,    0,  239,    2, 0x0a /* Public */,
      46,    2,  240,    2, 0x0a /* Public */,
      50,    4,  245,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5,    4,    6,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 8, 0x80000000 | 8,    4,    9,   10,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void, 0x80000000 | 20,    2,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 23, QMetaType::Int, QMetaType::Int,    2,    2,    2,
    QMetaType::Void, QMetaType::QString,   24,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   24,
    QMetaType::Void, QMetaType::QString,   24,
    QMetaType::Void, 0x80000000 | 35,   16,
    QMetaType::Void, 0x80000000 | 23, 0x80000000 | 35, QMetaType::Int,   37,   38,   16,
    QMetaType::Bool, QMetaType::QString,   40,
    QMetaType::Bool, 0x80000000 | 42,   43,
    QMetaType::Bool,
    QMetaType::QString,
    0x80000000 | 47, 0x80000000 | 23, 0x80000000 | 47,   48,   49,
    0x80000000 | 47, 0x80000000 | 23, 0x80000000 | 47, 0x80000000 | 47, 0x80000000 | 42,   48,   49,   51,   43,

       0        // eod
};

void FlowChart::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<FlowChart *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendChartStyle((*reinterpret_cast< QPen(*)>(_a[1])),(*reinterpret_cast< QBrush(*)>(_a[2]))); break;
        case 1: _t->sendLineStyle((*reinterpret_cast< QPen(*)>(_a[1])),(*reinterpret_cast< LINE_HEAD_TYPE(*)>(_a[2])),(*reinterpret_cast< LINE_HEAD_TYPE(*)>(_a[3]))); break;
        case 2: _t->disableStyle(); break;
        case 3: _t->updateWindowTitle((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->setPen((*reinterpret_cast< QPen(*)>(_a[1]))); break;
        case 5: _t->setBrush((*reinterpret_cast< QBrush(*)>(_a[1]))); break;
        case 6: _t->setLineWidth((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->setLineStartStyle((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->setLineEndStyle((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->setMousePressedFlag((*reinterpret_cast< MOUSE_EVENT_TYPE(*)>(_a[1]))); break;
        case 10: _t->setPaintChart(); break;
        case 11: _t->setSelecChart((*reinterpret_cast< Chart_Base*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 12: _t->setPaintChart((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 13: _t->setPaintChart_Rect(); break;
        case 14: _t->setPaintChart_Diamond(); break;
        case 15: _t->setPaintChart_RoundRect(); break;
        case 16: _t->setPaintChart_Ellipse(); break;
        case 17: _t->setPaintChart_Line(); break;
        case 18: _t->setPaintChart_trapezoid(); break;
        case 19: _t->resetPaintChartType(); break;
        case 20: _t->setPaintChart_RectSelf((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 21: _t->setPaintChart_DiamondSelf((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 22: _t->setTypeChangeSize((*reinterpret_cast< ORIENTION(*)>(_a[1]))); break;
        case 23: _t->setTypeCreateMagPoint((*reinterpret_cast< Chart_Base*(*)>(_a[1])),(*reinterpret_cast< ORIENTION(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 24: { bool _r = _t->openChartFile((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 25: { bool _r = _t->saveChartFile((*reinterpret_cast< ECU_SERVICE(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 26: { bool _r = _t->newChartFile();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 27: { QString _r = _t->getSysTime();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 28: { pugi::xml_node _r = _t->insertDiag((*reinterpret_cast< Chart_Base*(*)>(_a[1])),(*reinterpret_cast< pugi::xml_node(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< pugi::xml_node*>(_a[0]) = std::move(_r); }  break;
        case 29: { pugi::xml_node _r = _t->insertDiagnostic((*reinterpret_cast< Chart_Base*(*)>(_a[1])),(*reinterpret_cast< pugi::xml_node(*)>(_a[2])),(*reinterpret_cast< pugi::xml_node(*)>(_a[3])),(*reinterpret_cast< ECU_SERVICE(*)>(_a[4])));
            if (_a[0]) *reinterpret_cast< pugi::xml_node*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 11:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Chart_Base* >(); break;
            }
            break;
        case 23:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Chart_Base* >(); break;
            }
            break;
        case 28:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< Chart_Base* >(); break;
            }
            break;
        case 29:
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
            using _t = void (FlowChart::*)(QPen & , QBrush & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlowChart::sendChartStyle)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (FlowChart::*)(QPen & , LINE_HEAD_TYPE & , LINE_HEAD_TYPE & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlowChart::sendLineStyle)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (FlowChart::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlowChart::disableStyle)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (FlowChart::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FlowChart::updateWindowTitle)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject FlowChart::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_FlowChart.data,
    qt_meta_data_FlowChart,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *FlowChart::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FlowChart::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_FlowChart.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int FlowChart::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 30)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 30;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 30)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 30;
    }
    return _id;
}

// SIGNAL 0
void FlowChart::sendChartStyle(QPen & _t1, QBrush & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void FlowChart::sendLineStyle(QPen & _t1, LINE_HEAD_TYPE & _t2, LINE_HEAD_TYPE & _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void FlowChart::disableStyle()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void FlowChart::updateWindowTitle(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
