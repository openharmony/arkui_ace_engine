/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_v2/ability_component/render_ability_component.h"

#include "base/memory/ace_type.h"
#include "core/components_v2/ability_component/ability_component.h"

namespace OHOS::Ace::V2 {
RefPtr<RenderNode> RenderAbilityComponent::Create()
{
    return AceType::MakeRefPtr<RenderAbilityComponent>();
}

void RenderAbilityComponent::Update(const RefPtr<Component>& component)
{
    RefPtr<V2::AbilityComponent> abilityComponent = AceType::DynamicCast<V2::AbilityComponent>(component);
    if (!abilityComponent) {
        LOGE("[abilityComponent] Update Get component failed");
        return;
    }
    component_ = abilityComponent;

    Size size = Size(abilityComponent->GetWidth(), abilityComponent->GetHeight());
    if (currentRect_.GetSize() == size) {
        return;
    }
    currentRect_.SetSize(size);
    needLayout_ = true;
}

void RenderAbilityComponent::PerformLayout()
{
    Offset offset = GetGlobalOffset();
    if (currentRect_.GetSize().IsEmpty()) {
        currentRect_.SetSize(GetLayoutParam().GetMaxSize());
    }
    if (currentRect_.GetOffset() == offset && !needLayout_ && hasConnectionToAbility_) {
        return;
    }
    currentRect_.SetOffset(offset);
    SetLayoutSize(currentRect_.GetSize());
    if (hasConnectionToAbility_) {
        adapter_->UpdateRect(currentRect_);
        return;
    }
    adapter_ = WindowExtensionConnectionProxy::CreateAdapter();
    adapter_->ConnectExtension(component_->GetWant(), currentRect_, AceType::Claim(this));
}
} // namespace OHOS::Ace::V2
