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
#include "core/components_ng/pattern/panel/sliding_panel_layout_property.h"

#include <string>

namespace OHOS::Ace::NG {
namespace {

constexpr Dimension BLANK_MIN_HEIGHT = 8.0_vp;

} // namespace

void SlidingPanelLayoutProperty::ToJsonValue(std::unique_ptr<JsonValue>& json) const
{
    LayoutProperty::ToJsonValue(json);
    json->Put("show", propShow_.value_or(true) ? "true" : "false");
    static const char* PANEL_TYPE[] = { "PanelType.Minibar", "PanelType.Foldable", "PanelType.Temporary" };
    json->Put("type", PANEL_TYPE[static_cast<int32_t>(GetPanelType().value_or(PanelType::FOLDABLE_BAR))]);
    static const char* PANEL_MODE[] = { "PanelMode.Mini", "PanelMode.Half", "PanelMode.Full" };
    json->Put("mode", PANEL_MODE[static_cast<int32_t>(GetPanelMode().value_or(PanelMode::HALF))]);
    json->Put("dragBar", propHasDragBar_.value_or(true) ? "true" : "false");
    json->Put("miniHeight", std::to_string(GetMiniHeight().value_or(BLANK_MIN_HEIGHT).ConvertToPx()).c_str());
}
} // namespace OHOS::Ace::NG