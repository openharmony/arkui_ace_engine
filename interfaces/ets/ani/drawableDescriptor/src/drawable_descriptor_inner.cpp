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

#include <memory>

#include "draw/canvas.h"
#include "drawableDescriptor_utils.h"
#include "image/bitmap.h"
#include "image/image_info.h"
#include "interfaces/inner_api/drawable_descriptor/drawable_descriptor.h"
#include "interop_js/arkts_esvalue.h"
#include "pixel_map_taihe_ani.h"
#include "resource_manager.h"
#include "securec.h"

#include "base/image/pixel_map.h"
#include "base/log/log.h"
#include "core/common/ace_engine.h"
#include "core/drawable/animated_drawable_descriptor.h"
#include "core/drawable/layered_drawable_descriptor.h"
#include "core/drawable/pixel_map_drawable_descriptor.h"
#include "frameworks/base/error/error_code.h"

namespace OHOS::Ace::Ani {
namespace {
constexpr char PIXEL_MAP_CONSTRUCTOR[] = "C{@ohos.multimedia.image.image.PixelMap}:";
constexpr char PIXEL_MAP_DRAWABLE[] = "@ohos.arkui.drawableDescriptor.PixelMapDrawableDescriptor";
constexpr char ARRAY_GET[] = "i:C{std.core.Object}";
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

enum class DrawableType {
    BASE,
    LAYERED,
    ANIMATED,
    PIXELMAP,
};

ani_object CreatePixelMapDrawableByPixelMap(ani_env* env, const RefPtr<PixelMap>& pixelMap)
{
    auto pixelAni = Media::PixelMapTaiheAni::CreateEtsPixelMap(env, pixelMap->GetPixelMapSharedPtr());
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

static void HandleDrawableDescriptorLoadResult(std::shared_ptr<OHOS::Ace::Ani::DrawableAsyncContext> asyncContext,
    OHOS::Ace::DrawableDescriptorLoadResult loadResult)
{
    CHECK_NULL_VOID((asyncContext && asyncContext->deferred && asyncContext->vm));
    ani_env* env = nullptr;
    ani_status status = asyncContext->vm->GetEnv(ANI_VERSION_1, &env);
    if (status != ANI_OK || env == nullptr) {
        return;
    }
    ani_size nrRefs = SPECIFIED_CAPACITY;
    ANI_CALL(env, CreateLocalScope(nrRefs), return);
    if (loadResult.errorCode == 0) {
        ani_object drawableDescriptorLoadedResult =
            CreateDrawableDescriptorLoadedResult(env, loadResult.imageWidth_, loadResult.imageHeight_);
        ani_ref drawableDescriptorLoadedResultRef = static_cast<ani_ref>(drawableDescriptorLoadedResult);
        status = env->PromiseResolver_Resolve(asyncContext->deferred, drawableDescriptorLoadedResultRef);
        if (status != ANI_OK) {
            TAG_LOGW(OHOS::Ace::AceLogTag::ACE_DRAWABLE_DESCRIPTOR,
                "[ANI] PromiseResolver_Resolve fail. status: %{public}d", status);
        }
    } else {
        int32_t errorCode = OHOS::Ace::ERROR_CODE_DRAWABLE_LOADER_ERROR;
        ani_error error = OHOS::Ace::Ani::GetErrorObject(env, "resource loading failed.", errorCode);
        status = env->PromiseResolver_Reject(asyncContext->deferred, error);
        if (status != ANI_OK) {
            TAG_LOGW(OHOS::Ace::AceLogTag::ACE_DRAWABLE_DESCRIPTOR,
                "[ANI] PromiseResolver_Reject fail. status: %{public}d", status);
        }
    }
    status = env->DestroyLocalScope();
    if (status != ANI_OK) {
        TAG_LOGW(OHOS::Ace::AceLogTag::ACE_DRAWABLE_DESCRIPTOR,
            "[ANI] DestroyLocalScope fail. status: %{public}d", status);
    }
}

OHOS::Ace::DrawableDescriptor::LoadCallback CreateDrawableLoadCallback(ani_env* env, ani_object* result)
{
    auto asyncContext = std::make_shared<DrawableAsyncContext>();
    ANI_CALL(env, GetVM(&asyncContext->vm), return nullptr);
    asyncContext->instanceId = OHOS::Ace::Container::CurrentIdSafely();
    ANI_CALL(env, Promise_New(&asyncContext->deferred, result), return nullptr)
    auto callback = [asyncContext](DrawableDescriptorLoadResult loadResult) mutable {
        CHECK_NULL_VOID(asyncContext);
        auto container = OHOS::Ace::AceEngine::Get().GetContainer(asyncContext->instanceId);
        CHECK_NULL_VOID(container);
        auto taskExecutor = container->GetTaskExecutor();
        CHECK_NULL_VOID(taskExecutor);
        auto task = [asyncContext, loadResult]() {
            HandleDrawableDescriptorLoadResult(asyncContext, loadResult);
        };
        taskExecutor->PostTask(
            std::move(task), OHOS::Ace::TaskExecutor::TaskType::JS, "ArkUIDrawableParseLoadedResultCallback");
    };
    return callback;
}

ani_object LoadSync(ani_env* env, [[maybe_unused]] ani_class aniClass, ani_object drawableAni)
{
    ani_object retValue = nullptr;
    auto* retValueRef = static_cast<ani_ref>(retValue);
    ANI_CALL(env, GetUndefined(&retValueRef), return nullptr);

    ani_long nativeObj = 0;
    ANI_CALL(env, Object_GetPropertyByName_Long(drawableAni, "nativeObj", &nativeObj), return retValue);

    auto* drawableDescriptor = reinterpret_cast<DrawableDescriptor*>(nativeObj);
    if (drawableDescriptor == nullptr) {
        return retValue;
    }
    switch (drawableDescriptor->GetDrawableType()) {
        case OHOS::Ace::DrawableType::BASE:
        case OHOS::Ace::DrawableType::LAYERED:
        case OHOS::Ace::DrawableType::PIXELMAP:
            break;
        case OHOS::Ace::DrawableType::ANIMATED: {
            auto* animatedDrawable = static_cast<AnimatedDrawableDescriptor*>(drawableDescriptor);
            if (animatedDrawable == nullptr) {
                return nullptr;
            }
            auto drawableDescriptorLoadResult = animatedDrawable->LoadSync();
            if (drawableDescriptorLoadResult.errorCode == 0) {
                retValue = CreateDrawableDescriptorLoadedResult(
                    env, drawableDescriptorLoadResult.imageWidth_, drawableDescriptorLoadResult.imageHeight_);
            }
            break;
        }
        default:
            break;
    }
    return retValue;
}

ani_object Load(ani_env* env, [[maybe_unused]] ani_class aniClass, ani_object drawableAni)
{
    ani_object retValue = nullptr;
    auto* retValueRef = static_cast<ani_ref>(retValue);
    ANI_CALL(env, GetUndefined(&retValueRef), return nullptr);

    ani_long nativeObj = 0;
    ANI_CALL(env, Object_GetPropertyByName_Long(drawableAni, "nativeObj", &nativeObj), return retValue);

    auto* drawableDescriptor = reinterpret_cast<DrawableDescriptor*>(nativeObj);
    if (drawableDescriptor == nullptr) {
        return retValue;
    }

    switch (drawableDescriptor->GetDrawableType()) {
        case OHOS::Ace::DrawableType::BASE:
        case OHOS::Ace::DrawableType::LAYERED:
        case OHOS::Ace::DrawableType::PIXELMAP:
            break;
        case OHOS::Ace::DrawableType::ANIMATED: {
            auto* animatedDrawable = static_cast<AnimatedDrawableDescriptor*>(drawableDescriptor);
            if (animatedDrawable == nullptr) {
                break;
            }
            auto callBack = CreateDrawableLoadCallback(env, &retValue);
            if (callBack != nullptr) {
                animatedDrawable->LoadAsync(std::move(callBack));
            }
            break;
        }
        default:
            break;
    }

    return retValue;
}

ani_object GetAnimationController(
    ani_env* env, [[maybe_unused]] ani_class aniClass, ani_object AnimatedDrawable, [[maybe_unused]] ani_string id)
{
    ani_object retValue = nullptr;
    auto* retValueRef = static_cast<ani_ref>(retValue);
    ANI_CALL(env, GetUndefined(&retValueRef), return nullptr);

    ani_boolean isIdUndefined;
    ANI_CALL(env, Reference_IsUndefined(id, &isIdUndefined), return retValue);
    std::string componentId {};
    if (!(static_cast<bool>(isIdUndefined))) {
        componentId = ANIStringToStdString(env, id);
    }

    ani_long nativeObj = 0;
    ANI_CALL(env, Object_GetPropertyByName_Long(AnimatedDrawable, "nativeObj", &nativeObj), return retValue);

    auto* animatedDrawableDescriptor = reinterpret_cast<AnimatedDrawableDescriptor*>(nativeObj);
    if (animatedDrawableDescriptor == nullptr) {
        return retValue;
    }
    auto animationController = animatedDrawableDescriptor->GetControlledAnimator(componentId);
    if (!animationController) {
        return retValue;
    }

    auto* animationControllerRaw = AceType::RawPtr(animationController);

    ani_class cls;
    if (ANI_OK != env->FindClass(ANIMATION_CONTROLLER_INNER, &cls)) {
        TAG_LOGI(AceLogTag::ACE_DRAWABLE_DESCRIPTOR, "[ANI] find class fail");
        return retValue;
    }

    ani_method ctor;
    if (ANI_OK != env->Class_FindMethod(cls, "<ctor>", "l:", &ctor)) {
        TAG_LOGI(AceLogTag::ACE_DRAWABLE_DESCRIPTOR, "[ANI] find method fail");
        return retValue;
    }

    if (ANI_OK != env->Object_New(cls, ctor, &retValue, reinterpret_cast<ani_long>(animationControllerRaw))) {
        TAG_LOGI(AceLogTag::ACE_DRAWABLE_DESCRIPTOR, "[ANI] create animatorResult fail");
        return retValue;
    }

    return retValue;
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

    auto* durationAni = CreateANIDoubleObject(env, duration);
    auto* iterationsAni = CreateANIDoubleObject(env, iterations);

    env->Object_New(cls, ctor, &optionsAni);

    env->Object_SetPropertyByName_Ref(optionsAni, "duration", durationAni);
    env->Object_SetPropertyByName_Ref(optionsAni, "iterations", iterationsAni);

    ani_array pixelMapsAni;
    auto refPixelMap = PixelMap::Create(pixelMapList[0]);

    auto init = Media::PixelMapTaiheAni::CreateEtsPixelMap(env, refPixelMap->GetPixelMapSharedPtr());
    env->Array_New(pixelMapList.size(), init, &pixelMapsAni);

    for (size_t index = 1; index < pixelMapList.size(); index++) {
        auto refPixel = PixelMap::Create(pixelMapList[index]);
        auto pixelAni = Media::PixelMapTaiheAni::CreateEtsPixelMap(env, refPixel->GetPixelMapSharedPtr());
        env->Array_Set(pixelMapsAni, index, pixelAni);
    }

    env->FindClass(ANIMATED_DRAWABLE, &cls);

    ani_object obj {};
    env->Class_FindMethod(cls, "<ctor>", ANIMATED_CONSTRUCTOR, &ctor);
    env->Object_New(cls, ctor, &obj, pixelMapsAni, optionsAni);
    return obj;
}

ani_object CreateLayeredDrawableByPixelMap(
    ani_env* env, const RefPtr<PixelMap>& foreground, const RefPtr<PixelMap>& background, const RefPtr<PixelMap>& mask)
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
        LOGE("CreateLayeredDrawableByPixelMap [%{public}d]", status);
        return nullptr;
    }
    return obj;
}
} // namespace

