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

#include "core/components_ng/pattern/swiper_indicator/indicator_common/swiper_indicator_pattern.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float ANIMATION_HORIZONTAL_EXIT_SCALE_VALUE = 0.6f;
constexpr int32_t ANIMATION_HORIZONTAL_EXIT_SCALE_DURATION = 750;
constexpr int32_t ANIMATION_HORIZONTAL_EXIT_OFFSET_DURATION = 750;
constexpr int32_t ANIMATION_HORIZONTAL_EXIT_BLUR_VALUE = 30;
constexpr int32_t ANIMATION_HORIZONTAL_EXIT_BLUR_DELAY = 150;
constexpr int32_t ANIMATION_HORIZONTAL_EXIT_BLUR_DURATION = 250;
constexpr int32_t ANIMATION_HORIZONTAL_EXIT_ALPHA_DURATION = 750;

constexpr float ANIMATION_HORIZONTAL_ENTRY_SCALE_VALUE = 0.6f;
constexpr int32_t ANIMATION_HORIZONTAL_ENTRY_SCALE_DURATION = 750;
constexpr int32_t ANIMATION_HORIZONTAL_ENTRY_OFFSET_DURATION = 750;
constexpr int32_t ANIMATION_HORIZONTAL_ENTRY_BLUR_VALUE = 30;
constexpr int32_t ANIMATION_HORIZONTAL_ENTRY_BLUR_DURATION = 250;
constexpr int32_t ANIMATION_HORIZONTAL_ENTRY_ALPHA_DURATION = 500;

constexpr float ANIMATION_VERTICAL_EXIT_SCALE_VALUE = 0.95f;
constexpr int32_t ANIMATION_VERTICAL_EXIT_SCALE_DURATION = 330;
constexpr int32_t ANIMATION_VERTICAL_EXIT_OFFSET_DURATION = 750;
constexpr int32_t ANIMATION_VERTICAL_EXIT_BLUR_INITIAL_VALUE = 70;
constexpr int32_t ANIMATION_VERTICAL_EXIT_BLUR_VALUE = 100;
constexpr int32_t ANIMATION_VERTICAL_EXIT_BLUR_DURATION = 330;
constexpr int32_t ANIMATION_VERTICAL_EXIT_ALPHA_DURATION = 200;

constexpr float ANIMATION_VERTICAL_ENTRY_SCALE_VALUE = 101.5 / 100;
constexpr int32_t ANIMATION_VERTICAL_ENTRY_SCALE_DELAY = 130;
constexpr int32_t ANIMATION_VERTICAL_ENTRY_SCALE_DURATION = 200;
constexpr int32_t ANIMATION_VERTICAL_ENTRY_OFFSET_DELAY = 130;
constexpr int32_t ANIMATION_VERTICAL_ENTRY_OFFSET_DURATION = 200;
constexpr int32_t ANIMATION_VERTICAL_ENTRY_ALPHA_DELAY = 130;
constexpr int32_t ANIMATION_VERTICAL_ENTRY_ALPHA_DURATION = 200;
constexpr int32_t ANIMATION_VERTICAL_ENTRY_COLOR_DURATION = 40;

constexpr int32_t HALF = 2;
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

void ArcSwiperPattern::PlayHorizontalAnimation(const OffsetF& offset, const RefPtr<FrameNode>& frameNode,
    int32_t index)
{
    if (IsPreItem(index)) {
        PlayHorizontalExitAnimation(offset, frameNode);
    } else {
        PlayHorizontalEntryAnimation(offset, frameNode);
    }
}


void ArcSwiperPattern::PlayVerticalAnimation(const OffsetF& offset, const RefPtr<FrameNode>& frameNode, int32_t index)
{
    if (IsPreItem(index)) {
        PlayVerticalExitAnimation(offset, frameNode);
    } else {
        PlayVerticalEntryAnimation(offset, frameNode);
    }
}

bool ArcSwiperPattern::IsPreItem(int32_t index)
{
    if (index < itemPosition_.size() / HALF) {
        if (gestureState_ == GestureState::GESTURE_STATE_FOLLOW_RIGHT) {
            return true;
        } else {
            return false;
        }
    }
    return false;
}


