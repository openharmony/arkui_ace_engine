/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef KOALA_PROJECTS_ARKOALA_ARKTS_ARKUI_OHOS_RESOURCE_MODULE_H
#define KOALA_PROJECTS_ARKOALA_ARKTS_ARKUI_OHOS_RESOURCE_MODULE_H

#include <cstdint>
#include <vector>

#include "ani.h"

namespace OHOS::Ace::Ani {
class ResourceModule final {
public:
    static bool ParseAniColor(ani_env* env, ani_object aniValue, uint32_t& color);
    static bool IsResource(ani_env* env, ani_object obj);
    static void ParseAniResource(ani_env* env, ani_object aniValue, int32_t& resId, int32_t& resType,
        std::string& resBundleName, std::string& resModuleName);
    static bool HandleThemeColorsArg(ani_env* env, ani_array colorsArg, std::vector<uint32_t>& colors);
};
} // namespace OHOS::Ace::Ani

#endif