void CreatePixelMapDrawable(
    ani_env* env, [[maybe_unused]] ani_class aniClass, ani_object drawableAni, ani_object pixelAni)
{
    ani_boolean isUndefined;
    env->Reference_IsUndefined(pixelAni, &isUndefined);
    // first create native pixel map drawable descriptor
    auto* drawable = new PixelMapDrawableDescriptor();
    drawable->IncRefCount();
    auto ptr = reinterpret_cast<ani_long>(drawable);
    env->Object_SetPropertyByName_Long(drawableAni, "nativeObj", ptr);
    if (!isUndefined) {
        auto pixelMap = Media::PixelMapTaiheAni::GetNativePixelMap(env, pixelAni);
        drawable->SetPixelMap(PixelMap::Create(pixelMap));
    }
}

void CreateLayeredDrawable(ani_env* env, [[maybe_unused]] ani_class aniClass, ani_object drawableAni,
    ani_object foregroundAni, ani_object backgroundAni, ani_object maskAni)
{
    ani_boolean isForegroundUndefined;
    ani_boolean isBackgroundUndefined;
    ani_boolean isMaskUndefined;
    env->Reference_IsUndefined(foregroundAni, &isForegroundUndefined);
    env->Reference_IsUndefined(backgroundAni, &isBackgroundUndefined);
    env->Reference_IsUndefined(maskAni, &isMaskUndefined);
    auto* drawable = new LayeredDrawableDescriptor();
    drawable->IncRefCount();
    auto ptr = reinterpret_cast<ani_long>(drawable);
    env->Object_SetPropertyByName_Long(drawableAni, "nativeObj", ptr);
    if (!isForegroundUndefined) {
        auto foreground = Media::PixelMapTaiheAni::GetNativePixelMap(env, foregroundAni);
        drawable->SetForeground(PixelMap::Create(foreground));
    }
    if (!isBackgroundUndefined) {
        auto background = Media::PixelMapTaiheAni::GetNativePixelMap(env, backgroundAni);
        drawable->SetBackground(PixelMap::Create(background));
    }
    if (!isMaskUndefined) {
        auto mask = Media::PixelMapTaiheAni::GetNativePixelMap(env, maskAni);
        drawable->SetMask(PixelMap::Create(mask));
    } else {
        std::unique_ptr<uint8_t[]> maskData;
        size_t maskLen = 0;
        std::shared_ptr<Global::Resource::ResourceManager> resMgr(Global::Resource::CreateResourceManager());
        auto state = resMgr->GetMediaDataByName(DEFAULT_MASK, maskLen, maskData);
        if (state == Global::Resource::SUCCESS && maskLen > 0) {
            drawable->SetMaskData(maskData.release(), maskLen);
        }
    }
}

