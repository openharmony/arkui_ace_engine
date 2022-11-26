/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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
#ifndef FOUNDATION_ACE_ADAPTER_OHOS_OSAL_TEST_UNITTEST_MOCK_MOCK_EVENT_REPORT_DATA_H
#define FOUNDATION_ACE_ADAPTER_OHOS_OSAL_TEST_UNITTEST_MOCK_MOCK_EVENT_REPORT_DATA_H
#include "base/log/event_report.h"
#include "base/memory/ace_type.h"

namespace OHOS::Ace {
class MockEventReportData : public AceType {
    DECLARE_ACE_TYPE(MockEventReportData, AceType);
public:
    MockEventReportData() = default;
    ~MockEventReportData() override = default;
    bool SendEvent(const EventInfo& eventInfo);
    bool SendJsCardRenderTimeEvent(
        const std::string& sessionID,
        const std::string& timeType,
        uint64_t timeDelay);
    bool SendComponentException(ComponentExcepType type);
    bool SendAPIChannelException(APIChannelExcepType type);
    bool SendJsException(JsExcepType type);
    bool SendAnimationException(AnimationExcepType type);
    bool SendInternalException(InternalExcepType type);
    bool SendAccessibilityException(AccessibilityExcepType type);
    bool SendFormException(FormExcepType type);
    bool JsEventReport(int32_t eventType, const std::string& jsonStr);
    bool JsErrReport(
        const std::string& packageName, const std::string& reason, const std::string& summary);
    bool ANRRawReport(RawEventType type, int32_t uid, const std::string& packageName,
        const std::string& processName, const std::string& msg);
    bool ANRShowDialog(int32_t uid, const std::string& packageName,
        const std::string& processName, const std::string& msg);
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_ADAPTER_OHOS_OSAL_TEST_UNITTEST_MOCK_MOCK_EVENT_REPORT_DATA_H