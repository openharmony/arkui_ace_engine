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

#include "image_module.h"

#include "color_filter_ani/ani_color_filter.h"
#include "lattice_ani/ani_lattice.h"
#include "load.h"
#include "log/log.h"
#include "pixel_map_taihe_ani.h"
#include "core/interfaces/native/implementation/pixel_map_peer.h"

namespace OHOS::Ace::Ani {

ani_long ExtractorsToDrawableDescriptorPtr(
    ani_env* env, [[maybe_unused]] ani_object obj, ani_object drawableAni)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return 0;
    }
    ani_long nativeObj = 0;
    env->Object_GetPropertyByName_Long(drawableAni, "nativeObj", &nativeObj);
    auto* drawable = reinterpret_cast<void*>(nativeObj);
    if (drawable == nullptr) {
        HILOGE("image construct with drawable descriptor failed, nativeObj is nullptr");
        return 0;
    }
    return reinterpret_cast<ani_long>(drawable);
}

ani_long ExtractorsToDrawingColorFilterPtr(ani_env* env, [[maybe_unused]] ani_object obj, ani_object colorFilterAni)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return 0;
    }
    ani_long nativeObj = 0;
    env->Object_GetPropertyByName_Long(colorFilterAni, "nativeObj", &nativeObj);
    auto* colorFilter = reinterpret_cast<void*>(nativeObj);
    if (colorFilter == nullptr) {
        HILOGE("image colorFilter options is null");
        return 0;
    }
    auto* aniColorFilter = reinterpret_cast<OHOS::Rosen::Drawing::AniColorFilter*>(colorFilter);
    if (aniColorFilter == nullptr) {
        HILOGE("image aniColorFilter options is null");
        return 0;
    }
    auto drawingColorFilter = aniColorFilter->GetColorFilter();
    if (drawingColorFilter == nullptr) {
        HILOGE("image drawingColorFilter options is null");
        return 0;
    }
    auto colorFilterPeer =
        modifier->getImageAniModifier()->getDrawingColorFilterPeer(reinterpret_cast<void*>(&drawingColorFilter));
    return reinterpret_cast<ani_long>(colorFilterPeer);
}

ani_long ExtractorsToDrawingLatticePtr(ani_env* env, [[maybe_unused]] ani_object obj, ani_object latticeAni)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return 0;
    }
    ani_long nativeObj = 0;
    env->Object_GetPropertyByName_Long(latticeAni, "nativeObj", &nativeObj);
    auto* lattice = reinterpret_cast<void*>(nativeObj);
    if (lattice == nullptr) {
        HILOGE("image reziable options is null");
        return 0;
    }
    auto* aniLattice = reinterpret_cast<OHOS::Rosen::Drawing::AniLattice*>(lattice);
    if (aniLattice == nullptr) {
        HILOGE("image reziable aniLattice is null");
        return 0;
    }
    auto resizableLattic = aniLattice->GetLattice();
    if (resizableLattic == nullptr) {
        HILOGE("image reziable resizableLattic is null");
        return 0;
    }
    auto lattcePeer = modifier->getImageAniModifier()->getDrawingLatticePeer(reinterpret_cast<void*>(&resizableLattic));
    return reinterpret_cast<ani_long>(lattcePeer);
}

ani_object ExtractorsFromImagePixelMapPtr(ani_env* env, [[maybe_unused]]ani_object aniClass, ani_long pointer)
{
    auto* pixelMapPeer = reinterpret_cast<image_PixelMapPeer*>(pointer);
    CHECK_NULL_RETURN(pixelMapPeer, nullptr);
    CHECK_NULL_RETURN(pixelMapPeer->pixelMap, nullptr);
    auto mediaPixelMap = pixelMapPeer->pixelMap->GetPixelMapSharedPtr();
    CHECK_NULL_RETURN(mediaPixelMap, nullptr);
    return Media::PixelMapTaiheAni::CreateEtsPixelMap(env, mediaPixelMap);
}

ani_long ExtractorsToImagePixelMapPtr(ani_env* env, [[maybe_unused]] ani_object obj, ani_object pixelMapObj)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier) {
        return 0;
    }
    auto pixelMap = OHOS::Media::PixelMapTaiheAni::GetNativePixelMap(env, pixelMapObj);
    auto pixelMapPtr = reinterpret_cast<void*>(&pixelMap);
    auto imagePixelMapPeer = modifier->getImageAniModifier()->getPixelMapPeer(pixelMapPtr);
    return reinterpret_cast<ani_long>(imagePixelMapPeer);
}

