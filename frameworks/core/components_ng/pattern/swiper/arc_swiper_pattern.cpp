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

#include "core/components_ng/pattern/swiper/arc_swiper_pattern.h"

#include "base/perfmonitor/perf_constants.h"
#include "base/perfmonitor/perf_monitor.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/swiper_indicator_pattern.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float HORIZONTAL_EXIT_SCALE_FINAL_VALUE = 0.6f;
constexpr int32_t HORIZONTAL_EXIT_SCALE_DURATION = 750;
constexpr int32_t HORIZONTAL_EXIT_OFFSET_DURATION = 750;
constexpr int32_t HORIZONTAL_EXIT_BLUR_VALUE = 30;
constexpr int32_t HORIZONTAL_EXIT_BLUR_DELAY = 150;
constexpr int32_t HORIZONTAL_EXIT_BLUR_DURATION = 250;
constexpr int32_t HORIZONTAL_EXIT_ALPHA_DURATION = 750;

constexpr float HORIZONTAL_ENTRY_SCALE_INITIAL_VALUE = 0.6f;
constexpr int32_t HORIZONTAL_ENTRY_SCALE_DURATION = 750;
constexpr int32_t HORIZONTAL_ENTRY_OFFSET_DURATION = 750;
constexpr int32_t HORIZONTAL_ENTRY_BLUR_VALUE = 30;
constexpr int32_t HORIZONTAL_ENTRY_BLUR_DURATION = 250;
constexpr int32_t HORIZONTAL_ENTRY_ALPHA_DURATION = 500;

constexpr float VERTICAL_EXIT_SCALE_VALUE = 0.95f;
constexpr int32_t VERTICAL_EXIT_SCALE_DURATION = 330;
constexpr int32_t VERTICAL_EXIT_OFFSET_DURATION = 330;
constexpr int32_t VERTICAL_EXIT_BLUR_INITIAL_VALUE = 70;
constexpr int32_t VERTICAL_EXIT_BLUR_VALUE = 100;
constexpr int32_t VERTICAL_EXIT_BLUR_DURATION = 330;
constexpr int32_t VERTICAL_EXIT_ALPHA_DURATION = 200;

constexpr float VERTICAL_ENTRY_SCALE_VALUE = 101.5f / 100.0f;
constexpr int32_t VERTICAL_ENTRY_SCALE_DELAY = 130;
constexpr int32_t VERTICAL_ENTRY_SCALE_DURATION = 200;
constexpr int32_t VERTICAL_ENTRY_OFFSET_DELAY = 130;
constexpr int32_t VERTICAL_ENTRY_OFFSET_DURATION = 200;
constexpr int32_t VERTICAL_ENTRY_ALPHA_DELAY = 130;
constexpr int32_t VERTICAL_ENTRY_ALPHA_DURATION = 200;
constexpr int32_t VERTICAL_ENTRY_COLOR_DURATION = 40;

constexpr float HORIZONTAL_SCALE_REDUCTION_FACTOR = 0.4f;
constexpr float HORIZONTAL_BLUR_MIN_RATIO = 0.2f;
constexpr float HORIZONTAL_BLUR_REDUCTION_FACTOR = 750.0f / 250.0f * 30.0f;
constexpr float HORIZONTAL_BLUR_MAX_VALUE = 30.0f;
constexpr float HORIZONTAL_ALPHA_REDUCTION_FACTOR = 750.0f / 500.0f;

constexpr float VERTICAL_EXIT_SCALE_REDUCTION_FACTOR = 0.05f;
constexpr float VERTICAL_EXIT_SCALE_MIN_VALUE = 0.95f;
constexpr float VERTICAL_EXIT_BLUR_INCREASE_FACTOR = 30.0f;
constexpr float VERTICAL_EXIT_BLUR_MAX_VALUE = 100.0f;
constexpr float VERTICAL_EXIT_ALPHA_MIN_RATIO = 0.25f;
constexpr float VERTICAL_EXIT_ALPHA_REDUCTION_FACTOR = 2.32f;
constexpr float VERTICAL_EXIT_ALPHA_AT_CRITICAL_POINT = 0.42f;
constexpr float VERTICAL_EXIT_ALPHA_REDUCTION_FACTOR_AFTER_CRITICAL_POINT = 0.63f;