std::shared_ptr<AnimationUtils::Animation> ArcSwiperPattern::Animation(const AnimationParam &param)
{
    auto frameNode = param.frameNode;
    BlurOption blurOption;
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, nullptr);
    auto finishCallback = [param, blurOption, renderContext]() {
        if (param.type == AnimationType::TYPE_SCALE) {
            renderContext->UpdateTransformScale({ 1.0f, 1.0f });
        } else if (param.type == AnimationType::TYPE_ALPHA) {
            renderContext->UpdateOpacity(1);
        } else if (param.type == AnimationType::TYPE_BLUR) {
            renderContext->UpdateBackBlur(Dimension(0, DimensionUnit::PERCENT), blurOption);
        }
    };

    return AnimationUtils::StartAnimation(
        param.option,
        [param, blurOption, renderContext]() {
            if (param.type == AnimationType::TYPE_SCALE) {
                renderContext->UpdateTransformScale({param.scaleValue, param.scaleValue});
            } else if (param.type == AnimationType::TYPE_ALPHA) {
                renderContext->UpdateOpacity(param.opacityValue);
            } else if (param.type == AnimationType::TYPE_BLUR) {
                renderContext->UpdateBackBlur(Dimension(param.blurValue, DimensionUnit::PERCENT), blurOption);
            } else if (param.type == AnimationType::TYPE_COLOR) {
                renderContext->OnBackgroundColorUpdate(param.backColor);
            } else if (param.type == AnimationType::TYPE_OFFSET) {
                renderContext->UpdateTranslateInXY(param.offset);
            }
        },
        finishCallback);
}

void ArcSwiperPattern::PlayHorizontalExitAnimation(const OffsetF& offset, const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);

    //scale
    renderContext->UpdateTransformScale({ 1.0f, 1.0f });
    AnimationParam scaleParam;
    scaleParam.type = AnimationType::TYPE_SCALE;
    scaleParam.frameNode = frameNode;
    scaleParam.scaleValue = ANIMATION_HORIZONTAL_EXIT_SCALE_VALUE;

    AnimationOption scaleOption;
    scaleOption.SetDuration(ANIMATION_HORIZONTAL_EXIT_SCALE_DURATION);
    scaleOption.SetCurve(Curves::FRICTION);
    scaleParam.option = scaleOption;
    Animation(scaleParam);

    //Offset
    AnimationParam offsetParam;
    offsetParam.type = AnimationType::TYPE_OFFSET;
    offsetParam.frameNode = frameNode;
    offsetParam.offset = offset;

    AnimationOption offsetOption;
    offsetOption.SetDuration(ANIMATION_HORIZONTAL_EXIT_OFFSET_DURATION);
    offsetOption.SetCurve(Curves::FRICTION);
    offsetParam.option = offsetOption;
    Animation(offsetParam);

    //blur
    BlurOption blurOption;
    renderContext->UpdateBackBlur(Dimension(0, DimensionUnit::PERCENT), blurOption);
    AnimationParam blurParam;
    blurParam.type = AnimationType::TYPE_BLUR;
    blurParam.frameNode = frameNode;
    blurParam.blurValue = ANIMATION_HORIZONTAL_EXIT_BLUR_VALUE;

    AnimationOption blurAnimationOption;
    blurAnimationOption.SetDelay(ANIMATION_HORIZONTAL_EXIT_BLUR_DELAY);
    blurAnimationOption.SetDuration(ANIMATION_HORIZONTAL_EXIT_BLUR_DURATION);
    blurAnimationOption.SetCurve(Curves::LINEAR);
    blurParam.option = blurAnimationOption;
    Animation(blurParam);

    //alpha
    renderContext->UpdateOpacity(1);
    AnimationParam alphaParam;
    alphaParam.type = AnimationType::TYPE_ALPHA;
    alphaParam.frameNode = frameNode;
    alphaParam.opacityValue = 0;

    AnimationOption alphaOption;
    alphaOption.SetDuration(ANIMATION_HORIZONTAL_EXIT_ALPHA_DURATION);
    alphaOption.SetCurve(Curves::LINEAR);
    alphaParam.option = alphaOption;
    Animation(alphaParam);
}

