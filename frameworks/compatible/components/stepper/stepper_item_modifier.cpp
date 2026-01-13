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

#include "compatible/components/stepper/stepper_modifier_api.h"
#include "frameworks/compatible/components/stepper/stepper_item_component.h"
#include "interfaces/inner_api/ace_kit/include/ui/base/ace_type.h"

namespace OHOS::Ace::StepperItemModifier {

RefPtr<Component> CreateStepperItem()
{
    return AceType::MakeRefPtr<StepperItemComponent>(RefPtr<Component>());
}

RefPtr<Component> UpdateStepperItem(const RefPtr<Component>& component)
{
    return AceType::DynamicCast<StepperItemComponent>(component);
}

const ArkUIStepperItemComponentModifier* GetStepperItemComponentModifier()
{
    static const ArkUIStepperItemComponentModifier instance = {
        .createStepperItem = CreateStepperItem,
        .updateStepperItem = UpdateStepperItem,
    };
    return &instance;
}
} // OHOS::Ace::StepperItemModifier