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
    json->Put("Space", propSpace_.value_or(Dimension(0, DimensionUnit::VP)).ToString().c_str());
    json->Put("InitialIndex", std::to_string(propInitialIndex_.value_or(0)).c_str());
    json->Put("ListDirection", propListDirection_.value_or(Axis::VERTICAL) == Axis::VERTICAL
                                   ? "Axis::VERTICAL"
                                   : "Axis::HORIZONTAL");
    if (propDivider_.has_value()) {
        json->Put("DividerStrokeWidth", propDivider_.value().strokeWidth.ToString().c_str());
        json->Put("DividerStartMargin", propDivider_.value().startMargin.ToString().c_str());
        json->Put("DividerEndMargin", propDivider_.value().endMargin.ToString().c_str());
        json->Put("DividerColor", propDivider_.value().color.ColorToString().c_str());
    } else {
        json->Put("DividerStrokeWidth", Dimension(0, DimensionUnit::VP).ToString().c_str());
        json->Put("DividerStartMargin", Dimension(0, DimensionUnit::VP).ToString().c_str());
        json->Put("DividerEndMargin", Dimension(0, DimensionUnit::VP).ToString().c_str());
        json->Put("DividerColor", Color::WHITE.ColorToString().c_str());
    }
    json->Put("EdgeEffect", propEdgeEffect_.value_or(EdgeEffect::SPRING) == EdgeEffect::SPRING
                                ? "EdgeEffect::SPRING"
                                : "EdgeEffect::NONE");
    json->Put("Lanes", std::to_string(propLanes_.value_or(0)).c_str());
    json->Put("LaneMinLength", propLaneMinLength_.value_or(Dimension(0, DimensionUnit::VP)).ToString().c_str());
    json->Put("LaneMaxLength", propLaneMaxLength_.value_or(Dimension(0, DimensionUnit::VP)).ToString().c_str());
    if (propListItemAlign_.value_or(V2::ListItemAlign::CENTER) == V2::ListItemAlign::START) {
        json->Put("ListItemAlign", "ListItemAlign::START");
    } else if (propListItemAlign_.value_or(V2::ListItemAlign::CENTER) == V2::ListItemAlign::CENTER) {
        json->Put("ListItemAlign", "ListItemAlign::CENTER");
    } else {
        json->Put("ListItemAlign", "ListItemAlign::END");
    }
    json->Put("CachedCount", std::to_string(propCachedCount_.value_or(0)).c_str());
}
}