AnimatedDrawableDescriptor* BindAnimatedDrawableDescriptorNative(ani_env* env, ani_object drawableAni)
{
    auto* drawable = new AnimatedDrawableDescriptor();
    CHECK_NULL_RETURN(drawable, nullptr);
    drawable->IncRefCount();
    auto ptr = reinterpret_cast<ani_long>(drawable);
    auto result = env->Object_SetPropertyByName_Long(drawableAni, "nativeObj", ptr);
    if (result != ANI_OK) {
        drawable->DecRefCount();
        return nullptr;
    }
    return drawable;
}

void ParseAnimatedOptions(ani_env* env, ani_object optionsAni, AnimatedDrawableDescriptor* drawable)
{
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
        drawable->SetTotalDuration(static_cast<int32_t>(duration));
    }
    if (!isIterationsUndefined) {
        ani_int iterations;
        env->Object_CallMethodByName_Int(iterationsAni, "toInt", ":i", &iterations);
        drawable->SetIterations(static_cast<int32_t>(iterations));
    }
    std::vector<int32_t> frameDurations;
    if (GetArrayIntParam(env, optionsAni, "frameDurations", frameDurations)) {
        drawable->SetDurations(frameDurations);
    }

    bool autoPlay = false;
    if (GetBoolParam(env, optionsAni, "autoPlay", autoPlay)) {
        drawable->SetAutoPlay(autoPlay);
    }
}

