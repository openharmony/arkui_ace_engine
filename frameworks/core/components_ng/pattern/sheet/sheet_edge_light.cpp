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

#include "core/components_ng/pattern/sheet/sheet_edge_light.h"

#include "ui/animation/curves.h"

#include "core/components_ng/pattern/overlay/sheet_presentation_pattern.h"
#include "core/components_ng/pattern/overlay/sheet_style.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t UI_MATERIAL_LEVEL_LOW = 2;

constexpr float NUM_NOT_ZERO = 1.0f;
constexpr int EDGE_LIGHT_SHOW_ANIMATE_DURATION = 166;
#ifndef PREVIEW
constexpr float NUM_ZERO = 0.0f;
constexpr float SPREAD_FACTOR = 64.0f;
constexpr float BLOOM_INTENSITY_CUTOFF = 0.1f;
constexpr float LIGHT_MAX_INTENSITY = 1.0f;
constexpr float MAX_BLOOM_INTENSITY = 1.0f;
constexpr float BLOOM_FALLOFF_POW = 1.0f;
constexpr float MIN_BORDER_WIDTH = 0.8f;
constexpr float MAX_BORDER_WIDTH = 1.0f;
constexpr float INNER_BORDER_BLOOM_WIDTH = 30.0f;
constexpr float OUTER_BORDER_BLOOM_WIDTH = 20.0f;
constexpr float EDGE_LIGHT_COLOR = 255.0f;
constexpr float EDGE_LIGHT_RADIUS_X = 1.2f;
constexpr float EDGE_LIGHT_CENTER_X = 0.5f;
constexpr float EDGE_LIGHT_CENTER_Y = 0.05f;
#endif
} // namespace

AnimationOption SheetEdgeLightBase::GetSheetEdgeLightAnimateOption()
{
    AnimationOption option;
    const RefPtr<InterpolatingSpring> curve = AceType::MakeRefPtr<InterpolatingSpring>(0, 1, 224, 30);
    option.SetCurve(curve);
    option.SetDuration(NUM_NOT_ZERO);
    return option;
}

AnimationOption SheetEdgeLightBase::GetSheetEdgeLightAnimatePreShowOption()
{
    AnimationOption option;
    const RefPtr<CubicCurve> curve = AceType::MakeRefPtr<CubicCurve>(1.0f, 1.0f, 0.0f, 0.0f);
    option.SetCurve(curve);
    option.SetDuration(EDGE_LIGHT_SHOW_ANIMATE_DURATION);
    return option;
}

std::function<void()> SheetEdgeLightBase::GetSheetEdgeLightAnimateEvent(RefPtr<FrameNode>& sheetNode)
{
    return [sheetWK = AceType::WeakClaim(AceType::RawPtr(sheetNode))]() {
        auto sheetNode = sheetWK.Upgrade();
        CHECK_NULL_VOID(sheetNode);
        auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
        CHECK_NULL_VOID(sheetPattern);
        SheetEdgeLightBase::SetSheetEdgeLightTransitionStart(sheetNode);
    };
}

std::function<void()> SheetEdgeLightBase::GetSheetEdgeLightAnimateFinishEvent(RefPtr<FrameNode>& sheetNode)
{
    const std::function<void()> edgeLightMoveEvent = [sheetWK = AceType::WeakClaim(AceType::RawPtr(sheetNode))]() {
        auto sheetNode = sheetWK.Upgrade();
        CHECK_NULL_VOID(sheetNode);
        auto sheetPattern = sheetNode->GetPattern<SheetPresentationPattern>();
        CHECK_NULL_VOID(sheetPattern);
        SheetEdgeLightBase::SetSheetEdgeLightTransitionEnd(sheetNode);
    };
    const std::function<void()> edgeLightFinishEvent = [sheetWK = AceType::WeakClaim(AceType::RawPtr(sheetNode))]() {
        auto sheetNode = sheetWK.Upgrade();
        CHECK_NULL_VOID(sheetNode);
        auto renderContext = sheetNode->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        renderContext->SetForegroundShader(nullptr);
    };
    return [edgeLightEvent = edgeLightMoveEvent, finishEvent = edgeLightFinishEvent,
               sheetWK = AceType::WeakClaim(AceType::RawPtr(sheetNode))]() {
        auto sheetNode = sheetWK.Upgrade();
        CHECK_NULL_VOID(sheetNode);
        auto option = SheetEdgeLightBase::GetSheetEdgeLightAnimateOption();
        auto pipeline = sheetNode->GetContextRefPtr();
        CHECK_NULL_VOID(pipeline);
        AnimationUtils::Animate(option, edgeLightEvent, finishEvent, nullptr, pipeline);
    };
}

