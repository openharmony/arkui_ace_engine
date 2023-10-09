/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "base/log/ace_trace.h"

namespace OHOS::Ace {
bool AceTraceEnabled()
{
    return true;
}

void AceTraceBegin(const char* name) {}

void AceTraceEnd() {}

void AceAsyncTraceBegin(int32_t taskId, const char* name) {}

void AceAsyncTraceEnd(int32_t taskId, const char* name) {}

void AceCountTrace(const char* key, int32_t count) {}

bool AceTraceBeginWithArgv(const char* format, va_list args)
{
    return false;
}

bool AceTraceBeginWithArgs(const char* format, ...)
{
    return false;
}

void AceCountTraceWidthArgs(int32_t count, const char* format, ...) {}

AceScopedTrace::AceScopedTrace(const char* format, ...) : traceEnabled_(AceTraceEnabled()) {}

AceScopedTrace::~AceScopedTrace() = default;

AceScopedTraceFlag::AceScopedTraceFlag(bool flag, const char* format, ...) {}

AceScopedTraceFlag::~AceScopedTraceFlag()
{
    if (flagTraceEnabled_) {
        AceTraceEnd();
    }
}

std::string ACE_EXPORT AceAsyncTraceBeginWithArgv(int32_t taskId, const char* format, va_list args)
{
    return {};
}

std::string ACE_EXPORT AceAsyncTraceBeginWithArgs(int32_t taskId, char* format, ...)
{
    return {};
}

std::atomic<std::int32_t> AceAsyncScopedTrace::id_ = 0;

AceAsyncScopedTrace::AceAsyncScopedTrace(const char* format, ...)
{
    id_++;
    if (asyncTraceEnabled_) {
        taskId_ = id_;
    }
}

AceAsyncScopedTrace::~AceAsyncScopedTrace() = default;
} // namespace OHOS::Ace
