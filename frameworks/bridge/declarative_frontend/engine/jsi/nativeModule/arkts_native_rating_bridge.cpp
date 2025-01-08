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
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/rating/rating_model_ng.h"

namespace OHOS::Ace::NG {
constexpr double STEPS_DEFAULT = 0.5;
constexpr double STEPS_MIN_SIZE = 0.1;
constexpr int32_t STARS_DEFAULT = 5;
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int PARAM_ARR_LENGTH_1 = 1;
const char* NODEPTR_OF_UINODE = "nodePtr_";
panda::Local<panda::JSValueRef> JsRatingChangeCallback(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    auto vm = runtimeCallInfo->GetVM();
    int32_t argc = static_cast<int32_t>(runtimeCallInfo->GetArgsNumber());
    if (argc != 1) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (!firstArg->IsNumber()) {
        return panda::JSValueRef::Undefined(vm);
    }
    double value = firstArg->ToNumber(vm)->Value();
    auto ref = runtimeCallInfo->GetThisRef();
    auto obj = ref->ToObject(vm);
    if (obj->GetNativePointerFieldCount(vm) < 1) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = static_cast<FrameNode*>(obj->GetNativePointerField(vm, 0));
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    RatingModelNG::SetChangeValue(frameNode, value);
    return panda::JSValueRef::Undefined(vm);
}

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
    auto steps = secondArg->ToNumber(vm)->Value();
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
    if (backgroundUriArg->IsString(vm)) {
        backgroundUri = backgroundUriArg->ToString(vm)->ToString(vm);
    }

    std::string foregroundUri;
    if (foregroundUriArg->IsString(vm)) {
        foregroundUri = foregroundUriArg->ToString(vm)->ToString(vm);
    }

    std::string secondaryUri;
    if (secondaryUriArg->IsString(vm)) {
        secondaryUri = secondaryUriArg->ToString(vm)->ToString(vm);
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

ArkUINativeModuleValue RatingBridge::SetContentModifierBuilder(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto* frameNode = reinterpret_cast<FrameNode*>(firstArg->ToNativePointer(vm)->Value());
    if (!secondArg->IsObject(vm)) {
        RatingModelNG::SetBuilderFunc(frameNode, nullptr);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::CopyableGlobal<panda::ObjectRef> obj(vm, secondArg);
    auto containerId = Container::CurrentId();
    RatingModelNG::SetBuilderFunc(frameNode,
        [vm, frameNode, obj = std::move(obj), containerId](
            RatingConfiguration config) -> RefPtr<FrameNode> {
            ContainerScope scope(containerId);
            auto context = ArkTSUtils::GetContext(vm);
            CHECK_EQUAL_RETURN(context->IsUndefined(), true, nullptr);
            const char* keys[] = { "stars", "indicator", "rating", "stepSize", "enabled", "triggerChange" };
            Local<JSValueRef> values[] = { panda::NumberRef::New(vm, config.starNum_),
                panda::BooleanRef::New(vm, config.isIndicator_),
                panda::NumberRef::New(vm, config.rating_),
                panda::NumberRef::New(vm, config.stepSize_),
                panda::BooleanRef::New(vm, config.enabled_),
                panda::FunctionRef::New(vm, JsRatingChangeCallback) };
            auto rating = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
            rating->SetNativePointerFieldCount(vm, 1);
            rating->SetNativePointerField(vm, 0, static_cast<void*>(frameNode));
            panda::Local<panda::JSValueRef> params[NUM_2] = { context, rating };
            LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            auto makeFunc = obj.ToLocal()->Get(vm, panda::StringRef::NewFromUtf8(vm, "makeContentModifierNode"));
            CHECK_EQUAL_RETURN(makeFunc->IsFunction(vm), false, nullptr);
            panda::Local<panda::FunctionRef> func = makeFunc;
            auto result = func->Call(vm, obj.ToLocal(), params, 2);
            JSNApi::ExecutePendingJob(vm);
            CHECK_EQUAL_RETURN(result.IsEmpty() || trycatch.HasCaught() || !result->IsObject(vm), true, nullptr);
            panda::Local<panda::JSValueRef> nodeptr =
                result->ToObject(vm)->Get(vm, panda::StringRef::NewFromUtf8(vm, NODEPTR_OF_UINODE));
            CHECK_EQUAL_RETURN(nodeptr.IsEmpty() || nodeptr->IsUndefined() || nodeptr->IsNull(), true, nullptr);
            auto* frameNode = reinterpret_cast<FrameNode*>(nodeptr->ToNativePointer(vm)->Value());
            CHECK_NULL_RETURN(frameNode, nullptr);
            return AceType::Claim(frameNode);
        });
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RatingBridge::SetRatingOptions(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    CHECK_EQUAL_RETURN(runtimeCallInfo->GetArgsNumber() != NUM_3, true, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> ratingArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> indicatorArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    auto pointer = nodeArg->ToNativePointer(vm);
    CHECK_EQUAL_RETURN(pointer.IsEmpty(), true, panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(pointer->Value());
    CHECK_NULL_RETURN(nativeNode, panda::JSValueRef::Undefined(vm));

    double rating = 0.0;
    if (!ratingArg->IsNull() && ratingArg->IsNumber()) {
        rating = ratingArg->ToNumber(vm)->Value();
    }
    if (LessNotEqual(rating, 0.0)) {
        rating = 0.0;
    }

    int32_t indicator = 0;
    if (!indicatorArg->IsNull() && indicatorArg->IsBoolean()) {
        indicator = indicatorArg->ToBoolean(vm)->Value();
    }
    GetArkUINodeModifiers()->getRatingModifier()->setRatingOptions(
        nativeNode, rating, indicator);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RatingBridge::SetOnChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    int32_t argsNumber = runtimeCallInfo->GetArgsNumber();
    if (argsNumber != NUM_2) {
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getRatingModifier()->resetOnChange(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(const std::string&)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)](
                                                           const std::string& star) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        panda::Local<panda::NumberRef> starParam = panda::NumberRef::New(vm, std::stod(star));
        panda::Local<panda::JSValueRef> params[PARAM_ARR_LENGTH_1] = { starParam };
        func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_1);
    };
    GetArkUINodeModifiers()->getRatingModifier()->setOnChange(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RatingBridge::ResetOnChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(nativeNodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getRatingModifier()->resetOnChange(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

} // namespace OHOS::Ace::NG