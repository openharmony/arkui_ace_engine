/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/button/toggle_button_paint_property.h"

#include "core/components/toggle/toggle_theme.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
void ToggleButtonPaintProperty::ToJsonValue(
    std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto toggleTheme = pipeline->GetTheme<ToggleTheme>(host->GetThemeScopeId());
    CHECK_NULL_VOID(toggleTheme);
    auto selectedColor = toggleTheme->GetCheckedColor();
    json->PutExtAttr("type", "ToggleType.Button", filter);
    json->PutExtAttr("isOn", propIsOn_.value_or(false) ? "true" : "false", filter);
    json->PutExtAttr("selectedColor", propSelectedColor_.value_or(selectedColor).ColorToString().c_str(), filter);
}
} // namespace OHOS::Ace::NG
