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

constexpr float VERTICAL_ENTRY_SCALE_VALUE = 101.5 / 100;
constexpr int32_t VERTICAL_ENTRY_SCALE_DELAY = 130;
constexpr int32_t VERTICAL_ENTRY_SCALE_DURATION = 200;
constexpr int32_t VERTICAL_ENTRY_OFFSET_DELAY = 130;
constexpr int32_t VERTICAL_ENTRY_OFFSET_DURATION = 200;
constexpr int32_t VERTICAL_ENTRY_ALPHA_DELAY = 130;
constexpr int32_t VERTICAL_ENTRY_ALPHA_DURATION = 200;
constexpr int32_t VERTICAL_ENTRY_COLOR_DURATION = 40;

constexpr float HORIZONTAL_SCALE_REDUCTION_FACTOR = 0.4f;
constexpr float HORIZONTAL_BLUR_MIN_RATIO = 0.2f;
constexpr float HORIZONTAL_BLUR_REDUCTION_FACTOR = 750 / 250 * 30;
constexpr float HORIZONTAL_BLUR_MAX_VALUE = 30;
constexpr float HORIZONTAL_ALPHA_REDUCTION_FACTOR = 750 / 500;

constexpr float VERTICAL_EXIT_SCALE_REDUCTION_FACTOR = 0.05f;
constexpr float VERTICAL_EXIT_SCALE_MIN_VALUE = 0.95f;
constexpr float VERTICAL_EXIT_BLUR_INCREASE_FACTOR = 30;
constexpr float VERTICAL_EXIT_BLUR_MAX_VALUE = 100;
constexpr float VERTICAL_EXIT_ALPHA_MIN_RATIO = 0.25f;
constexpr float VERTICAL_EXIT_ALPHA_REDUCTION_FACTOR = 2.32f;
constexpr float VERTICAL_EXIT_ALPHA_AT_CRITICAL_POINT = 0.42f;
constexpr float VERTICAL_EXIT_ALPHA_REDUCTION_FACTOR_AFTER_CRITICAL_POINT = 0.63f;

constexpr float VERTICAL_ENTRY_CRITICAL_POINT_OF_COLOR = 0.25f;
constexpr float VERTICAL_ENTRY_CRITICAL_POINT_OF_OTHER = 130 / 330;
constexpr float VERTICAL_ENTRY_SCALE_INITIAL_VALUE = 1.015f;
constexpr float VERTICAL_ENTRY_SCALE_REDUCTION_FACTOR = 0.015f;
constexpr float VERTICAL_ENTRY_WHOLE_REDUCTION_FACTOR = 330 / 200;
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

void ArcSwiperPattern::PlayHorizontalAnimation(const OffsetF& offset, int32_t index, RefPtr<FrameNode>& frameNode)
{
    if (IsPreItem(index, offset.GetX())) {
        PlayHorizontalExitAnimation(offset, frameNode);
    } else {
        PlayHorizontalEntryAnimation(offset, frameNode);
    }
}

void ArcSwiperPattern::PlayVerticalAnimation(const OffsetF& offset, int32_t index, RefPtr<FrameNode>& frameNode)
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
    RefPtr<RenderContext>& renderContext, FinishCallback& finishCallback)
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

void ArcSwiperPattern::PlayHorizontalExitAnimation(const OffsetF& offset, RefPtr<FrameNode>& frameNode)
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
    scaleOption.SetDuration(HORIZONTAL_EXIT_SCALE_DURATION);
    scaleOption.SetCurve(Curves::FRICTION);
    scaleParam.option = scaleOption;
    animationVector_.push_back(Animation(true, scaleParam));

    // offset
    AnimationParam offsetParam;
    offsetParam.type = AnimationType::TYPE_OFFSET;
    offsetParam.frameNode = frameNode;
    offsetParam.offset = offset;

    AnimationOption offsetOption;
    offsetOption.SetDuration(HORIZONTAL_EXIT_OFFSET_DURATION);
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
    blurAnimationOption.SetDelay(HORIZONTAL_EXIT_BLUR_DELAY);
    blurAnimationOption.SetDuration(HORIZONTAL_EXIT_BLUR_DURATION);
    blurAnimationOption.SetCurve(Curves::LINEAR);
    blurParam.option = blurAnimationOption;
    animationVector_.push_back(Animation(true, blurParam));

    // alpha
    renderContext->UpdateOpacity(horizontalExitNodeOpacity_);
    AnimationParam alphaParam;
    alphaParam.type = AnimationType::TYPE_ALPHA;
    alphaParam.frameNode = frameNode;
    alphaParam.opacityValue = 0;

    AnimationOption alphaOption;
    alphaOption.SetDuration(HORIZONTAL_EXIT_ALPHA_DURATION);
    alphaOption.SetCurve(Curves::LINEAR);
    alphaParam.option = alphaOption;
    animationVector_.push_back(Animation(true, alphaParam));
}

