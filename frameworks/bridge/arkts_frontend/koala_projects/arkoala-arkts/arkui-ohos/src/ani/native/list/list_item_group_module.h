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

#ifndef KOALA_PROJECTS_ARKOALA_ARKTS_ARKUI_OHOS_ANI_NATIVE_LIST_ITEM_GROUP_MODULE
#define KOALA_PROJECTS_ARKOALA_ARKTS_ARKUI_OHOS_ANI_NATIVE_LIST_ITEM_GROUP_MODULE

#include "ani.h"
#include "core/interfaces/ani/ani_api.h"

namespace OHOS::Ace::Ani {
void SetListItemGroupHeaderContent(
    ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr, ani_long headerContent);
void SetListItemGroupFooterContent(
    ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr, ani_long footerContent);
void SetListItemGroupHeader(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr, ani_long headerPtr);
void SetListItemGroupFooter(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr, ani_long footerPtr);
void ResetListItemGroupHeader(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr);
void ResetListItemGroupFooter(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr);
void SetListItemGroupSpace(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr, ani_object space);
void SetListItemGroupStyle(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr, ani_int style);
} // namespace OHOS::Ace::Ani

#endif // KOALA_PROJECTS_ARKOALA_ARKTS_ARKUI_OHOS_ANI_NATIVE_LIST_ITEM_GROUP_MODULE
