/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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
#include "interfaces/napi/kits/napi_utils.h"
#include "bridge/common/utils/engine_helper.h"
#include "bridge/js_frontend/engine/common/js_engine.h"

namespace OHOS::Ace::Napi {
static int32_t HandleFontStyle(napi_value fontStyleNApi, napi_env env)
{
    size_t ret = 0;
    int32_t fontStyleInt = 0;
    std::string fontStyleStr;
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, fontStyleNApi, &valueType);
    if (valueType == napi_string) {
        size_t fontStyleLen = GetParamLen(fontStyleNApi) + 1;
        std::unique_ptr<char[]> fontStyleTemp = std::make_unique<char[]>(fontStyleLen);
        napi_get_value_string_utf8(env, fontStyleNApi, fontStyleTemp.get(), fontStyleLen, &ret);
        fontStyleStr = fontStyleTemp.get();
        fontStyleInt = StringUtils::StringToInt(fontStyleStr);
    } else if (valueType == napi_number) {
        napi_get_value_int32(env, fontStyleNApi, &fontStyleInt);
    } else if (valueType == napi_object) {
        int32_t id = 0;
        int32_t type = 0;
        std::vector<std::string> params;
        if (!ParseResourceParam(env, fontStyleNApi, id, type, params)) {
            LOGE("can not parse resource info from inout params.");
            return fontStyleInt;
        }
        if (!ParseString(id, type, params, fontStyleStr)) {
            LOGE("can not get message from resource manager.");
            return fontStyleInt;
        }
        fontStyleInt = StringUtils::StringToInt(fontStyleStr);
    } else {
        LOGE("The parameter type is incorrect.");
        return fontStyleInt;
    }
    return fontStyleInt;
}

static double HandleDoubleType(napi_value ParameterNApi, napi_env env)
{
    size_t ret = 0;
    double Parameter = 0.0;
    std::string ParameterStr;
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, ParameterNApi, &valueType);
    if (valueType == napi_number) {
        napi_get_value_double(env, ParameterNApi, &Parameter);
    } else if (valueType == napi_string) {
        size_t ParameterLen = GetParamLen(ParameterNApi) + 1;
        std::unique_ptr<char[]> ParameterTemp = std::make_unique<char[]>(ParameterLen);
        napi_get_value_string_utf8(env, ParameterNApi, ParameterTemp.get(), ParameterLen, &ret);
        ParameterStr = ParameterTemp.get();
        Parameter = StringUtils::StringToDouble(ParameterStr);
    } else if (valueType == napi_object) {
        int32_t id = 0;
        int32_t type = 0;
        std::vector<std::string> params;
        if (!ParseResourceParam(env, ParameterNApi, id, type, params)) {
            LOGE("can not parse resource info from inout params.");
            return Parameter;
        }
        if (!ParseString(id, type, params, ParameterStr)) {
            LOGE("can not get message from resource manager.");
            return Parameter;
        }
        Parameter = StringUtils::StringToDouble(ParameterStr);
    } else {
        LOGE("The parameter type is incorrect.");
        return Parameter;
    }
    return Parameter;
}

static std::string HandleStringType(napi_value ParameterNApi, napi_env env)
{
    size_t ret = 0;
    std::string ParameterStr;
    int32_t ParameterInt = 0;
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, ParameterNApi, &valueType);
    if (valueType == napi_string) {
        size_t ParameterLen = GetParamLen(ParameterNApi) + 1;
        std::unique_ptr<char[]> Parameter = std::make_unique<char[]>(ParameterLen);
        napi_get_value_string_utf8(env, ParameterNApi, Parameter.get(), ParameterLen, &ret);
        ParameterStr = Parameter.get();
    } else if (valueType == napi_number) {
        napi_get_value_int32(env, ParameterNApi, &ParameterInt);
        ParameterStr = std::to_string(ParameterInt);
    } else if (valueType == napi_object) {
        int32_t id = 0;
        int32_t type = 0;
        std::vector<std::string> params;
        if (!ParseResourceParam(env, ParameterNApi, id, type, params)) {
            LOGE("can not parse resource info from inout params.");
            return ParameterStr;
        }
        if (!ParseString(id, type, params, ParameterStr)) {
            LOGE("can not get message from resource manager.");
            return ParameterStr;
        }
    } else {
        LOGE("The parameter type is incorrect.");
        return ParameterStr;
    }
    return ParameterStr;
}

static napi_value JSMeasureText(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value result = nullptr;
    napi_value argv = nullptr;
    napi_value thisvar = nullptr;
    void* data = nullptr;
    napi_get_cb_info(env, info, &argc, &argv, &thisvar, &data);

    napi_value textContentNApi = nullptr;
    napi_value fontSizeNApi = nullptr;
    napi_value fontStyleNApi = nullptr;
    napi_value fontWeightNApi = nullptr;
    napi_value fontFamilyNApi = nullptr;
    napi_value letterSpacingNApi = nullptr;

    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, argv, &valueType);
    if (valueType == napi_object) {
        napi_get_named_property(env, argv, "textContent", &textContentNApi);
        napi_get_named_property(env, argv, "fontSize", &fontSizeNApi);
        napi_get_named_property(env, argv, "fontStyle", &fontStyleNApi);
        napi_get_named_property(env, argv, "fontWeight", &fontWeightNApi);
        napi_get_named_property(env, argv, "fontFamily", &fontFamilyNApi);
        napi_get_named_property(env, argv, "letterSpacing", &letterSpacingNApi);
    } else {
        return nullptr;
    }
    double fontSizeNum = HandleDoubleType(fontSizeNApi, env);
    double letterSpace = HandleDoubleType(letterSpacingNApi, env);
    int32_t fontStyle = HandleFontStyle(fontStyleNApi, env);
    std::string textContent = HandleStringType(textContentNApi, env);
    std::string fontWeight = HandleStringType(fontWeightNApi, env);
    std::string fontFamily = HandleStringType(fontFamilyNApi, env);
    auto delegate = EngineHelper::GetCurrentDelegate();
    if (!delegate) {
        return nullptr;
    }
    double textWidth =
        delegate->MeasureText(textContent, fontSizeNum, fontStyle, fontWeight, fontFamily, letterSpace);
    napi_create_double(env, textWidth, &result);
    return result;
}

static napi_value MeasureExport(napi_env env, napi_value exports)
{
    napi_property_descriptor measureDesc[] = {
        DECLARE_NAPI_FUNCTION("measureText", JSMeasureText),
    };
    NAPI_CALL(env, napi_define_properties(env, exports, sizeof(measureDesc) / sizeof(measureDesc[0]), measureDesc));
    return exports;
}

static napi_module measureModule = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = MeasureExport,
    .nm_modname = "measure",
    .nm_priv = ((void*)0),
    .reserved = { 0 },
};

extern "C" __attribute__((constructor)) void MeasureRegister()
{
    napi_module_register(&measureModule);
}
} // namespace OHOS::Ace::Napi

