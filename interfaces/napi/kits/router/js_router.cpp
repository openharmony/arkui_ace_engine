/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include <memory>
#include <cstdint>
#include <string>

#include "interfaces/napi/kits/utils/napi_utils.h"
#include "js_native_api.h"
#include "js_native_api_types.h"
#include "napi/native_api.h"
#include "napi/native_engine/native_value.h"
#include "napi/native_node_api.h"
#include "uv.h"

#include "frameworks/base/log/log.h"
#include "frameworks/bridge/common/utils/engine_helper.h"
#include "frameworks/bridge/js_frontend/engine/common/js_engine.h"

namespace OHOS::Ace::Napi {
const char EN_ALERT_APPROVE[] = "enableAlertBeforeBackPage:ok";
const char EN_ALERT_REJECT[] = "enableAlertBeforeBackPage:fail cancel";
const char DIS_ALERT_SUCCESS[] = "disableAlertBeforeBackPage:ok";

static constexpr size_t ARGC_WITH_MODE = 2;
static constexpr size_t ARGC_WITH_MODE_AND_CALLBACK = 3;
static constexpr uint32_t STANDARD = 0;
static constexpr uint32_t SINGLE = 1;

static void ParseUri(napi_env env, napi_value uriNApi, std::string& uriString)
{
    if (uriNApi != nullptr) {
        auto nativeUri = reinterpret_cast<NativeValue*>(uriNApi);
        auto resultUri = nativeUri->ToString();
        auto nativeStringUri = reinterpret_cast<NativeString*>(resultUri->GetInterface(NativeString::INTERFACE_ID));
        size_t uriLen = nativeStringUri->GetLength() + 1;
        std::unique_ptr<char[]> uri = std::make_unique<char[]>(uriLen);
        size_t retLen = 0;
        napi_get_value_string_utf8(env, uriNApi, uri.get(), uriLen, &retLen);
        uriString = uri.get();
    }
}

static void ParseParams(napi_env env, napi_value params, std::string& paramsString)
{
    // TODO: Save the original data instead of making the serial number.
    if (params == nullptr) {
        return;
    }
    napi_value globalValue;
    napi_get_global(env, &globalValue);
    napi_value jsonValue;
    napi_get_named_property(env, globalValue, "JSON", &jsonValue);
    napi_value stringifyValue;
    napi_get_named_property(env, jsonValue, "stringify", &stringifyValue);
    napi_value funcArgv[1] = { params };
    napi_value returnValue;
    napi_call_function(env, jsonValue, stringifyValue, 1, funcArgv, &returnValue);
    auto nativeValue = reinterpret_cast<NativeValue*>(returnValue);
    auto resultValue = nativeValue->ToString();
    auto nativeString = reinterpret_cast<NativeString*>(resultValue->GetInterface(NativeString::INTERFACE_ID));
    size_t len = nativeString->GetLength() + 1;
    std::unique_ptr<char[]> paramsChar = std::make_unique<char[]>(len);
    size_t ret = 0;
    napi_get_value_string_utf8(env, returnValue, paramsChar.get(), len, &ret);
    paramsString = paramsChar.get();
}

struct RouterAsyncContext {
    napi_env env = nullptr;
    napi_ref callbackSuccess = nullptr;
    napi_ref callbackFail = nullptr;
    napi_ref callbackComplete = nullptr;
    int32_t callbackType = 0;
    std::set<std::string> callbacks;
    std::string paramsString;
    std::string uriString;
    uint32_t mode;
    bool isModeType = false;
    napi_deferred deferred = nullptr;
    napi_ref callbackRef = nullptr;
    napi_async_work work = nullptr;
    ~RouterAsyncContext()
    {
        if (callbackSuccess) {
            napi_delete_reference(env, callbackSuccess);
        }
        if (callbackFail) {
            napi_delete_reference(env, callbackFail);
        }
        if (callbackComplete) {
            napi_delete_reference(env, callbackComplete);
        }
    }
};
static napi_value JSRouterPush(napi_env env, napi_callback_info info)
{
    LOGI("NAPI router push called");
    size_t requireArgc = 1;
    size_t argc = ARGC_WITH_MODE;
    napi_value argv[ARGC_WITH_MODE] = { 0 };
    napi_value thisVar = nullptr;
    void* data = nullptr;
    napi_get_cb_info(env, info, &argc, argv, &thisVar, &data);
    if (argc < requireArgc) {
        LOGE("params number err");
        return nullptr;
    }
    napi_value uriNApi = nullptr;
    napi_value params = nullptr;
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, argv[0], &valueType);
    if (valueType == napi_object) {
        napi_get_named_property(env, argv[0], "url", &uriNApi);
        napi_typeof(env, uriNApi, &valueType);
        if (valueType != napi_string) {
            LOGE("url is invalid");
            return nullptr;
        }
        napi_get_named_property(env, argv[0], "params", &params);
    }
    std::string paramsString;
    ParseParams(env, params, paramsString);
    std::string uriString;
    napi_typeof(env, uriNApi, &valueType);
    if (valueType == napi_string) {
        ParseUri(env, uriNApi, uriString);
    } else {
        LOGW("The parameter type is incorrect.");
    }
    auto delegate = EngineHelper::GetCurrentDelegate();
    if (!delegate) {
        LOGE("can not get delegate.");
        return nullptr;
    }

