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

#include "core/pipeline/base/composed_element.h"

#include "base/log/dump_log.h"
#include "base/log/log.h"
#include "base/utils/utils.h"
#include "core/common/frontend.h"
#include "core/pipeline/base/composed_component.h"
#include "core/pipeline/base/render_element.h"

namespace OHOS::Ace {

ComposedElement::ComposedElement(const ComposeId& id) : id_(id)
{
    type_ = COMPOSED_ELEMENT;
}

RefPtr<Element> ComposedElement::Create(const ComposeId& id)
{
    LOGD("ComposedElement::Create");
    return AceType::MakeRefPtr<ComposedElement>(id);
}

void ComposedElement::Detached()
{
    auto context = context_.Upgrade();
    if (addedToMap_ && context) {
        context->RemoveComposedElement(id_, AceType::Claim(this));
        addedToMap_ = false;
    }
}

void ComposedElement::Deactivate()
{
    Detached();
}

void ComposedElement::PerformBuild()
{
    LOGD("ComposedComponent PerformBuild.");
    auto context = context_.Upgrade();
    if (context && !addedToMap_) {
        context->AddComposedElement(id_, AceType::Claim(this));
        addedToMap_ = true;
    }

    const auto& child = children_.empty() ? nullptr : children_.front();
    if (HasRenderFunction()) {
        const auto& component = CallRenderFunction();
        UpdateChild(child, component, GetSlot());
    } else {
        const auto& component = BuildChild();
        if (context && context->GetIsDeclarative()) {
            UpdateChild(child, component, GetSlot());
        } else {
            UpdateChild(child, component);
        }
    }
}

void ComposedElement::Update()
{
    const RefPtr<ComposedComponent> compose = AceType::DynamicCast<ComposedComponent>(component_);
    if (compose != nullptr) {
        name_ = compose->GetName();
        if (id_ != compose->GetId()) {
            auto context = context_.Upgrade();
            if (addedToMap_ && context != nullptr) {
                context->RemoveComposedElement(id_, AceType::Claim(this));
                context->AddComposedElement(compose->GetId(), AceType::Claim(this));
            }
            id_ = compose->GetId();
        }
        compose->ClearNeedUpdate();
    }
}

RefPtr<Component> ComposedElement::BuildChild()
{
    RefPtr<ComposedComponent> compose = AceType::DynamicCast<ComposedComponent>(component_);
    if (compose != nullptr) {
        return compose->GetChild();
    }
    return nullptr;
}

void ComposedElement::Apply(const RefPtr<Element>& child)
{
    if (!child) {
        LOGE("Element child is null");
        return;
    }

    if (!parentRenderNode_) {
        LOGE("ComposedElement don't have a parent render node");
        return;
    }

    if (child->GetType() == RENDER_ELEMENT) {
        // Directly attach the RenderNode if child is ComposedElement
        RefPtr<RenderElement> renderChild = AceType::DynamicCast<RenderElement>(child);
        if (renderChild) {
            parentRenderNode_->AddChild(renderChild->GetRenderNode(), GetSlot());
        }
    } else if (child->GetType() == COMPOSED_ELEMENT) {
        // if child is ComposedElement, just set parent render node
        RefPtr<ComposedElement> composeChild = AceType::DynamicCast<ComposedElement>(child);
        if (composeChild) {
            composeChild->SetParentRenderNode(parentRenderNode_);
        }
    }
}

void ComposedElement::Dump()
{
    DumpLog::GetInstance().AddDesc("name:" + name_);
    DumpLog::GetInstance().AddDesc("id:" + id_);
}

bool ComposedElement::CanUpdate(const RefPtr<Component>& newComponent)
{
    auto compose = AceType::DynamicCast<ComposedComponent>(newComponent);
    if (!compose) {
        return false;
    }
    if (compose->GetId() == id_) {
        return true;
    }
    if (children_.empty()) {
        return true;
    }
    auto childComponent = compose->GetChild();
    if (!childComponent) {
        return true;
    }
    return children_.front()->CanUpdate(childComponent);
}

bool ComposedElement::NeedUpdateWithComponent(const RefPtr<Component>& newComponent)
{
    auto component = AceType::DynamicCast<ComposedComponent>(newComponent);
    if (component) {
        auto newId = component->GetId();
        if (newId.empty()) {
            return true;
        }

        if (component->NeedUpdate()) {
            return true;
        }

        auto context = context_.Upgrade();
        if (context && context->GetIsDeclarative()) {
            return newId == id_;
        } else {
            return newId != id_;
        }
    }
    return true;
}

} // namespace OHOS::Ace
