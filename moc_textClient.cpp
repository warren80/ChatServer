/****************************************************************************
** Meta object code from reading C++ file 'textClient.h'
**
** Created: Wed Mar 9 15:08:29 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "textClient.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'textClient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TextClient[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      43,   11,   11,   11, 0x0a,
      51,   11,   11,   11, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_TextClient[] = {
    "TextClient\0\0signalTextRecieved(PMESGSPECS)\0"
    "Start()\0txMessage(QString)\0"
};

const QMetaObject TextClient::staticMetaObject = {
    { &Component::staticMetaObject, qt_meta_stringdata_TextClient,
      qt_meta_data_TextClient, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TextClient::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TextClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TextClient::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TextClient))
        return static_cast<void*>(const_cast< TextClient*>(this));
    return Component::qt_metacast(_clname);
}

int TextClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Component::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: signalTextRecieved((*reinterpret_cast< PMESGSPECS(*)>(_a[1]))); break;
        case 1: Start(); break;
        case 2: txMessage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void TextClient::signalTextRecieved(PMESGSPECS _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
