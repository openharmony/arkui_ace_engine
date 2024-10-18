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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_nav_destination_bridge.h"

#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_navigation_utils.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "core/components_ng/pattern/navrouter/navdestination_model_ng.h"
namespace OHOS::Ace::NG {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;

ArkUINativeModuleValue NavDestinationBridge::SetHideTitleBar(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> hideArg = runtimeCallInfo->GetCallArgRef(1);
    const int32_t argsNum = 2; // 2: parameter index
    Local<JSValueRef> animatedArg = runtimeCallInfo->GetCallArgRef(argsNum);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    bool hide = false;
    bool animated = false;
    if (!hideArg->IsNull() && !hideArg->IsUndefined() && hideArg->IsBoolean()) {
        hide = hideArg->ToBoolean(vm)->Value();
    }
    if (!animatedArg->IsNull() && !animatedArg->IsUndefined() && animatedArg->IsBoolean()) {
        animated = animatedArg->ToBoolean(vm)->Value();
    }
    GetArkUINodeModifiers()->getNavDestinationModifier()->setHideTitleBar(nativeNode, hide, animated);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavDestinationBridge::ResetHideTitleBar(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getNavDestinationModifier()->resetHideTitleBar(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavDestinationBridge::SetHideToolBar(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> hideArg = runtimeCallInfo->GetCallArgRef(1);
    const int32_t argsNum = 2; // 2: parameter index
    Local<JSValueRef> animatedArg = runtimeCallInfo->GetCallArgRef(argsNum);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    bool hide = false;
    bool animated = false;
    if (!hideArg->IsNull() && !hideArg->IsUndefined() && hideArg->IsBoolean()) {
        hide = hideArg->ToBoolean(vm)->Value();
    }
    if (!animatedArg->IsNull() && !animatedArg->IsUndefined() && animatedArg->IsBoolean()) {
        animated = animatedArg->ToBoolean(vm)->Value();
    }
    GetArkUINodeModifiers()->getNavDestinationModifier()->setNavDestinationHideToolBar(nativeNode, hide, animated);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavDestinationBridge::ResetHideToolBar(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getNavDestinationModifier()->resetNavDestinationHideToolBar(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavDestinationBridge::SetBackButtonIcon(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);

    Framework::JsiCallbackInfo info = Framework::JsiCallbackInfo(runtimeCallInfo);
    std::string src;
    auto noPixMap = Framework::JSViewAbstract::ParseJsMedia(info[1], src);

    RefPtr<PixelMap> pixMap = nullptr;
#if defined(PIXEL_MAP_SUPPORTED)
    if (!noPixMap) {
        pixMap = CreatePixelMapFromNapiValue(info[1]);
    }
#endif
    std::string bundleName;
    std::string moduleName;
    
    Framework::JSViewAbstract::GetJsMediaBundleInfo(info[1], bundleName, moduleName);
    NavDestinationModelNG::SetBackButtonIcon(frameNode, src, noPixMap, pixMap);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavDestinationBridge::ResetBackButtonIcon(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    bool noPixMap = false;
    RefPtr<PixelMap> pixMap = nullptr;
    std::string src;
    NavDestinationModelNG::SetBackButtonIcon(frameNode, src, noPixMap, pixMap);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavDestinationBridge::SetNavDestinationMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);

    Framework::JsiCallbackInfo info = Framework::JsiCallbackInfo(runtimeCallInfo);
    if (!info[1]->IsNumber()) {
        // set default back ground color
        GetArkUINodeModifiers()->getNavDestinationModifier()->resetNavDestinationMode(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto mode = info[1]->ToNumber<int32_t>();
    NavDestinationModelNG::SetNavDestinationMode(frameNode, static_cast<NG::NavDestinationMode>(mode));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavDestinationBridge::ResetNavDestinationMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getNavDestinationModifier()->resetNavDestinationMode(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavDestinationBridge::SetIgnoreLayoutSafeArea(ArkUIRuntimeCallInfo *runtimeCallInfo)
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
    GetArkUINodeModifiers()->getNavDestinationModifier()->setIgnoreLayoutSafeArea(nativeNode, typeStr, edgesStr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavDestinationBridge::ResetIgnoreLayoutSafeArea(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getNavDestinationModifier()->resetIgnoreLayoutSafeArea(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavDestinationBridge::SetTitle(ArkUIRuntimeCallInfo* runtimeCallInfo)
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
        GetArkUINodeModifiers()->getNavDestinationModifier()->resetTitle(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    ArkUINavigationTitlebarOptions options;
    if (optionsArg->IsObject(vm)) {
        NativeNavigationUtils::ParseTitleOptions(vm, optionsArg, options);
    }
    ArkUINavigationTitleInfo titleInfo = { hasSub, hasMain, subtitle.c_str(), title.c_str() };
    GetArkUINodeModifiers()->getNavDestinationModifier()->setTitle(nativeNode, titleInfo, options);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavDestinationBridge::ResetTitle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getNavDestinationModifier()->resetTitle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavDestinationBridge::SetMenus(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> menusArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    std::vector<ArkUIBarItem> menuItems;
    if (menusArg->IsArray(vm)) {
        NativeNavigationUtils::ParseBarItems(vm, menusArg, menuItems);
        GetArkUINodeModifiers()->getNavDestinationModifier()->setMenus(nativeNode, menuItems.data(), menuItems.size());
        // get action and symbolModifier single
        auto actionSendFunc = GetArkUINodeModifiers()->getNavDestinationModifier()->setMenuItemAction;
        auto symbolSendFunc = GetArkUINodeModifiers()->getNavDestinationModifier()->setMenuItemSymbol;
        NativeNavigationUtils::ParseAndSendFunctionParam(runtimeCallInfo, menusArg, actionSendFunc, symbolSendFunc);
    } else if (menusArg->IsUndefined()) {
        menuItems = {};
        GetArkUINodeModifiers()->getNavDestinationModifier()->setMenus(nativeNode, menuItems.data(), menuItems.size());
    } else if (menusArg->IsObject(vm)) {
        GetArkUINodeModifiers()->getNavDestinationModifier()->resetMenus(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavDestinationBridge::ResetMenus(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getNavDestinationModifier()->resetHideTitleBar(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavDestinationBridge::SetRecoverable(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> recoverableArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    if (recoverableArg->IsNull() || recoverableArg->IsUndefined() || !recoverableArg->IsBoolean()) {
        GetArkUINodeModifiers()->getNavDestinationModifier()->resetRecoverable(nativeNode);
    } else {
        bool recoverable = recoverableArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getNavDestinationModifier()->setRecoverable(nativeNode, recoverable);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavDestinationBridge::ResetRecoverable(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getNavDestinationModifier()->resetRecoverable(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
