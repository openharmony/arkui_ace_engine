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

#include "core/components_ng/pattern/grid/grid_item_layout_property.h"

#include "core/components_ng/pattern/grid/grid_pattern.h"

namespace OHOS::Ace::NG {

void GridItemLayoutProperty::ResetGridLayoutInfoAndMeasure() const
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto uiNode = DynamicCast<UINode>(host);
    while (uiNode->GetTag() != V2::GRID_ETS_TAG) {
        uiNode = uiNode->GetParent();
        CHECK_NULL_VOID(uiNode);
    }
    auto grid = DynamicCast<FrameNode>(uiNode);
    CHECK_NULL_VOID(grid);
    auto pattern = grid->GetPattern<GridPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->ResetGridLayoutInfo();
    if (grid->GetParent()) {
        grid->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
}

void GridItemLayoutProperty::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    LayoutProperty::ToJsonValue(json, filter);
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    json->PutExtAttr("rowStart", std::to_string(propRowStart_.value_or(0)).c_str(), filter);
    json->PutExtAttr("rowEnd", std::to_string(propRowEnd_.value_or(0)).c_str(), filter);
    json->PutExtAttr("columnStart", std::to_string(propColumnStart_.value_or(0)).c_str(), filter);
    json->PutExtAttr("columnEnd", std::to_string(propColumnEnd_.value_or(0)).c_str(), filter);
}

int32_t GridItemLayoutProperty::GetCustomCrossIndex(Axis axis) const
{
    if (axis == Axis::VERTICAL) {
        return propColumnStart_.value_or(-1);
    }
    return propRowStart_.value_or(-1);
}

int32_t GridItemLayoutProperty::GetMainSpan(Axis axis) const
{
    if (axis == Axis::VERTICAL) {
        return std::max(propRowEnd_.value_or(-1) - propRowStart_.value_or(-1) + 1, 1);
    }
    return std::max(propColumnEnd_.value_or(-1) - propColumnStart_.value_or(-1) + 1, 1);
}

int32_t GridItemLayoutProperty::GetCrossSpan(Axis axis) const
{
    if (axis == Axis::VERTICAL) {
        return std::max(propColumnEnd_.value_or(-1) - propColumnStart_.value_or(-1) + 1, 1);
    }
    return std::max(propRowEnd_.value_or(-1) - propRowStart_.value_or(-1) + 1, 1);
}

int32_t GridItemLayoutProperty::GetMainStart(Axis axis) const
{
    if (axis == Axis::VERTICAL) {
        return propRowStart_.value_or(-1);
    }
    return propColumnStart_.value_or(-1);
}

int32_t GridItemLayoutProperty::GetCrossStart(Axis axis) const
{
    if (axis == Axis::VERTICAL) {
        return propColumnStart_.value_or(-1);
    }
    return propRowStart_.value_or(-1);
}

int32_t GridItemLayoutProperty::GetMainEnd(Axis axis) const
{
    if (axis == Axis::VERTICAL) {
        return propRowEnd_.value_or(-1);
    }
    return propColumnEnd_.value_or(-1);
}

int32_t GridItemLayoutProperty::GetCrossEnd(Axis axis) const
{
    if (axis == Axis::VERTICAL) {
        return propColumnEnd_.value_or(-1);
    }
    return propRowEnd_.value_or(-1);
}

int32_t GridItemLayoutProperty::GetRealMainSpan(Axis axis) const
{
    if (axis == Axis::VERTICAL) {
        return propRealRowSpan_.value_or(-1);
    }
    return propRealColumnSpan_.value_or(-1);
}

int32_t GridItemLayoutProperty::GetRealCrossSpan(Axis axis) const
{
    if (axis == Axis::VERTICAL) {
        return propRealColumnSpan_.value_or(-1);
    }
    return propRealRowSpan_.value_or(-1);
}

bool GridItemLayoutProperty::CheckWhetherCurrentItemAtExpectedPosition(Axis axis) const
{
    auto realMainSpan = GetRealMainSpan(axis);
    auto realCrossSpan = GetRealCrossSpan(axis);
    auto realMainIndex = propMainIndex_.value_or(-1);
    auto realCrossIndex = propCrossIndex_.value_or(-1);

    auto realMainStart = realMainIndex - realMainSpan + 1;
    auto realMainEnd = realMainIndex;
    auto realCrossStart = realCrossIndex;
    auto realCrossEnd = realCrossIndex + realCrossSpan - 1;

    auto expectMainStart = axis == Axis::VERTICAL ? propRowStart_.value_or(-1) : propColumnStart_.value_or(-1);
    auto expectMainEnd = axis == Axis::VERTICAL ? propRowEnd_.value_or(-1) : propColumnEnd_.value_or(-1);
    auto expectCrossStart = axis == Axis::VERTICAL ? propColumnStart_.value_or(-1) : propRowStart_.value_or(-1);
    auto expectCrossEnd = axis == Axis::VERTICAL ? propColumnEnd_.value_or(-1) : propRowEnd_.value_or(-1);

    if (realMainStart != expectMainStart || realMainEnd != expectMainEnd || realCrossStart != expectCrossStart ||
        realCrossEnd != expectCrossEnd) {
        return false;
    }
    return true;
}
} // namespace OHOS::Ace::NG
