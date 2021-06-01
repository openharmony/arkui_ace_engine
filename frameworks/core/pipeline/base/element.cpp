/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "core/pipeline/base/element.h"

#include "base/log/dump_log.h"
#include "base/log/log.h"
#include "core/common/frontend.h"
#include "core/components/focus_animation/focus_animation_element.h"
#include "core/components/page/page_element.h"
#include "core/components/shadow/shadow_element.h"
#include "core/pipeline/base/component.h"
#include "core/pipeline/base/composed_element.h"
#include "core/pipeline/pipeline_context.h"

namespace OHOS::Ace {

Element::~Element()
{
    for (const auto& child : children_) {
        DetachChild(child);
    }
}

void Element::AddChild(const RefPtr<Element>& child, int32_t slot)
{
    if (child != nullptr) {
        const auto& it = std::find(children_.begin(), children_.end(), child);
        if (it == children_.end()) {
            auto pos = children_.begin();
            std::advance(pos, slot);
            children_.insert(pos, child);
            child->SetParent(AceType::WeakClaim(this));
            child->SetSlot(slot);
            Apply(child);
        } else {
            LOGW("Element exist AddChild failed");
        }
    }
}

void Element::RemoveChild(const RefPtr<Element>& child)
{
    if (child) {
        DetachChild(child);
        children_.remove(child);
    }
}

void Element::DeactivateChild(const RefPtr<Element>& child)
{
    if (child) {
        RefPtr<PipelineContext> context = context_.Upgrade();
        if (context) {
            child->parent_ = nullptr;
            context->AddDeactivateElement(child->GetRetakeId(), child);
        }
        auto focusNode = AceType::DynamicCast<FocusNode>(child);
        if (focusNode) {
            focusNode->RemoveSelf();
        }
        child->Deactivate();
        children_.remove(child);
    }
}

void Element::DetachChild(const RefPtr<Element>& child)
{
    auto focusNode = AceType::DynamicCast<FocusNode>(child);
    if (focusNode) {
        focusNode->RemoveSelf();
    }
    child->Detached();
}

void Element::Rebuild()
{
    // When rebuild comes, newComponent_ should not be null, and will go to these 3 steps:
    // 1. Update self using new component
    // 2. PerformBuild will build and update child recursively
    // 3. Finish update and release the new component
    Update();
    PerformBuild();
    SetNewComponent(nullptr);
}

void Element::DumpTree(int32_t depth)
{
    if (DumpLog::GetInstance().GetDumpFile()) {
        Dump();
        DumpLog::GetInstance().AddDesc(std::string("retakeID: ").append(std::to_string(GetRetakeId())));
        DumpLog::GetInstance().Print(depth, AceType::TypeName(this), children_.size());
    }

    for (const auto& item : children_) {
        item->DumpTree(depth + 1);
    }
}

void Element::Dump() {}

bool Element::CanUpdate(const RefPtr<Component>& newComponent)
{
    // The raw ptr is persistent during app process.
    return componentTypeName_ == AceType::TypeName(newComponent);
}

inline RefPtr<Element> Element::DoUpdateChildWithNewComponent(
    const RefPtr<Element>& child, const RefPtr<Component>& newComponent, int32_t slot)
{
    child->SetNewComponent(newComponent);
    child->SetSlot(slot);
    child->Update();
    child->PerformBuild();
    return child;
}

RefPtr<Element> Element::UpdateChild(const RefPtr<Element>& child, const RefPtr<Component>& newComponent, int32_t slot)
{
    // Considering 4 cases:
    // 1. child == null && newComponent == null  -->  do nothing
    // 2. child == null && newComponent != null  -->  create new child configured with newComponent
    // 3. child != null && newComponent == null  -->  remove old child
    // 4. child != null && newComponent != null  -->  update old child with new configuration if possible(determined by
    //    [Element::CanUpdate]), or remove the old child and create new one configured with newComponent.
    if (!child) {
        if (!newComponent) {
            return nullptr;
        } else {
            return InflateComponent(newComponent, slot);
        }
    } else {
        if (!newComponent) {
            DeactivateChild(child);
            return nullptr;
        } else {
            if (child->CanUpdate(newComponent)) {
                auto context = context_.Upgrade();
                bool declarative = context ? context->GetIsDeclarative() : false;
                if (!declarative) {
                    // old, non-declarative code path
                    return DoUpdateChildWithNewComponent(child, newComponent, slot);
                } else {
                    // Declarative path
                    if (!newComponent->IsStatic()) {
                        // non static component
                        if (newComponent->HasElementFunction()) {
                            newComponent->CallElementFunction(AceType::RawPtr(child));
                        }
                        DoUpdateChildWithNewComponent(child, newComponent, slot);
                        child->SetNewComponent(nullptr);
                        return child;
                    } else {
                        // Declarative && Component marked as static
                        child->SetSlot(slot);
                        auto traverseChild = child;
                        while (AceType::TypeName<ComposedElement>() == AceType::TypeName(traverseChild)) {
                            // this child is a composedelement
                            // update its only child slot
                            // if the child is again composed component
                            // do the same until we hit a renderelement
                            traverseChild = traverseChild->GetFirstChild();
                            traverseChild->SetSlot(slot);
                        }
                        LOGD("skipping update for static child: %s", child->GetTag());
                        child->SetSlot(slot);
                        return child;
                    }
                }
            } else {
                // Can not update
                RefPtr<PipelineContext> context = context_.Upgrade();
                auto needRebuildFocusElement = AceType::DynamicCast<Element>(GetFocusScope());
                if (context && needRebuildFocusElement) {
                    context->AddNeedRebuildFocusElement(needRebuildFocusElement);
                }
                DeactivateChild(child);
                return InflateComponent(newComponent, slot);
            }
        }
    }
}

void Element::Mount(const RefPtr<Element>& parent, int32_t slot)
{
    SetParent(parent);
    SetDepth(parent != nullptr ? parent->GetDepth() + 1 : 1);
    SetPipelineContext(parent != nullptr ? parent->context_ : context_);
    Prepare(parent);
    if (parent) {
        parent->AddChild(AceType::Claim(this), slot);
        AddToFocus();
    }
    Rebuild();
}

void Element::AddToFocus()
{
    auto parent = parent_.Upgrade();
    if (!parent) {
        return;
    }
    auto focusNode = AceType::DynamicCast<FocusNode>(this);
    if (focusNode) {
        auto scope = parent->GetFocusScope();
        if (scope) {
            auto brothers = parent->GetChildren();
            auto iter = std::find(brothers.begin(), brothers.end(), AceType::Claim(this));
            if (iter == brothers.end()) {
                return;
            }
            ++iter;
            while (iter != brothers.end()) {
                auto nextFocusNode = AceType::DynamicCast<FocusNode>(*iter);
                if (nextFocusNode) {
                    break;
                }
                ++iter;
            }
            if (iter != brothers.end()) {
                scope->AddChild(AceType::Claim(focusNode), AceType::DynamicCast<FocusNode>(*iter));
            } else {
                scope->AddChild(AceType::Claim(focusNode));
            }
            focusNode->SetParentFocusable(scope->FocusNode::IsFocusable());
        }
    }

    auto focusAnimation = AceType::DynamicCast<FocusAnimationElement>(this);
    if (focusAnimation) {
        auto context = context_.Upgrade();
        if (context) {
            context->PushFocusAnimation(AceType::Claim(this));
        }
    }

    auto shadow = AceType::DynamicCast<ShadowElement>(this);
    if (shadow) {
        auto context = context_.Upgrade();
        if (context) {
            context->PushShadow(AceType::Claim(this));
        }
    }
}

void Element::MarkDirty()
{
    RefPtr<PipelineContext> context = context_.Upgrade();
    if (context) {
        context->AddDirtyElement(AceType::Claim(this));
    }
}

void Element::SetUpdateComponent(const RefPtr<Component>& newComponent)
{
    SetNewComponent(newComponent);
    RefPtr<PipelineContext> context = context_.Upgrade();
    if (context) {
        context->AddDirtyElement(AceType::Claim(this));
    }
}

const std::list<RefPtr<Element>>& Element::GetChildren() const
{
    return children_;
}

RefPtr<Element> Element::GetFirstChild() const
{
    if (children_.empty()) {
        return nullptr;
    }
    return children_.front();
}

RefPtr<Element> Element::GetLastChild() const
{
    if (children_.empty()) {
        return nullptr;
    }
    return children_.back();
}

void Element::SetPipelineContext(const WeakPtr<PipelineContext>& context)
{
    context_ = context;
    OnContextAttached();
}

RefPtr<Element> Element::InflateComponent(const RefPtr<Component>& newComponent, int32_t slot)
{
    // confirm whether there is a reuseable element.
    auto retakeElement = RetakeDeactivateElement(newComponent);
    if (retakeElement) {
        retakeElement->SetNewComponent(newComponent);
        retakeElement->SetSlot(slot);
        retakeElement->Mount(AceType::Claim(this), slot);
        return retakeElement;
    }

    RefPtr<Element> newChild = newComponent->CreateElement();
    newChild->SetNewComponent(newComponent);
    newChild->Mount(AceType::Claim(this), slot);
    return newChild;
}

RefPtr<FocusGroup> Element::GetFocusScope()
{
    auto rawPtrFocusGroup = AceType::DynamicCast<FocusGroup>(this);
    if (rawPtrFocusGroup) {
        return AceType::Claim(rawPtrFocusGroup);
    }

    auto rawPtrFocusNode = AceType::DynamicCast<FocusNode>(this);
    if (rawPtrFocusNode) {
        return nullptr;
    }

    auto parent = parent_.Upgrade();
    if (parent) {
        return parent->GetFocusScope();
    }

    return nullptr;
}

void Element::SetSlot(int32_t slot)
{
    auto context = context_.Upgrade();
    if (context && context->GetIsDeclarative()) {
        bool layoutNeeded = slot_ != slot;
        slot_ = slot;
        if (GetType() == RENDER_ELEMENT) {
            auto renderNode = GetRenderNode();
            if (!renderNode) {
                return;
            }

            auto parentNode = renderNode->GetParent().Upgrade();
            if (!parentNode) {
                return;
            }
            if (parentNode->GetFirstChild() == parentNode->GetLastChild()) {
                // This means it has only one child, no need to update position
                // of the rendernode
                return;
            }

            parentNode->RemoveChild(renderNode);
            parentNode->AddChild(renderNode, slot);
            if (layoutNeeded) {
                parentNode->MarkNeedLayout();
            }
        }
    } else {
        slot_ = slot;
    }
}

RefPtr<PageElement> Element::GetPageElement()
{
    auto pageElement = AceType::DynamicCast<PageElement>(this);
    if (pageElement != nullptr) {
        return AceType::Claim(pageElement);
    }

    auto parent = parent_.Upgrade();

    if (!parent) {
        return nullptr;
    }

    return parent->GetPageElement();
}

RefPtr<Element> Element::RetakeDeactivateElement(const RefPtr<Component>& newComponent)
{
    RefPtr<PipelineContext> context = context_.Upgrade();
    if (context != nullptr) {
        return context->GetDeactivateElement(newComponent->GetRetakeId());
    }
    return nullptr;
}

void Element::RebuildFocusTree()
{
    auto focusScope = AceType::DynamicCast<FocusGroup>(this);
    if (!focusScope) {
        return;
    }

    std::list<RefPtr<FocusNode>> rebuildFocusNodes;
    for (auto& item : children_) {
        auto tmp = item->RebuildFocusChild();
        if (tmp != nullptr) {
            rebuildFocusNodes.emplace_back(tmp);
        }
    }
    focusScope->RebuildChild(std::move(rebuildFocusNodes));
}

RefPtr<FocusNode> Element::RebuildFocusChild()
{
    auto focusNode = AceType::DynamicCast<FocusNode>(this);
    if (focusNode) {
        return AceType::Claim(focusNode);
    }

    for (auto& item : children_) {
        return item->RebuildFocusChild();
    }
    return nullptr;
}

} // namespace OHOS::Ace
