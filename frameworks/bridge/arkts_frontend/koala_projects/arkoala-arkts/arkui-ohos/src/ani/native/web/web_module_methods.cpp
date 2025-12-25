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

#include "web_module_methods.h"

#include "base/utils/utils.h"
#include "load.h"
#include "log/log.h"

#include "core/interfaces/ani/ani_api.h"
#include "interop_js/arkts_esvalue.h"
#include "interop_js/arkts_interop_js_api.h"
#include "utils/ani_utils.h"

namespace OHOS::Ace::Ani {

static ani_env* GetAniEnv(ani_vm* vm)
{
    if (!vm) {
        return nullptr;
    }
    ani_env* env = nullptr;
    ani_status status = vm->GetEnv(ANI_VERSION_1, &env);
    if (status != ANI_OK) {
        return nullptr;
    }
    return env;
}

static void GetCommonFunc(ani_vm* vm, ani_ref savePtr,
    WebviewControllerPeer* webviewControllerPeer)
{
    auto getNativePtrFunc = [vm, object = savePtr]() -> long {
        ani_long nativePtr = 0;
        ani_env* envTemp = GetAniEnv(vm);
        if (!envTemp || envTemp->Object_CallMethodByName_Long(
            reinterpret_cast<ani_object>(object), "innerGetThisVar", ":l", &nativePtr) != ANI_OK) {
            return 0;
        }
        return static_cast<long>(nativePtr);
    };
    auto releaseRefFunc = [vm, object = savePtr]() {
        ani_env* envTemp = GetAniEnv(vm);
        if (!envTemp) {
            return;
        }
        envTemp->GlobalReference_Delete(object);
    };
    webviewControllerPeer->getNativePtrFunc = std::move(getNativePtrFunc);
    webviewControllerPeer->releaseRefFunc = std::move(releaseRefFunc);
}

static bool GetObjectFromPtr(ani_env* env, const char* classDesc, ani_object* obj, void* args)
{
    ani_class cls;
    if (env->FindClass(classDesc, &cls) != ANI_OK) {
        HILOGE("FindClass fail: %{public}s", classDesc);
        return false;
    }
    ani_method ctor;
    if (env->Class_FindMethod(cls, "<ctor>", "l:", &ctor) != ANI_OK) {
        HILOGE("Class_FindMethod fail, <ctor> in %{public}s", classDesc);
        return false;
    }
    if (env->Object_New(cls, ctor, obj, args) != ANI_OK) {
        HILOGE("Object_New fail: %{public}s", classDesc);
        return false;
    }
    return true;
}

static void DefaultOnShowFileSelector(ani_vm* vm, void* paramPeer, void* resultPeer, std::function<void(void*)> release)
{
    HILOGI("Call defaultOnShowFileSelector start");
    ani_env* env = GetAniEnv(vm);
    if (!env) {
        HILOGE("DefaultOnShowFileSelector callback env is nullptr");
        release(paramPeer);
        release(resultPeer);
        return;
    }
    ani_object paramObj;
    if (!GetObjectFromPtr(env, "arkui.component.web.FileSelectorParam", &paramObj, paramPeer)) {
        release(paramPeer);
        release(resultPeer);
        return;
    }
    ani_object resultObj;
    if (!GetObjectFromPtr(env, "arkui.component.web.FileSelectorResult", &resultObj, resultPeer)) {
        release(resultPeer);
        return;
    }
    ani_class cls;
    if (env->FindClass("@ohos.web.fileSelector.SelectorDialog", &cls) != ANI_OK) {
        HILOGE("FindClass fail: SelectorDialog");
        return;
    }
    ani_method method;
    if (env->Class_FindMethod(cls, "<ctor>", ":", &method) != ANI_OK) {
        HILOGE("Class_FindMethod fail, <ctor> in SelectorDialog");
        return;
    }
    ani_object obj;
    if (env->Object_New(cls, method, &obj) != ANI_OK) {
        HILOGE("Object_New fail: SelectorDialog");
        return;
    }
    if (env->Class_FindMethod(cls, "defaultOnShowFileSelector",
                              "C{arkui.component.web.FileSelectorParam}C{arkui.component.web.FileSelectorResult}:",
                              &method) != ANI_OK) {
        HILOGE("Class_FindMethod fail, defaultOnShowFileSelector");
        return;
    }
    if (env->Object_CallMethod_Void(obj, method, paramObj, resultObj) != ANI_OK) {
        HILOGE("Call defaultOnShowFileSelector fail");
        return;
    }
    HILOGI("Call defaultOnShowFileSelector done");
}

static void DefaultPermissionClipboard(ani_vm* vm, void* peer, std::function<void()> release)
{
    HILOGI("Call defaultPermissionClipboard start");
    ani_env* env = GetAniEnv(vm);
    if (!env) {
        HILOGE("DefaultPermissionClipboard callback env is nullptr");
        release();
        return;
    }
    ani_object obj;
    if (!GetObjectFromPtr(env, "arkui.component.web.PermissionRequest", &obj, peer)) {
        release();
        return;
    }
    ani_class cls;
    if (env->FindClass("@ohos.web.permissionRequest.PermissionClipboard", &cls) != ANI_OK) {
        HILOGE("FindClass fail: PermissionClipboard");
        return;
    }
    ani_static_method method;
    if (env->Class_FindStaticMethod(cls, "defaultPermissionClipboard",
                                    "C{arkui.component.web.PermissionRequest}:",
                                    &method) != ANI_OK) {
        HILOGE("Class_FindStaticMethod fail, defaultPermissionClipboard");
        return;
    }
    if (env->Class_CallStaticMethod_Void(cls, method, obj) != ANI_OK) {
        HILOGE("Call defaultPermissionClipboard fail");
        return;
    }
    HILOGI("Call defaultPermissionClipboard done");
}

static void GetWebOptionsFunc(ani_vm* vm, ani_ref savePtr,
    WebviewControllerPeer* webviewControllerPeer)
{
    auto setWebIdFunc = [vm, object = savePtr](int32_t nwebId) {
        ani_env* envTemp = GetAniEnv(vm);
        if (!envTemp || envTemp->Object_CallMethodByName_Void(
            reinterpret_cast<ani_object>(object), "_setNWebId", "i:", static_cast<ani_int>(nwebId)) != ANI_OK) {
            HILOGE("setWebIdFunc callback to call _setNWebId failed");
        }
    };
    auto setHapPathFunc = [vm, object = savePtr](const std::string& hapPath) {
        ani_string aniHapPath = nullptr;
        ani_env* envTemp = GetAniEnv(vm);
        if (!envTemp) {
            HILOGE("setHapPathFunc callback envTemp is nullptr");
            return;
        }
        if (envTemp->String_NewUTF8(hapPath.c_str(), hapPath.size(), &aniHapPath) != ANI_OK ||
            envTemp->Object_CallMethodByName_Void(
                reinterpret_cast<ani_object>(object), "_setHapPath", "C{std.core.String}:", aniHapPath) != ANI_OK) {
            HILOGE("setHapPathFunc callback to call _setHapPath failed");
        }
    };
    auto setWebDetachFunc = [vm, object = savePtr](int32_t nwebId) {
        ani_env* envTemp = GetAniEnv(vm);
        if (!envTemp) {
            return;
        }
        if (envTemp->Object_CallMethodByName_Void(
            reinterpret_cast<ani_object>(object), "setWebDetach", "i:", static_cast<ani_int>(nwebId)) != ANI_OK) {
            HILOGE("SetWebDetach callback to call setWebDetach failed");
        }
        envTemp->GlobalReference_Delete(object);
    };
    auto defaultOnShowFileSelectorFunc = [vm](void* paramPeer, void* resultPeer, std::function<void(void*)> release) {
        DefaultOnShowFileSelector(vm, paramPeer, resultPeer, std::move(release));
    };
    auto defaultPermissionClipboardFunc = [vm](void* peer, std::function<void()> release) {
        DefaultPermissionClipboard(vm, peer, std::move(release));
    };
    webviewControllerPeer->setWebIdFunc = std::move(setWebIdFunc);
    webviewControllerPeer->setHapPathFunc = std::move(setHapPathFunc);
    webviewControllerPeer->setWebDetachFunc = std::move(setWebDetachFunc);
    webviewControllerPeer->defaultOnShowFileSelectorFunc = std::move(defaultOnShowFileSelectorFunc);
    webviewControllerPeer->defaultPermissionClipboardFunc = std::move(defaultPermissionClipboardFunc);
}

static void GetWebviewControllerHandlerFunc(ani_vm* vm, ani_ref savePtr,
    WebviewControllerPeer* webviewControllerPeer)
{
    auto getWebIdFunc = [vm, object = savePtr]() -> int32_t {
        ani_int nwebId;
        ani_env* envTemp = GetAniEnv(vm);
        if (!envTemp || envTemp->Object_CallMethodByName_Int(
            reinterpret_cast<ani_object>(object), "innerGetWebId", ":i", &nwebId) != ANI_OK) {
            HILOGE("getWebIdFunc callback to call innerGetWebId failed");
            return -1;
        }
        return static_cast<int32_t>(nwebId);
    };
    auto completeWindowNewFunc = [vm, object = savePtr](int32_t parentId) {
        ani_env* envTemp = GetAniEnv(vm);
        if (!envTemp) {
            HILOGE("completeWindowNewFunc callback envTemp is nullptr");
            return;
        }
        if (envTemp->Object_CallMethodByName_Void(reinterpret_cast<ani_object>(object),
            "innerCompleteWindowNew", "i:", static_cast<ani_int>(parentId))) {
            HILOGE("completeWindowNewFunc callback to call innerCompleteWindowNew failed");
        }
    };
    webviewControllerPeer->getWebIdFunc = std::move(getWebIdFunc);
    webviewControllerPeer->completeWindowNewFunc = std::move(completeWindowNewFunc);
}

ani_long ExtractorsToWebviewWebviewControllerPtr(ani_env* env, ani_class aniClass, ani_object object)
{
    HILOGI("ExtractorsToWebviewWebviewControllerPtr entry");
    ani_vm* vm = nullptr;
    ani_ref savePtr;
    if (env->GetVM(&vm) != ANI_OK ||
        env->GlobalReference_Create(reinterpret_cast<ani_ref>(object), &savePtr) != ANI_OK) {
        HILOGE("ExtractorsToWebviewWebviewControllerPtr get global object failed");
        return 0L;
    }

    auto controllerPeer = new WebviewControllerPeer();
    GetWebOptionsFunc(vm, savePtr, controllerPeer);
    GetWebviewControllerHandlerFunc(vm, savePtr, controllerPeer);
    GetCommonFunc(vm, savePtr, controllerPeer);
    return reinterpret_cast<ani_long>(controllerPeer);
}

ani_object ExtractorsFromWebviewWebviewControllerPtr(ani_env* env, [[maybe_unused]] ani_object aniClass, ani_long ptr)
{
    HILOGD("ExtractorsFromWebviewWebviewControllerPtr entry");
    ani_ref resultRef = nullptr;
    return static_cast<ani_object>(resultRef);
}

static ani_status FindJavaScriptProxyPropertyAndGetGlobalRef(
    ani_env* env, ani_object object, const char* propertyName, ani_ref* globalRef)
{
    ani_ref tempRef = nullptr;
    ani_status status = env->Object_GetPropertyByName_Ref(object, propertyName, &tempRef);
    if (status != ANI_OK) {
        HILOGE("Find JavaScriptProxy property: %{public}s failed, errno: %{public}d", propertyName, status);
        return status;
    }
    status = env->GlobalReference_Create(tempRef, globalRef);
    if (status != ANI_OK) {
        HILOGE("Create global reference failed, errno: %{public}d", status);
        return status;
    }
    return ANI_OK;
}

static void DestroyJavaScriptProxyPropertyRef(ani_env* env, JavaScriptProxyProperyRef& propertyRef)
{
    env->GlobalReference_Delete(propertyRef.objectRef);
    env->GlobalReference_Delete(propertyRef.nameRef);
    env->GlobalReference_Delete(propertyRef.methodListRef);
    env->GlobalReference_Delete(propertyRef.controllerRef);
    env->GlobalReference_Delete(propertyRef.asyncMethodListRef);
    env->GlobalReference_Delete(propertyRef.permissionRef);
}

static int32_t GetJavaScriptProxyProperty(ani_env* env, ani_object object, JavaScriptProxyProperyRef& properyRef)
{
    if (FindJavaScriptProxyPropertyAndGetGlobalRef(env, object, "jsObject", &properyRef.objectRef) != ANI_OK) {
        return -1;
    }
    if (FindJavaScriptProxyPropertyAndGetGlobalRef(env, object, "name", &properyRef.nameRef) != ANI_OK) {
        DestroyJavaScriptProxyPropertyRef(env, properyRef);
        return -1;
    }
    if (FindJavaScriptProxyPropertyAndGetGlobalRef(env, object, "methodList", &properyRef.methodListRef) != ANI_OK) {
        DestroyJavaScriptProxyPropertyRef(env, properyRef);
        return -1;
    }
    if (FindJavaScriptProxyPropertyAndGetGlobalRef(env, object, "controller", &properyRef.controllerRef) != ANI_OK) {
        DestroyJavaScriptProxyPropertyRef(env, properyRef);
        return -1;
    }
    if (FindJavaScriptProxyPropertyAndGetGlobalRef(env, object, "asyncMethodList", &properyRef.asyncMethodListRef) !=
        ANI_OK) {
        DestroyJavaScriptProxyPropertyRef(env, properyRef);
        return -1;
    }
    if (FindJavaScriptProxyPropertyAndGetGlobalRef(env, object, "permission", &properyRef.permissionRef) != ANI_OK) {
        DestroyJavaScriptProxyPropertyRef(env, properyRef);
        return -1;
    }
    return 0;
}

static void GetJavaScriptProxyFunc(ani_env* env, ani_vm* vm, ani_object object, ani_long node)
{
    const auto* modifier = GetNodeAniModifier();
    JavaScriptProxyProperyRef properyRef = { 0 };
    if (GetJavaScriptProxyProperty(env, object, properyRef) != 0) {
        return;
    }

    auto jsProxyCallback = [vm, controller = properyRef.controllerRef, jsObject = properyRef.objectRef,
                               name = properyRef.nameRef, methodList = properyRef.methodListRef,
                               asyncMethodList = properyRef.asyncMethodListRef,
                               permission = properyRef.permissionRef]() {
        ani_env* envTemp = GetAniEnv(vm);
        if (!envTemp) {
            HILOGE("jsProxyCallback callback envTemp is nullptr");
            return;
        }
        if (envTemp->Object_CallMethodByName_Void(reinterpret_cast<ani_object>(controller),
                                                  "jsProxy",
                                                  nullptr,
                                                  reinterpret_cast<ani_object>(jsObject),
                                                  reinterpret_cast<ani_string>(name),
                                                  reinterpret_cast<ani_array>(methodList),
                                                  reinterpret_cast<ani_array>(asyncMethodList),
                                                  reinterpret_cast<ani_string>(permission)) != ANI_OK) {
            HILOGE("jsProxyCallback callback to call innerJavaScriptProxy failed");
        }
        envTemp->GlobalReference_Delete(jsObject);
        envTemp->GlobalReference_Delete(name);
        envTemp->GlobalReference_Delete(methodList);
        envTemp->GlobalReference_Delete(controller);
        envTemp->GlobalReference_Delete(asyncMethodList);
        envTemp->GlobalReference_Delete(permission);
    };

    modifier->getWebAniModifier()->setJavaScriptProxyController(
        reinterpret_cast<void*>(node), std::move(jsProxyCallback));
}

void SetJavaScriptProxyController(ani_env* env, ani_class aniClass, ani_long node, ani_object object)
{
    HILOGD("SetJavaScriptProxyController entry");
    ani_vm* vm = nullptr;

    if (env->GetVM(&vm) != ANI_OK) {
        HILOGE("SetJavaScriptProxyController get global object failed");
        return;
    }

    GetJavaScriptProxyFunc(env, vm, object, node);
}

ani_boolean TransferScreenCaptureHandlerToStatic(ani_env* env, ani_class aniClass, ani_long node, ani_object input)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getWebAniModifier() || !env) {
        return ANI_FALSE;
    }
    void *nativePtr = nullptr;
    if (!arkts_esvalue_unwrap(env, input, &nativePtr) || nativePtr == nullptr) {
        HILOGE("TransferScreenCaptureHandlerToStatic arkts_esvalue_unwrap failed");
        return ANI_FALSE;
    }
    return modifier->getWebAniModifier()->
        transferScreenCaptureHandlerToStatic(reinterpret_cast<void*>(node), nativePtr);
}

