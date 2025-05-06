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

#ifndef FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UEC_UEC_UI_EXTENSION_ACCESSIBILITY_CALLBACK_H
#define FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UEC_UEC_UI_EXTENSION_ACCESSIBILITY_CALLBACK_H

#include "core/accessibility/accessibility_manager.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_component/ui_extension_pattern.h"

namespace OHOS::Ace::NG {

class UIExtensionAccessibilityChildTreeCallback : public AccessibilityChildTreeCallback {
public:
    UIExtensionAccessibilityChildTreeCallback(
        const WeakPtr<UIExtensionPattern>& weakPattern, int64_t accessibilityId);
    ~UIExtensionAccessibilityChildTreeCallback() override = default;

    bool OnRegister(uint32_t windowId, int32_t treeId) override;
    bool OnDeregister() override;
    bool OnSetChildTree(int32_t childWindowId, int32_t childTreeId) override;
    bool OnDumpChildInfo(const std::vector<std::string>& params, std::vector<std::string>& info) override;
    void OnClearRegisterFlag() override;

private:
    bool isReg_ = false;
    WeakPtr<UIExtensionPattern> weakPattern_;
};
} // namespace OHOS::Ace::NG
#endif // FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_UEC_UEC_UI_EXTENSION_ACCESSIBILITY_CALLBACK_H