void CreateAnimatedDrawable(ani_env* env, [[maybe_unused]] ani_class aniClass, ani_object drawableAni,
    ani_array pixelmapsAni, ani_object optionsAni)
{
    auto* drawable = BindAnimatedDrawableDescriptorNative(env, drawableAni);
    CHECK_NULL_VOID(drawable);
    ani_size size;
    ANI_CALL(env, Array_GetLength(pixelmapsAni, &size), return);
    std::vector<RefPtr<PixelMap>> results;
    ani_class arrayClass;
    ANI_CALL(env, FindClass("std.core.Array", &arrayClass), return);
    ani_method getDataMethod;
    ANI_CALL(env, Class_FindMethod(arrayClass, "$_get", ARRAY_GET, &getDataMethod), return);
    for (size_t index = 0; index < size; index++) {
        ani_ref pixelmapAni;
        ANI_CALL(env, Object_CallMethod_Ref(pixelmapsAni, getDataMethod, &pixelmapAni, index), return);
        auto pixelmap = Media::PixelMapTaiheAni::GetNativePixelMap(env, static_cast<ani_object>(pixelmapAni));
        results.push_back(PixelMap::Create(pixelmap));
    }
    drawable->SetPixelMapList(results);
    ani_boolean isOptionsUndefined;
    ANI_CALL(env, Reference_IsUndefined(optionsAni, &isOptionsUndefined), return);
    if (static_cast<bool>(isOptionsUndefined)) {
        return;
    }
    ParseAnimatedOptions(env, optionsAni, drawable);
}

