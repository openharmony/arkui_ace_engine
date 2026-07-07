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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWIPER_BRIDGE_SWIPER_CONTROLLER_MODIFIER_API_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SWIPER_BRIDGE_SWIPER_CONTROLLER_MODIFIER_API_H

#include <cstdint>
#include <functional>
#include <string>

#include "base/memory/ace_type.h"

namespace OHOS::Ace::NG::NodeModifier {
struct ArkUICustomSwiperControllerModifier {
    void (*swipeTo)(const RefPtr<AceType>& controller, int32_t index);
    void (*showNext)(const RefPtr<AceType>& controller);
    void (*showPrevious)(const RefPtr<AceType>& controller);
    void (*changeIndex)(const RefPtr<AceType>& controller, int32_t index, bool useAnimation);
    void (*changeIndexWithMode)(const RefPtr<AceType>& controller, int32_t index, int32_t animationMode);
    void (*setFinishCallback)(const RefPtr<AceType>& controller, const std::function<void()>& callback);
    void (*finishAnimation)(const RefPtr<AceType>& controller);
    void (*preloadItems)(const RefPtr<AceType>& controller, const int32_t* indices, int32_t count);
    void (*setPreloadFinishCallback)(
        const RefPtr<AceType>& controller, const std::function<void(int32_t, std::string)>& callback);
    bool (*startFakeDrag)(const RefPtr<AceType>& controller);
    bool (*fakeDragBy)(const RefPtr<AceType>& controller, float offset);
    bool (*stopFakeDrag)(const RefPtr<AceType>& controller);
    bool (*isFakeDragging)(const RefPtr<AceType>& controller);
};

extern const ArkUICustomSwiperControllerModifier* GetCustomSwiperControllerModifier();
} // namespace OHOS::Ace::NG

#endif
