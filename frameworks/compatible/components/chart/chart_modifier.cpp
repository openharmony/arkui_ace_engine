/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
#include "compatible/components/chart/chart_modifier_compatible.h"

#include "compatible/components/chart/dom_chart.h"
#include "compatible/components/chart/chart_component.h"
#include "core/pipeline/base/render_node.h"

namespace OHOS::Ace::ChartModifier {
namespace {
RefPtr<ChartComponent> CreateChartComponent()
{
    auto chartComponent = AceType::MakeRefPtr<ChartComponent>();
    return chartComponent;
}

void SetChartDatasets(const RefPtr<Framework::DOMNode>& node, void* datasets)
{
    auto chart = AceType::DynamicCast<Framework::DOMChart>(node);
    if (chart && datasets) {
        chart->SetChartAttrDatasets(*static_cast<std::vector<MainChart>*>(datasets));
    }
}

void SetChartOptions(const RefPtr<Framework::DOMNode>& node, void* options)
{
    auto chart = AceType::DynamicCast<Framework::DOMChart>(node);
    if (chart && options) {
        chart->SetChartAttrOptions(*static_cast<Framework::ChartOptions*>(options));
    }
}

void SetChartSegments(const RefPtr<Framework::DOMNode>& node, void* segments)
{
    auto chart = AceType::DynamicCast<Framework::DOMChart>(node);
    if (chart && segments) {
        chart->SetChartAttrSegments(*static_cast<std::vector<Segment>*>(segments));
    }
}
} // namespace
const ArkUIChartModifierCompatible* GetChartModifier()
{
    static const ArkUIChartModifierCompatible instance = {
        .createChartComponent = CreateChartComponent,
        .setChartDatasets = SetChartDatasets,
        .setChartOptions = SetChartOptions,
        .setChartSegments = SetChartSegments,
    };
    return &instance;
}
} // namespace OHOS::Ace::ChartModifier