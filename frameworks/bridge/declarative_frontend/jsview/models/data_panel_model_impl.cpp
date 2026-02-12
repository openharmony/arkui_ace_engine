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

#include "frameworks/bridge/declarative_frontend/jsview/models/data_panel_model_impl.h"

#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/components/data_panel/data_panel_component.h"

namespace OHOS::Ace::Framework {

constexpr size_t MAX_COUNT = 9;
void DataPanelModelImpl::Create(const std::vector<double>& values, double max, int32_t type)
{
    RefPtr<PercentageDataPanelComponent> component =
        AceType::MakeRefPtr<PercentageDataPanelComponent>(ChartType::RAINBOW);
    double valueSum = 0.0;
    // values
    size_t length = static_cast<size_t>(values.size());
    for (size_t i = 0; i < length && i < MAX_COUNT; i++) {
        auto value = values[i];
        if (LessOrEqual(value, 0.0)) {
            value = 0.0;
        }
        valueSum += value;
        if (GreatOrEqual(valueSum, max) && max > 0) {
            value = max - (valueSum - value);
            if (NearEqual(value, 0.0)) {
                break;
            }
            Segment segment;
            segment.SetValue(value);
            segment.SetColorType(SegmentStyleType::NONE);
            component->AppendSegment(segment);
            break;
        }
        Segment segment;
        segment.SetValue(value);
        segment.SetColorType(SegmentStyleType::NONE);
        component->AppendSegment(segment);
    }
    if (LessOrEqual(max, 0.0)) {
        max = valueSum;
    }
    component->SetMaxValue(max);
    if (type == 1) {
        component->SetPanelType(ChartType::LINE);
    } else if (type == 0) {
        component->SetPanelType(ChartType::RAINBOW);
    }
    RefPtr<ThemeManager> dataPanelManager = AceType::MakeRefPtr<ThemeManagerImpl>();
    component->InitalStyle(dataPanelManager);
    ViewStackProcessor::GetInstance()->ClaimElementId(component);
    ViewStackProcessor::GetInstance()->Push(component);
}

void DataPanelModelImpl::SetEffect(bool isCloseEffect)
{
    auto dataPanelComponent =
        AceType::DynamicCast<DataPanelComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(dataPanelComponent);
    dataPanelComponent->SetEffects(!isCloseEffect);
}

} // namespace OHOS::Ace::Framework