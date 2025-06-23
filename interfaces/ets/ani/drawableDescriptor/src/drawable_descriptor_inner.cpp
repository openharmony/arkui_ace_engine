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

#include "ani.h"
#include "draw/canvas.h"
#include "image/bitmap.h"
#include "image/image_info.h"
#include "pixel_map_taihe_ani.h"
#include "resource_manager.h"
#include "securec.h"

#include "base/image/pixel_map.h"
#include "base/log/log.h"
#include "core/drawable/layered_drawable_descriptor.h"
#include "core/drawable/pixel_map_drawable_descriptor.h"

namespace OHOS::Ace::Ani {
namespace {
const char PIXEL_MAP_CONSTRUCTOR[] = "L@ohos/multimedia/image/image/PixelMap;:";
const char PIXEL_MAP_DRAWABLE[] = "L@ohos/arkui/drawableDescriptor/PixelMapDrawableDescriptor;";
} // namespace

void CreatePixelMapDrawable(
    ani_env* env, [[maybe_unused]] ani_class aniClass, ani_object drawableAni, ani_object pixelAni)
{
    ani_boolean isUndefined;
    env->Reference_IsUndefined(pixelAni, &isUndefined);
    // first create native pixel map drawable descriptor
    auto* drawable = new PixelMapDrawableDescriptor();
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
    }
}

void CreatePixelMap(ani_env* env, [[maybe_unused]] ani_class aniClass, ani_object drawableAni)
{
    ani_long nativeObj = 0;
    env->Object_GetPropertyByName_Long(drawableAni, "nativeObj", &nativeObj);
    auto* pixelMapDrawable = reinterpret_cast<PixelMapDrawableDescriptor*>(nativeObj);
    if (pixelMapDrawable == nullptr) {
        return;
    }
    auto pixelMap = pixelMapDrawable->GetPixelMap();
    if (pixelMap == nullptr) {
        return;
    }
    // set pixel map property to arkts object
    auto pixelAni = Media::PixelMapTaiheAni::CreateEtsPixelMap(env, pixelMap->GetPixelMapSharedPtr());
    if (pixelAni == nullptr) {
        return;
    }
    env->Object_SetPropertyByName_Ref(drawableAni, "pixelMap", pixelAni);
}

void ComposePixelMap(ani_env* env, [[maybe_unused]] ani_class aniClass, ani_object drawableAni)
{
    ani_long nativeObj = 0;
    env->Object_GetPropertyByName_Long(drawableAni, "nativeObj", &nativeObj);
    auto* layeredDrawable = reinterpret_cast<LayeredDrawableDescriptor*>(nativeObj);
    if (layeredDrawable == nullptr) {
        return;
    }
    auto pixelMap = layeredDrawable->GetPixelMap();
    if (pixelMap == nullptr) {
        return;
    }
    // set pixel map property to arkts object
    auto pixelAni = Media::PixelMapTaiheAni::CreateEtsPixelMap(env, pixelMap->GetPixelMapSharedPtr());
    if (pixelAni == nullptr) {
        return;
    }
    env->Object_SetPropertyByName_Ref(drawableAni, "pixelMap", pixelAni);
}

void CreateForefround(ani_env* env, [[maybe_unused]] ani_class aniClass, ani_object drawableAni)
{
    ani_long nativeObj = 0;
    env->Object_GetPropertyByName_Long(drawableAni, "nativeObj", &nativeObj);
    auto* layeredDrawable = reinterpret_cast<LayeredDrawableDescriptor*>(nativeObj);
    if (layeredDrawable == nullptr) {
        return;
    }
    auto foreground = layeredDrawable->GetForeground();
    if (foreground == nullptr) {
        return;
    }
    auto pixelAni = Media::PixelMapTaiheAni::CreateEtsPixelMap(env, foreground->GetPixelMapSharedPtr());
    if (pixelAni == nullptr) {
        return;
    }
    // set foreground property to arkts object
    ani_class cls;
    ani_object obj;
    auto status = env->FindClass(PIXEL_MAP_DRAWABLE, &cls);
    if (status != ANI_OK) {
        return;
    }
    ani_method ctor;
    env->Class_FindMethod(cls, "<ctor>", PIXEL_MAP_CONSTRUCTOR, &ctor);
    env->Object_New(cls, ctor, &obj, pixelAni);
    env->Object_SetPropertyByName_Ref(drawableAni, "foreground", obj);
}

