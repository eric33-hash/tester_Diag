/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../qt_diagnostic/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[68];
    char stringdata0[1280];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 11), // "sendMessage"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 9), // "sendCount"
QT_MOC_LITERAL(4, 34, 8), // "sendJson"
QT_MOC_LITERAL(5, 43, 11), // "sendJsonotx"
QT_MOC_LITERAL(6, 55, 7), // "sendODX"
QT_MOC_LITERAL(7, 63, 11), // "ECU_SERVICE"
QT_MOC_LITERAL(8, 75, 3), // "ecu"
QT_MOC_LITERAL(9, 79, 10), // "startFlash"
QT_MOC_LITERAL(10, 90, 11), // "LinkedList*"
QT_MOC_LITERAL(11, 102, 4), // "path"
QT_MOC_LITERAL(12, 107, 11), // "startsignal"
QT_MOC_LITERAL(13, 119, 13), // "startsignal_c"
QT_MOC_LITERAL(14, 133, 10), // "recieveMsg"
QT_MOC_LITERAL(15, 144, 6), // "strMsg"
QT_MOC_LITERAL(16, 151, 12), // "recieveCount"
QT_MOC_LITERAL(17, 164, 11), // "receiveJson"
QT_MOC_LITERAL(18, 176, 14), // "receiveJsonotx"
QT_MOC_LITERAL(19, 191, 12), // "deletethread"
QT_MOC_LITERAL(20, 204, 13), // "displayString"
QT_MOC_LITERAL(21, 218, 3), // "str"
QT_MOC_LITERAL(22, 222, 15), // "displayProgress"
QT_MOC_LITERAL(23, 238, 7), // "u_int64"
QT_MOC_LITERAL(24, 246, 4), // "data"
QT_MOC_LITERAL(25, 251, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(26, 273, 19), // "on_Btn_File_clicked"
QT_MOC_LITERAL(27, 293, 21), // "on_Btn_File_4_clicked"
QT_MOC_LITERAL(28, 315, 21), // "on_Btn_File_5_clicked"
QT_MOC_LITERAL(29, 337, 19), // "on_Btn_save_clicked"
QT_MOC_LITERAL(30, 357, 27), // "on_treeWidget_doubleClicked"
QT_MOC_LITERAL(31, 385, 11), // "QModelIndex"
QT_MOC_LITERAL(32, 397, 5), // "index"
QT_MOC_LITERAL(33, 403, 20), // "on_Btn_clear_clicked"
QT_MOC_LITERAL(34, 424, 21), // "on_Btn_update_clicked"
QT_MOC_LITERAL(35, 446, 26), // "on_line_taskID_textChanged"
QT_MOC_LITERAL(36, 473, 4), // "arg1"
QT_MOC_LITERAL(37, 478, 30), // "on_line_taskID_editingFinished"
QT_MOC_LITERAL(38, 509, 23), // "on_Btn_File_otx_clicked"
QT_MOC_LITERAL(39, 533, 28), // "on_Btn_File_parseotx_clicked"
QT_MOC_LITERAL(40, 562, 40), // "on_treeWidget_customContextMe..."
QT_MOC_LITERAL(41, 603, 3), // "pos"
QT_MOC_LITERAL(42, 607, 23), // "on_pushButton_2_clicked"
QT_MOC_LITERAL(43, 631, 40), // "on_chart_rect_customContextMe..."
QT_MOC_LITERAL(44, 672, 24), // "on_Btn_ChoiceECU_clicked"
QT_MOC_LITERAL(45, 697, 22), // "on_Btn_Connect_clicked"
QT_MOC_LITERAL(46, 720, 20), // "on_Btn_Fresh_clicked"
QT_MOC_LITERAL(47, 741, 26), // "on_Btn_FileDiaglog_clicked"
QT_MOC_LITERAL(48, 768, 24), // "on_Btn_StartDiag_clicked"
QT_MOC_LITERAL(49, 793, 19), // "on_Btn_Send_clicked"
QT_MOC_LITERAL(50, 813, 25), // "on_Btn_disConnect_clicked"
QT_MOC_LITERAL(51, 839, 20), // "on_Btn_Start_clicked"
QT_MOC_LITERAL(52, 860, 19), // "on_Btn_FIle_clicked"
QT_MOC_LITERAL(53, 880, 24), // "on_Btn_StopFlash_clicked"
QT_MOC_LITERAL(54, 905, 19), // "on_Btn_Save_clicked"
QT_MOC_LITERAL(55, 925, 26), // "on_Btn_ConnectMqtt_clicked"
QT_MOC_LITERAL(56, 952, 29), // "on_Btn_disConnectMqtt_clicked"
QT_MOC_LITERAL(57, 982, 23), // "on_Btn_SendMqtt_clicked"
QT_MOC_LITERAL(58, 1006, 25), // "on_Btn_getVersion_clicked"
QT_MOC_LITERAL(59, 1032, 30), // "on_Btn_FileDiaglogMqtt_clicked"
QT_MOC_LITERAL(60, 1063, 29), // "on_Btn_SendMqttScript_clicked"
QT_MOC_LITERAL(61, 1093, 23), // "on_pushButton_3_clicked"
QT_MOC_LITERAL(62, 1117, 23), // "on_pushButton_4_clicked"
QT_MOC_LITERAL(63, 1141, 26), // "on_Btn_ReadVersion_clicked"
QT_MOC_LITERAL(64, 1168, 18), // "on_Btn_EOL_clicked"
QT_MOC_LITERAL(65, 1187, 27), // "on_Btn_StackVersion_clicked"
QT_MOC_LITERAL(66, 1215, 29), // "on_Btn_StackFlashTool_clicked"
QT_MOC_LITERAL(67, 1245, 34) // "on_Btn_StackDiagnosticFunc_cl..."

    },
    "MainWindow\0sendMessage\0\0sendCount\0"
    "sendJson\0sendJsonotx\0sendODX\0ECU_SERVICE\0"
    "ecu\0startFlash\0LinkedList*\0path\0"
    "startsignal\0startsignal_c\0recieveMsg\0"
    "strMsg\0recieveCount\0receiveJson\0"
    "receiveJsonotx\0deletethread\0displayString\0"
    "str\0displayProgress\0u_int64\0data\0"
    "on_pushButton_clicked\0on_Btn_File_clicked\0"
    "on_Btn_File_4_clicked\0on_Btn_File_5_clicked\0"
    "on_Btn_save_clicked\0on_treeWidget_doubleClicked\0"
    "QModelIndex\0index\0on_Btn_clear_clicked\0"
    "on_Btn_update_clicked\0on_line_taskID_textChanged\0"
    "arg1\0on_line_taskID_editingFinished\0"
    "on_Btn_File_otx_clicked\0"
    "on_Btn_File_parseotx_clicked\0"
    "on_treeWidget_customContextMenuRequested\0"
    "pos\0on_pushButton_2_clicked\0"
    "on_chart_rect_customContextMenuRequested\0"
    "on_Btn_ChoiceECU_clicked\0"
    "on_Btn_Connect_clicked\0on_Btn_Fresh_clicked\0"
    "on_Btn_FileDiaglog_clicked\0"
    "on_Btn_StartDiag_clicked\0on_Btn_Send_clicked\0"
    "on_Btn_disConnect_clicked\0"
    "on_Btn_Start_clicked\0on_Btn_FIle_clicked\0"
    "on_Btn_StopFlash_clicked\0on_Btn_Save_clicked\0"
    "on_Btn_ConnectMqtt_clicked\0"
    "on_Btn_disConnectMqtt_clicked\0"
    "on_Btn_SendMqtt_clicked\0"
    "on_Btn_getVersion_clicked\0"
    "on_Btn_FileDiaglogMqtt_clicked\0"
    "on_Btn_SendMqttScript_clicked\0"
    "on_pushButton_3_clicked\0on_pushButton_4_clicked\0"
    "on_Btn_ReadVersion_clicked\0"
    "on_Btn_EOL_clicked\0on_Btn_StackVersion_clicked\0"
    "on_Btn_StackFlashTool_clicked\0"
    "on_Btn_StackDiagnosticFunc_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      54,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  284,    2, 0x06 /* Public */,
       3,    2,  287,    2, 0x06 /* Public */,
       4,    1,  292,    2, 0x06 /* Public */,
       5,    1,  295,    2, 0x06 /* Public */,
       6,    1,  298,    2, 0x06 /* Public */,
       9,    1,  301,    2, 0x06 /* Public */,
      12,    0,  304,    2, 0x06 /* Public */,
      13,    0,  305,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      14,    1,  306,    2, 0x0a /* Public */,
      16,    2,  309,    2, 0x0a /* Public */,
      17,    1,  314,    2, 0x0a /* Public */,
      18,    1,  317,    2, 0x0a /* Public */,
      19,    0,  320,    2, 0x0a /* Public */,
      20,    1,  321,    2, 0x0a /* Public */,
      22,    1,  324,    2, 0x08 /* Private */,
      25,    0,  327,    2, 0x08 /* Private */,
      26,    0,  328,    2, 0x08 /* Private */,
      27,    0,  329,    2, 0x08 /* Private */,
      28,    0,  330,    2, 0x08 /* Private */,
      29,    0,  331,    2, 0x08 /* Private */,
      30,    1,  332,    2, 0x08 /* Private */,
      33,    0,  335,    2, 0x08 /* Private */,
      34,    0,  336,    2, 0x08 /* Private */,
      35,    1,  337,    2, 0x08 /* Private */,
      37,    0,  340,    2, 0x08 /* Private */,
      38,    0,  341,    2, 0x08 /* Private */,
      39,    0,  342,    2, 0x08 /* Private */,
      40,    1,  343,    2, 0x08 /* Private */,
      42,    0,  346,    2, 0x08 /* Private */,
      43,    1,  347,    2, 0x08 /* Private */,
      44,    0,  350,    2, 0x08 /* Private */,
      45,    0,  351,    2, 0x08 /* Private */,
      46,    0,  352,    2, 0x08 /* Private */,
      47,    0,  353,    2, 0x08 /* Private */,
      48,    0,  354,    2, 0x08 /* Private */,
      49,    0,  355,    2, 0x08 /* Private */,
      50,    0,  356,    2, 0x08 /* Private */,
      51,    0,  357,    2, 0x08 /* Private */,
      52,    0,  358,    2, 0x08 /* Private */,
      53,    0,  359,    2, 0x08 /* Private */,
      54,    0,  360,    2, 0x08 /* Private */,
      55,    0,  361,    2, 0x08 /* Private */,
      56,    0,  362,    2, 0x08 /* Private */,
      57,    0,  363,    2, 0x08 /* Private */,
      58,    0,  364,    2, 0x08 /* Private */,
      59,    0,  365,    2, 0x08 /* Private */,
      60,    0,  366,    2, 0x08 /* Private */,
      61,    0,  367,    2, 0x08 /* Private */,
      62,    0,  368,    2, 0x08 /* Private */,
      63,    0,  369,    2, 0x08 /* Private */,
      64,    0,  370,    2, 0x08 /* Private */,
      65,    0,  371,    2, 0x08 /* Private */,
      66,    0,  372,    2, 0x08 /* Private */,
      67,    0,  373,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,   15,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::QString,   15,
    QMetaType::Void, QMetaType::QString,   15,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   21,
    QMetaType::Void, 0x80000000 | 23,   24,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 31,   32,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   36,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,   41,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,   41,
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
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->sendCount((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->sendJson((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->sendJsonotx((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->sendODX((*reinterpret_cast< ECU_SERVICE(*)>(_a[1]))); break;
        case 5: _t->startFlash((*reinterpret_cast< LinkedList*(*)>(_a[1]))); break;
        case 6: _t->startsignal(); break;
        case 7: _t->startsignal_c(); break;
        case 8: _t->recieveMsg((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->recieveCount((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 10: _t->receiveJson((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 11: _t->receiveJsonotx((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 12: _t->deletethread(); break;
        case 13: _t->displayString((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 14: _t->displayProgress((*reinterpret_cast< u_int64(*)>(_a[1]))); break;
        case 15: _t->on_pushButton_clicked(); break;
        case 16: _t->on_Btn_File_clicked(); break;
        case 17: _t->on_Btn_File_4_clicked(); break;
        case 18: _t->on_Btn_File_5_clicked(); break;
        case 19: _t->on_Btn_save_clicked(); break;
        case 20: _t->on_treeWidget_doubleClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 21: _t->on_Btn_clear_clicked(); break;
        case 22: _t->on_Btn_update_clicked(); break;
        case 23: _t->on_line_taskID_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 24: _t->on_line_taskID_editingFinished(); break;
        case 25: _t->on_Btn_File_otx_clicked(); break;
        case 26: _t->on_Btn_File_parseotx_clicked(); break;
        case 27: _t->on_treeWidget_customContextMenuRequested((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 28: _t->on_pushButton_2_clicked(); break;
        case 29: _t->on_chart_rect_customContextMenuRequested((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 30: _t->on_Btn_ChoiceECU_clicked(); break;
        case 31: _t->on_Btn_Connect_clicked(); break;
        case 32: _t->on_Btn_Fresh_clicked(); break;
        case 33: _t->on_Btn_FileDiaglog_clicked(); break;
        case 34: _t->on_Btn_StartDiag_clicked(); break;
        case 35: _t->on_Btn_Send_clicked(); break;
        case 36: _t->on_Btn_disConnect_clicked(); break;
        case 37: _t->on_Btn_Start_clicked(); break;
        case 38: _t->on_Btn_FIle_clicked(); break;
        case 39: _t->on_Btn_StopFlash_clicked(); break;
        case 40: _t->on_Btn_Save_clicked(); break;
        case 41: _t->on_Btn_ConnectMqtt_clicked(); break;
        case 42: _t->on_Btn_disConnectMqtt_clicked(); break;
        case 43: _t->on_Btn_SendMqtt_clicked(); break;
        case 44: _t->on_Btn_getVersion_clicked(); break;
        case 45: _t->on_Btn_FileDiaglogMqtt_clicked(); break;
        case 46: _t->on_Btn_SendMqttScript_clicked(); break;
        case 47: _t->on_pushButton_3_clicked(); break;
        case 48: _t->on_pushButton_4_clicked(); break;
        case 49: _t->on_Btn_ReadVersion_clicked(); break;
        case 50: _t->on_Btn_EOL_clicked(); break;
        case 51: _t->on_Btn_StackVersion_clicked(); break;
        case 52: _t->on_Btn_StackFlashTool_clicked(); break;
        case 53: _t->on_Btn_StackDiagnosticFunc_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< LinkedList* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MainWindow::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::sendMessage)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::sendCount)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::sendJson)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::sendJsonotx)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(ECU_SERVICE );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::sendODX)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(LinkedList * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::startFlash)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::startsignal)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::startsignal_c)) {
                *result = 7;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 54)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 54;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 54)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 54;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::sendMessage(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainWindow::sendCount(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MainWindow::sendJson(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MainWindow::sendJsonotx(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void MainWindow::sendODX(ECU_SERVICE _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void MainWindow::startFlash(LinkedList * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void MainWindow::startsignal()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void MainWindow::startsignal_c()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
