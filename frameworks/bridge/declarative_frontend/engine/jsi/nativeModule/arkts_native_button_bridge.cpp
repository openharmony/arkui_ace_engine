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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_button_bridge.h"

#include "base/geometry/dimension.h"
#include "core/interfaces/native/node/api.h"
#include "core/components/common/properties/text_style.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_common_bridge.h"
#include "core/components_ng/pattern/button/button_request_data.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"

namespace OHOS::Ace::NG {
const std::vector<TextOverflow> TEXT_OVERFLOWS = { TextOverflow::NONE, TextOverflow::CLIP, TextOverflow::ELLIPSIS,
    TextOverflow::MARQUEE };
const std::vector<Ace::FontStyle> FONT_STYLES = { Ace::FontStyle::NORMAL, Ace::FontStyle::ITALIC };
const std::vector<TextHeightAdaptivePolicy> HEIGHT_ADAPTIVE_POLICY = { TextHeightAdaptivePolicy::MAX_LINES_FIRST,
    TextHeightAdaptivePolicy::MIN_FONT_SIZE_FIRST, TextHeightAdaptivePolicy::LAYOUT_CONSTRAINT_FIRST };
const std::string DEFAULT_FONT_WEIGHT = "400";
const std::string NONE_FONT_FAMILY = "NoneFontFamily";
constexpr int32_t CALL_ARG_0 = 0;
constexpr int32_t CALL_ARG_1 = 1;
constexpr int32_t CALL_ARG_2 = 2;
constexpr int32_t CALL_ARG_3 = 3;
constexpr int32_t CALL_ARG_4 = 4;
constexpr int32_t MAX_LINES_ARG_2 = 2;
constexpr int32_t MIN_FONT_SIZE_ARG_3 = 3;
constexpr int32_t MAX_FONT_SIZE_ARG_4 = 4;
constexpr int32_t ADAPT_HEIGHT_ARG_5 = 5;
constexpr int32_t FONT_SIZE_ARG_6 = 6;
constexpr int32_t FONT_WEIGHT_ARG_7 = 7;
constexpr int32_t FONT_STYLE_ARG_8 = 8;
constexpr int32_t FONT_FAMILY_ARG_9 = 9;

ArkUINativeModuleValue ButtonBridge::SetType(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    int type = secondArg->Int32Value(vm);
    GetArkUIInternalNodeAPI()->GetButtonModifier().SetButtonType(nativeNode, type);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ButtonBridge::ResetType(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetButtonModifier().ResetButtonType(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ButtonBridge::SetStateEffect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    if (secondArg->IsBoolean()) {
        bool stateEffect = secondArg->ToBoolean(vm)->Value();
        GetArkUIInternalNodeAPI()->GetButtonModifier().SetButtonStateEffect(nativeNode, stateEffect);
    } else {
        GetArkUIInternalNodeAPI()->GetButtonModifier().ResetButtonStateEffect(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ButtonBridge::ResetStateEffect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetButtonModifier().ResetButtonStateEffect(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ButtonBridge::SetFontColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    Color color;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color)) {
        GetArkUIInternalNodeAPI()->GetButtonModifier().ResetButtonFontColor(nativeNode);
    } else {
        GetArkUIInternalNodeAPI()->GetButtonModifier().SetButtonFontColor(nativeNode, color.GetValue());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ButtonBridge::ResetFontColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetButtonModifier().ResetButtonFontColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ButtonBridge::SetFontSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    Ace::CalcDimension fontSize;
    if (ArkTSUtils::ParseJsDimensionVpNG(vm, secondArg, fontSize) && fontSize.Unit() != DimensionUnit::PERCENT &&
        GreatOrEqual(fontSize.Value(), 0.0)) {
        ArkTSUtils::ParseJsDimensionFp(vm, secondArg, fontSize);
    } else {
        auto pipeline = PipelineBase::GetCurrentContext();
        CHECK_NULL_RETURN(pipeline, panda::NativePointerRef::New(vm, nullptr));
        auto buttonTheme = pipeline->GetTheme<ButtonTheme>();
        CHECK_NULL_RETURN(buttonTheme, panda::NativePointerRef::New(vm, nullptr));
        fontSize = buttonTheme->GetTextStyle().GetFontSize();
    }
    int fontSizeUnit = static_cast<int>(fontSize.Unit());
    GetArkUIInternalNodeAPI()->GetButtonModifier().SetButtonFontSize(nativeNode, fontSize.Value(), fontSizeUnit);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ButtonBridge::ResetFontSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetButtonModifier().ResetButtonFontSize(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ButtonBridge::SetFontWeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> fontWeightArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    std::string fontWeight = DEFAULT_FONT_WEIGHT;
    if (!fontWeightArg->IsNull()) {
        if (fontWeightArg->IsNumber()) {
            fontWeight = std::to_string(fontWeightArg->Int32Value(vm));
        } else if (fontWeightArg->IsString()) {
            // enum FontWeight is string.
            fontWeight = fontWeightArg->ToString(vm)->ToString();
        }
    }
    GetArkUIInternalNodeAPI()->GetButtonModifier().SetButtonFontWeight(nativeNode, fontWeight.c_str());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ButtonBridge::ResetFontWeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetButtonModifier().ResetButtonFontWeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ButtonBridge::SetFontStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    int fontStyle = secondArg->Int32Value(vm);
    GetArkUIInternalNodeAPI()->GetButtonModifier().SetButtonFontStyle(nativeNode, fontStyle);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ButtonBridge::ResetFontStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetButtonModifier().ResetButtonFontStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ButtonBridge::SetFontFamily(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    std::string fontFamily;
    if (!ArkTSUtils::ParseJsFontFamiliesToString(vm, secondArg, fontFamily)) {
        GetArkUIInternalNodeAPI()->GetButtonModifier().ResetButtonFontFamily(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    GetArkUIInternalNodeAPI()->GetButtonModifier().SetButtonFontFamily(nativeNode, fontFamily.c_str());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ButtonBridge::ResetFontFamily(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetButtonModifier().ResetButtonFontFamily(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ButtonBridge::SetBackgroundColor(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    Color color;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color)) {
        GetArkUIInternalNodeAPI()->GetButtonModifier().ResetButtonBackgroundColor(nativeNode);
    } else {
        GetArkUIInternalNodeAPI()->GetButtonModifier().SetButtonBackgroundColor(nativeNode, color.GetValue());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ButtonBridge::ResetBackgroundColor(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void *nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetButtonModifier().ResetButtonBackgroundColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

void ButtonBridge::PushValuesVector(const std::optional<int32_t>& value, std::vector<int32_t>& valuesVector)
{
    valuesVector.push_back(static_cast<int32_t>(value.has_value()));
    if (value.has_value()) {
        valuesVector.push_back(static_cast<int32_t>(value.value()));
    } else {
        valuesVector.push_back(0);
    }
}

void ButtonBridge::PutButtonValuesParameters(
    ArkUIRuntimeCallInfo* runtimeCallInfo, EcmaVM* vm, std::vector<int32_t>& valuesVector)
{
    std::optional<int32_t> overflowOptional = std::nullopt;
    Local<JSValueRef> overflowArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    if (!overflowArg->IsNull() && overflowArg->IsNumber()) {
        auto overflow = overflowArg->Int32Value(vm);
        if (overflow >= 0 && overflow < static_cast<int32_t>(TEXT_OVERFLOWS.size())) {
            overflowOptional = overflow;
        }
    }
    PushValuesVector(overflowOptional, valuesVector);

    std::optional<int32_t> maxLinesOptional = std::nullopt;
    Local<JSValueRef> maxLinesArg = runtimeCallInfo->GetCallArgRef(MAX_LINES_ARG_2);
    if (!maxLinesArg->IsNull() && maxLinesArg->IsNumber()) {
        auto maxLines = maxLinesArg->Int32Value(vm);
        maxLinesOptional = Positive(maxLines) ? maxLines : 1;
    }
    PushValuesVector(maxLinesOptional, valuesVector);

    std::optional<int32_t> adaptHeightOptional = std::nullopt;
    Local<JSValueRef> adaptHeightArg = runtimeCallInfo->GetCallArgRef(ADAPT_HEIGHT_ARG_5);
    if (!adaptHeightArg->IsNull() && adaptHeightArg->IsNumber()) {
        auto adaptHeight = adaptHeightArg->Int32Value(vm);
        if (adaptHeight >= 0 && adaptHeight < static_cast<double>(HEIGHT_ADAPTIVE_POLICY.size())) {
            adaptHeightOptional = adaptHeight;
        }
    }
    PushValuesVector(adaptHeightOptional, valuesVector);

    std::optional<int32_t> fontStyleOptional = std::nullopt;
    Local<JSValueRef> fontStyleArg = runtimeCallInfo->GetCallArgRef(FONT_STYLE_ARG_8);
    if (!fontStyleArg->IsNull() && fontStyleArg->IsNumber()) {
        auto fontStyle = fontStyleArg->Int32Value(vm);
        if (fontStyle >= 0 && fontStyle < static_cast<int32_t>(FONT_STYLES.size())) {
            fontStyleOptional = fontStyle;
        }
    }
    PushValuesVector(fontStyleOptional, valuesVector);
}

void ButtonBridge::PushDimensionVector(const std::optional<Dimension>& valueDimen, std::vector<double>& dimensions)
{
    dimensions.push_back(static_cast<double>(valueDimen.has_value()));
    if (valueDimen.has_value()) {
        dimensions.push_back(static_cast<double>(valueDimen.value().Value()));
        dimensions.push_back(static_cast<double>(valueDimen.value().Unit()));
    } else {
        dimensions.push_back(0);
        dimensions.push_back(0);
    }
}

void ButtonBridge::PushButtonDimension(
    ArkUIRuntimeCallInfo* runtimeCallInfo, EcmaVM* vm, std::vector<double>& fontSizesVector, int32_t argIndex)
{
    Local<JSValueRef> arg = runtimeCallInfo->GetCallArgRef(argIndex);
    std::optional<CalcDimension> dimemstionOptinal = std::nullopt;
    CalcDimension parsedDimension;
    if (ArkTSUtils::ParseJsDimensionFp(vm, arg, parsedDimension, false)) {
        dimemstionOptinal = parsedDimension;
    }
    PushDimensionVector(dimemstionOptinal, fontSizesVector);
}

void ButtonBridge::PutButtonDimensionParameters(
    ArkUIRuntimeCallInfo* runtimeCallInfo, EcmaVM* vm, std::vector<double>& fontSizesVector)
{
    std::vector<int32_t> indexVector = { MIN_FONT_SIZE_ARG_3, MAX_FONT_SIZE_ARG_4, FONT_SIZE_ARG_6 };
    for (size_t index = 0; index < indexVector.size(); index++) {
        PushButtonDimension(runtimeCallInfo, vm, fontSizesVector, indexVector[index]);
    }
}

void ButtonBridge::PutButtonStringParameters(
    ArkUIRuntimeCallInfo* runtimeCallInfo, EcmaVM* vm, std::vector<const char*>& stringParameters)
{
    std::vector<std::string> stringsVector;
    Local<JSValueRef> fontWeightArg = runtimeCallInfo->GetCallArgRef(FONT_WEIGHT_ARG_7);
    std::string fontWeight = DEFAULT_FONT_WEIGHT;
    if (!fontWeightArg->IsNull()) {
        if (fontWeightArg->IsNumber()) {
            fontWeight = std::to_string(fontWeightArg->Int32Value(vm));
        } else if (fontWeightArg->IsString()) {
            // enum FontWeight is sent as string.
            fontWeight = fontWeightArg->ToString(vm)->ToString();
        }
    }
    stringsVector.push_back(fontWeight);

    Local<JSValueRef> fontFamilyArg = runtimeCallInfo->GetCallArgRef(FONT_FAMILY_ARG_9);
    std::string strFontFamilies;
    if (ArkTSUtils::ParseJsFontFamiliesToString(vm, fontFamilyArg, strFontFamilies)) {
        stringsVector.push_back(strFontFamilies);
    } else {
        strFontFamilies = NONE_FONT_FAMILY;
        stringsVector.push_back(strFontFamilies);
    }

    for (size_t index = 0; index < stringsVector.size(); index++) {
        stringParameters.push_back(stringsVector[index].c_str());
    }
}

ArkUINativeModuleValue ButtonBridge::SetLabelStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    std::vector<int32_t> valuesVector;
    PutButtonValuesParameters(runtimeCallInfo, vm, valuesVector);
    std::vector<double> fontSizesVector;
    PutButtonDimensionParameters(runtimeCallInfo, vm, fontSizesVector);
    std::vector<const char*> stringParameters;
    PutButtonStringParameters(runtimeCallInfo, vm, stringParameters);
    std::vector<size_t> dataCountVector;
    dataCountVector.push_back(stringParameters.size());
    dataCountVector.push_back(valuesVector.size());
    dataCountVector.push_back(fontSizesVector.size());
    GetArkUIInternalNodeAPI()->GetButtonModifier().SetButtonLabelStyle(
        nativeNode, stringParameters.data(), valuesVector.data(), fontSizesVector.data(), dataCountVector.data());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ButtonBridge::ResetLabelStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetButtonModifier().ResetButtonLabelStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

void ParseBorderRadius(EcmaVM* vm, const Local<JSValueRef>& args, std::optional<CalcDimension>& optionalDimention)
{
    CalcDimension valueDimen;
    if (!args->IsUndefined() && ArkTSUtils::ParseJsDimensionVp(vm, args, valueDimen, false)) {
        optionalDimention = valueDimen;
    }
}

void PushBorderRadiusVector(const std::optional<CalcDimension>& valueDimen, std::vector<double> &options)
{
    options.push_back(static_cast<double>(valueDimen.has_value()));
    if (valueDimen.has_value()) {
        options.push_back(static_cast<double>(valueDimen.value().Value()));
        options.push_back(static_cast<double>(valueDimen.value().Unit()));
    } else {
        options.push_back(0);
        options.push_back(0);
    }
}

ArkUINativeModuleValue ButtonBridge::SetButtonBorderRadius(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    Local<JSValueRef> topLeftArgs = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);     // topLeft value
    Local<JSValueRef> topRightArgs = runtimeCallInfo->GetCallArgRef(CALL_ARG_2);    // topRight value
    Local<JSValueRef> bottomLeftArgs = runtimeCallInfo->GetCallArgRef(CALL_ARG_3);  // bottomLeft value
    Local<JSValueRef> bottomRightArgs = runtimeCallInfo->GetCallArgRef(CALL_ARG_4); // bottomRight value

    if (topLeftArgs->IsUndefined() && topRightArgs->IsUndefined() && bottomLeftArgs->IsUndefined() &&
        bottomRightArgs->IsUndefined()) {
        GetArkUIInternalNodeAPI()->GetButtonModifier().ResetButtonBorderRadius(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    std::optional<CalcDimension> radiusTopLeft;
    std::optional<CalcDimension> radiusTopRight;
    std::optional<CalcDimension> radiusBottomLeft;
    std::optional<CalcDimension> radiusBottomRight;

    ParseBorderRadius(vm, topLeftArgs, radiusTopLeft);
    ParseBorderRadius(vm, topRightArgs, radiusTopRight);
    ParseBorderRadius(vm, bottomLeftArgs, radiusBottomLeft);
    ParseBorderRadius(vm, bottomRightArgs, radiusBottomRight);

    std::vector<double> options;
    PushBorderRadiusVector(radiusTopLeft, options);
    PushBorderRadiusVector(radiusTopRight, options);
    PushBorderRadiusVector(radiusBottomLeft, options);
    PushBorderRadiusVector(radiusBottomRight, options);

    GetArkUIInternalNodeAPI()->GetButtonModifier().SetButtonBorderRadius(nativeNode, options.data(), options.size());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ButtonBridge::ResetButtonBorderRadius(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetButtonModifier().ResetButtonBorderRadius(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ButtonBridge::SetButtonBorder(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    CommonBridge::SetBorder(runtimeCallInfo);
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0); // 0:node info
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();

    Local<JSValueRef> topLeftArgs = runtimeCallInfo->GetCallArgRef(9);      // 9:topLeft value
    Local<JSValueRef> topRightArgs = runtimeCallInfo->GetCallArgRef(10);    // 10:topRight value
    Local<JSValueRef> bottomLeftArgs = runtimeCallInfo->GetCallArgRef(11);  // 11:bottomLeft value
    Local<JSValueRef> bottomRightArgs = runtimeCallInfo->GetCallArgRef(12); // 12:bottomRight value
    if (topLeftArgs->IsUndefined() && topRightArgs->IsUndefined() && bottomLeftArgs->IsUndefined() &&
        bottomRightArgs->IsUndefined()) {
        GetArkUIInternalNodeAPI()->GetButtonModifier().ResetButtonBorderRadius(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    std::optional<CalcDimension> radiusTopLeft;
    std::optional<CalcDimension> radiusTopRight;
    std::optional<CalcDimension> radiusBottomLeft;
    std::optional<CalcDimension> radiusBottomRight;

    ParseBorderRadius(vm, topLeftArgs, radiusTopLeft);
    ParseBorderRadius(vm, topRightArgs, radiusTopRight);
    ParseBorderRadius(vm, bottomLeftArgs, radiusBottomLeft);
    ParseBorderRadius(vm, bottomRightArgs, radiusBottomRight);

    std::vector<double> options;
    PushBorderRadiusVector(radiusTopLeft, options);
    PushBorderRadiusVector(radiusTopRight, options);
    PushBorderRadiusVector(radiusBottomLeft, options);
    PushBorderRadiusVector(radiusBottomRight, options);

    GetArkUIInternalNodeAPI()->GetButtonModifier().SetButtonBorderRadius(nativeNode, options.data(), options.size());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ButtonBridge::ResetButtonBorder(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0); // 0:node info
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetCommonModifier().ResetBorder(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ButtonBridge::SetButtonSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0); // 0:node info
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    Local<JSValueRef> widthArgs = runtimeCallInfo->GetCallArgRef(1); // 1:width value
    Local<JSValueRef> heightArg = runtimeCallInfo->GetCallArgRef(2); // 2:height value
    CalcDimension width;
    ArkTSUtils::ParseJsDimensionVp(vm, widthArgs, width);
    CalcDimension height;
    ArkTSUtils::ParseJsDimensionVp(vm, heightArg, height);
    GetArkUIInternalNodeAPI()->GetButtonModifier().SetButtonSize(nativeNode, width.Value(),
        static_cast<int32_t>(width.Unit()), height.Value(), static_cast<int32_t>(height.Unit()));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ButtonBridge::ResetButtonSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0); // 0:node info
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetButtonModifier().ResetButtonSize(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
