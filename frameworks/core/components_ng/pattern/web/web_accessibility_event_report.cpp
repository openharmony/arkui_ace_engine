/*
 * Copyright (C) 2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/web/web_accessibility_event_report.h"

#include <algorithm>
#include <string>
#include <vector>

#include "core/components_ng/pattern/web/web_pattern.h"
#include "core/components/web/resource/web_delegate.h"
#include "interfaces/inner_api/ui_session/ui_session_manager.h"

namespace OHOS::Ace::NG {

namespace {
constexpr char FOCUS_SYMBOL[] = "focus";
constexpr char BLUR_SYMBOL[] = "blur";
constexpr char TEXT_CHANGE_SYMBOL[] = "textChange";
constexpr char PASSWORD_PLACEHOLDER[] = "*";
}

WebAccessibilityEventReport::WebAccessibilityEventReport(const WeakPtr<Pattern>& pattern)
{
    pattern_ = pattern;
}

void WebAccessibilityEventReport::RegisterAllReportEventCallBack()
{
    TAG_LOGI(AceLogTag::ACE_WEB, "WebAccessibilityEventReport::RegisterAllReportEventCallBack");
    auto focusCallback = [](int64_t accessibilityId, const std::string data) {
        UiSessionManager::GetInstance()->ReportWebUnfocusEvent(accessibilityId, data, FOCUS_SYMBOL);
    };
    auto blurCallback = [](int64_t accessibilityId, const std::string data) {
        UiSessionManager::GetInstance()->ReportWebUnfocusEvent(accessibilityId, data, BLUR_SYMBOL);
    };
    auto textChangeCallback = [](int64_t accessibilityId, const std::string data) {
        UiSessionManager::GetInstance()->ReportWebUnfocusEvent(accessibilityId, data, TEXT_CHANGE_SYMBOL);
    };
    RegisterCallback(std::move(focusCallback), AccessibilityEventType::FOCUS);
    RegisterCallback(std::move(blurCallback), AccessibilityEventType::BLUR);
    RegisterCallback(std::move(textChangeCallback), AccessibilityEventType::TEXT_CHANGE);
}

void WebAccessibilityEventReport::RegisterCallback(EventReportCallback&& callback, AccessibilityEventType type)
{
    CHECK_NULL_VOID(callback);
    switch (type) {
        case AccessibilityEventType::FOCUS:
            textFocusCallback_ = std::move(callback);
            break;
        case AccessibilityEventType::BLUR:
            textBlurCallback_ = std::move(callback);
            break;
        case AccessibilityEventType::TEXT_CHANGE:
            textChangeCallback_ = std::move(callback);
            break;
        default:
            return;
    }
    auto webPattern = DynamicCast<WebPattern>(pattern_.Upgrade());
    CHECK_NULL_VOID(webPattern);
    webPattern->SetAccessibilityState(true);
    webPattern->SetTextEventAccessibilityEnable(true);
}

void WebAccessibilityEventReport::UnRegisterCallback()
{
    TAG_LOGI(AceLogTag::ACE_WEB, "WebAccessibilityEventReport::UnRegisterCallback");
    textFocusCallback_ = nullptr;
    textBlurCallback_ = nullptr;
    textChangeCallback_ = nullptr;
    auto webPattern = DynamicCast<WebPattern>(pattern_.Upgrade());
    CHECK_NULL_VOID(webPattern);
    webPattern->SetTextEventAccessibilityEnable(false);
    webPattern->SetAccessibilityState(false);
}

void WebAccessibilityEventReport::ReportEvent(AccessibilityEventType type, int64_t accessibilityId)
{
    TAG_LOGD(
        AceLogTag::ACE_WEB, "WebAccessibilityEventReport::ReportEvent type = %{public}zu", static_cast<size_t>(type));
    if (type == AccessibilityEventType::FOCUS) {
        ReportTextBlurEventByFocus(accessibilityId);
        CheckAccessibilityNodeAndReport(AccessibilityEventType::FOCUS, accessibilityId);
        return;
    }
    if (type == AccessibilityEventType::BLUR) {
        if (accessibilityId == lastFocusReportId_) {
            TAG_LOGI(AceLogTag::ACE_WEB, "WebAccessibilityEventReport::ReportEvent ignore same blur node");
            return;
        }
        CheckAccessibilityNodeAndReport(AccessibilityEventType::BLUR, accessibilityId);
        return;
    }
    if (type == AccessibilityEventType::TEXT_CHANGE) {
        CheckAccessibilityNodeAndReport(AccessibilityEventType::TEXT_CHANGE, accessibilityId);
        return;
    }
}

void WebAccessibilityEventReport::ReportTextBlurEventByFocus(int64_t accessibilityId)
{
    if (lastFocusInputId_ != accessibilityId) {
        CheckAccessibilityNodeAndReport(AccessibilityEventType::BLUR, lastFocusInputId_);
        lastFocusReportId_ = lastFocusInputId_;
    }
    if (accessibilityId != 0) {
        auto webPattern = DynamicCast<WebPattern>(pattern_.Upgrade());
        CHECK_NULL_VOID(webPattern);
        auto focusNode = webPattern->GetAccessibilityNodeById(accessibilityId);
        if (focusNode) {
            // record last editable focus id
            lastFocusInputId_ = accessibilityId;
        }
    }
}

void WebAccessibilityEventReport::CheckAccessibilityNodeAndReport(AccessibilityEventType type, int64_t accessibilityId)
{
    TAG_LOGI(AceLogTag::ACE_WEB, "WebAccessibilityEventReport::CheckAccessibilityNodeAndReport type = %{public}zu",
        static_cast<size_t>(type));
    auto webPattern = DynamicCast<WebPattern>(pattern_.Upgrade());
    CHECK_NULL_VOID(webPattern);
    auto accessibiliyNode = webPattern->GetAccessibilityNodeById(accessibilityId);
    CHECK_NULL_VOID(accessibiliyNode);
    std::string nodeText = accessibiliyNode->GetContent();
    if (accessibiliyNode->GetIsEditable()) {
        if (accessibiliyNode->GetIsPassword()) {
            nodeText = PASSWORD_PLACEHOLDER;
        }
        switch (type) {
            case AccessibilityEventType::FOCUS:
                CHECK_NULL_VOID(textFocusCallback_);
                textFocusCallback_(accessibilityId, nodeText);
                TAG_LOGD(AceLogTag::ACE_WEB, "report text focus, the content length is %{public}u",
                    static_cast<int32_t>(nodeText.length()));
                break;
            case AccessibilityEventType::BLUR:
                CHECK_NULL_VOID(textBlurCallback_);
                textBlurCallback_(accessibilityId, nodeText);
                TAG_LOGD(AceLogTag::ACE_WEB, "report text blur, the content length is %{public}u",
                    static_cast<int32_t>(nodeText.length()));
                break;
            case AccessibilityEventType::TEXT_CHANGE:
                CHECK_NULL_VOID(textChangeCallback_);
                textChangeCallback_(accessibilityId, nodeText);
                TAG_LOGD(AceLogTag::ACE_WEB, "report text change, the content length is %{public}u",
                    static_cast<int32_t>(nodeText.length()));
                return;
            default:
                return;
        }
    }
}
} // namespace OHOS::Ace::NG
