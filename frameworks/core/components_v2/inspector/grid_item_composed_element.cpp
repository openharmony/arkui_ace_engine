/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "core/components_v2/inspector/grid_item_composed_element.h"

#include "base/log/dump_log.h"
#include "core/components/grid_layout/render_grid_layout_item.h"

namespace OHOS::Ace::V2 {
namespace {

const std::unordered_map<std::string, std::function<std::string(const GridItemComposedElement&)>> CREATE_JSON_MAP {
    { "rowStart", [](const GridItemComposedElement& inspector) { return inspector.GetRowStart(); } },
    { "rowEnd", [](const GridItemComposedElement& inspector) { return inspector.GetRowEnd(); } },
    { "columnStart", [](const GridItemComposedElement& inspector) { return inspector.GetColumnStart(); } },
    { "columnEnd", [](const GridItemComposedElement& inspector) { return inspector.GetColumnEnd(); } },
    { "forceRebuild", [](const GridItemComposedElement& inspector) { return inspector.GetForceRebuild(); } },
    { "selectable", [](const GridItemComposedElement& inspector) { return inspector.GetSelectable(); } }
};

}

void GridItemComposedElement::Dump()
{
    InspectorComposedElement::Dump();
    DumpLog::GetInstance().AddDesc(
        std::string("rowStart: ").append(GetRowStart()));
    DumpLog::GetInstance().AddDesc(
        std::string("rowEnd: ").append(GetRowEnd()));
    DumpLog::GetInstance().AddDesc(
        std::string("columnStart: ").append(GetColumnStart()));
    DumpLog::GetInstance().AddDesc(
        std::string("columnEnd: ").append(GetColumnEnd()));
    DumpLog::GetInstance().AddDesc(
        std::string("forceRebuild: ").append(GetForceRebuild()));
}

std::unique_ptr<JsonValue> GridItemComposedElement::ToJsonObject() const
{
    auto resultJson = InspectorComposedElement::ToJsonObject();
    for (const auto& value : CREATE_JSON_MAP) {
        resultJson->Put(value.first.c_str(), value.second(*this).c_str());
    }
    return resultJson;
}

std::string GridItemComposedElement::GetRowStart() const
{
    auto node = GetInspectorNode(GridLayoutItemElement::TypeId(), true);
    if (!node) {
        return "0";
    }
    auto renderGripItem = AceType::DynamicCast<RenderGridLayoutItem>(node);
    if (renderGripItem) {
        if (renderGripItem->GetRowStart() == -1) {
            return "0";
        }
        return std::to_string(renderGripItem->GetRowStart());
    }
    return "0";
}

std::string GridItemComposedElement::GetRowEnd() const
{
    auto node = GetInspectorNode(GridLayoutItemElement::TypeId(), true);
    if (!node) {
        return "0";
    }
    auto renderGripItem = AceType::DynamicCast<RenderGridLayoutItem>(node);
    if (renderGripItem) {
        if (renderGripItem->GetRowEnd() == 0) {
            return "0";
        }
        return std::to_string(renderGripItem->GetRowEnd() - 1);
    }
    return "0";
}

std::string GridItemComposedElement::GetColumnStart() const
{
    auto node = GetInspectorNode(GridLayoutItemElement::TypeId(), true);
    if (!node) {
        return "0";
    }
    auto renderGripItem = AceType::DynamicCast<RenderGridLayoutItem>(node);
    if (renderGripItem) {
        if (renderGripItem->GetColumnStart() == -1) {
            return "0";
        }
        return std::to_string(renderGripItem->GetColumnStart());
    }
    return "0";
}


std::string GridItemComposedElement::GetColumnEnd() const
{
    auto node = GetInspectorNode(GridLayoutItemElement::TypeId(), true);
    if (!node) {
        return "0";
    }
    auto renderGripItem = AceType::DynamicCast<RenderGridLayoutItem>(node);
    if (renderGripItem) {
        if (renderGripItem->GetColumnEnd() == 0) {
            return "0";
        }
        return std::to_string(renderGripItem->GetColumnEnd() - 1);
    }
    return "0";
}

std::string GridItemComposedElement::GetForceRebuild() const
{
    auto node = GetInspectorNode(GridLayoutItemElement::TypeId(), true);
    if (!node) {
        return "false";
    }
    auto renderGripItem = AceType::DynamicCast<RenderGridLayoutItem>(node);
    if (renderGripItem) {
        return renderGripItem->GetForceRebuild() ? "true" : "false";
    }
    return "false";
}

std::string GridItemComposedElement::GetSelectable() const
{
    auto node = GetInspectorNode(GridLayoutItemElement::TypeId(), true);
    if (!node) {
        return "true";
    }
    auto renderGripItem = AceType::DynamicCast<RenderGridLayoutItem>(node);
    if (renderGripItem) {
        return renderGripItem->GetSelectable() ? "true" : "false";
    }
    return "true";
}

} // namespace OHOS::Ace::V2