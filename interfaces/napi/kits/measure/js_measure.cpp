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

#include <optional>
#include <string>

#include "interfaces/napi/kits/utils/napi_utils.h"
#include "js_native_api.h"
#include "js_native_api_types.h"
#include "napi/native_api.h"
#include "napi/native_engine/native_value.h"
#include "napi/native_node_api.h"

#include "base/geometry/dimension.h"
#include "base/geometry/size.h"
#include "bridge/common/utils/engine_helper.h"
#include "bridge/js_frontend/engine/common/js_engine.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/text_style.h"
#include "frameworks/base/utils/measure_util.h"

namespace OHOS::Ace::Napi {
static int32_t HandleIntStyle(napi_value fontStyleNApi, napi_env env)
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
        ResourceInfo recv;
        if (!ParseResourceParam(env, fontStyleNApi, recv)) {
            LOGE("can not parse resource info from inout params.");
            return fontStyleInt;
        }
        if (!ParseString(recv, fontStyleStr)) {
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
        ResourceInfo recv;
        if (!ParseResourceParam(env, ParameterNApi, recv)) {
            LOGE("can not parse resource info from inout params.");
            return ParameterStr;
        }
        if (!ParseString(recv, ParameterStr)) {
            LOGE("can not get message from resource manager.");
            return ParameterStr;
        }
    } else {
        LOGE("The parameter type is incorrect.");
        return ParameterStr;
    }
    return ParameterStr;
}

static std::optional<Dimension> HandleDimensionType(napi_value ParameterNApi, napi_env env)
{
    size_t ret = 0;
    std::string ParameterStr;
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, ParameterNApi, &valueType);
    Dimension Parameter;
    if (valueType == napi_number) {
        double ParameterValue;
        napi_get_value_double(env, ParameterNApi, &ParameterValue);
        Parameter.SetValue(ParameterValue);
        Parameter.SetUnit(DimensionUnit::VP);
    } else if (valueType == napi_string) {
        size_t ParameterLen = GetParamLen(ParameterNApi) + 1;
        std::unique_ptr<char[]> ParameterTemp = std::make_unique<char[]>(ParameterLen);
        napi_get_value_string_utf8(env, ParameterNApi, ParameterTemp.get(), ParameterLen, &ret);
        ParameterStr = ParameterTemp.get();
        Parameter = StringUtils::StringToDimensionWithUnit(ParameterStr, DimensionUnit::VP);
    } else if (valueType == napi_object) {
        ResourceInfo recv;
        if (!ParseResourceParam(env, ParameterNApi, recv)) {
            LOGE("can not parse resource info from inout params.");
            return std::nullopt;
        }
        if (!ParseString(recv, ParameterStr)) {
            LOGE("can not get message from resource manager.");
            return std::nullopt;
        }
        Parameter = StringUtils::StringToDimensionWithUnit(ParameterStr, DimensionUnit::VP);
    } else {
        return std::nullopt;
    }
    return Parameter;
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
    std::optional<Dimension> fontSizeNum = HandleDimensionType(fontSizeNApi, env);
    std::optional<Dimension> letterSpace = HandleDimensionType(letterSpacingNApi, env);
    int32_t fontStyle = HandleIntStyle(fontStyleNApi, env);
    std::string textContent = HandleStringType(textContentNApi, env);
    std::string fontWeight = HandleStringType(fontWeightNApi, env);
    std::string fontFamily = HandleStringType(fontFamilyNApi, env);
    MeasureContext context;
    context.textContent = textContent;
    context.fontSize = fontSizeNum;
    context.fontStyle = static_cast<FontStyle>(fontStyle);
    context.fontWeight = fontWeight;
    context.fontFamily = fontFamily;
    context.letterSpacing = letterSpace;
    auto delegate = EngineHelper::GetCurrentDelegate();
    if (!delegate) {
        return nullptr;
    }
    double textWidth = delegate->MeasureText(context);
    napi_create_double(env, textWidth, &result);
    return result;
}

