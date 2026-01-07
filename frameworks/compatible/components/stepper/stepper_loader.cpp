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

#include "compatible/components/stepper/stepper_loader.h"
#include "compatible/components/stepper/stepper_modifier_api.h"

#include "base/memory/ace_type.h"
#include "compatible/components/stepper/dom_stepper.h"
#include "compatible/components/stepper/stepper_composed_element.h"
#include "compatible/components/stepper/stepper_model_impl.h"
#include "frameworks/core/components/common/properties/input_option.h"

namespace OHOS::Ace {
RefPtr<Framework::DOMNode> StepperLoader::CreateDomNode(int32_t nodeId, const std::string& nodeName)
{
    return AceType::MakeRefPtr<Framework::DOMStepper>(nodeId, nodeName);
}

void* StepperLoader::CreateModel()
{
    return nullptr;
}

RefPtr<V2::InspectorComposedElement> StepperLoader::CreateInspectorElement(const std::string& id)
{
    return AceType::MakeRefPtr<V2::StepperComposedElement>(id);
}
} // namespace OHOS::Ace