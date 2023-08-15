/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "prompt_action.h"

#include <memory>
#include <string>

#include "interfaces/napi/kits/utils/napi_utils.h"

#include "base/subwindow/subwindow_manager.h"
#include "base/utils/system_properties.h"
#include "bridge/common/utils/engine_helper.h"
#include "core/common/ace_engine.h"

namespace OHOS::Ace::Napi {
namespace {
const int32_t SHOW_DIALOG_BUTTON_NUM_MAX = -1;
const int32_t SHOW_ACTION_MENU_BUTTON_NUM_MAX = 6;
constexpr char DEFAULT_FONT_COLOR_STRING_VALUE[] = "#ff007dff";
const std::vector<DialogAlignment> DIALOG_ALIGNMENT = { DialogAlignment::TOP, DialogAlignment::CENTER,
    DialogAlignment::BOTTOM, DialogAlignment::DEFAULT, DialogAlignment::TOP_START, DialogAlignment::TOP_END,
    DialogAlignment::CENTER_START, DialogAlignment::CENTER_END, DialogAlignment::BOTTOM_START,
    DialogAlignment::BOTTOM_END };

#ifdef OHOS_STANDARD_SYSTEM
bool ContainerIsService()
{
    auto containerId = Container::CurrentId();
    // Get active container when current instanceid is less than 0
    if (containerId < 0) {
        auto container = Container::GetActive();
        if (container) {
            containerId = container->GetInstanceId();
        }
    }
    // for pa service
    return containerId >= MIN_PA_SERVICE_ID || containerId < 0;
}
#endif
} // namespace

bool HasProperty(napi_env env, napi_value value, const std::string& targetStr)
{
    bool hasProperty = false;
    napi_has_named_property(env, value, targetStr.c_str(), &hasProperty);
    return hasProperty;
}

napi_value GetReturnObject(napi_env env, std::string callbackString)
{
    napi_value result = nullptr;
    napi_value returnObj = nullptr;
    napi_create_object(env, &returnObj);
    napi_create_string_utf8(env, callbackString.c_str(), NAPI_AUTO_LENGTH, &result);
    napi_set_named_property(env, returnObj, "errMsg", result);
    return returnObj;
}

napi_value JSPromptShowToast(napi_env env, napi_callback_info info)
{
    size_t requireArgc = 1;
    size_t argc = 1;
    napi_value argv = nullptr;
    napi_value thisVar = nullptr;
    void* data = nullptr;
    napi_get_cb_info(env, info, &argc, &argv, &thisVar, &data);
    if (argc != requireArgc) {
        NapiThrow(env, "The number of parameters must be equal to 1.", Framework::ERROR_CODE_PARAM_INVALID);
        return nullptr;
    }
    napi_value messageNApi = nullptr;
    napi_value durationNApi = nullptr;
    napi_value bottomNApi = nullptr;
    std::string messageString;
    std::string bottomString;
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, argv, &valueType);
    if (valueType == napi_object) {
        // message can not be null
        if (!HasProperty(env, argv, "message")) {
            NapiThrow(env, "Required input parameters are missing.", Framework::ERROR_CODE_PARAM_INVALID);
            return nullptr;
        }
        napi_get_named_property(env, argv, "message", &messageNApi);
        napi_get_named_property(env, argv, "duration", &durationNApi);
        napi_get_named_property(env, argv, "bottom", &bottomNApi);
    } else {
        NapiThrow(env, "The type of parameters is incorrect.", Framework::ERROR_CODE_PARAM_INVALID);
        return nullptr;
    }
    size_t ret = 0;
    napi_typeof(env, messageNApi, &valueType);
    if (valueType == napi_string) {
        size_t messageLen = GetParamLen(messageNApi) + 1;
        std::unique_ptr<char[]> message = std::make_unique<char[]>(messageLen);
        napi_get_value_string_utf8(env, messageNApi, message.get(), messageLen, &ret);
        messageString = message.get();
    } else if (valueType == napi_object) {
        int32_t id = 0;
        int32_t type = 0;
        std::vector<std::string> params;
        if (!ParseResourceParam(env, messageNApi, id, type, params)) {
            LOGE("can not parse resource info from input params.");
            NapiThrow(env, "Can not parse resource info from input params.", Framework::ERROR_CODE_INTERNAL_ERROR);
            return nullptr;
        }
        if (!ParseString(id, type, params, messageString)) {
            LOGE("can not get message from resource manager.");
            NapiThrow(env, "Can not get message from resource manager.", Framework::ERROR_CODE_INTERNAL_ERROR);
            return nullptr;
        }
    } else {
        LOGE("The parameter type is incorrect.");
        NapiThrow(env, "The type of message is incorrect.", Framework::ERROR_CODE_PARAM_INVALID);
        return nullptr;
    }