    napi_typeof(env, argv[1], &valueType);
    if (argc == ARGC_WITH_MODE && valueType == napi_number) {
        uint32_t mode = STANDARD;
        napi_get_value_uint32(env, argv[1], &mode);
        LOGI("router mode with single");
        delegate->PushWithMode(uriString, paramsString, mode);
        return nullptr;
    }
    delegate->Push(uriString, paramsString);
    return nullptr;
}

bool ParseParamWithCallback(napi_env env, RouterAsyncContext* asyncContext, const size_t argc, napi_value* argv)
{
    asyncContext->env = env;
    for (size_t i = 0; i < argc; i++) {
        napi_valuetype valueType = napi_undefined;
        napi_typeof(env, argv[i], &valueType);
        if ((i == 0) && valueType == napi_object) {
            napi_value uriNApi = nullptr;
            napi_value params = nullptr;
            napi_get_named_property(env, argv[i], "url", &uriNApi);
            napi_typeof(env, uriNApi, &valueType);
            if (valueType != napi_string) {
                LOGE("url is invalid");
                NapiThrow(env, "The type of the url parameter is not string.", Framework::ERROR_CODE_PARAM_INVALID);
                return false;
            }
            napi_get_named_property(env, argv[i], "params", &params);
            std::string paramsString;
            ParseParams(env, params, paramsString);
            asyncContext->paramsString = paramsString;
            std::string uriString;
            napi_typeof(env, uriNApi, &valueType);
            if (valueType == napi_string) {
                ParseUri(env, uriNApi, uriString);
                asyncContext->uriString = uriString;
            } else {
                LOGW("The parameter type is incorrect.");
            }
        } else if (valueType == napi_number) {
            uint32_t mode = STANDARD;
            napi_get_value_uint32(env, argv[i], &mode);
            LOGI("router mode with single");
            asyncContext->mode = mode;
            asyncContext->isModeType = true;
        } else if (valueType == napi_function) {
            napi_create_reference(env, argv[i], 1, &asyncContext->callbackRef);
        } else {
            delete asyncContext;
            asyncContext = nullptr;
            NapiThrow(env, "The type of parameters is incorrect.", Framework::ERROR_CODE_PARAM_INVALID);
            return false;
        }
    }
    return true;
}

