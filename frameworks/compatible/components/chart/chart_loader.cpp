/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "compatible/components/chart/chart_loader.h"

#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "bridge/common/dom/dom_configs.h"
#include "compatible/components/chart/dom_chart.h"

#include "compatible/components/chart/chart_modifier_compatible.h"

namespace OHOS::Ace {

namespace ChartModifier {
const ArkUIChartModifierCompatible* GetChartModifier();
}

RefPtr<Framework::DOMNode> ChartLoader::CreateDomNode(int32_t nodeId, const std::string& nodeName)
{
    return AceType::MakeRefPtr<Framework::DOMChart>(nodeId, nodeName);
}

void* ChartLoader::CreateModel()
{
    return nullptr;
}

RefPtr<V2::InspectorComposedElement> ChartLoader::CreateInspectorElement(const std::string& id)
{
    return nullptr;
}

const void* ChartLoader::GetCustomModifier(const std::string& name)
{
    return ChartModifier::GetChartModifier();
}
} // namespace OHOS::Ace