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

#include "core/components_v2/inspector/grid_col_composed_element.h"

#include "base/log/dump_log.h"
#include "core/components_v2/grid_layout/render_grid_col.h"
#include "core/components_v2/grid_layout/render_grid_row.h"

namespace OHOS::Ace::V2 {
namespace {
constexpr int32_t MAX_PARENT_FIND_COUNT = 10;

void FindGridRowParent(RefPtr<RenderNode>& nodePtr)
{
    int32_t findCount = MAX_PARENT_FIND_COUNT;
    while (nodePtr && findCount > 0) {
        auto parentWeak = nodePtr->GetParent();
        nodePtr = parentWeak.Upgrade();
        if (!nodePtr) {
            return;
        }
        if (AceType::InstanceOf<RenderGridRow>(nodePtr)) {
            return;
        }
        findCount--;
    }
}

const std::unordered_map<std::string, std::function<std::string(const GridColComposedElement&)>> CREATE_JSON_MAP {
    { "span", [](const GridColComposedElement& inspector) { return inspector.GetGridColSpan(); } },
    { "offset", [](const GridColComposedElement& inspector) { return inspector.GetGridColOffset(); } },
    { "gridColOffset", [](const GridColComposedElement& inspector) { return inspector.GetGridColOffset(); } },
    { "order", [](const GridColComposedElement& inspector) { return inspector.GetGridColOffset(); } }
};

} // namespace

void GridColComposedElement::Dump()
{
    InspectorComposedElement::Dump();
    DumpLog::GetInstance().AddDesc(
        std::string("span: ").append(GetGridColSpan()));
    DumpLog::GetInstance().AddDesc(
        std::string("offset: ").append(GetGridColOffset()));
    DumpLog::GetInstance().AddDesc(
        std::string("gridColOffset: ").append(GetGridColOffset()));
    DumpLog::GetInstance().AddDesc(
        std::string("order: ").append(GetGridColOrder()));
}

std::unique_ptr<JsonValue> GridColComposedElement::ToJsonObject() const
{
    auto resultJson = InspectorComposedElement::ToJsonObject();
    for (const auto& value : CREATE_JSON_MAP) {
        resultJson->Put(value.first.c_str(), value.second(*this).c_str());
    }
    return resultJson;
}

std::string GridColComposedElement::GetGridColSpan() const
{
    auto renderNode = GetInspectorNode(GridColElement::TypeId());
    auto renderGridCol = AceType::DynamicCast<RenderGridCol>(renderNode);
    if (!renderNode) {
        return "0";
    }
    FindGridRowParent(renderNode);
    if (!renderNode) {
        return "0";
    }
    auto renderGridRow = AceType::DynamicCast<RenderGridRow>(renderNode);
    if (!renderGridRow) {
        return "0";
    }
    return std::to_string(renderGridCol->GetSpan(renderGridRow->GetCurrentSizeType()));
}

std::string GridColComposedElement::GetGridColOffset() const
{
    auto renderNode = GetInspectorNode(GridColElement::TypeId());
    auto renderGridCol = AceType::DynamicCast<RenderGridCol>(renderNode);
    if (!renderNode) {
        return "0";
    }
    FindGridRowParent(renderNode);
    if (!renderNode) {
        return "0";
    }
    auto renderGridRow = AceType::DynamicCast<RenderGridRow>(renderNode);
    if (!renderGridRow) {
        return "0";
    }
    return std::to_string(renderGridCol->GetOffset(renderGridRow->GetCurrentSizeType()));
}

std::string GridColComposedElement::GetGridColOrder() const
{
    auto renderNode = GetInspectorNode(GridColElement::TypeId());
    auto renderGridCol = AceType::DynamicCast<RenderGridCol>(renderNode);
    if (!renderNode) {
        return "0";
    }
    FindGridRowParent(renderNode);
    if (!renderNode) {
        return "0";
    }
    auto renderGridRow = AceType::DynamicCast<RenderGridRow>(renderNode);
    if (!renderGridRow) {
        return "0";
    }
    return std::to_string(renderGridCol->GetOrder(renderGridRow->GetCurrentSizeType()));
}

} // namespace OHOS::Ace::V2