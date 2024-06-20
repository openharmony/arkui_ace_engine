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
constexpr float HORIZONTAL_EXIT_SCALE_VALUE = 0.6f;
constexpr int32_t HORIZONTAL_EXIT_SCALE_DURATION = 750;
constexpr int32_t HORIZONTAL_EXIT_OFFSET_DURATION = 750;
constexpr int32_t HORIZONTAL_EXIT_BLUR_VALUE = 30;
constexpr int32_t HORIZONTAL_EXIT_BLUR_DELAY = 150;
constexpr int32_t HORIZONTAL_EXIT_BLUR_DURATION = 250;
constexpr int32_t HORIZONTAL_EXIT_ALPHA_DURATION = 750;

constexpr float HORIZONTAL_ENTRY_SCALE_VALUE = 0.6f;
constexpr int32_t HORIZONTAL_ENTRY_SCALE_DURATION = 750;
constexpr int32_t HORIZONTAL_ENTRY_OFFSET_DURATION = 750;
constexpr int32_t HORIZONTAL_ENTRY_BLUR_VALUE = 30;
constexpr int32_t HORIZONTAL_ENTRY_BLUR_DURATION = 250;
constexpr int32_t HORIZONTAL_ENTRY_ALPHA_DURATION = 500;

constexpr float VERTICAL_EXIT_SCALE_VALUE = 0.95f;
constexpr int32_t VERTICAL_EXIT_SCALE_DURATION = 330;
constexpr int32_t VERTICAL_EXIT_OFFSET_DURATION = 750;
constexpr int32_t VERTICAL_EXIT_BLUR_INITIAL_VALUE = 70;
constexpr int32_t VERTICAL_EXIT_BLUR_VALUE = 100;
constexpr int32_t VERTICAL_EXIT_BLUR_DURATION = 330;
constexpr int32_t VERTICAL_EXIT_ALPHA_DURATION = 200;

constexpr float VERTICAL_ENTRY_SCALE_VALUE = 101.5 / 100;
constexpr int32_t VERTICAL_ENTRY_SCALE_DELAY = 130;
constexpr int32_t VERTICAL_ENTRY_SCALE_DURATION = 200;
constexpr int32_t VERTICAL_ENTRY_OFFSET_DELAY = 130;
constexpr int32_t VERTICAL_ENTRY_OFFSET_DURATION = 200;
constexpr int32_t VERTICAL_ENTRY_ALPHA_DELAY = 130;
constexpr int32_t VERTICAL_ENTRY_ALPHA_DURATION = 200;
constexpr int32_t VERTICAL_ENTRY_COLOR_DURATION = 40;

constexpr int32_t HALF = 2;
constexpr int32_t ANIMATION_SIZE = 8;
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

void ArcSwiperPattern::BuildAnimationFinishCallback(const AnimationParam& param,
    const RefPtr<RenderContext>& renderContext, bool exit, FinishCallback& finishCallback)
{
    BlurOption blurOption;
    finishCallback = [weak = WeakClaim(this), param, blurOption, renderContext, exit]() {
        auto swiper = weak.Upgrade();
        CHECK_NULL_VOID(swiper);
        if (param.type == AnimationType::TYPE_SCALE) {
            renderContext->UpdateTransformScale({ 1.0f, 1.0f });
            if (exit) {
                swiper->AddFinishAnimation(AnimationFinishType::EXIT_SCALE);
            } else {
                swiper->AddFinishAnimation(AnimationFinishType::ENTRY_SCALE);
            }
        } else if (param.type == AnimationType::TYPE_ALPHA) {
            renderContext->UpdateOpacity(1);
            if (exit) {
                swiper->AddFinishAnimation(AnimationFinishType::EXIT_ALPHA);
            } else {
                swiper->AddFinishAnimation(AnimationFinishType::ENTRY_ALPHA);
            }
        } else if (param.type == AnimationType::TYPE_BLUR) {
            renderContext->UpdateBackBlur(Dimension(0, DimensionUnit::PERCENT), blurOption);
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
            renderContext->OnBackgroundColorUpdate(swiper->GetBackgroundColorValue(param.frameNode));
            if (exit) {
                swiper->AddFinishAnimation(AnimationFinishType::EXIT_BACKGROUND);
            } else {
                swiper->AddFinishAnimation(AnimationFinishType::ENTRY_BACKGROUND);
            }
        }
    };
}

