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

#include "core/components_ng/modifier/layout/size_modifier.h"

#include "base/log/log.h"
#include "core/components_ng/layout/layout_property.h"
#include "core/components_ng/modifier/modifier.h"
#include "core/components_ng/property/calc_length.h"

#define ACE_DEFINE_MODIFY_SIZE_PROP(isWidth)                                                            \
    do {                                                                                                \
        if (!HasValue()) {                                                                              \
            return;                                                                                     \
        }                                                                                               \
        auto task = [length = GetValue()](LayoutProperty* layoutProperty) {                             \
            layoutProperty->UpdateCalcSelfIdealSize(                                                    \
                (isWidth) ? CalcSize(length, CalcLength(-1.0f)) : CalcSize(CalcLength(-1.0f), length)); \
        };                                                                                              \
        SetModifierTask(std::move(task));                                                               \
    } while (false);

namespace OHOS::Ace::NG {

WidthModifier::WidthModifier(const CalcLength& value) : PropertyModifier<CalcLength, LayoutProperty>(value)
{
    ACE_DEFINE_MODIFY_SIZE_PROP(true);
};

HeightModifier::HeightModifier(const CalcLength& value) : PropertyModifier<CalcLength, LayoutProperty>(value)
{
    ACE_DEFINE_MODIFY_SIZE_PROP(false);
};

} // namespace OHOS::Ace::NG