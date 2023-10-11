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

#include "core/components_ng/pattern/grid/grid_layout_property.h"

#include "base/geometry/dimension.h"
#include "base/utils/utils.h"
#include "core/components/scroll/scroll_bar_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/grid/grid_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

void GridLayoutProperty::ResetGridLayoutInfoAndMeasure() const
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pattern = host->GetPattern<GridPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->ResetGridLayoutInfo();
    if (host->GetParent()) {
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
    }
}

void GridLayoutProperty::ResetPositionFlags() const
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pattern = host->GetPattern<GridPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->ResetPositionFlags();
}

void GridLayoutProperty::ToJsonValue(std::unique_ptr<JsonValue>& json) const
{
    LayoutProperty::ToJsonValue(json);
    json->Put("columnsTemplate", propColumnsTemplate_.value_or("").c_str());
    json->Put("rowsTemplate", propRowsTemplate_.value_or("").c_str());
    json->Put("columnsGap", propColumnsGap_.value_or(0.0_vp).ToString().c_str());
    json->Put("rowsGap", propRowsGap_.value_or(0.0_vp).ToString().c_str());
    json->Put("cachedCount", propCachedCount_.value_or(1));
    json->Put("editMode", propEditable_.value_or(false) ? "true" : "false");
    json->Put("layoutDirection", GetGridDirectionStr().c_str());
    json->Put("maxCount", propMaxCount_.value_or(Infinity<int32_t>()));
    json->Put("minCount", propMinCount_.value_or(1));
    json->Put("cellLength", propCellLength_.value_or(0));
    auto edgeEffect = propEdgeEffect_.value_or(EdgeEffect::NONE);
    if (edgeEffect == EdgeEffect::SPRING) {
        json->Put("edgeEffect", "EdgeEffect.Spring");
    } else if (edgeEffect == EdgeEffect::FADE) {
        json->Put("edgeEffect", "EdgeEffect.Fade");
    } else {
        json->Put("edgeEffect", "EdgeEffect.None");
    }
    json->Put("enableScrollInteraction", propScrollEnabled_.value_or(true));
}

std::string GridLayoutProperty::GetGridDirectionStr() const
{
    auto gridDirection = propGridDirection_.value_or(FlexDirection::ROW);
    switch (gridDirection) {
        case FlexDirection::ROW:
            return "GridDirection.Row";
        case FlexDirection::ROW_REVERSE:
            return "GridDirection.RowReverse";
        case FlexDirection::COLUMN:
            return "GridDirection.Column";
        case FlexDirection::COLUMN_REVERSE:
            return "GridDirection.ColumnReverse";
        default:
            LOGE("grid direction %{public}d is not valid", gridDirection);
            break;
    }
    return "GridDirection.Row";
}

} // namespace OHOS::Ace::NG
