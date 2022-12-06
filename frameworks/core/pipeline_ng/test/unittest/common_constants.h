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
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_PIPELINE_NG_TEST_UNITTEST_COMMON_CONSTANTS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_PIPELINE_NG_TEST_UNITTEST_COMMON_CONSTANTS_H

#include <cstdint>

namespace OHOS::Ace {
constexpr int32_t DEFAULT_TEST_FLAG = 0;
constexpr int32_t TOUCH_TEST_FLAG = 1;
constexpr int32_t MOUSE_TEST_FLAG = 1 << 1;
constexpr int32_t AXIS_TEST_FLAG = 1 << 2;
constexpr int32_t DISPATCH_TOUCH_EVENT_TOUCH_EVENT_FLAG = 1 << 3;
constexpr int32_t DISPATCH_TOUCH_EVENT_AXIS_EVENT_FLAG = 1 << 4;
constexpr int32_t DISPATCH_MOUSE_EVENT_NG_FLAG = 1 << 5;
constexpr int32_t DISPATCH_MOUSE_HOVER_ANIMATION_NG_FLAG = 1 << 6;
constexpr int32_t DISPATCH_MOUSE_HOVER_EVENT_NG_FLAG = 1 << 7;
constexpr int32_t DISPATCH_AXIS_EVENT_FLAG = 1 << 8;
constexpr int32_t DISPATCH_AXIS_EVENT_NG_FLAG = 1 << 9;
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_PIPELINE_NG_TEST_UNITTEST_COMMON_CONSTANTS_H
