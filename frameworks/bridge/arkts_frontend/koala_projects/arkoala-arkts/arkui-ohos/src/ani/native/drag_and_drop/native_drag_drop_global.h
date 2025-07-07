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

#ifndef KOALA_PROJECTS_ARKOALA_ARKTS_ARKUI_OHOS_ANI_DRAG_AND_DROP_NATIVE_DRAG_DROP_GLOBAL
#define KOALA_PROJECTS_ARKOALA_ARKTS_ARKUI_OHOS_ANI_DRAG_AND_DROP_NATIVE_DRAG_DROP_GLOBAL

#include "ani.h"

#include <string>

namespace OHOS::Ace::Ani {
void DragEventSetData([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object,
    [[maybe_unused]] ani_long pointer, [[maybe_unused]] ani_object data);
ani_object DragEventGetData([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object,
    [[maybe_unused]] ani_long pointer);
ani_object DragEventGetSummary([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object,
    [[maybe_unused]] ani_long pointer);
ani_string DragEveStartDataLoading([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object,
    [[maybe_unused]] ani_long pointer, [[maybe_unused]] ani_object dataSyncOptions);
void DragEventSetPixelMap([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object,
    [[maybe_unused]] ani_long pointer, [[maybe_unused]] ani_object pixelMap);
void DragEventSetExtraInfo([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object,
    [[maybe_unused]] ani_long pointer, [[maybe_unused]] ani_string extraInfo);
void DragEventSetCustomNode([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object,
    [[maybe_unused]] ani_long pointer, [[maybe_unused]] ani_long node);
void DragSetAllowDropNull([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object,
    [[maybe_unused]] ani_long pointer);
void DragSetAllowDrop([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object,
    [[maybe_unused]] ani_long pointer, [[maybe_unused]] ani_array_ref array, [[maybe_unused]] ani_int length);
void DragSetDragPreview([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object,
    [[maybe_unused]] ani_long pointer, [[maybe_unused]] ani_object dragInfo);
} // namespace OHOS::Ace::Ani
#endif // KOALA_PROJECTS_ARKOALA_ARKTS_ARKUI_OHOS_ANI_DRAG_AND_DROP_NATIVE_DRAG_DROP_GLOBAL