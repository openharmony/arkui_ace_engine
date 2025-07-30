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

#include <ani.h>
#include <string>
#include <unistd.h>

#include "base/log/log.h"
#include "base/memory/ace_type.h"
#include "core/components_ng/base/observer_handler.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace {
// constexpr const char DENSITY_CHNAGE[] = "densityUpdate";
const char ANI_OBSERVER_NS[] = "L@ohos/arkui/observer/uiObserver;";
const char ANI_OBSERVER_CLS[] = "L@ohos/arkui/observer/uiObserver/UIObserverImpl;";
} // namespace
namespace OHOS::Ace {
class UiObserver {
public:
    explicit UiObserver(int32_t instanceId) : id_(instanceId) {}

    void CallJsFunction(ani_env* env, std::list<ani_ref>& cbList)
    {
        std::vector<ani_ref> vec;
        ani_ref fnReturnVal;
        for (auto& cb : cbList) {
            env->FunctionalObject_Call(reinterpret_cast<ani_fn_object>(cb), vec.size(), vec.data(), &fnReturnVal);
        }
    }

    // UIObserver.on(type: "densityUpdate", uiContext | null, callback)
    // register a listener on current page
    void RegisterDensityCallback(int32_t uiContextInstanceId, ani_ref& cb)
    {
        id_ = uiContextInstanceId;
        if (uiContextInstanceId == 0) {
            uiContextInstanceId = Container::CurrentId();
        }
        auto iter = densityCbMap_.find(uiContextInstanceId);
        if (iter == densityCbMap_.end()) {
            densityCbMap_.emplace(uiContextInstanceId, std::list<ani_ref>({ cb }));
            return;
        }
        auto& holder = iter->second;
        if (std::find(holder.begin(), holder.end(), cb) != holder.end()) {
            return;
        }
        holder.emplace_back(cb);
    }
    // UIObserver.off(type: "densityUpdate", uiContext | null, callback)
    void UnRegisterDensityCallback(ani_env* env, int32_t uiContextInstanceId, ani_ref& cb)
    {
        if (uiContextInstanceId == 0) {
            uiContextInstanceId = Container::CurrentId();
        }
        auto iter = densityCbMap_.find(uiContextInstanceId);
        if (iter == densityCbMap_.end()) {
            return;
        }
        auto& holder = iter->second;
        if (cb == nullptr) {
            holder.clear();
            return;
        }
        holder.erase(std::remove_if(
                         holder.begin(), holder.end(), [env, cb, this](ani_ref cb1) { return AniEqual(env, cb, cb1); }),
            holder.end());
    }

    void HandleDensityChange(ani_env* env, double density)
    {
        auto currentId = Container::CurrentId();
        auto iter = densityCbMap_.find(currentId);
        if (iter == densityCbMap_.end()) {
            return;
        }
        auto& holder = iter->second;
        std::vector<ani_ref> callbackParams;
        ani_ref fnReturnVal;
        ani_object res;
        CreateDensityInfo(env, density, res);
        callbackParams.emplace_back(res);
        for (auto& cb : holder) {
            env->FunctionalObject_Call(reinterpret_cast<ani_fn_object>(cb),
                                       callbackParams.size(),
                                       callbackParams.data(),
                                       &fnReturnVal);
        }
    }

    ani_boolean AniEqual(ani_env* env, ani_ref cb, ani_ref cb1)
    {
        ani_boolean isEquals = false;
        env->Reference_StrictEquals(cb, cb1, &isEquals);
        return isEquals;
    }

