//CoreTypes.h
//Created 12/01/18
//Created By Daniel Bowler
//
//Types

#pragma once

#include <stdint.h>

#ifdef PLATFORM_WINDOWS
typedef signed char         int8,   *pint8;
typedef signed short        int16,  *pint16;
typedef signed int          int32,  *pint32;
typedef signed __int64      int64,  *pint64;
typedef unsigned char       uint8,  *puint8;
typedef unsigned short      uint16, *puint16;
typedef unsigned int        uint32, *puint32;
typedef unsigned __int64    uint64, *puint64;
#endif