/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef KOALA_PROJECTS_ARKOALA_ARKTS_ARKUI_OHOS_ANI_NATIVE_DYNAMICLAYOUT_MODULE
#define KOALA_PROJECTS_ARKOALA_ARKTS_ARKUI_OHOS_ANI_NATIVE_DYNAMICLAYOUT_MODULE

#include "ani.h"

namespace OHOS::Ace::Ani {
ani_long DynamicLayoutConstruct(
    ani_env* env, [[maybe_unused]] ani_object aniClass, ani_int id, ani_int flags);
void SetDynamicLayoutStackLayoutAlgorithm(
    ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr, ani_object stackLayoutAlgorithm);
void SetDynamicLayoutRowLayoutAlgorithm(
    ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr, ani_object rowLayoutAlgorithm);
void SetDynamicLayoutColumnLayoutAlgorithm(
    ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr, ani_object columnLayoutAlgorithm);
void SetDynamicLayoutCustomLayoutAlgorithm(
    ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr, ani_object customLayoutAlgorithm,
    ani_object frameNode);
void SetDynamicLayoutGridLayoutAlgorithm(
    ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr, ani_object gridLayoutAlgorithm);
} // namespace OHOS::Ace::Ani

#endif // KOALA_PROJECTS_ARKOALA_ARKTS_ARKUI_OHOS_ANI_NATIVE_DYNAMICLAYOUT_MODULE
