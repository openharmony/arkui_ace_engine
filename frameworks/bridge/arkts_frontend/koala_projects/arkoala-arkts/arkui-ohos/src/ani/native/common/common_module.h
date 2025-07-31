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
ani_object GetSharedLocalStorage([[maybe_unused]] ani_env* env);
void SyncInstanceId(ani_env* env, ani_object obj, ani_int id);
void RestoreInstanceId(ani_env* env);
ani_int GetCurrentInstanceId(ani_env* env);
ani_int GetFocusedInstanceId(ani_env* env);
void SetDrawCallback(ani_env* env, ani_object obj, ani_long ptr, ani_fn_object fnObj);
void SetDrawModifier(
    ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr, uint32_t flag, ani_object drawModifier);
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
void SetParallelScoped(ani_env* env, ani_object obj, ani_boolean parallel);
void SetCustomPropertyCallBack(
    ani_env* env, ani_object aniClass, ani_long node, ani_fn_object removeCallback, ani_fn_object getCallback);
ani_string GetCustomProperty(ani_env* env, ani_object aniClass, ani_long node, ani_string aniKey);
void SetOverlayComponentContent(ani_env* env, ani_object obj, ani_long ptr, ani_long buildNodePtr, ani_object options);
ani_double Vp2px(ani_env* env, ani_object obj, ani_double value, ani_int instanceId);
ani_double Px2vp(ani_env* env, ani_object obj, ani_double value, ani_int instanceId);
ani_double Fp2px(ani_env* env, ani_object obj, ani_double value, ani_int instanceId);
ani_double Px2fp(ani_env* env, ani_object obj, ani_double value, ani_int instanceId);
ani_double Lpx2px(ani_env* env, ani_object obj, ani_double value, ani_int instanceId);
ani_double Px2lpx(ani_env* env, ani_object obj, ani_double value, ani_int instanceId);
void* TransferKeyEventPointer(ani_env* env, ani_object obj, ani_long pointer);
void* CreateKeyEventAccessorWithPointer(ani_env* env, [[maybe_unused]] ani_object obj, ani_long pointer);
void* CreateEventTargetInfoAccessor(ani_env* env, [[maybe_unused]] ani_object obj);
void EventTargetInfoAccessorWithId(ani_env* env, [[maybe_unused]] ani_object obj, ani_long input, ani_string id);
void* CreateScrollableTargetInfoAccessor(ani_env* env, [[maybe_unused]] ani_object obj);
void ScrollableTargetInfoAccessorWithId(ani_env* env, [[maybe_unused]] ani_object obj, ani_long input, ani_string id);
void ScrollableTargetInfoAccessorWithPointer(
    ani_env* env, [[maybe_unused]] ani_object obj, ani_long input, ani_long pointer);
void* TransferScrollableTargetInfoPointer(ani_env* env, ani_object obj, ani_long pointer);
ani_long CreateDragEventAccessorWithPointer(ani_env* env, ani_object obj, ani_long pointer);
ani_long GetDragEventPointer(ani_env* env, ani_object obj, ani_long pointer);
void* CreateTouchEventAccessorWithPointer(ani_env* env, [[maybe_unused]] ani_object obj, ani_long pointer);
void* CreateMouseEventAccessorWithPointer(ani_env* env, [[maybe_unused]] ani_object obj, ani_long pointer);
void* CreateAxisEventAccessorWithPointer(ani_env* env, [[maybe_unused]] ani_object obj, ani_long pointer);
void* CreateClickEventAccessorWithPointer(ani_env* env, [[maybe_unused]] ani_object obj, ani_long pointer);
void* CreateHoverEventAccessorWithPointer(ani_env* env, [[maybe_unused]] ani_object obj, ani_long pointer);
void* GetTouchEventPointer(ani_env* env, [[maybe_unused]] ani_object obj, ani_long touchEventPeer);
void* GetMouseEventPointer(ani_env* env, [[maybe_unused]] ani_object obj, ani_long mouseEventPeer);
void* GetAxisEventPointer(ani_env* env, [[maybe_unused]] ani_object obj, ani_long axisEventPeer);
void* GetClickEventPointer(ani_env* env, [[maybe_unused]] ani_object obj, ani_long clickEventPeer);
void* GetHoverEventPointer(ani_env* env, [[maybe_unused]] ani_object obj, ani_long hoverEventPeer);
} // namespace OHOS::Ace::Ani

#endif // KOALA_PROJECTS_ARKOALA_ARKTS_ARKUI_OHOS_ANI_NATIVE_COMMON_MODULE