bool SheetEdgeLightBase::CheckIfNeedShowEdgeLight(EdgeLightMode mode, SheetType sheetType)
{
    if (sheetType != SHEET_BOTTOM) {
        return false;
    }
    int32_t currentLevel = static_cast<int32_t>(SystemProperties::GetUiMaterialLevel());
    if (mode == EdgeLightMode::EDGELIGHT_DISABLED) {
        return false;
    }
    if (mode == EdgeLightMode::EDGELIGHT_ENABLED) {
        return true;
    }
    if (mode == EdgeLightMode::EDGELIGHT_AUTO && currentLevel != UI_MATERIAL_LEVEL_LOW) {
        return true;
    }
    return false;
}

void SheetEdgeLightBase::SetSheetEdgeLightTransitionPreShow(RefPtr<FrameNode>& sheetNode)
{
#ifndef PREVIEW
    CHECK_NULL_VOID(sheetNode);
    auto geometryNode = sheetNode->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto renderContext = sheetNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);

    auto sheetSize = geometryNode->GetFrameSize();

    auto edgeLightFilter = std::make_shared<Rosen::RSNGSDFEdgeLightEffect>();

    edgeLightFilter->Setter<Rosen::SDFEdgeLightEffectSpreadFactorTag>(SPREAD_FACTOR);
    edgeLightFilter->Setter<Rosen::SDFEdgeLightEffectBloomIntensityCutoffTag>(BLOOM_INTENSITY_CUTOFF);
    edgeLightFilter->Setter<Rosen::SDFEdgeLightEffectLightMaxIntensityTag>(NUM_ZERO);
    edgeLightFilter->Setter<Rosen::SDFEdgeLightEffectMaxBloomIntensityTag>(NUM_ZERO);
    edgeLightFilter->Setter<Rosen::SDFEdgeLightEffectBloomFalloffPowTag>(NUM_ZERO);
    edgeLightFilter->Setter<Rosen::SDFEdgeLightEffectMinBorderWidthTag>(NUM_ZERO);
    edgeLightFilter->Setter<Rosen::SDFEdgeLightEffectMaxBorderWidthTag>(NUM_ZERO);
    edgeLightFilter->Setter<Rosen::SDFEdgeLightEffectInnerBorderBloomWidthTag>(NUM_ZERO);
    edgeLightFilter->Setter<Rosen::SDFEdgeLightEffectOuterBorderBloomWidthTag>(NUM_ZERO);
    edgeLightFilter->Setter<Rosen::SDFEdgeLightEffectColorTag>(
        Rosen::Vector3f(EDGE_LIGHT_COLOR / 255.0f, EDGE_LIGHT_COLOR / 255.0f, EDGE_LIGHT_COLOR / 255.0f));

    auto radialGradientMask = std::make_shared<Rosen::RSNGRadialGradientMask>();

    Rosen::Vector2f center = { EDGE_LIGHT_CENTER_X, EDGE_LIGHT_CENTER_Y * sheetSize.Width() / sheetSize.Height() };
    std::vector<float> colors = { 0.0f, 0.0f, 1.0f, 0.0f };
    std::vector<float> positions = { 0.0f, 0.3f, 0.6f, 1.0f };
    float radiusX = EDGE_LIGHT_RADIUS_X * sheetSize.Width() / sheetSize.Height();
    float radiusY = EDGE_LIGHT_RADIUS_X * sheetSize.Width() / sheetSize.Height();
    radialGradientMask->Setter<Rosen::RadialGradientMaskCenterTag>(center);
    radialGradientMask->Setter<Rosen::RadialGradientMaskRadiusXTag>(radiusX);
    radialGradientMask->Setter<Rosen::RadialGradientMaskRadiusYTag>(radiusY);
    radialGradientMask->Setter<Rosen::RadialGradientMaskColorsTag>(colors);
    radialGradientMask->Setter<Rosen::RadialGradientMaskPositionsTag>(positions);

    edgeLightFilter->Setter<Rosen::SDFEdgeLightEffectLightMaskTag>(
        std::static_pointer_cast<Rosen::RSNGMaskBase>(radialGradientMask));

    auto edgeLightModifier = std::make_shared<RenderEdgeLightModifier>(edgeLightFilter);
    renderContext->SetForegroundShader(edgeLightModifier);
