/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/common/visual_effect/component_material_interaction.h"

#include "ui/base/geometry/dimension.h"
#include "ui/base/utils/utils.h"

#include "core/components/common/properties/ui_material.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/render/render_context.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

namespace {
constexpr float COMPONENT_SCOPE_INNER_THRESHOLD = 1.0f;
constexpr float COMPONENT_SCOPE_OUTER_THRESHOLD = 3.0f;
constexpr Dimension COMPONENT_MEDIUM_SIZE_THRESHOLD = 160.0_vp;
constexpr Dimension COMPONENT_LARGE_SIZE_THRESHOLD = 640.0_vp;

constexpr float TOUCH_DOWN_0_0_SCALE = 0.99f;
constexpr float TOUCH_MOVE_INNER_SCALE_HORIZONTAL_X = 0.03f;
constexpr float TOUCH_MOVE_INNER_SCALE_HORIZONTAL_Y = -0.01f;
constexpr float TOUCH_MOVE_INNER_SCALE_VERTICAL_X = -0.01f;
constexpr float TOUCH_MOVE_INNER_SCALE_VERTICAL_Y = 0.04f;

constexpr float TOUCH_MOVE_OUTER_SCALE_HORIZONTAL_X = 0.005f;
constexpr float TOUCH_MOVE_OUTER_SCALE_HORIZONTAL_Y = -0.005f;
constexpr float TOUCH_MOVE_OUTER_SCALE_VERTICAL_X = -0.005f;
constexpr float TOUCH_MOVE_OUTER_SCALE_VERTICAL_Y = 0.005f;

constexpr float TOUCH_MOVE_INNER_SCALE_LARGE_HORIZONTAL_X = 0.02f;
constexpr float TOUCH_MOVE_INNER_SCALE_LARGE_HORIZONTAL_Y = -0.00f;
constexpr float TOUCH_MOVE_INNER_SCALE_LARGE_VERTICAL_X = -0.00f;
constexpr float TOUCH_MOVE_INNER_SCALE_LARGE_VERTICAL_Y = 0.03f;

constexpr int32_t TOUCH_FINGER_COUNT = 1;
constexpr int32_t TOUCH_CURVE_DURATION = 1000;
constexpr float LIGHT_EFFECT_POSITION_Z = 80.0f;
constexpr float LIGHT_EFFECT_INTENSITY = 3.0f;
constexpr uint32_t LIGHT_ILLUMINATED = 3; // ILLUMINATED_TYPE_BORDER_CONTENT
constexpr Dimension ILLUMINATED_BORDER_WIDTH = 0.5_vp;

// Limit value within [min, max]
float Clamp(float value, float min, float max)
{
    return std::max(min, std::min(value, max));
}

// Normalization of central coordinates
Offset NormalizeToCenter(float x, float y, float width, float height)
{
    if (NearZero(width) || NearZero(height)) {
        return Offset(1.0f, 1.0f);
    }
    const float outerThreshold = COMPONENT_SCOPE_OUTER_THRESHOLD;

    const float normalizedX = Clamp((x - 0.5f * width) / (0.5f * width), -outerThreshold, outerThreshold);
    const float normalizedY = Clamp((y - 0.5f * height) / (0.5f * height), -outerThreshold, outerThreshold);
    return Offset(normalizedX, normalizedY);
}

float CalcNodeScale(const SizeF& nodeSize)
{
    return Clamp((std::max(nodeSize.Width(), nodeSize.Height()) - COMPONENT_MEDIUM_SIZE_THRESHOLD.ConvertToPx()) /
                     (COMPONENT_LARGE_SIZE_THRESHOLD.ConvertToPx() - COMPONENT_MEDIUM_SIZE_THRESHOLD.ConvertToPx()),
        0.0f, 1.0f);
}

float CalcMediumToLargeScale(float nodeScale, float smallScale, float largeScale)
{
    return smallScale + nodeScale * (largeScale - smallScale);
}

bool IsLargeComponentSize(const SizeF& nodeSize)
{
    return std::max(nodeSize.Width(), nodeSize.Height()) > COMPONENT_MEDIUM_SIZE_THRESHOLD.ConvertToPx();
}

Offset ConvertToScaleCoeff(float normalizedX, float normalizedY)
{
    const float innerThreshold = COMPONENT_SCOPE_INNER_THRESHOLD;
    const float baseScale = TOUCH_DOWN_0_0_SCALE;
    // Inner scale
    float innerUnitScaleHorizontalX = baseScale + Clamp(std::fabs(normalizedX), -innerThreshold, innerThreshold) *
                                                      TOUCH_MOVE_INNER_SCALE_HORIZONTAL_X;
    float innerUnitScaleHorizontalY = baseScale + Clamp(std::fabs(normalizedX), -innerThreshold, innerThreshold) *
                                                      TOUCH_MOVE_INNER_SCALE_HORIZONTAL_Y;

    float innerUnitScaleVerticalX =
        baseScale + Clamp(std::fabs(normalizedY), -innerThreshold, innerThreshold) * TOUCH_MOVE_INNER_SCALE_VERTICAL_X;
    float innerUnitScaleVerticalY =
        baseScale + Clamp(std::fabs(normalizedY), -innerThreshold, innerThreshold) * TOUCH_MOVE_INNER_SCALE_VERTICAL_Y;

    // Outer scale
    float outerUnitScaleHorizontalX = innerUnitScaleHorizontalX;
    float outerUnitScaleHorizontalY = innerUnitScaleHorizontalY;

    float outerUnitScaleVerticalX = innerUnitScaleVerticalX;
    float outerUnitScaleVerticalY = innerUnitScaleVerticalY;
    if (std::fabs(normalizedX) > innerThreshold) { // HORIZONTAL
        outerUnitScaleHorizontalX += (std::fabs(normalizedX) - innerThreshold) * TOUCH_MOVE_OUTER_SCALE_HORIZONTAL_X;
        outerUnitScaleHorizontalY += (std::fabs(normalizedX) - innerThreshold) * TOUCH_MOVE_OUTER_SCALE_HORIZONTAL_Y;
    }
    if (std::fabs(normalizedY) > innerThreshold) { // VERTICAL
        outerUnitScaleVerticalX += (std::fabs(normalizedY) - innerThreshold) * TOUCH_MOVE_OUTER_SCALE_VERTICAL_X;
        outerUnitScaleVerticalY += (std::fabs(normalizedY) - innerThreshold) * TOUCH_MOVE_OUTER_SCALE_VERTICAL_Y;
    }
    auto scaleX = std::max(
        { innerUnitScaleHorizontalX, innerUnitScaleVerticalX, outerUnitScaleHorizontalX, outerUnitScaleVerticalX });
    auto scaleY = std::max(
        { innerUnitScaleHorizontalY, innerUnitScaleVerticalY, outerUnitScaleHorizontalY, outerUnitScaleVerticalY });
    return Offset(scaleX, scaleY);
}

Offset ConvertToScaleCoeffLarge(float normalizedX, float normalizedY, float nodeScale)
{
    const float innerThreshold = COMPONENT_SCOPE_INNER_THRESHOLD;
    const float baseScale = TOUCH_DOWN_0_0_SCALE;

    // Inner scale
    float innerUnitScaleHorizontalX =
        baseScale + Clamp(std::fabs(normalizedX), -innerThreshold, innerThreshold) *
                        CalcMediumToLargeScale(
                            nodeScale, TOUCH_MOVE_INNER_SCALE_HORIZONTAL_X, TOUCH_MOVE_INNER_SCALE_LARGE_HORIZONTAL_X);
    float innerUnitScaleHorizontalY =
        baseScale + Clamp(std::fabs(normalizedX), -innerThreshold, innerThreshold) *
                        CalcMediumToLargeScale(
                            nodeScale, TOUCH_MOVE_INNER_SCALE_HORIZONTAL_Y, TOUCH_MOVE_INNER_SCALE_LARGE_HORIZONTAL_Y);

    float innerUnitScaleVerticalX = baseScale + Clamp(std::fabs(normalizedY), -innerThreshold, innerThreshold) *
                                                    CalcMediumToLargeScale(nodeScale, TOUCH_MOVE_INNER_SCALE_VERTICAL_X,
                                                        TOUCH_MOVE_INNER_SCALE_LARGE_VERTICAL_X);
    float innerUnitScaleVerticalY = baseScale + Clamp(std::fabs(normalizedY), -innerThreshold, innerThreshold) *
                                                    CalcMediumToLargeScale(nodeScale, TOUCH_MOVE_INNER_SCALE_VERTICAL_Y,
                                                        TOUCH_MOVE_INNER_SCALE_LARGE_VERTICAL_Y);

    // Outer scale
    float outerUnitScaleHorizontalX = innerUnitScaleHorizontalX;
    float outerUnitScaleHorizontalY = innerUnitScaleHorizontalY;

    float outerUnitScaleVerticalX = innerUnitScaleVerticalX;
    float outerUnitScaleVerticalY = innerUnitScaleVerticalY;
    if (std::fabs(normalizedX) > innerThreshold) { // HORIZONTAL
        outerUnitScaleHorizontalX += (std::fabs(normalizedX) - innerThreshold) * TOUCH_MOVE_OUTER_SCALE_HORIZONTAL_X;
        outerUnitScaleHorizontalY += (std::fabs(normalizedX) - innerThreshold) * TOUCH_MOVE_OUTER_SCALE_HORIZONTAL_Y;
    }
    if (std::fabs(normalizedY) > innerThreshold) { // VERTICAL
        outerUnitScaleVerticalX += (std::fabs(normalizedY) - innerThreshold) * TOUCH_MOVE_OUTER_SCALE_VERTICAL_X;
        outerUnitScaleVerticalY += (std::fabs(normalizedY) - innerThreshold) * TOUCH_MOVE_OUTER_SCALE_VERTICAL_Y;
    }
    auto scaleX = std::max(
        { innerUnitScaleHorizontalX, innerUnitScaleVerticalX, outerUnitScaleHorizontalX, outerUnitScaleVerticalX });
    auto scaleY = std::max(
        { innerUnitScaleHorizontalY, innerUnitScaleVerticalY, outerUnitScaleHorizontalY, outerUnitScaleVerticalY });
    return Offset(scaleX, scaleY);
}

Offset ConvertToOffset(
    float normalizedX, float normalizedY, Dimension innerOffsetAdditon, Dimension outerOffsetAddition)
{
    const float innerThreshold = COMPONENT_SCOPE_INNER_THRESHOLD;
    // Inner offset
    Dimension innerUnitOffset_X = innerOffsetAdditon * Clamp(normalizedX, -1, 1);
    Dimension innerUnitOffset_Y = innerOffsetAdditon * Clamp(normalizedY, -1, 1);
    // Outer offset
    Dimension outerUnitOffset_X = innerUnitOffset_X;
    Dimension outerUnitOffset_Y = innerUnitOffset_Y;

    if (std::fabs(normalizedX) > innerThreshold) { // HORIZONTAL
        outerUnitOffset_X +=
            outerOffsetAddition * (std::fabs(normalizedX) - innerThreshold) * (normalizedX / std::fabs(normalizedX));
    }
    if (std::fabs(normalizedY) > innerThreshold) { // VERTICAL
        outerUnitOffset_Y +=
            outerOffsetAddition * (std::fabs(normalizedY) - innerThreshold) * (normalizedY / std::fabs(normalizedY));
    }
    return Offset(outerUnitOffset_X.ConvertToPx(), outerUnitOffset_Y.ConvertToPx());
}
} // namespace

