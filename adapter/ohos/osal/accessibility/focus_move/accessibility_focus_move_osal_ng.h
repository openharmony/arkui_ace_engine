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

#ifndef FOUNDATION_ACE_ADAPTER_OHOS_OSAL_ACCESSIBILITY_FOCUS_MOVE_ACCESSIBILITY_FOCUS_MOVE_OSAL_NG_H
#define FOUNDATION_ACE_ADAPTER_OHOS_OSAL_ACCESSIBILITY_FOCUS_MOVE_ACCESSIBILITY_FOCUS_MOVE_OSAL_NG_H

#include "adapter/ohos/osal/accessibility/focus_move/accessibility_focus_move_osal.h"

namespace OHOS::Ace::Framework {
class JsAccessibilityManager;
class FocusStrategyOsalNG : public FocusStrategyOsal {
    DECLARE_ACE_TYPE(FocusStrategyOsalNG, AceType);
public:
    FocusStrategyOsalNG(const RefPtr<JsAccessibilityManager>& jsAccessibilityManager,
        const RefPtr<PipelineBase>& context, const RefPtr<PipelineBase>& mainContext)
        : FocusStrategyOsal(jsAccessibilityManager),
        jsAccessibilityManager_(jsAccessibilityManager), context_(context), mainContext_(mainContext) {}
    ~FocusStrategyOsalNG() override = default;

    void InvailidElementInfo(Accessibility::AccessibilityElementInfo& info) override;
    bool UpdateOriginNodeInfo(int64_t elementId) override;
    std::shared_ptr<FocusRulesCheckNode> GetCurrentCheckNode() override;
    void UpdateNextFocus(std::shared_ptr<FocusRulesCheckNode>& checkNode) override;
    std::shared_ptr<FocusRulesCheckNode> ChangeToRoot() override;
    bool ChangeToEmbed(
        const std::shared_ptr<FocusRulesCheckNode>& resultNode, Accessibility::AccessibilityElementInfo& info) override;
    bool UpdateElementInfo(
        const std::shared_ptr<FocusRulesCheckNode>& resultNode, Accessibility::AccessibilityElementInfo& info) override;
    Accessibility::FocusMoveResult DetectElementInfoFocusableThroughAncestor(
        const Accessibility::AccessibilityElementInfo& info,
        const Accessibility::AccessibilityFocusMoveParam& param,
        std::list<Accessibility::AccessibilityElementInfo>& targetInfos,
        const int32_t windowId);

private:
    Accessibility::FocusMoveResult CheckAndGetReadableInfoToRoot(
        const RefPtr<NG::FrameNode>& currentFrameNode, std::list<Accessibility::AccessibilityElementInfo>& targetInfos,
        const int32_t windowId);
    void UpdateBelongTreeIdAndParentWindowId(const int32_t windowId, Accessibility::FocusMoveResult &result);

    virtual bool CheckNodeIsAvailable(const std::shared_ptr<FocusRulesCheckNode>& node);

    RefPtr<NG::FrameNode> GetRootNodeFromContext();

    WeakPtr<JsAccessibilityManager> jsAccessibilityManager_;
    WeakPtr<PipelineBase> context_;
    WeakPtr<PipelineBase> mainContext_;
    WeakPtr<NG::FrameNode> rootNode_;
    WeakPtr<NG::FrameNode> baseNode_;
    WeakPtr<NG::FrameNode> baseNextNode_;
    WeakPtr<NG::FrameNode> basePrevNode_;
};
} // OHOS::Ace::Framework
#endif // FOUNDATION_ACE_ADAPTER_OHOS_OSAL_ACCESSIBILITY_FOCUS_MOVE_ACCESSIBILITY_FOCUS_MOVE_OSAL_NG_H
