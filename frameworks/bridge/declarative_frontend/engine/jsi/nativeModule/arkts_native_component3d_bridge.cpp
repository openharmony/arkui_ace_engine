/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_component3d_bridge.h"

#include "base/utils/utils.h"
#include "bridge/declarative_frontend/jsview/js_sceneview.h"
#include "core/components_ng/base/frame_node.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
} // namespace

ArkUINativeModuleValue Component3DBridge::SetShaderInputBuffer(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    if (firstArg.IsEmpty() || !firstArg->IsNativePointer(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    CHECK_NULL_RETURN(!secondArg.IsNull(), panda::JSValueRef::Undefined(vm));
    if (!secondArg->IsArray(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto array = Local<panda::ArrayRef>(secondArg);
    auto length = array->Length(vm);

    std::vector<ArkUI_Float32> bufferArray;
    for (uint32_t index = 0; index < length; index++) {
        Local<JSValueRef> value = panda::ArrayRef::GetValueAt(vm, array, index);
        double param;
        if (ArkTSUtils::ParseJsDouble(vm, value, param)) {
            bufferArray.emplace_back(static_cast<ArkUI_Float32>(param));
        } else {
            bufferArray.clear();
            break;
        }
    }

    auto component3DModifier = GetArkUINodeModifiers()->getComponent3DModifier();
    if (component3DModifier) {
        component3DModifier->setShaderInputBuffer(nativeNode, bufferArray.data(), bufferArray.size());
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue Component3DBridge::ResetShaderInputBuffer(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    if (firstArg.IsEmpty() || !firstArg->IsNativePointer(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto component3DModifier = GetArkUINodeModifiers()->getComponent3DModifier();
    if (component3DModifier) {
        component3DModifier->resetShaderInputBuffer(nativeNode);
    }

    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG
