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

#include "core/components/form/form_component.h"

#include "core/components/form/form_element.h"
#include "core/components/stage/stage_component.h"

namespace OHOS::Ace {

FormComponent::FormComponent(const ComposeId& id, const std::string& name, const RefPtr<Component>& child)
    : ComposedComponent(id, name, child)
{
    CreateChildren();
}

FormComponent::FormComponent(const ComposeId& id, const std::string& name) : ComposedComponent(id, name)
{
    CreateChildren();
}

void FormComponent::CreateChildren()
{
    // form-box(size-developer-set)-transform-cardbox(size-developer-set/density)-stage
    mountBox_ = AceType::MakeRefPtr<BoxComponent>();
    auto rootBox = AceType::MakeRefPtr<BoxComponent>();
    RefPtr<TransformComponent> cardTransformComponent_ = AceType::MakeRefPtr<TransformComponent>();
    cardTransformComponent_->SetOriginDimension(
        DimensionOffset(Dimension(0.5, DimensionUnit::PERCENT), Dimension(0.5, DimensionUnit::PERCENT)));
    RefPtr<StageComponent> stage = AceType::MakeRefPtr<StageComponent>(std::list<RefPtr<Component>>());

    stage->SetParent(rootBox);
    rootBox->SetParent(cardTransformComponent_);
    cardTransformComponent_->SetParent(mountBox_);
    mountBox_->SetParent(AceType::WeakClaim(this));

    mountBox_->SetChild(cardTransformComponent_);
    cardTransformComponent_->SetChild(rootBox);
    rootBox->SetChild(stage);
    SetChild(mountBox_);
}

RefPtr<Element> FormComponent::CreateElement()
{
    return AceType::MakeRefPtr<FormElement>("");
}

} // namespace OHOS::Ace