ani_boolean TransferJsGeolocationToStatic(ani_env* env, ani_class aniClass, ani_long node, ani_object input)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getWebAniModifier() || !env) {
        return ANI_FALSE;
    }
    void *nativePtr = nullptr;
    if (!arkts_esvalue_unwrap(env, input, &nativePtr) || nativePtr == nullptr) {
        HILOGE("TransferJsGeolocationToStatic arkts_esvalue_unwrap failed");
        return ANI_FALSE;
    }
    return modifier->getWebAniModifier()->transferJsGeolocationToStatic(reinterpret_cast<void*>(node), nativePtr);
}

ani_boolean TransferJsResultToStatic(ani_env* env, ani_class aniClass, ani_long node, ani_object input)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getWebAniModifier() || !env) {
        return ANI_FALSE;
    }
    void *nativePtr = nullptr;
    if (!arkts_esvalue_unwrap(env, input, &nativePtr) || nativePtr == nullptr) {
        HILOGE("TransferJsResultToStatic arkts_esvalue_unwrap failed");
        return ANI_FALSE;
    }
    return modifier->getWebAniModifier()->transferJsResultToStatic(reinterpret_cast<void*>(node), nativePtr);
}

ani_boolean TransferEventResultToStatic(ani_env* env, ani_class aniClass, ani_long node, ani_object input)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getWebAniModifier() || !env) {
        return ANI_FALSE;
    }
    void *nativePtr = nullptr;
    if (!arkts_esvalue_unwrap(env, input, &nativePtr) || nativePtr == nullptr) {
        HILOGE("TransferEventResultToStatic arkts_esvalue_unwrap failed");
        return ANI_FALSE;
    }
    return modifier->getWebAniModifier()->transferEventResultToStatic(reinterpret_cast<void*>(node), nativePtr);
}

