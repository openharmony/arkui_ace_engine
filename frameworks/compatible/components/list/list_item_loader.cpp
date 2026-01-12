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

#include "compatible/components/list/list_item_loader.h"

#include "base/memory/ace_type.h"
#include "compatible/components/list/dom_list_item.h"
#include "compatible/components/list/list_item_compatible_modifier.h"
#include "compatible/components/list/list_item_composed_element.h"
#include "compatible/components/list/list_item_model_impl.h"

namespace OHOS::Ace {

namespace ListItemCompatibleModifier {
const ArkUIListItemCompatibleModifier* GetListItemCompatibleModifier();
} // ListItemCompatibleModifier

RefPtr<Framework::DOMNode> ListItemLoader::CreateDomNode(int32_t nodeId, const std::string& nodeName)
{
    return nullptr;
}
RefPtr<Framework::DOMNode> ListItemLoader::CreateDomNodeWithItemIndex(
    int32_t nodeId, const std::string& nodeName, int32_t itemIndex)
{
    return AceType::MakeRefPtr<Framework::DOMListItem>(nodeId, nodeName, itemIndex);
}

void* ListItemLoader::CreateModel()
{
    return new Framework::ListItemModelImpl();
}

RefPtr<V2::InspectorComposedElement> ListItemLoader::CreateInspectorElement(const std::string& id)
{
    return AceType::MakeRefPtr<V2::ListItemComposedElement>(id);
}

const void* ListItemLoader::GetCustomModifier(const std::string& tag)
{
    return ListItemCompatibleModifier::GetListItemCompatibleModifier();
}
} // namespace OHOS::Ace