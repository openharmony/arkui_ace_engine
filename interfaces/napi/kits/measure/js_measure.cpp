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


#include "interfaces/napi/kits/utils/napi_utils.h"

#include "bridge/common/utils/engine_helper.h"

extern const char _binary_measure_js_start[];
extern const char _binary_measure_abc_start[];
#if !defined(IOS_PLATFORM)
extern const char _binary_measure_js_end[];
extern const char _binary_measure_abc_end[];
#else
extern const char* _binary_measure_js_end;
extern const char* _binary_measure_abc_end;
#endif

namespace OHOS::Ace::Napi {
namespace {
Dimension MeasureStringToDimensionWithUnit(const std::string& value, bool& useDefaultUnit,
    DimensionUnit defaultUnit = DimensionUnit::PX, float defaultValue = 0.0f, bool isCalc = false)
{
    errno = 0;
    if (std::strcmp(value.c_str(), "auto") == 0) {
        return Dimension(defaultValue, DimensionUnit::AUTO);
    }
    char* pEnd = nullptr;
    double result = std::strtod(value.c_str(), &pEnd);
    if (pEnd == value.c_str() || errno == ERANGE) {
        useDefaultUnit = true;
        return Dimension(defaultValue, defaultUnit);
    }
    if (pEnd != nullptr) {
        if (std::strcmp(pEnd, "%") == 0) {
            // Parse percent, transfer from [0, 100] to [0, 1]
            return Dimension(result / 100.0, DimensionUnit::PERCENT);
        }
        if (std::strcmp(pEnd, "px") == 0) {
            return Dimension(result, DimensionUnit::PX);
        }
        if (std::strcmp(pEnd, "vp") == 0) {
            return Dimension(result, DimensionUnit::VP);
        }
        if (std::strcmp(pEnd, "fp") == 0) {
            return Dimension(result, DimensionUnit::FP);
        }
        if (std::strcmp(pEnd, "lpx") == 0) {
            return Dimension(result, DimensionUnit::LPX);
        }
        if ((std::strcmp(pEnd, "\0") == 0) && isCalc) {
            return Dimension(result, DimensionUnit::NONE);
        }
        if (isCalc) {
            return Dimension(result, DimensionUnit::INVALID);
        }
    }
    useDefaultUnit = true;
    return Dimension(result, defaultUnit);
}
} // namespace
static int32_t HandleIntStyle(napi_value fontStyleNApi, napi_env env)
{
    size_t ret = 0;
    int32_t fontStyleInt = 0;
    std::string fontStyleStr;
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, fontStyleNApi, &valueType);
    if (valueType == napi_string) {
        size_t fontStyleLen = GetParamLen(env, fontStyleNApi) + 1;
        std::unique_ptr<char[]> fontStyleTemp = std::make_unique<char[]>(fontStyleLen);
        napi_get_value_string_utf8(env, fontStyleNApi, fontStyleTemp.get(), fontStyleLen, &ret);
        fontStyleStr = fontStyleTemp.get();
        fontStyleInt = StringUtils::StringToInt(fontStyleStr);
    } else if (valueType == napi_number) {
        napi_get_value_int32(env, fontStyleNApi, &fontStyleInt);
    } else if (valueType == napi_object) {
        ResourceInfo recv;
        if (!ParseResourceParam(env, fontStyleNApi, recv)) {
            return fontStyleInt;
        }
        if (!ParseString(recv, fontStyleStr)) {
            return fontStyleInt;
        }
        fontStyleInt = StringUtils::StringToInt(fontStyleStr);
    } else {
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
        size_t ParameterLen = GetParamLen(env, ParameterNApi) + 1;
        std::unique_ptr<char[]> Parameter = std::make_unique<char[]>(ParameterLen);
        napi_get_value_string_utf8(env, ParameterNApi, Parameter.get(), ParameterLen, &ret);
        ParameterStr = Parameter.get();
    } else if (valueType == napi_number) {
        napi_get_value_int32(env, ParameterNApi, &ParameterInt);
        ParameterStr = std::to_string(ParameterInt);
    } else if (valueType == napi_object) {
        ResourceInfo recv;
        if (!ParseResourceParam(env, ParameterNApi, recv)) {
            return ParameterStr;
        }
        if (!ParseString(recv, ParameterStr)) {
            return ParameterStr;
        }
    } else {
        return ParameterStr;
    }
    return ParameterStr;
}

