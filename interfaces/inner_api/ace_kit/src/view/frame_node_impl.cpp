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

#include "ui/base/ace_type.h"
#include "ui/base/referenced.h"
#include "ui/base/utils/utils.h"
#include "ui/view/frame_node.h"
#include "ui/view/pattern.h"
#include "ui/view/ui_context.h"

#include "core/components_ng/property/calc_length.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/property/property.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::Kit {

FrameNodeImpl::FrameNodeImpl(const RefPtr<AceNode>& node, const RefPtr<Pattern>& pattern)
    : nodeRef_(node), pattern_(pattern)
{
    frameNode_ = AceType::RawPtr(node);
}

FrameNodeImpl::FrameNodeImpl(const RefPtr<AceNode>& node) : nodeRef_(node)
{
    frameNode_ = AceType::RawPtr(node);
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
    CHECK_NULL_VOID(pattern_);
    property_ = pattern_->CreateProperty();
    CHECK_NULL_VOID(property_);
    property_->SetHost(WeakClaim(this));
}

void FrameNodeImpl::PushAceNode(const RefPtr<AceNode>& node)
{
    nodeRef_ = node;
}

RefPtr<AceNode> FrameNodeImpl::PopAceNode()
{
    RefPtr<AceNode> node;
    node.Swap(nodeRef_);
    return node;
}

RefPtr<AceNode> FrameNodeImpl::GetAceNode() const
{
    return nodeRef_;
}

AceNode* FrameNodeImpl::GetAceNodePtr()
{
    return frameNode_;
}

void FrameNodeImpl::Measure(const Kit::LayoutConstraintInfo& parentContraint)
{
    CHECK_NULL_VOID(frameNode_);
    std::optional<NG::LayoutConstraintF> constraint = std::make_optional<NG::LayoutConstraintF>();
    //minWidth
    constraint->minSize.SetWidth(parentContraint.minWidth);
    //minHeight
    constraint->minSize.SetHeight(parentContraint.minHeight);
    //maxWidth
    constraint->maxSize.SetWidth(parentContraint.maxWidth);
    //maxHeight
    constraint->maxSize.SetHeight(parentContraint.maxHeight);
    //minWidth == maxWidth
    if (parentContraint.minWidth == parentContraint.maxWidth) {
        constraint->selfIdealSize.SetWidth(parentContraint.minWidth);
    }
    //minHeight == maxHeight
    if (parentContraint.minHeight == parentContraint.maxHeight) {
        constraint->selfIdealSize.SetHeight(parentContraint.minHeight);
    }
    //percentReferenceWidth
    constraint->percentReference.SetWidth(parentContraint.percentReferWidth);
    //percentReferenceHeight
    constraint->percentReference.SetHeight(parentContraint.percentReferHeight);
    frameNode_->SetActive(true);
    frameNode_->Measure(constraint);
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

RefPtr<Property> FrameNodeImpl::GetProperty()
{
    return property_;
}

NG::LayoutWrapper* FrameNodeImpl::GetLayoutWrapper()
{
    CHECK_NULL_RETURN(frameNode_, nullptr);
    return frameNode_;
}

void FrameNodeImpl::MeasureChildren()
{
    CHECK_NULL_VOID(frameNode_);
    auto layoutConstraint = frameNode_->GetLayoutProperty()->CreateChildConstraint();
    for (auto& child : frameNode_->GetAllChildrenWithBuild()) {
        child->Measure(layoutConstraint);
    }
}

void FrameNodeImpl::LayoutChildren()
{
    CHECK_NULL_VOID(frameNode_);
    for (auto& child : frameNode_->GetAllChildrenWithBuild()) {
        child->Layout();
    }
}

RefPtr<UIContext> FrameNodeImpl::GetUIContext() const
{
    CHECK_NULL_RETURN(frameNode_, nullptr);
    auto* pipeline = frameNode_->GetContextWithCheck();
    CHECK_NULL_RETURN(pipeline, nullptr);
    return pipeline->GetUIContext();
}

NodeHandle FrameNodeImpl::GetHandle()
{
    return reinterpret_cast<NodeHandle>(frameNode_);
}

void FrameNodeImpl::AddChild(const RefPtr<FrameNode>& child)
{
    CHECK_NULL_VOID(frameNode_);
    auto childNode = AceType::DynamicCast<FrameNodeImpl>(child);
    CHECK_NULL_VOID(childNode);
    auto* childNodePtr = childNode->GetAceNodePtr();
    CHECK_NULL_VOID(childNodePtr);
    frameNode_->AddChild(AceType::Claim(childNodePtr));
}

std::list<RefPtr<FrameNode>> FrameNodeImpl::GetChildren()
{
    std::list<RefPtr<FrameNode>> children;
    CHECK_NULL_RETURN(frameNode_, children);
    for (auto& child : frameNode_->GetAllChildrenWithBuild(false)) {
        auto node = child->GetHostNode();
        if (!node) {
            continue;
        }
        auto kitNode = node->GetKitNode();
        if (!kitNode) {
            kitNode = MakeRefPtr<FrameNodeImpl>(node);
        }
        children.emplace_back(kitNode);
    }
    return children;
}

void FrameNodeImpl::MarkDirtyNode(NG::PropertyChangeFlag flag)
{
    CHECK_NULL_VOID(frameNode_);
    frameNode_->MarkDirtyNode(flag);
}

void FrameNodeImpl::RemoveChild(const RefPtr<FrameNode> &child)
{
    CHECK_NULL_VOID(frameNode_);
    auto childNode = AceType::DynamicCast<FrameNodeImpl>(child);
    auto* childNodePtr = childNode->GetAceNodePtr();
    CHECK_NULL_VOID(childNodePtr);
    frameNode_->RemoveChild(AceType::Claim(childNodePtr));
}

std::string FrameNodeImpl::GetTag() const
{
    CHECK_NULL_RETURN(frameNode_, "");
    return frameNode_->GetTag();
}

int32_t FrameNodeImpl::GetId() const
{
    CHECK_NULL_RETURN(frameNode_, -1);
    return frameNode_->GetId();
}
} // namespace OHOS::Ace::Kit
