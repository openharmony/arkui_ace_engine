/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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
namespace {
V2::ItemDivider ItemDividerFromJson(const std::unique_ptr<JsonValue>& json)
{
    V2::ItemDivider divider;
    divider.strokeWidth = Dimension::FromString(json->GetString("strokeWidth"));
    divider.startMargin = Dimension::FromString(json->GetString("startMargin"));
    divider.endMargin = Dimension::FromString(json->GetString("endMargin"));
    divider.color = Color::ColorFromString(json->GetString("color"));
    return divider;
}
} // namespace

void ListLayoutProperty::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    LayoutProperty::ToJsonValue(json, filter);
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        ScrollSnapPropToJsonValue(json, filter);
        return;
    }
    json->PutExtAttr("space", propSpace_.value_or(Dimension(0, DimensionUnit::VP)).ToString().c_str(), filter);
    json->PutExtAttr("contentStartOffset", std::to_string(propContentStartOffset_.value_or(0)).c_str(), filter);
    json->PutExtAttr("contentEndOffset", std::to_string(propContentEndOffset_.value_or(0)).c_str(), filter);
    json->PutExtAttr("initialIndex", std::to_string(propInitialIndex_.value_or(0)).c_str(), filter);
    json->PutExtAttr("listDirection", propListDirection_.value_or(Axis::VERTICAL) == Axis::VERTICAL
                                   ? "Axis.Vertical" : "Axis.Horizontal", filter);
    json->PutExtAttr("editMode", propEditMode_.value_or(false), filter);
    json->PutExtAttr("chainAnimation", propChainAnimation_.value_or(false), filter);
    auto divider = JsonUtil::Create(true);
    if (propDivider_.has_value()) {
        divider->Put("strokeWidth", propDivider_.value().strokeWidth.ToString().c_str());
        divider->Put("startMargin", propDivider_.value().startMargin.ToString().c_str());
        divider->Put("endMargin", propDivider_.value().endMargin.ToString().c_str());
        divider->Put("color", propDivider_.value().color.ColorToString().c_str());
    }
    json->PutExtAttr("divider", divider, filter);
    json->PutExtAttr("lanes", std::to_string(propLanes_.value_or(0)).c_str(), filter);
    json->PutExtAttr("laneMinLength",
        propLaneMinLength_.value_or(Dimension(0, DimensionUnit::VP)).ToString().c_str(), filter);
    json->PutExtAttr("laneMaxLength",
        propLaneMaxLength_.value_or(Dimension(0, DimensionUnit::VP)).ToString().c_str(), filter);
    json->PutExtAttr("laneGutter",
        propLaneGutter_.value_or(Dimension(0, DimensionUnit::VP)).ToString().c_str(), filter);
    if (propListItemAlign_.value_or(V2::ListItemAlign::START) == V2::ListItemAlign::START) {
        json->PutExtAttr("alignListItem", "ListItemAlign.Start", filter);
    } else if (propListItemAlign_.value_or(V2::ListItemAlign::START) == V2::ListItemAlign::CENTER) {
        json->PutExtAttr("alignListItem", "ListItemAlign.Center", filter);
    } else {
        json->PutExtAttr("alignListItem", "ListItemAlign.End", filter);
    }
    json->PutExtAttr("cachedCount", std::to_string(propCachedCount_.value_or(0)).c_str(), filter);
    auto sticky = propStickyStyle_.value_or(V2::StickyStyle::NONE);
    if (sticky == V2::StickyStyle::HEADER) {
        json->PutExtAttr("sticky", "StickyStyle.Header", filter);
    } else if (sticky == V2::StickyStyle::FOOTER) {
        json->PutExtAttr("sticky", "StickyStyle.Footer", filter);
    } else if (sticky == V2::StickyStyle::BOTH) {
        json->PutExtAttr("sticky", "StickyStyle.Header | StickyStyle.Footer", filter);
    } else {
        json->PutExtAttr("sticky", "StickyStyle.None", filter);
    }
    ScrollSnapPropToJsonValue(json, filter);
}

void ListLayoutProperty::ScrollSnapPropToJsonValue(
    std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    auto scrollSnapAlign = propScrollSnapAlign_.value_or(ScrollSnapAlign::NONE);
    if (scrollSnapAlign == ScrollSnapAlign::START) {
        json->PutExtAttr("scrollSnapAlign", "ScrollSnapAlign.START", filter);
    } else if (scrollSnapAlign == ScrollSnapAlign::CENTER) {
        json->PutExtAttr("scrollSnapAlign", "ScrollSnapAlign.CENTER", filter);
    } else if (scrollSnapAlign == ScrollSnapAlign::END) {
        json->PutExtAttr("scrollSnapAlign", "ScrollSnapAlign.END", filter);
    } else {
        json->PutExtAttr("scrollSnapAlign", "ScrollSnapAlign.NONE", filter);
    }
    json->PutExtAttr("enableScrollInteraction", propScrollEnabled_.value_or(true), filter);
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

void ListLayoutProperty::UpdateLayoutProperty(const ListLayoutProperty* layoutProperty)
{
    propSpace_ = layoutProperty->CloneSpace();
    propInitialIndex_ = layoutProperty->CloneInitialIndex();
    propListDirection_ = layoutProperty->CloneListDirection();
    propDivider_ = layoutProperty->CloneDivider();
    propLanes_ = layoutProperty->CloneLanes();
    propLaneMinLength_ = layoutProperty->CloneLaneMinLength();
    propLaneMaxLength_ = layoutProperty->CloneLaneMaxLength();
    propLaneGutter_ = layoutProperty->CloneLaneGutter();
    propListItemAlign_ = layoutProperty->CloneListItemAlign();
    propCachedCount_ = layoutProperty->CloneCachedCount();
    propStickyStyle_ = layoutProperty->CloneStickyStyle();
    propContentStartOffset_ = layoutProperty->CloneContentStartOffset();
    propContentEndOffset_ = layoutProperty->CloneContentEndOffset();
    propScrollSnapAlign_ = layoutProperty->CloneScrollSnapAlign();
    propEditMode_ = layoutProperty->CloneEditMode();
    propScrollEnabled_ = layoutProperty->CloneScrollEnabled();
}
}
