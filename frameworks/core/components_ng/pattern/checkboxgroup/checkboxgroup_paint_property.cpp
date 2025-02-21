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

#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_paint_property.h"

namespace OHOS::Ace::NG {

namespace {
const Color DEFAULT_GROUP_SELECTED_COLOR = Color(0xFF007DFF);
const Dimension DEFAULT_CHECKMARK_SIZE = Dimension(0, DimensionUnit::VP);
} // namespace

void CheckBoxGroupPaintProperty::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        PaintProperty::ToJsonValue(json, filter);
        return;
    }

    PaintProperty::ToJsonValue(json, filter);
    json->PutExtAttr("selectAll", GetCheckBoxGroupSelect().value_or(false) ? "true" : "false", filter);
    json->PutExtAttr("selectedColor",
        GetCheckBoxGroupSelectedColor().value_or(DEFAULT_GROUP_SELECTED_COLOR).ColorToString().c_str(), filter);
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        json->PutExtAttr("checkboxShape",
            std::to_string((int)(GetCheckBoxGroupSelectedStyleValue(CheckBoxStyle::CIRCULAR_STYLE))).c_str(), filter);
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto checkboxTheme = pipeline->GetTheme<CheckboxTheme>(host->GetThemeScopeId());
    CHECK_NULL_VOID(checkboxTheme);
    json->PutExtAttr("unselectedColor", GetCheckBoxGroupUnSelectedColor().value_or(
        checkboxTheme->GetInactiveColor()).ColorToString().c_str(), filter);
    auto markJsValue = JsonUtil::Create(true);
    markJsValue->Put("strokeColor", GetCheckBoxGroupCheckMarkColor().value_or(
        checkboxTheme->GetPointColor()).ColorToString().c_str());
    markJsValue->Put("size", GetCheckBoxGroupCheckMarkSize().value_or(
        DEFAULT_CHECKMARK_SIZE).ToString().c_str());
    markJsValue->Put("strokeWidth", GetCheckBoxGroupCheckMarkWidth().value_or(
        checkboxTheme->GetCheckStroke()).ToString().c_str());
    json->PutExtAttr("mark", markJsValue->ToString().c_str(), filter);
}
} // namespace OHOS::Ace::NG
