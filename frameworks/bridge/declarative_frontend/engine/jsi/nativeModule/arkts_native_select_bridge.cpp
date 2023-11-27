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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_select_bridge.h"

#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_select_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/utils/arkts_native_parse.h"
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_api.h"
#include "bridge/declarative_frontend/jsview/js_view_abstract.h"

namespace OHOS::Ace::NG {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int NUM_4 = 4;
const int SIZE_OF_TWO = 2;
const std::string FORMAT_FONT = "%s|%s|%s";
const std::string DEFAULT_STR = "-1";

std::string GetStringFromJS(const EcmaVM *vm, const Local<JSValueRef> &value)
{
    std::string result = DEFAULT_STR;
    if (!value->IsNull() && value->IsString()) {
        result = value->ToString(vm)->ToString();
    }
    return result;
}

ArkUINativeModuleValue SelectBridge::SelectBridge::SetSpace(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();

    if (secondArg->IsNumber() || secondArg->IsString()) {
        CalcDimension space;
        ParseJsDimensionFp(vm, secondArg, space);
        GetArkUIInternalNodeAPI()->GetSelectModifier().SetSpace(
            nativeNode, space.Value(), static_cast<int>(space.Unit()));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SetValue(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    if (secondArg->IsFunction()) {
        return panda::JSValueRef::Undefined(vm);
    }

    std::string value = secondArg->ToString(vm)->ToString();
    GetArkUIInternalNodeAPI()->GetSelectModifier().SetValue(nativeNode, value.c_str());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SetSelected(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    int32_t value = secondArg->Int32Value(vm);
    if (value < -1) {
        value = -1;
    }
    GetArkUIInternalNodeAPI()->GetSelectModifier().SetSelected(nativeNode, value);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SetFontColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    uint32_t colorVal = secondArg->Uint32Value(vm);

    GetArkUIInternalNodeAPI()->GetSelectModifier().SetSelectFontColor(nativeNode, colorVal);

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SetSelectedOptionBgColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    uint32_t colorVal = secondArg->Uint32Value(vm);

    GetArkUIInternalNodeAPI()->GetSelectModifier().SetSelectedOptionBgColor(nativeNode, colorVal);

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SetOptionBgColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    uint32_t colorVal = secondArg->Uint32Value(vm);

    GetArkUIInternalNodeAPI()->GetSelectModifier().SetOptionBgColor(nativeNode, colorVal);

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SetOptionFontColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    uint32_t colorVal = secondArg->Uint32Value(vm);

    GetArkUIInternalNodeAPI()->GetSelectModifier().SetOptionFontColor(nativeNode, colorVal);

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::SetSelectedOptionFontColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    uint32_t colorVal = secondArg->Uint32Value(vm);

    GetArkUIInternalNodeAPI()->GetSelectModifier().SetSelectedOptionFontColor(nativeNode, colorVal);

    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SelectBridge::SelectBridge::SetArrowPosition(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    int32_t arrowPosition = secondArg->Int32Value(vm);

    GetArkUIInternalNodeAPI()->GetSelectModifier().SetArrowPosition(nativeNode, arrowPosition);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SelectBridge::SetMenuAlign(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> offsetDx = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> offsetDy = runtimeCallInfo->GetCallArgRef(NUM_3);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();

    int32_t alignType = 0;
    if (secondArg->IsNumber()) {
        alignType = secondArg->Int32Value(vm);
    }
    CalcDimension menuAlignOffsetDx = Dimension(0.0);
    CalcDimension menuAlignOffsetDy = Dimension(0.0);

    if (offsetDx->IsNull() || !ParseJsDimensionFp(vm, offsetDx, menuAlignOffsetDx)) {
        menuAlignOffsetDx = Dimension(0.0);
    }

    if (offsetDy->IsNull() || !ParseJsDimensionFp(vm, offsetDy, menuAlignOffsetDy)) {
        menuAlignOffsetDx = Dimension(0.0);
    }

    uint32_t size = SIZE_OF_TWO;
    float values[size];
    int units[size];
    values[0] = menuAlignOffsetDx.Value();
    units[0] = static_cast<int>(menuAlignOffsetDx.Unit());
    values[1] = menuAlignOffsetDy.Value();
    units[1] = static_cast<int>(menuAlignOffsetDy.Unit());
    GetArkUIInternalNodeAPI()->GetSelectModifier().SetMenuAlign(nativeNode, alignType, values, units, SIZE_OF_TWO);
    
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SelectBridge::SetFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> fourthArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> fifthArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    
    std::string fontSize = GetStringFromJS(vm, secondArg);
    std::string weight = GetStringFromJS(vm, thirdArg);
    std::string fontFamily = GetStringFromJS(vm, fourthArg);

    int32_t styleVal = 0;
    if (!fifthArg->IsNull()) {
        styleVal = fifthArg->Int32Value(vm);
    }

    std::string fontInfo = StringUtils::FormatString(
        FORMAT_FONT.c_str(), fontSize.c_str(), weight.c_str(), fontFamily.c_str());

    GetArkUIInternalNodeAPI()->GetSelectModifier().SetFont(nativeNode, fontInfo.c_str(), styleVal);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SelectBridge::SetOptionFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> fourthArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> fifthArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();

    std::string fontSize = GetStringFromJS(vm, secondArg);
    std::string weight = GetStringFromJS(vm, thirdArg);
    std::string fontFamily = GetStringFromJS(vm, fourthArg);

    int32_t styleVal = 0;
    if (!fifthArg->IsNull()) {
        styleVal = fifthArg->Int32Value(vm);
    }

    std::string fontInfo = StringUtils::FormatString(
        FORMAT_FONT.c_str(), fontSize.c_str(), weight.c_str(), fontFamily.c_str());
    
    GetArkUIInternalNodeAPI()->GetSelectModifier().SetOptionFont(nativeNode, fontInfo.c_str(), styleVal);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SelectBridge::SetSelectedOptionFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> fourthArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> fifthArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();

    std::string fontSize = GetStringFromJS(vm, secondArg);
    std::string weight = GetStringFromJS(vm, thirdArg);
    std::string fontFamily = GetStringFromJS(vm, fourthArg);
    
    int32_t styleVal = 0;
    if (!fifthArg->IsNull()) {
        styleVal = fifthArg->Int32Value(vm);
    }
    
    std::string fontInfo = StringUtils::FormatString(
        FORMAT_FONT.c_str(), fontSize.c_str(), weight.c_str(), fontFamily.c_str());
 
    GetArkUIInternalNodeAPI()->GetSelectModifier().SetSelectedOptionFont(nativeNode, fontInfo.c_str(), styleVal);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::ResetSpace(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSelectModifier().ResetSpace(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::ResetValue(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSelectModifier().ResetValue(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::ResetSelected(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSelectModifier().ResetSelected(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::ResetFontColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSelectModifier().ResetSelectFontColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::ResetSelectedOptionBgColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSelectModifier().ResetSelectedOptionBgColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::ResetOptionBgColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSelectModifier().ResetOptionBgColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::ResetOptionFontColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSelectModifier().ResetOptionFontColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue SelectBridge::ResetSelectedOptionFontColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSelectModifier().ResetSelectedOptionFontColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SelectBridge::ResetFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSelectModifier().ResetFont(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SelectBridge::ResetOptionFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSelectModifier().ResetOptionFont(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SelectBridge::ResetSelectedOptionFont(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSelectModifier().ResetSelectedOptionFont(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SelectBridge::ResetMenuAlign(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSelectModifier().ResetMenuAlign(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue SelectBridge::ResetArrowPosition(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetSelectModifier().ResetArrowPosition(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG