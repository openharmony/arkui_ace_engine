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

#include "canvas_module.h"

#include <ani_signature_builder.h>

#include "canvas_ani/ani_canvas.h"
#include "load.h"
#include "pixel_map_taihe_ani.h"
#include "utils/ani_utils.h"

#include "base/log/log_wrapper.h"
#include "base/utils/utils.h"
#include "core/interfaces/native/ani/canvas_ani_modifier.h"
#include "core/interfaces/native/implementation/pixel_map_peer.h"

namespace OHOS::Ace::Ani {
namespace {
constexpr double DIFF = 1e-10;
}
void CanvasModule::SetPixelMap(
    ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long peerPtr, ani_object pixelMapObj)
{
    auto* peer = reinterpret_cast<ArkUICanvasRenderer>(peerPtr);
    CHECK_NULL_VOID(peer);
    auto mediaPixelMap = Media::PixelMapTaiheAni::GetNativePixelMap(env, pixelMapObj);
    CHECK_NULL_VOID(mediaPixelMap);
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_VOID(modifier);
    auto* canvasModifier = modifier->getCanvasAniModifier();
    CHECK_NULL_VOID(canvasModifier);
    canvasModifier->setPixelMap(peer, reinterpret_cast<void*>(&mediaPixelMap));
}

void CanvasModule::DrawPixelMap0(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long peerPtr,
    ani_object pixelMapObj, ani_double dx, ani_double dy)
{
    auto* peer = reinterpret_cast<ArkUICanvasRenderer>(peerPtr);
    CHECK_NULL_VOID(peer);
    auto mediaPixelMap = Media::PixelMapTaiheAni::GetNativePixelMap(env, pixelMapObj);
    CHECK_NULL_VOID(mediaPixelMap);
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_VOID(modifier);
    auto* canvasModifier = modifier->getCanvasAniModifier();
    CHECK_NULL_VOID(canvasModifier);
    canvasModifier->drawPixelMap0(peer, reinterpret_cast<void*>(&mediaPixelMap), dx, dy);
}

void CanvasModule::DrawPixelMap1(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long peerPtr,
    ani_object pixelMapObj, ani_double dx, ani_double dy, ani_double dw, ani_double dh)
{
    auto* peer = reinterpret_cast<ArkUICanvasRenderer>(peerPtr);
    CHECK_NULL_VOID(peer);
    auto mediaPixelMap = Media::PixelMapTaiheAni::GetNativePixelMap(env, pixelMapObj);
    CHECK_NULL_VOID(mediaPixelMap);
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_VOID(modifier);
    auto* canvasModifier = modifier->getCanvasAniModifier();
    CHECK_NULL_VOID(canvasModifier);
    canvasModifier->drawPixelMap1(peer, reinterpret_cast<void*>(&mediaPixelMap), dx, dy, dw, dh);
}

void CanvasModule::DrawPixelMap2(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long peerPtr,
    ani_object pixelMapObj, ani_double sx, ani_double sy, ani_double sw, ani_double sh, ani_double dx, ani_double dy,
    ani_double dw, ani_double dh)
{
    auto* peer = reinterpret_cast<ArkUICanvasRenderer>(peerPtr);
    CHECK_NULL_VOID(peer);
    auto mediaPixelMap = Media::PixelMapTaiheAni::GetNativePixelMap(env, pixelMapObj);
    CHECK_NULL_VOID(mediaPixelMap);
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_VOID(modifier);
    auto* canvasModifier = modifier->getCanvasAniModifier();
    CHECK_NULL_VOID(canvasModifier);
    canvasModifier->drawPixelMap2(peer, reinterpret_cast<void*>(&mediaPixelMap), sx, sy, sw, sh, dx, dy, dw, dh);
}

ani_long CanvasModule::ImageBitmapConstruct0(
    ani_env* env, [[maybe_unused]] ani_object aniClass, ani_string src, ani_int unit)
{
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_RETURN(modifier, {});
    auto* canvasModifier = modifier->getCanvasAniModifier();
    CHECK_NULL_RETURN(canvasModifier, {});
    std::string str = AniUtils::ANIStringToStdString(env, static_cast<ani_string>(src));
    return reinterpret_cast<ani_long>(canvasModifier->imageBitmapConstruct(str, nullptr, unit));
}

ani_long CanvasModule::ImageBitmapConstruct1(
    ani_env* env, [[maybe_unused]] ani_object aniClass, ani_object pixelMapObj, ani_int unit)
{
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_RETURN(modifier, {});
    auto* canvasModifier = modifier->getCanvasAniModifier();
    CHECK_NULL_RETURN(canvasModifier, {});
    auto mediaPixelMap = Media::PixelMapTaiheAni::GetNativePixelMap(env, pixelMapObj);
    CHECK_NULL_RETURN(mediaPixelMap, {});
    return reinterpret_cast<ani_long>(
        canvasModifier->imageBitmapConstruct("", reinterpret_cast<void*>(&mediaPixelMap), unit));
}

ani_double CanvasModule::GetCanvasDensity(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long peerPtr)
{
    auto* peer = reinterpret_cast<ArkUICanvasRenderer>(peerPtr);
    CHECK_NULL_RETURN(peer, 1.0);
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_RETURN(modifier, 1.0);
    auto* canvasModifier = modifier->getCanvasAniModifier();
    CHECK_NULL_RETURN(canvasModifier, 1.0);
    return canvasModifier->getCanvasDensity(peer);
}

ani_double CanvasModule::GetSystemDensity(ani_env* env, [[maybe_unused]] ani_object aniClass)
{
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_RETURN(modifier, 1.0);
    auto* canvasModifier = modifier->getCanvasAniModifier();
    CHECK_NULL_RETURN(canvasModifier, 1.0);
    return canvasModifier->getSystemDensity();
}

ani_object CanvasModule::GetImageData(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long peerPtr,
    ani_double sx, ani_double sy, ani_double sw, ani_double sh)
{
    static ani_ref gUint8ClampedArray = {};
    static ani_method gUint8ClampedArrayCtor = {};
    if (!gUint8ClampedArray) {
        static const char* className = "escompat.Uint8ClampedArray";
        ani_class cls;
        if (ANI_OK != env->FindClass(className, &cls) ||
            ANI_OK != env->GlobalReference_Create(static_cast<ani_ref>(cls), &gUint8ClampedArray)) {
            return nullptr;
        }
    }
    if (!gUint8ClampedArrayCtor) {
        arkts::ani_signature::SignatureBuilder signatureBuilder {};
        signatureBuilder.AddClass("escompat.ArrayBuffer").AddInt();
        if (ANI_OK != env->Class_FindMethod(static_cast<ani_class>(gUint8ClampedArray), "<ctor>",
            signatureBuilder.BuildSignatureDescriptor().c_str(), &gUint8ClampedArrayCtor)) {
            return nullptr;
        }
    }
    auto* peer = reinterpret_cast<ArkUICanvasRenderer>(peerPtr);
    CHECK_NULL_RETURN(peer, nullptr);
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_RETURN(modifier, nullptr);
    auto* canvasModifier = modifier->getCanvasAniModifier();
    CHECK_NULL_RETURN(canvasModifier, nullptr);
    auto density = canvasModifier->getCanvasDensity(peer);
    auto width = sw * density + DIFF;
    auto height = sh * density + DIFF;
    uint32_t finalWidth = static_cast<uint32_t>(std::abs(width));
    uint32_t finalHeight = static_cast<uint32_t>(std::abs(height));
    if (finalHeight > 0 && finalWidth > (UINT32_MAX / finalHeight)) {
        return nullptr;
    }
    size_t length = finalWidth * finalHeight * 4; // 4: size of pixel
    uint8_t* imageData = nullptr;
    ani_arraybuffer arrayBuffer;
    if (ANI_OK != env->CreateArrayBuffer(length, reinterpret_cast<void**>(&imageData), &arrayBuffer)) {
        return nullptr;
    }
    canvasModifier->getImageData(peer, imageData, sx * density, sy * density, sw * density, sh * density);
    ani_object aniValue;
    ani_int offset = 0;
    if (ANI_OK != env->Object_New(static_cast<ani_class>(gUint8ClampedArray), gUint8ClampedArrayCtor, &aniValue,
        arrayBuffer, offset)) {
        return nullptr;
    }
    return aniValue;
}

void CanvasModule::PutImageData0(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long peerPtr, ani_object array,
    ani_double dx, ani_double dy, ani_int width, ani_int height)
{
    auto* peer = reinterpret_cast<ArkUICanvasRenderer>(peerPtr);
    CHECK_NULL_VOID(peer);
    ani_ref buffer;
    if ((env->Object_GetFieldByName_Ref(array, "buffer", &buffer)) != ANI_OK) {
        return;
    }
    ani_arraybuffer arrayBuffer = static_cast<ani_arraybuffer>(buffer);
    uint8_t* data = nullptr;
    ani_size length = 0;
    if (env->ArrayBuffer_GetInfo(arrayBuffer, reinterpret_cast<void**>(&data), &length) != ANI_OK) {
        return;
    }
    CHECK_NULL_VOID(data);
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_VOID(modifier);
    auto* canvasModifier = modifier->getCanvasAniModifier();
    CHECK_NULL_VOID(canvasModifier);
    canvasModifier->putImageData0(peer, data, length, dx, dy, width, height);
}

void CanvasModule::PutImageData1(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long peerPtr, ani_object array,
    ani_double dx, ani_double dy, ani_int width, ani_int height, ani_double dirtyX, ani_double dirtyY,
    ani_double dirtyWidth, ani_double dirtyHeight)
{
    auto* peer = reinterpret_cast<ArkUICanvasRenderer>(peerPtr);
    CHECK_NULL_VOID(peer);
    ani_ref buffer;
    if ((env->Object_GetFieldByName_Ref(array, "buffer", &buffer)) != ANI_OK) {
        return;
    }
    ani_arraybuffer arrayBuffer = static_cast<ani_arraybuffer>(buffer);
    uint8_t* data = nullptr;
    ani_size length = 0;
    if (env->ArrayBuffer_GetInfo(arrayBuffer, reinterpret_cast<void**>(&data), &length) != ANI_OK) {
        return;
    }
    CHECK_NULL_VOID(data);
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_VOID(modifier);
    auto* canvasModifier = modifier->getCanvasAniModifier();
    CHECK_NULL_VOID(canvasModifier);
    canvasModifier->putImageData1(peer, data, length, dx, dy, width, height, dirtyX, dirtyY, dirtyWidth, dirtyHeight);
}

ani_object CanvasModule::GetDrawingCanvas(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long peerPtr)
{
    ani_ref aniRef;
    env->GetUndefined(&aniRef);
    ani_object undefined = static_cast<ani_object>(aniRef);
    
    auto* peer = reinterpret_cast<ArkUIDrawingRenderingContext>(peerPtr);
    CHECK_NULL_RETURN(peer, undefined);
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_RETURN(modifier, undefined);
    auto* canvasModifier = modifier->getCanvasAniModifier();
    CHECK_NULL_RETURN(canvasModifier, undefined);
    auto* drawingCanvas = canvasModifier->getDrawingCanvas(peer);
    CHECK_NULL_RETURN(drawingCanvas, undefined);
    auto* canvas = reinterpret_cast<Rosen::Drawing::Canvas*>(drawingCanvas);
    CHECK_NULL_RETURN(canvas, undefined);
    return Rosen::Drawing::AniCanvas::CreateAniCanvas(env, canvas);
}

ani_int CanvasModule::GetCanvasId(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long peerPtr)
{
    auto* peer = reinterpret_cast<ArkUICanvasRenderingContext>(peerPtr);
    CHECK_NULL_RETURN(peer, -1);
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_RETURN(modifier, -1);
    auto* canvasModifier = modifier->getCanvasAniModifier();
    CHECK_NULL_RETURN(canvasModifier, -1);
    return canvasModifier->getCanvasId(peer);
}

void CanvasModule::SetAttachCallbackId(
    ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long peerPtr, ani_int attachCallbackId)
{
    auto* peer = reinterpret_cast<ArkUICanvasRenderingContext>(peerPtr);
    CHECK_NULL_VOID(peer);
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_VOID(modifier);
    auto* canvasModifier = modifier->getCanvasAniModifier();
    CHECK_NULL_VOID(canvasModifier);
    canvasModifier->setAttachCallbackId(peer, attachCallbackId);
}
void CanvasModule::SetDetachCallbackId(
    ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long peerPtr, ani_int detachCallbackId)
{
    auto* peer = reinterpret_cast<ArkUICanvasRenderingContext>(peerPtr);
    CHECK_NULL_VOID(peer);
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_VOID(modifier);
    auto* canvasModifier = modifier->getCanvasAniModifier();
    CHECK_NULL_VOID(canvasModifier);
    canvasModifier->setDetachCallbackId(peer, detachCallbackId);
}
} // namespace OHOS::Ace::Ani
