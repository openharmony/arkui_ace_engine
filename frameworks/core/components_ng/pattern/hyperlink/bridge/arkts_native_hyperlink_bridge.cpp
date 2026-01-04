/*
 * Copyright (c) 2023-2025 Huawei Device Co., Ltd.
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

#include "base/log/ace_scoring_log.h"
#include "core/components_ng/base/view_stack_model.h"
#include "core/components_ng/pattern/hyperlink/hyperlink_model_ng.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "core/components_ng/pattern/hyperlink/bridge/hyperlink_model_impl.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
} // namespace

void HyperlinkBridge::RegisterHyperlinkAttributes(Local<panda::ObjectRef> object, EcmaVM *vm) {
    LOGI("Start RegisterHyperlinkAttributes nativeModule");

    const char* functionNames[] = {
        "create", "color", "draggable", "responseRegion", "pop",
    };

    Local<JSValueRef> functionValues[] = {
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), HyperlinkBridge::CreateHyperlink),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), HyperlinkBridge::Color),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), HyperlinkBridge::Draggable),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), HyperlinkBridge::ResponseRegion),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), HyperlinkBridge::Pop),
    };

    auto hyperlink = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(functionNames), functionNames, functionValues);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "hyperlink"), hyperlink);

    LOGI("Finish RegisterHyperlinkAttributes nativeModule");
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
    LOGI("[Hyperlink] HyperlinkBridge::CreateHyperlink arrived");
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    LOGI("[Hyperlink] HyperlinkBridge::CreateHyperlink arrivevm created");

    auto frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    LOGI("[Hyperlink] HyperlinkBridge::CreateHyperlink framenode created");
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_RETURN(pattern, panda::JSValueRef::Undefined(vm));
    LOGI("[Hyperlink] HyperlinkBridge::CreateHyperlink pattern created");

    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    std::string address{};
    RefPtr<ResourceObject> addressResObj{};
    auto addressRet = ArkTSUtils::ParseJsString(vm, firstArg, address, addressResObj);
    LOGI("[Hyperlink] HyperlinkBridge::CreateHyperlink address parsed");
    LOGI("[Hyperlink] HyperlinkBridge::CreateHyperlink %{public}s, %{public}d", address.c_str(), addressRet);

    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    std::string content{};
    RefPtr<ResourceObject> contentResObj{};
    auto contentRet = runtimeCallInfo->GetArgsNumber() == 2
                        ? ArkTSUtils::ParseJsString(vm, secondArg, content, contentResObj)
                        : false;
    LOGI("[Hyperlink] HyperlinkBridge::CreateHyperlink content parsed");
    LOGI("[Hyperlink] HyperlinkBridge::CreateHyperlink %{public}s, %{public}d", content.c_str(), contentRet);

    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    LOGI("[Hyperlink] HyperlinkBridge::CreateHyperlink nodeModifiers not null");

    nodeModifiers->getHyperlinkModifier()->create(address, content);
    LOGI("[Hyperlink] HyperlinkBridge::CreateHyperlink modifier create called");

    if (addressRet && SystemProperties::ConfigChangePerform() && addressResObj) {
        pattern->RegisterResource<std::string>("Address", addressResObj, address);
        LOGI("[Hyperlink] HyperlinkBridge::CreateHyperlink Address registered");
    } else {
        pattern->UnRegisterResource("Address");
        LOGI("[Hyperlink] HyperlinkBridge::CreateHyperlink Address unregistered");
    }

    if (contentRet && SystemProperties::ConfigChangePerform() && contentResObj) {
        pattern->RegisterResource<std::string>("Content", contentResObj, content);
        LOGI("[Hyperlink] HyperlinkBridge::CreateHyperlink Content registered");
    } else {
        pattern->UnRegisterResource("Content");
        LOGI("[Hyperlink] HyperlinkBridge::CreateHyperlink Content unregistered");
    }

    LOGI("[Hyperlink] HyperlinkBridge::CreateHyperlink finished");
    return panda::JSValueRef::Undefined(vm);
}

void HyperlinkBridge::PopNew() {
    if (ViewStackModel::GetInstance()->IsPrebuilding()) {
        return ViewStackModel::GetInstance()->PushPrebuildCompCmd("[HyperlinkBridge][pop]", &HyperlinkBridge::PopNew);
    }

    if (Container::IsCurrentUseNewPipeline()) {
        return ViewStackModel::GetInstance()->PopContainer();
    }

    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_VOID(nodeModifiers);
    nodeModifiers->getHyperlinkModifier()->pop();
}

ArkUINativeModuleValue HyperlinkBridge::Pop(ArkUIRuntimeCallInfo* runtimeCallInfo) {
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));

    PopNew();

    return panda::JSValueRef::Undefined(vm);
}

} // namespace OHOS::Ace::NG