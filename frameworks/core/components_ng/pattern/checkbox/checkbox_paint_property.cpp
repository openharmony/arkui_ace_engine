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

#include "core/components_ng/pattern/checkbox/checkbox_paint_property.h"

namespace OHOS::Ace::NG {
namespace {
const Color DEFAULT_SELECTED_COLOR = Color(0xFF007DFF);
const Dimension DEFAULT_CHECKMARK_SIZE = Dimension(0, DimensionUnit::VP);
} // namespace

void CheckBoxPaintProperty::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto checkboxTheme = pipeline->GetTheme<CheckboxTheme>();
    CHECK_NULL_VOID(checkboxTheme);
    PaintProperty::ToJsonValue(json, filter);
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    json->PutExtAttr("isOn", GetCheckBoxSelect().value_or(false) ? "true" : "false", filter);
    json->PutExtAttr("selectedColor",
        GetCheckBoxSelectedColor().value_or(DEFAULT_SELECTED_COLOR).ColorToString().c_str(), filter);
    json->PutExtAttr("unselectedColor", GetCheckBoxUnSelectedColor().value_or(
        checkboxTheme->GetInactiveColor()).ColorToString().c_str(), filter);
    auto markJsValue = JsonUtil::Create(true);
    markJsValue->Put("strokeColor", GetCheckBoxCheckMarkColor().value_or(
        checkboxTheme->GetPointColor()).ColorToString().c_str());
    markJsValue->Put("size", GetCheckBoxCheckMarkSize().value_or(
        DEFAULT_CHECKMARK_SIZE).ToString().c_str());
    markJsValue->Put("strokeWidth", GetCheckBoxCheckMarkWidth().value_or(
        checkboxTheme->GetCheckStroke()).ToString().c_str());

    json->PutExtAttr("mark", markJsValue->ToString().c_str(), filter);
    json->PutExtAttr("shape",
        std::to_string((int)(GetCheckBoxSelectedStyleValue(CheckBoxStyle::CIRCULAR_STYLE))).c_str(), filter);
}

} // namespace OHOS::Ace::NG
