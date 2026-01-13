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

#include "compatible/components/stepper/stepper_item_loader.h"

#include <cstdint>

#include "compatible/components/stepper/dom_stepper.h"
#include "compatible/components/stepper/stepper_modifier_api.h"
#include "compatible/components/stepper/dom_stepper_item.h"
#include "compatible/components/stepper/stepper_item_composed_element.h"
#include "compatible/components/stepper/stepper_item_model_impl.h"
#include "compatible/components/stepper/stepper_item_modifier.h"

#include "base/memory/ace_type.h"
#include "frameworks/core/components/common/properties/input_option.h"

namespace OHOS::Ace {

namespace StepperItemModifier {
const ArkUIStepperItemComponentModifier* GetStepperItemComponentModifier();
}

RefPtr<Framework::DOMNode> StepperItemLoader::CreateDomNode(int32_t nodeId, const std::string& nodeName)
{
    return nullptr;
}

RefPtr<Framework::DOMNode> StepperItemLoader::CreateDomNodeWithItemIndex(
    int32_t nodeId, const std::string& nodeName, int32_t itemIndex)
{
    return AceType::MakeRefPtr<Framework::DOMStepperItem>(nodeId, nodeName, itemIndex);
}

void* StepperItemLoader::CreateModel()
{
    return nullptr;
}

RefPtr<V2::InspectorComposedElement> StepperItemLoader::CreateInspectorElement(const std::string& id)
{
    return AceType::MakeRefPtr<V2::StepperItemComposedElement>(id);
}

void StepperItemLoader::UpdateDomConfig(const RefPtr<Framework::DOMNode>& node, void* config)
{
    CHECK_NULL_VOID(config);
    auto domStepperItem = AceType::DynamicCast<Framework::DOMStepperItem>(node);
    if (domStepperItem) {
    }
    domStepperItem->SetLabel(*reinterpret_cast<StepperLabels*>(config));
}

const void* StepperItemLoader::GetCustomModifier(const std::string& tag)
{
    return StepperItemModifier::GetStepperItemComponentModifier();
}
} // namespace OHOS::Ace