void ArcSwiperPattern::PlayHorizontalEntryAnimation(const OffsetF& offset, const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);

    //scale
    renderContext->UpdateTransformScale(
        {ANIMATION_HORIZONTAL_ENTRY_SCALE_VALUE, ANIMATION_HORIZONTAL_ENTRY_SCALE_VALUE});
    AnimationParam scaleParam;
    scaleParam.type = AnimationType::TYPE_SCALE;
    scaleParam.frameNode = frameNode;
    scaleParam.scaleValue = 1.0f;

    AnimationOption scaleOption;
    scaleOption.SetDuration(ANIMATION_HORIZONTAL_ENTRY_SCALE_DURATION);
    scaleOption.SetCurve(Curves::FRICTION);
    scaleParam.option = scaleOption;
    Animation(scaleParam);

    //Offset
    AnimationParam offsetParam;
    offsetParam.type = AnimationType::TYPE_OFFSET;
    offsetParam.frameNode = frameNode;
    offsetParam.offset = offset;

    AnimationOption offsetOption;
    offsetOption.SetDuration(ANIMATION_HORIZONTAL_ENTRY_OFFSET_DURATION);
    offsetOption.SetCurve(Curves::FRICTION);
    offsetParam.option = offsetOption;
    Animation(offsetParam);

    //blur
    BlurOption blurOption;
    renderContext->UpdateBackBlur(Dimension(ANIMATION_HORIZONTAL_ENTRY_BLUR_VALUE, DimensionUnit::PERCENT), blurOption);
    AnimationParam blurParam;
    blurParam.type = AnimationType::TYPE_BLUR;
    blurParam.frameNode = frameNode;
    blurParam.blurValue = 0;

    AnimationOption blurAnimationOption;
    blurAnimationOption.SetDuration(ANIMATION_HORIZONTAL_ENTRY_BLUR_DURATION);
    blurAnimationOption.SetCurve(Curves::LINEAR);
    blurParam.option = blurAnimationOption;
    Animation(blurParam);

    //alpha
    renderContext->UpdateOpacity(0);
    AnimationParam alphaParam;
    alphaParam.type = AnimationType::TYPE_ALPHA;
    alphaParam.frameNode = frameNode;
    alphaParam.opacityValue = 1;

    AnimationOption alphaOption;
    alphaOption.SetDuration(ANIMATION_HORIZONTAL_ENTRY_ALPHA_DURATION);
    alphaOption.SetCurve(Curves::LINEAR);
    alphaParam.option = alphaOption;
    Animation(alphaParam);
}

Color ArcSwiperPattern::GetBackgroundColorValue(const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_RETURN(frameNode, Color::TRANSPARENT);
    return frameNode->GetRenderContext()->GetBackgroundColor().value_or(Color::TRANSPARENT);
}

void ArcSwiperPattern::PlayVerticalExitAnimation(const OffsetF& offset, const RefPtr<FrameNode>& frameNode)
{
    preNodeBackgroundColor_ = GetBackgroundColorValue(frameNode);
    CHECK_NULL_VOID(frameNode);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);

    //scale
    renderContext->UpdateTransformScale({ 1.0f, 1.0f });
    AnimationParam scaleParam;
    scaleParam.type = AnimationType::TYPE_SCALE;
    scaleParam.frameNode = frameNode;
    scaleParam.scaleValue = ANIMATION_VERTICAL_EXIT_SCALE_VALUE;

    AnimationOption scaleOption;
    scaleOption.SetDuration(ANIMATION_VERTICAL_EXIT_SCALE_DURATION);
    scaleOption.SetCurve(Curves::FRICTION);
    scaleParam.option = scaleOption;
    Animation(scaleParam);

    //Offset
    AnimationParam offsetParam;
    offsetParam.type = AnimationType::TYPE_OFFSET;
    offsetParam.frameNode = frameNode;
    offsetParam.offset = offset;

    AnimationOption offsetOption;
    offsetOption.SetDuration(ANIMATION_VERTICAL_EXIT_OFFSET_DURATION);
    offsetOption.SetCurve(Curves::FRICTION);
    offsetParam.option = offsetOption;
    Animation(offsetParam);

    //blur
    BlurOption blurOption;
    renderContext->UpdateBackBlur(Dimension(ANIMATION_VERTICAL_EXIT_BLUR_INITIAL_VALUE, DimensionUnit::PERCENT),
        blurOption);
    AnimationParam blurParam;
    blurParam.type = AnimationType::TYPE_BLUR;
    blurParam.frameNode = frameNode;
    blurParam.blurValue = ANIMATION_VERTICAL_EXIT_BLUR_VALUE;

    AnimationOption blurAnimationOption;
    blurAnimationOption.SetDuration(ANIMATION_VERTICAL_EXIT_BLUR_DURATION);
    blurAnimationOption.SetCurve(Curves::LINEAR);
    blurParam.option = blurAnimationOption;
    Animation(blurParam);

    //alpha
    renderContext->UpdateOpacity(1);
    AnimationParam alphaParam;
    alphaParam.type = AnimationType::TYPE_ALPHA;
    alphaParam.frameNode = frameNode;
    alphaParam.opacityValue = 0;

    AnimationOption alphaOption;
    alphaOption.SetDuration(ANIMATION_VERTICAL_EXIT_ALPHA_DURATION);
    alphaOption.SetCurve(Curves::LINEAR);
    alphaParam.option = alphaOption;
    Animation(alphaParam);
}