static napi_value JSRouterPushWithCallback(napi_env env, napi_callback_info info)
{
    napi_value result = nullptr;
    size_t requireArgc = 1;
    size_t argc = ARGC_WITH_MODE_AND_CALLBACK;
    napi_value argv[ARGC_WITH_MODE_AND_CALLBACK] = { 0 };
    napi_value thisVar = nullptr;
    void* data = nullptr;
    napi_get_cb_info(env, info, &argc, argv, &thisVar, &data);
    if (argc < requireArgc) {
        LOGE("params number err");
        NapiThrow(env, "The number of parameters must be greater than or equal to 1.",
            Framework::ERROR_CODE_PARAM_INVALID);
        return result;
    }
    auto asyncContext = new RouterAsyncContext();
    if (!ParseParamWithCallback(env, asyncContext, argc, argv)) {
        LOGE("parse params failed");
        return result;
    }

    if (asyncContext->callbackRef == nullptr) {
        napi_create_promise(env, &asyncContext->deferred, &result);
    } else {
        asyncContext->deferred = nullptr;
        napi_get_undefined(env, &result);
    }
    napi_value resource = nullptr;
    napi_create_string_utf8(env, "JSRouterPush", NAPI_AUTO_LENGTH, &resource);
    napi_create_async_work(
        env, nullptr, resource, [](napi_env env, void* data) {},
        [](napi_env env, napi_status status, void* data) {
            RouterAsyncContext* asyncContext = (RouterAsyncContext*)data;
            auto errorCallback = [env, asyncContext](const std::string& message, int32_t errCode) {
                napi_value ret;
                napi_value code = nullptr;
                std::string strCode = std::to_string(errCode);
                napi_create_string_utf8(env, strCode.c_str(), strCode.length(), &code);

                napi_value msg = nullptr;
                std::string strMsg = ErrorToMessage(errCode) + message;
                LOGE("napi throw errCode %d strMsg %s", errCode, strMsg.c_str());
                napi_create_string_utf8(env, strMsg.c_str(), strMsg.length(), &msg);

                napi_value error = nullptr;
                napi_create_error(env, code, msg, &error);
                if (asyncContext->deferred) {
                    napi_reject_deferred(env, asyncContext->deferred, error);
                } else {
                    napi_value callback = nullptr;
                    napi_get_reference_value(env, asyncContext->callbackRef, &callback);
                    napi_call_function(env, nullptr, callback, 1, &error, &ret);
                    napi_delete_reference(env, asyncContext->callbackRef);
                }
                delete asyncContext;
            };
            auto delegate = EngineHelper::GetCurrentDelegate();
            if (delegate) {
                if (asyncContext->isModeType) {
                    delegate->PushWithModeAndCallback(
                        asyncContext->uriString, asyncContext->paramsString, asyncContext->mode, errorCallback);
                } else {
                    delegate->PushWithCallback(asyncContext->uriString, asyncContext->paramsString, errorCallback);
                }
            } else {
                LOGE("delegate is null");
                napi_value code = nullptr;
                std::string strCode = std::to_string(Framework::ERROR_CODE_INTERNAL_ERROR);
                napi_create_string_utf8(env, strCode.c_str(), strCode.length(), &code);
                napi_value msg = nullptr;
                std::string strMsg = ErrorToMessage(Framework::ERROR_CODE_INTERNAL_ERROR) + "Can not get delegate.";
                napi_create_string_utf8(env, strMsg.c_str(), strMsg.length(), &msg);
                napi_value error = nullptr;
                napi_create_error(env, code, msg, &error);

                if (asyncContext->deferred) {
                    napi_reject_deferred(env, asyncContext->deferred, error);
                } else {
                    napi_value ret1;
                    napi_value callback = nullptr;
                    napi_get_reference_value(env, asyncContext->callbackRef, &callback);
                    napi_call_function(env, nullptr, callback, 1, &error, &ret1);
                    napi_delete_reference(env, asyncContext->callbackRef);
                }
            }
            napi_delete_async_work(env, asyncContext->work);
        },
        (void*)asyncContext, &asyncContext->work);
    napi_queue_async_work(env, asyncContext->work);
    return result;
}

