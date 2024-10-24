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


#include "interfaces/napi/kits/utils/napi_utils.h"

#include "core/common/ace_engine.h"
#include "frameworks/bridge/common/utils/engine_helper.h"

namespace OHOS::Ace::Napi {
const char EN_ALERT_APPROVE[] = "enableAlertBeforeBackPage:ok";
const char EN_ALERT_REJECT[] = "enableAlertBeforeBackPage:fail cancel";
const char DIS_ALERT_SUCCESS[] = "disableAlertBeforeBackPage:ok";

static constexpr size_t ARGC_WITH_MODE = 2;
static constexpr size_t ARGC_WITH_ROUTER_PARAMTER = 2;
static constexpr size_t ARGC_WITH_MODE_AND_CALLBACK = 3;
static constexpr uint32_t STANDARD = 0;
static constexpr uint32_t SINGLE = 1;
static constexpr uint32_t INVALID = 2;
static constexpr uint32_t RESULT_ARRAY_INDEX_INDEX = 0;
static constexpr uint32_t RESULT_ARRAY_NAME_INDEX = 1;
static constexpr uint32_t RESULT_ARRAY_PATH_INDEX = 2;
static constexpr uint32_t RESULT_ARRAY_LENGTH = 3;

static void ParseUri(napi_env env, napi_value uriNApi, std::string& uriString)
{
    if (uriNApi != nullptr) {
        size_t uriLen = 0;
        napi_get_value_string_utf8(env, uriNApi, nullptr, 0, &uriLen);
        std::unique_ptr<char[]> uri = std::make_unique<char[]>(uriLen + 1);
        napi_get_value_string_utf8(env, uriNApi, uri.get(), uriLen + 1, &uriLen);
        uriString = uri.get();
    }
}

static void ParseParams(napi_env env, napi_value params, std::string& paramsString)
{
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
    if (napi_call_function(env, jsonValue, stringifyValue, 1, funcArgv, &returnValue) != napi_ok) {
        TAG_LOGE(AceLogTag::ACE_ROUTER,
            "Router parse param failed, probably caused by invalid format of JSON object 'params'");
    }
    size_t len = 0;
    napi_get_value_string_utf8(env, returnValue, nullptr, 0, &len);
    std::unique_ptr<char[]> paramsChar = std::make_unique<char[]>(len + 1);
    napi_get_value_string_utf8(env, returnValue, paramsChar.get(), len + 1, &len);
    paramsString = paramsChar.get();
}

static napi_value ParseJSONParams(napi_env env, const std::string& paramsStr)
{
    napi_value globalValue;
    napi_get_global(env, &globalValue);
    napi_value jsonValue;
    napi_get_named_property(env, globalValue, "JSON", &jsonValue);
    napi_value parseValue;
    napi_get_named_property(env, jsonValue, "parse", &parseValue);
    
    napi_value paramsNApi;
    napi_create_string_utf8(env, paramsStr.c_str(), NAPI_AUTO_LENGTH, &paramsNApi);
    napi_value funcArgv[1] = { paramsNApi };
    napi_value result;
    napi_call_function(env, jsonValue, parseValue, 1, funcArgv, &result);
    
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, result, &valueType);
    if (valueType != napi_object) {
        return nullptr;
    }
    
    return result;
}

static void ParseRecoverable(napi_env env, napi_value recoverableNApi, bool& recoverable)
{
    if (recoverableNApi == nullptr) {
        return;
    }
    napi_get_value_bool(env, recoverableNApi, &recoverable);
}