constexpr float VERTICAL_ENTRY_CRITICAL_POINT_OF_COLOR = 0.25f;
constexpr float VERTICAL_ENTRY_CRITICAL_POINT_OF_OTHER = 130.0f / 330.0f;
constexpr float VERTICAL_ENTRY_SCALE_INITIAL_VALUE = 1.015f;
constexpr float VERTICAL_ENTRY_SCALE_REDUCTION_FACTOR = 0.015f;
constexpr float VERTICAL_ENTRY_WHOLE_REDUCTION_FACTOR = 330.0f / 200.0f;
constexpr float DEFAULT_MINIMUM_AMPLITUDE_PX = 1.0f;
constexpr int32_t HALF = 2;
constexpr int32_t ANIMATION_SIZE = 8;
constexpr int32_t NO_ANIMAION_DEFAULT_DURATION = 400;
constexpr int32_t VERTICAL_ANIMAION_DEFAULT_DURATION = 330;
constexpr int32_t HORIZONTAL_ANIMAION_DEFAULT_DURATION = 750;
#ifdef SUPPORT_DIGITAL_CROWN
constexpr int32_t MIN_TURN_PAGE_VELOCITY = 1200;
constexpr int32_t NEW_MIN_TURN_PAGE_VELOCITY = 780;
#endif
} // namespace name
void ArcSwiperPattern::SaveCircleDotIndicatorProperty(const RefPtr<FrameNode>& indicatorNode)
{
    CHECK_NULL_VOID(indicatorNode);
    auto indicatorPattern = indicatorNode->GetPattern<SwiperIndicatorPattern>();
    CHECK_NULL_VOID(indicatorPattern);
    auto layoutProperty = indicatorNode->GetLayoutProperty<SwiperIndicatorLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto paintProperty = indicatorNode->GetPaintProperty<CircleDotIndicatorPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto pipelineContext = GetHost()->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto swiperIndicatorTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_VOID(swiperIndicatorTheme);
    auto swiperParameters = GetSwiperArcDotParameters();
    CHECK_NULL_VOID(swiperParameters);
    layoutProperty->ResetIndicatorLayoutStyle();
    paintProperty->UpdateArcDirection(swiperParameters->arcDirection.value_or(SwiperArcDirection::SIX_CLOCK_DIRECTION));
    paintProperty->UpdateColor(swiperParameters->itemColor.value_or(swiperIndicatorTheme->GetArcItemColor()));
    paintProperty->UpdateSelectedColor(
        swiperParameters->selectedItemColor.value_or(swiperIndicatorTheme->GetArcSelectedItemColor()));
    paintProperty->UpdateContainerColor(
        swiperParameters->containerColor.value_or(swiperIndicatorTheme->GetArcContainerColor()));
    paintProperty->UpdateMaskColor(swiperParameters->maskColor.value_or(swiperIndicatorTheme->GetArcMaskColor()));
    MarkDirtyNodeSelf();
    indicatorNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void ArcSwiperPattern::SetSwiperArcDotParameters(const SwiperArcDotParameters& swiperArcDotParameters)
{
    swiperArcDotParameters_ = std::make_shared<SwiperArcDotParameters>(swiperArcDotParameters);
}

std::string ArcSwiperPattern::GetArcDotIndicatorStyle() const
{
    auto swiperParameters = GetSwiperArcDotParameters();
    CHECK_NULL_RETURN(swiperParameters, "");
    auto jsonValue = JsonUtil::Create(true);
    auto pipelineContext = GetHost()->GetContext();
    CHECK_NULL_RETURN(pipelineContext, "");
    auto swiperIndicatorTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_RETURN(swiperIndicatorTheme, "");

    static const char* ARC_DIRECTION[] = { "ArcDirection.THREE_CLOCK_DIRECTION", "ArcDirection.SIX_CLOCK_DIRECTION",
        "ArcDirection.NINE_CLOCK_DIRECTION" };
    jsonValue->Put("arcDirection", ARC_DIRECTION[static_cast<int32_t>(swiperParameters->arcDirection.value_or(
        SwiperArcDirection::SIX_CLOCK_DIRECTION))]);
    jsonValue->Put("itemColor",
        swiperParameters->itemColor.value_or(swiperIndicatorTheme->GetArcItemColor()).ColorToString().c_str());
    jsonValue->Put("selectedItemColor",
        swiperParameters->selectedItemColor.value_or(swiperIndicatorTheme->GetArcSelectedItemColor())
            .ColorToString()
            .c_str());
    jsonValue->Put(
        "backgroundColor", swiperParameters->containerColor.value_or(swiperIndicatorTheme->GetArcContainerColor())
            .ColorToString()
            .c_str());
    jsonValue->Put("maskColor",
        GradientToJson(swiperParameters->maskColor.value_or(swiperIndicatorTheme->GetArcMaskColor())).c_str());

    return jsonValue->ToString();
}

std::shared_ptr<SwiperArcDotParameters> ArcSwiperPattern::GetSwiperArcDotParameters() const
{
    if (swiperArcDotParameters_ == nullptr) {
        swiperArcDotParameters_ = std::make_shared<SwiperArcDotParameters>();
        auto pipelineContext = GetHost()->GetContext();
        CHECK_NULL_RETURN(pipelineContext, swiperArcDotParameters_);
        auto swiperIndicatorTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();

        swiperArcDotParameters_->arcDirection = SwiperArcDirection::SIX_CLOCK_DIRECTION;
        swiperArcDotParameters_->itemColor = swiperIndicatorTheme->GetArcItemColor();
        swiperArcDotParameters_->selectedItemColor = swiperIndicatorTheme->GetArcSelectedItemColor();
        swiperArcDotParameters_->containerColor = swiperIndicatorTheme->GetArcContainerColor();
        swiperArcDotParameters_->maskColor = swiperIndicatorTheme->GetArcMaskColor();
    }
    return swiperArcDotParameters_;
}

std::string ArcSwiperPattern::GradientToJson(Gradient colors) const
{
    auto jsonArray = JsonUtil::CreateArray(true);
    for (size_t index = 0; index < colors.GetColors().size(); ++index) {
        auto gradientColor = colors.GetColors()[index];
        auto gradientColorJson = JsonUtil::Create(true);
        gradientColorJson->Put("color", gradientColor.GetLinearColor().ToColor().ColorToString().c_str());
        gradientColorJson->Put("offset", std::to_string(gradientColor.GetDimension().Value()).c_str());
        jsonArray->Put(std::to_string(index).c_str(), gradientColorJson);
    }
    return jsonArray->ToString();
}

void ArcSwiperPattern::SetDisableTransitionAnimation(bool isDisable)
{
    disableTransitionAnimation_ = isDisable;
}

bool ArcSwiperPattern::IsDisableTransitionAnimation() const
{
    return disableTransitionAnimation_;
}

void ArcSwiperPattern::PlayHorizontalAnimation(const OffsetF& offset, int32_t index, const RefPtr<FrameNode>& frameNode)
{
    if (IsPreItem(index, offset.GetX())) {
        PlayHorizontalExitAnimation(offset, frameNode);
    } else {
        PlayHorizontalEntryAnimation(offset, frameNode);
    }
}

void ArcSwiperPattern::PlayVerticalAnimation(const OffsetF& offset, int32_t index, const RefPtr<FrameNode>& frameNode)
{
    if (IsPreItem(index, offset.GetY())) {
        PlayVerticalExitAnimation(offset, frameNode);
    } else {
        PlayVerticalEntryAnimation(offset, frameNode);
    }
}

bool ArcSwiperPattern::IsPreItem(int32_t index, float translate)
{
    if (translate < 0) {
        if (index < itemPosition_.size() / HALF) {
            return true;
        } else {
            return false;
        }
    } else {
        if (index < itemPosition_.size() / HALF) {
            return false;
        } else {
            return true;
        }
    }
}

void ArcSwiperPattern::BuildAnimationFinishCallback(bool exit, AnimationParam& param,
    const RefPtr<RenderContext>& renderContext, FinishCallback& finishCallback)
{
    BlurOption blurOption;
    finishCallback = [weak = WeakClaim(this), param, blurOption,
        weakRenderContext = WeakPtr<RenderContext>(renderContext), exit]() {
        auto swiper = weak.Upgrade();
        CHECK_NULL_VOID(swiper);
        auto renderContext = weakRenderContext.Upgrade();
        CHECK_NULL_VOID(renderContext);
        if (param.type == AnimationType::TYPE_SCALE) {
            renderContext->UpdateTransformScale({ 1.0f, 1.0f });
            if (exit) {
                swiper->AddFinishAnimation(AnimationFinishType::EXIT_SCALE);
            } else {
                swiper->AddFinishAnimation(AnimationFinishType::ENTRY_SCALE);
            }
        } else if (param.type == AnimationType::TYPE_ALPHA) {
            renderContext->UpdateOpacity(1.0f);
            if (exit) {
                swiper->AddFinishAnimation(AnimationFinishType::EXIT_ALPHA);
            } else {
                swiper->AddFinishAnimation(AnimationFinishType::ENTRY_ALPHA);
            }
        } else if (param.type == AnimationType::TYPE_BLUR) {
            renderContext->UpdateBackBlur(Dimension(0.0f,  DimensionUnit::PERCENT), blurOption);
            if (exit) {
                swiper->AddFinishAnimation(AnimationFinishType::EXIT_BLUR);
            } else {
                swiper->AddFinishAnimation(AnimationFinishType::ENTRY_BLUR);
            }
        } else if (param.type == AnimationType::TYPE_OFFSET) {
            if (exit) {
                swiper->AddFinishAnimation(AnimationFinishType::EXIT_OFFSET);
            } else {
                swiper->AddFinishAnimation(AnimationFinishType::ENTRY_OFFSET);
            }
        } else if (param.type == AnimationType::TYPE_COLOR) {
            auto colorPtr = swiper->GetBackgroundColorValue(param.frameNode);
            if (colorPtr) {
                renderContext->OnBackgroundColorUpdate(*colorPtr);
            }
            if (exit) {
                swiper->AddFinishAnimation(AnimationFinishType::EXIT_BACKGROUND);
            } else {
                swiper->AddFinishAnimation(AnimationFinishType::ENTRY_BACKGROUND);
            }
        }
    };
}

std::shared_ptr<AnimationUtils::Animation> ArcSwiperPattern::Animation(bool exit, AnimationParam& param)
{
    auto frameNode = param.frameNode;
    BlurOption blurOption;
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, nullptr);
    FinishCallback finishCallback;
    BuildAnimationFinishCallback(exit, param, renderContext, finishCallback);
    auto propertyCallback = [param, blurOption, weakRenderContext = WeakPtr<RenderContext>(renderContext),
        weakFrameNode = WeakPtr<FrameNode>(frameNode)]() {
        auto renderContext = weakRenderContext.Upgrade();
        CHECK_NULL_VOID(renderContext);
        auto frameNode = weakFrameNode.Upgrade();
        CHECK_NULL_VOID(frameNode);
        if (param.type == AnimationType::TYPE_SCALE) {
            renderContext->UpdateTransformScale({param.scaleValue, param.scaleValue});
        } else if (param.type == AnimationType::TYPE_ALPHA) {
            renderContext->UpdateOpacity(param.opacityValue);
        } else if (param.type == AnimationType::TYPE_BLUR) {
            renderContext->UpdateBackBlur(Dimension(param.blurValue, DimensionUnit::PERCENT), blurOption);
        } else if (param.type == AnimationType::TYPE_COLOR) {
            auto parentNode = frameNode->GetParentFrameNode();
            CHECK_NULL_VOID(parentNode);
            auto context = parentNode->GetRenderContext();
            CHECK_NULL_VOID(context);
            context->OnBackgroundColorUpdate(param.backColor);
        } else if (param.type == AnimationType::TYPE_OFFSET) {
            renderContext->UpdateTranslateInXY(param.offset);
        }
    };
    return AnimationUtils::StartAnimation(param.option, propertyCallback, finishCallback);
}

