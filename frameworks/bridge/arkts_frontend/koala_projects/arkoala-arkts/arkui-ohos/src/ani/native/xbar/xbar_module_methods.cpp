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

#include "xbar_module_methods.h"

#include <functional>
#include <memory>
#include <string>
#include <utility>

#include "ani.h"
#include "common/common_module.h"
#include "load.h"
#include "log/log.h"
#include "pixel_map_taihe_ani.h"
#include "utils/ani_utils.h"

#include "base/utils/utils.h"

namespace OHOS::Ace::Ani {
ani_status CreateInt(ani_env* env, ani_int value, ani_object& rs)
{
    ani_class cls;
    ani_status status;
    if ((status = env->FindClass("std.core.Int", &cls)) != ANI_OK) {
        HILOGE("[ACE_APPBAR]Find Int class failed");
        return status;
    }
    ani_method ctor;
    if ((status = env->Class_FindMethod(cls, "<ctor>", "i:", &ctor)) != ANI_OK) {
        HILOGE("[ACE_APPBAR]Find Int ctor failed");
        return status;
    }
    env->Object_New(cls, ctor, &rs, value);
    return ANI_OK;
}

void ConvertComponentCreateFunc(ani_vm* vm, std::function<int64_t(const int32_t&, const int32_t&)>& callback,
    const std::shared_ptr<CommonModuleCallbackAni>& callbackAni)
{
    callback = [vm, callbackAni](const int32_t& xbarType, const int32_t& instanceId) -> int64_t {
        HILOGI("[ACE_APPBAR]Create title bar component");
        CHECK_NULL_RETURN(vm, 0);
        CHECK_NULL_RETURN(callbackAni, 0);
        ani_env* env = nullptr;
        auto attachCurrentThreadStatus = GetAniEnv(vm, &env);
        HILOGI("[ACE_APPBAR]GetAniEnv attachCurrentThreadStatus %{public}d", attachCurrentThreadStatus);
        CHECK_NULL_RETURN(env, 0);
        ani_status status;
        std::vector<ani_ref> args;
        ani_object xBarTypeAni;
        if ((status = CreateInt(env, xbarType, xBarTypeAni)) != ANI_OK) {
            HILOGE("[ACE_APPBAR]Create xBarTypeAni failed");
            return 0;
        }
        args.emplace_back((ani_ref)xBarTypeAni);
        ani_object instanceIdAni;
        if ((status = CreateInt(env, instanceId, instanceIdAni)) != ANI_OK) {
            HILOGE("[ACE_APPBAR]Create instanceIdAni failed");
            return 0;
        }
        args.emplace_back((ani_ref)instanceIdAni);
        ani_ref ret = nullptr;
        callbackAni->Call(env, args.size(), args.data(), &ret);
        if (attachCurrentThreadStatus == ANI_OK) {
            vm->DetachCurrentThread();
        }
        if (ret == nullptr) {
            HILOGE("[ACE_APPBAR]Create app bar custom node failed");
            return 0;
        }
        ani_long aniValue;
        if (ANI_OK != env->Object_CallMethodByName_Long((ani_object)ret, "toLong", ":l", &aniValue)) {
            HILOGE("[ACE_APPBAR]Create app bar custom node failed");
            return 0;
        }
        HILOGI("[ACE_APPBAR]create title bar component isTitlebar end");
        return static_cast<int64_t>(aniValue);
    };
}

void XBarSetComponentCreateFunc(ani_env* env, ani_object aniClass, ani_fn_object xbarComponentCreateFunc)
{
    HILOGI("[ACE_APPBAR]begin set component create func");
    CHECK_NULL_VOID(env);
    ani_ref xbarComponentCreateFuncAniRef = static_cast<ani_ref>(xbarComponentCreateFunc);
    auto xbarComponentCreateFuncAni = std::make_shared<CommonModuleCallbackAni>(env, xbarComponentCreateFuncAniRef);
    ani_vm* vm = nullptr;
    env->GetVM(&vm);
    std::function<int64_t(const int32_t&, const int32_t&)> componentCreateFunc = nullptr;
    ConvertComponentCreateFunc(vm, componentCreateFunc, xbarComponentCreateFuncAni);
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getXBarAniModifier() || !componentCreateFunc) {
        HILOGE("[ACE_APPBAR]GetNodeAniModifier failed");
        return;
    }
    modifier->getXBarAniModifier()->setComponentCreateFunc(std::move(componentCreateFunc));
}

