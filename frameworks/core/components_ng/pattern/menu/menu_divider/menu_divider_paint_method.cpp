/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/menu/menu_divider/menu_divider_paint_method.h"

#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {
void MenuDividerPaintMethod::CreateContentModifier()
{
    if (dividerModifier_) {
        return;
    }
    dividerModifier_ = MakeRefPtr<MenuDividerModifier>(themeStrokeWidth_, themeDividerColor_);
}

void MenuDividerPaintMethod::UpdateModfierParams(PaintWrapper* paintWrapper)
{
    CHECK_NULL_VOID(paintWrapper);
    auto paintProperty = DynamicCast<MenuDividerPaintProperty>(paintWrapper->GetPaintProperty());
    CHECK_NULL_VOID(paintProperty);
    auto renderContext = paintWrapper->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto host = renderContext->GetHost();
    CHECK_NULL_VOID(host);
    auto layoutProperty = host->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    auto geometryNode = paintWrapper->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    auto size = geometryNode->GetFrameSize();
    auto isRtl = layoutProperty->GetNonAutoLayoutDirection() == TextDirection::RTL;
    auto startMargin = 0.0f;
    auto endMargin = 0.0f;
    GetDividerMargin(startMargin, endMargin, paintProperty, size);
    dividerModifier_->SetLeftMargin(isRtl ? endMargin : startMargin);
    dividerModifier_->SetRightMargin(isRtl ? startMargin : endMargin);
    if (paintProperty->HasStrokeWidth()) {
        dividerModifier_->SetStrokeWidth(paintProperty->GetStrokeWidthValue().ConvertToPx());
    } else {
        dividerModifier_->SetStrokeWidth(themeStrokeWidth_);
    }
    auto dividerColor = paintProperty->GetDividerColorValue(themeDividerColor_);
    if (!isOption_ && dividerColor == Color::FOREGROUND) {
        dividerModifier_->SetDividerColor(themeDividerColor_);
    } else {
        dividerModifier_->SetDividerColor(dividerColor);
    }
    dividerModifier_->SetDefaultShow(defaultShowDivider_);
    auto selected = paintProperty->GetTopSelectedValue(false) || paintProperty->GetBottomSelectedValue(false);
    auto hover = paintProperty->GetTopHoverValue(false) || paintProperty->GetBottomHoverValue(false);
    auto press = paintProperty->GetTopPressValue(false) || paintProperty->GetBottomPressValue(false);
    dividerModifier_->SetSelected(selected);
    dividerModifier_->SetHover(hover);
    dividerModifier_->SetPress(press);
}

void MenuDividerPaintMethod::GetDividerMargin(
    float& startMargin, float& endMargin, const RefPtr<MenuDividerPaintProperty>& paintProperty, const SizeF& size)
{
    auto hasIcon = paintProperty->GetHasIconValue(false);
    auto themeStartPadding = isOption_ ? (themeOutPadding_ + (hasIcon ? themeIconPadding_ : 0.0f)) : themeHorInterval_;
    auto themeEndPadding = isOption_ ? themeOutPadding_ : themeHorInterval_;
    auto startMarginProp = paintProperty->GetStartMarginValue(Dimension(0, DimensionUnit::INVALID));
    auto endMarginProp = paintProperty->GetEndMarginValue(Dimension(0, DimensionUnit::INVALID));
    startMargin = startMarginProp.Unit() == DimensionUnit::INVALID ? themeStartPadding
                                                                   : startMarginProp.ConvertToPxWithSize(size.Width());
    endMargin = endMarginProp.Unit() == DimensionUnit::INVALID ? themeEndPadding
                                                               : endMarginProp.ConvertToPxWithSize(size.Width());
    if (startMargin < 0.0f || startMargin > size.Width()) {
        startMargin = themeStartPadding;
    }
    if (endMargin < 0.0f || endMargin > size.Width()) {
        endMargin = themeEndPadding;
    }
    if ((startMargin + endMargin) > size.Width()) {
        startMargin = themeStartPadding;
        endMargin = themeEndPadding;
    }
}
} // namespace OHOS::Ace::NG
