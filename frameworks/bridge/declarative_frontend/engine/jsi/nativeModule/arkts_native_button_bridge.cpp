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
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_api.h"
#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "core/components/common/properties/text_style.h"
#include "core/components_ng/pattern/button/button_request_data.h"

namespace OHOS::Ace::NG {
const std::vector<TextOverflow> TEXT_OVERFLOWS = { TextOverflow::NONE, TextOverflow::CLIP, TextOverflow::ELLIPSIS,
    TextOverflow::MARQUEE };
const std::vector<Ace::FontStyle> FONT_STYLES = { Ace::FontStyle::NORMAL, Ace::FontStyle::ITALIC };
const std::vector<TextHeightAdaptivePolicy> HEIGHT_ADAPTIVE_POLICY = { TextHeightAdaptivePolicy::MAX_LINES_FIRST,
    TextHeightAdaptivePolicy::MIN_FONT_SIZE_FIRST, TextHeightAdaptivePolicy::LAYOUT_CONSTRAINT_FIRST };
const double PLACE_HOLDER_ARRAY = -10001;
constexpr int INDEX_TEXT_OVERFLOW_0 = 0;
constexpr int INDEX_MAX_LINES_1 = 1;
constexpr int INDEX_ADAPT_HEIGHT_2 = 2;
constexpr int INDEX_FONT_WEIGHT_3 = 3;
constexpr int INDEX_FONT_STYLE_4 = 4;
constexpr int INDEX_MIN_FONT_SIZE_0 = 0;
constexpr int INDEX_MAX_FONT_SIZE_1 = 1;
constexpr int INDEX_FONT_SIZE_2 = 2;
constexpr int CALL_ARG_0 = 0;
constexpr int CALL_ARG_1 = 1;
constexpr int CALL_ARG_2 = 2;
constexpr int CALL_ARG_3 = 3;
constexpr int CALL_ARG_4 = 4;
constexpr int CALL_ARG_5 = 5;
constexpr int CALL_ARG_6 = 6;
constexpr int CALL_ARG_7 = 7;
constexpr int CALL_ARG_8 = 8;
constexpr int CALL_ARG_9 = 9;

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
    bool stateEffect = secondArg->ToBoolean(vm)->Value();
    GetArkUIInternalNodeAPI()->GetButtonModifier().SetButtonStateEffect(nativeNode, stateEffect);
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
    uint32_t fontColor = secondArg->Uint32Value(vm);
    GetArkUIInternalNodeAPI()->GetButtonModifier().SetButtonFontColor(nativeNode, fontColor);
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
    if (ButtonParseJsDimensionVpNG(vm, secondArg, fontSize) && fontSize.Unit() != DimensionUnit::PERCENT &&
        GreatOrEqual(fontSize.Value(), 0.0)) {
        ButtonParseJsDimensionFp(vm, secondArg, fontSize);
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
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    std::string fontWeight = secondArg->ToString(vm)->ToString();
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
    if (!secondArg->IsString()) {
        return panda::JSValueRef::Undefined(vm);
    }
    std::string families = secondArg->ToString(vm)->ToString();
    GetArkUIInternalNodeAPI()->GetButtonModifier().SetButtonFontFamily(nativeNode, families.c_str());
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

ArkUINativeModuleValue ButtonBridge::SetLabelStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    double valueArray[5] { PLACE_HOLDER_ARRAY, PLACE_HOLDER_ARRAY, PLACE_HOLDER_ARRAY, PLACE_HOLDER_ARRAY,
        PLACE_HOLDER_ARRAY };
    double dimensionValueArray[3] { PLACE_HOLDER_ARRAY, PLACE_HOLDER_ARRAY, PLACE_HOLDER_ARRAY };
    int dimensionUnitArray[3] { PLACE_HOLDER_ARRAY, PLACE_HOLDER_ARRAY, PLACE_HOLDER_ARRAY };
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_1);
    if (!secondArg->IsNull() && secondArg->IsNumber()) {
        auto overflow = secondArg->ToNumber(vm)->Value();
        if (overflow >= 0 && overflow < static_cast<double>(TEXT_OVERFLOWS.size())) {
            valueArray[INDEX_TEXT_OVERFLOW_0] = overflow;
        }
    }
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_2);
    if (!thirdArg->IsNull() && thirdArg->IsNumber()) {
        auto maxLines = thirdArg->ToNumber(vm)->Value();
        valueArray[INDEX_MAX_LINES_1] = Positive(maxLines) ? maxLines : 1;
    }
    Local<JSValueRef> sixthArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_5);
    if (!sixthArg->IsNull() && sixthArg->IsNumber()) {
        auto adaptHeight = sixthArg->ToNumber(vm)->Value();
        if (adaptHeight >= 0 && adaptHeight < static_cast<double>(HEIGHT_ADAPTIVE_POLICY.size())) {
            valueArray[INDEX_ADAPT_HEIGHT_2] = adaptHeight;
        }
    }
    Local<JSValueRef> eightArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_7);
    if (eightArg->IsString()) {
        valueArray[INDEX_FONT_WEIGHT_3] =
            static_cast<double>(Framework::ConvertStrToFontWeight(eightArg->ToString(vm)->ToString()));
    }
    Local<JSValueRef> ninthArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_8);
    if (!ninthArg->IsNull() && ninthArg->IsNumber()) {
        auto fontStyle = ninthArg->ToNumber(vm)->Value();
        if (fontStyle >= 0 && fontStyle < static_cast<int32_t>(FONT_STYLES.size())) {
            valueArray[INDEX_FONT_STYLE_4] = fontStyle;
        }
    }
    PutButtonDimensionParameters(runtimeCallInfo, vm, dimensionValueArray, dimensionUnitArray);
    Local<JSValueRef> tenthArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_9);
    std::string families = tenthArg->ToString(vm)->ToString();
    GetArkUIInternalNodeAPI()->GetButtonModifier().SetButtonLabelStyle(
        nativeNode, families.c_str(), valueArray, dimensionValueArray, dimensionUnitArray);
    return panda::JSValueRef::Undefined(vm);
}

