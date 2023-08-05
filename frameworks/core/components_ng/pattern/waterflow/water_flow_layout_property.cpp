/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/waterflow/water_flow_layout_property.h"

#include "base/geometry/dimension.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/waterflow/water_flow_pattern.h"
#include "core/components_v2/inspector/utils.h"

namespace OHOS::Ace::NG {
void WaterFlowLayoutProperty::ResetWaterflowLayoutInfoAndMeasure() const
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pattern = host->GetPattern<WaterFlowPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->ResetLayoutInfo();
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
}

void WaterFlowLayoutProperty::ToJsonValue(std::unique_ptr<JsonValue>& json) const
{
    LayoutProperty::ToJsonValue(json);
    json->Put("columnsTemplate", propColumnsTemplate_.value_or("").c_str());
    json->Put("rowsTemplate", propRowsTemplate_.value_or("").c_str());
    json->Put("columnsGap", propColumnsGap_.value_or(0.0_vp).ToString().c_str());
    json->Put("rowsGap", propRowsGap_.value_or(0.0_vp).ToString().c_str());
    json->Put("layoutDirection ", GetWaterflowDirectionStr().c_str());
    auto jsonConstraintSize = JsonUtil::Create(true);
    if (itemLayoutConstraint_) {
        jsonConstraintSize->Put("minWidth", itemLayoutConstraint_->minSize.value_or(CalcSize())
                                                .Width()
                                                .value_or(CalcLength(0, DimensionUnit::VP))
                                                .ToString()
                                                .c_str());
        jsonConstraintSize->Put("minHeight", itemLayoutConstraint_->minSize.value_or(CalcSize())
                                                .Height()
                                                .value_or(CalcLength(0, DimensionUnit::VP))
                                                .ToString()
                                                .c_str());
        jsonConstraintSize->Put("maxWidth", itemLayoutConstraint_->maxSize.value_or(CalcSize())
                                                .Width()
                                                .value_or(CalcLength(Infinity<double>(), DimensionUnit::VP))
                                                .ToString()
                                                .c_str());
        jsonConstraintSize->Put("maxHeight", itemLayoutConstraint_->maxSize.value_or(CalcSize())
                                                .Height()
                                                .value_or(CalcLength(Infinity<double>(), DimensionUnit::VP))
                                                .ToString()
                                                .c_str());
        json->Put("itemConstraintSize", jsonConstraintSize->ToString().c_str());
    } else {
        json->Put("itemConstraintSize", "0");
    }
    json->Put("enableScrollInteraction", propScrollEnabled_.value_or(true));
}

std::string WaterFlowLayoutProperty::GetWaterflowDirectionStr() const
{
    auto WaterflowDirection = propWaterflowDirection_.value_or(FlexDirection::COLUMN);
    return V2::ConvertFlexDirectionToStirng(WaterflowDirection);
}

RefPtr<LayoutProperty> WaterFlowLayoutProperty::Clone() const
{
    auto value = MakeRefPtr<WaterFlowLayoutProperty>();
    value->LayoutProperty::UpdateLayoutProperty(DynamicCast<LayoutProperty>(this));
    value->propRowsTemplate_ = CloneRowsTemplate();
    value->propColumnsTemplate_ = CloneColumnsTemplate();
    value->propRowsGap_ = CloneRowsGap();
    value->propColumnsGap_ = CloneColumnsGap();
    value->propWaterflowDirection_ = CloneWaterflowDirection();
    value->propScrollEnabled_ = CloneScrollEnabled();
    if (itemLayoutConstraint_) {
        value->itemLayoutConstraint_ = std::make_unique<MeasureProperty>(*itemLayoutConstraint_);
    }
    return value;
}
} // namespace OHOS::Ace::NG