#endif
}

void SheetEdgeLightBase::SetSheetEdgeLightTransitionStart(RefPtr<FrameNode>& sheetNode)
{
#ifndef PREVIEW
    CHECK_NULL_VOID(sheetNode);
    auto geometryNode = sheetNode->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto renderContext = sheetNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);

    auto sheetSize = geometryNode->GetFrameSize();

    auto edgeLightFilter = std::make_shared<Rosen::RSNGSDFEdgeLightEffect>();

    edgeLightFilter->Setter<Rosen::SDFEdgeLightEffectSpreadFactorTag>(SPREAD_FACTOR);
    edgeLightFilter->Setter<Rosen::SDFEdgeLightEffectBloomIntensityCutoffTag>(BLOOM_INTENSITY_CUTOFF);
    edgeLightFilter->Setter<Rosen::SDFEdgeLightEffectLightMaxIntensityTag>(LIGHT_MAX_INTENSITY);
    edgeLightFilter->Setter<Rosen::SDFEdgeLightEffectMaxBloomIntensityTag>(MAX_BLOOM_INTENSITY);
    edgeLightFilter->Setter<Rosen::SDFEdgeLightEffectBloomFalloffPowTag>(BLOOM_FALLOFF_POW);
    edgeLightFilter->Setter<Rosen::SDFEdgeLightEffectMinBorderWidthTag>(MIN_BORDER_WIDTH);
    edgeLightFilter->Setter<Rosen::SDFEdgeLightEffectMaxBorderWidthTag>(MAX_BORDER_WIDTH);
    edgeLightFilter->Setter<Rosen::SDFEdgeLightEffectInnerBorderBloomWidthTag>(INNER_BORDER_BLOOM_WIDTH);
    edgeLightFilter->Setter<Rosen::SDFEdgeLightEffectOuterBorderBloomWidthTag>(OUTER_BORDER_BLOOM_WIDTH);
    edgeLightFilter->Setter<Rosen::SDFEdgeLightEffectColorTag>(
        Rosen::Vector3f(EDGE_LIGHT_COLOR / 255.0f, EDGE_LIGHT_COLOR / 255.0f, EDGE_LIGHT_COLOR / 255.0f));

    auto radialGradientMask = std::make_shared<Rosen::RSNGRadialGradientMask>();
    Rosen::Vector2f center = { EDGE_LIGHT_CENTER_X, EDGE_LIGHT_CENTER_Y * sheetSize.Width() / sheetSize.Height() };

    std::vector<float> colors = { 0.0f, 0.0f, 1.0f, 0.0f };
    std::vector<float> positions = { 0.0f, 0.3f, 0.6f, 1.0f };
    float radiusX = EDGE_LIGHT_RADIUS_X * sheetSize.Width() / sheetSize.Height();
    float radiusY = EDGE_LIGHT_RADIUS_X * sheetSize.Width() / sheetSize.Height();
    radialGradientMask->Setter<Rosen::RadialGradientMaskCenterTag>(center);
    radialGradientMask->Setter<Rosen::RadialGradientMaskRadiusXTag>(radiusX);
    radialGradientMask->Setter<Rosen::RadialGradientMaskRadiusYTag>(radiusY);
    radialGradientMask->Setter<Rosen::RadialGradientMaskColorsTag>(colors);
    radialGradientMask->Setter<Rosen::RadialGradientMaskPositionsTag>(positions);

    edgeLightFilter->Setter<Rosen::SDFEdgeLightEffectLightMaskTag>(
        std::static_pointer_cast<Rosen::RSNGMaskBase>(radialGradientMask));

    auto edgeLightModifier = std::make_shared<RenderEdgeLightModifier>(edgeLightFilter);
    renderContext->SetForegroundShader(edgeLightModifier);
