/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_grid_row_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/jsi_types.h"
#include "core/components/common/layout/constants.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"

namespace OHOS::Ace::NG {
constexpr int32_t MAX_NUMBER_BREAKPOINT = 6;
constexpr int XS = 0;
constexpr int SM = 1;
constexpr int MD = 2;
constexpr int LG = 3;
constexpr int XL = 4;
constexpr int XXL = 5;
constexpr int32_t MAX_NUMBER_GUTTER = 12;
constexpr int X_XS = 0;
constexpr int X_SM = 1;
constexpr int X_MD = 2;
constexpr int X_LG = 3;
constexpr int X_XL = 4;
constexpr int X_XXL = 5;
constexpr int Y_XS = 6;
constexpr int Y_SM = 7;
constexpr int Y_MD = 8;
constexpr int Y_LG = 9;
constexpr int Y_XL = 10;
constexpr int Y_XXL = 11;

ArkUINativeModuleValue GridRowBridge::SetAlignItems(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsNumber()) {
        int32_t alignItem = secondArg->Int32Value(vm);
        if (alignItem == static_cast<int32_t>(OHOS::Ace::FlexAlign::FLEX_START) ||
            alignItem == static_cast<int32_t>(OHOS::Ace::FlexAlign::FLEX_END) ||
            alignItem == static_cast<int32_t>(OHOS::Ace::FlexAlign::CENTER) ||
            alignItem == static_cast<int32_t>(OHOS::Ace::FlexAlign::STRETCH)) {
            GetArkUINodeModifiers()->getGridRowModifier()->setAlignItems(nativeNode, alignItem);
        } else if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
            GetArkUINodeModifiers()->getGridRowModifier()->setAlignItems(nativeNode,
                static_cast<int32_t>(OHOS::Ace::FlexAlign::FLEX_START));
        }
    } else {
        GetArkUINodeModifiers()->getGridRowModifier()->resetAlignItems(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridRowBridge::ResetAlignItems(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getGridRowModifier()->resetAlignItems(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridRowBridge::SetDirection(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    if (secondArg->IsNumber()) {
        GetArkUINodeModifiers()->getGridRowModifier()->setDirection(nativeNode, secondArg->Int32Value(vm));
    } else {
        GetArkUINodeModifiers()->getGridRowModifier()->resetDirection(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue GridRowBridge::ResetDirection(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getGridRowModifier()->resetDirection(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridRowBridge::SetBreakpoints(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    Local<JSValueRef> threeArg = runtimeCallInfo->GetCallArgRef(2);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    int32_t reference = 0;
    if (threeArg->IsNumber()) {
        reference = threeArg->Int32Value(vm);
    }

    std::vector<ArkUI_Float32> pointValues;
    std::vector<const char*> pointStr;
    int32_t size = 0;
    if (!secondArg->IsArray(vm)) {
        GetArkUINodeModifiers()->getGridRowModifier()->setBreakpoints(
            nativeNode, reference, pointValues.data(), pointStr.data(), size);
        return panda::JSValueRef::Undefined(vm);
    }
    auto arrayVal = panda::Local<panda::ArrayRef>(secondArg);
    auto length = arrayVal->Length(vm);
    if (length <= 0 || length > (MAX_NUMBER_BREAKPOINT-1)) {
        GetArkUINodeModifiers()->getGridRowModifier()->setBreakpoints(
            nativeNode, reference, pointValues.data(), pointStr.data(), size);
        return panda::JSValueRef::Undefined(vm);
    }
    for (uint32_t index = 0; index < length; index++) {
        CalcDimension calvalue;
        std::string calcStr;
        auto item = panda::ArrayRef::GetValueAt(vm, arrayVal, index);
        calcStr = item->ToString(vm)->ToString();
        if (!ArkTSUtils::ParseJsDimensionVp(vm, item, calvalue, false)) {
            calvalue = CalcDimension(0, DimensionUnit::VP);
        }
        pointValues.push_back(calvalue.Value());
        pointStr.push_back(calcStr.c_str());
        size++;
    }
    GetArkUINodeModifiers()->getGridRowModifier()->setBreakpoints(nativeNode, reference, pointValues.data(),
        pointStr.data(), size);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue GridRowBridge::ResetBreakpoints(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getGridRowModifier()->resetBreakpoints(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridRowBridge::SetColumns(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> xs = runtimeCallInfo->GetCallArgRef(XS + 1);
    Local<JSValueRef> sm = runtimeCallInfo->GetCallArgRef(SM + 1);
    Local<JSValueRef> md = runtimeCallInfo->GetCallArgRef(MD + 1);
    Local<JSValueRef> lg = runtimeCallInfo->GetCallArgRef(LG + 1);
    Local<JSValueRef> xl = runtimeCallInfo->GetCallArgRef(XL + 1);
    Local<JSValueRef> xxl = runtimeCallInfo->GetCallArgRef(XXL + 1);
    int32_t containerSizeArray[MAX_NUMBER_BREAKPOINT];
    if (xs->IsNumber() && xs->Int32Value(vm) >= 0) {
        containerSizeArray[XS] = xs->Int32Value(vm);
    } else {
        containerSizeArray[XS] = -1;
    }
    if (sm->IsNumber() && sm->Int32Value(vm) >= 0) {
        containerSizeArray[SM] = sm->Int32Value(vm);
    } else {
        containerSizeArray[SM] = -1;
    }
    if (md->IsNumber() && md->Int32Value(vm) >= 0) {
        containerSizeArray[MD] = md->Int32Value(vm);
    } else {
        containerSizeArray[MD] = -1;
    }
    if (lg->IsNumber() && lg->Int32Value(vm) >= 0) {
        containerSizeArray[LG] = lg->Int32Value(vm);
    } else {
        containerSizeArray[LG] = -1;
    }
    if (xl->IsNumber() && xl->Int32Value(vm) >= 0) {
        containerSizeArray[XL] = xl->Int32Value(vm);
    } else {
        containerSizeArray[XL] = -1;
    }
    if (xxl->IsNumber() && xxl->Int32Value(vm) >= 0) {
        containerSizeArray[XXL] = xxl->Int32Value(vm);
    } else {
        containerSizeArray[XXL] = -1;
    }
    GetArkUINodeModifiers()->getGridRowModifier()->setColumns(nativeNode, containerSizeArray, MAX_NUMBER_BREAKPOINT);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue GridRowBridge::ResetColumns(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getGridRowModifier()->resetColumns(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridRowBridge::SetGutter(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> xXs = runtimeCallInfo->GetCallArgRef(X_XS + 1);
    Local<JSValueRef> xSm = runtimeCallInfo->GetCallArgRef(X_SM + 1);
    Local<JSValueRef> xMd = runtimeCallInfo->GetCallArgRef(X_MD + 1);
    Local<JSValueRef> xLg = runtimeCallInfo->GetCallArgRef(X_LG + 1);
    Local<JSValueRef> xXl = runtimeCallInfo->GetCallArgRef(X_XL + 1);
    Local<JSValueRef> xXxl = runtimeCallInfo->GetCallArgRef(X_XXL + 1);
    Local<JSValueRef> yXs = runtimeCallInfo->GetCallArgRef(Y_XS + 1);
    Local<JSValueRef> ySm = runtimeCallInfo->GetCallArgRef(Y_SM + 1);
    Local<JSValueRef> yMd = runtimeCallInfo->GetCallArgRef(Y_MD + 1);
    Local<JSValueRef> yLg = runtimeCallInfo->GetCallArgRef(Y_LG + 1);
    Local<JSValueRef> yXl = runtimeCallInfo->GetCallArgRef(Y_XL + 1);
    Local<JSValueRef> yXxl = runtimeCallInfo->GetCallArgRef(Y_XXL + 1);
    int32_t containerSizeArray[MAX_NUMBER_GUTTER];
    if (xXs->IsNumber() && xXs->Int32Value(vm) >= 0) {
        containerSizeArray[X_XS] = xXs->Int32Value(vm);
    } else {
        containerSizeArray[X_XS] = -1;
    }
    if (xSm->IsNumber() && xSm->Int32Value(vm) >= 0) {
        containerSizeArray[X_SM] = xSm->Int32Value(vm);
    } else {
        containerSizeArray[X_SM] = -1;
    }
    if (xMd->IsNumber() && xMd->Int32Value(vm) >= 0) {
        containerSizeArray[X_MD] = xMd->Int32Value(vm);
    } else {
        containerSizeArray[X_MD] = -1;
    }
    if (xLg->IsNumber() && xLg->Int32Value(vm) >= 0) {
        containerSizeArray[X_LG] = xLg->Int32Value(vm);
    } else {
        containerSizeArray[X_LG] = -1;
    }
    if (xXl->IsNumber() && xXl->Int32Value(vm) >= 0) {
        containerSizeArray[X_XL] = xXl->Int32Value(vm);
    } else {
        containerSizeArray[X_XL] = -1;
    }
    if (xXxl->IsNumber() && xXxl->Int32Value(vm) >= 0) {
        containerSizeArray[X_XXL] = xXxl->Int32Value(vm);
    } else {
        containerSizeArray[X_XXL] = -1;
    }

    if (yXs->IsNumber() && yXs->Int32Value(vm) >= 0) {
        containerSizeArray[Y_XS] = yXs->Int32Value(vm);
    } else {
        containerSizeArray[Y_XS] = -1;
    }
    if (ySm->IsNumber() && ySm->Int32Value(vm) >= 0) {
        containerSizeArray[Y_SM] = ySm->Int32Value(vm);
    } else {
        containerSizeArray[Y_SM] = -1;
    }
    if (yMd->IsNumber() && yMd->Int32Value(vm) >= 0) {
        containerSizeArray[Y_MD] = yMd->Int32Value(vm);
    } else {
        containerSizeArray[Y_MD] = -1;
    }
    if (yLg->IsNumber() && yLg->Int32Value(vm) >= 0) {
        containerSizeArray[Y_LG] = yLg->Int32Value(vm);
    } else {
        containerSizeArray[Y_LG] = -1;
    }
    if (yXl->IsNumber() && yXl->Int32Value(vm) >= 0) {
        containerSizeArray[Y_XL] = yXl->Int32Value(vm);
    } else {
        containerSizeArray[Y_XL] = -1;
    }
    if (yXxl->IsNumber() && yXxl->Int32Value(vm) >= 0) {
        containerSizeArray[Y_XXL] = yXxl->Int32Value(vm);
    } else {
        containerSizeArray[Y_XXL] = -1;
    }
    GetArkUINodeModifiers()->getGridRowModifier()->setGutter(nativeNode, containerSizeArray, MAX_NUMBER_GUTTER);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue GridRowBridge::ResetGutter(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getGridRowModifier()->resetGutter(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
}

