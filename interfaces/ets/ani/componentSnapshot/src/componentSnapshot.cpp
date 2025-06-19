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

#include <ani.h>
#include <cstdint>
#include <sys/stat.h>
#ifdef PIXEL_MAP_SUPPORTED
#include "pixel_map.h"
// #include "pixel_map_ani.h"
#include "pixel_map_napi.h"

#endif
#include "core/common/ace_engine.h"
#include "frameworks/bridge/common/utils/engine_helper.h"

namespace {
static ani_ref createInt(ani_env* env, ani_int value)
{
    ani_class cls;
    env->FindClass("Lstd/core/Int;", &cls);
    ani_method ctor;
    env->Class_FindMethod(cls, "<ctor>", ":V", &ctor);

    ani_object rs;
    env->Object_New(cls, ctor, &rs, value);
    return static_cast<ani_object>(rs);
}
} // namespace

static bool GetOptionsScale(ani_env* env, ani_object options, float& value)
{
    ani_boolean isUndefined;
    env->Reference_IsUndefined(options, &isUndefined);
    if (!isUndefined) {
        return false;
    }
    static const char* className = "L@ohos/componentSnapshot/componentSnapshot/SnapshotOptions;";
    ani_class cls;
    if (ANI_OK != env->FindClass(className, &cls)) {
        return false;
    }
    ani_ref propertyRef;
    if (ANI_OK != env->Object_GetPropertyByName_Ref(options, "scale", &propertyRef)) {
        return false;
    }

    ani_boolean isPropertyUndefined;
    env->Reference_IsUndefined(propertyRef, &isPropertyUndefined);
    if (!isPropertyUndefined) {
        return false;
    }
    ani_double aniValue;
    if (ANI_OK !=
        env->Object_CallMethodByName_Double(static_cast<ani_object>(propertyRef), "doubleValue", nullptr, &aniValue)) {
        return false;
    }
    value = static_cast<double>(aniValue);
    return true;
}

static bool GetOptionsWaitUntilRenderFinished(ani_env* env, ani_object options, bool& value)
{
    ani_boolean isUndefined;
    env->Reference_IsUndefined(options, &isUndefined);
    if (!isUndefined) {
        return false;
    }
    static const char* className = "L@ohos/componentSnapshot/componentSnapshot/SnapshotOptions;";
    ani_class cls;
    if (ANI_OK != env->FindClass(className, &cls)) {
        return false;
    }
    ani_ref propertyRef;
    if (ANI_OK != env->Object_GetPropertyByName_Ref(options, "waitUntilRenderFinished", &propertyRef)) {
        return false;
    }

    ani_boolean isPropertyUndefined;
    env->Reference_IsUndefined(propertyRef, &isPropertyUndefined);
    if (!isPropertyUndefined) {
        return false;
    }
    ani_boolean aniValue;
    if (ANI_OK !=
        env->Object_CallMethodByName_Boolean(static_cast<ani_object>(propertyRef), "unboxed", nullptr, &aniValue)) {
        return false;
    }
    value = static_cast<bool>(aniValue);
    return true;
}

static bool GetDelay(ani_env* env, ani_object object, int32_t& value)
{
    ani_boolean isUndefined;
    env->Reference_IsUndefined(object, &isUndefined);
    if (!isUndefined) {
        return false;
    }
    ani_int aniValue;
    if (ANI_OK != env->Object_CallMethodByName_Int(object, "intValue", nullptr, &aniValue)) {
        return false;
    }
    value = static_cast<int32_t>(aniValue);
    return true;
}

static bool GetCheckImageStatus(ani_env* env, ani_object object, bool& value)
{
    ani_boolean isUndefined;
    env->Reference_IsUndefined(object, &isUndefined);
    if (!isUndefined) {
        return false;
    }
    ani_boolean aniValue;
    if (ANI_OK != env->Object_CallMethodByName_Boolean(object, "unboxed", nullptr, &aniValue)) {
        return false;
    }
    value = static_cast<bool>(aniValue);
    return true;
}

static void createFromBuilder([[maybe_unused]] ani_env* env, ani_object builderObj, ani_object callbackObj,
    ani_object delay, ani_object checkImageStatus, ani_object options)
{
    auto biulder = [env, builderObj]() {
        env->FunctionalObject_Call(static_cast<ani_fn_object>(builderObj), 0, nullptr, nullptr);
    };
    auto callback = [env, callbackObj](std::shared_ptr<OHOS::Media::PixelMap> pixmap, int32_t errCode,
                        std::function<void()> finishCallback) {
        std::vector<ani_ref> vec;
        vec.push_back(createInt(env, ani_int(errCode)));
        if (errCode == 0) {
#ifdef PIXEL_MAP_SUPPORTED
            ani_ref pixmapItem = OHOS::Media::PixelMapAni::CreateAniPixelMap(env, pixmap);
            if (pixmapItem) {
                vec.push_back(pixmapItem);
            }
#endif
        }
        env->FunctionalObject_Call(static_cast<ani_fn_object>(callbackObj), vec.size(), vec.data(), nullptr);
    };

    OHOS::Ace::NG::SnapshotParam param;
    GetDelay(env, delay, param.delay);
    GetCheckImageStatus(env, checkImageStatus, param.checkImageStatus);
    GetOptionsScale(env, options, param.options.scale);
    GetOptionsWaitUntilRenderFinished(env, options, param.options.waitUntilRenderFinished);

    auto delegate = OHOS::Ace::EngineHelper::GetCurrentDelegateSafely();
    if (!delegate) {
        return;
    }
    delegate->CreateSnapshot(biulder, callback, true, param);
}

ANI_EXPORT ani_status ANI_Constructor(ani_vm* vm, uint32_t* result)
{
    ani_env* env;
    if (ANI_OK != vm->GetEnv(ANI_VERSION_1, &env)) {
        return ANI_ERROR;
    }

    ani_namespace ns;
    if (ANI_OK != env->FindNamespace("L@ohos/componentSnapshot/componentSnapshot;", &ns)) {
        return ANI_ERROR;
    }
    std::array methods = {
        ani_native_function { "createFromBuilder", nullptr, reinterpret_cast<void*>(createFromBuilder) },
    };
    if (ANI_OK != env->Namespace_BindNativeFunctions(ns, methods.data(), methods.size())) {
        return ANI_ERROR;
    }

    *result = ANI_VERSION_1;
    return ANI_OK;
}
