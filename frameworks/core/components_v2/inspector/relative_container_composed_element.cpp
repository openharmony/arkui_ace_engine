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

#include "core/components_v2/inspector/relative_container_composed_element.h"

#include "base/log/dump_log.h"

namespace OHOS::Ace::V2 {
namespace {

const std::unordered_map<std::string, std::function<std::string(const RelativeContainerComposedElement&)>>
    CREATE_JSON_MAP { { "alignRulesMap",
        [](const RelativeContainerComposedElement& inspector) { return inspector.GetAlignRulesMap(); } } };

} // namespace

void RelativeContainerComposedElement::Dump()
{
    InspectorComposedElement::Dump();
    DumpLog::GetInstance().AddDesc(std::string("alignRulesMap: ").append(GetAlignRulesMap()));
}

std::unique_ptr<JsonValue> RelativeContainerComposedElement::ToJsonObject() const
{
    auto resultJson = InspectorComposedElement::ToJsonObject();
    for (const auto& value : CREATE_JSON_MAP) {
        resultJson->Put(value.first.c_str(), value.second(*this).c_str());
    }
    return resultJson;
}

std::string RelativeContainerComposedElement::GetAlignRulesMap() const
{
    std::string result;
    auto renderRelativeContainer = GetRenderRelativeContainer();
    auto alignRulesMap = renderRelativeContainer->GetAlignRulesMap();
    for (auto& firstIter : alignRulesMap) {
        result.append(firstIter.first + ": ");
        auto curAlignRules = firstIter.second;
        for (auto& curAlignRule : curAlignRules) {
            auto alignDirection = curAlignRule.first;
            auto alignRule = curAlignRule.second;
            result.append(GetAlignDirectionStr(alignDirection) + ": {");
            result.append(GetAlignRuleStr(alignRule));
        }
    }
    return result;
}

RefPtr<RenderRelativeContainer> RelativeContainerComposedElement::GetRenderRelativeContainer() const
{
    auto node = GetInspectorNode(RelativeContainerElement::TypeId());
    if (node) {
        return AceType::DynamicCast<RenderRelativeContainer>(node);
    }
    return nullptr;
}

std::string RelativeContainerComposedElement::GetAlignDirectionStr(AlignDirection alignDirection) const
{
    switch (alignDirection) {
        case AlignDirection::LEFT:
            return "left";
        case AlignDirection::MIDDLE:
            return "middle";
        case AlignDirection::RIGHT:
            return "right";
        case AlignDirection::TOP:
            return "top";
        case AlignDirection::CENTER:
            return "center";
        case AlignDirection::BOTTOM:
            return "bottom";
        default:
            return "";
    }
}

std::string RelativeContainerComposedElement::GetAlignRuleStr(AlignRule alignRule) const
{
    std::string result;
    alignRule.anchor = alignRule.anchor == "__container__" ? "" : alignRule.anchor;
    result = "anchor: " + alignRule.anchor + ", align: ";
    if (alignRule.horizontal == HorizontalAlign::START) {
        result += "HorizontalAlign::START }";
    } else if (alignRule.horizontal == HorizontalAlign::CENTER) {
        result += "HorizontalAlign::CENTER }";
    } else if (alignRule.horizontal == HorizontalAlign::END) {
        result += "HorizontalAlign::END }";
    } else if (alignRule.vertical == VerticalAlign::TOP) {
        result += "VerticalAlign::TOP }";
    } else if (alignRule.vertical == VerticalAlign::CENTER) {
        result += "VerticalAlign::CENTER }";
    } else if (alignRule.vertical == VerticalAlign::BOTTOM) {
        result += "VerticalAlign::BOTTOM }";
    } else {
        result = "";
    }
    return result;
}

} // namespace OHOS::Ace::V2