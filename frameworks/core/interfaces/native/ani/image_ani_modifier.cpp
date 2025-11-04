/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "image_ani_modifier.h"

#include "ani.h"

#include "base/image/drawing_lattice.h"
#include "base/image/pixel_map.h"
#include "base/image/drawing_color_filter.h"
#include "base/log/log.h"
#include "core/components_ng/pattern/image/image_model_ng.h"
#include "core/components_ng/pattern/image/image_model_static.h"
#include "core/drawable/drawable_descriptor.h"
#include "core/interfaces/native/implementation/color_filter_peer.h"
#include "core/interfaces/native/implementation/pixel_map_peer.h"
#include "core/interfaces/native/implementation/drawing_color_filter_peer.h"
#include "core/interfaces/native/implementation/drawing_lattice_peer.h"

namespace OHOS::Ace::NG {

void SetPixelMap(ArkUINodeHandle node, void* pixelMap)
{
    auto pixelMapRef = PixelMap::CreatePixelMap(pixelMap);
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    ImageModelStatic::SetPixelMap(frameNode, pixelMapRef);
}

void SetDrawableDescriptor(ArkUINodeHandle node, void* drawableDescriptor)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    ImageModelStatic::SetDrawableDescriptor(frameNode, static_cast<DrawableDescriptor*>(drawableDescriptor));
}

void SetResizableLattice(ArkUINodeHandle node, void* aniLattice)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    auto lattice = DrawingLattice::CreateDrawingLatticeFromNative(aniLattice);
    ImageModelStatic::SetResizableLattice(frameNode, lattice);
}

void SetDrawingColorFilter(ArkUINodeHandle node, void* aniColorFilter)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    auto colorFilter = DrawingColorFilter::CreateDrawingColorFilterFromNative(aniColorFilter);
    ImageModelStatic::SetDrawingColorFilter(frameNode, colorFilter);
}

void* GetPixelMapPeer(void* pixelMapPtr)
{
    return reinterpret_cast<void*>(image_PixelMapPeer::Create(PixelMap::CreatePixelMap(pixelMapPtr)));
}

ani_long CreateColorFilterPeer(ani_long colorFilter)
{
    CHECK_EQUAL_RETURN(colorFilter, 0, 0);
    auto* rawPtr = reinterpret_cast<OHOS::Ace::ImageColorFilter*>(colorFilter);
    auto imageColorFilter = Referenced::Claim<OHOS::Ace::ImageColorFilter>(rawPtr);
    if (!imageColorFilter) {
        return 0;
    }
    auto* peer = new ColorFilterPeer();
    CHECK_NULL_RETURN(peer, 0);
    peer->SetColorFilter(imageColorFilter);
    auto pointer = reinterpret_cast<ani_long>(peer);
    return pointer;
}

ani_long GetColorFilter(ani_long colorFilterPeer)
{
    if (colorFilterPeer == 0) {
        return 0;
    }
    auto* peer = reinterpret_cast<ColorFilterPeer*>(colorFilterPeer);
    auto imageColorFilter = peer->GetColorFilter();
    if (!imageColorFilter) {
        return 0;
    }
    auto* rawPtr = Referenced::RawPtr(imageColorFilter);
    auto pointer = reinterpret_cast<ani_long>(rawPtr);
    return pointer;
}

void* GetDrawingColorFilterPeer(void* colorFilterMapPtr)
{
    return reinterpret_cast<void*>(drawing_ColorFilterPeer::Create(colorFilterMapPtr));
}

void* GetDrawingLatticePeer(void* drawingLatticePeerPtr)
{
    return reinterpret_cast<void*>(drawing_LatticePeer::Create(drawingLatticePeerPtr));
}

static ani_object CreateImageErrorAni(ani_env* env, const LoadImageFailEvent& info)
{
    ani_object imageErrorAni {};
    ani_class imageErrorClass;
    if (env->FindClass("arkui.hooks.ImageOpsHandWritten.ImageErrorImpl", &imageErrorClass) != ANI_OK) {
        return nullptr;
    }

    ani_method ctor;
    env->Class_FindMethod(imageErrorClass, "<ctor>", ":", &ctor);
    ani_string stringAni {};
    env->String_NewUTF8(info.GetErrorMessage().c_str(), info.GetErrorMessage().size(), &stringAni);
    env->Object_New(imageErrorClass, ctor, &imageErrorAni);
    env->Object_SetPropertyByName_Int(imageErrorAni, "componentWidth", info.GetComponentWidth());
    env->Object_SetPropertyByName_Int(imageErrorAni, "componentHeight", info.GetComponentHeight());
    env->Object_SetPropertyByName_Ref(imageErrorAni, "message", stringAni);

    ani_class cls;
    if (env->FindClass("@ohos.base.BusinessError", &cls) != ANI_OK) {
        return nullptr;
    }
    env->Class_FindMethod(imageErrorClass, "<ctor>", ":", &ctor);
    ani_object errAni {};
    env->Object_New(cls, ctor, &errAni);
    ani_string msgAni {};
    env->String_NewUTF8(info.GetErrorInfo().errorMessage.c_str(), info.GetErrorInfo().errorMessage.size(), &msgAni);
    env->Object_SetPropertyByName_Ref(errAni, "message", msgAni);
    env->Object_SetPropertyByName_Int(errAni, "code", static_cast<int32_t>(info.GetErrorInfo().errorCode));
    env->Object_SetPropertyByName_Ref(imageErrorAni, "error", errAni);

    return imageErrorAni;
}

