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

#include "core/components_ng/pattern/stage/page_node.h"
#include "core/pipeline/base/element_register.h"

namespace OHOS::Ace::NG {
RefPtr<PageNode> PageNode::CreatePageNode(int32_t nodeId, const RefPtr<Pattern>& pattern, bool isRoot)
{
    auto pageNode = MakeRefPtr<PageNode>(V2::PAGE_ETS_TAG, nodeId, pattern, isRoot);
    ElementRegister::GetInstance()->AddUINode(pageNode);
    pageNode->InitializePatternAndContext();
    return pageNode;
}

void PageNode::Measure(const std::optional<LayoutConstraintF>& parentConstraint)
{
    if (viewportConfig_) {
        ScopePageViewportConfig scopeConfig(viewportConfig_);
        auto constraint = viewportConfig_->CreateRootLayoutConstraint();
        FrameNode::Measure(constraint);
        return;
    }
    FrameNode::Measure(parentConstraint);
}

void PageNode::Layout()
{
    if (viewportConfig_) {
        ScopePageViewportConfig scopeConfig(viewportConfig_);
        FrameNode::Layout();
        return;
    }
    FrameNode::Layout();
}
} // namespace OHOS::Ace::NG