void CreateAnimatedDrawableByResource(ani_env* env, [[maybe_unused]] ani_class aniClass, ani_object drawableAni,
    ani_object resource, ani_object optionsAni)
{
    auto* drawable = BindAnimatedDrawableDescriptorNative(env, drawableAni);
    CHECK_NULL_VOID(drawable);
    ResourceObjectInfo result;
    GetResourceParam(env, resource, result);

    auto resourceRef = AceType::MakeRefPtr<ResourceObject>(result.resId, result.type, result.params,
        result.bundleName.value_or(""), result.moduleName.value_or(""), Container::CurrentIdSafely());
    auto info = AceType::MakeRefPtr<DrawableDescriptorInfo>(resourceRef);
    drawable->SetDrawableDescriptorInfo(info);

    ani_boolean isOptionsUndefined;
    ANI_CALL(env, Reference_IsUndefined(optionsAni, &isOptionsUndefined), return);
    if (static_cast<bool>(isOptionsUndefined)) {
        return;
    }
    ParseAnimatedOptions(env, optionsAni, drawable);
}

void CreateAnimatedDrawableByString(ani_env* env, [[maybe_unused]] ani_class aniClass, ani_object drawableAni,
    ani_string resource, ani_object optionsAni)
{
    auto* drawable = BindAnimatedDrawableDescriptorNative(env, drawableAni);
    CHECK_NULL_VOID(drawable);

    auto src = ANIStringToStdString(env, resource);
    if (!src.empty()) {
        auto info = AceType::MakeRefPtr<DrawableDescriptorInfo>(src);
        drawable->SetDrawableDescriptorInfo(info);
    }

    ani_boolean isOptionsUndefined;
    ANI_CALL(env, Reference_IsUndefined(optionsAni, &isOptionsUndefined), return);
    if (static_cast<bool>(isOptionsUndefined)) {
        return;
    }
    ParseAnimatedOptions(env, optionsAni, drawable);
}

ani_object CreatePixelMap(ani_env* env, [[maybe_unused]] ani_class aniClass, ani_object drawableAni)
{
    ani_long nativeObj = 0;
    env->Object_GetPropertyByName_Long(drawableAni, "nativeObj", &nativeObj);
    auto* drawableDescriptor = reinterpret_cast<DrawableDescriptor*>(nativeObj);
    if (drawableDescriptor == nullptr) {
        return nullptr;
    }
    auto pixelMap = drawableDescriptor->GetPixelMap();
    if (pixelMap == nullptr) {
        return nullptr;
    }
    // set pixel map property to arkts object
    auto pixelAni = Media::PixelMapTaiheAni::CreateEtsPixelMap(env, pixelMap->GetPixelMapSharedPtr());
    return pixelAni;
}

ani_object ComposePixelMap(ani_env* env, [[maybe_unused]] ani_class aniClass, ani_object drawableAni)
{
    ani_long nativeObj = 0;
    env->Object_GetPropertyByName_Long(drawableAni, "nativeObj", &nativeObj);
    auto* layeredDrawable = reinterpret_cast<LayeredDrawableDescriptor*>(nativeObj);
    if (layeredDrawable == nullptr) {
        return nullptr;
    }
    auto pixelMap = layeredDrawable->GetPixelMap();
    if (pixelMap == nullptr) {
        return nullptr;
    }
    // set pixel map property to arkts object
    auto pixelAni = Media::PixelMapTaiheAni::CreateEtsPixelMap(env, pixelMap->GetPixelMapSharedPtr());
    return pixelAni;
}

ani_object CreateForefround(ani_env* env, [[maybe_unused]] ani_class aniClass, ani_object drawableAni)
{
    ani_long nativeObj = 0;
    env->Object_GetPropertyByName_Long(drawableAni, "nativeObj", &nativeObj);
    auto* layeredDrawable = reinterpret_cast<LayeredDrawableDescriptor*>(nativeObj);
    if (layeredDrawable == nullptr) {
        return nullptr;
    }
    auto foreground = layeredDrawable->GetForeground();
    if (foreground == nullptr) {
        return nullptr;
    }
    auto obj = CreatePixelMapDrawableByPixelMap(env, foreground);
    return obj;
}

