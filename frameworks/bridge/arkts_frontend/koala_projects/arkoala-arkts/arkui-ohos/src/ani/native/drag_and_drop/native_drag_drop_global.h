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
#include <string>

#include "ani.h"
#include "core/interfaces/ani/ani_api.h"

namespace OHOS::Ace::Ani {
void DragEventSetData([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object,
    [[maybe_unused]] ani_long pointer, [[maybe_unused]] ani_object data);
ani_object DragEventGetData([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object,
    [[maybe_unused]] ani_long pointer);
ani_object DragEventGetSummary([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object,
    [[maybe_unused]] ani_long pointer);
ani_string DragEveStartDataLoading([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object,
    [[maybe_unused]] ani_long pointer, [[maybe_unused]] ani_object dataSyncOptions);
void DragEventEnableInternalDropAnimation([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object,
    [[maybe_unused]] ani_long pointer, [[maybe_unused]] ani_string configuration);
void DragEventSetPixelMap([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object,
    [[maybe_unused]] ani_long pointer, [[maybe_unused]] ani_object pixelMap);
void DragEventSetExtraInfo([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object,
    [[maybe_unused]] ani_long pointer, [[maybe_unused]] ani_string extraInfo);
void DragEventSetCustomNode([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object,
    [[maybe_unused]] ani_long pointer, [[maybe_unused]] ani_long node);
void DragSetAllowDropNull([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object,
    [[maybe_unused]] ani_long pointer);
void DragSetAllowDrop([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object,
    [[maybe_unused]] ani_long pointer, [[maybe_unused]] ani_array array);
void DragSetDragPreview([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object,
    [[maybe_unused]] ani_long pointer, [[maybe_unused]] ani_object dragInfo);
void DragSetDragPreviewOptions([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object,
    [[maybe_unused]] ani_long pointer, [[maybe_unused]] ani_object value, [[maybe_unused]] ani_object options);

//utils
void SetPropertyValueByName(ani_env* env, ani_object obj, std::string name, bool& target);
bool ParsePreviewOptionMode(ani_env* env, ArkUIDragPreviewOption& previewOptions,
    ani_object dragPreviewMode, bool& isAuto);
bool ParseDragPreviewMode(ani_env* env, ArkUIDragPreviewOption& previewOptions, ani_object value);
bool ParseDragPreviewModifier(ani_env* env, ArkUIDragPreviewOption& previewOptions, ani_object value);
bool ParseNumberBadge(ani_env* env, ArkUIDragPreviewOption& previewOptions, ani_object value);
bool ParseSizeChangeEffect(ani_env* env, ArkUIDragPreviewOption& previewOptions, ani_object value);
void ParseDragPreviewOptions(ani_env* env, ArkUIDragPreviewOption& previewOptions, ani_object value);
void ParseDragInteractionOptions(ani_env* env, ArkUIDragPreviewOption& previewOptions,
    ani_object options);

// extractors
ani_long ExtractorFromUnifiedDataToPtr(ani_env* env, [[maybe_unused]] ani_object object, ani_object data);
ani_object ExtractorFromPtrToUnifiedData(ani_env* env, [[maybe_unused]] ani_object object, ani_long pointer);
std::string GetAniStringEnum(ani_env* env, ani_array array, ani_int index, bool& isSuccess);
} // namespace OHOS::Ace::Ani
#endif // KOALA_PROJECTS_ARKOALA_ARKTS_ARKUI_OHOS_ANI_DRAG_AND_DROP_NATIVE_DRAG_DROP_GLOBAL