static napi_value JSRouterReplace(napi_env env, napi_callback_info info)
{
    size_t requireArgc = 1;
    size_t argc = ARGC_WITH_MODE;
    napi_value argv[ARGC_WITH_MODE] = { 0 };
    napi_value thisVar = nullptr;
    void* data = nullptr;
    napi_get_cb_info(env, info, &argc, argv, &thisVar, &data);
    if (argc < requireArgc) {
        LOGE("params number err");
        return nullptr;
    }
    napi_value uriNApi = nullptr;
    napi_value params = nullptr;
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, argv[0], &valueType);
    if (valueType == napi_object) {
        napi_get_named_property(env, argv[0], "url", &uriNApi);
        napi_typeof(env, uriNApi, &valueType);
        if (valueType != napi_string) {
            LOGE("url is invalid");
            return nullptr;
        }
        napi_get_named_property(env, argv[0], "params", &params);
    }
    std::string paramsString;
    ParseParams(env, params, paramsString);
    std::string uriString;
    napi_typeof(env, uriNApi, &valueType);
    if (valueType == napi_string) {
        ParseUri(env, uriNApi, uriString);
    } else {
        LOGW("The parameter type is incorrect.");
    }

    auto delegate = EngineHelper::GetCurrentDelegate();
    if (!delegate) {
        LOGE("can not get delegate.");
        return nullptr;
    }

    napi_typeof(env, argv[1], &valueType);
    if (argc == ARGC_WITH_MODE && valueType == napi_number) {
        uint32_t mode = STANDARD;
        napi_get_value_uint32(env, argv[1], &mode);
        LOGI("router mode with single");
        delegate->ReplaceWithMode(uriString, paramsString, mode);
        return nullptr;
    }

    delegate->Replace(uriString, paramsString);
    return nullptr;
}

static napi_value JSRouterReplaceWithCallback(napi_env env, napi_callback_info info)
{
    napi_value result = nullptr;
    size_t requireArgc = 1;
    size_t argc = ARGC_WITH_MODE_AND_CALLBACK;
    napi_value argv[ARGC_WITH_MODE_AND_CALLBACK] = { 0 };
    napi_value thisVar = nullptr;
    void* data = nullptr;
    napi_get_cb_info(env, info, &argc, argv, &thisVar, &data);
    if (argc < requireArgc) {
        LOGE("params number err");
        NapiThrow(env, "The number of parameters must be greater than or equal to 1.",
            Framework::ERROR_CODE_PARAM_INVALID);
        return result;
    }
    auto asyncContext = new RouterAsyncContext();
    if (!ParseParamWithCallback(env, asyncContext, argc, argv)) {
        LOGE("parse params failed");
        return result;
    }

    if (asyncContext->callbackRef == nullptr) {
        napi_create_promise(env, &asyncContext->deferred, &result);
    } else {
        asyncContext->deferred = nullptr;
        napi_get_undefined(env, &result);
    }
    napi_value resource = nullptr;
    napi_create_string_utf8(env, "JSRouterReplace", NAPI_AUTO_LENGTH, &resource);
    napi_create_async_work(
        env, nullptr, resource, [](napi_env env, void* data) {},
        [](napi_env env, napi_status status, void* data) {
            RouterAsyncContext* asyncContext = (RouterAsyncContext*)data;
            auto errorCallback = [env, asyncContext](const std::string& message, int32_t errCode) {
                napi_value ret;
                napi_value code = nullptr;
                std::string strCode = std::to_string(errCode);
                napi_create_string_utf8(env, strCode.c_str(), strCode.length(), &code);

                napi_value msg = nullptr;
                std::string strMsg = ErrorToMessage(errCode) + message;
                LOGE("napi throw errCode %{public}d strMsg %{public}s", errCode, strMsg.c_str());
                napi_create_string_utf8(env, strMsg.c_str(), strMsg.length(), &msg);

                napi_value error = nullptr;
                napi_create_error(env, code, msg, &error);
                if (asyncContext->deferred) {
                    napi_reject_deferred(env, asyncContext->deferred, error);
                } else {
                    napi_value callback = nullptr;
                    napi_get_reference_value(env, asyncContext->callbackRef, &callback);
                    napi_call_function(env, nullptr, callback, 1, &error, &ret);
                    napi_delete_reference(env, asyncContext->callbackRef);
                }
                delete asyncContext;
            };
            auto delegate = EngineHelper::GetCurrentDelegate();
            if (delegate) {
                if (asyncContext->isModeType) {
                    delegate->ReplaceWithModeAndCallback(
                        asyncContext->uriString, asyncContext->paramsString, asyncContext->mode, errorCallback);
                } else {
                    delegate->ReplaceWithCallback(asyncContext->uriString, asyncContext->paramsString, errorCallback);
                }
            } else {
                LOGE("delegate is null");
                napi_value code = nullptr;
                std::string strCode = std::to_string(Framework::ERROR_CODE_INTERNAL_ERROR);
                napi_create_string_utf8(env, strCode.c_str(), strCode.length(), &code);
                napi_value msg = nullptr;
                std::string strMsg = ErrorToMessage(Framework::ERROR_CODE_INTERNAL_ERROR) + "Can not get delegate.";
                napi_create_string_utf8(env, strMsg.c_str(), strMsg.length(), &msg);
                napi_value error = nullptr;
                napi_create_error(env, code, msg, &error);

                if (asyncContext->deferred) {
                    napi_reject_deferred(env, asyncContext->deferred, error);
                } else {
                    napi_value ret1;
                    napi_value callback = nullptr;
                    napi_get_reference_value(env, asyncContext->callbackRef, &callback);
                    napi_call_function(env, nullptr, callback, 1, &error, &ret1);
                    napi_delete_reference(env, asyncContext->callbackRef);
                }
            }
            napi_delete_async_work(env, asyncContext->work);
        },
        (void*)asyncContext, &asyncContext->work);
    napi_queue_async_work(env, asyncContext->work);
    return result;
}

static napi_value JSRouterBack(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value argv = nullptr;
    napi_value thisVar = nullptr;
    void* data = nullptr;
    napi_get_cb_info(env, info, &argc, &argv, &thisVar, &data);

    auto delegate = EngineHelper::GetCurrentDelegate();
    if (!delegate) {
        LOGE("can not get delegate.");
        NapiThrow(env, "Can not get delegate.", Framework::ERROR_CODE_INTERNAL_ERROR);
        return nullptr;
    }
    std::string uriString = "";
    std::string paramsString = "";
    napi_value uriNApi = nullptr;
    napi_value params = nullptr;
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, argv, &valueType);
    if (valueType == napi_object) {
        napi_get_named_property(env, argv, "url", &uriNApi);
        napi_typeof(env, uriNApi, &valueType);
        if (valueType == napi_undefined) {
            napi_get_named_property(env, argv, "path", &uriNApi);
            napi_typeof(env, uriNApi, &valueType);
        }
        if (valueType == napi_string) {
            ParseUri(env, uriNApi, uriString);
        } else {
            LOGW("the url and path is all invalid");
        }

        napi_get_named_property(env, argv, "params", &params);
        napi_typeof(env, params, &valueType);
        if (valueType == napi_object) {
            ParseParams(env, params, paramsString);
        } else {
            LOGW("The parameter type is incorrect.");
        }
    }
    delegate->Back(uriString, paramsString);
    return nullptr;
}

static napi_value JSRouterClear(napi_env env, napi_callback_info info)
{
    auto delegate = EngineHelper::GetCurrentDelegate();
    if (!delegate) {
        LOGE("can not get delegate.");
        NapiThrow(env, "Can not get delegate.", Framework::ERROR_CODE_INTERNAL_ERROR);
        return nullptr;
    }
    delegate->Clear();
    return nullptr;
}