void ControlInteractionBase::InitInteractionOffset(RefPtr<FrameNode> targetNode, ControlInteractionInfo& info)
{
    CHECK_NULL_VOID(targetNode);
    auto geometryNode = targetNode->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    info.curFrameSize = geometryNode->GetFrameSize();

    info.innerMoveOffset = Dimension(2.3f, DimensionUnit::VP);
    info.outerMoveOffset = Dimension(0.575f, DimensionUnit::VP);
}

void ControlInteractionBase::HandleTouchEvent(RefPtr<FrameNode> targetNode, const TouchEventInfo& info)
{
    CHECK_NULL_VOID(targetNode);

    if (info.GetTouches().empty() || info.GetTouches().size() > TOUCH_FINGER_COUNT) {
        HandleTouchCancel(targetNode);
        return;
    }
    auto touchType = info.GetTouches().front().GetTouchType();
    auto clickPos = info.GetTouches().front().GetLocalLocation();
    ControlInteractionInfo interactionInfo;
    InitInteractionOffset(targetNode, interactionInfo);
    if (touchType == TouchType::DOWN) {
        HandleTouchDown(targetNode, clickPos, interactionInfo);
    } else if (touchType == TouchType::MOVE) {
        HandleTouchMove(targetNode, clickPos, interactionInfo);
    } else if (touchType == TouchType::UP || touchType == TouchType::CANCEL) {
        HandleTouchCancel(targetNode);
    }
}

