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

#ifndef KOALA_PROJECTS_ARKOALA_ARKTS_ARKUI_OHOS_ANI_NATIVE_NODE_ADAPTER_MODULE
#define KOALA_PROJECTS_ARKOALA_ARKTS_ARKUI_OHOS_ANI_NATIVE_NODE_ADAPTER_MODULE

#include "ani.h"

namespace OHOS::Ace::Ani {
ani_long NodeAdapterConstruct(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_object nodeAdapter);
void NodeAdapterDetachNodeAdapter(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr);
ani_boolean NodeAdapterAttachNodeAdapter(
    ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr, ani_long node);
void NodeAdapterDispose(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr);
void NodeAdapterNotifyItemReloaded(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr);
void NodeAdapterSetTotalNodeCount(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr, ani_double count);
void NodeAdapterNotifyItemChanged(
    ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr, ani_double start, ani_double count);
void NodeAdapterNotifyItemRemoved(
    ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr, ani_double start, ani_double count);
void NodeAdapterNotifyItemInserted(
    ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr, ani_double start, ani_double count);
void NodeAdapterNotifyItemMoved(
    ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr, ani_double from, ani_double to);
ani_array NodeAdapterGetAllItems(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr);
} // namespace OHOS::Ace::Ani

#endif // KOALA_PROJECTS_ARKOALA_ARKTS_ARKUI_OHOS_ANI_NATIVE_NODE_ADAPTER_MODULE