struct RouterAsyncContext {
    napi_env env = nullptr;
    napi_ref callbackSuccess = nullptr;
    napi_ref callbackFail = nullptr;
    napi_ref callbackComplete = nullptr;
    int32_t callbackType = 0;
    std::string keyForUrl;
    std::string paramsString;
    std::string uriString;
    bool recoverable = true;
    uint32_t mode = STANDARD;
    napi_deferred deferred = nullptr;
    napi_ref callbackRef = nullptr;
    int32_t callbackCode = 0;
    std::string callbackMsg;
    int32_t instanceId = -1;
    ~RouterAsyncContext()
    {
        if (callbackRef) {
            napi_delete_reference(env, callbackRef);
        }
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

using RouterFunc = std::function<void(const std::string&, const std::string&, int32_t)>;

static void CommonRouterProcess(napi_env env, napi_callback_info info, const RouterFunc& callback)
{
    size_t requireArgc = 1;
    size_t argc = ARGC_WITH_MODE;
    napi_value argv[ARGC_WITH_MODE] = { 0 };
    napi_value thisVar = nullptr;
    void* data = nullptr;
    napi_get_cb_info(env, info, &argc, argv, &thisVar, &data);
    if (argc < requireArgc) {
        return;
    }
    napi_value uriNApi = nullptr;
    napi_value params = nullptr;
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, argv[0], &valueType);
    if (valueType == napi_object) {
        napi_get_named_property(env, argv[0], "url", &uriNApi);
        napi_typeof(env, uriNApi, &valueType);
        if (valueType != napi_string) {
            return;
        }
        napi_get_named_property(env, argv[0], "params", &params);
    }
    std::string paramsString;
    ParseParams(env, params, paramsString);
    std::string uriString;
    napi_typeof(env, uriNApi, &valueType);
    if (valueType == napi_string) {
        ParseUri(env, uriNApi, uriString);
    }

    uint32_t mode = INVALID;
    napi_typeof(env, argv[1], &valueType);
    if (argc == ARGC_WITH_MODE && valueType == napi_number) {
        napi_get_value_uint32(env, argv[1], &mode);
    }
    callback(uriString, paramsString, mode);
}

static napi_value JSRouterPush(napi_env env, napi_callback_info info)
{
    auto callback = [](const std::string& uri, const std::string& params, uint32_t mode) {
        auto delegate = EngineHelper::GetCurrentDelegateSafely();
        if (!delegate) {
            return;
        }
        if (mode == INVALID) {
            delegate->Push(uri, params);
        } else {
            delegate->PushWithMode(uri, params, mode);
        }
    };
    CommonRouterProcess(env, info, callback);
    return nullptr;
}

static napi_value JSRouterReplace(napi_env env, napi_callback_info info)
{
    auto callback = [](const std::string& uri, const std::string& params, uint32_t mode) {
        auto delegate = EngineHelper::GetCurrentDelegateSafely();
        if (!delegate) {
            return;
        }
        if (mode == INVALID) {
            delegate->Replace(uri, params);
        } else {
            delegate->ReplaceWithMode(uri, params, mode);
        }
    };
    CommonRouterProcess(env, info, callback);
    return nullptr;
}

bool ParseParamWithCallback(napi_env env, std::shared_ptr<RouterAsyncContext> asyncContext, const size_t argc,
    napi_value* argv, napi_value* result)
{
    asyncContext->env = env;
    for (size_t i = 0; i < argc; i++) {
        napi_valuetype valueType = napi_undefined;
        napi_typeof(env, argv[i], &valueType);
        if (i == 0) {
            if (valueType != napi_object) {
                NapiThrow(env, "The type of parameters is incorrect.", ERROR_CODE_PARAM_INVALID);
                return false;
            }
            napi_value uriNApi = nullptr;
            napi_value params = nullptr;
            napi_value recoverable = nullptr;
            napi_get_named_property(env, argv[i], asyncContext->keyForUrl.c_str(), &uriNApi);
            napi_typeof(env, uriNApi, &valueType);
            if (valueType != napi_string) {
                NapiThrow(env, "The type of the url parameter is not string.", ERROR_CODE_PARAM_INVALID);
                return false;
            }
            ParseUri(env, uriNApi, asyncContext->uriString);
            napi_get_named_property(env, argv[i], "params", &params);
            ParseParams(env, params, asyncContext->paramsString);
            napi_get_named_property(env, argv[i], "recoverable", &recoverable);
            ParseRecoverable(env, recoverable, asyncContext->recoverable);
        } else if (valueType == napi_number) {
            napi_get_value_uint32(env, argv[i], &asyncContext->mode);
        } else if (valueType == napi_function) {
            napi_create_reference(env, argv[i], 1, &asyncContext->callbackRef);
        } else {
            NapiThrow(env, "The type of parameters is incorrect.", ERROR_CODE_PARAM_INVALID);
            return false;
        }
    }

    if (asyncContext->callbackRef == nullptr) {
        if (argc > ARGC_WITH_MODE) {
            NapiThrow(env, "The largest number of parameters is 2 in Promise.", ERROR_CODE_PARAM_INVALID);
            return false;
        }
        napi_create_promise(env, &asyncContext->deferred, result);
    }
    return true;
}

void TriggerCallback(std::shared_ptr<RouterAsyncContext> asyncContext)
{
    napi_handle_scope scope = nullptr;
    napi_open_handle_scope(asyncContext->env, &scope);
    if (scope == nullptr) {
        return;
    }

    if (asyncContext->callbackCode == ERROR_CODE_NO_ERROR) {
        napi_value result = nullptr;
        napi_get_undefined(asyncContext->env, &result);
        if (asyncContext->deferred) {
            napi_resolve_deferred(asyncContext->env, asyncContext->deferred, result);
        } else {
            napi_value callback = nullptr;
            napi_get_reference_value(asyncContext->env, asyncContext->callbackRef, &callback);
            napi_value ret;
            napi_call_function(asyncContext->env, nullptr, callback, 1, &result, &ret);
        }
    } else {
        napi_value code = nullptr;
        std::string strCode = std::to_string(asyncContext->callbackCode);
        napi_create_string_utf8(asyncContext->env, strCode.c_str(), strCode.length(), &code);

        napi_value msg = nullptr;
        std::string strMsg = ErrorToMessage(asyncContext->callbackCode) + asyncContext->callbackMsg;
        napi_create_string_utf8(asyncContext->env, strMsg.c_str(), strMsg.length(), &msg);

        napi_value error = nullptr;
        napi_create_error(asyncContext->env, code, msg, &error);
        if (asyncContext->deferred) {
            napi_reject_deferred(asyncContext->env, asyncContext->deferred, error);
        } else {
            napi_value callback = nullptr;
            napi_get_reference_value(asyncContext->env, asyncContext->callbackRef, &callback);
            napi_value ret;
            napi_call_function(asyncContext->env, nullptr, callback, 1, &error, &ret);
        }
    }
    napi_close_handle_scope(asyncContext->env, scope);
}

using ErrorCallback = std::function<void(const std::string&, int32_t)>;
using RouterWithCallbackFunc = std::function<void(std::shared_ptr<RouterAsyncContext>, const ErrorCallback&)>;

static napi_value CommonRouterWithCallbackProcess(
    napi_env env, napi_callback_info info, const RouterWithCallbackFunc& callback, const std::string& keyForUrl)
{
    napi_value result = nullptr;
    napi_get_undefined(env, &result);
    size_t requireArgc = 1;
    size_t argc = ARGC_WITH_MODE_AND_CALLBACK;
    napi_value argv[ARGC_WITH_MODE_AND_CALLBACK] = { 0 };
    napi_value thisVar = nullptr;
    void* data = nullptr;
    napi_get_cb_info(env, info, &argc, argv, &thisVar, &data);
    if (argc < requireArgc) {
        NapiThrow(
            env, "The number of parameters must be greater than or equal to 1.", ERROR_CODE_PARAM_INVALID);
        return result;
    } else if (argc > ARGC_WITH_MODE_AND_CALLBACK) {
        NapiThrow(env, "The largest number of parameters is 3.", ERROR_CODE_PARAM_INVALID);
        return result;
    }

    auto asyncContext = std::make_shared<RouterAsyncContext>();
    asyncContext->keyForUrl = keyForUrl;
    if (!ParseParamWithCallback(env, asyncContext, argc, argv, &result)) {
        return result;
    }

    auto errorCallback = [asyncContext](const std::string& message, int32_t errCode) mutable {
        if (!asyncContext) {
            return;
        }
        asyncContext->callbackCode = errCode;
        asyncContext->callbackMsg = message;
        TriggerCallback(asyncContext);
        asyncContext = nullptr;
    };
    callback(asyncContext, errorCallback);
    return result;
}

static napi_value JSRouterPushWithCallback(napi_env env, napi_callback_info info)
{
    auto callback = [](std::shared_ptr<RouterAsyncContext> context, const ErrorCallback& errorCallback) {
        auto delegate = EngineHelper::GetCurrentDelegateSafely();
        auto defaultDelegate = EngineHelper::GetDefaultDelegate();
        if (!delegate && !defaultDelegate) {
            NapiThrow(context->env, "UI execution context not found.", ERROR_CODE_INTERNAL_ERROR);
            return;
        }
        if (delegate) {
            delegate->PushWithCallback(context->uriString, context->paramsString,
                context->recoverable, errorCallback, context->mode);
        } else {
            defaultDelegate->PushWithCallback(context->uriString, context->paramsString,
                context->recoverable, errorCallback, context->mode);
        }
    };
    return CommonRouterWithCallbackProcess(env, info, callback, "url");
}

static napi_value JSRouterReplaceWithCallback(napi_env env, napi_callback_info info)
{
    auto callback = [](std::shared_ptr<RouterAsyncContext> context, const ErrorCallback& errorCallback) {
        auto delegate = EngineHelper::GetCurrentDelegateSafely();
        auto defaultDelegate = EngineHelper::GetDefaultDelegate();
        if (!delegate && !defaultDelegate) {
            NapiThrow(context->env, "UI execution context not found.", ERROR_CODE_INTERNAL_ERROR);
            return;
        }
        if (delegate) {
            delegate->ReplaceWithCallback(context->uriString, context->paramsString,
                context->recoverable, errorCallback, context->mode);
        } else {
            defaultDelegate->ReplaceWithCallback(context->uriString, context->paramsString,
                context->recoverable, errorCallback, context->mode);
        }
    };
    return CommonRouterWithCallbackProcess(env, info, callback, "url");
}

static napi_value JSPushNamedRoute(napi_env env, napi_callback_info info)
{
    auto callback = [](std::shared_ptr<RouterAsyncContext> context, const ErrorCallback& errorCallback) {
        auto delegate = EngineHelper::GetCurrentDelegateSafely();
        if (!delegate) {
            NapiThrow(context->env, "UI execution context not found.", ERROR_CODE_INTERNAL_ERROR);
            return;
        }
        delegate->PushNamedRoute(context->uriString, context->paramsString,
            context->recoverable, errorCallback, context->mode);
    };
    return CommonRouterWithCallbackProcess(env, info, callback, "name");
}

static napi_value JSReplaceNamedRoute(napi_env env, napi_callback_info info)
{
    auto callback = [](std::shared_ptr<RouterAsyncContext> context, const ErrorCallback& errorCallback) {
        auto delegate = EngineHelper::GetCurrentDelegateSafely();
        if (!delegate) {
            NapiThrow(context->env, "UI execution context not found.", ERROR_CODE_INTERNAL_ERROR);
            return;
        }
        delegate->ReplaceNamedRoute(context->uriString, context->paramsString,
            context->recoverable, errorCallback, context->mode);
    };
    return CommonRouterWithCallbackProcess(env, info, callback, "name");
}

static napi_value JsBackToIndex(napi_env env, napi_callback_info info)
{
    size_t argc = ARGC_WITH_ROUTER_PARAMTER;
    napi_value argv[ARGC_WITH_ROUTER_PARAMTER] = { nullptr };
    napi_value thisVar = nullptr;
    void* data = nullptr;
    napi_get_cb_info(env, info, &argc, argv, &thisVar, &data);

    auto delegate = EngineHelper::GetCurrentDelegateSafely();
    if (!delegate) {
        NapiThrow(env, "UI execution context not found.", ERROR_CODE_INTERNAL_ERROR);
        return nullptr;
    }
    std::string paramsString;
    int32_t routeIndex = 0;
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, argv[0], &valueType);
    if (valueType == napi_number) {
        napi_get_value_int32(env, argv[0], &routeIndex);
    } else {
        TAG_LOGE(AceLogTag::ACE_ROUTER, "Index is not of type number");
        return nullptr;
    }
    napi_typeof(env, argv[1], &valueType);
    if (valueType == napi_object) {
        ParseParams(env, argv[1], paramsString);
    }
    delegate->BackToIndex(routeIndex, paramsString);
    return nullptr;
}

