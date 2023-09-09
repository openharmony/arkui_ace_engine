/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_STEPPER_STEPPER_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_STEPPER_STEPPER_NODE_H

#include "core/components_ng/base/group_node.h"
#include "core/components_ng/pattern/stepper/stepper_pattern.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT StepperNode : public GroupNode {
    DECLARE_ACE_TYPE(StepperNode, GroupNode);

public:
    StepperNode(const std::string& tag, int32_t nodeId, const RefPtr<Pattern>& pattern, bool isRoot = false)
        : GroupNode(tag, nodeId, pattern, isRoot)
    {}
    ~StepperNode() override = default;

    static RefPtr<StepperNode> GetOrCreateStepperNode(
        const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator);

    void AddChildToGroup(const RefPtr<UINode>& child, int32_t slot = DEFAULT_NODE_SLOT) override;
    void DeleteChildFromGroup(int32_t slot = DEFAULT_NODE_SLOT) override;

    bool HasSwiperNode() const
    {
        return swiperId_.has_value();
    }

    bool HasLeftButtonNode() const
    {
        return leftButtonId_.has_value();
    }

    bool HasRightButtonNode() const
    {
        return rightButtonId_.has_value();
    }

    int32_t GetSwiperId()
    {
        if (!swiperId_.has_value()) {
            swiperId_ = ElementRegister::GetInstance()->MakeUniqueId();
        }
        return swiperId_.value();
    }

    int32_t GetLeftButtonId()
    {
        if (!leftButtonId_.has_value()) {
            leftButtonId_ = ElementRegister::GetInstance()->MakeUniqueId();
        }
        return leftButtonId_.value();
    }

    int32_t GetRightButtonId()
    {
        if (!rightButtonId_.has_value()) {
            rightButtonId_ = ElementRegister::GetInstance()->MakeUniqueId();
        }
        return rightButtonId_.value();
    }

    void RemoveLeftButtonNode()
    {
        CHECK_NULL_VOID(HasLeftButtonNode());
        RemoveChildAtIndex(GetChildIndexById(GetLeftButtonId()));
        leftButtonId_ = std::nullopt;
    }

    void RemoveRightButtonNode()
    {
        CHECK_NULL_VOID(HasRightButtonNode());
        RemoveChildAtIndex(GetChildIndexById(GetRightButtonId()));
        rightButtonId_ = std::nullopt;
    }

private:
    std::optional<int32_t> swiperId_;
    std::optional<int32_t> leftButtonId_;
    std::optional<int32_t> rightButtonId_;
    ACE_DISALLOW_COPY_AND_MOVE(StepperNode);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_STEPPER_STEPPER_NODE_H
