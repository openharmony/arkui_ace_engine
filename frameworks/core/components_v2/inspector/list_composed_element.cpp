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

#include "core/components_v2/inspector/list_composed_element.h"

#include "base/log/dump_log.h"
#include "core/components/common/layout/constants.h"
#include "core/components_v2/inspector/utils.h"
#include "core/components_v2/list/list_element.h"
#include "core/components_v2/list/render_list.h"

namespace OHOS::Ace::V2 {
namespace {

const std::unordered_map<std::string, std::function<std::string(const ListComposedElement&)>> CREATE_JSON_MAP {
    { "space", [](const ListComposedElement& inspector) { return inspector.GetSpace(); } },
    { "initialIndex", [](const ListComposedElement& inspector) { return inspector.GetInitialIndex(); } },
    { "listDirection", [](const ListComposedElement& inspector) { return inspector.GetListDirection(); } },
    { "editMode", [](const ListComposedElement& inspector) { return inspector.GetEditMode(); } }
};

}

void ListComposedElement::Dump()
{
    InspectorComposedElement::Dump();
    DumpLog::GetInstance().AddDesc(
        std::string("space: ").append(GetSpace()));
    DumpLog::GetInstance().AddDesc(
        std::string("initialIndex: ").append(GetInitialIndex()));
    DumpLog::GetInstance().AddDesc(
        std::string("listDirection: ").append(GetListDirection()));
    DumpLog::GetInstance().AddDesc(
        std::string("editMode: ").append(GetEditMode()));
}

std::unique_ptr<JsonValue> ListComposedElement::ToJsonObject() const
{
    auto resultJson = InspectorComposedElement::ToJsonObject();
    for (const auto& value : CREATE_JSON_MAP) {
        resultJson->Put(value.first.c_str(), value.second(*this).c_str());
    }
    return resultJson;
}

std::string ListComposedElement::GetSpace() const
{
    auto node = GetInspectorNode(ListElement::TypeId());
    if (!node) {
        return "0";
    }
    auto renderList = AceType::DynamicCast<RenderList>(node);
    if (renderList) {
        return std::to_string(renderList->GetSpace());
    }
    return "0";
}

std::string ListComposedElement::GetInitialIndex() const
{
    auto node = GetInspectorNode(ListElement::TypeId());
    if (!node) {
        return "0";
    }
    auto renderList = AceType::DynamicCast<RenderList>(node);
    if (renderList) {
        return std::to_string(renderList->GetStartIndex());
    }
    return "0";
}

std::string ListComposedElement::GetListDirection() const
{
    auto node = GetInspectorNode(ListElement::TypeId());
    if (!node) {
        return "Axis.Vertical";
    }
    auto renderList = AceType::DynamicCast<RenderList>(node);
    if (renderList) {
        return renderList->GetDirection() ? "Axis.Vertical" : "Axis.Horizontal";
    }
    return "Axis.Vertical";
}

std::string ListComposedElement::GetEditMode() const
{
    auto node = GetInspectorNode(ListElement::TypeId());
    if (!node) {
        return "false";
    }
    auto renderList = AceType::DynamicCast<RenderList>(node);
    if (renderList) {
        return renderList->GetEditable() ? "true" : "false";
    }
    return "false";
}

} // namespace OHOS::Ace::V2