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

#include "drawable_module.h"

#include "interfaces/inner_api/drawable_descriptor/drawable_descriptor.h"
#include "interop_js/arkts_esvalue.h"
#include "load.h"
#include "log/log.h"
#include "pixel_map_taihe_ani.h"
#include "resource_manager.h"
#include "securec.h"
#include "utils/ani_utils.h"

#include "base/log/log_wrapper.h"
#include "core/interfaces/ani/ani_api.h"

namespace OHOS::Ace::Ani {
namespace {
constexpr char PIXEL_MAP_CONSTRUCTOR[] = "C{@ohos.multimedia.image.image.PixelMap}:";
constexpr char PIXEL_MAP_DRAWABLE[] = "@ohos.arkui.drawableDescriptor.PixelMapDrawableDescriptor";
constexpr char ARRAY_GET[] = "i:Y";
constexpr char ANIMATED_CONSTRUCTOR[] = "C{std.core.Array}C{@ohos.arkui.drawableDescriptor.AnimationOptions}:";
constexpr char ANIMATED_DRAWABLE[] = "@ohos.arkui.drawableDescriptor.AnimatedDrawableDescriptor";
constexpr char LAYERED_CONSTRUCTOR[] =
    "C{@ohos.arkui.drawableDescriptor.DrawableDescriptor}C{@ohos.arkui.drawableDescriptor.DrawableDescriptor}C{@ohos."
    "arkui.drawableDescriptor.DrawableDescriptor}:";
constexpr char LAYERED_DRAWABLE[] = "@ohos.arkui.drawableDescriptor.LayeredDrawableDescriptor";
constexpr char LOAD_RESULT_IMPL[] = "@ohos.arkui.drawableDescriptor.DrawableDescriptorLoadedResultImpl";
constexpr char ANIMATION_CONTROLLER_INNER[] = "@ohos.arkui.drawableDescriptor.AnimationControllerInner";
constexpr char ANIMATION_OPTIONS_IMPL[] = "@ohos.arkui.drawableDescriptor.AnimationOptionsImpl";

constexpr char DRAWABLE_DESCRIPTOR_NAME[] = "DrawableDescriptor";
constexpr char LAYERED_DRAWABLE_DESCRIPTOR_NAME[] = "LayeredDrawableDescriptor";
constexpr char ANIMATED_DRAWABLE_DESCRIPTOR_NAME[] = "AnimatedDrawableDescriptor";
constexpr char PIXELMAP_DRAWABLE_DESCRIPTOR_NAME[] = "PixelMapDrawableDescriptor";
constexpr char DEFAULT_MASK[] = "ohos_icon_mask";
constexpr size_t MAX_TYPENAME_LEN = 255;
constexpr int32_t SPECIFIED_CAPACITY = 16;

enum class DrawableType {
    BASE,
    LAYERED,
    ANIMATED,
    PIXELMAP,
};

enum class ControlStatus {
    IDLE,    // when animation not start or been cancel.
    RUNNING, // play in reverse / forward direction.
    PAUSED,  // paused by call Pause API.
    STOPPED, // stopped by call Finish/Stop API or has played to the end.
};

ani_object CreatePixelMapDrawableByPixelMap(ani_env* env, const std::shared_ptr<Media::PixelMap>& pixelMap)
{
    auto pixelAni = Media::PixelMapTaiheAni::CreateEtsPixelMap(env, pixelMap);
    if (pixelAni == nullptr) {
        return nullptr;
    }
    // set foreground property to arkts object
    ani_class cls;
    auto status = env->FindClass(PIXEL_MAP_DRAWABLE, &cls);
    if (status != ANI_OK) {
        return nullptr;
    }
    ani_object obj {};
    ani_method ctor {};
    env->Class_FindMethod(cls, "<ctor>", PIXEL_MAP_CONSTRUCTOR, &ctor);
    env->Object_New(cls, ctor, &obj, pixelAni);
    return obj;
}

ani_object CreateDrawableDescriptorLoadedResult(ani_env* env, const int32_t imageWidth, const int32_t imageHeight)
{
    ani_object drawableDescriptorLoadedResultAni {};
    ani_class cls;
    if (env->FindClass(LOAD_RESULT_IMPL, &cls) != ANI_OK) {
        return nullptr;
    }
    ani_method ctor;
    if (env->Class_FindMethod(cls, "<ctor>", ":", &ctor) != ANI_OK) {
        return nullptr;
    }

    ANI_CALL(env, Object_New(cls, ctor, &drawableDescriptorLoadedResultAni), return drawableDescriptorLoadedResultAni);
    ANI_CALL(env,
        Object_SetPropertyByName_Int(drawableDescriptorLoadedResultAni, "imageWidth", static_cast<ani_int>(imageWidth)),
        return drawableDescriptorLoadedResultAni);
    ANI_CALL(env,
        Object_SetPropertyByName_Int(
            drawableDescriptorLoadedResultAni, "imageHeight", static_cast<ani_int>(imageHeight)),
        return drawableDescriptorLoadedResultAni);

    return drawableDescriptorLoadedResultAni;
}

void TriggerJsCallback(std::shared_ptr<ArkUIDrawableAsync> asyncCtx)
{
    CHECK_NULL_VOID((asyncCtx && asyncCtx->deferred && asyncCtx->env));

    ani_size nrRefs = SPECIFIED_CAPACITY;
    ANI_CALL(asyncCtx->env, CreateLocalScope(nrRefs), { return; });
    if (asyncCtx->errorCode == 0) {
        ani_object drawableDescriptorLoadedResult =
            CreateDrawableDescriptorLoadedResult(asyncCtx->env, asyncCtx->imageWidth_, asyncCtx->imageHeight_);
        ani_ref drawableDescriptorLoadedResultRef = static_cast<ani_ref>(drawableDescriptorLoadedResult);
        auto status = asyncCtx->env->PromiseResolver_Resolve(asyncCtx->deferred, drawableDescriptorLoadedResultRef);
        if (status != ANI_OK) {
            HILOGW("AceDrawableDescriptor [ANI] PromiseResolver_Resolve fail. status: %{public}d", status);
        }
    } else {
        ani_error error = AniUtils::GetErrorObject(
            asyncCtx->env, "resource loading failed.", asyncCtx->errorCode, "AceDrawableDescriptor");
        auto status = asyncCtx->env->PromiseResolver_Reject(asyncCtx->deferred, error);
        if (status != ANI_OK) {
            HILOGW("AceDrawableDescriptor [ANI] PromiseResolver_Reject fail. status: %{public}d", status);
        }
    }
    auto status = asyncCtx->env->DestroyLocalScope();
    if (status != ANI_OK) {
        HILOGW("AceDrawableDescriptor [ANI] DestroyLocalScope fail. status: %{public}d", status);
    }
}

void CreateDrawableLoadCallback(ani_env* env, ArkUIDrawableAsync& asyncCtx, ani_object* result)
{
    asyncCtx.env = env;
    env->Promise_New(&asyncCtx.deferred, result);
    auto jsCallback = [](std::shared_ptr<ArkUIDrawableAsync> drawableCtx) { TriggerJsCallback(drawableCtx); };
    asyncCtx.callBackJsFunction = jsCallback;
}

ani_object CreateAnimatedDrawableByPixelMapList(ani_env* env,
    const std::vector<std::shared_ptr<Media::PixelMap>>& pixelMapList, int32_t duration, int32_t iterations)
{
    ani_object optionsAni {};
    if (pixelMapList.empty()) {
        return nullptr;
    }
    ani_class cls;
    env->FindClass(ANIMATION_OPTIONS_IMPL, &cls);
    ani_method ctor;
    env->Class_FindMethod(cls, "<ctor>", ":", &ctor);

    auto* durationAni = AniUtils::CreateDouble(env, duration);
    auto* iterationsAni = AniUtils::CreateDouble(env, iterations);

    env->Object_New(cls, ctor, &optionsAni);

    env->Object_SetPropertyByName_Ref(optionsAni, "duration", durationAni);
    env->Object_SetPropertyByName_Ref(optionsAni, "iterations", iterationsAni);

    ani_array pixelMapsAni;
    auto init = Media::PixelMapTaiheAni::CreateEtsPixelMap(env, pixelMapList[0]);

    env->Array_New(pixelMapList.size(), init, &pixelMapsAni);

    for (size_t index = 1; index < pixelMapList.size(); index++) {
        auto pixelAni = Media::PixelMapTaiheAni::CreateEtsPixelMap(env, pixelMapList[index]);
        env->Array_Set(pixelMapsAni, index, pixelAni);
    }

    env->FindClass(ANIMATED_DRAWABLE, &cls);

    ani_object obj {};
    env->Class_FindMethod(cls, "<ctor>", ANIMATED_CONSTRUCTOR, &ctor);
    env->Object_New(cls, ctor, &obj, pixelMapsAni, optionsAni);
    return obj;
}

ani_object CreateLayeredDrawableByPixelMap(ani_env* env, const std::shared_ptr<Media::PixelMap>& foreground,
    const std::shared_ptr<Media::PixelMap>& background, const std::shared_ptr<Media::PixelMap>& mask)
{
    ani_class cls {};
    auto status = env->FindClass(LAYERED_DRAWABLE, &cls);
    if (status != ANI_OK) {
        return nullptr;
    }
    ani_object obj {};
    ani_method ctor {};
    if (ANI_OK != env->Class_FindMethod(cls, "<ctor>", LAYERED_CONSTRUCTOR, &ctor)) {
        return nullptr;
    }

    ani_object objForeground {};
    ani_object objBackground {};
    ani_object objMask {};
    if (foreground) {
        objForeground = CreatePixelMapDrawableByPixelMap(env, foreground);
    }

    if (background) {
        objBackground = CreatePixelMapDrawableByPixelMap(env, background);
    }

    if (mask) {
        objMask = CreatePixelMapDrawableByPixelMap(env, mask);
    }

    status = env->Object_New(cls, ctor, &obj, objForeground, objBackground, objMask);
    if (ANI_OK != status) {
        HILOGW("AceDrawableDescriptor CreateLayeredDrawableByPixelMap [%{public}d]", status);
        return nullptr;
    }
    return obj;
}
} // namespace

void DrawableCreatePixelMapDrawable(
    ani_env* env, [[maybe_unused]] ani_class aniClass, ani_object drawableAni, ani_object pixelAni)
{
    ani_boolean isUndefined;
    env->Reference_IsUndefined(pixelAni, &isUndefined);
    auto* modifier = GetDrawableDescriptorModifier();
    // first create native pixel map drawable descriptor
    auto* drawable = modifier->createDrawableDescriptorByType(static_cast<uint32_t>(DrawableType::PIXELMAP));
    modifier->increaseRef(drawable);
    auto ptr = reinterpret_cast<ani_long>(drawable);
    env->Object_SetPropertyByName_Long(drawableAni, "nativeObj", ptr);
    if (!isUndefined) {
        auto pixelMap = Media::PixelMapTaiheAni::GetNativePixelMap(env, pixelAni);
        modifier->setPixelMapByPixelMap(drawable, &pixelMap);
    }
}

void DrawableCreateLayeredDrawable(ani_env* env, [[maybe_unused]] ani_class aniClass, ani_object drawableAni,
    ani_object foregroundAni, ani_object backgroundAni, ani_object maskAni)
{
    ani_boolean isForegroundUndefined;
    ani_boolean isBackgroundUndefined;
    ani_boolean isMaskUndefined;
    env->Reference_IsUndefined(foregroundAni, &isForegroundUndefined);
    env->Reference_IsUndefined(backgroundAni, &isBackgroundUndefined);
    env->Reference_IsUndefined(maskAni, &isMaskUndefined);
    auto* modifier = GetDrawableDescriptorModifier();
    auto* drawable = modifier->createDrawableDescriptorByType(static_cast<uint32_t>(DrawableType::LAYERED));
    modifier->increaseRef(drawable);
    auto ptr = reinterpret_cast<ani_long>(drawable);
    env->Object_SetPropertyByName_Long(drawableAni, "nativeObj", ptr);
    if (!isForegroundUndefined) {
        auto foreground = Media::PixelMapTaiheAni::GetNativePixelMap(env, foregroundAni);
        modifier->setLayeredForeground(drawable, &foreground);
    }
    if (!isBackgroundUndefined) {
        auto background = Media::PixelMapTaiheAni::GetNativePixelMap(env, backgroundAni);
        modifier->setLayeredBackground(drawable, &background);
    }
    if (!isMaskUndefined) {
        auto mask = Media::PixelMapTaiheAni::GetNativePixelMap(env, maskAni);
        modifier->setLayeredMask(drawable, &mask);
    } else {
        std::unique_ptr<uint8_t[]> maskData;
        size_t maskLen = 0;
        std::shared_ptr<Global::Resource::ResourceManager> resMgr(Global::Resource::CreateResourceManager());
        if (resMgr == nullptr) {
            return;
        }
        auto state = resMgr->GetMediaDataByName(DEFAULT_MASK, maskLen, maskData);
        if (state == Global::Resource::SUCCESS && maskLen > 0) {
            modifier->setMaskData(drawable, maskData.release(), maskLen);
        }
    }
}

void* BindAnimatedDrawableDescriptorNative(ani_env* env, ani_object drawableAni)
{
    auto* modifier = GetDrawableDescriptorModifier();
    CHECK_NULL_RETURN(modifier, nullptr);
    auto* drawable = modifier->createDrawableDescriptorByType(static_cast<uint32_t>(DrawableType::ANIMATED));
    CHECK_NULL_RETURN(drawable, nullptr);
    modifier->increaseRef(drawable);
    auto ptr = reinterpret_cast<ani_long>(drawable);
    auto result = env->Object_SetPropertyByName_Long(drawableAni, "nativeObj", ptr);
    if (result != ANI_OK) {
        modifier->decreaseRef(drawable);
        return nullptr;
    }
    return drawable;
}

void ParseAnimatedOptions(ani_env* env, ani_object optionsAni, void* drawable)
{
    auto* modifier = GetDrawableDescriptorModifier();
    CHECK_NULL_VOID(modifier);
    ani_boolean isDurationUndefined;
    ani_boolean isIterationsUndefined;
    ani_ref durationRef;
    ani_ref iterationsRef;
    env->Object_GetPropertyByName_Ref(optionsAni, "duration", &durationRef);
    env->Object_GetPropertyByName_Ref(optionsAni, "iterations", &iterationsRef);

    ani_object durationAni = static_cast<ani_object>(durationRef);
    ani_object iterationsAni = static_cast<ani_object>(iterationsRef);
    env->Reference_IsUndefined(durationAni, &isDurationUndefined);
    env->Reference_IsUndefined(iterationsAni, &isIterationsUndefined);
    if (!isDurationUndefined) {
        ani_int duration;
        env->Object_CallMethodByName_Int(durationAni, "toInt", ":i", &duration);
        modifier->setAnimatedTotalDuration(drawable, static_cast<int32_t>(duration));
    }
    if (!isIterationsUndefined) {
        ani_int iterations;
        env->Object_CallMethodByName_Int(iterationsAni, "toInt", ":i", &iterations);
        modifier->setAnimatedIterations(drawable, static_cast<int32_t>(iterations));
    }
    std::vector<int32_t> frameDurations;
    if (AniUtils::GetArrayIntParam(env, optionsAni, "frameDurations", frameDurations)) {
        modifier->setAnimatedDurations(drawable, &frameDurations);
    }

    bool autoPlay = false;
    if (AniUtils::GetBoolParam(env, optionsAni, "autoPlay", autoPlay)) {
        modifier->setAnimatedAutoPlay(drawable, autoPlay);
    }
}

void DrawableCreateAnimatedDrawable(ani_env* env, [[maybe_unused]] ani_class aniClass, ani_object drawableAni,
    ani_array pixelmapsAni, ani_object optionsAni)
{
    auto* modifier = GetDrawableDescriptorModifier();
    CHECK_NULL_VOID(modifier);
    auto* drawable = BindAnimatedDrawableDescriptorNative(env, drawableAni);
    CHECK_NULL_VOID(drawable);
    ani_size size;
    ANI_CALL(env, Array_GetLength(pixelmapsAni, &size), { return; });
    std::vector<std::shared_ptr<OHOS::Media::PixelMap>> results;
    ani_class arrayClass;
    ANI_CALL(env, FindClass("std.core.Array", &arrayClass), { return; });
    ani_method getDataMethod;
    ANI_CALL(env, Class_FindMethod(arrayClass, "$_get", ARRAY_GET, &getDataMethod), { return; });
    for (size_t index = 0; index < size; index++) {
        ani_ref pixelmapAni;
        ANI_CALL(env, Object_CallMethod_Ref(pixelmapsAni, getDataMethod, &pixelmapAni, index), { return; });
        auto pixelmap = Media::PixelMapTaiheAni::GetNativePixelMap(env, static_cast<ani_object>(pixelmapAni));
        results.push_back(pixelmap);
    }
    modifier->setPixelMapList(drawable, &results);
    ani_boolean isOptionsUndefined;
    ANI_CALL(env, Reference_IsUndefined(optionsAni, &isOptionsUndefined), { return; });
    if (static_cast<bool>(isOptionsUndefined)) {
        return;
    }
    ParseAnimatedOptions(env, optionsAni, drawable);
}

void DrawableCreateAnimatedDrawableByResource(ani_env* env, [[maybe_unused]] ani_class aniClass, ani_object drawableAni,
    ani_long resourceObjectKPointer, ani_object optionsAni)
{
    auto* drawable = BindAnimatedDrawableDescriptorNative(env, drawableAni);
    CHECK_NULL_VOID(drawable);

    auto* modifier = GetDrawableDescriptorModifier();
    CHECK_NULL_VOID(modifier);
    modifier->setAnimatedResource(drawable, reinterpret_cast<void*>(resourceObjectKPointer));

    ani_boolean isOptionsUndefined;
    ANI_CALL(env, Reference_IsUndefined(optionsAni, &isOptionsUndefined), { return; });
    if (static_cast<bool>(isOptionsUndefined)) {
        return;
    }
    ParseAnimatedOptions(env, optionsAni, drawable);
}

void DrawableCreateAnimatedDrawableByString(ani_env* env, [[maybe_unused]] ani_class aniClass, ani_object drawableAni,
    ani_string resource, ani_object optionsAni)
{
    auto* drawable = BindAnimatedDrawableDescriptorNative(env, drawableAni);
    CHECK_NULL_VOID(drawable);

    auto* modifier = GetDrawableDescriptorModifier();
    CHECK_NULL_VOID(modifier);

    auto src = AniUtils::ANIStringToStdString(env, resource);
    if (!src.empty()) {
        modifier->setAnimatedPath(drawable, src.c_str());
    }

    ani_boolean isOptionsUndefined;
    ANI_CALL(env, Reference_IsUndefined(optionsAni, &isOptionsUndefined), { return; });
    if (static_cast<bool>(isOptionsUndefined)) {
        return;
    }
    ParseAnimatedOptions(env, optionsAni, drawable);
}

ani_object DrawableCreatePixelMap(ani_env* env, [[maybe_unused]] ani_class aniClass, ani_object drawableAni)
{
    ani_long nativeObj = 0;
    env->Object_GetPropertyByName_Long(drawableAni, "nativeObj", &nativeObj);

    auto* modifier = GetDrawableDescriptorModifier();
    CHECK_NULL_RETURN(modifier, nullptr);

    auto* native = reinterpret_cast<void*>(nativeObj);
    CHECK_NULL_RETURN(native, nullptr);

    std::shared_ptr<Media::PixelMap> pixmap;
    modifier->getPixelMap(native, &pixmap);

    if (pixmap == nullptr) {
        return nullptr;
    }
    // set pixel map property to arkts object
    auto pixelAni = Media::PixelMapTaiheAni::CreateEtsPixelMap(env, pixmap);
    return pixelAni;
}

ani_object DrawableCreateForeground(ani_env* env, [[maybe_unused]] ani_class aniClass, ani_object drawableAni)
{
    ani_long nativeObj = 0;
    env->Object_GetPropertyByName_Long(drawableAni, "nativeObj", &nativeObj);

    auto* modifier = GetDrawableDescriptorModifier();
    CHECK_NULL_RETURN(modifier, nullptr);

    auto* native = reinterpret_cast<void*>(nativeObj);
    CHECK_NULL_RETURN(native, nullptr);

    std::shared_ptr<Media::PixelMap> pixmap;
    modifier->getForegroundPixelMap(native, &pixmap);

    if (pixmap == nullptr) {
        return nullptr;
    }
    auto obj = CreatePixelMapDrawableByPixelMap(env, pixmap);
    return obj;
}

ani_object DrawableCreateBackground(ani_env* env, [[maybe_unused]] ani_class aniClass, ani_object drawableAni)
{
    ani_long nativeObj = 0;
    env->Object_GetPropertyByName_Long(drawableAni, "nativeObj", &nativeObj);

    auto* modifier = GetDrawableDescriptorModifier();
    CHECK_NULL_RETURN(modifier, nullptr);

    auto* native = reinterpret_cast<void*>(nativeObj);
    CHECK_NULL_RETURN(native, nullptr);

    std::shared_ptr<Media::PixelMap> pixmap;
    modifier->getBackgroundPixelMap(native, &pixmap);

    if (pixmap == nullptr) {
        return nullptr;
    }
    auto obj = CreatePixelMapDrawableByPixelMap(env, pixmap);
    return obj;
}

ani_object DrawableCreateMask(ani_env* env, [[maybe_unused]] ani_class aniClass, ani_object drawableAni)
{
    ani_long nativeObj = 0;
    env->Object_GetPropertyByName_Long(drawableAni, "nativeObj", &nativeObj);

    auto* modifier = GetDrawableDescriptorModifier();
    CHECK_NULL_RETURN(modifier, nullptr);

    auto* native = reinterpret_cast<void*>(nativeObj);
    CHECK_NULL_RETURN(native, nullptr);

    std::shared_ptr<Media::PixelMap> pixmap;
    modifier->getMaskPixelMap(native, &pixmap);

    if (pixmap == nullptr) {
        return nullptr;
    }
    auto obj = CreatePixelMapDrawableByPixelMap(env, pixmap);
    return obj;
}

ani_string DrawableGetMaskClipPath(ani_env* env)
{
    std::string data;
    std::shared_ptr<Global::Resource::ResourceManager> resMgr(Global::Resource::CreateResourceManager());
    if (resMgr == nullptr) {
        ani_string aniString {};
        return aniString;
    }
    resMgr->GetStringByName("ohos_drawable_descriptor_path", data);
    ani_string aniString {};
    env->String_NewUTF8(data.c_str(), data.size(), &aniString);
    return aniString;
}

ani_object DrawableLoadSync(ani_env* env, [[maybe_unused]] ani_class aniClass, ani_object drawableAni)
{
    ani_object retValue = nullptr;
    auto* retValueRef = static_cast<ani_ref>(retValue);
    ANI_CALL(env, GetUndefined(&retValueRef), return nullptr);

    ani_long nativeObj = 0;
    ANI_CALL(env, Object_GetPropertyByName_Long(drawableAni, "nativeObj", &nativeObj), return retValue);

    auto* modifier = GetDrawableDescriptorModifier();
    CHECK_NULL_RETURN(modifier, nullptr);

    auto* native = reinterpret_cast<void*>(nativeObj);
    CHECK_NULL_RETURN(native, nullptr);

    auto drawableType = DrawableType(modifier->getDrawableType(native));
    switch (drawableType) {
        case DrawableType::BASE:
        case DrawableType::LAYERED:
        case DrawableType::PIXELMAP:
            break;
        case DrawableType::ANIMATED: {
            int32_t width = 0;
            int32_t height = 0;
            int32_t errorCode = -1;
            modifier->loadSyncAnimated(native, &width, &height, &errorCode);
            if (errorCode == 0) {
                retValue = CreateDrawableDescriptorLoadedResult(env, width, height);
            } else {
                ani_error error =
                    AniUtils::GetErrorObject(env, "resource loading failed.", errorCode, "AceDrawableDescriptor");
                env->ThrowError(error);
            }
            break;
        }
        default:
            break;
    }
    return retValue;
}

ani_object DrawableLoad(ani_env* env, [[maybe_unused]] ani_class aniClass, ani_object drawableAni)
{
    ani_object retValue = nullptr;
    auto* retValueRef = static_cast<ani_ref>(retValue);
    ANI_CALL(env, GetUndefined(&retValueRef), return nullptr);

    ani_long nativeObj = 0;
    ANI_CALL(env, Object_GetPropertyByName_Long(drawableAni, "nativeObj", &nativeObj), return retValue);

    auto* modifier = GetDrawableDescriptorModifier();
    CHECK_NULL_RETURN(modifier, nullptr);

    auto* native = reinterpret_cast<void*>(nativeObj);
    CHECK_NULL_RETURN(native, nullptr);

    auto drawableType = DrawableType(modifier->getDrawableType(native));
    switch (drawableType) {
        case DrawableType::BASE:
        case DrawableType::LAYERED:
        case DrawableType::PIXELMAP:
            break;
        case DrawableType::ANIMATED: {
            ArkUIDrawableAsync asyncCtx;
            CreateDrawableLoadCallback(env, asyncCtx, &retValue);
            modifier->loadAsyncAnimated(native, asyncCtx);
            break;
        }
        default:
            break;
    }

    return retValue;
}

ani_object DrawableGetAnimationController(
    ani_env* env, [[maybe_unused]] ani_class aniClass, ani_object AnimatedDrawable, [[maybe_unused]] ani_string id)
{
    ani_object retValue = nullptr;
    auto* retValueRef = static_cast<ani_ref>(retValue);
    ANI_CALL(env, GetUndefined(&retValueRef), return nullptr);

    ani_boolean isIdUndefined;
    ANI_CALL(env, Reference_IsUndefined(id, &isIdUndefined), return retValue);
    std::string componentId {};
    if (!(static_cast<bool>(isIdUndefined))) {
        componentId = AniUtils::ANIStringToStdString(env, id);
    }

    ani_long nativeObj = 0;
    ANI_CALL(env, Object_GetPropertyByName_Long(AnimatedDrawable, "nativeObj", &nativeObj), return retValue);

    auto* modifier = GetDrawableDescriptorModifier();
    CHECK_NULL_RETURN(modifier, nullptr);

    auto* native = reinterpret_cast<void*>(nativeObj);
    CHECK_NULL_RETURN(native, nullptr);

    auto* animationControllerRaw = modifier->getAnimatedController(native, componentId.c_str());

    ani_class cls;
    if (ANI_OK != env->FindClass(ANIMATION_CONTROLLER_INNER, &cls)) {
        HILOGI("AceDrawableDescriptor [ANI] find class fail");
        return retValue;
    }

    ani_method ctor;
    if (ANI_OK != env->Class_FindMethod(cls, "<ctor>", "l:", &ctor)) {
        HILOGI("AceDrawableDescriptor [ANI] find method fail");
        return retValue;
    }

    if (ANI_OK != env->Object_New(cls, ctor, &retValue, reinterpret_cast<ani_long>(animationControllerRaw))) {
        HILOGI("AceDrawableDescriptor [ANI] create animatorResult fail");
        return retValue;
    }

    return retValue;
}

DrawableType GetDrawableType(ani_env* env, ani_string typeName)
{
    char typeNameValue[MAX_TYPENAME_LEN] = {};
    ani_size typeNameLen = 0;
    env->String_GetUTF8(typeName, typeNameValue, sizeof(typeNameValue), &typeNameLen);
    std::string typeNameStr(typeNameValue, typeNameLen);

    auto drawableType = DrawableType::BASE;

    if (typeNameStr == DRAWABLE_DESCRIPTOR_NAME) {
        drawableType = DrawableType::BASE;
    } else if (typeNameStr == LAYERED_DRAWABLE_DESCRIPTOR_NAME) {
        drawableType = DrawableType::LAYERED;
    } else if (typeNameStr == ANIMATED_DRAWABLE_DESCRIPTOR_NAME) {
        drawableType = DrawableType::ANIMATED;
    } else if (typeNameStr == PIXELMAP_DRAWABLE_DESCRIPTOR_NAME) {
        drawableType = DrawableType::PIXELMAP;
    }
    return drawableType;
}

ani_object CreateDrawableByNapiType(ani_env* env, DrawableType drawableType, void* unwrapResult)
{
    ani_object retValue = nullptr;
    auto napiDrawable = reinterpret_cast<Napi::DrawableDescriptor*>(unwrapResult);

    switch (drawableType) {
        case DrawableType::LAYERED: {
            auto layered = static_cast<Napi::LayeredDrawableDescriptor*>(napiDrawable);
            if (layered == nullptr) {
                return nullptr;
            }
            auto foreground = layered->GetForeground();
            auto background = layered->GetBackground();
            auto mask = layered->GetMask();
            auto ptrForeground = (foreground && foreground->GetPixelMap()) ? foreground->GetPixelMap() : nullptr;
            auto ptrBackground = (background && background->GetPixelMap()) ? background->GetPixelMap() : nullptr;
            auto ptrMask = (mask && mask->GetPixelMap()) ? mask->GetPixelMap() : nullptr;

            retValue = CreateLayeredDrawableByPixelMap(env, ptrForeground, ptrBackground, ptrMask);
            break;
        }
        case DrawableType::PIXELMAP: {
            auto pixelMap = static_cast<Napi::DrawableDescriptor*>(napiDrawable);
            if (pixelMap == nullptr || pixelMap->GetPixelMap() == nullptr) {
                return nullptr;
            }
            retValue = CreatePixelMapDrawableByPixelMap(env, pixelMap->GetPixelMap());
            break;
        }
        default:
            break;
    }
    return retValue;
}

void DrawableSetBlendMode(
    ani_env* env, [[maybe_unused]] ani_class aniClass, ani_object drawableAni, ani_enum_item blendMode)
{
    ani_long nativeObj = 0;
    env->Object_GetPropertyByName_Long(drawableAni, "nativeObj", &nativeObj);

    auto* modifier = GetDrawableDescriptorModifier();
    CHECK_NULL_VOID(modifier);

    auto* native = reinterpret_cast<void*>(nativeObj);
    CHECK_NULL_VOID(native);

    ani_boolean isUndefined;
    env->Reference_IsUndefined(blendMode, &isUndefined);
    ani_int mode = -1;
    if (isUndefined) {
        return;
    }
    if (ANI_OK != env->EnumItem_GetValue_Int(blendMode, &mode)) {
        return;
    }

    modifier->setBlendMode(native, static_cast<int32_t>(mode));
}

ani_object DrawableNativeTransferStatic(
    ani_env* env, [[maybe_unused]] ani_class aniClass, ani_object input, ani_string typeName)
{
    auto drawableType = GetDrawableType(env, typeName);

    void* unwrapResult = nullptr;
    if (!arkts_esvalue_unwrap(env, input, &unwrapResult) || unwrapResult == nullptr) {
        return nullptr;
    }
    ani_object retValue = nullptr;
    if (drawableType == DrawableType::ANIMATED) {
        auto* modifier = GetDrawableDescriptorModifier();
        CHECK_NULL_RETURN(modifier, nullptr);
        auto* native = reinterpret_cast<void*>(unwrapResult);
        CHECK_NULL_RETURN(native, nullptr);
        std::vector<std::shared_ptr<OHOS::Media::PixelMap>> pixelMapList;
        modifier->getAnimatedPixelMaps(native, &pixelMapList);
        retValue = CreateAnimatedDrawableByPixelMapList(
            env, pixelMapList, modifier->getAnimatedDuration(native), modifier->getAnimatedIterations(native));
    } else {
        retValue = CreateDrawableByNapiType(env, drawableType, unwrapResult);
    }
    return retValue;
}
void DrawableDestructDrawable([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_class aniClass, ani_long pointer)
{
    if (pointer == 0) {
        return;
    }

    auto* modifier = GetDrawableDescriptorModifier();
    CHECK_NULL_VOID(modifier);
    auto* native = reinterpret_cast<void*>(pointer);
    CHECK_NULL_VOID(native);
    modifier->decreaseRef(native);
}

void* GetAnimationControllerNative(ani_env* env, ani_object animationController)
{
    ani_boolean isUndefined;
    env->Reference_IsUndefined(animationController, &isUndefined);
    if (static_cast<bool>(isUndefined)) {
        return nullptr;
    }
    ani_long nativeObj = 0;
    ANI_CALL(env, Object_GetFieldByName_Long(animationController, "nativeObj", &nativeObj), return nullptr);
    if (nativeObj == 0) {
        return nullptr;
    }
    auto* controlledAnimator = reinterpret_cast<void*>(nativeObj);
    return controlledAnimator;
}

void DrawableAnimationControllerStart(ani_env* env, [[maybe_unused]] ani_class aniClass, ani_object animationController)
{
    auto* controlledAnimator = GetAnimationControllerNative(env, animationController);
    if (controlledAnimator == nullptr) {
        return;
    }
    auto* modifier = GetDrawableDescriptorModifier();
    CHECK_NULL_VOID(modifier);
    modifier->startAnimated(controlledAnimator);
}

void DrawableAnimationControllerStop(ani_env* env, [[maybe_unused]] ani_class aniClass, ani_object animationController)
{
    auto* controlledAnimator = GetAnimationControllerNative(env, animationController);
    if (controlledAnimator == nullptr) {
        return;
    }
    auto* modifier = GetDrawableDescriptorModifier();
    CHECK_NULL_VOID(modifier);
    modifier->stopAnimated(controlledAnimator);
}

void DrawableAnimationControllerPause(ani_env* env, [[maybe_unused]] ani_class aniClass, ani_object animationController)
{
    auto* controlledAnimator = GetAnimationControllerNative(env, animationController);
    if (controlledAnimator == nullptr) {
        return;
    }
    auto* modifier = GetDrawableDescriptorModifier();
    CHECK_NULL_VOID(modifier);
    modifier->pauseAnimated(controlledAnimator);
}

void DrawableAnimationControllerResume(
    ani_env* env, [[maybe_unused]] ani_class aniClass, ani_object animationController)
{
    auto* controlledAnimator = GetAnimationControllerNative(env, animationController);
    if (controlledAnimator == nullptr) {
        return;
    }
    auto* modifier = GetDrawableDescriptorModifier();
    CHECK_NULL_VOID(modifier);
    modifier->resumeAnimated(controlledAnimator);
}

ani_enum_item DrawableAnimationControllerGetStatus(
    ani_env* env, [[maybe_unused]] ani_class aniClass, ani_object animationController)
{
    auto* controlledAnimator = GetAnimationControllerNative(env, animationController);
    if (controlledAnimator == nullptr) {
        return nullptr;
    }
    auto* modifier = GetDrawableDescriptorModifier();
    CHECK_NULL_RETURN(modifier, nullptr);
    auto status = ControlStatus(modifier->getAnimatedStatus(controlledAnimator));

    ani_enum animationStatus;
    if (env->FindEnum("arkui.component.enums.AnimationStatus", &animationStatus) != ANI_OK) {
        return nullptr;
    }

    ani_enum_item animationStatusItem = nullptr;
    switch (status) {
        case ControlStatus::IDLE: {
            if (env->Enum_GetEnumItemByName(animationStatus, "Initial", &animationStatusItem) != ANI_OK) {
                HILOGI("AceDrawableDescriptor [ANI] GetEnumItem fail");
            }
            break;
        }
        case ControlStatus::RUNNING: {
            if (env->Enum_GetEnumItemByName(animationStatus, "Running", &animationStatusItem) != ANI_OK) {
                HILOGI("AceDrawableDescriptor [ANI] GetEnumItem fail");
            }
            break;
        }
        case ControlStatus::PAUSED: {
            if (env->Enum_GetEnumItemByName(animationStatus, "Paused", &animationStatusItem) != ANI_OK) {
                HILOGI("AceDrawableDescriptor [ANI] GetEnumItem fail");
            }
            break;
        }
        case ControlStatus::STOPPED: {
            if (env->Enum_GetEnumItemByName(animationStatus, "Stopped", &animationStatusItem) != ANI_OK) {
                HILOGI("AceDrawableDescriptor [ANI] GetEnumItem fail");
            }
            break;
        }
        default:
            break;
    }
    return animationStatusItem;
}
} // namespace OHOS::Ace::Ani