void ArcSwiperPattern::PlayHorizontalExitAnimation(const OffsetF& offset, const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);

    // scale
    renderContext->UpdateTransformScale({ horizontalExitNodeScale_, horizontalExitNodeScale_ });
    AnimationParam scaleParam;
    scaleParam.type = AnimationType::TYPE_SCALE;
    scaleParam.frameNode = frameNode;
    scaleParam.scaleValue = HORIZONTAL_EXIT_SCALE_FINAL_VALUE;

    AnimationOption scaleOption;
    scaleOption.SetDuration(CalcTime(HORIZONTAL_EXIT_SCALE_DURATION));
    scaleOption.SetCurve(Curves::FRICTION);
    scaleParam.option = scaleOption;
    animationVector_.push_back(Animation(true, scaleParam));

    // offset
    AnimationParam offsetParam;
    offsetParam.type = AnimationType::TYPE_OFFSET;
    offsetParam.frameNode = frameNode;
    offsetParam.offset = offset;

    AnimationOption offsetOption;
    offsetOption.SetDuration(CalcTime(HORIZONTAL_EXIT_OFFSET_DURATION));
    offsetOption.SetCurve(Curves::FRICTION);
    ElementRegister::GetInstance()->ReSyncGeometryTransition(GetHost(), offsetOption);
    offsetParam.option = offsetOption;
    animationVector_.push_back(Animation(true, offsetParam));

    // blur
    BlurOption blurOption;
    renderContext->UpdateBackBlur(Dimension(horizontalExitNodeBlur_, DimensionUnit::PERCENT), blurOption);
    AnimationParam blurParam;
    blurParam.type = AnimationType::TYPE_BLUR;
    blurParam.frameNode = frameNode;
    blurParam.blurValue = HORIZONTAL_EXIT_BLUR_VALUE;

    AnimationOption blurAnimationOption;
    blurAnimationOption.SetDelay(CalcTime(HORIZONTAL_EXIT_BLUR_DELAY));
    blurAnimationOption.SetDuration(CalcTime(HORIZONTAL_EXIT_BLUR_DURATION));
    blurAnimationOption.SetCurve(Curves::LINEAR);
    blurParam.option = blurAnimationOption;
    animationVector_.push_back(Animation(true, blurParam));

    // alpha
    renderContext->UpdateOpacity(horizontalExitNodeOpacity_);
    AnimationParam alphaParam;
    alphaParam.type = AnimationType::TYPE_ALPHA;
    alphaParam.frameNode = frameNode;
    alphaParam.opacityValue = 0.0f;

    AnimationOption alphaOption;
    alphaOption.SetDuration(CalcTime(HORIZONTAL_EXIT_ALPHA_DURATION));
    alphaOption.SetCurve(Curves::LINEAR);
    alphaParam.option = alphaOption;
    animationVector_.push_back(Animation(true, alphaParam));
}

void ArcSwiperPattern::PlayHorizontalEntryAnimation(const OffsetF& offset, const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);

    // scale
    renderContext->UpdateTransformScale(
        {horizontalEntryNodeScale_, horizontalEntryNodeScale_});
    AnimationParam scaleParam;
    scaleParam.type = AnimationType::TYPE_SCALE;
    scaleParam.frameNode = frameNode;
    scaleParam.scaleValue = 1.0f;

    AnimationOption scaleOption;
    scaleOption.SetDuration(CalcTime(HORIZONTAL_ENTRY_SCALE_DURATION));
    scaleOption.SetCurve(Curves::FRICTION);
    scaleParam.option = scaleOption;
    animationVector_.push_back(Animation(false, scaleParam));

    // offset
    AnimationParam offsetParam;
    offsetParam.type = AnimationType::TYPE_OFFSET;
    offsetParam.frameNode = frameNode;
    offsetParam.offset = offset;

    AnimationOption offsetOption;
    offsetOption.SetDuration(CalcTime(HORIZONTAL_ENTRY_OFFSET_DURATION));
    offsetOption.SetCurve(Curves::FRICTION);
    ElementRegister::GetInstance()->ReSyncGeometryTransition(GetHost(), offsetOption);
    offsetParam.option = offsetOption;
    animationVector_.push_back(Animation(false, offsetParam));

    // blur
    BlurOption blurOption;
    renderContext->UpdateBackBlur(Dimension(horizontalEntryNodeBlur_, DimensionUnit::PERCENT), blurOption);
    AnimationParam blurParam;
    blurParam.type = AnimationType::TYPE_BLUR;
    blurParam.frameNode = frameNode;
    blurParam.blurValue = 0.0f;

    AnimationOption blurAnimationOption;
    blurAnimationOption.SetDuration(CalcTime(HORIZONTAL_ENTRY_BLUR_DURATION));
    blurAnimationOption.SetCurve(Curves::LINEAR);
    blurParam.option = blurAnimationOption;
    animationVector_.push_back(Animation(false, blurParam));

    // alpha
    renderContext->UpdateOpacity(horizontalEntryNodeOpacity_);
    AnimationParam alphaParam;
    alphaParam.type = AnimationType::TYPE_ALPHA;
    alphaParam.frameNode = frameNode;
    alphaParam.opacityValue = 1.0f;

    AnimationOption alphaOption;
    alphaOption.SetDuration(CalcTime(HORIZONTAL_ENTRY_ALPHA_DURATION));
    alphaOption.SetCurve(Curves::LINEAR);
    alphaParam.option = alphaOption;
    animationVector_.push_back(Animation(false, alphaParam));
}

std::shared_ptr<Color> ArcSwiperPattern::GetBackgroundColorValue(const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto context = frameNode->GetRenderContext();
    CHECK_NULL_RETURN(context, nullptr);
    auto color = context->GetBackgroundColor();
    CHECK_NULL_RETURN(color, nullptr);
    return std::make_shared<Color>(color.value());
}

void ArcSwiperPattern::PlayVerticalExitAnimation(const OffsetF& offset, const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);

    // scale
    renderContext->UpdateTransformScale({ verticalExitNodeScale_, verticalExitNodeScale_ });
    AnimationParam scaleParam;
    scaleParam.type = AnimationType::TYPE_SCALE;
    scaleParam.frameNode = frameNode;
    scaleParam.scaleValue = VERTICAL_EXIT_SCALE_VALUE;

    AnimationOption scaleOption;
    scaleOption.SetDuration(CalcTime(VERTICAL_EXIT_SCALE_DURATION));
    scaleOption.SetCurve(Curves::FRICTION);
    scaleParam.option = scaleOption;
    animationVector_.push_back(Animation(true, scaleParam));

    // offset
    AnimationParam offsetParam;
    offsetParam.type = AnimationType::TYPE_OFFSET;
    offsetParam.frameNode = frameNode;
    offsetParam.offset = offset;

    AnimationOption offsetOption;
    offsetOption.SetDuration(CalcTime(VERTICAL_EXIT_OFFSET_DURATION));
    offsetOption.SetCurve(Curves::FRICTION);
    ElementRegister::GetInstance()->ReSyncGeometryTransition(GetHost(), offsetOption);
    offsetParam.option = offsetOption;
    animationVector_.push_back(Animation(true, offsetParam));

    // blur
    BlurOption blurOption;
    renderContext->UpdateBackBlur(Dimension(verticalExitNodeBlur_, DimensionUnit::PERCENT),
        blurOption);
    AnimationParam blurParam;
    blurParam.type = AnimationType::TYPE_BLUR;
    blurParam.frameNode = frameNode;
    blurParam.blurValue = VERTICAL_EXIT_BLUR_VALUE;

    AnimationOption blurAnimationOption;
    blurAnimationOption.SetDuration(CalcTime(VERTICAL_EXIT_BLUR_DURATION));
    blurAnimationOption.SetCurve(Curves::LINEAR);
    blurParam.option = blurAnimationOption;
    animationVector_.push_back(Animation(true, blurParam));

    // alpha
    renderContext->UpdateOpacity(verticalExitNodeOpacity_);
    AnimationParam alphaParam;
    alphaParam.type = AnimationType::TYPE_ALPHA;
    alphaParam.frameNode = frameNode;
    alphaParam.opacityValue = 0.0f;

    AnimationOption alphaOption;
    alphaOption.SetDuration(CalcTime(VERTICAL_EXIT_ALPHA_DURATION));
    alphaOption.SetCurve(Curves::LINEAR);
    alphaParam.option = alphaOption;
    animationVector_.push_back(Animation(true, alphaParam));

    // color
    renderContext->OnBackgroundColorUpdate(Color::TRANSPARENT);
}

void ArcSwiperPattern::GetEntryNodeBackgroundColor(const RefPtr<FrameNode>& frameNode, std::shared_ptr<Color>& colorPtr)
{
    // color
    CHECK_NULL_VOID(frameNode);
    colorPtr = GetBackgroundColorValue(frameNode);
    if (!colorPtr || *colorPtr == Color::TRANSPARENT) {
        colorPtr = parentNodeBackgroundColor_;
    }
    if (colorPtr == nullptr) {
        colorPtr = std::make_shared<Color>(Color::TRANSPARENT);
    }
}

