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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_ROSEN_ROSEN_CONVERT_HELPER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_ROSEN_ROSEN_CONVERT_HELPER_H

#include "core/common/rosen/rosen_enums.h"
#include "core/components/common/properties/blur_parameter.h"
#include "core/components/common/properties/decoration.h"

namespace OHOS::Ace {
MATERIAL_BLUR_STYLE GetRosenBlurStyleValue(const BlurStyleOption& option);
std::optional<BlurParameter> GetBlurParameter(BlurStyle style, ThemeColorMode colorMode);
} // namespace OHOS::Ace
#endif  // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_ROSEN_ROSEN_CONVERT_HELPER_H