static napi_value JSRouterBack(napi_env env, napi_callback_info info)
{
    size_t argc = ARGC_WITH_ROUTER_PARAMTER;
    napi_value argv[ARGC_WITH_ROUTER_PARAMTER] = { nullptr };
    napi_value thisVar = nullptr;
    void* data = nullptr;
    napi_get_cb_info(env, info, &argc, argv, &thisVar, &data);

    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, argv[0], &valueType);
    if (argc == ARGC_WITH_ROUTER_PARAMTER || valueType == napi_number) {
        return JsBackToIndex(env, info);
    }
    auto delegate = EngineHelper::GetCurrentDelegateSafely();
    if (!delegate) {
        NapiThrow(env, "UI execution context not found.", ERROR_CODE_INTERNAL_ERROR);
        return nullptr;
    }
    std::string uriString = "";
    std::string paramsString = "";
    napi_value uriNApi = nullptr;
    napi_value params = nullptr;
    if (valueType == napi_object) {
        napi_get_named_property(env, argv[0], "url", &uriNApi);
        napi_typeof(env, uriNApi, &valueType);
        if (valueType == napi_undefined) {
            napi_get_named_property(env, argv[0], "path", &uriNApi);
            napi_typeof(env, uriNApi, &valueType);
        }
        if (valueType == napi_string) {
            ParseUri(env, uriNApi, uriString);
        }

        napi_get_named_property(env, argv[0], "params", &params);
        napi_typeof(env, params, &valueType);
        if (valueType == napi_object) {
            ParseParams(env, params, paramsString);
        }
    }
    delegate->Back(uriString, paramsString);
    return nullptr;
}

