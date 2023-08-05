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

#ifndef FOUNDATION_ACE_ADAPTER_PREVIEW_EXTERNAL_MULTIMODALINPUT_COMMON_TYPE_H
#define FOUNDATION_ACE_ADAPTER_PREVIEW_EXTERNAL_MULTIMODALINPUT_COMMON_TYPE_H

#include <chrono>

namespace OHOS {
namespace MMI {

enum class SourceType : int32_t {
    NONE = 0,
    MOUSE = 1,
    TOUCH = 2,
    TOUCH_PAD = 3,
    KEYBOARD = 4
};

enum class SourceTool : int32_t {
    UNKNOWN = 0,
    FINGER = 1,
    PEN = 2,
    RUBBER = 3,
    BRUSH = 4,
    PENCIL = 5,
    AIRBRUSH = 6,
    MOUSE = 7,
    LENS = 8,
};

using TimeStamp = std::chrono::high_resolution_clock::time_point;

} // namespace MMI
} // namespace OHOS
#endif // FOUNDATION_ACE_ADAPTER_PREVIEW_EXTERNAL_MULTIMODALINPUT_COMMON_TYPE_H
