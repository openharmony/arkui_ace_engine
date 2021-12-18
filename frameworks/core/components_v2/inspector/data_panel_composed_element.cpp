/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "core/components_v2/inspector/data_panel_composed_element.h"

#include <unordered_map>

#include "base/log/dump_log.h"
#include "core/components/common/layout/constants.h"
#include "core/components/data_panel/data_panel_element.h"
#include "core/components_v2/inspector/utils.h"

namespace OHOS::Ace::V2 {
namespace {

const std::unordered_map<std::string, std::function<std::string(const DataPanelComposedElement&)>> CREATE_JSON_MAP {
    { "values", [](const DataPanelComposedElement& inspector) { return inspector.GetValues(); } },
    { "max", [](const DataPanelComposedElement& inspector) { return inspector.GetMax(); } },
    { "closeEffect", [](const DataPanelComposedElement& inspector) { return inspector.GetCloseEffect(); } }
};

} // namespace

void DataPanelComposedElement::Dump()
{
    InspectorComposedElement::Dump();
    DumpLog::GetInstance().AddDesc(std::string("values: ").append(GetValues()));
    DumpLog::GetInstance().AddDesc(std::string("max: ").append(GetMax()));
    DumpLog::GetInstance().AddDesc(std::string("closeEffect: ").append(GetCloseEffect()));
}

std::unique_ptr<JsonValue> DataPanelComposedElement::ToJsonObject() const
{
    auto resultJson = InspectorComposedElement::ToJsonObject();
    for (const auto& value : CREATE_JSON_MAP) {
        resultJson->Put(value.first.c_str(), value.second(*this).c_str());
    }
    return resultJson;
}

std::string DataPanelComposedElement::GetValues() const
{
    auto render = GetRenderPercentageDataPanel();
    if (render) {
        std::string values = "";
        auto Segments = render->GetSegments();
        for (size_t i = 0; i < Segments.size(); ++i) {
            double value = Segments[i].GetValue();
            values += std::to_string(value) + " ";
        }
        return values;
    }
    return "";
}

std::string DataPanelComposedElement::GetMax() const
{
    auto render = GetRenderPercentageDataPanel();
    if (render) {
        return std::to_string(render->GetMaxValue());
    }
    return "";
}

std::string DataPanelComposedElement::GetCloseEffect() const
{
    auto render = GetRenderPercentageDataPanel();
    if (render) {
        return ConvertBoolToString(render->GetCloseEffect());
    }
    return "";
}

RefPtr<RenderPercentageDataPanel> DataPanelComposedElement::GetRenderPercentageDataPanel() const
{
    auto node = GetInspectorNode(DataPanelElement::TypeId());
    if (node) {
        return AceType::DynamicCast<RenderPercentageDataPanel>(node);
    }
    return nullptr;
}

} // namespace OHOS::Ace::V2