static std::optional<Dimension> HandleDimensionType(
    napi_value ParameterNApi, napi_env env, DimensionUnit defaultUnit, bool& useDefaultUnit)
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
        Parameter.SetUnit(defaultUnit);
        useDefaultUnit = true;
    } else if (valueType == napi_string) {
        size_t ParameterLen = GetParamLen(env, ParameterNApi) + 1;
        std::unique_ptr<char[]> ParameterTemp = std::make_unique<char[]>(ParameterLen);
        napi_get_value_string_utf8(env, ParameterNApi, ParameterTemp.get(), ParameterLen, &ret);
        ParameterStr = ParameterTemp.get();
        Parameter = MeasureStringToDimensionWithUnit(ParameterStr, useDefaultUnit, defaultUnit);
    } else if (valueType == napi_object) {
        ResourceInfo recv;
        if (!ParseResourceParam(env, ParameterNApi, recv)) {
            return std::nullopt;
        }
        if (!ParseString(recv, ParameterStr)) {
            return std::nullopt;
        }
        if (!ParseIntegerToString(recv, ParameterStr)) {
            return std::nullopt;
        }
        Parameter = MeasureStringToDimensionWithUnit(ParameterStr, useDefaultUnit, defaultUnit);
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
    MeasureContext context;
    auto isFontSizeUseDefaultUnit = false;
    std::optional<Dimension> fontSizeNum =
        HandleDimensionType(fontSizeNApi, env, DimensionUnit::FP, isFontSizeUseDefaultUnit);
    context.isFontSizeUseDefaultUnit = isFontSizeUseDefaultUnit;
    std::optional<Dimension> letterSpace =
        HandleDimensionType(letterSpacingNApi, env, DimensionUnit::VP, isFontSizeUseDefaultUnit);
    int32_t fontStyle = HandleIntStyle(fontStyleNApi, env);
    std::string textContent = HandleStringType(textContentNApi, env);
    std::string fontWeight = HandleStringType(fontWeightNApi, env);
    std::string fontFamily = HandleStringType(fontFamilyNApi, env);
    context.textContent = textContent;
    context.fontSize = fontSizeNum;
    context.fontStyle = static_cast<FontStyle>(fontStyle);
    context.fontWeight = fontWeight;
    context.fontFamily = fontFamily;
    context.letterSpacing = letterSpace;
    auto delegate = EngineHelper::GetCurrentDelegateSafely();
    if (!delegate) {
        return nullptr;
    }
    double textWidth = delegate->MeasureText(context);
    napi_create_double(env, textWidth, &result);
    return result;
}

static void CreateMeasureTextSizeParamMap(std::map<std::string, napi_value>& contextParamMap)
{
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
    napi_value textIndentNApi = nullptr;
    napi_value wordBreakNApi = nullptr;
    contextParamMap["textContentNApi"] = textContentNApi;
    contextParamMap["constraintWidthNApi"] = constraintWidthNApi;
    contextParamMap["fontSizeNApi"] = fontSizeNApi;
    contextParamMap["fontStyleNApi"] = fontStyleNApi;
    contextParamMap["fontWeightNApi"] = fontWeightNApi;
    contextParamMap["fontFamilyNApi"] = fontFamilyNApi;
    contextParamMap["letterSpacingNApi"] = letterSpacingNApi;
    contextParamMap["textAlignNApi"] = textAlignNApi;
    contextParamMap["textOverFlowNApi"] = textOverFlowNApi;
    contextParamMap["maxLinesNApi"] = maxLinesNApi;
    contextParamMap["lineHeightNApi"] = lineHeightNApi;
    contextParamMap["baselineOffsetNApi"] = baselineOffsetNApi;
    contextParamMap["textCaseNApi"] = textCaseNApi;
    contextParamMap["textIndentNApi"] = textIndentNApi;
    contextParamMap["wordBreakNApi"] = wordBreakNApi;
}

static void SetMeasureTextNapiProperty(
    std::map<std::string, napi_value>& contextParamMap, napi_value& argv, napi_env& env)
{
    napi_get_named_property(env, argv, "textContent", &contextParamMap["textContentNApi"]);
    napi_get_named_property(env, argv, "constraintWidth", &contextParamMap["constraintWidthNApi"]);
    napi_get_named_property(env, argv, "fontSize", &contextParamMap["fontSizeNApi"]);
    napi_get_named_property(env, argv, "fontStyle", &contextParamMap["fontStyleNApi"]);
    napi_get_named_property(env, argv, "fontWeight", &contextParamMap["fontWeightNApi"]);
    napi_get_named_property(env, argv, "fontFamily", &contextParamMap["fontFamilyNApi"]);
    napi_get_named_property(env, argv, "letterSpacing", &contextParamMap["letterSpacingNApi"]);
    napi_get_named_property(env, argv, "textAlign", &contextParamMap["textAlignNApi"]);
    napi_get_named_property(env, argv, "overflow", &contextParamMap["textOverFlowNApi"]);
    napi_get_named_property(env, argv, "maxLines", &contextParamMap["maxLinesNApi"]);
    napi_get_named_property(env, argv, "lineHeight", &contextParamMap["lineHeightNApi"]);
    napi_get_named_property(env, argv, "baselineOffset", &contextParamMap["baselineOffsetNApi"]);
    napi_get_named_property(env, argv, "textCase", &contextParamMap["textCaseNApi"]);
    napi_get_named_property(env, argv, "textIndent", &contextParamMap["textIndentNApi"]);
    bool hasElement = false;
    napi_has_named_property(env, argv, "wordBreak", &hasElement);
    if (hasElement) {
        napi_get_named_property(env, argv, "wordBreak", &contextParamMap["wordBreakNApi"]);
    }
}

