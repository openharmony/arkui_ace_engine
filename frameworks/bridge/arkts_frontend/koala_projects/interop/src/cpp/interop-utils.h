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
#include <cstdio>
#include <climits>
#include "interop-logging.h"
#include "securec.h"

inline errno_t InteropStringCopy(char *dest, size_t destSize, const char *src)
{
    errno_t ret = strcpy_s(dest, destSize, src);
    if (ret > 0) {
        LOGE("strcpy_s error code: %d", ret);
    }
    return ret;
}

inline errno_t interop_string_concatenate(char *dest, size_t destSize, const char *src)
{
    errno_t ret = strcat_s(dest, destSize, src);
    if (ret > 0) {
        LOGE("strcat_s error code: %d", ret);
    }
    return ret;
}

inline errno_t interop_memory_copy(void *dest, size_t destSize, const void *src, size_t count)
{
    errno_t ret = memcpy_s(dest, destSize, src, count);
    if (ret > 0) {
        LOGE("memcpy_s error code: %d", ret);
    }
    return ret;
}

inline errno_t interop_memory_set(void *dest, size_t destSize, int ch, size_t count)
{
    errno_t ret = memset_s(dest, destSize, ch, count);
    if (ret > 0) {
        LOGE("memset_s error code: %d", ret);
    }
    return ret;
}

template <typename... T>
inline int InteropPrintToBuffer(char *buffer, size_t bufSize, const char *format, T... args)
{
    int ret = sprintf_s(buffer, bufSize, format, args...);
    if (ret < 0) {
        INTEROP_FATAL("WriteToString: sprintf_s format failed! Error code: %d", ret);
    }
    return ret;
}

template <typename... T>
inline int InteropPrintToBufferN(char *buffer, size_t bufSize, const char *format, T... args)
{
    int ret = snprintf_s(buffer, bufSize, bufSize - 1, format, args...);
    if (ret < 0) {
        INTEROP_FATAL("WriteToString: snprintf_s format failed! Error code: %d", ret);
    }
    return ret;
}

inline int InteropPrintVlistToBufferN(char *buffer, size_t bufSize, const char *format, va_list vlist)
{
    int ret = vsnprintf_s(buffer, bufSize, bufSize - 1, format, vlist);
    if (ret == EINVAL) {
        LOGE("log format failed");
    } else {
        LOGE("FATAL: %{public}s", buffer);
    }
    return ret;
}

#endif // _INTEROP_UTILS_H_