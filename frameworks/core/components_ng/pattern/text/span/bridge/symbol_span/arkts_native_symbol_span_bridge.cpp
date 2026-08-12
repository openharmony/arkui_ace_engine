/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/text/span/bridge/symbol_span/arkts_native_symbol_span_bridge.h"

#include "bridge/common/utils/utils.h"
#include "frameworks/base/geometry/calc_dimension.h"
#include "frameworks/base/geometry/dimension.h"
#include "frameworks/base/utils/string_utils.h"
#include "frameworks/base/utils/utils.h"
#include "frameworks/bridge/declarative_frontend/engine/js_types.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "frameworks/core/components_ng/pattern/text/span_node.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int32_t SYSTEM_SYMBOL_BOUNDARY = 0XFFFFF;
const std::string DEFAULT_SYMBOL_FONTFAMILY = "HM Symbol";
constexpr int32_t DEFAULT_VARIABLE_FONT_WEIGHT = 400;
const std::string DEFAULT_FONT_WEIGHT = "400";

void SetSymbolSpanFontFamilies(const ArkUISymbolSpanModifier* symbolSpanModifier,
    const std::vector<std::string>& familyNames)
{
    CHECK_NULL_VOID(symbolSpanModifier);
    std::vector<ArkUI_CharPtr> fontFamilies;
    fontFamilies.reserve(familyNames.size());
    for (const auto& familyName : familyNames) {
        fontFamilies.emplace_back(familyName.c_str());
    }
    symbolSpanModifier->setSymbolSpanFontFamilies(fontFamilies.data(), static_cast<ArkUI_Uint32>(fontFamilies.size()));
}
} // namespace

bool GetNativeNode(ArkUINodeHandle& nativeNode, const Local<JSValueRef>& firstArg, panda::ecmascript::EcmaVM* vm)
{
    if (firstArg->IsNativePointer(vm)) {
        nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
        return true;
    }
    if (firstArg->IsBoolean() && firstArg->ToBoolean(vm)->Value()) {
        auto uiNode = Referenced::RawPtr(ViewStackProcessor::GetInstance()->GetMainElementNode());
        nativeNode = reinterpret_cast<ArkUINodeHandle>(uiNode);
        return true;
    }

    return false;
}

void SetFontWeightJs(panda::ecmascript::EcmaVM* vm, Local<JSValueRef> secondArg, ArkUINodeHandle nativeNode)
{
    std::string weight = DEFAULT_FONT_WEIGHT;
    ArkTSUtils::ParseJsString(vm, secondArg, weight);
    auto parseResult = Framework::ParseFontWeight(weight);
    int32_t variableFontWeight;
    if (parseResult.first) {
        variableFontWeight = Framework::GetFontWeightNumericValue(parseResult.second);
    } else {
        variableFontWeight = StringUtils::IsNumber(weight) ?
            StringUtils::StringToInt(weight, DEFAULT_VARIABLE_FONT_WEIGHT) : DEFAULT_VARIABLE_FONT_WEIGHT;
    }
    GetArkUINodeModifiers()->getSymbolSpanModifier()->setSymbolSpanFontWeight(
        nativeNode, static_cast<int32_t>(parseResult.second));
    GetArkUINodeModifiers()->getSymbolSpanModifier()->setSymbolSpanVariableFontWeight(
        nativeNode, variableFontWeight);
}

