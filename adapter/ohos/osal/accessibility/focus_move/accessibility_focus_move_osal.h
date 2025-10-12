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

namespace OHOS::Accessibility {

enum class FocusMoveResultStub : int32_t {
    NOT_SUPPORT = -1,
    SEARCH_SUCCESS = 0,
    SEARCH_SUCCESS_NEXT_BYPASS_DESCENDANTS,
    SEARCH_FAIL,
    SEARCH_FAIL_IN_CHILDTREE,
    SEARCH_FAIL_LOST_NODE,
    SEARCH_NEXT,
    DOUBLE_CHECK_CHILD_PROPERTY,
    DOUBLE_CHECK_CHILD_PROPERTY_AND_GET_LAST,
    SERAH_FAIL_IN_SCROLL
};

enum class DetailConditionStub : int32_t {
    BYPASS_SELF = 0x00000001,
    BYPASS_SELF_DESCENDANTS = 0x00000002,
    CHECK_SELF = 0x00000004,
    CHECK_SELF_BYPASS_DESCENDANTS = 0x00000008,
};

enum class FocusMoveDirectionStub : int32_t {
    DIRECTION_INVAILD = 0,
    UP = 0x00000001,
    DOWN = 0x00000002,
    LEFT = 0x00000004,
    RIGHT = 0x00000008,
    FORWARD = 0x00000010,
    BACKWARD = 0x00000020,
    FIND_LAST = 0x00000040,
    GET_FORWARD_SCROLL_ANCESTOR = 0x00000080,
    GET_BACKWARD_SCROLL_ANCESTOR = 0x00000100,
    GET_SCROLLABLE_ANCESTOR = 0x00000200,
};

struct AccessibilityFocusMoveParamStub {
    FocusMoveDirectionStub direction;
    DetailConditionStub condition;
};

}

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
    Accessibility::FocusMoveResultStub ExecuteFocusMoveSearch(
        const int64_t elementId,
        const Accessibility::AccessibilityFocusMoveParamStub& param,
        Accessibility::AccessibilityElementInfo& info);

    void ProcessGetScrollAncestor(
        const int64_t elementId,
        const Accessibility::AccessibilityFocusMoveParamStub& param,
        std::list<Accessibility::AccessibilityElementInfo>& infos);

    static bool IsProcessGetScrollAncestor(const Accessibility::AccessibilityFocusMoveParamStub& param);
private:
    AceFocusMoveDetailCondition GetAceCondition(
        const Accessibility::AccessibilityFocusMoveParamStub& param);
    Accessibility::FocusMoveResultStub HandleFocusMoveSearchResult(
        const Accessibility::AccessibilityFocusMoveParamStub& param,
        const std::shared_ptr<FocusRulesCheckNode>& targetNode,
        AceFocusMoveResult result,
        Accessibility::AccessibilityElementInfo& info);

    WeakPtr<AccessibilityManager> accessibilityManager_;
};


} // OHOS::Ace::Framework
#endif // FOUNDATION_ACE_ADAPTER_OHOS_OSAL_ACCESSIBILITY_FOCUS_MOVE_ACCESSIBILITY_FOCUS_MOVE_OSAL_H
