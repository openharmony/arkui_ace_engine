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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CUSTOM_FRAME_NODE_CUSTOM_ACCESSIBILITY_CHILD_TREE_CALLBACK_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CUSTOM_FRAME_NODE_CUSTOM_ACCESSIBILITY_CHILD_TREE_CALLBACK_H

#include "core/accessibility/accessibility_manager.h"
#include "core/components_ng/pattern/custom_frame_node/custom_pattern.h"

namespace OHOS::Ace::NG {
class CustomAccessibilityChildTreeCallback : public AccessibilityChildTreeCallback {
public:
    CustomAccessibilityChildTreeCallback(const WeakPtr<CustomPattern> &pattern, int64_t accessibilityId)
        : AccessibilityChildTreeCallback(accessibilityId), weakPattern_(pattern)
    {}

    ~CustomAccessibilityChildTreeCallback() override = default;

    bool OnRegister(uint32_t windowId, int32_t treeId) override;
    bool OnDeregister() override;
    bool OnSetChildTree(int32_t childWindowId, int32_t childTreeId) override;
    bool OnDumpChildInfo(const std::vector<std::string>& params, std::vector<std::string>& info) override;
    void OnClearRegisterFlag() override;

private:
    bool isReg_ = false;
    WeakPtr<CustomPattern> weakPattern_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CUSTOM_FRAME_NODE_CUSTOM_ACCESSIBILITY_CHILD_TREE_CALLBACK_H