void SetSymbolSpanFontWeightFlags(panda::ecmascript::EcmaVM* vm, ArkUINodeHandle nativeNode,
    Local<JSValueRef> enableVariableFontWeightArg, Local<JSValueRef> enableDeviceFontWeightCategoryArg)
{
    if (!enableVariableFontWeightArg->IsNull() && !enableVariableFontWeightArg->IsUndefined() &&
        enableVariableFontWeightArg->IsBoolean()) {
        GetArkUINodeModifiers()->getSymbolSpanModifier()->setSymbolSpanEnableVariableFontWeight(nativeNode,
            enableVariableFontWeightArg->ToBoolean(vm)->Value());
    } else {
        GetArkUINodeModifiers()->getSymbolSpanModifier()->resetSymbolSpanEnableVariableFontWeight(nativeNode);
    }
    if (!enableDeviceFontWeightCategoryArg->IsNull() && !enableDeviceFontWeightCategoryArg->IsUndefined() &&
        enableDeviceFontWeightCategoryArg->IsBoolean()) {
        GetArkUINodeModifiers()->getSymbolSpanModifier()->setSymbolSpanEnableDeviceFontWeightCategory(nativeNode,
            enableDeviceFontWeightCategoryArg->ToBoolean(vm)->Value());
    } else {
        GetArkUINodeModifiers()->getSymbolSpanModifier()->resetSymbolSpanEnableDeviceFontWeightCategory(nativeNode);
    }
}

void SymbolSpanBridge::RegisterSymbolSpanAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    const char* functionNames[] = {
        "jsCreate",
        "setFontColor",
        "resetFontColor",
        "setFontSize",
        "resetFontSize",
        "setFontWeight",
        "resetFontWeight",
        "setEffectStrategy",
        "resetEffectStrategy",
        "setRenderingStrategy",
        "resetRenderingStrategy",
        "setId"
    };
    Local<JSValueRef> functionValues[] = {
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SymbolSpanBridge::JsCreate),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SymbolSpanBridge::SetFontColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SymbolSpanBridge::ResetFontColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SymbolSpanBridge::SetFontSize),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SymbolSpanBridge::ResetFontSize),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SymbolSpanBridge::SetFontWeight),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SymbolSpanBridge::ResetFontWeight),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SymbolSpanBridge::SetEffectStrategy),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SymbolSpanBridge::ResetEffectStrategy),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SymbolSpanBridge::SetRenderingStrategy),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SymbolSpanBridge::ResetRenderingStrategy),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SymbolSpanBridge::SetId)
    };
    auto symbolSpan = panda::ObjectRef::NewWithNamedProperties(
        vm, ArraySize(functionNames), functionNames, functionValues);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "symbolSpan"), symbolSpan);
}