void ArcSwiperPattern::PlayVerticalEntryAnimation(const OffsetF& offset, const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    // color
    frameNode->GetRenderContext()->OnBackgroundColorUpdate(Color::TRANSPARENT);

    // scale
    renderContext->UpdateTransformScale({ verticalEntryNodeScale_, verticalEntryNodeScale_ });
    AnimationParam scaleParam;
    scaleParam.type = AnimationType::TYPE_SCALE;
    scaleParam.frameNode = frameNode;
    scaleParam.scaleValue = 1.0f;

    AnimationOption scaleOption;
    scaleOption.SetDelay(CalcTime(VERTICAL_ENTRY_SCALE_DELAY));
    scaleOption.SetDuration(CalcTime(VERTICAL_ENTRY_SCALE_DURATION));
    scaleOption.SetCurve(Curves::FRICTION);
    scaleParam.option = scaleOption;
    animationVector_.push_back(Animation(false, scaleParam));

    // offset
    AnimationParam offsetParam;
    offsetParam.type = AnimationType::TYPE_OFFSET;
    offsetParam.frameNode = frameNode;
    offsetParam.offset = offset;

    AnimationOption offsetOption;
    offsetOption.SetDelay(CalcTime(VERTICAL_ENTRY_OFFSET_DELAY));
    offsetOption.SetDuration(CalcTime(VERTICAL_ENTRY_OFFSET_DURATION));
    offsetOption.SetCurve(Curves::FRICTION);
    ElementRegister::GetInstance()->ReSyncGeometryTransition(GetHost(), offsetOption);
    offsetParam.option = offsetOption;
    animationVector_.push_back(Animation(false, offsetParam));

    // alpha
    renderContext->UpdateOpacity(verticalEntryNodeOpacity_);
    AnimationParam alphaParam;
    alphaParam.type = AnimationType::TYPE_ALPHA;
    alphaParam.frameNode = frameNode;
    alphaParam.opacityValue = 1.0f;

    AnimationOption alphaOption;
    alphaOption.SetDelay(CalcTime(VERTICAL_ENTRY_ALPHA_DELAY));
    alphaOption.SetDuration(CalcTime(VERTICAL_ENTRY_ALPHA_DURATION));
    alphaOption.SetCurve(Curves::LINEAR);
    alphaParam.option = alphaOption;
    animationVector_.push_back(Animation(false, alphaParam));

    // color
    GetEntryNodeBackgroundColor(frameNode, entryNodeBackgroundColor_);
    CHECK_NULL_VOID(entryNodeBackgroundColor_);
    AnimationParam colorParam;
    colorParam.type = AnimationType::TYPE_COLOR;

    colorParam.frameNode = frameNode;
    colorParam.backColor = *entryNodeBackgroundColor_;

    AnimationOption colorOption;
    colorOption.SetDuration(CalcTime(VERTICAL_ENTRY_COLOR_DURATION));
    colorOption.SetCurve(Curves::LINEAR);
    colorParam.option = colorOption;
    animationVector_.push_back(Animation(false, colorParam));
}

bool ArcSwiperPattern::IsScrollOverCritical()
{
    if (targetIndex_.value() == currentIndex_) {
        return false;
    }
    return true;
}

void ArcSwiperPattern::PlayAnimation(const OffsetF& offset, int32_t index, const RefPtr<FrameNode>& frameNode)
{
    PerfMonitor::GetPerfMonitor()->Start(PerfConstants::APP_SWIPER_FLING, PerfActionType::FIRST_MOVE, "");
    if (IsScrollOverCritical()) {
        if (GetDirection() == Axis::HORIZONTAL) {
            PlayHorizontalAnimation(offset, index, frameNode);
        } else {
            PlayVerticalAnimation(offset, index, frameNode);
        }
    } else {
        InitialFrameNodePropertyAnimation(offset, frameNode, true);
    }
}

void ArcSwiperPattern::ClearAnimationFinishList()
{
    animationFinishList_.clear();
}

void ArcSwiperPattern::AnimationFinish()
{
    if (!hasTabsAncestor_) {
        PerfMonitor::GetPerfMonitor()->End(PerfConstants::APP_SWIPER_FLING, true);
    }
    OffsetF finalOffset = itemPosition_.empty() ? OffsetF()
        : itemPosition_.begin()->second.node
            ? itemPosition_.begin()->second.node->GetRenderContext()->GetTranslateXYProperty()
            : OffsetF();
    TAG_LOGI(AceLogTag::ACE_SWIPER,
        "ArcSwiper finish property translate animation with offsetX: %{public}f, offsetY: %{public}f",
        finalOffset.GetX(), finalOffset.GetY());
    ACE_SCOPED_TRACE("ArcSwiper finish property animation X: %f, Y: %f", finalOffset.GetX(), finalOffset.GetY());
    targetIndex_.reset();
    OnPropertyTranslateAnimationFinish(offset_);
}

void ArcSwiperPattern::PlayPropertyTranslateFlipAnimation(const OffsetF& offset)
{
    offset_ = offset;
    int32_t index = 0;
    if (!hasTabsAncestor_) {
        PerfMonitor::GetPerfMonitor()->Start(PerfConstants::APP_SWIPER_FLING, PerfActionType::FIRST_MOVE, "");
    }
    for (auto &item : itemPosition_) {
        auto frameNode = item.second.node;
        if (frameNode) {
            PlayAnimation(offset, index, frameNode);
            index++;
            item.second.finalOffset = offset;
        }
    }
    itemPositionInAnimation_ = itemPosition_;
}

void ArcSwiperPattern::InitialFrameNodePropertyAnimation(const OffsetF& offset, const RefPtr<FrameNode>& frameNode,
    bool cancel)
{
    CHECK_NULL_VOID(frameNode);
    for (auto animaiton: animationVector_) {
        AnimationUtils::StopAnimation(animaiton);
    }
    AnimationOption option;
    option.SetCurve(Curves::LINEAR);
    option.SetDuration(0);
    auto upgradeCallback = [weak = WeakClaim(this), weakFrameNode = WeakPtr<FrameNode>(frameNode), offset]() {
        auto swiper = weak.Upgrade();
        CHECK_NULL_VOID(swiper);
        auto frameNode = weakFrameNode.Upgrade();
        CHECK_NULL_VOID(frameNode);
        frameNode->GetRenderContext()->UpdateOpacity(1.0f);
        frameNode->GetRenderContext()->UpdateTransformScale({1.0f, 1.0f});
        BlurOption blurOption;
        frameNode->GetRenderContext()->UpdateBackBlur(Dimension(0.0f, DimensionUnit::PERCENT), blurOption);
        frameNode->GetRenderContext()->UpdateTranslateInXY(offset);
        auto colorPtr = swiper->GetBackgroundColorValue(frameNode);
        CHECK_NULL_VOID(colorPtr);
        frameNode->GetRenderContext()->OnBackgroundColorUpdate(*colorPtr);
    };
    auto finishCallback = [weak = WeakClaim(this), weakFrameNode = WeakPtr<FrameNode>(frameNode), offset, cancel]() {
        if (cancel) {
            auto swiper = weak.Upgrade();
            CHECK_NULL_VOID(swiper);
            swiper->OnPropertyTranslateAnimationFinish(offset);
        }
    };
    AnimationUtils::Animate(option, upgradeCallback, finishCallback);
}

void ArcSwiperPattern::CancelFrameNodePropertyAnimation(const RefPtr<RenderContext>& context)
{
    CHECK_NULL_VOID(context);
    for (auto animaiton: animationVector_) {
        AnimationUtils::StopAnimation(animaiton);
    }
    animationVector_.clear();
    context->UpdateOpacity(1.0f);
    context->UpdateTransformScale({1.0f, 1.0f});
    BlurOption blurOption;
    context->UpdateBackBlur(Dimension(0.0f, DimensionUnit::PERCENT), blurOption);
    context->CancelTranslateXYAnimation();
}

void ArcSwiperPattern::AddFinishAnimation(const AnimationFinishType& animationFinishType)
{
    animationFinishList_.push_back(animationFinishType);
    if (animationFinishList_.size() == ANIMATION_SIZE) {
        AnimationFinish();
    }
}

