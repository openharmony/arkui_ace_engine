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
#include "core/components_ng/property/border_property.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_ng/property/measure_property.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT ViewAbstract {
public:
    static void SetWidth(const CalcLength& width);
    static void SetHeight(const CalcLength& height);
    static void SetBackgroundColor(const Color& color);
    static void SetPadding(const CalcLength& value);
    static void SetPadding(const PaddingProperty& value);
    static void SetLayoutWeight(int32_t value);
    static void SetBorderRadius(const BorderRadiusProperty& value);
    static void SetBorderRadius(const Dimension& value);

    // event
    static void SetOnClick(GestureEventFunc&& clickEventFunc);
    static void SetOnTouch(TouchEventFunc&& touchEventFunc);

    static void Pop();
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_VIEW_ABSTRACT_H
