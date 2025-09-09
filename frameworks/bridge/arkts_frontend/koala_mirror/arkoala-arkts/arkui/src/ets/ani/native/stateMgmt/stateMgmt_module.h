/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef KOALA_PROJECTS_ARKOALA_ARKTS_ARKUI_OHOS_ANI_NATIVE_STATEMGMT_MODULE
#define KOALA_PROJECTS_ARKOALA_ARKTS_ARKUI_OHOS_ANI_NATIVE_STATEMGMT_MODULE

#include "ani.h"

namespace OHOS::Ace::Ani {
    // for persistentStorage
    ani_string PersistentStorage_Get(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_string key);
    void PersistentStorage_Set(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_string key, ani_string value);
    ani_boolean PersistentStorage_Has(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_string key);
    void PersistentStorage_Clear(ani_env* env, [[maybe_unused]] ani_object aniClass);
    void PersistentStorage_Delete(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_string key);

    // for environment
    ani_boolean Env_GetAccessibilityEnabled(ani_env* env);
    ani_int Env_GetColorMode(ani_env* env);
    ani_float Env_GetFontScale(ani_env* env);
    ani_float Env_GetFontWeightScale(ani_env* env);
    ani_string Env_GetLayoutDirection(ani_env* env);
    ani_string Env_GetLanguageCode(ani_env* env);
} // namespace OHOS::Ace::Ani

#endif // KOALA_PROJECTS_ARKOALA_ARKTS_ARKUI_OHOS_ANI_NATIVE_STATEMGMT_MODULE
