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

#ifndef KOALA_PROJECTS_ARKOALA_ARKTS_ARKUI_OHOS_ANI_NATIVE_COMMON_MODULE
#define KOALA_PROJECTS_ARKOALA_ARKTS_ARKUI_OHOS_ANI_NATIVE_COMMON_MODULE

#include "ani.h"

namespace OHOS::Ace::Ani {
ani_object GetHostContext([[maybe_unused]] ani_env* env, ani_object obj, ani_int key);
void SyncInstanceId(ani_env* env, ani_object obj, ani_int id);
void RestoreInstanceId(ani_env* env);
void SetDrawCallback(ani_env* env, ani_object obj, ani_long ptr, ani_fn_object fnObj);
void SetDrawModifier(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr, ani_object drawModifier);
void Invalidate(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr);
} // namespace OHOS::Ace::Ani

#endif // KOALA_PROJECTS_ARKOALA_ARKTS_ARKUI_OHOS_ANI_NATIVE_COMMON_MODULE
