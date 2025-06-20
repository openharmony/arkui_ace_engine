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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_menu_item_bridge.h"

#include "core/components_ng/pattern/menu/menu_item/menu_item_model_ng.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"

using namespace OHOS::Ace::Framework;

namespace OHOS::Ace::NG {
const std::string FORMAT_FONT = "%s|%s|%s";
const std::string DEFAULT_ERR_CODE = "-1";
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
ArkUINativeModuleValue MenuItemBridge::SetMenuItemSelected(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> isSelectedArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    if (isSelectedArg->IsBoolean()) {
        bool isSelected = isSelectedArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getMenuItemModifier()->setMenuItemSelected(nativeNode, isSelected);
    } else {
        GetArkUINodeModifiers()->getMenuItemModifier()->resetMenuItemSelected(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MenuItemBridge::ResetMenuItemSelected(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getMenuItemModifier()->resetMenuItemSelected(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MenuItemBridge::SetLabelFontColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Color color;
    RefPtr<ResourceObject> colorResObj;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, colorArg, color, colorResObj)) {
        GetArkUINodeModifiers()->getMenuItemModifier()->resetLabelFontColor(nativeNode);
    } else {
        auto colorRawPtr = AceType::RawPtr(colorResObj);
        GetArkUINodeModifiers()->getMenuItemModifier()->setLabelFontColor(nativeNode, color.GetValue(), colorRawPtr);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MenuItemBridge::ResetLabelFontColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getMenuItemModifier()->resetLabelFontColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MenuItemBridge::SetContentFontColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Color color;
    RefPtr<ResourceObject> colorResObj;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, colorArg, color, colorResObj)) {
        GetArkUINodeModifiers()->getMenuItemModifier()->resetContentFontColor(nativeNode);
    } else {
        auto colorRawPtr = AceType::RawPtr(colorResObj);
        GetArkUINodeModifiers()->getMenuItemModifier()->setContentFontColor(nativeNode, color.GetValue(), colorRawPtr);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MenuItemBridge::ResetContentFontColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getMenuItemModifier()->resetContentFontColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MenuItemBridge::SetLabelFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> sizeArg = runtimeCallInfo->GetCallArgRef(1);   // 1: label font size
    Local<JSValueRef> weightArg = runtimeCallInfo->GetCallArgRef(2); // 2: label font weight
    Local<JSValueRef> familyArg = runtimeCallInfo->GetCallArgRef(3); // 3: label font family
    Local<JSValueRef> styleArg = runtimeCallInfo->GetCallArgRef(4);  // 4: label font style
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    if (sizeArg->IsUndefined() && weightArg->IsUndefined() && familyArg->IsUndefined() && styleArg->IsUndefined()) {
        GetArkUINodeModifiers()->getMenuItemModifier()->resetLabelFont(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    CalcDimension fontSize;
    RefPtr<ResourceObject> fontSizeResObj;
    if (!ArkTSUtils::ParseJsDimensionFp(vm, sizeArg, fontSize, fontSizeResObj, false)) {
        fontSize = Dimension(0.0);
    }

    std::string weight = DEFAULT_ERR_CODE;
    if (weightArg->IsNumber()) {
        weight = std::to_string(weightArg->Int32Value(vm));
    } else {
        if (!ArkTSUtils::ParseJsString(vm, weightArg, weight) || weight.empty()) {
            weight = DEFAULT_ERR_CODE;
        }
    }

    int32_t style = -1;
    if (styleArg->IsNumber()) {
        style = styleArg->Int32Value(vm);
    }

    std::string family;
    RefPtr<ResourceObject> fontFamiliesResObj;
    if (!ArkTSUtils::ParseJsFontFamiliesToString(vm, familyArg, family, fontFamiliesResObj) || family.empty()) {
        family = DEFAULT_ERR_CODE;
    }

    std::string fontSizeStr = fontSize.ToString();
    std::string fontInfo =
        StringUtils::FormatString(FORMAT_FONT.c_str(), fontSizeStr.c_str(), weight.c_str(), family.c_str());
    auto fontFamiliesRawPtr = AceType::RawPtr(fontFamiliesResObj);
    auto fontSizeRawPtr = AceType::RawPtr(fontSizeResObj);
    GetArkUINodeModifiers()->getMenuItemModifier()->setLabelFont(
        nativeNode, fontInfo.c_str(), style, fontFamiliesRawPtr, fontSizeRawPtr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MenuItemBridge::ResetLabelFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getMenuItemModifier()->resetLabelFont(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MenuItemBridge::SetContentFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> sizeArg = runtimeCallInfo->GetCallArgRef(1);   // 1: index of font size
    Local<JSValueRef> weightArg = runtimeCallInfo->GetCallArgRef(2); // 2: index of font weight
    Local<JSValueRef> familyArg = runtimeCallInfo->GetCallArgRef(3); // 3: index of font family
    Local<JSValueRef> styleArg = runtimeCallInfo->GetCallArgRef(4);  // 4: index of font style
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    if (sizeArg->IsUndefined() && weightArg->IsUndefined() && familyArg->IsUndefined() && styleArg->IsUndefined()) {
        GetArkUINodeModifiers()->getMenuItemModifier()->resetContentFont(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    CalcDimension fontSize;
    RefPtr<ResourceObject> fontSizeResObj;
    if (!ArkTSUtils::ParseJsDimensionFp(vm, sizeArg, fontSize, fontSizeResObj, false)) {
        fontSize = Dimension(0.0);
    }

    std::string weight = DEFAULT_ERR_CODE;
    if (weightArg->IsNumber()) {
        weight = std::to_string(weightArg->Int32Value(vm));
    } else {
        if (!ArkTSUtils::ParseJsString(vm, weightArg, weight) || weight.empty()) {
            weight = DEFAULT_ERR_CODE;
        }
    }

    int32_t style = -1;
    if (styleArg->IsNumber()) {
        style = styleArg->Int32Value(vm);
    }

    std::string family;
    RefPtr<ResourceObject> fontFamiliesResObj;
    if (!ArkTSUtils::ParseJsFontFamiliesToString(vm, familyArg, family, fontFamiliesResObj) || family.empty()) {
        family = DEFAULT_ERR_CODE;
    }

    std::string fontSizeStr = fontSize.ToString();
    std::string fontInfo =
        StringUtils::FormatString(FORMAT_FONT.c_str(), fontSizeStr.c_str(), weight.c_str(), family.c_str());
    auto fontFamiliesRawPtr = AceType::RawPtr(fontFamiliesResObj);
    auto fontSizeRawPtr = AceType::RawPtr(fontSizeResObj);
    GetArkUINodeModifiers()->getMenuItemModifier()->setContentFont(
        nativeNode, fontInfo.c_str(), style, fontSizeRawPtr, fontFamiliesRawPtr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MenuItemBridge::ResetContentFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getMenuItemModifier()->resetContentFont(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MenuItemBridge::SetSelectIcon(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> inputArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    std::function<void(WeakPtr<NG::FrameNode>)> symbolApply;
    bool isShow = false;
    std::string icon;
    RefPtr<ResourceObject> selectIconResObj;
    if (inputArg->IsBoolean()) {
        isShow = inputArg->ToBoolean(vm)->Value();
    } else if (inputArg->IsString(vm)) {
        icon = inputArg->ToString(vm)->ToString(vm);
        isShow = true;
    } else if (ArkTSUtils::ParseJsMedia(vm, inputArg, icon, selectIconResObj)) {
        isShow = true;
    } else if (inputArg->IsObject(vm)) {
        isShow = true;
        Framework::JsiCallbackInfo info = Framework::JsiCallbackInfo(runtimeCallInfo);
        Framework::JSViewAbstract::SetSymbolOptionApply(runtimeCallInfo, symbolApply, info[1]);
    }
    auto selectIconRawPtr = AceType::RawPtr(selectIconResObj);
    GetArkUINodeModifiers()->getMenuItemModifier()->setSelectIcon(nativeNode, isShow);
    GetArkUINodeModifiers()->getMenuItemModifier()->setSelectIconSrc(nativeNode, icon.c_str(), selectIconRawPtr);
    GetArkUINodeModifiers()->getMenuItemModifier()->setSelectIconSymbol(
        nativeNode, reinterpret_cast<void*>(&symbolApply));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MenuItemBridge::ResetSelectIcon(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getMenuItemModifier()->resetSelectIcon(nativeNode);
    GetArkUINodeModifiers()->getMenuItemModifier()->resetSelectIconSrc(nativeNode);
    GetArkUINodeModifiers()->getMenuItemModifier()->resetSelectIconSymbol(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MenuItemBridge::SetOnChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    uint32_t argsNumber = runtimeCallInfo->GetArgsNumber();
    if (argsNumber != NUM_2) {
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getMenuItemModifier()->resetOnChange(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(bool)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)](bool flag) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        panda::Local<panda::JSValueRef> params[1] = { panda::BooleanRef::New(vm, flag) };
        func->Call(vm, func.ToLocal(), params, 1);
    };
    GetArkUINodeModifiers()->getMenuItemModifier()->setOnChange(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MenuItemBridge::ResetOnChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getMenuItemModifier()->resetOnChange(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

} // namespace OHOS::Ace::NG