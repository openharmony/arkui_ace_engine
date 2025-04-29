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

#include "frameworks/bridge/declarative_frontend/jsview/models/gauge_model_impl.h"

#include "base/log/log_wrapper.h"
#include "bridge/declarative_frontend/jsview/js_gauge.h"
#include "bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/components/chart/chart_component.h"

namespace OHOS::Ace::Framework {

void GaugeModelImpl::Create(float values, float min, float max)
{
    auto progressChild = AceType::MakeRefPtr<ProgressComponent>(min, values, min, max, ProgressType::GAUGE);
    progressChild->SetIndicatorFlag(true);
    progressChild->SetInspectorTag("Gauge");
    ViewStackProcessor::GetInstance()->ClaimElementId(progressChild);
    ViewStackProcessor::GetInstance()->Push(progressChild);
    RefPtr<ProgressTheme> progressTheme = JSGauge::GetTheme<ProgressTheme>();
    progressChild->InitStyle(progressTheme);
}

void GaugeModelImpl::SetValue(float value)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto gaugeComponent = AceType::DynamicCast<ProgressComponent>(component);
    if (!gaugeComponent) {
        return;
    }
    gaugeComponent->SetValue(value);
}

void GaugeModelImpl::SetStartAngle(float startAngle)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto gaugeComponent = AceType::DynamicCast<ProgressComponent>(component);
    if (!gaugeComponent) {
        return;
    }
    gaugeComponent->GetTrack()->GetTrackInfo()->SetStartDegree(startAngle);
}

void GaugeModelImpl::SetEndAngle(float endAngle)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto gaugeComponent = AceType::DynamicCast<ProgressComponent>(component);
    if (!gaugeComponent) {
        return;
    }
    gaugeComponent->GetTrack()->GetTrackInfo()->SetSweepDegree(endAngle);
}

void GaugeModelImpl::SetColors(const std::vector<Color>& colors, const std::vector<float>& values)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    std::vector<double> values_old;
    for (size_t i = 0; i < values.size(); ++i) {
        values_old.push_back(values[i]);
    }
    auto gaugeComponent = AceType::DynamicCast<ProgressComponent>(component);
    if (!gaugeComponent) {
        return;
    }
    gaugeComponent->SetSectionsStyle(colors, values_old);
}

void GaugeModelImpl::SetStrokeWidth(const Dimension& strokeWidth)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto gaugeComponent = AceType::DynamicCast<ProgressComponent>(component);
    if (!gaugeComponent) {
        return;
    }
    gaugeComponent->SetTrackThickness(strokeWidth);
}

void GaugeModelImpl::SetLabelMarkedText(const std::string labelTextString)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto gaugeComponent = AceType::DynamicCast<ProgressComponent>(component);
    gaugeComponent->SetLabelMarkedText(labelTextString);
}

void GaugeModelImpl::SetMarkedTextColor(const Color& color)
{
    auto component = ViewStackProcessor::GetInstance()->GetMainComponent();
    auto gaugeComponent = AceType::DynamicCast<ProgressComponent>(component);
    gaugeComponent->SetMarkedTextColor(color);
}

} // namespace OHOS::Ace::Framework