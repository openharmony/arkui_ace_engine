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

#include "core/components_v2/inspector/water_flow_composed_element.h"

#include "base/log/dump_log.h"
#include "core/components_v2/inspector/utils.h"

namespace OHOS::Ace::V2 {
namespace {

const std::unordered_map<std::string, std::function<std::string(const WaterFlowComposedElement&)>> CREATE_JSON_MAP {
    { "columnsTemplate", [](const WaterFlowComposedElement& inspector) { return inspector.GetColumnsTemplate(); } },
    { "rowsTemplate", [](const WaterFlowComposedElement& inspector) { return inspector.GetRowsTemplate(); } },
    { "columnsGap", [](const WaterFlowComposedElement& inspector) { return inspector.GetColumnsGap(); } },
    { "rowsGap", [](const WaterFlowComposedElement& inspector) { return inspector.GetRowsGap(); } },
    { "itemConstraintSize",
        [](const WaterFlowComposedElement& inspector) { return inspector.GetItemConstraintSize(); } },
};

} // namespace

void WaterFlowComposedElement::Dump()
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
    DumpLog::GetInstance().AddDesc(
        std::string("itemConstraintSize: ").append(GetItemConstraintSize()));
}

std::unique_ptr<JsonValue> WaterFlowComposedElement::ToJsonObject() const
{
    auto resultJson = InspectorComposedElement::ToJsonObject();
    for (const auto& value : CREATE_JSON_MAP) {
        resultJson->Put(value.first.c_str(), value.second(*this).c_str());
    }
    return resultJson;
}

std::string WaterFlowComposedElement::GetColumnsTemplate() const
{
    std::string ret = "1fr";
    auto node = GetInspectorNode(WaterFlowElement::TypeId());
    if (!node) {
        return ret;
    }
    auto waterFlow = AceType::DynamicCast<RenderWaterFlow>(node);
    if (waterFlow) {
        return waterFlow->GetColumnsArgs();
    }
    return ret;
}

std::string WaterFlowComposedElement::GetRowsTemplate() const
{
    std::string ret = "1fr";
    auto node = GetInspectorNode(WaterFlowElement::TypeId());
    if (!node) {
        return ret;
    }
    auto waterFlow = AceType::DynamicCast<RenderWaterFlow>(node);
    if (waterFlow) {
        return waterFlow->GetRowsArgs();
    }
    return ret;
}

std::string WaterFlowComposedElement::GetColumnsGap() const
{
    std::string ret = "0";
    auto node = GetInspectorNode(WaterFlowElement::TypeId());
    if (!node) {
        return ret;
    }
    auto waterFlow = AceType::DynamicCast<RenderWaterFlow>(node);
    if (waterFlow) {
        return waterFlow->GetColumnsGap().ToString();
    }
    return ret;
}

std::string WaterFlowComposedElement::GetRowsGap() const
{
    std::string ret = "0";
    auto node = GetInspectorNode(WaterFlowElement::TypeId());
    if (!node) {
        return ret;
    }
    auto waterFlow = AceType::DynamicCast<RenderWaterFlow>(node);
    if (waterFlow) {
        return waterFlow->GetRowsGap().ToString();
    }
    return ret;
}

std::string WaterFlowComposedElement::GetlayoutDirection() const
{
    std::string ret = ConvertFlexDirectionToStirng(FlexDirection::COLUMN);
    auto node = GetInspectorNode(WaterFlowElement::TypeId());
    if (!node) {
        return ret;
    }
    auto waterFlow = AceType::DynamicCast<RenderWaterFlow>(node);
    if (waterFlow) {
        return ConvertFlexDirectionToStirng(waterFlow->GetlayoutDirection());
    }
    return ret;
}

std::string WaterFlowComposedElement::GetItemConstraintSize() const
{
    std::string ret = "0";
    auto node = GetInspectorNode(WaterFlowElement::TypeId());
    if (!node) {
        return ret;
    }
    auto waterFlow = AceType::DynamicCast<RenderWaterFlow>(node);
    if (waterFlow) {
        auto jsonStr = JsonUtil::Create(true);
        auto constraintSize = waterFlow->GetItemConstraintSize();
        jsonStr->Put("minWidth", std::to_string(constraintSize.minCrossSize).c_str());
        jsonStr->Put("minHeight", std::to_string(constraintSize.minMainSize).c_str());
        jsonStr->Put("maxWidth", std::to_string(constraintSize.maxCrossSize).c_str());
        jsonStr->Put("maxHeight", std::to_string(constraintSize.maxMainSize).c_str());
        return jsonStr->ToString();
    }
    return ret;
}

void WaterFlowComposedElement::AddChildWithSlot(int32_t slot, const RefPtr<Component>& newComponent)
{
    auto waterFlow = GetContentElement<WaterFlowElement>(WaterFlowElement::TypeId());
    if (!waterFlow) {
        LOGE("get WaterFlowElement failed");
        return;
    }
    waterFlow->UpdateChildWithSlot(nullptr, newComponent, slot, slot);
    waterFlow->MarkDirty();
}

void WaterFlowComposedElement::UpdateChildWithSlot(int32_t slot, const RefPtr<Component>& newComponent)
{
    auto waterFlow = GetContentElement<WaterFlowElement>(WaterFlowElement::TypeId());
    if (!waterFlow) {
        LOGE("get WaterFlowElement failed");
        return;
    }
    auto child = waterFlow->GetChildBySlot(slot);
    if (!child) {
        LOGE("waterFlowElement get GetChildBySlot failed");
        return;
    }
    waterFlow->UpdateChildWithSlot(child, newComponent, slot, slot);
    waterFlow->MarkDirty();
}

void WaterFlowComposedElement::DeleteChildWithSlot(int32_t slot)
{
    auto waterFlow = GetContentElement<WaterFlowElement>(WaterFlowElement::TypeId());
    if (!waterFlow) {
        LOGE("get WaterFlowElement failed");
        return;
    }
    auto child = waterFlow->GetChildBySlot(slot);
    if (!child) {
        LOGE("waterFlowElement get GetChildBySlot failed");
        return;
    }
    waterFlow->UpdateChildWithSlot(child, nullptr, slot, slot);
    waterFlow->MarkDirty();
}

} // namespace OHOS::Ace::V2