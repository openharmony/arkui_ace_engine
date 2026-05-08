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

#include "core/components/container_modal/container_modal_constants.h"

namespace OHOS::Ace::V2 {

RenderAbilityComponent::~RenderAbilityComponent()
{
    if (adapter_) {
        adapter_->RemoveExtension();
    }

    auto context = context_.Upgrade();
    if (!context || callbackId_ <= 0) {
        return;
    }
    context->UnregisterSurfacePositionChangedCallback(callbackId_);
}

void RenderAbilityComponent::Update(const RefPtr<Component>& component)
{
    RefPtr<V2::AbilityComponent> abilityComponent = AceType::DynamicCast<V2::AbilityComponent>(component);
    if (!abilityComponent) {
        LOGE("[abilityComponent] Update Get component failed");
        return;
    }

    auto context = context_.Upgrade();
    if (context && callbackId_ <= 0) {
        callbackId_ =
            context->RegisterSurfacePositionChangedCallback([weak = WeakClaim(this)](int32_t posX, int32_t posY) {
                auto client = weak.Upgrade();
                if (client) {
                    client->ConnectOrUpdateExtension();
                }
            });
    }

    component_ = abilityComponent;
    auto width = abilityComponent->GetWidth();
    auto height = abilityComponent->GetHeight();
    if (width == width_ && height == height_) {
        LOGI("size not change.");
        return;
    }
    width_ = width;
    height_ = height;
    needLayout_ = true;
}

void RenderAbilityComponent::PerformLayout()
{
    Size size = Size(NormalizePercentToPx(width_, false), NormalizePercentToPx(height_, true));
    currentRect_.SetSize(size);
    if (currentRect_.GetSize().IsEmpty()) {
        currentRect_.SetSize(GetLayoutParam().GetMaxSize());
    }

    SetLayoutSize(currentRect_.GetSize());
}

void RenderAbilityComponent::Paint(RenderContext& context, const Offset& offset)
{
    ConnectOrUpdateExtension();
}

void RenderAbilityComponent::ConnectOrUpdateExtension()
{
    Offset globalOffset = GetGlobalOffsetExternal();
    if (currentRect_.GetOffset() == globalOffset && !needLayout_ && hasConnectionToAbility_) {
        return;
    }

    auto pipelineContext = context_.Upgrade();
    if (!pipelineContext) {
        return;
    }

    auto parentWindowOffset = pipelineContext->GetCurrentWindowRect().GetOffset();
    Offset containerModalOffset;
    auto isContainerModal = pipelineContext->GetWindowModal() == WindowModal::CONTAINER_MODAL &&
        pipelineContext->GetWindowManager()->GetWindowMode() == WindowMode::WINDOW_MODE_FLOATING;
    if (isContainerModal) {
        containerModalOffset = Offset((NormalizeToPx(CONTAINER_BORDER_WIDTH) + NormalizeToPx(CONTENT_PADDING)),
            NormalizeToPx(CONTAINER_TITLE_HEIGHT));
    }
    currentRect_.SetOffset(globalOffset + parentWindowOffset + containerModalOffset);

    if (!adapter_) {
        adapter_ = WindowExtensionConnectionProxy::CreateAdapter();
        auto windowId = pipelineContext->GetWindowId();
        adapter_->ConnectExtension(component_->GetWant(), currentRect_, AceType::Claim(this), windowId);
        return;
    }

    if (hasConnectionToAbility_) {
        adapter_->UpdateRect(currentRect_);
    }
}

void RenderAbilityComponent::OnPaintFinish()
{
    if (globalOffsetExternal_ != GetGlobalOffsetExternal()) {
        globalOffsetExternal_ = GetGlobalOffsetExternal();
        ConnectOrUpdateExtension();
    }
}

} // namespace OHOS::Ace::V2
