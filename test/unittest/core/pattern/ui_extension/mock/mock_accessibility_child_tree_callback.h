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
#ifndef FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_UI_EXTENSION_MOCK_ACCESSIBILITY_H
#define FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_UI_EXTENSION_MOCK_ACCESSIBILITY_H
#include "core/components_ng/pattern/ui_extension/ui_extension_component/ui_extension_pattern.h"
#include "core/accessibility/accessibility_manager.h"

namespace OHOS::Ace::NG {
class UIExtensionAccessibilityChildTreeCallback : public AccessibilityChildTreeCallback {
public:
    UIExtensionAccessibilityChildTreeCallback(const WeakPtr<UIExtensionPattern> &weakPattern, int64_t accessibilityId)
        : AccessibilityChildTreeCallback(accessibilityId), weakPattern_(weakPattern)
    {}

    ~UIExtensionAccessibilityChildTreeCallback() override = default;

    bool OnRegister(uint32_t windowId, int32_t treeId) override
    {
        auto pattern = weakPattern_.Upgrade();
        if (pattern == nullptr) {
            return false;
        }
        if (isReg_) {
            return true;
        }
        pattern->OnAccessibilityChildTreeRegister(windowId, treeId, GetAccessibilityId());
        isReg_ = true;
        return true;
    }

    bool OnDeregister() override
    {
        auto pattern = weakPattern_.Upgrade();
        if (pattern == nullptr) {
            return false;
        }
        if (!isReg_) {
            return true;
        }
        pattern->OnAccessibilityChildTreeDeregister();
        isReg_ = false;
        return true;
    }

    bool OnSetChildTree(int32_t childWindowId, int32_t childTreeId) override
    {
        auto pattern = weakPattern_.Upgrade();
        if (pattern == nullptr) {
            return false;
        }
        pattern->OnSetAccessibilityChildTree(childWindowId, childTreeId);
        return true;
    }

    bool OnDumpChildInfo(const std::vector<std::string>& params, std::vector<std::string>& info) override
    {
        auto pattern = weakPattern_.Upgrade();
        if (pattern == nullptr) {
            return false;
        }
        pattern->OnAccessibilityDumpChildInfo(params, info);
        return true;
    }

    void OnClearRegisterFlag() override
    {
        auto pattern = weakPattern_.Upgrade();
        if (pattern == nullptr) {
            return;
        }
        isReg_ = false;
    }

private:
    bool isReg_ = false;
    WeakPtr<UIExtensionPattern> weakPattern_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_TEST_UNITTEST_CORE_PATTERN_UI_EXTENSION_MOCK_ACCESSIBILITY_H
