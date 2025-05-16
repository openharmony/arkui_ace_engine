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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SAVE_BUTTON_SAVE_COMMON_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SAVE_BUTTON_SAVE_COMMON_H

#include <cstdint>
#include "base/geometry/dimension.h"
#include "core/components_ng/pattern/security_component/security_component_common.h"

namespace OHOS::Ace {
enum class SaveButtonIconStyle : int32_t {
    ICON_NULL = -1,
    ICON_FULL_FILLED = 0,
    ICON_LINE = 1,
    ICON_PICTURE = 2
};

enum class SaveButtonSaveDescription : int32_t {
    TEXT_NULL = -1,
    DOWNLOAD = 0,
    DOWNLOAD_FILE,
    SAVE,
    SAVE_IMAGE,
    SAVE_FILE,
    DOWNLOAD_AND_SHARE,
    RECEIVE,
    CONTINUE_TO_RECEIVE,
    SAVE_TO_GALLERY,
    EXPORT_TO_GALLERY,
    QUICK_SAVE_TO_GALLERY,
    RESAVE_TO_GALLERY,
    SAVE_ALL,
    MAX_LABEL_TYPE
};

enum class TipPosition : int32_t {
    ABOVE_BOTTOM = 0,
    BELOW_TOP = 1
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SAVE_BUTTON_SAVE_COMMON_H