std::shared_ptr<AnimationUtils::Animation> ArcSwiperPattern::Animation(const AnimationParam& param, bool exit)
{
    auto frameNode = param.frameNode;
    BlurOption blurOption;
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_RETURN(renderContext, nullptr);
    
    FinishCallback finishCallback;
    BuildAnimationFinishCallback(param, renderContext, exit, finishCallback);
    auto propertyCallback = [param, blurOption, renderContext]() {
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
    };
    return AnimationUtils::StartAnimation(param.option, propertyCallback, finishCallback);
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
    scaleParam.scaleValue = HORIZONTAL_EXIT_SCALE_VALUE;

    AnimationOption scaleOption;
    scaleOption.SetDuration(HORIZONTAL_EXIT_SCALE_DURATION);
    scaleOption.SetCurve(Curves::FRICTION);
    scaleParam.option = scaleOption;
    animationVector_.push_back(Animation(scaleParam, true));

    //Offset
    AnimationParam offsetParam;
    offsetParam.type = AnimationType::TYPE_OFFSET;
    offsetParam.frameNode = frameNode;
    offsetParam.offset = offset;

    AnimationOption offsetOption;
    offsetOption.SetDuration(HORIZONTAL_EXIT_OFFSET_DURATION);
    offsetOption.SetCurve(Curves::FRICTION);
    ElementRegister::GetInstance()->ReSyncGeometryTransition(GetHost(), offsetOption);
    offsetParam.option = offsetOption;
    animationVector_.push_back(Animation(offsetParam, true));

    //blur
    BlurOption blurOption;
    renderContext->UpdateBackBlur(Dimension(0, DimensionUnit::PERCENT), blurOption);
    AnimationParam blurParam;
    blurParam.type = AnimationType::TYPE_BLUR;
    blurParam.frameNode = frameNode;
    blurParam.blurValue = HORIZONTAL_EXIT_BLUR_VALUE;

    AnimationOption blurAnimationOption;
    blurAnimationOption.SetDelay(HORIZONTAL_EXIT_BLUR_DELAY);
    blurAnimationOption.SetDuration(HORIZONTAL_EXIT_BLUR_DURATION);
    blurAnimationOption.SetCurve(Curves::LINEAR);
    blurParam.option = blurAnimationOption;
    animationVector_.push_back(Animation(blurParam, true));

    //alpha
    renderContext->UpdateOpacity(1);
    AnimationParam alphaParam;
    alphaParam.type = AnimationType::TYPE_ALPHA;
    alphaParam.frameNode = frameNode;
    alphaParam.opacityValue = 0;

    AnimationOption alphaOption;
    alphaOption.SetDuration(HORIZONTAL_EXIT_ALPHA_DURATION);
    alphaOption.SetCurve(Curves::LINEAR);
    alphaParam.option = alphaOption;
    animationVector_.push_back(Animation(alphaParam, true));
}

