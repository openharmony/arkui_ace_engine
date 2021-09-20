/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include <string>

#include "napi/native_api.h"
#include "napi/native_engine/native_value.h"
#include "napi/native_node_api.h"

#include "frameworks/bridge/js_frontend/engine/common/js_engine.h"

namespace OHOS::Ace::Napi {
namespace {

const int SHOW_DIALOG_BUTTON_NUM_MAX = 3;
const int SHOW_ACTION_MENU_BUTTON_NUM_MAX = 6;

} // namespace

size_t GetParamLen(napi_value nApi)
{
    auto nativeValue = reinterpret_cast<NativeValue*>(nApi);
    auto resultValue = nativeValue->ToString();
    auto nativeString = reinterpret_cast<NativeString*>(resultValue->GetInterface(NativeString::INTERFACE_ID));
    size_t len = nativeString->GetLength();
    return len;
}

napi_value GetReturnObj(napi_env env, std::string callbackString)
{
    napi_value result = nullptr;
    napi_value returnObj = nullptr;
    napi_create_object(env, &returnObj);
    napi_create_string_utf8(env, callbackString.c_str(), NAPI_AUTO_LENGTH, &result);
    napi_set_named_property(env, returnObj, "errMsg", result);
    return returnObj;
}

static napi_value JSPromptShowToast(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value argv = nullptr;
    napi_value thisVar = nullptr;
    void* data = nullptr;
    napi_get_cb_info(env, info, &argc, &argv, &thisVar, &data);

    napi_value messageNApi = nullptr;
    napi_value durationNApi = nullptr;
    napi_value bottomNApi = nullptr;
    std::string messageString;
    std::string bottomString;

    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, argv, &valueType);
    if (valueType == napi_object) {
        napi_get_named_property(env, argv, "message", &messageNApi);
        napi_get_named_property(env, argv, "duration", &durationNApi);
        napi_get_named_property(env, argv, "bottom", &bottomNApi);
    } else {
        return nullptr;
    }
    size_t ret = 0;
    napi_typeof(env, messageNApi, &valueType);
    if (valueType == napi_string) {
        size_t messageLen = GetParamLen(messageNApi) + 1;
        std::unique_ptr<char[]> message = std::make_unique<char[]>(messageLen);
        napi_get_value_string_utf8(env, messageNApi, message.get(), messageLen, &ret);
        messageString = message.get();
    } else {
        LOGE("The paramter type is incorrect");
        return nullptr;
    }

    int32_t duration = -1;
    napi_typeof(env, durationNApi, &valueType);
    if (valueType == napi_number) {
        napi_get_value_int32(env, durationNApi, &duration);
    }

    napi_typeof(env, bottomNApi, &valueType);
    if (valueType == napi_string) {
        size_t bottomLen = GetParamLen(bottomNApi) + 1;
        std::unique_ptr<char[]> message = std::make_unique<char[]>(bottomLen);
        napi_get_value_string_utf8(env, bottomNApi, message.get(), bottomLen, &ret);
        bottomString = message.get();
    }

    OHOS::Ace::Framework::JsEngine* jsEngine = nullptr;
    napi_get_jsEngine(env, (void**)&jsEngine);
    jsEngine->GetFrontend()->ShowToast(messageString, duration, bottomString);
    return nullptr;
}

struct PromptAsyncContext {
    napi_env env = nullptr;
    napi_async_work work = nullptr;
    napi_value titleNApi = nullptr;
    napi_value messageNApi = nullptr;
    napi_value buttonsNApi = nullptr;
    napi_ref callbackSuccess = nullptr;
    napi_ref callbackCancel = nullptr;
    napi_ref callbackComplete = nullptr;
    std::string titleString;
    std::string messageString;
    std::vector<std::pair<std::string, std::string>> buttons;
    bool autoCancel = true;
    std::set<std::string> callbacks;
    std::string callbackSuccessString;
    std::string callbackCancelString;
    std::string callbackCompleteString;
};

