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

#include "core/components_v2/inspector/list_item_composed_element.h"

#include "base/log/dump_log.h"
#include "core/components/common/layout/constants.h"
#include "core/components_v2/inspector/utils.h"
#include "core/components_v2/list/list_item_element.h"
#include "core/components_v2/list/render_list_item.h"

namespace OHOS::Ace::V2 {
namespace {

const std::unordered_map<std::string, std::function<std::string(const ListItemComposedElement&)>> CREATE_JSON_MAP {
    { "sticky", [](const ListItemComposedElement& inspector) { return inspector.GetSticky(); } },
    { "editMode", [](const ListItemComposedElement& inspector) { return inspector.GetEditMode(); } }
};

}

void ListItemComposedElement::Dump()
{
    InspectorComposedElement::Dump();
    DumpLog::GetInstance().AddDesc(
        std::string("sticky: ").append(GetSticky()));
    DumpLog::GetInstance().AddDesc(
        std::string("editMode: ").append(GetEditMode()));
}


std::unique_ptr<JsonValue> ListItemComposedElement::ToJsonObject() const
{
    auto resultJson = InspectorComposedElement::ToJsonObject();
    for (const auto& value : CREATE_JSON_MAP) {
        resultJson->Put(value.first.c_str(), value.second(*this).c_str());
    }
    return resultJson;
}

std::string ListItemComposedElement::GetSticky() const
{
    auto node = GetInspectorNode(ListItemElement::TypeId());
    if (!node) {
        return "Sticky.None";
    }
    auto renderListItem = AceType::DynamicCast<RenderListItem>(node);
    if (renderListItem) {
        return renderListItem->GetSticky() == StickyMode::NONE ? "Sticky.None" : "Sticky.Normal";
    }
    return "Sticky.None";
}

std::string ListItemComposedElement::GetEditMode() const
{
    auto node = GetInspectorNode(ListItemElement::TypeId());
    if (!node) {
        return "EditMode.None";
    }
    auto renderListItem = AceType::DynamicCast<RenderListItem>(node);
    if (!renderListItem) {
        return "EditMode.None";
    }
    if (renderListItem->IsDeletable()) {
        if (renderListItem->IsMovable()) {
            return "EditMode.Deletable | EditMode.Movable";
        } else {
            return "EditMode.Deletable";
        }
    } else {
        if (renderListItem->IsMovable()) {
            return "EditMode.Movable";
        } else {
            return "EditMode.None";
        }
    }
}

} // namespace OHOS::Ace::V2