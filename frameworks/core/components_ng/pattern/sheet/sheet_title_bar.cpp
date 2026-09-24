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

#include "base/geometry/calc_dimension.h"
#include "base/utils/utils.h"
#include "core/common/resource/resource_parse_utils.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/sheet/sheet_presentation_pattern.h"
#include "core/components_ng/pattern/sheet/sheet_presentation_property.h"
#include "core/components_ng/pattern/sheet/sheet_style.h"
#include "core/components_ng/pattern/scroll/scroll_pattern.h"
#include "core/components_ng/pattern/scrollable/scrollable_controller.h"
#include "core/components_ng/pattern/scrollable/scrollable_paint_property.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"
#include "core/components_ng/property/gradient_property.h"
#include "core/components_ng/render/render_context.h"
#include "core/pipeline/base/element_register.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr double SHEET_GRADUAL_BLUR_MASK_EXTRA_HEIGHT_VP = 32.0;
constexpr SheetTitleBarBackgroundBlur DEFAULT_TITLE_BAR_BACKGROUND_BLUR = SheetTitleBarBackgroundBlur::NONE;
constexpr float SHEET_GRADUAL_BLUR_RADIUS = 12.0f;
constexpr Dimension SHEET_TITLE_BAR_BLUR_EFFECTIVE_DISTANCE = 8.0_vp;
constexpr Dimension SHEET_FLING_BLUR_CLOSE_THRESHOLD_PX = 10.0_px;
constexpr Dimension SHEET_FLING_BLUR_REOPEN_THRESHOLD_PX = 9.0_px;
constexpr int32_t SHEET_TITLE_EFFECT_Z_INDEX = 1;
constexpr int32_t SHEET_TITLE_STACK_Z_INDEX = 2;
const Color SHEET_NON_SMOOTH_GRADUAL_BLUR_LIGHT_BG_COLOR = Color::FromString("#CCF1F3F5");
const Color SHEET_NON_SMOOTH_GRADUAL_BLUR_DARK_BG_COLOR = Color::FromString("#66202224");
const Color SHEET_SMOOTH_GRADUAL_BLUR_LIGHT_BG_COLOR = Color::FromString("#F2F1F3F5");
const Color SHEET_SMOOTH_GRADUAL_BLUR_DARK_BG_COLOR = Color::FromString("#E5202224");
const std::vector<std::pair<float, float>> SHEET_GRADIENT_BLUR_STOPS = { { 1.0f, 0.0f }, { 0.6f, 0.6f },
    { 0.0f, 1.0f } };
const std::vector<std::pair<float, float>> SHEET_SMOOTH_GRADUAL_MASK_FRACTION_STOPS = { { 1.0f, 0.0f },
    { 0.99764f, 0.450f }, { 0.99010f, 0.478f }, { 0.97627f, 0.508f }, { 0.95574f, 0.536f }, { 0.92808f, 0.566f },
    { 0.89108f, 0.594f }, { 0.84375f, 0.624f }, { 0.78547f, 0.652f }, { 0.71344f, 0.682f }, { 0.63048f, 0.710f },
    { 0.53513f, 0.740f }, { 0.43280f, 0.768f }, { 0.33021f, 0.798f }, { 0.23699f, 0.826f }, { 0.15625f, 0.854f },
    { 0.09588f, 0.884f }, { 0.05096f, 0.914f }, { 0.02089f, 0.942f }, { 0.00491f, 0.972f }, { 0.0f, 1.0f } };
const std::vector<std::pair<float, float>> SHEET_NON_SMOOTH_GRADUAL_MASK_FRACTION_STOPS = { { 1.0f, 0.0f },
    { 1.0f, 0.3f }, { 0.99764f, 0.335f }, { 0.99010f, 0.370f }, { 0.97627f, 0.405f }, { 0.95574f, 0.440f },
    { 0.92808f, 0.475f }, { 0.89108f, 0.510f }, { 0.84375f, 0.545f }, { 0.78547f, 0.580f }, { 0.71344f, 0.615f },
    { 0.63048f, 0.650f }, { 0.53513f, 0.685f }, { 0.43280f, 0.720f }, { 0.33021f, 0.755f }, { 0.23699f, 0.790f },
    { 0.15625f, 0.825f }, { 0.09588f, 0.860f }, { 0.05096f, 0.895f }, { 0.02089f, 0.930f }, { 0.00491f, 0.965f },
    { 0.0f, 1.0f } };

