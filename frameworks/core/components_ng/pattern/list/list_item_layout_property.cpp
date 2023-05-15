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
#include "core/components/common/layout/constants.h"
#include "core/components_v2/list/list_properties.h"

namespace OHOS::Ace::NG {

void ListItemLayoutProperty::ToJsonValue(std::unique_ptr<JsonValue>& json) const
{
    LayoutProperty::ToJsonValue(json);
    auto sticky = propStickyMode_.value_or(V2::StickyMode::NONE);
    if (sticky == V2::StickyMode::NORMAL) {
        json->Put("sticky", "Sticky.Normal");
    } else if (sticky == V2::StickyMode::OPACITY) {
        json->Put("sticky", "Sticky.Opacity");
    } else {
        json->Put("sticky", "Sticky.None");
    }
    auto editMode = propEditMode_.value_or(V2::EditMode::SHAM);
    if (editMode == V2::EditMode::NONE) {
        json->Put("editable", "EditMode.None");
    } else if (editMode == V2::EditMode::MOVABLE) {
        json->Put("editable", "EditMode.Movable");
    } else if (editMode == V2::EditMode::DELETABLE) {
        json->Put("editable", "EditMode.Deletable");
    } else if (editMode == (V2::EditMode::DELETABLE | V2::EditMode::MOVABLE)) {
        json->Put("editable", true);
    } else {
        json->Put("editable", false);
    }
    if (propEdgeEffect_.has_value()) {
        auto swipeAction = JsonUtil::Create(true);
        swipeAction->Put("edgeEffect", propEdgeEffect_.value() == V2::SwipeEdgeEffect::Spring ?
            "SwipeEdgeEffect.Spring" : "SwipeEdgeEffect.Node");
        json->Put("swipeAction", swipeAction);
    } else {
        auto swipeAction = JsonUtil::Create(true);
        json->Put("swipeAction", swipeAction);
    }
    json->Put("startDeleteAreaDistance",
        propStartDeleteAreaDistance_.value_or(Dimension(0, DimensionUnit::VP)).ToString().c_str());
    json->Put("endDeleteAreaDistance",
        propEndDeleteAreaDistance_.value_or(Dimension(0, DimensionUnit::VP)).ToString().c_str());
}
}
