#ifndef CMLIB_GLOBAL_H
#define CMLIB_GLOBAL_H

#include <QtCore/qglobal.h>

// This file defines the CMLIB_EXPORT macro (with the help of CMLIB_LIBRARY) which would be used to exprot contents of
// this library to other subprojects

#if defined(CMLIB_LIBRARY)
#define CMLIB_EXPORT Q_DECL_EXPORT
#else
#define CMLIB_EXPORT Q_DECL_IMPORT
#endif

#endif // CMLIB_GLOBAL_H
