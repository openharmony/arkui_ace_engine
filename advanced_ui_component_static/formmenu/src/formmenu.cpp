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
#include "base/log/log.h"
#include "ani_common_want.h"
#include "form_mgr.h"
#include "form_mgr_errors.h"
#include "ets_error_utils.h"


namespace {
    const char ANI_FORMMENU_NS[] = "arkui.FormMenu.formMenuItem";
    constexpr const char* ASYNC_CALLBACK_WRAPPER_CLASS_NAME = "arkui.FormMenu.AsyncCallbackWrapper";
}
namespace OHOS::Ace {

std::string ANIUtils_ANIStringToStdString(ani_env* env, ani_string ani_str)
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

ani_object WrapBusinessError(ani_env *env, const std::string &msg)
{
    if (env == nullptr) {
        LOGE("env is nullptr");
        return nullptr;
    }

    ani_status status = ANI_ERROR;
    ani_string aniMsg = nullptr;
    ani_ref undefRef = nullptr;
    ani_class cls = nullptr;
    ani_method method = nullptr;
    ani_object obj = nullptr;

    status = env->String_NewUTF8(msg.c_str(), msg.size(), &aniMsg);
    if (status != ANI_OK) {
        LOGE("String_NewUTF8 failed, status: %{public}d", status);
        return nullptr;
    }

    status = env->GetUndefined(&undefRef);
    if (status != ANI_OK) {
        LOGE("GetUndefined failed, status: %{public}d", status);
        return nullptr;
    }

    status = env->FindClass("escompat.Error", &cls);
    if (status != ANI_OK) {
        LOGE("FindClass failed, status: %{public}d", status);
        return nullptr;
    }

    status = env->Class_FindMethod(cls, "<ctor>", "C{std.core.String}C{escompat.ErrorOptions}:", &method);
    if (status != ANI_OK) {
        LOGE("Class_FindMethod failed, status: %{public}d", status);
        return nullptr;
    }

    status = env->Object_New(cls, method, &obj, aniMsg, undefRef);
    if (status != ANI_OK) {
        LOGE("Object_New failed, status: %{public}d", status);
        return nullptr;
    }

    return obj;
}

bool InvokeAsyncCallback(ani_env *env, ani_object obj, ani_object error, ani_object arg)
{
    if (env == nullptr) {
        LOGE("null env");
        return false;
    }
    ani_class clsCall = nullptr;
    ani_status status = env->FindClass(ASYNC_CALLBACK_WRAPPER_CLASS_NAME, &clsCall);
    if (status != ANI_OK || clsCall == nullptr) {
        LOGE("FindClass status: %{public}d, or null clsCall", status);
        return false;
    }
    ani_method method = nullptr;
    if ((status = env->Class_FindMethod(clsCall, "invoke", nullptr, &method)) != ANI_OK || method == nullptr) {
        LOGE("Class_FindMethod status: %{public}d, or null method", status);
        return false;
    }
    if (error == nullptr) {
        ani_ref nullRef = nullptr;
        env->GetNull(&nullRef);
        error = reinterpret_cast<ani_object>(nullRef);
    }
    if (arg == nullptr) {
        ani_ref undefinedRef = nullptr;
        env->GetUndefined(&undefinedRef);
        arg = reinterpret_cast<ani_object>(undefinedRef);
    }
    if ((status = env->Object_CallMethod_Void(obj, method, error, arg)) != ANI_OK) {
        LOGE("Object_CallMethod_Void status: %{public}d", status);
        return false;
    }
    return true;
}

ani_object CreateBusinessError(ani_env *env, ani_int code, const std::string& msg)
{
    if (env == nullptr) {
        LOGE("null env");
        return nullptr;
    }
    ani_class cls {};
    ani_method method {};
    ani_object obj = nullptr;
    ani_status status = env->FindClass("@ohos.base.BusinessError", &cls);
    if (status != ANI_OK) {
        LOGE("FindClass failed %{public}d", status);
        return nullptr;
    }
    status = env->Class_FindMethod(cls, "<ctor>", "iC{escompat.Error}:", &method);
    if (status != ANI_OK) {
        LOGE("Class_FindMethod failed %{public}d", status);
        return nullptr;
    }
    ani_object error = WrapBusinessError(env, msg);
    if (error == nullptr) {
        LOGE("error nulll");
        return nullptr;
    }
    status = env->Object_New(cls, method, &obj, code, error);
    if (status != ANI_OK) {
        LOGE("Object_New failed %{public}d", status);
        return nullptr;
    }
    return obj;
}

void InvokeAsyncWithBusinessError(ani_env *env, ani_object obj, int32_t internalErrorCode, ani_object arg)
{
    auto extErrCode = AppExecFwk::FormErrors::GetInstance().QueryExternalErrorCode(internalErrorCode);
    auto errMsg = AppExecFwk::FormErrors::GetInstance().QueryExternalErrorMessage(internalErrorCode, extErrCode);

    ani_boolean isUndefined;
    env->Reference_IsUndefined(obj, &isUndefined);
    auto callbackIsValid = (obj != nullptr) || (isUndefined != ANI_TRUE);
    if ((internalErrorCode != ERR_OK) && !callbackIsValid) {
        AbilityRuntime::EtsErrorUtil::ThrowError(env, extErrCode, errMsg);
        return;
    }

    ani_object errorObject = CreateBusinessError(env, extErrCode, errMsg);
    bool result = InvokeAsyncCallback(env, obj, errorObject, arg);
    if (!result) {
        auto errorCode = static_cast<int>(ERR_APPEXECFWK_FORM_COMMON_CODE);
        auto message = AppExecFwk::FormErrors::GetInstance().GetErrorMsgByExternalErrorCode(errorCode);
        AbilityRuntime::EtsErrorUtil::ThrowError(env, errorCode, message);
        return;
    }
}

static void requestPublishFormWithSnapshot([[maybe_unused]] ani_env* env, ani_object wantObj,
    ani_string formBindingDataStr, ani_object callback)
{
    LOGI(" call.");
    int64_t formId = 0;
    std::string errMsg;
    OHOS::AAFwk::Want want;
    bool ret = OHOS::AppExecFwk::UnwrapWant(env, wantObj, want);
    if (!ret) {
        LOGE("UnwrapWant failed when SetUiextensionWant");
        return;
    }
    std::unique_ptr<AppExecFwk::FormProviderData> formBindingData = std::make_unique<AppExecFwk::FormProviderData>();
    bool withFormBindingData = false;
    std::string formProviderDataStr = ANIUtils_ANIStringToStdString(env, formBindingDataStr);
    if (!formProviderDataStr.empty()) {
        withFormBindingData = true;
        formBindingData->SetDataString(formProviderDataStr);
        formBindingData->ParseImagesData();
    }
    std::vector<AppExecFwk::FormDataProxy> formDataProxies;
    int32_t errCode = AppExecFwk::FormMgr::GetInstance().RequestPublishFormWithSnapshot(want,
    withFormBindingData, formBindingData, formId, formDataProxies);
    if (!callback) {
        LOGE("callback is null");
        return;
    }
    ani_string formIdAniStr = nullptr;
    std::string formIdStr = std::to_string(formId);
    env->String_NewUTF8(formIdStr.c_str(), formIdStr.size(), &formIdAniStr);
    InvokeAsyncWithBusinessError(env, callback, errCode, formIdAniStr);
}
}

