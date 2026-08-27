/****************************************************************************
** Meta object code from reading C++ file 'deepseekaiassistants.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../deepseekaiassistants.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'deepseekaiassistants.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DeepSeekAIAssistants_t {
    QByteArrayData data[13];
    char stringdata0[218];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DeepSeekAIAssistants_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DeepSeekAIAssistants_t qt_meta_stringdata_DeepSeekAIAssistants = {
    {
QT_MOC_LITERAL(0, 0, 20), // "DeepSeekAIAssistants"
QT_MOC_LITERAL(1, 21, 18), // "onResponseReceived"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 14), // "QNetworkReply*"
QT_MOC_LITERAL(4, 56, 5), // "reply"
QT_MOC_LITERAL(5, 62, 33), // "on_listWidget_History_itemCli..."
QT_MOC_LITERAL(6, 96, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(7, 113, 4), // "item"
QT_MOC_LITERAL(8, 118, 18), // "onDownloadProgress"
QT_MOC_LITERAL(9, 137, 13), // "bytesReceived"
QT_MOC_LITERAL(10, 151, 10), // "bytesTotal"
QT_MOC_LITERAL(11, 162, 28), // "on_pushButton_Commit_clicked"
QT_MOC_LITERAL(12, 191, 26) // "on_pushButton_Exit_clicked"

    },
    "DeepSeekAIAssistants\0onResponseReceived\0"
    "\0QNetworkReply*\0reply\0"
    "on_listWidget_History_itemClicked\0"
    "QListWidgetItem*\0item\0onDownloadProgress\0"
    "bytesReceived\0bytesTotal\0"
    "on_pushButton_Commit_clicked\0"
    "on_pushButton_Exit_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DeepSeekAIAssistants[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x08 /* Private */,
       5,    1,   42,    2, 0x08 /* Private */,
       8,    2,   45,    2, 0x08 /* Private */,
      11,    0,   50,    2, 0x08 /* Private */,
      12,    0,   51,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong,    9,   10,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void DeepSeekAIAssistants::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DeepSeekAIAssistants *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onResponseReceived((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 1: _t->on_listWidget_History_itemClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 2: _t->onDownloadProgress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 3: _t->on_pushButton_Commit_clicked(); break;
        case 4: _t->on_pushButton_Exit_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject DeepSeekAIAssistants::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_DeepSeekAIAssistants.data,
    qt_meta_data_DeepSeekAIAssistants,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DeepSeekAIAssistants::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DeepSeekAIAssistants::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DeepSeekAIAssistants.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int DeepSeekAIAssistants::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
