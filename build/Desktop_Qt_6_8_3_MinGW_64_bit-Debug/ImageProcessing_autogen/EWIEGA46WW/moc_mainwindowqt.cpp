/****************************************************************************
** Meta object code from reading C++ file 'mainwindowqt.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.8.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../mainwindowqt.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindowqt.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.8.3. It"
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
struct qt_meta_tag_ZN12MainWindowQtE_t {};
} // unnamed namespace


#ifdef QT_MOC_HAS_STRINGDATA
static constexpr auto qt_meta_stringdata_ZN12MainWindowQtE = QtMocHelpers::stringData(
    "MainWindowQt",
    "on_loadImage_clicked",
    "",
    "loadImage",
    "pathToImage",
    "loadModifiedImage",
    "image_to_load",
    "on_negative_clicked",
    "on_greyScale_clicked",
    "on_Contrast_clicked",
    "on_Gamma_clicked",
    "on_Brightnes_clicked",
    "on_histogram_clicked",
    "on_Stretching_clicked",
    "on_wyrownanie_clicked",
    "getPixel",
    "QRgb",
    "image",
    "x",
    "y",
    "optionsOfPixelsFillingOutsideOfImage",
    "option",
    "getWindow",
    "QList<QList<int>>",
    "size",
    "channel",
    "getMask",
    "QList<QList<float>>",
    "join",
    "a",
    "b",
    "sum",
    "matrix",
    "reflection",
    "convolute",
    "mask",
    "on_rozmycieRownomierne_clicked",
    "on_rozmycieGausowskie_clicked",
    "on_Save_as_clicked",
    "blackAndWhite"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA

Q_CONSTINIT static const uint qt_meta_data_ZN12MainWindowQtE[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      22,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  146,    2, 0x08,    1 /* Private */,
       3,    1,  147,    2, 0x08,    2 /* Private */,
       5,    1,  150,    2, 0x08,    4 /* Private */,
       7,    0,  153,    2, 0x08,    6 /* Private */,
       8,    0,  154,    2, 0x08,    7 /* Private */,
       9,    0,  155,    2, 0x08,    8 /* Private */,
      10,    0,  156,    2, 0x08,    9 /* Private */,
      11,    0,  157,    2, 0x08,   10 /* Private */,
      12,    0,  158,    2, 0x08,   11 /* Private */,
      13,    0,  159,    2, 0x08,   12 /* Private */,
      14,    0,  160,    2, 0x08,   13 /* Private */,
      15,    4,  161,    2, 0x08,   14 /* Private */,
      22,    6,  170,    2, 0x08,   19 /* Private */,
      26,    1,  183,    2, 0x08,   26 /* Private */,
      28,    2,  186,    2, 0x08,   28 /* Private */,
      31,    1,  191,    2, 0x08,   31 /* Private */,
      33,    1,  194,    2, 0x08,   33 /* Private */,
      34,    4,  197,    2, 0x08,   35 /* Private */,
      36,    0,  206,    2, 0x08,   40 /* Private */,
      37,    0,  207,    2, 0x08,   41 /* Private */,
      38,    0,  208,    2, 0x08,   42 /* Private */,
      39,    0,  209,    2, 0x08,   43 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::QImage,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    0x80000000 | 16, QMetaType::QImage, QMetaType::Int, QMetaType::Int, 0x80000000 | 20,   17,   18,   19,   21,
    0x80000000 | 23, QMetaType::QImage, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, 0x80000000 | 20,   17,   18,   19,   24,   25,   21,
    0x80000000 | 27, QMetaType::Int,   24,
    0x80000000 | 27, 0x80000000 | 23, 0x80000000 | 27,   29,   30,
    QMetaType::Float, 0x80000000 | 27,   32,
    0x80000000 | 27, 0x80000000 | 27,   32,
    QMetaType::QImage, QMetaType::QImage, 0x80000000 | 27, QMetaType::Int, 0x80000000 | 20,   17,   35,   25,   21,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::QImage,

       0        // eod
};

