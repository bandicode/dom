// Copyright (C) 2019 Vincent Chambrin
// This file is part of the 'dom' project
// For conditions of distribution and use, see copyright notice in LICENSE

#ifndef DOM_DEFS_H
#define DOM_DEFS_H

#if (defined(WIN32) || defined(_WIN32)) && !defined(DOM_LIB_STATIC_LINKING)

#if defined(DOM_BUILD_LIB)
#  define DOM_API __declspec(dllexport)
#else
#  define DOM_API __declspec(dllimport)
#endif

#else

#  define DOM_API

#endif

#endif // DOM_DEFS_H