bool ANI_ConstructorForAni(ani_env* env)
{
    ani_namespace ns;
    if (ANI_OK != env->FindNamespace(ANI_FORMMENU_NS, &ns)) {
        LOGE("formmenu-ani Not found ns");
        return false;
    }
    std::array methods = {
        ani_native_function { "requestPublishFormWithSnapshot",
            "C{@ohos.app.ability.Want.Want}C{std.core.String}C{arkui.FormMenu.AsyncCallbackWrapper}:",
            reinterpret_cast<void*>(OHOS::Ace::requestPublishFormWithSnapshot) },
    };
    if (ANI_OK != env->Namespace_BindNativeFunctions(ns, methods.data(), methods.size())) {
        LOGE("formmenu-ani Namespace_BindNativeFunctions error");
        return false;
    }
    return true;
}

ANI_EXPORT ani_status ANI_Constructor(ani_vm* vm, uint32_t* result)
{
    ani_env* env;
    if (ANI_OK != vm->GetEnv(ANI_VERSION_1, &env)) {
        LOGE("formmenu-ani Unsupported ANI_VERSION_1");
        return ANI_ERROR;
    }
    if (ANI_ConstructorForAni(env)) {
        *result = ANI_VERSION_1;
        return ANI_OK;
    }
    return ANI_ERROR;
}