static napi_value JSRouterGetLength(napi_env env, napi_callback_info info)
{
    auto delegate = EngineHelper::GetCurrentDelegate();
    if (!delegate) {
        LOGE("can not get delegate.");
        NapiThrow(env, "Can not get delegate.", Framework::ERROR_CODE_INTERNAL_ERROR);
        return nullptr;
    }
    int32_t routeNumber = delegate->GetStackSize();
    napi_value routeNApiNum = nullptr;
    napi_create_int32(env, routeNumber, &routeNApiNum);
    napi_value result = nullptr;
    napi_coerce_to_string(env, routeNApiNum, &result);
    return result;
}

static napi_value JSRouterGetState(napi_env env, napi_callback_info info)
{
    int32_t routeIndex = 0;
    std::string routeName;
    std::string routePath;
    auto delegate = EngineHelper::GetCurrentDelegate();
    if (!delegate) {
        LOGE("can not get delegate.");
        NapiThrow(env, "Can not get delegate.", Framework::ERROR_CODE_INTERNAL_ERROR);
        return nullptr;
    }
    delegate->GetState(routeIndex, routeName, routePath);
    size_t routeNameLen = routeName.length();
    size_t routePathLen = routePath.length();

    napi_value resultArray[3] = { 0 };
    napi_create_int32(env, routeIndex, &resultArray[0]);
    napi_create_string_utf8(env, routeName.c_str(), routeNameLen, &resultArray[1]);
    napi_create_string_utf8(env, routePath.c_str(), routePathLen, &resultArray[2]);

    napi_value result = nullptr;
    napi_create_object(env, &result);
    napi_set_named_property(env, result, "index", resultArray[0]);
    napi_set_named_property(env, result, "name", resultArray[1]);
    napi_set_named_property(env, result, "path", resultArray[2]);
    return result;
}

void CallBackToJSTread(RouterAsyncContext* context)
{
    uv_loop_s* loop = nullptr;
    napi_get_uv_event_loop(context->env, &loop);

    uv_work_t* work = new uv_work_t;
    work->data = (void*)context;

    uv_queue_work(
        loop, work, [](uv_work_t* work) {},
        [](uv_work_t* work, int status) {
            RouterAsyncContext* context = (RouterAsyncContext*)work->data;
            napi_handle_scope scope = nullptr;
            napi_open_handle_scope(context->env, &scope);
            if (scope == nullptr) {
                return;
            }

            napi_value result = nullptr;
            napi_value callback = nullptr;
            napi_value ret = nullptr;
            if (Framework::AlertState(context->callbackType) == Framework::AlertState::USER_CONFIRM) {
                if (context->callbackSuccess) {
                    napi_create_string_utf8(context->env, EN_ALERT_APPROVE, NAPI_AUTO_LENGTH, &result);
                    napi_value argv[1] = { result };
                    napi_get_reference_value(context->env, context->callbackSuccess, &callback);
                    napi_call_function(context->env, nullptr, callback, 1, argv, &ret);
                }
                if (context->callbackComplete) {
                    napi_get_reference_value(context->env, context->callbackComplete, &callback);
                    napi_call_function(context->env, nullptr, callback, 0, nullptr, &ret);
                }
            }
            if (Framework::AlertState(context->callbackType) == Framework::AlertState::USER_CANCEL) {
                if (context->callbackFail) {
                    napi_create_string_utf8(context->env, EN_ALERT_REJECT, NAPI_AUTO_LENGTH, &result);
                    napi_value argv[1] = { result };
                    napi_get_reference_value(context->env, context->callbackFail, &callback);
                    napi_call_function(context->env, nullptr, callback, 1, argv, &ret);
                }
                if (context->callbackComplete) {
                    napi_get_reference_value(context->env, context->callbackComplete, &callback);
                    napi_call_function(context->env, nullptr, callback, 0, nullptr, &ret);
                }
            }

            napi_close_handle_scope(context->env, scope);

            if (work != nullptr) {
                delete work;
            }
        });
}

