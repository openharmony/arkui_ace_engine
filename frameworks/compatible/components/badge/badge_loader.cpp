/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "compatible/components/badge/badge_loader.h"

#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "bridge/common/dom/dom_configs.h"
#include "compatible/components/badge/badge_composed_element.h"
#include "compatible/components/badge/badge_declaration.h"
#include "compatible/components/badge/badge_model_impl.h"
#include "compatible/components/badge/dom_badge.h"

namespace OHOS::Ace {

RefPtr<Framework::DOMNode> BadgeLoader::CreateDomNode(int32_t nodeId, const std::string& nodeName)
{
    return AceType::MakeRefPtr<Framework::DOMBadge>(nodeId, nodeName);
}

void* BadgeLoader::CreateModel()
{
    return new Framework::BadgeModelImpl();
}

RefPtr<V2::InspectorComposedElement> BadgeLoader::CreateInspectorElement(const std::string& id)
{
    return AceType::MakeRefPtr<V2::BadgeComposedElement>(id);
}

RefPtr<Declaration> BadgeLoader::CreateDeclaration()
{
    return AceType::MakeRefPtr<BadgeDeclaration>();
}

void BadgeLoader::UpdateDomConfig(const RefPtr<Framework::DOMNode>& node, void* config)
{
    CHECK_NULL_VOID(config);
    auto domBadge = AceType::DynamicCast<Framework::DOMBadge>(node);
    if (domBadge) {
        domBadge->SetBadgeConfig(*reinterpret_cast<Framework::BadgeConfig*>(config));
    }
}

} // namespace OHOS::Ace