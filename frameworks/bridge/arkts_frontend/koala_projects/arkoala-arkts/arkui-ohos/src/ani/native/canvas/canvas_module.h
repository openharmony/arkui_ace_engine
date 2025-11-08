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

#ifndef KOALA_PROJECTS_ARKOALA_ARKTS_ARKUI_OHOS_ANI_NATIVE_CANVAS_CANVAS_MODULE
#define KOALA_PROJECTS_ARKOALA_ARKTS_ARKUI_OHOS_ANI_NATIVE_CANVAS_CANVAS_MODULE

#include "ani.h"

namespace OHOS::Ace::Ani {
class CanvasModule {
public:
    static void SetPixelMap(
        ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long peerPtr, ani_object pixelMapObj);
    static void DrawPixelMap0(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long peerPtr,
        ani_object pixelMapObj, ani_double dx, ani_double dy);
    static void DrawPixelMap1(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long peerPtr,
        ani_object pixelMapObj, ani_double dx, ani_double dy, ani_double dw, ani_double dh);
    static void DrawPixelMap2(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long peerPtr,
        ani_object pixelMapObj, ani_double sx, ani_double sy, ani_double sw, ani_double sh, ani_double dx,
        ani_double dy, ani_double dw, ani_double dh);
    static ani_long ImageBitmapConstruct0(
        ani_env* env, [[maybe_unused]] ani_object aniClass, ani_string src, ani_int unit);
    static ani_long ImageBitmapConstruct1(
        ani_env* env, [[maybe_unused]] ani_object aniClass, ani_object pixelMapObj, ani_int unit);
    static ani_double GetCanvasDensity(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long peerPtr);
    static ani_double GetSystemDensity(ani_env* env, [[maybe_unused]] ani_object aniClass);
    static ani_object GetImageData(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long peerPtr, ani_double sx,
        ani_double sy, ani_double sw, ani_double sh);
    static void PutImageData0(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long peerPtr, ani_object array,
        ani_double dx, ani_double dy, ani_int width, ani_int height);
    static void PutImageData1(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long peerPtr, ani_object array,
        ani_double dx, ani_double dy, ani_int width, ani_int height, ani_double dirtyX, ani_double dirtyY,
        ani_double dirtyWidth, ani_double dirtyHeight);
    static ani_object GetDrawingCanvas(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long peerPtr);
    static ani_int GetCanvasId(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long peerPtr);
    static void SetAttachCallbackId(
        ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long peerPtr, ani_int attachCallbackId);
    static void SetDetachCallbackId(
        ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long peerPtr, ani_int detachCallbackId);
};
} // namespace OHOS::Ace::Ani

#endif // KOALA_PROJECTS_ARKOALA_ARKTS_ARKUI_OHOS_ANI_NATIVE_CANVAS_CANVAS_MODULE