void XBarSetOnWindowEventFunc(ani_env* env, const ani_type& type, ani_vm* vm, std::shared_ptr<ani_wref> weakRef,
    ani_long ptr, const std::string funcName)
{
    CHECK_NULL_VOID(env);
    ani_status status;
    ani_method onWindowMethod;
    if ((status = env->Class_FindMethod(static_cast<ani_class>(type), funcName.c_str(), nullptr, &onWindowMethod)) !=
        ANI_OK) {
        HILOGE("[ACE_APPBAR]Get %{public}s method of xBar failed status %{public}d", funcName.c_str(), status);
        return;
    }

    auto&& onWindowEvent = [vm, weakRef, onWindowMethod, funcName]() {
        HILOGI("[ACE_APPBAR]start call %{public}s", funcName.c_str());
        ani_env* env = nullptr;
        ani_status status;
        if ((status = vm->GetEnv(ANI_VERSION_1, &env)) != ANI_OK) {
            HILOGE("[ACE_APPBAR]%{public}s method GetEnv failed status %{public}d", funcName.c_str(), status);
            return;
        }
        ani_boolean released;
        ani_ref localRef;
        if ((status = env->WeakReference_GetReference(*weakRef, &released, &localRef)) != ANI_OK) {
            HILOGE("[ACE_APPBAR]%{public}s method GetReference failed status %{public}d", funcName.c_str(), status);
            return;
        }
        if (released) {
            HILOGE("[ACE_APPBAR]%{public}s reference is released", funcName.c_str());
            return;
        }
        if ((status = env->Object_CallMethod_Void(static_cast<ani_object>(localRef), onWindowMethod)) != ANI_OK) {
            HILOGE("[ACE_APPBAR]%{public}s call is failed status %{public}d", funcName.c_str(), status);
            return;
        }
        HILOGI("[ACE_APPBAR]%{public}s call end", funcName.c_str());
    };
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getXBarAniModifier()) {
        HILOGE("[ACE_APPBAR]GetNodeAniModifier failed");
        return;
    }
    if (funcName == "onWindowFocused") {
        modifier->getXBarAniModifier()->setOnWindowFocusedFunc(ptr, std::move(onWindowEvent));
    } else {
        modifier->getXBarAniModifier()->setOnWindowUnFocusedFunc(ptr, std::move(onWindowEvent));
    }
    HILOGI("[ACE_APPBAR]end XBarSet %{public}s Func", funcName.c_str());
}

void XBarSetAppTitleFunc(
    ani_env* env, const ani_type& type, ani_vm* vm, std::shared_ptr<ani_wref> weakRef, ani_long ptr)
{
    CHECK_NULL_VOID(env);
    ani_status status;
    ani_method setAppTitleMethod;
    if ((status = env->Class_FindMethod(static_cast<ani_class>(type), "setAppTitle", nullptr, &setAppTitleMethod)) !=
        ANI_OK) {
        HILOGE("[ACE_APPBAR]Get setAppTitle method of xBar failed status %{public}d", status);
        return;
    }

    auto&& setAppTitleFunc = [vm, weakRef, setAppTitleMethod](const std::string& content) {
        HILOGI("[ACE_APPBAR]start call setAppTitle");
        ani_env* env = nullptr;
        ani_status status;
        if ((status = vm->GetEnv(ANI_VERSION_1, &env)) != ANI_OK) {
            HILOGE("[ACE_APPBAR]setAppTitle method GetEnv failed status %{public}d", status);
            return;
        }
        ani_boolean released;
        ani_ref localRef;
        if ((status = env->WeakReference_GetReference(*weakRef, &released, &localRef)) != ANI_OK) {
            HILOGE("[ACE_APPBAR]setAppTitle method GetReference failed status %{public}d", status);
            return;
        }
        if (released) {
            HILOGE("[ACE_APPBAR]setAppTitle reference is released");
            return;
        }
        auto contentAni = AniUtils::StdStringToANIString(env, content);
        if ((status = env->Object_CallMethod_Void(static_cast<ani_object>(localRef), setAppTitleMethod, *contentAni)) !=
            ANI_OK) {
            HILOGE("[ACE_APPBAR]setAppTitle call is failed status %{public}d", status);
            return;
        }
        HILOGI("[ACE_APPBAR]setAppTitle call end");
    };
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getXBarAniModifier()) {
        HILOGE("[ACE_APPBAR]GetNodeAniModifier failed");
        return;
    }
    modifier->getXBarAniModifier()->setSetAppTitleFunc(ptr, std::move(setAppTitleFunc));
    HILOGI("[ACE_APPBAR]end XBarSetsetAppTitleFunc");
}

