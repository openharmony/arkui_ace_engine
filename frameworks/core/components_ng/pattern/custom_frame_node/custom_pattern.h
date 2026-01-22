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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CUSTOM_FRAME_NODE_CUSTOM_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CUSTOM_FRAME_NODE_CUSTOM_PATTERN_H

#include <cstdint>
#include <memory>

#include "core/components_ng/event/overflow_scroll_event_hub.h"
#include "core/components_ng/layout/vertical_overflow_handler.h"
#include "core/components_ng/pattern/pattern.h"

struct ArkUI_AccessibilityProvider;

namespace OHOS::Ace {
class AccessibilityChildTreeCallback;
class AccessibilityManager;
class AccessibilityProvider;
} // namespace OHOS::Ace

namespace OHOS::Ace::NG {
class AccessibilitySessionAdapter;
class FrameNode;
class PipelineContext;
class VerticalOverflowHandler;

class ACE_EXPORT CustomPattern : public Pattern {
    DECLARE_ACE_TYPE(CustomPattern, Pattern);

public:
    CustomPattern();
    ~CustomPattern() override;

    FocusPattern GetFocusPattern() const override
    {
        auto node = GetHost();
        CHECK_NULL_RETURN(node, FocusPattern());
        auto focusHub = node->GetFocusHub();
        CHECK_NULL_RETURN(focusHub, FocusPattern());
        return { focusHub->GetFocusType(), focusHub->GetFocusable() };
    }

    bool ReusedNodeSkipMeasure() override;
    ArkUI_AccessibilityProvider* GetNativeAccessibilityProvider();
    void InitializeAccessibility(PipelineContext* context);
    void UninitializeAccessibility(FrameNode* frameNode, PipelineContext* context);
    bool OnAccessibilityChildTreeRegister(uint32_t windowId, int32_t treeId);
    bool OnAccessibilityChildTreeDeregister(FrameNode* frameNode = nullptr);
    void OnSetAccessibilityChildTree(int32_t childWindowId, int32_t childTreeId);
    void InitializeAccessibilityCallback();
    void HandleRegisterAccessibilityEvent(bool isRegister);
    RefPtr<AccessibilitySessionAdapter> GetAccessibilitySessionAdapter() override;

    RefPtr<EventHub> CreateEventHub() override;

    RefPtr<VerticalOverflowHandler> GetOrCreateVerticalOverflowHandler(const WeakPtr<FrameNode>& host) override;

    void DumpInfo() override;

    bool GetIsVertical() const override
    {
        return true;
    }

private:
    void OnAttachContext(PipelineContext *context) override;
    void OnDetachContext(PipelineContext* context) override;
    std::shared_ptr<ArkUI_AccessibilityProvider> arkuiAccessibilityProvider_;
    std::shared_ptr<AccessibilityChildTreeCallback> accessibilityChildTreeCallback_;
    RefPtr<AccessibilityProvider> accessibilityProvider_;
    RefPtr<AccessibilitySessionAdapter> accessibilitySessionAdapter_;
    uint32_t windowId_ = 0;
    int32_t treeId_ = -1;
    RefPtr<VerticalOverflowHandler> vOverflowHandler_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CUSTOM_FRAME_NODE_CUSTOM_PATTERN_H
