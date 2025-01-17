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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_swiper_ffi.h"

#include "cj_lambda.h"

#include "bridge/cj_frontend/cppview/swiper_controller.h"
#include "bridge/cj_frontend/cppview/view_abstract.h"
#include "bridge/common/utils/utils.h"
#include "core/components/swiper/swiper_indicator_theme.h"
#include "core/components_ng/pattern/scrollable/scrollable_properties.h"
#include "core/components_ng/pattern/swiper/swiper_content_transition_proxy.h"
#include "core/components_ng/pattern/swiper/swiper_model.h"
#include "core/components_ng/pattern/swiper/swiper_model_ng.h"

using namespace OHOS::Ace;
using namespace OHOS::FFI;
using namespace OHOS::Ace::Framework;

namespace {
const int32_t INVALID_UNIT = -1;
constexpr float ARROW_SIZE_COEFFICIENT = 0.75f;
constexpr int32_t DEFAULT_CUSTOM_ANIMATION_TIMEOUT = 0;
const std::vector<SwiperDisplayMode> SWIPER_DISPLAY_MODES = { SwiperDisplayMode::STRETCH,
    SwiperDisplayMode::AUTO_LINEAR };
const std::vector<EdgeEffect> EDGE_EFFECTS = { EdgeEffect::SPRING, EdgeEffect::FADE, EdgeEffect::NONE };

std::optional<Dimension> ParseIndicatorDimension(double& value, int32_t& unit)
{
    std::optional<Dimension> indicatorDimension;
    if (unit == INVALID_UNIT) {
        return indicatorDimension;
    }
    CalcDimension dimension(value, static_cast<DimensionUnit>(unit));
    indicatorDimension = dimension.ConvertToPx() >= 0.0f ? dimension : 0.0_vp;
    return indicatorDimension;
}

SwiperParameters GetDotIndicatorInfo(CJDotIndicator& value)
{
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, SwiperParameters());
    auto swiperIndicatorTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_RETURN(swiperIndicatorTheme, SwiperParameters());
    SwiperParameters swiperParameters;
    swiperParameters.dimLeft = ParseIndicatorDimension(value.indicator.left, value.indicator.leftUnit);
    swiperParameters.dimTop = ParseIndicatorDimension(value.indicator.top, value.indicator.topUnit);
    swiperParameters.dimRight = ParseIndicatorDimension(value.indicator.right, value.indicator.rightUnit);
    swiperParameters.dimBottom = ParseIndicatorDimension(value.indicator.bottom, value.indicator.bottomUnit);
    CalcDimension dimStart(value.indicator.start, static_cast<DimensionUnit>(value.indicator.startUnit));
    CalcDimension dimEnd(value.indicator.end, static_cast<DimensionUnit>(value.indicator.endUnit));
    swiperParameters.dimStart = dimStart;
    swiperParameters.dimEnd = dimEnd;

