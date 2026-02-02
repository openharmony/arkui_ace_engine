/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "adapter/ohos/entrance/ui_session/include/ui_session_trace.h"

#include "hitrace_meter.h"

#include "base/utils/utils.h"

#include "securec.h"

namespace OHOS::Ace {
namespace {
const size_t MAX_STRING_SIZE = 512;
}

void UiSessionTraceBegin(const char* name)
{
    CHECK_NULL_VOID(name);
    std::string nameStr(name);
    StartTrace(HITRACE_TAG_ACE, nameStr);
}

void UiSessionTraceEnd()
{
    FinishTrace(HITRACE_TAG_ACE);
}

bool UiSessionTraceBeginWithArgv(const char* format, va_list args)
{
    char name[MAX_STRING_SIZE] = { 0 };
    if (vsnprintf_s(name, sizeof(name), sizeof(name) - 1, format, args) < 0) {
        return false;
    }
    UiSessionTraceBegin(name);
    return true;
}

UiSessionScopedTrace::UiSessionScopedTrace(const char* format, ...)
{
    va_list args;
    va_start(args, format);
    strValid_ = UiSessionTraceBeginWithArgv(format, args);
    va_end(args);
}

UiSessionScopedTrace::~UiSessionScopedTrace()
{
    if (strValid_) {
        UiSessionTraceEnd();
    }
}
} // namespace OHOS::Ace