ani_object CreateBackground(ani_env* env, [[maybe_unused]] ani_class aniClass, ani_object drawableAni)
{
    ani_long nativeObj = 0;
    env->Object_GetPropertyByName_Long(drawableAni, "nativeObj", &nativeObj);
    auto* layeredDrawable = reinterpret_cast<LayeredDrawableDescriptor*>(nativeObj);
    if (layeredDrawable == nullptr) {
        return nullptr;
    }
    auto background = layeredDrawable->GetBackground();
    if (background == nullptr) {
        return nullptr;
    }
    auto obj = CreatePixelMapDrawableByPixelMap(env, background);
    return obj;
}

ani_object CreateMask(ani_env* env, [[maybe_unused]] ani_class aniClass, ani_object drawableAni)
{
    ani_long nativeObj = 0;
    env->Object_GetPropertyByName_Long(drawableAni, "nativeObj", &nativeObj);
    auto* layeredDrawable = reinterpret_cast<LayeredDrawableDescriptor*>(nativeObj);
    if (layeredDrawable == nullptr) {
        return nullptr;
    }
    auto mask = layeredDrawable->GetMask();
    if (mask == nullptr) {
        return nullptr;
    }
    auto obj = CreatePixelMapDrawableByPixelMap(env, mask);
    return obj;
}

ani_string DrawableMaskClipPath(ani_env* env)
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
            RefPtr<PixelMap> ptrForeground =
                (foreground && foreground->GetPixelMap()) ? PixelMap::Create(foreground->GetPixelMap()) : nullptr;
            RefPtr<PixelMap> ptrBackground =
                (background && background->GetPixelMap()) ? PixelMap::Create(background->GetPixelMap()) : nullptr;
            RefPtr<PixelMap> ptrMask = (mask && mask->GetPixelMap()) ? PixelMap::Create(mask->GetPixelMap()) : nullptr;

            retValue = CreateLayeredDrawableByPixelMap(env, ptrForeground, ptrBackground, ptrMask);
            break;
        }
        case DrawableType::PIXELMAP: {
            auto pixelMap = static_cast<Napi::DrawableDescriptor*>(napiDrawable);
            if (pixelMap == nullptr || pixelMap->GetPixelMap() == nullptr) {
                return nullptr;
            }
            retValue = CreatePixelMapDrawableByPixelMap(env, PixelMap::Create(pixelMap->GetPixelMap()));
            break;
        }
        default:
            break;
    }
    return retValue;
}

void SetBlendMode(ani_env* env, [[maybe_unused]] ani_class aniClass, ani_object drawableAni, ani_enum_item blendMode)
{
    ani_long nativeObj = 0;
    env->Object_GetPropertyByName_Long(drawableAni, "nativeObj", &nativeObj);
    auto* layeredDrawable = reinterpret_cast<LayeredDrawableDescriptor*>(nativeObj);
    if (layeredDrawable == nullptr) {
        return;
    }
    ani_boolean isUndefined;
    env->Reference_IsUndefined(blendMode, &isUndefined);
    ani_int mode = -1;
    if (isUndefined) {
        return;
    } else {
        if (ANI_OK != env->EnumItem_GetValue_Int(blendMode, &mode)) {
            return;
        }
    }
    layeredDrawable->SetBlendMode(mode);
}

ani_object NativeTransferStatic(
    ani_env* env, [[maybe_unused]] ani_class aniClass, ani_object input, ani_string typeName)
{
    auto drawableType = GetDrawableType(env, typeName);

    void* unwrapResult = nullptr;
    if (!arkts_esvalue_unwrap(env, input, &unwrapResult) || unwrapResult == nullptr) {
        return nullptr;
    }
    ani_object retValue = nullptr;
    if (drawableType == DrawableType::ANIMATED) {
        auto animated = reinterpret_cast<AnimatedDrawableDescriptor*>(unwrapResult);
        if (animated == nullptr) {
            return nullptr;
        }
        const auto& refList = animated->GetPixelMapList();
        std::vector<std::shared_ptr<Media::PixelMap>> pixelMapList;
        pixelMapList.reserve(refList.size());
        for (const auto& refPtr : refList) {
            pixelMapList.push_back(refPtr ? refPtr->GetPixelMapSharedPtr() : nullptr);
        }
        retValue = CreateAnimatedDrawableByPixelMapList(
            env, pixelMapList, animated->GetTotalDuration(), animated->GetIterations());
    } else {
        retValue = CreateDrawableByNapiType(env, drawableType, unwrapResult);
    }
    return retValue;
}
void DestructDrawable([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_class aniClass, ani_long pointer)
{
    if (pointer == 0) {
        return;
    }
    auto* drawable = reinterpret_cast<DrawableDescriptor*>(pointer);
    if (drawable != nullptr) {
        drawable->DecRefCount();
    }
}

OHOS::Ace::ControlledAnimator* GetAnimationControllerNative(ani_env* env, ani_object animationController)
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
    auto* controlledAnimator = reinterpret_cast<OHOS::Ace::ControlledAnimator*>(nativeObj);
    return controlledAnimator;
}

