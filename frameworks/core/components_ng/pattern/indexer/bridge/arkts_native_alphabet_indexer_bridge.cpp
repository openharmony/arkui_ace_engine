/*
 * Copyright (c) 2023-2026 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/indexer/bridge/arkts_native_alphabet_indexer_bridge.h"
#include "jsnapi_expo.h"
#include "ui/base/ace_type.h"
#include "ui/base/utils/utils.h"

#include "core/interfaces/native/node/node_api.h"
#include "core/components_ng/pattern/indexer/indexer_model_impl.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_common_bridge.h"
#include "core/components_ng/pattern/indexer/indexer_model_ng.h"
#include "core/components_ng/pattern/indexer/indexer_theme.h"
#include "frameworks/bridge/declarative_frontend/ark_theme/theme_apply/js_indexer_theme.h"

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

bool GetNativeNode(ArkUINodeHandle& nativeNode, const Local<JSValueRef>& firstArg, panda::ecmascript::EcmaVM* vm)
{
    if (firstArg->IsNativePointer(vm)) {
        nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
        return true;
    }
    if (firstArg->IsBoolean() && firstArg->ToBoolean(vm)->Value()) {
        nativeNode = nullptr;
        return true;
    }
    return false;
}

FrameNode* GetFrameNode(ArkUINodeHandle node)
{
    return node ? reinterpret_cast<FrameNode*>(node) : ViewStackProcessor::GetInstance()->GetMainFrameNode();
}

void ParseIndexerSelectedObject(const EcmaVM* vm, const Local<JSValueRef>& changeEventVal, bool isMethodProp = false)
{
    CHECK_NULL_VOID(changeEventVal->IsFunction(vm));
    auto targetNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(targetNode);
    panda::Local<panda::FunctionRef> func = changeEventVal->ToObject(vm);
    std::function<void(const int32_t selected)> changeEvent = [vm, targetNode, func = panda::CopyableGlobal(vm, func)](
                                                                  const int32_t selected) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(targetNode));
        panda::Local<panda::JSValueRef> params[1] = { panda::NumberRef::New(vm, selected) };
        auto result = func->Call(vm, func.ToLocal(), params, 1);
        ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
    };

    if (isMethodProp) {
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->setIndexerChangeEvent(
            reinterpret_cast<void*>(&changeEvent));
    } else {
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->setIndexerCreateChangeEvent(
            reinterpret_cast<void*>(&changeEvent));
    }
}
} // namespace

ArkUINativeModuleValue AlphabetIndexerBridge::SetPopupItemFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> fontSizeArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> weightArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = nodeArg->IsBoolean() && nodeArg->ToBoolean(vm)->Value();
    if (isJsView) {
        CalcDimension fontSize;
        std::string weight;
        RefPtr<ResourceObject> resObj;
        if (fontSizeArg->IsObject(vm)) {
            auto obj = fontSizeArg->ToObject(vm);
            auto size = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "size"));
            if (!size->IsNull()) {
                CalcDimension fontSizeData;
                if (ArkTSUtils::ParseJsDimensionFp(vm, size, fontSizeData, resObj) && !fontSizeData.IsNegative() &&
                    fontSizeData.Unit() != DimensionUnit::PERCENT) {
                    fontSize = fontSizeData;
                }
            }
            auto jsWeight = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "weight"));
            if (!jsWeight->IsNull()) {
                if (jsWeight->IsNumber()) {
                    weight = std::to_string(jsWeight->Int32Value(vm));
                } else {
                    ArkTSUtils::ParseJsString(vm, jsWeight, weight);
                }
            }
        }
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->setPopupItemFont(
            nativeNode, fontSize.Value(), static_cast<int>(fontSize.Unit()), weight.c_str());
        if (SystemProperties::ConfigChangePerform()) {
            GetArkUINodeModifiers()->getAlphabetIndexerModifier()->createWithResourceObj(nativeNode,
                static_cast<int32_t>(IndexerJsResourceType::POPUP_ITEM_FONT_SIZE),
                reinterpret_cast<void*>(AceType::RawPtr(resObj)));
        }
        return panda::JSValueRef::Undefined(vm);
    }
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

void GetFontContent(ArkUIRuntimeCallInfo* runtimeCallInfo, IndexerTextStyle& textStyle)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_VOID(vm);
    auto obj = runtimeCallInfo->GetCallArgRef(NUM_1)->ToObject(vm);
    auto size = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "size"));
    CalcDimension fontSizeData;
    if (ArkTSUtils::ParseJsDimensionFp(vm, size, fontSizeData, textStyle.fontSizeResObj) &&
        !fontSizeData.IsNegative() && fontSizeData.Unit() != DimensionUnit::PERCENT) {
        textStyle.fontSize = fontSizeData;
    }

    auto weight = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "weight"));
    if (weight->IsString(vm) || weight->IsNumber()) {
        textStyle.fontWeight = StringUtils::StringToFontWeight(weight->ToString(vm)->ToString(vm), FontWeight::NORMAL);
    }

    auto family = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "family"));
    std::vector<std::string> fontFamilies;
    if (ArkTSUtils::ParseJsFontFamilies(vm, family, fontFamilies, textStyle.fontFamilyResObj)) {
        textStyle.fontFamily = fontFamilies;
    }

    auto style = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "style"));
    if (style->IsNumber()) {
        int32_t value = style->Int32Value(vm);
        if (value >= 0 && value < static_cast<int32_t>(FONT_STYLES.size())) {
            textStyle.fontStyle = FONT_STYLES[value];
        }
    }
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
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = nodeArg->IsBoolean() && nodeArg->ToBoolean(vm)->Value();
    if (isJsView) {
        uint32_t argc = runtimeCallInfo->GetArgsNumber();
        if (argc < NUM_2) {
            return panda::JSValueRef::Undefined(vm);
        }
        IndexerTextStyle textStyle;
        if (fontSizeArg->IsObject(vm)) {
            GetFontContent(runtimeCallInfo, textStyle);
        }
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->setSelectedFontJs(&textStyle);
        if (SystemProperties::ConfigChangePerform()) {
            GetArkUINodeModifiers()->getAlphabetIndexerModifier()->createWithResourceObj(nativeNode,
                static_cast<int32_t>(IndexerJsResourceType::SELECTED_FONT_SIZE),
                reinterpret_cast<void*>(AceType::RawPtr(textStyle.fontSizeResObj)));
            GetArkUINodeModifiers()->getAlphabetIndexerModifier()->createWithResourceObj(nativeNode,
                static_cast<int32_t>(IndexerJsResourceType::SELECTED_FONT_FAMILY),
                reinterpret_cast<void*>(AceType::RawPtr(textStyle.fontFamilyResObj)));
        }
        return panda::JSValueRef::Undefined(vm);
    }
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
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = nodeArg->IsBoolean() && nodeArg->ToBoolean(vm)->Value();
    if (isJsView) {
        uint32_t argc = runtimeCallInfo->GetArgsNumber();
        if (argc < NUM_2) {
            return panda::JSValueRef::Undefined(vm);
        }
        IndexerTextStyle textStyle;
        if (fontSizeArg->IsObject(vm)) {
            GetFontContent(runtimeCallInfo, textStyle);
        }
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->setPopupFontJs(&textStyle);
        if (SystemProperties::ConfigChangePerform()) {
            GetArkUINodeModifiers()->getAlphabetIndexerModifier()->createWithResourceObj(nativeNode,
                static_cast<int32_t>(IndexerJsResourceType::POPUP_FONT_SIZE),
                reinterpret_cast<void*>(AceType::RawPtr(textStyle.fontSizeResObj)));
            GetArkUINodeModifiers()->getAlphabetIndexerModifier()->createWithResourceObj(nativeNode,
                static_cast<int32_t>(IndexerJsResourceType::POPUP_FONT_FAMILY),
                reinterpret_cast<void*>(AceType::RawPtr(textStyle.fontFamilyResObj)));
        }
        return panda::JSValueRef::Undefined(vm);
    }
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
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = nodeArg->IsBoolean() && nodeArg->ToBoolean(vm)->Value();
    if (isJsView) {
        uint32_t argc = runtimeCallInfo->GetArgsNumber();
        if (argc < NUM_2) {
            return panda::JSValueRef::Undefined(vm);
        }
        IndexerTextStyle textStyle;
        if (fontSizeArg->IsObject(vm)) {
            GetFontContent(runtimeCallInfo, textStyle);
        }
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->setFontJs(&textStyle);
        if (SystemProperties::ConfigChangePerform()) {
            GetArkUINodeModifiers()->getAlphabetIndexerModifier()->createWithResourceObj(nativeNode,
                static_cast<int32_t>(IndexerJsResourceType::FONT_SIZE),
                reinterpret_cast<void*>(AceType::RawPtr(textStyle.fontSizeResObj)));
            GetArkUINodeModifiers()->getAlphabetIndexerModifier()->createWithResourceObj(nativeNode,
                static_cast<int32_t>(IndexerJsResourceType::FONT_FAMILY),
                reinterpret_cast<void*>(AceType::RawPtr(textStyle.fontFamilyResObj)));
        }
        return panda::JSValueRef::Undefined(vm);
    }
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
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    Color color;
    RefPtr<ResourceObject> resObj;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    bool isColorValid = ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color, resObj, nodeInfo);
    bool isJsView = firstArg->IsBoolean() && firstArg->ToBoolean(vm)->Value();
    if (isJsView) {
        uint32_t argc = runtimeCallInfo->GetArgsNumber();
        if (argc < NUM_2) {
            return panda::JSValueRef::Undefined(vm);
        }
        bool setByUser = false;
        std::optional<Color> colorOpt;
        if (isColorValid) {
            setByUser = true;
            colorOpt = color;
        }
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->setPopupItemBackgroundColorJs(&colorOpt);
        if (SystemProperties::ConfigChangePerform()) {
            GetArkUINodeModifiers()->getAlphabetIndexerModifier()->createWithResourceObj(nativeNode,
                static_cast<int32_t>(IndexerJsResourceType::POPUP_ITEM_BACKGROUND_COLOR),
                reinterpret_cast<void*>(AceType::RawPtr(resObj)));
            GetArkUINodeModifiers()->getAlphabetIndexerModifier()->setPopupItemBackgroundColorByUser(setByUser);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    if (!isColorValid) {
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
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    Color color;
    RefPtr<ResourceObject> resObj;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    bool isColorValid = ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color, resObj, nodeInfo);
    bool isJsView = firstArg->IsBoolean() && firstArg->ToBoolean(vm)->Value();
    if (isJsView) {
        uint32_t argc = runtimeCallInfo->GetArgsNumber();
        if (argc < NUM_2) {
            return panda::JSValueRef::Undefined(vm);
        }
        bool setByUser = false;
        std::optional<Color> colorOpt;
        if (isColorValid) {
            setByUser = true;
            colorOpt = color;
        }
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->setAlphabetIndexerColorJs(&colorOpt);
        if (SystemProperties::ConfigChangePerform()) {
            GetArkUINodeModifiers()->getAlphabetIndexerModifier()->createWithResourceObj(nativeNode,
                static_cast<int32_t>(IndexerJsResourceType::COLOR),
                reinterpret_cast<void*>(AceType::RawPtr(resObj)));
            GetArkUINodeModifiers()->getAlphabetIndexerModifier()->setAlphabetIndexerColorByUser(setByUser);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    if (!isColorValid) {
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
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    Color color;
    RefPtr<ResourceObject> resObj;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    bool isColorValid = ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color, resObj, nodeInfo);
    bool isJsView = firstArg->IsBoolean() && firstArg->ToBoolean(vm)->Value();
    if (isJsView) {
        uint32_t argc = runtimeCallInfo->GetArgsNumber();
        if (argc < NUM_2) {
            return panda::JSValueRef::Undefined(vm);
        }
        bool setByUser = false;
        std::optional<Color> colorOpt;
        if (isColorValid) {
            setByUser = true;
            colorOpt = color;
        }
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->setPopupColorJs(&colorOpt);
        if (SystemProperties::ConfigChangePerform()) {
            GetArkUINodeModifiers()->getAlphabetIndexerModifier()->createWithResourceObj(nativeNode,
                static_cast<int32_t>(IndexerJsResourceType::POPUP_COLOR),
                reinterpret_cast<void*>(AceType::RawPtr(resObj)));
            GetArkUINodeModifiers()->getAlphabetIndexerModifier()->setPopupColorByUser(setByUser);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    if (!isColorValid) {
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
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    Color color;
    RefPtr<ResourceObject> resObj;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    bool isColorValid = ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color, resObj, nodeInfo);
    bool isJsView = firstArg->IsBoolean() && firstArg->ToBoolean(vm)->Value();
    if (isJsView) {
        uint32_t argc = runtimeCallInfo->GetArgsNumber();
        if (argc < NUM_2) {
            return panda::JSValueRef::Undefined(vm);
        }
        bool setByUser = false;
        std::optional<Color> colorOpt;
        if (isColorValid) {
            setByUser = true;
            colorOpt = color;
        }
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->setSelectedColorJs(&colorOpt);
        if (SystemProperties::ConfigChangePerform()) {
            GetArkUINodeModifiers()->getAlphabetIndexerModifier()->createWithResourceObj(nativeNode,
                static_cast<int32_t>(IndexerJsResourceType::SELECTED_COLOR),
                reinterpret_cast<void*>(AceType::RawPtr(resObj)));
            GetArkUINodeModifiers()->getAlphabetIndexerModifier()->setSelectedColorByUser(setByUser);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    if (!isColorValid) {
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
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    Color color;
    RefPtr<ResourceObject> resObj;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    bool isColorValid = ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color, resObj, nodeInfo);
    bool isJsView = firstArg->IsBoolean() && firstArg->ToBoolean(vm)->Value();
    if (isJsView) {
        uint32_t argc = runtimeCallInfo->GetArgsNumber();
        if (argc < NUM_2) {
            return panda::JSValueRef::Undefined(vm);
        }
        bool setByUser = false;
        std::optional<Color> colorOpt;
        if (isColorValid) {
            setByUser = true;
            colorOpt = color;
        }
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->setPopupBackgroundJs(&colorOpt);
        if (SystemProperties::ConfigChangePerform()) {
            GetArkUINodeModifiers()->getAlphabetIndexerModifier()->createWithResourceObj(nativeNode,
                static_cast<int32_t>(IndexerJsResourceType::POPUP_BACKGROUND),
                reinterpret_cast<void*>(AceType::RawPtr(resObj)));
            GetArkUINodeModifiers()->getAlphabetIndexerModifier()->setPopupBackgroundByUser(setByUser);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    if (!isColorValid) {
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
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    Color color;
    RefPtr<ResourceObject> resObj;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    bool isColorValid = ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color, resObj, nodeInfo);
    bool isJsView = firstArg->IsBoolean() && firstArg->ToBoolean(vm)->Value();
    if (isJsView) {
        uint32_t argc = runtimeCallInfo->GetArgsNumber();
        if (argc < NUM_2) {
            return panda::JSValueRef::Undefined(vm);
        }
        bool setByUser = false;
        std::optional<Color> colorOpt;
        if (isColorValid) {
            setByUser = true;
            colorOpt = color;
        }
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->setSelectedBackgroundColorJs(&colorOpt);
        if (SystemProperties::ConfigChangePerform()) {
            GetArkUINodeModifiers()->getAlphabetIndexerModifier()->createWithResourceObj(nativeNode,
                static_cast<int32_t>(IndexerJsResourceType::SELECTED_BACKGROUND_COLOR),
                reinterpret_cast<void*>(AceType::RawPtr(resObj)));
            GetArkUINodeModifiers()->getAlphabetIndexerModifier()->setSelectedBackgroundColorByUser(setByUser);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    if (!isColorValid) {
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
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    Color color;
    RefPtr<ResourceObject> resObj;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    bool isColorValid = ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color, resObj, nodeInfo);
    bool isJsView = firstArg->IsBoolean() && firstArg->ToBoolean(vm)->Value();
    if (isJsView) {
        uint32_t argc = runtimeCallInfo->GetArgsNumber();
        if (argc < NUM_2) {
            return panda::JSValueRef::Undefined(vm);
        }
        bool setByUser = false;
        std::optional<Color> colorOpt;
        if (isColorValid) {
            setByUser = true;
            colorOpt = color;
        }
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->setPopupUnselectedColorJs(&colorOpt);
        if (SystemProperties::ConfigChangePerform()) {
            GetArkUINodeModifiers()->getAlphabetIndexerModifier()->createWithResourceObj(nativeNode,
                static_cast<int32_t>(IndexerJsResourceType::POPUP_UNSELECTED_COLOR),
                reinterpret_cast<void*>(AceType::RawPtr(resObj)));
            GetArkUINodeModifiers()->getAlphabetIndexerModifier()->setPopupUnselectedColorByUser(setByUser);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    if (!isColorValid) {
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
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = firstArg->IsBoolean() && firstArg->ToBoolean(vm)->Value();
    if (isJsView) {
        uint32_t argc = runtimeCallInfo->GetArgsNumber();
        if (argc < NUM_2) {
            return panda::JSValueRef::Undefined(vm);
        }
        int32_t value = Container::IsCurrentUseNewPipeline() ? static_cast<int32_t>(NG::AlignStyle::END)
                                                             : static_cast<int32_t>(V2::AlignStyle::END);
        auto alignValue = -1;
        if (secondArg->IsNumber()) {
            alignValue = secondArg->Int32Value(vm);
        }
        if (alignValue >= 0 && alignValue < static_cast<int32_t>(ALIGN_STYLE.size())) {
            value = alignValue;
        }
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->setAlignStyle(nativeNode, value);
        CalcDimension popupHorizontalSpace(-1.0);
        RefPtr<ResourceObject> resObj;
        if (argc > NUM_2) {
            ArkTSUtils::ParseJsDimensionVp(vm, thirdArg, popupHorizontalSpace, resObj);
        }
        if (SystemProperties::ConfigChangePerform()) {
            GetArkUINodeModifiers()->getAlphabetIndexerModifier()->createWithResourceObj(nativeNode,
                static_cast<int32_t>(IndexerJsResourceType::ALIGN_OFFSET),
                reinterpret_cast<void*>(AceType::RawPtr(resObj)));
        }
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->setPopupHorizontalSpace(
            nativeNode, popupHorizontalSpace.Value(), static_cast<int>(popupHorizontalSpace.Unit()));
        return panda::JSValueRef::Undefined(vm);
    }
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
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    Color color;
    RefPtr<ResourceObject> resObj;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    bool isColorValid = ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color, resObj, nodeInfo);
    bool isJsView = firstArg->IsBoolean() && firstArg->ToBoolean(vm)->Value();
    if (isJsView) {
        uint32_t argc = runtimeCallInfo->GetArgsNumber();
        if (argc < NUM_2) {
            return panda::JSValueRef::Undefined(vm);
        }
        bool setByUser = false;
        std::optional<Color> colorOpt;
        if (isColorValid) {
            setByUser = true;
            colorOpt = color;
        }
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->setPopupSelectedColorJs(&colorOpt);
        if (SystemProperties::ConfigChangePerform()) {
            GetArkUINodeModifiers()->getAlphabetIndexerModifier()->createWithResourceObj(nativeNode,
                static_cast<int32_t>(IndexerJsResourceType::POPUP_SELECTED_COLOR),
                reinterpret_cast<void*>(AceType::RawPtr(resObj)));
            GetArkUINodeModifiers()->getAlphabetIndexerModifier()->setPopupSelectedColorByUser(setByUser);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    if (!isColorValid) {
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
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = nodeArg->IsBoolean() && nodeArg->ToBoolean(vm)->Value();
    bool isUnValid = usingPopupArg->IsNull() || usingPopupArg->IsUndefined();
    if (isUnValid && !isJsView) {
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->resetUsingPopup(nativeNode);
    };
    if (!isUnValid) {
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

ArkUINativeModuleValue JsAlphabetIndexerSelect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    uint32_t argc = runtimeCallInfo->GetArgsNumber();
    if (argc < NUM_2) {
        return panda::JSValueRef::Undefined(vm);
    }
    int32_t selected = 0;
    Local<JSValueRef> selectedVal = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> changeEventVal;
    if (selectedVal->IsObject(vm)) {
        auto jsObj = selectedVal->ToObject(vm);
        selectedVal = jsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "value"));
        changeEventVal = jsObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "$value"));
    } else if (argc > NUM_2) {
        changeEventVal = runtimeCallInfo->GetCallArgRef(NUM_2);
    }
    if (ArkTSUtils::ParseJsIntegerWithResource(vm, selectedVal, selected)) {
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->setAlphabetIndexerSelected(nullptr, selected);
    }
    ParseIndexerSelectedObject(vm, changeEventVal, true);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue AlphabetIndexerBridge::SetSelected(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> selectedArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = nodeArg->IsBoolean() && nodeArg->ToBoolean(vm)->Value();
    if (isJsView) {
        JsAlphabetIndexerSelect(runtimeCallInfo);
        return panda::JSValueRef::Undefined(vm);
    }
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
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
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
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = nodeArg->IsBoolean() && nodeArg->ToBoolean(vm)->Value();
    if (isJsView) {
        Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_1);
        std::optional<Dimension> xOpt;
        std::optional<Dimension> yOpt;
        if (firstArg->IsObject(vm)) {
            auto obj = firstArg->ToObject(vm);
            CalcDimension x;
            CalcDimension y;
            RefPtr<ResourceObject> resObjX;
            RefPtr<ResourceObject> resObjY;
            auto xVal = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "x"));
            auto yVal = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "y"));
            if ((xVal->IsString(vm) &&
                    StringUtils::StringToCalcDimensionNG(xVal->ToString(vm)->ToString(vm), x, false)) ||
                (!xVal->IsString(vm) && ArkTSUtils::ParseJsDimensionVp(vm, xVal, x, resObjX))) {
                xOpt = x;
            }
            if ((yVal->IsString(vm) &&
                    StringUtils::StringToCalcDimensionNG(yVal->ToString(vm)->ToString(vm), y, false)) ||
                (!yVal->IsString(vm) && ArkTSUtils::ParseJsDimensionVp(vm, yVal, y, resObjY))) {
                yOpt = y;
            }
            if (SystemProperties::ConfigChangePerform()) {
                GetArkUINodeModifiers()->getAlphabetIndexerModifier()->createWithResourceObj(nativeNode,
                    static_cast<int32_t>(IndexerJsResourceType::POPUP_POSITION_X),
                    reinterpret_cast<void*>(AceType::RawPtr(resObjX)));
                GetArkUINodeModifiers()->getAlphabetIndexerModifier()->createWithResourceObj(nativeNode,
                    static_cast<int32_t>(IndexerJsResourceType::POPUP_POSITION_Y),
                    reinterpret_cast<void*>(AceType::RawPtr(resObjY)));
            }
        } else if (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
            return panda::JSValueRef::Undefined(vm);
        }
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->setPopupPositionJs(&xOpt, &yOpt);
        return panda::JSValueRef::Undefined(vm);
    }
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
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = nodeArg->IsBoolean() && nodeArg->ToBoolean(vm)->Value();
    Local<JSValueRef> radiusArg = runtimeCallInfo->GetCallArgRef(NUM_1);

    CalcDimension radius;
    CalcDimension popupRadius;
    if (radiusArg->IsNull() || radiusArg->IsUndefined() || !radiusArg->IsNumber()) {
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->resetPopupItemBorderRadius(nativeNode);
    } else {
        if (isJsView) {
            radius = Dimension(ZERO_RADIUS, DimensionUnit::VP);
            auto radiusValue = radiusArg->ToNumber(vm)->Value();
            if (radiusValue >= 0) {
                radius.SetValue(radiusValue);
                radius.SetUnit(DimensionUnit::VP);
            }
        } else {
            ArkTSUtils::ParseJsDimensionVp(vm, radiusArg, radius);
        }
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
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = nodeArg->IsBoolean() && nodeArg->ToBoolean(vm)->Value();
    Local<JSValueRef> radiusArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto radius = CalcDimension(ZERO_RADIUS, DimensionUnit::VP);
    auto indexerRadius = Dimension(ZERO_RADIUS, DimensionUnit::VP);
    if (radiusArg->IsNull() || radiusArg->IsUndefined() || !radiusArg->IsNumber()) {
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->resetItemBorderRadius(nativeNode);
    } else {
        if (isJsView) {
            radius = Dimension(ZERO_RADIUS, DimensionUnit::VP);
            auto radiusValue = radiusArg->ToNumber(vm)->Value();
            if (radiusValue >= 0) {
                radius.SetValue(radiusValue);
                radius.SetUnit(DimensionUnit::VP);
            }
        } else {
            ArkTSUtils::ParseJsDimensionVp(vm, radiusArg, radius);
        }
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
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> blurStyleArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    bool isJsView = nodeArg->IsBoolean() && nodeArg->ToBoolean(vm)->Value();
    if (isJsView) {
        uint32_t argc = runtimeCallInfo->GetArgsNumber();
        if (argc < NUM_2) {
            return panda::JSValueRef::Undefined(vm);
        }
        BlurStyle blurStyle;
        if (blurStyleArg->IsNumber()) {
            auto blurStyleInt = blurStyleArg->Int32Value(vm);
            if (blurStyleInt >= static_cast<int>(BlurStyle::NO_MATERIAL) &&
                blurStyleInt <= static_cast<int>(BlurStyle::COMPONENT_ULTRA_THICK)) {
                blurStyle = static_cast<BlurStyle>(blurStyleInt);
            } else {
                blurStyle = BlurStyle::COMPONENT_REGULAR;
            }
        } else {
            blurStyle = BlurStyle::COMPONENT_REGULAR;
        }
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->setPopupBackgroundBlurStyle(
            nativeNode, static_cast<ArkUI_Uint32>(blurStyle));
    }

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
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Color color;
    RefPtr<ResourceObject> resObj;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    bool isColorValid = ArkTSUtils::ParseJsColorAlpha(vm, colorArg, color, resObj, nodeInfo);
    bool isJsView = nodeArg->IsBoolean() && nodeArg->ToBoolean(vm)->Value();
    if (isJsView) {
        uint32_t argc = runtimeCallInfo->GetArgsNumber();
        if (argc < NUM_2) {
            return panda::JSValueRef::Undefined(vm);
        }
        bool setByUser = false;
        std::optional<Color> colorOpt;
        if (isColorValid) {
            setByUser = true;
            colorOpt = color;
        }
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->setPopupTitleBackgroundJs(&colorOpt);
        if (SystemProperties::ConfigChangePerform()) {
            GetArkUINodeModifiers()->getAlphabetIndexerModifier()->createWithResourceObj(nativeNode,
                static_cast<int32_t>(IndexerJsResourceType::POPUP_TITLE_BACKGROUND),
                reinterpret_cast<void*>(AceType::RawPtr(resObj)));
            GetArkUINodeModifiers()->getAlphabetIndexerModifier()->setPopupTitleBackgroundByUser(setByUser);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    if (!isColorValid) {
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

bool JsAdaptiveWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, false);
    Local<JSValueRef> jsValue = runtimeCallInfo->GetCallArgRef(1);
    ViewAbstractModel::GetInstance()->ResetResObj("width");
    CalcDimension value;
    RefPtr<ResourceObject> valueResObj;
    if (jsValue->IsUndefined()) {
        ViewAbstractModel::GetInstance()->UpdateLayoutPolicyProperty(LayoutCalPolicy::NO_MATCH, true);
        ViewAbstractModel::GetInstance()->ClearWidthOrHeight(true);
        return true;
    }
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
        if (!ArkTSUtils::ParseJsDimensionVpNG(vm, jsValue, value, valueResObj)) {
            // JsWidth return false, check if set LayoutPolicy before return.
            ViewAbstractModel::GetInstance()->ClearWidthOrHeight(true);
            if (jsValue->IsObject(vm)) {
                auto object = jsValue->ToObject(vm);
                auto layoutPolicy = object->Get(vm, panda::StringRef::NewFromUtf8(vm, "id_"));
                if (layoutPolicy->IsString(vm)) {
                    auto policy = CommonBridge::ParseLayoutPolicy(layoutPolicy->ToString(vm)->ToString(vm));
                    ViewAbstractModel::GetInstance()->UpdateLayoutPolicyProperty(policy, true);
                    return true;
                }
            }
            ViewAbstractModel::GetInstance()->UpdateLayoutPolicyProperty(LayoutCalPolicy::NO_MATCH, true);
            return false;
        }
    } else if (!ArkTSUtils::ParseJsDimensionVp(vm, jsValue, value, valueResObj)) {
        return false;
    }

    ViewAbstractModel::GetInstance()->UpdateLayoutPolicyProperty(LayoutCalPolicy::NO_MATCH, true);
    if (!SystemProperties::ConfigChangePerform() ? LessNotEqual(value.Value(), 0.0)
                                                 : (LessNotEqual(value.Value(), 0.0) && !valueResObj)) {
        if (AceApplicationInfo::GetInstance().GreatOrEqualTargetAPIVersion(PlatformVersion::VERSION_TWELVE)) {
            ViewAbstractModel::GetInstance()->ClearWidthOrHeight(true);
            return true;
        } else {
            value.SetValue(0.0);
        }
    }

    if (SystemProperties::ConfigChangePerform() && valueResObj) {
        ViewAbstractModel::GetInstance()->SetWidth(valueResObj);
    } else {
        ViewAbstractModel::GetInstance()->SetWidth(value);
    }
    return true;
}

ArkUINativeModuleValue AlphabetIndexerBridge::SetAdaptiveWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    bool isJsView = firstArg->IsBoolean() && firstArg->ToBoolean(vm)->Value();
    if (isJsView) {
        JsAdaptiveWidth(runtimeCallInfo);
        if (secondArg->IsString(vm) && secondArg->ToString(vm)->ToString(vm) == "auto") {
            GetArkUINodeModifiers()->getAlphabetIndexerModifier()->setAdaptiveWidth(nativeNode);
        } else {
            GetArkUINodeModifiers()->getAlphabetIndexerModifier()->resetAdaptiveWidth(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }

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
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
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
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
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
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = firstArg->IsBoolean() && firstArg->ToBoolean(vm)->Value();
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        if (!isJsView) {
            GetArkUINodeModifiers()->getAlphabetIndexerModifier()->resetOnIndexerSelect(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = GetFrameNode(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(const int32_t selected)> callback =
        [vm, frameNode, isJsView, func = panda::CopyableGlobal(vm, func)](const int32_t selected) {
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
            panda::Local<panda::JSValueRef> params[NUM_1] = { panda::NumberRef::New(vm, selected) };
            auto result = func->Call(vm, func.ToLocal(), params, NUM_1);
            if (isJsView) {
                ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
            }
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
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
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
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = firstArg->IsBoolean() && firstArg->ToBoolean(vm)->Value();
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        if (!isJsView) {
            GetArkUINodeModifiers()->getAlphabetIndexerModifier()->resetOnIndexerSelect(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = GetFrameNode(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);

    std::function<void(const int32_t selected)> callback =
        [vm, frameNode, isJsView, func = panda::CopyableGlobal(vm, func)](const int32_t selected) {
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
            panda::Local<panda::JSValueRef> params[NUM_1] = { panda::NumberRef::New(vm, selected) };
            auto result = func->Call(vm, func.ToLocal(), params, NUM_1);
            if (isJsView) {
                ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
            }
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
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
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
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = firstArg->IsBoolean() && firstArg->ToBoolean(vm)->Value();
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        if (!isJsView) {
            GetArkUINodeModifiers()->getAlphabetIndexerModifier()->resetOnRequestPopupData(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = GetFrameNode(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);

    std::function<std::vector<std::string>(int32_t)> callback =
        [vm, frameNode, isJsView, func = panda::CopyableGlobal(vm, func)](
            const int32_t selected) -> std::vector<std::string> {
        std::vector<std::string> popupData = {};
        CHECK_NULL_RETURN(vm, popupData);
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        panda::Local<panda::JSValueRef> params[NUM_1] = { panda::NumberRef::New(vm, selected) };
        auto result = func->Call(vm, func.ToLocal(), params, NUM_1);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        }
        if (!result->IsArray(vm)) {
            return popupData;
        }
        auto array = panda::Local<panda::ArrayRef>(result);
        uint32_t length = static_cast<uint32_t>(ArkTSUtils::GetArrayLength(vm, array));
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
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
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
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->resetOnPopupSelected(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = GetFrameNode(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);

    bool isJsView = firstArg->IsBoolean() && firstArg->ToBoolean(vm)->Value();
    std::function<void(const int32_t selected)> callback =
        [vm, frameNode, isJsView, func = panda::CopyableGlobal(vm, func)](const int32_t selected) {
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
            panda::Local<panda::JSValueRef> params[NUM_1] = { panda::NumberRef::New(vm, selected) };
            auto result = func->Call(vm, func.ToLocal(), params, NUM_1);
            if (isJsView) {
                ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
            }
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
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getAlphabetIndexerModifier()->resetOnPopupSelected(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

void AlphabetIndexerBridge::RegisterIndexerAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    const char* functionNames[] = { "create", "setPopupItemFont", "resetPopupItemFont", "setSelectedFont",
        "resetSelectedFont", "setPopupFont", "resetPopupFont", "setFont", "resetFont", "setPopupItemBackgroundColor",
        "resetPopupItemBackgroundColor", "setColor", "resetColor", "setPopupColor", "resetPopupColor",
        "setSelectedColor", "resetSelectedColor", "setPopupBackground", "resetPopupBackground",
        "setSelectedBackgroundColor", "resetSelectedBackgroundColor", "setPopupUnselectedColor",
        "resetPopupUnselectedColor", "setPopupSelectedColor", "resetPopupSelectedColor", "setAlignStyle",
        "resetAlignStyle", "setUsingPopup", "resetUsingPopup", "setSelected", "resetSelected", "setItemSize",
        "resetItemSize", "setPopupPosition", "resetPopupPosition", "setPopupItemBorderRadius",
        "resetPopupItemBorderRadius", "setItemBorderRadius", "resetItemBorderRadius", "setPopupBackgroundBlurStyle",
        "resetPopupBackgroundBlurStyle", "setPopupTitleBackground", "resetPopupTitleBackground", "setAdaptiveWidth",
        "resetAdaptiveWidth", "setAutoCollapse", "resetAutoCollapse", "setEnableHapticFeedback",
        "resetEnableHapticFeedback", "setOnSelected", "resetOnSelected", "setOnSelect", "resetOnSelect",
        "setOnRequestPopupData", "resetOnRequestPopupData", "setOnPopupSelect", "resetOnPopupSelect" };

    Local<JSValueRef> funcValues[] = {
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::CreateIndexer),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::SetPopupItemFont),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::ResetPopupItemFont),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::SetSelectedFont),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::ResetSelectedFont),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::SetPopupFont),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::ResetPopupFont),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::SetFont),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::ResetFont),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::SetPopupItemBackgroundColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::ResetPopupItemBackgroundColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::SetColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::ResetColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::SetPopupColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::ResetPopupColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::SetSelectedColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::ResetSelectedColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::SetPopupBackground),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::ResetPopupBackground),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::SetSelectedBackgroundColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::ResetSelectedBackgroundColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::SetPopupUnselectedColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::ResetPopupUnselectedColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::SetPopupSelectedColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::ResetPopupSelectedColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::SetAlignStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::ResetAlignStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::SetUsingPopup),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::ResetUsingPopup),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::SetSelected),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::ResetSelected),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::SetItemSize),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::ResetItemSize),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::SetPopupPosition),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::ResetPopupPosition),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::SetPopupItemBorderRadius),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::ResetPopupItemBorderRadius),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::SetItemBorderRadius),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::ResetItemBorderRadius),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::SetPopupBackgroundBlurStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::ResetPopupBackgroundBlurStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::SetPopupTitleBackground),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::ResetPopupTitleBackground),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::SetAdaptiveWidth),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::ResetAdaptiveWidth),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::SetAutoCollapse),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::ResetAutoCollapse),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::SetEnableHapticFeedback),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::ResetEnableHapticFeedback),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::SetOnSelected),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::ResetOnSelected),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::SetOnSelect),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::ResetOnSelect),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::SetOnRequestPopupData),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::ResetOnRequestPopupData),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::SetOnPopupSelect),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), AlphabetIndexerBridge::ResetOnPopupSelect),
    };

    auto alphabetIndexer =
        panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(functionNames), functionNames, funcValues);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "alphabetIndexer"), alphabetIndexer);
}

ArkUINativeModuleValue AlphabetIndexerBridge::CreateIndexer(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    uint32_t argc = runtimeCallInfo->GetArgsNumber();
    if (argc < NUM_2) {
        return panda::JSValueRef::Undefined(vm);
    }
    bool isArc = false;
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    if (secondArg->IsBoolean()) {
        isArc = secondArg->ToBoolean(vm)->Value();
    }
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsObject(vm), panda::JSValueRef::Undefined(vm));
    auto firstArgObj = firstArg->ToObject(vm);
    auto arrayProperty = firstArgObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "arrayValue"));
    CHECK_NULL_RETURN(arrayProperty->IsArray(vm), panda::JSValueRef::Undefined(vm));
    std::vector<std::string> indexerData = {};
    auto array = panda::Local<panda::ArrayRef>(arrayProperty);
    uint32_t length = static_cast<uint32_t>(ArkTSUtils::GetArrayLength(vm, array));
    for (uint32_t i = 0; i < length; ++i) {
        auto item = array->Get(vm, i);
        if (item->IsString(vm)) {
            indexerData.emplace_back(item->ToString(vm)->ToString(vm));
        }
    }
    int32_t selected = 0;
    Local<JSValueRef> selectedProperty = firstArgObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "selected"));
    if (selectedProperty->IsNumber()) {
        selected = static_cast<int32_t>(selectedProperty->ToNumber(vm)->Value());
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->create(&indexerData, selected, isArc);
        Framework::JSIndexerTheme::ApplyTheme();
        Local<JSValueRef> changeEventVal = firstArgObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "$selected"));
        ParseIndexerSelectedObject(vm, changeEventVal);
    } else if (!isArc && length > 0 && selectedProperty->IsObject(vm)) {
        auto selectedObj = selectedProperty->ToObject(vm);
        auto selectedValueProperty = selectedObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "value"));
        if (selectedValueProperty->IsNumber()) {
            selected = static_cast<int32_t>(selectedValueProperty->ToNumber(vm)->Value());
        }
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->create(&indexerData, selected, isArc);
        Framework::JSIndexerTheme::ApplyTheme();
        auto changeEventVal = selectedObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "changeEvent"));
        if (!changeEventVal.IsEmpty()) {
            if (!changeEventVal->IsUndefined() && changeEventVal->IsFunction(vm)) {
                ParseIndexerSelectedObject(vm, changeEventVal);
            }
            return panda::JSValueRef::Undefined(vm);
        }
    } else {
        GetArkUINodeModifiers()->getAlphabetIndexerModifier()->create(&indexerData, selected, isArc);
        Framework::JSIndexerTheme::ApplyTheme();
    }
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
