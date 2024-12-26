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
    ~FrameNodeImpl();

    void Reset() override;
    void Measure(const std::optional<NG::LayoutConstraintT<float>>& parentContraint) override;

    void Layout() override;

    void InitializePatternAndContext() override;

    RefPtr<NG::LayoutProperty> GetLayoutProperty() override;
    RefPtr<Pattern> GetPattern() override;
    RefPtr<AceNode> PopAceNode();
    NG::LayoutWrapper* GetLayoutWrapper();

private:
    AceNode* frameNode_;
    RefPtr<AceNode> nodeRef_;
    RefPtr<Pattern> pattern_;
};
} // namespace OHOS::Ace::Kit

#endif // FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_SRC_VIEW_FRAME_NODE_IMPL_H