ani_boolean TransferFileSelectorResultToStatic(ani_env* env, ani_class aniClass, ani_long node, ani_object input)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getWebAniModifier() || !env) {
        return ANI_FALSE;
    }
    void *nativePtr = nullptr;
    if (!arkts_esvalue_unwrap(env, input, &nativePtr) || nativePtr == nullptr) {
        HILOGE("TransferFileSelectorResultToStatic arkts_esvalue_unwrap failed");
        return ANI_FALSE;
    }
    return modifier->getWebAniModifier()->transferFileSelectorResultToStatic(reinterpret_cast<void*>(node), nativePtr);
}

ani_boolean TransferFileSelectorParamToStatic(ani_env* env, ani_class aniClass, ani_long node, ani_object input)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getWebAniModifier() || !env) {
        return ANI_FALSE;
    }
    void *nativePtr = nullptr;
    if (!arkts_esvalue_unwrap(env, input, &nativePtr) || nativePtr == nullptr) {
        HILOGE("TransferFileSelectorParamToStatic arkts_esvalue_unwrap failed");
        return ANI_FALSE;
    }
    return modifier->getWebAniModifier()->transferFileSelectorParamToStatic(reinterpret_cast<void*>(node), nativePtr);
}

ani_boolean TransferWebContextMenuResultToStatic(ani_env* env, ani_class aniClass, ani_long node, ani_object input)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getWebAniModifier() || !env) {
        return ANI_FALSE;
    }
    void *nativePtr = nullptr;
    if (!arkts_esvalue_unwrap(env, input, &nativePtr) || nativePtr == nullptr) {
        HILOGE("TransferWebContextMenuResultToStatic arkts_esvalue_unwrap failed");
        return ANI_FALSE;
    }
    return modifier->getWebAniModifier()->transferWebContextMenuResultToStatic(
        reinterpret_cast<void*>(node), nativePtr);
}

