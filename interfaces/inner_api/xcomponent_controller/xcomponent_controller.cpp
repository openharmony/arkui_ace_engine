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

#include "utils.h"
#include "js_native_api.h"

#include "bridge/declarative_frontend/jsview/js_xcomponent_controller.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_pattern.h"

namespace OHOS::Ace {
namespace {
const char* NODEPTR_OF_UINODE = "nodePtr_";
constexpr char XCOMPONENT_GET_CONTROLLER_FUNC[] = "OHOS_ACE_GetXComponentController";
constexpr char XCOMPONENT_CHANGE_SURFACE_CALLBACKMODE_FUNC[] = "OHOS_ACE_ChangeXComponentSurfaceCallbackMode";
constexpr char XCOMPONENT_SET_RENDER_FIT_FUNC[] = "OHOS_ACE_SetRenderFitBySurfaceId";
constexpr char XCOMPONENT_GET_RENDER_FIT_FUNC[] = "OHOS_ACE_GetRenderFitBySurfaceId";
using GetControllerFunc = void (*)(void*, void*);
using ChangeSurfaceCallbackModeFunc = XComponentControllerErrorCode (*)(void*, char);
using SetRenderFitFunc = XComponentControllerErrorCode (*)(const std::string&, int32_t, bool);
using GetRenderFitFunc = XComponentControllerErrorCode (*)(const std::string&, int32_t&, bool&);
} // namespace
void GetController(void* jsController, void* controller)
{
    static GetControllerFunc entry = nullptr;
    if (entry == nullptr) {
        LIBHANDLE handle = LOADLIB(AceForwardCompatibility::GetAceLibName());
        if (handle == nullptr) {
            return;
        }
        entry = reinterpret_cast<GetControllerFunc>(LOADSYM(handle, XCOMPONENT_GET_CONTROLLER_FUNC));
        if (entry == nullptr) {
            FREELIB(handle);
            return;
        }
    }
    entry(jsController, controller);
}

XComponentControllerErrorCode ChangeSurfaceCallbackMode(void* frameNode, char mode)
{
    static ChangeSurfaceCallbackModeFunc entry = nullptr;
    if (entry == nullptr) {
        LIBHANDLE handle = LOADLIB(AceForwardCompatibility::GetAceLibName());
        if (handle == nullptr) {
            return XComponentControllerErrorCode::XCOMPONENT_CONTROLLER_BAD_PARAMETER;
        }
        entry = reinterpret_cast<ChangeSurfaceCallbackModeFunc>(
            LOADSYM(handle, XCOMPONENT_CHANGE_SURFACE_CALLBACKMODE_FUNC));
        if (entry == nullptr) {
            FREELIB(handle);
            return XComponentControllerErrorCode::XCOMPONENT_CONTROLLER_BAD_PARAMETER;
        }
    }
    return entry(frameNode, mode);
}
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
    std::shared_ptr<XComponentController> controller;
    GetController(Local<panda::ObjectRef>(localRef)->GetNativePointerField(vm, 0), &controller);
    return controller;
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
    if (!nodePtr->IsNativePointer(vm)) {
        return XComponentControllerErrorCode::XCOMPONENT_CONTROLLER_BAD_PARAMETER;
    }
    return ChangeSurfaceCallbackMode(nodePtr->ToNativePointer(vm)->Value(), static_cast<char>(mode));
}

XComponentControllerErrorCode XComponentController::SetRenderFitBySurfaceId(
    const std::string& surfaceId, int32_t renderFitNumber, bool isRenderFitNewVersionEnabled)
{
    static SetRenderFitFunc setRenderFitMethod = nullptr;
    if (setRenderFitMethod == nullptr) {
        LIBHANDLE handle = LOADLIB(AceForwardCompatibility::GetAceLibName());
        if (handle == nullptr) {
            return XComponentControllerErrorCode::XCOMPONENT_CONTROLLER_LOAD_LIB_FAILED;
        }
        setRenderFitMethod = reinterpret_cast<SetRenderFitFunc>(
            LOADSYM(handle, XCOMPONENT_SET_RENDER_FIT_FUNC));
        if (setRenderFitMethod == nullptr) {
            FREELIB(handle);
            return XComponentControllerErrorCode::XCOMPONENT_CONTROLLER_LOAD_LIB_FAILED;
        }
    }
    return setRenderFitMethod(surfaceId, renderFitNumber, isRenderFitNewVersionEnabled);
}

XComponentControllerErrorCode XComponentController::GetRenderFitBySurfaceId(
    const std::string& surfaceId, int32_t& renderFitNumber, bool& isRenderFitNewVersionEnabled)
{
    static GetRenderFitFunc getRenderFitMethod = nullptr;
    if (getRenderFitMethod == nullptr) {
        LIBHANDLE handle = LOADLIB(AceForwardCompatibility::GetAceLibName());
        if (handle == nullptr) {
            return XComponentControllerErrorCode::XCOMPONENT_CONTROLLER_LOAD_LIB_FAILED;
        }
        getRenderFitMethod = reinterpret_cast<GetRenderFitFunc>(
            LOADSYM(handle, XCOMPONENT_GET_RENDER_FIT_FUNC));
        if (getRenderFitMethod == nullptr) {
            FREELIB(handle);
            return XComponentControllerErrorCode::XCOMPONENT_CONTROLLER_LOAD_LIB_FAILED;
        }
    }
    return getRenderFitMethod(surfaceId, renderFitNumber, isRenderFitNewVersionEnabled);
}
} // namespace OHOS::Ace
