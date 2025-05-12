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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_span_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_frame_node_bridge.h"

#include <string>

#include "base/geometry/calc_dimension.h"
#include "base/geometry/dimension.h"
#include "bridge/declarative_frontend/engine/jsi/jsi_types.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "core/components/common/layout/constants.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int SIZE_OF_TEXT_CASES = 2;
constexpr TextDecorationStyle DEFAULT_DECORATION_STYLE = TextDecorationStyle::SOLID;
constexpr Color DEFAULT_DECORATION_COLOR = Color(0xff000000);
const std::string DEFAULT_FONT_WEIGHT = "400";
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int NUM_4 = 4;
constexpr int NUM_5 = 5;
constexpr int NUM_6 = 6;
constexpr int NUM_7 = 7;
const std::vector<OHOS::Ace::FontStyle> FONT_STYLES = { OHOS::Ace::FontStyle::NORMAL, OHOS::Ace::FontStyle::ITALIC };

void ParseOuterBorderRadius(ArkUIRuntimeCallInfo* runtimeCallInfo, EcmaVM* vm, std::vector<ArkUI_Float32>& values,
    std::vector<ArkUI_Int32>& units, int32_t argsIndex)
{
    Local<JSValueRef> topLeftArgs = runtimeCallInfo->GetCallArgRef(argsIndex);
    Local<JSValueRef> topRightArgs = runtimeCallInfo->GetCallArgRef(argsIndex + NUM_1);
    Local<JSValueRef> bottomLeftArgs = runtimeCallInfo->GetCallArgRef(argsIndex + NUM_2);
    Local<JSValueRef> bottomRightArgs = runtimeCallInfo->GetCallArgRef(argsIndex + NUM_3);

    std::optional<CalcDimension> topLeftOptional;
    std::optional<CalcDimension> topRightOptional;
    std::optional<CalcDimension> bottomLeftOptional;
    std::optional<CalcDimension> bottomRightOptional;

    ArkTSUtils::ParseOuterBorder(vm, topLeftArgs, topLeftOptional);
    ArkTSUtils::ParseOuterBorder(vm, topRightArgs, topRightOptional);
    ArkTSUtils::ParseOuterBorder(vm, bottomLeftArgs, bottomLeftOptional);
    ArkTSUtils::ParseOuterBorder(vm, bottomRightArgs, bottomRightOptional);

    ArkTSUtils::PushOuterBorderDimensionVector(topLeftOptional, values, units);
    ArkTSUtils::PushOuterBorderDimensionVector(topRightOptional, values, units);
    ArkTSUtils::PushOuterBorderDimensionVector(bottomLeftOptional, values, units);
    ArkTSUtils::PushOuterBorderDimensionVector(bottomRightOptional, values, units);
}

bool ParseTextShadow(ArkUIRuntimeCallInfo* runtimeCallInfo, uint32_t length,
    std::vector<ArkUITextShadowStruct>& textShadowArray)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, false);
    Local<JSValueRef> radiusArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> typeArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> offsetXArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    Local<JSValueRef> offsetYArg = runtimeCallInfo->GetCallArgRef(NUM_5);
    Local<JSValueRef> fillArg = runtimeCallInfo->GetCallArgRef(NUM_6);
    auto radiusArray = std::make_unique<double[]>(length);
    auto typeArray = std::make_unique<uint32_t[]>(length);
    auto colorArray = std::make_unique<uint32_t[]>(length);
    auto offsetXArray = std::make_unique<double[]>(length);
    auto offsetYArray = std::make_unique<double[]>(length);
    auto fillArray = std::make_unique<uint32_t[]>(length);
    bool radiusParseResult =
        ArkTSUtils::ParseArray<double>(vm, radiusArg, radiusArray.get(), length, ArkTSUtils::parseShadowRadius);
    bool typeParseResult =
        ArkTSUtils::ParseArray<uint32_t>(vm, typeArg, typeArray.get(), length, ArkTSUtils::parseShadowType);
    bool colorParseResult =
        ArkTSUtils::ParseArray<uint32_t>(vm, colorArg, colorArray.get(), length, ArkTSUtils::parseShadowColor);
    bool offsetXParseResult =
        ArkTSUtils::ParseArray<double>(vm, offsetXArg, offsetXArray.get(), length, ArkTSUtils::parseShadowOffset);
    bool offsetYParseResult =
        ArkTSUtils::ParseArray<double>(vm, offsetYArg, offsetYArray.get(), length, ArkTSUtils::parseShadowOffset);
    bool fillParseResult =
        ArkTSUtils::ParseArray<uint32_t>(vm, fillArg, fillArray.get(), length, ArkTSUtils::parseShadowFill);
    if (!radiusParseResult || !colorParseResult || !offsetXParseResult || !offsetYParseResult || !fillParseResult ||
        !typeParseResult) {
        return false;
    }
    for (uint32_t i = 0; i < length; i++) {
        ArkUITextShadowStruct textShadow;
        textShadow.radius = radiusArray[i];
        textShadow.type = typeArray[i];
        textShadow.color = colorArray[i];
        textShadow.offsetX = offsetXArray[i];
        textShadow.offsetY = offsetYArray[i];
        textShadow.fill = fillArray[i];
        textShadowArray.emplace_back(textShadow);
    }
    return true;
}
} // namespace

ArkUINativeModuleValue SpanBridge::SetSpanSrc(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    std::string src;
    if (!ArkTSUtils::ParseJsString(vm, secondArg, src)) {
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUINodeModifiers()->getSpanModifier()->setSpanSrc(nativeNode, src.c_str());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SpanBridge::SetTextCase(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsNumber() && secondArg->Int32Value(vm) >= NUM_0 &&
        secondArg->Int32Value(vm) <= SIZE_OF_TEXT_CASES) {
        GetArkUINodeModifiers()->getSpanModifier()->setSpanTextCase(nativeNode, secondArg->Int32Value(vm));
    } else {
        GetArkUINodeModifiers()->getSpanModifier()->resetSpanTextCase(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SpanBridge::ResetTextCase(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSpanModifier()->resetSpanTextCase(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SpanBridge::SetFontWeight(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    std::string weight = DEFAULT_FONT_WEIGHT;
    if (!secondArg->IsNull()) {
        if (secondArg->IsNumber()) {
            weight = std::to_string(secondArg->Int32Value(vm));
        } else if ((secondArg->IsString(vm) || secondArg->IsObject(vm)) &&
            (!(ArkTSUtils::ParseJsString(vm, secondArg, weight)))) {
            return panda::JSValueRef::Undefined(vm);
        }
    }

    GetArkUINodeModifiers()->getSpanModifier()->setSpanFontWeight(nativeNode,
        static_cast<ArkUI_Int32>(Framework::ConvertStrToFontWeight(weight)));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SpanBridge::ResetFontWeight(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSpanModifier()->resetSpanFontWeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SpanBridge::SetLineHeight(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    CalcDimension lineHeight(0.0, DimensionUnit::PX);
    if (!ArkTSUtils::ParseJsDimensionFpNG(vm, secondArg, lineHeight) || lineHeight.IsNegative()) {
        lineHeight.Reset();
    }
    GetArkUINodeModifiers()->getSpanModifier()->setSpanLineHeight(
        nativeNode, lineHeight.Value(), static_cast<int8_t>(lineHeight.Unit()));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SpanBridge::ResetLineHeight(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSpanModifier()->resetSpanLineHeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SpanBridge::SetFontStyle(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsNumber()) {
        int32_t value = secondArg->Int32Value(vm);
        if (value >= 0 && value < static_cast<int32_t>(FONT_STYLES.size())) {
            GetArkUINodeModifiers()->getSpanModifier()->setSpanFontStyle(nativeNode, value);
        } else {
            GetArkUINodeModifiers()->getSpanModifier()->resetSpanFontStyle(nativeNode);
            return panda::JSValueRef::Undefined(vm);
        }
    } else {
        GetArkUINodeModifiers()->getSpanModifier()->resetSpanFontStyle(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SpanBridge::ResetFontStyle(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSpanModifier()->resetSpanFontStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SpanBridge::SetFontSize(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto theme = GetTheme<TextTheme>();
    CHECK_NULL_RETURN(theme, panda::JSValueRef::Undefined(vm));

    CalcDimension fontSize = theme->GetTextStyle().GetFontSize();
    if (!ArkTSUtils::ParseJsDimensionFpNG(vm, secondArg, fontSize, false) || fontSize.IsNegative()) {
        GetArkUINodeModifiers()->getSpanModifier()->resetSpanFontSize(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUINodeModifiers()->getSpanModifier()->setSpanFontSize(nativeNode, fontSize.Value(),
        static_cast<int8_t>(fontSize.Unit()));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SpanBridge::ResetFontSize(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSpanModifier()->resetSpanFontSize(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SpanBridge::SetFontFamily(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    std::vector<std::string> fontFamilies;
    if (!ArkTSUtils::ParseJsFontFamilies(vm, secondArg, fontFamilies)) {
        GetArkUINodeModifiers()->getSpanModifier()->resetSpanFontFamily(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto families = std::make_unique<char *[]>(fontFamilies.size());
    for (uint32_t i = 0; i < fontFamilies.size(); i++) {
        families[i] = const_cast<char *>(fontFamilies.at(i).c_str());
    }
    GetArkUINodeModifiers()->getSpanModifier()->setSpanFontFamily(nativeNode,
        const_cast<const char **>(families.get()), fontFamilies.size());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SpanBridge::ResetFontFamily(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    GetArkUINodeModifiers()->getSpanModifier()->resetSpanFontFamily(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SpanBridge::SetDecoration(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> fourthArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    int32_t textDecoration = static_cast<int32_t>(TextDecoration::NONE);
    Color color = DEFAULT_DECORATION_COLOR;
    int32_t style = static_cast<int32_t>(DEFAULT_DECORATION_STYLE);
    if (secondArg->IsInt()) {
        textDecoration = secondArg->Int32Value(vm);
    }
    if (!ArkTSUtils::ParseJsColorAlpha(vm, thirdArg, color)) {
        color = DEFAULT_DECORATION_COLOR;
    }
    if (fourthArg->IsInt()) {
        style = fourthArg->Int32Value(vm);
    }
    GetArkUINodeModifiers()->getSpanModifier()->setSpanDecoration(nativeNode, textDecoration, color.GetValue(), style);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SpanBridge::ResetDecoration(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSpanModifier()->resetSpanDecoration(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SpanBridge::SetFontColor(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto theme = GetTheme<TextTheme>();
    CHECK_NULL_RETURN(theme, panda::JSValueRef::Undefined(vm));

    Color textColor = theme->GetTextStyle().GetTextColor();
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, textColor)) {
        GetArkUINodeModifiers()->getSpanModifier()->resetSpanFontColor(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUINodeModifiers()->getSpanModifier()->setSpanFontColor(nativeNode, textColor.GetValue());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SpanBridge::ResetFontColor(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    GetArkUINodeModifiers()->getSpanModifier()->resetSpanFontColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SpanBridge::SetLetterSpacing(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    struct ArkUIStringAndFloat letterSpacingValue = { 0.0, nullptr };
    std::string tempValueStr = "";
    if (secondArg->IsNumber()) {
        letterSpacingValue.value = secondArg->ToNumber(vm)->Value();
        GetArkUINodeModifiers()->getSpanModifier()->setSpanLetterSpacing(nativeNode, &letterSpacingValue);
    } else if ((secondArg->IsString(vm) || secondArg->IsObject(vm)) &&
        ArkTSUtils::ParseJsString(vm, secondArg, tempValueStr)) {
        letterSpacingValue.valueStr = tempValueStr.c_str();
        GetArkUINodeModifiers()->getSpanModifier()->setSpanLetterSpacing(nativeNode, &letterSpacingValue);
    } else {
        GetArkUINodeModifiers()->getSpanModifier()->resetSpanLetterSpacing(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SpanBridge::ResetLetterSpacing(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSpanModifier()->resetSpanLetterSpacing(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SpanBridge::SetBaselineOffset(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    CalcDimension result;
    if (secondArg->IsObject(vm) && ArkTSUtils::ParseJsLengthMetrics(vm, secondArg, result) &&
        result.Unit() != DimensionUnit::PERCENT && !std::isnan(result.Value())) {
        GetArkUINodeModifiers()->getSpanModifier()->setSpanBaselineOffset(
            nativeNode, result.Value(), static_cast<int8_t>(result.Unit()));
    } else {
        GetArkUINodeModifiers()->getSpanModifier()->resetSpanBaselineOffset(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SpanBridge::ResetBaselineOffset(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSpanModifier()->resetSpanBaselineOffset(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SpanBridge::SetFont(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> sizeArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> weightArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> familyArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> styleArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto theme = GetTheme<TextTheme>();
    CHECK_NULL_RETURN(theme, panda::JSValueRef::Undefined(vm));
    CalcDimension fontSize;
    if (ArkTSUtils::ParseJsDimensionFpNG(vm, sizeArg, fontSize, false) && !fontSize.IsNegative()) {
        GetArkUINodeModifiers()->getSpanModifier()->setSpanFontSize(
            nativeNode, fontSize.Value(), static_cast<int8_t>(fontSize.Unit()));
    } else {
        GetArkUINodeModifiers()->getSpanModifier()->resetSpanFontSize(nativeNode);
    }

    std::string weight = DEFAULT_FONT_WEIGHT;
    if (weightArg->IsNull() || weightArg->IsUndefined()) {
        GetArkUINodeModifiers()->getSpanModifier()->resetSpanFontWeight(nativeNode);
    } else {
        if (weightArg->IsNumber()) {
            weight = std::to_string(weightArg->Int32Value(vm));
        } else if (weightArg->IsString(vm)) {
            weight = weightArg->ToString(vm)->ToString(vm);
        }
        GetArkUINodeModifiers()->getSpanModifier()->setSpanFontWeight(
            nativeNode, static_cast<ArkUI_Int32>(Framework::ConvertStrToFontWeight(weight)));
    }
    if (styleArg->IsInt()) {
        int32_t style = styleArg->Int32Value(vm);
        if (style >= 0 && style < static_cast<int32_t>(FONT_STYLES.size())) {
            GetArkUINodeModifiers()->getSpanModifier()->setSpanFontStyle(nativeNode, style);
        } else {
            GetArkUINodeModifiers()->getSpanModifier()->resetSpanFontStyle(nativeNode);
        }
    } else {
        GetArkUINodeModifiers()->getSpanModifier()->resetSpanFontStyle(nativeNode);
    }
    std::vector<std::string> fontFamilies;
    if (ArkTSUtils::ParseJsFontFamilies(vm, familyArg, fontFamilies)) {
        uint32_t familyLength = fontFamilies.size();
        auto families = std::make_unique<const char* []>(familyLength);
        for (uint32_t i = 0; i < fontFamilies.size(); i++) {
            families[i] = fontFamilies[i].c_str();
        }
        GetArkUINodeModifiers()->getSpanModifier()->setSpanFontFamily(
            nativeNode, const_cast<const char**>(families.get()), fontFamilies.size());
    } else {
        GetArkUINodeModifiers()->getSpanModifier()->resetSpanFontFamily(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SpanBridge::ResetFont(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSpanModifier()->resetSpanFont(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SpanBridge::SetTextBackgroundStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Color color;
    std::vector<ArkUI_Float32> radiusArray;
    std::vector<ArkUI_Int32> valueUnits;
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (!(ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color))) {
        color = Color::TRANSPARENT;
    }
    ParseOuterBorderRadius(runtimeCallInfo, vm, radiusArray, valueUnits, NUM_2); // Border Radius args start index
    GetArkUINodeModifiers()->getSpanModifier()->setSpanTextBackgroundStyle(
        nativeNode, color.GetValue(), radiusArray.data(), valueUnits.data(), static_cast<int32_t>(radiusArray.size()));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SpanBridge::ResetTextBackgroundStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSpanModifier()->resetSpanTextBackgroundStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SpanBridge::SetTextShadow(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> lengthArg = runtimeCallInfo->GetCallArgRef(NUM_7);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    uint32_t length;
    if (!lengthArg->IsNumber() || lengthArg->Uint32Value(vm) == 0) {
        return panda::JSValueRef::Undefined(vm);
    }
    length = lengthArg->Uint32Value(vm);
    std::vector<ArkUITextShadowStruct> textShadowArray;
    ParseTextShadow(runtimeCallInfo, length, textShadowArray);
    GetArkUINodeModifiers()->getSpanModifier()->setTextShadow(nativeNode, textShadowArray.data(), length);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SpanBridge::ResetTextShadow(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSpanModifier()->resetTextShadow(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SpanBridge::SetAccessibilityText(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsString(vm)) {
        std::string stringValue = secondArg->ToString(vm)->ToString(vm);
        GetArkUINodeModifiers()->getSpanModifier()->setAccessibilityText(nativeNode, stringValue.c_str());
    } else {
        GetArkUINodeModifiers()->getSpanModifier()->resetAccessibilityText(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SpanBridge::ResetAccessibilityText(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSpanModifier()->resetAccessibilityText(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SpanBridge::SetAccessibilityDescription(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsString(vm)) {
        std::string stringValue = secondArg->ToString(vm)->ToString(vm);
        GetArkUINodeModifiers()->getSpanModifier()->setAccessibilityDescription(nativeNode, stringValue.c_str());
    } else {
        GetArkUINodeModifiers()->getSpanModifier()->resetAccessibilityDescription(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SpanBridge::ResetAccessibilityDescription(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSpanModifier()->resetAccessibilityDescription(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SpanBridge::SetAccessibilityLevel(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsString(vm)) {
        std::string stringValue = secondArg->ToString(vm)->ToString(vm);
        GetArkUINodeModifiers()->getSpanModifier()->setAccessibilityLevel(nativeNode, stringValue.c_str());
    } else {
        GetArkUINodeModifiers()->getSpanModifier()->resetAccessibilityLevel(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SpanBridge::ResetAccessibilityLevel(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSpanModifier()->resetAccessibilityLevel(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SpanBridge::SetOnHover(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    if (secondArg->IsFunction(vm)) {
        panda::Local<panda::FunctionRef> func = secondArg->ToObject(vm);
        OnHoverFunc callback = [vm, frameNode,
            func = panda::CopyableGlobal(vm, func)](bool isHover, HoverInfo& info) {
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));

            auto obj = FrameNodeBridge::CreateHoverInfo(vm, info);
            obj->SetNativePointerFieldCount(vm, 1);
            obj->SetNativePointerField(vm, 0, static_cast<void*>(&info));

            panda::Local<panda::JSValueRef> params[NUM_2] = {
                panda::BooleanRef::New(vm, isHover), obj };
            func->Call(vm, func.ToLocal(), params, NUM_2);
        };
        GetArkUINodeModifiers()->getSpanModifier()->setSpanOnHover(nativeNode, reinterpret_cast<void*>(&callback));
    } else {
        GetArkUINodeModifiers()->getSpanModifier()->resetSpanOnHover(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SpanBridge::ResetOnHover(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getSpanModifier()->resetSpanOnHover(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