void ImageResizableOptions(ani_env* env, [[maybe_unused]] ani_object obj, ani_long node, ani_object latticeAni)
{
    auto* arkNode = reinterpret_cast<ArkUINodeHandle>(node);
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !arkNode) {
        return;
    }
    ani_long nativeObj = 0;
    env->Object_GetPropertyByName_Long(latticeAni, "nativeObj", &nativeObj);
    auto* lattice = reinterpret_cast<void*>(nativeObj);
    if (lattice == nullptr) {
        HILOGE("image reziable options is null");
        return;
    }
    auto* aniLattice = reinterpret_cast<OHOS::Rosen::Drawing::AniLattice*>(lattice);
    if (aniLattice == nullptr) {
        HILOGE("image reziable aniLattice is null");
        return;
    }
    auto resizableLattic = aniLattice->GetLattice();
    if (resizableLattic == nullptr) {
        HILOGE("image reziable resizableLattic is null");
        return;
    }
    modifier->getImageAniModifier()->setResizableLattice(arkNode, &resizableLattic);
}

void ImageConstructPixelMap(ani_env* env, [[maybe_unused]] ani_object obj, ani_long node, ani_object pixelMapAni)
{
    auto* arkNode = reinterpret_cast<ArkUINodeHandle>(node);
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !arkNode) {
        return;
    }
    auto pixelMap = OHOS::Media::PixelMapTaiheAni::GetNativePixelMap(env, pixelMapAni);
    modifier->getImageAniModifier()->setPixelMap(arkNode, &pixelMap);
}

void ImageConstructDrawableDescriptor(
    ani_env* env, [[maybe_unused]] ani_object obj, ani_long node, ani_object drawableAni)
{
    auto* arkNode = reinterpret_cast<ArkUINodeHandle>(node);
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !arkNode) {
        return;
    }
    ani_long nativeObj = 0;
    env->Object_GetPropertyByName_Long(drawableAni, "nativeObj", &nativeObj);
    auto* drawable = reinterpret_cast<void*>(nativeObj);
    if (drawable == nullptr) {
        HILOGE("image construct with drawable descriptor failed, nativeObj is nullptr");
        return;
    }
    modifier->getImageAniModifier()->setDrawableDescriptor(arkNode, drawable);
}

void ImageDrawingColorFilter(ani_env* env, [[maybe_unused]] ani_object obj, ani_long node, ani_object colorFilterAni)
{
    auto* arkNode = reinterpret_cast<ArkUINodeHandle>(node);
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !arkNode) {
        return;
    }
    ani_long nativeObj = 0;
    env->Object_GetPropertyByName_Long(colorFilterAni, "nativeObj", &nativeObj);
    auto* colorFilter = reinterpret_cast<void*>(nativeObj);
    if (colorFilter == nullptr) {
        HILOGE("image colorFilter options is null");
        return;
    }
    auto* aniColorFilter = reinterpret_cast<OHOS::Rosen::Drawing::AniColorFilter*>(colorFilter);
    if (aniColorFilter == nullptr) {
        HILOGE("image aniColorFilter options is null");
        return;
    }
    auto drawingColorFilter = aniColorFilter->GetColorFilter();
    if (drawingColorFilter == nullptr) {
        HILOGE("image drawingColorFilter options is null");
        return;
    }
    modifier->getImageAniModifier()->setDrawingColorFilter(arkNode, &drawingColorFilter);
}

ani_long Image_ColorFilter_TransferStatic(ani_env* env, [[maybe_unused]] ani_object obj, ani_long colorFilter)
{
    const auto* modifier = GetNodeAniModifier();
    if (modifier == nullptr || colorFilter == 0) {
        return 0;
    }
    auto colorFilterPeer = modifier->getImageAniModifier()->createColorFilterPeer(colorFilter);
    if (colorFilterPeer == 0) {
        return 0;
    }
    auto pointer = reinterpret_cast<ani_long>(colorFilterPeer);
    return pointer;
}

ani_long Image_ColorFilter_TransferDynamic(ani_env* env, [[maybe_unused]] ani_object obj, ani_long colorFilterPeer)
{
    const auto* modifier = GetNodeAniModifier();
    if (modifier == nullptr || colorFilterPeer == 0) {
        return 0;
    }
    auto pointer = modifier->getImageAniModifier()->getColorFilter(colorFilterPeer);
    return pointer;
}
} // namespace OHOS::Ace::Ani
