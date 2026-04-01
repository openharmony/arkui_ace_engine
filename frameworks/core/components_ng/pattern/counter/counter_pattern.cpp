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

#include "core/components_ng/pattern/counter/counter_pattern.h"
#include "interfaces/inner_api/ui_session/ui_session_manager.h"

namespace OHOS::Ace::NG {

void CounterPattern::SetCounterOnInc()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto counterPattern = DynamicCast<CounterPattern>(host->GetPattern());
    CHECK_NULL_VOID(counterPattern);
    auto addId = counterPattern->GetAddId();
    auto addNode = DynamicCast<FrameNode>(host->GetChildAtIndex(host->GetChildIndexById(addId)));
    CHECK_NULL_VOID(addNode);
    auto gestureHub = addNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    auto onIncClickEventFunc = gestureHub->GetClickEvent();
    CHECK_NULL_VOID(onIncClickEventFunc);
    GestureEvent info;
    onIncClickEventFunc(info);
}

void CounterPattern::SetCounterOnDec()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto counterPattern = DynamicCast<CounterPattern>(host->GetPattern());
    CHECK_NULL_VOID(counterPattern);
    auto subId = counterPattern->GetSubId();
    auto subNode = DynamicCast<FrameNode>(host->GetChildAtIndex(host->GetChildIndexById(subId)));
    CHECK_NULL_VOID(subNode);
    auto gestureHub = subNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    auto onDecClickEventFunc = gestureHub->GetClickEvent();
    CHECK_NULL_VOID(onDecClickEventFunc);
    GestureEvent info;
    onDecClickEventFunc(info);
}

static std::string ParseCommand(const std::string& command)
{
    auto json = JsonUtil::ParseJsonString(command);
    if (!json || json->IsNull()) {
        return std::string();
    }

    return json->GetString("cmd");
}

int32_t CounterPattern::OnInjectionEvent(const std::string& command)
{
    std::string cmdType = ParseCommand(command);
    if (cmdType == "setCounterOnInc") {
        SetCounterOnInc();
    } else if (cmdType == "setCounterOnDec") {
        SetCounterOnDec();
    } else {
        TAG_LOGD(AceLogTag::ACE_COUNTER, "unknown cmd: %{public}s", cmdType.c_str());
        return RET_FAILED;
    }
    return RET_SUCCESS;
}

} // namespace OHOS::Ace::NG