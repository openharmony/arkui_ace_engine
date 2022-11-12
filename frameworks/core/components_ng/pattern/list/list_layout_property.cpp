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

#include "core/components_ng/pattern/list/list_layout_property.h"

namespace OHOS::Ace::NG {

void ListLayoutProperty::ToJsonValue(std::unique_ptr<JsonValue>& json) const
{
    LayoutProperty::ToJsonValue(json);
    json->Put("space", propSpace_.value_or(Dimension(0, DimensionUnit::VP)).ToString().c_str());
    json->Put("initialIndex", std::to_string(propInitialIndex_.value_or(0)).c_str());
    json->Put("listDirection", propListDirection_.value_or(Axis::VERTICAL) == Axis::VERTICAL
                                   ? "Axis.Vertical"
                                   : "Axis.Horizontal");
    json->Put("editMode", "true");
    json->Put("chainAnimation", "true");
    if (propDivider_.has_value()) {
        auto divider = JsonUtil::Create(false);
        divider->Put("strokeWidth", propDivider_.value().strokeWidth.ToString().c_str());
        divider->Put("startMargin", propDivider_.value().startMargin.ToString().c_str());
        divider->Put("endMargin", propDivider_.value().endMargin.ToString().c_str());
        divider->Put("color", propDivider_.value().color.ColorToString().c_str());
        json->Put("divider", divider);
    } else {
        auto divider = JsonUtil::Create(false);
        json->Put("divider", divider);
    }
    json->Put("edgeEffect", propEdgeEffect_.value_or(EdgeEffect::SPRING) == EdgeEffect::SPRING
                                ? "EdgeEffect.Spring"
                                : "EdgeEffect.None");
    json->Put("lanes", std::to_string(propLanes_.value_or(0)).c_str());
    json->Put("laneMinLength", propLaneMinLength_.value_or(Dimension(0, DimensionUnit::VP)).ToString().c_str());
    json->Put("laneMaxLength", propLaneMaxLength_.value_or(Dimension(0, DimensionUnit::VP)).ToString().c_str());
    if (propListItemAlign_.value_or(V2::ListItemAlign::CENTER) == V2::ListItemAlign::START) {
        json->Put("listItemAlign", "ListItemAlign.Start");
    } else if (propListItemAlign_.value_or(V2::ListItemAlign::CENTER) == V2::ListItemAlign::CENTER) {
        json->Put("listItemAlign", "ListItemAlign.Center");
    } else {
        json->Put("listItemAlign", "ListItemAlign.End");
    }
    json->Put("cachedCount", std::to_string(propCachedCount_.value_or(0)).c_str());
}
}
