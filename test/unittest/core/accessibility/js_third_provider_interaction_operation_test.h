/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef TEST_UNITTEST_CORE_ACCESSIBILITY_JS_THIRD_PROVIDER_INTERACTION_OPERATION_TEST_H
#define TEST_UNITTEST_CORE_ACCESSIBILITY_JS_THIRD_PROVIDER_INTERACTION_OPERATION_TEST_H

#include "adapter/ohos/osal/js_third_provider_interaction_operation.h"

namespace OHOS::Ace {
constexpr int32_t MAX_TEST_ELEMENT_COUNT = 10;
constexpr int32_t TEST_PARAMETER_OFFSET1 = 1;
constexpr int32_t TEST_PARAMETER_OFFSET2 = 2;
constexpr int32_t TEST_PARAMETER_OFFSET3 = 3;
constexpr int32_t SPECIAL_CURSOR_POSTION = 100;
constexpr int32_t INVALID_PARENT_ID = -2100000;

class ProviderMockResult {
    public:
        ProviderMockResult()
        {
            for (int32_t i = 0; i < MAX_TEST_ELEMENT_COUNT; i++) {
                ArkUI_AccessibilityElementInfo tempElementInfo;
                tempElementInfo.SetElementId(i);
                tempElementInfo.SetContents("testForFindByText");
                if (i < MAX_TEST_ELEMENT_COUNT - 1) {
                    tempElementInfo.AddChildNodeId(i + 1);
                }

                if (i > 0) {
                    tempElementInfo.SetParentId(i - 1);
                } else {
                    tempElementInfo.SetParentId(INVALID_PARENT_ID);
                }

                elementInfosList_.push_back(tempElementInfo);
            }

            focusElementInfo_.SetElementId(
                MAX_TEST_ELEMENT_COUNT + TEST_PARAMETER_OFFSET1);
            nextFocusElementInfo_.SetElementId(
                MAX_TEST_ELEMENT_COUNT + TEST_PARAMETER_OFFSET2);

            originActionArguments_.emplace("action0", "1");
            originActionArguments_.emplace("action1", "2");
            cursorPosition_ = MAX_TEST_ELEMENT_COUNT + TEST_PARAMETER_OFFSET3;
        }
        ~ProviderMockResult() = default;

        void Reset()
        {
            elementId_ = 0;
            mode_ = static_cast<int32_t>(ARKUI_ACCESSIBILITY_NATIVE_SEARCH_MODE_PREFETCH_CURRENT);
            requestId_ = 0;
            focusType_ = ARKUI_ACCESSIBILITY_NATIVE_FOCUS_TYPE_INVALID;
            direction_ = ARKUI_ACCESSIBILITY_NATIVE_DIRECTION_INVALID;
            action_ = ARKUI_ACCESSIBILITY_NATIVE_ACTION_TYPE_INVALID;
            receiveClear_ = false;
            errorCode_ = 0;
            injectResult_ = 0;
            injectActionResult_ = 0;
        }

    public:
        int64_t elementId_;
        int32_t mode_;
        int32_t requestId_;
        std::vector<ArkUI_AccessibilityElementInfo> elementInfosList_;
        ArkUI_AccessibilityFocusType focusType_;
        ArkUI_AccessibilityElementInfo focusElementInfo_;
        ArkUI_AccessibilityElementInfo nextFocusElementInfo_;
        ArkUI_AccessibilityFocusMoveDirection direction_;
        ArkUI_Accessibility_ActionType action_;
        std::map<std::string, std::string> originActionArguments_;
        std::map<std::string, std::string> resultActionArguments_;
        int32_t cursorPosition_;
        bool receiveClear_;

        bool registerResult_;

