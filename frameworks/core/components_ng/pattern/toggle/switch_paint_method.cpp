/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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
#include "core/common/container.h"
#include "core/components/checkable/checkable_theme.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/pattern/toggle/switch_layout_algorithm.h"
#include "core/components_ng/pattern/toggle/switch_paint_property.h"
#include "core/components_ng/render/drawing_prop_convertor.h"
#include "core/components_ng/render/paint_property.h"

namespace OHOS::Ace::NG {
CanvasDrawFunction SwitchPaintMethod::GetContentDrawFunction(PaintWrapper* paintWrapper)
{
    auto paintProperty = DynamicCast<SwitchPaintProperty>(paintWrapper->GetPaintProperty());
    CHECK_NULL_RETURN(paintProperty, nullptr);
    auto contentSize = paintWrapper->GetContentSize();
    auto contentOffset = paintWrapper->GetContentOffset();
    auto paintFunc = [weak = WeakClaim(this), paintProperty, contentSize, contentOffset](RSCanvas& canvas) {
        auto switch_ = weak.Upgrade();
        if (switch_) {
            switch_->PaintContent(canvas, paintProperty, contentSize, contentOffset);
        }
    };

    return paintFunc;
}

void SwitchPaintMethod::PaintContent(
    RSCanvas& canvas, RefPtr<SwitchPaintProperty> paintProperty, SizeF contentSize, OffsetF contentOffset)
{
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_VOID(pipelineContext);
    auto themeManager = pipelineContext->GetThemeManager();
    CHECK_NULL_VOID(themeManager);
    RefPtr<SwitchTheme> switchTheme = themeManager->GetTheme<SwitchTheme>();
    CHECK_NULL_VOID(switchTheme);

    auto width = contentSize.Width();
    auto height = contentSize.Height();
    auto radius = height / 2;

    auto xOffset = contentOffset.GetX();
    auto yOffset = contentOffset.GetY();

    auto borderWidth_ = static_cast<float>(switchTheme->GetBorderWidth().Value());
    auto hoverRadius_ = static_cast<float>(switchTheme->GetHoverRadius().Value());

    hoverRadius_ = radius - radiusGap_;

    RSBrush brush;
    brush.SetColor(ToRSColor(switchTheme->GetInactiveColor()));
    brush.SetBlendMode(RSBlendMode::SRC_OVER);
    canvas.AttachBrush(brush);

    rosen::Rect rect;
    rect.SetLeft(xOffset);
    rect.SetTop(yOffset);
    rect.SetRight(xOffset + width);
    rect.SetBottom(yOffset + height);
    rosen::RoundRect roundRect(rect, radius, radius);
    canvas.DrawRoundRect(roundRect);

    if (!NearEqual(mainDelta_, 0)) {
        brush.SetColor(ToRSColor(paintProperty->GetSelectedColor().value_or(switchTheme->GetActiveColor())));
        canvas.AttachBrush(brush);
        rosen::Rect rectCover;
        rectCover.SetLeft(xOffset);
        rectCover.SetTop(yOffset);
        rectCover.SetRight(xOffset + mainDelta_ + height - radiusGap_);
        rectCover.SetBottom(yOffset + height);
        rosen::RoundRect roundRectCover(rectCover, radius, radius);
        canvas.DrawRoundRect(roundRectCover);
    }
    brush.SetColor(ToRSColor(paintProperty->GetSwitchPointColor().value_or(switchTheme->GetPointColor())));
    canvas.AttachBrush(brush);
    rosen::Point point;
    point.SetX(xOffset + borderWidth_ + hoverRadius_ + mainDelta_);
    point.SetY(yOffset + radius);
    canvas.DrawCircle(point, hoverRadius_);
}

} // namespace OHOS::Ace::NG