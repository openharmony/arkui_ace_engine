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

#include "base/geometry/ng/offset_t.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components/checkable/checkable_theme.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/pattern/toggle/switch_layout_algorithm.h"
#include "core/components_ng/pattern/toggle/switch_modifier.h"
#include "core/components_ng/pattern/toggle/switch_paint_property.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/drawing_prop_convertor.h"
#include "core/components_ng/render/paint_property.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::NG {

namespace {
constexpr uint8_t ENABLED_ALPHA = 255;
constexpr uint8_t DISABLED_ALPHA = 102;
} // namespace

SwitchModifier::SwitchModifier(bool isSelect, const Color& boardColor, float dragOffsetX)
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto switchTheme = pipeline->GetTheme<SwitchTheme>();
    CHECK_NULL_VOID(switchTheme);
    animatableBoardColor_ = AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor(boardColor));
    animateTouchHoverColor_ = AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor(Color::TRANSPARENT));
    animatePointColor_ = AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor(switchTheme->GetPointColor()));
    pointOffset_ = AceType::MakeRefPtr<AnimatablePropertyFloat>(0.0f);
    dragOffsetX_ = AceType::MakeRefPtr<PropertyFloat>(dragOffsetX);
    isSelect_ = AceType::MakeRefPtr<PropertyBool>(isSelect);
    isHover_ = AceType::MakeRefPtr<PropertyBool>(false);
    offset_ = AceType::MakeRefPtr<AnimatablePropertyOffsetF>(OffsetF());
    size_ = AceType::MakeRefPtr<AnimatablePropertySizeF>(SizeF());
    enabled_ = AceType::MakeRefPtr<PropertyBool>(true);

    AttachProperty(animatableBoardColor_);
    AttachProperty(animateTouchHoverColor_);
    AttachProperty(animatePointColor_);
    AttachProperty(pointOffset_);
    AttachProperty(dragOffsetX_);
    AttachProperty(isSelect_);
    AttachProperty(isHover_);
    AttachProperty(offset_);
    AttachProperty(size_);
    AttachProperty(enabled_);
}

void SwitchModifier::InitializeParam()
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto switchTheme = pipeline->GetTheme<SwitchTheme>();
    CHECK_NULL_VOID(switchTheme);
    activeColor_ = switchTheme->GetActiveColor();
    inactiveColor_ = switchTheme->GetInactiveColor();
    clickEffectColor_ = switchTheme->GetClickEffectColor();
    hoverColor_ = switchTheme->GetHoverColor();
    hoverRadius_ = switchTheme->GetHoverRadius();
    userActiveColor_ = activeColor_;
    hoverDuration_ = switchTheme->GetHoverDuration();
    hoverToTouchDuration_ = switchTheme->GetHoverToTouchDuration();
    touchDuration_ = switchTheme->GetTouchDuration();
    colorAnimationDuration_ = switchTheme->GetColorAnimationDuration();
    pointAnimationDuration_ = switchTheme->GetPointAnimationDuration();
}

void SwitchModifier::PaintSwitch(RSCanvas& canvas, const OffsetF& contentOffset, const SizeF& contentSize)
{
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto switchTheme = pipelineContext->GetTheme<SwitchTheme>();
    CHECK_NULL_VOID(switchTheme);

    auto width = contentSize.Width();
    auto height = contentSize.Height();
    auto radius = height / 2;
    auto actualGap = radiusGap_.ConvertToPx() * height /
                     (switchTheme->GetHeight() - switchTheme->GetHotZoneVerticalPadding() * 2).ConvertToPx();
    auto xOffset = contentOffset.GetX();
    auto yOffset = contentOffset.GetY();
    pointRadius_ = radius - actualGap;
    clickEffectColor_ = switchTheme->GetClickEffectColor();
    hoverColor_ = switchTheme->GetHoverColor();
    hoverRadius_ = switchTheme->GetHoverRadius();
    auto defaultWidth = switchTheme->GetDefaultWidth().ConvertToPx();
    auto defaultHeight = switchTheme->GetDefaultHeight().ConvertToPx();
    auto defaultWidthGap =
        defaultWidth - (switchTheme->GetWidth() - switchTheme->GetHotZoneHorizontalPadding() * 2).ConvertToPx();
    auto defaultHeightGap =
        defaultHeight - (switchTheme->GetHeight() - switchTheme->GetHotZoneVerticalPadding() * 2).ConvertToPx();
    actualWidth_ = width + defaultWidthGap;
    actualHeight_ = height + defaultHeightGap;
    hoverRadius_ =
        hoverRadius_ * height / (switchTheme->GetHeight() - switchTheme->GetHotZoneVerticalPadding() * 2).ConvertToPx();

    OffsetF hoverBoardOffset;
    hoverBoardOffset.SetX(xOffset - (actualWidth_ - width) / 2.0);
    hoverBoardOffset.SetY(yOffset - (actualHeight_ - height) / 2.0);
    DrawTouchAndHoverBoard(canvas, hoverBoardOffset);
    RSRect rect;
    rect.SetLeft(xOffset);
    rect.SetTop(yOffset);
    rect.SetRight(xOffset + width);
    rect.SetBottom(yOffset + height);
    RSRoundRect roundRect(rect, radius, radius);

    RSBrush brush;
    if (!enabled_->Get()) {
        brush.SetColor(
            ToRSColor(animatableBoardColor_->Get().BlendOpacity(static_cast<float>(DISABLED_ALPHA) / ENABLED_ALPHA)));
    } else {
        brush.SetColor(ToRSColor(animatableBoardColor_->Get()));
    }
    brush.SetBlendMode(RSBlendMode::SRC_OVER);
    brush.SetAntiAlias(true);
    canvas.AttachBrush(brush);
    canvas.DrawRoundRect(roundRect);

    brush.SetColor(ToRSColor(animatePointColor_->Get()));
    brush.SetAntiAlias(true);
    canvas.AttachBrush(brush);

    RSPoint point;
    point.SetX(xOffset + actualGap + pointRadius_ + pointOffset_->Get());
    point.SetY(yOffset + radius);
    canvas.DrawCircle(point, pointRadius_);
}

void SwitchModifier::DrawTouchAndHoverBoard(RSCanvas& canvas, const OffsetF& offset) const
{
    RSBrush brush;
    brush.SetColor(ToRSColor(animateTouchHoverColor_->Get()));
    brush.SetAntiAlias(true);
    auto rightBottomX = offset.GetX() + actualWidth_;
    auto rightBottomY = offset.GetY() + actualHeight_;
    auto rrect = RSRoundRect({ offset.GetX(), offset.GetY(), rightBottomX, rightBottomY }, hoverRadius_.ConvertToPx(),
        hoverRadius_.ConvertToPx());
    canvas.AttachBrush(brush);
    canvas.DrawRoundRect(rrect);
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
