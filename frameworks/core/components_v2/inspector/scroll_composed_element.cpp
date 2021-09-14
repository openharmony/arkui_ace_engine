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

#include "core/components_v2/inspector/scroll_composed_element.h"

#include <unordered_map>

#include "base/log/dump_log.h"
#include "core/components/common/layout/constants.h"
#include "core/components/scroll/render_single_child_scroll.h"
#include "core/components/scroll/scroll_element.h"
#include "core/components_v2/inspector/utils.h"

namespace OHOS::Ace::V2 {
namespace {

const std::unordered_map<std::string, std::function<std::string(const ScrollComposedElement&)>> CREATE_JSON_MAP {
    { "AxisDirection", [](const ScrollComposedElement& inspector) { return inspector.GetAxisDirection(); } }
};

} // namespace

void ScrollComposedElement::Dump()
{
    InspectorComposedElement::Dump();
    DumpLog::GetInstance().AddDesc(std::string("axisDirection: ").append(GetAxisDirection()));
}

std::unique_ptr<JsonValue> ScrollComposedElement::ToJsonObject() const
{
    auto resultJson = InspectorComposedElement::ToJsonObject();
    for (const auto& value : CREATE_JSON_MAP) {
        resultJson->Put(value.first.c_str(), value.second(*this).c_str());
    }
    return resultJson;
}

std::string ScrollComposedElement::GetAxisDirection() const
{
    auto renderSingleChildScroll = GetRenderSingleChildScroll();
    Axis axisDirection = renderSingleChildScroll->GetAxis();
    switch (axisDirection) {
        case Axis::VERTICAL:
            return std::string("VERTICAL");
        case Axis::HORIZONTAL:
            return std::string("HORIZONTAL");
        case Axis::FREE:
            return std::string("FREE");
        case Axis::NONE:
            return std::string("NONE");
        default:
            return std::string("");
    }
}

RefPtr<RenderSingleChildScroll> ScrollComposedElement::GetRenderSingleChildScroll() const
{
    auto node = GetInspectorNode(ScrollElement::TypeId());
    if (node) {
        return AceType::DynamicCast<RenderSingleChildScroll>(node);
    }
    return nullptr;
}

} // namespace OHOS::Ace::V2