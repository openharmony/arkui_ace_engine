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

#ifndef FOUNDATION_ACE_ADAPTER_OHOS_OSAL_ACCESSIBILITY_FOCUS_MOVE_ACCESSIBILITY_FOCUS_MOVE_OSAL_H
#define FOUNDATION_ACE_ADAPTER_OHOS_OSAL_ACCESSIBILITY_FOCUS_MOVE_ACCESSIBILITY_FOCUS_MOVE_OSAL_H

#include "accessibility_config.h"
#include "accessibility_element_operator.h"
#include "accessibility_event_info.h"
#include "accessibility_state_event.h"

#include "base/memory/ace_type.h"
#include "base/utils/macros.h"
#include "adapter/ohos/osal/accessibility/focus_move/accessibility_focus_strategy.h"
#include "frameworks/core/accessibility/accessibility_manager.h"

namespace OHOS::Ace::Framework {

class FocusStrategyOsal : public virtual AceType {
    DECLARE_ACE_TYPE(FocusStrategyOsal, AceType);
public:
    FocusStrategyOsal(const WeakPtr<AccessibilityManager>& accessibilityManager)
        : accessibilityManager_(accessibilityManager) {}
    virtual ~FocusStrategyOsal() = default;

    virtual void InvailidElementInfo(Accessibility::AccessibilityElementInfo& info) {}
    virtual bool UpdateOriginNodeInfo(int64_t elementId) { return false; }
    virtual std::shared_ptr<FocusRulesCheckNode> GetCurrentCheckNode() { return nullptr; }
    virtual void UpdateNextFocus(std::shared_ptr<FocusRulesCheckNode>& checkNode) {}
    virtual std::shared_ptr<FocusRulesCheckNode> ChangeToRoot() { return nullptr; }
    virtual bool ChangeToEmbed(
        const std::shared_ptr<FocusRulesCheckNode>& resultNode, Accessibility::AccessibilityElementInfo& info)
    {
        return false;
    }
    virtual bool UpdateElementInfo(
        const std::shared_ptr<FocusRulesCheckNode>& resultNode, Accessibility::AccessibilityElementInfo& info)
    {
        return false;
    }
    Accessibility::FocusMoveResult ExecuteFocusMoveSearch(
        const int64_t elementId,
        const Accessibility::AccessibilityFocusMoveParam& param,
        Accessibility::AccessibilityElementInfo& info);

    Accessibility::FocusMoveResult ProcessGetScrollAncestor(
        const int64_t elementId,
        const Accessibility::AccessibilityFocusMoveParam& param,
        std::list<Accessibility::AccessibilityElementInfo>& infos);

    static bool IsProcessGetScrollAncestor(const Accessibility::AccessibilityFocusMoveParam& param);

    static bool IsProcessDetectFocusable(const Accessibility::AccessibilityFocusMoveParam& param);

    virtual bool CheckIsRootType(
        const std::shared_ptr<FocusRulesCheckNode>& checkNode);

    virtual bool CheckIsReadable(
        const std::shared_ptr<FocusRulesCheckNode>& checkNode);

    virtual bool CheckIsReadableRulesEnable();

    bool NeedChangeToReadableNodeThroughAncestor(
        const std::shared_ptr<FocusRulesCheckNode>& checkNode, std::shared_ptr<FocusRulesCheckNode>& targetNode);

private:
    AceFocusMoveDetailCondition GetAceCondition(
        const Accessibility::AccessibilityFocusMoveParam& param);
    Accessibility::FocusMoveResultType HandleFocusMoveSearchResult(
        const Accessibility::AccessibilityFocusMoveParam& param,
        const std::shared_ptr<FocusRulesCheckNode>& targetNode,
        AceFocusMoveResult result,
        Accessibility::AccessibilityElementInfo& info);

    WeakPtr<AccessibilityManager> accessibilityManager_;
};


} // OHOS::Ace::Framework
#endif // FOUNDATION_ACE_ADAPTER_OHOS_OSAL_ACCESSIBILITY_FOCUS_MOVE_ACCESSIBILITY_FOCUS_MOVE_OSAL_H