    auto defaultSize = swiperIndicatorTheme->GetSize();
    auto itemWidth = CalcDimension(value.itemWidth, static_cast<DimensionUnit>(value.itemWidthUnit));
    bool isWidthPercent = value.itemWidthUnit == static_cast<int32_t>(DimensionUnit::PERCENT);
    swiperParameters.itemWidth = (!isWidthPercent && itemWidth > 0.0_vp) ? itemWidth : defaultSize;
    auto itemHeight = CalcDimension(value.itemHeight, static_cast<DimensionUnit>(value.itemHeightUnit));
    bool isHeightPercent = value.itemHeightUnit == static_cast<int32_t>(DimensionUnit::PERCENT);
    swiperParameters.itemHeight = (!isHeightPercent && itemHeight > 0.0_vp) ? itemHeight : defaultSize;
    auto selectedItemWidth =
        CalcDimension(value.selectedItemWidth, static_cast<DimensionUnit>(value.selectedItemWidthUnit));
    bool isSelectedWidthPercent = value.selectedItemWidthUnit == static_cast<int32_t>(DimensionUnit::PERCENT);
    swiperParameters.selectedItemWidth =
        (!isSelectedWidthPercent && selectedItemWidth > 0.0_vp) ? selectedItemWidth : defaultSize;
    auto selectedItemHeight =
        CalcDimension(value.selectedItemHeight, static_cast<DimensionUnit>(value.selectedItemHeightUnit));
    bool isSelectedHeightPercent = value.selectedItemHeightUnit == static_cast<int32_t>(DimensionUnit::PERCENT);
    swiperParameters.selectedItemHeight =
        (!isSelectedHeightPercent && selectedItemHeight > 0.0_vp) ? selectedItemHeight : defaultSize;
    SwiperModel::GetInstance()->SetIsIndicatorCustomSize(
        isWidthPercent || isHeightPercent || isSelectedWidthPercent || isSelectedHeightPercent);
    swiperParameters.maskValue = value.mask;
    swiperParameters.colorVal = Color(value.color);
    swiperParameters.selectedColorVal = Color(value.selectedColor);
    swiperParameters.maxDisplayCountVal = value.maxDisplayCount;
    return swiperParameters;
}

SwiperDigitalParameters GetDigitIndicatorInfo(CJDigitIndicator& value)
{
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, SwiperDigitalParameters());
    auto swiperIndicatorTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_RETURN(swiperIndicatorTheme, SwiperDigitalParameters());
    SwiperDigitalParameters digitalParameters;
    digitalParameters.dimLeft = ParseIndicatorDimension(value.indicator.left, value.indicator.leftUnit);
    digitalParameters.dimTop = ParseIndicatorDimension(value.indicator.top, value.indicator.topUnit);
    digitalParameters.dimRight = ParseIndicatorDimension(value.indicator.right, value.indicator.rightUnit);
    digitalParameters.dimBottom = ParseIndicatorDimension(value.indicator.bottom, value.indicator.bottomUnit);
    CalcDimension dimStart(value.indicator.start, static_cast<DimensionUnit>(value.indicator.startUnit));
    CalcDimension dimEnd(value.indicator.end, static_cast<DimensionUnit>(value.indicator.endUnit));
    digitalParameters.dimStart = dimStart;
    digitalParameters.dimEnd = dimEnd;
    digitalParameters.fontColor = Color(value.fontColor);
    digitalParameters.selectedFontColor = Color(value.selectedColor);
    digitalParameters.fontSize =
        CalcDimension(value.digitFontSize, static_cast<DimensionUnit>(value.digitFontSizeUnit));
    digitalParameters.fontWeight = ConvertStrToFontWeight(value.digitFontWeight);
    digitalParameters.selectedFontSize =
        CalcDimension(value.selectedDigitFontSize, static_cast<DimensionUnit>(value.selectedDigitFontSizeUnit));
    digitalParameters.selectedFontWeight = ConvertStrToFontWeight(value.selectedDigitFontWeight);
    return digitalParameters;
}