ArkUINativeModuleValue SymbolSpanBridge::JsCreate(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> arg = runtimeCallInfo->GetCallArgRef(0);
    uint32_t symbolId = 0;
    RefPtr<ResourceObject> resourceObject;
    ArkTSUtils::ParseJsSymbolId(vm, arg, symbolId, resourceObject);

    auto nodeModifiers = GetArkUINodeModifiers();
    auto symbolSpanModifier = nodeModifiers->getSymbolSpanModifier();
    symbolSpanModifier->createModel(symbolId);
    std::vector<std::string> familyNames;
    if (symbolId > SYSTEM_SYMBOL_BOUNDARY) {
        ArkTSUtils::ParseJsSymbolCustomFamilyNames(vm, familyNames, arg);
        SetSymbolSpanFontFamilies(symbolSpanModifier, familyNames);
        symbolSpanModifier->setSymbolSpanType(static_cast<ArkUI_Uint32>(SymbolType::CUSTOM));
    } else {
        familyNames.push_back(DEFAULT_SYMBOL_FONTFAMILY);
        SetSymbolSpanFontFamilies(symbolSpanModifier, familyNames);
        symbolSpanModifier->setSymbolSpanType(static_cast<ArkUI_Uint32>(SymbolType::SYSTEM));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SymbolSpanBridge::SetFontColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    bool isJsView = firstArg->IsBoolean() && firstArg->ToBoolean(vm)->Value();

    if (!secondArg->IsArray(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto array = Local<panda::ArrayRef>(secondArg);
    auto length = ArkTSUtils::GetArrayLength(vm, array);

    std::vector<ArkUI_Uint32> colorArray;
    std::vector<Color> colorArr;
    std::vector<std::pair<int32_t, RefPtr<ResourceObject>>> resObjArr;
    for (uint32_t index = 0; index < length; index++) {
        Local<JSValueRef> value = panda::ArrayRef::GetValueAt(vm, array, index);
        Color color;
        RefPtr<ResourceObject> resObj;
        auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
        if (ArkTSUtils::ParseJsColorAlpha(vm, value, color, resObj, nodeInfo)) {
            colorArray.emplace_back(color.GetValue());
            colorArr.emplace_back(color);
        } else {
            colorArray.clear();
            break;
        }
        if (SystemProperties::ConfigChangePerform() && resObj) {
            std::pair<int32_t, RefPtr<ResourceObject>> pair(index, resObj);
            resObjArr.push_back(pair);
        }
    }
    if (!isJsView && static_cast<uint32_t>(length) == colorArray.size() && (static_cast<uint32_t>(length) & 1)) {
        for (uint32_t i = 0; i < length; i++) {
            colorArray.emplace_back(colorArray[i]);
        }
    }
    GetArkUINodeModifiers()->getSymbolSpanModifier()->setSymbolSpanFontColor(
        nativeNode, colorArray.data(), colorArray.size());
    auto* uiNode = reinterpret_cast<UINode*>(nativeNode);
    CHECK_NULL_RETURN(uiNode, panda::JSValueRef::Undefined(vm));
    auto spanNode = AceType::DynamicCast<NG::SpanNode>(uiNode);
    CHECK_NULL_RETURN(spanNode, panda::JSValueRef::Undefined(vm));
    if (!resObjArr.empty()) {
        spanNode->RegisterSymbolFontColorResource("symbolColor",
            colorArr, resObjArr);
    } else {
        spanNode->UnregisterResource("symbolColor");
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SymbolSpanBridge::ResetFontColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    ArkUINodeHandle nativeNode = nullptr;
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSymbolSpanModifier()->resetSymbolSpanFontColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SymbolSpanBridge::SetFontSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = firstArg->IsBoolean() && firstArg->ToBoolean(vm)->Value();

    CalcDimension fontSize;
    RefPtr<ResourceObject> resObj;
    if (!ArkTSUtils::ParseJsDimensionFpNG(vm, secondArg, fontSize, resObj, false)) {
        GetArkUINodeModifiers()->getSymbolSpanModifier()->resetSymbolSpanFontSize(nativeNode);
    } else {
        if (isJsView && fontSize.IsNegative()) {
            GetArkUINodeModifiers()->getSymbolSpanModifier()->resetSymbolSpanFontSize(nativeNode);
            return panda::JSValueRef::Undefined(vm);
        }
        GetArkUINodeModifiers()->getSymbolSpanModifier()->setSymbolSpanFontSize(
            nativeNode, fontSize.Value(), static_cast<int>(fontSize.Unit()), AceType::RawPtr(resObj));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SymbolSpanBridge::ResetFontSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSymbolSpanModifier()->resetSymbolSpanFontSize(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SymbolSpanBridge::SetFontWeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> fourthArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = firstArg->IsBoolean() && firstArg->ToBoolean(vm)->Value();
    if (secondArg->IsString(vm)) {
        std::string weight = secondArg->ToString(vm)->ToString(vm);
        auto parseResult = Framework::ParseFontWeight(weight);
        int32_t variableFontWeight;
        if (parseResult.first) {
            variableFontWeight = Framework::GetFontWeightNumericValue(parseResult.second);
        } else {
            variableFontWeight = StringUtils::IsNumber(weight) ?
                StringUtils::StringToInt(weight, DEFAULT_VARIABLE_FONT_WEIGHT) : DEFAULT_VARIABLE_FONT_WEIGHT;
        }
        GetArkUINodeModifiers()->getSymbolSpanModifier()->setSymbolSpanFontWeight(
            nativeNode, static_cast<int32_t>(parseResult.second));
        GetArkUINodeModifiers()->getSymbolSpanModifier()->setSymbolSpanVariableFontWeight(
            nativeNode, variableFontWeight);
    } else if (secondArg->IsNumber()) {
        int32_t weightNum = secondArg->Int32Value(vm);
        std::string weight = std::to_string(weightNum);
        FontWeight fontWeightEnum = Framework::ConvertStrToFontWeight(weight);
        GetArkUINodeModifiers()->getSymbolSpanModifier()->setSymbolSpanFontWeight(
            nativeNode, static_cast<int32_t>(fontWeightEnum));
        GetArkUINodeModifiers()->getSymbolSpanModifier()->setSymbolSpanVariableFontWeight(
            nativeNode, weightNum);
    } else if (isJsView && secondArg->IsObject(vm)) {
        SetFontWeightJs(vm, secondArg, nativeNode);
    } else {
        GetArkUINodeModifiers()->getSymbolSpanModifier()->resetSymbolSpanFontWeight(nativeNode);
        GetArkUINodeModifiers()->getSymbolSpanModifier()->resetSymbolSpanVariableFontWeight(nativeNode);
    }
    SetSymbolSpanFontWeightFlags(vm, nativeNode, thirdArg, fourthArg);
    if ((thirdArg->IsNull() || thirdArg->IsUndefined()) && (fourthArg->IsNull() || fourthArg->IsUndefined())) {
        GetArkUINodeModifiers()->getSymbolSpanModifier()->resetSymbolSpanVariableFontWeight(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SymbolSpanBridge::ResetFontWeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSymbolSpanModifier()->resetSymbolSpanFontWeight(nativeNode);
    GetArkUINodeModifiers()->getSymbolSpanModifier()->resetSymbolSpanVariableFontWeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SymbolSpanBridge::SetRenderingStrategy(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (secondArg->IsNumber() && secondArg->Int32Value(vm) >= NUM_0 &&
        secondArg->Int32Value(vm) <= NUM_2) {
        GetArkUINodeModifiers()->getSymbolSpanModifier()->setSymbolSpanRenderingStrategy(
            nativeNode, secondArg->Int32Value(vm));
    } else {
        GetArkUINodeModifiers()->getSymbolSpanModifier()->resetSymbolSpanRenderingStrategy(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SymbolSpanBridge::ResetRenderingStrategy(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSymbolSpanModifier()->resetSymbolSpanRenderingStrategy(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SymbolSpanBridge::SetEffectStrategy(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (secondArg->IsNumber() && secondArg->Int32Value(vm) >= NUM_0 &&
        secondArg->Int32Value(vm) <= NUM_2) {
        GetArkUINodeModifiers()->getSymbolSpanModifier()->setSymbolSpanEffectStrategy(
            nativeNode, secondArg->Int32Value(vm));
    } else {
        GetArkUINodeModifiers()->getSymbolSpanModifier()->resetSymbolSpanEffectStrategy(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SymbolSpanBridge::ResetEffectStrategy(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getSymbolSpanModifier()->resetSymbolSpanEffectStrategy(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SymbolSpanBridge::SetId(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    uint32_t content = 0;
    if (ArkTSUtils::ParseJsSymbolId(vm, secondArg, content)) {
        if (content > SYSTEM_SYMBOL_BOUNDARY) {
            std::string symbolFontFamilyName;
            ArkTSUtils::ParseJsSymbolFontFamilyName(vm, secondArg, symbolFontFamilyName);
            GetArkUINodeModifiers()->getSymbolSpanModifier()->setCustomSymbolSpanId(nativeNode, content,
                symbolFontFamilyName.c_str());
        } else {
            GetArkUINodeModifiers()->getSymbolSpanModifier()->setSymbolSpanId(nativeNode, content);
        }
    }
    return panda::JSValueRef::Undefined(vm);
}

} // namespace OHOS::Ace::NG