void ArcSwiperPattern::PlayHorizontalEntryAnimation(const OffsetF& offset, RefPtr<FrameNode>& frameNode)
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
    scaleOption.SetDuration(HORIZONTAL_ENTRY_SCALE_DURATION);
    scaleOption.SetCurve(Curves::FRICTION);
    scaleParam.option = scaleOption;
    animationVector_.push_back(Animation(false, scaleParam));

    // offset
    AnimationParam offsetParam;
    offsetParam.type = AnimationType::TYPE_OFFSET;
    offsetParam.frameNode = frameNode;
    offsetParam.offset = offset;

    AnimationOption offsetOption;
    offsetOption.SetDuration(HORIZONTAL_ENTRY_OFFSET_DURATION);
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
    blurParam.blurValue = 0;

    AnimationOption blurAnimationOption;
    blurAnimationOption.SetDuration(HORIZONTAL_ENTRY_BLUR_DURATION);
    blurAnimationOption.SetCurve(Curves::LINEAR);
    blurParam.option = blurAnimationOption;
    animationVector_.push_back(Animation(false, blurParam));

    // alpha
    renderContext->UpdateOpacity(horizontalEntryNodeOpacity_);
    AnimationParam alphaParam;
    alphaParam.type = AnimationType::TYPE_ALPHA;
    alphaParam.frameNode = frameNode;
    alphaParam.opacityValue = 1;

    AnimationOption alphaOption;
    alphaOption.SetDuration(HORIZONTAL_ENTRY_ALPHA_DURATION);
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

void ArcSwiperPattern::PlayVerticalExitAnimation(const OffsetF& offset, RefPtr<FrameNode>& frameNode)
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
    scaleOption.SetDuration(VERTICAL_EXIT_SCALE_DURATION);
    scaleOption.SetCurve(Curves::FRICTION);
    scaleParam.option = scaleOption;
    animationVector_.push_back(Animation(true, scaleParam));

    // offset
    AnimationParam offsetParam;
    offsetParam.type = AnimationType::TYPE_OFFSET;
    offsetParam.frameNode = frameNode;
    offsetParam.offset = offset;

    AnimationOption offsetOption;
    offsetOption.SetDuration(VERTICAL_EXIT_OFFSET_DURATION);
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
    blurAnimationOption.SetDuration(VERTICAL_EXIT_BLUR_DURATION);
    blurAnimationOption.SetCurve(Curves::LINEAR);
    blurParam.option = blurAnimationOption;
    animationVector_.push_back(Animation(true, blurParam));

    // alpha
    renderContext->UpdateOpacity(verticalExitNodeOpacity_);
    AnimationParam alphaParam;
    alphaParam.type = AnimationType::TYPE_ALPHA;
    alphaParam.frameNode = frameNode;
    alphaParam.opacityValue = 0;

    AnimationOption alphaOption;
    alphaOption.SetDuration(VERTICAL_EXIT_ALPHA_DURATION);
    alphaOption.SetCurve(Curves::LINEAR);
    alphaParam.option = alphaOption;
    animationVector_.push_back(Animation(true, alphaParam));
}

