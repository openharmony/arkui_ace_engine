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

#include "core/interfaces/native/ani/ani_theme.h"

#include <cstdint>

#include "ani.h"

#include "base/log/log_wrapper.h"
#include "bridge/arkts_frontend/arkts_ani_utils.h"
#include "core/interfaces/native/ani/resource_ani_modifier.h"

namespace OHOS::Ace::NG {
std::map<int32_t, AniTheme> AniThemeScope::aniThemes = {};

void AniThemeColors::SetColors(ani_env* env, ani_array colors)
{
    ani_size length;
    env->Array_GetLength(colors, &length);
    for (int i = 0; i < length; i++) {
        // type ResourceColor = number | string | Resource
        ani_ref value;
        env->Array_Get_Ref((ani_array_ref)colors, i, &value);
        colors_.push_back((ani_object)value);
    }
    env->GetVM(&vm_);
}

Color AniThemeColors::ConvertAniValueToColor(ani_object aniValue) const
{
    if (!vm_) {
        LOGW("Invalid vm when ConvertAniValueToColor");
        return Color();
    }
    auto* env = ArktsAniUtils::GetAniEnv(vm_);
    if (!env) {
        LOGW("Invalid env when ConvertAniValueToColor");
        return Color();
    }
    Color color;
    ResourceAniModifier::ParseAniColor(env, aniValue, color);
    return color;
}
} // namespace OHOS::Ace::NG
