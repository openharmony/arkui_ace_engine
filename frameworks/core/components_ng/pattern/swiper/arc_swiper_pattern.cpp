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
constexpr int32_t VERTICAL_EXIT_SCALE_DURATION = 250;
constexpr int32_t VERTICAL_EXIT_OFFSET_DURATION = 250;
constexpr int32_t VERTICAL_EXIT_BLUR_INITIAL_VALUE = 0;
constexpr int32_t VERTICAL_EXIT_BLUR_VALUE = 40;
constexpr int32_t VERTICAL_EXIT_BLUR_DURATION = 250;
constexpr int32_t VERTICAL_EXIT_ALPHA_DURATION = 250;

constexpr float VERTICAL_ENTRY_SCALE_VALUE = 105.0f / 100.0f;
constexpr int32_t VERTICAL_ENTRY_SCALE_DELAY = 100;
constexpr int32_t VERTICAL_ENTRY_SCALE_DURATION = 270;
constexpr int32_t VERTICAL_ENTRY_OFFSET_DELAY = 100;
constexpr int32_t VERTICAL_ENTRY_OFFSET_DURATION = 270;
constexpr int32_t VERTICAL_ENTRY_ALPHA_DELAY = 100;
constexpr int32_t VERTICAL_ENTRY_ALPHA_DURATION = 270;
constexpr int32_t VERTICAL_ENTRY_COLOR_DURATION = 370;

constexpr float HORIZONTAL_SCALE_REDUCTION_FACTOR = 0.4f;
constexpr float HORIZONTAL_BLUR_MIN_RATIO = 0.2f;
constexpr float HORIZONTAL_BLUR_REDUCTION_FACTOR = 750.0f / 250.0f * 30.0f;
constexpr float HORIZONTAL_BLUR_MAX_VALUE = 30.0f;
constexpr float HORIZONTAL_ALPHA_REDUCTION_FACTOR = 750.0f / 500.0f;

constexpr float VERTICAL_EXIT_SCALE_REDUCTION_FACTOR = 466.0f / 2300.0f;
constexpr float VERTICAL_EXIT_SCALE_MIN_VALUE = 0.95f;
constexpr float VERTICAL_EXIT_BLUR_REDUCTION_FACTOR = 3728.0f  / 23.0f;
constexpr float VERTICAL_EXIT_BLUR_MAX_VALUE = 40.0f;
constexpr float VERTICAL_EXIT_OFFSET_PART = 115.0f / 466.0f;
constexpr float VERTICAL_EXIT_ALPHA_REDUCTION_FACTOR = 466.0f / 115.0f;

constexpr float VERTICAL_ENTRY_OFFSET_PART = 0.6f;
constexpr float VERTICAL_ENTRY_SCALE_INITIAL_VALUE = 1.05f;
constexpr float VERTICAL_ENTRY_SCALE_REDUCTION_FACTOR = 0.125f;
constexpr float VERTICAL_ENTRY_BLUR_INITIAL_VALUE = 40.0f;
constexpr float VERTICAL_ENTRY_BLUR_REDUCTION_FACTOR = 100.0f;
constexpr float VERTICAL_ENTRY_BLUR_ALPHA_FACTOR = 2.5f;

constexpr float DEFAULT_MINIMUM_AMPLITUDE_PX = 2.5f;
constexpr int32_t HALF = 2;
constexpr int32_t ANIMATION_SIZE = 8;
constexpr int32_t VERTICAL_ANIMATION_SIZE = 9;
constexpr int32_t NO_ANIMAION_DEFAULT_DURATION = 400;
constexpr int32_t VERTICAL_ANIMAION_DEFAULT_DURATION = 330;
constexpr int32_t HORIZONTAL_ANIMAION_DEFAULT_DURATION = 750;

