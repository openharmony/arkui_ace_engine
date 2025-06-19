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
#include <string>
#include <unistd.h>
#include "base/log/log_wrapper.h"
#include "base/memory/ace_type.h"
#include "bridge/arkts_frontend/arkts_frontend.h"
#include "core/components_ng/base/inspector.h"
#include "core/pipeline_ng/pipeline_context.h"
 
namespace {
const char LAYOUT_TYPE[] = "layout";
const char DRAW_TYPE[] = "draw";
const char ANI_INSPECTOR_NS[] = "L@ohos/arkui/inspector/inspector;";
const char ANI_COMPONENT_OBSERVER_CLS[] = "L@ohos/arkui/inspector/inspector/ComponentObserverImpl;";
const char KOALA_INSPECTOR_CLS[] = "L@koalaui/arkts-arkui/generated/arkts/ohos/arkui/inspector/Inspector;";
const char KOALA_COMPONENT_CLS[] = "L@koalaui/arkts-arkui/generated/arkts/ohos/arkui/inspector/ComponentObserver;";
} // namespace
 
namespace OHOS::Ace {
class ComponentObserver {
public:
    explicit ComponentObserver(std::string key): id_(key) {}
    
    static RefPtr<ArktsFrontend> getFronted()
    {
        auto context = NG::PipelineContext::GetCurrentContextSafely();
        if (context == nullptr) {
            LOGE("inspector-ani can not get current context.");
            return nullptr;
        }
        auto frontend = context->GetFrontend();
        if (frontend == nullptr) {
            LOGE("inspector-ani can not get current frontend.");
            return nullptr;
        }
        auto arkTsFrontend = AceType::DynamicCast<ArktsFrontend>(frontend);
        if (frontend == nullptr) {
            LOGE("inspector-ani can not convert to arkts frontend.");
            return nullptr;
        }
        return arkTsFrontend;
    }
    
    std::list<ani_ref>::iterator FindCbList(ani_ref& cb, const std::string& eventType, ani_env* env)
    {
        if (strcmp(LAYOUT_TYPE, eventType.c_str()) == 0) {
            return std::find_if(cbLayoutList_.begin(), cbLayoutList_.end(), [env, cb](const ani_ref& item) -> bool {
                ani_boolean rs;
                env->Reference_StrictEquals(cb, item, &rs);
                return rs == ANI_TRUE;
            });
        } else {
            return std::find_if(cbDrawList_.begin(), cbDrawList_.end(), [env, cb](const ani_ref& item) -> bool {
                ani_boolean rs;
                env->Reference_StrictEquals(cb, item, &rs);
                return rs == ANI_TRUE;
            });
        }
    }
    
    void AddCallbackToList(std::list<ani_ref>& fnList, ani_ref& cb, const std::string& eventType, ani_env* env)
    {
        auto iter = FindCbList(cb, eventType, env);
        if (iter != fnList.end()) {
            return;
        }
        LOGI("inspector-ani add %{public}s call back on %{public}s", eventType.c_str(), id_.c_str());
        fnList.emplace_back(cb);
    }
    
    void RemoveCallbackToList(std::list<ani_ref>& fnList, ani_ref& cb, const std::string& eventType, ani_env* env)
    {
        if (cb == nullptr) {
            LOGW("inspector-ani start to clear all %{public}s callback list", eventType.c_str());
            for (auto& ref : fnList) {
                env->GlobalReference_Delete(ref);
            }
            fnList.clear();
        } else {
            auto iter = FindCbList(cb, eventType, env);
            if (iter != fnList.end()) {
                auto& deleteRef = *iter;
                fnList.erase(iter);
                env->GlobalReference_Delete(deleteRef);
            }
        }
        if (fnList.empty()) {
            auto arkTsFrontend = ComponentObserver::getFronted();
            if (arkTsFrontend == nullptr) {
                LOGE("inspector-ani Can not convert to arkts frontend.");
                return;
            }
            if (strcmp(LAYOUT_TYPE, eventType.c_str()) == 0) {
                arkTsFrontend->UnregisterLayoutInspectorCallback(id_);
            } else {
                arkTsFrontend->UnregisterDrawInspectorCallback(id_);
            }
        }
    }
    
    void CallUserFunction(ani_env* env, std::list<ani_ref>& cbList)
    {
        std::vector<ani_ref> vec;
        ani_ref fnReturnVal;
        for (auto& cb : cbList) {
            LOGD("inspector-ani start to call user function for component %{public}s", id_.c_str());
            env->FunctionalObject_Call(reinterpret_cast<ani_fn_object>(cb), vec.size(), vec.data(), &fnReturnVal);
        }
    }
    
    std::list<ani_ref>&  GetCbListByType(const std::string& eventType)
    {
        if (strcmp(LAYOUT_TYPE, eventType.c_str()) == 0) {
            return cbLayoutList_;
        }
        return cbDrawList_;
    }
    
    RefPtr<InspectorEvent> GetInspectorFuncByType(const std::string& eventType)
    {
        if (strcmp(LAYOUT_TYPE, eventType.c_str()) == 0) {
            return layoutEvent_;
        }
        return drawEvent_;
    }
    