static void SetContextProperty(
    std::map<std::string, napi_value>& contextParamMap, MeasureContext& context, napi_env& env)
{
    auto isFontSizeUseDefaultUnit = false;
    std::optional<Dimension> fontSizeNum =
        HandleDimensionType(contextParamMap["fontSizeNApi"], env, DimensionUnit::FP, isFontSizeUseDefaultUnit);
    context.isFontSizeUseDefaultUnit = isFontSizeUseDefaultUnit;
    std::optional<Dimension> letterSpace =
        HandleDimensionType(contextParamMap["letterSpacingNApi"], env, DimensionUnit::VP, isFontSizeUseDefaultUnit);
    std::optional<Dimension> constraintWidth =
        HandleDimensionType(contextParamMap["constraintWidthNApi"], env, DimensionUnit::VP, isFontSizeUseDefaultUnit);
    std::optional<Dimension> lineHeight =
        HandleDimensionType(contextParamMap["lineHeightNApi"], env, DimensionUnit::VP, isFontSizeUseDefaultUnit);
    std::optional<Dimension> baselineOffset =
        HandleDimensionType(contextParamMap["baselineOffsetNApi"], env, DimensionUnit::VP, isFontSizeUseDefaultUnit);
    std::optional<Dimension> textIndent =
        HandleDimensionType(contextParamMap["textIndentNApi"], env, DimensionUnit::VP, isFontSizeUseDefaultUnit);

    int32_t fontStyle = HandleIntStyle(contextParamMap["fontStyleNApi"], env);
    int32_t textAlign = HandleIntStyle(contextParamMap["textAlignNApi"], env);
    int32_t textOverFlow = HandleIntStyle(contextParamMap["textOverFlowNApi"], env);
    int32_t maxlines = HandleIntStyle(contextParamMap["maxLinesNApi"], env);
    int32_t textCase = HandleIntStyle(contextParamMap["textCaseNApi"], env);

    if (contextParamMap["wordBreakNApi"] != nullptr) {
        napi_valuetype jsValueType = napi_undefined;
        napi_typeof(env, contextParamMap["wordBreakNApi"], &jsValueType);
        if (jsValueType != napi_undefined) {
            int32_t wordBreak = HandleIntStyle(contextParamMap["wordBreakNApi"], env);
            context.wordBreak = static_cast<WordBreak>(wordBreak);
        }
    }

    std::string textContent = HandleStringType(contextParamMap["textContentNApi"], env);
    std::string fontWeight = HandleStringType(contextParamMap["fontWeightNApi"], env);
    std::string fontFamily = HandleStringType(contextParamMap["fontFamilyNApi"], env);

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
    context.textIndent = textIndent;
}

static napi_value JSMeasureTextSize(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value result = nullptr;
    napi_value argv = nullptr;
    napi_value thisvar = nullptr;
    void* data = nullptr;
    napi_get_cb_info(env, info, &argc, &argv, &thisvar, &data);

    std::map<std::string, napi_value> contextParamMap;
    CreateMeasureTextSizeParamMap(contextParamMap);
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, argv, &valueType);
    MeasureContext context;
    if (valueType == napi_object) {
        SetMeasureTextNapiProperty(contextParamMap, argv, env);
    } else {
        return nullptr;
    }
    SetContextProperty(contextParamMap, context, env);
    auto delegate = EngineHelper::GetCurrentDelegateSafely();
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

extern "C" __attribute__((visibility("default"))) void NAPI_measure_GetJSCode(const char** buf, int* bufLen)
{
    if (buf != nullptr) {
        *buf = _binary_measure_js_start;
    }

    if (bufLen != nullptr) {
        *bufLen = _binary_measure_js_end - _binary_measure_js_start;
    }
}

extern "C" __attribute__((visibility("default"))) void NAPI_measure_GetABCCode(const char** buf, int* buflen)
{
    if (buf != nullptr) {
        *buf = _binary_measure_abc_start;
    }
    if (buflen != nullptr) {
        *buflen = _binary_measure_abc_end - _binary_measure_abc_start;
    }
}

static napi_module_with_js measureModule = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = "libmeasure.z.so/measure.js",
    .nm_register_func = MeasureExport,
    .nm_modname = "measure",
    .nm_priv = ((void*)0),
    .nm_get_abc_code = NAPI_measure_GetABCCode,
    .nm_get_js_code = NAPI_measure_GetJSCode,
};

extern "C" __attribute__((constructor)) void MeasureRegister()
{
    napi_module_with_js_register(&measureModule);
}
} // namespace OHOS::Ace::Napi