void ControlInteractionBase::HandleTouchCancel(RefPtr<FrameNode> targetNode)
{
    CHECK_NULL_VOID(targetNode);
    auto renderContext = targetNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    if (IsLightEffectEnabled(targetNode)) {
        ResetLightPositionAndColor(targetNode);
    }
    if (!IsInteractiveEnabled(targetNode)) {
        return;
    }
    AnimationOption option;
    const RefPtr<InterpolatingSpring> curve = AceType::MakeRefPtr<InterpolatingSpring>(0, 1, 228, 16);
    option.SetCurve(curve);
    option.SetDuration(TOUCH_CURVE_DURATION);
    AnimationUtils::Animate(
        option,
        [weak = AceType::WeakClaim(AceType::RawPtr(targetNode))]() {
            auto targetNode = weak.Upgrade();
            CHECK_NULL_VOID(targetNode);
            auto renderContext = targetNode->GetRenderContext();
            CHECK_NULL_VOID(renderContext);
            // Reset offset and scale
            double offsetX = 0.0;
            double offsetY = 0.0;
            double scaleX = 1.0;
            double scaleY = 1.0;
            renderContext->UpdateMaterialInteractionEffect(scaleX, scaleY, offsetX, offsetY);
        },
        nullptr, nullptr, targetNode->GetContextRefPtr());
}

