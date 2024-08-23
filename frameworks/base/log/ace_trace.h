/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_LOG_ACE_TRACE_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_LOG_ACE_TRACE_H

#include <atomic>
#include <cstdarg>
#include <cstdio>
#include <memory>
#include <string>

#include "base/utils/macros.h"
#include "base/utils/noncopyable.h"
#include "base/utils/system_properties.h"

#define ACE_SCOPED_TRACE(fmt, ...) AceScopedTrace aceScopedTrace(fmt, ##__VA_ARGS__)
#define ACE_SCOPED_TRACE_COMMERCIAL(fmt, ...) AceScopedTraceCommercial aceScopedTrace(fmt, ##__VA_ARGS__)
#define ACE_SCOPED_TRACE_FLAG(flag, fmt, ...) AceScopedTraceFlag aceScopedTraceFlag(flag, fmt, ##__VA_ARGS__)
#define ACE_SVG_SCOPED_TRACE(fmt, ...) \
    AceScopedTraceFlag aceScopedTraceFlag(SystemProperties::GetSvgTraceEnabled(), fmt, ##__VA_ARGS__)
#define ACE_TEXT_SCOPED_TRACE(fmt, ...) \
    AceScopedTraceFlag aceScopedTraceFlag(SystemProperties::GetTextTraceEnabled(), fmt, ##__VA_ARGS__)
#define ACE_SYNTAX_SCOPED_TRACE(fmt, ...) \
    AceScopedTraceFlag aceScopedTraceFlag(SystemProperties::GetSyntaxTraceEnabled(), fmt, ##__VA_ARGS__)
#define ACE_ACCESS_SCOPED_TRACE(fmt, ...) \
    AceScopedTraceFlag aceScopedTraceFlag(SystemProperties::GetAccessTraceEnabled(), fmt, ##__VA_ARGS__)
#define ACE_LAYOUT_SCOPED_TRACE(fmt, ...) \
    AceScopedTraceFlag aceScopedTraceFlag(SystemProperties::GetLayoutTraceEnabled(), fmt, ##__VA_ARGS__)
#define ACE_IMAGE_SCOPED_TRACE(fmt, ...) \
    AceScopedTraceFlag aceScopedTraceFlag(SystemProperties::GetDebugEnabled(), fmt, ##__VA_ARGS__)
#ifdef ACE_DEBUG
#define ACE_DEBUG_SCOPED_TRACE(fmt, ...) AceScopedTrace aceScopedTrace(fmt, ##__VA_ARGS__)
#else
#define ACE_DEBUG_SCOPED_TRACE(fmt, ...)
#endif

#define ACE_LAYOUT_TRACE_BEGIN(fmt, ...) \
    if (SystemProperties::GetLayoutTraceEnabled()) { \
        AceTraceBeginWithArgs(fmt, ##__VA_ARGS__); \
    }
#define ACE_LAYOUT_TRACE_END() \
    if (SystemProperties::GetLayoutTraceEnabled()) { \
        AceTraceEnd(); \
    }

// Enable trace for component creation and attribute settings
#define ACE_BUILD_TRACE_BEGIN(fmt, ...) \
    if (SystemProperties::GetBuildTraceEnabled()) { \
        AceTraceBeginWithArgs(fmt, ##__VA_ARGS__); \
    }
#define ACE_BUILD_TRACE_END() \
    if (SystemProperties::GetBuildTraceEnabled()) { \
        AceTraceEnd(); \
    }

#define CHECK_NULL_VOID_LAYOUT_TRACE_END(ptr) \
    do {                           \
        if (!(ptr)) {              \
            if (SystemProperties::GetLayoutTraceEnabled()) { \
                AceTraceEnd();     \
            }                      \
            return;                \
        }                          \
    } while (0)                    \

#define ACE_FUNCTION_TRACE() ACE_SCOPED_TRACE(__func__)

#define ACE_COUNT_TRACE(count, fmt, ...) AceCountTraceWidthArgs(count, fmt, ##__VA_ARGS__)

namespace OHOS::Ace {
bool ACE_EXPORT AceAsyncTraceEnable();
void ACE_EXPORT AceTraceBegin(const char* name);
void ACE_EXPORT AceAsyncTraceBegin(int32_t taskId, const char* name, bool isAnimationTrace = false);
bool ACE_EXPORT AceTraceBeginWithArgs(const char* format, ...) __attribute__((__format__(printf, 1, 2)));
std::string ACE_EXPORT AceAsyncTraceBeginWithArgs(int32_t taskId, char* format, ...);
bool ACE_EXPORT AceTraceBeginWithArgv(const char* format, va_list args);
std::string ACE_EXPORT AceAsyncTraceBeginWithArgv(int32_t taskId, const char* format, va_list args);
void ACE_EXPORT AceTraceEnd();
void ACE_EXPORT AceAsyncTraceEnd(int32_t taskId, const char* name, bool isAnimationTrace = false);
void ACE_EXPORT AceCountTrace(const char *key, int32_t count);
void ACE_EXPORT AceCountTraceWidthArgs(int32_t count, const char* format, ...);

// for commercial trace
void ACE_EXPORT AceTraceBeginCommercial(const char* name);
void ACE_EXPORT AceTraceEndCommercial();
void ACE_EXPORT AceAsyncTraceBeginCommercial(int32_t taskId, const char* name, bool isAnimationTrace = false);
void ACE_EXPORT AceAsyncTraceEndCommercial(int32_t taskId, const char* name, bool isAnimationTrace = false);

class ACE_FORCE_EXPORT AceScopedTrace final {
public:
    explicit AceScopedTrace(const char* format, ...) __attribute__((__format__(printf, 2, 3)));
    ~AceScopedTrace();

    ACE_DISALLOW_COPY_AND_MOVE(AceScopedTrace);
private:
    bool strValid_ = false;
};

class ACE_FORCE_EXPORT AceScopedTraceCommercial final {
public:
    explicit AceScopedTraceCommercial(const char* format, ...) __attribute__((__format__(printf, 2, 3)));
    ~AceScopedTraceCommercial();

    ACE_DISALLOW_COPY_AND_MOVE(AceScopedTraceCommercial);
private:
    bool strValid_ = false;
};

class ACE_FORCE_EXPORT AceScopedTraceFlag final {
public:
    AceScopedTraceFlag(bool flag, const char* format, ...) __attribute__((__format__(printf, 3, 4)));
    ~AceScopedTraceFlag();

    ACE_DISALLOW_COPY_AND_MOVE(AceScopedTraceFlag);

private:
    bool flagTraceEnabled_ { false };
};

class ACE_EXPORT AceAsyncScopedTrace final {
public:
    AceAsyncScopedTrace(const char* format, ...);
    ~AceAsyncScopedTrace();

    ACE_DISALLOW_COPY_AND_MOVE(AceAsyncScopedTrace);

private:
    std::string name_;
    int32_t taskId_;
    static std::atomic<std::int32_t> id_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_LOG_ACE_TRACE_H