Gradient CreateSheetFadeOutGradient(const Color& color, double opacity, UiMaterialLevel materialLevel)
{
    const auto& fractionStops = (materialLevel == UiMaterialLevel::SMOOTH)
                                    ? SHEET_SMOOTH_GRADUAL_MASK_FRACTION_STOPS
                                    : SHEET_NON_SMOOTH_GRADUAL_MASK_FRACTION_STOPS;
    auto blendColor = color.BlendOpacity(opacity);
    Gradient gradient;
    gradient.CreateGradientWithType(GradientType::LINEAR);
    gradient.SetDirection(GradientDirection::BOTTOM);
    for (const auto& fractionStop : fractionStops) {
        GradientColor stepColor(blendColor.BlendOpacity(fractionStop.first));
        stepColor.SetDimension(fractionStop.second * 100.0f, DimensionUnit::PERCENT);
        gradient.AddColor(stepColor);
    }
    return gradient;
}

float CalculateTitleBarBlurProgress(double totalOffset, const SheetTitleBarBackgroundBlurOptions& options)
{
    double effectiveDistanceBase = SHEET_TITLE_BAR_BLUR_EFFECTIVE_DISTANCE.ConvertToPx();
    if (options.effectiveDistance.has_value()) {
        auto customEffectiveDistancePx = options.effectiveDistance.value().ConvertToPx();
        effectiveDistanceBase = std::max(static_cast<double>(1e-6), customEffectiveDistancePx);
    }
    return static_cast<float>(std::max(totalOffset, static_cast<double>(0.0f)) / effectiveDistanceBase);
}

void UpdateNodeZIndex(const RefPtr<FrameNode>& node, int32_t zIndex)
{
    CHECK_NULL_VOID(node);
    auto renderContext = node->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    int32_t currentDragBarZIndex = renderContext->GetZIndexValue(0);
    if (currentDragBarZIndex > SHEET_TITLE_STACK_Z_INDEX) {
        return;
    }
    renderContext->UpdateZIndex(zIndex);
}
} // namespace

bool SheetPresentationPattern::CheckSheetHaveTitle(const NG::SheetStyle& sheetStyle)
{
    return sheetStyle.isTitleBuilder.has_value();
}

bool SheetPresentationPattern::CheckTitleIsStackMode(const SheetStyle& sheetStyle)
{
    if (!sheetStyle.titleBarHoverMode) {
        return false;
    }
    return sheetStyle.titleBarHoverMode.value() == SheetTitleBarHoverMode::STACK && CheckSheetHaveTitle(sheetStyle);
}

bool SheetPresentationPattern::CheckTitleIsHasEffectNode(const SheetStyle& sheetStyle)
{
    if (!sheetStyle.titleBarBackgroundBlur) {
        return false;
    }
    auto options = sheetStyle.titleBarBackgroundBlur.value();
    if (!options.blurStyle) {
        return false;
    }
    return options.blurStyle.value() == SheetTitleBarBackgroundBlur::GRADIENT && CheckSheetHaveTitle(sheetStyle);
}

