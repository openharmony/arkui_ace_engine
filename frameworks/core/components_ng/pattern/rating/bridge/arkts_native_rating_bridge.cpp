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

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_model.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/rating/bridge/arkts_native_rating_bridge.h"
#include "core/components_ng/pattern/rating/rating_model_ng.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"

namespace OHOS::Ace::NG {
constexpr double RATING_SCORE_DEFAULT_VALUE = 0.0;
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

bool GetNativeNode(ArkUINodeHandle& nativeNode, const Local<JSValueRef>& firstArg, panda::ecmascript::EcmaVM* vm)
{
    if (firstArg->IsNativePointer(vm)) {
        nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
        return true;
    }
    if (firstArg->IsBoolean() && firstArg->ToBoolean(vm)->Value()) {
        nativeNode = nullptr;
        return true;
    }
    return false;
}

bool IsJsView(const Local<JSValueRef>& firstArg, panda::ecmascript::EcmaVM* vm)
{
    return firstArg->IsBoolean() && firstArg->ToBoolean(vm)->Value();
}

ArkUINativeModuleValue RatingBridge::CreateRating(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (IsJsView(firstArg, vm)) {
        return JsCreateRating(runtimeCallInfo);
    }
    CHECK_NULL_RETURN(firstArg->IsNumber(), panda::JSValueRef::Undefined(vm));
    double rating = static_cast<double>(firstArg->ToNumber(vm)->Value());
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(secondArg->IsBoolean(), panda::JSValueRef::Undefined(vm));
    bool indicator = static_cast<bool>(secondArg->ToBoolean(vm)->Value());
    GetArkUINodeModifiers()->getRatingModifier()->createRating(rating, indicator);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue JsCreateSetOnChangeEvent(const EcmaVM* vm, const Local<JSValueRef>& changeEventVal)
{
    panda::Local<panda::FunctionRef> func = changeEventVal->ToObject(vm);
    NG::FrameNode* frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    std::function<void(const std::string&)> callback = [vm, weakNode = AceType::WeakClaim(frameNode),
                                                        func = panda::CopyableGlobal(vm, func)]
                                                        (const std::string& star) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(weakNode);
        panda::Local<panda::NumberRef> starParam = panda::NumberRef::New(vm, StringUtils::StringToDouble(star));
        panda::Local<panda::JSValueRef> params[PARAM_ARR_LENGTH_1] = { starParam };
        auto result = func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_1);
        ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
    };
    GetArkUINodeModifiers()->getRatingModifier()->setOnChangeEvent(reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RatingBridge::JsCreateRating(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(secondArg->IsObject(vm), panda::JSValueRef::Undefined(vm));
    double rating = RATING_SCORE_DEFAULT_VALUE;
    bool indicator = false;
    Local<JSValueRef> changeEventVal = panda::JSValueRef::Undefined(vm);
    auto obj = secondArg->ToObject(vm);
    auto getRating = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "rating"));
    auto getIndicator = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "indicator"));
    auto bindingV1 = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "$rating"));
    if (getRating->IsObject(vm)) {
        auto getRatingObj = getRating->ToObject(vm);
        changeEventVal = getRatingObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "changeEvent"));
        auto ratingValue = getRatingObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "value"));
        if (ratingValue->IsNumber()) {
            rating = static_cast<double>(ratingValue->ToNumber(vm)->Value());
        }
    } else if (!bindingV1->IsUndefined() && !bindingV1->IsNull()) {
        changeEventVal = bindingV1;
        if (getRating->IsNumber()) {
            rating = static_cast<double>(getRating->ToNumber(vm)->Value());
        }
    } else if (getRating->IsNumber()) {
        rating = static_cast<double>(getRating->ToNumber(vm)->Value());
    }
    if (rating < 0) {
        rating = RATING_SCORE_DEFAULT_VALUE;
    }
    if (getIndicator->IsBoolean()) {
        indicator = getIndicator->ToBoolean(vm)->Value();
    }
    GetArkUINodeModifiers()->getRatingModifier()->createRating(rating, indicator);
    if (changeEventVal->IsUndefined() || changeEventVal->IsNull() || !changeEventVal->IsFunction(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    return JsCreateSetOnChangeEvent(vm, changeEventVal);
}

ArkUINativeModuleValue RatingBridge::SetStars(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (IsJsView(firstArg, vm) && (secondArg->IsNull() || !secondArg->IsNumber())) {
        GetArkUINodeModifiers()->getRatingModifier()->setStars(nativeNode, STARS_DEFAULT);
        return panda::JSValueRef::Undefined(vm);
    }
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
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
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
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> backgroundUriArg = panda::JSValueRef::Undefined(vm);
    Local<JSValueRef> foregroundUriArg = panda::JSValueRef::Undefined(vm);
    Local<JSValueRef> secondaryUriArg = panda::JSValueRef::Undefined(vm);
    if (IsJsView(nodeArg, vm)) {
        Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
        if (!secondArg->IsObject(vm)) {
            return ResetStarStyle(runtimeCallInfo);
        }
        auto obj = secondArg->ToObject(vm);
        backgroundUriArg = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "backgroundUri"));
        foregroundUriArg = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "foregroundUri"));
        secondaryUriArg = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "secondaryUri"));
    } else {
        backgroundUriArg = runtimeCallInfo->GetCallArgRef(NUM_1);
        foregroundUriArg = runtimeCallInfo->GetCallArgRef(NUM_2);
        secondaryUriArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    }
    ArkUIRatingStyleStruct resObj;
    std::string backgroundUri;
    RefPtr<ResourceObject> backgroundResObj;
    if (!ArkTSUtils::ParseJsMedia(vm, backgroundUriArg, backgroundUri, backgroundResObj)) {
        ArkTSUtils::ParseJsString(vm, backgroundUriArg, backgroundUri, backgroundResObj);
    }
    resObj.backgroundResObj = AceType::RawPtr(backgroundResObj);
    std::string foregroundUri;
    RefPtr<ResourceObject> foregroundResObj;
    if (!ArkTSUtils::ParseJsMedia(vm, foregroundUriArg, foregroundUri, foregroundResObj)) {
        ArkTSUtils::ParseJsString(vm, foregroundUriArg, foregroundUri, foregroundResObj);
    }
    resObj.foregroundResObj = AceType::RawPtr(foregroundResObj);
    std::string secondaryUri;
    RefPtr<ResourceObject> secondaryResObj;
    if (!ArkTSUtils::ParseJsMedia(vm, secondaryUriArg, secondaryUri, secondaryResObj)) {
        ArkTSUtils::ParseJsString(vm, secondaryUriArg, secondaryUri, secondaryResObj);
    }
    resObj.secondaryResObj = AceType::RawPtr(secondaryResObj);
    if (secondaryUri.empty() && !backgroundUri.empty()) {
        secondaryUri = backgroundUri;
        resObj.secondaryResObj = AceType::RawPtr(backgroundResObj);
    }
    GetArkUINodeModifiers()->getRatingModifier()->setStarStylePtr(
        nativeNode, backgroundUri.c_str(), foregroundUri.c_str(), secondaryUri.c_str(), resObj);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue RatingBridge::ResetStarStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
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
            panda::LocalScope pandaScope(vm);
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
            panda::TryCatch trycatch(vm);
            auto makeFunc = obj.ToLocal()->Get(vm, panda::StringRef::NewFromUtf8(vm, "makeContentModifierNode"));
            CHECK_EQUAL_RETURN(makeFunc->IsFunction(vm), false, nullptr);
            panda::Local<panda::FunctionRef> func = makeFunc;
            auto result = func->Call(vm, obj.ToLocal(), params, 2);
            panda::JSNApi::ExecutePendingJob(vm);
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
    uint32_t argsNumber = runtimeCallInfo->GetArgsNumber();
    if (argsNumber != NUM_2) {
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> nativeNodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(GetNativeNode(nativeNode, nativeNodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    bool isJsView = IsJsView(nativeNodeArg, vm);
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        if (!isJsView) {
            GetArkUINodeModifiers()->getRatingModifier()->resetOnChange(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    NG::FrameNode* frameNode = nullptr;
    if (nativeNode) {
        frameNode = reinterpret_cast<FrameNode*>(nativeNode);
        CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    } else {
        frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(const std::string&)> callback = [vm, isJsView, weakNode = AceType::WeakClaim(frameNode),
                                                           func = panda::CopyableGlobal(vm, func)]
                                                           (const std::string& star) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(weakNode);
        panda::Local<panda::NumberRef> starParam = panda::NumberRef::New(vm, StringUtils::StringToDouble(star));
        panda::Local<panda::JSValueRef> params[PARAM_ARR_LENGTH_1] = { starParam };
        auto result = func->Call(vm, func.ToLocal(), params, PARAM_ARR_LENGTH_1);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        }
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

void RatingBridge::RegisterRatingAttributes(Local<panda::ObjectRef> object, EcmaVM *vm)
{
    const char* functionNames[] = { "create", "setStars", "resetStars", "setStepSize",
        "resetStepSize", "setStarStyle", "resetStarStyle", "setContentModifierBuilder", "setRatingOptions",
        "setOnChange", "resetOnChange" };

    Local<JSValueRef> funcValues[] = {
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RatingBridge::CreateRating),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RatingBridge::SetStars),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RatingBridge::ResetStars),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RatingBridge::SetRatingStepSize),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RatingBridge::ResetRatingStepSize),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RatingBridge::SetStarStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RatingBridge::ResetStarStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RatingBridge::SetContentModifierBuilder),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RatingBridge::SetRatingOptions),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RatingBridge::SetOnChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RatingBridge::ResetOnChange),
    };

    auto rating = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(functionNames), functionNames, funcValues);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "rating"), rating);
}

} // namespace OHOS::Ace::NG