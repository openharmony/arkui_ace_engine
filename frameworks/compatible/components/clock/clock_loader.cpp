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

#include "compatible/components/clock/clock_loader.h"

#include "compatible/components/clock/clock_declaration.h"
#include "compatible/components/clock/dom_clock.h"

#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "bridge/common/dom/dom_configs.h"

namespace OHOS::Ace {

RefPtr<Framework::DOMNode> ClockLoader::CreateDomNode(int32_t nodeId, const std::string& nodeName)
{
    return AceType::MakeRefPtr<Framework::DOMClock>(nodeId, nodeName);
}

void* ClockLoader::CreateModel()
{
    return nullptr;
}

RefPtr<V2::InspectorComposedElement> ClockLoader::CreateInspectorElement(const std::string& id)
{
    return nullptr;
}

RefPtr<Declaration> ClockLoader::CreateDeclaration()
{
    return AceType::MakeRefPtr<ClockDeclaration>();
}

void ClockLoader::UpdateDomConfig(const RefPtr<Framework::DOMNode>& node, void* config)
{
    CHECK_NULL_VOID(config);
    auto domClock = AceType::DynamicCast<Framework::DOMClock>(node);
    if (domClock) {
        domClock->SetClockConfig(*reinterpret_cast<ClockConfig*>(config));
    }
}

} // namespace OHOS::Ace