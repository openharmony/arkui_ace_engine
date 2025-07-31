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
const char ANI_OBSERVER_NS[] = "@ohos.arkui.observer.uiObserver";
const char ANI_OBSERVER_CLS[] = "@ohos.arkui.observer.uiObserver.UIObserverImpl";
constexpr char ANI_NAVDESTINATION_INFO_CLS[] = "@ohos.arkui.observer.uiObserver.NavDestinationInfoImpl";
constexpr char ANI_NAVDESTINATION_STATE_TYPE[] = "@ohos.arkui.observer.uiObserver.NavDestinationState";
constexpr char ANI_NAVDESTINATION_MODE_TYPE[] = "arkui.component.navDestination.NavDestinationMode";
constexpr char NAVDESTINATION_UPDATE[] = "navDestinationUpdate";
constexpr char NAVDESTINATION_PARAM_WITHID[] =
    "C{std.core.String}C{@ohos.arkui.observer.uiObserver.NavDestinationSwitchObserverOptions}C{std.core.Object}:";
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

    void RegisterBeforePanStartCallback(int32_t uiContextInstanceId, ani_ref& cb)
    {
        id_ = uiContextInstanceId;
        if (uiContextInstanceId == 0) {
            uiContextInstanceId = Container::CurrentId();
        }
        auto iter = specifiedBeforePanStartCbMap_.find(uiContextInstanceId);
        if (iter == specifiedBeforePanStartCbMap_.end()) {
            specifiedBeforePanStartCbMap_.emplace(uiContextInstanceId, std::list<ani_ref>({ cb }));
            return;
        }
        auto& holder = iter->second;
        if (std::find(holder.begin(), holder.end(), cb) != holder.end()) {
            return;
        }
        holder.emplace_back(cb);
    }

    void UnRegisterBeforePanStartCallback(ani_env* env, int32_t uiContextInstanceId, ani_ref& cb)
    {
        if (uiContextInstanceId == 0) {
            uiContextInstanceId = Container::CurrentId();
        }
        auto iter = specifiedBeforePanStartCbMap_.find(uiContextInstanceId);
        if (iter == specifiedBeforePanStartCbMap_.end()) {
            return;
        }
        auto& holder = iter->second;
        if (cb == nullptr) {
            holder.clear();
            return;
        }
        holder.erase(std::remove_if(holder.begin(),
                                    holder.end(),
                                    [env, cb, this](ani_ref cb1) { return AniEqual(env, cb, cb1); }),
                     holder.end());
    }

    void RegisterAfterPanStartCallback(int32_t uiContextInstanceId, ani_ref& cb)
    {
        if (uiContextInstanceId == 0) {
            uiContextInstanceId = Container::CurrentId();
        }
        auto iter = specifiedAfterPanStartCbMap_.find(uiContextInstanceId);
        if (iter == specifiedAfterPanStartCbMap_.end()) {
            specifiedAfterPanStartCbMap_.emplace(uiContextInstanceId, std::list<ani_ref>({ cb }));
            return;
        }
        auto& holder = iter->second;
        if (std::find(holder.begin(), holder.end(), cb) != holder.end()) {
            return;
        }
        holder.emplace_back(cb);
    }

    void UnRegisterAfterPanStartCallback(ani_env* env, int32_t uiContextInstanceId, ani_ref& cb)
    {
        if (uiContextInstanceId == 0) {
            uiContextInstanceId = Container::CurrentId();
        }
        auto iter = specifiedAfterPanStartCbMap_.find(uiContextInstanceId);
        if (iter == specifiedAfterPanStartCbMap_.end()) {
            return;
        }
        auto& holder = iter->second;
        if (cb == nullptr) {
            holder.clear();
            return;
        }
        holder.erase(std::remove_if(holder.begin(),
                                    holder.end(),
                                    [env, cb, this](ani_ref cb1) { return AniEqual(env, cb, cb1); }),
                     holder.end());
    }

    void RegisterBeforePanEndCallback(int32_t uiContextInstanceId, ani_ref& cb)
    {
        id_ = uiContextInstanceId;
        if (uiContextInstanceId == 0) {
            uiContextInstanceId = Container::CurrentId();
        }
        auto iter = specifiedBeforePanEndCbMap_.find(uiContextInstanceId);
        if (iter == specifiedBeforePanEndCbMap_.end()) {
            specifiedBeforePanEndCbMap_.emplace(uiContextInstanceId, std::list<ani_ref>({ cb }));
            return;
        }
        auto& holder = iter->second;
        if (std::find(holder.begin(), holder.end(), cb) != holder.end()) {
            return;
        }
        holder.emplace_back(cb);
    }

    void UnRegisterBeforePanEndCallback(ani_env* env, int32_t uiContextInstanceId, ani_ref& cb)
    {
        if (uiContextInstanceId == 0) {
            uiContextInstanceId = Container::CurrentId();
        }
        auto iter = specifiedBeforePanEndCbMap_.find(uiContextInstanceId);
        if (iter == specifiedBeforePanEndCbMap_.end()) {
            return;
        }
        auto& holder = iter->second;
        if (cb == nullptr) {
            holder.clear();
            return;
        }
        holder.erase(std::remove_if(holder.begin(),
                                    holder.end(),
                                    [env, cb, this](ani_ref cb1) { return AniEqual(env, cb, cb1); }),
                     holder.end());
    }

    void RegisterAfterPanEndCallback(int32_t uiContextInstanceId, ani_ref& cb)
    {
        id_ = uiContextInstanceId;
        if (uiContextInstanceId == 0) {
            uiContextInstanceId = Container::CurrentId();
        }
        auto iter = specifiedAfterPanEndCbMap_.find(uiContextInstanceId);
        if (iter == specifiedAfterPanEndCbMap_.end()) {
            specifiedAfterPanEndCbMap_.emplace(uiContextInstanceId, std::list<ani_ref>({ cb }));
            return;
        }
        auto& holder = iter->second;
        if (std::find(holder.begin(), holder.end(), cb) != holder.end()) {
            return;
        }
        holder.emplace_back(cb);
    }

    void UnRegisterAfterPanEndCallback(ani_env* env, int32_t uiContextInstanceId, ani_ref& cb)
    {
        if (uiContextInstanceId == 0) {
            uiContextInstanceId = Container::CurrentId();
        }
        auto iter = specifiedAfterPanEndCbMap_.find(uiContextInstanceId);
        if (iter == specifiedAfterPanEndCbMap_.end()) {
            return;
        }
        auto& holder = iter->second;
        if (cb == nullptr) {
            holder.clear();
            return;
        }
        holder.erase(std::remove_if(holder.begin(),
                                    holder.end(),
                                    [env, cb, this](ani_ref cb1) { return AniEqual(env, cb, cb1); }),
                     holder.end());
    }

    void RegisterWillClickCallback(int32_t uiContextInstanceId, ani_ref& cb)
    {
        id_ = uiContextInstanceId;
        if (uiContextInstanceId == 0) {
            uiContextInstanceId = Container::CurrentId();
        }
        auto iter = specifiedWillClickCbMap_.find(uiContextInstanceId);
        if (iter == specifiedWillClickCbMap_.end()) {
            specifiedWillClickCbMap_.emplace(uiContextInstanceId, std::list<ani_ref>({ cb }));
            return;
        }
        auto& holder = iter->second;
        if (std::find(holder.begin(), holder.end(), cb) != holder.end()) {
            return;
        }
        holder.emplace_back(cb);
    }

    void UnRegisterWillClickCallback(ani_env* env, int32_t uiContextInstanceId, ani_ref& cb)
    {
        if (uiContextInstanceId == 0) {
            uiContextInstanceId = Container::CurrentId();
        }
        auto iter = specifiedWillClickCbMap_.find(uiContextInstanceId);
        if (iter == specifiedWillClickCbMap_.end()) {
            return;
        }
        auto& holder = iter->second;
        if (cb == nullptr) {
            holder.clear();
            return;
        }
        holder.erase(std::remove_if(holder.begin(),
                                    holder.end(),
                                    [env, cb, this](ani_ref cb1) { return AniEqual(env, cb, cb1); }),
                     holder.end());
    }

    void UnRegisterWillDrawCallback(ani_env* env, int32_t uiContextInstanceId, ani_ref& cb) {}

    void RegisterWillDrawCallback(int32_t uiContextInstanceId, ani_ref& cb) {}

    void UnRegisterDidLayoutCallback(ani_env* env, int32_t uiContextInstanceId, ani_ref& cb) {}

    void RegisterDidLayoutCallback(int32_t uiContextInstanceId, ani_ref& cb) {}

    void RegisterDidClickCallback(int32_t uiContextInstanceId, ani_ref& cb)
    {
        id_ = uiContextInstanceId;
        if (uiContextInstanceId == 0) {
            uiContextInstanceId = Container::CurrentId();
        }
        auto iter = specifiedDidClickCbMap_.find(uiContextInstanceId);
        if (iter == specifiedDidClickCbMap_.end()) {
            specifiedDidClickCbMap_.emplace(uiContextInstanceId, std::list<ani_ref>({ cb }));
            return;
        }
        auto& holder = iter->second;
        if (std::find(holder.begin(), holder.end(), cb) != holder.end()) {
            return;
        }
        holder.emplace_back(cb);
    }

    void UnRegisterDidClickCallback(ani_env* env, int32_t uiContextInstanceId, ani_ref& cb)
    {
        if (uiContextInstanceId == 0) {
            uiContextInstanceId = Container::CurrentId();
        }
        auto iter = specifiedDidClickCbMap_.find(uiContextInstanceId);
        if (iter == specifiedDidClickCbMap_.end()) {
            return;
        }
        auto& holder = iter->second;
        if (cb == nullptr) {
            holder.clear();
            return;
        }
        holder.erase(std::remove_if(holder.begin(),
                                    holder.end(),
                                    [env, cb, this](ani_ref cb1) { return AniEqual(env, cb, cb1); }),
                     holder.end());
    }

    // UIObserver.on(type: "navDestinationUpdate", callback)
    void RegisterNavigationCallback(ani_ref& cb)
    {
        if (std::find(unspecifiedNavigationListeners_.begin(), unspecifiedNavigationListeners_.end(), cb) !=
            unspecifiedNavigationListeners_.end()) {
            return;
        }
        unspecifiedNavigationListeners_.emplace_back(cb);
    }

    // UIObserver.off(type: "navDestinationUpdate", callback)
    void UnRegisterNavigationCallback(ani_env* env, ani_ref& cb)
    {
        if (cb == nullptr) {
            unspecifiedNavigationListeners_.clear();
            return;
        }

        unspecifiedNavigationListeners_.erase(
            std::remove_if(unspecifiedNavigationListeners_.begin(), unspecifiedNavigationListeners_.end(),
                [env, cb, this](ani_ref cb1) { return AniEqual(env, cb, cb1); }),
            unspecifiedNavigationListeners_.end());
    }

    // UIObserver.on(type: "navDestinationUpdate", options, callback)
    void RegisterNavigationCallback(std::string navigationId, ani_ref& cb)
    {
        auto iter = specifiedCNavigationListeners_.find(navigationId);
        if (iter == specifiedCNavigationListeners_.end()) {
            specifiedCNavigationListeners_.emplace(navigationId, std::list<ani_ref>({ cb }));
            return;
        }
        auto& holder = iter->second;
        if (std::find(holder.begin(), holder.end(), cb) != holder.end()) {
            return;
        }
        holder.emplace_back(cb);
    }

    // UIObserver.off(type: "navDestinationUpdate", optisons, callback)
    void UnRegisterNavigationCallback(ani_env* env, std::string navigationId, ani_ref& cb)
    {
        auto iter = specifiedCNavigationListeners_.find(navigationId);
        if (iter == specifiedCNavigationListeners_.end()) {
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

    void HandleBeforePanStart(ani_env* env)
    {
        auto currentId = Container::CurrentId();
        auto iter = specifiedBeforePanStartCbMap_.find(currentId);
        if (iter == specifiedBeforePanStartCbMap_.end()) {
            return;
        }
        auto& holder = iter->second;
        CallJsFunction(env, holder);
    }

    void HandleAfterPanStart(ani_env* env)
    {
        auto currentId = Container::CurrentId();
        auto iter = specifiedAfterPanStartCbMap_.find(currentId);
        if (iter == specifiedAfterPanStartCbMap_.end()) {
            return;
        }
        auto& holder = iter->second;
        CallJsFunction(env, holder);
    }

    void HandleBeforePanEnd(ani_env* env)
    {
        auto currentId = Container::CurrentId();
        auto iter = specifiedBeforePanEndCbMap_.find(currentId);
        if (iter == specifiedBeforePanEndCbMap_.end()) {
            return;
        }
        auto& holder = iter->second;
        CallJsFunction(env, holder);
    }

    void HandleAfterPanEnd(ani_env* env)
    {
        auto currentId = Container::CurrentId();
        auto iter = specifiedAfterPanEndCbMap_.find(currentId);
        if (iter == specifiedAfterPanEndCbMap_.end()) {
            return;
        }
        auto& holder = iter->second;
        CallJsFunction(env, holder);
    }

    void HandleWillClick(ani_env* env)
    {
        auto currentId = Container::CurrentId();
        auto iter = specifiedWillClickCbMap_.find(currentId);
        if (iter == specifiedWillClickCbMap_.end()) {
            return;
        }
        auto& holder = iter->second;
        CallJsFunction(env, holder);
    }
    void HandleDidClick(ani_env* env)
    {
        auto currentId = Container::CurrentId();
        auto iter = specifiedDidClickCbMap_.find(currentId);
        if (iter == specifiedDidClickCbMap_.end()) {
            return;
        }
        auto& holder = iter->second;
        CallJsFunction(env, holder);
    }

    void HandleNavigationStateChange(ani_env* env, const NG::NavDestinationInfo& info)
    {
        auto unspecifiedHolder = unspecifiedNavigationListeners_;
        std::vector<ani_ref> cbParam;
        ani_ref fnRetrunVal;
        ani_object res;
        CreateNavigationInfo(env, info, res);
        cbParam.emplace_back(res);
        for (auto& cb : unspecifiedHolder) {
            env->FunctionalObject_Call(
                reinterpret_cast<ani_fn_object>(cb), cbParam.size(), cbParam.data(), &fnRetrunVal);
        }

        auto iter = specifiedCNavigationListeners_.find(info.navigationId);
        if (iter == specifiedCNavigationListeners_.end()) {
            return;
        }

        auto holder = iter->second;
        std::vector<ani_ref> cbParamsWithId;
        ani_ref fnReturnValWithId;
        ani_object resWithId;
        CreateNavigationInfo(env, info, resWithId);
        cbParamsWithId.emplace_back(resWithId);
        for (auto& cb : holder) {
            env->FunctionalObject_Call(
                reinterpret_cast<ani_fn_object>(cb), cbParamsWithId.size(), cbParamsWithId.data(), &fnReturnValWithId);
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
        static const char* className = "@ohos.arkui.observer.uiObserver.DensityInfo";
        ani_class cls;
        env->FindClass(className, &cls);
        ani_method ctor;
        env->Class_FindMethod(cls, "<ctor>", ":", &ctor);
        env->Object_New(cls, ctor, &obj);
        env->Object_SetPropertyByName_Double(obj, "density", ani_double(density));
    }

    void CreateNavigationInfo(ani_env* env, const NG::NavDestinationInfo& info, ani_object& res)
    {
        ani_class cls;
        env->FindClass(ANI_NAVDESTINATION_INFO_CLS, &cls);
        ani_method navDestinationInfoCtor;
        env->Class_FindMethod(cls, "<ctor>", nullptr, &navDestinationInfoCtor);
        env->Object_New(cls, navDestinationInfoCtor, &res);

        env->Object_SetPropertyByName_Double(res, "uniqueId", static_cast<ani_double>(info.uniqueId));
        env->Object_SetPropertyByName_Int(res, "index", static_cast<ani_int>(info.index));

        ani_string navDesName {};
        env->String_NewUTF8(info.name.c_str(), info.name.size(), &navDesName);
        env->Object_SetPropertyByName_Ref(res, "name", navDesName);

        ani_string navDesId {};
        env->String_NewUTF8(info.navDestinationId.c_str(), info.navDestinationId.size(), &navDesId);
        env->Object_SetPropertyByName_Ref(res, "navDestinationId", navDesId);

        ani_string navigationId {};
        env->String_NewUTF8(info.navigationId.c_str(), info.navigationId.size(), &navigationId);
        env->Object_SetPropertyByName_Ref(res, "navigationId", navigationId);

        ani_enum navDesState;
        env->FindEnum(ANI_NAVDESTINATION_STATE_TYPE, &navDesState);
        ani_enum_item navDesStateItem;
        env->Enum_GetEnumItemByIndex(navDesState, static_cast<ani_size>(info.state), &navDesStateItem);
        env->Object_SetPropertyByName_Ref(res, "state", navDesStateItem);

        ani_enum navMode;
        env->FindEnum(ANI_NAVDESTINATION_MODE_TYPE, &navMode);
        ani_enum_item navModeItem;
        env->Enum_GetEnumItemByIndex(navMode, static_cast<ani_size>(info.mode), &navModeItem);
        env->Object_SetPropertyByName_Ref(res, "mode", navModeItem);
    }

private:
    int32_t id_;
    std::unordered_map<int32_t, std::list<ani_ref>> densityCbMap_;

    std::unordered_map<int32_t, std::list<ani_ref>> specifiedBeforePanStartCbMap_;
    std::unordered_map<int32_t, std::list<ani_ref>> specifiedAfterPanStartCbMap_;
    std::unordered_map<int32_t, std::list<ani_ref>> specifiedBeforePanEndCbMap_;
    std::unordered_map<int32_t, std::list<ani_ref>> specifiedAfterPanEndCbMap_;

    std::unordered_map<int32_t, std::list<ani_ref>> specifiedWillClickCbMap_;
    std::unordered_map<int32_t, std::list<ani_ref>> specifiedDidClickCbMap_;
    std::list<ani_ref> unspecifiedNavigationListeners_;
    std::unordered_map<std::string, std::list<ani_ref>> specifiedCNavigationListeners_;
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

    const int idMs = 100000;
    if (typeStr == "densityUpdate") {
        observer->RegisterDensityCallback(idMs, fnObjGlobalRef);
    } else if (typeStr == "beforePanStart") {
        observer->RegisterBeforePanStartCallback(idMs, fnObjGlobalRef);
    } else if (typeStr == "afterPanStart") {
        observer->RegisterAfterPanStartCallback(idMs, fnObjGlobalRef);
    } else if (typeStr == "beforePanEnd") {
        observer->RegisterBeforePanEndCallback(idMs, fnObjGlobalRef);
    } else if (typeStr == "afterPanEnd") {
        observer->RegisterAfterPanEndCallback(idMs, fnObjGlobalRef);
    } else if (typeStr == "willClick") {
        observer->RegisterWillClickCallback(idMs, fnObjGlobalRef);
    } else if (typeStr == "didClick") {
        observer->RegisterDidClickCallback(idMs, fnObjGlobalRef);
    } else if (typeStr == NAVDESTINATION_UPDATE) {
        observer->RegisterNavigationCallback(fnObjGlobalRef);
    } else if (typeStr == "willDraw") {
        observer->RegisterWillDrawCallback(idMs, fnObjGlobalRef);
    } else if (typeStr == "didLayout") {
        observer->RegisterDidLayoutCallback(idMs, fnObjGlobalRef);
    }
}

static void Off([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object, ani_string type, ani_fn_object fnObj)
{
    LOGE("lzr in off");
    auto* observer = Unwrapp(env, object);
    if (observer == nullptr) {
        LOGE("observer-ani context is null.");
        return;
    }
    std::string typeStr = ANIUtils_ANIStringToStdString(env, type);
    ani_ref fnObjGlobalRef = nullptr;
    env->GlobalReference_Create(reinterpret_cast<ani_ref>(fnObj), &fnObjGlobalRef);

    const int idMs = 100000;
    if (typeStr == "densityUpdate") {
        observer->UnRegisterDensityCallback(env, idMs, fnObjGlobalRef);
    } else if (typeStr == "beforePanStart") {
        observer->UnRegisterBeforePanStartCallback(env, idMs, fnObjGlobalRef);
    } else if (typeStr == "afterPanStart") {
        observer->UnRegisterAfterPanStartCallback(env, idMs, fnObjGlobalRef);
    } else if (typeStr == "beforePanEnd") {
        observer->UnRegisterBeforePanEndCallback(env, idMs, fnObjGlobalRef);
    } else if (typeStr == "afterPanEnd") {
        observer->UnRegisterAfterPanEndCallback(env, idMs, fnObjGlobalRef);
    } else if (typeStr == "willClick") {
        observer->UnRegisterWillClickCallback(env, idMs, fnObjGlobalRef);
    } else if (typeStr == "didClick") {
        observer->UnRegisterDidClickCallback(env, idMs, fnObjGlobalRef);
    } else if (typeStr == NAVDESTINATION_UPDATE) {
        observer->UnRegisterNavigationCallback(env, fnObjGlobalRef);
    } else if (typeStr == "willDraw") {
        observer->UnRegisterWillDrawCallback(env, idMs, fnObjGlobalRef);
    } else if (typeStr == "didLayout") {
        observer->UnRegisterDidLayoutCallback(env, idMs, fnObjGlobalRef);
    }
}

static void OnNavDestinationUpdateWithId([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object,
    ani_string type, ani_object options, ani_fn_object fnObj)
{
    if (!fnObj) {
        return;
    }
    auto* observer = Unwrapp(env, object);
    if (!observer) {
        return;
    }
    ani_ref aniNavId;
    env->Object_GetPropertyByName_Ref(options, "navigationId", &aniNavId);
    std::string navigationId = ANIUtils_ANIStringToStdString(env, reinterpret_cast<ani_string>(aniNavId));
    ani_ref fnObjGlobalRef = nullptr;
    env->GlobalReference_Create(reinterpret_cast<ani_ref>(fnObj), &fnObjGlobalRef);
    observer->RegisterNavigationCallback(navigationId, fnObjGlobalRef);
}

static void OffNavDestinationUpdateWithId([[maybe_unused]] ani_env* env, [[maybe_unused]] ani_object object,
    ani_string type, ani_object options, ani_fn_object fnObj)
{
    if (!fnObj) {
        return;
    }
    auto* observer = Unwrapp(env, object);
    if (!observer) {
        return;
    }
    ani_ref aniNavId;
    env->Object_GetPropertyByName_Ref(options, "navigationId", &aniNavId);
    std::string navigationId = ANIUtils_ANIStringToStdString(env, reinterpret_cast<ani_string>(aniNavId));
    ani_ref fnObjGlobalRef = nullptr;
    env->GlobalReference_Create(reinterpret_cast<ani_ref>(fnObj), &fnObjGlobalRef);
    observer->UnRegisterNavigationCallback(env, navigationId, fnObjGlobalRef);
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

    auto beforePanStartCallback = [observer, env]() {
        observer->HandleBeforePanStart(env);
    };
    NG::UIObserverHandler::GetInstance().SetBeforePanStartHandleFuncForAni(beforePanStartCallback);

    auto afterPanStartCallback = [observer, env]() {
        observer->HandleAfterPanStart(env);
    };
    NG::UIObserverHandler::GetInstance().SetAfterPanStartHandleFuncForAni(afterPanStartCallback);

    auto beforePanEndCallback = [observer, env]() {
        observer->HandleBeforePanEnd(env);
    };
    NG::UIObserverHandler::GetInstance().SetBeforePanEndHandleFuncForAni(beforePanEndCallback);

    auto afterPanEndCallback = [observer, env]() {
        observer->HandleAfterPanEnd(env);
    };
    NG::UIObserverHandler::GetInstance().SetAfterPanEndHandleFuncForAni(afterPanEndCallback);

    auto willClickCallback = [observer, env]() {
        observer->HandleWillClick(env);
    };
    NG::UIObserverHandler::GetInstance().SetWillClickHandleFuncForAni(willClickCallback);
    auto didClickCallback = [observer, env]() {
        observer->HandleDidClick(env);
    };
    NG::UIObserverHandler::GetInstance().SetDidClickHandleFuncForAni(didClickCallback);
    auto navigationStateChangeCalback = [observer, env](const NG::NavDestinationInfo& info) {
        observer->HandleNavigationStateChange(env, info);
    };
    NG::UIObserverHandler::GetInstance().SetHandleNavigationChangeFuncForAni(navigationStateChangeCalback);
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
        ani_native_function { "on", "C{std.core.String}C{Lstd.core.Object}:", reinterpret_cast<void*>(OHOS::Ace::On) },
        ani_native_function { "off", "C{std.core.String}C{std.core.Object}:", reinterpret_cast<void*>(OHOS::Ace::Off) },
        ani_native_function {
            "on", NAVDESTINATION_PARAM_WITHID, reinterpret_cast<void*>(OHOS::Ace::OnNavDestinationUpdateWithId) },
        ani_native_function {
            "off", NAVDESTINATION_PARAM_WITHID, reinterpret_cast<void*>(OHOS::Ace::OffNavDestinationUpdateWithId) },
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
