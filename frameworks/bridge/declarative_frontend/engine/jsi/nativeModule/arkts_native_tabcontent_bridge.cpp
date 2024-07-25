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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_tabcontent_bridge.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_tab_content.h"

namespace OHOS::Ace::NG {
ArkUINativeModuleValue TabContentBridge::SetTabBar(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    Framework::JSTabContent::SetTabBar(Framework::JsiCallbackInfo(runtimeCallInfo));
    return panda::JSValueRef::Undefined(runtimeCallInfo->GetVM());
}

ArkUINativeModuleValue TabContentBridge::ResetTabBar(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabContentModifier()->setTabContentLabel(nativeNode, "");
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabContentBridge::SetTabContentWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    LOGW("TabContent does not support width and height settings");
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabContentBridge::SetTabContentHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    LOGW("TabContent does not support width and height settings");
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabContentBridge::SetTabContentSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    LOGW("TabContent does not support width and height settings");
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue TabContentBridge::ResetTabContentWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    LOGW("TabContent does not support width and height settings");
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabContentBridge::ResetTabContentHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    LOGW("TabContent does not support width and height settings");
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabContentBridge::ResetTabContentSize(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    LOGW("TabContent does not support width and height settings");
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