void ArcSwiperPattern::HandlePropertyTranslateCallback(float translate, int32_t nextIndex, float velocity)
{
    AnimationCallbackInfo info;
    info.velocity = Dimension(velocity, DimensionUnit::PX).ConvertToVp();
    info.currentOffset = GetCustomPropertyOffset() +
        Dimension(currentIndexOffset_, DimensionUnit::PX).ConvertToVp();
    info.targetOffset = GetCustomPropertyTargetOffset() - Dimension(translate, DimensionUnit::PX).ConvertToVp();
    if (IsHorizontalAndRightToLeft()) {
        info.currentOffset = GetCustomPropertyOffset() +
            Dimension(-currentIndexOffset_, DimensionUnit::PX).ConvertToVp();
    }

    auto pipeline = PipelineContext::GetCurrentContext();
    if (pipeline) {
        pipeline->AddAfterRenderTask([weak = WeakClaim(this), info, nextIndex = GetLoopIndex(nextIndex)]() {
            auto swiper = weak.Upgrade();
            CHECK_NULL_VOID(swiper);
            swiper->FireAnimationStartEvent(swiper->GetLoopIndex(swiper->currentIndex_), nextIndex, info);
            swiper->FireAndCleanScrollingListener();
        });
    }
}

void ArcSwiperPattern::BuildDefaultTranslateAnimationOption(AnimationOption& option, float translate)
{
    option.SetDuration(GetDuration());
    auto iter = frameRateRange_.find(SwiperDynamicSyncSceneType::ANIMATE);
    if (iter  != frameRateRange_.end()) {
        option.SetFrameRateRange(iter->second);
    }
    auto curve = GetCurveIncludeMotion();
    float minimumAmplitudeRatio = 0.0f;
    if (translate != 0) {
        minimumAmplitudeRatio = DEFAULT_MINIMUM_AMPLITUDE_PX / translate;
    }
    if (InstanceOf<InterpolatingSpring>(curve) &&
        LessNotEqualCustomPrecision(
            minimumAmplitudeRatio, InterpolatingSpring::DEFAULT_INTERPOLATING_SPRING_AMPLITUDE_RATIO)) {
        auto interpolatingSpring = AceType::DynamicCast<InterpolatingSpring>(curve);
        interpolatingSpring->UpdateMinimumAmplitudeRatio(minimumAmplitudeRatio);
    }
    option.SetCurve(curve);
    option.SetFinishCallbackType(GetFinishCallbackType());
}

void ArcSwiperPattern::PlayPropertyTranslateDefaultAnimation(const OffsetF& offset, float translate)
{
    AnimationOption option;
    BuildDefaultTranslateAnimationOption(option, translate);
    auto finishCallback = [weak = WeakClaim(this), offset]() {
        auto swiper = weak.Upgrade();
        CHECK_NULL_VOID(swiper);
        if (!swiper->hasTabsAncestor_) {
            PerfMonitor::GetPerfMonitor()->End(PerfConstants::APP_SWIPER_FLING, true);
        }
        OffsetF finalOffset =
            swiper->itemPosition_.empty() ? OffsetF()
            : swiper->itemPosition_.begin()->second.node
                ? swiper->itemPosition_.begin()->second.node->GetRenderContext()->GetTranslateXYProperty()
                : OffsetF();
        TAG_LOGI(AceLogTag::ACE_SWIPER,
            "ArcSwiper finish property translate animation with offsetX: %{public}f, offsetY: %{public}f",
            finalOffset.GetX(), finalOffset.GetY());
        ACE_SCOPED_TRACE("ArcSwiper finish property animation X: %f, Y: %f", finalOffset.GetX(), finalOffset.GetY());
        swiper->targetIndex_.reset();
        swiper->OnPropertyTranslateAnimationFinish(offset);
    };

    // property callback will call immediately.
    auto propertyUpdateCallback = [swiper = WeakClaim(this), offset]() {
        auto swiperPattern = swiper.Upgrade();
        CHECK_NULL_VOID(swiperPattern);
        if (!swiperPattern->hasTabsAncestor_) {
            PerfMonitor::GetPerfMonitor()->Start(PerfConstants::APP_SWIPER_FLING, PerfActionType::FIRST_MOVE, "");
        }
        TAG_LOGI(AceLogTag::ACE_SWIPER,
            "ArcSwiper start property translate animation with offsetX: %{public}f, offsetY: %{public}f", offset.GetX(),
            offset.GetY());
        ACE_SCOPED_TRACE("ArcSwiper start property animation, X: %f, Y: %f", offset.GetX(), offset.GetY());
        for (auto& item : swiperPattern->itemPosition_) {
            auto frameNode = item.second.node;
            if (frameNode) {
                frameNode->GetRenderContext()->UpdateTranslateInXY(offset);
                item.second.finalOffset = offset;
            }
        }
        swiperPattern->itemPositionInAnimation_ = swiperPattern->itemPosition_;
    };
    ElementRegister::GetInstance()->ReSyncGeometryTransition(GetHost(), option);
    AnimationUtils::Animate(option, propertyUpdateCallback, finishCallback);
}

void ArcSwiperPattern::UsePropertyAnimation(const OffsetF& offset)
{
    if (usePropertyAnimation_) {
        if (!NeedStartNewAnimation(offset)) {
            stopIndicatorAnimation_ = false;
            return;
        }
        std::optional<int32_t> targetIndex;
        if (targetIndex_) {
            targetIndex = targetIndex_;
        }
        StopPropertyTranslateAnimation(isFinishAnimation_);
        StopIndicatorAnimation();

        if (targetIndex) {
            targetIndex_ = targetIndex;
            MarkDirtyNodeSelf();
            return;
        }
    }
}

void ArcSwiperPattern::PlayPropertyTranslateAnimation(
    float translate, int32_t nextIndex, float velocity, bool stopAutoPlay)
{
    if (IsHorizontalAndRightToLeft()) {
        translate = -translate;
    }
    if (NearZero(translate)) {
        OnAnimationTranslateZero(nextIndex, stopAutoPlay);
        return;
    }

    if (translate != 0) {
        motionVelocity_ = velocity / translate;
    }

    OffsetF offset;
    if (GetDirection() == Axis::HORIZONTAL) {
        offset.AddX(translate);
    } else {
        offset.AddY(translate);
    }
    UsePropertyAnimation(offset);
    ClearAnimationFinishList();
    // initial translate info.
    for (auto& item : itemPosition_) {
        auto frameNode = item.second.node;
        if (frameNode) {
            InitialFrameNodePropertyAnimation(item.second.finalOffset, frameNode, false);
        }
    }

    usePropertyAnimation_ = true;
    propertyAnimationIndex_ = nextIndex;
    if (EnableTransitionAnimation()) {
        PlayPropertyTranslateFlipAnimation(offset);
    } else {
        PlayPropertyTranslateDefaultAnimation(offset, translate);
    }

    HandlePropertyTranslateCallback(translate, nextIndex, velocity);

    // enable lazy load feature.
    SetLazyLoadFeature(true);
    UpdateItemRenderGroup(true);
}

bool ArcSwiperPattern::IsLoop() const
{
    return false;
}

void ArcSwiperPattern::SetBackgroundColor(const RefPtr<RenderContext>& renderContext,
    const std::shared_ptr<Color>& color)
{
    CHECK_NULL_VOID(renderContext);
    if (color) {
        renderContext->OnBackgroundColorUpdate(*color);
    } else {
        renderContext->OnBackgroundColorUpdate(Color::TRANSPARENT);
    }
}

void ArcSwiperPattern::PlayScrollBackgroundAnimation(const std::shared_ptr<Color>& color,
    const std::shared_ptr<Color>& parentColor, const RefPtr<RenderContext>& parentRenderContext,
    bool exitNodeNeedTransparent)
{
    CHECK_NULL_VOID(parentRenderContext);
    if (exitNodeNeedTransparent) {
        auto exitFrameNode = exitFrameNode_.Upgrade();
        CHECK_NULL_VOID(exitFrameNode);
        auto exitRenderContext = exitFrameNode->GetRenderContext();
        CHECK_NULL_VOID(exitRenderContext);
        exitRenderContext->OnBackgroundColorUpdate(Color::TRANSPARENT);
        CHECK_NULL_VOID(parentRenderContext);
        if (color && (*color != Color::TRANSPARENT)) {
            parentRenderContext->OnBackgroundColorUpdate(*color);
        } else {
            SetBackgroundColor(parentRenderContext, parentColor);
        }
    } else {
        CHECK_NULL_VOID(parentRenderContext);
        if (color && (*color != Color::TRANSPARENT)) {
            parentRenderContext->OnBackgroundColorUpdate(*color);
        } else {
            SetBackgroundColor(parentRenderContext, parentColor);
        }
    }
}

