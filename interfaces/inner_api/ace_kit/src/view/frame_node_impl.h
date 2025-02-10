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

#ifndef FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_SRC_VIEW_FRAME_NODE_IMPL_H
#define FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_SRC_VIEW_FRAME_NODE_IMPL_H

#include "interfaces/inner_api/ace_kit/include/ui/view/frame_node.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/layout/layout_wrapper.h"

namespace OHOS::Ace::Kit {
using AceNode = NG::FrameNode;

class FrameNodeImpl : public FrameNode {
    DECLARE_ACE_TYPE(FrameNodeImpl, FrameNode);

public:
    FrameNodeImpl(const RefPtr<AceNode>& node, const RefPtr<Pattern>& pattern);
    explicit FrameNodeImpl(const RefPtr<AceNode>& node);
    ~FrameNodeImpl();

    void Reset() override;

    void Measure(const Kit::LayoutConstraintInfo& parentContraint) override;
    void Layout() override;

    void InitializePatternAndContext() override;

    RefPtr<NG::LayoutProperty> GetLayoutProperty() override;
    RefPtr<Pattern> GetPattern() override;
    void PushAceNode(const RefPtr<AceNode>& node);
    RefPtr<AceNode> PopAceNode();
    RefPtr<AceNode> GetAceNode() const;
    NG::LayoutWrapper* GetLayoutWrapper();
    RefPtr<UIContext> GetUIContext() const override;
    AceNode* GetAceNodePtr();
    RefPtr<Property> GetProperty() override;

    void AddChild(const RefPtr<FrameNode>& child) override;
    std::list<RefPtr<FrameNode>> GetChildren() override;
    void MarkDirtyNode(NG::PropertyChangeFlag flag) override;
    void RemoveChild(const RefPtr<FrameNode>& child) override;

    std::string GetTag() const override;
    int32_t GetId() const override;

    void MeasureChildren() override;
    void LayoutChildren() override;
    NodeHandle GetHandle() override;

private:
    AceNode* frameNode_;
    RefPtr<AceNode> nodeRef_;
    RefPtr<Pattern> pattern_;
    RefPtr<Property> property_;
};
} // namespace OHOS::Ace::Kit

#endif // FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_SRC_VIEW_FRAME_NODE_IMPL_H
