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

#include "compatible/components/text_field/text_field_loader.h"

#include "base/memory/ace_type.h"
#include "compatible/components/text_field/dom_textarea.h"
#include "compatible/components/text_field/textarea_composed_element.h"
#include "compatible/components/text_field/text_field_model_impl.h"
#include "frameworks/core/components/common/properties/input_option.h"
#include "compatible/components/text_field/modifier/text_field_modifier.h"

namespace OHOS::Ace {


RefPtr<Framework::DOMNode> TextFieldLoader::CreateDomNode(int32_t nodeId, const std::string& nodeName)
{
    return AceType::MakeRefPtr<Framework::DOMTextarea>(nodeId, nodeName);
}

void* TextFieldLoader::CreateModel()
{
    return new Framework::TextFieldModelImpl();
}

RefPtr<V2::InspectorComposedElement> TextFieldLoader::CreateInspectorElement(const std::string& id)
{
    return AceType::MakeRefPtr<V2::TextareaComposedElement>(id);
}

void TextFieldLoader::UpdateDomConfig(const RefPtr<Framework::DOMNode>& node, void* config)
{
    CHECK_NULL_VOID(config);
    auto domArea = AceType::DynamicCast<Framework::DOMTextarea>(node);
    if (domArea) {
        domArea->SetInputOptions(*reinterpret_cast<std::vector<InputOption>*>(config));
    }
}

const void* TextFieldLoader::GetCustomModifier(const std::string& tag)
{
    return TextFieldModifier::GetTextFieldModifier();
}
} // namespace OHOS::Ace