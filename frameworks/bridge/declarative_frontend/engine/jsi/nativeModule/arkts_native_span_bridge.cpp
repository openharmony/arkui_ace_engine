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

#include <string>
#include "base/geometry/dimension.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_api.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components/text/text_theme.h"
#include "bridge/declarative_frontend/engine/jsi/jsi_types.h"


namespace OHOS::Ace::NG {
constexpr int SIZE_OF_TEXT_CASES = 2;
constexpr double DEFAULT_SPAN_FONT_SIZE = 16;
constexpr DimensionUnit DEFAULT_SPAN_FONT_UNIT = DimensionUnit::FP;
constexpr TextDecorationStyle DEFAULT_DECORATION_STYLE = TextDecorationStyle::SOLID;
constexpr Ace::FontStyle DEFAULT_FONT_STYLE = Ace::FontStyle::NORMAL;
constexpr Color DEFAULT_DECORATION_COLOR = Color(0xff000000);
const std::string DEFAULT_FONT_WEIGHT = "400";
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int NUM_4 = 4;

ArkUINativeModuleValue SpanBridge::SetTextCase(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    void *nativeNode = firstArg->ToNativePointer(vm)->Value();
    int32_t value = secondArg->Int32Value(vm);
    if (value >= NUM_0 && value <= SIZE_OF_TEXT_CASES) {
        GetArkUIInternalNodeAPI()->GetSpanModifier().SetSpanTextCase(nativeNode, value);
    } else {
        GetArkUIInternalNodeAPI()->GetSpanModifier().ResetSpanTextCase(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SpanBridge::ResetTextCase(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void *nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSpanModifier().ResetSpanTextCase(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SpanBridge::SetFontWeight(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    void *nativeNode = firstArg->ToNativePointer(vm)->Value();
    
    std::string weight = DEFAULT_FONT_WEIGHT;
    if (!secondArg->IsNull()) {
        if (secondArg->IsNumber()) {
            weight = std::to_string(secondArg->Int32Value(vm));
        } else if (secondArg->IsString()) {
            weight = secondArg->ToString(vm)->ToString();
        }
    }
    GetArkUIInternalNodeAPI()->GetSpanModifier().SetSpanFontWeight(nativeNode, weight.c_str());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SpanBridge::ResetFontWeight(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void *nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSpanModifier().ResetSpanFontWeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SpanBridge::SetLineHeight(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    void *nativeNode = firstArg->ToNativePointer(vm)->Value();

    std::string str;
    struct StringAndDouble result = { 0.0, nullptr };
    if (secondArg->IsNumber()) {
        result.value = secondArg->ToNumber(vm)->Value();
        GetArkUIInternalNodeAPI()->GetSpanModifier().SetSpanLineHeight(nativeNode, &result);
    } else if (secondArg->IsString()) {
        str = secondArg->ToString(vm)->ToString();
        result.valueStr = str.c_str();
        GetArkUIInternalNodeAPI()->GetSpanModifier().SetSpanLineHeight(nativeNode, &result);
    } else {
        GetArkUIInternalNodeAPI()->GetSpanModifier().ReSetSpanLineHeight(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SpanBridge::ReSetLineHeight(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void *nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSpanModifier().ReSetSpanLineHeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SpanBridge::SetFontStyle(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    void *nativeNode = firstArg->ToNativePointer(vm)->Value();

    if (secondArg->IsNumber()) {
        int32_t value = secondArg->Int32Value(vm);
        GetArkUIInternalNodeAPI()->GetSpanModifier().SetSpanFontStyle(nativeNode, value);
    } else {
        GetArkUIInternalNodeAPI()->GetSpanModifier().ReSetSpanFontStyle(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SpanBridge::ReSetFontStyle(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void *nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSpanModifier().ReSetSpanFontStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SpanBridge::SetFontSize(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    void *nativeNode = firstArg->ToNativePointer(vm)->Value();
    auto theme = Framework::JSViewAbstract::GetTheme<TextTheme>();

    CalcDimension fontSize(DEFAULT_SPAN_FONT_SIZE, DEFAULT_SPAN_FONT_UNIT);
    if (!ArkTSUtils::ParseJsDimensionFp(vm, secondArg, fontSize)) {
        fontSize.SetUnit(DEFAULT_SPAN_FONT_UNIT);
        fontSize.SetValue(DEFAULT_SPAN_FONT_SIZE);
    }
    if (fontSize.IsNegative() && theme) {
        fontSize = theme->GetTextStyle().GetFontSize();
    }
    GetArkUIInternalNodeAPI()->GetSpanModifier().SetSpanFontSize(nativeNode, fontSize.Value(),
        static_cast<int8_t>(fontSize.Unit()));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SpanBridge::ResetFontSize(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void *nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSpanModifier().ResetSpanFontSize(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SpanBridge::SetFontFamily(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    void *nativeNode = firstArg->ToNativePointer(vm)->Value();

    std::vector<std::string> fontFamilies;
    if (!ArkTSUtils::ParseJsFontFamilies(vm, secondArg, fontFamilies)) {
        GetArkUIInternalNodeAPI()->GetSpanModifier().ResetSpanFontFamily(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto families = std::make_unique<char *[]>(fontFamilies.size());
    for (uint32_t i = 0; i < fontFamilies.size(); i++) {
        families[i] = const_cast<char *>(fontFamilies.at(i).c_str());
    }
    GetArkUIInternalNodeAPI()->GetSpanModifier().SetSpanFontFamily(nativeNode,
        const_cast<const char **>(families.get()), fontFamilies.size());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SpanBridge::ResetFontFamily(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void *nativeNode = firstArg->ToNativePointer(vm)->Value();

    GetArkUIInternalNodeAPI()->GetSpanModifier().ResetSpanFontFamily(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SpanBridge::SetDecoration(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    void *nativeNode = firstArg->ToNativePointer(vm)->Value();
    int32_t textDecoration = static_cast<int32_t>(TextDecoration::NONE);
    Color color = DEFAULT_DECORATION_COLOR;
    uint32_t style = static_cast<uint32_t>(DEFAULT_DECORATION_STYLE);
    if (secondArg->IsInt()) {
        textDecoration = secondArg->Int32Value(vm);
    }
    if (!ArkTSUtils::ParseJsColorAlpha(vm, thirdArg, color)) {
        color = DEFAULT_DECORATION_COLOR;
    }
    GetArkUIInternalNodeAPI()->GetSpanModifier().SetSpanDecoration(nativeNode, textDecoration, color.GetValue(), style);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SpanBridge::ResetDecoration(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void *nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSpanModifier().ResetSpanDecoration(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SpanBridge::SetFontColor(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    void *nativeNode = firstArg->ToNativePointer(vm)->Value();

    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, panda::JSValueRef::Undefined(vm));
    auto theme = pipelineContext->GetTheme<TextTheme>();
    CHECK_NULL_RETURN(theme, panda::JSValueRef::Undefined(vm));

    Color textColor = theme->GetTextStyle().GetTextColor();
    if (secondArg->IsInt() && ArkTSUtils::ParseJsColorAlpha(vm, secondArg, textColor)) {
        GetArkUIInternalNodeAPI()->GetSpanModifier().SetSpanFontColor(nativeNode, textColor.GetValue());
    } else {
        GetArkUIInternalNodeAPI()->GetSpanModifier().ResetSpanFontColor(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SpanBridge::ResetFontColor(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void *nativeNode = firstArg->ToNativePointer(vm)->Value();

    GetArkUIInternalNodeAPI()->GetSpanModifier().ResetSpanFontColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SpanBridge::SetLetterSpacing(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    void *nativeNode = firstArg->ToNativePointer(vm)->Value();
    struct StringAndDouble letterSpacingValue = { 0.0, nullptr };
    if (secondArg->IsNumber()) {
        letterSpacingValue.value = secondArg->ToNumber(vm)->Value();
        GetArkUIInternalNodeAPI()->GetSpanModifier().SetSpanLetterSpacing(nativeNode, &letterSpacingValue);
    } else if (secondArg->IsString()) {
        std::string tempValueStr = secondArg->ToString(vm)->ToString();
        letterSpacingValue.valueStr = tempValueStr.c_str();
        GetArkUIInternalNodeAPI()->GetSpanModifier().SetSpanLetterSpacing(nativeNode, &letterSpacingValue);
    } else {
        GetArkUIInternalNodeAPI()->GetSpanModifier().ResetSpanLetterSpacing(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SpanBridge::ResetLetterSpacing(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void *nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSpanModifier().ResetSpanLetterSpacing(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SpanBridge::SetFont(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> forthArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> fifthArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    void *nativeNode = firstArg->ToNativePointer(vm)->Value();
    struct StringAndDouble size = { 0.0, nullptr };

    if (secondArg->IsNumber()) {
        size.value = secondArg->ToNumber(vm)->Value();
    } else if (secondArg->IsString()) {
        size.valueStr = secondArg->ToString(vm)->ToString().c_str();
    }

    std::string weight = DEFAULT_FONT_WEIGHT;
    if (!thirdArg->IsNull()) {
        if (thirdArg->IsNumber()) {
            weight = std::to_string(thirdArg->Int32Value(vm));
        } else if (thirdArg->IsString()) {
            weight = thirdArg->ToString(vm)->ToString();
        }
    }
    std::string str;
    const char *family = nullptr;
    if (!forthArg->IsNull()) {
        str = forthArg->ToString(vm)->ToString();
        family = str.c_str();
    }
    int32_t style = static_cast<int32_t>(DEFAULT_FONT_STYLE);
    if (fifthArg->IsInt()) {
        style = fifthArg->Int32Value(vm);
    }
    GetArkUIInternalNodeAPI()->GetSpanModifier().SetSpanFont(nativeNode, &size, weight.c_str(), family, style);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SpanBridge::ResetFont(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void *nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSpanModifier().ResetSpanFont(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
