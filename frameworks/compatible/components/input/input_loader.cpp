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

#include "compatible/components/input/input_loader.h"

#include "base/memory/ace_type.h"
#include "compatible/components/input/dom_input.h"
#include "compatible/components/input/textinput_composed_element.h"
#include "compatible/components/text_field/text_field_model_impl.h"
#include "frameworks/core/components/common/properties/input_option.h"

namespace OHOS::Ace {

RefPtr<Framework::DOMNode> InputLoader::CreateDomNode(int32_t nodeId, const std::string& nodeName)
{
    return AceType::MakeRefPtr<Framework::DOMInput>(nodeId, nodeName);
}

void* InputLoader::CreateModel()
{
    return new Framework::TextFieldModelImpl();
}

RefPtr<V2::InspectorComposedElement> InputLoader::CreateInspectorElement(const std::string& id)
{
    return AceType::MakeRefPtr<V2::TextInputComposedElement>(id);
}

void InputLoader::UpdateDomConfig(const RefPtr<Framework::DOMNode>& node, void* config)
{
    CHECK_NULL_VOID(config);
    auto domInput = AceType::DynamicCast<Framework::DOMInput>(node);
    if (domInput) {
        domInput->SetInputOptions(*reinterpret_cast<std::vector<InputOption>*>(config));
    }
}
} // namespace OHOS::Ace