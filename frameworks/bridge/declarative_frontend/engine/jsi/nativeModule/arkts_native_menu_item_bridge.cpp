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

#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_api.h"
#include "core/components_ng/pattern/menu/menu_item/menu_item_model_ng.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"

using namespace OHOS::Ace::Framework;

namespace OHOS::Ace::NG {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int NUM_4 = 4;
const std::string FORMAT_FONT = "%s|%s|%s";
const std::string DEFAULT_ERR_CODE = "-1";
ArkUINativeModuleValue MenuItemBridge::SetMenuItemSelected(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    if (secondArg->IsBoolean()) {
        bool selected = secondArg->ToBoolean(vm)->Value();
        GetArkUIInternalNodeAPI()->GetMenuItemModifier().SetMenuItemSelected(nativeNode, selected);
    } else {
        GetArkUIInternalNodeAPI()->GetMenuItemModifier().ResetMenuItemSelected(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MenuItemBridge::ResetMenuItemSelected(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetMenuItemModifier().ResetMenuItemSelected(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MenuItemBridge::SetLabelFontColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    Color color;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color)) {
        GetArkUIInternalNodeAPI()->GetMenuItemModifier().ResetLabelFontColor(nativeNode);
    } else {
        GetArkUIInternalNodeAPI()->GetMenuItemModifier().SetLabelFontColor(nativeNode, color.GetValue());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MenuItemBridge::ResetLabelFontColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetMenuItemModifier().ResetLabelFontColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MenuItemBridge::SetContentFontColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    Color color;
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color)) {
        GetArkUIInternalNodeAPI()->GetMenuItemModifier().ResetContentFontColor(nativeNode);
    } else {
        GetArkUIInternalNodeAPI()->GetMenuItemModifier().SetContentFontColor(nativeNode, color.GetValue());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MenuItemBridge::ResetContentFontColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetMenuItemModifier().ResetContentFontColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MenuItemBridge::SetLabelFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> sizeArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> weightArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> familyArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> styleArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    if (sizeArg->IsUndefined() && weightArg->IsUndefined() && familyArg->IsUndefined() && styleArg->IsUndefined()) {
        GetArkUIInternalNodeAPI()->GetMenuItemModifier().ResetLabelFont(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    CalcDimension fontSize;
    if (!ArkTSUtils::ParseJsDimensionFp(vm, sizeArg, fontSize, false)) {
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
    if (!ArkTSUtils::ParseJsFontFamiliesToString(vm, familyArg, family) || family.empty()) {
        family = DEFAULT_ERR_CODE;
    }
    
    std::string fontSizeStr = fontSize.ToString();
    std::string fontInfo = StringUtils::FormatString(
        FORMAT_FONT.c_str(), fontSizeStr.c_str(), weight.c_str(), family.c_str());

    GetArkUIInternalNodeAPI()->GetMenuItemModifier().SetLabelFont(nativeNode, fontInfo.c_str(), style);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MenuItemBridge::ResetLabelFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetMenuItemModifier().ResetLabelFont(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MenuItemBridge::SetContentFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> sizeArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> weightArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> familyArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> styleArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    if (sizeArg->IsUndefined() && weightArg->IsUndefined() && familyArg->IsUndefined() && styleArg->IsUndefined()) {
        GetArkUIInternalNodeAPI()->GetMenuItemModifier().ResetContentFont(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    CalcDimension fontSize;
    if (!ArkTSUtils::ParseJsDimensionFp(vm, sizeArg, fontSize, false)) {
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
    if (!ArkTSUtils::ParseJsFontFamiliesToString(vm, familyArg, family) || family.empty()) {
        family = DEFAULT_ERR_CODE;
    }

    std::string fontSizeStr = fontSize.ToString();
    std::string fontInfo = StringUtils::FormatString(
        FORMAT_FONT.c_str(), fontSizeStr.c_str(), weight.c_str(), family.c_str());
    GetArkUIInternalNodeAPI()->GetMenuItemModifier().SetContentFont(nativeNode, fontInfo.c_str(), style);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue MenuItemBridge::ResetContentFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetMenuItemModifier().ResetContentFont(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
}