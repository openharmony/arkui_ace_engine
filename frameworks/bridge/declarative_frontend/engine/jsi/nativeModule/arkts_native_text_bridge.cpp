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
#include "core/components/common/properties/shadow.h"
#include "frameworks/base/geometry/calc_dimension.h"
#include "frameworks/base/geometry/dimension.h"
#include "frameworks/bridge/declarative_frontend/engine/js_types.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/jsi_value_conversions.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_shape_abstract.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int SIZE_OF_TEXT_CASES = 2;
constexpr double DEFAULT_SPAN_FONT_SIZE = 16;
constexpr DimensionUnit DEFAULT_SPAN_FONT_UNIT = DimensionUnit::FP;
constexpr TextDecorationStyle DEFAULT_DECORATION_STYLE = TextDecorationStyle::SOLID;
constexpr Ace::FontStyle DEFAULT_FONT_STYLE = Ace::FontStyle::NORMAL;
const Color DEFAULT_DECORATION_COLOR = Color::BLACK;
const std::string DEFAULT_FONT_WEIGHT = "400";
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
} // namespace

ArkUINativeModuleValue TextBridge::SetFontWeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsString()) {
        std::string weight = secondArg->ToString(vm)->ToString();
        GetArkUINodeModifiers()->getTextModifier()->setFontWeightStr(nativeNode, weight.c_str());
    } else {
        GetArkUINodeModifiers()->getTextModifier()->resetFontWeight(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::ResetFontWeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextModifier()->resetFontWeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::SetFontStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
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
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextModifier()->resetFontStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::SetTextAlign(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
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
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextModifier()->resetTextAlign(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::SetFontColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Color color;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color)) {
        GetArkUINodeModifiers()->getTextModifier()->resetFontColor(nativeNode);
    } else {
        GetArkUINodeModifiers()->getTextModifier()->setFontColor(nativeNode, color.GetValue());
    }
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue TextBridge::ResetFontColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextModifier()->resetFontColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::SetForegroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto colorArg = runtimeCallInfo->GetCallArgRef(1);
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
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    GetArkUINodeModifiers()->getTextModifier()->resetTextForegroundColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::SetFontSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    CalcDimension fontSize;
    if (!ArkTSUtils::ParseJsDimensionFp(vm, secondArg, fontSize)) {
        GetArkUINodeModifiers()->getTextModifier()->resetFontSize(nativeNode);
    } else {
        GetArkUINodeModifiers()->getTextModifier()->setFontSize(
            nativeNode, fontSize.Value(), static_cast<int>(fontSize.Unit()));
    }
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue TextBridge::ResetFontSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextModifier()->resetFontSize(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::SetLineHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    CalcDimension lineHeight(0.0, DEFAULT_SPAN_FONT_UNIT);
    if (!ArkTSUtils::ParseJsDimensionFp(vm, secondArg, lineHeight)) {
        lineHeight.Reset();
    }
    if (lineHeight.IsNegative()) {
        lineHeight.Reset();
    }
    GetArkUINodeModifiers()->getTextModifier()->setTextLineHeight(
        nativeNode, lineHeight.Value(), static_cast<int8_t>(lineHeight.Unit()));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::ResetLineHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextModifier()->resetTextLineHeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::SetTextOverflow(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
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
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextModifier()->resetTextOverflow(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::SetDecoration(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    int32_t textDecoration = static_cast<int32_t>(TextDecoration::NONE);
    Color color = DEFAULT_DECORATION_COLOR;
    if (secondArg->IsInt()) {
        textDecoration = secondArg->Int32Value(vm);
    }
    if (!ArkTSUtils::ParseJsColorAlpha(vm, thirdArg, color)) {
        color = DEFAULT_DECORATION_COLOR;
    }
    GetArkUINodeModifiers()->getTextModifier()->setTextDecoration(
        nativeNode, textDecoration, color.GetValue(), static_cast<int32_t>(DEFAULT_DECORATION_STYLE));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::ResetDecoration(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextModifier()->resetTextDecoration(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::SetTextCase(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
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
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextModifier()->resetTextCase(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::SetMaxLines(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsNumber() && secondArg->ToNumber(vm)->Value() >= NUM_0) {
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
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextModifier()->resetTextMaxLines(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::SetMinFontSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    CalcDimension fontSize;
    if (ArkTSUtils::ParseJsDimensionFp(vm, secondArg, fontSize)) {
        GetArkUINodeModifiers()->getTextModifier()->setTextMinFontSize(
            nativeNode, fontSize.Value(), static_cast<int8_t>(fontSize.Unit()));
    } else {
        GetArkUINodeModifiers()->getTextModifier()->resetTextMinFontSize(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::ReSetMinFontSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextModifier()->resetTextMinFontSize(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::SetDraggable(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
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
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextModifier()->resetTextDraggable(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::SetMaxFontSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    CalcDimension fontSize;
    if (ArkTSUtils::ParseJsDimensionFp(vm, secondArg, fontSize)) {
        GetArkUINodeModifiers()->getTextModifier()->setTextMaxFontSize(
            nativeNode, fontSize.Value(), static_cast<int8_t>(fontSize.Unit()));
    } else {
        GetArkUINodeModifiers()->getTextModifier()->resetTextMaxFontSize(nativeNode);
    }
    
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::ResetMaxFontSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextModifier()->resetTextMaxFontSize(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::SetFontFamily(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    std::vector<std::string> fontFamilies;
    if (!ArkTSUtils::ParseJsFontFamilies(vm, secondArg, fontFamilies)) {
        GetArkUINodeModifiers()->getTextModifier()->resetTextFontFamily(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto families = std::make_unique<char* []>(fontFamilies.size());
    for (uint32_t i = 0; i < fontFamilies.size(); i++) {
        families[i] = const_cast<char*>(fontFamilies.at(i).c_str());
    }
    GetArkUINodeModifiers()->getTextModifier()->setTextFontFamily(
        nativeNode, const_cast<const char**>(families.get()), fontFamilies.size());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::ResetFontFamily(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    GetArkUINodeModifiers()->getTextModifier()->resetTextFontFamily(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::SetCopyOption(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
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
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextModifier()->resetTextCopyOption(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::SetTextShadow(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> radiusArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> typeArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> offsetXArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    Local<JSValueRef> offsetYArg = runtimeCallInfo->GetCallArgRef(NUM_5);
    Local<JSValueRef> fillArg = runtimeCallInfo->GetCallArgRef(NUM_6);
    Local<JSValueRef> lengthArg = runtimeCallInfo->GetCallArgRef(NUM_7);
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
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextModifier()->resetTextShadow(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::SetHeightAdaptivePolicy(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
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
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextModifier()->resetTextHeightAdaptivePolicy(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::SetTextIndent(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    CalcDimension indent;
    if (!ArkTSUtils::ParseJsDimensionFp(vm, secondArg, indent) || indent.IsNegative()) {
        indent.Reset();
    }
    
    GetArkUINodeModifiers()->getTextModifier()->setTextIndent(
        nativeNode, indent.Value(), static_cast<int8_t>(indent.Unit()));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::ResetTextIndent(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextModifier()->resetTextIndent(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::SetBaselineOffset(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    CalcDimension baselineOffset;
    if (!ArkTSUtils::ParseJsDimensionNG(vm, secondArg, baselineOffset, DimensionUnit::FP, false)) {
        baselineOffset.Reset();
    }

    GetArkUINodeModifiers()->getTextModifier()->setTextBaselineOffset(
        nativeNode, baselineOffset.Value(), static_cast<int8_t>(baselineOffset.Unit()));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::ResetBaselineOffset(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextModifier()->resetTextBaselineOffset(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::SetLetterSpacing(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
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
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextModifier()->resetTextLetterSpacing(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::SetFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> sizeArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> weightArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> familyArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> styleArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    ArkUIFontStruct fontInfo;
    CalcDimension fontSize;
    if (!ArkTSUtils::ParseJsDimensionFp(vm, sizeArg,  fontSize) || sizeArg->IsNull()) {
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

    std::string weight = DEFAULT_FONT_WEIGHT;
    if (!weightArg->IsNull()) {
        if (weightArg->IsNumber()) {
            weight = std::to_string(weightArg->Int32Value(vm));
        } else if (weightArg->IsString()) {
            weight = weightArg->ToString(vm)->ToString();
        }
    }
    fontInfo.fontWeight = static_cast<uint8_t>(Framework::ConvertStrToFontWeight(weight));
    
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
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextModifier()->resetTextFont(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::SetWordBreak(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> workBreakArg = runtimeCallInfo->GetCallArgRef(NUM_1);
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
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextModifier()->resetWordBreak(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::SetEllipsisMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> ellipsisModeArg = runtimeCallInfo->GetCallArgRef(NUM_1);
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
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextModifier()->resetEllipsisMode(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::SetEnableDataDetector(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> enableDataDetectorArg = runtimeCallInfo->GetCallArgRef(NUM_1);
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
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextModifier()->resetEnableDataDetector(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::SetFontFeature(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsString()) {
        auto value = secondArg->ToString(vm)->ToString();
        GetArkUINodeModifiers()->getTextModifier()->setTextFontFeature(nativeNode, value.c_str());
    } else {
        GetArkUINodeModifiers()->getTextModifier()->resetTextFontFeature(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TextBridge::ResetFontFeature(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTextModifier()->resetTextFontFeature(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