void SheetPresentationPattern::MountTitleBarEffectNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (titleBarEffectNode_) {
        return;
    }
    titleBarEffectNode_ = FrameNode::CreateFrameNode(
        "SheetTitleBarEffect", ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<Pattern>());
    titleBarEffectNode_->SetHitTestMode(HitTestMode::HTMNONE);

    titleBarEffectNode_->MountToParent(host);
    UpdateNodeZIndex(titleBarEffectNode_, SHEET_TITLE_EFFECT_Z_INDEX);
    UpdateNodeZIndex(GetTitleBuilderNode(), SHEET_TITLE_STACK_Z_INDEX);
    UpdateNodeZIndex(GetSheetCloseIcon(), SHEET_TITLE_STACK_Z_INDEX);
    UpdateNodeZIndex(GetDragBarNode(), SHEET_TITLE_STACK_Z_INDEX);
    titleBarEffectNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SheetPresentationPattern::RefreshTitleBarBlurByCurrentOffset()
{
    auto layoutProperty = GetLayoutProperty<SheetPresentationProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto sheetStyle = layoutProperty->GetSheetStyleValue();
    if (!CheckTitleIsHasEffectNode(sheetStyle)) {
        return;
    }
    auto scrollNode = GetSheetScrollNode();
    CHECK_NULL_VOID(scrollNode);
    auto scrollPattern = scrollNode->GetPattern<ScrollablePattern>();
    CHECK_NULL_VOID(scrollPattern);
    double totalOffset = GetTitleBlurNestedScrollOffset() + scrollPattern->GetTotalOffset();
    const auto& options = sheetStyle.titleBarBackgroundBlur.value();
    auto progress = CalculateTitleBarBlurProgress(totalOffset, options);
    UpdateTitleEffectBlurAndMaskColorProgress(progress);
}

void SheetPresentationPattern::ResetTitleBarEffectNode()
{
    isTitleBarBlurDisabledByFling_ = false;
    UnRegisterTitleBarScrollObserver();
    UnRegisterTitleBlurNestedScroll();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (titleBarEffectNode_) {
        host->RemoveChild(titleBarEffectNode_);
        titleBarEffectNode_->MountToParent(nullptr);
        titleBarEffectNode_ = nullptr;
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);

        UpdateNodeZIndex(GetTitleBuilderNode(), 0);
        UpdateNodeZIndex(GetSheetCloseIcon(), 0);
        UpdateNodeZIndex(GetDragBarNode(), 0);
    }
}

bool SheetPresentationPattern::CheckSheetTypeForTitleEffectNode()
{
    auto currentSheetType = GetSheetTypeNoProcess();
    return currentSheetType != SheetType::SHEET_MINIMIZE && currentSheetType != SheetType::SHEET_CONTENT_COVER;
}

void SheetPresentationPattern::ApplyTitleBarBackgroundBlur()
{
    auto layoutProperty = GetLayoutProperty<SheetPresentationProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto sheetStyle = layoutProperty->GetSheetStyleValue();
    if (!CheckTitleIsHasEffectNode(sheetStyle) || !CheckSheetTypeForTitleEffectNode()) {
        ResetTitleBarEffectNode();
        return;
    }

    MountTitleBarEffectNode();
    RegisterTitleBarScrollObserver();

    if (!GetTitleBarEffectNode()) {
        return;
    }
    auto scrollNode = GetSheetScrollNode();
    CHECK_NULL_VOID(scrollNode);
    auto scrollPattern = scrollNode->GetPattern<ScrollablePattern>();
    CHECK_NULL_VOID(scrollPattern);
    double totalOffset = GetTitleBlurNestedScrollOffset() + scrollPattern->GetTotalOffset();
    const auto& options = sheetStyle.titleBarBackgroundBlur.value();
    auto progress = CalculateTitleBarBlurProgress(totalOffset, options);
    UpdateTitleEffectBlurAndMaskColorProgress(progress);
}

void SheetPresentationPattern::OnContentScrollUpdate(double totalOffset, double frameOffset, bool isFling)
{
    auto layoutProperty = GetLayoutProperty<SheetPresentationProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto sheetStyle = layoutProperty->GetSheetStyleValue();
    if (!GetTitleBarEffectNode() || !sheetStyle.titleBarBackgroundBlur.has_value()) {
        return;
    }
    const auto& options = sheetStyle.titleBarBackgroundBlur.value();
    auto blurStyle = options.blurStyle.value_or(DEFAULT_TITLE_BAR_BACKGROUND_BLUR);
    if (blurStyle == SheetTitleBarBackgroundBlur::NONE) {
        return;
    }
    if (isFling) {
        auto absFrameOffset = std::abs(frameOffset);
        if (absFrameOffset > SHEET_FLING_BLUR_CLOSE_THRESHOLD_PX.ConvertToPx()) {
            isTitleBarBlurDisabledByFling_ = true;
        } else if (absFrameOffset < SHEET_FLING_BLUR_REOPEN_THRESHOLD_PX.ConvertToPx()) {
            isTitleBarBlurDisabledByFling_ = false;
        }
    } else {
        isTitleBarBlurDisabledByFling_ = false;
    }
    auto progress = CalculateTitleBarBlurProgress(totalOffset, options);
    UpdateTitleEffectBlurAndMaskColorProgress(progress);
}