void ControlInteractionBase::HandleTouchDown(
    RefPtr<FrameNode> targetNode, const Offset& clickPosition, const ControlInteractionInfo& info)
{
    if (IsLightEffectEnabled(targetNode)) {
        UpdateLightPositionAndColor(targetNode, clickPosition.GetX(), clickPosition.GetY());
    }
    if (!IsInteractiveEnabled(targetNode)) {
        return;
    }
    CHECK_NULL_VOID(info.curFrameSize);

    Offset normalizedXY = NormalizeToCenter(
        clickPosition.GetX(), clickPosition.GetY(), info.curFrameSize->Width(), info.curFrameSize->Height());
    Offset scaleXY;
    if (IsLargeComponentSize(info.curFrameSize.value())) {
        scaleXY = ConvertToScaleCoeffLarge(
            normalizedXY.GetX(), normalizedXY.GetY(), CalcNodeScale(info.curFrameSize.value()));
    } else {
        scaleXY = ConvertToScaleCoeff(normalizedXY.GetX(), normalizedXY.GetY());
    }
    Offset offsetXY =
        ConvertToOffset(normalizedXY.GetX(), normalizedXY.GetY(), info.innerMoveOffset, info.outerMoveOffset);
    float offsetX = offsetXY.GetX();
    float offsetY = offsetXY.GetY();
    float scaleX = scaleXY.GetX();
    float scaleY = scaleXY.GetY();

    AnimationOption option;
    const RefPtr<InterpolatingSpring> curve = AceType::MakeRefPtr<InterpolatingSpring>(0, 1, 228, 16);
    option.SetCurve(curve);
    option.SetDuration(TOUCH_CURVE_DURATION);
    AnimationUtils::Animate(
        option,
        [weak = AceType::WeakClaim(AceType::RawPtr(targetNode)), offsetX = offsetX, offsetY = offsetY, scaleX = scaleX,
            scaleY = scaleY]() {
            auto targetNode = weak.Upgrade();
            CHECK_NULL_VOID(targetNode);
            auto renderContext = targetNode->GetRenderContext();
            CHECK_NULL_VOID(renderContext);
            renderContext->UpdateMaterialInteractionEffect(scaleX, scaleY, offsetX, offsetY);
        },
        nullptr, nullptr, targetNode->GetContextRefPtr());
}

void ControlInteractionBase::HandleTouchMove(
    RefPtr<FrameNode> targetNode, const Offset& clickPosition, const ControlInteractionInfo& info)
{
    if (IsLightEffectEnabled(targetNode)) {
        UpdateLightPositionAndColor(targetNode, clickPosition.GetX(), clickPosition.GetY());
    }
    if (!IsInteractiveEnabled(targetNode)) {
        return;
    }
    CHECK_NULL_VOID(info.curFrameSize);

    Offset normalizedXY = NormalizeToCenter(
        clickPosition.GetX(), clickPosition.GetY(), info.curFrameSize->Width(), info.curFrameSize->Height());
    Offset scaleXY;
    if (IsLargeComponentSize(info.curFrameSize.value())) {
        scaleXY = ConvertToScaleCoeffLarge(
            normalizedXY.GetX(), normalizedXY.GetY(), CalcNodeScale(info.curFrameSize.value()));
    } else {
        scaleXY = ConvertToScaleCoeff(normalizedXY.GetX(), normalizedXY.GetY());
    }
    Offset offsetXY =
        ConvertToOffset(normalizedXY.GetX(), normalizedXY.GetY(), info.innerMoveOffset, info.outerMoveOffset);
    float offsetX = offsetXY.GetX();
    float offsetY = offsetXY.GetY();
    float scaleX = scaleXY.GetX();
    float scaleY = scaleXY.GetY();

    CHECK_NULL_VOID(targetNode);
    auto renderContext = targetNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateMaterialInteractionEffect(scaleX, scaleY, offsetX, offsetY);
}

