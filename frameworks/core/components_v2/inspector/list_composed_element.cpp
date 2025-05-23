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
#include "core/components_v2/inspector/utils.h"

namespace OHOS::Ace::V2 {
namespace {

const std::unordered_map<std::string, std::function<std::string(const ListComposedElement&)>> CREATE_JSON_MAP {
    { "space", [](const ListComposedElement& inspector) { return inspector.GetSpace(); } },
    { "initialIndex", [](const ListComposedElement& inspector) { return inspector.GetInitialIndex(); } },
    { "listDirection", [](const ListComposedElement& inspector) { return inspector.GetListDirection(); } },
    { "editMode", [](const ListComposedElement& inspector) { return inspector.GetEditMode(); } },
    { "edgeEffect", [](const ListComposedElement& inspector) { return inspector.GetEdgeEffect(); } },
    { "chainAnimation", [](const ListComposedElement& inspector) { return inspector.GetChainAnimation(); } },
    { "restoreId", [](const ListComposedElement& inspector) { return inspector.GetRestoreId(); } },
    { "multiSelectable ", [](const ListComposedElement& inspector) { return inspector.GetMultiSelectable(); } },
    { "scrollBar ", [](const ListComposedElement& inspector) { return inspector.GetScrollBar(); } }
};

const std::unordered_map<std::string, std::function<std::unique_ptr<JsonValue>(const ListComposedElement&)>>
    CREATE_JSON_JSON_VALUE_MAP {
    { "divider", [](const ListComposedElement& inspector) { return inspector.GetDivider(); } }
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
    DumpLog::GetInstance().AddDesc(
        std::string("chainAnimation: ").append(GetChainAnimation()));
}

std::unique_ptr<JsonValue> ListComposedElement::ToJsonObject() const
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

std::string ListComposedElement::GetSpace() const
{
    auto node = GetInspectorNode(ListElement::TypeId());
    if (!node) {
        return "0";
    }
    auto renderList = AceType::DynamicCast<RenderList>(node);
    if (renderList) {
        return renderList->GetListSpace().ToString().c_str();
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
        return std::to_string(renderList->GetIndex());
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
        return renderList->IsVertical() ? "Axis.Vertical" : "Axis.Horizontal";
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

std::string ListComposedElement::GetRestoreId() const
{
    auto node = GetInspectorNode(ListElement::TypeId());
    if (!node) {
        return "";
    }
    auto renderList = AceType::DynamicCast<RenderList>(node);
    if (renderList) {
        std::string res;
        auto restoreId = renderList->GetRestoreId();
        if (restoreId >= 0) {
            res = std::to_string(restoreId);
        }
        return res;
    }
    return "";
}

std::string ListComposedElement::GetMultiSelectable() const
{
    auto node = GetInspectorNode(ListElement::TypeId());
    if (!node) {
        return "false";
    }
    auto renderList = AceType::DynamicCast<RenderList>(node);
    if (renderList) {
        return renderList->GetMultiSelectable() ? "true" : "false";
    }
    return "false";
}

std::unique_ptr<JsonValue> ListComposedElement::GetDivider() const
{
    auto jsonValue = JsonUtil::Create(true);
    do {
        auto node = GetInspectorNode(ListElement::TypeId());
        if (!node) {
            LOGE("list inspector node is null when try get divider for list inspector");
            break;
        }
        auto renderList = AceType::DynamicCast<RenderList>(node);
        if (!renderList) {
            LOGE("list render node is null when try get divider for list inspector");
            break;
        }
        auto listComponent = AceType::DynamicCast<ListComponent>(renderList->GetComponent());
        if (!listComponent) {
            LOGE("list component is null when try get divider for list inspector");
            break;
        }
        const auto& divider = listComponent->GetItemDivider();
        if (!divider) {
            LOGE("item divider is null when try get divider for list inspector");
            break;
        }
        jsonValue->Put("strokeWidth", divider->strokeWidth.ToString().c_str());
        jsonValue->Put("color", ConvertColorToString(divider->color).c_str());
        jsonValue->Put("startMargin", divider->startMargin.ToString().c_str());
        jsonValue->Put("endMargin", divider->endMargin.ToString().c_str());
        return jsonValue;
    } while (0);
    jsonValue->Put("strokeWidth", "0.0vp");
    jsonValue->Put("color", "#FFFFFFFF");
    jsonValue->Put("startMargin", "0.0vp");
    jsonValue->Put("endMargin", "0.0vp");
    return jsonValue;
}

std::string ListComposedElement::GetEdgeEffect() const
{
    do {
        auto node = GetInspectorNode(ListElement::TypeId());
        if (!node) {
            LOGE("list inspector node is null when try get edge effect for list inspector.");
            break;
        }
        auto renderList = AceType::DynamicCast<RenderList>(node);
        if (!renderList) {
            LOGE("list render node is null when try get edge effect for list inspector.");
            break;
        }
        auto listComponent = AceType::DynamicCast<ListComponent>(renderList->GetComponent());
        if (!listComponent) {
            LOGE("list component is null when try get edge effect for list inspector.");
            break;
        }
        switch (listComponent->GetEdgeEffect()) {
            case EdgeEffect::FADE:
                return "EdgeEffect.Fade";
            case EdgeEffect::NONE:
                return "EdgeEffect.None";
            case EdgeEffect::SPRING:
            default:
                return "EdgeEffect.Spring";
        }
    } while (0);
    return "EdgeEffect.Spring";
}

std::string ListComposedElement::GetChainAnimation() const
{
    auto node = GetInspectorNode(ListElement::TypeId());
    if (!node) {
        return "false";
    }
    auto renderList = AceType::DynamicCast<RenderList>(node);
    if (renderList) {
        return renderList->GetLinkage() ? "true" : "false";
    }
    return "false";
}

std::string ListComposedElement::GetScrollBar() const
{
    auto node = GetInspectorNode(ListElement::TypeId());
    if (!node) {
        return "BarState.Off";
    }
    auto renderList = AceType::DynamicCast<RenderList>(node);
    if (!renderList) {
        return "BarState.Off";
    }
    auto listComponent = AceType::DynamicCast<ListComponent>(renderList->GetComponent());
    if (!listComponent) {
        return "BarState.Off";
    }
    switch (listComponent->GetScrollBar()) {
        case DisplayMode::AUTO:
            return "BarState.Auto";
        case DisplayMode::ON:
            return "BarState.On";
        case DisplayMode::OFF:
        default:
            return "BarState.Off";
    }
    return "BarState.Off";
}

RefPtr<Element> ListComposedElement::GetElementChildBySlot(const RefPtr<Element>& element, int32_t& slot) const
{
    auto listElement = AceType::DynamicCast<ListElement>(element);
    CHECK_NULL_RETURN(listElement, nullptr);
    return listElement->GetListItemBySlot(slot);
}

} // namespace OHOS::Ace::V2