void ArcSwiperPattern::PlayVerticalEntryAnimation(const OffsetF& offset, const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);

    //scale
    renderContext->UpdateTransformScale({ ANIMATION_VERTICAL_ENTRY_SCALE_VALUE, ANIMATION_VERTICAL_ENTRY_SCALE_VALUE });
    AnimationParam scaleParam;
    scaleParam.type = AnimationType::TYPE_SCALE;
    scaleParam.frameNode = frameNode;
    scaleParam.scaleValue = 1.0f;

    AnimationOption scaleOption;
    scaleOption.SetDelay(ANIMATION_VERTICAL_ENTRY_SCALE_DELAY);
    scaleOption.SetDuration(ANIMATION_VERTICAL_ENTRY_SCALE_DURATION);
    scaleOption.SetCurve(Curves::FRICTION);
    scaleParam.option = scaleOption;
    Animation(scaleParam);

    //Offset
    AnimationParam offsetParam;
    offsetParam.type = AnimationType::TYPE_OFFSET;
    offsetParam.frameNode = frameNode;
    offsetParam.offset = offset;

    AnimationOption offsetOption;
    offsetOption.SetDelay(ANIMATION_VERTICAL_ENTRY_OFFSET_DELAY);
    offsetOption.SetDuration(ANIMATION_VERTICAL_ENTRY_OFFSET_DURATION);
    offsetOption.SetCurve(Curves::FRICTION);
    offsetParam.option = offsetOption;
    Animation(offsetParam);

    //alpha
    renderContext->UpdateOpacity(0);
    AnimationParam alphaParam;
    alphaParam.type = AnimationType::TYPE_ALPHA;
    alphaParam.frameNode = frameNode;
    alphaParam.opacityValue = 1;

    AnimationOption alphaOption;
    alphaOption.SetDelay(ANIMATION_VERTICAL_ENTRY_ALPHA_DELAY);
    alphaOption.SetDuration(ANIMATION_VERTICAL_ENTRY_ALPHA_DURATION);
    alphaOption.SetCurve(Curves::LINEAR);
    alphaParam.option = alphaOption;
    Animation(alphaParam);

    //color
    renderContext->OnBackgroundColorUpdate(preNodeBackgroundColor_);
    Color bgColor = GetBackgroundColorValue(frameNode);
    AnimationParam colorParam;
    colorParam.type = AnimationType::TYPE_COLOR;
    colorParam.frameNode = frameNode;
    colorParam.backColor = bgColor;

    AnimationOption colorOption;
    colorOption.SetDuration(ANIMATION_VERTICAL_ENTRY_COLOR_DURATION);
    colorOption.SetCurve(Curves::LINEAR);
    colorParam.option = colorOption;
    Animation(colorParam);
}

bool ArcSwiperPattern::IsScrollOverCritical()
{
    if (targetIndex_.value() == currentIndex_) {
        return false;
    }
    return true;
}

void ArcSwiperPattern::PlayAnimation(const OffsetF& offset, const RefPtr<FrameNode>& frameNode, int32_t index)
{
    if (IsScrollOverCritical()) {
        if (GetDirection() == Axis::HORIZONTAL) {
            PlayHorizontalAnimation(offset, frameNode, index);
        } else {
            PlayVerticalAnimation(offset, frameNode, index);
        }
    } else {
        frameNode->GetRenderContext()->UpdateTransformScale({1.0f, 1.0f});
        frameNode->GetRenderContext()->UpdateOpacity(1);
        frameNode->GetRenderContext()->UpdateTranslateInXY(offset);
    }
}

void ArcSwiperPattern::PlayDisplacementAnimation(SwiperLayoutAlgorithm::PositionMap &positionMap, const OffsetF &offset)
{
    int32_t index = 0;
    for (auto &item : positionMap) {
        auto frameNode = item.second.node;
        if (frameNode) {
            PlayAnimation(offset, frameNode, index);
            index++;
            item.second.finalOffset = offset;
        }
    }
}
} // namespace OHOS::Ace::NG