static napi_value JSRouterClear(napi_env env, napi_callback_info info)
{
    auto delegate = EngineHelper::GetCurrentDelegateSafely();
    if (!delegate) {
        NapiThrow(env, "UI execution context not found.", ERROR_CODE_INTERNAL_ERROR);
        return nullptr;
    }
    delegate->Clear();
    return nullptr;
}

static napi_value JSRouterGetLength(napi_env env, napi_callback_info info)
{
    auto delegate = EngineHelper::GetCurrentDelegateSafely();
    if (!delegate) {
        NapiThrow(env, "UI execution context not found.", ERROR_CODE_INTERNAL_ERROR);
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
    auto delegate = EngineHelper::GetCurrentDelegateSafely();
    if (!delegate) {
        NapiThrow(env, "UI execution context not found.", ERROR_CODE_INTERNAL_ERROR);
        return nullptr;
    }
    delegate->GetState(routeIndex, routeName, routePath);
    size_t routeNameLen = routeName.length();
    size_t routePathLen = routePath.length();

    std::string paramsStr = delegate->GetParams();
    napi_value params = paramsStr.empty() ? nullptr : ParseJSONParams(env, paramsStr);
    napi_value resultArray[RESULT_ARRAY_LENGTH] = { 0 };
    napi_create_int32(env, routeIndex, &resultArray[RESULT_ARRAY_INDEX_INDEX]);
    napi_create_string_utf8(env, routeName.c_str(), routeNameLen, &resultArray[RESULT_ARRAY_NAME_INDEX]);
    napi_create_string_utf8(env, routePath.c_str(), routePathLen, &resultArray[RESULT_ARRAY_PATH_INDEX]);

    napi_value result = nullptr;
    napi_create_object(env, &result);
    napi_set_named_property(env, result, "index", resultArray[RESULT_ARRAY_INDEX_INDEX]);
    napi_set_named_property(env, result, "name", resultArray[RESULT_ARRAY_NAME_INDEX]);
    napi_set_named_property(env, result, "path", resultArray[RESULT_ARRAY_PATH_INDEX]);
    napi_set_named_property(env, result, "params", params);
    return result;
}

static napi_value JSGetStateByIndex(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value argv = nullptr;
    napi_value thisVar = nullptr;
    void* data = nullptr;
    napi_get_cb_info(env, info, &argc, &argv, &thisVar, &data);

    int32_t routeIndex = 0;
    std::string routeName;
    std::string routePath;
    std::string routeParams;
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, argv, &valueType);
    if (valueType == napi_number) {
        napi_get_value_int32(env, argv, &routeIndex);
    }
    auto delegate = EngineHelper::GetCurrentDelegateSafely();
    if (!delegate) {
        NapiThrow(env, "UI execution context not found.", ERROR_CODE_INTERNAL_ERROR);
        return nullptr;
    }

    delegate->GetRouterStateByIndex(routeIndex, routeName, routePath, routeParams);
    if (routeName.empty()) {
        napi_value undefined;
        napi_get_undefined(env, &undefined);
        return undefined;
    }
    size_t routeNameLen = routeName.length();
    size_t routePathLen = routePath.length();

    napi_value resultArray[RESULT_ARRAY_LENGTH] = { 0 };
    napi_create_int32(env, routeIndex, &resultArray[RESULT_ARRAY_INDEX_INDEX]);
    napi_create_string_utf8(env, routeName.c_str(), routeNameLen, &resultArray[RESULT_ARRAY_NAME_INDEX]);
    napi_create_string_utf8(env, routePath.c_str(), routePathLen, &resultArray[RESULT_ARRAY_PATH_INDEX]);
    
    napi_value parsedParams = nullptr;
    if (!routeParams.empty()) {
        parsedParams = ParseJSONParams(env, routeParams);
    } else {
        napi_create_object(env, &parsedParams);
    }

    napi_value result = nullptr;
    napi_create_object(env, &result);
    napi_set_named_property(env, result, "index", resultArray[RESULT_ARRAY_INDEX_INDEX]);
    napi_set_named_property(env, result, "name", resultArray[RESULT_ARRAY_NAME_INDEX]);
    napi_set_named_property(env, result, "path", resultArray[RESULT_ARRAY_PATH_INDEX]);
    napi_set_named_property(env, result, "params", parsedParams);
    return result;
}

