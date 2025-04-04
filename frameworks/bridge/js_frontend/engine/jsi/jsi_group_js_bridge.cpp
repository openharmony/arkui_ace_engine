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

#include "frameworks/bridge/js_frontend/engine/jsi/jsi_group_js_bridge.h"

#include "base/log/event_report.h"
#include "frameworks/bridge/js_frontend/engine/jsi/jsi_engine.h"
#if defined(PREVIEW)
#include "frameworks/bridge/declarative_frontend/engine/jsi/jsi_declarative_engine.h"
#include "adapter/preview/entrance/ace_container.h"
#include "core/common/ace_engine.h"
#endif

namespace OHOS::Ace::Framework {
namespace {

const int32_t PLUGIN_REQUEST_MIN_ARGC_NUM = 4;
const int32_t PLUGIN_REQUEST_ARG_RESOLVE_INDEX = 0;
const int32_t PLUGIN_REQUEST_ARG_REJECT_INDEX = 1;
const int32_t PLUGIN_REQUEST_ARG_GROUP_NAME_INDEX = 2;
const int32_t PLUGIN_REQUEST_ARG_FUNCTION_NAME_INDEX = 3;
const int32_t PLUGIN_REQUEST_ARG_APP_PARAMS_INDEX = 4;

const int32_t PLUGIN_REQUEST_MIN_ARGC_NUM_SYNC = 2;
const int32_t PLUGIN_REQUEST_ARG_GROUP_NAME_INDEX_SYNC = 0;
const int32_t PLUGIN_REQUEST_ARG_FUNCTION_NAME_INDEX_SYNC = 1;
const int32_t PLUGIN_REQUEST_ARG_APP_PARAMS_INDEX_SYNC = 2;

} // namespace

int32_t JsiGroupJsBridge::InitializeGroupJsBridge(const shared_ptr<JsRuntime>& runtime)
{
    if (!runtime) {
        LOGE("group module init, context is null");
        EventReport::SendAPIChannelException(APIChannelExcepType::JS_BRIDGE_INIT_ERR);
        return JS_CALL_FAIL;
    }
    runtime_ = runtime;

    if (LoadJsBridgeFunction() != JS_CALL_SUCCESS) {
        LOGE("group module init, load bridge function failed!");
        EventReport::SendAPIChannelException(APIChannelExcepType::JS_BRIDGE_INIT_ERR);
        return JS_CALL_FAIL;
    }

    eventCallBackFuncs_.clear();
    moduleCallBackFuncs_.clear();
    pendingCallbackId_ = 1;

    return JS_CALL_SUCCESS;
}

int32_t JsiGroupJsBridge::LoadJsBridgeFunction()
{
    shared_ptr<JsValue> group = runtime_->NewObject();
    bool succ = group->SetProperty(runtime_, "sendGroupMessage", runtime_->NewFunction(ProcessJsRequest));
    if (!succ) {
        LOGE("bridge function, set sendGroupMessage sending function mapping failed!");
        EventReport::SendAPIChannelException(APIChannelExcepType::SET_FUNCTION_ERR);
        return JS_CALL_FAIL;
    }
    succ = group->SetProperty(runtime_, "sendGroupMessageSync", runtime_->NewFunction(ProcessJsRequestSync));
    if (!succ) {
        LOGE("bridge function, set sendGroupMessageSync sending function mapping failed!");
        EventReport::SendAPIChannelException(APIChannelExcepType::SET_FUNCTION_ERR);
        return JS_CALL_FAIL;
    }
    succ = runtime_->GetGlobal()->SetProperty(runtime_, "group", group);
    if (!succ) {
        LOGE("bridge function, set root node failed!");
        EventReport::SendAPIChannelException(APIChannelExcepType::SET_FUNCTION_ERR);
        return JS_CALL_FAIL;
    }
    return JS_CALL_SUCCESS;
}
#if defined(PREVIEW)
shared_ptr<JsValue> JsiGroupJsBridge::ProcessJsRequest(const shared_ptr<JsRuntime>& runtime,
    const shared_ptr<JsValue>& thisObj, const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
{
    ACE_SCOPED_TRACE("ProcessJsRequest");
    JsiEngineInstance* instance = nullptr;
    JsiDeclarativeEngineInstance* declarativeInstance = nullptr;
    RefPtr<JsiGroupJsBridge> groupJsBridge;
    auto container = AceType::DynamicCast<OHOS::Ace::Platform::AceContainer>(AceEngine::Get().GetContainer(0));
    if (!container) {
        LOGE("ProcessJsRequest container is null!");
        return runtime->NewUndefined();
    }
    auto type = container->GetType();
    if (type == FrontendType::JS) {
        instance = static_cast<JsiEngineInstance*>(runtime->GetEmbedderData());
        if (instance == nullptr) {
            LOGE("invalid args, failed to get JsiEngineInstance from the runtime");
            return runtime->NewUndefined();
        }
        groupJsBridge = AceType::DynamicCast<JsiGroupJsBridge>(instance->GetDelegate()->GetGroupJsBridge());
    } else if (type == FrontendType::DECLARATIVE_JS) {
        declarativeInstance = static_cast<JsiDeclarativeEngineInstance*>(runtime->GetEmbedderData());
        if (declarativeInstance == nullptr) {
            LOGE("invalid args, failed to get JsiDeclarativeEngineInstance from the runtime");
            return runtime->NewUndefined();
        }
        groupJsBridge =
            AceType::DynamicCast<JsiGroupJsBridge>(declarativeInstance->GetDelegate()->GetGroupJsBridge());
    } else {
        LOGE("Frontend type not supported");
        return runtime->NewUndefined();
    }

    if (groupJsBridge == nullptr) {
        LOGE("invalid args, failed to get GroupJsBridge from the JSContext");
        return runtime->NewUndefined();
    }

    // Should have at least 4 parameters
    if (argv.size() < PLUGIN_REQUEST_MIN_ARGC_NUM) {
        LOGE("invalid args number:%{public}d", argc);
        return runtime->NewUndefined();
    }
    int32_t callbackId = groupJsBridge->GetPendingCallbackIdAndIncrement();
    if (!groupJsBridge->SetModuleGroupCallbackFuncs(argv, PLUGIN_REQUEST_ARG_RESOLVE_INDEX,
        PLUGIN_REQUEST_ARG_REJECT_INDEX, callbackId)) {
        LOGE("set module callback function failed!");
        return runtime->NewUndefined();
    }
    std::string groupName  = argv[PLUGIN_REQUEST_ARG_GROUP_NAME_INDEX]->ToString(runtime);
    if (groupName.empty()) {
        LOGE("invalid paras, groupName:%{private}s", groupName.c_str());
        return runtime->NewUndefined();
    }
    LOGI("send message, groupName: %{private}s, callbackId: %{private}d", groupName.c_str(), callbackId);
    std::string strFunctionName = argv[PLUGIN_REQUEST_ARG_FUNCTION_NAME_INDEX]->ToString(runtime);
    // In the preview scenario, only the fetch interface is available. If other APIs need to be supported in the future,
    // adaptation is required.
    if (strFunctionName != "fetch") {
        LOGE("unsupported function %{private}s", strFunctionName.c_str());
        return runtime->NewUndefined();
    }
    OHOS::Ace::RequestData requestData;
    ParseJsDataResult parseJsResult = groupJsBridge->ParseRequestData(argc, argv, requestData, callbackId);
    if (parseJsResult != ParseJsDataResult::PARSE_JS_SUCCESS) {
        ProcessParseJsError(parseJsResult, runtime, callbackId);
        return runtime->NewNull();
    }
    if ((type == FrontendType::JS && !instance->CallCurlFunction(requestData, callbackId)) ||
        (type == FrontendType::DECLARATIVE_JS && !declarativeInstance->CallCurlFunction(requestData, callbackId))) {
        LOGE("CallPlatformFunction fail");
        groupJsBridge->TriggerModulePluginGetErrorCallback(callbackId, PLUGIN_REQUEST_FAIL, "send message failed");
        return runtime->NewNull();
    }
    return runtime->NewNull();
}
#else
// function callback for groupObj's function: sendGroupMessage
shared_ptr<JsValue> JsiGroupJsBridge::ProcessJsRequest(const shared_ptr<JsRuntime>& runtime,
    const shared_ptr<JsValue>& thisObj, const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
{
    shared_ptr<JsValue> res = runtime->NewUndefined();
    auto engine = static_cast<JsiEngineInstance*>(runtime->GetEmbedderData());
    if (engine == nullptr) {
        LOGE("send message para check, fail to get engine");
        return res;
    }
    auto delegate = engine->GetFrontendDelegate();
    if (!delegate) {
        LOGE("send message para check, fail to get front-end delegate");
        return res;
    }

    auto groupJsBridge = AceType::DynamicCast<JsiGroupJsBridge>(delegate->GetGroupJsBridge());
    if (!groupJsBridge) {
        LOGE("send message para check, fail to get group-js-bridge");
        return res;
    }

    // Should have at least 4 parameters
    if (argv.size() < PLUGIN_REQUEST_MIN_ARGC_NUM) {
        LOGE("send message para check, invalid args number:%{public}u", (uint32_t)argv.size());
        return res;
    }

    std::string strGroupName(argv[PLUGIN_REQUEST_ARG_GROUP_NAME_INDEX]->ToString(runtime));
    std::string strFunctionName(argv[PLUGIN_REQUEST_ARG_FUNCTION_NAME_INDEX]->ToString(runtime));
    if (strGroupName.empty()) {
        LOGE("send message para check, group or function name is null");
        return res;
    }
    int32_t callbackId = groupJsBridge->GetPendingCallbackIdAndIncrement();
    // the third and fourth parameters are resolve and reject callback function
    if (!groupJsBridge->SetModuleGroupCallbackFuncs(argv,
        PLUGIN_REQUEST_ARG_RESOLVE_INDEX, PLUGIN_REQUEST_ARG_REJECT_INDEX, callbackId)) {
        LOGE("send message, set module callback function failed!");
        return res;
    }

    if (strGroupName.empty()) {
        groupJsBridge->TriggerModulePluginGetErrorCallback(
            callbackId, PLUGIN_REQUEST_FAIL, "plugin name can't be null");
        LOGE("plugin name is null");
        return res;
    }

    LOGI("send message, groupName:%{private}s functionName:%{private}s callbackId:%{private}d", strGroupName.c_str(),
        strFunctionName.c_str(), callbackId);

    std::vector<CodecData> arguments;
    ParseJsDataResult parseJsResult =
        groupJsBridge->ParseJsPara(runtime, argv, PLUGIN_REQUEST_ARG_APP_PARAMS_INDEX, callbackId, arguments);
    if (parseJsResult != ParseJsDataResult::PARSE_JS_SUCCESS) {
        ProcessParseJsError(parseJsResult, runtime, callbackId);
        return res;
    }

    FunctionCall functionCall(strFunctionName, arguments);
    StandardFunctionCodec codec;
    std::vector<uint8_t> encodeBuf;
    if (!codec.EncodeFunctionCall(functionCall, encodeBuf)) {
        groupJsBridge->TriggerModulePluginGetErrorCallback(
            callbackId, PLUGIN_REQUEST_FAIL, "encode request message failed");
        return res;
    }

    // CallPlatformFunction
    auto dispatcher = engine->GetJsMessageDispatcher().Upgrade();
    if (dispatcher) {
        dispatcher->Dispatch(strGroupName, std::move(encodeBuf), callbackId);
    } else {
        LOGW("Dispatcher Upgrade fail when dispatch request message to platform");
        groupJsBridge->TriggerModulePluginGetErrorCallback(callbackId, PLUGIN_REQUEST_FAIL, "send message failed");
    }
    return res;
}
#endif
// function callback for groupObj's function: sendGroupMessageSync
shared_ptr<JsValue> JsiGroupJsBridge::ProcessJsRequestSync(const shared_ptr<JsRuntime>& runtime,
    const shared_ptr<JsValue>& thisObj, const std::vector<shared_ptr<JsValue>>& argv, int32_t argc)
{
    shared_ptr<JsValue> res = runtime->NewUndefined();
    auto engine = static_cast<JsiEngineInstance*>(runtime->GetEmbedderData());
    if (engine == nullptr) {
        LOGE("send message para check, fail to get engine");
        return res;
    }
    auto delegate = engine->GetFrontendDelegate();
    if (!delegate) {
        LOGE("send message para check, fail to get front-end delegate");
        return res;
    }

    auto groupJsBridge = AceType::DynamicCast<JsiGroupJsBridge>(delegate->GetGroupJsBridge());
    if (!groupJsBridge) {
        LOGE("send message para check, fail to get group-js-bridge");
        return res;
    }

    // Should have at least 2 parameters
    if (argv.size() < PLUGIN_REQUEST_MIN_ARGC_NUM_SYNC) {
        LOGE("send message para check, invalid args number:%{public}u", (uint32_t)argv.size());
        return res;
    }

    std::string strGroupName(argv[PLUGIN_REQUEST_ARG_GROUP_NAME_INDEX_SYNC]->ToString(runtime));
    std::string strFunctionName(argv[PLUGIN_REQUEST_ARG_FUNCTION_NAME_INDEX_SYNC]->ToString(runtime));
    if (strGroupName.empty()) {
        LOGE("send message para check, group or function name is null");
        return res;
    }

    if (strGroupName.empty()) {
        LOGE("plugin name is null");
        return res;
    }

    LOGI("send message, groupName:%{private}s functionName:%{private}s", strGroupName.c_str(), strFunctionName.c_str());

    std::vector<CodecData> arguments;
    ParseJsDataResult parseJsResult =
        groupJsBridge->ParseJsPara(runtime, argv, PLUGIN_REQUEST_ARG_APP_PARAMS_INDEX_SYNC, 0, arguments);
    if (parseJsResult != ParseJsDataResult::PARSE_JS_SUCCESS) {
        LOGE("encode arguments fail");
        return res;
    }

    FunctionCall functionCall(strFunctionName, arguments);
    StandardFunctionCodec codec;
    std::vector<uint8_t> encodeBuf;
    if (!codec.EncodeFunctionCall(functionCall, encodeBuf)) {
        LOGE("encode request message failed");
        return res;
    }

    // CallPlatformFunction
    auto dispatcher = engine->GetJsMessageDispatcher().Upgrade();

    uint8_t* resData = nullptr;
    int64_t position = 0;
    if (dispatcher) {
        dispatcher->DispatchSync(strGroupName, std::move(encodeBuf), &resData, position);
    } else {
        LOGW("Dispatcher Upgrade fail when dispatch request message to platform");
        return res;
    }
    std::vector<uint8_t> messageData = std::vector<uint8_t>(resData, resData + position);

    shared_ptr<JsValue> callBackResult;
    CodecData codecResult;
    if (codec.DecodePlatformMessage(messageData, codecResult)) {
        std::string resultString = codecResult.GetStringValue();
        LOGI("sync resultString = %{private}s", resultString.c_str());
        if (resultString.empty()) {
            callBackResult = runtime->NewNull();
        } else {
            callBackResult = runtime->NewString(resultString);
        }
    }
    return callBackResult;
}

bool JsiGroupJsBridge::SetEventGroupCallBackFuncs(const shared_ptr<JsRuntime>& runtime,
    const shared_ptr<JsValue>& localEventCallbackFunc, int32_t callbackId, int32_t requestId)
{
    if (localEventCallbackFunc->IsNull(runtime) || !localEventCallbackFunc->IsFunction(runtime)) {
        LOGE("callback function is invalid!");
        return false;
    }

    LOGI("record event callback, requestId:%{private}d, callbackId:%{private}d", requestId, callbackId);
    auto result = eventCallBackFuncs_.try_emplace(callbackId, localEventCallbackFunc);
    if (!result.second) {
        result.first->second = localEventCallbackFunc;
    }
    AddRequestIdCallbackIdRelation(callbackId, requestId);
    return true;
}

void JsiGroupJsBridge::RemoveEventGroupCallBackFuncs(int32_t callbackId)
{
    LOGI("remove event callback, callbackId:%{private}d", callbackId);
    auto itFunc = eventCallBackFuncs_.find(callbackId);
    if (itFunc != eventCallBackFuncs_.end()) {
        eventCallBackFuncs_.erase(callbackId);
    }
}

void JsiGroupJsBridge::AddRequestIdCallbackIdRelation(int32_t eventId, int32_t requestId)
{
    auto result = requestIdCallbackIdMap_.try_emplace(requestId, eventId);
    if (!result.second) {
        result.first->second = eventId;
    }
}

void JsiGroupJsBridge::RemoveRequestIdCallbackIdRelation(int32_t requestId, bool removeEventCallback)
{
    auto eventId = requestIdCallbackIdMap_.find(requestId);
    if (eventId != requestIdCallbackIdMap_.end()) {
        if (removeEventCallback) {
            RemoveEventGroupCallBackFuncs(eventId->second);
        }
        requestIdCallbackIdMap_.erase(requestId);
    }
}

void JsiGroupJsBridge::ProcessParseJsError(
    ParseJsDataResult errorType, const shared_ptr<JsRuntime>& runtime, int32_t callbackId)
{
    auto engine = static_cast<JsiEngineInstance*>(runtime->GetEmbedderData());
    if (engine == nullptr) {
        LOGE("Process parse js error check, fail to get engine");
        return;
    }
    // PluginErrorCallback
    auto dispatcher = engine->GetJsMessageDispatcher().Upgrade();
    if (!dispatcher) {
        LOGW("Dispatcher Upgrade fail at ProcessParseJsError");
        return;
    }
    std::string errMessage;
    switch (errorType) {
        case ParseJsDataResult::PARSE_JS_ERR_UNSUPPORTED_TYPE:
            errMessage = "unsupported js parameter types";
            dispatcher->DispatchPluginError(callbackId,
                static_cast<int32_t>(ParseJsDataResult::PARSE_JS_ERR_UNSUPPORTED_TYPE), std::move(errMessage));
            break;
        case ParseJsDataResult::PARSE_JS_ERR_TOO_MANY_PARAM:
            errMessage = "the number of parameters exceeds 255";
            dispatcher->DispatchPluginError(callbackId,
                static_cast<int32_t>(ParseJsDataResult::PARSE_JS_ERR_TOO_MANY_PARAM), std::move(errMessage));
            break;
        default:
            break;
    }
}

bool JsiGroupJsBridge::SetModuleGroupCallbackFuncs(const std::vector<shared_ptr<JsValue>>& argv,
    int32_t resolveCallbackIndex, int32_t rejectCallbackIndex, int32_t callbackId)
{
    if (argv[resolveCallbackIndex]->IsNull(runtime_) || !argv[resolveCallbackIndex]->IsFunction(runtime_) ||
        argv[rejectCallbackIndex]->IsNull(runtime_) || !argv[rejectCallbackIndex]->IsFunction(runtime_)) {
        LOGE("resolve or reject callback function is invalid");
        return false;
    }

    PromiseCallback promiseCallJsFunc;

    promiseCallJsFunc.resolveCallback = argv[resolveCallbackIndex];
    promiseCallJsFunc.rejectCallback = argv[rejectCallbackIndex];

    auto result = moduleCallBackFuncs_.try_emplace(callbackId, promiseCallJsFunc);
    if (!result.second) {
        LOGE("module callback function has been existed!");
        return false;
    }
    return true;
}

std::string JsiGroupJsBridge::SerializationObjectToString(
    const shared_ptr<JsRuntime>& runtime, const shared_ptr<JsValue>& val)
{
    shared_ptr<JsValue> global = runtime->GetGlobal();
    if (!global->IsObject(runtime)) {
        LOGE("SerializationObjectToString error: fail to get Global Object");
        return "";
    }
    shared_ptr<JsValue> json = global->GetProperty(runtime, "JSON");
    if (!json->IsObject(runtime)) {
        LOGE("SerializationObjectToString error: global has no attribute JsON");
        return "";
    }
    shared_ptr<JsValue> jsFunc = json->GetProperty(runtime, "stringify");
    if (!jsFunc->IsFunction(runtime)) {
        LOGE("SerializationObjectToString error: JSON has no attribute stringify");
        return "";
    }
    shared_ptr<JsValue> strValue = jsFunc->Call(runtime, runtime->NewUndefined(), { val }, 1);
    if (strValue->IsUndefined(runtime)) {
        LOGE("SerializationObjectToString error: js call error.");
        return "";
    }
    return strValue->ToString(runtime);
}

ParseJsDataResult JsiGroupJsBridge::ParseJsPara(const shared_ptr<JsRuntime>& runtime,
    const std::vector<shared_ptr<JsValue>>& argv, int32_t beginIndex, int32_t requestId,
    std::vector<CodecData>& arguments)
{
    int32_t argc = (int32_t)argv.size();
    if (argc < beginIndex) { // no others params
        return ParseJsDataResult::PARSE_JS_SUCCESS;
    }
    for (int32_t i = beginIndex; i < argc; i++) {
        shared_ptr<JsValue> val = argv[i];
        if (val->IsString(runtime)) {
            CodecData arg(val->ToString(runtime));
            arguments.push_back(arg);
        } else if (val->IsNumber(runtime)) {
            if (val->WithinInt32(runtime)) {
                int32_t valInt = val->ToInt32(runtime);
                CodecData arg(valInt);
                arguments.push_back(arg);
            } else {
                double valDouble = val->ToDouble(runtime);
                CodecData arg(valDouble);
                arguments.push_back(arg);
            }
        } else if (val->IsBoolean(runtime)) {
            bool valBool = val->ToBoolean(runtime);
            CodecData arg(valBool);
            arguments.push_back(arg);
        } else if (val->IsNull(runtime)) {
            CodecData argNull;
            arguments.push_back(argNull);
        } else if (val->IsFunction(runtime)) {
            int32_t functionId = GetPendingCallbackIdAndIncrement();
            CodecData arg(functionId, BufferDataType::TYPE_FUNCTION);
            arguments.push_back(arg);
            SetEventGroupCallBackFuncs(runtime, val, functionId, requestId);
        } else if (val->IsArray(runtime) || val->IsObject(runtime)) {
            std::string objStr = SerializationObjectToString(runtime, val);
            CodecData arg(objStr);
            arguments.push_back(arg);
        } else if (val->IsUndefined(runtime)) {
        } else {
            LOGE("Process callNative para type: unsupported type");
            return ParseJsDataResult::PARSE_JS_ERR_UNSUPPORTED_TYPE;
        }
    }
    return ParseJsDataResult::PARSE_JS_SUCCESS;
}

void JsiGroupJsBridge::TriggerModuleJsCallback(int32_t callbackId, int32_t code, std::vector<uint8_t>&& messageData)
{
    shared_ptr<JsValue> callBackResult;
    CodecData codecResult;
    StandardFunctionCodec codec;
    if (codec.DecodePlatformMessage(messageData, codecResult)) {
        std::string resultString = codecResult.GetStringValue();
        if (resultString.empty()) {
            callBackResult = runtime_->NewNull();
        } else {
            callBackResult = runtime_->NewString(resultString);
        }
    } else {
        LOGE("trigger JS resolve callback function error, decode message fail, callbackId:%{private}d", callbackId);
        callBackResult = runtime_->NewString("invalid response data");
    }
    CallModuleJsCallback(callbackId, code, callBackResult);

    messageData.clear();
}

void JsiGroupJsBridge::CallModuleJsCallback(int32_t callbackId, int32_t code, const shared_ptr<JsValue>& callBackResult)
{
    RemoveRequestIdCallbackIdRelation(callbackId, code != PLUGIN_REQUEST_SUCCESS);

    shared_ptr<JsValue> global = runtime_->GetGlobal();

    auto itFunc = moduleCallBackFuncs_.find(callbackId);
    if (itFunc != moduleCallBackFuncs_.end()) {
        shared_ptr<JsValue> jsFunc =
            (code == PLUGIN_REQUEST_SUCCESS ? itFunc->second.resolveCallback : itFunc->second.rejectCallback);
        if (jsFunc->IsNull(runtime_) || !jsFunc->IsFunction(runtime_)) {
            LOGE("trigger JS result function error, it is not a function, callbackId:%{private}d", callbackId);
            return;
        }
        std::vector<shared_ptr<JsValue>> argv = { callBackResult };

        // Pass only 1 parameter, call promise resolve call back.
        jsFunc->Call(runtime_, global, argv, 1);
        itFunc->second.rejectCallback = runtime_->NewUndefined();
        itFunc->second.resolveCallback = runtime_->NewUndefined();
        moduleCallBackFuncs_.erase(itFunc);
    } else {
        LOGE("trigger JS result function is not exists, callbackId:%{private}d, code:%{private}d", callbackId, code);
    }
}

void JsiGroupJsBridge::TriggerModulePluginGetErrorCallback(
    int32_t callbackId, int32_t errorCode, std::string&& errorMessage)
{
    RemoveRequestIdCallbackIdRelation(callbackId, true);
    shared_ptr<JsValue> global = runtime_->GetGlobal();

    CodecData codecResult;
    auto itFunc = moduleCallBackFuncs_.find(callbackId);
    if (itFunc != moduleCallBackFuncs_.end()) {
        shared_ptr<JsValue> jsFunc = itFunc->second.rejectCallback;
        if (jsFunc->IsNull(runtime_) || !jsFunc->IsFunction(runtime_)) {
            LOGE("trigger Js reject callback function error, reject is not a function, callbackId:%{private}d",
                callbackId);
            return;
        }
        auto resultJson = JsonUtil::Create(true);
        resultJson->Put(std::string("code").c_str(), errorCode);
        resultJson->Put(std::string("data").c_str(), errorMessage.c_str());
        shared_ptr<JsValue> emptyReplyCallback = runtime_-> NewString(resultJson->ToString().c_str());
        std::vector<shared_ptr<JsValue>> argv;
        argv.push_back(emptyReplyCallback);
        int32_t len = 1;
        // Pass only 1 parameter, call promise reject call back for error get in plugin.
        shared_ptr<JsValue> res = jsFunc->Call(runtime_, global, argv, len);
        if (!res || res->IsUndefined(runtime_)) {
            LOGW("trigger Js reject callback function fail, callbackId:%{private}d", callbackId);
        } else {
            LOGI("trigger Js reject callback function success, callbackId:%{private}d", callbackId);
        }
        moduleCallBackFuncs_.erase(itFunc);
    } else {
        LOGE("trigger Js reject callback function is not exists, callbackId:%{private}d", callbackId);
    }
}

void JsiGroupJsBridge::CallEventJsCallback(int32_t callbackId, std::vector<uint8_t>&& eventData)
{
    shared_ptr<JsValue> global = runtime_->GetGlobal();

    shared_ptr<JsValue> callBackEvent;
    CodecData codecEvent;
    StandardFunctionCodec codec;
    if (codec.DecodePlatformMessage(eventData, codecEvent)) {
        std::string eventString = codecEvent.GetStringValue();
        if (eventString.empty()) {
            callBackEvent = runtime_->NewNull();
        } else {
            callBackEvent = runtime_->NewString(eventString);
        }
    } else {
        LOGE("trigger Js callback function error, decode message fail, callbackId:%{private}d", callbackId);
        return;
    }

    auto itFunc = eventCallBackFuncs_.find(callbackId);
    if (itFunc != eventCallBackFuncs_.end()) {
        shared_ptr<JsValue> jsFunc = itFunc->second;
        if (!jsFunc->IsFunction(runtime_) || jsFunc->IsNull(runtime_)) {
            LOGE("trigger Js callback function error, callback is not a function, callbackId:%{private}d", callbackId);
            return;
        }

        // Pass only 1 parameter
        int32_t len = 1;
        std::vector<shared_ptr<JsValue>> argv = { callBackEvent };
        jsFunc->Call(runtime_, global, argv, len);
    } else {
        LOGE("trigger Js callback function error, it is not exists, callbackId:%{private}d", callbackId);
    }
    eventData.clear();
}

void JsiGroupJsBridge::TriggerEventJsCallback(int32_t callbackId, int32_t code, std::vector<uint8_t>&& eventData)
{
    if (code == PLUGIN_CALLBACK_DESTROY) {
        RemoveEventGroupCallBackFuncs(callbackId);
    } else {
        CallEventJsCallback(callbackId, std::move(eventData));
    }
}

void JsiGroupJsBridge::LoadPluginJsCode(std::string&& jsCode)
{
    LOGE("Do not support load JsCode in ark vm.");
}

void JsiGroupJsBridge::LoadPluginJsByteCode(std::vector<uint8_t>&& jsCode, std::vector<int32_t>&& jsCodeLen)
{
    if (!runtime_) {
        return;
    }

    int32_t countLen = 0;
    for (auto len : jsCodeLen) {
        runtime_->EvaluateJsCode(jsCode.data() + countLen, len);
        countLen += len;
    }
}

void JsiGroupJsBridge::Destroy()
{
    eventCallBackFuncs_.clear();
    moduleCallBackFuncs_.clear();
    runtime_.reset();
}
#if defined(PREVIEW)
void JsiGroupJsBridge::TriggerModuleJsCallbackPreview(int32_t callbackId, int32_t code, ResponseData responseData)
{
    shared_ptr<JsValue> callBackResult = runtime_->NewNull();
    std::string resultString = responseData.GetResultString()->ToString();
    code = responseData.GetActionCode();
    if (!resultString.empty()) {
        callBackResult = runtime_->NewString(resultString);
    } else {
        code = PLUGIN_REQUEST_FAIL;
        callBackResult = runtime_->NewString(std::string("{\"code\":").append(std::to_string(code)).append(",")
            .append("\"data\":\"invalid response data\"}"));
    }
    CallModuleJsCallback(callbackId, code, callBackResult);
}

const LinearMapNode<void (*)(const char*, OHOS::Ace::RequestData&)> JsiGroupJsBridge::fetchRequestDataMap1[] = {
    { "data",
        [](const char* valStr, OHOS::Ace::RequestData& requestData) { requestData.SetData(valStr); } },
    { "method",
        [](const char* valStr, OHOS::Ace::RequestData& requestData) { requestData.SetMethod(valStr); } },
    { "responseType", [](const char* valStr,
                            OHOS::Ace::RequestData& requestData) { requestData.SetResponseType(valStr); } },
    { "url", [](const char* valStr, OHOS::Ace::RequestData& requestData) { requestData.SetUrl(valStr); } },
};

const LinearMapNode<void (*)(shared_ptr<JsRuntime>, const shared_ptr<JsValue>&, RequestData&)>
    JsiGroupJsBridge::fetchRequestDataMap2[] = {
        { "data",
            [](shared_ptr<JsRuntime> runtime,
                const shared_ptr<JsValue>& val, OHOS::Ace::RequestData& requestData) {
                std::string objStr = SerializationObjectToString(runtime, val);
                if (objStr.empty()) {
                    return;
                }
                requestData.SetData(objStr.c_str());
            } },
        { "header",
            [](shared_ptr<JsRuntime> runtime,
                const shared_ptr<JsValue>& val, OHOS::Ace::RequestData& requestData) {
                if (!val->IsObject(runtime)) {
                    return;
                }
                int32_t length = 0;
                shared_ptr<JsValue> propertyNames;
                if (val->GetEnumerablePropertyNames(runtime, propertyNames, length)) {
                    std::map<std::string, std::string> header;
                    for (int32_t i = 0; i < length; ++i) {
                        shared_ptr<JsValue> key = propertyNames->GetElement(runtime, i);
                        if (key->IsString(runtime)) {
                            shared_ptr<JsValue> item = val->GetProperty(runtime, key);
                            if (item->IsString(runtime)) {
                                header[key->ToString(runtime)] = item->ToString(runtime);
                            }
                        } else {
                            LOGW("key is null. Ignoring!");
                        }
                    }
                    requestData.SetHeader(header);
                }
            } },
    };

void JsiGroupJsBridge::GetRequestData(const shared_ptr<JsValue>& valObject, RequestData& requestData)
{
    if (!valObject->IsObject(runtime_)) {
        return;
    }
    int32_t len = 0;
    shared_ptr<JsValue> propertyNames;
    valObject->GetEnumerablePropertyNames(runtime_, propertyNames, len);
    for (int32_t i = 0; i < len; ++i) {
        shared_ptr<JsValue> key = propertyNames->GetElement(runtime_, i);
        shared_ptr<JsValue> item = valObject->GetProperty(runtime_, key);
        if (item->IsString(runtime_)) {
            auto iter = BinarySearchFindIndex(
                fetchRequestDataMap1, ArraySize(fetchRequestDataMap1), key->ToString(runtime_).c_str());
            if (iter != -1) {
                fetchRequestDataMap1[iter].value(item->ToString(runtime_).c_str(), requestData);
            }
        } else if (item->IsObject(runtime_)) {
            auto iter = BinarySearchFindIndex(
                fetchRequestDataMap2, ArraySize(fetchRequestDataMap2), key->ToString(runtime_).c_str());
            if (iter != -1) {
                fetchRequestDataMap2[iter].value(runtime_, item, requestData);
            }
        }
    }
}

ParseJsDataResult JsiGroupJsBridge::ParseRequestData(
    int32_t argc, const std::vector<shared_ptr<JsValue>>& argv, OHOS::Ace::RequestData& requestData, int32_t requestId)
{
    if (argc < PLUGIN_REQUEST_ARG_APP_PARAMS_INDEX) {
        return ParseJsDataResult::PARSE_JS_SUCCESS;
    }
    for (int32_t i = PLUGIN_REQUEST_ARG_APP_PARAMS_INDEX; i < argc; i++) {
        const shared_ptr<JsValue> val = argv[i];
        if (val->IsObject(runtime_)) {
            std::string objStr = SerializationObjectToString(runtime_, val);
            if (objStr.empty()) {
                LOGW("Process callNative para is null");
                return ParseJsDataResult::PARSE_JS_ERR_UNSUPPORTED_TYPE;
            }
            GetRequestData(val, requestData);
        } else if (val->IsUndefined(runtime_)) {
        } else {
            LOGE("Process callNative para type: unsupported type");
            return ParseJsDataResult::PARSE_JS_ERR_UNSUPPORTED_TYPE;
        }
    }
    return ParseJsDataResult::PARSE_JS_SUCCESS;
}
#endif

} // namespace OHOS::Ace::Framework
