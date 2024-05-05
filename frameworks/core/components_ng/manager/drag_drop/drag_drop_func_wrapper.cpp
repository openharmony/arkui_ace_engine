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

#include "core/components/theme/shadow_theme.h"
#include "core/components_ng/manager/drag_drop/drag_drop_func_wrapper.h"
#include "core/components_ng/pattern/image/image_pattern.h"

namespace OHOS::Ace::NG {

constexpr float DEFAULT_OPACITY = 0.95f;

void DragDropFuncWrapper::SetDraggingPointerAndPressedState(int32_t currentPointerId, int32_t containerId)
{
    auto pipelineContext = PipelineContext::GetContextByContainerId(containerId);
    CHECK_NULL_VOID(pipelineContext);
    auto manager = pipelineContext->GetDragDropManager();
    CHECK_NULL_VOID(manager);
    manager->SetDraggingPointer(currentPointerId);
    manager->SetDraggingPressedState(true);
}

void DragDropFuncWrapper::DecideWhetherToStopDragging(
    const PointerEvent& pointerEvent, const std::string& extraParams, int32_t currentPointerId, int32_t containerId)
{
    auto pipelineContext = PipelineContext::GetContextByContainerId(containerId);
    CHECK_NULL_VOID(pipelineContext);
    auto manager = pipelineContext->GetDragDropManager();
    CHECK_NULL_VOID(manager);
    if (!manager->IsDraggingPressed(currentPointerId)) {
        manager->OnDragEnd(pointerEvent, extraParams);
    }
}

void DragDropFuncWrapper::UpdateDragPreviewOptionsFromModifier(
    std::function<void(WeakPtr<FrameNode>)> applyOnNodeSync, DragPreviewOption& option)
{
    // create one temporary frame node for receiving the value from the modifier
    auto imageNode = FrameNode::GetOrCreateFrameNode(V2::IMAGE_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(),
        []() { return AceType::MakeRefPtr<ImagePattern>(); });
    CHECK_NULL_VOID(imageNode);

    // execute the modifier
    CHECK_NULL_VOID(applyOnNodeSync);
    applyOnNodeSync(AceType::WeakClaim(AceType::RawPtr(imageNode)));

    // get values from the temporary frame node
    auto imageContext = imageNode->GetRenderContext();
    CHECK_NULL_VOID(imageContext);
    auto opacity = imageContext->GetOpacity();
    if (opacity.has_value()) {
        option.options.opacity = opacity.value();
    } else {
        option.options.opacity = DEFAULT_OPACITY;
    }

    auto shadow = imageContext->GetBackShadow();
    if (shadow.has_value()) {
        option.options.shadow = shadow.value();
    }
}

void DragDropFuncWrapper::UpdatePreviewOptionDefaultAttr(DragPreviewOption& option)
{
    option.options.opacity = DEFAULT_OPACITY;
    if (option.isDefaultShadowEnabled) {
        option.options.shadow = GetDefaultShadow();
    } else {
        option.options.shadow = std::nullopt;
    }
}

void DragDropFuncWrapper::UpdateExtraInfo(std::unique_ptr<JsonValue>& arkExtraInfoJson,
    DragPreviewOption& option)
{
    CHECK_NULL_VOID(arkExtraInfoJson);
    double opacity = option.options.opacity;
    arkExtraInfoJson->Put("dip_opacity", opacity);
    PrepareShadowParametersForDragData(arkExtraInfoJson, option);
}

void DragDropFuncWrapper::PrepareShadowParametersForDragData(std::unique_ptr<JsonValue>& arkExtraInfoJson,
    DragPreviewOption& option)
{
    CHECK_NULL_VOID(arkExtraInfoJson);
    auto shadow = option.options.shadow;
    if (!shadow.has_value() || !shadow->IsValid()) {
        arkExtraInfoJson->Put("shadow_enable", false);
        return;
    }
    arkExtraInfoJson->Put("drag_type", "non-text");
    arkExtraInfoJson->Put("shadow_enable", true);
    ParseShadowInfo(shadow.value(), arkExtraInfoJson);
}

void DragDropFuncWrapper::ParseShadowInfo(Shadow& shadow, std::unique_ptr<JsonValue>& arkExtraInfoJson)
{
    CHECK_NULL_VOID(arkExtraInfoJson);
    arkExtraInfoJson->Put("shadow_is_filled", shadow.GetIsFilled());
    arkExtraInfoJson->Put("drag_shadow_OffsetX", shadow.GetOffset().GetX());
    arkExtraInfoJson->Put("drag_shadow_OffsetY", shadow.GetOffset().GetY());
    arkExtraInfoJson->Put("shadow_mask", shadow.GetShadowType() == ShadowType::BLUR);
    int32_t argb = static_cast<int32_t>(shadow.GetColor().GetValue());
    arkExtraInfoJson->Put("drag_shadow_argb", argb);
    int32_t strategy = static_cast<int32_t>(shadow.GetShadowColorStrategy());
    arkExtraInfoJson->Put("shadow_color_strategy", strategy);
    arkExtraInfoJson->Put("shadow_corner", shadow.GetBlurRadius());
    arkExtraInfoJson->Put("shadow_elevation", shadow.GetElevation());
    arkExtraInfoJson->Put("shadow_is_hardwareacceleration", shadow.GetHardwareAcceleration());
}

std::optional<Shadow> DragDropFuncWrapper::GetDefaultShadow()
{
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, std::nullopt);
    auto shadowTheme = pipelineContext->GetTheme<ShadowTheme>();
    CHECK_NULL_RETURN(shadowTheme, std::nullopt);
    auto colorMode = SystemProperties::GetColorMode();
    auto shadow = shadowTheme->GetShadow(ShadowStyle::OuterFloatingSM, colorMode);
    shadow.SetIsFilled(true);
    return shadow;
}

} // namespace OHOS::Ace