static napi_value JSGetStateByUrl(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value argv = nullptr;
    napi_value thisVar = nullptr;
    void* data = nullptr;
    napi_get_cb_info(env, info, &argc, &argv, &thisVar, &data);

    auto delegate = EngineHelper::GetCurrentDelegateSafely();
    if (!delegate) {
        NapiThrow(env, "UI execution context not found.", ERROR_CODE_INTERNAL_ERROR);
        return nullptr;
    }
    std::string uriString;
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, argv, &valueType);
    if (valueType == napi_string) {
        ParseUri(env, argv, uriString);
    }
    std::vector<Framework::StateInfo> stateArray;
    delegate->GetRouterStateByUrl(uriString, stateArray);

    napi_value result = nullptr;
    napi_create_array(env, &result);
    int32_t index = 0;
    for (const auto& info : stateArray) {
        napi_value pageObj = nullptr;
        napi_create_object(env, &pageObj);
        int32_t routeIndex = info.index;
        std::string routeName = info.name;
        std::string routePath = info.path;
        std::string routeParams = info.params;
        napi_value indexValue = nullptr;
        napi_value nameValue = nullptr;
        napi_value pathValue = nullptr;

        napi_create_int32(env, routeIndex, &indexValue);
        napi_create_string_utf8(env, routeName.c_str(), NAPI_AUTO_LENGTH, &nameValue);
        napi_create_string_utf8(env, routePath.c_str(), NAPI_AUTO_LENGTH, &pathValue);
        napi_value parsedParams = nullptr;
        if (!routeParams.empty()) {
            parsedParams = ParseJSONParams(env, routeParams);
        } else {
            napi_create_object(env, &parsedParams);
        }
        napi_set_named_property(env, pageObj, "index", indexValue);
        napi_set_named_property(env, pageObj, "name", nameValue);
        napi_set_named_property(env, pageObj, "path", pathValue);
        napi_set_named_property(env, pageObj, "params", parsedParams);
        napi_set_element(env, result, index++, pageObj);
    }
    return result;
}