ani_boolean TransferWebContextMenuParamToStatic(ani_env* env, ani_class aniClass, ani_long node, ani_object input)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getWebAniModifier() || !env) {
        return ANI_FALSE;
    }
    void *nativePtr = nullptr;
    if (!arkts_esvalue_unwrap(env, input, &nativePtr) || nativePtr == nullptr) {
        HILOGE("TransferWebContextMenuParamToStatic arkts_esvalue_unwrap failed");
        return ANI_FALSE;
    }
    return modifier->getWebAniModifier()->transferWebContextMenuParamToStatic(reinterpret_cast<void*>(node), nativePtr);
}

ani_object TransferScreenCaptureHandlerToDynamic(ani_env* env, ani_class aniClass, ani_long node)
{
    CHECK_NULL_RETURN(env, nullptr);
    ani_ref undefinedRef;
    env->GetUndefined(&undefinedRef);
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getWebAniModifier()) {
        return reinterpret_cast<ani_object>(undefinedRef);
    }
    ani_ref result = nullptr;
    {
        napi_env jsenv {};
        bool success = arkts_napi_scope_open(env, &jsenv);
        CHECK_NULL_RETURN(success, reinterpret_cast<ani_object>(undefinedRef));
        napi_value dynamic =
            modifier->getWebAniModifier()->transferScreenCaptureHandlerToDynamic(jsenv, reinterpret_cast<void*>(node));
        CHECK_NULL_RETURN(dynamic, reinterpret_cast<ani_object>(undefinedRef));
        success = arkts_napi_scope_close_n(jsenv, 1, &dynamic, &result);
        CHECK_NULL_RETURN(success, reinterpret_cast<ani_object>(undefinedRef));
    }
    return reinterpret_cast<ani_object>(result);
}

ani_boolean TransferHttpAuthHandlerToStatic(ani_env* env, ani_class aniClass, ani_long node, ani_object input)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getWebAniModifier() || !env) {
        return ANI_FALSE;
    }
    void *nativePtr = nullptr;
    if (!arkts_esvalue_unwrap(env, input, &nativePtr) || nativePtr == nullptr) {
        HILOGE("TransferHttpAuthHandlerToStatic arkts_esvalue_unwrap failed");
        return ANI_FALSE;
    }
    return modifier->getWebAniModifier()->transferHttpAuthHandlerToStatic(reinterpret_cast<void*>(node), nativePtr);
}

ani_boolean TransferWebResourceReponseToStatic(ani_env* env, ani_class aniClass, ani_long node, ani_object input)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getWebAniModifier() || !env) {
        return ANI_FALSE;
    }
    void *nativePtr = nullptr;
    if (!arkts_esvalue_unwrap(env, input, &nativePtr) || nativePtr == nullptr) {
        HILOGE("TransferWebResourceReponseToStatic arkts_esvalue_unwrap failed");
        return ANI_FALSE;
    }
    return modifier->getWebAniModifier()->transferWebResourceReponseToStatic(reinterpret_cast<void*>(node), nativePtr);
}

