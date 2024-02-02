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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_grid_col_bridge.h"

namespace OHOS::Ace::NG {
constexpr int32_t MAX_NUMBER_BREAKPOINT = 6;
constexpr int XS = 0;
constexpr int SM = 1;
constexpr int MD = 2;
constexpr int LG = 3;
constexpr int XL = 4;
constexpr int XXL = 5;
int32_t defaultVal = 0;

ArkUINativeModuleValue GridColBridge::SetGridColOffset(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
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
    GetArkUINodeModifiers()->getGridColModifier()->setGridColOffset(nativeNode, containerSizeArray,
        MAX_NUMBER_BREAKPOINT);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridColBridge::ResetGridColOffset(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getGridColModifier()->resetGridColOffset(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridColBridge::SetSpan(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
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
    GetArkUINodeModifiers()->getGridColModifier()->setSpan(nativeNode, containerSizeArray, MAX_NUMBER_BREAKPOINT);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridColBridge::ResetSpan(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getGridColModifier()->resetSpan(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridColBridge::SetOrder(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
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
    GetArkUINodeModifiers()->getGridColModifier()->setOrder(nativeNode, containerSizeArray, MAX_NUMBER_BREAKPOINT);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue GridColBridge::ResetOrder(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getGridColModifier()->resetOrder(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
}