Q_CONSTINIT const QMetaObject MainWindowQt::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_ZN12MainWindowQtE.offsetsAndSizes,
    qt_meta_data_ZN12MainWindowQtE,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_tag_ZN12MainWindowQtE_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<MainWindowQt, std::true_type>,
        // method 'on_loadImage_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'loadImage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'loadModifiedImage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QImage, std::false_type>,
        // method 'on_negative_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_greyScale_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_Contrast_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_Gamma_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_Brightnes_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_histogram_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_Stretching_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_wyrownanie_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'getPixel'
        QtPrivate::TypeAndForceComplete<QRgb, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QImage &, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<optionsOfPixelsFillingOutsideOfImage, std::false_type>,
        // method 'getWindow'
        QtPrivate::TypeAndForceComplete<QVector<QVector<int> >, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QImage &, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<optionsOfPixelsFillingOutsideOfImage, std::false_type>,
        // method 'getMask'
        QtPrivate::TypeAndForceComplete<QVector<QVector<float> >, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'join'
        QtPrivate::TypeAndForceComplete<QVector<QVector<float> >, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QVector<QVector<int>> &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QVector<QVector<float>> &, std::false_type>,
        // method 'sum'
        QtPrivate::TypeAndForceComplete<float, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QVector<QVector<float> > &, std::false_type>,
        // method 'reflection'
        QtPrivate::TypeAndForceComplete<QVector<QVector<float> >, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QVector<QVector<float>> &, std::false_type>,
        // method 'convolute'
        QtPrivate::TypeAndForceComplete<QImage, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QImage &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QVector<QVector<float>> &, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<optionsOfPixelsFillingOutsideOfImage, std::false_type>,
        // method 'on_rozmycieRownomierne_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_rozmycieGausowskie_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_Save_as_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'blackAndWhite'
        QtPrivate::TypeAndForceComplete<QImage, std::false_type>
    >,
    nullptr
} };

void MainWindowQt::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<MainWindowQt *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->on_loadImage_clicked(); break;
        case 1: _t->loadImage((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->loadModifiedImage((*reinterpret_cast< std::add_pointer_t<QImage>>(_a[1]))); break;
        case 3: _t->on_negative_clicked(); break;
        case 4: _t->on_greyScale_clicked(); break;
        case 5: _t->on_Contrast_clicked(); break;
        case 6: _t->on_Gamma_clicked(); break;
        case 7: _t->on_Brightnes_clicked(); break;
        case 8: _t->on_histogram_clicked(); break;
        case 9: _t->on_Stretching_clicked(); break;
        case 10: _t->on_wyrownanie_clicked(); break;
        case 11: { QRgb _r = _t->getPixel((*reinterpret_cast< std::add_pointer_t<QImage>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<optionsOfPixelsFillingOutsideOfImage>>(_a[4])));
            if (_a[0]) *reinterpret_cast< QRgb*>(_a[0]) = std::move(_r); }  break;
        case 12: { QList<QList<int>> _r = _t->getWindow((*reinterpret_cast< std::add_pointer_t<QImage>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[5])),(*reinterpret_cast< std::add_pointer_t<optionsOfPixelsFillingOutsideOfImage>>(_a[6])));
            if (_a[0]) *reinterpret_cast< QList<QList<int>>*>(_a[0]) = std::move(_r); }  break;
        case 13: { QList<QList<float>> _r = _t->getMask((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QList<QList<float>>*>(_a[0]) = std::move(_r); }  break;
        case 14: { QList<QList<float>> _r = _t->join((*reinterpret_cast< std::add_pointer_t<QList<QList<int>>>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QList<QList<float>>>>(_a[2])));
            if (_a[0]) *reinterpret_cast< QList<QList<float>>*>(_a[0]) = std::move(_r); }  break;
        case 15: { float _r = _t->sum((*reinterpret_cast< std::add_pointer_t<QList<QList<float>>>>(_a[1])));
            if (_a[0]) *reinterpret_cast< float*>(_a[0]) = std::move(_r); }  break;
        case 16: { QList<QList<float>> _r = _t->reflection((*reinterpret_cast< std::add_pointer_t<QList<QList<float>>>>(_a[1])));
            if (_a[0]) *reinterpret_cast< QList<QList<float>>*>(_a[0]) = std::move(_r); }  break;
        case 17: { QImage _r = _t->convolute((*reinterpret_cast< std::add_pointer_t<QImage>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QList<QList<float>>>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<optionsOfPixelsFillingOutsideOfImage>>(_a[4])));
            if (_a[0]) *reinterpret_cast< QImage*>(_a[0]) = std::move(_r); }  break;
        case 18: _t->on_rozmycieRownomierne_clicked(); break;
        case 19: _t->on_rozmycieGausowskie_clicked(); break;
        case 20: _t->on_Save_as_clicked(); break;
        case 21: { QImage _r = _t->blackAndWhite();
            if (_a[0]) *reinterpret_cast< QImage*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 14:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QList<QList<float>> >(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QList<QList<int>> >(); break;
            }
            break;
        case 15:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QList<QList<float>> >(); break;
            }
            break;
        case 16:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QList<QList<float>> >(); break;
            }
            break;
        case 17:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QList<QList<float>> >(); break;
            }
            break;
        }
    }
}

const QMetaObject *MainWindowQt::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindowQt::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ZN12MainWindowQtE.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindowQt::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 22)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 22;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 22)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 22;
    }
    return _id;
}
QT_WARNING_POP
