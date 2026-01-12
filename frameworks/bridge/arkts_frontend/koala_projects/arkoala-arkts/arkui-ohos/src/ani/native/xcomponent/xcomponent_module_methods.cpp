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

#include "xcomponent_module_methods.h"

#include "base/utils/utils.h"
#include "base/utils/string_utils.h"
#include "load.h"
#include "utils/ani_utils.h"

namespace OHOS::Ace::Ani {
namespace {
bool IsUndefined(ani_env* env, ani_ref obj)
{
    CHECK_NULL_RETURN(env, false);
    ani_boolean isUndefined;
    env->Reference_IsUndefined(obj, &isUndefined);
    return isUndefined;
}
ani_status GetAniEnv(ani_vm* vm, ani_env** env)
{
    CHECK_NULL_RETURN(vm, ANI_ERROR);
    ani_options aniOpt {0, nullptr};
    auto status = vm->AttachCurrentThread(&aniOpt, ANI_VERSION_1, env);
    if (status != ANI_OK) {
        vm->GetEnv(ANI_VERSION_1, env);
    }
    return status;
}

ani_string CreateSurfaceIdAni(ani_env* env, const std::string& surfaceId)
{
    CHECK_NULL_RETURN(env, nullptr);
    ani_string surfaceIdRef;
    if (ANI_OK != env->String_NewUTF8(surfaceId.c_str(), surfaceId.size(), &surfaceIdRef)) {
        return nullptr;
    }
    return surfaceIdRef;
}

ani_object CreateSurfaceRectAni(ani_env* env, float width, float height, float offsetX, float offsetY)
{
    CHECK_NULL_RETURN(env, nullptr);
    static ani_ref gSurfaceRect = {};
    static ani_method gSurfaceRectCtor = {};
    if (!gSurfaceRect) {
        static const char* className = "arkui.component.xcomponent.SurfaceRectAniInternal";
        ani_class cls;
        if (ANI_OK != env->FindClass(className, &cls) ||
            ANI_OK != env->GlobalReference_Create(static_cast<ani_ref>(cls), &gSurfaceRect)) {
            return nullptr;
        }
    }
    if (!gSurfaceRectCtor) {
        if (ANI_OK !=
            env->Class_FindMethod(static_cast<ani_class>(gSurfaceRect), "<ctor>", "dddd:", &gSurfaceRectCtor)) {
            return nullptr;
        }
    }
    ani_object surfaceRectRef;
    if (ANI_OK != env->Object_New(static_cast<ani_class>(gSurfaceRect), gSurfaceRectCtor, &surfaceRectRef, width,
        height, offsetX, offsetY)) {
        return nullptr;
    }
    return surfaceRectRef;
}

class XComponentCallbackAni {
public:
    XComponentCallbackAni(ani_env* env, ani_ref func)
    {
        CHECK_NULL_VOID(env);
        env->GetVM(&vm_);
        env->GlobalReference_Create(func, &func_);
    }
    ~XComponentCallbackAni()
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

void ConvertSurfaceCreatedCallback(ani_vm* vm, ani_env* env, ani_object value,
    std::function<void(const std::string&)>& callback)
{
    CHECK_NULL_VOID(env);
    ani_ref onSurfaceCreatededRef = nullptr;
    if (ANI_OK != env->Object_GetPropertyByName_Ref(value, "onSurfaceCreated", &onSurfaceCreatededRef)) {
        return;
    }
    if (IsUndefined(env, onSurfaceCreatededRef)) {
        return;
    }
    auto callbackAni = std::make_shared<XComponentCallbackAni>(env, onSurfaceCreatededRef);
    callback = [vm, callbackAni](const std::string& surfaceId) {
        CHECK_NULL_VOID(vm);
        CHECK_NULL_VOID(callbackAni);
        ani_env* env;
        auto attachCurrentThreadStatus = GetAniEnv(vm, &env);
        CHECK_NULL_VOID(env);
        ani_string surfaceIdAni = CreateSurfaceIdAni(env, surfaceId);
        CHECK_NULL_VOID(surfaceIdAni);
        std::vector<ani_ref> args = { surfaceIdAni };
        ani_ref ret = nullptr;
        callbackAni->Call(env, args.size(), args.data(), &ret);
        if (attachCurrentThreadStatus == ANI_OK) {
            vm->DetachCurrentThread();
        }
    };
}

void ConvertSurfaceChangeCallback(ani_vm* vm, ani_env* env, ani_object value,
    std::function<void(const std::string&, float, float, float, float)>& callback)
{
    CHECK_NULL_VOID(env);
    ani_ref onSurfaceChangedRef = nullptr;
    if (ANI_OK != env->Object_GetPropertyByName_Ref(value, "onSurfaceChanged", &onSurfaceChangedRef)) {
        return;
    }
    if (IsUndefined(env, onSurfaceChangedRef)) {
        return;
    }
    auto callbackAni = std::make_shared<XComponentCallbackAni>(env, onSurfaceChangedRef);
    callback = [vm, callbackAni](const std::string& surfaceId,
        float width, float height, float offsetX, float offsetY) {
        CHECK_NULL_VOID(vm);
        CHECK_NULL_VOID(callbackAni);
        ani_env* env;
        auto attachCurrentThreadStatus = GetAniEnv(vm, &env);
        CHECK_NULL_VOID(env);
        ani_string surfaceIdAni = CreateSurfaceIdAni(env, surfaceId);
        ani_object surfaceRectAni = CreateSurfaceRectAni(env, width, height, offsetX, offsetY);
        CHECK_NULL_VOID(surfaceIdAni);
        CHECK_NULL_VOID(surfaceRectAni);
        std::vector<ani_ref> args = { surfaceIdAni, surfaceRectAni };
        ani_ref ret = nullptr;
        callbackAni->Call(env, args.size(), args.data(), &ret);
        if (attachCurrentThreadStatus == ANI_OK) {
            vm->DetachCurrentThread();
        }
    };
}

void ConvertSurfaceDestroyedCallback(ani_vm* vm, ani_env* env, ani_object value,
    std::function<void(const std::string&)>& callback)
{
    CHECK_NULL_VOID(env);
    ani_ref onSurfaceDestroyedRef = nullptr;
    if (ANI_OK != env->Object_GetPropertyByName_Ref(value, "onSurfaceDestroyed", &onSurfaceDestroyedRef)) {
        return;
    }
    if (IsUndefined(env, onSurfaceDestroyedRef)) {
        return;
    }
    auto callbackAni = std::make_shared<XComponentCallbackAni>(env, onSurfaceDestroyedRef);
    callback = [vm, callbackAni](const std::string& surfaceId) {
        CHECK_NULL_VOID(vm);
        CHECK_NULL_VOID(callbackAni);
        ani_env* env;
        auto attachCurrentThreadStatus = GetAniEnv(vm, &env);
        CHECK_NULL_VOID(env);
        ani_string surfaceIdAni = CreateSurfaceIdAni(env, surfaceId);
        CHECK_NULL_VOID(surfaceIdAni);
        std::vector<ani_ref> args = { surfaceIdAni };
        ani_ref ret = nullptr;
        callbackAni->Call(env, args.size(), args.data(), &ret);
        if (attachCurrentThreadStatus == ANI_OK) {
            vm->DetachCurrentThread();
        }
    };
}
} // namespace

void SetXComponentControllerCallback(
    ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long peer, ani_object options)
{
    CHECK_NULL_VOID(env);
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_VOID(modifier);
    auto xcomponentModifier = modifier->getArkUIAniXComponentModifier();
    CHECK_NULL_VOID(xcomponentModifier);
    ArkUIXComponentParams xcParams;
    ani_vm* vm = nullptr;
    env->GetVM(&vm);
    ConvertSurfaceCreatedCallback(vm, env, options, xcParams.onSurfaceCreated);
    ConvertSurfaceChangeCallback(vm, env, options, xcParams.onSurfaceChanged);
    ConvertSurfaceDestroyedCallback(vm, env, options, xcParams.onSurfaceDestroyed);
    xcomponentModifier->setXComponentControllerCallback(reinterpret_cast<void*>(peer), xcParams);
}
} // namespace OHOS::Ace::Ani
