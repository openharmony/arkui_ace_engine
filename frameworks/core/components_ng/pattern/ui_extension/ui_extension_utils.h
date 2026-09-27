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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_UI_EXTENSION_UI_EXTENSION_UTILS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_UI_EXTENSION_UI_EXTENSION_UTILS_H

#include <cstdint>

#include "core/components_ng/pattern/ui_extension/ui_extension_config.h"

namespace OHOS::Rosen {

// Defined in window_manager (wm_layout_common.h and previewer wm_type.h) as
// `enum class DpiFollowStrategy : uint32_t { NONE = 0, FOLLOW_HOST_DPI_UEA = 1, FOLLOW_HOST_DPI_ALL = 2 }`.
// Forward declared so that targets without window_manager include paths (e.g. the koala ani
// target) can still include this header; ConvertToRosenDpiFollowStrategy maps by underlying value.
enum class DpiFollowStrategy : uint32_t;
} // namespace OHOS::Rosen

namespace OHOS::Ace::NG {
inline DpiFollowStrategy ParseDpiFollowStrategy(int32_t value)
{
    switch (value) {
        case static_cast<int32_t>(DpiFollowStrategy::FOLLOW_HOST_DPI):
            return DpiFollowStrategy::FOLLOW_HOST_DPI;
        case static_cast<int32_t>(DpiFollowStrategy::FOLLOW_HOST_DPI_ALL):
            return DpiFollowStrategy::FOLLOW_HOST_DPI_ALL;
        case static_cast<int32_t>(DpiFollowStrategy::FOLLOW_UI_EXTENSION_ABILITY_DPI):
        default:
            return DpiFollowStrategy::FOLLOW_UI_EXTENSION_ABILITY_DPI;
    }
}

// Mirrors Rosen::DpiFollowStrategy enumerator values (window_manager wm_layout_common.h):
// NONE = 0, FOLLOW_HOST_DPI_UEA = 1, FOLLOW_HOST_DPI_ALL = 2. The Rosen enum is only
// forward declared, so ConvertToRosenDpiFollowStrategy maps by its underlying values.
constexpr uint32_t ROSEN_NONE = 0;
constexpr uint32_t ROSEN_FOLLOW_HOST_DPI_UEA = 1;
constexpr uint32_t ROSEN_FOLLOW_HOST_DPI_ALL = 2;

inline Rosen::DpiFollowStrategy ConvertToRosenDpiFollowStrategy(DpiFollowStrategy dpiFollowStrategy)
{
    switch (dpiFollowStrategy) {
        case DpiFollowStrategy::FOLLOW_HOST_DPI:
            return static_cast<Rosen::DpiFollowStrategy>(ROSEN_FOLLOW_HOST_DPI_UEA);
        case DpiFollowStrategy::FOLLOW_HOST_DPI_ALL:
            return static_cast<Rosen::DpiFollowStrategy>(ROSEN_FOLLOW_HOST_DPI_ALL);
        case DpiFollowStrategy::FOLLOW_UI_EXTENSION_ABILITY_DPI:
        default:
            return static_cast<Rosen::DpiFollowStrategy>(ROSEN_NONE);
    }
}
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_UI_EXTENSION_UI_EXTENSION_UTILS_H
