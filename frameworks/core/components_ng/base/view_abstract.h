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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_VIEW_ABSTRACT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_VIEW_ABSTRACT_H

#include <cstdint>

#include "base/memory/referenced.h"
#include "core/common/container.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_ng/property/measure_property.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT ViewAbstract {
public:
    static void Width(const CalcLength& width);
    static void Height(const CalcLength& height);
    static void BackgroundColor(const Color& color);
    static void Padding(const CalcLength& value);
    static void Padding(const PaddingProperty& value);
    static void LayoutWeight(int32_t value);

    static void Pop();
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_VIEW_ABSTRACT_H