static napi_value JSRouterEnableAlertBeforeBackPage(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value argv = nullptr;
    napi_value thisVar = nullptr;
    void* data = nullptr;
    napi_get_cb_info(env, info, &argc, &argv, &thisVar, &data);

    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, argv, &valueType);
    if (valueType != napi_object) {
        LOGW("EnableAlertBeforeBackPage: params is null");
        NapiThrow(env, "The type of the parameter is not object.", Framework::ERROR_CODE_PARAM_INVALID);
        return nullptr;
    }

    napi_value messageNapi = nullptr;
    std::unique_ptr<char[]> messageChar;
    napi_get_named_property(env, argv, "message", &messageNapi);
    napi_typeof(env, messageNapi, &valueType);
    if (valueType == napi_string) {
        size_t length = 0;
        napi_get_value_string_utf8(env, messageNapi, nullptr, 0, &length);
        messageChar = std::make_unique<char[]>(length + 1);
        napi_get_value_string_utf8(env, messageNapi, messageChar.get(), length + 1, &length);
    } else {
        LOGW("EnableAlertBeforeBackPage: message is null");
        NapiThrow(env, "The type of the message is not string.", Framework::ERROR_CODE_PARAM_INVALID);
        return nullptr;
    }

    auto delegate = EngineHelper::GetCurrentDelegate();
    if (!delegate) {
        LOGW("EnableAlertBeforeBackPage: delegate is null");
        NapiThrow(env, "Can not get delegate.", Framework::ERROR_CODE_INTERNAL_ERROR);
        return nullptr;
    }

    auto routerAsyncContext = new RouterAsyncContext();
    routerAsyncContext->env = env;
    napi_value successFunc = nullptr;
    napi_value failFunc = nullptr;
    napi_value completeFunc = nullptr;
    napi_get_named_property(env, argv, "success", &successFunc);
    napi_get_named_property(env, argv, "cancel", &failFunc);
    napi_get_named_property(env, argv, "complete", &completeFunc);
    napi_typeof(env, successFunc, &valueType);
    if (valueType == napi_function) {
        napi_create_reference(env, successFunc, 1, &routerAsyncContext->callbackSuccess);
    }

    napi_typeof(env, failFunc, &valueType);
    if (valueType == napi_function) {
        napi_create_reference(env, failFunc, 1, &routerAsyncContext->callbackFail);
    }
    napi_typeof(env, completeFunc, &valueType);
    if (valueType == napi_function) {
        napi_create_reference(env, completeFunc, 1, &routerAsyncContext->callbackComplete);
    }

    auto dilogCallback = [routerAsyncContext](int32_t callbackType) {
        LOGI("callback after dialog click, callbackType = %{public}d", callbackType);
        if (routerAsyncContext && Framework::AlertState(callbackType) == Framework::AlertState::RECOVERY) {
            delete routerAsyncContext;
            return;
        }
        if (routerAsyncContext) {
            routerAsyncContext->callbackType = callbackType;
        }
        CallBackToJSTread(routerAsyncContext);
    };
    delegate->EnableAlertBeforeBackPage(messageChar.get(), std::move(dilogCallback));

    return nullptr;
}

static napi_value JSRouterDisableAlertBeforeBackPage(napi_env env, napi_callback_info info)
{
    auto delegate = EngineHelper::GetCurrentDelegate();
    if (delegate) {
        delegate->DisableAlertBeforeBackPage();
    } else {
        LOGW("DisableAlertBeforeBackPage: delegate is null");
        NapiThrow(env, "Can not get delegate.", Framework::ERROR_CODE_INTERNAL_ERROR);
        return nullptr;
    }

    size_t argc = 1;
    napi_value argv = nullptr;
    napi_value thisVar = nullptr;
    void* data = nullptr;
    napi_get_cb_info(env, info, &argc, &argv, &thisVar, &data);
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, argv, &valueType);
    if (valueType == napi_object) {
        napi_value successFunc = nullptr;
        napi_value completeFunc = nullptr;
        napi_get_named_property(env, argv, "success", &successFunc);
        napi_get_named_property(env, argv, "complete", &completeFunc);

        napi_value result = nullptr;
        napi_value ret = nullptr;
        napi_create_string_utf8(env, DIS_ALERT_SUCCESS, NAPI_AUTO_LENGTH, &result);
        napi_value argv[1] = { result };

        napi_typeof(env, successFunc, &valueType);
        if (valueType == napi_function) {
            napi_call_function(env, nullptr, successFunc, 1, argv, &ret);
        }
        napi_typeof(env, completeFunc, &valueType);
        if (valueType == napi_function) {
            napi_call_function(env, nullptr, completeFunc, 1, argv, &ret);
        }
    }
    return nullptr;
}