float GetHorizontalExitScaleValue(bool rollBack)
{
    return rollBack ? 1.0f : HORIZONTAL_EXIT_SCALE_FINAL_VALUE;
}
float GetHorizontalExitBlurValue(bool rollBack)
{
    return rollBack ? 0.0f : HORIZONTAL_EXIT_BLUR_VALUE;
}
float GetHorizontalExitAlphaValue(bool rollBack)
{
    return rollBack ? 1.0f : 0.0f;
}
float GetVerticalExitScaleValue(bool rollBack)
{
    return rollBack ? 1.0f : VERTICAL_EXIT_SCALE_VALUE;
}
float GetVerticalExitBlurValue(bool rollBack)
{
    return rollBack ? 0.0f : VERTICAL_EXIT_BLUR_VALUE;
}
float GetVerticalExitAlphaValue(bool rollBack)
{
    return rollBack ? 1.0f : 0.0f;
}
float GetVerticalExitOffsetValue(bool rollBack, float offset)
{
    return rollBack ? offset : offset * VERTICAL_EXIT_OFFSET_PART;
}
float GetVerticalEntryAlphaValue(bool rollBack)
{
    return rollBack ? 0.0f : 1.0f;
}
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

void ArcSwiperPattern::PlayHorizontalAnimation(const OffsetF& offset, int32_t index, const RefPtr<FrameNode>& frameNode,
    bool rollBack)
{
    if (IsPreItem(index, offset.GetX(), rollBack)) {
        PlayHorizontalExitAnimation(offset, frameNode, rollBack);
    } else {
        PlayHorizontalEntryAnimation(offset, frameNode, rollBack);
    }
}

void ArcSwiperPattern::PlayVerticalAnimation(const OffsetF& offset, int32_t index, const RefPtr<FrameNode>& frameNode,
    bool rollBack)
{
    if (IsPreItem(index, offset.GetY(), rollBack)) {
        PlayVerticalExitAnimation(offset, frameNode, rollBack);
    } else {
        PlayVerticalEntryAnimation(offset, frameNode, rollBack);
    }
}

