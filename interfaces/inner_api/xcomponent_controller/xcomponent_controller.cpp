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

#include "xcomponent_controller.h"

#include "js_native_api.h"

#include "bridge/declarative_frontend/jsview/js_xcomponent_controller.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_pattern.h"

namespace OHOS::Ace {
namespace {
const char* NODEPTR_OF_UINODE = "nodePtr_";
} // namespace
std::shared_ptr<XComponentController> XComponentController::GetXComponentControllerFromNapiValue(
    napi_env env, napi_value napiValue)
{
    if (env == nullptr) {
        return nullptr;
    }
    const auto* vm = reinterpret_cast<NativeEngine*>(env)->GetEcmaVm();
    auto localRef = NapiValueToLocalValue(napiValue);
    if (localRef->IsNull()) {
        return nullptr;
    }
    auto* jsXComponentController = static_cast<Framework::JSXComponentController*>(
        Local<panda::ObjectRef>(localRef)->GetNativePointerField(vm, 0));
    if (!jsXComponentController) {
        return nullptr;
    }
    return jsXComponentController->GetController();
}

XComponentControllerErrorCode XComponentController::SetSurfaceCallbackMode(
    napi_env env, napi_value node, SurfaceCallbackMode mode)
{
    if (env == nullptr) {
        return XComponentControllerErrorCode::XCOMPONENT_CONTROLLER_BAD_PARAMETER;
    }
    const auto* vm = reinterpret_cast<NativeEngine*>(env)->GetEcmaVm();
    auto nodeRef = NapiValueToLocalValue(node);
    if (nodeRef.IsEmpty() || !nodeRef->IsObject(vm)) {
        return XComponentControllerErrorCode::XCOMPONENT_CONTROLLER_BAD_PARAMETER;
    }
    auto nodeObj = nodeRef->ToObject(vm);
    panda::Local<panda::JSValueRef> nodePtr = nodeObj->Get(vm, panda::StringRef::NewFromUtf8(vm, NODEPTR_OF_UINODE));
    if (nodePtr.IsEmpty() || nodePtr->IsNull() || nodePtr->IsUndefined()) {
        return XComponentControllerErrorCode::XCOMPONENT_CONTROLLER_BAD_PARAMETER;
    }
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(nodePtr->ToNativePointer(vm)->Value());
    if (!frameNode) {
        return XComponentControllerErrorCode::XCOMPONENT_CONTROLLER_BAD_PARAMETER;
    }
    auto* xcPattern = frameNode->GetPatternPtr<NG::XComponentPattern>();
    if (!xcPattern) {
        return XComponentControllerErrorCode::XCOMPONENT_CONTROLLER_BAD_PARAMETER;
    }
    xcPattern->ChangeSurfaceCallbackMode(mode);
    return XComponentControllerErrorCode::XCOMPONENT_CONTROLLER_NO_ERROR;
}
} // namespace OHOS::Ace
