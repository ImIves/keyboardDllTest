#ifndef KEYBOARD_GLOBAL_H
#define KEYBOARD_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(KEYBOARD_LIBRARY)
#  define KEYBOARDSHARED_EXPORT Q_DECL_EXPORT
#else
#  define KEYBOARDSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // KEYBOARD_GLOBAL_H
