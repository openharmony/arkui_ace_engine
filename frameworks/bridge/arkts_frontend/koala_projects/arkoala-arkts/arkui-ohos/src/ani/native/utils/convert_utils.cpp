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

#include "convert_utils.h"

#include "canvas_ani/ani_canvas.h"
#include "pixel_map_taihe_ani.h"

#include "base/log/log_wrapper.h"
#include "base/utils/utils.h"

namespace OHOS::Ace::Ani {
ani_long ConvertFromPixelMapAni(ani_env* env, [[maybe_unused]]ani_object aniClass, ani_object pixelMapObj)
{
    auto mediaPixelMap = Media::PixelMapTaiheAni::GetNativePixelMap(env, pixelMapObj);
    CHECK_NULL_RETURN(mediaPixelMap, {});
    auto* ptrAddr = reinterpret_cast<void*>(&mediaPixelMap);
    return reinterpret_cast<ani_long>(ptrAddr);
}

ani_object ConvertToPixelMapAni(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long pixelMapPtr)
{
    auto* ptrAddr = reinterpret_cast<void*>(pixelMapPtr);
    CHECK_NULL_RETURN(ptrAddr, nullptr);
    std::shared_ptr<Media::PixelMap>* mediaPixelMap = reinterpret_cast<std::shared_ptr<Media::PixelMap>*>(ptrAddr);
    CHECK_NULL_RETURN(*mediaPixelMap, nullptr);
    return Media::PixelMapTaiheAni::CreateEtsPixelMap(env, *mediaPixelMap);
}

ani_long ExtractorsToDrawingCanvasPtr(ani_env* env, [[maybe_unused]]ani_object aniClass, ani_object drawingCanvasObj)
{
    ani_long nativeObj {};
    if (env->Object_GetFieldByName_Long(drawingCanvasObj, "nativeObj", &nativeObj) != ANI_OK) {
        return {};
    }
    auto* canvasAni = reinterpret_cast<Rosen::Drawing::AniCanvas*>(nativeObj);
    CHECK_NULL_RETURN(canvasAni, {});
    auto rsCanvas = canvasAni->GetCanvas();
    return reinterpret_cast<ani_long>(rsCanvas);
}

ani_object ExtractorsFromDrawingCanvasPtr(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long drawingCanvasPtr)
{
    auto rsCanvas = reinterpret_cast<OHOS::Rosen::Drawing::Canvas*>(drawingCanvasPtr);
    CHECK_NULL_RETURN(rsCanvas, nullptr);
    return Rosen::Drawing::AniCanvas::CreateAniCanvas(env, rsCanvas);
}

} // namespace OHOS::Ace::Ani
