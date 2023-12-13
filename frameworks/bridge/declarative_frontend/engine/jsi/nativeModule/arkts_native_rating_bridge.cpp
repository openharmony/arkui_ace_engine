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

#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_api.h"
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
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    auto input = secondArg->ToNumber(vm)->Value();
    int32_t stars = static_cast<int32_t>(input);
    if (stars <= 0) {
        stars = STARS_DEFAULT;
    }
    GetArkUIInternalNodeAPI()->GetRatingModifier().SetStars(nativeNode, stars);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RatingBridge::ResetStars(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetRatingModifier().ResetStars(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue RatingBridge::SetRatingStepSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    
    if (secondArg->IsNull() || !secondArg->IsNumber()) {
        GetArkUIInternalNodeAPI()->GetRatingModifier().ResetRatingStepSize(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto steps  = secondArg->ToNumber(vm)->Value();
    if (LessNotEqual(steps, STEPS_MIN_SIZE)) {
        steps = STEPS_DEFAULT;
    }
    GetArkUIInternalNodeAPI()->GetRatingModifier().SetRatingStepSize(nativeNode, steps);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RatingBridge::ResetRatingStepSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetRatingModifier().ResetRatingStepSize(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RatingBridge::SetStarStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> forthArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();

    std::string backgroundUri;
    ArkTSUtils::ParseJsMedia(vm, secondArg, backgroundUri);
    std::string foregroundUri;
    ArkTSUtils::ParseJsMedia(vm, thirdArg, foregroundUri);
    std::string secondaryUri;
    ArkTSUtils::ParseJsMedia(vm, forthArg, secondaryUri);

    GetArkUIInternalNodeAPI()->GetRatingModifier().SetStarStyle(nativeNode,
        backgroundUri.c_str(), foregroundUri.c_str(), secondaryUri.c_str());
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RatingBridge::ResetStarStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    void* nativeNode = firstArg->ToNativePointer(vm)->Value();
    GetArkUIInternalNodeAPI()->GetRatingModifier().ResetStarStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG