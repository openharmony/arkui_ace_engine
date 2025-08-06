/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WEB_ACCESSIBILITY_EVENT_REPORT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WEB_ACCESSIBILITY_EVENT_REPORT_H

#include <list>

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/web/web_property.h"

namespace OHOS::Ace::NG {

using EventReportCallback = std::function<void(int64_t, const std::string)>;

class WebAccessibilityEventReport : public AceType {
    DECLARE_ACE_TYPE(WebAccessibilityEventReport, AceType);
public:
    explicit WebAccessibilityEventReport(const WeakPtr<Pattern>& pattern);

    void RegisterAllReportEventCallBack();
    void RegisterCallback(EventReportCallback&& callback, AccessibilityEventType type);
    void UnRegisterCallback();

    void ReportEvent(AccessibilityEventType type, int64_t accessibilityId);
    void ReportTextBlurEventByFocus(int64_t accessibilityId);

private:
    void CheckAccessibilityNodeAndReport(AccessibilityEventType type, int64_t accessibilityId);

    WeakPtr<Pattern> pattern_;
    int64_t lastFocusInputId_ = 0;
    int64_t lastFocusReportId_ = 0;  // last report blur id by focus event
    EventReportCallback textFocusCallback_ = nullptr;
    EventReportCallback textBlurCallback_ = nullptr;
    EventReportCallback textChangeCallback_ = nullptr;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WEB_ACCESSIBILITY_EVENT_REPORT_H