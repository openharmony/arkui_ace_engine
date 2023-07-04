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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SECURITY_COMPONENT_COMMON_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SECURITY_COMPONENT_COMMON_H

#include <cstdint>
#include "base/geometry/dimension.h"
#include "core/components/common/layout/constants.h"

namespace OHOS::Ace {
enum class SecurityComponentHandleResult : int32_t {
    CLICK_SUCCESS = 0,
    CLICK_GRANT_FAILED = 1,
};

enum class SecurityComponentIconStyle : int32_t {
    ICON_NULL = -1,
};

enum class SecurityComponentDescription : int32_t {
    TEXT_NULL = -1,
};

enum class SecurityComponentBackgroundType : int32_t {
    BACKGROUND_NULL = -1,
    CAPSULE = 0,
    CIRCLE = 1,
    NORMAL = 2
};

enum class SecurityComponentLayoutDirection : int32_t {
    HORIZONTAL = 0,
    VERTICAL = 1,
};

enum class SecSecurityComponentLayoutOrder : int32_t {
    ICON_FIRST = 0,
    TEXT_FIRST = 1,
};

static int32_t BUTTON_TYPE_NULL = -1;
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SECURITY_COMPONENT_COMMON_H
