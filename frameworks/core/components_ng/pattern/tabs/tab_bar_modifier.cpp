/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/tabs/tab_bar_modifier.h"

#include "base/utils/utils.h"
#include "core/components_ng/render/drawing_prop_convertor.h"

namespace OHOS::Ace::NG {
TabBarModifier::TabBarModifier()
    :indicatorColor_(AceType::MakeRefPtr<AnimatablePropertyColor>(LinearColor::BLACK)),
    indicatorLeft_(AceType::MakeRefPtr<AnimatablePropertyFloat>(-1)),
    indicatorTop_(AceType::MakeRefPtr<AnimatablePropertyFloat>(-1)),
    indicatorWidth_(AceType::MakeRefPtr<AnimatablePropertyFloat>(-1)),
    indicatorHeight_(AceType::MakeRefPtr<AnimatablePropertyFloat>(-1)),
    indicatorBorderRadius_(AceType::MakeRefPtr<AnimatablePropertyFloat>(-1)),
    indicatorMarginTop_(AceType::MakeRefPtr<AnimatablePropertyFloat>(-1)),
    hasIndicator_(AceType::MakeRefPtr<PropertyBool>(true))
{
    AttachProperty(indicatorColor_);
    AttachProperty(indicatorLeft_);
    AttachProperty(indicatorTop_);
    AttachProperty(indicatorWidth_);
    AttachProperty(indicatorHeight_);
    AttachProperty(indicatorBorderRadius_);
    AttachProperty(indicatorMarginTop_);
    AttachProperty(hasIndicator_);
}

void TabBarModifier::onDraw(DrawingContext& context)
{
    if (!hasIndicator_ || hasIndicator_->Get()) {
        PaintIndicator(context);
    }
}

void TabBarModifier::SetIndicatorOffset(const OffsetF& indicatorOffset)
{
    if (indicatorLeft_) {
        indicatorLeft_->Set(indicatorOffset.GetX());
    }
    if (indicatorTop_) {
        indicatorTop_->Set(indicatorOffset.GetY());
    }
}

void TabBarModifier::SetIndicatorColor(const LinearColor& indicatorColor)
{
    if (indicatorColor_) {
        indicatorColor_->Set(indicatorColor);
    }
}

void TabBarModifier::SetIndicatorWidth(float indicatorWidth)
{
    if (indicatorWidth_) {
        indicatorWidth_->Set(indicatorWidth);
    }
}

void TabBarModifier::SetIndicatorHeight(float indicatorHeight)
{
    if (indicatorHeight_) {
        indicatorHeight_->Set(indicatorHeight);
    }
}

void TabBarModifier::SetIndicatorBorderRadius(float indicatorBorderRadius)
{
    if (indicatorBorderRadius_) {
        indicatorBorderRadius_->Set(indicatorBorderRadius);
    }
}

void TabBarModifier::SetIndicatorMarginTop(float indicatorMarginTop)
{
    if (indicatorMarginTop_) {
        indicatorMarginTop_->Set(indicatorMarginTop);
    }
}

void TabBarModifier::SetHasIndicator(bool hasIndicator)
{
    if (hasIndicator_) {
        hasIndicator_->Set(hasIndicator);
    }
}

void TabBarModifier::PaintIndicator(DrawingContext& context)
{
    auto& canvas = context.canvas;
    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    auto tabTheme = pipelineContext->GetTheme<TabTheme>();
    CHECK_NULL_VOID(tabTheme);

    RectF indicator;
    if (GreatNotEqual(indicatorHeight_->Get(), 0.0f)) {
        indicator.SetHeight(indicatorHeight_->Get());
    } else {
        indicator.SetHeight(tabTheme->GetSubTabIndicatorHeight().ConvertToPx());
    }
    indicator.SetWidth(indicatorWidth_->Get());
    indicator.SetLeft(indicatorLeft_->Get());
    if (GreatNotEqual(indicatorMarginTop_->Get(), 0.0f)) {
        indicator.SetTop(indicatorTop_->Get() + indicatorMarginTop_->Get());
    } else {
        indicator.SetTop(indicatorTop_->Get());
    }

    RSBrush brush;
    brush.SetAntiAlias(true);
    brush.SetColor(ToRSColor(indicatorColor_->Get()));
    brush.SetBlendMode(RSBlendMode::SRC_OVER);
    canvas.AttachBrush(brush);
    if (indicatorBorderRadius_->Get() > 0) {
        RSRoundRect rect(ToRSRect(indicator), indicatorBorderRadius_->Get(), indicatorBorderRadius_->Get());
        canvas.DrawRoundRect(rect);
    } else {
        canvas.DrawRect(ToRSRect(indicator));
    }
    canvas.DetachBrush();
    canvas.Restore();
}
} // namespace OHOS::Ace::NG
