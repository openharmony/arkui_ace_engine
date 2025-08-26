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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "core/components/common/layout/constants.h"
#include "bridge/declarative_frontend/engine/jsi/jsi_types.h"

#include "core/common/resource/resource_object.h"
#include "core/common/resource/resource_parse_utils.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int SIZE_OF_TEXT_CASES = 2;
constexpr TextDecorationStyle DEFAULT_DECORATION_STYLE = TextDecorationStyle::SOLID;
constexpr Ace::FontStyle DEFAULT_FONT_STYLE = Ace::FontStyle::NORMAL;
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

bool ParseTextShadow(ArkUIRuntimeCallInfo* runtimeCallInfo, uint32_t length,
    std::vector<ArkUITextShadowStruct>& textShadowArray,
    std::vector<RefPtr<ResourceObject>>& radiusResArr, std::vector<RefPtr<ResourceObject>>& colorResArr,
    std::vector<RefPtr<ResourceObject>>& offsetXResArr, std::vector<RefPtr<ResourceObject>>& offsetYResArr,
    const std::optional<NodeInfo>& nodeInfo = std::nullopt)
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

    bool radiusParseResult = ArkTSUtils::ParseArrayWithResObj<double>(vm, radiusArg, radiusArray.get(), length,
        ArkTSUtils::parseShadowRadiusWithResObj, radiusResArr);
    bool typeParseResult = ArkTSUtils::ParseArray<uint32_t>(vm, typeArg, typeArray.get(), length,
        ArkTSUtils::parseShadowType);
    bool colorParseResult = ArkTSUtils::ParseArrayWithResObj<uint32_t>(vm, colorArg, colorArray.get(), length,
        ArkTSUtils::parseShadowColorWithResObj, colorResArr, nodeInfo);
    bool offsetXParseResult = ArkTSUtils::ParseArrayWithResObj<double>(vm, offsetXArg, offsetXArray.get(), length,
        ArkTSUtils::parseShadowOffsetWithResObj, offsetXResArr);
    bool offsetYParseResult = ArkTSUtils::ParseArrayWithResObj<double>(vm, offsetYArg, offsetYArray.get(), length,
        ArkTSUtils::parseShadowOffsetWithResObj, offsetYResArr);
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
    RefPtr<ResourceObject> resObj;
    if (!secondArg->IsNull()) {
        if (secondArg->IsNumber()) {
            weight = std::to_string(secondArg->Int32Value(vm));
        } else if ((secondArg->IsString(vm) || secondArg->IsObject(vm)) &&
            (!(ArkTSUtils::ParseJsString(vm, secondArg, weight, resObj)))) {
            return panda::JSValueRef::Undefined(vm);
        }
    }

    GetArkUINodeModifiers()->getSpanModifier()->setSpanFontWeight(nativeNode,
        static_cast<ArkUI_Int32>(Framework::ConvertStrToFontWeight(weight)), AceType::RawPtr(resObj));
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
    RefPtr<ResourceObject> lineHeightObj;
    if (!ArkTSUtils::ParseJsDimensionFpNG(vm, secondArg, lineHeight, lineHeightObj) || lineHeight.IsNegative()) {
        lineHeight.Reset();
    }
    GetArkUINodeModifiers()->getSpanModifier()->setSpanLineHeight(
        nativeNode, lineHeight.Value(), static_cast<int8_t>(lineHeight.Unit()), AceType::RawPtr(lineHeightObj));
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
    RefPtr<ResourceObject> fontSizeResObj;
    if (!ArkTSUtils::ParseJsDimensionFpNG(vm, secondArg, fontSize, fontSizeResObj, false) || fontSize.IsNegative()) {
        fontSize = theme->GetTextStyle().GetFontSize();
    }
    GetArkUINodeModifiers()->getSpanModifier()->setSpanFontSize(nativeNode, fontSize.Value(),
        static_cast<int8_t>(fontSize.Unit()), AceType::RawPtr(fontSizeResObj));
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
    RefPtr<ResourceObject> resourceObject;
    if (!ArkTSUtils::ParseJsFontFamilies(vm, secondArg, fontFamilies, resourceObject)) {
        GetArkUINodeModifiers()->getSpanModifier()->resetSpanFontFamily(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto families = std::make_unique<char *[]>(fontFamilies.size());
    for (uint32_t i = 0; i < fontFamilies.size(); i++) {
        families[i] = const_cast<char *>(fontFamilies.at(i).c_str());
    }
    GetArkUINodeModifiers()->getSpanModifier()->setSpanFontFamily(nativeNode,
        const_cast<const char **>(families.get()), fontFamilies.size(), AceType::RawPtr(resourceObject));
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
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!ArkTSUtils::ParseJsColorAlpha(vm, thirdArg, color, resourceObject, nodeInfo)) {
        color = DEFAULT_DECORATION_COLOR;
    }
    if (fourthArg->IsInt()) {
        style = fourthArg->Int32Value(vm);
    }
    if (!ArkTSUtils::ParseJsDouble(vm, fifthArg, lineThicknessScale)) {
        lineThicknessScale = 1.0;
    }
    lineThicknessScale = lineThicknessScale < 0 ? 1.0 : lineThicknessScale;
    GetArkUINodeModifiers()->getSpanModifier()->setSpanDecoration(
        nativeNode, textDecoration, color.GetValue(), AceType::RawPtr(resourceObject),
        style, static_cast<float>(lineThicknessScale));
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
    RefPtr<ResourceObject> colorResObj;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, textColor, colorResObj, nodeInfo)) {
        textColor = theme->GetTextStyle().GetTextColor();
    }
    GetArkUINodeModifiers()->getSpanModifier()->setSpanFontColor(
        nativeNode, textColor.GetValue(), AceType::RawPtr(colorResObj));
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
    RefPtr<ResourceObject> resObj;
    if (secondArg->IsNumber()) {
        letterSpacingValue.value = secondArg->ToNumber(vm)->Value();
        GetArkUINodeModifiers()->getSpanModifier()->setSpanLetterSpacing(nativeNode, &letterSpacingValue,
            AceType::RawPtr(resObj));
    } else if ((secondArg->IsString(vm) || secondArg->IsObject(vm)) &&
        ArkTSUtils::ParseJsString(vm, secondArg, tempValueStr, resObj)) {
        letterSpacingValue.valueStr = tempValueStr.c_str();
        GetArkUINodeModifiers()->getSpanModifier()->setSpanLetterSpacing(nativeNode, &letterSpacingValue,
            AceType::RawPtr(resObj));
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
    RefPtr<ResourceObject> resourceObject;
    if (secondArg->IsObject(vm) && ArkTSUtils::ParseJsLengthMetrics(vm, secondArg, result, resourceObject) &&
        result.Unit() != DimensionUnit::PERCENT && !std::isnan(result.Value())) {
        GetArkUINodeModifiers()->getSpanModifier()->setSpanBaselineOffset(
            nativeNode, result.Value(), static_cast<int8_t>(result.Unit()), AceType::RawPtr(resourceObject));
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
    ArkUIFontStruct fontInfo;
    auto theme = GetTheme<TextTheme>();
    CHECK_NULL_RETURN(theme, panda::JSValueRef::Undefined(vm));

    CalcDimension fontSize = theme->GetTextStyle().GetFontSize();
    RefPtr<ResourceObject> fontSizeObj;
    if (sizeArg->IsNull() || !ArkTSUtils::ParseJsDimensionFpNG(vm, sizeArg, fontSize, fontSizeObj, false) ||
        fontSize.IsNegative()) {
        fontSize = theme->GetTextStyle().GetFontSize();
    }
    fontInfo.fontSizeNumber = fontSize.Value();
    fontInfo.fontSizeUnit = static_cast<int8_t>(fontSize.Unit());

    std::string weight = DEFAULT_FONT_WEIGHT;
    if (!weightArg->IsNull()) {
        if (weightArg->IsNumber()) {
            weight = std::to_string(weightArg->Int32Value(vm));
        } else if (weightArg->IsString(vm)) {
            weight = weightArg->ToString(vm)->ToString(vm);
        }
    }
    fontInfo.fontWeight = static_cast<uint8_t>(Framework::ConvertStrToFontWeight(weight));
    int32_t style = static_cast<int32_t>(DEFAULT_FONT_STYLE);
    if (styleArg->IsInt()) {
        style = styleArg->Int32Value(vm);
        if (style <= 0 || style > static_cast<int32_t>(FONT_STYLES.size())) {
            style = static_cast<int32_t>(DEFAULT_FONT_STYLE);
        }
    }
    fontInfo.fontStyle = static_cast<uint8_t>(style);
    std::vector<std::string> fontFamilies;
    RefPtr<ResourceObject> fontFamiliesObject;
    fontInfo.fontFamilies = nullptr;
    if (!familyArg->IsNull() && ArkTSUtils::ParseJsFontFamilies(vm, familyArg, fontFamilies, fontFamiliesObject)) {
        fontInfo.familyLength = fontFamilies.size();
        auto families = std::make_unique<const char* []>(fontInfo.familyLength);
        for (uint32_t i = 0; i < fontFamilies.size(); i++) {
            families[i] = fontFamilies[i].c_str();
        }
        fontInfo.fontFamilies = families.get();
        GetArkUINodeModifiers()->getSpanModifier()->setSpanFont(nativeNode, &fontInfo);
    } else {
        GetArkUINodeModifiers()->getSpanModifier()->setSpanFont(nativeNode, &fontInfo);
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
    std::shared_ptr<TextBackgroundStyle> style = std::make_shared<TextBackgroundStyle>();
    RefPtr<ResourceObject> colorResObj;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!(ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color, colorResObj, nodeInfo))) {
        color = Color::TRANSPARENT;
    }
    ArkTSUtils::ParseOuterBorderRadius(runtimeCallInfo, vm, radiusArray, valueUnits, NUM_2, style);
    ArkTSUtils::SetTextBackgroundStyle(style, color, colorResObj, radiusArray.data(), valueUnits.data());
    GetArkUINodeModifiers()->getSpanModifier()->setSpanTextBackgroundStyle(
        nativeNode, color.GetValue(), radiusArray.data(), valueUnits.data(), static_cast<int32_t>(radiusArray.size()),
        style.get());
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
    std::vector<RefPtr<ResourceObject>> radiusResArr;
    std::vector<RefPtr<ResourceObject>> colorResArr;
    std::vector<RefPtr<ResourceObject>> offsetXResArr;
    std::vector<RefPtr<ResourceObject>> offsetYResArr;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    ParseTextShadow(runtimeCallInfo, length, textShadowArray, radiusResArr, colorResArr, offsetXResArr, offsetYResArr,
        nodeInfo);
    GetArkUINodeModifiers()->getSpanModifier()->setTextShadow(nativeNode, textShadowArray.data(), length,
        static_cast<void*>(&radiusResArr), static_cast<void*>(&colorResArr),
        static_cast<void*>(&offsetXResArr), static_cast<void*>(&offsetYResArr));
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