ani_boolean TransferWebResourceRequestToStatic(ani_env* env, ani_class aniClass, ani_long node, ani_object input)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getWebAniModifier() || !env) {
        return ANI_FALSE;
    }
    void *nativePtr = nullptr;
    if (!arkts_esvalue_unwrap(env, input, &nativePtr) || nativePtr == nullptr) {
        HILOGE("TransferWebResourceRequestToStatic arkts_esvalue_unwrap failed");
        return ANI_FALSE;
    }
    return modifier->getWebAniModifier()->transferWebResourceRequestToStatic(reinterpret_cast<void*>(node), nativePtr);
}

ani_boolean TransferConsoleMessageToStatic(ani_env* env, ani_class aniClass, ani_long node, ani_object input)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getWebAniModifier() || !env) {
        return ANI_FALSE;
    }
    void *nativePtr = nullptr;
    if (!arkts_esvalue_unwrap(env, input, &nativePtr) || nativePtr == nullptr) {
        HILOGE("TransferConsoleMessageToStatic arkts_esvalue_unwrap failed");
        return ANI_FALSE;
    }
    return modifier->getWebAniModifier()->transferConsoleMessageToStatic(reinterpret_cast<void*>(node), nativePtr);
}

ani_boolean TransferDataResubmissionHandlerToStatic(ani_env* env, ani_class aniClass, ani_long node, ani_object input)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getWebAniModifier() || !env) {
        return ANI_FALSE;
    }
    void *nativePtr = nullptr;
    if (!arkts_esvalue_unwrap(env, input, &nativePtr) || nativePtr == nullptr) {
        HILOGE("TransferDataResubmissionHandlerToStatic arkts_esvalue_unwrap failed");
        return ANI_FALSE;
    }
    return modifier->getWebAniModifier()->transferDataResubmissionHandlerToStatic(
        reinterpret_cast<void*>(node), nativePtr);
}

ani_boolean TransferClientAuthenticationHandlerToStatic(
    ani_env* env, ani_class aniClass, ani_long node, ani_object input)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getWebAniModifier() || !env) {
        return ANI_FALSE;
    }
    void *nativePtr = nullptr;
    if (!arkts_esvalue_unwrap(env, input, &nativePtr) || nativePtr == nullptr) {
        HILOGE("TransferClientAuthenticationHandlerToStatic arkts_esvalue_unwrap failed");
        return ANI_FALSE;
    }
    return modifier->getWebAniModifier()->transferClientAuthenticationHandlerToStatic(
        reinterpret_cast<void*>(node), nativePtr);
}


ani_boolean TransferSslErrorHandlerToStatic(ani_env* env, ani_class aniClass, ani_long node, ani_object input)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getWebAniModifier() || !env) {
        return ANI_FALSE;
    }
    void *nativePtr = nullptr;
    if (!arkts_esvalue_unwrap(env, input, &nativePtr) || nativePtr == nullptr) {
        HILOGE("TransferSslErrorHandlerToStatic arkts_esvalue_unwrap failed");
        return ANI_FALSE;
    }
    return modifier->getWebAniModifier()->transferSslErrorHandlerToStatic(
        reinterpret_cast<void*>(node), nativePtr);
}

ani_object TransferJsGeolocationToDynamic(ani_env* env, ani_class aniClass, ani_long node)
{
    CHECK_NULL_RETURN(env, nullptr);
    ani_ref undefinedRef;
    env->GetUndefined(&undefinedRef);
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getWebAniModifier()) {
        return reinterpret_cast<ani_object>(undefinedRef);
    }
    ani_ref result = nullptr;
    {
        napi_env jsenv {};
        bool success = arkts_napi_scope_open(env, &jsenv);
        CHECK_NULL_RETURN(success, reinterpret_cast<ani_object>(undefinedRef));
        napi_value dynamic =
            modifier->getWebAniModifier()->transferJsGeolocationToDynamic(jsenv, reinterpret_cast<void*>(node));
        CHECK_NULL_RETURN(dynamic, reinterpret_cast<ani_object>(undefinedRef));
        success = arkts_napi_scope_close_n(jsenv, 1, &dynamic, &result);
        CHECK_NULL_RETURN(success, reinterpret_cast<ani_object>(undefinedRef));
    }
    return reinterpret_cast<ani_object>(result);
}

ani_object TransferJsResultToDynamic(ani_env* env, ani_class aniClass, ani_long node)
{
    CHECK_NULL_RETURN(env, nullptr);
    ani_ref undefinedRef;
    env->GetUndefined(&undefinedRef);
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getWebAniModifier()) {
        return reinterpret_cast<ani_object>(undefinedRef);
    }
    ani_ref result = nullptr;
    {
        napi_env jsenv {};
        bool success = arkts_napi_scope_open(env, &jsenv);
        CHECK_NULL_RETURN(success, reinterpret_cast<ani_object>(undefinedRef));
        napi_value dynamic =
            modifier->getWebAniModifier()->transferJsResultToDynamic(jsenv, reinterpret_cast<void*>(node));
        CHECK_NULL_RETURN(dynamic, reinterpret_cast<ani_object>(undefinedRef));
        success = arkts_napi_scope_close_n(jsenv, 1, &dynamic, &result);
        CHECK_NULL_RETURN(success, reinterpret_cast<ani_object>(undefinedRef));
    }
    return reinterpret_cast<ani_object>(result);
}

ani_object TransferEventResultToDynamic(ani_env* env, ani_class aniClass, ani_long node)
{
    CHECK_NULL_RETURN(env, nullptr);
    ani_ref undefinedRef;
    env->GetUndefined(&undefinedRef);
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getWebAniModifier()) {
        return reinterpret_cast<ani_object>(undefinedRef);
    }
    ani_ref result = nullptr;
    {
        napi_env jsenv {};
        bool success = arkts_napi_scope_open(env, &jsenv);
        CHECK_NULL_RETURN(success, reinterpret_cast<ani_object>(undefinedRef));
        napi_value dynamic =
            modifier->getWebAniModifier()->transferEventResultToDynamic(jsenv, reinterpret_cast<void*>(node));
        CHECK_NULL_RETURN(dynamic, reinterpret_cast<ani_object>(undefinedRef));
        success = arkts_napi_scope_close_n(jsenv, 1, &dynamic, &result);
        CHECK_NULL_RETURN(success, reinterpret_cast<ani_object>(undefinedRef));
    }
    return reinterpret_cast<ani_object>(result);
}

