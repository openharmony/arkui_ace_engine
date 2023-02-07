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

#include "core/components_v2/inspector/list_item_group_composed_element.h"
#include "base/log/dump_log.h"
#include "core/components_v2/inspector/utils.h"

namespace OHOS::Ace::V2 {

namespace {
const std::unordered_map<std::string, std::function<std::string(const ListItemGroupComposedElement&)>>
    CREATE_JSON_MAP {
    { "space", [](const ListItemGroupComposedElement& inspector) { return inspector.GetSpace(); } }
};
const std::unordered_map<std::string, std::function<std::unique_ptr<JsonValue>(const ListItemGroupComposedElement&)>>
    CREATE_JSON_JSON_VALUE_MAP {
    { "divider", [](const ListItemGroupComposedElement& inspector) { return inspector.GetDivider(); } }
};
} // namespace

void ListItemGroupComposedElement::Dump()
{
    InspectorComposedElement::Dump();
    DumpLog::GetInstance().AddDesc(
        std::string("space: ").append(GetSpace()));
}

std::string ListItemGroupComposedElement::GetSpace() const
{
    auto node = GetInspectorNode(ListItemGroupElement::TypeId());
    if (!node) {
        return "0";
    }
    auto renderListItemGroup = AceType::DynamicCast<RenderListItemGroup>(node);
    if (renderListItemGroup) {
        return renderListItemGroup->GetListSpace().ToString();
    }
    return "0";
}

std::unique_ptr<JsonValue> ListItemGroupComposedElement::GetDivider() const
{
    auto jsonValue = JsonUtil::Create(true);
    do {
        auto node = GetInspectorNode(ListItemGroupElement::TypeId());
        if (!node) {
            LOGE("list inspector node is null when try get divider for list inspector");
            break;
        }
        auto renderListItemGroup = AceType::DynamicCast<RenderListItemGroup>(node);
        if (!renderListItemGroup) {
            LOGE("list render node is null when try get divider for list inspector");
            break;
        }
        auto listItemGroupComponent =
            AceType::DynamicCast<ListItemGroupComponent>(renderListItemGroup->GetComponent());
        if (!listItemGroupComponent) {
            LOGE("list component is null when try get divider for list inspector");
            break;
        }
        const auto& divider = listItemGroupComponent->GetItemDivider();
        if (!divider) {
            LOGE("item divider is null when try get divider for list inspector");
            break;
        }
        jsonValue->Put("strokeWidth", divider->strokeWidth.ToString().c_str());
        jsonValue->Put("color", ConvertColorToString(divider->color).c_str());
        jsonValue->Put("startMargin", divider->startMargin.ToString().c_str());
        jsonValue->Put("endMargin", divider->endMargin.ToString().c_str());
        return jsonValue;
    } while (false);
    jsonValue->Put("strokeWidth", "0.0vp");
    jsonValue->Put("color", "#FFFFFFFF");
    jsonValue->Put("startMargin", "0.0vp");
    jsonValue->Put("endMargin", "0.0vp");
    return jsonValue;
}

std::unique_ptr<JsonValue> ListItemGroupComposedElement::ToJsonObject() const
{
    auto resultJson = InspectorComposedElement::ToJsonObject();
    for (const auto& value : CREATE_JSON_MAP) {
        resultJson->Put(value.first.c_str(), value.second(*this).c_str());
    }
    for (const auto& value : CREATE_JSON_JSON_VALUE_MAP) {
        resultJson->Put(value.first.c_str(), value.second(*this));
    }
    return resultJson;
}

RefPtr<Element> ListItemGroupComposedElement::GetElementChildBySlot(const RefPtr<Element>& element, int32_t& slot) const
{
    auto listItemGroupElement = AceType::DynamicCast<ListItemGroupElement>(element);
    CHECK_NULL_RETURN(listItemGroupElement, nullptr);
    return listItemGroupElement->GetListItemBySlot(slot);
}

} // namespace OHOS::Ace::V2