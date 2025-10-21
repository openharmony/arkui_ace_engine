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

#include "trace_ani_modifier.h"

#include "base/log/ace_trace.h"
#include "frameworks/base/utils/system_properties.h"

namespace OHOS::Ace::NG {

namespace TraceAniModifier {

bool GetAttributeSetTraceEnabled()
{
    return SystemProperties::GetAttributeSetTraceEnabled();
}

void TraceBegin(const std::string& traceName)
{
    AceTraceBeginWithArgs("%s", traceName.c_str());
}

void TraceEnd()
{
    AceTraceEnd();
}

void AsyncTraceBegin(const std::string& traceName, int taskId)
{
    AceAsyncTraceBegin(taskId, traceName.c_str(), false);
}

void AsyncTraceEnd(const std::string& traceName, int taskId)
{
    AceAsyncTraceEnd(taskId, traceName.c_str(), false);
}

} // namespace TraceAniModifier

const ArkUIAniTraceModifier* GetTraceAniModifier()
{
    static ArkUIAniTraceModifier impl = {
        .getAttributeSetTraceEnabled = TraceAniModifier::GetAttributeSetTraceEnabled,
        .traceBegin = TraceAniModifier::TraceBegin,
        .traceEnd = TraceAniModifier::TraceEnd,
        .asyncTraceBegin = TraceAniModifier::AsyncTraceBegin,
        .asyncTraceEnd = TraceAniModifier::AsyncTraceEnd,
    };

    return &impl;
}

} // namespace OHOS::Ace::NG