void ArcSwiperPattern::PlayHorizontalScrollExitAnimation(float swiperWidth, float startPos,
    const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto curContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(curContext);
    if (swiperWidth == 0) {
        return;
    }
    auto exitNodePercent = std::abs(startPos) / swiperWidth;
    // scale
    horizontalExitNodeScale_ = 1.0f - exitNodePercent * HORIZONTAL_SCALE_REDUCTION_FACTOR;
    if (horizontalExitNodeScale_ < HORIZONTAL_EXIT_SCALE_FINAL_VALUE) {
        horizontalExitNodeScale_ = HORIZONTAL_EXIT_SCALE_FINAL_VALUE;
    }
    curContext->UpdateTransformScale({horizontalExitNodeScale_, horizontalExitNodeScale_});

    // blur
    if (exitNodePercent > HORIZONTAL_BLUR_MIN_RATIO) {
        horizontalExitNodeBlur_ = HORIZONTAL_BLUR_REDUCTION_FACTOR * exitNodePercent;
        if (horizontalExitNodeBlur_ > HORIZONTAL_BLUR_MAX_VALUE) {
            horizontalExitNodeBlur_ = HORIZONTAL_BLUR_MAX_VALUE;
        }
        BlurOption blurOption;
        curContext->UpdateBackBlur(Dimension(horizontalExitNodeBlur_, DimensionUnit::PERCENT), blurOption);
    }

    // alpha
    horizontalExitNodeOpacity_ = 1.0f - exitNodePercent;
    if (horizontalExitNodeOpacity_ < 0.0f) {
        horizontalExitNodeOpacity_ = 0.0f;
    }
    curContext->UpdateOpacity(horizontalExitNodeOpacity_);
}

void ArcSwiperPattern::PlayHorizontalScrollEntryAnimation(float swiperWidth, float startPos,
    const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto entryNodeContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(entryNodeContext);
    if (swiperWidth == 0) {
        return;
    }
    auto entryNodePercent = (swiperWidth - std::abs(startPos)) / swiperWidth;
    // scale
    horizontalEntryNodeScale_ = HORIZONTAL_ENTRY_SCALE_INITIAL_VALUE +
        HORIZONTAL_SCALE_REDUCTION_FACTOR * entryNodePercent;
    if (horizontalEntryNodeScale_ >= 1.0f) {
        horizontalEntryNodeScale_ = 1.0f;
    }
    entryNodeContext->UpdateTransformScale({horizontalEntryNodeScale_, horizontalEntryNodeScale_});

    // blur
    horizontalEntryNodeBlur_ = HORIZONTAL_BLUR_MAX_VALUE - HORIZONTAL_BLUR_REDUCTION_FACTOR * entryNodePercent;
    if (horizontalEntryNodeBlur_ < 0.0f) {
        horizontalEntryNodeBlur_ = 0.0f;
    }
    BlurOption blurOption;
    entryNodeContext->UpdateBackBlur(Dimension(horizontalEntryNodeBlur_, DimensionUnit::PERCENT), blurOption);

    // alpha
    horizontalEntryNodeOpacity_ = HORIZONTAL_ALPHA_REDUCTION_FACTOR * entryNodePercent;
    if (horizontalEntryNodeOpacity_ > 1.0f) {
        horizontalEntryNodeOpacity_ = 1.0f;
    }
    entryNodeContext->UpdateOpacity(horizontalEntryNodeOpacity_);
}

void ArcSwiperPattern::HorizontalScrollAnimation()
{
    auto swiperWidth = CalculateVisibleSize();
    int32_t nextIndex = -1;
    if (gestureState_ == GestureState::GESTURE_STATE_FOLLOW_RIGHT) {
        nextIndex = currentIndex_ + 1;
    } else if (gestureState_ == GestureState::GESTURE_STATE_FOLLOW_LEFT) {
        nextIndex = currentIndex_ - 1;
    }
    auto nextInter = itemPosition_.find(nextIndex);
    if (nextInter == itemPosition_.end()) {
        return;
    }
    auto curInter = itemPosition_.find(currentIndex_);
    if (curInter != itemPosition_.end()) {
        auto curStartPos = curInter->second.startPos;
        auto curFrameNode = curInter->second.node;
        CHECK_NULL_VOID(curFrameNode);
        PlayHorizontalScrollExitAnimation(swiperWidth, curStartPos, curFrameNode);
    }

    if (nextInter != itemPosition_.end()) {
        auto nextStartPos = nextInter->second.startPos;
        auto nextFrameNode = nextInter->second.node;
        PlayHorizontalScrollEntryAnimation(swiperWidth, nextStartPos, nextFrameNode);
    }
}

void ArcSwiperPattern::VerticalScrollAnimation()
{
    auto swiperWidth = CalculateVisibleSize();
    int32_t nextIndex = -1;
    if (gestureState_ == GestureState::GESTURE_STATE_FOLLOW_RIGHT) {
        nextIndex = currentIndex_ + 1;
    } else if (gestureState_ == GestureState::GESTURE_STATE_FOLLOW_LEFT) {
        nextIndex = currentIndex_ - 1;
    }
    auto nextInter = itemPosition_.find(nextIndex);
    if (nextInter == itemPosition_.end()) {
        return;
    }

    auto curInter = itemPosition_.find(currentIndex_);
    if (curInter != itemPosition_.end()) {
        auto curStartPos = curInter->second.startPos;
        auto curFrameNode = curInter->second.node;
        CHECK_NULL_VOID(curFrameNode);
        PlayVerticalScrollExitAnimation(swiperWidth, curStartPos, curFrameNode);
    }

    if (nextInter != itemPosition_.end()) {
        auto nextStartPos = nextInter->second.startPos;
        auto nextFrameNode = nextInter->second.node;
        PlayVerticalScrollEntryAnimation(swiperWidth, nextStartPos, nextFrameNode);
    }
}

void ArcSwiperPattern::PlayVerticalScrollExitAnimation(float swiperWidth, float startPos,
    const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_VOID(frameNode);
    exitFrameNode_ = WeakPtr<FrameNode>(frameNode);
    auto curNodeContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(curNodeContext);
    if (swiperWidth == 0) {
        return;
    }
    auto exitNodePercent = std::abs(startPos) / swiperWidth;
    // color
    preNodeBackgroundColor_ = GetBackgroundColorValue(frameNode);

    // scale
    verticalExitNodeScale_ = 1.0f - exitNodePercent * VERTICAL_EXIT_SCALE_REDUCTION_FACTOR;
    if (verticalExitNodeScale_ < VERTICAL_EXIT_SCALE_MIN_VALUE) {
        verticalExitNodeScale_ = VERTICAL_EXIT_SCALE_MIN_VALUE;
    }
    curNodeContext->UpdateTransformScale({verticalExitNodeScale_, verticalExitNodeScale_});

    // blur
    verticalExitNodeBlur_ = VERTICAL_EXIT_BLUR_INITIAL_VALUE + exitNodePercent * VERTICAL_EXIT_BLUR_INCREASE_FACTOR;

    if (verticalExitNodeBlur_ > VERTICAL_EXIT_BLUR_MAX_VALUE) {
        verticalExitNodeBlur_ = VERTICAL_EXIT_BLUR_MAX_VALUE;
    }
    BlurOption blurOption;
    curNodeContext->UpdateBackBlur(Dimension(verticalExitNodeBlur_, DimensionUnit::PERCENT), blurOption);

    // alpha
    if (exitNodePercent < VERTICAL_EXIT_ALPHA_MIN_RATIO) {
        verticalExitNodeOpacity_ = 1.0f - VERTICAL_EXIT_ALPHA_REDUCTION_FACTOR * exitNodePercent;
    } else if (exitNodePercent == VERTICAL_EXIT_ALPHA_MIN_RATIO) {
        verticalExitNodeOpacity_ = VERTICAL_EXIT_ALPHA_AT_CRITICAL_POINT;
    } else {
        verticalExitNodeOpacity_ = VERTICAL_EXIT_ALPHA_AT_CRITICAL_POINT -
            VERTICAL_EXIT_ALPHA_REDUCTION_FACTOR_AFTER_CRITICAL_POINT * exitNodePercent;
    }
    if (verticalExitNodeOpacity_ < 0.0f) {
        verticalExitNodeOpacity_ = 0.0f;
    }
    curNodeContext->UpdateOpacity(verticalExitNodeOpacity_);
}