    int32_t duration = -1;
    std::string durationStr;
    napi_typeof(env, durationNApi, &valueType);
    if (valueType == napi_number) {
        napi_get_value_int32(env, durationNApi, &duration);
    } else if (valueType == napi_object) {
        int32_t id = 0;
        int32_t type = 0;
        std::vector<std::string> params;
        if (!ParseResourceParam(env, durationNApi, id, type, params)) {
            LOGE("can not parse resource info from input params.");
            NapiThrow(env, "Can not parse resource info from input params.", Framework::ERROR_CODE_INTERNAL_ERROR);
            return nullptr;
        }
        if (!ParseString(id, type, params, durationStr)) {
            LOGE("can not get message from resource manager.");
            NapiThrow(env, "Can not get message from resource manager.", Framework::ERROR_CODE_INTERNAL_ERROR);
            return nullptr;
        }
        duration = StringUtils::StringToInt(durationStr);
    }

    napi_typeof(env, bottomNApi, &valueType);
    if (valueType == napi_string) {
        size_t bottomLen = GetParamLen(bottomNApi) + 1;
        std::unique_ptr<char[]> bottom = std::make_unique<char[]>(bottomLen);
        napi_get_value_string_utf8(env, bottomNApi, bottom.get(), bottomLen, &ret);
        bottomString = bottom.get();
    } else if (valueType == napi_number) {
        double bottom = 0.0;
        napi_get_value_double(env, bottomNApi, &bottom);
        bottomString = std::to_string(bottom);
    } else if (valueType == napi_object) {
        int32_t id = 0;
        int32_t type = 0;
        std::vector<std::string> params;
        if (!ParseResourceParam(env, bottomNApi, id, type, params)) {
            LOGE("can not parse resource info from input params.");
            NapiThrow(env, "Can not parse resource info from input params.", Framework::ERROR_CODE_INTERNAL_ERROR);
            return nullptr;
        }
        if (!ParseString(id, type, params, bottomString)) {
            LOGE("can not get message from resource manager.");
            NapiThrow(env, "Can not get message from resource manager.", Framework::ERROR_CODE_INTERNAL_ERROR);
            return nullptr;
        }
    }
#ifdef OHOS_STANDARD_SYSTEM
    if (SystemProperties::GetExtSurfaceEnabled() || !ContainerIsService()) {
        auto delegate = EngineHelper::GetCurrentDelegate();
        if (!delegate) {
            LOGE("can not get delegate.");
            NapiThrow(env, "Can not get delegate.", Framework::ERROR_CODE_INTERNAL_ERROR);
            return nullptr;
        }
        delegate->ShowToast(messageString, duration, bottomString);
    } else if (SubwindowManager::GetInstance() != nullptr) {
        SubwindowManager::GetInstance()->ShowToast(messageString, duration, bottomString);
    }
#else
    auto delegate = EngineHelper::GetCurrentDelegate();
    if (!delegate) {
        LOGE("can not get delegate.");
        NapiThrow(env, "UI execution context not found.", Framework::ERROR_CODE_INTERNAL_ERROR);
        return nullptr;
    }
    delegate->ShowToast(messageString, duration, bottomString);
#endif

    return nullptr;
}

struct PromptAsyncContext {
    napi_env env = nullptr;
    napi_value titleNApi = nullptr;
    napi_value messageNApi = nullptr;
    napi_value buttonsNApi = nullptr;
    napi_value autoCancel = nullptr;
    napi_value alignmentApi = nullptr;
    napi_value offsetApi = nullptr;
    napi_value maskRectApi = nullptr;
    napi_ref callbackSuccess = nullptr;
    napi_ref callbackCancel = nullptr;
    napi_ref callbackComplete = nullptr;
    std::string titleString;
    std::string messageString;
    std::vector<ButtonInfo> buttons;
    bool autoCancelBool = true;
    std::set<std::string> callbacks;
    std::string callbackSuccessString;
    std::string callbackCancelString;
    std::string callbackCompleteString;
    napi_deferred deferred = nullptr;
    napi_ref callbackRef = nullptr;
    int32_t callbackType = -1;
    int32_t successType = -1;
    bool valid = true;
    int32_t instanceId = -1;
};