static napi_value JSRouterGetParams(napi_env env, napi_callback_info info)
{
    auto delegate = EngineHelper::GetCurrentDelegate();
    if (!delegate) {
        LOGE("can not get delegate.");
        NapiThrow(env, "Can not get delegate.", Framework::ERROR_CODE_INTERNAL_ERROR);
        return nullptr;
    }
    std::string paramsStr = delegate->GetParams();
    if (paramsStr.empty()) {
        LOGI("PageGetParams params is null");
        return nullptr;
    }
    napi_value globalValue;
    napi_get_global(env, &globalValue);
    napi_value jsonValue;
    napi_get_named_property(env, globalValue, "JSON", &jsonValue);
    napi_value parseValue;
    napi_get_named_property(env, jsonValue, "parse", &parseValue);
    napi_value routerParamsNApi;
    napi_create_string_utf8(env, paramsStr.c_str(), NAPI_AUTO_LENGTH, &routerParamsNApi);
    napi_value funcArgv[1] = { routerParamsNApi };
    napi_value result;
    napi_call_function(env, jsonValue, parseValue, 1, funcArgv, &result);
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, result, &valueType);
    if (valueType != napi_object) {
        LOGE("parse result fail");
        return nullptr;
    }
    return result;
}

static napi_value RouterExport(napi_env env, napi_value exports)
{
    napi_value routerMode = nullptr;
    napi_create_object(env, &routerMode);
    napi_value prop = nullptr;
    napi_create_uint32(env, STANDARD, &prop);
    napi_set_named_property(env, routerMode, "Standard", prop);
    napi_create_uint32(env, SINGLE, &prop);
    napi_set_named_property(env, routerMode, "Single", prop);

    napi_property_descriptor routerDesc[] = {
        DECLARE_NAPI_FUNCTION("push", JSRouterPush),
        DECLARE_NAPI_FUNCTION("pushUrl", JSRouterPushWithCallback),
        DECLARE_NAPI_FUNCTION("replace", JSRouterReplace),
        DECLARE_NAPI_FUNCTION("replaceUrl", JSRouterReplaceWithCallback),
        DECLARE_NAPI_FUNCTION("back", JSRouterBack),
        DECLARE_NAPI_FUNCTION("clear", JSRouterClear),
        DECLARE_NAPI_FUNCTION("getLength", JSRouterGetLength),
        DECLARE_NAPI_FUNCTION("getState", JSRouterGetState),
        DECLARE_NAPI_FUNCTION("enableAlertBeforeBackPage", JSRouterEnableAlertBeforeBackPage),
        DECLARE_NAPI_FUNCTION("enableBackPageAlert", JSRouterEnableAlertBeforeBackPage),
        DECLARE_NAPI_FUNCTION("disableAlertBeforeBackPage", JSRouterDisableAlertBeforeBackPage),
        DECLARE_NAPI_FUNCTION("getParams", JSRouterGetParams),
        DECLARE_NAPI_PROPERTY("RouterMode", routerMode),
    };
    NAPI_CALL(env, napi_define_properties(env, exports, sizeof(routerDesc) / sizeof(routerDesc[0]), routerDesc));

    return exports;
}

static napi_module routerModule = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = RouterExport,
    .nm_modname = "router",
    .nm_priv = ((void*)0),
    .reserved = { 0 },
};

extern "C" __attribute__((constructor)) void RouterRegister()
{
    napi_module_register(&routerModule);
}

} // namespace OHOS::Ace::Napi
