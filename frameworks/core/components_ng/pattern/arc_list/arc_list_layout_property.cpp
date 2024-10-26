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

#include "core/components_ng/pattern/arc_list/arc_list_layout_property.h"

namespace OHOS::Ace::NG {

void ArcListLayoutProperty::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    LayoutProperty::ToJsonValue(json, filter);
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        ScrollSnapPropToJsonValue(json, filter);
        return;
    }
    json->PutExtAttr("space", propSpace_.value_or(Dimension(0, DimensionUnit::VP)).ToString().c_str(), filter);
    json->PutExtAttr("initialIndex", std::to_string(propInitialIndex_.value_or(0)).c_str(), filter);
    json->PutExtAttr("cachedCount", std::to_string(propCachedCount_.value_or(0)).c_str(), filter);
    json->PutExtAttr("chainAnimation", propChainAnimation_.value_or(false), filter);
    ScrollSnapPropToJsonValue(json, filter);
}

void ArcListLayoutProperty::ScrollSnapPropToJsonValue(
    std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    json->PutExtAttr("enableScrollInteraction", propScrollEnabled_.value_or(true), filter);
}

void ArcListLayoutProperty::FromJson(const std::unique_ptr<JsonValue>& json)
{
    UpdateSpace(Dimension::FromString(json->GetString("space")));
    UpdateInitialIndex(StringUtils::StringToInt(json->GetString("initialIndex")));
    LayoutProperty::FromJson(json);
}

} // namespace OHOS::Ace::NG
