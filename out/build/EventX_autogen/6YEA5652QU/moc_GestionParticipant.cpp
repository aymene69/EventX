/****************************************************************************
** Meta object code from reading C++ file 'GestionParticipant.hpp'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../include/GestionParticipant.hpp"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GestionParticipant.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSGestionParticipantDialogENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSGestionParticipantDialogENDCLASS = QtMocHelpers::stringData(
    "GestionParticipantDialog",
    "dataModified",
    "",
    "creerParticipant",
    "modifierParticipant",
    "supprimerParticipant",
    "onEventComboBoxChanged",
    "index"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSGestionParticipantDialogENDCLASS_t {
    uint offsetsAndSizes[16];
    char stringdata0[25];
    char stringdata1[13];
    char stringdata2[1];
    char stringdata3[17];
    char stringdata4[20];
    char stringdata5[21];
    char stringdata6[23];
    char stringdata7[6];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSGestionParticipantDialogENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSGestionParticipantDialogENDCLASS_t qt_meta_stringdata_CLASSGestionParticipantDialogENDCLASS = {
    {
        QT_MOC_LITERAL(0, 24),  // "GestionParticipantDialog"
        QT_MOC_LITERAL(25, 12),  // "dataModified"
        QT_MOC_LITERAL(38, 0),  // ""
        QT_MOC_LITERAL(39, 16),  // "creerParticipant"
        QT_MOC_LITERAL(56, 19),  // "modifierParticipant"
        QT_MOC_LITERAL(76, 20),  // "supprimerParticipant"
        QT_MOC_LITERAL(97, 22),  // "onEventComboBoxChanged"
        QT_MOC_LITERAL(120, 5)   // "index"
    },
    "GestionParticipantDialog",
    "dataModified",
    "",
    "creerParticipant",
    "modifierParticipant",
    "supprimerParticipant",
    "onEventComboBoxChanged",
    "index"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSGestionParticipantDialogENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   44,    2, 0x06,    1 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       3,    0,   45,    2, 0x0a,    2 /* Public */,
       4,    0,   46,    2, 0x0a,    3 /* Public */,
       5,    0,   47,    2, 0x0a,    4 /* Public */,
       6,    1,   48,    2, 0x08,    5 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,

       0        // eod
};

Q_CONSTINIT const QMetaObject GestionParticipantDialog::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_CLASSGestionParticipantDialogENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSGestionParticipantDialogENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSGestionParticipantDialogENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<GestionParticipantDialog, std::true_type>,
        // method 'dataModified'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'creerParticipant'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'modifierParticipant'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'supprimerParticipant'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onEventComboBoxChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>
    >,
    nullptr
} };

void GestionParticipantDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GestionParticipantDialog *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->dataModified(); break;
        case 1: _t->creerParticipant(); break;
        case 2: _t->modifierParticipant(); break;
        case 3: _t->supprimerParticipant(); break;
        case 4: _t->onEventComboBoxChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (GestionParticipantDialog::*)();
            if (_t _q_method = &GestionParticipantDialog::dataModified; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject *GestionParticipantDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GestionParticipantDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSGestionParticipantDialogENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int GestionParticipantDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void GestionParticipantDialog::dataModified()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP