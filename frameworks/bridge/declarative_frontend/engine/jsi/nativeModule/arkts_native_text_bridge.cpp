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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_text_bridge.h"

#include "base/utils/string_utils.h"
#include "base/utils/utils.h"
#include "bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "bridge/declarative_frontend/engine/jsi/jsi_types.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_frame_node_bridge.h"
#include "bridge/declarative_frontend/style_string/js_span_string.h"
#include "core/components/common/properties/shadow.h"
#include "core/components_ng/pattern/text/text_model_ng.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_text.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int PARAM_ARR_LENGTH_1 = 1;
constexpr int PARAM_ARR_LENGTH_2 = 2;
constexpr int SIZE_OF_TEXT_CASES = 2;
constexpr int16_t DEFAULT_ALPHA = 255;
constexpr double DEFAULT_OPACITY = 0.2;
constexpr double DEFAULT_SPAN_FONT_SIZE = 16;
constexpr DimensionUnit DEFAULT_SPAN_FONT_UNIT = DimensionUnit::FP;
constexpr TextDecorationStyle DEFAULT_DECORATION_STYLE = TextDecorationStyle::SOLID;
constexpr Ace::FontStyle DEFAULT_FONT_STYLE = Ace::FontStyle::NORMAL;
const Color DEFAULT_DECORATION_COLOR = Color::BLACK;
const std::string DEFAULT_FONT_WEIGHT = "400";
constexpr int DEFAULT_VARIABLE_FONT_WEIGHT = 400;
constexpr Dimension DEFAULT_MARQUEE_STEP_VALUE = 4.0_vp;
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int NUM_4 = 4;
constexpr int NUM_5 = 5;
constexpr int NUM_6 = 6;
constexpr int NUM_7 = 7;
const std::vector<TextOverflow> TEXT_OVERFLOWS = { TextOverflow::NONE, TextOverflow::CLIP, TextOverflow::ELLIPSIS,
    TextOverflow::MARQUEE };
const std::vector<std::string> TEXT_DETECT_TYPES = { "phoneNum", "url", "email", "location", "datetime" };
} // namespace

