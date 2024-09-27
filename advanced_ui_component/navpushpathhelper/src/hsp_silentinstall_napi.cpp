/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "advanced_ui_component/navpushpathhelper/include/hsp_silentinstall_napi.h"
#include "advanced_ui_component/navpushpathhelper/include/hsp_silentinstall.h"
#include "base/log/log.h"

using namespace std;

namespace OHOS::NavPushPathHelper {

napi_value HspSilentInstallNapi::IsHspExist(napi_env env, napi_callback_info info)
{
    size_t argc = 2;
    size_t requireArgc = 2;
    napi_value args[2] = { nullptr };
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, args, nullptr, nullptr));
    NAPI_ASSERT(env, argc >= requireArgc, "Wrong number of arguments");

    // get first parameter：moduleName
    napi_valuetype moduleNameType;
    NAPI_CALL(env, napi_typeof(env, args[0], &moduleNameType));
    NAPI_ASSERT(env, moduleNameType == napi_string, "Wrong argument type. String expected.");

    size_t maxValueLen = 1024;
    char moduleNameValue[maxValueLen];
    size_t moduleNameLength = 0;
    napi_get_value_string_utf8(env, args[0], moduleNameValue, maxValueLen, &moduleNameLength);
    std::string moduleName = moduleNameValue;

    // get second parameter：pathName
    napi_valuetype pathNameType;
    NAPI_CALL(env, napi_typeof(env, args[1], &pathNameType));
    NAPI_ASSERT(env, pathNameType == napi_string, "Wrong argument type. String expected.");

    char pathNameValue[maxValueLen];
    size_t pathNameLength = 0;
    napi_get_value_string_utf8(env, args[1], pathNameValue, maxValueLen, &pathNameLength);
    std::string pathName = pathNameValue;

    bool isHspExits = HspSilentInstall::IsHspExist(moduleName, pathName);
    napi_value jsResult;
    NAPI_CALL(env, napi_get_boolean(env, isHspExits, &jsResult));
    return jsResult;
}

napi_value HspSilentInstallNapi::SilentInstall(napi_env env, napi_callback_info info)
{
    napi_value result = nullptr;
    size_t argc = 3;
    size_t requireArgc = 3;
    napi_value args[3] = { nullptr };
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, args, nullptr, nullptr));
    NAPI_ASSERT(env, argc >= requireArgc, "Wrong number of arguments");

    // get first parameter：moduleName
    std::string moduleName;
    getModuleName(env, args[0], moduleName);

    auto callbackData = new (std::nothrow) CallbackData();
    if (callbackData == nullptr) {
        return result;
    }
    uv_work_t *work = new (std::nothrow) uv_work_t;
    if (work == nullptr) {
        delete callbackData;
        callbackData = nullptr;
        return result;
    }
    int parameterNum = 1;
    const int indexTwo = 2;
    napi_create_reference(env, args[1], parameterNum, &(callbackData->successCallback));
    napi_create_reference(env, args[indexTwo], parameterNum, &(callbackData->failCallback));
    callbackData->env = env;

    auto successCallback = [callbackData, work]() {
        uv_loop_s *loop = nullptr;
        napi_get_uv_event_loop(callbackData->env, &loop);
        work->data = reinterpret_cast<void *>(callbackData);
        uv_queue_work(loop, work, [](uv_work_t *work) { (void)work; }, SendSuccessBackWork);
    };

    auto failCallback = [callbackData, work](int32_t errorCode, const std::string& errorMessage) {
        callbackData->errCode = errorCode;
        callbackData->errorMessage = errorMessage;

        uv_loop_s *loop = nullptr;
        napi_get_uv_event_loop(callbackData->env, &loop);
        work->data = reinterpret_cast<void *>(callbackData);
        uv_queue_work(loop, work, [](uv_work_t *work) { (void)work; }, SendFailBackWork);
    };

    HspSilentInstall::SilentInstall(moduleName, successCallback, failCallback);
    return result;
}

napi_value HspSilentInstallNapi::getModuleName(napi_env env, napi_value args, std::string& moduleName)
{
    napi_valuetype moduleNameType;
    NAPI_CALL(env, napi_typeof(env, args, &moduleNameType));
    NAPI_ASSERT(env, moduleNameType == napi_string, "Wrong argument type. String expected.");

    napi_status status;
    size_t maxValueLen = 1024;
    char moduleNameValue[maxValueLen];
    size_t moduleNameLength = 0;
    status = napi_get_value_string_utf8(env, args, moduleNameValue, maxValueLen, &moduleNameLength);
    NAPI_ASSERT(env, status == napi_ok, "Failed to napi_get_value_string_utf8");
    moduleName = moduleNameValue;
    return nullptr;
}

