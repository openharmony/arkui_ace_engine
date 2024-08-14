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

#include "core/components_v2/inspector/row_composed_element.h"

#include "base/log/dump_log.h"
#include "core/components/flex/render_flex.h"

namespace OHOS::Ace::V2 {
namespace {

const std::unordered_map<std::string, std::function<std::string(const RowComposedElement&)>> CREATE_JSON_MAP {
    { "alignItems", [](const RowComposedElement& inspector) { return inspector.GetAlignItems(); } },
    { "space", [](const RowComposedElement& inspector) { return inspector.GetSpace(); } },
    { "selfAlign", [](const RowComposedElement& inspector) { return inspector.GetVerticalAlign(); } },
    { "justifyContent", [](const RowComposedElement& inspector) { return inspector.GetJustifyContent(); } },
};

}

void RowComposedElement::Dump()
{
    InspectorComposedElement::Dump();
    DumpLog::GetInstance().AddDesc(
        std::string("alignItems: ").append(GetAlignItems()));
    DumpLog::GetInstance().AddDesc(
        std::string("space: ").append(GetSpace()));
}

std::unique_ptr<JsonValue> RowComposedElement::ToJsonObject() const
{
    auto resultJson = InspectorComposedElement::ToJsonObject();
    for (const auto& value : CREATE_JSON_MAP) {
        resultJson->Put(value.first.c_str(), value.second(*this).c_str());
    }
    return resultJson;
}

std::string RowComposedElement::GetAlignItems() const
{
    auto node = GetInspectorNode(RowElement::TypeId());
    if (!node) {
        return "VerticalAlign.Center";
    }
    auto renderRow = AceType::DynamicCast<RenderFlex>(node);
    if (renderRow) {
        auto alignItems = renderRow->GetAlignItems();
        if (alignItems == FlexAlign::FLEX_START) {
            return "VerticalAlign.Top";
        } else if (alignItems == FlexAlign::CENTER) {
            return "VerticalAlign.Center";
        } else if (alignItems == FlexAlign::FLEX_END) {
            return "VerticalAlign.Bottom";
        }
    }
    return "VerticalAlign.Center";
}

std::string RowComposedElement::GetSpace() const
{
    auto node = GetInspectorNode(RowElement::TypeId());
    if (!node) {
        return Dimension(0.0).ToString();
    }
    auto renderRow = AceType::DynamicCast<RenderFlex>(node);
    if (renderRow) {
        auto dimension = renderRow->GetInspectorSpace();
        return dimension.ToString();
    }
    return Dimension(0.0).ToString();
}

std::string RowComposedElement::GetVerticalAlign() const
{
    auto node = GetInspectorNode(RowElement::TypeId());
    if (!node) {
        return "VerticalAlign::Center";
    }
    auto renderRow = AceType::DynamicCast<RenderFlex>(node);
    if (renderRow) {
        auto alignPtr = renderRow->GetAlignPtr();
        if (alignPtr) {
            auto verticalAlign = alignPtr->GetVerticalAlign();
            switch (verticalAlign) {
                case VerticalAlign::TOP:
                    return "VerticalAlign::Top";
                case VerticalAlign::CENTER:
                    return "VerticalAlign::Center";
                case VerticalAlign::BOTTOM:
                    return "VerticalAlign::Bottom";
                default:
                    return "verticalAlign::Center";
            }
        }
    }
    return "verticalAlign::Center";
}

std::string RowComposedElement::GetJustifyContent() const
{
    auto node = GetInspectorNode(RowElement::TypeId());
    if (!node) {
        return "FlexAlign.Start";
    }
    auto renderRow = AceType::DynamicCast<RenderFlex>(node);
    if (!renderRow) {
        return "FlexAlign.Start";
    }
    auto flexAlign = renderRow->GetJustifyContent();
    return ConvertFlexAlignToString(flexAlign);
}

std::string RowComposedElement::ConvertFlexAlignToString(FlexAlign flexAlign) const
{
    std::string result = "";
    switch (flexAlign) {
        case FlexAlign::FLEX_START:
            result = "FlexAlign.Start";
            break;
        case FlexAlign::FLEX_END:
            result = "FlexAlign.End";
            break;
        case FlexAlign::CENTER:
            result = "FlexAlign.Center";
            break;
        case FlexAlign::SPACE_BETWEEN:
            result = "FlexAlign.SpaceBetween";
            break;
        case FlexAlign::SPACE_AROUND:
            result = "FlexAlign.SpaceAround";
            break;
        case FlexAlign::SPACE_EVENLY:
            result = "FlexAlign.SpaceEvenly";
            break;
        default:
            result = "FlexAlign.Start";
            break;
    }
    return result;
}

} // namespace OHOS::Ace::V2