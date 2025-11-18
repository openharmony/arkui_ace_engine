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
#include "base/error/error_code.h"
#include "base/log/log_wrapper.h"
#include "base/memory/ace_type.h"
#include "bridge/arkts_frontend/arkts_frontend.h"
#include "core/components_ng/base/inspector.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "inspector_util.h"
 
namespace {
const char LAYOUT_TYPE[] = "layout";
const char DRAW_TYPE[] = "draw";
const char DRAW_CHILDREN_TYPE[] = "drawChildren";
const char ANI_INSPECTOR_NS[] = "@ohos.arkui.inspector.inspector";
const char ANI_COMPONENT_OBSERVER_CLS[] = "@ohos.arkui.inspector.inspector.ComponentObserver";
const char KOALA_INSPECTOR_CLS[] = "@koalaui.arkts-arkui.generated.arkts.ohos.arkui.inspector.Inspector";
const char KOALA_COMPONENT_CLS[] = "@koalaui.arkts-arkui.generated.arkts.ohos.arkui.inspector.ComponentObserver";
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
        if (LAYOUT_TYPE == eventType) {
            return std::find_if(cbLayoutList_.begin(), cbLayoutList_.end(), [env, cb](const ani_ref& item) -> bool {
                ani_boolean rs;
                env->Reference_StrictEquals(cb, item, &rs);
                return rs == ANI_TRUE;
            });
        } else if (DRAW_CHILDREN_TYPE == eventType) {
            return std::find_if(cbDrawChildrenList_.begin(), cbDrawChildrenList_.end(),
                [env, cb](const ani_ref& item) -> bool {
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
            if (LAYOUT_TYPE == eventType) {
                arkTsFrontend->UnregisterLayoutInspectorCallback(id_);
            } else if (DRAW_CHILDREN_TYPE == eventType) {
                arkTsFrontend->UnregisterDrawChildrenInspectorCallback(id_);
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
        if (LAYOUT_TYPE == eventType) {
            return cbLayoutList_;
        } else if (DRAW_CHILDREN_TYPE == eventType) {
            return cbDrawChildrenList_;
        }
        return cbDrawList_;
    }
    
    RefPtr<InspectorEvent> GetInspectorFuncByType(const std::string& eventType)
    {
        if (LAYOUT_TYPE == eventType) {
            return layoutEvent_;
        } else if (DRAW_CHILDREN_TYPE == eventType) {
            return drawChildrenEvent_;
        }
        return drawEvent_;
    }
    
    void SetInspectorFuncByType(const std::string& eventType, const RefPtr<InspectorEvent>& fun)
    {
        if (LAYOUT_TYPE == eventType) {
            layoutEvent_ = fun;
        } else if (DRAW_CHILDREN_TYPE == eventType) {
            drawChildrenEvent_ = fun;
        } else {
            drawEvent_ = fun;
        }
    }
private:
    std::string id_;
    std::list<ani_ref> cbLayoutList_;
    std::list<ani_ref> cbDrawList_;
    std::list<ani_ref> cbDrawChildrenList_;
    RefPtr<InspectorEvent> layoutEvent_;
    RefPtr<InspectorEvent> drawEvent_;
    RefPtr<InspectorEvent> drawChildrenEvent_;
};

static ComponentObserver* Unwrapp(ani_env *env, ani_object object)
{
    ani_long nativeAddr;
    if (ANI_OK != env->Object_GetFieldByName_Long(object, "nativeComponentObserver", &nativeAddr)) {
        return nullptr;
    }
    return reinterpret_cast<ComponentObserver *>(nativeAddr);
}

static void On(ani_env *env, ani_object object, ani_string type, ani_fn_object fnObj)
{
    if (fnObj == nullptr) {
        TAG_LOGE(AceLogTag::ACE_LAYOUT_INSPECTOR, "inspector-ani callback is undefined.");
        return;
    }
    std::string typeStr;
    ANIUtils_ANIStringToStdString(env, type, typeStr);
    if (LAYOUT_TYPE != typeStr && DRAW_TYPE != typeStr && DRAW_CHILDREN_TYPE != typeStr) {
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
    if (LAYOUT_TYPE != typeStr && DRAW_TYPE != typeStr && DRAW_CHILDREN_TYPE != typeStr) {
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

static ani_boolean AniSendEventByKey(ani_env *env, ani_string id, ani_int action, ani_string params)
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

static ani_string AniGetInspectorTree(ani_env *env)
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

static ani_string AniGetFilteredInspectorTree(ani_env *env, ani_array filters)
{
    bool isLayoutInspector = false;
    const NG::InspectorFilter& inspectorFilter = GetInspectorFilter(env, filters, isLayoutInspector);
    ContainerScope scope{Container::CurrentIdSafelyWithCheck()};
    bool needThrow = false;
    auto nodeInfos = NG::Inspector::GetInspector(isLayoutInspector, inspectorFilter, needThrow);
    if (needThrow) {
        AniThrow(env, "Unable to obtain current ui context", ERROR_CODE_PARAM_ERROR);
        return nullptr;
    }
    ani_string result;
    if (ANI_OK != env->String_NewUTF8(nodeInfos.c_str(), nodeInfos.size(), &result)) {
        TAG_LOGE(AceLogTag::ACE_LAYOUT_INSPECTOR, "get filter inspector tree failed");
        return nullptr;
    }
    return result;
}
 
static ani_string AniGetFilteredInspectorTreeById(ani_env *env, ani_string id, ani_int depth, ani_array filters)
{
    if (depth < 0) {
        AniThrow(env, "The parameter depth must be greater than 0.",
            ERROR_CODE_INSPECTOR_PARAM_DEPTH_INVALID);
        return nullptr;
    }
    bool isLayoutInspector = false;
    NG::InspectorFilter inspectorFilter = GetInspectorFilter(env, filters, isLayoutInspector);
    std::string idStr;
    if (ANI_OK != ANIUtils_ANIStringToStdString(env, id, idStr)) {
        TAG_LOGE(AceLogTag::ACE_LAYOUT_INSPECTOR, "get filter inspector tree failed");
        return nullptr;
    }
    inspectorFilter.SetFilterID(idStr);
    inspectorFilter.SetFilterDepth(depth);
    ContainerScope scope{Container::CurrentIdSafelyWithCheck()};
    bool needThrow = false;
    auto nodeInfos = NG::Inspector::GetInspector(false, inspectorFilter, needThrow);
    if (needThrow) {
        AniThrow(env, "Unable to obtain current UI context", ERROR_CODE_PARAM_ERROR);
        return nullptr;
    }
    ani_string result;
    if (ANI_OK != env->String_NewUTF8(nodeInfos.c_str(), nodeInfos.size(), &result)) {
        TAG_LOGE(AceLogTag::ACE_LAYOUT_INSPECTOR, "get filter inspector tree failed");
        return nullptr;
    }
    return result;
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

static ani_ref CreateComponentObserver(ani_env *env, ani_string id, const char *className)
{
    ani_class cls;
    ani_ref undefinedRef {};
    env->GetUndefined(&undefinedRef);
    if (ANI_OK != env->FindClass(className, &cls)) {
        TAG_LOGE(AceLogTag::ACE_LAYOUT_INSPECTOR, "inspector-ani not found class");
        return undefinedRef;
    }
    
    ani_method ctor;
    if (ANI_OK != env->Class_FindMethod(cls, "<ctor>", nullptr, &ctor)) {
        TAG_LOGE(AceLogTag::ACE_LAYOUT_INSPECTOR, "inspector-ani can not get construct method.");
        return undefinedRef;
    }
    
    std::string key;
    ani_status status = ANIUtils_ANIStringToStdString(env, id, key);
    if (status != ANI_OK) {
        TAG_LOGE(AceLogTag::ACE_LAYOUT_INSPECTOR, "inspector-ani get key of observer failed.");
        return undefinedRef;
    }
    TAG_LOGI(AceLogTag::ACE_LAYOUT_INSPECTOR, "inspector-ani start to CreateComponentObserver key is %{public}s",
        key.c_str());
    
    auto arkTsFrontend = ComponentObserver::getFronted();
    if (arkTsFrontend == nullptr) {
        TAG_LOGE(AceLogTag::ACE_LAYOUT_INSPECTOR, "inspector-ani Can not convert to arkts frontend.");
        return undefinedRef;
    }
    auto* observer = new ComponentObserver(key);
    
    ani_object context_object;
    if (ANI_OK != env->Object_New(cls, ctor, &context_object, reinterpret_cast<ani_long>(observer))) {
        TAG_LOGE(AceLogTag::ACE_LAYOUT_INSPECTOR, "inspector-ani Can not new object.");
        delete observer;
        return undefinedRef;
    }
    
    auto layoutCallback = [observer, env]() -> void {
        observer->CallUserFunction(env, observer->GetCbListByType(LAYOUT_TYPE));
    };
    observer->SetInspectorFuncByType(LAYOUT_TYPE, AceType::MakeRefPtr<InspectorEvent>(std::move(layoutCallback)));
    
    auto drawCallback = [observer, env]() -> void {
        observer->CallUserFunction(env, observer->GetCbListByType(DRAW_TYPE));
    };
    observer->SetInspectorFuncByType(DRAW_TYPE, AceType::MakeRefPtr<InspectorEvent>(std::move(drawCallback)));
    
    auto drawChildrenCallback = [observer, env]() -> void {
        observer->CallUserFunction(env, observer->GetCbListByType(DRAW_CHILDREN_TYPE));
    };
    observer->SetInspectorFuncByType(DRAW_CHILDREN_TYPE,
        AceType::MakeRefPtr<InspectorEvent>(std::move(drawChildrenCallback)));

    arkTsFrontend->RegisterLayoutInspectorCallback(observer->GetInspectorFuncByType(LAYOUT_TYPE), key);
    arkTsFrontend->RegisterDrawInspectorCallback(observer->GetInspectorFuncByType(DRAW_TYPE), key);
    arkTsFrontend->RegisterDrawChildrenInspectorCallback(observer->GetInspectorFuncByType(DRAW_CHILDREN_TYPE), key);
    return context_object;
}

static ani_ref CreateComponentObserverForAni(ani_env *env, ani_string id)
{
    return CreateComponentObserver(env, id, ANI_COMPONENT_OBSERVER_CLS);
}

static ani_ref CreateComponentObserverForKoala(ani_env *env, [[maybe_unused]] ani_object object, ani_string id)
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
        ani_native_function {"getInspectorTreeNative", nullptr,
            reinterpret_cast<void *>(OHOS::Ace::AniGetInspectorTree)},
        ani_native_function {"getFilteredInspectorTree", nullptr,
            reinterpret_cast<void *>(OHOS::Ace::AniGetFilteredInspectorTree)},
        ani_native_function {"getFilteredInspectorTreeById", nullptr,
            reinterpret_cast<void *>(OHOS::Ace::AniGetFilteredInspectorTreeById)},
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