void CreateBackground(ani_env* env, [[maybe_unused]] ani_class aniClass, ani_object drawableAni)
{
    ani_long nativeObj = 0;
    env->Object_GetPropertyByName_Long(drawableAni, "nativeObj", &nativeObj);
    auto* layeredDrawable = reinterpret_cast<LayeredDrawableDescriptor*>(nativeObj);
    if (layeredDrawable == nullptr) {
        return;
    }
    auto background = layeredDrawable->GetBackground();
    if (background == nullptr) {
        return;
    }
    auto pixelAni = Media::PixelMapTaiheAni::CreateEtsPixelMap(env, background->GetPixelMapSharedPtr());
    // set background property to arkts object
    ani_class cls;
    ani_object obj;
    auto status = env->FindClass(PIXEL_MAP_DRAWABLE, &cls);
    if (status != ANI_OK) {
        return;
    }
    ani_method ctor;
    env->Class_FindMethod(cls, "<ctor>", PIXEL_MAP_CONSTRUCTOR, &ctor);
    env->Object_New(cls, ctor, &obj, pixelAni);
    env->Object_SetPropertyByName_Ref(drawableAni, "background", obj);
}

void CreateMask(ani_env* env, [[maybe_unused]] ani_class aniClass, ani_object drawableAni)
{
    ani_long nativeObj = 0;
    env->Object_GetPropertyByName_Long(drawableAni, "nativeObj", &nativeObj);
    auto* layeredDrawable = reinterpret_cast<LayeredDrawableDescriptor*>(nativeObj);
    if (layeredDrawable == nullptr) {
        return;
    }
    auto mask = layeredDrawable->GetMask();
    if (mask == nullptr) {
        return;
    }
    auto pixelAni = Media::PixelMapTaiheAni::CreateEtsPixelMap(env, mask->GetPixelMapSharedPtr());
    // set mask property to arkts object
    ani_class cls;
    ani_object obj;
    auto status = env->FindClass(PIXEL_MAP_DRAWABLE, &cls);
    if (status != ANI_OK) {
        return;
    }
    ani_method ctor;
    env->Class_FindMethod(cls, "<ctor>", PIXEL_MAP_CONSTRUCTOR, &ctor);
    env->Object_New(cls, ctor, &obj, pixelAni);
    env->Object_SetPropertyByName_Ref(drawableAni, "mask", obj);
}

ani_string DrawableMaskClipPath(ani_env* env)
{
    std::string data;
    std::shared_ptr<Global::Resource::ResourceManager> resMgr(Global::Resource::CreateResourceManager());
    resMgr->GetStringByName("ohos_drawable_descriptor_path", data);
    ani_string aniString {};
    env->String_NewUTF8(data.c_str(), data.size(), &aniString);
    return aniString;
}

} // namespace OHOS::Ace::Ani

ANI_EXPORT ani_status ANI_Constructor(ani_vm* vm, uint32_t* result)
{
    ani_env* env;
    if (ANI_OK != vm->GetEnv(ANI_VERSION_1, &env)) {
        return ANI_ERROR;
    }
    ani_class cls;
    auto ani_status = env->FindClass("L@ohos/arkui/drawableDescriptor/DrawableDescriptorInner;", &cls);
    if (ani_status != ANI_OK) {
        LOGI("find arkui drawable descriptor inner failed");
        return ANI_ERROR;
    }
    std::array methods = {
        ani_native_function {
            "createPixelMapDrawable", nullptr, reinterpret_cast<void*>(OHOS::Ace::Ani::CreatePixelMapDrawable) },
        ani_native_function {
            "createLayeredDrawable", nullptr, reinterpret_cast<void*>(OHOS::Ace::Ani::CreateLayeredDrawable) },
        ani_native_function { "createPixelMap", nullptr, reinterpret_cast<void*>(OHOS::Ace::Ani::CreatePixelMap) },
        ani_native_function { "composePixelMap", nullptr, reinterpret_cast<void*>(OHOS::Ace::Ani::ComposePixelMap) },
        ani_native_function { "createForeground", nullptr, reinterpret_cast<void*>(OHOS::Ace::Ani::CreateForefround) },
        ani_native_function { "createBackground", nullptr, reinterpret_cast<void*>(OHOS::Ace::Ani::CreateBackground) },
        ani_native_function { "createMask", nullptr, reinterpret_cast<void*>(OHOS::Ace::Ani::CreateMask) },
        ani_native_function {
            "getMaskClipPath", nullptr, reinterpret_cast<void*>(OHOS::Ace::Ani::DrawableMaskClipPath) },
    };
    auto bindRst = env->Class_BindNativeMethods(cls, methods.data(), methods.size());
    if (bindRst != ANI_OK) {
        LOGI("bind native methods failed, id = %{public}d", static_cast<int>(bindRst));
        return bindRst;
    }
    *result = ANI_VERSION_1;
    return ANI_OK;
}