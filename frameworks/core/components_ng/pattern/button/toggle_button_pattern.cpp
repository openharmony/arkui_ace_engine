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

#include "core/components_ng/pattern/button/toggle_button_pattern.h"

#include "base/geometry/axis.h"
#include "base/utils/macros.h"
#include "base/utils/utils.h"
#include "core/components/button/button_theme.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components/toggle/toggle_theme.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/button/toggle_button_paint_property.h"
#include "core/components_ng/pattern/button/toggle_button_view.h"
#include "core/components_ng/property/property.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

void ToggleButtonPattern::OnModifyDone()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto layoutProperty = host->GetLayoutProperty();
    CHECK_NULL_VOID(layoutProperty);
    if (layoutProperty->GetPositionProperty()) {
        layoutProperty->UpdateAlignment(
            layoutProperty->GetPositionProperty()->GetAlignment().value_or(Alignment::CENTER));
    } else {
        layoutProperty->UpdateAlignment(Alignment::CENTER);
    }

    auto buttonPaintProperty = GetPaintProperty<ToggleButtonPaintProperty>();
    CHECK_NULL_VOID(buttonPaintProperty);
    if (!isOn_.has_value()) {
        isOn_ = buttonPaintProperty->GetIsOnValue();
    }
    bool changed = false;
    if (buttonPaintProperty->HasIsOn()) {
        bool isOn = buttonPaintProperty->GetIsOnValue();
        changed = isOn ^ isOn_.value();
        isOn_ = isOn;
    }
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto toggleTheme = pipeline->GetTheme<ToggleTheme>();
    CHECK_NULL_VOID(toggleTheme);
    const auto& renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);

    if (isOn_.value()) {
        auto color = toggleTheme->GetCheckedColor();
        auto selectedColor = buttonPaintProperty->GetSelectedColor().value_or(color);
        renderContext->UpdateBackgroundColor(selectedColor);
    } else {
        auto backgroundColor = toggleTheme->GetBackgroundColor();
        auto bgColor = buttonPaintProperty->GetBackgroundColor().value_or(backgroundColor);
        renderContext->UpdateBackgroundColor(bgColor);
    }

    if (changed) {
        auto toggleButtonEventHub = GetEventHub<ToggleButtonEventHub>();
        CHECK_NULL_VOID(toggleButtonEventHub);
        toggleButtonEventHub->UpdateChangeEvent(isOn_.value());
    }

    if (clickListener_) {
        return;
    }

    auto gesture = host->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gesture);

    auto clickCallback = [weak = WeakClaim(this)](GestureEvent& info) {
        auto buttonPattern = weak.Upgrade();
        CHECK_NULL_VOID(buttonPattern);
        buttonPattern->OnClick();
    };

    clickListener_ = MakeRefPtr<ClickEvent>(std::move(clickCallback));
    gesture->AddClickEvent(clickListener_);
}

void ToggleButtonPattern::OnClick()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto paintProperty = host->GetPaintProperty<ToggleButtonPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    bool isLastSelected = false;
    if (paintProperty->HasIsOn()) {
        isLastSelected = paintProperty->GetIsOnValue();
    }
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto toggleTheme = pipeline->GetTheme<ToggleTheme>();
    CHECK_NULL_VOID(toggleTheme);
    auto color = toggleTheme->GetCheckedColor();
    const auto& renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    Color selectedColor;
    auto buttonPaintProperty = host->GetPaintProperty<ToggleButtonPaintProperty>();
    CHECK_NULL_VOID(buttonPaintProperty);
    if (isLastSelected) {
        selectedColor = buttonPaintProperty->GetBackgroundColor().value_or(toggleTheme->GetBackgroundColor());
    } else {
        selectedColor = buttonPaintProperty->GetSelectedColor().value_or(color);
    }
    paintProperty->UpdateIsOn(!isLastSelected);
    isOn_ = !isLastSelected;
    renderContext->UpdateBackgroundColor(selectedColor);
    auto buttonEventHub = GetEventHub<ToggleButtonEventHub>();
    CHECK_NULL_VOID(buttonEventHub);
    buttonEventHub->UpdateChangeEvent(!isLastSelected);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

} // namespace OHOS::Ace::NG