void DeleteContextAndThrowError(
    napi_env env, std::shared_ptr<PromptAsyncContext>& context, const std::string& errorMessage)
{
    if (!context) {
        // context is null, no need to delete
        return;
    }
    NapiThrow(env, errorMessage, Framework::ERROR_CODE_PARAM_INVALID);
}

bool ParseButtons(napi_env env, std::shared_ptr<PromptAsyncContext>& context, int32_t maxButtonNum)
{
    uint32_t buttonsLen = 0;
    napi_value buttonArray = nullptr;
    napi_value textNApi = nullptr;
    napi_value colorNApi = nullptr;
    napi_valuetype valueType = napi_undefined;
    int32_t index = 0;
    napi_get_array_length(env, context->buttonsNApi, &buttonsLen);
    int32_t buttonsLenInt = buttonsLen;
    if (buttonsLenInt == 0) {
        DeleteContextAndThrowError(env, context, "Required input parameters are missing.");
        return false;
    }
    if (buttonsLenInt > maxButtonNum && maxButtonNum != -1) {
        buttonsLenInt = maxButtonNum;
        LOGW("Supports 1 - %{public}u buttons", maxButtonNum);
    }
    for (index = 0; index < buttonsLenInt; index++) {
        napi_get_element(env, context->buttonsNApi, index, &buttonArray);
        if (!HasProperty(env, buttonArray, "text")) {
            DeleteContextAndThrowError(env, context, "Required input parameters are missing.");
            return false;
        }
        std::string textString;
        napi_get_named_property(env, buttonArray, "text", &textNApi);
        if (!GetNapiString(env, textNApi, textString, valueType)) {
            DeleteContextAndThrowError(env, context, "The type of parameters is incorrect.");
            return false;
        }
        if (!HasProperty(env, buttonArray, "color")) {
            DeleteContextAndThrowError(env, context, "Required input parameters are missing.");
            return false;
        }
        std::string colorString;
        napi_get_named_property(env, buttonArray, "color", &colorNApi);
        if (!GetNapiString(env, colorNApi, colorString, valueType)) {
            if (valueType == napi_undefined) {
                colorString = DEFAULT_FONT_COLOR_STRING_VALUE;
            } else {
                DeleteContextAndThrowError(env, context, "The type of parameters is incorrect.");
                return false;
            }
        }
        ButtonInfo buttonInfo = { .text = textString, .textColor = colorString };
        context->buttons.emplace_back(buttonInfo);
    }
    return true;
}

bool ParseNapiDimension(napi_env env, CalcDimension& result, napi_value napiValue, DimensionUnit defaultUnit)
{
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, napiValue, &valueType);
    if (valueType == napi_number) {
        double value = 0;
        napi_get_value_double(env, napiValue, &value);
        result.SetUnit(defaultUnit);
        result.SetValue(value);
        return true;
    } else if (valueType == napi_string) {
        std::string valueString;
        if (!GetNapiString(env, napiValue, valueString, valueType)) {
            return false;
        }
        result = StringUtils::StringToCalcDimension(valueString, false, defaultUnit);
        return true;
    } else if (valueType == napi_object) {
        int32_t id = 0;
        int32_t type = 0;
        std::vector<std::string> params;
        std::string ParameterStr;
        if (!ParseResourceParam(env, napiValue, id, type, params)) {
            LOGE("can not parse resource info from inout params.");
            return false;
        }
        if (!ParseString(id, type, params, ParameterStr)) {
            LOGE("can not get message from resource manager.");
            return false;
        }
        result = StringUtils::StringToDimensionWithUnit(ParameterStr);
        return true;
    }
    return false;
}