    void CreateDensityInfo(ani_env* env, double density, ani_object& obj)
    {
        static const char* className = "L@ohos/arkui/observer/uiObserver/DensityInfo;";
        ani_class cls;
        env->FindClass(className, &cls);
        ani_method ctor;
        env->Class_FindMethod(cls, "<ctor>", ":V", &ctor);
        env->Object_New(cls, ctor, &obj);
        env->Object_SetPropertyByName_Double(obj, "density", ani_double(density));
    }

private:
    int32_t id_;
    std::unordered_map<int32_t, std::list<ani_ref>> densityCbMap_;
};

static UiObserver* Unwrapp(ani_env* env, ani_object object)
{
    ani_long nativeAddr;
    if (ANI_OK != env->Object_GetFieldByName_Long(object, "nativeObserverAddr", &nativeAddr)) {
        return nullptr;
    }
    return reinterpret_cast<UiObserver*>(nativeAddr);
}

std::string ANIUtils_ANIStringToStdString(ani_env* env, ani_string ani_str)
{
    ani_size strSize;
    env->String_GetUTF8Size(ani_str, &strSize);

    std::vector<char> buffer(strSize + 1);
    char* utf8Buffer = buffer.data();

    ani_size bytes_written = 0;
    env->String_GetUTF8(ani_str, utf8Buffer, strSize + 1, &bytes_written);

    utf8Buffer[bytes_written] = '\0';
    std::string content = std::string(utf8Buffer);
    return content;
}

static void On([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object, ani_string type, ani_fn_object fnObj)
{
    if (fnObj == nullptr) {
        LOGE("observer-ani callback is undefined.");
        return;
    }
    std::string typeStr = ANIUtils_ANIStringToStdString(env, type);
    auto* observer = Unwrapp(env, object);
    if (observer == nullptr) {
        LOGE("observer-ani context is null.");
        return;
    }
    ani_ref fnObjGlobalRef = nullptr;
    env->GlobalReference_Create(reinterpret_cast<ani_ref>(fnObj), &fnObjGlobalRef);
    observer->RegisterDensityCallback(100000, fnObjGlobalRef);
}

static void Off([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object, ani_string type, ani_fn_object fnObj)
{
    LOGE("lzr in off");
    auto* observer = Unwrapp(env, object);
    if (observer == nullptr) {
        LOGE("observer-ani context is null.");
        return;
    }
    ani_ref fnObjGlobalRef = nullptr;
    env->GlobalReference_Create(reinterpret_cast<ani_ref>(fnObj), &fnObjGlobalRef);
    observer->UnRegisterDensityCallback(env, 100000, fnObjGlobalRef);
}

static ani_object CreateObserver([[maybe_unused]] ani_env* env, ani_int id)
{
    ani_class cls;
    if (ANI_OK != env->FindClass(ANI_OBSERVER_CLS, &cls)) {
        LOGE("observer-ani not found class");
        return nullptr;
    }

    ani_method ctor;
    if (ANI_OK != env->Class_FindMethod(cls, "<ctor>", nullptr, &ctor)) {
        LOGE("observer-ani can not get construct method.");
        return nullptr;
    }

    auto* observer = new UiObserver(id);
    auto densityChangeCallback = [observer, env](NG::AbilityContextInfo& info, double density) {
        observer->HandleDensityChange(env, density);
    };
    NG::UIObserverHandler::GetInstance().SetHandleDensityChangeFuncForAni(densityChangeCallback);
    ani_object context_object;
    if (ANI_OK != env->Object_New(cls, ctor, &context_object, reinterpret_cast<ani_long>(observer))) {
        LOGE("observer-ani Can not new object.");
        return nullptr;
    }
    return context_object;
}
} // namespace OHOS::Ace
bool ANI_ConstructorForAni(ani_env* env)
{
    ani_namespace ns;
    if (ANI_OK != env->FindNamespace(ANI_OBSERVER_NS, &ns)) {
        LOGE("observer-ani Not found ns");
        return false;
    }
    std::array methods = {
        ani_native_function { "createUIObserver", nullptr, reinterpret_cast<void*>(OHOS::Ace::CreateObserver) },
    };

    if (ANI_OK != env->Namespace_BindNativeFunctions(ns, methods.data(), methods.size())) {
        LOGE("observer-ani Namespace_BindNativeFunctions error");
        return false;
    }

    ani_class clsObserver;
    if (ANI_OK != env->FindClass(ANI_OBSERVER_CLS, &clsObserver)) {
        LOGE("observer-ani not found class");
        return false;
    }

    std::array methodsObserver = {
        ani_native_function { "on", nullptr, reinterpret_cast<void*>(OHOS::Ace::On) },
        ani_native_function { "off", nullptr, reinterpret_cast<void*>(OHOS::Ace::Off) },
    };
    if (ANI_OK != env->Class_BindNativeMethods(clsObserver, methodsObserver.data(), methodsObserver.size())) {
        return false;
    }
    return true;
}

ANI_EXPORT ani_status ANI_Constructor(ani_vm* vm, uint32_t* result)
{
    ani_env* env;
    if (ANI_OK != vm->GetEnv(ANI_VERSION_1, &env)) {
        LOGE("observer-ani Unsupported ANI_VERSION_1");
        return ANI_ERROR;
    }
    if (ANI_ConstructorForAni(env)) {
        *result = ANI_VERSION_1;
        return ANI_OK;
    }
    return ANI_ERROR;
}