ani_object TransferFileSelectorResultToDynamic(ani_env* env, ani_class aniClass, ani_long node)
{
    CHECK_NULL_RETURN(env, nullptr);
    ani_ref undefinedRef;
    env->GetUndefined(&undefinedRef);
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getWebAniModifier()) {
        return reinterpret_cast<ani_object>(undefinedRef);
    }
    ani_ref result = nullptr;
    {
        napi_env jsenv {};
        bool success = arkts_napi_scope_open(env, &jsenv);
        CHECK_NULL_RETURN(success, reinterpret_cast<ani_object>(undefinedRef));
        napi_value dynamic =
            modifier->getWebAniModifier()->transferFileSelectorResultToDynamic(jsenv, reinterpret_cast<void*>(node));
        CHECK_NULL_RETURN(dynamic, reinterpret_cast<ani_object>(undefinedRef));
        success = arkts_napi_scope_close_n(jsenv, 1, &dynamic, &result);
        CHECK_NULL_RETURN(success, reinterpret_cast<ani_object>(undefinedRef));
    }
    return reinterpret_cast<ani_object>(result);
}

ani_object TransferFileSelectorParamToDynamic(ani_env* env, ani_class aniClass, ani_long node)
{
    CHECK_NULL_RETURN(env, nullptr);
    ani_ref undefinedRef;
    env->GetUndefined(&undefinedRef);
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getWebAniModifier()) {
        return reinterpret_cast<ani_object>(undefinedRef);
    }
    ani_ref result = nullptr;
    {
        napi_env jsenv {};
        bool success = arkts_napi_scope_open(env, &jsenv);
        CHECK_NULL_RETURN(success, reinterpret_cast<ani_object>(undefinedRef));
        napi_value dynamic =
            modifier->getWebAniModifier()->transferFileSelectorParamToDynamic(jsenv, reinterpret_cast<void*>(node));
        CHECK_NULL_RETURN(dynamic, reinterpret_cast<ani_object>(undefinedRef));
        success = arkts_napi_scope_close_n(jsenv, 1, &dynamic, &result);
        CHECK_NULL_RETURN(success, reinterpret_cast<ani_object>(undefinedRef));
    }
    return reinterpret_cast<ani_object>(result);
}

ani_object TransferWebContextMenuResultToDynamic(ani_env* env, ani_class aniClass, ani_long node)
{
    CHECK_NULL_RETURN(env, nullptr);
    ani_ref undefinedRef;
    env->GetUndefined(&undefinedRef);
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getWebAniModifier()) {
        return reinterpret_cast<ani_object>(undefinedRef);
    }
    ani_ref result = nullptr;
    {
        napi_env jsenv {};
        bool success = arkts_napi_scope_open(env, &jsenv);
        CHECK_NULL_RETURN(success, reinterpret_cast<ani_object>(undefinedRef));
        napi_value dynamic =
            modifier->getWebAniModifier()->transferWebContextMenuResultToDynamic(jsenv, reinterpret_cast<void*>(node));
        CHECK_NULL_RETURN(dynamic, reinterpret_cast<ani_object>(undefinedRef));
        success = arkts_napi_scope_close_n(jsenv, 1, &dynamic, &result);
        CHECK_NULL_RETURN(success, reinterpret_cast<ani_object>(undefinedRef));
    }
    return reinterpret_cast<ani_object>(result);
}

ani_object TransferWebContextMenuParamToDynamic(ani_env* env, ani_class aniClass, ani_long node)
{
    CHECK_NULL_RETURN(env, nullptr);
    ani_ref undefinedRef;
    env->GetUndefined(&undefinedRef);
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getWebAniModifier()) {
        return reinterpret_cast<ani_object>(undefinedRef);
    }
    ani_ref result = nullptr;
    {
        napi_env jsenv {};
        bool success = arkts_napi_scope_open(env, &jsenv);
        CHECK_NULL_RETURN(success, reinterpret_cast<ani_object>(undefinedRef));
        napi_value dynamic = modifier->getWebAniModifier()->transferWebContextMenuParamToDynamic(
            jsenv, reinterpret_cast<void*>(node));
        CHECK_NULL_RETURN(dynamic, reinterpret_cast<ani_object>(undefinedRef));
        success = arkts_napi_scope_close_n(jsenv, 1, &dynamic, &result);
        CHECK_NULL_RETURN(success, reinterpret_cast<ani_object>(undefinedRef));
    }
    return reinterpret_cast<ani_object>(result);
}

ani_object TransferHttpAuthHandlerToDynamic(ani_env* env, ani_class aniClass, ani_long node)
{
    CHECK_NULL_RETURN(env, nullptr);
    ani_ref undefinedRef;
    env->GetUndefined(&undefinedRef);
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getWebAniModifier()) {
        return reinterpret_cast<ani_object>(undefinedRef);
    }
    ani_ref result = nullptr;
    {
        napi_env jsenv {};
        bool success = arkts_napi_scope_open(env, &jsenv);
        CHECK_NULL_RETURN(success, reinterpret_cast<ani_object>(undefinedRef));
        napi_value dynamic =
            modifier->getWebAniModifier()->transferHttpAuthHandlerToDynamic(jsenv, reinterpret_cast<void*>(node));
        CHECK_NULL_RETURN(dynamic, reinterpret_cast<ani_object>(undefinedRef));
        success = arkts_napi_scope_close_n(jsenv, 1, &dynamic, &result);
        CHECK_NULL_RETURN(success, reinterpret_cast<ani_object>(undefinedRef));
    }
    return reinterpret_cast<ani_object>(result);
}

