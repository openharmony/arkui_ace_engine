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

#include "core/components_ng/pattern/hyperlink/bridge/arkts_native_hyperlink_bridge.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_model.h"
#include "core/components_ng/pattern/hyperlink/hyperlink_model_ng.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"

namespace OHOS::Ace {

HyperlinkModel* HyperlinkModel::GetInstance()
{
#ifdef NG_BUILD
    static NG::HyperlinkModelNG instance;
    return &instance;
#else
    if (Container::IsCurrentUseNewPipeline()) {
        static NG::HyperlinkModelNG instance;
        return &instance;
    } else {
        static Framework::HyperlinkModelImpl instance;
        return &instance;
    }
#endif
}

} // namespace OHOS::Ace

namespace OHOS::Ace::NG {
namespace {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
} // namespace

void HyperlinkBridge::RegisterHyperlinkAttributes(Local<panda::ObjectRef> object, EcmaVM *vm) {
    LOGE("Start RegisterHyperlinkAttributes nativeModule");

    const char* functionNames[] = {
        "create", "pop", "color", "draggable", "responseRegion"
    };

    Local<JSValueRef> functionValues[] = {
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), HyperlinkBridge::CreateHyperlink),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), HyperlinkBridge::Color),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), HyperlinkBridge::Draggable),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), HyperlinkBridge::ResponseRegion),
    };

    auto hyperlink = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(functionNames), functionNames, functionValues);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "hyperlink"), hyperlink);

    LOGE("Finish RegisterHyperlinkAttributes nativeModule");
}

ArkUINativeModuleValue HyperlinkBridge::Color(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    class Color color;
    RefPtr<ResourceObject> resourceObject;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color, resourceObject, nodeInfo)) {
        GetArkUINodeModifiers()->getHyperlinkModifier()->resetHyperlinkColor(nativeNode);
    } else {
        GetArkUINodeModifiers()->getHyperlinkModifier()->setHyperlinkColor(
            nativeNode, color.GetValue(), AceType::RawPtr(resourceObject));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue HyperlinkBridge::Draggable(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> draggableArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    if (draggableArg->IsBoolean()) {
        bool boolValue = draggableArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getHyperlinkModifier()->setHyperlinkDraggable(nativeNode, boolValue);
    } else {
        GetArkUINodeModifiers()->getHyperlinkModifier()->resetHyperlinkDraggable(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue HyperlinkBridge::ResponseRegion(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    int32_t length = thirdArg->Int32Value(vm);
    ArkUI_Float32 regionArray[length];
    int32_t regionUnits[length];
    if (!ArkTSUtils::ParseResponseRegion(vm, secondArg, regionArray, regionUnits, length)) {
        GetArkUINodeModifiers()->getHyperlinkModifier()->resetHyperlinkResponseRegion(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUINodeModifiers()->getHyperlinkModifier()->setHyperlinkResponseRegion(
        nativeNode, regionArray, regionUnits, length);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue HyperlinkBridge::CreateHyperlink(ArkUIRuntimeCallInfo* runtimeCallInfo) {
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));

    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());

    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    std::string address{};
    RefPtr<ResourceObject> addressResObj{};
    auto addressRet = ArkTSUtils::ParseJsString(vm, firstArg, address, addressResObj);

    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    std::string content{};
    RefPtr<ResourceObject> contentResObj{};
    auto contentRet = runtimeCallInfo->GetArgsNumber() == 2
                        ? ArkTSUtils::ParseJsString(vm, firstArg, address, contentResObj)
                        : false;

    HyperlinkModel::GetInstance()->Create(address, content);

    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_RETURN(pattern, panda::JSValueRef::Undefined(vm))

    if (addressRet && SystemProperties::ConfigChangePerform() && addressResObj) {
        pattern->RegisterResource<std::string>("Address", addressResObj, address);
    } else {
        pattern->UnRegisterResource("Address");
    }

    if (contentRet && SystemProperties::ConfigChangePerform() && contentResObj) {
        pattern->RegisterResource<std::string>("Content", contentResObj, content);
    } else {
        pattern->UnRegisterResource("Content");
    }
                
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue HyperlinkBridge::Pop() {
    if (ViewStackModel::GetInstance()->IsPrebuilding()) {
        ViewStackModel::GetInstance()->PushPrebuildCompCmd("[JSHyperlink][pop]", &JSHyperlink::Pop);
        return panda::JSValueRef::Undefined(vm);
    }

    if (Container::IsCurrentUseNewPipeline()) {
        ViewStackModel::GetInstance()->PopContainer();
        return panda::JSValueRef::Undefined(vm);
    }

    HyperlinkModel::GetInstance()->Pop();
    return panda::JSValueRef::Undefined(vm);
}

} // namespace OHOS::Ace::NG