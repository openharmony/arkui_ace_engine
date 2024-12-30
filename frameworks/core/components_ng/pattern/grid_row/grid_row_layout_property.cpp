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

namespace OHOS::Ace::NG {
using OHOS::Ace::V2::GridContainerUtils;
using OHOS::Ace::V2::GridContainerUtils;
const auto COLUMNS_DEFAULT_VALUE = 12;
const auto DIRECTION_DEFAULT_VALUE = V2::GridRowDirection::Row;
const auto ALIGN_ITEMS_DEFAULT_VALUE = FlexAlign::FLEX_START;

std::string BreakPointsReferenceToStr(V2::BreakPointsReference reference)
{
    switch (reference) {
        case V2::BreakPointsReference::WindowSize: return "BreakPointsReference.WindowSize";
        case V2::BreakPointsReference::ComponentSize: return "BreakPointsReference.ComponentSize";
        default:
            return "Unknown";
    }
}

std::string GridRowDirectionToStr(std::optional<V2::GridRowDirection> direction)
{
    if (!direction.has_value()) {
        return "Unknown";
    }
    switch (direction.value()) {
        case V2::GridRowDirection::Row: return "GridRowDirection.Row";
        case V2::GridRowDirection::RowReverse: return "GridRowDirection.RowReverse";
        default:
            return "Unknown";
    }
}

std::string FlexAlignToStr(FlexAlign alignItem)
{
    switch (alignItem) {
        case FlexAlign::AUTO: return "ItemAlign.Auto";
        case FlexAlign::FLEX_START: return "ItemAlign.Start";
        case FlexAlign::CENTER: return "ItemAlign.Center";
        case FlexAlign::FLEX_END: return "ItemAlign.End";
        case FlexAlign::STRETCH: return "ItemAlign.Stretch";
        case FlexAlign::BASELINE: return "ItemAlign.Baseline";
        default:
            return "Unknown";
    }
}
void GridRowLayoutProperty::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    LayoutProperty::ToJsonValue(json, filter);
    /* no fixed attr below, just return */
    if (filter.IsFastFilter()) {
        return;
    }
    auto sizeType = GetSizeTypeValue(V2::GridSizeType::UNDEFINED);
    auto gutter = GridContainerUtils::ProcessGutter(sizeType, GetGutterValue(V2::Gutter()));
    auto jsonGutter = JsonUtil::Create(false);
    jsonGutter->Put("x", std::to_string(gutter.first.ConvertToPx()).c_str());
    jsonGutter->Put("y", std::to_string(gutter.second.ConvertToPx()).c_str());
    json->Put("gutter", jsonGutter);

    auto columns = GridContainerUtils::ProcessColumn(
        sizeType, GetColumnsValue(V2::GridContainerSize(COLUMNS_DEFAULT_VALUE)));
    json->PutExtAttr("columns", std::to_string(columns).c_str(), filter);

    auto breakPoints = GetBreakPointsValue(V2::BreakPoints());
    auto jsonBreakpoints = JsonUtil::Create(false);
    auto jsonBreakpointsValues = JsonUtil::CreateArray(false);
    auto jsonBreakpointsItem = JsonUtil::Create(false);
    jsonBreakpointsItem->Put("val", "?");
    for (auto& breakpoint : breakPoints.breakpoints) {
        jsonBreakpointsItem->Replace("val", breakpoint.c_str());
        jsonBreakpointsValues->Put(jsonBreakpointsItem->GetValue("val"));
    }
    jsonBreakpoints->Put("value", jsonBreakpointsValues);
    auto referenceStr = BreakPointsReferenceToStr(breakPoints.reference);
    jsonBreakpoints->Put("reference", referenceStr.c_str());
    json->Put("breakpoints", jsonBreakpoints);
    
    auto direction = GetDirection().value_or(DIRECTION_DEFAULT_VALUE);
    auto directStr = GridRowDirectionToStr(direction);
    json->PutExtAttr("gridRowDirection", directStr.c_str(), filter);

    auto alignItem = GetAlignItemsValue(ALIGN_ITEMS_DEFAULT_VALUE);
    std::string alignItemsStr = FlexAlignToStr(alignItem);
    json->Put("itemAlign", alignItemsStr.c_str());
}
} // namespace OHOS::Ace::NG
