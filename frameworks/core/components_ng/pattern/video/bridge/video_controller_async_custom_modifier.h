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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_VIDEO_BRIDGE_VIDEO_CONTROLLER_ASYNC_CUSTOM_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_VIDEO_BRIDGE_VIDEO_CONTROLLER_ASYNC_CUSTOM_MODIFIER_H

#include <cstdint>

namespace OHOS::Ace {

struct ArkUIVideoControllerAsyncModifier {
    void* (*create)();
    void (*start)(void* controller, void* asyncCallback);
    void (*pause)(void* controller, void* asyncCallback);
    void (*stop)(void* controller, void* asyncCallback);
    void (*reset)(void* controller, void* asyncCallback);
    void (*seekTo)(void* controller, float time, int32_t seekMode);
    void (*requestFullscreen)(void* controller, bool landscape);
    void (*exitFullscreen)(void* controller);
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_VIDEO_BRIDGE_VIDEO_CONTROLLER_ASYNC_CUSTOM_MODIFIER_H
