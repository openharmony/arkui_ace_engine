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

#include "base/log/ace_trace.h"

#include "hitrace_meter.h"

#include "base/utils/utils.h"

namespace OHOS::Ace {
namespace {
static constexpr uint64_t ACE_TRACE_COMMERCIAL = HITRACE_TAG_ACE | HITRACE_TAG_COMMERCIAL;
static constexpr uint64_t ANIMATION_TRACE_COMMERCIAL = HITRACE_TAG_ANIMATION | HITRACE_TAG_COMMERCIAL;
}

void AceTraceBegin(const char* name)
{
    CHECK_NULL_VOID(name);
    std::string nameStr(name);
    StartTrace(HITRACE_TAG_ACE, nameStr);
}

void AceTraceEnd()
{
    FinishTrace(HITRACE_TAG_ACE);
}

void AceTraceBeginCommercial(const char* name)
{
    StartTraceEx(HITRACE_LEVEL_COMMERCIAL, ACE_TRACE_COMMERCIAL, name);
}

void AceTraceEndCommercial()
{
    FinishTraceEx(HITRACE_LEVEL_COMMERCIAL, ACE_TRACE_COMMERCIAL);
}

void AceAsyncTraceBegin(int32_t taskId, const char* name, bool isAnimationTrace)
{
    CHECK_NULL_VOID(name);
    std::string nameStr(name);
    if (isAnimationTrace) {
        StartAsyncTrace(HITRACE_TAG_ANIMATION, nameStr, taskId);
    } else {
        StartAsyncTrace(HITRACE_TAG_ACE, nameStr, taskId);
    }
}

void AceAsyncTraceEnd(int32_t taskId, const char* name, bool isAnimationTrace)
{
    CHECK_NULL_VOID(name);
    std::string nameStr(name);
    if (isAnimationTrace) {
        FinishAsyncTrace(HITRACE_TAG_ANIMATION, nameStr, taskId);
    } else {
        FinishAsyncTrace(HITRACE_TAG_ACE, nameStr, taskId);
    }
}

void AceAsyncTraceBeginCommercial(int32_t taskId, const char* name, bool isAnimationTrace)
{
    CHECK_NULL_VOID(name);
    std::string nameStr(name);
    if (isAnimationTrace) {
        StartAsyncTrace(ANIMATION_TRACE_COMMERCIAL, nameStr, taskId);
    } else {
        StartAsyncTrace(ACE_TRACE_COMMERCIAL, nameStr, taskId);
    }
}

void AceAsyncTraceEndCommercial(int32_t taskId, const char* name, bool isAnimationTrace)
{
    CHECK_NULL_VOID(name);
    std::string nameStr(name);
    if (isAnimationTrace) {
        FinishAsyncTrace(ANIMATION_TRACE_COMMERCIAL, nameStr, taskId);
    } else {
        FinishAsyncTrace(ACE_TRACE_COMMERCIAL, nameStr, taskId);
    }
}

void AceCountTrace(const char *key, int32_t count)
{
    CHECK_NULL_VOID(key);
    std::string keyStr(key);
    CountTrace(HITRACE_TAG_ACE, keyStr, count);
}
} // namespace OHOS::Ace