void ArcSwiperPattern::PlayVerticalScrollEntryAnimation(float swiperWidth, float startPos,
    const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto entryNodeContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(entryNodeContext);
    if (swiperWidth == 0) {
        return;
    }
    auto entryNodePercent = (swiperWidth - std::abs(startPos)) / swiperWidth;

    // color
    entryNodeBackgroundColor_ = GetBackgroundColorValue(frameNode);
    auto parentNode = frameNode->GetParentFrameNode();
    CHECK_NULL_VOID(parentNode);
    auto parentContext = parentNode->GetRenderContext();
    CHECK_NULL_VOID(parentContext);

    parentNodeBackgroundColor_ = GetBackgroundColorValue(parentNode);
    if (entryNodePercent < VERTICAL_ENTRY_CRITICAL_POINT_OF_COLOR) {
        entryNodeContext->OnBackgroundColorUpdate(Color::TRANSPARENT);
        PlayScrollBackgroundAnimation(preNodeBackgroundColor_, parentNodeBackgroundColor_, parentContext, false);
    }

    if (entryNodePercent >= VERTICAL_ENTRY_CRITICAL_POINT_OF_COLOR) {
        PlayScrollBackgroundAnimation(entryNodeBackgroundColor_, parentNodeBackgroundColor_, parentContext, true);
    }

    if (entryNodePercent >= VERTICAL_ENTRY_CRITICAL_POINT_OF_OTHER) {
        // scale
        verticalEntryNodeScale_ = VERTICAL_ENTRY_SCALE_INITIAL_VALUE -
            VERTICAL_ENTRY_SCALE_REDUCTION_FACTOR * (entryNodePercent - VERTICAL_ENTRY_CRITICAL_POINT_OF_OTHER) *
            VERTICAL_ENTRY_WHOLE_REDUCTION_FACTOR;
        if (verticalEntryNodeScale_ < 1.0f) {
            verticalEntryNodeScale_ = 1.0f;
        }
        entryNodeContext->UpdateTransformScale({verticalEntryNodeScale_, verticalEntryNodeScale_});

        // alpha
        verticalEntryNodeOpacity_ = (entryNodePercent - VERTICAL_ENTRY_CRITICAL_POINT_OF_OTHER) *
            VERTICAL_ENTRY_WHOLE_REDUCTION_FACTOR;
        if (verticalEntryNodeOpacity_ > 1.0f) {
            verticalEntryNodeOpacity_ = 1.0f;
        }
        entryNodeContext->UpdateOpacity(verticalEntryNodeOpacity_);
    }
}

void ArcSwiperPattern::PlayScrollAnimation(float offset)
{
    if (!EnableTransitionAnimation()) {
        return;
    }

    if (!isDragging_) {
        return;
    }

    if (NearZero(offset)) {
        return;
    }

    if (GetDirection() == Axis::HORIZONTAL) {
        HorizontalScrollAnimation();
    } else {
        VerticalScrollAnimation();
    }
}

void ArcSwiperPattern::ResetAnimationParam()
{
    StopPropertyTranslateAnimation(isFinishAnimation_);
    StopIndicatorAnimation();

    horizontalExitNodeScale_ = 1.0f;
    horizontalExitNodeBlur_ = 0.0f;
    horizontalExitNodeOpacity_ = 1.0f;
    horizontalEntryNodeScale_ = HORIZONTAL_ENTRY_SCALE_INITIAL_VALUE;
    horizontalEntryNodeBlur_ = HORIZONTAL_ENTRY_BLUR_VALUE;
    horizontalEntryNodeOpacity_ = 0.0f;

    verticalExitNodeScale_ = 1.0f;
    verticalExitNodeBlur_ = VERTICAL_EXIT_BLUR_INITIAL_VALUE;
    verticalExitNodeOpacity_ = 1.0f;
    verticalEntryNodeScale_ = VERTICAL_ENTRY_SCALE_VALUE;
    verticalEntryNodeOpacity_ = 0.0f;
    if (axis_ == GetDirection()) {
        return;
    }
    axis_ = GetDirection();
    if (axis_ == Axis::HORIZONTAL) {
        auto curInter = itemPosition_.find(currentIndex_);
        if (curInter == itemPosition_.end()) {
            return;
        }

        auto curFrameNode = curInter->second.node;
        CHECK_NULL_VOID(curFrameNode);
        auto parentFrameNode = curFrameNode->GetParentFrameNode();
        CHECK_NULL_VOID(parentFrameNode);
        auto parentContext = parentFrameNode->GetRenderContext();
        CHECK_NULL_VOID(parentContext);
        auto colorPtr = GetBackgroundColorValue(parentFrameNode);
        CHECK_NULL_VOID(colorPtr);
        parentContext->OnBackgroundColorUpdate(*colorPtr);
    }
}

void ArcSwiperPattern::ResetFrameNodeAnimation(const RefPtr<FrameNode>& frameNode, bool resetBackgroundcolor)
{
    CHECK_NULL_VOID(frameNode);
    auto context = frameNode->GetRenderContext();
    CHECK_NULL_VOID(context);
    context->UpdateTransformScale({1.0f, 1.0f});
    context->UpdateOpacity(1.0f);
    BlurOption blurOption;
    context->UpdateBackBlur(Dimension(0.0f, DimensionUnit::PERCENT), blurOption);
    if (resetBackgroundcolor) {
        auto backColor = GetBackgroundColorValue(frameNode);
        if (backColor) {
            context->OnBackgroundColorUpdate(*backColor);
        }
    }
}

void ArcSwiperPattern::ResetCurrentFrameNodeAnimation()
{
    auto curInter = itemPosition_.find(currentIndex_);
    if (curInter != itemPosition_.end()) {
        auto curFrameNode = curInter->second.node;
        CHECK_NULL_VOID(curFrameNode);
        ResetFrameNodeAnimation(curFrameNode, true);
    }
}

void ArcSwiperPattern::ResetParentNodeColor()
{
    auto curInter = itemPosition_.find(currentIndex_);
    if (curInter == itemPosition_.end()) {
        return;
    }
    auto curFrameNode = curInter->second.node;
    CHECK_NULL_VOID(curFrameNode);
    auto parentNode = curFrameNode->GetParentFrameNode();
    CHECK_NULL_VOID(parentNode);
    auto parentContext = parentNode->GetRenderContext();
    CHECK_NULL_VOID(parentContext);
    auto colorPtr = GetBackgroundColorValue(parentNode);
    if (colorPtr) {
        parentContext->OnBackgroundColorUpdate(*colorPtr);
    } else {
        parentContext->OnBackgroundColorUpdate(Color::TRANSPARENT);
    }
}

bool ArcSwiperPattern::EnableTransitionAnimation() const
{
    if (SupportSwiperCustomAnimation() || IsDisableTransitionAnimation()) {
        return false;
    }
    return true;
}

RefPtr<Curve> ArcSwiperPattern::GetCurve() const
{
    auto swiperPaintProperty = GetPaintProperty<SwiperPaintProperty>();
    CHECK_NULL_RETURN(swiperPaintProperty, nullptr);
    if (EnableTransitionAnimation()) {
        return Curves::FRICTION;
    }
    return swiperPaintProperty->GetCurve().value_or(nullptr);
}

int32_t ArcSwiperPattern::GetDuration() const
{
    auto swiperPaintProperty = GetPaintProperty<SwiperPaintProperty>();
    int32_t defaultDuration = 0;
    if (EnableTransitionAnimation()) {
        if (GetDirection() == Axis::HORIZONTAL) {
            defaultDuration = HORIZONTAL_ANIMAION_DEFAULT_DURATION;
        } else {
            defaultDuration = VERTICAL_ANIMAION_DEFAULT_DURATION;
        }
    } else {
        defaultDuration = NO_ANIMAION_DEFAULT_DURATION;
    }
    CHECK_NULL_RETURN(swiperPaintProperty, defaultDuration);
    return swiperPaintProperty->GetDuration().value_or(defaultDuration);
}

