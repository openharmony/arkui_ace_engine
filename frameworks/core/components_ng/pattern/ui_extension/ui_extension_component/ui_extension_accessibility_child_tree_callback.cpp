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

#include "core/components_ng/pattern/ui_extension/ui_extension_component/ui_extension_accessibility_child_tree_callback.h"

#include "base/log/log_wrapper.h"
 
namespace OHOS::Ace::NG {
UIExtensionAccessibilityChildTreeCallback::UIExtensionAccessibilityChildTreeCallback(
    const WeakPtr<UIExtensionPattern>& weakPattern, int64_t accessibilityId)
    : AccessibilityChildTreeCallback(accessibilityId), weakPattern_(weakPattern)
{
    TAG_LOGI(AceLogTag::ACE_DYNAMIC_COMPONENT, "Create UIExtensionAccessibilityChildTreeCallback");
}

bool UIExtensionAccessibilityChildTreeCallback::OnRegister(uint32_t windowId, int32_t treeId)
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

bool UIExtensionAccessibilityChildTreeCallback::OnDeregister()
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

bool UIExtensionAccessibilityChildTreeCallback::OnSetChildTree(
    int32_t childWindowId, int32_t childTreeId)
{
    auto pattern = weakPattern_.Upgrade();
    if (pattern == nullptr) {
        return false;
    }

    pattern->OnSetAccessibilityChildTree(childWindowId, childTreeId);
    return true;
}

bool UIExtensionAccessibilityChildTreeCallback::OnDumpChildInfo(
    const std::vector<std::string>& params, std::vector<std::string>& info)
{
    auto pattern = weakPattern_.Upgrade();
    if (pattern == nullptr) {
        return false;
    }

    pattern->OnAccessibilityDumpChildInfo(params, info);
    return true;
}

void UIExtensionAccessibilityChildTreeCallback::OnClearRegisterFlag()
{
    auto pattern = weakPattern_.Upgrade();
    if (pattern == nullptr) {
        return;
    }

    isReg_ = false;
}
} // namespace OHOS::Ace::NG
 