/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "compatible/components/refresh/refresh_loader.h"

#include "base/memory/ace_type.h"
#include "compatible/components/refresh/dom_refresh.h"
#include "compatible/components/refresh/refresh_composed_element.h"
#include "compatible/components/refresh/refresh_model_impl.h"
#include "core/components/refresh/render_refresh_target.h"

namespace OHOS::Ace {

namespace RefreshModifier {
const ArkUIRefreshModifierCompatible* GetRefreshModifier();
} // RefreshModifier
RefPtr<Framework::DOMNode> RefreshLoader::CreateDomNode(int32_t nodeId, const std::string& nodeName)
{
    return AceType::MakeRefPtr<Framework::DOMRefresh>(nodeId, nodeName);
}

void* RefreshLoader::CreateModel()
{
    return new Framework::RefreshModelImpl();
}

RefPtr<V2::InspectorComposedElement> RefreshLoader::CreateInspectorElement(const std::string& id)
{
    return AceType::MakeRefPtr<V2::RefreshComposedElement>(id);
}

const void* RefreshLoader::GetCustomModifier(const std::string& tag)
{
    return RefreshModifier::GetRefreshModifier();
}
} // namespace OHOS::Ace