SwiperArrowParameters GetArrowInfo(CJArrowStyle& value)
{
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, SwiperArrowParameters());
    auto swiperIndicatorTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_RETURN(swiperIndicatorTheme, SwiperArrowParameters());
    SwiperArrowParameters arrowParameters;
    arrowParameters.isShowBackground = value.showBackground;
    arrowParameters.isSidebarMiddle = value.isSidebarMiddle;
    if (arrowParameters.isSidebarMiddle) {
        CalcDimension backgroundSize(value.backgroundSize, static_cast<DimensionUnit>(value.backgroundSizeUnit));
        arrowParameters.backgroundSize =
            GreatNotEqual(backgroundSize.ConvertToVp(), 0.0) && (backgroundSize.Unit() != DimensionUnit::PERCENT)
                ? backgroundSize
                : swiperIndicatorTheme->GetBigArrowBackgroundSize();
        arrowParameters.backgroundColor = Color(value.backgroundColor);
        if (arrowParameters.isShowBackground.value()) {
            arrowParameters.arrowSize = arrowParameters.backgroundSize.value() * ARROW_SIZE_COEFFICIENT;
        } else {
            CalcDimension arrowSize(value.arrowSize, static_cast<DimensionUnit>(value.arrowSizeUnit));
            arrowParameters.arrowSize =
                GreatNotEqual(arrowSize.ConvertToVp(), 0.0) && (arrowSize.Unit() != DimensionUnit::PERCENT)
                    ? arrowSize
                    : swiperIndicatorTheme->GetBigArrowSize();
            arrowParameters.backgroundSize = arrowParameters.arrowSize;
        }
        arrowParameters.arrowColor = Color(value.arrowColor);
    } else {
        CalcDimension backgroundSize(value.backgroundSize, static_cast<DimensionUnit>(value.backgroundSizeUnit));
        arrowParameters.backgroundSize =
            GreatNotEqual(backgroundSize.ConvertToVp(), 0.0) && (backgroundSize.Unit() != DimensionUnit::PERCENT)
                ? backgroundSize
                : swiperIndicatorTheme->GetSmallArrowBackgroundSize();
        arrowParameters.backgroundColor = Color(value.backgroundColor);
        if (arrowParameters.isShowBackground.value()) {
            arrowParameters.arrowSize = arrowParameters.backgroundSize.value() * ARROW_SIZE_COEFFICIENT;
        } else {
            CalcDimension arrowSize(value.arrowSize, static_cast<DimensionUnit>(value.arrowSizeUnit));
            arrowParameters.arrowSize =
                GreatNotEqual(arrowSize.ConvertToVp(), 0.0) && (arrowSize.Unit() != DimensionUnit::PERCENT)
                    ? arrowSize
                    : swiperIndicatorTheme->GetSmallArrowSize();
            arrowParameters.backgroundSize = arrowParameters.arrowSize;
        }
        arrowParameters.arrowColor = Color(value.arrowColor);
    }
    return arrowParameters;
}

} // namespace

