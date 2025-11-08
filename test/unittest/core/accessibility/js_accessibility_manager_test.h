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

#ifndef TEST_UNITTEST_CORE_ACCESSIBILITY_JS_ACCESSIBILITY_MANAGER_TEST_H
#define TEST_UNITTEST_CORE_ACCESSIBILITY_JS_ACCESSIBILITY_MANAGER_TEST_H

#include "accessibility_system_ability_client.h"
#include "adapter/ohos/osal/js_accessibility_manager.h"

namespace OHOS::Ace {

class MockAccessibilityElementOperatorCallback : public Accessibility::AccessibilityElementOperatorCallback {
public:
    ~MockAccessibilityElementOperatorCallback() = default;

    void SetSearchElementInfoByAccessibilityIdResult(const std::list<Accessibility::AccessibilityElementInfo> &infos,
        const int32_t requestId)  override
    {
        mockInfos_ = infos;
        mockRequestId = requestId;
    }

    void SetSearchElementInfoByTextResult(const std::list<Accessibility::AccessibilityElementInfo> &infos,
        const int32_t requestId) override
    {
        mockInfos_ = infos;
        mockRequestId = requestId;
    }

    void SetSearchDefaultFocusByWindowIdResult(const std::list<Accessibility::AccessibilityElementInfo> &infos,
        const int32_t requestId) override
    {
        mockInfos_ = infos;
        mockRequestId = requestId;
    }

    void SetFindFocusedElementInfoResult(
        const Accessibility::AccessibilityElementInfo &info,
        const int32_t requestId) override
    {
        mockInfo_ = info;
        mockRequestId = requestId;
    }

    void SetFocusMoveSearchResult(const Accessibility::AccessibilityElementInfo &info, const int32_t requestId) override
    {
        mockInfo_ = info;
        mockRequestId = requestId;
    }

    void SetExecuteActionResult(const bool succeeded, const int32_t requestId) override
    {
        mockSucceeded_ = succeeded;
        mockRequestId = requestId;
    }

    void SetCursorPositionResult(const int32_t cursorPosition, const int32_t requestId) override
    {
        mockCursorPosition_ = cursorPosition;
        mockRequestId = requestId;
    }

    void SetSearchElementInfoBySpecificPropertyResult(const std::list<Accessibility::AccessibilityElementInfo> &infos,
        const std::list<Accessibility::AccessibilityElementInfo> &treeInfos, const int32_t requestId) override
    {
        mockInfos_ = infos;
        mockRequestId = requestId;
    }

    void SetFocusMoveSearchWithConditionResult(const std::list<Accessibility::AccessibilityElementInfo> &info,
        const Accessibility::FocusMoveResult &result, const int32_t requestId) override
    {
        mockInfos_ = info;
        mockResult_ = result;
        mockRequestId = requestId;
    }

    std::list<Accessibility::AccessibilityElementInfo> mockInfos_;
    Accessibility::AccessibilityElementInfo mockInfo_;
    Accessibility::FocusMoveResult mockResult_;
    int32_t mockRequestId = 0;
    bool mockSucceeded_ = false;
    bool mockFocusable_ = false;
    int32_t mockCursorPosition_ = 0;
};
}  // namespace OHOS::Ace

#endif // TEST_UNITTEST_CORE_ACCESSIBILITY_JS_ACCESSIBILITY_MANAGER_TEST_H