/*
 * Copyright (c) 2023-2026 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/image_animator/bridge/arkts_native_image_animator_bridge.h"

#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "base/log/ace_scoring_log.h"
#include "base/memory/referenced.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
using AnimatorEvent = std::function<void()>;
constexpr int32_t DEFAULT_DURATION = 1000; // ms

constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int NUM_3 = 3;
constexpr int NUM_4 = 4;
constexpr int NUM_5 = 5;
constexpr int NUM_6 = 6;
constexpr int NUM_7 = 7;
constexpr int32_t IMAGE_SIZE = 4;
constexpr FillMode DEFAULT_FILL_MODE = FillMode::FORWARDS;

AnimatorEvent GetAnimatorEvent(ArkUIRuntimeCallInfo* runtimeCallInfo, std::string&& eventName)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, {});
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        return {};
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto callback = [vm, func = panda::CopyableGlobal(vm, func), node = targetNode, event = std::move(eventName)]() {
        CHECK_EQUAL_VOID(ArkTSUtils::CheckJavaScriptScope(vm), false);
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        ACE_SCORING_EVENT(event);
        PipelineContext::SetCallBackNode(node);
        auto result = func->Call(vm, func.ToLocal(), nullptr, 0);
        ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
    };
    return callback;
}

void ParseImageObject(const EcmaVM* vm, const Local<JSValueRef>& image, ImageProperties& imageProperties)
{
    if (!image->IsObject(vm)) {
        return;
    }
    auto jsObjImage = image->ToObject(vm);

    auto srcProp = jsObjImage->Get(vm, panda::StringRef::NewFromUtf8(vm, "src"));
    RefPtr<ResourceObject> resObj;
    bool srcValid = ArkTSUtils::ParseJsMedia(vm, srcProp, imageProperties.src, resObj);
    ArkTSUtils::GetJsMediaBundleInfo(vm, srcProp, imageProperties.bundleName, imageProperties.moduleName);
    if (!srcValid) {
#if defined(PIXEL_MAP_SUPPORTED)
        imageProperties.pixelMap = ArkTSUtils::CreatePixelMapFromNapiValue(vm, srcProp);
#endif
    }

    auto widthProp = jsObjImage->Get(vm, panda::StringRef::NewFromUtf8(vm, "width"));
    ArkTSUtils::ParseJsDimensionVp(vm, widthProp, imageProperties.width, false);
    auto heightProp = jsObjImage->Get(vm, panda::StringRef::NewFromUtf8(vm, "height"));
    ArkTSUtils::ParseJsDimensionVp(vm, heightProp, imageProperties.height, false);
    auto topProp = jsObjImage->Get(vm, panda::StringRef::NewFromUtf8(vm, "top"));
    ArkTSUtils::ParseJsDimensionVp(vm, topProp, imageProperties.top, false);
    auto leftProp = jsObjImage->Get(vm, panda::StringRef::NewFromUtf8(vm, "left"));
    ArkTSUtils::ParseJsDimensionVp(vm, leftProp, imageProperties.left, false);

    auto durationProp = jsObjImage->Get(vm, panda::StringRef::NewFromUtf8(vm, "duration"));
    ArkTSUtils::ParseJsInt32(vm, durationProp, imageProperties.duration);
}
} // namespace

void ImageAnimatorBridge::RegisterImageAnimatorAttributes(Local<panda::ObjectRef> object, EcmaVM* vm)
{
    const char* functionNames[] = { "create", "setState", "resetState", "setDuration", "resetDuration", "setFixedSize",
        "resetFixedSize", "setFillMode", "resetFillMode", "setReverse", "resetReverse", "setImages", "setJSImages",
        "resetImages", "setIterations", "resetIterations", "setAutoMonitorInvisibleArea", "setImageAnimatorOnStart",
        "resetImageAnimatorOnStart", "setImageAnimatorOnPause", "resetImageAnimatorOnPause", "setImageAnimatorOnRepeat",
        "resetImageAnimatorOnRepeat", "setImageAnimatorOnCancel", "resetImageAnimatorOnCancel",
        "setImageAnimatorOnFinish", "resetImageAnimatorOnFinish" };

    Local<JSValueRef> funcValues[] = {
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageAnimatorBridge::CreateImageAnimator),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageAnimatorBridge::SetState),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageAnimatorBridge::ResetState),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageAnimatorBridge::SetDuration),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageAnimatorBridge::ResetDuration),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageAnimatorBridge::SetFixedSize),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageAnimatorBridge::ResetFixedSize),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageAnimatorBridge::SetFillMode),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageAnimatorBridge::ResetFillMode),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageAnimatorBridge::SetReverse),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageAnimatorBridge::ResetReverse),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageAnimatorBridge::SetImages),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageAnimatorBridge::SetJSImages),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageAnimatorBridge::ResetImages),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageAnimatorBridge::SetIteration),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageAnimatorBridge::ResetIteration),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageAnimatorBridge::SetAutoMonitorInvisibleArea),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageAnimatorBridge::SetImageAnimatorOnStart),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageAnimatorBridge::ResetImageAnimatorOnStart),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageAnimatorBridge::SetImageAnimatorOnPause),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageAnimatorBridge::ResetImageAnimatorOnPause),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageAnimatorBridge::SetImageAnimatorOnRepeat),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageAnimatorBridge::ResetImageAnimatorOnRepeat),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageAnimatorBridge::SetImageAnimatorOnCancel),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageAnimatorBridge::ResetImageAnimatorOnCancel),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageAnimatorBridge::SetImageAnimatorOnFinish),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), ImageAnimatorBridge::ResetImageAnimatorOnFinish),
    };

    auto imageAnimator =
        panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(functionNames), functionNames, funcValues);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "imageAnimator"), imageAnimator);
}

ArkUINativeModuleValue ImageAnimatorBridge::CreateImageAnimator(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getImageAnimatorModifier()->createModel();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageAnimatorBridge::SetState(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    int32_t state = static_cast<int32_t>(Animator::Status::IDLE);
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (secondArg->IsNumber()) {
        state = secondArg->Int32Value(vm);
        if (state < static_cast<int32_t>(Animator::Status::IDLE) ||
            state > static_cast<int32_t>(Animator::Status::STOPPED)) {
            state = static_cast<int32_t>(Animator::Status::IDLE);
        }
        nodeModifiers->getImageAnimatorModifier()->setState(nativeNode, state);
    } else {
        nodeModifiers->getImageAnimatorModifier()->resetState(nativeNode);
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageAnimatorBridge::ResetState(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getImageAnimatorModifier()->resetState(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageAnimatorBridge::SetDuration(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    int32_t duration = DEFAULT_DURATION;
    if (secondArg->IsNumber()) {
        duration = secondArg->Int32Value(vm);
        if (duration < 0) {
            duration = DEFAULT_DURATION;
        }
    }
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getImageAnimatorModifier()->setDuration(nativeNode, duration);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageAnimatorBridge::ResetDuration(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    int32_t duration = DEFAULT_DURATION;
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getImageAnimatorModifier()->setDuration(nativeNode, duration);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageAnimatorBridge::SetFixedSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    uint32_t fixedSize = 1;
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (secondArg->IsBoolean()) {
        fixedSize = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
        nodeModifiers->getImageAnimatorModifier()->setFixedSize(nativeNode, fixedSize);
    } else {
        nodeModifiers->getImageAnimatorModifier()->resetFixedSize(nativeNode);
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageAnimatorBridge::ResetFixedSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getImageAnimatorModifier()->resetFixedSize(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageAnimatorBridge::SetFillMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (secondArg->IsNumber()) {
        int32_t fillMode = secondArg->Int32Value(vm);
        if (fillMode < static_cast<int32_t>(FillMode::NONE) || fillMode > static_cast<int32_t>(FillMode::BOTH)) {
            fillMode = static_cast<int32_t>(DEFAULT_FILL_MODE);
        }
        nodeModifiers->getImageAnimatorModifier()->setFillMode(nativeNode, fillMode);
    } else {
        nodeModifiers->getImageAnimatorModifier()->resetFillMode(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageAnimatorBridge::ResetFillMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getImageAnimatorModifier()->resetFillMode(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageAnimatorBridge::SetReverse(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (secondArg->IsBoolean()) {
        uint32_t value = static_cast<uint32_t>(secondArg->ToBoolean(vm)->Value());
        nodeModifiers->getImageAnimatorModifier()->setReverse(nativeNode, value);
    } else {
        nodeModifiers->getImageAnimatorModifier()->resetReverse(nativeNode);
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageAnimatorBridge::ResetReverse(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getImageAnimatorModifier()->resetReverse(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageAnimatorBridge::SetImages(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    Local<JSValueRef> fourthArg = runtimeCallInfo->GetCallArgRef(NUM_3);
    Local<JSValueRef> fifthArg = runtimeCallInfo->GetCallArgRef(NUM_4);
    Local<JSValueRef> sixthArg = runtimeCallInfo->GetCallArgRef(NUM_5);
    Local<JSValueRef> seventhArg = runtimeCallInfo->GetCallArgRef(NUM_6);
    Local<JSValueRef> eighthArg = runtimeCallInfo->GetCallArgRef(NUM_7);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    if (!eighthArg->IsNumber() || eighthArg->Int32Value(vm) <= 0) {
        return panda::JSValueRef::Undefined(vm);
    }
    int32_t arrayLength = eighthArg->Int32Value(vm);

    if (secondArg->IsNull() || !secondArg->IsArray(vm) || thirdArg->IsNull() || !thirdArg->IsArray(vm) ||
        fourthArg->IsNull() || !fourthArg->IsArray(vm) || fifthArg->IsNull() || !fifthArg->IsArray(vm) ||
        sixthArg->IsNull() || !sixthArg->IsArray(vm) || seventhArg->IsNull() || !seventhArg->IsArray(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto parseDimensionStruct = [](const EcmaVM* vm, const Local<JSValueRef>& arg) {
        CalcDimension val(0.0, DimensionUnit::VP);
        ArkTSUtils::ParseJsDimensionVp(vm, arg, val);
        return val;
    };
    auto parseInt32 = [](const EcmaVM* vm, const Local<JSValueRef>& arg) {
        if (arg->IsNumber()) {
            return arg->Int32Value(vm);
        }
        return 0;
    };
    auto srcArray = std::make_unique<std::string[]>(arrayLength);
    auto calcDimension = std::make_unique<CalcDimension[]>(arrayLength * 4);
    auto durationArray = std::make_unique<int32_t[]>(arrayLength);
    if (!ArkTSUtils::ParseStringArray(vm, secondArg, srcArray.get(), arrayLength) ||
        !ArkTSUtils::ParseArray<CalcDimension>(
            vm, thirdArg, calcDimension.get() + arrayLength * NUM_0, arrayLength, parseDimensionStruct) ||
        !ArkTSUtils::ParseArray<CalcDimension>(
            vm, fourthArg, calcDimension.get() + arrayLength * NUM_1, arrayLength, parseDimensionStruct) ||
        !ArkTSUtils::ParseArray<CalcDimension>(
            vm, fifthArg, calcDimension.get() + arrayLength * NUM_2, arrayLength, parseDimensionStruct) ||
        !ArkTSUtils::ParseArray<CalcDimension>(
            vm, sixthArg, calcDimension.get() + arrayLength * NUM_3, arrayLength, parseDimensionStruct) ||
        !ArkTSUtils::ParseArray<int32_t>(vm, seventhArg, durationArray.get(), arrayLength, parseInt32)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto images = std::make_unique<ArkUIImagePropertiesStruct[]>(arrayLength);
    for (int32_t i = 0; i < arrayLength; i++) {
        images[i].src = srcArray[i].c_str();
        for (int32_t j = 0; j < IMAGE_SIZE; j++) {
            images[i].number[j] = calcDimension[arrayLength * j + i].Value();
            images[i].unit[j] = static_cast<int8_t>(calcDimension[arrayLength * j + i].Unit());
            images[i].calc[j] = const_cast<char*>(calcDimension[arrayLength * j + i].CalcValue().c_str());
        }
        images[i].duration = *(durationArray.get() + i);
    }
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getImageAnimatorModifier()->setImages(nativeNode, images.get(), arrayLength);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageAnimatorBridge::SetJSImages(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    if (secondArg->IsNull() || !secondArg->IsArray(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }

    auto imageArray = panda::Local<panda::ArrayRef>(secondArg);
    int32_t arrayLength = static_cast<int32_t>(ArkTSUtils::GetArrayLength(vm, imageArray));
    std::vector<ImageProperties> imageList;
    for (int32_t i = 0; i < arrayLength; ++i) {
        ImageProperties imageProperties;
        auto element = imageArray->GetValueAt(vm, imageArray, i);
        ParseImageObject(vm, element, imageProperties);
        imageList.push_back(std::move(imageProperties));
    }

    auto images = std::make_unique<ArkUIImageJSProperties[]>(arrayLength);
    std::vector<CalcDimension> dimStorage(arrayLength * IMAGE_SIZE);
    for (int32_t i = 0; i < arrayLength; i++) {
        images[i].src = imageList[i].src.c_str();
        dimStorage[i * IMAGE_SIZE + NUM_0] = imageList[i].width;
        dimStorage[i * IMAGE_SIZE + NUM_1] = imageList[i].height;
        dimStorage[i * IMAGE_SIZE + NUM_2] = imageList[i].top;
        dimStorage[i * IMAGE_SIZE + NUM_3] = imageList[i].left;
        for (int32_t j = 0; j < IMAGE_SIZE; j++) {
            auto& dim = dimStorage[i * IMAGE_SIZE + j];
            images[i].number[j] = static_cast<float>(dim.Value());
            images[i].unit[j] = static_cast<int32_t>(dim.Unit());
            images[i].calc[j] = const_cast<char*>(dim.CalcValue().c_str());
        }
        images[i].duration = imageList[i].duration;
        images[i].pixelMap = reinterpret_cast<void*>(imageList[i].pixelMap.GetRawPtr());
        images[i].bundleName = imageList[i].bundleName.c_str();
        images[i].moduleName = imageList[i].moduleName.c_str();
    }
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getImageAnimatorModifier()->setJSImages(nativeNode, images.get(), arrayLength);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageAnimatorBridge::ResetImages(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getImageAnimatorModifier()->resetImages(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageAnimatorBridge::SetIteration(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    int32_t value;
    if (secondArg->IsNumber()) {
        value = secondArg->Int32Value(vm);
    } else {
        return panda::JSValueRef::Undefined(vm);
    }

    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getImageAnimatorModifier()->setImageAnimatorIteration(nativeNode, value);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageAnimatorBridge::ResetIteration(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getImageAnimatorModifier()->resetImageAnimatorIteration(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageAnimatorBridge::SetAutoMonitorInvisibleArea(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool value = false;
    if (secondArg->IsBoolean()) {
        value = secondArg->ToBoolean(vm)->BooleaValue(vm);
    }

    GetArkUINodeModifiers()->getImageAnimatorModifier()->setAutoMonitorInvisibleArea(nativeNode, value);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageAnimatorBridge::SetImageAnimatorOnStart(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getImageAnimatorModifier()->resetImageAnimatorOnStart(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (isJsView) {
        auto callback = GetAnimatorEvent(runtimeCallInfo, "ImageAnimator.onStart");
        GetArkUINodeModifiers()->getImageAnimatorModifier()->setImageAnimatorOnStart(
            nativeNode, reinterpret_cast<void*>(&callback));
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    std::function<void()> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)]() {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        func->Call(vm, func.ToLocal(), nullptr, 0);
    };
    GetArkUINodeModifiers()->getImageAnimatorModifier()->setImageAnimatorOnStart(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageAnimatorBridge::ResetImageAnimatorOnStart(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getImageAnimatorModifier()->resetImageAnimatorOnStart(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue ImageAnimatorBridge::SetImageAnimatorOnPause(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getImageAnimatorModifier()->resetImageAnimatorOnPause(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (isJsView) {
        auto callback = GetAnimatorEvent(runtimeCallInfo, "ImageAnimator.onPause");
        GetArkUINodeModifiers()->getImageAnimatorModifier()->setImageAnimatorOnPause(
            nativeNode, reinterpret_cast<void*>(&callback));
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    std::function<void()> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)]() {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        func->Call(vm, func.ToLocal(), nullptr, 0);
    };
    GetArkUINodeModifiers()->getImageAnimatorModifier()->setImageAnimatorOnPause(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageAnimatorBridge::ResetImageAnimatorOnPause(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getImageAnimatorModifier()->resetImageAnimatorOnPause(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageAnimatorBridge::SetImageAnimatorOnRepeat(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getImageAnimatorModifier()->resetImageAnimatorOnRepeat(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (isJsView) {
        auto callback = GetAnimatorEvent(runtimeCallInfo, "ImageAnimator.onRepeat");
        GetArkUINodeModifiers()->getImageAnimatorModifier()->setImageAnimatorOnRepeat(
            nativeNode, reinterpret_cast<void*>(&callback));
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    std::function<void()> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)]() {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        func->Call(vm, func.ToLocal(), nullptr, 0);
    };
    GetArkUINodeModifiers()->getImageAnimatorModifier()->setImageAnimatorOnRepeat(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageAnimatorBridge::ResetImageAnimatorOnRepeat(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getImageAnimatorModifier()->resetImageAnimatorOnRepeat(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageAnimatorBridge::SetImageAnimatorOnCancel(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getImageAnimatorModifier()->resetImageAnimatorOnCancel(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (isJsView) {
        auto callback = GetAnimatorEvent(runtimeCallInfo, "ImageAnimator.onCancel");
        GetArkUINodeModifiers()->getImageAnimatorModifier()->setImageAnimatorOnCancel(
            nativeNode, reinterpret_cast<void*>(&callback));
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    std::function<void()> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)]() {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        func->Call(vm, func.ToLocal(), nullptr, 0);
    };
    GetArkUINodeModifiers()->getImageAnimatorModifier()->setImageAnimatorOnCancel(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageAnimatorBridge::ResetImageAnimatorOnCancel(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getImageAnimatorModifier()->resetImageAnimatorOnCancel(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageAnimatorBridge::SetImageAnimatorOnFinish(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getImageAnimatorModifier()->resetImageAnimatorOnFinish(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (isJsView) {
        auto callback = GetAnimatorEvent(runtimeCallInfo, "ImageAnimator.onFinish");
        GetArkUINodeModifiers()->getImageAnimatorModifier()->setImageAnimatorOnFinish(
            nativeNode, reinterpret_cast<void*>(&callback));
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    std::function<void()> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)]() {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        func->Call(vm, func.ToLocal(), nullptr, 0);
    };
    GetArkUINodeModifiers()->getImageAnimatorModifier()->setImageAnimatorOnFinish(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue ImageAnimatorBridge::ResetImageAnimatorOnFinish(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    GetArkUINodeModifiers()->getImageAnimatorModifier()->resetImageAnimatorOnFinish(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
