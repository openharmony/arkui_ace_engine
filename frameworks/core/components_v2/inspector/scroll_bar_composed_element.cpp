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

#include "core/components_v2/inspector/scroll_bar_composed_element.h"

#include "base/log/dump_log.h"

namespace OHOS::Ace::V2 {
namespace {

const std::unordered_map<std::string, std::function<std::string(const ScrollBarComposedElement&)>> CREATE_JSON_MAP {
    { "direction", [](const ScrollBarComposedElement& inspector) { return inspector.GetScrollBarDirection(); } },
    { "state", [](const ScrollBarComposedElement& inspector) { return inspector.GetBarState(); } }
};

} // namespace

void ScrollBarComposedElement::Dump()
{
    InspectorComposedElement::Dump();
    DumpLog::GetInstance().AddDesc(std::string("direction: ").append(GetScrollBarDirection()));
    DumpLog::GetInstance().AddDesc(std::string("state: ").append(GetBarState()));
}

std::unique_ptr<JsonValue> ScrollBarComposedElement::ToJsonObject() const
{
    auto resultJson = InspectorComposedElement::ToJsonObject();
    for (const auto& value : CREATE_JSON_MAP) {
        resultJson->Put(value.first.c_str(), value.second(*this).c_str());
    }
    return resultJson;
}

std::string ScrollBarComposedElement::GetScrollBarDirection() const
{
    auto renderScrollBar = GetRenderScrollBar();
    if (!renderScrollBar) {
        return std::string("ScrollBarDirection.Vertical");
    }
    Axis axisDirection = renderScrollBar->GetAxis();
    switch (axisDirection) {
        case Axis::VERTICAL:
            return std::string("ScrollBarDirection.Vertical");
        case Axis::HORIZONTAL:
            return std::string("ScrollBarDirection.Horizontal");
        default:
            return std::string("ScrollBarDirection.Vertical");
    }
}

std::string ScrollBarComposedElement::GetBarState() const
{
    auto renderScrollBar = GetRenderScrollBar();
    if (!renderScrollBar) {
        return std::string("BarState.Auto");
    }
    DisplayMode displayMode = renderScrollBar->GetDisplayMode();
    switch (displayMode) {
        case DisplayMode::OFF:
            return std::string("BarState.Off");
        case DisplayMode::AUTO:
            return std::string("BarState.Auto");
        case DisplayMode::ON:
            return std::string("BarState.On");
        default:
            return std::string("BarState.Auto");
    }
}

RefPtr<RenderScrollBar> ScrollBarComposedElement::GetRenderScrollBar() const
{
    auto node = GetInspectorNode(ScrollBarElement::TypeId());
    if (node) {
        return AceType::DynamicCast<RenderScrollBar>(node);
    }
    return nullptr;
}

} // namespace OHOS::Ace::V2