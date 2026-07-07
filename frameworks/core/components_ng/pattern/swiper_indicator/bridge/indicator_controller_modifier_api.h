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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWIPER_INDICATOR_BRIDGE_INDICATOR_CONTROLLER_MODIFIER_API_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWIPER_INDICATOR_BRIDGE_INDICATOR_CONTROLLER_MODIFIER_API_H

#include <functional>

#include "base/memory/ace_type.h"

namespace OHOS::Ace::NG {
struct ArkUIIndicatorControllerModifier {
    RefPtr<AceType> (*createControllerHandle)();
    void (*setController)(const RefPtr<AceType>& handle, const RefPtr<AceType>& controller,
        const RefPtr<AceType>& indicatorNode);
    void (*showNext)(const RefPtr<AceType>& handle);
    void (*showPrevious)(const RefPtr<AceType>& handle);
    void (*changeIndex)(const RefPtr<AceType>& handle, int32_t index, bool useAnimation);
    void (*resetSwiperNode)(const RefPtr<AceType>& handle);
    std::function<void()> (*setSwiperNodeBySwiper)(const RefPtr<AceType>& handle, const RefPtr<AceType>& node);
    RefPtr<AceType> (*getControllerBase)(const RefPtr<AceType>& handle);
};

extern const ArkUIIndicatorControllerModifier* GetIndicatorControllerModifier();
} // namespace OHOS::Ace::NG

#endif
