/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LOADING_PROGRESS_LOADING_PROGRESS_BASE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LOADING_PROGRESS_LOADING_PROGRESS_BASE_H

#include <stdint.h>

namespace OHOS::Ace::NG {
enum class LoadingProgressBase : int32_t {
    BASE16 = 0,
    BASE24 = 1,
    BASE32 = 2,
    BASE40 = 3,
    BASE48 = 4,
    BASE76 = 5
}; // namespace OHOS::Ace::NG
struct CometParam {
    float radius = 0.0f;
    float alphaScale = 1.0f;
    float sizeScale = 1.0f;
    uint32_t pointCount = 0;
};
struct RingParam {
    float radius = 1.0f;
    float strokeWidth = 1.0f;
    float movement = 0.0f;
    float darkRingRadius = 0.0f;
    float darkBackgroundWidth = 1.0f;
    float darkBackgroundRadius = 1.0f;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LOADING_PROGRESS_LOADING_PROGRESS_BASE_H
