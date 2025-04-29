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

#include "core/components_ng/pattern/grid_row/grid_row_layout_property.h"

#include "core/components_v2/grid_layout/grid_container_utils.h"

namespace {
std::string GetAlignItemsStr(OHOS::Ace::FlexAlign alignItems)
{
    switch (alignItems) {
        case OHOS::Ace::FlexAlign::CENTER:
            return "ItemAlign.Center";
        case OHOS::Ace::FlexAlign::STRETCH:
            return "ItemAlign.Stretch";
        case OHOS::Ace::FlexAlign::FLEX_END:
            return "ItemAlign.End";
        case OHOS::Ace::FlexAlign::FLEX_START:
            return "ItemAlign.Start";
        default:
            return "Unknown";
    }
}
};
namespace OHOS::Ace::NG {
using OHOS::Ace::V2::GridContainerUtils;
void GridRowLayoutProperty::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    LayoutProperty::ToJsonValue(json, filter);
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    auto sizeType = GetSizeTypeValue(V2::GridSizeType::UNDEFINED);
    std::string str;

    auto gutter = GridContainerUtils::ProcessGutter(sizeType, GetGutterValue());
    str.assign("<");
    str.append(std::to_string(gutter.first.ConvertToPx()));
    str.append(", ");
    str.append(std::to_string(gutter.second.ConvertToPx()));
    json->PutExtAttr("gutter", str.c_str(), filter);

    auto columns = GridContainerUtils::ProcessColumn(sizeType, GetColumnsValue());
    json->PutExtAttr("columns", std::to_string(columns).c_str(), filter);

    auto breakPoints = GetBreakPointsValue();
    str.assign("[");
    for (auto& breakpoint : breakPoints.breakpoints) {
        str.append(breakpoint);
        str.append(", ");
    }
    str = (static_cast<int32_t>(breakPoints.breakpoints.size()) > 1) ?
        str.substr(0, static_cast<int32_t>(str.size()) - 1).append("]") : str.append("]");
    json->PutExtAttr("breakpoints", str.c_str(), filter);
    if (breakPoints.reference == V2::BreakPointsReference::WindowSize) {
        str.assign("WindowSize");
    } else {
        str.assign("ComponentSize");
    }
    json->PutExtAttr("reference", str.c_str(), filter);
    auto direction = GetDirection();
    if (!direction) {
        str.assign("Row");
    } else if (direction == V2::GridRowDirection::Row) {
        str.assign("Row");
    } else if (direction == V2::GridRowDirection::RowReverse) {
        str.assign("RowReverse");
    } else {
        str.assign("Unknown");
    }
    json->PutExtAttr("direction", str.c_str(), filter);
    auto alignItems = GetAlignItems();
    json->PutExtAttr("alignItems", GetAlignItemsStr(alignItems.value_or(FlexAlign::FLEX_START)).c_str(), filter);
}
} // namespace OHOS::Ace::NG