void ArcSwiperPattern::PlayVerticalEntryAnimation(const OffsetF& offset, RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto renderContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);

    // scale
    renderContext->UpdateTransformScale({ verticalEntryNodeScale_, verticalEntryNodeScale_ });
    AnimationParam scaleParam;
    scaleParam.type = AnimationType::TYPE_SCALE;
    scaleParam.frameNode = frameNode;
    scaleParam.scaleValue = 1.0f;

    AnimationOption scaleOption;
    scaleOption.SetDelay(VERTICAL_ENTRY_SCALE_DELAY);
    scaleOption.SetDuration(VERTICAL_ENTRY_SCALE_DURATION);
    scaleOption.SetCurve(Curves::FRICTION);
    scaleParam.option = scaleOption;
    animationVector_.push_back(Animation(false, scaleParam));

    // offset
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
    animationVector_.push_back(Animation(false, offsetParam));

    // alpha
    renderContext->UpdateOpacity(verticalEntryNodeOpacity_);
    AnimationParam alphaParam;
    alphaParam.type = AnimationType::TYPE_ALPHA;
    alphaParam.frameNode = frameNode;
    alphaParam.opacityValue = 1;

    AnimationOption alphaOption;
    alphaOption.SetDelay(VERTICAL_ENTRY_ALPHA_DELAY);
    alphaOption.SetDuration(VERTICAL_ENTRY_ALPHA_DURATION);
    alphaOption.SetCurve(Curves::LINEAR);
    alphaParam.option = alphaOption;
    animationVector_.push_back(Animation(false, alphaParam));

    // color
    if (entryNodeBackground_) {
        AnimationParam colorParam;
        colorParam.type = AnimationType::TYPE_COLOR;
        colorParam.frameNode = frameNode;
        colorParam.backColor = *entryNodeBackground_;

        AnimationOption colorOption;
        colorOption.SetDuration(VERTICAL_ENTRY_COLOR_DURATION);
        colorOption.SetCurve(Curves::LINEAR);
        colorParam.option = colorOption;
        animationVector_.push_back(Animation(false, colorParam));
    }
}

bool ArcSwiperPattern::IsScrollOverCritical()
{
    if (targetIndex_.value() == currentIndex_) {
        return false;
    }
    return true;
}

void ArcSwiperPattern::PlayAnimation(const OffsetF& offset, int32_t index, RefPtr<FrameNode>& frameNode)
{
    PerfMonitor::GetPerfMonitor()->Start(PerfConstants::APP_SWIPER_FLING, PerfActionType::FIRST_MOVE, "");
    if (IsScrollOverCritical()) {
        if (GetDirection() == Axis::HORIZONTAL) {
            PlayHorizontalAnimation(offset, index, frameNode);
        } else {
            PlayVerticalAnimation(offset, index, frameNode);
        }
    } else {
        InitialFrameNodePropertyAnimation(offset, frameNode);
    }
    MarkDirtyNodeSelf();
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

void ArcSwiperPattern::InitialFrameNodePropertyAnimation(const OffsetF& offset, RefPtr<FrameNode>& frameNode)
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
        frameNode->GetRenderContext()->UpdateOpacity(1);
        frameNode->GetRenderContext()->UpdateTransformScale({1.0f, 1.0f});
        BlurOption blurOption;
        frameNode->GetRenderContext()->UpdateBackBlur(Dimension(0, DimensionUnit::PERCENT), blurOption);
        frameNode->GetRenderContext()->UpdateTranslateInXY(offset);
        auto colorPtr = swiper->GetBackgroundColorValue(frameNode);
        CHECK_NULL_VOID(colorPtr);
        frameNode->GetRenderContext()->OnBackgroundColorUpdate(*colorPtr);
    };
    AnimationUtils::Animate(option, upgradeCallback);
}