static void AnimationControllerStart(ani_env* env, ani_object animationController)
{
    auto* controlledAnimator = GetAnimationControllerNative(env, animationController);
    if (controlledAnimator == nullptr) {
        return;
    }
    controlledAnimator->Finish();
    controlledAnimator->Forward();
}

static void AnimationControllerStop(ani_env* env, ani_object animationController)
{
    auto* controlledAnimator = GetAnimationControllerNative(env, animationController);
    if (controlledAnimator == nullptr) {
        return;
    }
    controlledAnimator->Finish();
}

static void AnimationControllerPause(ani_env* env, ani_object animationController)
{
    auto* controlledAnimator = GetAnimationControllerNative(env, animationController);
    if (controlledAnimator == nullptr) {
        return;
    }
    controlledAnimator->Pause();
}

static void AnimationControllerResume(ani_env* env, ani_object animationController)
{
    auto* controlledAnimator = GetAnimationControllerNative(env, animationController);
    if (controlledAnimator == nullptr) {
        return;
    }
    controlledAnimator->Forward();
}

static ani_enum_item AnimationControllerGetStatus(ani_env* env, ani_object animationController)
{
    auto* controlledAnimator = GetAnimationControllerNative(env, animationController);
    if (controlledAnimator == nullptr) {
        return nullptr;
    }
    auto status = controlledAnimator->GetControlStatus();

    ani_enum animationStatus;
    if (env->FindEnum("arkui.component.enums.AnimationStatus", &animationStatus) != ANI_OK) {
        return nullptr;
    }

    ani_enum_item animationStatusItem = nullptr;
    switch (status) {
        case OHOS::Ace::ControlledAnimator::ControlStatus::IDLE: {
            if (env->Enum_GetEnumItemByName(animationStatus, "Initial", &animationStatusItem) != ANI_OK) {
                TAG_LOGI(AceLogTag::ACE_DRAWABLE_DESCRIPTOR, "[ANI] GetEnumItem fail");
            }
            break;
        }
        case OHOS::Ace::ControlledAnimator::ControlStatus::RUNNING: {
            if (env->Enum_GetEnumItemByName(animationStatus, "Running", &animationStatusItem) != ANI_OK) {
                TAG_LOGI(AceLogTag::ACE_DRAWABLE_DESCRIPTOR, "[ANI] GetEnumItem fail");
            }
            break;
        }
        case OHOS::Ace::ControlledAnimator::ControlStatus::PAUSED: {
            if (env->Enum_GetEnumItemByName(animationStatus, "Paused", &animationStatusItem) != ANI_OK) {
                TAG_LOGI(AceLogTag::ACE_DRAWABLE_DESCRIPTOR, "[ANI] GetEnumItem fail");
            }
            break;
        }
        case OHOS::Ace::ControlledAnimator::ControlStatus::STOPPED: {
            if (env->Enum_GetEnumItemByName(animationStatus, "Stopped", &animationStatusItem) != ANI_OK) {
                TAG_LOGI(AceLogTag::ACE_DRAWABLE_DESCRIPTOR, "[ANI] GetEnumItem fail");
            }
            break;
        }
        default:
            break;
    }
    return animationStatusItem;
}
} // namespace OHOS::Ace::Ani

