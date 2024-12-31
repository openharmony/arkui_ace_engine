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

#include "interfaces/inner_api/ace_kit/src/view/frame_node_impl.h"

#include "interfaces/inner_api/ace_kit/include/ui/base/ace_type.h"
#include "interfaces/inner_api/ace_kit/include/ui/base/referenced.h"
#include "interfaces/inner_api/ace_kit/include/ui/base/utils/utils.h"
#include "interfaces/inner_api/ace_kit/include/ui/view/pattern.h"

#include "core/components_ng/property/calc_length.h"
#include "core/components_ng/property/property.h"

namespace OHOS::Ace::Kit {

FrameNodeImpl::FrameNodeImpl(const RefPtr<AceNode>& node, const RefPtr<Pattern>& pattern)
    : nodeRef_(node), pattern_(pattern)
{
    frameNode_ = AceType::RawPtr(node);
    node->MarkDirtyNode(NG::PROPERTY_UPDATE_MEASURE | NG::PROPERTY_UPDATE_RENDER);
}

FrameNodeImpl::~FrameNodeImpl()
{
    Reset();
}

void FrameNodeImpl::Reset()
{
    frameNode_ = nullptr;
    nodeRef_.Reset();
    pattern_.Reset();
}

void FrameNodeImpl::InitializePatternAndContext()
{
    CHECK_NULL_VOID(frameNode_);
    frameNode_->InitializePatternAndContext();
}

RefPtr<AceNode> FrameNodeImpl::PopAceNode()
{
    RefPtr<AceNode> node;
    node.Swap(nodeRef_);
    return node;
}

void FrameNodeImpl::Measure(const std::optional<NG::LayoutConstraintT<float>>& parentContraint)
{
    CHECK_NULL_VOID(frameNode_);
    frameNode_->Measure(parentContraint);
}

void FrameNodeImpl::Layout()
{
    CHECK_NULL_VOID(frameNode_);
    frameNode_->Layout();
}

RefPtr<Ace::NG::LayoutProperty> FrameNodeImpl::GetLayoutProperty()
{
    CHECK_NULL_RETURN(frameNode_, nullptr);
    return frameNode_->GetLayoutProperty();
}

RefPtr<Pattern> FrameNodeImpl::GetPattern()
{
    return pattern_;
}

NG::LayoutWrapper* FrameNodeImpl::GetLayoutWrapper()
{
    CHECK_NULL_RETURN(frameNode_, nullptr);
    return frameNode_;
}
} // namespace OHOS::Ace::Kit
