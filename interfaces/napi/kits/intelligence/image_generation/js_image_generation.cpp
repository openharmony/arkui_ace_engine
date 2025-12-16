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

#include "napi/native_api.h"
#include "napi/native_common.h"
#include "napi/native_node_api.h"
#include "base/utils/utils.h"
#include "base/error/error_code.h"

#include "bridge/declarative_frontend/engine/jsi/jsi_image_generator_dialog_view.h"

namespace OHOS::Ace::Napi {
namespace {
#define GET_PARAMS(env, info, max) \
    size_t argc = max;             \
    napi_value argv[max] = { 0 };  \
    napi_value thisVar = nullptr;  \
    void* data;                    \
    napi_get_cb_info(env, info, &argc, argv, &thisVar, &data)


// error code
constexpr int32_t CREATOR_IMAGES_OVERSIZE = 1;
constexpr int32_t CREATOR_CONTENT_OVERSIZE = 2;
constexpr int32_t CREATOR_INTERNAL_ERROR = 99;
// error message
constexpr char FIRST_ARG_TYPE_INCORRECT[] = "type of first param is incorrect!";
constexpr char IMAGES_INPUT_OVER_SIZE[] = "images input are oversize(larger than 4)!";
constexpr char CONTENT_INPUT_OVER_SIZE[] = "content input is oversize(larger than 600 character)!";
constexpr char INTERNAL_ERROR_MSG[] = "internal error, create canvas failed!";
constexpr char IMAGE_GENERATOR_DIALOG_CREATOR_FUNC[] = "__imageGeneratorDialogCreator";

napi_value CreateErrorValue(napi_env env, int32_t errCode, const std::string& errMsg = "")
{
    napi_value code = nullptr;
    std::string codeStr = std::to_string(errCode);
    napi_create_string_utf8(env, codeStr.c_str(), codeStr.length(), &code);
    napi_value msg = nullptr;
    napi_create_string_utf8(env, errMsg.c_str(), errMsg.length(), &msg);
    napi_value error = nullptr;
    napi_create_error(env, code, msg, &error);
    return error;
}

napi_value CreatePromise(napi_env env, int32_t errCode, const std::string& errMsg)
{
    CHECK_NULL_RETURN(env, nullptr);
    napi_deferred deferred = nullptr;
    napi_value promise = nullptr;
    napi_create_promise(env, &deferred, &promise);

    if (errCode != ERROR_CODE_NO_ERROR) {
        napi_value result = CreateErrorValue(env, errCode, errMsg);
        napi_reject_deferred(env, deferred, result);
    } else {
        napi_value result = nullptr;
        napi_get_undefined(env, &result);
        napi_resolve_deferred(env, deferred, result);
    }
    return promise;
}
}

static int32_t CallImageGeneratorCreator(napi_env env, napi_value options)
{
    napi_handle_scope scope = nullptr;
    napi_open_handle_scope(env, &scope);
    if (scope == nullptr) {
        return CREATOR_INTERNAL_ERROR;
    }
    napi_value globalValue;
    napi_get_global(env, &globalValue);
    napi_value imageGeneratorCreator;
    napi_get_named_property(env, globalValue, IMAGE_GENERATOR_DIALOG_CREATOR_FUNC, &imageGeneratorCreator);
    napi_value funcArgv[1] = { options };
    napi_value returnValue;
    if (napi_call_function(env, globalValue, imageGeneratorCreator, 1, funcArgv, &returnValue) != napi_ok) {
        TAG_LOGE(AceLogTag::ACE_SIDEBAR, "CallLoadImageGeneratorDialog failed");
        return CREATOR_INTERNAL_ERROR;
    }
    int32_t errorCode = CREATOR_INTERNAL_ERROR;
    if (napi_get_value_int32(env, returnValue, &errorCode) != napi_ok) {
        TAG_LOGE(AceLogTag::ACE_SIDEBAR, "parse error code failed when create image generator");
        return CREATOR_INTERNAL_ERROR;
    }
    return errorCode;
}

static napi_value JSShowGeneratorDialog(napi_env env, napi_callback_info info)
{
    GET_PARAMS(env, info, 2);
    NAPI_ASSERT(env, (argc >= 1), "Invalid argc");
    // parse uiContext start
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, argv[0], &valueType);
    if (valueType != napi_object) {
        return CreatePromise(env, ERROR_CODE_PARAM_INVALID, FIRST_ARG_TYPE_INCORRECT);
    }
    napi_value napiInstanceId = nullptr;
    napi_get_named_property(env, argv[0], "instanceId_", &napiInstanceId);
    int32_t instanceId = -1;
    if (napi_get_value_int32(env, napiInstanceId, &instanceId) != napi_ok) {
        TAG_LOGE(AceLogTag::ACE_SIDEBAR, "parse instanceId failed when create image generator");
        return CreatePromise(env, ERROR_CODE_INTERNAL_ERROR, INTERNAL_ERROR_MSG);
    }
    // parse uiContext finish
    napi_value options = argc == 2 ? argv[1] : nullptr;
    if (!Framework::ImageGeneratorDialogView::ExecuteImageGeneratorDialogAbc(-1)) {
        return CreatePromise(env, ERROR_CODE_INTERNAL_ERROR, INTERNAL_ERROR_MSG);
    }
    int32_t errorCode = CallImageGeneratorCreator(env, options);
    if (errorCode == CREATOR_IMAGES_OVERSIZE) {
        return CreatePromise(env, ERROR_CODE_PARAM_INVALID, IMAGES_INPUT_OVER_SIZE);
    }
    if (errorCode == CREATOR_CONTENT_OVERSIZE) {
        return CreatePromise(env, ERROR_CODE_PARAM_INVALID, CONTENT_INPUT_OVER_SIZE);
    }
    if (errorCode == CREATOR_INTERNAL_ERROR) {
        return CreatePromise(env, ERROR_CODE_INTERNAL_ERROR, INTERNAL_ERROR_MSG);
    }
    if (Framework::ImageGeneratorDialogView::Create(instanceId)) {
        return CreatePromise(env, ERROR_CODE_NO_ERROR, "");
    } else {
        return CreatePromise(env, ERROR_CODE_INTERNAL_ERROR, INTERNAL_ERROR_MSG);
    }
}

static napi_value Export(napi_env env, napi_value exports)
{
    napi_property_descriptor properties[] = { DECLARE_NAPI_FUNCTION(
        "showGeneratorDialog", JSShowGeneratorDialog) };

    NAPI_CALL(env, napi_define_properties(env, exports, sizeof(properties) / sizeof(properties[0]), properties));
    return exports;
}

static napi_module inspector_module = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = Export,
    .nm_modname = "arkui.intelligence.imageGeneration", // relative to the dynamic library's name
    .nm_priv = ((void*)0),
    .reserved = { 0 },
};

extern "C" __attribute__((constructor)) void RegisterInspector()
{
    napi_module_register(&inspector_module);
}
} // namespace OHOS::Ace::Napi
