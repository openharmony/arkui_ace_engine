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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWIPER_BRIDGE_SWIPER_TRANSITION_PROXY_MODIFIER_API_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWIPER_BRIDGE_SWIPER_TRANSITION_PROXY_MODIFIER_API_H

#include <cstdint>

#include "base/memory/ace_type.h"

namespace OHOS::Ace::NG::NodeModifier {
struct ArkUISwiperContentTransitionModifier {
    int32_t (*getSelectedIndex)(const RefPtr<AceType>& proxy);
    int32_t (*getIndex)(const RefPtr<AceType>& proxy);
    float (*getPosition)(const RefPtr<AceType>& proxy);
    float (*getMainAxisLength)(const RefPtr<AceType>& proxy);
    void (*finishTransition)(const RefPtr<AceType>& proxy);
};

extern const ArkUISwiperContentTransitionModifier* GetSwiperTransitionProxyModifier();
} // namespace OHOS::Ace

#endif