ani_object TransferWebResourceReponseToDynamic(ani_env* env, ani_class aniClass, ani_long node)
{
    CHECK_NULL_RETURN(env, nullptr);
    ani_ref undefinedRef;
    env->GetUndefined(&undefinedRef);
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getWebAniModifier()) {
        return reinterpret_cast<ani_object>(undefinedRef);
    }
    ani_ref result = nullptr;
    {
        napi_env jsenv {};
        bool success = arkts_napi_scope_open(env, &jsenv);
        CHECK_NULL_RETURN(success, reinterpret_cast<ani_object>(undefinedRef));
        napi_value dynamic =
            modifier->getWebAniModifier()->transferWebResourceReponseToDynamic(jsenv, reinterpret_cast<void*>(node));
        CHECK_NULL_RETURN(dynamic, reinterpret_cast<ani_object>(undefinedRef));
        success = arkts_napi_scope_close_n(jsenv, 1, &dynamic, &result);
        CHECK_NULL_RETURN(success, reinterpret_cast<ani_object>(undefinedRef));
    }
    return reinterpret_cast<ani_object>(result);
}

ani_object TransferWebResourceRequestToDynamic(ani_env* env, ani_class aniClass, ani_long node)
{
    CHECK_NULL_RETURN(env, nullptr);
    ani_ref undefinedRef;
    env->GetUndefined(&undefinedRef);
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getWebAniModifier()) {
        return reinterpret_cast<ani_object>(undefinedRef);
    }
    ani_ref result = nullptr;
    {
        napi_env jsenv {};
        bool success = arkts_napi_scope_open(env, &jsenv);
        CHECK_NULL_RETURN(success, reinterpret_cast<ani_object>(undefinedRef));
        napi_value dynamic = modifier->getWebAniModifier()->transferWebResourceRequestToDynamic(
            jsenv, reinterpret_cast<void*>(node));
        CHECK_NULL_RETURN(dynamic, reinterpret_cast<ani_object>(undefinedRef));
        success = arkts_napi_scope_close_n(jsenv, 1, &dynamic, &result);
        CHECK_NULL_RETURN(success, reinterpret_cast<ani_object>(undefinedRef));
    }
    return reinterpret_cast<ani_object>(result);
}

ani_object TransferConsoleMessageToDynamic(ani_env* env, ani_class aniClass, ani_long node)
{
    CHECK_NULL_RETURN(env, nullptr);
    ani_ref undefinedRef;
    env->GetUndefined(&undefinedRef);
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getWebAniModifier()) {
        return reinterpret_cast<ani_object>(undefinedRef);
    }
    ani_ref result = nullptr;
    {
        napi_env jsenv {};
        bool success = arkts_napi_scope_open(env, &jsenv);
        CHECK_NULL_RETURN(success, reinterpret_cast<ani_object>(undefinedRef));
        napi_value dynamic = modifier->getWebAniModifier()->transferConsoleMessageToDynamic(
            jsenv, reinterpret_cast<void*>(node));
        CHECK_NULL_RETURN(dynamic, reinterpret_cast<ani_object>(undefinedRef));
        success = arkts_napi_scope_close_n(jsenv, 1, &dynamic, &result);
        CHECK_NULL_RETURN(success, reinterpret_cast<ani_object>(undefinedRef));
    }
    return reinterpret_cast<ani_object>(result);
}

ani_object TransferDataResubmissionHandlerToDynamic(ani_env* env, ani_class aniClass, ani_long node)
{
    CHECK_NULL_RETURN(env, nullptr);
    ani_ref undefinedRef;
    env->GetUndefined(&undefinedRef);
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getWebAniModifier()) {
        return reinterpret_cast<ani_object>(undefinedRef);
    }
    ani_ref result = nullptr;
    {
        napi_env jsenv {};
        bool success = arkts_napi_scope_open(env, &jsenv);
        CHECK_NULL_RETURN(success, reinterpret_cast<ani_object>(undefinedRef));
        napi_value dynamic = modifier->getWebAniModifier()->transferDataResubmissionHandlerToDynamic(
            jsenv, reinterpret_cast<void*>(node));
        CHECK_NULL_RETURN(dynamic, reinterpret_cast<ani_object>(undefinedRef));
        success = arkts_napi_scope_close_n(jsenv, 1, &dynamic, &result);
        CHECK_NULL_RETURN(success, reinterpret_cast<ani_object>(undefinedRef));
    }
    return reinterpret_cast<ani_object>(result);
}

ani_object TransferClientAuthenticationHandlerToDynamic(ani_env* env, ani_class aniClass, ani_long node)
{
    CHECK_NULL_RETURN(env, nullptr);
    ani_ref undefinedRef;
    env->GetUndefined(&undefinedRef);
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getWebAniModifier()) {
        return reinterpret_cast<ani_object>(undefinedRef);
    }
    ani_ref result = nullptr;
    {
        napi_env jsenv {};
        bool success = arkts_napi_scope_open(env, &jsenv);
        CHECK_NULL_RETURN(success, reinterpret_cast<ani_object>(undefinedRef));
        napi_value dynamic = modifier->getWebAniModifier()->transferClientAuthenticationHandlerToDynamic(
            jsenv, reinterpret_cast<void*>(node));
        CHECK_NULL_RETURN(dynamic, reinterpret_cast<ani_object>(undefinedRef));
        success = arkts_napi_scope_close_n(jsenv, 1, &dynamic, &result);
        CHECK_NULL_RETURN(success, reinterpret_cast<ani_object>(undefinedRef));
    }
    return reinterpret_cast<ani_object>(result);
}