void XBarSetAppIconFunc(ani_env* env, const ani_type& type, ani_vm* vm, std::shared_ptr<ani_wref> weakRef, ani_long ptr)
{
    CHECK_NULL_VOID(env);
    ani_status status;
    ani_method setAppIconMethod;
    if ((status = env->Class_FindMethod(static_cast<ani_class>(type), "setAppIcon", nullptr, &setAppIconMethod)) !=
        ANI_OK) {
        HILOGE("[ACE_APPBAR]Get setAppIcon method of xBar failed status %{public}d", status);
        return;
    }

    auto&& setAppIconFunc = [vm, weakRef, setAppIconMethod](void* pm) {
        HILOGI("[ACE_APPBAR]start call setAppIcon");
        ani_env* env = nullptr;
        ani_status status;
        if ((status = vm->GetEnv(ANI_VERSION_1, &env)) != ANI_OK) {
            HILOGE("[ACE_APPBAR]setAppIcon method GetEnv failed status %{public}d", status);
            return;
        }
        ani_boolean released;
        ani_ref localRef;
        if ((status = env->WeakReference_GetReference(*weakRef, &released, &localRef)) != ANI_OK) {
            HILOGE("[ACE_APPBAR]setAppIcon method GetReference failed status %{public}d", status);
            return;
        }
        if (released) {
            HILOGE("[ACE_APPBAR]setAppIcon reference is released");
            return;
        }
        auto* pixmapPtr = reinterpret_cast<std::shared_ptr<Media::PixelMap>*>(pm);
        if (pixmapPtr == nullptr || *pixmapPtr == nullptr) {
            HILOGE("[ACE_APPBAR]pixmapPtr reference is nullptr");
            return;
        }
        ani_object pixmapItem = OHOS::Media::PixelMapTaiheAni::CreateEtsPixelMap(env, *pixmapPtr);
        if (!pixmapItem) {
            HILOGE("[ACE_APPBAR]setAppIcon can't get pixel map");
            return;
        }
        if ((status = env->Object_CallMethod_Void(static_cast<ani_object>(localRef), setAppIconMethod, pixmapItem)) !=
            ANI_OK) {
            HILOGE("[ACE_APPBAR]setAppIcon call is failed status %{public}d", status);
            return;
        }
        HILOGI("[ACE_APPBAR]setAppIcon call end");
    };
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getXBarAniModifier()) {
        HILOGE("[ACE_APPBAR]GetNodeAniModifier failed");
        return;
    }
    modifier->getXBarAniModifier()->setSetAppIconFunc(ptr, std::move(setAppIconFunc));
    HILOGI("[ACE_APPBAR]end XBarSetsetAppIconFunc");
}