void ArcSwiperPattern::PlayHorizontalEntryAnimation(const OffsetF& offset, const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);

    //scale
    renderContext->UpdateTransformScale(
        {HORIZONTAL_ENTRY_SCALE_VALUE, HORIZONTAL_ENTRY_SCALE_VALUE});
    AnimationParam scaleParam;
    scaleParam.type = AnimationType::TYPE_SCALE;
    scaleParam.frameNode = frameNode;
    scaleParam.scaleValue = 1.0f;

    AnimationOption scaleOption;
    scaleOption.SetDuration(HORIZONTAL_ENTRY_SCALE_DURATION);
    scaleOption.SetCurve(Curves::FRICTION);
    scaleParam.option = scaleOption;
    animationVector_.push_back(Animation(scaleParam, false));

    //Offset
    AnimationParam offsetParam;
    offsetParam.type = AnimationType::TYPE_OFFSET;
    offsetParam.frameNode = frameNode;
    offsetParam.offset = offset;

    AnimationOption offsetOption;
    offsetOption.SetDuration(HORIZONTAL_ENTRY_OFFSET_DURATION);
    offsetOption.SetCurve(Curves::FRICTION);
    ElementRegister::GetInstance()->ReSyncGeometryTransition(GetHost(), offsetOption);
    offsetParam.option = offsetOption;
    animationVector_.push_back(Animation(offsetParam, false));

    //blur
    BlurOption blurOption;
    renderContext->UpdateBackBlur(Dimension(HORIZONTAL_ENTRY_BLUR_VALUE, DimensionUnit::PERCENT), blurOption);
    AnimationParam blurParam;
    blurParam.type = AnimationType::TYPE_BLUR;
    blurParam.frameNode = frameNode;
    blurParam.blurValue = 0;

    AnimationOption blurAnimationOption;
    blurAnimationOption.SetDuration(HORIZONTAL_ENTRY_BLUR_DURATION);
    blurAnimationOption.SetCurve(Curves::LINEAR);
    blurParam.option = blurAnimationOption;
    animationVector_.push_back(Animation(blurParam, false));

    //alpha
    renderContext->UpdateOpacity(0);
    AnimationParam alphaParam;
    alphaParam.type = AnimationType::TYPE_ALPHA;
    alphaParam.frameNode = frameNode;
    alphaParam.opacityValue = 1;

    AnimationOption alphaOption;
    alphaOption.SetDuration(HORIZONTAL_ENTRY_ALPHA_DURATION);
    alphaOption.SetCurve(Curves::LINEAR);
    alphaParam.option = alphaOption;
    animationVector_.push_back(Animation(alphaParam, false));
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
    scaleParam.scaleValue = VERTICAL_EXIT_SCALE_VALUE;

    AnimationOption scaleOption;
    scaleOption.SetDuration(VERTICAL_EXIT_SCALE_DURATION);
    scaleOption.SetCurve(Curves::FRICTION);
    scaleParam.option = scaleOption;
    animationVector_.push_back(Animation(scaleParam, true));

    //Offset
    AnimationParam offsetParam;
    offsetParam.type = AnimationType::TYPE_OFFSET;
    offsetParam.frameNode = frameNode;
    offsetParam.offset = offset;

    AnimationOption offsetOption;
    offsetOption.SetDuration(VERTICAL_EXIT_OFFSET_DURATION);
    offsetOption.SetCurve(Curves::FRICTION);
    ElementRegister::GetInstance()->ReSyncGeometryTransition(GetHost(), offsetOption);
    offsetParam.option = offsetOption;
    animationVector_.push_back(Animation(offsetParam, true));

    //blur
    BlurOption blurOption;
    renderContext->UpdateBackBlur(Dimension(VERTICAL_EXIT_BLUR_INITIAL_VALUE, DimensionUnit::PERCENT),
        blurOption);
    AnimationParam blurParam;
    blurParam.type = AnimationType::TYPE_BLUR;
    blurParam.frameNode = frameNode;
    blurParam.blurValue = VERTICAL_EXIT_BLUR_VALUE;

    AnimationOption blurAnimationOption;
    blurAnimationOption.SetDuration(VERTICAL_EXIT_BLUR_DURATION);
    blurAnimationOption.SetCurve(Curves::LINEAR);
    blurParam.option = blurAnimationOption;
    animationVector_.push_back(Animation(blurParam, true));

    //alpha
    renderContext->UpdateOpacity(1);
    AnimationParam alphaParam;
    alphaParam.type = AnimationType::TYPE_ALPHA;
    alphaParam.frameNode = frameNode;
    alphaParam.opacityValue = 0;

    AnimationOption alphaOption;
    alphaOption.SetDuration(VERTICAL_EXIT_ALPHA_DURATION);
    alphaOption.SetCurve(Curves::LINEAR);
    alphaParam.option = alphaOption;
    animationVector_.push_back(Animation(alphaParam, true));
}