void GetNapiDialogProps(napi_env env, const std::shared_ptr<PromptAsyncContext>& asyncContext,
                        std::optional<DialogAlignment>& alignment,
                        std::optional<DimensionOffset>& offset,
                        std::optional<DimensionRect>& maskRect)
{
    napi_valuetype valueType = napi_undefined;
    // parse alignment
    napi_typeof(env, asyncContext->alignmentApi, &valueType);
    if (valueType == napi_number) {
        int32_t num;
        napi_get_value_int32(env, asyncContext->alignmentApi, &num);
        if (num >= 0 && num < static_cast<int32_t>(DIALOG_ALIGNMENT.size())) {
            alignment = DIALOG_ALIGNMENT[num];
        }
    }

    // parse offset
    napi_typeof(env, asyncContext->offsetApi, &valueType);
    if (valueType == napi_object) {
        napi_value dxApi = nullptr;
        napi_value dyApi = nullptr;
        napi_get_named_property(env, asyncContext->offsetApi, "dx", &dxApi);
        napi_get_named_property(env, asyncContext->offsetApi, "dy", &dyApi);
        CalcDimension dx;
        CalcDimension dy;
        ParseNapiDimension(env, dx, dxApi, DimensionUnit::VP);
        ParseNapiDimension(env, dy, dyApi, DimensionUnit::VP);
        offset = DimensionOffset { dx, dy };
    }

    // parse maskRect
    napi_typeof(env, asyncContext->maskRectApi, &valueType);
    if (valueType == napi_object) {
        napi_value xApi = nullptr;
        napi_value yApi = nullptr;
        napi_value widthApi = nullptr;
        napi_value heightApi = nullptr;
        napi_get_named_property(env, asyncContext->maskRectApi, "x", &xApi);
        napi_get_named_property(env, asyncContext->maskRectApi, "y", &yApi);
        napi_get_named_property(env, asyncContext->maskRectApi, "width", &widthApi);
        napi_get_named_property(env, asyncContext->maskRectApi, "height", &heightApi);
        CalcDimension x;
        CalcDimension y;
        CalcDimension width;
        CalcDimension height;
        ParseNapiDimension(env, x, xApi, DimensionUnit::VP);
        ParseNapiDimension(env, y, yApi, DimensionUnit::VP);
        ParseNapiDimension(env, width, widthApi, DimensionUnit::VP);
        ParseNapiDimension(env, height, heightApi, DimensionUnit::VP);
        DimensionOffset dimensionOffset = { x, y };
        maskRect = DimensionRect { width, height, dimensionOffset};
    }
}

