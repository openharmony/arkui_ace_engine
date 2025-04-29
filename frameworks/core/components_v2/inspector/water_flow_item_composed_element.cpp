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

#include "core/components_v2/inspector/water_flow_item_composed_element.h"

namespace OHOS::Ace::V2 {
namespace {

const std::unordered_map<std::string,
std::function<std::string(const WaterFlowItemComposedElement&)>> CREATE_JSON_MAP {
};

} // namespace

void WaterFlowItemComposedElement::Dump()
{
    InspectorComposedElement::Dump();
}

std::unique_ptr<JsonValue> WaterFlowItemComposedElement::ToJsonObject() const
{
    auto resultJson = InspectorComposedElement::ToJsonObject();
    for (const auto& value : CREATE_JSON_MAP) {
        resultJson->Put(value.first.c_str(), value.second(*this).c_str());
    }
    return resultJson;
}

} // namespace OHOS::Ace::V2