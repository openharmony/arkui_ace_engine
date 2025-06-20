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
            TAG_LOGE(AceLogTag::ACE_LAYOUT_INSPECTOR, "inspector-ani can not get current context.");
            return nullptr;
        }
        auto frontend = context->GetFrontend();
        if (frontend == nullptr) {
            TAG_LOGE(AceLogTag::ACE_LAYOUT_INSPECTOR, "inspector-ani can not get current frontend.");
            return nullptr;
        }
        auto arkTsFrontend = AceType::DynamicCast<ArktsFrontend>(frontend);
        if (frontend == nullptr) {
            TAG_LOGE(AceLogTag::ACE_LAYOUT_INSPECTOR, "inspector-ani can not convert to arkts frontend.");
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
        TAG_LOGI(AceLogTag::ACE_LAYOUT_INSPECTOR, "inspector-ani add %{public}s call back on %{public}s",
            eventType.c_str(), id_.c_str());
        fnList.emplace_back(cb);
    }
    
    void RemoveCallbackToList(std::list<ani_ref>& fnList, ani_ref& cb, const std::string& eventType, ani_env* env)
    {
        if (cb == nullptr) {
            TAG_LOGW(AceLogTag::ACE_LAYOUT_INSPECTOR, "inspector-ani start to clear all %{public}s callback list",
                eventType.c_str());
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
                TAG_LOGE(AceLogTag::ACE_LAYOUT_INSPECTOR, "inspector-ani Can not convert to arkts frontend.");
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
            TAG_LOGD(AceLogTag::ACE_LAYOUT_INSPECTOR,
                "inspector-ani start to call user function for component %{public}s", id_.c_str());
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

ani_status ANIUtils_ANIStringToStdString(ani_env *env, ani_string ani_str, std::string& str)
{
    ani_size strSize;
    ani_status status = env->String_GetUTF8Size(ani_str, &strSize);
    if (status != ANI_OK) {
        TAG_LOGE(AceLogTag::ACE_LAYOUT_INSPECTOR, "inspector-ani String_GetUTF8Size failed %{public}d.", status);
        return status;
    }
   
    std::vector<char> buffer(strSize + 1); // +1 for null terminator
    char* utf8Buffer = buffer.data();

    ani_size bytes_written = 0;
    status = env->String_GetUTF8(ani_str, utf8Buffer, buffer.size(), &bytes_written);
    if (status != ANI_OK) {
        TAG_LOGE(AceLogTag::ACE_LAYOUT_INSPECTOR, "inspector-ani String_GetUTF8 failed %{public}d.", status);
        return status;
    }
    
    utf8Buffer[bytes_written] = '\0';
    str = std::string(utf8Buffer);
    return status;
}

static void On(ani_env *env, ani_object object, ani_string type, ani_fn_object fnObj)
{
    if (fnObj == nullptr) {
        TAG_LOGE(AceLogTag::ACE_LAYOUT_INSPECTOR, "inspector-ani callback is undefined.");
        return;
    }
    std::string typeStr;
    ANIUtils_ANIStringToStdString(env, type, typeStr);
    if (strcmp(LAYOUT_TYPE, typeStr.c_str()) != 0 && strcmp(DRAW_TYPE, typeStr.c_str()) != 0) {
        TAG_LOGE(AceLogTag::ACE_LAYOUT_INSPECTOR, "inspector-ani method on not support event type %{public}s",
            typeStr.c_str());
        return;
    }
    
    auto *observer = Unwrapp(env, object);
    if (observer == nullptr) {
        TAG_LOGE(AceLogTag::ACE_LAYOUT_INSPECTOR, "inspector-ani context is null.");
        return;
    }
    ani_ref fnObjGlobalRef = nullptr;
    env->GlobalReference_Create(reinterpret_cast<ani_ref>(fnObj), &fnObjGlobalRef);
    observer->AddCallbackToList(observer->GetCbListByType(typeStr), fnObjGlobalRef, typeStr, env);
}

static void Off(ani_env *env, ani_object object, ani_string type, ani_fn_object fnObj)
{
    std::string typeStr;
    ANIUtils_ANIStringToStdString(env, type, typeStr);
    if (strcmp(LAYOUT_TYPE, typeStr.c_str()) != 0 && strcmp(DRAW_TYPE, typeStr.c_str()) != 0) {
        TAG_LOGE(AceLogTag::ACE_LAYOUT_INSPECTOR, "inspector-ani method on not support event type %{public}s",
            typeStr.c_str());
        return;
    }
    
    auto *observer = Unwrapp(env, object);
    if (observer == nullptr) {
        TAG_LOGE(AceLogTag::ACE_LAYOUT_INSPECTOR, "inspector-ani context is null.");
        return;
    }
    ani_ref fnObjGlobalRef = nullptr;
    env->GlobalReference_Create(reinterpret_cast<ani_ref>(fnObj), &fnObjGlobalRef);
    observer->RemoveCallbackToList(observer->GetCbListByType(typeStr), fnObjGlobalRef, typeStr, env);
}

static ani_boolean AniSendEventByKey(ani_env *env, ani_string id, ani_double action, ani_string params)
{
    std::string keyStr;
    ani_status status = ANIUtils_ANIStringToStdString(env, id, keyStr);
    if (status != ANI_OK) {
        TAG_LOGE(AceLogTag::ACE_LAYOUT_INSPECTOR, "inspector-ani get send event key error.");
        return ANI_FALSE;
    }
    std::string paramsStr;
    status = ANIUtils_ANIStringToStdString(env, params, paramsStr);
    if (status != ANI_OK) {
        TAG_LOGE(AceLogTag::ACE_LAYOUT_INSPECTOR, "inspector-ani get send event params error.");
        return ANI_FALSE;
    }
    ContainerScope scope {Container::CurrentIdSafelyWithCheck()};
    bool result = NG::Inspector::SendEventByKey(keyStr, action, paramsStr);
    if (result) {
        return ANI_TRUE;
    }
    return ANI_FALSE;
}

static ani_object AniGetInspectorTree(ani_env *env)
{
    ContainerScope scope {Container::CurrentIdSafelyWithCheck()};
    std::string resultStr = NG::Inspector::GetInspector(false);
    if (resultStr.empty()) {
        TAG_LOGE(AceLogTag::ACE_LAYOUT_INSPECTOR, "inspector-ani inspector tree is empty.");
        return nullptr;
    }
    ani_string aniResult;
    ani_status status = env->String_NewUTF8(resultStr.c_str(), resultStr.size(), &aniResult);
    if (ANI_OK != status) {
        TAG_LOGE(AceLogTag::ACE_LAYOUT_INSPECTOR, "inspector-ani Can not convert string to ani_string.");
        return nullptr;
    }
    return aniResult;
}

static ani_string AniGetInspectorByKey(ani_env *env, ani_string key)
{
    std::string keyStr;
    ani_status getStdStringStatus = ANIUtils_ANIStringToStdString(env, key, keyStr);
    if (getStdStringStatus != ANI_OK) {
        TAG_LOGE(AceLogTag::ACE_LAYOUT_INSPECTOR, "inspector-ani get key failed.");
        return nullptr;
    }
    ContainerScope scope{Container::CurrentIdSafelyWithCheck()};
    std::string resultStr = NG::Inspector::GetInspectorNodeByKey(keyStr);
    if (resultStr.empty()) {
        TAG_LOGE(AceLogTag::ACE_LAYOUT_INSPECTOR, "inspector-ani node %{public}s is empty.", keyStr.c_str());
        return nullptr;
    }
    ani_string ani_str;
    ani_status status = env->String_NewUTF8(resultStr.c_str(), resultStr.size(), &ani_str);
    if (ANI_OK != status) {
        TAG_LOGE(AceLogTag::ACE_LAYOUT_INSPECTOR, "inspector-ani Can not convert string to ani_string.");
        return nullptr;
    }
    return ani_str;
}

static ani_object CreateComponentObserver(ani_env *env, ani_string id, const char *className)
{
    ani_class cls;
    if (ANI_OK != env->FindClass(className, &cls)) {
        TAG_LOGE(AceLogTag::ACE_LAYOUT_INSPECTOR, "inspector-ani not found class");
        return nullptr;
    }
    
    ani_method ctor;
    if (ANI_OK != env->Class_FindMethod(cls, "<ctor>", nullptr, &ctor)) {
        TAG_LOGE(AceLogTag::ACE_LAYOUT_INSPECTOR, "inspector-ani can not get construct method.");
        return nullptr;
    }
    
    std::string key;
    ani_status status = ANIUtils_ANIStringToStdString(env, id, key);
    if (status != ANI_OK) {
        TAG_LOGE(AceLogTag::ACE_LAYOUT_INSPECTOR, "inspector-ani get key of observer failed.");
        return nullptr;
    }
    TAG_LOGI(AceLogTag::ACE_LAYOUT_INSPECTOR, "inspector-ani start to CreateComponentObserver key is %{public}s",
        key.c_str());
    
    auto arkTsFrontend = ComponentObserver::getFronted();
    if (arkTsFrontend == nullptr) {
        TAG_LOGE(AceLogTag::ACE_LAYOUT_INSPECTOR, "inspector-ani Can not convert to arkts frontend.");
        return nullptr;
    }
    auto* observer = new ComponentObserver(key);
    
    ani_object context_object;
    if (ANI_OK != env->Object_New(cls, ctor, &context_object, reinterpret_cast<ani_long>(observer))) {
        TAG_LOGE(AceLogTag::ACE_LAYOUT_INSPECTOR, "inspector-ani Can not new object.");
        delete observer;
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

static ani_object CreateComponentObserverForAni(ani_env *env, ani_string id)
{
    return CreateComponentObserver(env, id, ANI_COMPONENT_OBSERVER_CLS);
}

static ani_object CreateComponentObserverForKoala(ani_env *env, [[maybe_unused]] ani_object object, ani_string id)
{
    return CreateComponentObserver(env, id, KOALA_COMPONENT_CLS);
}
} // namespace OHOS::Ace

bool ANI_ConstructorForAni(ani_env *env)
{
    ani_namespace ns;
    if (ANI_OK != env->FindNamespace(ANI_INSPECTOR_NS, &ns)) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_LAYOUT_INSPECTOR, "inspector-ani Not found ns");
        return false;
    }
    std::array methods = {
        ani_native_function {"createComponentObserver", nullptr,
            reinterpret_cast<void *>(OHOS::Ace::CreateComponentObserverForAni)},
        ani_native_function {"getInspectorByKey", nullptr,
            reinterpret_cast<void *>(OHOS::Ace::AniGetInspectorByKey)},
        ani_native_function {"sendEventByKey", nullptr,
            reinterpret_cast<void *>(OHOS::Ace::AniSendEventByKey)},
        ani_native_function {"getInspectorTree", nullptr,
            reinterpret_cast<void *>(OHOS::Ace::AniGetInspectorTree)},
    };
    
    if (ANI_OK != env->Namespace_BindNativeFunctions(ns, methods.data(), methods.size())) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_LAYOUT_INSPECTOR, "inspector-ani Namespace_BindNativeFunctions error");
        return false;
    }
    
    ani_class clsInspector;
    if (ANI_OK != env->FindClass(ANI_COMPONENT_OBSERVER_CLS, &clsInspector)) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_LAYOUT_INSPECTOR, "inspector-ani not found class");
        return false;
    }
    
    std::array methodsInspector = {
        ani_native_function {"on", nullptr, reinterpret_cast<void *>(OHOS::Ace::On)},
        ani_native_function {"off", nullptr, reinterpret_cast<void *>(OHOS::Ace::Off)},
    };
    
    if (ANI_OK != env->Class_BindNativeMethods(clsInspector, methodsInspector.data(), methodsInspector.size())) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_LAYOUT_INSPECTOR, "inspector-ani Class_BindNativeFunctions error");
        return false;
    }
    return true;
}

