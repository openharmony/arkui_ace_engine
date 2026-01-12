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

#include "compatible/components/list/list_loader.h"

#include "base/memory/ace_type.h"
#include "compatible/components/list/dom_list.h"
#include "compatible/components/list/list_compatible_modifier.h"
#include "compatible/components/list/list_composed_element.h"
#include "compatible/components/list/list_model_impl.h"

namespace OHOS::Ace {

namespace ListCompatibleModifier {
const ArkUIListCompatibleModifier* GetListCompatibleModifier();
} // ListCompatibleModifier
RefPtr<Framework::DOMNode> ListLoader::CreateDomNode(int32_t nodeId, const std::string& nodeName)
{
    return AceType::MakeRefPtr<Framework::DOMList>(nodeId, nodeName);
}

void* ListLoader::CreateModel()
{
    return new Framework::ListModelImpl();
}

RefPtr<V2::InspectorComposedElement> ListLoader::CreateInspectorElement(const std::string& id)
{
    return AceType::MakeRefPtr<V2::ListComposedElement>(id);
}

const void* ListLoader::GetCustomModifier(const std::string& tag)
{
    return ListCompatibleModifier::GetListCompatibleModifier();
}
} // namespace OHOS::Ace