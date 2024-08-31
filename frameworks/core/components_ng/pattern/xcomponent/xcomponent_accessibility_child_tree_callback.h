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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_XCOMPONENT_XCOMPONENT_ACCESSIBILITY_CHILD_TREE_CALLBACL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_XCOMPONENT_XCOMPONENT_ACCESSIBILITY_CHILD_TREE_CALLBACL_H

#include "core/accessibility/accessibility_manager.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_pattern.h"

namespace OHOS::Ace::NG {
class XComponentAccessibilityChildTreeCallback : public AccessibilityChildTreeCallback {
public:
    XComponentAccessibilityChildTreeCallback(
        const WeakPtr<XComponentPattern> &xComponentPattern, int64_t accessibilityId)
        : AccessibilityChildTreeCallback(accessibilityId), weakPattern_(xComponentPattern)
    {}

    ~XComponentAccessibilityChildTreeCallback() override = default;

    bool OnRegister(uint32_t windowId, int32_t treeId) override;
    bool OnDeregister() override;
    bool OnSetChildTree(int32_t childWindowId, int32_t childTreeId) override;
    bool OnDumpChildInfo(
        const std::vector<std::string>& params, std::vector<std::string>& info) override;
    void OnClearRegisterFlag() override;

private:
    bool isReg_ = false;
    WeakPtr<XComponentPattern> weakPattern_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_XCOMPONENT_XCOMPONENT_ACCESSIBILITY_CHILD_TREE_CALLBACL_H