void HspSilentInstallNapi::SendSuccessBackWork(uv_work_t *work, int statusIn)
{
    if (work == nullptr) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_DEFAULT_DOMAIN, "SendSuccessBackWork -> work is null");
        return;
    }
    (void)statusIn;
    napi_status status;
    napi_handle_scope scope = nullptr;
    CallbackData *callbackData = reinterpret_cast<CallbackData *>(work->data);
    if (callbackData == nullptr) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_DEFAULT_DOMAIN, "SendSuccessBackWork -> callbackData is null");
        return;
    }

    napi_open_handle_scope(callbackData->env, &scope);
    if (scope == nullptr) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_DEFAULT_DOMAIN, "SendSuccessBackWork -> scope is null");
        return;
    }

    napi_value callback = nullptr;
    status = napi_get_reference_value(callbackData->env, callbackData->successCallback, &callback);
    if (status != napi_ok) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_DEFAULT_DOMAIN, "SendSuccessBackWork -> napi_get_reference_value error");
        napi_close_handle_scope(callbackData->env, scope);
        return;
    }

    napi_value result;
    status = napi_call_function(callbackData->env, nullptr, callback, 0, nullptr, &result);
    if (status != napi_ok) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_DEFAULT_DOMAIN, "SendSuccessBackWork -> napi_call_function error");
        napi_close_handle_scope(callbackData->env, scope);
        return;
    }

    napi_close_handle_scope(callbackData->env, scope);

    if (callbackData != nullptr) {
        delete callbackData;
        callbackData = nullptr;
    }

    if (work != nullptr) {
        delete work;
        work = nullptr;
    }
}

void HspSilentInstallNapi::SendFailBackWork(uv_work_t *work, int statusIn)
{
    if (work == nullptr) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_DEFAULT_DOMAIN, "SendSuccessBackWork -> work is null");
        return;
    }
    (void)statusIn;
    napi_status status;
    napi_handle_scope scope = nullptr;
    CallbackData *callbackData = reinterpret_cast<CallbackData *>(work->data);
    if (callbackData == nullptr) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_DEFAULT_DOMAIN, "SendFailBackWork -> callbackData is null");
        return;
    }

    napi_open_handle_scope(callbackData->env, &scope);
    if (scope == nullptr) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_DEFAULT_DOMAIN, "SendFailBackWork -> scope is null");
        return;
    }

    napi_value callback = nullptr;
    status = napi_get_reference_value(callbackData->env, callbackData->failCallback, &callback);
    if (status != napi_ok) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_DEFAULT_DOMAIN, "SendFailBackWork -> napi_get_reference_value error");
        napi_close_handle_scope(callbackData->env, scope);
        return;
    }

    size_t resultLength = 1;
    napi_value resultMessage = CreateResultMessage(callbackData);
    napi_value result[] = { resultMessage };
    status = napi_call_function(callbackData->env, nullptr, callback, resultLength, result, nullptr);
    if (status != napi_ok) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_DEFAULT_DOMAIN, "SendFailBackWork -> napi_call_function error");
        napi_close_handle_scope(callbackData->env, scope);
        return;
    }

    napi_close_handle_scope(callbackData->env, scope);

    if (callbackData != nullptr) {
        delete callbackData;
        callbackData = nullptr;
    }

    if (work != nullptr) {
        delete work;
        work = nullptr;
    }
}

napi_value HspSilentInstallNapi::CreateResultMessage(CallbackData *callbackData)
{
    napi_status status;
    napi_value result = nullptr;
    napi_value code = nullptr;

    status = napi_create_int32(callbackData->env, callbackData->errCode, &code);
    if (status != napi_ok) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_DEFAULT_DOMAIN, "CreateResultMessage -> napi_create_int32 error");
        return result;
    }

    napi_value message = nullptr;
    status = napi_create_string_utf8(callbackData->env, callbackData->errorMessage.c_str(),
        NAPI_AUTO_LENGTH, &message);
    if (status != napi_ok) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_DEFAULT_DOMAIN, "CreateResultMessage -> napi_create_string_utf8 error");
        return result;
    }

    napi_value businessError = nullptr;
    status = napi_create_object(callbackData->env, &businessError);
    if (status != napi_ok) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_DEFAULT_DOMAIN, "CreateResultMessage -> napi_create_object error");
        return result;
    }

    status = napi_set_named_property(callbackData->env, businessError, "code", code);
    if (status != napi_ok) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_DEFAULT_DOMAIN, "CreateResultMessage -> napi_set_named_property error");
        return result;
    }

    status = napi_set_named_property(callbackData->env, businessError, "message", message);
    if (status != napi_ok) {
        TAG_LOGE(OHOS::Ace::AceLogTag::ACE_DEFAULT_DOMAIN, "CreateResultMessage -> napi_set_named_property error");
        return result;
    }
    return businessError;
}
}