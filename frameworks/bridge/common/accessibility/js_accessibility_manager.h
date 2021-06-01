/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BRIDGE_COMMON_ACCESSIBILITY_JS_ACCESSIBILITY_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_BRIDGE_COMMON_ACCESSIBILITY_JS_ACCESSIBILITY_MANAGER_H

#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "core/accessibility/accessibility_manager.h"
#include "core/accessibility/accessibility_utils.h"
#include "frameworks/bridge/common/accessibility/accessibility_node_manager.h"

namespace OHOS::Ace::Framework {

class JsAccessibilityManager : public AccessibilityNodeManager {
    DECLARE_ACE_TYPE(JsAccessibilityManager, AccessibilityNodeManager);

public:
    JsAccessibilityManager() = default;
    ~JsAccessibilityManager() override = default;

    // JsAccessibilityManager overrides functions.
    void InitializeCallback() override;
    void SendAccessibilityAsyncEvent(const AccessibilityEvent& accessibilityEvent) override;
    void DumpHandleEvent(const std::vector<std::string>& params) override;
    void DumpProperty(const std::vector<std::string>& params) override;
    void DumpTree(int32_t depth, NodeId nodeID) override;
    void SetCardViewParams(const std::string& key, bool focus) override;

private:
    void UpdateNodeChildIds(const RefPtr<AccessibilityNode>& node);
    void SendAccessibilitySyncEvent(const AccessibilityEvent& accessibilityEvent);

    std::string callbackKey_;
};

} // namespace OHOS::Ace::Framework

#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_COMMON_ACCESSIBILITY_JS_ACCESSIBILITY_MANAGER_H