static napi_value JSPromptShowDialog(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value argv = nullptr;
    napi_value thisVar = nullptr;
    void* data = nullptr;
    napi_get_cb_info(env, info, &argc, &argv, &thisVar, &data);

    auto asyncContext = new PromptAsyncContext();
    asyncContext->env = env;
    napi_value successFunc = nullptr;
    napi_value cancelFunc = nullptr;
    napi_value completeFunc = nullptr;
    size_t ret = 0;
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, argv, &valueType);
    if (valueType == napi_object) {
        napi_get_named_property(env, argv, "title", &asyncContext->titleNApi);
        napi_get_named_property(env, argv, "message", &asyncContext->messageNApi);
        napi_get_named_property(env, argv, "buttons", &asyncContext->buttonsNApi);
        napi_get_named_property(env, argv, "success", &successFunc);
        napi_get_named_property(env, argv, "cancel", &cancelFunc);
        napi_get_named_property(env, argv, "complete", &completeFunc);

        napi_typeof(env, asyncContext->titleNApi, &valueType);
        size_t titleLen = GetParamLen(asyncContext->titleNApi);
        std::unique_ptr<char[]> titleChar = std::make_unique<char[]>(titleLen);
        if (asyncContext->titleNApi != nullptr && valueType == napi_string) {
            napi_get_value_string_utf8(env, asyncContext->titleNApi, titleChar.get(), titleLen, &ret);
            asyncContext->titleString = titleChar.get();
        }
        napi_typeof(env, asyncContext->messageNApi, &valueType);
        size_t messageLen = GetParamLen(asyncContext->messageNApi);
        std::unique_ptr<char[]> messageChar = std::make_unique<char[]>(messageLen);
        if (asyncContext->messageNApi != nullptr && valueType == napi_string) {
            napi_get_value_string_utf8(env, asyncContext->messageNApi, messageChar.get(), messageLen, &ret);
            asyncContext->messageString = messageChar.get();
        }
        bool isBool = false;
        napi_is_array(env, asyncContext->buttonsNApi, &isBool);
        napi_typeof(env, asyncContext->buttonsNApi, &valueType);
        if (valueType == napi_object && isBool) {
            uint32_t buttonsLen = 0;
            napi_value buttonArray = nullptr;
            napi_value textNApi = nullptr;
            napi_value colorNApi = nullptr;

            uint32_t index = 0;
            napi_get_array_length(env, asyncContext->buttonsNApi, &buttonsLen);
            int buttonsLenInt = buttonsLen;
            if (buttonsLenInt > SHOW_DIALOG_BUTTON_NUM_MAX) {
                buttonsLenInt = SHOW_DIALOG_BUTTON_NUM_MAX;
                LOGE("Supports 1 - 3 buttons");
            }
            for (int j = 0; j < buttonsLenInt; j++) {
                napi_get_element(env, asyncContext->buttonsNApi, index, &buttonArray);
                index++;
                napi_get_named_property(env, buttonArray, "text", &textNApi);
                napi_get_named_property(env, buttonArray, "color", &colorNApi);
                std::string textString;
                std::string colorString;
                napi_typeof(env, textNApi, &valueType);
                if (valueType == napi_string) {
                    size_t textLen = GetParamLen(textNApi);
                    char text[textLen + 1];
                    napi_get_value_string_utf8(env, textNApi, text, textLen, &ret);
                    textString = text;
                }
                napi_typeof(env, colorNApi, &valueType);
                if (valueType == napi_string) {
                    size_t colorLen = GetParamLen(colorNApi);
                    char color[colorLen + 1];
                    napi_get_value_string_utf8(env, colorNApi, color, colorLen, &ret);
                    colorString = color;
                }
                asyncContext->buttons.emplace_back(textString, colorString);
            }
        }

        napi_typeof(env, successFunc, &valueType);
        if (valueType == napi_function) {
            napi_create_reference(env, successFunc, 1, &asyncContext->callbackSuccess);
        }

        napi_typeof(env, cancelFunc, &valueType);
        if (valueType == napi_function) {
            napi_create_reference(env, cancelFunc, 1, &asyncContext->callbackCancel);
        }

        napi_typeof(env, completeFunc, &valueType);
        if (valueType == napi_function) {
            napi_create_reference(env, completeFunc, 1, &asyncContext->callbackComplete);
        }
        if (asyncContext->callbackSuccess) {
            asyncContext->callbacks.emplace("success");
        }
        if (asyncContext->callbackCancel) {
            asyncContext->callbacks.emplace("cancel");
        }
        if (asyncContext->callbackComplete) {
            asyncContext->callbacks.emplace("complete");
        }
    }

    napi_value resource = nullptr;
    napi_create_string_utf8(env, "JSPromptShowDialog", NAPI_AUTO_LENGTH, &resource);
    napi_create_async_work(
        env, nullptr, resource, [](napi_env env, void* data) {},
        [](napi_env env, napi_status status, void* data) {
            PromptAsyncContext* asyncContext = (PromptAsyncContext*)data;
            OHOS::Ace::Framework::JsEngine* jsEngine = nullptr;
            napi_get_jsEngine(env, (void**)&jsEngine);

            auto callBack = [env, asyncContext](int32_t callbackType, int32_t successType) {
                napi_value ret;
                napi_value callback = nullptr;
                napi_value successIndex = nullptr;
                napi_create_int32(env, successType, &successIndex);
                asyncContext->callbackSuccessString = "PromptShowDialog : ok";
                napi_value indexObj = GetReturnObj(env, asyncContext->callbackSuccessString);
                napi_set_named_property(env, indexObj, "index", successIndex);
                switch (callbackType) {
                    case 0:
                        if (asyncContext->callbackSuccess) {
                            napi_get_reference_value(env, asyncContext->callbackSuccess, &callback);
                            napi_call_function(env, nullptr, callback, 1, &indexObj, &ret);
                            napi_delete_reference(env, asyncContext->callbackSuccess);
                        }
                        break;
                    case 1:
                        if (asyncContext->callbackCancel) {
                            asyncContext->callbackCancelString = "cancel";
                            napi_value returnObj = GetReturnObj(env, asyncContext->callbackCancelString);
                            napi_get_reference_value(env, asyncContext->callbackCancel, &callback);
                            napi_call_function(env, nullptr, callback, 1, &returnObj, &ret);
                            napi_delete_reference(env, asyncContext->callbackCancel);
                        }
                        break;
                    case 2:
                        if (asyncContext->callbackComplete) {
                            asyncContext->callbackCompleteString = "Complete";
                            napi_value returnObj = GetReturnObj(env, asyncContext->callbackCompleteString);
                            napi_get_reference_value(env, asyncContext->callbackComplete, &callback);
                            napi_call_function(env, nullptr, callback, 1, &returnObj, &ret);
                            napi_delete_reference(env, asyncContext->callbackComplete);
                        }
                        break;
                    default:
                        break;
                }
            };
            jsEngine->GetFrontend()->ShowDialog(asyncContext->titleString, asyncContext->messageString,
                asyncContext->buttons, asyncContext->autoCancel, std::move(callBack), asyncContext->callbacks);
        },
        (void*)asyncContext, &asyncContext->work);
    napi_queue_async_work(env, asyncContext->work);
    return nullptr;
}

