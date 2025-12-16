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

#include "ani.h"
#include "color_filter_ani/ani_color_filter.h"
#include "lattice_ani/ani_lattice.h"
#include "load.h"
#include "log/log.h"
#include "pixel_map_taihe_ani.h"
#include "core/interfaces/native/implementation/pixel_map_peer.h"
#include "utils/ani_utils.h"

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

static ani_object CreateImageErrorAni(ani_env* env, const ArkUIAniImageOnErrorParams& param)
{
    ani_object imageErrorAni {};
    ani_class imageErrorClass;
    if (env->FindClass("arkui.hooks.ImageOpsHandWritten.ImageErrorImpl", &imageErrorClass) != ANI_OK) {
        return nullptr;
    }

    ani_method ctor;
    env->Class_FindMethod(imageErrorClass, "<ctor>", ":", &ctor);
    ani_string stringAni {};
    env->String_NewUTF8(param.errorMessage.c_str(), param.errorMessage.size(), &stringAni);
    env->Object_New(imageErrorClass, ctor, &imageErrorAni);
    env->Object_SetPropertyByName_Int(imageErrorAni, "componentWidth", param.componentWidth);
    env->Object_SetPropertyByName_Int(imageErrorAni, "componentHeight", param.componentHeight);
    env->Object_SetPropertyByName_Ref(imageErrorAni, "message", stringAni);

    ani_class cls;
    if (env->FindClass("@ohos.base.BusinessError", &cls) != ANI_OK) {
        return nullptr;
    }
    env->Class_FindMethod(imageErrorClass, "<ctor>", ":", &ctor);
    ani_object errAni {};
    env->Object_New(cls, ctor, &errAni);
    ani_string msgAni {};
    env->String_NewUTF8(param.errorInfo.c_str(), param.errorInfo.size(), &msgAni);
    env->Object_SetPropertyByName_Ref(errAni, "message", msgAni);
    env->Object_SetPropertyByName_Int(errAni, "code", static_cast<int32_t>(param.errorCode));
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
    ani_env* env, ani_object onErrorCallback, std::function<void(const ArkUIAniImageOnErrorParams& param)>& callback)
{
    CHECK_NULL_VOID(env);

    ani_vm* vm = nullptr;
    env->GetVM(&vm);
    ani_ref fnObjGlobalRef = static_cast<ani_object>(onErrorCallback);

    auto callbackAni = std::make_shared<ImageCallbackAni>(env, fnObjGlobalRef);
    callback = [vm, callbackAni](const ArkUIAniImageOnErrorParams& param) {
        CHECK_NULL_VOID(vm);
        CHECK_NULL_VOID(callbackAni);
        ani_env* env;
        auto attachCurrentThreadStatus = GetAniEnv(vm, &env);
        CHECK_NULL_VOID(env);

        ani_object imageErrorAni = CreateImageErrorAni(env, param);
        CHECK_NULL_VOID(imageErrorAni);
        std::vector<ani_ref> args = { imageErrorAni };
        ani_ref ret = nullptr;
        callbackAni->Call(env, args.size(), args.data(), &ret);
        if (attachCurrentThreadStatus == ANI_OK) {
            vm->DetachCurrentThread();
        }
    };
}

void Image_SetOnErrorCallback(ani_env* env, [[maybe_unused]] ani_object obj, ani_long node, ani_object onErrorCallback)
{
    auto* arkNode = reinterpret_cast<ArkUINodeHandle>(node);
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !arkNode) {
        return;
    }
    if (AniUtils::IsUndefined(env, onErrorCallback)) {
        return;
    }

    ani_object fnObjGlobal = static_cast<ani_object>(onErrorCallback);

    std::function<void(const ArkUIAniImageOnErrorParams &param)> onErrorCallbackFun = nullptr;
    ConvertOnErrorCallback(env, fnObjGlobal, onErrorCallbackFun);
    modifier->getImageAniModifier()->setImageOnErrorCallback(arkNode, std::move(onErrorCallbackFun));
}
} // namespace OHOS::Ace::Ani