int32_t ArcSwiperPattern::CalcTime(int32_t time)
{
    auto duration = GetDuration();
    int32_t baseTime = 0;
    if (GetDirection() == Axis::HORIZONTAL) {
        baseTime = HORIZONTAL_ANIMAION_DEFAULT_DURATION;
    } else {
        baseTime = VERTICAL_ANIMAION_DEFAULT_DURATION;
    }
    return time * duration / baseTime;
}

#ifdef SUPPORT_DIGITAL_CROWN
void ArcSwiperPattern::SetDigitalCrownSensitivity(CrownSensitivity sensitivity)
{
    crownSensitivity_ = sensitivity;
}

void ArcSwiperPattern::InitOnCrownEventInternal(const RefPtr<FocusHub>& focusHub)
{
    auto host = GetHost();
    auto onCrownEvent = [weak = WeakClaim(this), weakNode = AceType::WeakClaim(AceType::RawPtr(
        host))](const CrownEvent& event) -> bool {
        auto pattern = weak.Upgrade();
        CHECK_NULL_RETURN(pattern, false);
        auto node = weakNode.Upgrade();
        CHECK_NULL_RETURN(node, false);

        auto offset = node->GetGeometryNode()->GetFrameOffset();
        auto contentSize = node->GetGeometryNode()->GetFrameSize();
        auto swiperPattern = node->GetPattern<SwiperPattern>();
        float centerX = contentSize.Width() * 0.5 + offset.GetX();
        float centerY = contentSize.Height() * 0.5 + offset.GetY();
        OffsetF center;
        center.SetX(centerX);
        center.SetY(centerY);
        pattern->HandleCrownEvent(event, center, offset);
        return true;
    };
    focusHub->SetOnCrownEventInternal(std::move(onCrownEvent));
}

bool ArcSwiperPattern::IsCrownSpring() const
{
    return isCrownSpring_;
}

void ArcSwiperPattern::SetIsCrownSpring(bool isCrownSpring)
{
    isCrownSpring_ = false;
}

void ArcSwiperPattern::HandleCrownEvent(const CrownEvent& event, const OffsetF& center, const OffsetF& offset)
{
    DimensionOffset centerDimension(center);
    Offset globalLocation(centerDimension.GetX().ConvertToPx(), centerDimension.GetY().ConvertToPx());
    GestureEvent info;
    info.SetSourceDevice(SourceType::CROWN);
    info.SetSourceTool(SourceTool::UNKNOWN);
    info.SetGlobalLocation(globalLocation);
    double mainDelta = GetCrownRotatePx(event);
    switch (event.action) {
        case CrownAction::BEGIN:
            HandleCrownActionBegin(event.degree, mainDelta, info);
            break;
        case CrownAction::UPDATE:
            HandleCrownActionUpdate(event.degree, mainDelta, info, offset);
            break;
        case CrownAction::END:
            HandleCrownActionEnd(event.degree, mainDelta, info, offset);
            break;
        default:
            HandleCrownActionCancel();
            break;
    }
}

void ArcSwiperPattern::HandleCrownActionBegin(double degree, double mainDelta,
    GestureEvent& info)
{
    accumulativeCrownPx_.Reset();
    UpdateCrownVelocity(degree, mainDelta);
    info.SetMainDelta(mainDelta);
    info.SetMainVelocity(crownVelocity_);
    InitIndexCanChangeMap();
    FireAndCleanScrollingListener();
    HandleDragStart(info);
    NotifyParentScrollStart(WeakClaim(this), direction_ == Axis::HORIZONTAL ? info.GetGlobalLocation().GetX()
                                    : info.GetGlobalLocation().GetY());
    TouchLocationInfo touchLocationInfo(1);
    touchLocationInfo.SetGlobalLocation(info.GetGlobalLocation());
    HandleTouchDown(touchLocationInfo);
    isCrownSpring_ = false;
    isHandleCrownActionEnd_ = false;
}

void ArcSwiperPattern::HandleCrownActionUpdate(double degree, double mainDelta,
    GestureEvent& info, const OffsetF& offset)
{
    if (isCrownSpring_) {
        return;
    }
    if (!isDragging_) {
        HandleCrownActionBegin(degree, mainDelta, info);
        return;
    }
    UpdateCrownVelocity(degree, mainDelta);
    info.SetMainDelta(mainDelta);
    info.SetMainVelocity(crownVelocity_);
    HandleDragUpdate(info);
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_VOID(theme);
    if (degree < theme->GetSpringVelocityThreshold()) {
        auto length = (direction_ == Axis::HORIZONTAL ? info.GetGlobalLocation().GetX() - offset.GetX():
                    info.GetGlobalLocation().GetY() - offset.GetY()) * 2;
        double offsetLen = direction_ == Axis::VERTICAL ? accumulativeCrownPx_.GetY() : accumulativeCrownPx_.GetX();
        if (std::abs(offsetLen) >= length * theme->GetCrownTranslocationRatio()) {
            isCrownSpring_ = true;
            HandleDragEnd(crownTurnVelocity_);
            HandleTouchUp();
        }
    } else {
        isCrownSpring_ = true;
        HandleDragEnd(crownVelocity_);
        HandleTouchUp();
    }
}

void ArcSwiperPattern::HandleCrownActionEnd(
    double degree, double mainDelta, GestureEvent& info, const OffsetF& offset)
{
    if (!isDragging_ || isHandleCrownActionEnd_) {
        return;
    }
    isHandleCrownActionEnd_ = true;
    UpdateCrownVelocity(degree, mainDelta, true);
    info.SetMainDelta(mainDelta);
    info.SetMainVelocity(crownVelocity_);
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_VOID(theme);
    isCrownSpring_ = true;
    if (degree < theme->GetSpringVelocityThreshold()) {
        auto length = (direction_ == Axis::HORIZONTAL ? info.GetGlobalLocation().GetX() - offset.GetX():
                    info.GetGlobalLocation().GetY() - offset.GetY()) * 2;
        double offsetLen = direction_ == Axis::VERTICAL ? accumulativeCrownPx_.GetY() : accumulativeCrownPx_.GetX();
        if (std::abs(offsetLen) >= length * theme->GetCrownTranslocationRatio()) {
            HandleDragEnd(crownTurnVelocity_);
            HandleTouchUp();
        } else {
            HandleDragEnd(0.0);
            HandleTouchUp();
        }
    } else {
        HandleDragEnd(crownVelocity_);
        HandleTouchUp();
    }
}

void ArcSwiperPattern::HandleCrownActionCancel()
{
    isCrownSpring_ = false;
    isHandleCrownActionEnd_ = false;
    if (!isDragging_) {
        return;
    }

    HandleDragEnd(0.0);
    HandleTouchUp();
    isDragging_ = false;
}

double ArcSwiperPattern::GetCrownRotatePx(const CrownEvent& event) const
{
    double velocity = event.degree;
    double px = 0.0;
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, 0.0);
    auto theme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_RETURN(theme, 0.0);

    if (LessOrEqualCustomPrecision(velocity, theme->GetSlowVelocityThreshold(), 0.01f)) {
        px = theme->GetDisplayControlRatioSlow() * velocity;
    } else {
        px = theme->GetDisplayControlRatioFast() * velocity;
    }

    switch (crownSensitivity_) {
        case CrownSensitivity::LOW:
            px *= theme->GetCrownSensitivityLow();
            break;
        case CrownSensitivity::MEDIUM:
            px *= theme->GetCrownSensitivityMedium();
            break;
        case CrownSensitivity::HIGH:
            px *= theme->GetCrownSensitivityHigh();
            break;
        default:
            break;
    }
    return px;
}

void ArcSwiperPattern::UpdateCrownVelocity(double degree, double mainDelta, bool isEnd)
{
    if (isEnd) {
        return;
    }
    if (direction_ == Axis::VERTICAL) {
        accumulativeCrownPx_ += Offset(0, mainDelta);
    } else {
        accumulativeCrownPx_ += Offset(mainDelta, 0);
    }
    auto turnVelocity = Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)
                                                        ? NEW_MIN_TURN_PAGE_VELOCITY
                                                        : MIN_TURN_PAGE_VELOCITY;
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_VOID(theme);
    crownVelocity_ = degree * turnVelocity / theme->GetSpringVelocityThreshold();
    if (degree > 0) {
        crownTurnVelocity_ = turnVelocity + 1;
    } else {
        crownTurnVelocity_ = -turnVelocity - 1;
    }
}
#endif
} // namespace OHOS::Ace::NG