extern "C" {
void FfiOHOSAceFrameworkSwiperCreate(int64_t controllerId)
{
    auto nativeSwiperController = FFIData::GetData<NativeSwiperController>(controllerId);
    if (nativeSwiperController == nullptr) {
        LOGE("Swiper create error, Cannot get NativeSwiperController by id: %{public}" PRId64, controllerId);
        return;
    }
    auto controller = SwiperModel::GetInstance()->Create();
    nativeSwiperController->SetController(controller);
}

void FfiOHOSAceFrameworkSwiperSetAutoplay(bool autoPlay)
{
    SwiperModel::GetInstance()->SetAutoPlay(autoPlay);
}

void FfiOHOSAceFrameworkSwiperSetDigital(bool digitalIndicator)
{
    // deleted in the future
}

void FfiOHOSAceFrameworkSwiperSetDuration(uint32_t duration)
{
    SwiperModel::GetInstance()->SetDuration(duration);
}

void FfiOHOSAceFrameworkSwiperSetIndex(uint32_t index)
{
    SwiperModel::GetInstance()->SetIndex(index);
}

void FfiOHOSAceFrameworkSwiperSetInterval(uint32_t interval)
{
    SwiperModel::GetInstance()->SetAutoPlayInterval(interval);
}

void FfiOHOSAceFrameworkSwiperSetLoop(bool loop)
{
    SwiperModel::GetInstance()->SetLoop(loop);
}

void FfiOHOSAceFrameworkSwiperSetVertical(bool isVertical)
{
    SwiperModel::GetInstance()->SetDirection(isVertical ? Axis::VERTICAL : Axis::HORIZONTAL);
}

void FfiOHOSAceFrameworkSwiperSetIndicator(bool showIndicator)
{
    SwiperModel::GetInstance()->SetShowIndicator(showIndicator);
}

void FfiOHOSAceFrameworkSwiperSetWidth(double width, int32_t unit)
{
    Dimension value(width, static_cast<DimensionUnit>(unit));
    ViewAbstractModel::GetInstance()->SetWidth(value);
    SwiperModel::GetInstance()->SetMainSwiperSizeWidth();
}

void FfiOHOSAceFrameworkSwiperSetHeight(double height, int32_t unit)
{
    Dimension value(height, static_cast<DimensionUnit>(unit));
    ViewAbstractModel::GetInstance()->SetHeight(value);
    SwiperModel::GetInstance()->SetMainSwiperSizeHeight();
}

void FfiOHOSAceFrameworkSwiperSetSize(double width, int32_t widthUnit, double height, int32_t heightUnit)
{
    Dimension widthValue(width, static_cast<DimensionUnit>(widthUnit));
    Dimension heightValue(height, static_cast<DimensionUnit>(heightUnit));
    ViewAbstractModel::GetInstance()->SetWidth(widthValue);
    ViewAbstractModel::GetInstance()->SetHeight(heightValue);
}

void FfiOHOSAceFrameworkSwiperSetIndicatorStyle(CJIndicatorStyle value)
{
    Dimension leftValue(value.left, static_cast<DimensionUnit>(value.leftUnit));
    Dimension topValue(value.top, static_cast<DimensionUnit>(value.topUnit));
    Dimension rightValue(value.right, static_cast<DimensionUnit>(value.rightUnit));
    Dimension bottomValue(value.bottom, static_cast<DimensionUnit>(value.bottomUnit));
    Dimension sizeValue(value.size, static_cast<DimensionUnit>(value.sizeUnit));
    SwiperParameters swiperParameters { .dimLeft = leftValue,
        .dimTop = topValue,
        .dimRight = rightValue,
        .dimBottom = bottomValue,
        .maskValue = value.mask,
        .colorVal = Color(value.color),
        .selectedColorVal = Color(value.selectedColor) };
    SwiperModel::GetInstance()->SetIndicatorStyle(swiperParameters);
}

void FfiOHOSAceFrameworkSwiperSetItemSpace(double itemSpace, int32_t unit)
{
    Dimension value(itemSpace, static_cast<DimensionUnit>(unit));
    if (LessNotEqual(value.Value(), 0.0)) {
        value.SetValue(0.0);
    }
    SwiperModel::GetInstance()->SetItemSpace(value);
}

void FfiOHOSAceFrameworkSwiperSetDisplayMode(int32_t modeValue)
{
    if (!Utils::CheckParamsValid(modeValue, SWIPER_DISPLAY_MODES.size())) {
        LOGE("invalid value for swiper display mode");
        return;
    }
    SwiperModel::GetInstance()->SetDisplayMode(SWIPER_DISPLAY_MODES[modeValue]);
}

void FfiOHOSAceFrameworkSwiperSetEffectMode(int32_t modeValue)
{
    if (!Utils::CheckParamsValid(modeValue, EDGE_EFFECTS.size())) {
        LOGE("invalid value for effect mode");
        return;
    }
    SwiperModel::GetInstance()->SetEdgeEffect(EDGE_EFFECTS[modeValue]);
}

void FfiOHOSAceFrameworkSwiperSetDisplayCount(int32_t count)
{
    SwiperModel::GetInstance()->SetDisplayCount(count);
}

void FfiOHOSAceFrameworkSwiperSetCachedCount(int32_t cachedCount)
{
    SwiperModel::GetInstance()->SetCachedCount(cachedCount);
}

void FfiOHOSAceFrameworkSwiperSetEnabled(bool value)
{
    ViewAbstract::CjEnabled(value);
    SwiperModel::GetInstance()->SetEnabled(value);
}

void FfiOHOSAceFrameworkSwiperSetDisableSwipe(bool disable)
{
    SwiperModel::GetInstance()->SetDisableSwipe(disable);
}

void FfiOHOSAceFrameworkSwiperSetCurve(const char* curveStr)
{
    RefPtr<Curve> curve = CreateCurve(curveStr);
    SwiperModel::GetInstance()->SetCurve(curve);
}

void FfiOHOSAceFrameworkSwiperSetOnChange(void (*callback)(int32_t index))
{
    auto lambda = CJLambda::Create(callback);
    auto onChange = [lambda](const BaseEventInfo* info) {
        const auto* swiperInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
        if (!swiperInfo) {
            return;
        }
        lambda(swiperInfo->GetIndex());
    };
    SwiperModel::GetInstance()->SetOnChange(std::move(onChange));
}

int64_t FfiOHOSAceFrameworkSwiperControllerCtor()
{
    auto ret_ = FFIData::Create<NativeSwiperController>();
    if (ret_ == nullptr) {
        return FFI_ERROR_CODE;
    }
    return ret_->GetID();
}

void FfiOHOSAceFrameworkSwiperControllerShowNext(int64_t selfId)
{
    auto self_ = FFIData::GetData<NativeSwiperController>(selfId);
    if (self_ != nullptr) {
        self_->ShowNext();
    }
}

void FfiOHOSAceFrameworkSwiperControllerShowPrevious(int64_t selfId)
{
    auto self_ = FFIData::GetData<NativeSwiperController>(selfId);
    if (self_ != nullptr) {
        self_->ShowPrevious();
    }
}

void FfiOHOSAceFrameworkSwiperControllerFinishAnimation(int64_t selfId)
{
    auto self_ = FFIData::GetData<NativeSwiperController>(selfId);
    if (self_ != nullptr) {
        self_->FinishAnimation();
    }
}

void FfiOHOSAceFrameworkSwiperControllerFinishAnimationWithCallback(int64_t selfId, void (*callback)())
{
    auto self_ = FFIData::GetData<NativeSwiperController>(selfId);
    if (self_ != nullptr) {
        self_->FinishAnimationWithCallback(CJLambda::Create(callback));
    }
}

void FfiOHOSAceFrameworkSwiperSetIndicatorWithDot(CJDotIndicator value)
{
    SwiperParameters swiperParameters = GetDotIndicatorInfo(value);
    SwiperModel::GetInstance()->SetDotIndicatorStyle(swiperParameters);
    SwiperModel::GetInstance()->SetIndicatorType(SwiperIndicatorType::DOT);
}

void FfiOHOSAceFrameworkSwiperSetIndicatorWithDit(CJDigitIndicator value)
{
    SwiperDigitalParameters digitalParameters = GetDigitIndicatorInfo(value);
    SwiperModel::GetInstance()->SetDigitIndicatorStyle(digitalParameters);
    SwiperModel::GetInstance()->SetIndicatorType(SwiperIndicatorType::DIGIT);
}

void FfiOHOSAceFrameworkSwiperSetDisplayCountWithObj(CJSwiperAutoFill value, bool swipeByGroup)
{
    SwiperModel::GetInstance()->SetSwipeByGroup(swipeByGroup);
    CalcDimension minSizeValue(value.minSize, static_cast<DimensionUnit>(value.minSizeUnit));
    SwiperModel::GetInstance()->SetMinSize(minSizeValue);
}

void FfiOHOSAceFrameworkSwiperSetDisplayCountByGroup(int32_t count, bool swipeByGroup)
{
    SwiperModel::GetInstance()->SetSwipeByGroup(swipeByGroup);
    SwiperModel::GetInstance()->SetDisplayCount(count);
}

void FfiOHOSAceFrameworkSwiperSetDisplayArrowWithBool(bool value, bool isHoverShow)
{
    if (value) {
        auto pipelineContext = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        auto swiperIndicatorTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
        CHECK_NULL_VOID(swiperIndicatorTheme);
        SwiperArrowParameters swiperArrowParameters;
        swiperArrowParameters.isShowBackground = swiperIndicatorTheme->GetIsShowArrowBackground();
        swiperArrowParameters.isSidebarMiddle = swiperIndicatorTheme->GetIsSidebarMiddle();
        swiperArrowParameters.backgroundSize = swiperIndicatorTheme->GetSmallArrowBackgroundSize();
        swiperArrowParameters.backgroundColor = swiperIndicatorTheme->GetSmallArrowBackgroundColor();
        swiperArrowParameters.arrowSize = swiperIndicatorTheme->GetSmallArrowSize();
        swiperArrowParameters.arrowColor = swiperIndicatorTheme->GetSmallArrowColor();
        SwiperModel::GetInstance()->SetArrowStyle(swiperArrowParameters);
        SwiperModel::GetInstance()->SetDisplayArrow(true);
    } else {
        SwiperModel::GetInstance()->SetDisplayArrow(false);
        return;
    }
    SwiperModel::GetInstance()->SetHoverShow(isHoverShow);
}

void FfiOHOSAceFrameworkSwiperSetDisplayArrowWithObj(CJArrowStyle value, bool isHoverShow)
{
    SwiperArrowParameters swiperArrowParameters = GetArrowInfo(value);
    SwiperModel::GetInstance()->SetArrowStyle(swiperArrowParameters);
    SwiperModel::GetInstance()->SetDisplayArrow(true);
    SwiperModel::GetInstance()->SetHoverShow(isHoverShow);
}

void FfiOHOSAceFrameworkSwiperNextMargin(double value, int32_t unit, bool ignoreBlank)
{
    CalcDimension margin(value, static_cast<DimensionUnit>(unit));
    SwiperModel::GetInstance()->SetNextMargin(margin, ignoreBlank);
}

void FfiOHOSAceFrameworkSwiperPrevMargin(double value, int32_t unit, bool ignoreBlank)
{
    CalcDimension margin(value, static_cast<DimensionUnit>(unit));
    SwiperModel::GetInstance()->SetPreviousMargin(margin, ignoreBlank);
}

void FfiOHOSAceFrameworkSwiperNestedScroll(int32_t value)
{
    NestedScrollOptions nestedOpt = {
        .forward = NestedScrollMode::SELF_ONLY,
        .backward = NestedScrollMode::SELF_ONLY,
    };
    auto mode = static_cast<NestedScrollMode>(value);
    if (mode < NestedScrollMode::SELF_ONLY || mode > NestedScrollMode::SELF_FIRST) {
        SwiperModel::GetInstance()->SetNestedScroll(nestedOpt);
        return;
    }
    nestedOpt.forward = mode;
    nestedOpt.backward = mode;
    SwiperModel::GetInstance()->SetNestedScroll(nestedOpt);
}

void FfiOHOSAceFrameworkSwiperIndicatorInteractive(bool value)
{
    SwiperModel::GetInstance()->SetIndicatorInteractive(value);
}

void FfiOHOSAceFrameworkSwiperOnAnimationStart(
    void (*callback)(int32_t index, int32_t targetIndex, CJSwiperAnimationEvent event))
{
    auto lambda = CJLambda::Create(callback);
    auto targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onAnimationStart = [node = targetNode, lambda](
                                int32_t index, int32_t targetIndex, const AnimationCallbackInfo& info) {
        PipelineContext::SetCallBackNode(node);
        auto currentOffset = info.currentOffset.has_value() ? info.currentOffset.value() : 0.0;
        auto targetOffset = info.targetOffset.has_value() ? info.targetOffset.value() : 0.0;
        auto velocity = info.velocity.has_value() ? info.velocity.value() : 0.0;
        CJSwiperAnimationEvent event = {
            .currentOffset = currentOffset, .targetOffset = targetOffset, .velocity = velocity
        };
        lambda(index, targetIndex, event);
    };
    SwiperModel::GetInstance()->SetOnAnimationStart(std::move(onAnimationStart));
}

void FfiOHOSAceFrameworkSwiperOnAnimationEnd(void (*callback)(int32_t index, CJSwiperAnimationEvent event))
{
    auto lambda = CJLambda::Create(callback);
    auto targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onAnimationEnd = [node = targetNode, lambda](int32_t index, const AnimationCallbackInfo& info) {
        PipelineContext::SetCallBackNode(node);
        auto currentOffset = info.currentOffset.has_value() ? info.currentOffset.value() : 0.0;
        auto targetOffset = info.targetOffset.has_value() ? info.targetOffset.value() : 0.0;
        auto velocity = info.velocity.has_value() ? info.velocity.value() : 0.0;
        CJSwiperAnimationEvent event = {
            .currentOffset = currentOffset, .targetOffset = targetOffset, .velocity = velocity
        };
        lambda(index, event);
    };
    SwiperModel::GetInstance()->SetOnAnimationEnd(std::move(onAnimationEnd));
}

void FfiOHOSAceFrameworkSwiperOnGestureSwipe(void (*callback)(int32_t index, CJSwiperAnimationEvent event))
{
    auto lambda = CJLambda::Create(callback);
    auto targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onGestureSwipe = [node = targetNode, lambda](int32_t index, const AnimationCallbackInfo& info) {
        PipelineContext::SetCallBackNode(node);
        auto currentOffset = info.currentOffset.has_value() ? info.currentOffset.value() : 0.0;
        auto targetOffset = info.targetOffset.has_value() ? info.targetOffset.value() : 0.0;
        auto velocity = info.velocity.has_value() ? info.velocity.value() : 0.0;
        CJSwiperAnimationEvent event = {
            .currentOffset = currentOffset, .targetOffset = targetOffset, .velocity = velocity
        };
        lambda(index, event);
    };
    SwiperModel::GetInstance()->SetOnGestureSwipe(std::move(onGestureSwipe));
}

void FfiOHOSAceFrameworkSwiperOnContentDidScroll(
    void (*callback)(int32_t selectedIndex, int32_t index, float position, float mainAxisLength))
{
    auto lambda = CJLambda::Create(callback);
    auto onContentDidScroll = [lambda](int32_t selectedIndex, int32_t index, float position, float mainAxisLength) {
        lambda(selectedIndex, index, position, mainAxisLength);
    };
    SwiperModel::GetInstance()->SetOnContentDidScroll(std::move(onContentDidScroll));
}

void FfiOHOSAceFrameworkSwiperCustomContentTransition(
    int32_t timeout, void (*callback)(CJSwiperContentTransitionProxy proxy))
{
    SwiperContentAnimatedTransition transitionInfo;
    transitionInfo.timeout = timeout < 0 ? DEFAULT_CUSTOM_ANIMATION_TIMEOUT : timeout;
    auto lambda = CJLambda::Create(callback);
    auto onTransition = [lambda](const RefPtr<SwiperContentTransitionProxy>& proxy) {
        auto finishTransitionLambda = [](void* cjProxy) {
            auto realProxy = static_cast<SwiperContentTransitionProxy*>(cjProxy);
            realProxy->FinishTransition();
        };
        CJSwiperContentTransitionProxy swiperProxy = { .selectedIndex = proxy->GetSelectedIndex(),
            .index = proxy->GetIndex(),
            .position = proxy->GetPosition(),
            .mainAxisLength = proxy->GetMainAxisLength(),
            .proxy = reinterpret_cast<void*>(proxy.GetRawPtr()),
            .finishTransition = finishTransitionLambda };
        lambda(swiperProxy);
    };
    transitionInfo.transition = std::move(onTransition);
    SwiperModel::GetInstance()->SetCustomContentTransition(transitionInfo);
}

void FfiOHOSAceFrameworkSwiperControllerChangeIndex(int32_t index, bool useAnimation, int64_t id)
{
    auto self_ = FFIData::GetData<NativeSwiperController>(id);
    if (self_ != nullptr) {
        self_->ChangeIndex(index, useAnimation);
    }
}
}