bool ArcSwiperPattern::IsPreItem(int32_t index, float translate, bool rollback)
{
    if (translate < 0) {
        if (index < static_cast<int32_t>(itemPosition_.size() / HALF)) {
            return !rollback;
        } else {
            return rollback;
        }
    } else {
        if (index < static_cast<int32_t>(itemPosition_.size() / HALF)) {
            return rollback;
        } else {
            return !rollback;
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

std::shared_ptr<AnimationUtils::Animation> ArcSwiperPattern::Animation(bool exit, AnimationParam& param, bool vertical,
    bool rollback)
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

void ArcSwiperPattern::PlayHorizontalExitAnimation(const OffsetF& offset, const RefPtr<FrameNode>& frameNode,
    bool rollBack)
{
    CHECK_NULL_VOID(frameNode);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    // scale
    renderContext->UpdateTransformScale({ horizontalExitNodeScale_, horizontalExitNodeScale_ });
    AnimationParam scaleParam;
    scaleParam.type = AnimationType::TYPE_SCALE;
    scaleParam.frameNode = frameNode;
    scaleParam.scaleValue = GetHorizontalExitScaleValue(rollBack);

    AnimationOption scaleOption;
    scaleOption.SetDuration(CalcTime(HORIZONTAL_EXIT_SCALE_DURATION));
    scaleOption.SetCurve(Curves::FRICTION);
    scaleParam.option = scaleOption;
    animationVector_.emplace_back(Animation(true, scaleParam));

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
    animationVector_.emplace_back(Animation(true, offsetParam));

    // blur
    BlurOption blurOption;
    renderContext->UpdateBackBlur(Dimension(horizontalExitNodeBlur_, DimensionUnit::PERCENT), blurOption);
    AnimationParam blurParam;
    blurParam.type = AnimationType::TYPE_BLUR;
    blurParam.frameNode = frameNode;
    blurParam.blurValue = GetHorizontalExitBlurValue(rollBack);

    AnimationOption blurAnimationOption;
    blurAnimationOption.SetDelay(CalcTime(HORIZONTAL_EXIT_BLUR_DELAY));
    blurAnimationOption.SetDuration(CalcTime(HORIZONTAL_EXIT_BLUR_DURATION));
    blurAnimationOption.SetCurve(Curves::LINEAR);
    blurParam.option = blurAnimationOption;
    animationVector_.emplace_back(Animation(true, blurParam));

    // alpha
    renderContext->UpdateOpacity(horizontalExitNodeOpacity_);
    AnimationParam alphaParam;
    alphaParam.type = AnimationType::TYPE_ALPHA;
    alphaParam.frameNode = frameNode;
    alphaParam.opacityValue = GetHorizontalExitAlphaValue(rollBack);

    AnimationOption alphaOption;
    alphaOption.SetDuration(CalcTime(HORIZONTAL_EXIT_ALPHA_DURATION));
    alphaOption.SetCurve(Curves::LINEAR);
    alphaParam.option = alphaOption;
    animationVector_.emplace_back(Animation(true, alphaParam));
}

void ArcSwiperPattern::PlayHorizontalEntryAnimation(const OffsetF& offset, const RefPtr<FrameNode>& frameNode,
    bool rollback)
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
    animationVector_.emplace_back(Animation(false, scaleParam));

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
    animationVector_.emplace_back(Animation(false, offsetParam));

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
    animationVector_.emplace_back(Animation(false, blurParam));
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
    animationVector_.emplace_back(Animation(false, alphaParam));
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

void ArcSwiperPattern::PlayVerticalExitOffsetAnimation(const OffsetF& offset, const RefPtr<FrameNode>& frameNode,
    bool rollBack)
{
    AnimationParam offsetParam;
    offsetParam.type = AnimationType::TYPE_OFFSET;
    offsetParam.frameNode = frameNode;

    auto offsetPart = GetVerticalExitOffsetValue(rollBack, offset.GetY());
    offsetParam.offset.SetY(offsetPart);

    AnimationOption offsetOption;
    offsetOption.SetDuration(CalcTime(VERTICAL_EXIT_OFFSET_DURATION));
    offsetOption.SetCurve(Curves::FRICTION);
    ElementRegister::GetInstance()->ReSyncGeometryTransition(GetHost(), offsetOption);
    offsetParam.option = offsetOption;
    animationVector_.emplace_back(Animation(true, offsetParam, true, rollBack));
}

void ArcSwiperPattern::PlayVerticalExitAnimation(const OffsetF& offset, const RefPtr<FrameNode>& frameNode,
    bool rollBack)
{
    CHECK_NULL_VOID(frameNode);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);

    // scale
    renderContext->UpdateTransformScale({ verticalExitNodeScale_, verticalExitNodeScale_ });
    AnimationParam scaleParam;
    scaleParam.type = AnimationType::TYPE_SCALE;
    scaleParam.frameNode = frameNode;
    scaleParam.scaleValue = GetVerticalExitScaleValue(rollBack);

    AnimationOption scaleOption;
    scaleOption.SetDuration(CalcTime(VERTICAL_EXIT_SCALE_DURATION));
    scaleOption.SetCurve(Curves::FRICTION);
    scaleParam.option = scaleOption;
    animationVector_.emplace_back(Animation(true, scaleParam, true, rollBack));

    // offset
    PlayVerticalExitOffsetAnimation(offset, frameNode, rollBack);
    
    // blur
    BlurOption blurOption;
    renderContext->UpdateBackBlur(Dimension(verticalExitNodeBlur_, DimensionUnit::PERCENT),
        blurOption);
    AnimationParam blurParam;
    blurParam.type = AnimationType::TYPE_BLUR;
    blurParam.frameNode = frameNode;
    blurParam.blurValue = GetVerticalExitBlurValue(rollBack);

    AnimationOption blurAnimationOption;
    blurAnimationOption.SetDuration(CalcTime(VERTICAL_EXIT_BLUR_DURATION));
    blurAnimationOption.SetCurve(Curves::LINEAR);
    blurParam.option = blurAnimationOption;
    animationVector_.emplace_back(Animation(true, blurParam, true, rollBack));

    // alpha
    renderContext->UpdateOpacity(verticalExitNodeOpacity_);
    AnimationParam alphaParam;
    alphaParam.type = AnimationType::TYPE_ALPHA;
    alphaParam.frameNode = frameNode;
    alphaParam.opacityValue = GetVerticalExitAlphaValue(rollBack);

    AnimationOption alphaOption;
    alphaOption.SetDuration(CalcTime(VERTICAL_EXIT_ALPHA_DURATION));
    alphaOption.SetCurve(Curves::LINEAR);
    alphaParam.option = alphaOption;
    animationVector_.emplace_back(Animation(true, alphaParam, true, rollBack));

    // color
    renderContext->OnBackgroundColorUpdate(Color::TRANSPARENT);
}

std::shared_ptr<Color> ArcSwiperPattern::GetEntryNodeBackgroundColor(const RefPtr<FrameNode>& frameNode)
{
    // color
    std::shared_ptr<Color> colorPtr = nullptr;
    CHECK_NULL_RETURN(frameNode, colorPtr);
    colorPtr = GetBackgroundColorValue(frameNode);
    if (!colorPtr || *colorPtr == Color::TRANSPARENT) {
        colorPtr = parentNodeBackgroundColor_;
    }
    if (colorPtr == nullptr) {
        colorPtr = std::make_shared<Color>(Color::TRANSPARENT);
    }
    return colorPtr;
}

Color ArcSwiperPattern::GetVerticalEntryBackgroundValue(bool rollBack)
{
    Color color = Color::TRANSPARENT;
    if (rollBack) {
        if (preNodeBackgroundColor_ && *preNodeBackgroundColor_ != Color::TRANSPARENT) {
            color = *preNodeBackgroundColor_;
        } else if (parentNodeBackgroundColor_) {
            color = *parentNodeBackgroundColor_;
        }
    } else {
        if (entryNodeBackgroundColor_ && *entryNodeBackgroundColor_ != Color::TRANSPARENT) {
            color = *entryNodeBackgroundColor_;
        } else if (parentNodeBackgroundColor_) {
            color = *parentNodeBackgroundColor_;
        }
    }
    return color;
}

void ArcSwiperPattern::PlayVerticalEntryOffsetAnimation(const OffsetF& offset, const RefPtr<FrameNode>& frameNode,
    bool rollBack)
{
    if (!rollBack) {
        // offset1: When alpha is 0, move to the starting point of the animation effect.
        AnimationParam offsetParam1;
        offsetParam1.type = AnimationType::TYPE_OFFSET;
        offsetParam1.frameNode = frameNode;
        auto offsetPart1 = offset.GetY() * VERTICAL_ENTRY_OFFSET_PART;
        OffsetF offset1;
        offset1.SetY(offsetPart1);
        offsetParam1.offset = offset1;

        AnimationOption offsetOption1;
        offsetOption1.SetDuration(CalcTime(VERTICAL_ENTRY_OFFSET_DELAY));
        offsetOption1.SetCurve(Curves::FRICTION);
        offsetParam1.option = offsetOption1;
        animationVector_.emplace_back(Animation(false, offsetParam1));
    }

    // offset2: Move to target position
    AnimationParam offsetParam2;
    offsetParam2.type = AnimationType::TYPE_OFFSET;
    offsetParam2.frameNode = frameNode;
    auto offsetPart2 = offset.GetY();
    OffsetF offset2;
    offset2.SetY(offsetPart2);
    offsetParam2.offset = offset2;

    AnimationOption offsetOption2;
    offsetOption2.SetDelay(CalcTime(VERTICAL_ENTRY_OFFSET_DELAY));
    offsetOption2.SetDuration(CalcTime(VERTICAL_ENTRY_OFFSET_DURATION));
    offsetOption2.SetCurve(Curves::FRICTION);
    ElementRegister::GetInstance()->ReSyncGeometryTransition(GetHost(), offsetOption2);
    offsetParam2.option = offsetOption2;
    animationVector_.emplace_back(Animation(false, offsetParam2));
}

void ArcSwiperPattern::PlayVerticalEntryAnimation(const OffsetF& offset, const RefPtr<FrameNode>& frameNode,
    bool rollBack)
{
    CHECK_NULL_VOID(frameNode);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    // color
    frameNode->GetRenderContext()->OnBackgroundColorUpdate(Color::TRANSPARENT);
    frameNode->GetRenderContext()->UpdateOpacity(0);
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
    animationVector_.emplace_back(Animation(false, scaleParam, true, rollBack));

    // offset
    PlayVerticalEntryOffsetAnimation(offset, frameNode, rollBack);
    
    // alpha
    if (!rollBack) {
        renderContext->UpdateOpacity(verticalEntryNodeOpacity_);
    }
    AnimationParam alphaParam;
    alphaParam.type = AnimationType::TYPE_ALPHA;
    alphaParam.frameNode = frameNode;
    alphaParam.opacityValue = GetVerticalEntryAlphaValue(rollBack);

    AnimationOption alphaOption;
    alphaOption.SetDelay(CalcTime(VERTICAL_ENTRY_ALPHA_DELAY));
    alphaOption.SetDuration(CalcTime(VERTICAL_ENTRY_ALPHA_DURATION));
    alphaOption.SetCurve(Curves::LINEAR);
    alphaParam.option = alphaOption;
    animationVector_.emplace_back(Animation(false, alphaParam));

    // color
    entryNodeBackgroundColor_ = GetEntryNodeBackgroundColor(frameNode);
    CHECK_NULL_VOID(entryNodeBackgroundColor_);
    AnimationParam colorParam;
    colorParam.type = AnimationType::TYPE_COLOR;
    
    colorParam.frameNode = frameNode;
    colorParam.backColor = GetVerticalEntryBackgroundValue(rollBack);

    AnimationOption colorOption;
    colorOption.SetDuration(CalcTime(VERTICAL_ENTRY_COLOR_DURATION));
    colorOption.SetCurve(Curves::LINEAR);
    colorParam.option = colorOption;
    animationVector_.emplace_back(Animation(false, colorParam));
}

bool ArcSwiperPattern::IsScrollOverCritical()
{
    if (targetIndex_ && targetIndex_.value() == currentIndex_) {
        return false;
    }
    return true;
}

void ArcSwiperPattern::PlayAnimation(const OffsetF& offset, int32_t index, const RefPtr<FrameNode>& frameNode)
{
    PerfMonitor::GetPerfMonitor()->Start(PerfConstants::APP_SWIPER_FLING, PerfActionType::FIRST_MOVE, "");
    if (GetDirection() == Axis::HORIZONTAL) {
        PlayHorizontalAnimation(offset, index, frameNode, !IsScrollOverCritical());
    } else {
        PlayVerticalAnimation(offset, index, frameNode, !IsScrollOverCritical());
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
    auto adOffset = offset;
    if (IsHorizontalAndRightToLeft()) {
        if (GetDirection() == Axis::HORIZONTAL) {
            adOffset.SetX(-adOffset.GetX());
        } else {
            adOffset.SetY(-adOffset.GetY());
        }
    }
    int32_t index = 0;
    if (!hasTabsAncestor_) {
        PerfMonitor::GetPerfMonitor()->Start(PerfConstants::APP_SWIPER_FLING, PerfActionType::FIRST_MOVE, "");
    }
    for (auto &item : itemPosition_) {
        auto frameNode = item.second.node;
        if (frameNode) {
            PlayAnimation(adOffset, index, frameNode);
            index++;
            item.second.finalOffset = adOffset;
        }
    }
    itemPositionInAnimation_ = itemPosition_;
}

void ArcSwiperPattern::InitialFrameNodePropertyAnimation(const OffsetF& offset, const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_VOID(frameNode);
    for (auto animaiton: animationVector_) {
        AnimationUtils::StopAnimation(animaiton);
    }
    frameNode->GetRenderContext()->UpdateOpacity(1.0f);
    frameNode->GetRenderContext()->UpdateTransformScale({1.0f, 1.0f});
    BlurOption blurOption;
    frameNode->GetRenderContext()->UpdateBackBlur(Dimension(0.0f, DimensionUnit::PERCENT), blurOption);
    frameNode->GetRenderContext()->UpdateTranslateInXY(offset);
    auto colorPtr = GetBackgroundColorValue(frameNode);
    CHECK_NULL_VOID(colorPtr);
    frameNode->GetRenderContext()->OnBackgroundColorUpdate(*colorPtr);
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

void ArcSwiperPattern::AddFinishAnimation(const AnimationFinishType& animationFinishType, bool vertical, bool rollBack)
{
    animationFinishList_.emplace_back(animationFinishType);
    if (vertical && !rollBack && animationFinishList_.size() == VERTICAL_ANIMATION_SIZE) {
        AnimationFinish();
    } else {
        if (animationFinishList_.size() == ANIMATION_SIZE) {
            AnimationFinish();
        }
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
    auto adOffset = offset;
    if (IsHorizontalAndRightToLeft()) {
        if (GetDirection() == Axis::HORIZONTAL) {
            adOffset.SetX(-adOffset.GetX());
        } else {
            adOffset.SetY(-adOffset.GetY());
        }
    }
    AnimationOption option;
    BuildDefaultTranslateAnimationOption(option, translate);
    auto finishCallback = [weak = WeakClaim(this), offset]() {
        auto swiper = weak.Upgrade();
        CHECK_NULL_VOID(swiper);
        if (!swiper->hasTabsAncestor_) {
            PerfMonitor::GetPerfMonitor()->End(PerfConstants::APP_SWIPER_FLING, true);
        }
        OffsetF finalOffset =
            swiper->itemPosition_.empty() ? OffsetF() : swiper->itemPosition_.begin()->second.node
                ? swiper->itemPosition_.begin()->second.node->GetRenderContext()->GetTranslateXYProperty() : OffsetF();
        TAG_LOGI(AceLogTag::ACE_SWIPER,
            "ArcSwiper finish property translate animation with offsetX: %{public}f, offsetY: %{public}f",
            finalOffset.GetX(), finalOffset.GetY());
        ACE_SCOPED_TRACE("ArcSwiper finish property animation X: %f, Y: %f", finalOffset.GetX(), finalOffset.GetY());
        swiper->targetIndex_.reset();
        swiper->OnPropertyTranslateAnimationFinish(offset);
    };

    // property callback will call immediately.
    auto propertyUpdateCallback = [swiper = WeakClaim(this), offset = adOffset]() {
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
    if (GetPropertyAnimationIsRunning()) {
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
            InitialFrameNodePropertyAnimation(item.second.finalOffset, frameNode);
        }
    }

    SetPropertyAnimationIsRunning(true);
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
    curNodeContext->OnBackgroundColorUpdate(Color::TRANSPARENT);
    // scale
    verticalExitNodeScale_ = 1.0f -  exitNodePercent * VERTICAL_EXIT_SCALE_REDUCTION_FACTOR;
    if (verticalExitNodeScale_ < VERTICAL_EXIT_SCALE_MIN_VALUE) {
        verticalExitNodeScale_ = VERTICAL_EXIT_SCALE_MIN_VALUE;
    }
    curNodeContext->UpdateTransformScale({verticalExitNodeScale_, verticalExitNodeScale_});

    // blur
    verticalExitNodeBlur_ = exitNodePercent * VERTICAL_EXIT_BLUR_REDUCTION_FACTOR;

    if (verticalExitNodeBlur_ > VERTICAL_EXIT_BLUR_MAX_VALUE) {
        verticalExitNodeBlur_ = VERTICAL_EXIT_BLUR_MAX_VALUE;
    }
    BlurOption blurOption;
    curNodeContext->UpdateBackBlur(Dimension(verticalExitNodeBlur_, DimensionUnit::PERCENT), blurOption);

    // alpha
    verticalExitNodeOpacity_ = 1.0f -  exitNodePercent  * VERTICAL_EXIT_ALPHA_REDUCTION_FACTOR;
    if (verticalExitNodeOpacity_ < 0.0f) {
        verticalExitNodeOpacity_ = 0.0f;
    }
    curNodeContext->UpdateOpacity(verticalExitNodeOpacity_);
}

std::shared_ptr<Color> ArcSwiperPattern::CalcBackgroundByPercent(const std::shared_ptr<Color>& colorA,
    const std::shared_ptr<Color>& colorB, float percent)
{
    Color retColor = Color::TRANSPARENT;
    Color tempColorA = Color::TRANSPARENT;
    Color tempColorB = Color::TRANSPARENT;
    if (colorA) {
        tempColorA = *colorA;
    }
    if (colorB) {
        tempColorB = *colorB;
    }
    auto r = tempColorA.GetRed() * (1.0f - percent) + tempColorB.GetRed() * percent;
    auto g = tempColorA.GetGreen() * (1.0f - percent) + tempColorB.GetGreen() * percent;
    auto b = tempColorA.GetBlue() * (1.0f - percent) + tempColorB.GetBlue() * percent;
    auto a = tempColorA.GetAlpha() * (1.0f - percent) + tempColorB.GetAlpha() * percent;
    retColor = retColor.FromARGB(a, r, g, b);
    std::shared_ptr<Color> colorPtr = std::make_shared<Color>(retColor);
    return colorPtr;
}

void ArcSwiperPattern::PlayVerticalScrollEntryBackgroundAnimation(float percent, const RefPtr<FrameNode>& frameNode)
{
    entryNodeBackgroundColor_ = GetBackgroundColorValue(frameNode);
    auto parentNode = frameNode->GetParentFrameNode();
    CHECK_NULL_VOID(parentNode);
    auto parentContext = parentNode->GetRenderContext();
    CHECK_NULL_VOID(parentContext);

    std::shared_ptr<Color> beginColor = std::shared_ptr<Color>();
    std::shared_ptr<Color> endColor = std::shared_ptr<Color>();
    if (!preNodeBackgroundColor_ || (preNodeBackgroundColor_ && *preNodeBackgroundColor_ == Color::TRANSPARENT)) {
        beginColor = parentNodeBackgroundColor_;
    } else {
        beginColor = preNodeBackgroundColor_;
    }

    if (!entryNodeBackgroundColor_ || (entryNodeBackgroundColor_ && *entryNodeBackgroundColor_ == Color::TRANSPARENT)) {
        endColor = parentNodeBackgroundColor_;
    } else {
        endColor = entryNodeBackgroundColor_;
    }

    auto color = CalcBackgroundByPercent(beginColor, endColor, percent);
    PlayScrollBackgroundAnimation(color, parentNodeBackgroundColor_, parentContext, true);
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
    entryNodeContext->OnBackgroundColorUpdate(Color::TRANSPARENT);
    entryNodeContext->UpdateOpacity(0);
    auto entryNodePercent = (swiperWidth - std::abs(startPos)) / swiperWidth;

    // color
    PlayVerticalScrollEntryBackgroundAnimation(entryNodePercent, frameNode);

    if (entryNodePercent >= VERTICAL_ENTRY_OFFSET_PART) {
        // scale
        verticalEntryNodeScale_ = VERTICAL_ENTRY_SCALE_INITIAL_VALUE - VERTICAL_ENTRY_SCALE_REDUCTION_FACTOR *
            (entryNodePercent - VERTICAL_ENTRY_OFFSET_PART);
        if (verticalEntryNodeScale_ < 1.0f) {
            verticalEntryNodeScale_ = 1.0f;
        }
        entryNodeContext->UpdateTransformScale({verticalEntryNodeScale_, verticalEntryNodeScale_});

        // blur
        verticalEntryNodeBlur_ = VERTICAL_ENTRY_BLUR_INITIAL_VALUE - VERTICAL_ENTRY_BLUR_REDUCTION_FACTOR *
            (entryNodePercent - VERTICAL_ENTRY_OFFSET_PART);

        if (verticalEntryNodeBlur_ < 0) {
            verticalEntryNodeBlur_ = 0;
        }
        BlurOption blurOption;
        entryNodeContext->UpdateBackBlur(Dimension(verticalEntryNodeBlur_, DimensionUnit::PERCENT), blurOption);

        // alpha
        verticalEntryNodeOpacity_ = (entryNodePercent - VERTICAL_ENTRY_OFFSET_PART) * VERTICAL_ENTRY_BLUR_ALPHA_FACTOR;
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
    verticalEntryNodeBlur_ = 0.0f;
    auto axis = GetDirection();
    if (axis_ == axis && axis == Axis::HORIZONTAL) {
        return;
    }
    axis_ = axis;
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
    auto parentColorPtr = GetBackgroundColorValue(parentFrameNode);
    if (axis_ == Axis::HORIZONTAL) {
        CHECK_NULL_VOID(parentColorPtr);
        parentContext->OnBackgroundColorUpdate(*parentColorPtr);
    } else {
        parentNodeBackgroundColor_ = GetBackgroundColorValue(parentFrameNode);
        preNodeBackgroundColor_ = GetBackgroundColorValue(curFrameNode);
        if (preNodeBackgroundColor_ && *preNodeBackgroundColor_ != Color::TRANSPARENT) {
            parentContext->OnBackgroundColorUpdate(*preNodeBackgroundColor_);
        } else {
            CHECK_NULL_VOID(parentColorPtr);
            preNodeBackgroundColor_ = parentColorPtr;
            parentContext->OnBackgroundColorUpdate(*parentColorPtr);
        }
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