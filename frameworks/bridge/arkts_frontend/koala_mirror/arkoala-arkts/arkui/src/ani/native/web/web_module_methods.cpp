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

#include "interop_js/arkts_esvalue.h"
#include "interop_js/arkts_interop_js_api.h"

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
    std::function<long()> &getNativePtrFunc, std::function<void()> &releaseRefFunc)
{
    getNativePtrFunc = [vm, object = savePtr]() -> long {
        ani_long nativePtr = 0;
        ani_env* envTemp = GetAniEnv(vm);
        if (!envTemp || envTemp->Object_CallMethodByName_Long(
            reinterpret_cast<ani_object>(object), "innerGetThisVar", ":J", &nativePtr) != ANI_OK) {
            return 0;
        }
        return static_cast<long>(nativePtr);
    };
    releaseRefFunc = [vm, object = savePtr]() {
        ani_env* envTemp = GetAniEnv(vm);
        if (!envTemp) {
            return;
        }
        envTemp->GlobalReference_Delete(object);
    };
}

void SetWebOptions(ani_env* env, ani_class aniClass, ani_long node, ani_object object)
{
    auto* arkNode = reinterpret_cast<ArkUINodeHandle>(node);
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getWebAniModifier() || !env || !arkNode) {
        return;
    }

    ani_vm* vm = nullptr;
    ani_ref savePtr;
    if (env->GetVM(&vm) != ANI_OK ||
        env->GlobalReference_Create(reinterpret_cast<ani_ref>(object), &savePtr) != ANI_OK) {
        return;
    }

    auto setWebIdFunc = [vm, object = savePtr](int32_t nwebId) {
        ani_env* envTemp = GetAniEnv(vm);
        if (!envTemp || envTemp->Object_CallMethodByName_Void(
            reinterpret_cast<ani_object>(object), "_setNWebId", "I:V", static_cast<ani_int>(nwebId)) != ANI_OK) {
            return;
        }
    };
    auto setHapPathFunc = [vm, object = savePtr](const std::string& hapPath) {
        ani_string aniHapPath = nullptr;
        ani_env* envTemp = GetAniEnv(vm);
        if (!envTemp) {
            return;
        }
        if (envTemp->String_NewUTF8(hapPath.c_str(), hapPath.size(), &aniHapPath) != ANI_OK ||
            envTemp->Object_CallMethodByName_Void(
                reinterpret_cast<ani_object>(object), "_setHapPath", "Lstd/core/String;:V", aniHapPath) != ANI_OK) {
            envTemp->GlobalReference_Delete(object);
            return;
        }
        envTemp->GlobalReference_Delete(object);
    };
    std::function<long()> getNativePtrFunc = nullptr;
    std::function<void()> releaseRefFunc = nullptr;
    GetCommonFunc(vm, savePtr, getNativePtrFunc, releaseRefFunc);
    modifier->getWebAniModifier()->setWebOptions(arkNode, {
        .setWebIdFunc = std::move(setWebIdFunc),
        .setHapPathFunc = std::move(setHapPathFunc),
        .getNativePtrFunc = std::move(getNativePtrFunc),
        .releaseRefFunc = std::move(releaseRefFunc),
    });
}

void SetWebControllerControllerHandler(ani_env* env, ani_class aniClass, ani_long handler, ani_object object)
{
    void* controllerHandler = reinterpret_cast<void*>(handler);
    const auto* modifier = GetNodeAniModifier();
    if (!modifier || !modifier->getWebAniModifier() || !env || !controllerHandler) {
        return;
    }

    ani_vm* vm = nullptr;
    ani_ref savePtr;
    if (env->GetVM(&vm) != ANI_OK ||
        env->GlobalReference_Create(reinterpret_cast<ani_ref>(object), &savePtr) != ANI_OK) {
        return;
    }

    auto getWebIdFunc = [vm, object = savePtr]() -> int32_t {
        ani_int nwebId;
        ani_env* envTemp = GetAniEnv(vm);
        if (!envTemp || envTemp->Object_CallMethodByName_Int(
            reinterpret_cast<ani_object>(object), "getWebId", ":I", &nwebId) != ANI_OK) {
            return -1;
        }
        return static_cast<int32_t>(nwebId);
    };
    auto completeWindowNewFunc = [vm, object = savePtr](int32_t parentId) {
        ani_env* envTemp = GetAniEnv(vm);
        if (!envTemp) {
            return;
        }
        envTemp->Object_CallMethodByName_Void(
            reinterpret_cast<ani_object>(object), "innerCompleteWindowNew", "I:V", static_cast<ani_int>(parentId));
    };
    std::function<long()> getNativePtrFunc = nullptr;
    std::function<void()> releaseRefFunc = nullptr;
    GetCommonFunc(vm, savePtr, getNativePtrFunc, releaseRefFunc);
    modifier->getWebAniModifier()->setWebControllerControllerHandler(controllerHandler, {
        .getWebIdFunc = std::move(getWebIdFunc),
        .completeWindowNewFunc = std::move(completeWindowNewFunc),
        .getNativePtrFunc = std::move(getNativePtrFunc),
        .releaseRefFunc = std::move(releaseRefFunc),
    });
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
