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
ani_object GetHostContext([[maybe_unused]] ani_env* env);
ani_object GetSharedLocalStorage([[maybe_unused]] ani_env* env);
void SyncInstanceId(ani_env* env, ani_object obj, ani_int id);
void RestoreInstanceId(ani_env* env);
ani_int GetCurrentInstanceId(ani_env* env);
ani_int GetFocusedInstanceId(ani_env* env);
void SetDrawCallback(ani_env* env, ani_object obj, ani_long ptr, ani_fn_object fnObj);
void SetDrawModifier(
    ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr, ani_int flag, ani_object drawModifier);
void Invalidate(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr);
ani_long BuilderProxyNodeConstruct(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_int id);
void RemoveComponentFromFrameNode(ani_env* env, ani_object obj, ani_long node, ani_long content);
void AddComponentToFrameNode(ani_env* env, ani_object obj, ani_long node, ani_long content);
void SetBackgroundImagePixelMap([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object aniClass, ani_object node,
    ani_object pixelMap, ani_int repeat);
void SetCustomCallback(ani_env* env, ani_object obj, ani_long ptr,
    ani_fn_object fnObjMeasure, ani_fn_object fnObjLayout);
ani_int RequireArkoalaNodeId(ani_env* env, ani_object obj, ani_int capacity);
ani_int CheckIsUIThread(ani_env* env, ani_object obj, ani_int id);
ani_int IsDebugMode(ani_env* env, ani_object obj, ani_int id);
void OnMeasureInnerMeasure(ani_env* env, ani_object obj, ani_long ptr);
void OnLayoutInnerLayout(ani_env* env, ani_object obj, ani_long ptr);
void FrameNodeMarkDirtyNode(ani_env* env, ani_object obj, ani_long ptr);
void SetOverlayComponentContent(ani_env* env, ani_object obj, ani_long ptr, ani_long buildNodePtr, ani_object options);
void SetParallelScoped(ani_env* env, ani_object obj, ani_boolean parallel);
void SetCustomPropertyCallBack(
    ani_env* env, ani_object aniClass, ani_long node, ani_fn_object removeCallback, ani_fn_object getCallback);
ani_string GetCustomProperty(ani_env* env, ani_object aniClass, ani_long node, ani_string aniKey);
} // namespace OHOS::Ace::Ani

#endif // KOALA_PROJECTS_ARKOALA_ARKTS_ARKUI_OHOS_ANI_NATIVE_COMMON_MODULE