static napi_value JSMeasureTextSize(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value result = nullptr;
    napi_value argv = nullptr;
    napi_value thisvar = nullptr;
    void* data = nullptr;
    napi_get_cb_info(env, info, &argc, &argv, &thisvar, &data);

    napi_value textContentNApi = nullptr;
    napi_value constraintWidthNApi = nullptr;
    napi_value fontSizeNApi = nullptr;
    napi_value fontStyleNApi = nullptr;
    napi_value fontWeightNApi = nullptr;
    napi_value fontFamilyNApi = nullptr;
    napi_value letterSpacingNApi = nullptr;
    napi_value textAlignNApi = nullptr;
    napi_value textOverFlowNApi = nullptr;
    napi_value maxLinesNApi = nullptr;
    napi_value lineHeightNApi = nullptr;
    napi_value baselineOffsetNApi = nullptr;
    napi_value textCaseNApi = nullptr;

    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, argv, &valueType);
    MeasureContext context;
    if (valueType == napi_object) {
        napi_get_named_property(env, argv, "textContent", &textContentNApi);
        napi_get_named_property(env, argv, "constraintWidth", &constraintWidthNApi);
        napi_get_named_property(env, argv, "fontSize", &fontSizeNApi);
        napi_get_named_property(env, argv, "fontStyle", &fontStyleNApi);
        napi_get_named_property(env, argv, "fontWeight", &fontWeightNApi);
        napi_get_named_property(env, argv, "fontFamily", &fontFamilyNApi);
        napi_get_named_property(env, argv, "letterSpacing", &letterSpacingNApi);
        napi_get_named_property(env, argv, "textAlign", &textAlignNApi);
        napi_get_named_property(env, argv, "overflow", &textOverFlowNApi);
        napi_get_named_property(env, argv, "maxLines", &maxLinesNApi);
        napi_get_named_property(env, argv, "lineHeight", &lineHeightNApi);
        napi_get_named_property(env, argv, "baselineOffset", &baselineOffsetNApi);
        napi_get_named_property(env, argv, "textCase", &textCaseNApi);
    } else {
        return nullptr;
    }
    std::optional<Dimension> fontSizeNum = HandleDimensionType(fontSizeNApi, env);
    std::optional<Dimension> letterSpace = HandleDimensionType(letterSpacingNApi, env);
    std::optional<Dimension> constraintWidth = HandleDimensionType(constraintWidthNApi, env);
    std::optional<Dimension> lineHeight = HandleDimensionType(lineHeightNApi, env);
    std::optional<Dimension> baselineOffset = HandleDimensionType(baselineOffsetNApi, env);
    int32_t fontStyle = HandleIntStyle(fontStyleNApi, env);
    int32_t textAlign = HandleIntStyle(textAlignNApi, env);
    int32_t textOverFlow = HandleIntStyle(textOverFlowNApi, env);
    int32_t maxlines = HandleIntStyle(maxLinesNApi, env);
    int32_t textCase = HandleIntStyle(textCaseNApi, env);
    std::string textContent = HandleStringType(textContentNApi, env);
    std::string fontWeight = HandleStringType(fontWeightNApi, env);
    std::string fontFamily = HandleStringType(fontFamilyNApi, env);
    context.textContent = textContent;
    context.constraintWidth = constraintWidth;
    context.fontSize = fontSizeNum;
    context.fontStyle = static_cast<FontStyle>(fontStyle);
    context.fontWeight = fontWeight;
    context.fontFamily = fontFamily;
    context.letterSpacing = letterSpace;
    context.textAlign = static_cast<TextAlign>(textAlign);
    context.textOverlayFlow = static_cast<TextOverflow>(textOverFlow);
    context.maxlines = maxlines;
    context.lineHeight = lineHeight;
    context.baselineOffset = baselineOffset;
    context.textCase = static_cast<TextCase>(textCase);
    auto delegate = EngineHelper::GetCurrentDelegate();
    if (!delegate) {
        return nullptr;
    }
    Size textSize = delegate->MeasureTextSize(context);

    napi_escapable_handle_scope scope = nullptr;
    napi_open_escapable_handle_scope(env, &scope);
    if (scope == nullptr) {
        return result;
    }

    napi_value resultArray[2] = { 0 };
    napi_create_double(env, textSize.Width(), &resultArray[0]);
    napi_create_double(env, textSize.Height(), &resultArray[1]);

    napi_create_object(env, &result);
    napi_set_named_property(env, result, "width", resultArray[0]);
    napi_set_named_property(env, result, "height", resultArray[1]);

    napi_value newResult = nullptr;
    napi_escape_handle(env, scope, result, &newResult);
    napi_close_escapable_handle_scope(env, scope);
    return result;
}

static napi_value MeasureExport(napi_env env, napi_value exports)
{
    napi_property_descriptor measureDesc[] = {
        DECLARE_NAPI_FUNCTION("measureText", JSMeasureText),
        DECLARE_NAPI_FUNCTION("measureTextSize", JSMeasureTextSize),
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
