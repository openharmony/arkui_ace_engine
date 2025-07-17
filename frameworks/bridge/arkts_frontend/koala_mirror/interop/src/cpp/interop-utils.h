/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _INTEROP_UTILS_H_
#define _INTEROP_UTILS_H_

#include <cstring>
#include <stdio.h>

#ifdef __STDC_LIB_EXT1__
    #include "securec.h"
    #define USE_SAFE(name, ...) name##_s(__VA_ARGS__)
#else
    #define USE_SAFE(name, ...) name(__VA_ARGS__)
#endif

inline char *interop_strcpy(char *dest, size_t destsz, const char *src)
{
#ifdef __STDC_LIB_EXT1__
    return reinterpret_cast<char(*)>(USE_SAFE(strcpy, dest, reinterpret_cast<rsize_t>(destsz), src));
#else
    return USE_SAFE(strcpy, dest, src);
#endif
}

inline char *interop_strcat(char *dest, size_t destsz, const char *src)
{
#ifdef __STDC_LIB_EXT1__
    return reinterpret_cast<char(*)>(USE_SAFE(strcat, dest, reinterpret_cast<rsize_t>(destsz), src));
#else
    return USE_SAFE(strcat, dest, src);
#endif
}

inline void *interop_memcpy(void *dest, size_t destsz, const void *src, size_t count)
{
#ifdef __STDC_LIB_EXT1__
    return reinterpret_cast<void(*)>(USE_SAFE(memcpy, dest, reinterpret_cast<rsize_t>(destsz), src, count));
#else
    return USE_SAFE(memcpy, dest, src, count);
#endif
}

inline void *interop_memset(void *dest, size_t destsz, int ch, size_t count)
{
#ifdef __STDC_LIB_EXT1__
    return reinterpret_cast<void(*)>(USE_SAFE(memset, dest, reinterpret_cast<rsize_t>(destsz), ch, count))
#else
    return USE_SAFE(memset, dest, ch, count);
#endif
}

template <typename... T>
inline int interop_sprintf(char *buffer, size_t bufsz, const char *format, T... args)
{
#ifdef __STDC_LIB_EXT1__
    return USE_SAFE(sprintf, buffer, reinterpret_cast<rsize_t>(bufsz), format, args...);
#else
    return USE_SAFE(sprintf, buffer, format, args...);
#endif
}

template <typename... T>
inline int interop_snprintf(char *buffer, size_t bufsz, const char *format, T... args)
{
    return USE_SAFE(snprintf, buffer, bufsz, format, args...);
}

inline int interop_vsnprintf(char *buffer, size_t bufsz, const char *format, va_list vlist)
{
    return USE_SAFE(vsnprintf, buffer, bufsz, format, vlist);
}

inline size_t interop_strlen(const char *str)
{
#ifdef __STDC_LIB_EXT1__
    return USE_SAFE(strlen, str, sizeof(str) - 1);
#else
    return USE_SAFE(strlen, str);
#endif
}

#endif // _INTEROP_UTILS_H_