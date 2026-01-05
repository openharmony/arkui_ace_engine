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

#include "compatible/components/label/label_loader.h"

#include "compatible/components/label/modifier/label_modifier.h"

namespace OHOS::Ace {

RefPtr<Framework::DOMNode> LabelLoader::CreateDomNode(int32_t nodeId, const std::string& nodeName)
{
    return AceType::MakeRefPtr<Framework::DOMLabel>(nodeId, nodeName);
}

void* LabelLoader::CreateModel()
{
    return nullptr;
}

RefPtr<V2::InspectorComposedElement> LabelLoader::CreateInspectorElement(const std::string& id)
{
    return nullptr;
}

RefPtr<Declaration> LabelLoader::CreateDeclaration()
{
    return AceType::MakeRefPtr<TextDeclaration>();
}

const void* LabelLoader::GetCustomModifier(const std::string& tag)
{
    return LabelModifier::GetLabelModifierCompatible();
}

} // namespace OHOS::Ace