void CallBackToJSTread(std::shared_ptr<RouterAsyncContext> context)
{
    auto container = AceEngine::Get().GetContainer(context->instanceId);
    if (!container) {
        return;
    }

    auto taskExecutor = container->GetTaskExecutor();
    if (!taskExecutor) {
        return;
    }
    taskExecutor->PostTask(
        [context]() {
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
        },
        TaskExecutor::TaskType::JS, "ArkUIRouterAlertCallback");
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
        NapiThrow(env, "The type of the parameter is not object.", ERROR_CODE_PARAM_INVALID);
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
        NapiThrow(env, "The type of the message is not string.", ERROR_CODE_PARAM_INVALID);
        return nullptr;
    }

    auto delegate = EngineHelper::GetCurrentDelegateSafely();
    if (!delegate) {
        NapiThrow(env, "UI execution context not found.", ERROR_CODE_INTERNAL_ERROR);
        return nullptr;
    }

    auto context = std::make_shared<RouterAsyncContext>();
    context->env = env;
    context->instanceId = Container::CurrentIdSafely();
    napi_value successFunc = nullptr;
    napi_value failFunc = nullptr;
    napi_value completeFunc = nullptr;
    napi_get_named_property(env, argv, "success", &successFunc);
    napi_get_named_property(env, argv, "cancel", &failFunc);
    napi_get_named_property(env, argv, "complete", &completeFunc);
    bool isNeedCallBack = false;
    napi_typeof(env, successFunc, &valueType);
    if (valueType == napi_function) {
        napi_create_reference(env, successFunc, 1, &context->callbackSuccess);
        isNeedCallBack = true;
    }

    napi_typeof(env, failFunc, &valueType);
    if (valueType == napi_function) {
        napi_create_reference(env, failFunc, 1, &context->callbackFail);
        isNeedCallBack = true;
    }
    napi_typeof(env, completeFunc, &valueType);
    if (valueType == napi_function) {
        napi_create_reference(env, completeFunc, 1, &context->callbackComplete);
        isNeedCallBack = true;
    }

    auto dilogCallback = [context, isNeedCallBack](int32_t callbackType) mutable {
        if (context && isNeedCallBack) {
            if (Framework::AlertState(callbackType) == Framework::AlertState::RECOVERY) {
                context = nullptr;
                return;
            }
            context->callbackType = callbackType;
            CallBackToJSTread(context);
        }
    };
    delegate->EnableAlertBeforeBackPage(messageChar.get(), std::move(dilogCallback));

    return nullptr;
}

