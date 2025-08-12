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

#include "core/components_ng/pattern/toggle/toggle_model_static.h"

#include "core/components/toggle/toggle_theme.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/pattern/button/toggle_button_model_ng.h"
#include "core/components_ng/pattern/button/toggle_button_pattern.h"
#include "core/components_ng/pattern/checkbox/checkbox_model_ng.h"
#include "core/components_ng/pattern/checkbox/toggle_checkbox_pattern.h"
#include "core/components_ng/pattern/toggle/switch_pattern.h"

namespace OHOS::Ace::NG {
void ToggleModelStatic::SetPointRadius(FrameNode* frameNode, const std::optional<Dimension>& switchPointRadius)
{
    CHECK_NULL_VOID(frameNode);
    auto paintProperty = frameNode->GetPaintProperty<SwitchPaintProperty>();
    if (paintProperty) {
        if (switchPointRadius.has_value()) {
            paintProperty->UpdatePointRadius(switchPointRadius.value());
        } else {
            paintProperty->ResetPointRadius();
            paintProperty->UpdatePropertyChangeFlag(PROPERTY_UPDATE_RENDER);
        }
    }
}

void ToggleModelStatic::SetUnselectedColor(FrameNode* frameNode, const std::optional<Color>& unselectedColor)
{
    CHECK_NULL_VOID(frameNode);
    auto paintProperty = frameNode->GetPaintProperty<SwitchPaintProperty>();
    if (paintProperty) {
        if (unselectedColor.has_value()) {
            paintProperty->UpdateUnselectedColor(unselectedColor.value());
        } else {
            paintProperty->ResetUnselectedColor();
        }
    }
}

void ToggleModelStatic::SetTrackBorderRadius(FrameNode* frameNode, const std::optional<Dimension>& borderRadius)
{
    CHECK_NULL_VOID(frameNode);
    auto paintProperty = frameNode->GetPaintProperty<SwitchPaintProperty>();
    if (paintProperty) {
        if (borderRadius.has_value()) {
            paintProperty->UpdateTrackBorderRadius(borderRadius.value());
        } else {
            paintProperty->ResetTrackBorderRadius();
            paintProperty->UpdatePropertyChangeFlag(PROPERTY_UPDATE_RENDER);
        }
    }
}

void ToggleModelStatic::OnChangeEvent(FrameNode* frameNode, ChangeEvent&& onChangeEvent)
{
    CHECK_NULL_VOID(frameNode);
    auto checkboxPattern = AceType::DynamicCast<ToggleCheckBoxPattern>(frameNode->GetPattern());
    if (checkboxPattern) {
        auto eventHub = frameNode->GetEventHub<CheckBoxEventHub>();
        CHECK_NULL_VOID(eventHub);
        eventHub->SetChangeEvent(std::move(onChangeEvent));
        return;
    }
    auto buttonPattern = AceType::DynamicCast<ToggleButtonPattern>(frameNode->GetPattern());
    if (buttonPattern) {
        auto eventHub = frameNode->GetEventHub<ToggleButtonEventHub>();
        CHECK_NULL_VOID(eventHub);
        eventHub->SetOnChangeEvent(std::move(onChangeEvent));
        return;
    }
    auto eventHub = frameNode->GetEventHub<SwitchEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnChangeEvent(std::move(onChangeEvent));
}

} // namespace OHOS::Ace::NG