#endif
}

void SheetEdgeLightBase::SetSheetEdgeLightTransitionEnd(RefPtr<FrameNode>& sheetNode)
{
#ifndef PREVIEW
    CHECK_NULL_VOID(sheetNode);
    auto geometryNode = sheetNode->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto renderContext = sheetNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);

    auto sheetSize = geometryNode->GetFrameSize();

    auto edgeLightFilter = std::make_shared<Rosen::RSNGSDFEdgeLightEffect>();

    edgeLightFilter->Setter<Rosen::SDFEdgeLightEffectSpreadFactorTag>(SPREAD_FACTOR);
    edgeLightFilter->Setter<Rosen::SDFEdgeLightEffectBloomIntensityCutoffTag>(BLOOM_INTENSITY_CUTOFF);
    edgeLightFilter->Setter<Rosen::SDFEdgeLightEffectLightMaxIntensityTag>(LIGHT_MAX_INTENSITY);
    edgeLightFilter->Setter<Rosen::SDFEdgeLightEffectMaxBloomIntensityTag>(MAX_BLOOM_INTENSITY);
    edgeLightFilter->Setter<Rosen::SDFEdgeLightEffectBloomFalloffPowTag>(BLOOM_FALLOFF_POW);
    edgeLightFilter->Setter<Rosen::SDFEdgeLightEffectMinBorderWidthTag>(MIN_BORDER_WIDTH);
    edgeLightFilter->Setter<Rosen::SDFEdgeLightEffectMaxBorderWidthTag>(MAX_BORDER_WIDTH);
    edgeLightFilter->Setter<Rosen::SDFEdgeLightEffectInnerBorderBloomWidthTag>(INNER_BORDER_BLOOM_WIDTH);
    edgeLightFilter->Setter<Rosen::SDFEdgeLightEffectOuterBorderBloomWidthTag>(OUTER_BORDER_BLOOM_WIDTH);
    edgeLightFilter->Setter<Rosen::SDFEdgeLightEffectColorTag>(
        Rosen::Vector3f(EDGE_LIGHT_COLOR / 255.0f, EDGE_LIGHT_COLOR / 255.0f, EDGE_LIGHT_COLOR / 255.0f));

    auto radialGradientMask = std::make_shared<Rosen::RSNGRadialGradientMask>();

    Rosen::Vector2f center = { EDGE_LIGHT_CENTER_X, EDGE_LIGHT_CENTER_Y * sheetSize.Width() / sheetSize.Height() };
    std::vector<float> colors = { 1.0f, 0.7f, 0.4f, 0.0f };
    std::vector<float> positions = { 0.0f, 0.3f, 0.6f, 1.0f };
    float radiusX = NUM_ZERO;
    float radiusY = NUM_ZERO;
    radialGradientMask->Setter<Rosen::RadialGradientMaskCenterTag>(center);
    radialGradientMask->Setter<Rosen::RadialGradientMaskRadiusXTag>(radiusX);
    radialGradientMask->Setter<Rosen::RadialGradientMaskRadiusYTag>(radiusY);
    radialGradientMask->Setter<Rosen::RadialGradientMaskColorsTag>(colors);
    radialGradientMask->Setter<Rosen::RadialGradientMaskPositionsTag>(positions);

    edgeLightFilter->Setter<Rosen::SDFEdgeLightEffectLightMaskTag>(
        std::static_pointer_cast<Rosen::RSNGMaskBase>(radialGradientMask));

    auto edgeLightModifier = std::make_shared<RenderEdgeLightModifier>(edgeLightFilter);
    renderContext->SetForegroundShader(edgeLightModifier);
#endif
}

} // namespace OHOS::Ace::NG