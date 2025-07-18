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
#include "load.h"

namespace OHOS::Ace::Ani {
namespace {
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
    static const char* className = "Larkui/component/xcomponent/SurfaceRectAniInternal;";
    ani_class cls;
    if (ANI_OK != env->FindClass(className, &cls)) {
        return nullptr;
    }
    ani_method ctor;
    if (ANI_OK != env->Class_FindMethod(cls, "<ctor>", "DDDD:V", &ctor)) {
        return nullptr;
    }
    ani_object surfaceRectRef;
    if (ANI_OK != env->Object_New(cls, ctor, &surfaceRectRef, width, height, offsetX, offsetY)) {
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

void ConvertSurfaceIdCallback(ani_vm* vm,
    std::function<void(const std::string&)>& callback, const std::shared_ptr<XComponentCallbackAni>& callbackAni)
{
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

void ConvertSurfaceChangeCallback(ani_vm* vm,
    std::function<void(const std::string&, float, float, float, float)>& callback,
    const std::shared_ptr<XComponentCallbackAni>& callbackAni)
{
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
} // namespace

void SetXComponentControllerCallback(ani_env* env, [[maybe_unused]] ani_object aniClass,
    ani_object node, ani_object callbackAni)
{
    CHECK_NULL_VOID(env);
    auto* arkNode = reinterpret_cast<ArkUINodeHandle>(node);
    CHECK_NULL_VOID(arkNode);
    const auto* modifier = GetNodeAniModifier();
    CHECK_NULL_VOID(modifier);
    auto xcomponentModifier = modifier->getArkUIAniXComponentModifier();
    CHECK_NULL_VOID(xcomponentModifier);
    ani_ref onSurfaceCreatedAni = nullptr;
    ani_ref onSurfaceChangedAni = nullptr;
    ani_ref onSurfaceDestroyedAni = nullptr;
    if (ANI_OK != env->Object_GetPropertyByName_Ref(callbackAni, "onSurfaceCreated", &onSurfaceCreatedAni)) {
        return;
    }
    if (ANI_OK != env->Object_GetPropertyByName_Ref(callbackAni, "onSurfaceChanged", &onSurfaceChangedAni)) {
        return;
    }
    if (ANI_OK != env->Object_GetPropertyByName_Ref(callbackAni, "onSurfaceDestroyed", &onSurfaceDestroyedAni)) {
        return;
    }
    auto onSurfaceCreatedCallback = std::make_shared<XComponentCallbackAni>(env, onSurfaceCreatedAni);
    auto onSurfaceChangedCallback = std::make_shared<XComponentCallbackAni>(env, onSurfaceChangedAni);
    auto onSurfaceDestroyedCallback = std::make_shared<XComponentCallbackAni>(env, onSurfaceDestroyedAni);
    ani_vm* vm = nullptr;
    env->GetVM(&vm);
    std::function<void(const std::string&)> onSurfaceCreated = nullptr;
    std::function<void(const std::string&, float, float, float, float)> onSurfaceChanged = nullptr;
    std::function<void(const std::string&)> onSurfaceDestroyed = nullptr;
    ConvertSurfaceIdCallback(vm, onSurfaceCreated, onSurfaceCreatedCallback);
    ConvertSurfaceChangeCallback(vm, onSurfaceChanged, onSurfaceChangedCallback);
    ConvertSurfaceIdCallback(vm, onSurfaceDestroyed, onSurfaceDestroyedCallback);
    xcomponentModifier->setXComponentControllerCallback(arkNode, std::move(onSurfaceCreated),
        std::move(onSurfaceChanged), std::move(onSurfaceDestroyed));
}

} // namespace OHOS::Ace::Ani
