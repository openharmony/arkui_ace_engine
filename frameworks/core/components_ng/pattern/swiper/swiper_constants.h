/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_COMPATIBLE_COMPONENTS_SWIPER_ENUM_H
#define FOUNDATION_ACE_FRAMEWORKS_COMPATIBLE_COMPONENTS_SWIPER_ENUM_H

namespace OHOS::Ace {
enum class SwiperDisplayMode {
    STRETCH = 0,
    AUTO_LINEAR,
};

enum class SwiperIndicatorType {
    DOT = 0,
    DIGIT,
    ARC_DOT,
};

enum class SwiperArcDirection {
    THREE_CLOCK_DIRECTION = 0,
    SIX_CLOCK_DIRECTION,
    NINE_CLOCK_DIRECTION,
};
}
#endif // FOUNDATION_ACE_FRAMEWORKS_COMPATIBLE_COMPONENTS_SWIPER_ENUM_H