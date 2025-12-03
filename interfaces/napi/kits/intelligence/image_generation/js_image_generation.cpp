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

#include "napi/native_api.h"
#include "napi/native_common.h"
#include "napi/native_node_api.h"
#include "base/error/error_code.h"

#include "core/components_ng/pattern/image_generator_dialog/image_generator_dialog_view.h"

namespace OHOS::Ace::Napi {
namespace {
#define GET_PARAMS(env, info, max) \
    size_t argc = max;             \
    napi_value argv[max] = { 0 };  \
    napi_value thisVar = nullptr;  \
    void* data;                    \
    napi_get_cb_info(env, info, &argc, argv, &thisVar, &data)

constexpr uint32_t IMAGES_INPUT_MAX_COUNT = 4;
constexpr size_t CONTENT_INPUT_MAX_SIZE = 600;
constexpr char FIRST_ARG_TYPE_INCORRECT[] = "type of first param is incorrect!";
constexpr char SECOND_ARG_TYPE_INCORRECT[] = "type of second param is incorrect!";
constexpr char IMAGES_INPUT_OVER_SIZE[] = "images input are oversize(larger than 4)!";
constexpr char CONTENT_INPUT_OVER_SIZE[] = "content input is oversize(larger than 600 character)!";
constexpr char INTERNAL_ERROR_MSG[] = "internal error, create canvas failed!";

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

static napi_value JSShowGeneratorDialog(napi_env env, napi_callback_info info)
{
    std::string optionStr = "__NA__";

    GET_PARAMS(env, info, 2);

    NAPI_ASSERT(env, (argc >= 1), "Invalid argc");

    // parse uiContext start
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, argv[0], &valueType);
    if (valueType == napi_undefined || valueType != napi_object) {
        // >>>>------ NOT IMPL YET ------<<<<
        return CreatePromise(env, ERROR_CODE_PARAM_INVALID, FIRST_ARG_TYPE_INCORRECT);
    }
    // parse uiContext finish
    // parse options start
    if (argc == 2) {
        napi_typeof(env, argv[1], &valueType);
        if (valueType == napi_undefined || valueType != napi_object) {
            return CreatePromise(env, ERROR_CODE_PARAM_INVALID, SECOND_ARG_TYPE_INCORRECT);
        }
        napi_value generatorDialogOptions = argv[1];
        napi_value imagesNapi = nullptr;
        if (napi_get_named_property(env, generatorDialogOptions, "images", &imagesNapi) == napi_ok) {
            uint32_t length = 0;
            napi_get_array_length(env, imagesNapi, &length);
            if (length > IMAGES_INPUT_MAX_COUNT) {
                return CreatePromise(env, ERROR_CODE_PARAM_INVALID, IMAGES_INPUT_OVER_SIZE);
            }
        }
        napi_value contentNapi = nullptr;
        if (napi_get_named_property(env, generatorDialogOptions, "content", &contentNapi) == napi_ok) {
            size_t size = 0;
            napi_get_value_string_utf8(env, contentNapi, nullptr, 0, &size);
            if (size > CONTENT_INPUT_MAX_SIZE) {
                return CreatePromise(env, ERROR_CODE_PARAM_INVALID, CONTENT_INPUT_OVER_SIZE);
            }
        }
    }
    // parse options finish
    auto isSuccess = NG::ImageGeneratorDialogView::Create(optionStr, -1);
    TAG_LOGE(AceLogTag::ACE_SIDEBAR, "create canvas %{public}s", isSuccess ? "success" : "failed");
    if (isSuccess) {
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