void XBarSetCustomCallbackFunc(
    ani_env* env, const ani_type& type, ani_vm* vm, std::shared_ptr<ani_wref> weakRef, ani_long ptr)
{
    CHECK_NULL_VOID(env);
    ani_status status;
    ani_method setCustomCallbackMethod;
    if ((status = env->Class_FindMethod(
             static_cast<ani_class>(type), "setCustomCallback", nullptr, &setCustomCallbackMethod)) != ANI_OK) {
        HILOGE("[ACE_APPBAR]Get setCustomCallback method of xBar failed status %{public}d", status);
        return;
    }

    auto&& setCustomCallbackFunc = [vm, weakRef, setCustomCallbackMethod](
                                       const std::string& eventName, const std::string& param) {
        HILOGI("[ACE_APPBAR]start call setCustomCallback");
        ani_env* env = nullptr;
        ani_status status;
        if ((status = vm->GetEnv(ANI_VERSION_1, &env)) != ANI_OK) {
            HILOGE("[ACE_APPBAR]setCustomCallback method GetEnv failed status %{public}d", status);
            return;
        }
        ani_boolean released;
        ani_ref localRef;
        if ((status = env->WeakReference_GetReference(*weakRef, &released, &localRef)) != ANI_OK) {
            HILOGE("[ACE_APPBAR]setCustomCallback method GetReference failed status %{public}d", status);
            return;
        }
        if (released) {
            HILOGE("[ACE_APPBAR]setCustomCallback reference is released");
            return;
        }
        auto eventNameAni = AniUtils::StdStringToANIString(env, eventName);
        auto paramAni = AniUtils::StdStringToANIString(env, param);
        if ((status = env->Object_CallMethod_Void(
                 static_cast<ani_object>(localRef), setCustomCallbackMethod, *eventNameAni, *paramAni)) != ANI_OK) {
            HILOGE("[ACE_APPBAR]setCustomCallback call is failed status %{public}d", status);
            return;
        }
        HILOGI("[ACE_APPBAR]setCustomCallback call end");
    };
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getXBarAniModifier()) {
        HILOGE("[ACE_APPBAR]GetNodeAniModifier failed");
        return;
    }
    modifier->getXBarAniModifier()->setSetCustomCallbackFunc(ptr, std::move(setCustomCallbackFunc));
    HILOGI("[ACE_APPBAR]end XBarSetCustomCallbackFunc");
}

void XBarSetJsFunc(ani_env* env, ani_object aniClass, ani_long ptr, ani_ref xBar)
{
    HILOGE("[ACE_APPBAR]start XBarSetJsFunc");
    CHECK_NULL_VOID(env);
    ani_vm* vm = nullptr;
    env->GetVM(&vm);

    std::shared_ptr<ani_wref> weakRef(new ani_wref, [vm](ani_wref* wref) {
        ani_env* env = nullptr;
        vm->GetEnv(ANI_VERSION_1, &env);
        env->WeakReference_Delete(*wref);
    });

    env->WeakReference_Create(xBar, weakRef.get());
    ani_status status;
    ani_type type;
    if ((status = env->Object_GetType((ani_object)xBar, &type)) != ANI_OK) {
        HILOGE("[ACE_APPBAR]Get type of xBar failed status %{public}d", status);
        return;
    }

    XBarSetOnWindowEventFunc(env, type, vm, weakRef, ptr, "onWindowFocused");
    XBarSetOnWindowEventFunc(env, type, vm, weakRef, ptr, "onWindowUnfocused");
    XBarSetAppTitleFunc(env, type, vm, weakRef, ptr);
    XBarSetAppIconFunc(env, type, vm, weakRef, ptr);
    XBarSetCustomCallbackFunc(env, type, vm, weakRef, ptr);
}

void XBarCallNative(ani_env* env, ani_object aniClass, ani_int xBarType, ani_string callType, ani_string message)
{
    HILOGI("[ACE_APPBAR]start XBarCallNative");
    CHECK_NULL_VOID(env);
    std::string eventName = AniUtils::ANIStringToStdString(env, callType);
    std::string param = AniUtils::ANIStringToStdString(env, message);
    HILOGI("[ACE_APPBAR]%{public}d call native, event name: %{public}s, param: %{public}s", xBarType, eventName.c_str(),
        param.c_str());
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getXBarAniModifier()) {
        HILOGE("[ACE_APPBAR]GetNodeAniModifier failed");
        return;
    }
    modifier->getXBarAniModifier()->callNative(xBarType, eventName, param);
    HILOGI("[ACE_APPBAR]end XBarCallNative");
}
} // namespace OHOS::Ace::Ani