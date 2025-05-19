/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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
#include "ui/properties/ng/measure_property.h"
#include "ui/view/frame_node.h"
#include "ui/view/pattern.h"
#include "ui/view/ui_context.h"

#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/components_ng/property/property.h"
#include "core/interfaces/arkoala/arkoala_api.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::Kit {
RefPtr<FrameNode> FrameNode::GetFrameNode(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto kitNode = frameNode->GetKitNode();
    if (!kitNode) {
        kitNode = MakeRefPtr<FrameNodeImpl>(Claim(frameNode));
    }
    return kitNode;
}

FrameNodeImpl::FrameNodeImpl(const RefPtr<AceNode>& node, const RefPtr<Pattern>& pattern)
    : frameNode_(AceType::RawPtr(node)), pattern_(pattern)
{
    // Need temporary save strong pointer to AceNode in the FrameNodeImpl.
    // That guaranty that AceNode will not be destroyed since there is strong pointer to it.
    // Need to keep this temporary strong pointer until ownership of AceNode will be moved ace_engine
    // with ViewStackProcessor::Push() call or FrameNodeImpl::AddChild() call or other calls like this.
    // Call FrameNodeImpl::MoveOwnershipAndGetAceNode() when you need put AceNode to ace_engine.
    PushAceNode(node);
}

FrameNodeImpl::FrameNodeImpl(const RefPtr<AceNode>& node) : frameNode_(AceType::RawPtr(node))
{
    // The same reason of this call as above
    PushAceNode(node);
}

// This constructor should be called for AceNode that already owned by ace_engine
// so PushAceNode() is not called here.
FrameNodeImpl::FrameNodeImpl(AceNode* node) : frameNode_(node) {}

FrameNodeImpl::~FrameNodeImpl()
{
    Reset();
}

void FrameNodeImpl::Reset()
{
    frameNode_ = nullptr;
    nodeTempRef_.Reset();
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
    nodeTempRef_ = node;
}

RefPtr<AceNode> FrameNodeImpl::PopAceNode()
{
    RefPtr<AceNode> node;
    node.Swap(nodeTempRef_);
    return node;
}

RefPtr<AceNode> FrameNodeImpl::MoveOwnershipAndGetAceNode()
{
    auto aceNode = PopAceNode();
    if (aceNode) {
        aceNode->SetKitNode(AceType::Claim(this));
    } else {
        aceNode = GetAceNode();
    }
    return aceNode;
}

RefPtr<AceNode> FrameNodeImpl::GetAceNode() const
{
    return AceType::Claim(frameNode_);
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
    auto childNodePtr = childNode->MoveOwnershipAndGetAceNode();
    CHECK_NULL_VOID(childNodePtr);
    frameNode_->AddChild(childNodePtr);
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
            kitNode = MakeRefPtr<FrameNodeImpl>(AceType::RawPtr(node));
            node->SetKitNode(kitNode);
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

void FrameNodeImpl::SetMeasureCallback(const std::function<void(RefPtr<FrameNode>)>& measureCallback)
{
    CHECK_NULL_VOID(frameNode_);
    auto frameNode = frameNode_;
    auto onMeasureCallback = [frameNode, measureCallback](int32_t nodeId) {
        RefPtr<FrameNode> node = frameNode->GetKitNode();
        if (!node) {
            node = AceType::MakeRefPtr<FrameNodeImpl>(frameNode);
        }
        measureCallback(node);
    };
    frameNode_->SetMeasureCallback(std::move(onMeasureCallback));
}

int32_t FrameNodeImpl::GetMeasureWidth()
{
    CHECK_NULL_RETURN(frameNode_, 0);
    return frameNode_->GetGeometryNode()->GetFrameSize().Width();
}

int32_t FrameNodeImpl::GetMeasureHeight()
{
    CHECK_NULL_RETURN(frameNode_, 0);
    return frameNode_->GetGeometryNode()->GetFrameSize().Height();
}

void FrameNodeImpl::SetOnNodeDestroyCallback(const std::function<void(RefPtr<FrameNode>)>& destroyCallback)
{
    CHECK_NULL_VOID(frameNode_);
    auto frameNode = frameNode_;
    auto onDestroyCallback = [frameNode, destroyCallback](int32_t nodeId) {
        RefPtr<FrameNode> node = frameNode->GetKitNode();
        if (!node) {
            node = AceType::MakeRefPtr<FrameNodeImpl>(frameNode);
        }
        destroyCallback(node);
    };
    frameNode_->SetOnNodeDestroyCallback(std::move(onDestroyCallback));
}

void FrameNodeImpl::SetConfigurationUpdateCallback(
    const std::function<void(const ConfigurationChange& configurationChange)>&& callback)
{
    frameNode_->SetConfigurationModeUpdateCallback(std::move(callback));
}

void FrameNodeImpl::AddExtraCustomProperty(const std::string& key, void* extraData)
{
    CHECK_NULL_VOID(frameNode_);
    frameNode_->AddExtraCustomProperty(key, extraData);
}

void* FrameNodeImpl::GetExtraCustomProperty(const std::string& key) const
{
    CHECK_NULL_RETURN(frameNode_, nullptr);
    return frameNode_->GetExtraCustomProperty(key);
}

void FrameNodeImpl::SetClipEdge(bool isClip)
{
    CHECK_NULL_VOID(frameNode_);
    NG::ViewAbstract::SetClipEdge(frameNode_, isClip);
}

void FrameNodeImpl::SetPadding(const NG::PaddingPropertyT<NG::CalcLength>& value)
{
    CHECK_NULL_VOID(frameNode_);
    NG::ViewAbstract::SetPadding(frameNode_, value);
}

void FrameNodeImpl::SetSafeAreaPadding(const NG::CalcLength& value)
{
    CHECK_NULL_VOID(frameNode_);
    NG::ViewAbstract::SetSafeAreaPadding(frameNode_, value);
}

void FrameNodeImpl::ResetSafeAreaPadding()
{
    CHECK_NULL_VOID(frameNode_);
    NG::ViewAbstract::ResetSafeAreaPadding();
}

void FrameNodeImpl::SetLinearGradient(const NG::Gradient& gradient)
{
    CHECK_NULL_VOID(frameNode_);
    NG::ViewAbstract::SetLinearGradient(frameNode_, gradient);
}

void FrameNodeImpl::SetLinearGradientBlur(const NG::LinearGradientBlurPara& blurPara)
{
    CHECK_NULL_VOID(frameNode_);
    NG::ViewAbstract::SetLinearGradientBlur(frameNode_, blurPara);
}

} // namespace OHOS::Ace::Kit
