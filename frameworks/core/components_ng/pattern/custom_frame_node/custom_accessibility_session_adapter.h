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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CUSTOM_FRAME_NODE_CUSTOM_ACCESSIBILITY_SESSION_ADAPTER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CUSTOM_FRAME_NODE_CUSTOM_ACCESSIBILITY_SESSION_ADAPTER_H

#include "core/accessibility/accessibility_session_adapter.h"
#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {
class CustomAccessibilitySessionAdapter : public AccessibilitySessionAdapter {
    DECLARE_ACE_TYPE(CustomAccessibilitySessionAdapter, AccessibilitySessionAdapter);
public:
    explicit CustomAccessibilitySessionAdapter(
        const WeakPtr<FrameNode> host): host_(host) {}
    ~CustomAccessibilitySessionAdapter() override = default;

    void TransferHoverEvent(const PointF& point, SourceType source,
        AccessibilityHoverEventType eventType, TimeStamp time) override;
    bool IgnoreHostNode() const override;
private:
    WeakPtr<FrameNode> host_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CUSTOM_FRAME_NODE_CUSTOM_ACCESSIBILITY_SESSION_ADAPTER_H