void SheetPresentationPattern::OnFlingEnd(double totalOffset)
{
    isTitleBarBlurDisabledByFling_ = false;
    OnContentScrollUpdate(totalOffset, 0.0, false);
}

void SheetPresentationPattern::UpdateTitleEffectBlurAndMaskColorProgress(float progress)
{
    progress = std::clamp(progress, 0.0f, 1.0f);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    bool isDarkMode = pipeline->GetColorMode() == ColorMode::DARK;
    auto materialLevel = SystemProperties::GetUiMaterialLevel();
    auto layoutProperty = GetLayoutProperty<SheetPresentationProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto sheetStyle = layoutProperty->GetSheetStyleValue();

    auto bgColor = GetTitleBarEffectBgColor(sheetStyle, materialLevel, isDarkMode);
    float currentOpacity = progress;
    auto gradient = CreateSheetFadeOutGradient(bgColor, currentOpacity, materialLevel);
    CHECK_NULL_VOID(titleBarEffectNode_);
    auto renderContext = titleBarEffectNode_->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->UpdateLinearGradient(gradient);

    auto blurStyle = DEFAULT_TITLE_BAR_BACKGROUND_BLUR;
    if (sheetStyle.titleBarBackgroundBlur.has_value()) {
        blurStyle = sheetStyle.titleBarBackgroundBlur->blurStyle.value_or(SheetTitleBarBackgroundBlur::NONE);
    }
    if (blurStyle == SheetTitleBarBackgroundBlur::NONE || materialLevel == UiMaterialLevel::SMOOTH ||
        isTitleBarBlurDisabledByFling_) {
        NG::LinearGradientBlurPara blurPara(
            Dimension(0.0f, DimensionUnit::VP), SHEET_GRADIENT_BLUR_STOPS, GradientDirection::BOTTOM);
        renderContext->UpdateLinearGradientBlur(blurPara);
        return;
    }
    float currentBlurRadius = progress * SHEET_GRADUAL_BLUR_RADIUS;

    NG::LinearGradientBlurPara blurPara(
        Dimension(currentBlurRadius, DimensionUnit::VP), SHEET_GRADIENT_BLUR_STOPS, GradientDirection::BOTTOM);
    renderContext->UpdateLinearGradientBlur(blurPara);
}

Color SheetPresentationPattern::GetTitleBarEffectBgColor(
    const NG::SheetStyle& sheetStyle, UiMaterialLevel materialLevel, bool isDarkMode)
{
    if (sheetStyle.titleBarBackgroundBlur.has_value()) {
        const auto& options = sheetStyle.titleBarBackgroundBlur.value();
        if (options.maskColor.has_value()) {
            return options.maskColor.value();
        }
    }
    if (materialLevel == UiMaterialLevel::SMOOTH) {
        if (isDarkMode) {
            return SHEET_SMOOTH_GRADUAL_BLUR_DARK_BG_COLOR;
        }
        return SHEET_SMOOTH_GRADUAL_BLUR_LIGHT_BG_COLOR;
    }
    return isDarkMode ? SHEET_NON_SMOOTH_GRADUAL_BLUR_DARK_BG_COLOR : SHEET_NON_SMOOTH_GRADUAL_BLUR_LIGHT_BG_COLOR;
}

