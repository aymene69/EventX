/****************************************************************************
** Meta object code from reading C++ file 'GestionEvenement.hpp'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../include/GestionEvenement.hpp"
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GestionEvenement.hpp' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSGestionEvenementDialogENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSGestionEvenementDialogENDCLASS = QtMocHelpers::stringData(
    "GestionEvenementDialog",
    "dataModified",
    "",
    "creerEvenement",
    "modifierEvenement",
    "supprimerEvenement"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSGestionEvenementDialogENDCLASS_t {
    uint offsetsAndSizes[12];
    char stringdata0[23];
    char stringdata1[13];
    char stringdata2[1];
    char stringdata3[15];
    char stringdata4[18];
    char stringdata5[19];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSGestionEvenementDialogENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSGestionEvenementDialogENDCLASS_t qt_meta_stringdata_CLASSGestionEvenementDialogENDCLASS = {
    {
        QT_MOC_LITERAL(0, 22),  // "GestionEvenementDialog"
        QT_MOC_LITERAL(23, 12),  // "dataModified"
        QT_MOC_LITERAL(36, 0),  // ""
        QT_MOC_LITERAL(37, 14),  // "creerEvenement"
        QT_MOC_LITERAL(52, 17),  // "modifierEvenement"
        QT_MOC_LITERAL(70, 18)   // "supprimerEvenement"
    },
    "GestionEvenementDialog",
    "dataModified",
    "",
    "creerEvenement",
    "modifierEvenement",
    "supprimerEvenement"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSGestionEvenementDialogENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   38,    2, 0x06,    1 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       3,    0,   39,    2, 0x0a,    2 /* Public */,
       4,    0,   40,    2, 0x0a,    3 /* Public */,
       5,    0,   41,    2, 0x0a,    4 /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject GestionEvenementDialog::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_CLASSGestionEvenementDialogENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSGestionEvenementDialogENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSGestionEvenementDialogENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<GestionEvenementDialog, std::true_type>,
        // method 'dataModified'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'creerEvenement'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'modifierEvenement'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'supprimerEvenement'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void GestionEvenementDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GestionEvenementDialog *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->dataModified(); break;
        case 1: _t->creerEvenement(); break;
        case 2: _t->modifierEvenement(); break;
        case 3: _t->supprimerEvenement(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (GestionEvenementDialog::*)();
            if (_t _q_method = &GestionEvenementDialog::dataModified; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
    }
    (void)_a;
}

const QMetaObject *GestionEvenementDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GestionEvenementDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSGestionEvenementDialogENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int GestionEvenementDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void GestionEvenementDialog::dataModified()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