void ArcSwiperPattern::PlayVerticalEntryAnimation(const OffsetF& offset, const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);

    //scale
    renderContext->UpdateTransformScale({ VERTICAL_ENTRY_SCALE_VALUE, VERTICAL_ENTRY_SCALE_VALUE });
    AnimationParam scaleParam;
    scaleParam.type = AnimationType::TYPE_SCALE;
    scaleParam.frameNode = frameNode;
    scaleParam.scaleValue = 1.0f;

    AnimationOption scaleOption;
    scaleOption.SetDelay(VERTICAL_ENTRY_SCALE_DELAY);
    scaleOption.SetDuration(VERTICAL_ENTRY_SCALE_DURATION);
    scaleOption.SetCurve(Curves::FRICTION);
    scaleParam.option = scaleOption;
    animationVector_.push_back(Animation(scaleParam, false));

    //Offset
    AnimationParam offsetParam;
    offsetParam.type = AnimationType::TYPE_OFFSET;
    offsetParam.frameNode = frameNode;
    offsetParam.offset = offset;

    AnimationOption offsetOption;
    offsetOption.SetDelay(VERTICAL_ENTRY_OFFSET_DELAY);
    offsetOption.SetDuration(VERTICAL_ENTRY_OFFSET_DURATION);
    offsetOption.SetCurve(Curves::FRICTION);
    ElementRegister::GetInstance()->ReSyncGeometryTransition(GetHost(), offsetOption);
    offsetParam.option = offsetOption;
    animationVector_.push_back(Animation(offsetParam, false));

    //alpha
    renderContext->UpdateOpacity(0);
    AnimationParam alphaParam;
    alphaParam.type = AnimationType::TYPE_ALPHA;
    alphaParam.frameNode = frameNode;
    alphaParam.opacityValue = 1;

    AnimationOption alphaOption;
    alphaOption.SetDelay(VERTICAL_ENTRY_ALPHA_DELAY);
    alphaOption.SetDuration(VERTICAL_ENTRY_ALPHA_DURATION);
    alphaOption.SetCurve(Curves::LINEAR);
    alphaParam.option = alphaOption;
    animationVector_.push_back(Animation(alphaParam, false));

    //color
    renderContext->OnBackgroundColorUpdate(preNodeBackgroundColor_);
    Color bgColor = GetBackgroundColorValue(frameNode);
    AnimationParam colorParam;
    colorParam.type = AnimationType::TYPE_COLOR;
    colorParam.frameNode = frameNode;
    colorParam.backColor = bgColor;

    AnimationOption colorOption;
    colorOption.SetDuration(VERTICAL_ENTRY_COLOR_DURATION);
    colorOption.SetCurve(Curves::LINEAR);
    colorParam.option = colorOption;
    animationVector_.push_back(Animation(colorParam, false));
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
    PerfMonitor::GetPerfMonitor()->Start(PerfConstants::APP_SWIPER_FLING, PerfActionType::FIRST_MOVE, "");
    if (IsScrollOverCritical()) {
        if (GetDirection() == Axis::HORIZONTAL) {
            PlayHorizontalAnimation(offset, frameNode, index);
        } else {
            PlayVerticalAnimation(offset, frameNode, index);
        }
    } else {
        InitialFrameNodePropertyAnimation(frameNode, offset);
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
            PlayAnimation(offset, frameNode, index);
            index++;
            item.second.finalOffset = offset;
        }
    }
    itemPositionInAnimation_ = itemPosition_;
}

void ArcSwiperPattern::InitialFrameNodePropertyAnimation(const RefPtr<FrameNode>& frameNode, const OffsetF& offset)
{
    for (auto animaiton: animationVector_) {
        AnimationUtils::StopAnimation(animaiton);
    }
    AnimationOption option;
    option.SetCurve(Curves::LINEAR);
    option.SetDuration(0);
    auto upgradeCallback = [weak = WeakClaim(this), frameNode, offset]() {
        auto swiper = weak.Upgrade();
        CHECK_NULL_VOID(swiper);
        frameNode->GetRenderContext()->UpdateTranslateInXY(offset);
        frameNode->GetRenderContext()->OnBackgroundColorUpdate(swiper->GetBackgroundColorValue(frameNode));
        frameNode->GetRenderContext()->UpdateTransformScale({1.0f, 1.0f});
        frameNode->GetRenderContext()->UpdateOpacity(1);

        BlurOption blurOption;
        frameNode->GetRenderContext()->UpdateBackBlur(Dimension(0, DimensionUnit::PERCENT), blurOption);
    };
    AnimationUtils::Animate(option, upgradeCallback);
}

void ArcSwiperPattern::CancelFrameNodePropertyAnimation(const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_VOID(frameNode);
    for (auto animaiton: animationVector_) {
        AnimationUtils::StopAnimation(animaiton);
    }
    frameNode->GetRenderContext()->CancelTranslateXYAnimation();
    frameNode->GetRenderContext()->OnBackgroundColorUpdate(GetBackgroundColorValue(frameNode));
    frameNode->GetRenderContext()->UpdateTransformScale({1.0f, 1.0f});
    frameNode->GetRenderContext()->UpdateOpacity(1);

    BlurOption blurOption;
    frameNode->GetRenderContext()->UpdateBackBlur(Dimension(0, DimensionUnit::PERCENT), blurOption);
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

    // initial translate info.
    for (auto& item : itemPosition_) {
        auto frameNode = item.second.node;
        if (frameNode) {
            InitialFrameNodePropertyAnimation(frameNode, item.second.finalOffset);
        }
    }

    usePropertyAnimation_ = true;
    propertyAnimationIndex_ = nextIndex;
    PlayPropertyTranslateFlipAnimation(offset);
    HandlePropertyTranslateCallback(translate, nextIndex, velocity);
    
    // enable lazy load feature.
    SetLazyLoadFeature(true);
    UpdateItemRenderGroup(true);
}

bool ArcSwiperPattern::IsLoop() const
{
    return false;
}
} // namespace OHOS::Ace::NG