void SheetPresentationPattern::UpdateStackModeZIndex()
{
    auto layoutProperty = GetLayoutProperty<SheetPresentationProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto sheetStyle = layoutProperty->GetSheetStyleValue();
    bool titleUseStackMode = CheckTitleIsStackMode(sheetStyle);
    bool hasEffectNode = CheckTitleIsHasEffectNode(sheetStyle);
    UpdateNodeZIndex(GetTitleBuilderNode(), titleUseStackMode || hasEffectNode ? SHEET_TITLE_STACK_Z_INDEX : 0);
    UpdateNodeZIndex(GetSheetCloseIcon(), titleUseStackMode || hasEffectNode ? SHEET_TITLE_STACK_Z_INDEX : 0);
    UpdateNodeZIndex(GetDragBarNode(), titleUseStackMode || hasEffectNode ? SHEET_TITLE_STACK_Z_INDEX : 0);

    if (preScrollSelfHeight_.has_value() && preTitleStackMode_ != titleUseStackMode) {
        auto scrollNode = GetSheetScrollNode();
        CHECK_NULL_VOID(scrollNode);
        auto scrollProps = scrollNode->GetLayoutProperty<ScrollLayoutProperty>();
        CHECK_NULL_VOID(scrollProps);
        auto titleHeight = GetTitleBuilderHeight();
        scrollProps->UpdateUserDefinedIdealSize(CalcSize(std::nullopt,
            CalcLength(
                Dimension(preScrollSelfHeight_.value() + (titleUseStackMode ? titleHeight : 0), DimensionUnit::PX))));
        scrollNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
}

void SheetPresentationPattern::RegisterTitleBlurNestedScroll(WeakPtr<NestableScrollContainer> sourceScrollNode)
{
    auto layoutProperty = GetLayoutProperty<SheetPresentationProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto sheetStyle = layoutProperty->GetSheetStyleValue(SheetStyle());
    if (!CheckTitleIsHasEffectNode(sheetStyle)) {
        return;
    }

    UnRegisterTitleBlurNestedScroll();
    auto scrollNode = GetSheetScrollNode();
    CHECK_NULL_VOID(scrollNode);
    auto scrollNodeId = scrollNode->GetId();
    auto currentContainer = sourceScrollNode.Upgrade();
    CHECK_NULL_VOID(currentContainer);

    while (currentContainer) {
        auto currentNode = currentContainer->GetHost();
        CHECK_NULL_VOID(currentNode);
        auto currentNodeId = currentNode->GetId();
        if (currentNodeId == scrollNodeId) {
            return;
        }
        nestedScrollNodeList_.push_back(WeakClaim(AceType::RawPtr(currentNode)));

        auto currentPattern = currentNode->GetPattern<ScrollablePattern>();
        CHECK_NULL_VOID(currentPattern);
        {
            auto controller = currentPattern->GetOrCreatePositionController();
            CHECK_NULL_VOID(controller);
            auto obsMgr = controller->GetObserverManager();
            if (!obsMgr) {
                obsMgr = AceType::MakeRefPtr<ScrollerObserverManager>();
                controller->SetObserverManager(obsMgr);
            }
            ScrollerObserver observer;
            observer.onDidScrollEvent = [weakSheet = WeakClaim(this), weakScrollNode = WeakClaim(RawPtr(currentNode))](
                                            Dimension frameDelta, ScrollSource source, bool isAtTop, bool isAtBottom) {
                auto sheet = weakSheet.Upgrade();
                CHECK_NULL_VOID(sheet);
                auto sheetScrollNode = sheet->GetSheetScrollNode();
                CHECK_NULL_VOID(sheetScrollNode);
                auto sheetScrollPattern = sheetScrollNode->GetPattern<ScrollablePattern>();
                CHECK_NULL_VOID(sheetScrollPattern);
                auto scrollNode = weakScrollNode.Upgrade();
                CHECK_NULL_VOID(scrollNode);
                double totalOffset = sheet->GetTitleBlurNestedScrollOffset() + sheetScrollPattern->GetTotalOffset();
                bool isFling = source == ScrollSource::FLING;
                sheet->OnContentScrollUpdate(totalOffset, frameDelta.ConvertToPx(), isFling);
            };
            obsMgr->AddObserver(observer, currentNodeId);
        }
        currentContainer = currentPattern->GetNestedScrollParent();
    }
}

void SheetPresentationPattern::UnRegisterTitleBlurNestedScroll()
{
    for (auto weakNode : nestedScrollNodeList_) {
        auto scrollableNode = weakNode.Upgrade();
        CHECK_NULL_VOID(scrollableNode);
        auto currentPattern = scrollableNode->GetPattern<ScrollablePattern>();
        CHECK_NULL_VOID(currentPattern);
        auto controller = currentPattern->GetOrCreatePositionController();
        CHECK_NULL_VOID(controller);
        auto obsMgr = controller->GetObserverManager();
        if (!obsMgr) {
            continue;
        }
        obsMgr->RemoveObserver(scrollableNode->GetId());
    }
    nestedScrollNodeList_.clear();
}

float SheetPresentationPattern::GetTitleBlurNestedScrollOffset()
{
    float totalOffset = 0.0f;
    for (auto weakNode : nestedScrollNodeList_) {
        auto scrollNode = weakNode.Upgrade();
        CHECK_NULL_RETURN(scrollNode, 0.0f);
        auto currentPattern = scrollNode->GetPattern<ScrollablePattern>();
        CHECK_NULL_RETURN(currentPattern, 0.0f);
        double currentOffset = currentPattern->GetTotalOffset();
        totalOffset += currentOffset;
    }
    return totalOffset;
}

void SheetPresentationPattern::RegisterTitleBarScrollObserver()
{
    if (hasTitleBarScrollObs_) {
        return;
    }
    auto scrollNode = GetSheetScrollNode();
    CHECK_NULL_VOID(scrollNode);
    auto scrollPattern = scrollNode->GetPattern<ScrollablePattern>();
    CHECK_NULL_VOID(scrollPattern);
    auto controller = scrollPattern->GetOrCreatePositionController();
    CHECK_NULL_VOID(controller);
    auto obsMgr = controller->GetObserverManager();
    if (!obsMgr) {
        obsMgr = AceType::MakeRefPtr<ScrollerObserverManager>();
        controller->SetObserverManager(obsMgr);
    }
    ScrollerObserver observer;
    observer.onDidScrollEvent = [weakSheet = WeakClaim(this), weakScrollNode = WeakClaim(RawPtr(scrollNode))](
                                    Dimension frameDelta, ScrollSource source, bool isAtTop, bool isAtBottom) {
        auto sheet = weakSheet.Upgrade();
        CHECK_NULL_VOID(sheet);
        auto scrollNode = weakScrollNode.Upgrade();
        CHECK_NULL_VOID(scrollNode);
        auto scrollPattern = scrollNode->GetPattern<ScrollablePattern>();
        CHECK_NULL_VOID(scrollPattern);
        double totalOffset = sheet->GetTitleBlurNestedScrollOffset() + scrollPattern->GetTotalOffset();
        bool isFling = source == ScrollSource::FLING;
        sheet->OnContentScrollUpdate(totalOffset, frameDelta.ConvertToPx(), isFling);
    };
    observer.onScrollStopEvent = [weakSheet = WeakClaim(this),
                                     weakScrollNode = WeakClaim(RawPtr(scrollNode))]() {
        auto sheet = weakSheet.Upgrade();
        CHECK_NULL_VOID(sheet);
        if (!sheet->IsTitleBarBlurDisabledByFling()) {
            return;
        }
        auto scrollNode = weakScrollNode.Upgrade();
        CHECK_NULL_VOID(scrollNode);
        auto scrollPattern = scrollNode->GetPattern<ScrollablePattern>();
        CHECK_NULL_VOID(scrollPattern);
        double totalOffset = sheet->GetTitleBlurNestedScrollOffset() + scrollPattern->GetTotalOffset();
        sheet->OnFlingEnd(totalOffset);
    };

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    obsMgr->AddObserver(observer, host->GetId());
    hasTitleBarScrollObs_ = true;
}

void SheetPresentationPattern::UnRegisterTitleBarScrollObserver()
{
    if (hasTitleBarScrollObs_) {
        auto scrollNode = GetSheetScrollNode();
        CHECK_NULL_VOID(scrollNode);
        auto scrollPattern = scrollNode->GetPattern<ScrollablePattern>();
        CHECK_NULL_VOID(scrollPattern);
        auto controller = scrollPattern->GetOrCreatePositionController();
        CHECK_NULL_VOID(controller);
        auto obsMgr = controller->GetObserverManager();
        CHECK_NULL_VOID(obsMgr);

        auto host = GetHost();
        CHECK_NULL_VOID(host);
        obsMgr->RemoveObserver(host->GetId());
        hasTitleBarScrollObs_ = false;
    }
}

double SheetPresentationPattern::GetTitleBarEffectHeight(const SheetStyle& sheetStyle, float titleBarHeight)
{
    if (!sheetStyle.titleBarBackgroundBlur.has_value() || !GetTitleBarEffectNode()) {
        return 0.0f;
    }
    double maskExtraHeightPx = 0.0f;
    const auto& options = sheetStyle.titleBarBackgroundBlur.value();
    if (options.maskExtraHeight.has_value()) {
        maskExtraHeightPx = options.maskExtraHeight.value().ConvertToPx();
    } else {
        maskExtraHeightPx = Dimension(SHEET_GRADUAL_BLUR_MASK_EXTRA_HEIGHT_VP, DimensionUnit::VP).ConvertToPx();
    }
    double resHeight = static_cast<double>(titleBarHeight) + maskExtraHeightPx;
    resHeight = std::max(static_cast<double>(0.0f), resHeight);
    return resHeight;
}

void SheetPresentationPattern::UpdateTitleBarMaskColor(
    const RefPtr<ResourceObject>& resObj, const WeakPtr<FrameNode>& sheetNodeWK)
{
    auto sheetNode = sheetNodeWK.Upgrade();
    CHECK_NULL_VOID(sheetNode);
    Color maskColor;
    bool result = ResourceParseUtils::ParseResColor(resObj, maskColor);
    if (!result) {
        return;
    }
    auto layoutProperty = DynamicCast<SheetPresentationProperty>(sheetNode->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto currSheetStyle = layoutProperty->GetSheetStyleValue();
    if (!currSheetStyle.titleBarBackgroundBlur.has_value()) {
        return;
    }
    currSheetStyle.titleBarBackgroundBlur->maskColor = maskColor;
    layoutProperty->UpdateSheetStyle(currSheetStyle);
    auto pattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->RefreshTitleBarBlurByCurrentOffset();
}

void SheetPresentationPattern::RegisterTitleBarMaskColorRes(
    const RefPtr<FrameNode>& sheetNode, RefPtr<ResourceObject>& colorResObj)
{
    CHECK_NULL_VOID(sheetNode);
    auto pattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(pattern);
    if (colorResObj) {
        auto&& updateFunc = [sheetNodeWK = AceType::WeakClaim(AceType::RawPtr(sheetNode)), weak = WeakClaim(this)](
                                const RefPtr<ResourceObject>& colorResObj) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->UpdateTitleBarMaskColor(colorResObj, sheetNodeWK);
        };
        pattern->AddResObj("sheetPage.titleBarMaskColor", colorResObj, std::move(updateFunc));
    } else {
        pattern->RemoveResObj("sheetPage.titleBarMaskColor");
    }
}

void SheetPresentationPattern::UpdateTitleBarMaskExtraHeight(
    const RefPtr<ResourceObject>& resObj, const WeakPtr<FrameNode>& sheetNodeWK)
{
    auto sheetNode = sheetNodeWK.Upgrade();
    CHECK_NULL_VOID(sheetNode);
    CalcDimension maskExtraHeight;
    bool result = ResourceParseUtils::ParseResDimensionVpNG(resObj, maskExtraHeight);
    if (!result) {
        return;
    }
    auto layoutProperty = DynamicCast<SheetPresentationProperty>(sheetNode->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto currSheetStyle = layoutProperty->GetSheetStyleValue();
    if (!currSheetStyle.titleBarBackgroundBlur.has_value()) {
        return;
    }
    currSheetStyle.titleBarBackgroundBlur->maskExtraHeight = maskExtraHeight;
    layoutProperty->UpdateSheetStyle(currSheetStyle);
    sheetNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void SheetPresentationPattern::RegisterTitleBarMaskExtraHeightRes(
    const RefPtr<FrameNode>& sheetNode, RefPtr<ResourceObject>& resObj)
{
    CHECK_NULL_VOID(sheetNode);
    auto pattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(pattern);
    if (resObj) {
        auto&& updateFunc = [sheetNodeWK = AceType::WeakClaim(AceType::RawPtr(sheetNode)), weak = WeakClaim(this)](
                                const RefPtr<ResourceObject>& resObj) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->UpdateTitleBarMaskExtraHeight(resObj, sheetNodeWK);
        };
        pattern->AddResObj("sheetPage.titleBarMaskExtraHeight", resObj, std::move(updateFunc));
    } else {
        pattern->RemoveResObj("sheetPage.titleBarMaskExtraHeight");
    }
}

void SheetPresentationPattern::UpdateTitleBarEffectiveDistance(
    const RefPtr<ResourceObject>& resObj, const WeakPtr<FrameNode>& sheetNodeWK)
{
    auto sheetNode = sheetNodeWK.Upgrade();
    CHECK_NULL_VOID(sheetNode);
    CalcDimension effectiveDistance;
    bool result = ResourceParseUtils::ParseResDimensionVpNG(resObj, effectiveDistance);
    if (!result) {
        return;
    }
    auto layoutProperty = DynamicCast<SheetPresentationProperty>(sheetNode->GetLayoutProperty());
    CHECK_NULL_VOID(layoutProperty);
    auto currSheetStyle = layoutProperty->GetSheetStyleValue();
    if (!currSheetStyle.titleBarBackgroundBlur.has_value()) {
        return;
    }
    currSheetStyle.titleBarBackgroundBlur->effectiveDistance = effectiveDistance;
    layoutProperty->UpdateSheetStyle(currSheetStyle);
    auto pattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->RefreshTitleBarBlurByCurrentOffset();
}

void SheetPresentationPattern::RegisterTitleBarEffectiveDistanceRes(
    const RefPtr<FrameNode>& sheetNode, RefPtr<ResourceObject>& resObj)
{
    CHECK_NULL_VOID(sheetNode);
    auto pattern = sheetNode->GetPattern<SheetPresentationPattern>();
    CHECK_NULL_VOID(pattern);
    if (resObj) {
        auto&& updateFunc = [sheetNodeWK = AceType::WeakClaim(AceType::RawPtr(sheetNode)), weak = WeakClaim(this)](
                                const RefPtr<ResourceObject>& resObj) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->UpdateTitleBarEffectiveDistance(resObj, sheetNodeWK);
        };
        pattern->AddResObj("sheetPage.titleBarEffectiveDistance", resObj, std::move(updateFunc));
    } else {
        pattern->RemoveResObj("sheetPage.titleBarEffectiveDistance");
    }
}

void SheetPresentationPattern::UpdateSheetScrollBar(const NG::SheetStyle& sheetStyle)
{
    if (preScrollBarState_ == sheetStyle.scrollBarState) {
        return;
    }
    preScrollBarState_ = sheetStyle.scrollBarState;

    auto barState = sheetStyle.scrollBarState.value_or(DisplayMode::OFF);
    auto scrollNode = GetSheetScrollNode();
    CHECK_NULL_VOID(scrollNode);
    auto paintProperty = scrollNode->GetPaintProperty<ScrollablePaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    paintProperty->UpdateScrollBarMode(barState);
    scrollNode->MarkModifyDone();
    scrollNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void SheetPresentationPattern::UpdateZIndexAndTitleEffectNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty<SheetPresentationProperty>();
    CHECK_NULL_VOID(layoutProperty);

    auto sheetStyle = layoutProperty->GetSheetStyleValue();

    bool currentIsTitleStackMode = CheckTitleIsStackMode(sheetStyle);

    if (sheetStyle.titleBarBackgroundBlur.has_value() || preTitleBlurOptions_ != sheetStyle.titleBarBackgroundBlur) {
        ApplyTitleBarBackgroundBlur();
        preTitleBlurOptions_ = sheetStyle.titleBarBackgroundBlur;
    }
    if (sheetStyle.titleBarHoverMode.has_value() || currentIsTitleStackMode != preTitleStackMode_) {
        UpdateStackModeZIndex();
        preTitleStackMode_ = currentIsTitleStackMode;
    }
}
} // namespace OHOS::Ace::NG