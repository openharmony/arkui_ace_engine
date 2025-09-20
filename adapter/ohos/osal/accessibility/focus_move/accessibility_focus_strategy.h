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

namespace OHOS::Accessibility {

enum class ValueTypeStub {
    UNKONW = -1,
    BOOL,
    STRING,
    ARRAY,
    NUMBER
};

enum class CondOperatorStub {
    UNKONW = -1,
    EQ,
    NE,
    NOT_ONEOF,
    IS_ONEOF,
    HAS_ANY
};

class PropValueStub {
public:
    bool Compare(CondOperatorStub op, const ValueTypeStub& other)
    {
        return false;
    }

    ValueTypeStub valueType = ValueTypeStub::UNKONW;
    std::set<std::string> valueArray;
    std::string valueStr;
    int32_t valueNum = 0;
    bool valueBool = false;
};

class ReadableRulesNodeStub {
public:
    explicit ReadableRulesNodeStub(int64_t accessibilityId) : accessibilityId_(accessibilityId) {}

    virtual ~ReadableRulesNodeStub() = default;

    int64_t GetAccessibilityId()
    {
        return accessibilityId_;
    }

    virtual bool GetPropText(PropValueStub& value);

    virtual bool GetPropHintText(PropValueStub& value);

    virtual bool GetPropDesc(PropValueStub& value);

    virtual bool GetPropAccessibilityText(PropValueStub& value);

    virtual bool GetPropType(PropValueStub& value);

    virtual bool GetPropAccessibilityLevel(PropValueStub& value);

    virtual bool GetPropAccessibilityGroup(PropValueStub& value);

    virtual bool GetPropIsEnable(PropValueStub& value);

    virtual bool GetPropChildrenCount(PropValueStub& value);

    virtual bool GetPropActionNames(PropValueStub& value);

    virtual std::vector<std::shared_ptr<ReadableRulesNodeStub>> GetChildren();

    virtual std::shared_ptr<ReadableRulesNodeStub> GetParent();

    virtual bool IsModalForPopup()
    {
        return true;
    }
private:
    int64_t accessibilityId_;
};
}

namespace OHOS::Ace::Framework {

#ifdef SUPPORT_ACCESSIBILITY_FOCUS_MOVE
#define HILOG_INFO_FOCUS(fmt, ...)                                      \
    (TAG_LOGI(AceLogTag::ACE_ACCESSIBILITY, "AceFocus " fmt, ##__VA__ARGS__))
#else
#define HILOG_INFO_FOCUS(...)
#endif

enum class AceFocusMoveResult : int32_t {
    FIND_SUCCESS = 0,
    FIND_FAIL,
    FIND_CHILDTREE,
    FIND_EMBED_TARGET,
    FIND_FAIL_IN_CHILDTREE,
    FIND_FAIL_IN_SCROLL,
};

struct AceFocusMoveDetailCondtion {
    bool bypassSelf = true;
    bool bypassDescendants = false;
};

class FocusRulesCheckNode : public Accessibility::ReadableRulesNodeStub {
public:
    explicit FocusRulesCheckNode(int64_t accessibilityId)
        : Accessibility::ReadableRulesNodeStub(accessibilityId) {}
    ~FocusRulesCheckNode() override = default;

    virtual std::vector<std::shared_ptr<FocusRulesCheckNode>> GetAceChildren();

    virtual std::shared_ptr<FocusRulesCheckNode> GetAceParent();

    virtual std::shared_ptr<Accessibility::ReadableRulesNodeStub> GetUserNextFocusNode()
    {
        return nullptr;
    }

    virtual std::shared_ptr<Accessibility::ReadableRulesNodeStub> GetUserPrevFocusNode()
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
};

class AccessibilityFocusStrategy {
public:
    AccessibilityFocusStrategy() = default;
    virtual ~AccessibilityFocusStrategy() = default;

    static const std::map<AceAction, std::string> aceActionToFocusActionName;

    bool CanAccessibilityFocus(const std::shared_ptr<FocusRulesCheckNode>& currentNode);

    std::shared_ptr<FocusRulesCheckNode> GetParentNodeStopByRootType(
        const std::shared_ptr<FocusRulesCheckNode>& currentNode);

    AceFocusMoveResult FindNextReadableNode (
        AceFocusMoveDetailCondtion condtion,
        const std::shared_ptr<FocusRulesCheckNode>& currentNode,
        std::shared_ptr<FocusRulesCheckNode>& targetNode);

    AceFocusMoveResult FindPrevReadableNode (
        AceFocusMoveDetailCondtion condtion,
        const std::shared_ptr<FocusRulesCheckNode>& currentNode,
        std::shared_ptr<FocusRulesCheckNode>& targetNode);

    AceFocusMoveResult FindLastNodeWithoutCheck (
        AceFocusMoveDetailCondtion condtion,
        const std::shared_ptr<FocusRulesCheckNode>& currentNode,
        std::shared_ptr<FocusRulesCheckNode>& targetNode);

    AceFocusMoveResult FindForwardScrollAncestor (
        AceFocusMoveDetailCondtion condtion,
        const std::shared_ptr<FocusRulesCheckNode>& currentNode,
        std::list<std::shared_ptr<FocusRulesCheckNode>>& targetNodes);

    AceFocusMoveResult FindBackwardScrollAncestor (
        AceFocusMoveDetailCondtion condtion,
        const std::shared_ptr<FocusRulesCheckNode>& currentNode,
        std::list<std::shared_ptr<FocusRulesCheckNode>>& targetNodes);
private:
    AceFocusMoveResult FindNextReadableNodeBySelfAndSameLevel (
        AceFocusMoveDetailCondtion condtion,
        const std::shared_ptr<FocusRulesCheckNode>& currentNode,
        const std::vector<std::shared_ptr<FocusRulesCheckNode>>& samenLevelNodes,
        std::shared_ptr<FocusRulesCheckNode>& targetNode);

    AceFocusMoveResult FindPrevReadableNodeByChildAndSelf (
        const std::shared_ptr<FocusRulesCheckNode>& currentNode,
        std::shared_ptr<FocusRulesCheckNode>& targetNode);
};
} // OHOS::Ace::Framework
#endif // FOUNDATION_ACE_ADAPTER_OHOS_OSAL_ACCESSIBILITY_FOCUS_MOVE_ACCESSIBILITY_FOCUS_STRATEGY_H