void ControlInteractionBase::RegisterMaterialInteractionEvent(
    RefPtr<FrameNode> targetNode, const std::shared_ptr<ImmersiveOptions>& options)
{
    CHECK_NULL_VOID(targetNode);

    auto touchTask = [weak = AceType::WeakClaim(AceType::RawPtr(targetNode))](const TouchEventInfo& info) {
        auto targetNode = weak.Upgrade();
        CHECK_NULL_VOID(targetNode);
        ControlInteractionBase::HandleTouchEvent(targetNode, info);
    };
    auto gestureHub = targetNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    auto touchEvent = AceType::MakeRefPtr<TouchEventImpl>(std::move(touchTask));
    gestureHub->AddMaterialInteractionEvent(touchEvent);
    if (options && options->lightEffectOptions) {
        InitLightEffect(targetNode);
    }
}

std::optional<LightEffectOptions> ControlInteractionBase::GetLightEffectOptions(RefPtr<FrameNode>& targetNode)
{
    CHECK_NULL_RETURN(targetNode, std::nullopt);
    auto renderContext = targetNode->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, std::nullopt);
    auto config = renderContext->GetImmersiveMaterialConfig();
    if (config.has_value() && config->lightEffectOptions) {
        return config->lightEffectOptions;
    }
    return std::nullopt;
}

bool ControlInteractionBase::IsInteractiveEnabled(RefPtr<FrameNode>& targetNode)
{
    CHECK_NULL_RETURN(targetNode, false);
    auto renderContext = targetNode->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, false);
    auto config = renderContext->GetImmersiveMaterialConfig();
    return config.has_value() && config->interactive;
}

bool ControlInteractionBase::IsLightEffectEnabled(RefPtr<FrameNode>& targetNode)
{
    return GetLightEffectOptions(targetNode).has_value();
}

void ControlInteractionBase::InitLightEffect(RefPtr<FrameNode>& targetNode)
{
    CHECK_NULL_VOID(targetNode);
    auto renderContext = targetNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateLightIlluminated(LIGHT_ILLUMINATED);
    renderContext->UpdateIlluminatedBorderWidth(ILLUMINATED_BORDER_WIDTH);
}

void ControlInteractionBase::UninitLightEffect(FrameNode* targetNode)
{
    CHECK_NULL_VOID(targetNode);
    auto renderContext = targetNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto config = renderContext->GetImmersiveMaterialConfig();
    if (!config.has_value() || !config->lightEffectOptions) {
        return;
    }
    if (renderContext->GetLightColor().has_value()) {
        renderContext->ResetLightColor();
    }
    if (renderContext->GetLightIlluminated().has_value()) {
        renderContext->ResetLightIlluminated();
    }
    if (renderContext->GetLightIntensity().has_value()) {
        renderContext->ResetLightIntensity();
    }
    if (renderContext->GetLightPosition().has_value()) {
        renderContext->ResetLightPosition();
    }
}

void ControlInteractionBase::UpdateLightPositionAndColor(RefPtr<FrameNode>& targetNode, float x, float y)
{
    auto lightEffectOptions = GetLightEffectOptions(targetNode);
    CHECK_NULL_VOID(lightEffectOptions);
    auto renderContext = targetNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateLightIntensity(LIGHT_EFFECT_INTENSITY);
    renderContext->UpdateLightPosition(TranslateOptions(Dimension(Dimension(x).ConvertToVp(), DimensionUnit::VP),
        Dimension(Dimension(y).ConvertToVp(), DimensionUnit::VP),
        Dimension(LIGHT_EFFECT_POSITION_Z, DimensionUnit::VP)));
    renderContext->UpdateLightColor(lightEffectOptions->color);
}

void ControlInteractionBase::ResetLightPositionAndColor(RefPtr<FrameNode>& targetNode)
{
    CHECK_NULL_VOID(targetNode);
    auto lightEffectOptions = GetLightEffectOptions(targetNode);
    CHECK_NULL_VOID(lightEffectOptions);
    auto renderContext = targetNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    if (renderContext->GetLightColor().has_value()) {
        renderContext->ResetLightColor();
    }
    if (renderContext->GetLightPosition().has_value()) {
        renderContext->ResetLightPosition();
    }
    renderContext->UpdateLightIntensity(0.0f);
}
} // namespace OHOS::Ace::NG