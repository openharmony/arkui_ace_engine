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

#ifndef FOUNDATION_ACE_ADAPTER_OHOS_OSAL_ACCESSIBILITY_FOCUS_MOVE_ACCESSIBILITY_FOCUS_FRAME_NODE_UTILS_H
#define FOUNDATION_ACE_ADAPTER_OHOS_OSAL_ACCESSIBILITY_FOCUS_MOVE_ACCESSIBILITY_FOCUS_FRAME_NODE_UTILS_H

#include "adapter/ohos/osal/accessibility/focus_move/accessibility_focus_strategy.h"
#include "frameworks/core/components_ng/base/frame_node.h"
#include "frameworks/core/accessibility/node_utils/accessibility_frame_node_utils.h"

namespace OHOS::Ace::Framework {

class FrameNodeRulesCheckNode : public FocusRulesCheckNode {
public:
    FrameNodeRulesCheckNode(const RefPtr<NG::FrameNode>& node, int64_t accessibilityId);
    FrameNodeRulesCheckNode(
        const RefPtr<NG::FrameNode>& node, int64_t accessibilityId, NG::FrameNodeHandleParam& handleParam)
        : FocusRulesCheckNode(accessibilityId), handleParam_(handleParam), weakNode_(node) {}
    ~FrameNodeRulesCheckNode() override = default;

    bool GetPropText(Accessibility::PropValueStub& value) override;

    bool GetPropHintText(Accessibility::PropValueStub& value) override;

    bool GetPropDesc(Accessibility::PropValueStub& value) override;

    bool GetPropAccessibilityText(Accessibility::PropValueStub& value) override;

    bool GetPropType(Accessibility::PropValueStub& value) override;

    bool GetPropAccessibilityLevel(Accessibility::PropValueStub& value) override;

    bool GetPropAccessibilityGroup(Accessibility::PropValueStub& value) override;

    bool GetPropIsEnable(Accessibility::PropValueStub& value) override;

    bool GetPropChildrenCount(Accessibility::PropValueStub& value) override;

    bool GetPropActionNames(Accessibility::PropValueStub& value) override;

    std::vector<std::shared_ptr<Accessibility::ReadableRulesNodeStub>> GetChildren() override;

    std::shared_ptr<Accessibility::ReadableRulesNodeStub> GetParent() override;

    std::vector<std::shared_ptr<FocusRulesCheckNode>> GetAceChildren() override;

    std::shared_ptr<FocusRulesCheckNode> GetAceParent() override;

    bool IsModalForPopup() override;

    std::shared_ptr<Accessibility::ReadableRulesNodeStub> GetUserNextFocusNode() override;

    std::shared_ptr<Accessibility::ReadableRulesNodeStub> GetUserPrevFocusNode() override;

    bool IsAccessibiltyVisible() override;

    bool IsChildTreeContainer() override;

    bool IsEmbededTarget() override;

    RefPtr<NG::FrameNode> GetFrameNode()
    {
        return weakNode_.Upgrade();
    }

    void SetNextFocusFrameNode(const RefPtr<NG::FrameNode>& frameNode)
    {
        nextNode_ = frameNode;
    }

    void SetPrevFocusFrameNode(const RefPtr<NG::FrameNode>& frameNode)
    {
        prevNode_ = frameNode;
    }
private:
    template<typename T>
    std::vector<std::shared_ptr<T>> GetChildrenTemplate();
    NG::FrameNodeHandleParam handleParam_;
    WeakPtr<NG::FrameNode> weakNode_;
    WeakPtr<NG::FrameNode> nextNode_;
    WeakPtr<NG::FrameNode> prevNode_;
};
} // OHOS::Ace::Framework
#endif // FOUNDATION_ACE_ADAPTER_OHOS_OSAL_ACCESSIBILITY_FOCUS_MOVE_ACCESSIBILITY_FOCUS_FRAME_NODE_UTILS_H