ArkUINativeModuleValue TextBridge::SetFontWeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> weightArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> optionsArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    ArkUIFontWeightWithOptionsStruct weightInfo;
    int32_t variableFontWeight = DEFAULT_VARIABLE_FONT_WEIGHT;
    std::string weight = DEFAULT_FONT_WEIGHT;
    if (!weightArg->IsNull()) {
        if (weightArg->IsNumber()) {
            weight = std::to_string(weightArg->Int32Value(vm));
            variableFontWeight = weightArg->Int32Value(vm);
        } else if ((weightArg->IsString(vm) || weightArg->IsObject(vm)) &&
            (!ArkTSUtils::ParseJsString(vm, weightArg, weight))) {
            variableFontWeight = StringUtils::StringToInt(weight);
        }
    }
    weightInfo.weight = weight.c_str();
    weightInfo.variableFontWeight = variableFontWeight;

    if (optionsArg->IsBoolean()) {
        weightInfo.enableVariableFontWeight = static_cast<int32_t>(optionsArg->BooleaValue(vm));
    }
    GetArkUINodeModifiers()->getTextModifier()->setFontWeightWithOption(nativeNode, &weightInfo);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::ResetFontWeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextModifier()->resetFontWeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::SetFontStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsNumber()) {
        uint32_t fontStyle = secondArg->Uint32Value(vm);
        if (fontStyle < static_cast<uint32_t>(OHOS::Ace::FontStyle::NORMAL) ||
            fontStyle > static_cast<uint32_t>(OHOS::Ace::FontStyle::ITALIC)) {
            fontStyle = static_cast<uint32_t>(OHOS::Ace::FontStyle::NORMAL);
        }
        GetArkUINodeModifiers()->getTextModifier()->setFontStyle(nativeNode, fontStyle);
    } else {
        GetArkUINodeModifiers()->getTextModifier()->resetFontStyle(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::ResetFontStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextModifier()->resetFontStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::SetTextAlign(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsNumber()) {
        GetArkUINodeModifiers()->getTextModifier()->setTextAlign(nativeNode, secondArg->ToNumber(vm)->Value());
    } else {
        GetArkUINodeModifiers()->getTextModifier()->resetTextAlign(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::ResetTextAlign(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextModifier()->resetTextAlign(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::SetFontColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Color color;
    RefPtr<ResourceObject> colorResObj;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color, colorResObj)) {
        GetArkUINodeModifiers()->getTextModifier()->resetFontColor(nativeNode);
    } else {
        GetArkUINodeModifiers()->getTextModifier()->setFontColor(
            nativeNode, color.GetValue(), AceType::RawPtr(colorResObj));
    }
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue TextBridge::ResetFontColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextModifier()->resetFontColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::SetForegroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto colorArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());

    ForegroundColorStrategy strategy;
    if (ArkTSUtils::ParseJsColorStrategy(vm, colorArg, strategy)) {
        auto strategyInt = static_cast<uint32_t>(ForegroundColorStrategy::INVERT);
        GetArkUINodeModifiers()->getTextModifier()->setTextForegroundColor(nativeNode, false, strategyInt);
        return panda::JSValueRef::Undefined(vm);
    }
    Color foregroundColor;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, colorArg, foregroundColor)) {
        GetArkUINodeModifiers()->getTextModifier()->resetTextForegroundColor(nativeNode);
    } else {
        GetArkUINodeModifiers()->getTextModifier()->setTextForegroundColor(
            nativeNode, true, foregroundColor.GetValue());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::ResetForegroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getTextModifier()->resetTextForegroundColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::SetFontSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    CalcDimension fontSize;
    RefPtr<ResourceObject> fontSizeResObj;
    if (!ArkTSUtils::ParseJsDimensionFpNG(vm, secondArg, fontSize, fontSizeResObj, false)) {
        GetArkUINodeModifiers()->getTextModifier()->resetFontSize(nativeNode);
    } else {
        GetArkUINodeModifiers()->getTextModifier()->setFontSize(
            nativeNode, fontSize.Value(), static_cast<int>(fontSize.Unit()), AceType::RawPtr(fontSizeResObj));
    }
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue TextBridge::ResetFontSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextModifier()->resetFontSize(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::SetLineHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    CalcDimension lineHeight(0.0, DEFAULT_SPAN_FONT_UNIT);
    RefPtr<ResourceObject> lineHeightObj;
    if (!ArkTSUtils::ParseJsDimensionFpNG(vm, secondArg, lineHeight, lineHeightObj)) {
        lineHeight.Reset();
    }
    if (lineHeight.IsNegative()) {
        lineHeight.Reset();
    }
    GetArkUINodeModifiers()->getTextModifier()->setTextLineHeight(
        nativeNode, lineHeight.Value(), static_cast<int8_t>(lineHeight.Unit()), AceType::RawPtr(lineHeightObj));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::ResetLineHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextModifier()->resetTextLineHeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::SetTextOverflow(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    int32_t value;
    if (secondArg->IsUndefined()) {
        value = 0;
    } else if (secondArg->IsNumber()) {
        value = secondArg->Int32Value(vm);
    } else {
        return panda::JSValueRef::Undefined(vm);
    }
    if (value < 0 || value >= static_cast<int32_t>(TEXT_OVERFLOWS.size())) {
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUINodeModifiers()->getTextModifier()->setTextOverflow(nativeNode, value);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::ResetTextOverflow(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextModifier()->resetTextOverflow(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::SetDecoration(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> fourthArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> fifthArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    int32_t textDecoration = static_cast<int32_t>(TextDecoration::NONE);
    Color color = DEFAULT_DECORATION_COLOR;
    int32_t style = static_cast<int32_t>(DEFAULT_DECORATION_STYLE);
    double lineThicknessScale = 1.0;
    if (secondArg->IsInt()) {
        textDecoration = secondArg->Int32Value(vm);
    }
    RefPtr<ResourceObject> resourceObject;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, thirdArg, color, resourceObject)) {
        color = DEFAULT_DECORATION_COLOR;
    }
    if (fourthArg->IsInt()) {
        style = fourthArg->Int32Value(vm);
    }
    if (!ArkTSUtils::ParseJsDouble(vm, fifthArg, lineThicknessScale)) {
        lineThicknessScale = 1.0;
    }
    lineThicknessScale = lineThicknessScale < 0 ? 1.0 : lineThicknessScale;
    GetArkUINodeModifiers()->getTextModifier()->setTextDecoration(nativeNode, textDecoration, color.GetValue(),
        AceType::RawPtr(resourceObject), style, static_cast<float>(lineThicknessScale));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::ResetDecoration(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextModifier()->resetTextDecoration(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::SetTextCase(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsNumber() && secondArg->Int32Value(vm) >= NUM_0 &&
        secondArg->Int32Value(vm) <= SIZE_OF_TEXT_CASES) {
        GetArkUINodeModifiers()->getTextModifier()->setTextCase(nativeNode, secondArg->Int32Value(vm));
    } else {
        GetArkUINodeModifiers()->getTextModifier()->resetTextCase(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::ResetTextCase(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextModifier()->resetTextCase(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::SetMaxLines(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsNumber()) {
        uint32_t maxLine = secondArg->Uint32Value(vm);
        GetArkUINodeModifiers()->getTextModifier()->setTextMaxLines(nativeNode, maxLine);
    } else {
        GetArkUINodeModifiers()->getTextModifier()->resetTextMaxLines(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::ResetMaxLines(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextModifier()->resetTextMaxLines(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::SetMinFontSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    CalcDimension fontSize;
    RefPtr<ResourceObject> resourceObject;
    if (ArkTSUtils::ParseJsDimensionFpNG(vm, secondArg, fontSize, resourceObject, false)) {
        GetArkUINodeModifiers()->getTextModifier()->setTextMinFontSize(
            nativeNode, fontSize.Value(), static_cast<int8_t>(fontSize.Unit()), AceType::RawPtr(resourceObject));
    } else {
        GetArkUINodeModifiers()->getTextModifier()->resetTextMinFontSize(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::ReSetMinFontSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextModifier()->resetTextMinFontSize(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::SetDraggable(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    uint32_t draggable = false;
    if (secondArg->IsBoolean()) {
        draggable = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
    }
    GetArkUINodeModifiers()->getTextModifier()->setTextDraggable(nativeNode, draggable);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::ResetDraggable(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextModifier()->resetTextDraggable(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::SetPrivacySensitive(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    uint32_t sensitive = false;
    if (secondArg->IsBoolean()) {
        sensitive = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
    }
    GetArkUINodeModifiers()->getTextModifier()->setTextPrivacySensitive(nativeNode, sensitive);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::ResetPrivacySensitive(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextModifier()->resetTextPrivacySensitive(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::SetMaxFontSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    CalcDimension fontSize;
    RefPtr<ResourceObject> resourceObject;
    if (ArkTSUtils::ParseJsDimensionFpNG(vm, secondArg, fontSize, resourceObject, false)) {
        GetArkUINodeModifiers()->getTextModifier()->setTextMaxFontSize(
            nativeNode, fontSize.Value(), static_cast<int8_t>(fontSize.Unit()), AceType::RawPtr(resourceObject));
    } else {
        GetArkUINodeModifiers()->getTextModifier()->resetTextMaxFontSize(nativeNode);
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::ResetMaxFontSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextModifier()->resetTextMaxFontSize(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::SetMinFontScale(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    double minFontScale;
    RefPtr<ResourceObject> resourceObject;
    if (!ArkTSUtils::ParseJsDouble(vm, secondArg, minFontScale, resourceObject)) {
        return panda::JSValueRef::Undefined(vm);
    }
    if (LessOrEqual(minFontScale, 0.0f)) {
        GetArkUINodeModifiers()->getTextModifier()->setTextMinFontScale(
            nativeNode, static_cast<float>(minFontScale), nullptr);
        minFontScale = 0.0f;
    } else if (GreatOrEqual(minFontScale, 1.0f)) {
        minFontScale = 1.0f;
    }
    GetArkUINodeModifiers()->getTextModifier()->setTextMinFontScale(
        nativeNode, static_cast<float>(minFontScale), AceType::RawPtr(resourceObject));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::ResetMinFontScale(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextModifier()->resetTextMinFontScale(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::SetMaxFontScale(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    double maxFontScale;
    RefPtr<ResourceObject> resourceObject;
    if (!ArkTSUtils::ParseJsDouble(vm, secondArg, maxFontScale, resourceObject)) {
        return panda::JSValueRef::Undefined(vm);
    }
    if (LessOrEqual(maxFontScale, 1.0f)) {
        maxFontScale = 1.0f;
    }
    GetArkUINodeModifiers()->getTextModifier()->setTextMaxFontScale(
        nativeNode, static_cast<float>(maxFontScale), AceType::RawPtr(resourceObject));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::ResetMaxFontScale(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextModifier()->resetTextMaxFontScale(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::SetFontFamily(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    std::vector<std::string> fontFamilies;
    RefPtr<ResourceObject> resourceObject;
    if (!ArkTSUtils::ParseJsFontFamilies(vm, secondArg, fontFamilies, resourceObject)) {
        GetArkUINodeModifiers()->getTextModifier()->resetTextFontFamily(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto families = std::make_unique<char* []>(fontFamilies.size());
    for (uint32_t i = 0; i < fontFamilies.size(); i++) {
        families[i] = const_cast<char*>(fontFamilies.at(i).c_str());
    }
    GetArkUINodeModifiers()->getTextModifier()->setTextFontFamily(
        nativeNode, const_cast<const char**>(families.get()), fontFamilies.size(), AceType::RawPtr(resourceObject));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::ResetFontFamily(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    GetArkUINodeModifiers()->getTextModifier()->resetTextFontFamily(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::SetCopyOption(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    int32_t copyOption = static_cast<int32_t>(CopyOptions::None);
    if (secondArg->IsInt()) {
        copyOption = secondArg->Int32Value(vm);
    }
    GetArkUINodeModifiers()->getTextModifier()->setTextCopyOption(nativeNode, copyOption);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::ResetCopyOption(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextModifier()->resetTextCopyOption(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::SetTextShadow(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> radiusArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> typeArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> offsetXArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    Local<JSValueRef> offsetYArg = runtimeCallInfo->GetCallArgRef(NUM_5);
    Local<JSValueRef> fillArg = runtimeCallInfo->GetCallArgRef(NUM_6);
    Local<JSValueRef> lengthArg = runtimeCallInfo->GetCallArgRef(NUM_7);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    uint32_t length;
    if (!lengthArg->IsNumber() || lengthArg->Uint32Value(vm) == 0) {
        return panda::JSValueRef::Undefined(vm);
    }
    length = lengthArg->Uint32Value(vm);
    auto radiusArray = std::make_unique<double[]>(length);
    auto typeArray = std::make_unique<uint32_t[]>(length);
    auto colorArray = std::make_unique<uint32_t[]>(length);
    auto offsetXArray = std::make_unique<double[]>(length);
    auto offsetYArray = std::make_unique<double[]>(length);
    auto fillArray = std::make_unique<uint32_t[]>(length);
    bool radiusParseResult = ArkTSUtils::ParseArray<double>(
        vm, radiusArg, radiusArray.get(), length, ArkTSUtils::parseShadowRadius);
    bool typeParseResult = ArkTSUtils::ParseArray<uint32_t>(
        vm, typeArg, typeArray.get(), length, ArkTSUtils::parseShadowType);
    bool colorParseResult = ArkTSUtils::ParseArray<uint32_t>(
        vm, colorArg, colorArray.get(), length, ArkTSUtils::parseShadowColor);
    bool offsetXParseResult = ArkTSUtils::ParseArray<double>(
        vm, offsetXArg, offsetXArray.get(), length, ArkTSUtils::parseShadowOffset);
    bool offsetYParseResult = ArkTSUtils::ParseArray<double>(
        vm, offsetYArg, offsetYArray.get(), length, ArkTSUtils::parseShadowOffset);
    bool fillParseResult = ArkTSUtils::ParseArray<uint32_t>(
        vm, fillArg, fillArray.get(), length, ArkTSUtils::parseShadowFill);
    if (!radiusParseResult || !colorParseResult || !offsetXParseResult ||
        !offsetYParseResult || !fillParseResult || !typeParseResult) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto textShadowArray = std::make_unique<ArkUITextShadowStruct[]>(length);
    CHECK_NULL_RETURN(textShadowArray.get(), panda::JSValueRef::Undefined(vm));
    for (uint32_t i = 0; i < length; i++) {
        textShadowArray[i].radius = radiusArray[i];
        textShadowArray[i].type = typeArray[i];
        textShadowArray[i].color = colorArray[i];
        textShadowArray[i].offsetX = offsetXArray[i];
        textShadowArray[i].offsetY = offsetYArray[i];
        textShadowArray[i].fill = fillArray[i];
    }
    GetArkUINodeModifiers()->getTextModifier()->setTextShadow(nativeNode, textShadowArray.get(), length);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::ResetTextShadow(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextModifier()->resetTextShadow(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::SetContent(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Framework::JsiCallbackInfo info = Framework::JsiCallbackInfo(runtimeCallInfo);

    Framework::JSRef<Framework::JSVal> args = info[1];
    if (args->IsObject() && Framework::JSRef<Framework::JSObject>::Cast(args)->Unwrap<Framework::JSSpanString>()) {
        auto* spanString = Framework::JSRef<Framework::JSObject>::Cast(args)->Unwrap<Framework::JSSpanString>();
        CHECK_NULL_RETURN(spanString, panda::JSValueRef::Undefined(vm));
        auto spanStringController = spanString->GetController();
        if (spanStringController) {
            TextModelNG::InitSpanStringController(reinterpret_cast<FrameNode*>(nativeNode), spanStringController);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    std::string content;
    RefPtr<ResourceObject> resourceObject;
    if (ArkTSUtils::ParseJsString(vm, secondArg, content, resourceObject)) {
        GetArkUINodeModifiers()->getTextModifier()->setContent(
            nativeNode, content.c_str(), AceType::RawPtr(resourceObject));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::SetTextController(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Framework::JsiCallbackInfo info = Framework::JsiCallbackInfo(runtimeCallInfo);
    Framework::JSRef<Framework::JSVal> args = info[1];
    if (args->IsObject()) {
        auto paramObject = Framework::JSRef<Framework::JSObject>::Cast(args);
        auto controllerObj = paramObject->GetProperty("controller");
        Framework::JSTextController* jsController = nullptr;
        if (controllerObj->IsObject()) {
            jsController =
                Framework::JSRef<Framework::JSObject>::Cast(controllerObj)->Unwrap<Framework::JSTextController>();
        }
        RefPtr<TextControllerBase> controller =
            TextModelNG::InitTextController(reinterpret_cast<FrameNode*>(nativeNode));
        if (jsController) {
            jsController->SetController(controller);
        }
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::SetHeightAdaptivePolicy(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsNumber()
        && secondArg->Int32Value(vm) >= static_cast<int32_t>(TextHeightAdaptivePolicy::MAX_LINES_FIRST)
        && secondArg->Int32Value(vm) <= static_cast<int32_t>(TextHeightAdaptivePolicy::LAYOUT_CONSTRAINT_FIRST)) {
        auto value = secondArg->Int32Value(vm);
        GetArkUINodeModifiers()->getTextModifier()->setTextHeightAdaptivePolicy(nativeNode, value);
    } else {
        GetArkUINodeModifiers()->getTextModifier()->resetTextHeightAdaptivePolicy(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::ResetHeightAdaptivePolicy(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextModifier()->resetTextHeightAdaptivePolicy(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::SetTextIndent(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    CalcDimension indent;
    RefPtr<ResourceObject> resourceObject;
    if (!ArkTSUtils::ParseJsDimensionFpNG(vm, secondArg, indent, resourceObject) || indent.IsNegative()) {
        indent.Reset();
    }

    GetArkUINodeModifiers()->getTextModifier()->setTextIndent(
        nativeNode, indent.Value(), static_cast<int8_t>(indent.Unit()), AceType::RawPtr(resourceObject));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::ResetTextIndent(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextModifier()->resetTextIndent(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::SetBaselineOffset(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    CalcDimension baselineOffset;
    RefPtr<ResourceObject> resourceObject;
    if (!ArkTSUtils::ParseJsDimensionNG(vm, secondArg, baselineOffset, DimensionUnit::FP, resourceObject, false)) {
        baselineOffset.Reset();
    }

    GetArkUINodeModifiers()->getTextModifier()->setTextBaselineOffset(nativeNode, baselineOffset.Value(),
        static_cast<int8_t>(baselineOffset.Unit()), AceType::RawPtr(resourceObject));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::ResetBaselineOffset(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextModifier()->resetTextBaselineOffset(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::SetLetterSpacing(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    CalcDimension letterSpacing;
    if (!ArkTSUtils::ParseJsDimensionNG(vm, secondArg, letterSpacing, DimensionUnit::FP, false)) {
        letterSpacing.Reset();
    }

    GetArkUINodeModifiers()->getTextModifier()->setTextLetterSpacing(
        nativeNode, letterSpacing.Value(), static_cast<int8_t>(letterSpacing.Unit()));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::ResetLetterSpacing(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextModifier()->resetTextLetterSpacing(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::SetFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> sizeArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> weightArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> familyArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> styleArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    Local<JSValueRef> optionsArg = runtimeCallInfo->GetCallArgRef(NUM_5);

    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    ArkUIFontWithOptionsStruct fontInfo;
    CalcDimension fontSize;
    if (!ArkTSUtils::ParseJsDimensionFpNG(vm, sizeArg, fontSize, false) || sizeArg->IsNull()) {
        fontSize.SetValue(DEFAULT_SPAN_FONT_SIZE);
        fontSize.SetUnit(DEFAULT_SPAN_FONT_UNIT);
    }
    if (sizeArg->IsUndefined() || fontSize.IsNegative() || fontSize.Unit() == DimensionUnit::PERCENT) {
        auto theme = ArkTSUtils::GetTheme<TextTheme>();
        CHECK_NULL_RETURN(theme, panda::JSValueRef::Undefined(vm));
        auto size = theme->GetTextStyle().GetFontSize();
        fontInfo.fontSizeNumber = size.Value();
        fontInfo.fontSizeUnit = static_cast<int8_t>(size.Unit());
    } else {
        fontInfo.fontSizeNumber = fontSize.Value();
        fontInfo.fontSizeUnit = static_cast<int8_t>(fontSize.Unit());
    }

    int32_t variableFontWeight = DEFAULT_VARIABLE_FONT_WEIGHT;
    std::string weight = DEFAULT_FONT_WEIGHT;
    if (!weightArg->IsNull()) {
        if (weightArg->IsNumber()) {
            weight = std::to_string(weightArg->Int32Value(vm));
            variableFontWeight = weightArg->Int32Value(vm);
        } else if (weightArg->IsString(vm)) {
            weight = weightArg->ToString(vm)->ToString(vm);
            variableFontWeight = StringUtils::StringToInt(weight);
        }
    }
    fontInfo.fontWeight = static_cast<uint8_t>(Framework::ConvertStrToFontWeight(weight));
    fontInfo.variableFontWeight = variableFontWeight;

    if (optionsArg->IsBoolean()) {
        fontInfo.enableVariableFontWeight = static_cast<int32_t>(optionsArg->BooleaValue(vm));
    }

    int32_t style = static_cast<int32_t>(DEFAULT_FONT_STYLE);
    if (styleArg->IsInt()) {
        style = styleArg->Int32Value(vm);
    }
    fontInfo.fontStyle = static_cast<uint8_t>(style);

    std::vector<std::string> fontFamilies;
    fontInfo.fontFamilies = nullptr;
    if (!familyArg->IsNull() && ArkTSUtils::ParseJsFontFamilies(vm, familyArg, fontFamilies)) {
        fontInfo.familyLength = fontFamilies.size();
        auto families = std::make_unique<const char* []>(fontInfo.familyLength);
        for (uint32_t i = 0; i < fontFamilies.size(); i++) {
            families[i] = fontFamilies[i].c_str();
        }
        fontInfo.fontFamilies = families.get();
        GetArkUINodeModifiers()->getTextModifier()->setTextFont(nativeNode, &fontInfo);
    } else {
        GetArkUINodeModifiers()->getTextModifier()->setTextFont(nativeNode, &fontInfo);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::ResetFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextModifier()->resetTextFont(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::SetWordBreak(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> workBreakArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (workBreakArg->IsNull() || workBreakArg->IsUndefined() || !workBreakArg->IsNumber()) {
        GetArkUINodeModifiers()->getTextModifier()->resetWordBreak(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    uint32_t wordBreak = workBreakArg->Uint32Value(vm);
    GetArkUINodeModifiers()->getTextModifier()->setWordBreak(nativeNode, wordBreak);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::ResetWordBreak(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextModifier()->resetWordBreak(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::SetLineBreakStrategy(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> lineBreakStrategyArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (lineBreakStrategyArg->IsNull() || lineBreakStrategyArg->IsUndefined() || !lineBreakStrategyArg->IsNumber()) {
        GetArkUINodeModifiers()->getTextModifier()->resetLineBreakStrategy(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    uint32_t lineBreakStrategy = lineBreakStrategyArg->Uint32Value(vm);
    GetArkUINodeModifiers()->getTextModifier()->setLineBreakStrategy(nativeNode, lineBreakStrategy);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::ResetLineBreakStrategy(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextModifier()->resetLineBreakStrategy(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::SetEllipsisMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> ellipsisModeArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (ellipsisModeArg->IsNull() || ellipsisModeArg->IsUndefined() || !ellipsisModeArg->IsNumber()) {
        GetArkUINodeModifiers()->getTextModifier()->resetEllipsisMode(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    uint32_t ellipsisMode = ellipsisModeArg->Uint32Value(vm);
    GetArkUINodeModifiers()->getTextModifier()->setEllipsisMode(nativeNode, ellipsisMode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::ResetEllipsisMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextModifier()->resetEllipsisMode(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::SetEnableDataDetector(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> enableDataDetectorArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (enableDataDetectorArg->IsNull() || enableDataDetectorArg->IsUndefined() ||
        !enableDataDetectorArg->IsBoolean()) {
        GetArkUINodeModifiers()->getTextModifier()->resetEnableDataDetector(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    uint32_t enableDataDetector = enableDataDetectorArg->Uint32Value(vm);
    GetArkUINodeModifiers()->getTextModifier()->setEnableDataDetector(nativeNode, enableDataDetector);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::ResetEnableDataDetector(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextModifier()->resetEnableDataDetector(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::SetFontFeature(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsString(vm)) {
        auto value = secondArg->ToString(vm)->ToString(vm);
        GetArkUINodeModifiers()->getTextModifier()->setTextFontFeature(nativeNode, value.c_str());
    } else {
        GetArkUINodeModifiers()->getTextModifier()->resetTextFontFeature(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::ResetFontFeature(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextModifier()->resetTextFontFeature(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::SetLineSpacing(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> optionsArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    CalcDimension value;
    if (!ArkTSUtils::ParseJsLengthMetrics(vm, secondArg, value)) {
        GetArkUINodeModifiers()->getTextModifier()->resetTextLineSpacing(nativeNode);
    } else {
        if (value.IsNegative()) {
            value.Reset();
        }
        bool isOnlyBetweenLines = optionsArg->IsBoolean() ? optionsArg->ToBoolean(vm)->Value() : false;
        GetArkUINodeModifiers()->getTextModifier()->setTextLineSpacing(
            nativeNode, value.Value(), static_cast<int>(value.Unit()), isOnlyBetweenLines);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::ResetLineSpacing(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextModifier()->resetTextLineSpacing(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::SetOptimizeTrailingSpace(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    uint32_t optimizeTrailingSpace = false;
    if (secondArg->IsBoolean()) {
        optimizeTrailingSpace = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
    }
    GetArkUINodeModifiers()->getTextModifier()->setTextOptimizeTrailingSpace(nativeNode, optimizeTrailingSpace);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::ResetOptimizeTrailingSpace(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextModifier()->resetTextOptimizeTrailingSpace(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::SetSelection(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> startArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> endArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (!startArg->IsNumber() || !endArg->IsNumber()) {
        GetArkUINodeModifiers()->getTextModifier()->resetTextSelection(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    int32_t startIndex = startArg->Int32Value(vm);
    int32_t endIndex = endArg->Int32Value(vm);
    if (startIndex >= endIndex) {
        GetArkUINodeModifiers()->getTextModifier()->resetTextSelection(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUINodeModifiers()->getTextModifier()->setTextSelection(nativeNode, startIndex, endIndex);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::ResetSelection(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextModifier()->resetTextSelection(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::SetTextSelectableMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> textSelectableModeArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (textSelectableModeArg->IsNull() || textSelectableModeArg->IsUndefined() || !textSelectableModeArg->IsNumber()) {
        GetArkUINodeModifiers()->getTextModifier()->resetTextSelectableMode(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    uint32_t textSelectableMode = textSelectableModeArg->Uint32Value(vm);
    GetArkUINodeModifiers()->getTextModifier()->setTextSelectableMode(nativeNode, textSelectableMode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::ResetTextSelectableMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextModifier()->resetTextSelectableMode(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::SetCaretColor(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Color color;
    RefPtr<ResourceObject> resourceObject;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color, resourceObject)) {
        GetArkUINodeModifiers()->getTextModifier()->resetTextCaretColor(nativeNode);
    } else {
        GetArkUINodeModifiers()->getTextModifier()->setTextCaretColor(
            nativeNode, color.GetValue(), AceType::RawPtr(resourceObject));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::ResetCaretColor(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextModifier()->resetTextCaretColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::SetSelectedBackgroundColor(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Color color;
    RefPtr<ResourceObject> resourceObject;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color, resourceObject)) {
        GetArkUINodeModifiers()->getTextModifier()->resetTextSelectedBackgroundColor(nativeNode);
    } else {
        if (color.GetAlpha() == DEFAULT_ALPHA) {
            color = color.ChangeOpacity(DEFAULT_OPACITY);
        }
        GetArkUINodeModifiers()->getTextModifier()->setTextSelectedBackgroundColor(
            nativeNode, color.GetValue(), AceType::RawPtr(resourceObject));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::ResetSelectedBackgroundColor(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextModifier()->resetTextSelectedBackgroundColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::SetDataDetectorConfig(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> typesArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    if (!typesArg->IsArray(vm)) {
        GetArkUINodeModifiers()->getTextModifier()->
            resetTextDataDetectorConfigWithEvent(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    struct ArkUITextDetectConfigStruct arkUITextDetectConfig;
    std::string types;
    auto array = panda::Local<panda::ArrayRef>(typesArg);
    for (size_t i = 0; i < array->Length(vm); i++) {
        auto value = panda::ArrayRef::GetValueAt(vm, array, i);
        auto index = value->Int32Value(vm);
        if (index < 0 || index >= static_cast<int32_t>(TEXT_DETECT_TYPES.size())) {
            return panda::JSValueRef::Undefined(vm);
        }
        if (i != 0) {
            types.append(",");
        }
        types.append(TEXT_DETECT_TYPES[index]);
    }
    arkUITextDetectConfig.types = types.c_str();
    std::function<void(const std::string&)> callback;
    if (callbackArg->IsFunction(vm)) {
        panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
        callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)](const std::string& info) {
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
            panda::Local<panda::JSValueRef> params[PARAM_ARR_LENGTH_1] = {
                panda::StringRef::NewFromUtf8(vm, info.c_str()) };
            func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_1);
        };
        arkUITextDetectConfig.onResult = reinterpret_cast<void*>(&callback);
    }
    ParseAIEntityColorAndPreview(runtimeCallInfo, arkUITextDetectConfig);
    GetArkUINodeModifiers()->getTextModifier()->
        setTextDataDetectorConfigWithEvent(nativeNode, &arkUITextDetectConfig);
    return panda::JSValueRef::Undefined(vm);
}

void TextBridge::ParseAIEntityColorAndPreview(
    ArkUIRuntimeCallInfo* runtimeCallInfo, struct ArkUITextDetectConfigStruct& arkUITextDetectConfig)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_VOID(vm);
    TextDetectConfig textDetectConfig;
    Local<JSValueRef> entityColorArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    ArkTSUtils::ParseJsColorAlpha(vm, entityColorArg, textDetectConfig.entityColor);
    arkUITextDetectConfig.entityColor = textDetectConfig.entityColor.GetValue();

    Local<JSValueRef> entityDecorationTypeArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    Local<JSValueRef> entityDecorationColorArg = runtimeCallInfo->GetCallArgRef(NUM_5);
    Local<JSValueRef> entityDecorationStyleArg = runtimeCallInfo->GetCallArgRef(NUM_6);
    arkUITextDetectConfig.entityDecorationType = static_cast<int32_t>(textDetectConfig.entityDecorationType);
    arkUITextDetectConfig.entityDecorationColor = arkUITextDetectConfig.entityColor;
    arkUITextDetectConfig.entityDecorationStyle = static_cast<int32_t>(textDetectConfig.entityDecorationStyle);

    if (entityDecorationTypeArg->IsInt()) {
        arkUITextDetectConfig.entityDecorationType = entityDecorationTypeArg->Int32Value(vm);
    }
    if (ArkTSUtils::ParseJsColorAlpha(vm, entityDecorationColorArg, textDetectConfig.entityDecorationColor)) {
        arkUITextDetectConfig.entityDecorationColor = textDetectConfig.entityDecorationColor.GetValue();
    }
    if (entityDecorationStyleArg->IsInt()) {
        arkUITextDetectConfig.entityDecorationStyle = entityDecorationStyleArg->Int32Value(vm);
    }

    Local<JSValueRef> enablePreviewMenu = runtimeCallInfo->GetCallArgRef(NUM_7);
    auto enablePreviewMenuValue = false;
    if (enablePreviewMenu->IsBoolean()) {
        enablePreviewMenuValue = enablePreviewMenu->ToBoolean(vm)->Value();
    }
    arkUITextDetectConfig.entityEnablePreviewMenu = enablePreviewMenuValue;
}

ArkUINativeModuleValue TextBridge::ResetDataDetectorConfig(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextModifier()->
        resetTextDataDetectorConfigWithEvent(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::SetOnCopy(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getTextModifier()->resetTextOnCopy(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(const std::u16string&)> callback = [vm, frameNode,
        func = panda::CopyableGlobal(vm, func)](const std::u16string& copyStr) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        panda::Local<panda::JSValueRef> params[PARAM_ARR_LENGTH_1] = {
            panda::StringRef::NewFromUtf16(vm, copyStr.c_str()) };
        func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_1);
    };
    GetArkUINodeModifiers()->getTextModifier()->setTextOnCopy(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::ResetOnCopy(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextModifier()->resetTextOnCopy(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::SetOnTextSelectionChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getTextModifier()->resetTextOnTextSelectionChange(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(int32_t, int32_t)> callback = [vm, frameNode,
        func = panda::CopyableGlobal(vm, func)](int32_t selectionStart, int32_t selectionEnd) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        panda::Local<panda::NumberRef> startParam = panda::NumberRef::New(vm, selectionStart);
        panda::Local<panda::NumberRef> endParam = panda::NumberRef::New(vm, selectionEnd);
        panda::Local<panda::JSValueRef> params[PARAM_ARR_LENGTH_2] = { startParam, endParam };
        func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_2);
    };
    GetArkUINodeModifiers()->getTextModifier()->setTextOnTextSelectionChange(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::ResetOnTextSelectionChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextModifier()->resetTextOnTextSelectionChange(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::SetSelectionMenuOptions(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    NG::OnCreateMenuCallback onCreateMenuCallback;
    NG::OnMenuItemClickCallback onMenuItemClickCallback;
    NG::OnPrepareMenuCallback onPrepareMenuCallback;
    if (!ArkTSUtils::ParseSelectionMenuOptions(
        runtimeCallInfo, vm, onCreateMenuCallback, onMenuItemClickCallback, onPrepareMenuCallback)) {
        GetArkUINodeModifiers()->getTextModifier()->resetTextSelectionMenuOptions(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUINodeModifiers()->getTextModifier()->setTextSelectionMenuOptions(nativeNode,
        reinterpret_cast<void*>(&onCreateMenuCallback), reinterpret_cast<void*>(&onMenuItemClickCallback),
        reinterpret_cast<void*>(&onPrepareMenuCallback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::ResetSelectionMenuOptions(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextModifier()->resetTextSelectionMenuOptions(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::SetHalfLeading(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    bool halfLeading = false;
    if (secondArg->IsBoolean()) {
        halfLeading = secondArg->ToBoolean(vm)->Value();
    }
    GetArkUINodeModifiers()->getTextModifier()->setTextHalfLeading(nativeNode, halfLeading);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::ResetHalfLeading(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextModifier()->resetTextHalfLeading(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::SetOnClick(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getTextModifier()->resetTextOnClick(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    auto containerId = Container::CurrentId();
    std::function<void(GestureEvent& info)> callback = [vm,
        func = panda::CopyableGlobal(vm, func), containerId, node = AceType::WeakClaim(frameNode)]
        (GestureEvent& info) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        ContainerScope scope(containerId);
        PipelineContext::SetCallBackNode(node);
        auto obj = FrameNodeBridge::CreateGestureEventInfo(vm, info);
        panda::Local<panda::JSValueRef> params[1] = { obj };
        func->Call(vm, func.ToLocal(), params, 1);
    };
    GetArkUINodeModifiers()->getTextModifier()->setTextOnClick(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::ResetOnClick(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextModifier()->resetTextOnClick(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::SetResponseRegion(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    int32_t length = thirdArg->Int32Value(vm);
    ArkUI_Float32 regionArray[length];
    int32_t regionUnits[length];
    if (!ArkTSUtils::ParseResponseRegion(vm, secondArg, regionArray, regionUnits, length)) {
        GetArkUINodeModifiers()->getTextModifier()->resetTextResponseRegion(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUINodeModifiers()->getTextModifier()->setTextResponseRegion(nativeNode, regionArray, regionUnits, length);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::ResetResponseRegion(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextModifier()->resetTextResponseRegion(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::SetEnableHapticFeedback(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    if (secondArg->IsBoolean()) {
        uint32_t value = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
        GetArkUINodeModifiers()->getTextModifier()->setTextEnableHapticFeedback(nativeNode, value);
    } else {
        GetArkUINodeModifiers()->getTextModifier()->resetTextEnableHapticFeedback(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::ResetEnableHapticFeedback(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextModifier()->resetTextEnableHapticFeedback(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::SetShaderStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto centerArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto radiusArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    auto angleArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    auto directionArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    auto repeatingArg = runtimeCallInfo->GetCallArgRef(NUM_5);
    auto colorsArg = runtimeCallInfo->GetCallArgRef(NUM_6);
    
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (centerArg->IsArray(vm) && (radiusArg->IsNumber() || radiusArg->IsString(vm))) {
        std::vector<ArkUIInt32orFloat32> values;
        ArkTSUtils::ParseGradientCenter(vm, centerArg, values);
        CalcDimension radius;
        auto hasRadius = ArkTSUtils::ParseJsDimensionVp(vm, radiusArg, radius, false);
        values.push_back({ .i32 = static_cast<ArkUI_Int32>(hasRadius) });
        values.push_back({ .f32 = static_cast<ArkUI_Float32>(radius.Value()) });
        values.push_back({ .i32 = static_cast<ArkUI_Int32>(radius.Unit()) });
        std::vector<ArkUIInt32orFloat32> colors;
        ArkTSUtils::ParseGradientColorStops(vm, colorsArg, colors);
        auto repeating = repeatingArg->IsBoolean() ? repeatingArg->BooleaValue(vm) : false;
        values.push_back({ .i32 = static_cast<ArkUI_Int32>(repeating) });
        GetArkUINodeModifiers()->getTextModifier()->setRadialGradient(
            nativeNode, values.data(), values.size(), colors.data(), colors.size());
    } else if ((angleArg->IsNumber() || angleArg->IsString(vm)) || directionArg->IsNumber()) {
        std::vector<ArkUIInt32orFloat32> values;
        ArkTSUtils::ParseGradientAngle(vm, angleArg, values);
        int32_t direction = static_cast<int32_t>(GradientDirection::NONE);
        ArkTSUtils::ParseJsInt32(vm, directionArg, direction);
        values.push_back({ .i32 = static_cast<ArkUI_Int32>(direction) });

        std::vector<ArkUIInt32orFloat32> colors;
        ArkTSUtils::ParseGradientColorStops(vm, colorsArg, colors);
        auto repeating = repeatingArg->IsBoolean() ? repeatingArg->BooleaValue(vm) : false;
        values.push_back({ .i32 = static_cast<ArkUI_Int32>(repeating) });
        GetArkUINodeModifiers()->getTextModifier()->setLinearGradient(
            nativeNode, values.data(), values.size(), colors.data(), colors.size());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::ResetShaderStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextModifier()->resetTextGradient(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::SetMarqueeOptions(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> startArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> fromStartArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> stepArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> loopArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    Local<JSValueRef> delayArg = runtimeCallInfo->GetCallArgRef(NUM_5);
    Local<JSValueRef> fadeoutArg = runtimeCallInfo->GetCallArgRef(NUM_6);
    Local<JSValueRef> marqueeStartPolicyArg = runtimeCallInfo->GetCallArgRef(NUM_7);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    auto textMarqueeOptions = std::make_unique<ArkUITextMarqueeOptions>();
    textMarqueeOptions->start = startArg->IsBoolean() ? startArg->ToBoolean(vm)->Value() : true;
    textMarqueeOptions->fromStart = fromStartArg->IsBoolean() ? fromStartArg->ToBoolean(vm)->Value() : true;
    textMarqueeOptions->step = stepArg->IsNumber() ?
        Dimension(stepArg->ToNumber(vm)->Value(), DimensionUnit::VP).ConvertToPx() :
        DEFAULT_MARQUEE_STEP_VALUE.ConvertToPx();
    textMarqueeOptions->loop = loopArg->IsNumber() ? loopArg->Int32Value(vm) : -1;
    textMarqueeOptions->delay = delayArg->IsNumber() ? delayArg->Int32Value(vm) : 0;
    textMarqueeOptions->fadeout = fadeoutArg->IsBoolean() ? fadeoutArg->ToBoolean(vm)->Value() : false;
    textMarqueeOptions->marqueeStartPolicy = marqueeStartPolicyArg->IsNumber() ?
        marqueeStartPolicyArg->Int32Value(vm) : 0;

    bool isValid = startArg->IsBoolean() || fromStartArg->IsBoolean() || stepArg->IsNumber() || loopArg->IsNumber()
        || delayArg->IsNumber() || fadeoutArg->IsBoolean() || marqueeStartPolicyArg->IsNumber();
    if (isValid) {
        GetArkUINodeModifiers()->getTextModifier()->setTextMarqueeOptions(nativeNode, textMarqueeOptions.get());
    } else {
        GetArkUINodeModifiers()->getTextModifier()->resetTextMarqueeOptions(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::ResetMarqueeOptions(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextModifier()->resetTextMarqueeOptions(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::SetOnMarqueeStateChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getTextModifier()->resetOnMarqueeStateChange(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(int32_t)> callback = [vm, frameNode,
        func = panda::CopyableGlobal(vm, func)](int32_t state) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        panda::Local<panda::NumberRef> stateParam = panda::NumberRef::New(vm, state);
        panda::Local<panda::JSValueRef> params[PARAM_ARR_LENGTH_1] = { stateParam };
        func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_1);
    };
    GetArkUINodeModifiers()->getTextModifier()->setOnMarqueeStateChange(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::ResetOnMarqueeStateChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextModifier()->resetOnMarqueeStateChange(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::SetEnableAutoSpacing(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    uint32_t enableAutoSpacing = false;
    if (secondArg->IsBoolean()) {
        enableAutoSpacing = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
    }
    GetArkUINodeModifiers()->getTextModifier()->setEnableAutoSpacing(nativeNode, enableAutoSpacing);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::ResetEnableAutoSpacing(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextModifier()->resetEnableAutoSpacing(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::SetTextVerticalAlign(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    uint32_t textVerticalAlign = static_cast<uint32_t>(TextVerticalAlign::BASELINE);
    if (secondArg->IsNumber()) {
        textVerticalAlign = static_cast<uint32_t>(secondArg->Int32Value(vm));
    }
    GetArkUINodeModifiers()->getTextModifier()->setTextVerticalAlign(nativeNode, textVerticalAlign);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::ResetTextVerticalAlign(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextModifier()->resetTextVerticalAlign(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