struct ShowActionMenuAsyncContext {
    napi_env env = nullptr;
    napi_async_work work = nullptr;

    napi_value titleNApi = nullptr;
    napi_value buttonsNApi = nullptr;
    napi_ref callbackSuccess = nullptr;
    napi_ref callbackFail = nullptr;
    napi_ref callbackComplete = nullptr;
    std::string titleString;
    std::vector<std::pair<std::string, std::string>> buttons;

    std::string callbackSuccessString;
    std::string callbackFailString;
    std::string callbackCompleteString;
};

static napi_value JSPromptShowActionMenu(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value argv = nullptr;
    napi_value thisVar = nullptr;
    void* data = nullptr;
    napi_get_cb_info(env, info, &argc, &argv, &thisVar, &data);

    auto asyncContext = new ShowActionMenuAsyncContext();
    asyncContext->env = env;
    napi_value successFunc = nullptr;
    napi_value failFunc = nullptr;
    napi_value completeFunc = nullptr;
    size_t ret = 0;
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, argv, &valueType);
    if (valueType == napi_object) {
        napi_get_named_property(env, argv, "title", &asyncContext->titleNApi);
        napi_get_named_property(env, argv, "buttons", &asyncContext->buttonsNApi);
        napi_get_named_property(env, argv, "success", &successFunc);
        napi_get_named_property(env, argv, "fail", &failFunc);
        napi_get_named_property(env, argv, "complete", &completeFunc);

        napi_typeof(env, asyncContext->titleNApi, &valueType);
        size_t titleLen = GetParamLen(asyncContext->titleNApi);
        std::unique_ptr<char[]> titleChar = std::make_unique<char[]>(titleLen);
        if (asyncContext->titleNApi != nullptr && valueType == napi_string) {
            napi_get_value_string_utf8(env, asyncContext->titleNApi, titleChar.get(), titleLen, &ret);
            asyncContext->titleString = titleChar.get();
        }
        bool isBool = false;
        napi_is_array(env, asyncContext->buttonsNApi, &isBool);
        napi_typeof(env, asyncContext->buttonsNApi, &valueType);
        if (valueType == napi_object && isBool) {
            uint32_t buttonsLen = 0;
            napi_value buttonArray = nullptr;
            napi_value textNApi = nullptr;
            napi_value colorNApi = nullptr;

            uint32_t index = 0;
            napi_get_array_length(env, asyncContext->buttonsNApi, &buttonsLen);
            int buttonsLenInt = buttonsLen;
            if (buttonsLenInt > SHOW_ACTION_MENU_BUTTON_NUM_MAX) {
                asyncContext->callbackFailString = "enableAlertBeforeBackPage:buttons is invalid";
                asyncContext->callbackCompleteString = "enableAlertBeforeBackPage:buttons is invalid";
            }
            for (int j = 0; j < buttonsLenInt; j++) {
                napi_get_element(env, asyncContext->buttonsNApi, index, &buttonArray);
                index++;
                napi_get_named_property(env, buttonArray, "text", &textNApi);
                napi_get_named_property(env, buttonArray, "color", &colorNApi);
                std::string textString;
                std::string colorString;
                napi_typeof(env, textNApi, &valueType);
                if (valueType == napi_string) {
                    size_t textLen = GetParamLen(textNApi);
                    char text[textLen + 1];
                    napi_get_value_string_utf8(env, textNApi, text, textLen, &ret);
                    textString = text;
                }
                napi_typeof(env, colorNApi, &valueType);
                if (valueType == napi_string) {
                    size_t colorLen = GetParamLen(colorNApi);
                    char color[colorLen + 1];
                    napi_get_value_string_utf8(env, colorNApi, color, colorLen, &ret);
                    colorString = color;
                }
                asyncContext->buttons.emplace_back(textString, colorString);
            }
        }

        napi_typeof(env, successFunc, &valueType);
        if (valueType == napi_function) {
            napi_create_reference(env, successFunc, 1, &asyncContext->callbackSuccess);
        }

        napi_typeof(env, failFunc, &valueType);
        if (valueType == napi_function) {
            napi_create_reference(env, failFunc, 1, &asyncContext->callbackFail);
        }

        napi_typeof(env, completeFunc, &valueType);
        if (valueType == napi_function) {
            napi_create_reference(env, completeFunc, 1, &asyncContext->callbackComplete);
        }
    }

    napi_value resource = nullptr;
    napi_create_string_utf8(env, "JSPromptShowActionMenu", NAPI_AUTO_LENGTH, &resource);
    napi_create_async_work(
        env, nullptr, resource, [](napi_env env, void* data) {},
        [](napi_env env, napi_status status, void* data) {
            ShowActionMenuAsyncContext* asyncContext = (ShowActionMenuAsyncContext*)data;
            OHOS::Ace::Framework::JsEngine* jsEngine = nullptr;
            napi_get_jsEngine(env, (void**)&jsEngine);
            napi_value ret;
            napi_value callback = nullptr;
            if (!asyncContext->callbackFailString.empty()) {
                if (asyncContext->callbackFail) {
                    napi_value returnObj = GetReturnObj(env, asyncContext->callbackFailString);
                    napi_get_reference_value(env, asyncContext->callbackFail, &callback);
                    napi_call_function(env, nullptr, callback, 1, &returnObj, &ret);
                    napi_delete_reference(env, asyncContext->callbackFail);
                }
                if (asyncContext->callbackComplete) {
                    napi_value returnObj = GetReturnObj(env, asyncContext->callbackCompleteString);
                    napi_get_reference_value(env, asyncContext->callbackComplete, &callback);
                    napi_call_function(env, nullptr, callback, 1, &returnObj, &ret);
                    napi_delete_reference(env, asyncContext->callbackComplete);
                }
            } else {
                auto callBack = [env, asyncContext](int32_t callbackType, int32_t successType) {
                    napi_value ret;
                    napi_value callback = nullptr;
                    napi_value successIndex = nullptr;
                    napi_create_int32(env, successType, &successIndex);
                    asyncContext->callbackSuccessString = "showActionMenu:ok";
                    napi_value indexObj = GetReturnObj(env, asyncContext->callbackSuccessString);
                    napi_set_named_property(env, indexObj, "tapIndex", successIndex);
                    switch (callbackType) {
                        case 0:
                            if (asyncContext->callbackSuccess) {
                                napi_get_reference_value(env, asyncContext->callbackSuccess, &callback);
                                napi_call_function(env, nullptr, callback, 1, &indexObj, &ret);
                                napi_delete_reference(env, asyncContext->callbackSuccess);
                            }
                            if (asyncContext->callbackComplete) {
                                napi_get_reference_value(env, asyncContext->callbackComplete, &callback);
                                napi_call_function(env, nullptr, callback, 1, &indexObj, &ret);
                                napi_delete_reference(env, asyncContext->callbackComplete);
                            }
                            break;
                        case 1:
                            if (asyncContext->callbackFail) {
                                asyncContext->callbackFailString = "Fail showActionMenu:fail cancel";
                                napi_value returnObj = GetReturnObj(env, asyncContext->callbackFailString);
                                napi_get_reference_value(env, asyncContext->callbackFail, &callback);
                                napi_call_function(env, nullptr, callback, 1, &returnObj, &ret);
                                napi_delete_reference(env, asyncContext->callbackFail);
                            }
                            if (asyncContext->callbackComplete) {
                                asyncContext->callbackCompleteString = "Complete showActionMenu:fail cancel";
                                napi_value returnObj = GetReturnObj(env, asyncContext->callbackCompleteString);
                                napi_get_reference_value(env, asyncContext->callbackComplete, &callback);
                                napi_call_function(env, nullptr, callback, 1, &returnObj, &ret);
                                napi_delete_reference(env, asyncContext->callbackComplete);
                            }
                            break;
                        default:
                            break;
                    }
                };
                jsEngine->GetFrontend()->ShowActionMenu(
                    asyncContext->titleString, asyncContext->buttons, std::move(callBack));
            }
        },
        (void*)asyncContext, &asyncContext->work);
    napi_queue_async_work(env, asyncContext->work);
    return nullptr;
}

static napi_value PromptExport(napi_env env, napi_value exports)
{
    static napi_property_descriptor promptDesc[] = {
        DECLARE_NAPI_FUNCTION("showToast", JSPromptShowToast),
        DECLARE_NAPI_FUNCTION("showDialog", JSPromptShowDialog),
        DECLARE_NAPI_FUNCTION("showActionMenu", JSPromptShowActionMenu),
    };
    NAPI_CALL(env, napi_define_properties(env, exports, sizeof(promptDesc) / sizeof(promptDesc[0]), promptDesc));
    return exports;
}

static napi_module promptModule = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = PromptExport,
    .nm_modname = "prompt",
    .nm_priv = ((void*)0),
    .reserved = { 0 },
};

extern "C" __attribute__((constructor)) void PromptRegister()
{
    napi_module_register(&promptModule);
}

} // namespace OHOS::Ace::Napi
