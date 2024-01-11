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

#include "core/interfaces/native/node/api.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "core/components_ng/pattern/navigation/navigation_declaration.h"
#include "core/components_ng/pattern/navigation/navigation_model_ng.h"
#include "frameworks/bridge/declarative_frontend/engine/js_types.h"
namespace OHOS::Ace::NG {} // namespace OHOS::Ace::NG
namespace OHOS::Ace::NG {
ArkUINativeModuleValue NavigationBridge::SetHideToolBar(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> hideArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    if (hideArg->IsNull() || hideArg->IsUndefined() || !hideArg->IsBoolean()) {
        GetArkUIInternalNodeAPI()->GetNavigationModifier().ResetHideToolBar(nativeNode);
    } else {
        bool hide = hideArg->ToBoolean(vm)->Value();
        GetArkUIInternalNodeAPI()->GetNavigationModifier().SetHideToolBar(nativeNode, hide);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::ResetHideToolBar(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetNavigationModifier().ResetHideToolBar(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::SetTitleMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    int32_t value;
    if (valueArg->IsNull() || valueArg->IsUndefined() || !ArkTSUtils::ParseJsInteger(vm, valueArg, value)) {
        GetArkUIInternalNodeAPI()->GetNavigationModifier().ResetTitleMode(nativeNode);
    } else {
        GetArkUIInternalNodeAPI()->GetNavigationModifier().SetTitleMode(nativeNode, value);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::ResetTitleMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetNavigationModifier().ResetTitleMode(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::SetHideBackButton(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> hideArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    if (hideArg->IsBoolean()) {
        bool hide = hideArg->ToBoolean(vm)->Value();
        GetArkUIInternalNodeAPI()->GetNavigationModifier().SetHideBackButton(nativeNode, hide);
    } else {
        GetArkUIInternalNodeAPI()->GetNavigationModifier().ResetHideBackButton(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::ResetHideBackButton(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetNavigationModifier().ResetHideBackButton(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::SetSubtitle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> subtitleArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    if (subtitleArg->IsString()) {
        std::string subtitle = subtitleArg->ToString(vm)->ToString();
        GetArkUIInternalNodeAPI()->GetNavigationModifier().SetSubtitle(nativeNode, subtitle.c_str());
    } else {
        GetArkUIInternalNodeAPI()->GetNavigationModifier().ResetSubtitle(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::ResetSubtitle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetNavigationModifier().ResetSubtitle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::SetHideNavBar(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> hideArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    if (hideArg->IsBoolean()) {
        bool hide = hideArg->ToBoolean(vm)->Value();
        GetArkUIInternalNodeAPI()->GetNavigationModifier().SetHideNavBar(nativeNode, hide);
    } else {
        GetArkUIInternalNodeAPI()->GetNavigationModifier().ResetHideNavBar(nativeNode);
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::ResetHideNavBar(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetNavigationModifier().ResetHideNavBar(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::SetUsrNavigationMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    if (valueArg->IsUndefined() || !valueArg->IsNumber()) {
        GetArkUIInternalNodeAPI()->GetNavigationModifier().ResetUsrNavigationMode(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    uint32_t value = valueArg->Uint32Value(vm);
    GetArkUIInternalNodeAPI()->GetNavigationModifier().SetUsrNavigationMode(nativeNode, value);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::ResetUsrNavigationMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetNavigationModifier().ResetUsrNavigationMode(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::SetHideTitleBar(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> hideArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    if (hideArg->IsBoolean()) {
        bool hide = hideArg->ToBoolean(vm)->Value();
        GetArkUIInternalNodeAPI()->GetNavigationModifier().SetNavHideTitleBar(nativeNode, hide);
    } else {
        GetArkUIInternalNodeAPI()->GetNavigationModifier().ResetNavHideTitleBar(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::ResetHideTitleBar(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetNavigationModifier().ResetNavHideTitleBar(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::SetNavBarPosition(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    if (valueArg->IsUndefined() || !valueArg->IsNumber()) {
        GetArkUIInternalNodeAPI()->GetNavigationModifier().ResetNavBarPosition(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    int32_t value = valueArg->Int32Value(vm);
    GetArkUIInternalNodeAPI()->GetNavigationModifier().SetNavBarPosition(nativeNode, value);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::ResetNavBarPosition(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetNavigationModifier().ResetNavBarPosition(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::SetNavBarWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    Local<JSValueRef> jsValue = runtimeCallInfo->GetCallArgRef(1);

    CalcDimension width;
    if (jsValue->IsNull() || jsValue->IsUndefined() || !ArkTSUtils::ParseJsDimensionVpNG(vm, jsValue, width)) {
        GetArkUIInternalNodeAPI()->GetNavigationModifier().ResetNavBarWidth(nativeNode);
    } else {
        GetArkUIInternalNodeAPI()->GetNavigationModifier().SetNavBarWidth(
            nativeNode, width.Value(), static_cast<int>(width.Unit()));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::ResetNavBarWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetNavigationModifier().ResetNavBarWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::SetNavBarWidthRange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    Local<JSValueRef> jsValue = runtimeCallInfo->GetCallArgRef(1);
    if (jsValue->IsNull() || jsValue->IsUndefined() || !jsValue->IsArray(vm)) {
        GetArkUIInternalNodeAPI()->GetNavigationModifier().ResetMinNavBarWidth(nativeNode);
        GetArkUIInternalNodeAPI()->GetNavigationModifier().ResetMaxNavBarWidth(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto rangeArray = panda::Local<panda::ArrayRef>(jsValue);
    auto minNavBarWidth = panda::ArrayRef::GetValueAt(vm, rangeArray, 0);
    CalcDimension minWidth;
    if (minNavBarWidth->IsNull() || minNavBarWidth->IsUndefined() ||
        !ArkTSUtils::ParseJsDimensionVp(vm, minNavBarWidth, minWidth)) {
        GetArkUIInternalNodeAPI()->GetNavigationModifier().ResetMinNavBarWidth(nativeNode);
    } else {
        GetArkUIInternalNodeAPI()->GetNavigationModifier().SetMinNavBarWidth(
            nativeNode, minWidth.Value(), static_cast<int>(minWidth.Unit()));
    }
    auto maxNavBarWidth = panda::ArrayRef::GetValueAt(vm, rangeArray, 1);
    CalcDimension maxWidth;
    if (maxNavBarWidth->IsNull() || maxNavBarWidth->IsUndefined() ||
        !ArkTSUtils::ParseJsDimensionVp(vm, maxNavBarWidth, maxWidth)) {
        GetArkUIInternalNodeAPI()->GetNavigationModifier().ResetMaxNavBarWidth(nativeNode);
    } else {
        GetArkUIInternalNodeAPI()->GetNavigationModifier().SetMaxNavBarWidth(
            nativeNode, maxWidth.Value(), static_cast<int>(maxWidth.Unit()));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::ResetNavBarWidthRange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetNavigationModifier().ResetMinNavBarWidth(nativeNode);
    GetArkUIInternalNodeAPI()->GetNavigationModifier().ResetMaxNavBarWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::SetMinContentWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = nodeArg->ToNativePointer(vm)->Value();
    Local<JSValueRef> jsValue = runtimeCallInfo->GetCallArgRef(1);

    CalcDimension width;
    if (jsValue->IsNull() || jsValue->IsUndefined() || !ArkTSUtils::ParseJsDimensionVpNG(vm, jsValue, width)) {
        GetArkUIInternalNodeAPI()->GetNavigationModifier().ResetMinContentWidth(nativeNode);
    } else {
        GetArkUIInternalNodeAPI()->GetNavigationModifier().SetMinContentWidth(
            nativeNode, width.Value(), static_cast<int>(width.Unit()));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::ResetMinContentWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetNavigationModifier().ResetMinContentWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::SetBackButtonIcon(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
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

    NavigationModelNG::SetBackButtonIcon(frameNode, src, noPixMap, pixMap);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::ResetBackButtonIcon(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    bool noPixMap = false;
    RefPtr<PixelMap> pixMap = nullptr;
    std::string src;
    NavigationModelNG::SetBackButtonIcon(frameNode, src, noPixMap, pixMap);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