ani_object TransferSslErrorHandlerToDynamic(ani_env* env, ani_class aniClass, ani_long node)
{
    CHECK_NULL_RETURN(env, nullptr);
    ani_ref undefinedRef;
    env->GetUndefined(&undefinedRef);
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getWebAniModifier()) {
        return reinterpret_cast<ani_object>(undefinedRef);
    }
    ani_ref result = nullptr;
    {
        napi_env jsenv {};
        bool success = arkts_napi_scope_open(env, &jsenv);
        CHECK_NULL_RETURN(success, reinterpret_cast<ani_object>(undefinedRef));
        napi_value dynamic =
            modifier->getWebAniModifier()->transferSslErrorHandlerToDynamic(jsenv, reinterpret_cast<void*>(node));
        CHECK_NULL_RETURN(dynamic, reinterpret_cast<ani_object>(undefinedRef));
        success = arkts_napi_scope_close_n(jsenv, 1, &dynamic, &result);
        CHECK_NULL_RETURN(success, reinterpret_cast<ani_object>(undefinedRef));
    }
    return reinterpret_cast<ani_object>(result);
}

ani_boolean TransferPermissionRequestToStatic(ani_env* env, ani_class aniClass, ani_long node, ani_object input)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getWebAniModifier() || !env) {
        return ANI_FALSE;
    }
    void *nativePtr = nullptr;
    if (!arkts_esvalue_unwrap(env, input, &nativePtr) || nativePtr == nullptr) {
        HILOGE("TransferPermissionRequestToStatic arkts_esvalue_unwrap failed");
        return ANI_FALSE;
    }
    return modifier->getWebAniModifier()->transferPermissionRequestToStatic(reinterpret_cast<void*>(node), nativePtr);
}

ani_boolean TransferControllerHandlerToStatic(ani_env* env, ani_class aniClass, ani_long node, ani_object input)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getWebAniModifier() || !env) {
        return ANI_FALSE;
    }
    void *nativePtr = nullptr;
    if (!arkts_esvalue_unwrap(env, input, &nativePtr) || nativePtr == nullptr) {
        HILOGE("TransferControllerHandlerToStatic arkts_esvalue_unwrap failed");
        return ANI_FALSE;
    }
    return modifier->getWebAniModifier()->transferControllerHandlerToStatic(reinterpret_cast<void*>(node), nativePtr);
}

ani_boolean TransferWebKeyboardControllerToStatic(ani_env* env, ani_class aniClass, ani_long node, ani_object input)
{
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getWebAniModifier() || !env) {
        return ANI_FALSE;
    }
    void *nativePtr = nullptr;
    if (!arkts_esvalue_unwrap(env, input, &nativePtr) || nativePtr == nullptr) {
        HILOGE("arkweb_test TransferWebKeyboardControllerToStatic arkts_esvalue_unwrap failed");
        return ANI_FALSE;
    }
    return modifier->getWebAniModifier()->transferWebKeyboardControllerToStatic(
        reinterpret_cast<void*>(node), nativePtr);
}

ani_object TransferControllerHandlerToDynamic(ani_env* env, ani_class aniClass, ani_long node)
{
    CHECK_NULL_RETURN(env, nullptr);
    ani_ref undefinedRef;
    env->GetUndefined(&undefinedRef);
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getWebAniModifier()) {
        return reinterpret_cast<ani_object>(undefinedRef);
    }
    ani_ref result = nullptr;
    {
        napi_env jsenv {};
        bool success = arkts_napi_scope_open(env, &jsenv);
        CHECK_NULL_RETURN(success, reinterpret_cast<ani_object>(undefinedRef));
        napi_value dynamic =
            modifier->getWebAniModifier()->transferControllerHandlerToDynamic(jsenv, reinterpret_cast<void*>(node));
        CHECK_NULL_RETURN(dynamic, reinterpret_cast<ani_object>(undefinedRef));
        success = arkts_napi_scope_close_n(jsenv, 1, &dynamic, &result);
        CHECK_NULL_RETURN(success, reinterpret_cast<ani_object>(undefinedRef));
    }
    return reinterpret_cast<ani_object>(result);
}
ani_object TransferPermissionRequestToDynamic(ani_env* env, ani_class aniClass, ani_long node)
{
    CHECK_NULL_RETURN(env, nullptr);
    ani_ref undefinedRef;
    env->GetUndefined(&undefinedRef);
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getWebAniModifier()) {
        return reinterpret_cast<ani_object>(undefinedRef);
    }
    ani_ref result = nullptr;
    {
        napi_env jsenv {};
        bool success = arkts_napi_scope_open(env, &jsenv);
        CHECK_NULL_RETURN(success, reinterpret_cast<ani_object>(undefinedRef));
        napi_value dynamic =
            modifier->getWebAniModifier()->transferPermissionRequestToDynamic(jsenv, reinterpret_cast<void*>(node));
        CHECK_NULL_RETURN(dynamic, reinterpret_cast<ani_object>(undefinedRef));
        success = arkts_napi_scope_close_n(jsenv, 1, &dynamic, &result);
        CHECK_NULL_RETURN(success, reinterpret_cast<ani_object>(undefinedRef));
    }
    return reinterpret_cast<ani_object>(result);
}
ani_object TransferWebKeyboardControllerToDynamic(ani_env* env, ani_class aniClass, ani_long node)
{
    CHECK_NULL_RETURN(env, nullptr);
    ani_ref undefinedRef;
    env->GetUndefined(&undefinedRef);
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getWebAniModifier()) {
        return reinterpret_cast<ani_object>(undefinedRef);
    }
    ani_ref result = nullptr;
    {
        napi_env jsenv {};
        bool success = arkts_napi_scope_open(env, &jsenv);
        CHECK_NULL_RETURN(success, reinterpret_cast<ani_object>(undefinedRef));
        napi_value dynamic =
            modifier->getWebAniModifier()->transferWebKeyboardControllerToDynamic(jsenv, reinterpret_cast<void*>(node));
        CHECK_NULL_RETURN(dynamic, reinterpret_cast<ani_object>(undefinedRef));
        success = arkts_napi_scope_close_n(jsenv, 1, &dynamic, &result);
        CHECK_NULL_RETURN(success, reinterpret_cast<ani_object>(undefinedRef));
    }
    return reinterpret_cast<ani_object>(result);
}
} // namespace OHOS::Ace::Ani
