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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_alphabet_indexer_bridge.h"
#include "ui/base/ace_type.h"

#include "core/interfaces/native/node/node_api.h"
#include "bridge/declarative_frontend/jsview/models/indexer_model_impl.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_common_bridge.h"
namespace OHOS::Ace::NG {
namespace {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int NUM_4 = 4;
const std::string FORMAT_FONT = "%s|%s|%s";
const std::string DEFAULT_FAMILY = "HarmonyOS Sans";
constexpr double DEFAULT_POPUP_ITEM_FONT_SIZE = 24.0;
constexpr Dimension DEFAULT_FONT_SIZE_VAL = 12.0_fp;
const std::string DEFAULT_POPUP_ITEM_FONT_WEIGHT = "medium";
constexpr Dimension DEFAULT_POPUP_POSITION_X = 60.0_vp;
constexpr Dimension DEFAULT_POPUP_POSITION_Y = 48.0_vp;
constexpr double RADIUS_OFFSET = 4.0;
} // namespace

ArkUINativeModuleValue AlphabetIndexerBridge::SetPopupItemFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> fontSizeArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> weightArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    CalcDimension fontSize;
    RefPtr<ResourceObject> resObj;
    if (!fontSizeArg->IsNull()) {
        CalcDimension fontSizeData;
        if (ArkTSUtils::ParseJsDimensionFp(vm, fontSizeArg, fontSizeData, resObj) && !fontSizeData.IsNegative() &&
            fontSizeData.Unit() != DimensionUnit::PERCENT) {
            fontSize = fontSizeData;
        }
    }
    std::string weight = DEFAULT_POPUP_ITEM_FONT_WEIGHT;
    if (!weightArg->IsNull() && !weightArg->IsUndefined()) {
        if (weightArg->IsNumber()) {
            weight = std::to_string(weightArg->Int32Value(vm));
        } else {
            if (!ArkTSUtils::ParseJsString(vm, weightArg, weight) || weight.empty()) {
                weight = DEFAULT_POPUP_ITEM_FONT_WEIGHT;
            }
        }
    }
    if (SystemProperties::ConfigChangePerform()) {
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->createWithResourceObj(nativeNode,
            static_cast<int32_t>(IndexerJsResourceType::POPUP_ITEM_FONT_SIZE),
            reinterpret_cast<void*>(AceType::RawPtr(resObj)));
    }
    GetArkUINodeModifiers()->getAlphabetIndexerModifier()->setPopupItemFont(
        nativeNode, fontSize.Value(), static_cast<int>(fontSize.Unit()), weight.c_str());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::ResetPopupItemFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getAlphabetIndexerModifier()->resetPopupItemFont(nativeNode);
    if (SystemProperties::ConfigChangePerform()) {
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->createWithResourceObj(
            nativeNode, static_cast<int32_t>(IndexerJsResourceType::POPUP_ITEM_FONT_SIZE), nullptr);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::SetSelectedFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> fontSizeArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> weightArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> fontFamilyArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> styleValArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    bool isUndefinedValue = (fontSizeArg->IsNull() || fontSizeArg->IsUndefined()) &&
                            (weightArg->IsNull() || weightArg->IsUndefined()) &&
                            (fontFamilyArg->IsNull() || fontFamilyArg->IsUndefined()) &&
                            (styleValArg->IsNull() || styleValArg->IsUndefined());
    if (isUndefinedValue) {
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->resetSelectedFont(nativeNode);
    }
    CalcDimension fontSizeData(DEFAULT_FONT_SIZE_VAL);
    std::string fontSize = fontSizeData.ToString();
    RefPtr<ResourceObject> FontSizeResObj;
    if (!fontSizeArg->IsNull() && !fontSizeArg->IsUndefined() &&
        ArkTSUtils::ParseJsDimensionFp(vm, fontSizeArg, fontSizeData, FontSizeResObj) && !fontSizeData.IsNegative() &&
        fontSizeData.Unit() != DimensionUnit::PERCENT) {
        fontSize = fontSizeData.ToString();
    }
    std::string weight = "normal";
    if (!weightArg->IsNull() && !weightArg->IsUndefined() && (weightArg->IsString(vm) || weightArg->IsNumber())) {
        weight = weightArg->ToString(vm)->ToString(vm);
    }
    std::string fontFamily;
    RefPtr<ResourceObject> fontFamilyResObj;
    if (!ArkTSUtils::ParseJsFontFamiliesToString(vm, fontFamilyArg, fontFamily, fontFamilyResObj) ||
        fontFamily.empty()) {
        fontFamily = DEFAULT_FAMILY;
    }
    int32_t styleVal = 0;
    if (!styleValArg->IsNull() && !styleValArg->IsUndefined() && styleValArg->IsNumber()) {
        styleVal = styleValArg->Int32Value(vm);
    }
    std::string fontInfo =
        StringUtils::FormatString(FORMAT_FONT.c_str(), fontSize.c_str(), weight.c_str(), fontFamily.c_str());
    GetArkUINodeModifiers()->getAlphabetIndexerModifier()->setSelectedFont(nativeNode, fontInfo.c_str(), styleVal);
    if (SystemProperties::ConfigChangePerform()) {
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->createWithResourceObj(nativeNode,
            static_cast<int32_t>(IndexerJsResourceType::SELECTED_FONT_SIZE),
            reinterpret_cast<void*>(AceType::RawPtr(FontSizeResObj)));
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->createWithResourceObj(nativeNode,
            static_cast<int32_t>(IndexerJsResourceType::SELECTED_FONT_FAMILY),
            reinterpret_cast<void*>(AceType::RawPtr(fontFamilyResObj)));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::ResetSelectedFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getAlphabetIndexerModifier()->resetSelectedFont(nativeNode);
    if (SystemProperties::ConfigChangePerform()) {
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->createWithResourceObj(
            nativeNode, static_cast<int32_t>(IndexerJsResourceType::SELECTED_FONT_SIZE), nullptr);
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->createWithResourceObj(
            nativeNode, static_cast<int32_t>(IndexerJsResourceType::SELECTED_FONT_FAMILY), nullptr);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::SetPopupFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> fontSizeArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> weightArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> fontFamilyArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> styleValArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    bool isUndefinedValue = (fontSizeArg->IsNull() || fontSizeArg->IsUndefined()) &&
                            (weightArg->IsNull() || weightArg->IsUndefined()) &&
                            (fontFamilyArg->IsNull() || fontFamilyArg->IsUndefined()) &&
                            (styleValArg->IsNull() || styleValArg->IsUndefined());
    if (isUndefinedValue) {
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->resetPopupFont(nativeNode);
    }
    CalcDimension fontSizeData(Dimension(DEFAULT_POPUP_ITEM_FONT_SIZE, DimensionUnit::FP));
    std::string fontSize = fontSizeData.ToString();
    RefPtr<ResourceObject> fontSizeResObj;
    if (!fontSizeArg->IsNull() && !fontSizeArg->IsUndefined() &&
        ArkTSUtils::ParseJsDimensionFp(vm, fontSizeArg, fontSizeData, fontSizeResObj) && !fontSizeData.IsNegative() &&
        fontSizeData.Unit() != DimensionUnit::PERCENT) {
        fontSize = fontSizeData.ToString();
    }
    std::string weight = "normal";
    if (!weightArg->IsNull() && !weightArg->IsUndefined() && (weightArg->IsString(vm) || weightArg->IsNumber())) {
        weight = weightArg->ToString(vm)->ToString(vm);
    }
    std::string fontFamily;
    RefPtr<ResourceObject> fontFamilyResObj;
    if (!ArkTSUtils::ParseJsFontFamiliesToString(vm, fontFamilyArg, fontFamily, fontFamilyResObj) ||
        fontFamily.empty()) {
        fontFamily = DEFAULT_FAMILY;
    }
    int32_t styleVal = 0;
    if (!styleValArg->IsNull() && !styleValArg->IsUndefined() && styleValArg->IsNumber()) {
        styleVal = styleValArg->Int32Value(vm);
    }
    std::string fontInfo =
        StringUtils::FormatString(FORMAT_FONT.c_str(), fontSize.c_str(), weight.c_str(), fontFamily.c_str());
    GetArkUINodeModifiers()->getAlphabetIndexerModifier()->setPopupFont(nativeNode, fontInfo.c_str(), styleVal);
    if (SystemProperties::ConfigChangePerform()) {
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->createWithResourceObj(nativeNode,
            static_cast<int32_t>(IndexerJsResourceType::POPUP_FONT_SIZE),
            reinterpret_cast<void*>(AceType::RawPtr(fontSizeResObj)));
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->createWithResourceObj(nativeNode,
            static_cast<int32_t>(IndexerJsResourceType::POPUP_FONT_FAMILY),
            reinterpret_cast<void*>(AceType::RawPtr(fontFamilyResObj)));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::ResetPopupFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getAlphabetIndexerModifier()->resetPopupFont(nativeNode);
    if (SystemProperties::ConfigChangePerform()) {
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->createWithResourceObj(
            nativeNode, static_cast<int32_t>(IndexerJsResourceType::POPUP_FONT_SIZE), nullptr);
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->createWithResourceObj(
            nativeNode, static_cast<int32_t>(IndexerJsResourceType::POPUP_FONT_FAMILY), nullptr);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::SetFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> fontSizeArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> weightArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> fontFamilyArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> styleValArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    bool isUndefinedValue = (fontSizeArg->IsNull() || fontSizeArg->IsUndefined()) &&
                            (weightArg->IsNull() || weightArg->IsUndefined()) &&
                            (fontFamilyArg->IsNull() || fontFamilyArg->IsUndefined()) &&
                            (styleValArg->IsNull() || styleValArg->IsUndefined());
    if (isUndefinedValue) {
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->resetAlphabetIndexerFont(nativeNode);
    }
    CalcDimension fontSizeData(DEFAULT_FONT_SIZE_VAL);
    std::string fontSize = fontSizeData.ToString();
    RefPtr<ResourceObject> fontSizeResObj;
    if (!fontSizeArg->IsNull() && !fontSizeArg->IsUndefined() &&
        ArkTSUtils::ParseJsDimensionFp(vm, fontSizeArg, fontSizeData, fontSizeResObj) && !fontSizeData.IsNegative() &&
        fontSizeData.Unit() != DimensionUnit::PERCENT) {
        fontSize = fontSizeData.ToString();
    }
    std::string weight = "normal";
    if (!weightArg->IsNull() && !weightArg->IsUndefined() && (weightArg->IsString(vm) || weightArg->IsNumber())) {
        weight = weightArg->ToString(vm)->ToString(vm);
    }
    std::string fontFamily;
    RefPtr<ResourceObject> fontFamilyResObj;
    if (!ArkTSUtils::ParseJsFontFamiliesToString(vm, fontFamilyArg, fontFamily, fontFamilyResObj) ||
        fontFamily.empty()) {
        fontFamily = DEFAULT_FAMILY;
    }
    int32_t styleVal = 0;
    if (!styleValArg->IsNull() && !styleValArg->IsUndefined() && styleValArg->IsNumber()) {
        styleVal = styleValArg->Int32Value(vm);
    }
    std::string fontInfo =
        StringUtils::FormatString(FORMAT_FONT.c_str(), fontSize.c_str(), weight.c_str(), fontFamily.c_str());
    GetArkUINodeModifiers()->getAlphabetIndexerModifier()->setAlphabetIndexerFont(
        nativeNode, fontInfo.c_str(), styleVal);
    if (SystemProperties::ConfigChangePerform()) {
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->createWithResourceObj(nativeNode,
            static_cast<int32_t>(IndexerJsResourceType::FONT_SIZE),
            reinterpret_cast<void*>(AceType::RawPtr(fontSizeResObj)));
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->createWithResourceObj(nativeNode,
            static_cast<int32_t>(IndexerJsResourceType::FONT_FAMILY),
            reinterpret_cast<void*>(AceType::RawPtr(fontFamilyResObj)));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::ResetFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getAlphabetIndexerModifier()->resetAlphabetIndexerFont(nativeNode);
    if (SystemProperties::ConfigChangePerform()) {
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->createWithResourceObj(
            nativeNode, static_cast<int32_t>(IndexerJsResourceType::FONT_SIZE), nullptr);
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->createWithResourceObj(
            nativeNode, static_cast<int32_t>(IndexerJsResourceType::FONT_FAMILY), nullptr);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::SetPopupItemBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Color color;
    RefPtr<ResourceObject> resObj;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color, resObj, nodeInfo)) {
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->resetPopupItemBackgroundColor(nativeNode);
    } else {
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->setPopupItemBackgroundColor(
            nativeNode, color.GetValue());
    }
    if (SystemProperties::ConfigChangePerform()) {
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->createWithResourceObj(nativeNode,
            static_cast<int32_t>(IndexerJsResourceType::POPUP_ITEM_BACKGROUND_COLOR),
            reinterpret_cast<void*>(AceType::RawPtr(resObj)));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::ResetPopupItemBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getAlphabetIndexerModifier()->resetPopupItemBackgroundColor(nativeNode);
    if (SystemProperties::ConfigChangePerform()) {
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->createWithResourceObj(
            nativeNode, static_cast<int32_t>(IndexerJsResourceType::POPUP_ITEM_BACKGROUND_COLOR), nullptr);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::SetColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Color color;
    RefPtr<ResourceObject> resObj;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color, resObj, nodeInfo)) {
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->resetAlphabetIndexerColor(nativeNode);
    } else {
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->setAlphabetIndexerColor(nativeNode, color.GetValue());
    }
    if (SystemProperties::ConfigChangePerform()) {
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->createWithResourceObj(nativeNode,
            static_cast<int32_t>(IndexerJsResourceType::COLOR),
            reinterpret_cast<void*>(AceType::RawPtr(resObj)));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::ResetColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getAlphabetIndexerModifier()->resetAlphabetIndexerColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::SetPopupColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Color color;
    RefPtr<ResourceObject> resObj;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color, resObj, nodeInfo)) {
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->resetPopupColor(nativeNode);
    } else {
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->setPopupColor(nativeNode, color.GetValue());
    }
    if (SystemProperties::ConfigChangePerform()) {
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->createWithResourceObj(nativeNode,
            static_cast<int32_t>(IndexerJsResourceType::POPUP_COLOR),
            reinterpret_cast<void*>(AceType::RawPtr(resObj)));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::ResetPopupColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getAlphabetIndexerModifier()->resetPopupColor(nativeNode);
    if (SystemProperties::ConfigChangePerform()) {
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->createWithResourceObj(
            nativeNode, static_cast<int32_t>(IndexerJsResourceType::COLOR), nullptr);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::SetSelectedColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Color color;
    RefPtr<ResourceObject> resObj;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color, resObj, nodeInfo)) {
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->resetAlphabetIndexerSelectedColor(nativeNode);
    } else {
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->setAlphabetIndexerSelectedColor(
            nativeNode, color.GetValue());
    }
    if (SystemProperties::ConfigChangePerform()) {
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->createWithResourceObj(nativeNode,
            static_cast<int32_t>(IndexerJsResourceType::SELECTED_COLOR),
            reinterpret_cast<void*>(AceType::RawPtr(resObj)));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::ResetSelectedColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getAlphabetIndexerModifier()->resetAlphabetIndexerSelectedColor(nativeNode);
    if (SystemProperties::ConfigChangePerform()) {
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->createWithResourceObj(
            nativeNode, static_cast<int32_t>(IndexerJsResourceType::SELECTED_COLOR), nullptr);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::SetPopupBackground(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Color color;
    RefPtr<ResourceObject> resObj;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color, resObj, nodeInfo)) {
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->resetPopupBackground(nativeNode);
    } else {
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->setPopupBackground(nativeNode, color.GetValue());
    }
    if (SystemProperties::ConfigChangePerform()) {
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->createWithResourceObj(nativeNode,
            static_cast<int32_t>(IndexerJsResourceType::POPUP_BACKGROUND),
            reinterpret_cast<void*>(AceType::RawPtr(resObj)));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::ResetPopupBackground(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getAlphabetIndexerModifier()->resetPopupBackground(nativeNode);
    if (SystemProperties::ConfigChangePerform()) {
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->createWithResourceObj(
            nativeNode, static_cast<int32_t>(IndexerJsResourceType::POPUP_BACKGROUND), nullptr);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::SetSelectedBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Color color;
    RefPtr<ResourceObject> resObj;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color, resObj, nodeInfo)) {
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->resetSelectedBackgroundColor(nativeNode);
    } else {
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->setSelectedBackgroundColor(
            nativeNode, color.GetValue());
    }
    if (SystemProperties::ConfigChangePerform()) {
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->createWithResourceObj(nativeNode,
            static_cast<int32_t>(IndexerJsResourceType::SELECTED_BACKGROUND_COLOR),
            reinterpret_cast<void*>(AceType::RawPtr(resObj)));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::ResetSelectedBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getAlphabetIndexerModifier()->resetSelectedBackgroundColor(nativeNode);
    if (SystemProperties::ConfigChangePerform()) {
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->createWithResourceObj(
            nativeNode, static_cast<int32_t>(IndexerJsResourceType::SELECTED_BACKGROUND_COLOR), nullptr);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::SetPopupUnselectedColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Color color;
    RefPtr<ResourceObject> resObj;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color, resObj, nodeInfo)) {
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->resetPopupUnselectedColor(nativeNode);
    } else {
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->setPopupUnselectedColor(nativeNode, color.GetValue());
    }
    if (SystemProperties::ConfigChangePerform()) {
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->createWithResourceObj(nativeNode,
            static_cast<int32_t>(IndexerJsResourceType::POPUP_UNSELECTED_COLOR),
            reinterpret_cast<void*>(AceType::RawPtr(resObj)));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::ResetPopupUnselectedColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (SystemProperties::ConfigChangePerform()) {
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->createWithResourceObj(
            nativeNode, static_cast<int32_t>(IndexerJsResourceType::POPUP_UNSELECTED_COLOR), nullptr);
    }
    GetArkUINodeModifiers()->getAlphabetIndexerModifier()->resetPopupUnselectedColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::SetAlignStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (!secondArg->IsNumber()) {
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->resetAlignStyle(nativeNode);
    } else {
        int32_t alignValue = secondArg->Int32Value(vm);
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->setAlignStyle(nativeNode, alignValue);
    }
    CalcDimension popupHorizontalSpace;
    RefPtr<ResourceObject> resObj;
    if (!thirdArg->IsNull() && !thirdArg->IsUndefined() &&
        ArkTSUtils::ParseJsDimensionVp(vm, thirdArg, popupHorizontalSpace, resObj)) {
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->setPopupHorizontalSpace(
            nativeNode, popupHorizontalSpace.Value(), static_cast<int>(popupHorizontalSpace.Unit()));
    } else {
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->resetPopupHorizontalSpace(nativeNode);
    }
    if (SystemProperties::ConfigChangePerform()) {
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->createWithResourceObj(nativeNode,
            static_cast<int32_t>(IndexerJsResourceType::ALIGN_OFFSET),
            reinterpret_cast<void*>(AceType::RawPtr(resObj)));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::ResetAlignStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getAlphabetIndexerModifier()->resetAlignStyle(nativeNode);
    if (SystemProperties::ConfigChangePerform()) {
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->createWithResourceObj(
            nativeNode, static_cast<int32_t>(IndexerJsResourceType::ALIGN_OFFSET), nullptr);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::SetPopupSelectedColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Color color;
    RefPtr<ResourceObject> resObj;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color, resObj, nodeInfo)) {
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->resetPopupSelectedColor(nativeNode);
    } else {
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->setPopupSelectedColor(nativeNode, color.GetValue());
    }
    if (SystemProperties::ConfigChangePerform()) {
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->createWithResourceObj(nativeNode,
            static_cast<int32_t>(IndexerJsResourceType::POPUP_SELECTED_COLOR),
            reinterpret_cast<void*>(AceType::RawPtr(resObj)));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::ResetPopupSelectedColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getAlphabetIndexerModifier()->resetPopupSelectedColor(nativeNode);
    if (SystemProperties::ConfigChangePerform()) {
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->createWithResourceObj(
            nativeNode, static_cast<int32_t>(IndexerJsResourceType::POPUP_SELECTED_COLOR), nullptr);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::SetUsingPopup(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> usingPopupArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    if (usingPopupArg->IsNull() || usingPopupArg->IsUndefined()) {
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->resetUsingPopup(nativeNode);
    } else {
        bool usingPopup = usingPopupArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->setUsingPopup(nativeNode, usingPopup);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::ResetUsingPopup(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getAlphabetIndexerModifier()->resetUsingPopup(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::SetSelected(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> selectedArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    int32_t selected = 0;
    if (selectedArg->IsNull() || selectedArg->IsUndefined() || !ArkTSUtils::ParseJsInteger(vm, selectedArg, selected)) {
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->resetAlphabetIndexerSelected(nativeNode);
    } else {
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->setAlphabetIndexerSelected(nativeNode, selected);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::ResetSelected(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getAlphabetIndexerModifier()->resetAlphabetIndexerSelected(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::SetItemSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> itemSizeArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    CalcDimension itemSize;

    if (itemSizeArg->IsNull() || itemSizeArg->IsUndefined()) {
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->resetItemSize(nativeNode);
    }

    if (ArkTSUtils::ParseJsDimensionVp(vm, itemSizeArg, itemSize) && GreatNotEqual(itemSize.Value(), 0.0) &&
        itemSize.Unit() != DimensionUnit::PERCENT) {
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->setItemSize(
            nativeNode, itemSize.Value(), static_cast<int>(itemSize.Unit()));
    } else {
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->resetItemSize(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::ResetItemSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getAlphabetIndexerModifier()->resetItemSize(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::SetPopupPosition(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> sizeX = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> sizeY = runtimeCallInfo->GetCallArgRef(NUM_2);
    CalcDimension x;
    CalcDimension y;
    RefPtr<ResourceObject> resObjX;
    RefPtr<ResourceObject> resObjY;
    if (sizeX->IsNull() || sizeX->IsUndefined() || !ArkTSUtils::ParseJsDimensionVp(vm, sizeX, x, resObjX)) {
        x = DEFAULT_POPUP_POSITION_X;
    }
    if (sizeY->IsNull() || sizeY->IsUndefined() || !ArkTSUtils::ParseJsDimensionVp(vm, sizeY, y, resObjY)) {
        y = DEFAULT_POPUP_POSITION_Y;
    }
    if (SystemProperties::ConfigChangePerform()) {
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->createWithResourceObj(nativeNode,
            static_cast<int32_t>(IndexerJsResourceType::POPUP_POSITION_X),
            reinterpret_cast<void*>(AceType::RawPtr(resObjX)));
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->createWithResourceObj(nativeNode,
            static_cast<int32_t>(IndexerJsResourceType::POPUP_POSITION_Y),
            reinterpret_cast<void*>(AceType::RawPtr(resObjY)));
    }
    GetArkUINodeModifiers()->getAlphabetIndexerModifier()->setPopupPosition(
        nativeNode, x.Value(), static_cast<int>(x.Unit()), y.Value(), static_cast<int>(y.Unit()));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::ResetPopupPosition(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getAlphabetIndexerModifier()->resetPopupPosition(nativeNode);
    if (SystemProperties::ConfigChangePerform()) {
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->createWithResourceObj(
            nativeNode, static_cast<int32_t>(IndexerJsResourceType::POPUP_POSITION_X), nullptr);
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->createWithResourceObj(
            nativeNode, static_cast<int32_t>(IndexerJsResourceType::POPUP_POSITION_Y), nullptr);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::SetPopupItemBorderRadius(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> radiusArg = runtimeCallInfo->GetCallArgRef(NUM_1);

    CalcDimension radius;
    CalcDimension popupRadius;
    if (radiusArg->IsNull() || radiusArg->IsUndefined() || !radiusArg->IsNumber()) {
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->resetPopupItemBorderRadius(nativeNode);
    } else {
        ArkTSUtils::ParseJsDimensionVp(vm, radiusArg, radius);
        popupRadius.SetValue(radius.Value() + RADIUS_OFFSET);
        popupRadius.SetUnit(DimensionUnit::VP);
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->setPopupItemBorderRadius(nativeNode, radius.Value(),
            static_cast<int>(radius.Unit()), popupRadius.Value(), static_cast<int>(popupRadius.Unit()));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::ResetPopupItemBorderRadius(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getAlphabetIndexerModifier()->resetPopupItemBorderRadius(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::SetItemBorderRadius(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> radiusArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto radius = CalcDimension(ZERO_RADIUS, DimensionUnit::VP);
    auto indexerRadius = Dimension(ZERO_RADIUS, DimensionUnit::VP);
    if (radiusArg->IsNull() || radiusArg->IsUndefined() || !radiusArg->IsNumber()) {
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->resetItemBorderRadius(nativeNode);
    } else {
        ArkTSUtils::ParseJsDimensionVp(vm, radiusArg, radius);
        indexerRadius.SetValue(radius.Value() + RADIUS_OFFSET);
        indexerRadius.SetUnit(DimensionUnit::VP);
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->setItemBorderRadius(nativeNode, radius.Value(),
            static_cast<int>(radius.Unit()), indexerRadius.Value(), static_cast<int>(indexerRadius.Unit()));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::ResetItemBorderRadius(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getAlphabetIndexerModifier()->resetItemBorderRadius(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::SetPopupBackgroundBlurStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> blurStyleArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    int32_t blurStyle = blurStyleArg->Int32Value(vm);
    if (!ArkTSUtils::ParseJsInteger(vm, blurStyleArg, blurStyle)) {
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->resetPopupBackgroundBlurStyle(nativeNode);
    } else {
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->setPopupBackgroundBlurStyle(nativeNode, blurStyle);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::ResetPopupBackgroundBlurStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getAlphabetIndexerModifier()->resetPopupBackgroundBlurStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue AlphabetIndexerBridge::SetPopupTitleBackground(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Color color;
    RefPtr<ResourceObject> resObj;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!ArkTSUtils::ParseJsColorAlpha(vm, colorArg, color, resObj, nodeInfo)) {
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->resetPopupTitleBackground(nativeNode);
    } else {
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->setPopupTitleBackground(nativeNode, color.GetValue());
    }
    if (SystemProperties::ConfigChangePerform()) {
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->createWithResourceObj(nativeNode,
            static_cast<int32_t>(IndexerJsResourceType::POPUP_TITLE_BACKGROUND),
            reinterpret_cast<void*>(AceType::RawPtr(resObj)));
    }
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue AlphabetIndexerBridge::ResetPopupTitleBackground(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getAlphabetIndexerModifier()->resetPopupTitleBackground(nativeNode);
    if (SystemProperties::ConfigChangePerform()) {
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->createWithResourceObj(
            nativeNode, static_cast<int32_t>(IndexerJsResourceType::POPUP_TITLE_BACKGROUND), nullptr);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::SetAdaptiveWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);

    CalcDimension width;
    ArkTSUtils::ParseJsDimensionVpNG(vm, secondArg, width);
    if (width.Unit() == DimensionUnit::AUTO) {
        CommonBridge::SetWidth(runtimeCallInfo);
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->setAdaptiveWidth(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    } else {
        CommonBridge::SetWidth(runtimeCallInfo);
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->resetAdaptiveWidth(nativeNode);
    }
    CommonBridge::SetWidth(runtimeCallInfo);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::ResetAdaptiveWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    CommonBridge::ResetWidth(runtimeCallInfo);
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getAlphabetIndexerModifier()->resetAdaptiveWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::SetAutoCollapse(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> autoCollapseArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    bool autoCollapse = true;
    if (autoCollapseArg->IsBoolean()) {
        autoCollapse = autoCollapseArg->ToBoolean(vm)->Value();
    }
    GetArkUINodeModifiers()->getAlphabetIndexerModifier()->setAutoCollapse(nativeNode, autoCollapse);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::ResetAutoCollapse(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getAlphabetIndexerModifier()->resetAutoCollapse(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::SetEnableHapticFeedback(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> hapticFeedbackArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    bool isHapticEnable = true;
    if (hapticFeedbackArg->IsBoolean()) {
        isHapticEnable = hapticFeedbackArg->ToBoolean(vm)->Value();
    }
    GetArkUINodeModifiers()->getAlphabetIndexerModifier()->setEnableHapticFeedback(nativeNode, isHapticEnable);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::ResetEnableHapticFeedback(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getAlphabetIndexerModifier()->resetEnableHapticFeedback(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::SetOnSelected(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->resetOnIndexerSelect(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);

    std::function<void(const int32_t selected)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)](
                                                               const int32_t selected) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        panda::Local<panda::JSValueRef> params[NUM_1] = { panda::NumberRef::New(vm, selected) };
        func->Call(vm, func.ToLocal(), params, NUM_1);
    };
    GetArkUINodeModifiers()->getAlphabetIndexerModifier()->setOnIndexerSelect(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::ResetOnSelected(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getAlphabetIndexerModifier()->resetOnIndexerSelect(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::SetOnSelect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->resetOnIndexerSelect(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);

    std::function<void(const int32_t selected)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)](
                                                               const int32_t selected) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        panda::Local<panda::JSValueRef> params[NUM_1] = { panda::NumberRef::New(vm, selected) };
        func->Call(vm, func.ToLocal(), params, NUM_1);
    };
    GetArkUINodeModifiers()->getAlphabetIndexerModifier()->setOnIndexerSelect(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::ResetOnSelect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getAlphabetIndexerModifier()->resetOnIndexerSelect(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::SetOnRequestPopupData(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->resetOnRequestPopupData(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);

    std::function<std::vector<std::string>(int32_t)> callback =
        [vm, frameNode, func = panda::CopyableGlobal(vm, func)](const int32_t selected) -> std::vector<std::string> {
        std::vector<std::string> popupData = {};
        CHECK_NULL_RETURN(vm, popupData);
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        panda::Local<panda::JSValueRef> params[NUM_1] = { panda::NumberRef::New(vm, selected) };
        auto result = func->Call(vm, func.ToLocal(), params, NUM_1);
        if (!result->IsArray(vm)) {
            return popupData;
        }
        auto array = panda::Local<panda::ArrayRef>(result);
        uint32_t length = array->Length(vm);
        for (uint32_t i = 0; i < length; ++i) {
            auto item = array->Get(vm, i);
            if (item->IsString(vm)) {
                popupData.emplace_back(item->ToString(vm)->ToString(vm));
            }
        }
        return popupData;
    };
    GetArkUINodeModifiers()->getAlphabetIndexerModifier()->setOnRequestPopupData(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::ResetOnRequestPopupData(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getAlphabetIndexerModifier()->resetOnRequestPopupData(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::SetOnPopupSelect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->resetOnPopupSelected(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);

    std::function<void(const int32_t selected)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)](
                                                               const int32_t selected) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        panda::Local<panda::JSValueRef> params[NUM_1] = { panda::NumberRef::New(vm, selected) };
        func->Call(vm, func.ToLocal(), params, NUM_1);
    };
    GetArkUINodeModifiers()->getAlphabetIndexerModifier()->setOnPopupSelected(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::ResetOnPopupSelect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getAlphabetIndexerModifier()->resetOnPopupSelected(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

} // namespace OHOS::Ace::NG
