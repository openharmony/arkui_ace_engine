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

#include "compatible/components/search/search_loader.h"

#include "base/memory/ace_type.h"
#include "compatible/components/search/dom_search.h"
#include "compatible/components/search/search_composed_element.h"
#include "compatible/components/search/search_model_impl.h"

namespace OHOS::Ace {

RefPtr<Framework::DOMNode> SearchLoader::CreateDomNode(int32_t nodeId, const std::string& nodeName)
{
    return AceType::MakeRefPtr<Framework::DOMSearch>(nodeId, nodeName);
}

void* SearchLoader::CreateModel()
{
    return new Framework::SearchModelImpl();
}

RefPtr<V2::InspectorComposedElement> SearchLoader::CreateInspectorElement(const std::string& id)
{
    return AceType::MakeRefPtr<V2::SearchComposedElement>(id);
}
RefPtr<Declaration> SearchLoader::CreateDeclaration()
{
    return AceType::MakeRefPtr<SearchDeclaration>();
}

} // namespace OHOS::Ace