bool ANI_ConstructorForKoala(ani_env *env)
{
    ani_class clsInspector;
    if (ANI_OK != env->FindClass(KOALA_INSPECTOR_CLS, &clsInspector)) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_LAYOUT_INSPECTOR, "inspector-koala not found class");
        return false;
    }
    std::array methodsInspector = {
        ani_native_function {"createComponentObserver", nullptr,
            reinterpret_cast<void *>(OHOS::Ace::CreateComponentObserverForKoala)},
    };
    if (ANI_OK != env->Class_BindNativeMethods(clsInspector, methodsInspector.data(), methodsInspector.size())) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_LAYOUT_INSPECTOR, "inspector-koala Class_BindNativeFunctions error");
        return false;
    }
    
    ani_class clsObserver;
    if (ANI_OK != env->FindClass(KOALA_COMPONENT_CLS, &clsObserver)) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_LAYOUT_INSPECTOR, "inspector-koala not found class");
        return false;
    }
    std::array methodsObserver = {
        ani_native_function {"on", nullptr, reinterpret_cast<void *>(OHOS::Ace::On)},
        ani_native_function {"off", nullptr, reinterpret_cast<void *>(OHOS::Ace::Off)},
    };
    if (ANI_OK != env->Class_BindNativeMethods(clsObserver, methodsObserver.data(), methodsObserver.size())) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_LAYOUT_INSPECTOR, "inspector-koala Class_BindNativeFunctions error");
        return false;
    }
    return true;
}

ANI_EXPORT ani_status ANI_Constructor(ani_vm *vm, uint32_t *result)
{
    ani_env *env;
    if (ANI_OK != vm->GetEnv(ANI_VERSION_1, &env)) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_LAYOUT_INSPECTOR, "inspector-ani Unsupported ANI_VERSION_1");
        return ANI_ERROR;
    }
    if (ANI_ConstructorForAni(env) || ANI_ConstructorForKoala(env)) {
        *result = ANI_VERSION_1;
        return ANI_OK;
    }
    return ANI_ERROR;
}