ani_status BindAnimationController(ani_env* env)
{
    ani_class cls;
    auto res = env->FindClass(OHOS::Ace::Ani::ANIMATION_CONTROLLER_INNER, &cls);
    if (ANI_OK != res) {
        return ANI_ERROR;
    }

    std::array methods = {
        ani_native_function { "start", nullptr, reinterpret_cast<void*>(OHOS::Ace::Ani::AnimationControllerStart) },
        ani_native_function { "stop", nullptr, reinterpret_cast<void*>(OHOS::Ace::Ani::AnimationControllerStop) },
        ani_native_function { "pause", nullptr, reinterpret_cast<void*>(OHOS::Ace::Ani::AnimationControllerPause) },
        ani_native_function { "resume", nullptr, reinterpret_cast<void*>(OHOS::Ace::Ani::AnimationControllerResume) },
        ani_native_function {
            "getStatus", nullptr, reinterpret_cast<void*>(OHOS::Ace::Ani::AnimationControllerGetStatus) },
    };
    res = env->Class_BindNativeMethods(cls, methods.data(), methods.size());
    if (ANI_OK != res) {
        return ANI_ERROR;
    }

    return ANI_OK;
}

ANI_EXPORT ani_status ANI_Constructor(ani_vm* vm, uint32_t* result)
{
    ani_env* env;
    if (ANI_OK != vm->GetEnv(ANI_VERSION_1, &env)) {
        return ANI_ERROR;
    }

    if (BindAnimationController(env) != ANI_OK) {
        return ANI_ERROR;
    }

    ani_class cls;
    auto ani_status = env->FindClass("@ohos.arkui.drawableDescriptor.DrawableDescriptorInner", &cls);
    if (ani_status != ANI_OK) {
        return ANI_ERROR;
    }

    std::array staticMethods = {
        ani_native_function {
            "createPixelMapDrawable", nullptr, reinterpret_cast<void*>(OHOS::Ace::Ani::CreatePixelMapDrawable) },
        ani_native_function {
            "createLayeredDrawable", nullptr, reinterpret_cast<void*>(OHOS::Ace::Ani::CreateLayeredDrawable) },
        ani_native_function {
            "createAnimatedDrawable", nullptr, reinterpret_cast<void*>(OHOS::Ace::Ani::CreateAnimatedDrawable) },
        ani_native_function { "createAnimatedDrawableByResource", nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::CreateAnimatedDrawableByResource) },
        ani_native_function { "createAnimatedDrawableByString", nullptr,
            reinterpret_cast<void*>(OHOS::Ace::Ani::CreateAnimatedDrawableByString) },
        ani_native_function { "createPixelMap", nullptr, reinterpret_cast<void*>(OHOS::Ace::Ani::CreatePixelMap) },
        ani_native_function { "composePixelMap", nullptr, reinterpret_cast<void*>(OHOS::Ace::Ani::ComposePixelMap) },
        ani_native_function { "createForeground", nullptr, reinterpret_cast<void*>(OHOS::Ace::Ani::CreateForefround) },
        ani_native_function { "createBackground", nullptr, reinterpret_cast<void*>(OHOS::Ace::Ani::CreateBackground) },
        ani_native_function { "createMask", nullptr, reinterpret_cast<void*>(OHOS::Ace::Ani::CreateMask) },
        ani_native_function {
            "getMaskClipPath", nullptr, reinterpret_cast<void*>(OHOS::Ace::Ani::DrawableMaskClipPath) },
        ani_native_function { "loadSync", nullptr, reinterpret_cast<void*>(OHOS::Ace::Ani::LoadSync) },
        ani_native_function { "load", nullptr, reinterpret_cast<void*>(OHOS::Ace::Ani::Load) },
        ani_native_function {
            "getAnimationController", nullptr, reinterpret_cast<void*>(OHOS::Ace::Ani::GetAnimationController) },
        ani_native_function {
            "nativeTransferStatic", nullptr, reinterpret_cast<void*>(OHOS::Ace::Ani::NativeTransferStatic) },
        ani_native_function { "setBlendMode", nullptr, reinterpret_cast<void*>(OHOS::Ace::Ani::SetBlendMode) },
        ani_native_function { "destructDrawable", nullptr, reinterpret_cast<void*>(OHOS::Ace::Ani::DestructDrawable) },
    };
    auto bindRst = env->Class_BindStaticNativeMethods(cls, staticMethods.data(), staticMethods.size());
    if (bindRst != ANI_OK) {
        LOGI("bind static native methods failed, id = %{public}d", static_cast<int>(bindRst));
        return bindRst;
    }
    *result = ANI_VERSION_1;
    return ANI_OK;
}
