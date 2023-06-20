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

#include "base/utils/string_utils.h"
#include "core/components_v2/list/list_properties.h"

namespace OHOS::Ace::NG {
namespace {
V2::ItemDivider ItemDividerFromJson(const std::unique_ptr<JsonValue>& json)
{
    LOGD("UITree json=%{public}s", json->ToString().c_str());
    V2::ItemDivider divider;
    divider.strokeWidth = Dimension::FromString(json->GetString("strokeWidth"));
    divider.startMargin = Dimension::FromString(json->GetString("startMargin"));
    divider.endMargin = Dimension::FromString(json->GetString("endMargin"));
    divider.color = Color::ColorFromString(json->GetString("color"));
    return divider;
}
} // namespace

void ListLayoutProperty::ToJsonValue(std::unique_ptr<JsonValue>& json) const
{
    LayoutProperty::ToJsonValue(json);
    json->Put("space", propSpace_.value_or(Dimension(0, DimensionUnit::VP)).ToString().c_str());
    json->Put("initialIndex", std::to_string(propInitialIndex_.value_or(0)).c_str());
    json->Put("listDirection", propListDirection_.value_or(Axis::VERTICAL) == Axis::VERTICAL
                                   ? "Axis.Vertical"
                                   : "Axis.Horizontal");
    json->Put("editMode", propEditMode_.value_or(false));
    json->Put("chainAnimation", propChainAnimation_.value_or(false));
    if (propDivider_.has_value()) {
        auto divider = JsonUtil::Create(true);
        divider->Put("strokeWidth", propDivider_.value().strokeWidth.ToString().c_str());
        divider->Put("startMargin", propDivider_.value().startMargin.ToString().c_str());
        divider->Put("endMargin", propDivider_.value().endMargin.ToString().c_str());
        divider->Put("color", propDivider_.value().color.ColorToString().c_str());
        json->Put("divider", divider);
    } else {
        auto divider = JsonUtil::Create(true);
        json->Put("divider", divider);
    }
    auto edgeEffect = propEdgeEffect_.value_or(EdgeEffect::SPRING);
    if (edgeEffect == EdgeEffect::SPRING) {
        json->Put("edgeEffect", "EdgeEffect.Spring");
    } else if (edgeEffect == EdgeEffect::FADE) {
        json->Put("edgeEffect", "EdgeEffect.Fade");
    } else {
        json->Put("edgeEffect", "EdgeEffect.None");
    }
    json->Put("lanes", std::to_string(propLanes_.value_or(0)).c_str());
    json->Put("laneMinLength", propLaneMinLength_.value_or(Dimension(0, DimensionUnit::VP)).ToString().c_str());
    json->Put("laneMaxLength", propLaneMaxLength_.value_or(Dimension(0, DimensionUnit::VP)).ToString().c_str());
    if (propListItemAlign_.value_or(V2::ListItemAlign::START) == V2::ListItemAlign::START) {
        json->Put("alignListItem", "ListItemAlign.Start");
    } else if (propListItemAlign_.value_or(V2::ListItemAlign::START) == V2::ListItemAlign::CENTER) {
        json->Put("alignListItem", "ListItemAlign.Center");
    } else {
        json->Put("alignListItem", "ListItemAlign.End");
    }
    json->Put("cachedCount", std::to_string(propCachedCount_.value_or(0)).c_str());
    auto sticky = propStickyStyle_.value_or(V2::StickyStyle::NONE);
    if (sticky == V2::StickyStyle::HEADER) {
        json->Put("sticky", "StickyStyle.Header");
    } else if (sticky == V2::StickyStyle::FOOTER) {
        json->Put("sticky", "StickyStyle.Footer");
    } else if (sticky == V2::StickyStyle::BOTH) {
        json->Put("sticky", "StickyStyle.Header | StickyStyle.Footer");
    } else {
        json->Put("sticky", "StickyStyle.None");
    }
    json->Put("enableScrollInteraction", propScrollEnabled_.value_or(true));
}

void ListLayoutProperty::FromJson(const std::unique_ptr<JsonValue>& json)
{
    UpdateSpace(Dimension::FromString(json->GetString("space")));
    UpdateInitialIndex(StringUtils::StringToInt(json->GetString("initialIndex")));
    auto dividerJson = json->GetObject("divider");
    if (dividerJson->Contains("strokeWidth")) {
        UpdateDivider(ItemDividerFromJson(dividerJson));
    }
    LayoutProperty::FromJson(json);
}
}