static ani_status GetAniEnv(ani_vm* vm, ani_env** env)
{
    CHECK_NULL_RETURN(vm, ANI_ERROR);
    ani_options aniOpt { 0, nullptr };
    auto status = vm->AttachCurrentThread(&aniOpt, ANI_VERSION_1, env);
    if (status != ANI_OK) {
        vm->GetEnv(ANI_VERSION_1, env);
    }
    return status;
}

class ImageCallbackAni {
public:
    ImageCallbackAni(ani_env* env, ani_ref func)
    {
        CHECK_NULL_VOID(env);
        env->GetVM(&vm_);
        env->GlobalReference_Create(func, &func_);
    }
    ~ImageCallbackAni()
    {
        CHECK_NULL_VOID(vm_);
        CHECK_NULL_VOID(func_);
        ani_env* env;
        auto attachCurrentThreadStatus = GetAniEnv(vm_, &env);
        CHECK_NULL_VOID(env);
        env->GlobalReference_Delete(func_);
        if (attachCurrentThreadStatus == ANI_OK) {
            vm_->DetachCurrentThread();
        }
    }
    void Call(ani_env* env, ani_size argc, ani_ref* argv, ani_ref* result)
    {
        CHECK_NULL_VOID(env);
        env->FunctionalObject_Call(static_cast<ani_fn_object>(func_), argc, argv, result);
    }

private:
    ani_vm* vm_ = nullptr;
    ani_ref func_ = nullptr;
};

static void ConvertOnErrorCallback(
    ani_env* env, ani_object onErrorCallback, std::function<void(const LoadImageFailEvent& info)>& callback)
{
    CHECK_NULL_VOID(env);

    ani_vm* vm = nullptr;
    env->GetVM(&vm);
    ani_ref fnObjGlobalRef = static_cast<ani_object>(onErrorCallback);

    auto callbackAni = std::make_shared<ImageCallbackAni>(env, fnObjGlobalRef);
    callback = [vm, callbackAni](const LoadImageFailEvent& info) {
        CHECK_NULL_VOID(vm);
        CHECK_NULL_VOID(callbackAni);
        ani_env* env;
        auto attachCurrentThreadStatus = GetAniEnv(vm, &env);
        CHECK_NULL_VOID(env);

        ani_object imageErrorAni = CreateImageErrorAni(env, info);
        CHECK_NULL_VOID(imageErrorAni);
        std::vector<ani_ref> args = { imageErrorAni };
        ani_ref ret = nullptr;
        callbackAni->Call(env, args.size(), args.data(), &ret);
        if (attachCurrentThreadStatus == ANI_OK) {
            vm->DetachCurrentThread();
        }
    };
}

void SetImageOnErrorCallback(ani_env* env, ArkUINodeHandle node, void* callback)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(env);
    ani_object fnObjGlobal = static_cast<ani_object>(callback);

    std::function<void(const LoadImageFailEvent& info)> onErrorCallbackFun = nullptr;
    ConvertOnErrorCallback(env, fnObjGlobal, onErrorCallbackFun);

    ImageModelNG::SetOnError(frameNode, std::move(onErrorCallbackFun));
}

const ArkUIAniImageModifier* GetImageAniModifier()
{
    static const ArkUIAniImageModifier impl = {
        .setPixelMap = OHOS::Ace::NG::SetPixelMap,
        .setDrawableDescriptor = OHOS::Ace::NG::SetDrawableDescriptor,
        .setResizableLattice = OHOS::Ace::NG::SetResizableLattice,
        .setDrawingColorFilter = OHOS::Ace::NG::SetDrawingColorFilter,
        .getPixelMapPeer = OHOS::Ace::NG::GetPixelMapPeer,
        .createColorFilterPeer = OHOS::Ace::NG::CreateColorFilterPeer,
        .getColorFilter = OHOS::Ace::NG::GetColorFilter,
        .getDrawingColorFilterPeer = OHOS::Ace::NG::GetDrawingColorFilterPeer,
        .getDrawingLatticePeer = OHOS::Ace::NG::GetDrawingLatticePeer,
        .setImageOnErrorCallback = OHOS::Ace::NG::SetImageOnErrorCallback,
    };
    return &impl;
}

} // namespace OHOS::Ace::NG