        int32_t errorCode_;
        int32_t injectResult_ = 0;
        int32_t injectActionResult_ = 0;
        ArkUI_AccessibilityElementInfo elementInfo_;
};

class MockOhAccessibilityProvider : public AccessibilityProvider {
    DECLARE_ACE_TYPE(MockOhAccessibilityProvider, AccessibilityProvider);
public:
    MockOhAccessibilityProvider() = default;
    int32_t FindAccessibilityNodeInfosById(
        const int64_t elementId, const int32_t mode, const int32_t requestId,
        std::vector<ArkUI_AccessibilityElementInfo>& infos) override
    {
        providerMockResult_.elementId_ = elementId;
        providerMockResult_.mode_ = mode;
        providerMockResult_.requestId_ = requestId;
        int64_t startElementId = elementId;
        if (startElementId == -1) {
            startElementId = 0;
        }

        if (startElementId >= MAX_TEST_ELEMENT_COUNT) {
            return -1;
        }

        if (mode == static_cast<uint32_t>(Accessibility::PREFETCH_RECURSIVE_CHILDREN)) {
            std::vector<ArkUI_AccessibilityElementInfo>::iterator start
                = providerMockResult_.elementInfosList_.begin() + startElementId;
            std::vector<ArkUI_AccessibilityElementInfo>::iterator end = providerMockResult_.elementInfosList_.end();
            infos.reserve(std::distance(start, end));
            std::copy(start, end, std::back_inserter(infos));
        } else {
            infos.push_back(providerMockResult_.elementInfosList_[startElementId]);
        }

        return providerMockResult_.injectResult_;
    }
    int32_t FindAccessibilityNodeInfosByText(
        const int64_t elementId, std::string text, const int32_t requestId,
        std::vector<ArkUI_AccessibilityElementInfo>& infos) override
    {
        providerMockResult_.elementId_ = elementId;
        providerMockResult_.requestId_ = requestId;

        std::string textStr(text);
        for (const auto &elementInfo: providerMockResult_.elementInfosList_) {
            if (elementInfo.GetContents() == textStr) {
                infos.push_back(elementInfo);
            }
        }

        return providerMockResult_.injectResult_;
    }
    int32_t FindFocusedAccessibilityNode(
        const int64_t elementId, int32_t focusType, const int32_t requestId,
        ArkUI_AccessibilityElementInfo& elementInfo) override
    {
        elementInfo = providerMockResult_.focusElementInfo_;
        return providerMockResult_.injectResult_;
    }
    int32_t FindNextFocusAccessibilityNode(
        const int64_t elementId, int32_t direction, const int32_t requestId,
        ArkUI_AccessibilityElementInfo& elementInfo) override
    {
        elementInfo = providerMockResult_.nextFocusElementInfo_;
        return providerMockResult_.injectResult_;
    }
    int32_t ExecuteAccessibilityAction(
        const int64_t elementId, int32_t action, const int32_t requestId,
        const std::map<std::string, std::string>& actionArguments) override
    {
        return providerMockResult_.injectActionResult_;
    }
    int32_t ClearFocusedAccessibilityNode() override
    {
        providerMockResult_.receiveClear_ = true;
        return providerMockResult_.injectResult_;
    }
    int32_t GetAccessibilityNodeCursorPosition(
        const int64_t elementId,
        const int32_t requestId,
        int32_t &cursorPosition) override
    {
        cursorPosition = SPECIAL_CURSOR_POSTION;
        return providerMockResult_.injectResult_;
    }
    int32_t SendAccessibilityAsyncEvent(
        const ArkUI_AccessibilityEventInfo& accessibilityEvent,
        void (*callback)(int32_t errorCode)) override
    {
        return providerMockResult_.injectResult_;
    }
    void SendThirdAccessibilityProvider(
        const std::weak_ptr<ThirdAccessibilityManager>& thirdAccessibilityManager)
        override {}

public:
    void SetInjectResult(int32_t injectResult)
    {
        providerMockResult_.injectResult_ = injectResult;
    }

    void SetInjectActionResult(int32_t injectResult)
    {
        providerMockResult_.injectActionResult_ = injectResult;
    }

    ProviderMockResult providerMockResult_;
};

}  // namespace OHOS::Ace

#endif // TEST_UNITTEST_CORE_ACCESSIBILITY_JS_THIRD_PROVIDER_INTERACTION_OPERATION_TEST_H