napi_value JSPromptShowDialog(napi_env env, napi_callback_info info)
{
    size_t requireArgc = 1;
    size_t argc = 2;
    napi_value argv[3] = { 0 };
    napi_value thisVar = nullptr;
    void* data = nullptr;
    napi_get_cb_info(env, info, &argc, argv, &thisVar, &data);
    if (argc < requireArgc) {
        NapiThrow(
            env, "The number of parameters must be greater than or equal to 1.", Framework::ERROR_CODE_PARAM_INVALID);
        return nullptr;
    }
    if (thisVar == nullptr) {
        LOGE("%{public}s, This argument is nullptr.", __func__);
        return nullptr;
    }
    napi_valuetype valueTypeOfThis = napi_undefined;
    napi_typeof(env, thisVar, &valueTypeOfThis);
    if (valueTypeOfThis == napi_undefined) {
        LOGE("%{public}s, Wrong this value.", __func__);
        return nullptr;
    }

    auto asyncContext = std::make_shared<PromptAsyncContext>();
    asyncContext->env = env;
    asyncContext->instanceId = Container::CurrentId();

    std::optional<DialogAlignment> alignment;
    std::optional<DimensionOffset> offset;
    std::optional<DimensionRect> maskRect;

    for (size_t i = 0; i < argc; i++) {
        napi_valuetype valueType = napi_undefined;
        napi_typeof(env, argv[i], &valueType);
        if (i == 0) {
            if (valueType != napi_object) {
                DeleteContextAndThrowError(env, asyncContext, "The type of parameters is incorrect.");
                return nullptr;
            }
            napi_get_named_property(env, argv[0], "title", &asyncContext->titleNApi);
            napi_get_named_property(env, argv[0], "message", &asyncContext->messageNApi);
            napi_get_named_property(env, argv[0], "buttons", &asyncContext->buttonsNApi);
            napi_get_named_property(env, argv[0], "autoCancel", &asyncContext->autoCancel);
            napi_get_named_property(env, argv[0], "alignment", &asyncContext->alignmentApi);
            napi_get_named_property(env, argv[0], "offset", &asyncContext->offsetApi);
            napi_get_named_property(env, argv[0], "maskRect", &asyncContext->maskRectApi);
            GetNapiString(env, asyncContext->titleNApi, asyncContext->titleString, valueType);
            GetNapiString(env, asyncContext->messageNApi, asyncContext->messageString, valueType);
            GetNapiDialogProps(env, asyncContext, alignment, offset, maskRect);
            bool isBool = false;
            napi_is_array(env, asyncContext->buttonsNApi, &isBool);
            napi_typeof(env, asyncContext->buttonsNApi, &valueType);
            if (valueType == napi_object && isBool) {
                if (!ParseButtons(env, asyncContext, SHOW_DIALOG_BUTTON_NUM_MAX)) {
                    return nullptr;
                }
            }
            napi_typeof(env, asyncContext->autoCancel, &valueType);
            if (valueType == napi_boolean) {
                napi_get_value_bool(env, asyncContext->autoCancel, &asyncContext->autoCancelBool);
            }
        } else if (valueType == napi_function) {
            napi_create_reference(env, argv[i], 1, &asyncContext->callbackRef);
        } else {
            DeleteContextAndThrowError(env, asyncContext, "The type of parameters is incorrect.");
            return nullptr;
        }
    }
    napi_value result = nullptr;
    if (asyncContext->callbackRef == nullptr) {
        napi_create_promise(env, &asyncContext->deferred, &result);
    } else {
        napi_get_undefined(env, &result);
    }
    asyncContext->callbacks.emplace("success");
    asyncContext->callbacks.emplace("cancel");

    auto callBack = [asyncContext](int32_t callbackType, int32_t successType) {
        if (asyncContext == nullptr) {
            return;
        }

        asyncContext->callbackType = callbackType;
        asyncContext->successType = successType;
        auto container = AceEngine::Get().GetContainer(asyncContext->instanceId);
        if (!container) {
            LOGW("container is null. %{public}d", asyncContext->instanceId);
            return;
        }

        auto taskExecutor = container->GetTaskExecutor();
        if (!taskExecutor) {
            LOGW("taskExecutor is null.");
            return;
        }
        taskExecutor->PostTask(
            [asyncContext]() mutable {
                if (asyncContext == nullptr) {
                    LOGE("%{public}s, asyncContext is nullptr.", __func__);
                    return;
                }

                if (!asyncContext->valid) {
                    LOGE("%{public}s, module exported object is invalid.", __func__);
                    return;
                }

                napi_handle_scope scope = nullptr;
                napi_open_handle_scope(asyncContext->env, &scope);
                if (scope == nullptr) {
                    LOGE("%{public}s, open handle scope failed.", __func__);
                    return;
                }

                napi_value ret;
                napi_value successIndex = nullptr;
                napi_create_int32(asyncContext->env, asyncContext->successType, &successIndex);
                napi_value indexObj = nullptr;
                napi_create_object(asyncContext->env, &indexObj);
                napi_set_named_property(asyncContext->env, indexObj, "index", successIndex);
                napi_value result[2] = { 0 };
                napi_create_object(asyncContext->env, &result[1]);
                napi_set_named_property(asyncContext->env, result[1], "index", successIndex);
                bool dialogResult = true;
                switch (asyncContext->callbackType) {
                    case 0:
                        napi_get_undefined(asyncContext->env, &result[0]);
                        dialogResult = true;
                        break;
                    case 1:
                        napi_value message = nullptr;
                        napi_create_string_utf8(asyncContext->env, "cancel", strlen("cancel"), &message);
                        napi_create_error(asyncContext->env, nullptr, message, &result[0]);
                        dialogResult = false;
                        break;
                }
                if (asyncContext->deferred) {
                    if (dialogResult) {
                        napi_resolve_deferred(asyncContext->env, asyncContext->deferred, result[1]);
                    } else {
                        napi_reject_deferred(asyncContext->env, asyncContext->deferred, result[0]);
                    }
                } else {
                    napi_value callback = nullptr;
                    napi_get_reference_value(asyncContext->env, asyncContext->callbackRef, &callback);
                    napi_call_function(
                        asyncContext->env, nullptr, callback, sizeof(result) / sizeof(result[0]), result, &ret);
                    napi_delete_reference(asyncContext->env, asyncContext->callbackRef);
                }
                napi_close_handle_scope(asyncContext->env, scope);
            },
            TaskExecutor::TaskType::JS);
    };

    PromptDialogAttr promptDialogAttr = {
        .title = asyncContext->titleString,
        .message = asyncContext->messageString,
        .autoCancel = asyncContext->autoCancelBool,
        .alignment = alignment,
        .offset = offset,
        .maskRect = maskRect,
    };

#ifdef OHOS_STANDARD_SYSTEM
    // NG
    if (SystemProperties::GetExtSurfaceEnabled() || !ContainerIsService()) {
        auto delegate = EngineHelper::GetCurrentDelegate();
        if (delegate) {
            delegate->ShowDialog(promptDialogAttr, asyncContext->buttons, std::move(callBack),
                                 asyncContext->callbacks);
        } else {
            LOGE("delegate is null");
            // throw internal error
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
    } else if (SubwindowManager::GetInstance() != nullptr) {
        SubwindowManager::GetInstance()->ShowDialog(promptDialogAttr, asyncContext->buttons, std::move(callBack),
                                                    asyncContext->callbacks);
    }
#else
    auto delegate = EngineHelper::GetCurrentDelegate();
    if (delegate) {
            delegate->ShowDialog(promptDialogAttr, asyncContext->buttons, std::move(callBack),
                                 asyncContext->callbacks);
    } else {
        LOGE("delegate is null");
        // throw internal error
        napi_value code = nullptr;
        std::string strCode = std::to_string(Framework::ERROR_CODE_INTERNAL_ERROR);
        napi_create_string_utf8(env, strCode.c_str(), strCode.length(), &code);
        napi_value msg = nullptr;
        std::string strMsg = ErrorToMessage(Framework::ERROR_CODE_INTERNAL_ERROR) + "UI execution context not found.";
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
#endif
    return result;
}

napi_value JSPromptShowActionMenu(napi_env env, napi_callback_info info)
{
    size_t requireArgc = 1;
    size_t argc = 2;
    napi_value argv[3] = { 0 };
    napi_value thisVar = nullptr;
    void* data = nullptr;
    napi_get_cb_info(env, info, &argc, argv, &thisVar, &data);
    if (argc < requireArgc) {
        NapiThrow(
            env, "The number of parameters must be greater than or equal to 1.", Framework::ERROR_CODE_PARAM_INVALID);
        return nullptr;
    }
    if (thisVar == nullptr) {
        LOGE("%{public}s, This argument is nullptr.", __func__);
        return nullptr;
    }
    napi_valuetype valueTypeOfThis = napi_undefined;
    napi_typeof(env, thisVar, &valueTypeOfThis);
    if (valueTypeOfThis == napi_undefined) {
        LOGE("%{public}s, Wrong this value.", __func__);
        return nullptr;
    }

    auto asyncContext = std::make_shared<PromptAsyncContext>();
    asyncContext->env = env;
    asyncContext->instanceId = Container::CurrentId();
    for (size_t i = 0; i < argc; i++) {
        napi_valuetype valueType = napi_undefined;
        napi_typeof(env, argv[i], &valueType);
        if (i == 0) {
            if (valueType != napi_object) {
                DeleteContextAndThrowError(env, asyncContext, "The type of parameters is incorrect.");
                return nullptr;
            }
            napi_get_named_property(env, argv[0], "title", &asyncContext->titleNApi);
            GetNapiString(env, asyncContext->titleNApi, asyncContext->titleString, valueType);
            if (!HasProperty(env, argv[0], "buttons")) {
                DeleteContextAndThrowError(env, asyncContext, "Required input parameters are missing.");
                return nullptr;
            }
            napi_get_named_property(env, argv[0], "buttons", &asyncContext->buttonsNApi);
            bool isBool = false;
            napi_is_array(env, asyncContext->buttonsNApi, &isBool);
            napi_typeof(env, asyncContext->buttonsNApi, &valueType);
            if (valueType == napi_object && isBool) {
                if (!ParseButtons(env, asyncContext, SHOW_ACTION_MENU_BUTTON_NUM_MAX)) {
                    return nullptr;
                }
            } else {
                DeleteContextAndThrowError(env, asyncContext, "The type of the button parameters is incorrect.");
                return nullptr;
            }
        } else if (valueType == napi_function) {
            napi_create_reference(env, argv[i], 1, &asyncContext->callbackRef);
        } else {
            DeleteContextAndThrowError(env, asyncContext, "The type of parameters is incorrect.");
            return nullptr;
        }
    }
    napi_value result = nullptr;
    if (asyncContext->callbackRef == nullptr) {
        napi_create_promise(env, &asyncContext->deferred, &result);
    } else {
        napi_get_undefined(env, &result);
    }

    auto callBack = [asyncContext](int32_t callbackType, int32_t successType) {
        if (asyncContext == nullptr) {
            return;
        }

        asyncContext->callbackType = callbackType;
        asyncContext->successType = successType;
        auto container = AceEngine::Get().GetContainer(asyncContext->instanceId);
        if (!container) {
            LOGW("container is null. %{public}d", asyncContext->instanceId);
            return;
        }

        auto taskExecutor = container->GetTaskExecutor();
        if (!taskExecutor) {
            LOGW("taskExecutor is null.");
            return;
        }
        taskExecutor->PostTask(
            [asyncContext]() mutable {
                if (asyncContext == nullptr) {
                    LOGE("%{public}s, asyncContext is nullptr.", __func__);
                    return;
                }

                if (!asyncContext->valid) {
                    LOGE("%{public}s, module exported object is invalid.", __func__);
                    return;
                }

                napi_handle_scope scope = nullptr;
                napi_open_handle_scope(asyncContext->env, &scope);
                if (scope == nullptr) {
                    LOGE("%{public}s, open handle scope failed.", __func__);
                    return;
                }

                napi_value ret;
                napi_value successIndex = nullptr;
                napi_create_int32(asyncContext->env, asyncContext->successType, &successIndex);
                asyncContext->callbackSuccessString = "showActionMenu:ok";
                napi_value indexObj = GetReturnObject(asyncContext->env, asyncContext->callbackSuccessString);
                napi_set_named_property(asyncContext->env, indexObj, "index", successIndex);
                napi_value result[2] = { 0 };
                napi_create_object(asyncContext->env, &result[1]);
                napi_set_named_property(asyncContext->env, result[1], "index", successIndex);
                bool dialogResult = true;
                switch (asyncContext->callbackType) {
                    case 0:
                        napi_get_undefined(asyncContext->env, &result[0]);
                        dialogResult = true;
                        break;
                    case 1:
                        napi_value message = nullptr;
                        napi_create_string_utf8(asyncContext->env, "cancel", strlen("cancel"), &message);
                        napi_create_error(asyncContext->env, nullptr, message, &result[0]);
                        dialogResult = false;
                        break;
                }
                if (asyncContext->deferred) {
                    if (dialogResult) {
                        napi_resolve_deferred(asyncContext->env, asyncContext->deferred, result[1]);
                    } else {
                        napi_reject_deferred(asyncContext->env, asyncContext->deferred, result[0]);
                    }
                } else {
                    napi_value callback = nullptr;
                    napi_get_reference_value(asyncContext->env, asyncContext->callbackRef, &callback);
                    napi_call_function(
                        asyncContext->env, nullptr, callback, sizeof(result) / sizeof(result[0]), result, &ret);
                    napi_delete_reference(asyncContext->env, asyncContext->callbackRef);
                }
                napi_close_handle_scope(asyncContext->env, scope);
            },
            TaskExecutor::TaskType::JS);
    };

#ifdef OHOS_STANDARD_SYSTEM
    if (SystemProperties::GetExtSurfaceEnabled() || !ContainerIsService()) {
        auto delegate = EngineHelper::GetCurrentDelegate();
        if (delegate) {
            delegate->ShowActionMenu(asyncContext->titleString, asyncContext->buttons, std::move(callBack));
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
    } else if (SubwindowManager::GetInstance() != nullptr) {
        SubwindowManager::GetInstance()->ShowActionMenu(
            asyncContext->titleString, asyncContext->buttons, std::move(callBack));
    }
#else
    auto delegate = EngineHelper::GetCurrentDelegate();
    if (delegate) {
        delegate->ShowActionMenu(asyncContext->titleString, asyncContext->buttons, std::move(callBack));
    } else {
        LOGE("delegate is null");
        napi_value code = nullptr;
        std::string strCode = std::to_string(Framework::ERROR_CODE_INTERNAL_ERROR);
        napi_create_string_utf8(env, strCode.c_str(), strCode.length(), &code);
        napi_value msg = nullptr;
        std::string strMsg = ErrorToMessage(Framework::ERROR_CODE_INTERNAL_ERROR) + "UI execution context not found.";
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
#endif
    return result;
}
} // namespace OHOS::Ace::Napi
