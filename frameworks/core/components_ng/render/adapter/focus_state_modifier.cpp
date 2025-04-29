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

#include "core/components_ng/render/adapter/focus_state_modifier.h"

#include "core/common/container.h"
#include "core/components_ng/pattern/checkbox/checkbox_paint_property.h"
#include "core/components_ng/render/drawing_prop_convertor.h"

namespace OHOS::Ace::NG {
void FocusStateModifier::PaintFocusState(const RSRoundRect& rrect, RSCanvas& rsCanvas) const
{
    RSPen pen;
    pen.SetAntiAlias(true);
    pen.SetColor(ToRSColor(paintColor_));
    pen.SetWidth(paintWidthPx_);
    rsCanvas.AttachPen(pen);
    auto delegatePtr = weakFrameNode_.Upgrade();
    CHECK_NULL_VOID(delegatePtr);
    if (!delegatePtr->GetCheckboxFlag()) {
        rsCanvas.DrawRoundRect(rrect);
    } else {
        auto paintProperty = delegatePtr->GetPaintProperty<CheckBoxPaintProperty>();
        CHECK_NULL_VOID(paintProperty);
        CheckBoxStyle checkboxStyle = CheckBoxStyle::CIRCULAR_STYLE;
        if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN)) {
            checkboxStyle = CheckBoxStyle::CIRCULAR_STYLE;
        } else {
            checkboxStyle = CheckBoxStyle::SQUARE_STYLE;
        }
        if (paintProperty->HasCheckBoxSelectedStyle()) {
            checkboxStyle = paintProperty->GetCheckBoxSelectedStyleValue(CheckBoxStyle::CIRCULAR_STYLE);
        }
        RSScalar halfDenominator = 2.0f;
        RSScalar radius = 0.0f;
        RSRect rect = rrect.GetRect();
        RSScalar x = (rect.GetLeft() + rect.GetRight()) / halfDenominator;
        RSScalar y = (rect.GetTop() + rect.GetBottom()) / halfDenominator;
        RSPoint centerPt(x, y);
        if (rect.GetWidth() > rect.GetHeight()) {
            radius = rect.GetHeight() / halfDenominator;
        } else {
            radius = rect.GetWidth() / halfDenominator;
        }
        if (CheckBoxStyle::SQUARE_STYLE == checkboxStyle) {
            rsCanvas.DrawRoundRect(rrect);
        } else {
            rsCanvas.DrawCircle(centerPt, radius);
        }
    }
    rsCanvas.DetachPen();
}
} // namespace OHOS::Ace::NG