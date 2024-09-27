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

#include "core/components_ng/pattern/list/list_item_layout_property.h"

namespace OHOS::Ace::NG {

void ListItemLayoutProperty::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    LayoutProperty::ToJsonValue(json, filter);
    auto editMode = propEditMode_.value_or(V2::EditMode::SHAM);
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        if (editMode == V2::EditMode::NONE) {
            json->PutFixedAttr("editable", "EditMode.None", filter, FIXED_ATTR_EDITABLE);
        } else if (editMode == V2::EditMode::MOVABLE) {
            json->PutFixedAttr("editable", "EditMode.Movable", filter, FIXED_ATTR_EDITABLE);
        } else if (editMode == V2::EditMode::DELETABLE) {
            json->PutFixedAttr("editable", "EditMode.Deletable", filter, FIXED_ATTR_EDITABLE);
        } else if (editMode == (V2::EditMode::DELETABLE | V2::EditMode::MOVABLE)) {
            json->PutFixedAttr("editable", true, filter, FIXED_ATTR_EDITABLE);
        } else {
            json->PutFixedAttr("editable", false, filter, FIXED_ATTR_EDITABLE);
        }
        return;
    }
    auto sticky = propStickyMode_.value_or(V2::StickyMode::NONE);
    if (sticky == V2::StickyMode::NORMAL) {
        json->PutExtAttr("sticky", "Sticky.Normal", filter);
    } else if (sticky == V2::StickyMode::OPACITY) {
        json->PutExtAttr("sticky", "Sticky.Opacity", filter);
    } else {
        json->PutExtAttr("sticky", "Sticky.None", filter);
    }
    if (editMode == V2::EditMode::NONE) {
        json->PutFixedAttr("editable", "EditMode.None", filter, FIXED_ATTR_EDITABLE);
    } else if (editMode == V2::EditMode::MOVABLE) {
        json->PutFixedAttr("editable", "EditMode.Movable", filter, FIXED_ATTR_EDITABLE);
    } else if (editMode == V2::EditMode::DELETABLE) {
        json->PutFixedAttr("editable", "EditMode.Deletable", filter, FIXED_ATTR_EDITABLE);
    } else if (editMode == (V2::EditMode::DELETABLE | V2::EditMode::MOVABLE)) {
        json->PutFixedAttr("editable", true, filter, FIXED_ATTR_EDITABLE);
    } else {
        json->PutFixedAttr("editable", false, filter, FIXED_ATTR_EDITABLE);
    }
    if (propEdgeEffect_.has_value()) {
        auto swipeAction = JsonUtil::Create(true);
        swipeAction->Put("edgeEffect", propEdgeEffect_.value() == V2::SwipeEdgeEffect::Spring ?
            "SwipeEdgeEffect.Spring" : "SwipeEdgeEffect.None");
        json->PutExtAttr("swipeAction", swipeAction, filter);
    } else {
        auto swipeAction = JsonUtil::Create(true);
        json->PutExtAttr("swipeAction", swipeAction, filter);
    }
    json->PutExtAttr("startDeleteAreaDistance",
        propStartDeleteAreaDistance_.value_or(Dimension(0, DimensionUnit::VP)).ToString().c_str(), filter);
    json->PutExtAttr("endDeleteAreaDistance",
        propEndDeleteAreaDistance_.value_or(Dimension(0, DimensionUnit::VP)).ToString().c_str(), filter);
}
}