static napi_value JSRouterDisableAlertBeforeBackPage(napi_env env, napi_callback_info info)
{
    auto delegate = EngineHelper::GetCurrentDelegateSafely();
    if (delegate) {
        delegate->DisableAlertBeforeBackPage();
    } else {
        NapiThrow(env, "UI execution context not found.", ERROR_CODE_INTERNAL_ERROR);
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
    auto delegate = EngineHelper::GetCurrentDelegateSafely();
    if (!delegate) {
        NapiThrow(env, "UI execution context not found.", ERROR_CODE_INTERNAL_ERROR);
        return nullptr;
    }
    std::string paramsStr = delegate->GetParams();
    if (paramsStr.empty()) {
        return nullptr;
    }
    napi_value result = ParseJSONParams(env, paramsStr);
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
        DECLARE_NAPI_FUNCTION("getStateByIndex", JSGetStateByIndex),
        DECLARE_NAPI_FUNCTION("getStateByUrl", JSGetStateByUrl),
        DECLARE_NAPI_FUNCTION("enableAlertBeforeBackPage", JSRouterEnableAlertBeforeBackPage),
        DECLARE_NAPI_FUNCTION("enableBackPageAlert", JSRouterEnableAlertBeforeBackPage),
        DECLARE_NAPI_FUNCTION("showAlertBeforeBackPage", JSRouterEnableAlertBeforeBackPage),
        DECLARE_NAPI_FUNCTION("disableAlertBeforeBackPage", JSRouterDisableAlertBeforeBackPage),
        DECLARE_NAPI_FUNCTION("hideAlertBeforeBackPage", JSRouterDisableAlertBeforeBackPage),
        DECLARE_NAPI_FUNCTION("getParams", JSRouterGetParams),
        DECLARE_NAPI_FUNCTION("pushNamedRoute", JSPushNamedRoute),
        DECLARE_NAPI_FUNCTION("replaceNamedRoute", JSReplaceNamedRoute),
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
