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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_navigation_bridge.h"

#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_navigation_utils.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "core/components_ng/pattern/navigation/navigation_declaration.h"
#include "core/components_ng/pattern/navigation/navigation_model_ng.h"
#include "frameworks/bridge/declarative_frontend/engine/js_types.h"
namespace OHOS::Ace::NG {} // namespace OHOS::Ace::NG
namespace OHOS::Ace::NG {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;

ArkUINativeModuleValue NavigationBridge::SetHideToolBar(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> hideArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    if (hideArg->IsNull() || hideArg->IsUndefined() || !hideArg->IsBoolean()) {
        GetArkUINodeModifiers()->getNavigationModifier()->resetHideToolBar(nativeNode);
    } else {
        bool hide = hideArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getNavigationModifier()->setHideToolBar(nativeNode, hide);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::ResetHideToolBar(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getNavigationModifier()->resetHideToolBar(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::SetTitleMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    int32_t value;
    if (valueArg->IsNull() || valueArg->IsUndefined() || !ArkTSUtils::ParseJsInteger(vm, valueArg, value)) {
        GetArkUINodeModifiers()->getNavigationModifier()->resetTitleMode(nativeNode);
    } else {
        GetArkUINodeModifiers()->getNavigationModifier()->setTitleMode(nativeNode, value);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::ResetTitleMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getNavigationModifier()->resetTitleMode(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::SetHideBackButton(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> hideArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    if (hideArg->IsBoolean()) {
        bool hide = hideArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getNavigationModifier()->setHideBackButton(nativeNode, hide);
    } else {
        GetArkUINodeModifiers()->getNavigationModifier()->resetHideBackButton(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::ResetHideBackButton(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getNavigationModifier()->resetHideBackButton(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::SetSubtitle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> subtitleArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    if (subtitleArg->IsString(vm)) {
        std::string subtitle = subtitleArg->ToString(vm)->ToString(vm);
        GetArkUINodeModifiers()->getNavigationModifier()->setSubtitle(nativeNode, subtitle.c_str());
    } else {
        GetArkUINodeModifiers()->getNavigationModifier()->resetSubtitle(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::ResetSubtitle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getNavigationModifier()->resetSubtitle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::SetHideNavBar(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> hideArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    if (hideArg->IsBoolean()) {
        bool hide = hideArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getNavigationModifier()->setHideNavBar(nativeNode, hide);
    } else {
        GetArkUINodeModifiers()->getNavigationModifier()->resetHideNavBar(nativeNode);
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::ResetHideNavBar(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getNavigationModifier()->resetHideNavBar(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::SetUsrNavigationMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    if (valueArg->IsUndefined() || !valueArg->IsNumber()) {
        GetArkUINodeModifiers()->getNavigationModifier()->resetUsrNavigationMode(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    uint32_t value = valueArg->Uint32Value(vm);
    GetArkUINodeModifiers()->getNavigationModifier()->setUsrNavigationMode(nativeNode, value);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::ResetUsrNavigationMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getNavigationModifier()->resetUsrNavigationMode(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::SetHideTitleBar(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> hideArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    if (hideArg->IsBoolean()) {
        bool hide = hideArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getNavigationModifier()->setNavHideTitleBar(nativeNode, hide);
    } else {
        GetArkUINodeModifiers()->getNavigationModifier()->resetNavHideTitleBar(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::ResetHideTitleBar(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getNavigationModifier()->resetNavHideTitleBar(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::SetNavBarPosition(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    if (valueArg->IsUndefined() || !valueArg->IsNumber()) {
        GetArkUINodeModifiers()->getNavigationModifier()->resetNavBarPosition(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    int32_t value = valueArg->Int32Value(vm);
    GetArkUINodeModifiers()->getNavigationModifier()->setNavBarPosition(nativeNode, value);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::ResetNavBarPosition(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getNavigationModifier()->resetNavBarPosition(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::SetNavBarWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> jsValue = runtimeCallInfo->GetCallArgRef(1);

    CalcDimension width;
    if (jsValue->IsNull() || jsValue->IsUndefined() || !ArkTSUtils::ParseJsDimensionVpNG(vm, jsValue, width)) {
        GetArkUINodeModifiers()->getNavigationModifier()->resetNavBarWidth(nativeNode);
    } else {
        GetArkUINodeModifiers()->getNavigationModifier()->setNavBarWidth(
            nativeNode, width.Value(), static_cast<int>(width.Unit()));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::ResetNavBarWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getNavigationModifier()->resetNavBarWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::SetNavBarWidthRange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> jsValue = runtimeCallInfo->GetCallArgRef(1);
    if (jsValue->IsNull() || jsValue->IsUndefined() || !jsValue->IsArray(vm)) {
        GetArkUINodeModifiers()->getNavigationModifier()->resetMinNavBarWidth(nativeNode);
        GetArkUINodeModifiers()->getNavigationModifier()->resetMaxNavBarWidth(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto rangeArray = panda::Local<panda::ArrayRef>(jsValue);
    auto minNavBarWidth = panda::ArrayRef::GetValueAt(vm, rangeArray, 0);
    CalcDimension minWidth;
    if (minNavBarWidth->IsNull() || minNavBarWidth->IsUndefined() ||
        !ArkTSUtils::ParseJsDimensionVp(vm, minNavBarWidth, minWidth)) {
        GetArkUINodeModifiers()->getNavigationModifier()->resetMinNavBarWidth(nativeNode);
    } else {
        GetArkUINodeModifiers()->getNavigationModifier()->setMinNavBarWidth(
            nativeNode, minWidth.Value(), static_cast<int>(minWidth.Unit()));
    }
    auto maxNavBarWidth = panda::ArrayRef::GetValueAt(vm, rangeArray, 1);
    CalcDimension maxWidth;
    if (maxNavBarWidth->IsNull() || maxNavBarWidth->IsUndefined() ||
        !ArkTSUtils::ParseJsDimensionVp(vm, maxNavBarWidth, maxWidth)) {
        GetArkUINodeModifiers()->getNavigationModifier()->resetMaxNavBarWidth(nativeNode);
    } else {
        GetArkUINodeModifiers()->getNavigationModifier()->setMaxNavBarWidth(
            nativeNode, maxWidth.Value(), static_cast<int>(maxWidth.Unit()));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::ResetNavBarWidthRange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getNavigationModifier()->resetMinNavBarWidth(nativeNode);
    GetArkUINodeModifiers()->getNavigationModifier()->resetMaxNavBarWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::SetMinContentWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> jsValue = runtimeCallInfo->GetCallArgRef(1);

    CalcDimension width;
    if (jsValue->IsNull() || jsValue->IsUndefined() || !ArkTSUtils::ParseJsDimensionVpNG(vm, jsValue, width)) {
        GetArkUINodeModifiers()->getNavigationModifier()->resetMinContentWidth(nativeNode);
    } else {
        GetArkUINodeModifiers()->getNavigationModifier()->setMinContentWidth(
            nativeNode, width.Value(), static_cast<int>(width.Unit()));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::ResetMinContentWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getNavigationModifier()->resetMinContentWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::SetBackButtonIcon(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);

    Framework::JsiCallbackInfo info = Framework::JsiCallbackInfo(runtimeCallInfo);
    std::string src;
    auto noPixMap = Framework::JSViewAbstract::ParseJsMedia(info[1], src);
    auto isValidImage = false;
    RefPtr<PixelMap> pixMap = nullptr;
#if defined(PIXEL_MAP_SUPPORTED)
    if (!noPixMap) {
        pixMap = CreatePixelMapFromNapiValue(info[1]);
    }
#endif
    if (noPixMap || pixMap != nullptr) {
        isValidImage = true;
    }
    std::string bundleName;
    std::string moduleName;
    Framework::JSViewAbstract::GetJsMediaBundleInfo(info[1], bundleName, moduleName);
    NG::ImageOption imageOption;
    std::function<void(WeakPtr<NG::FrameNode>)> iconSymbol = nullptr;
    auto isSymbol = info[1]->IsObject() && src.empty() && pixMap == nullptr;
    if (isSymbol) {
        Framework::JSViewAbstract::SetSymbolOptionApply(info, iconSymbol, info[1]);
    }
    imageOption.noPixMap = noPixMap;
    imageOption.isValidImage = isValidImage;
    NavigationModelNG::SetBackButtonIcon(frameNode, iconSymbol, src, imageOption, pixMap);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::ResetBackButtonIcon(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    bool noPixMap = false;
    NG::ImageOption imageOption;
    imageOption.noPixMap = noPixMap;
    imageOption.isValidImage = false;
    RefPtr<PixelMap> pixMap = nullptr;
    std::function<void(WeakPtr<NG::FrameNode>)> iconSymbol = nullptr;
    std::string src;
    NavigationModelNG::SetBackButtonIcon(frameNode, iconSymbol, src, imageOption, pixMap);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::SetIgnoreLayoutSafeArea(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    std::string typeCppStr;
    std::string edgesCppStr;
    if (secondArg->IsString(vm)) {
        typeCppStr = secondArg->ToString(vm)->ToString(vm);
    } else {
        //type system
        typeCppStr = "0";
    }

    if (thirdArg->IsString(vm)) {
        edgesCppStr = thirdArg->ToString(vm)->ToString(vm);
    } else {
        //edge top and bottom
        edgesCppStr = "0|1";
    }
    const char* typeStr = typeCppStr.c_str();
    const char* edgesStr = edgesCppStr.c_str();
    GetArkUINodeModifiers()->getNavigationModifier()->setNavIgnoreLayoutSafeArea(nativeNode, typeStr, edgesStr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::ResetIgnoreLayoutSafeArea(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getNavigationModifier()->resetNavIgnoreLayoutSafeArea(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::SetTitle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> titleArg = runtimeCallInfo->GetCallArgRef(1);
    Local<JSValueRef> optionsArg = runtimeCallInfo->GetCallArgRef(2);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    std::string title;
    std::string subtitle;
    bool hasMain = false;
    bool hasSub = false;
    if (ArkTSUtils::ParseJsString(vm, titleArg, title)) {
        // Resource and string type.
        subtitle = "";
        hasMain = true;
        hasSub = false;
    } else if (titleArg->IsObject(vm)) {
        // NavigationCommonTitle
        auto obj = titleArg->ToObject(vm);
        auto main = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "main"));
        auto sub = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "sub"));
        hasMain = ArkTSUtils::ParseJsString(vm, main, title);
        hasSub = ArkTSUtils::ParseJsString(vm, sub, subtitle);
        // NavigationCustomTitle or CustomBuilder is not supported
    } else {
        GetArkUINodeModifiers()->getNavigationModifier()->resetNavTitle(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    ArkUINavigationTitlebarOptions options;
    if (optionsArg->IsObject(vm)) {
        NativeNavigationUtils::ParseTitleOptions(vm, optionsArg, options);
    }
    ArkUINavigationTitleInfo titleInfo = { hasSub, hasMain, subtitle.c_str(), title.c_str() };
    GetArkUINodeModifiers()->getNavigationModifier()->setNavTitle(nativeNode, titleInfo, options);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::ResetTitle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getNavigationModifier()->resetNavTitle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::SetMenus(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> menusArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    std::vector<ArkUIBarItem> menuItems;
    if (menusArg->IsArray(vm)) {
        NativeNavigationUtils::ParseBarItems(vm, menusArg, menuItems);
        GetArkUINodeModifiers()->getNavigationModifier()->setNavMenus(nativeNode, menuItems.data(), menuItems.size());
        // get action and symbolModifier single
        auto actionSendFunc = GetArkUINodeModifiers()->getNavigationModifier()->setNavMenuItemAction;
        auto symbolSendFunc = GetArkUINodeModifiers()->getNavigationModifier()->setNavMenuItemSymbol;
        NativeNavigationUtils::ParseAndSendFunctionParam(runtimeCallInfo, menusArg, actionSendFunc, symbolSendFunc);
    } else if (menusArg->IsUndefined()) {
        menuItems = {};
        GetArkUINodeModifiers()->getNavigationModifier()->setNavMenus(nativeNode, menuItems.data(), menuItems.size());
    } else if (menusArg->IsObject(vm)) {
        GetArkUINodeModifiers()->getNavigationModifier()->resetNavMenus(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::ResetMenus(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getNavigationModifier()->resetNavMenus(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::SetRecoverable(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> recoverableArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    if (recoverableArg->IsNull() || recoverableArg->IsUndefined() || !recoverableArg->IsBoolean()) {
        GetArkUINodeModifiers()->getNavigationModifier()->resetRecoverable(nativeNode);
    } else {
        bool recoverable = recoverableArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getNavigationModifier()->setRecoverable(nativeNode, recoverable);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::ResetRecoverable(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getNavigationModifier()->resetRecoverable(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
