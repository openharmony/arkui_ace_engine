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

#include "compatible/components/toolbaritem/tool_bar_item_loader.h"

#include "base/memory/ace_type.h"
#include "compatible/components/toolbaritem/dom_tool_bar_item.h"

namespace OHOS::Ace {

RefPtr<Framework::DOMNode> ToolBarItemLoader::CreateDomNode(int32_t nodeId, const std::string& nodeName)
{
    return AceType::MakeRefPtr<Framework::DOMToolBarItem>(nodeId, nodeName);
}

void* ToolBarItemLoader::CreateModel()
{
    return nullptr;
}

RefPtr<V2::InspectorComposedElement> ToolBarItemLoader::CreateInspectorElement(const std::string& id)
{
    return nullptr;
}
} // namespace OHOS::Ace