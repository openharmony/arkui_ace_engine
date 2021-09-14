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

#include "core/components_v2/inspector/grid_composed_element.h"

#include "base/log/dump_log.h"
#include "core/components/common/layout/constants.h"
#include "core/components/grid_layout/grid_layout_element.h"
#include "core/components/grid_layout/render_grid_layout.h"
#include "core/components_v2/inspector/utils.h"

namespace OHOS::Ace::V2 {
namespace {

const std::unordered_map<std::string, std::function<std::string(const GridComposedElement&)>> CREATE_JSON_MAP {
    { "columnsTemplate", [](const GridComposedElement& inspector) { return inspector.GetColumnsTemplate(); } },
    { "rowsTemplate", [](const GridComposedElement& inspector) { return inspector.GetRowsTemplate(); } },
    { "columnsGap", [](const GridComposedElement& inspector) { return inspector.GetColumnsGap(); } },
    { "rowsGap", [](const GridComposedElement& inspector) { return inspector.GetRowsGap(); } }
};

}

void GridComposedElement::Dump()
{
    InspectorComposedElement::Dump();
    DumpLog::GetInstance().AddDesc(
        std::string("columnsTemplate: ").append(GetColumnsTemplate()));
    DumpLog::GetInstance().AddDesc(
        std::string("rowsTemplate: ").append(GetRowsTemplate()));
    DumpLog::GetInstance().AddDesc(
        std::string("columnsGap: ").append(GetColumnsGap()));
    DumpLog::GetInstance().AddDesc(
        std::string("rowsGap: ").append(GetRowsGap()));
}

std::unique_ptr<JsonValue> GridComposedElement::ToJsonObject() const
{
    auto resultJson = InspectorComposedElement::ToJsonObject();
    for (const auto& value : CREATE_JSON_MAP) {
        resultJson->Put(value.first.c_str(), value.second(*this).c_str());
    }
    return resultJson;
}

std::string GridComposedElement::GetColumnsTemplate() const
{
    auto node = GetInspectorNode(GridLayoutElement::TypeId());
    if (!node) {
        return "1fr";
    }
    auto renderGrip = AceType::DynamicCast<RenderGridLayout>(node);
    if (renderGrip) {
        return renderGrip->GetColumnsTemplate();
    }
    return "1fr";
}

std::string GridComposedElement::GetRowsTemplate() const
{
    auto node = GetInspectorNode(GridLayoutElement::TypeId());
    if (!node) {
        return "1fr";
    }
    auto renderGrip = AceType::DynamicCast<RenderGridLayout>(node);
    if (renderGrip) {
        return renderGrip->GetRowTemplate();
    }
    return "1fr";
}

std::string GridComposedElement::GetColumnsGap() const
{
    auto node = GetInspectorNode(GridLayoutElement::TypeId());
    if (!node) {
        return "1fr";
    }
    auto renderGrip = AceType::DynamicCast<RenderGridLayout>(node);
    if (renderGrip) {
        return std::to_string(renderGrip->GetColumnsGap());
    }
    return "1fr";
}

std::string GridComposedElement::GetRowsGap() const
{
    auto node = GetInspectorNode(GridLayoutElement::TypeId());
    if (!node) {
        return "1fr";
    }
    auto renderGrip = AceType::DynamicCast<RenderGridLayout>(node);
    if (renderGrip) {
        return std::to_string(renderGrip->GetRowGaps());
    }
    return "1fr";
}

} // namespace OHOS::Ace::V2