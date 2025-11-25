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

#ifndef FOUNDATION_ACE_ADAPTER_OHOS_OSAL_ACCESSIBILITY_FOCUS_MOVE_ACCESSIBILITY_FOCUS_STRATEGY_H
#define FOUNDATION_ACE_ADAPTER_OHOS_OSAL_ACCESSIBILITY_FOCUS_MOVE_ACCESSIBILITY_FOCUS_STRATEGY_H

#include "accessibility_system_ability_client.h"

#include <string>
#include <list>
#include "base/memory/ace_type.h"
#include "base/utils/macros.h"
#include "hilog/log.h"
#include "frameworks/core/accessibility/accessibility_utils.h"

namespace OHOS::Ace::Framework {

#ifdef SUPPORT_ACCESSIBILITY_FOCUS_MOVE
#define HILOG_INFO_FOCUS(fmt, ...)                                      \
    (TAG_LOGI(AceLogTag::ACE_ACCESSIBILITY, "AceA11yFocus " fmt, ##__VA_ARGS__))
#else
#define HILOG_INFO_FOCUS(fmt, ...)                                      \
    (TAG_LOGD(AceLogTag::ACE_ACCESSIBILITY, "AceA11yFocus " fmt, ##__VA_ARGS__))
#endif

enum class AceFocusMoveResult : int32_t {
    FIND_SUCCESS = 0,
    FIND_FAIL,
    FIND_CHILDTREE,
    FIND_EMBED_TARGET,
    FIND_FAIL_IN_CHILDTREE,
    FIND_FAIL_IN_SCROLL,
    FIND_FAIL_LOST_NODE,
    FIND_FAIL_IN_ROOT_TYPE,
};

struct AceFocusMoveDetailCondition {
    bool bypassSelf = true;
    bool bypassDescendants = false;
};

enum class CheckSupportScrollAction : int32_t {
    FIND_FORWARD = 0,
    FIND_BACKWARD,
    FIND_ANY,
};

struct AceDetectThroughAncestorParam {
    bool changeToAncestorFocusable = false; // change to parent's focusable component
    bool needCheckValid = false; // check node is valid in detect
};

class FocusRulesCheckNode : public Accessibility::ReadableRulesNode {
public:
    explicit FocusRulesCheckNode(int64_t accessibilityId)
        : Accessibility::ReadableRulesNode(accessibilityId) {}
    ~FocusRulesCheckNode() override = default;

    virtual std::vector<std::shared_ptr<FocusRulesCheckNode>> GetAceChildren();

    virtual std::shared_ptr<FocusRulesCheckNode> GetAceParent();

    virtual std::shared_ptr<FocusRulesCheckNode> GetUserNextFocusNode()
    {
        return nullptr;
    }

    virtual std::shared_ptr<FocusRulesCheckNode> GetUserPrevFocusNode()
    {
        return nullptr;
    }

    virtual bool IsAccessibiltyVisible()
    {
        return true;
    }

    virtual bool IsChildTreeContainer()
    {
        return false;
    }

    virtual bool IsEmbededTarget()
    {
        return false;
    }

    virtual bool IsInChildTree()
    {
        return false;
    }
};

class AccessibilityFocusStrategy {
public:
    AccessibilityFocusStrategy() = default;
    virtual ~AccessibilityFocusStrategy() = default;

    static const std::map<AceAction, std::string> aceActionToFocusActionName;
    static const std::map<OHOS::Accessibility::ActionType, std::string> actionToFocusActionName;

    virtual bool CanAccessibilityFocus(const std::shared_ptr<FocusRulesCheckNode>& currentNode);

    std::shared_ptr<FocusRulesCheckNode> GetParentNodeStopByRootType(
        const std::shared_ptr<FocusRulesCheckNode>& currentNode, bool& hitRootType);

    AceFocusMoveResult FindNextReadableNode (
        AceFocusMoveDetailCondition condition,
        const std::shared_ptr<FocusRulesCheckNode>& currentNode,
        std::shared_ptr<FocusRulesCheckNode>& targetNode);

    AceFocusMoveResult FindPrevReadableNode (
        AceFocusMoveDetailCondition condition,
        const std::shared_ptr<FocusRulesCheckNode>& currentNode,
        std::shared_ptr<FocusRulesCheckNode>& targetNode);

    AceFocusMoveResult FindLastNodeWithoutCheck (
        AceFocusMoveDetailCondition condition,
        const std::shared_ptr<FocusRulesCheckNode>& currentNode,
        std::shared_ptr<FocusRulesCheckNode>& targetNode);

    AceFocusMoveResult FindForwardScrollAncestor (
        AceFocusMoveDetailCondition condition,
        const std::shared_ptr<FocusRulesCheckNode>& currentNode,
        std::list<std::shared_ptr<FocusRulesCheckNode>>& targetNodes);

    AceFocusMoveResult FindBackwardScrollAncestor (
        AceFocusMoveDetailCondition condition,
        const std::shared_ptr<FocusRulesCheckNode>& currentNode,
        std::list<std::shared_ptr<FocusRulesCheckNode>>& targetNodes);

    AceFocusMoveResult FindAnyScrollAncestor(
        AceFocusMoveDetailCondition condition,
        const std::shared_ptr<FocusRulesCheckNode>& currentNode,
        std::list<std::shared_ptr<FocusRulesCheckNode>>& targetNodes);

private:
    AceFocusMoveResult FindNextReadableNodeBySelfAndSameLevel (
        AceFocusMoveDetailCondition condition,
        const std::shared_ptr<FocusRulesCheckNode>& currentNode,
        const std::vector<std::shared_ptr<FocusRulesCheckNode>>& sameLevelNodes,
        std::shared_ptr<FocusRulesCheckNode>& targetNode);

    AceFocusMoveResult FindPrevReadableNodeByChildAndSelf (
        const std::shared_ptr<FocusRulesCheckNode>& currentNode,
        std::shared_ptr<FocusRulesCheckNode>& targetNode);

    AceFocusMoveResult FindNextReadableNodeToHigherLevel(
        std::shared_ptr<FocusRulesCheckNode>& parent,
        std::shared_ptr<FocusRulesCheckNode>& targetNode);

    AceFocusMoveResult FindPrevReadableNodeToHigherLevel(
        const std::shared_ptr<FocusRulesCheckNode>& currentNode,
        std::shared_ptr<FocusRulesCheckNode>& targetNode);

    virtual bool IsForceSupportScrollType(
        const std::shared_ptr<FocusRulesCheckNode>& currentNode);

    AceFocusMoveResult FindScrollAncestor(
        AceFocusMoveDetailCondition condition,
        const std::shared_ptr<FocusRulesCheckNode>& currentNode,
        std::list<std::shared_ptr<FocusRulesCheckNode>>& targetNodes,
        CheckSupportScrollAction checkAction,
        bool checkType);

    AceFocusMoveResult CheckParentEarlyStop(
        const std::shared_ptr<FocusRulesCheckNode>& parent,
        std::shared_ptr<FocusRulesCheckNode>& targetNode);

    std::string GetChildrenIdsStr(
        const std::vector<std::shared_ptr<FocusRulesCheckNode>>& children);
};
} // OHOS::Ace::Framework
#endif // FOUNDATION_ACE_ADAPTER_OHOS_OSAL_ACCESSIBILITY_FOCUS_MOVE_ACCESSIBILITY_FOCUS_STRATEGY_H
