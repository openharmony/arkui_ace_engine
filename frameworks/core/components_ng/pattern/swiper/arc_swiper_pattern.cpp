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

void ArcSwiperPattern::HandleCrownActionBegin(double degree, double mainDelta, GestureEvent& info)
{
    accumulativeCrownPx_.Reset();
    UpdateCrownVelocity(degree, mainDelta);
    info.SetMainDelta(mainDelta);
    info.SetMainVelocity(crownVelocity_);
    InitIndexCanChangeMap();
    FireAndCleanScrollingListener();
    HandleDragStart(info);
    NotifyParentScrollStart(direction_ == Axis::HORIZONTAL ? info.GetGlobalLocation().GetX()
                                    : info.GetGlobalLocation().GetY());
    TouchLocationInfo touchLocationInfo(1);
    touchLocationInfo.SetGlobalLocation(info.GetGlobalLocation());
    HandleTouchDown(touchLocationInfo);
    isCrownSpring_ = false;
    isHandleCrownActionEnd_ = false;
}

void ArcSwiperPattern::HandleCrownActionUpdate(
    double degree, double mainDelta, GestureEvent& info, const OffsetF& offset)
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