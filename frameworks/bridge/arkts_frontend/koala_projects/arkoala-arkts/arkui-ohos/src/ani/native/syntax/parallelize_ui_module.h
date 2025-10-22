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

#ifndef KOALA_PROJECTS_ARKOALA_ARKTS_ARKUI_OHOS_ANI_NATIVE_PARALLELIZE_UI_MODULE_H
#define KOALA_PROJECTS_ARKOALA_ARKTS_ARKUI_OHOS_ANI_NATIVE_PARALLELIZE_UI_MODULE_H

#include <memory>

#include "ani.h"
#include "common/common_module.h"
#include "load.h"

namespace OHOS::Ace::Ani {

ani_long ParallelizeUIAdapterNodeConstruct(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_int id);

void ParallelizeUIReset(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr);

void ConvertGetCountCallbackFun(
    ani_vm* vm, std::function<int32_t()>& callback, const std::shared_ptr<CommonModuleCallbackAni>& callbackAni);

void ConvertGetFrameNodeCallbackFun(ani_vm* vm, std::function<ArkUINodeHandle(int32_t)>& callback,
    const std::shared_ptr<CommonModuleCallbackAni>& callbackAni);

void ParallelizeUIRegisterCallback(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr,
    ani_fn_object getCountCallback, ani_fn_object getFrameNodeCallback);

} // namespace OHOS::Ace::Ani
#endif // KOALA_PROJECTS_ARKOALA_ARKTS_ARKUI_OHOS_ANI_NATIVE_PARALLELIZE_UI_MODULE_H