void ButtonBridge::PutButtonDimensionParameters(
    ArkUIRuntimeCallInfo* runtimeCallInfo, EcmaVM* vm, double* dimensionValueArray, int* dimensionUnitArray)
{
    if (dimensionValueArray != nullptr && dimensionUnitArray != nullptr) {
        Local<JSValueRef> fourthArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_3);
        CalcDimension minFontSize;
        if (ButtonParseJsDimensionFp(vm, fourthArg, minFontSize)) {
            dimensionValueArray[INDEX_MIN_FONT_SIZE_0] = minFontSize.Value();
            dimensionUnitArray[INDEX_MIN_FONT_SIZE_0] = static_cast<int>(minFontSize.Unit());
        }
        Local<JSValueRef> fifthArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_4);
        CalcDimension maxFontSize;
        if (ButtonParseJsDimensionFp(vm, fifthArg, maxFontSize)) {
            dimensionValueArray[INDEX_MAX_FONT_SIZE_1] = maxFontSize.Value();
            dimensionUnitArray[INDEX_MAX_FONT_SIZE_1] = static_cast<int>(maxFontSize.Unit());
        }
        Local<JSValueRef> seventhArg = runtimeCallInfo->GetCallArgRef(CALL_ARG_6);
        CalcDimension fontSize;
        if (ButtonParseJsDimensionFp(vm, seventhArg, fontSize)) {
            dimensionValueArray[INDEX_FONT_SIZE_2] = fontSize.Value();
            dimensionUnitArray[INDEX_FONT_SIZE_2] = static_cast<int>(fontSize.Unit());
        }
    }
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

bool ButtonBridge::ButtonParseJsDimensionFp(const EcmaVM* vm, const Local<JSValueRef>& value, CalcDimension& result)
{
    if (value->IsNumber()) {
        result = CalcDimension(value->ToNumber(vm)->Value(), DimensionUnit::FP);
        return true;
    }
    if (value->IsString()) {
        result = StringUtils::StringToCalcDimension(value->ToString(vm)->ToString(), false, DimensionUnit::VP);
        return true;
    }
    return false;
}

bool ButtonBridge::ButtonParseJsDimensionVp(const EcmaVM* vm, const Local<JSValueRef>& value, CalcDimension& result)
{
    if (value->IsNumber()) {
        result = CalcDimension(value->ToNumber(vm)->Value(), DimensionUnit::VP);
        return true;
    }
    if (value->IsString()) {
        result = StringUtils::StringToCalcDimension(value->ToString(vm)->ToString(), false, DimensionUnit::VP);
        return true;
    }
    return false;
}

bool ButtonBridge::ButtonParseJsDimensionNG(const EcmaVM* vm, const Local<JSValueRef>& jsValue, CalcDimension& result,
    DimensionUnit defaultUnit, bool isSupportPercent)
{
    if (jsValue->IsNumber()) {
        result = CalcDimension(jsValue->ToNumber(vm)->Value(), defaultUnit);
        return true;
    }
    if (jsValue->IsString()) {
        auto value = jsValue->ToString(vm)->ToString();
        if (value.back() == '%' && !isSupportPercent) {
            return false;
        }
        return StringUtils::StringToCalcDimensionNG(jsValue->ToString(vm)->ToString(), result, false, defaultUnit);
    }
    return false;
}

bool ButtonBridge::ButtonParseJsDimensionVpNG(
    const EcmaVM* vm, const Local<JSValueRef>& jsValue, CalcDimension& result, bool isSupportPercent)
{
    return ButtonParseJsDimensionNG(vm, jsValue, result, DimensionUnit::VP, isSupportPercent);
}
} // namespace OHOS::Ace::NG