void ArcSwiperPattern::CancelFrameNodePropertyAnimation(RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_VOID(frameNode);
    for (auto animaiton: animationVector_) {
        AnimationUtils::StopAnimation(animaiton);
    }
    animationVector_.clear();
    frameNode->GetRenderContext()->UpdateOpacity(1);
    frameNode->GetRenderContext()->UpdateTransformScale({1.0f, 1.0f});
    BlurOption blurOption;
    frameNode->GetRenderContext()->UpdateBackBlur(Dimension(0, DimensionUnit::PERCENT), blurOption);
    frameNode->GetRenderContext()->CancelTranslateXYAnimation();
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

void ArcSwiperPattern::ResetScrollAnimation()
{
    for (auto animation: scrollAnimationVector_) {
        AnimationUtils::StopAnimation(animation);
    }
    scrollAnimationVector_.clear();

    for (auto& item : itemPosition_) {
        auto node = item.second.node;
        CHECK_NULL_VOID(node);
        auto context = node->GetRenderContext();
        CHECK_NULL_VOID(context);
        BlurOption blurOption;
        context->UpdateBackBlur(Dimension(0, DimensionUnit::PERCENT), blurOption);
        context->UpdateOpacity(1);
        context->UpdateTransformScale({1.0, 1.0});
        auto colorPtr = GetBackgroundColorValue(node);
        if (colorPtr) {
            context->OnBackgroundColorUpdate(*colorPtr);
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
            InitialFrameNodePropertyAnimation(item.second.finalOffset, frameNode);
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

void ArcSwiperPattern::PlayScrollScaleAnimation(float scale, RefPtr<RenderContext>& renderContext)
{
    AnimationOption option;
    option.SetDelay(0);
    option.SetDuration(0);
    option.SetCurve(Curves::FRICTION);
    auto updateCallback = [weakRenderContext = WeakPtr<RenderContext>(renderContext), scale]() {
        auto renderContext = weakRenderContext.Upgrade();
        CHECK_NULL_VOID(renderContext);
        renderContext->UpdateTransformScale({scale, scale});
    };
    scrollAnimationVector_.push_back(AnimationUtils::StartAnimation(option, updateCallback));
}

void ArcSwiperPattern::PlayScrollBlurAnimation(float blur, RefPtr<RenderContext>& renderContext)
{
    AnimationOption option;
    option.SetDelay(0);
    option.SetDuration(0);
    option.SetCurve(Curves::LINEAR);
    auto updateCallback = [weakRenderContext = WeakPtr<RenderContext>(renderContext), blur]() {
        BlurOption blurOption;
        auto renderContext = weakRenderContext.Upgrade();
        CHECK_NULL_VOID(renderContext);
        renderContext->UpdateBackBlur(Dimension(blur, DimensionUnit::PERCENT), blurOption);
    };
    scrollAnimationVector_.push_back(AnimationUtils::StartAnimation(option, updateCallback));
}

void ArcSwiperPattern::PlayScrollAlpahAnimation(float alpha, RefPtr<RenderContext>& renderContext)
{
    AnimationOption option;
    option.SetDelay(0);
    option.SetDuration(0);
    option.SetCurve(Curves::LINEAR);
    auto updateCallback = [weakRenderContext = WeakPtr<RenderContext>(renderContext), alpha]() {
        auto renderContext = weakRenderContext.Upgrade();
        CHECK_NULL_VOID(renderContext);
        renderContext->UpdateOpacity(alpha);
    };
    scrollAnimationVector_.push_back(AnimationUtils::StartAnimation(option, updateCallback));
}

void ArcSwiperPattern::PlayScrollBackgroundAnimation(const std::shared_ptr<Color>& color,
    RefPtr<RenderContext>& renderContext)
{
    CHECK_NULL_VOID(color);
    CHECK_NULL_VOID(renderContext);
    auto finishCallback = [weak = WeakClaim(this), color]() {
        auto swiper = weak.Upgrade();
        CHECK_NULL_VOID(swiper);
        swiper->preNodeBackgroundColor_ = color;
    };

    auto updateCallback = [weakRenderContext = WeakPtr<RenderContext>(renderContext), color]() {
        auto renderContext = weakRenderContext.Upgrade();
        CHECK_NULL_VOID(renderContext);
        renderContext->OnBackgroundColorUpdate(*color);
    };
    AnimationOption option;
    option.SetDelay(0);
    option.SetDuration(VERTICAL_ENTRY_COLOR_DURATION);
    option.SetCurve(Curves::LINEAR);
    scrollAnimationVector_.push_back(AnimationUtils::StartAnimation(option, updateCallback));
}

void ArcSwiperPattern::PlayHorizontalScrollExitAnimation(float swiperWidth, float startPos,
    RefPtr<FrameNode>& frameNode)
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
    PlayScrollScaleAnimation(horizontalExitNodeScale_, curContext);

    // blur
    if (exitNodePercent > HORIZONTAL_BLUR_MIN_RATIO) {
        horizontalExitNodeBlur_ = HORIZONTAL_BLUR_REDUCTION_FACTOR * exitNodePercent;
        if (horizontalExitNodeBlur_ > HORIZONTAL_BLUR_MAX_VALUE) {
            horizontalExitNodeBlur_ = HORIZONTAL_BLUR_MAX_VALUE;
        }
        PlayScrollBlurAnimation(horizontalExitNodeBlur_, curContext);
    }

    // alpha
    horizontalExitNodeOpacity_ = 1.0 - exitNodePercent;
    if (horizontalExitNodeOpacity_ < 0) {
        horizontalExitNodeOpacity_ = 0;
    }
    PlayScrollAlpahAnimation(horizontalExitNodeOpacity_, curContext);
}

void ArcSwiperPattern::PlayHorizontalScrollEntryAnimation(float swiperWidth, float startPos,
    RefPtr<FrameNode>& frameNode)
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
    if (horizontalEntryNodeScale_ >= 1) {
        horizontalEntryNodeScale_ = 1;
    }
    PlayScrollScaleAnimation(horizontalEntryNodeScale_, entryNodeContext);

    // blur
    horizontalEntryNodeBlur_ = HORIZONTAL_BLUR_MAX_VALUE - HORIZONTAL_BLUR_REDUCTION_FACTOR * entryNodePercent;
    if (horizontalEntryNodeBlur_ < 0) {
        horizontalEntryNodeBlur_ = 0;
    }
    PlayScrollBlurAnimation(horizontalEntryNodeBlur_, entryNodeContext);

    // alpha
    horizontalEntryNodeOpacity_ = HORIZONTAL_ALPHA_REDUCTION_FACTOR * entryNodePercent;
    if (horizontalEntryNodeOpacity_ > 1) {
        horizontalEntryNodeOpacity_ = 1;
    }
    PlayScrollAlpahAnimation(horizontalEntryNodeOpacity_, entryNodeContext);
}

void ArcSwiperPattern::HorizontalScrollAnimation()
{
    auto swiperWidth = CalculateVisibleSize();
    int32_t nextIndex = 0;
    if (gestureState_ == GestureState::GESTURE_STATE_FOLLOW_RIGHT) {
        nextIndex = currentIndex_ + 1;
    } else if (gestureState_ == GestureState::GESTURE_STATE_FOLLOW_LEFT) {
        nextIndex = currentIndex_ - 1;
    }
    auto nextInter = itemPosition_.find(nextIndex);
    if (nextInter == itemPosition_.end()) {
        ResetScrollAnimation();
        return;
    }
    auto curInter = itemPosition_.find(currentIndex_);
    if (curInter != itemPosition_.end()) {
        auto curStartPos = curInter->second.startPos;
        auto curFrameNode = curInter->second.node;
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
    int32_t nextIndex = 0;
    if (gestureState_ == GestureState::GESTURE_STATE_FOLLOW_RIGHT) {
        nextIndex = currentIndex_ + 1;
    } else if (gestureState_ == GestureState::GESTURE_STATE_FOLLOW_LEFT) {
        nextIndex = currentIndex_ - 1;
    }
 
    auto nextInter = itemPosition_.find(nextIndex);
    if (nextInter == itemPosition_.end()) {
        ResetScrollAnimation();
        return;
    }
    
    auto curInter = itemPosition_.find(currentIndex_);
    if (curInter != itemPosition_.end()) {
        auto curStartPos = curInter->second.startPos;
        auto curFrameNode = curInter->second.node;
        PlayVerticalScrollExitAnimation(swiperWidth, curStartPos, curFrameNode);
    }

    if (nextInter != itemPosition_.end()) {
        auto nextStartPos = nextInter->second.startPos;
        auto nextFrameNode = nextInter->second.node;
        PlayVerticalScrollEntryAnimation(swiperWidth, nextStartPos, nextFrameNode);
    }
}

void ArcSwiperPattern::PlayVerticalScrollExitAnimation(float swiperWidth, float startPos,
    RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto curNodeContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(curNodeContext);
    if (swiperWidth == 0) {
        return;
    }
    auto exitNodePercent = std::abs(startPos) / swiperWidth;
    if (!hasGetExitColor_) {
        auto colorPtr = GetBackgroundColorValue(frameNode);
        preNodeBackgroundColor_ = colorPtr;
        exitNodes_.insert(std::make_pair(WeakPtr<FrameNode>(frameNode), preNodeBackgroundColor_));
        hasGetExitColor_ = true;
    }

    // scale
    verticalExitNodeScale_ = 1.0 - exitNodePercent * VERTICAL_EXIT_SCALE_REDUCTION_FACTOR;
    if (verticalExitNodeScale_ < VERTICAL_EXIT_SCALE_MIN_VALUE) {
        verticalExitNodeScale_ = VERTICAL_EXIT_SCALE_MIN_VALUE;
    }
    PlayScrollScaleAnimation(verticalExitNodeScale_, curNodeContext);

    // blur
    verticalExitNodeBlur_ = VERTICAL_EXIT_BLUR_INITIAL_VALUE + exitNodePercent * VERTICAL_EXIT_BLUR_INCREASE_FACTOR;
    if (verticalExitNodeBlur_ > VERTICAL_EXIT_BLUR_MAX_VALUE) {
        verticalExitNodeBlur_ = VERTICAL_EXIT_BLUR_MAX_VALUE;
    }
    PlayScrollBlurAnimation(verticalExitNodeBlur_, curNodeContext);

    // alpha
    if (exitNodePercent < VERTICAL_EXIT_ALPHA_MIN_RATIO) {
        verticalExitNodeOpacity_ = 1.0 - VERTICAL_EXIT_ALPHA_REDUCTION_FACTOR * exitNodePercent;
    } else if (exitNodePercent == VERTICAL_EXIT_ALPHA_MIN_RATIO) {
        verticalExitNodeOpacity_ = VERTICAL_EXIT_ALPHA_AT_CRITICAL_POINT;
    } else {
        verticalExitNodeOpacity_ = VERTICAL_EXIT_ALPHA_AT_CRITICAL_POINT -
            VERTICAL_EXIT_ALPHA_REDUCTION_FACTOR_AFTER_CRITICAL_POINT * exitNodePercent;
    }
    if (verticalExitNodeOpacity_ < 0) {
        verticalExitNodeOpacity_ = 0;
    }
    PlayScrollAlpahAnimation(verticalExitNodeOpacity_, curNodeContext);

    auto context = frameNode->GetRenderContext();
    CHECK_NULL_VOID(context);
    context->OnBackgroundColorUpdate(Color::TRANSPARENT);
}

void ArcSwiperPattern::PlayVerticalScrollEntryAnimation(float swiperWidth, float startPos,
    RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto entryNodeContext = frameNode->GetRenderContext();
    CHECK_NULL_VOID(entryNodeContext);
    if (swiperWidth == 0) {
        return;
    }
    auto entryNodePercent = (swiperWidth - std::abs(startPos)) / swiperWidth;

    // color
    if (!hasGetEntryColor_) {
        auto colorPtr = GetBackgroundColorValue(frameNode);
        entryNodeBackground_ = colorPtr;
        entryNodes_.insert(std::make_pair(WeakPtr<FrameNode>(frameNode), entryNodeBackground_));
        hasGetEntryColor_ = true;
    }

    auto parentNode = frameNode->GetParentFrameNode();
    CHECK_NULL_VOID(parentNode);
    auto parentContext = parentNode->GetRenderContext();
    CHECK_NULL_VOID(parentContext);

    if (entryNodePercent < VERTICAL_ENTRY_CRITICAL_POINT_OF_COLOR) {
        entryNodeContext->OnBackgroundColorUpdate(Color::TRANSPARENT);
        PlayScrollBackgroundAnimation(preNodeBackgroundColor_, parentContext);
    }

    if (entryNodePercent >= VERTICAL_ENTRY_CRITICAL_POINT_OF_COLOR) {
        auto parentContext = parentNode->GetRenderContext();
        CHECK_NULL_VOID(parentContext);
        PlayScrollBackgroundAnimation(entryNodeBackground_, parentContext);
    }

    if (entryNodePercent >= VERTICAL_ENTRY_CRITICAL_POINT_OF_OTHER) {
        // scale
        verticalEntryNodeScale_ = VERTICAL_ENTRY_SCALE_INITIAL_VALUE -
            VERTICAL_ENTRY_SCALE_REDUCTION_FACTOR * (entryNodePercent - VERTICAL_ENTRY_CRITICAL_POINT_OF_OTHER) *
            VERTICAL_ENTRY_WHOLE_REDUCTION_FACTOR;
        if (verticalEntryNodeScale_ < 1) {
            verticalEntryNodeScale_ = 1;
        }
        PlayScrollScaleAnimation(verticalEntryNodeScale_, entryNodeContext);

        // alpha
        verticalEntryNodeOpacity_ = (entryNodePercent - VERTICAL_ENTRY_CRITICAL_POINT_OF_OTHER) *
            VERTICAL_ENTRY_WHOLE_REDUCTION_FACTOR;
        if (verticalEntryNodeOpacity_ > 1) {
            verticalEntryNodeOpacity_ = 1;
        }
        PlayScrollAlpahAnimation(verticalEntryNodeOpacity_, entryNodeContext);
    }
}

void ArcSwiperPattern::PlayScrollAnimation(float offset)
{
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
    MarkDirtyNodeSelf();
}

void ArcSwiperPattern::ResetBackcolor()
{
    for (auto& node: exitNodes_) {
        auto frameNode = node.first.Upgrade();
        CHECK_NULL_BREAK(frameNode);
        auto context = frameNode->GetRenderContext();
        CHECK_NULL_BREAK(context);
        auto colorPtr = node.second;
        CHECK_NULL_BREAK(colorPtr);
        context->OnBackgroundColorUpdate(*colorPtr);
        colorPtr = nullptr;
    }
    exitNodes_.clear();

    for (auto& node: entryNodes_) {
        auto frameNode = node.first.Upgrade();
        CHECK_NULL_BREAK(frameNode);
        auto context = frameNode->GetRenderContext();
        CHECK_NULL_BREAK(context);
        auto nodeColorPtr = node.second;
        if (nodeColorPtr) {
            context->OnBackgroundColorUpdate(*nodeColorPtr);
            nodeColorPtr = nullptr;
        }

        auto parentFrameNode = frameNode->GetParentFrameNode();
        CHECK_NULL_BREAK(parentFrameNode);
        auto parentColorPtr = GetBackgroundColorValue(parentFrameNode);
        if (parentColorPtr) {
            auto parentContext = parentFrameNode->GetRenderContext();
            CHECK_NULL_BREAK(parentContext);
            parentContext->OnBackgroundColorUpdate(*parentColorPtr);
            parentColorPtr = nullptr;
        }
    }
    entryNodes_.clear();
}

void ArcSwiperPattern::ResetAnimationParam()
{
    for (auto aniamton : scrollAnimationVector_) {
        AnimationUtils::StopAnimation(aniamton);
    }
    scrollAnimationVector_.clear();
    hasGetEntryColor_ = false;
    hasGetExitColor_ = false;
    ResetBackcolor();
    StopPropertyTranslateAnimation(isFinishAnimation_);
    StopIndicatorAnimation();
    
    horizontalExitNodeScale_ = 1.0f;
    horizontalExitNodeBlur_ = 0;
    horizontalExitNodeOpacity_ = 1.0f;
    horizontalEntryNodeScale_ = HORIZONTAL_ENTRY_SCALE_INITIAL_VALUE;
    horizontalEntryNodeBlur_ = HORIZONTAL_ENTRY_BLUR_VALUE;
    horizontalEntryNodeOpacity_ = 0;

    verticalExitNodeScale_ = 1.0f;
    verticalExitNodeBlur_ = VERTICAL_EXIT_BLUR_INITIAL_VALUE;
    verticalExitNodeOpacity_ = 1.0f;
    verticalEntryNodeScale_ = VERTICAL_ENTRY_SCALE_VALUE;
    verticalEntryNodeOpacity_ = 0;
}
} // namespace OHOS::Ace::NG
