/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MODIFIERS_LAYOUT_LAYOUT_WEIGHT_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MODIFIERS_LAYOUT_LAYOUT_WEIGHT_MODIFIER_H

#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/modifier/modifier.h"

namespace OHOS::Ace::NG {
class LayoutWeightModifier : public PropertyModifier<float, LayoutProperty> {
public:
    LayoutWeightModifier(float value) : PropertyModifier<float, LayoutProperty>(value)
    {
        ACE_DEFINE_MODIFIER_TASK(LayoutProperty, LayoutProperty, LayoutWeight);
    };
    ~LayoutWeightModifier() override = default;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MODIFIERS_LAYOUT_LAYOUT_WEIGHT_MODIFIER_H