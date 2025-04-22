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

#ifndef FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_UI_PROPERTIES_TABS_EFFECT_NODE_OPTION_H
#define FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_UI_PROPERTIES_TABS_EFFECT_NODE_OPTION_H

#include "ui/base/geometry/dimension.h"

namespace OHOS::Ace {

struct TabsEffectNodeOption {
    Dimension strokeWidth = 0.0_vp;
    bool isNull = false;
    bool operator==(const TabsEffectNodeOption& other) const
    {
        return (strokeWidth == other.strokeWidth) && (isNull == other.isNull);
    }
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_INTERFACES_INNER_API_ACE_KIT_INCLUDE_UI_PROPERTIES_TABS_EFFECT_NODE_OPTION_H