    void SetInspectorFuncByType(const std::string& eventType, const RefPtr<InspectorEvent>& fun)
    {
        if (strcmp(LAYOUT_TYPE, eventType.c_str()) == 0) {
            layoutEvent_ = fun;
        } else {
            drawEvent_ = fun;
        }
    }
private:
    std::string id_;
    std::list<ani_ref> cbLayoutList_;
    std::list<ani_ref> cbDrawList_;
    RefPtr<InspectorEvent> layoutEvent_;
    RefPtr<InspectorEvent> drawEvent_;
};

static ComponentObserver* Unwrapp(ani_env *env, ani_object object)
{
    ani_long nativeAddr;
    if (ANI_OK != env->Object_GetFieldByName_Long(object, "nativeComponentObserver", &nativeAddr)) {
        return nullptr;
    }
    return reinterpret_cast<ComponentObserver *>(nativeAddr);
}

std::string ANIUtils_ANIStringToStdString(ani_env *env, ani_string ani_str)
{
    ani_size strSize;
    env->String_GetUTF8Size(ani_str, &strSize);
   
    std::vector<char> buffer(strSize + 1); // +1 for null terminator
    char* utf8Buffer = buffer.data();

    ani_size bytes_written = 0;
    env->String_GetUTF8(ani_str, utf8Buffer, strSize + 1, &bytes_written);
    
    utf8Buffer[bytes_written] = '\0';
    std::string content = std::string(utf8Buffer);
    return content;
}

static void On([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_string type, ani_fn_object fnObj)
{
    if (fnObj == nullptr) {
        LOGE("inspector-ani callback is undefined.");
        return;
    }
    std::string typeStr = ANIUtils_ANIStringToStdString(env, type);
    if (strcmp(LAYOUT_TYPE, typeStr.c_str()) != 0 && strcmp(DRAW_TYPE, typeStr.c_str()) != 0) {
        LOGE("inspector-ani method on not support event type %{public}s", typeStr.c_str());
        return;
    }
    
    auto *observer = Unwrapp(env, object);
    if (observer == nullptr) {
        LOGE("inspector-ani context is null.");
        return;
    }
    ani_ref fnObjGlobalRef = nullptr;
    env->GlobalReference_Create(reinterpret_cast<ani_ref>(fnObj), &fnObjGlobalRef);
    observer->AddCallbackToList(observer->GetCbListByType(typeStr), fnObjGlobalRef, typeStr, env);
}

static void Off([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_string type, ani_fn_object fnObj)
{
    std::string typeStr = ANIUtils_ANIStringToStdString(env, type);
    if (strcmp(LAYOUT_TYPE, typeStr.c_str()) != 0 && strcmp(DRAW_TYPE, typeStr.c_str()) != 0) {
        LOGE("inspector-ani method on not support event type %{public}s", typeStr.c_str());
        return;
    }
    
    auto *observer = Unwrapp(env, object);
    if (observer == nullptr) {
        LOGE("inspector-ani context is null.");
        return;
    }
    ani_ref fnObjGlobalRef = nullptr;
    env->GlobalReference_Create(reinterpret_cast<ani_ref>(fnObj), &fnObjGlobalRef);
    observer->RemoveCallbackToList(observer->GetCbListByType(typeStr), fnObjGlobalRef, typeStr, env);
}

static ani_string AniGetInspectorByKey([[maybe_unused]] ani_env *env, ani_string key)
{
    std::string keyStr = ANIUtils_ANIStringToStdString(env, key);
    if (keyStr.empty()) {
        LOGE("inspector-ani key is empty.");
        return nullptr;
    }
    std::string resultStr = NG::Inspector::GetInspectorNodeByKey(keyStr);
    if (resultStr.empty()) {
        LOGE("inspector-ani node %{public}s is empty.", keyStr.c_str());
        return nullptr;
    }
    ani_string ani_str;
    ani_status status = env->String_NewUTF8(resultStr.c_str(), resultStr.size(), &ani_str);
    if (ANI_OK != status) {
        LOGE("inspector-ani Can not convert string to ani_string.");
        return nullptr;
    }
    return ani_str;
}

static ani_object CreateComponentObserver([[maybe_unused]] ani_env *env, ani_string id, const char *className)
{
    ani_class cls;
    if (ANI_OK != env->FindClass(className, &cls)) {
        LOGE("inspector-ani not found class");
        return nullptr;
    }
    
    ani_method ctor;
    if (ANI_OK != env->Class_FindMethod(cls, "<ctor>", nullptr, &ctor)) {
        LOGE("inspector-ani can not get construct method.");
        return nullptr;
    }
    
    std::string key = ANIUtils_ANIStringToStdString(env, id);
    LOGI("inspector-ani start to CreateComponentObserver key is %{public}s", key.c_str());
    auto* observer = new ComponentObserver(key);
    
    auto arkTsFrontend = ComponentObserver::getFronted();
    if (arkTsFrontend == nullptr) {
        LOGE("inspector-ani Can not convert to arkts frontend.");
        return nullptr;
    }
    
    ani_object context_object;
    if (ANI_OK != env->Object_New(cls, ctor, &context_object, reinterpret_cast<ani_long>(observer))) {
        LOGE("inspector-ani Can not new object.");
        return nullptr;
    }
    
    auto layoutCallback = [observer, env]() -> void {
        observer->CallUserFunction(env, observer->GetCbListByType(LAYOUT_TYPE));
    };
    observer->SetInspectorFuncByType(LAYOUT_TYPE, AceType::MakeRefPtr<InspectorEvent>(std::move(layoutCallback)));
    
    auto drawCallback = [observer, env]() -> void {
        observer->CallUserFunction(env, observer->GetCbListByType(DRAW_TYPE));
    };
    observer->SetInspectorFuncByType(DRAW_TYPE, AceType::MakeRefPtr<InspectorEvent>(std::move(drawCallback)));
    
    arkTsFrontend->RegisterLayoutInspectorCallback(observer->GetInspectorFuncByType(LAYOUT_TYPE), key);
    arkTsFrontend->RegisterDrawInspectorCallback(observer->GetInspectorFuncByType(DRAW_TYPE), key);
    return context_object;
}

static ani_object CreateComponentObserverForAni([[maybe_unused]] ani_env *env, ani_string id)
{
    return CreateComponentObserver(env, id, ANI_COMPONENT_OBSERVER_CLS);
}

static ani_object CreateComponentObserverForKoala([[maybe_unused]] ani_env *env,
    [[maybe_unused]] ani_object object, ani_string id)
{
    return CreateComponentObserver(env, id, KOALA_COMPONENT_CLS);
}
} // namespace OHOS::Ace

bool ANI_ConstructorForAni(ani_env *env)
{
    ani_namespace ns;
    if (ANI_OK != env->FindNamespace(ANI_INSPECTOR_NS, &ns)) {
        LOGE("inspector-ani Not found ns");
        return false;
    }
    std::array methods = {
        ani_native_function {"createComponentObserver", nullptr,
            reinterpret_cast<void *>(OHOS::Ace::CreateComponentObserverForAni)},
        ani_native_function {"getInspectorByKey", nullptr,
            reinterpret_cast<void *>(OHOS::Ace::AniGetInspectorByKey)},
    };
    
    if (ANI_OK != env->Namespace_BindNativeFunctions(ns, methods.data(), methods.size())) {
        LOGE("inspector-ani Namespace_BindNativeFunctions error");
        return false;
    }
    
    ani_class clsInspector;
    if (ANI_OK != env->FindClass(ANI_COMPONENT_OBSERVER_CLS, &clsInspector)) {
        LOGE("inspector-ani not found class");
        return false;
    }
    
    std::array methodsInspector = {
        ani_native_function {"on", nullptr, reinterpret_cast<void *>(OHOS::Ace::On)},
        ani_native_function {"off", nullptr, reinterpret_cast<void *>(OHOS::Ace::Off)},
    };
    
    if (ANI_OK != env->Class_BindNativeMethods(clsInspector, methodsInspector.data(), methodsInspector.size())) {
        LOGE("inspector-ani Class_BindNativeFunctions error");
        return false;
    }
    return true;
}

bool ANI_ConstructorForKoala(ani_env *env)
{
    ani_class clsInspector;
    if (ANI_OK != env->FindClass(KOALA_INSPECTOR_CLS, &clsInspector)) {
        LOGE("inspector-koala not found class");
        return false;
    }
    std::array methodsInspector = {
        ani_native_function {"createComponentObserver", nullptr,
            reinterpret_cast<void *>(OHOS::Ace::CreateComponentObserverForKoala)},
    };
    if (ANI_OK != env->Class_BindNativeMethods(clsInspector, methodsInspector.data(), methodsInspector.size())) {
        LOGE("inspector-koala Class_BindNativeFunctions error");
        return false;
    }
    
    ani_class clsObserver;
    if (ANI_OK != env->FindClass(KOALA_COMPONENT_CLS, &clsObserver)) {
        LOGE("inspector-koala not found class");
        return false;
    }
    std::array methodsObserver = {
        ani_native_function {"on", nullptr, reinterpret_cast<void *>(OHOS::Ace::On)},
        ani_native_function {"off", nullptr, reinterpret_cast<void *>(OHOS::Ace::Off)},
    };
    if (ANI_OK != env->Class_BindNativeMethods(clsObserver, methodsObserver.data(), methodsObserver.size())) {
        LOGE("inspector-koala Class_BindNativeFunctions error");
        return false;
    }
    return true;
}

ANI_EXPORT ani_status ANI_Constructor(ani_vm *vm, uint32_t *result)
{
    ani_env *env;
    if (ANI_OK != vm->GetEnv(ANI_VERSION_1, &env)) {
        LOGE("inspector-ani Unsupported ANI_VERSION_1");
        return ANI_ERROR;
    }
    if (ANI_ConstructorForAni(env) || ANI_ConstructorForKoala(env)) {
        *result = ANI_VERSION_1;
        return ANI_OK;
    }
    return ANI_ERROR;
}