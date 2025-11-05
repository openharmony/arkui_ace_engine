/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/render_node/render_node_layout_property.h"

#include "core/components_ng/property/position_property.h"

namespace OHOS::Ace::NG {

void RenderNodeLayoutProperty::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    LayoutProperty::ToJsonValue(json, filter);
    auto align = Alignment::TOP_LEFT;
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    if (GetPositionProperty()) {
        align = GetPositionProperty()->GetAlignment().value_or(Alignment::TOP_LEFT);
    }
    json->PutExtAttr("alignContent", align.GetAlignmentStr(TextDirection::LTR).c_str(), filter);
}

void RenderNodeLayoutProperty::FromJson(const std::unique_ptr<JsonValue>& json)
{
    UpdateAlignment(Alignment::GetAlignment(TextDirection::LTR, json->GetString("alignContent")));
    LayoutProperty::FromJson(json);
}

} // namespace OHOS::Ace::NG
