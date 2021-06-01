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

#include "core/pipeline/base/render_element.h"

#include "base/log/log.h"
#include "base/utils/string_utils.h"
#include "base/utils/utils.h"
#include "core/accessibility/accessibility_manager.h"
#include "core/components/focus_animation/render_focus_animation.h"
#include "core/components/shadow/render_shadow.h"
#include "core/pipeline/base/composed_element.h"
#include "core/pipeline/base/render_component.h"

namespace OHOS::Ace {

RenderElement::RenderElement()
{
    type_ = RENDER_ELEMENT;
}

RenderElement::~RenderElement() {}

void RenderElement::Prepare(const WeakPtr<Element>& parent)
{
    if (!renderNode_) {
        renderNode_ = CreateRenderNode();
    }
    if (renderNode_ != nullptr) {
        SetAccessibilityNode(parent);
        renderNode_->Attach(context_);
    }

    // register on fcous move callback
    auto focusItem = AceType::DynamicCast<FocusNode>(this);
    if (focusItem) {
        focusItem->SetFocusMoveCallback([weak = AceType::WeakClaim(this)] {
            auto element = weak.Upgrade();
            if (element && element->renderNode_) {
                element->renderNode_->MoveWhenOutOfViewPort(true);
            }
        });
    }
}

void RenderElement::SetAccessibilityNode(const WeakPtr<Element>& parent)
{
    auto parentNode = parent.Upgrade();
    while (parentNode) {
        if (!parentNode->IsAutoAccessibility()) {
            break;
        }
        if (AceType::TypeId(parentNode) == AceType::TypeId<ComposedElement>()) {
            auto composedElement = AceType::DynamicCast<ComposedElement>(parentNode);
            if (!composedElement) {
                LOGE("SetAccessibilityNode composedElement is null");
                return;
            }
            composeId_ = composedElement->GetId();
            SetAccessibilityNodeById(composeId_);
            break;
        } else {
            parentNode = parentNode->GetElementParent().Upgrade();
        }
    }
}

void RenderElement::SetAccessibilityNodeById(const ComposeId& id)
{
    auto context = context_.Upgrade();
    if (!context) {
        LOGE("SetAccessibilityNode context is null");
        return;
    }
    if (!renderNode_) {
        LOGE("RenderElement don't have a render node");
        return;
    }
    auto accessibilityManager = context->GetAccessibilityManager();
    if (!accessibilityManager) {
        LOGE("SetAccessibilityNode accessibilityManager is null");
        return;
    }
    auto nodeId = StringUtils::StringToInt(id);
    auto accessibilityNode = accessibilityManager->GetAccessibilityNodeById(nodeId);
    if (accessibilityNode) {
        renderNode_->SetAccessibilityNode(accessibilityNode);
    }
}

void RenderElement::UpdateAccessibilityNode()
{
    // fetch new composedId from component.
    ComposeId updateId;
    auto component = component_;
    while (component) {
        auto composedNode = AceType::DynamicCast<ComposedComponent>(component);
        if (composedNode) {
            updateId = composedNode->GetId();
            break;
        }
        component = component->GetParent().Upgrade();
    }

    // Update new composedId to renderNode.
    if (!updateId.empty() && updateId != composeId_) {
        SetAccessibilityNodeById(updateId);
        LOGD("Update ComposeId from %s to %s", composeId_.c_str(), updateId.c_str());
        composeId_ = updateId;
    }
}

void RenderElement::Apply(const RefPtr<Element>& child)
{
    if (!child) {
        LOGE("Element child is null");
        return;
    }

    if (!renderNode_) {
        LOGE("RenderElement don't have a render node");
        return;
    }

    if (child->GetType() == RENDER_ELEMENT) {
        // Directly attach the RenderNode if child is RenderElement.
        RefPtr<RenderElement> renderChild = AceType::DynamicCast<RenderElement>(child);
        if (renderChild) {
            renderNode_->AddChild(renderChild->GetRenderNode(), renderChild->GetSlot());
        }
    } else if (child->GetType() == COMPOSED_ELEMENT) {
        // If child is ComposedElement, just set parent render node.
        RefPtr<ComposedElement> composeChild = AceType::DynamicCast<ComposedElement>(child);
        if (composeChild) {
            composeChild->SetParentRenderNode(renderNode_);
        }
    }
}

void RenderElement::Update()
{
    if (renderNode_ != nullptr) {
        UpdateAccessibilityNode();
        renderNode_->UpdateAll(component_);
    }
}

RefPtr<RenderNode> RenderElement::CreateRenderNode()
{
    RefPtr<RenderComponent> renderComponent = AceType::DynamicCast<RenderComponent>(component_);
    if (renderComponent) {
        auto renderNode = GetCachedRenderNode();
        if (renderNode) {
            LOGD("RenderElement Using Cache RenderNode");
            return renderNode;
        } else {
            return renderComponent->CreateRenderNode();
        }
    }
    return nullptr;
}

void RenderElement::Detached()
{
    Deactivate();
    if (renderNode_) {
        renderNode_ = nullptr;
    }
}

void RenderElement::Deactivate()
{
    if (renderNode_) {
        auto focusAnimation = AceType::DynamicCast<RenderFocusAnimation>(renderNode_);
        auto context = context_.Upgrade();
        if (focusAnimation) {
            if (context) {
                focusAnimation->IsRoot() ? context->PopRootFocusAnimation() : context->PopFocusAnimation();
            }
        }

        auto shadow = AceType::DynamicCast<RenderShadow>(renderNode_);
        if (shadow) {
            if (context) {
                context->PopShadow();
            }
        }
        if (renderNode_->NeedWindowBlur()) {
            renderNode_->MarkNeedWindowBlur(false);
        }
        renderNode_->Unmount();
    }
}

} // namespace OHOS::Ace
