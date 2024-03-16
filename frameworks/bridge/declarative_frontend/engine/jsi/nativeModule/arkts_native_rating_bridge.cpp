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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_rating_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"

namespace OHOS::Ace::NG {
constexpr double STEPS_DEFAULT = 0.5;
constexpr double STEPS_MIN_SIZE = 0.1;
constexpr int32_t STARS_DEFAULT = 5;
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;

ArkUINativeModuleValue RatingBridge::SetStars(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    int32_t stars = secondArg->Int32Value(vm);
    if (stars <= 0) {
        stars = STARS_DEFAULT;
    }
    GetArkUINodeModifiers()->getRatingModifier()->setStars(nativeNode, stars);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RatingBridge::ResetStars(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getRatingModifier()->resetStars(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue RatingBridge::SetRatingStepSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());

    if (secondArg->IsNull() || !secondArg->IsNumber()) {
        GetArkUINodeModifiers()->getRatingModifier()->resetRatingStepSize(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto steps  = secondArg->ToNumber(vm)->Value();
    if (LessNotEqual(steps, STEPS_MIN_SIZE)) {
        steps = STEPS_DEFAULT;
    }
    GetArkUINodeModifiers()->getRatingModifier()->setRatingStepSize(nativeNode, steps);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RatingBridge::ResetRatingStepSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getRatingModifier()->resetRatingStepSize(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RatingBridge::SetStarStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> backgroundUriArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> foregroundUriArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> secondaryUriArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());

    std::string backgroundUri;
    if (backgroundUriArg->IsString()) {
        backgroundUri = backgroundUriArg->ToString(vm)->ToString();
    }

    std::string foregroundUri;
    if (foregroundUriArg->IsString()) {
        foregroundUri = foregroundUriArg->ToString(vm)->ToString();
    }

    std::string secondaryUri;
    if (secondaryUriArg->IsString()) {
        secondaryUri = secondaryUriArg->ToString(vm)->ToString();
    }

    if (secondaryUri.empty() && !backgroundUri.empty()) {
        secondaryUri = backgroundUri;
    }

    GetArkUINodeModifiers()->getRatingModifier()->setStarStyle(
        nativeNode, backgroundUri.c_str(), foregroundUri.c_str(), secondaryUri.c_str());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RatingBridge::ResetStarStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getRatingModifier()->resetStarStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG