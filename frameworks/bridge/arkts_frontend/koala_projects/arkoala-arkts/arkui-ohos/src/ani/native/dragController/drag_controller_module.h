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

#ifndef KOALA_PROJECTS_ARKOALA_ARKTS_ARKUI_OHOS_ANI_NATIVE_DRAG_CONTROLLER_MODULE_H
#define KOALA_PROJECTS_ARKOALA_ARKTS_ARKUI_OHOS_ANI_NATIVE_DRAG_CONTROLLER_MODULE_H

#include "ani.h"

namespace OHOS::Ace::Ani {
ani_object ANIExecuteDragWithCallback(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_object custom,
    ani_long builderObj, ani_object destroyCallbackObj, ani_object dragInfo, ani_object callback);
ani_object ANIExecuteDragWithPromise(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_object custom,
    ani_long builderObj, ani_object destroyCallbackObj, ani_object dragInfo);
ani_object ANICreateDragAction([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object aniClass,
    ani_object customArray, ani_object builderArray, ani_object destroyCallbackObj,
    [[maybe_unused]] ani_object dragInfoObj);
ani_object ANIDragActionStartDrag(
    [[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long dragActionPtr);
void ANIDragActionOn([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object aniClass, ani_string type,
    ani_object callback, ani_long dragActionPtr);
void ANIDragActionOff([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object aniClass, ani_string type,
    [[maybe_unused]] ani_object callback, ani_long dragActionPtr);
ani_object ANIGetDragPreview([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object aniClass);
void ANIDragPreviewSetForegroundColor([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object aniClass,
    ani_object color, ani_long dragPreviewPtr);
void ANIDragPreviewAnimate([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object aniClass, ani_object options,
    ani_object handler, ani_long dragPreviewPtr);
void ANIDragActionSetDragEventStrictReportingEnabled(
    [[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object aniClass, bool enable);
void ANIDragActionCancelDataLoading(
    [[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object aniClass, ani_string key);
void ANIDragActionNotifyDragStartReques(
    [[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object aniClass, ani_enum_item requestStatus);
} // namespace OHOS::Ace::Ani

#endif // KOALA_PROJECTS_ARKOALA_ARKTS_ARKUI_OHOS_ANI_NATIVE_DRAG_CONTROLLER_MODULE_H