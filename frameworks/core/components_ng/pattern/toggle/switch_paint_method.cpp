/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/toggle/switch_paint_method.h"

#include "core/components_ng/render/drawing_prop_convertor.h"

namespace OHOS::Ace::NG {

namespace {
const Color TMP_INACTIVE_COLOR = Color(0x337F7F7F);
} // namespace

SwitchModifier::SwitchModifier(const SizeF& size, const OffsetF& offset, float pointOffset, bool isSelect,
    const Color& boardColor, float dragOffsetX)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto switchTheme = pipeline->GetTheme<SwitchTheme>();
    CHECK_NULL_VOID(switchTheme);
    animatableBoardColor_ = AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor(boardColor));
    animateTouchHoverColor_ = AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor(Color::TRANSPARENT));
    animatePointColor_ = AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor(switchTheme->GetPointColor()));
    pointOffset_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(pointOffset);
    dragOffsetX_ = AceType::MakeRefPtr<PropertyFloat>(dragOffsetX);
    isSelect_ = AceType::MakeRefPtr<PropertyBool>(isSelect);
    isHover_ = AceType::MakeRefPtr<PropertyBool>(false);
    offset_ = AceType::MakeRefPtr<AnimatablePropertyOffsetF>(offset);
    size_ = AceType::MakeRefPtr<AnimatablePropertySizeF>(size);
    useContentModifier_ = AceType::MakeRefPtr<PropertyBool>(false);
    animatePointRadius_ = AceType::MakeRefPtr<PropertyFloat>(SWITCH_ERROR_RADIUS);
    animateTrackRadius_ = AceType::MakeRefPtr<PropertyFloat>(SWITCH_ERROR_RADIUS);

    AttachProperty(animatableBoardColor_);
    AttachProperty(animateTouchHoverColor_);
    AttachProperty(animatePointColor_);
    AttachProperty(pointOffset_);
    AttachProperty(dragOffsetX_);
    AttachProperty(isSelect_);
    AttachProperty(isHover_);
    AttachProperty(offset_);
    AttachProperty(size_);
    AttachProperty(animatePointRadius_);
    AttachProperty(animateTrackRadius_);
}

void SwitchModifier::InitializeParam()
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto switchTheme = pipeline->GetTheme<SwitchTheme>();
    CHECK_NULL_VOID(switchTheme);
    activeColor_ = switchTheme->GetActiveColor();
    inactiveColor_ = TMP_INACTIVE_COLOR;
    clickEffectColor_ = switchTheme->GetInteractivePressedColor();
    hoverColor_ = switchTheme->GetInteractiveHoverColor();
    userActiveColor_ = activeColor_;
    hoverDuration_ = switchTheme->GetHoverDuration();
    hoverToTouchDuration_ = switchTheme->GetHoverToTouchDuration();
    touchDuration_ = switchTheme->GetTouchDuration();
    colorAnimationDuration_ = switchTheme->GetColorAnimationDuration();
    pointAnimationDuration_ = switchTheme->GetPointAnimationDuration();
}

float SwitchModifier::CalcActualWidth(float width, float height, double actualGap, double defaultWidthGap)
{
    float result = 0.0f;
    if (GreatOrEqual(width, height)) {
        result = (pointRadius_ * NUM_TWO > height ? (width - (actualGap * NUM_TWO)) : width) + defaultWidthGap;
    } else {
        result = (pointRadius_ > actualTrackRadius_ ? (width + (pointRadius_ - actualTrackRadius_) * NUM_TWO) : width) +
                 defaultWidthGap;
    }
    return result;
}

void SwitchModifier::PaintSwitch(RSCanvas& canvas, const OffsetF& contentOffset, const SizeF& contentSize)
{
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto switchTheme = pipelineContext->GetTheme<SwitchTheme>();
    CHECK_NULL_VOID(switchTheme);

    auto width = contentSize.Width();
    auto height = contentSize.Height();
    auto trackRadius =
        (animateTrackRadius_->Get() < 0) ? (height / NUM_TWO) : animateTrackRadius_->Get();
    auto radius = height / 2;
    auto actualGap = radiusGap_.ConvertToPx() * height /
                     (switchTheme->GetHeight() - switchTheme->GetHotZoneVerticalPadding() * 2).ConvertToPx();
    auto xOffset = contentOffset.GetX();
    auto yOffset = contentOffset.GetY();
    if (animatePointRadius_->Get() < 0) {
        pointRadius_ = radius - actualGap;
    } else {
        pointRadius_ = animatePointRadius_->Get();
        actualGap = radius - pointRadius_;
    }
    auto defaultWidth = switchTheme->GetDefaultWidth().ConvertToPx();
    auto defaultHeight = switchTheme->GetDefaultHeight().ConvertToPx();
    auto defaultWidthGap =
        defaultWidth - (switchTheme->GetWidth() - switchTheme->GetHotZoneHorizontalPadding() * 2).ConvertToPx();
    auto defaultHeightGap =
        defaultHeight - (switchTheme->GetHeight() - switchTheme->GetHotZoneVerticalPadding() * 2).ConvertToPx();
    actualWidth_ = CalcActualWidth(width, height, actualGap, defaultWidthGap);
    actualHeight_ = (pointRadius_ * NUM_TWO > height ? pointRadius_ * NUM_TWO : height) + defaultHeightGap;

    OffsetF hoverBoardOffset;
    hoverBoardOffset.SetX(xOffset - (actualWidth_ - width) / 2.0);
    hoverBoardOffset.SetY(yOffset - (actualHeight_ - height) / 2.0);

    RSRect rect;
    rect.SetLeft(xOffset);
    rect.SetTop(yOffset);
    rect.SetRight(xOffset + width);
    rect.SetBottom(yOffset + height);
    RSRoundRect roundRect(rect, trackRadius, trackRadius);

    RSBrush brush;
    brush.SetColor(ToRSColor(animatableBoardColor_->Get()));
    brush.SetBlendMode(RSBlendMode::SRC_OVER);
    brush.SetAntiAlias(true);
    canvas.AttachBrush(brush);
    canvas.DrawRoundRect(roundRect);
    canvas.DetachBrush();
    brush.SetColor(ToRSColor(animateTouchHoverColor_->Get()));
    canvas.AttachBrush(brush);
    canvas.DrawRoundRect(roundRect);
    canvas.DetachBrush();

    brush.SetColor(ToRSColor(animatePointColor_->Get()));
    brush.SetAntiAlias(true);
    canvas.AttachBrush(brush);
    RSPoint point;
    if (GreatOrEqual(contentSize.Width(), contentSize.Height())) {
        point.SetX(xOffset + actualGap + pointRadius_ + pointOffset_->Get());
    } else {
        point.SetX(xOffset + pointOffset_->Get());
    }
    point.SetY(yOffset + radius);
    canvas.DrawCircle(point, pointRadius_);
    canvas.DetachBrush();
}

float SwitchModifier::GetSwitchWidth(const SizeF& contentSize) const
{
    const float switchGap = 2.0f;
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, false);
    auto switchTheme = pipelineContext->GetTheme<SwitchTheme>();
    auto actualGap = switchGap * contentSize.Height() /
                     (switchTheme->GetHeight() - switchTheme->GetHotZoneVerticalPadding() * 2).ConvertToPx();
    auto switchWidth = contentSize.Width() - contentSize.Height() + actualGap;
    return switchWidth;
}

} // namespace OHOS::Ace::NG
