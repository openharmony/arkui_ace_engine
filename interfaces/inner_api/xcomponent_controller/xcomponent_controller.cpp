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
#include "utils.h"
#include "ani.h"
#include "xcomponent_controller_log.h"

#include "bridge/declarative_frontend/jsview/js_xcomponent_controller.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_pattern.h"
#include "core/interfaces/native/implementation/frame_node_peer_impl.h"
#include "core/interfaces/native/implementation/x_component_controller_peer_impl.h"

namespace OHOS::Ace {
namespace {
const char* NODEPTR_OF_UINODE = "nodePtr_";
constexpr char XCOMPONENT_GET_CONTROLLER_FUNC[] = "OHOS_ACE_GetXComponentController";
constexpr char XCOMPONENT_CHANGE_SURFACE_CALLBACKMODE_FUNC[] = "OHOS_ACE_ChangeXComponentSurfaceCallbackMode";
constexpr char XCOMPONENT_SET_RENDER_FIT_FUNC[] = "OHOS_ACE_SetRenderFitBySurfaceId";
constexpr char XCOMPONENT_GET_RENDER_FIT_FUNC[] = "OHOS_ACE_GetRenderFitBySurfaceId";
constexpr char XCOMPONENT_GET_SURFACE_ROTATION_FUNC[] = "OHOS_ACE_GetSurfaceRotationBySurfaceId";
using GetControllerFunc = void (*)(void*, void*);
using ChangeSurfaceCallbackModeFunc = XComponentControllerErrorCode (*)(void*, char);
using SetRenderFitFunc = XComponentControllerErrorCode (*)(const std::string&, int32_t, bool);
using GetRenderFitFunc = XComponentControllerErrorCode (*)(const std::string&, int32_t&, bool&);
using GetSurfaceRotationFunc = XComponentControllerErrorCode (*)(const std::string&, bool&);
} // namespace
void GetController(void* jsController, void* controller)
{
    static GetControllerFunc entry = nullptr;
    if (entry == nullptr) {
        LIBHANDLE handle = LOADLIB(AceForwardCompatibility::GetAceLibName());
        CHECK_NULL_VOID(handle);
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
        CHECK_NULL_RETURN(handle, XComponentControllerErrorCode::XCOMPONENT_CONTROLLER_BAD_PARAMETER);
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
    CHECK_NULL_RETURN(env, nullptr);
    const auto* vm = reinterpret_cast<NativeEngine*>(env)->GetEcmaVm();
    auto localRef = NapiValueToLocalValue(napiValue);
    if (localRef->IsNull()) {
        return nullptr;
    }
    std::shared_ptr<XComponentController> controller;
    GetController(Local<panda::ObjectRef>(localRef)->GetNativePointerField(vm, 0), &controller);
    return controller;
}

std::shared_ptr<XComponentController> XComponentController::GetXComponentControllerFromAniValue(
    ani_env* env, ani_object controller)
{
    if (env == nullptr) {
        HILOG_ERROR("XComponentController GetXComponentControllerFromAniValue env is null");
        return nullptr;
    }
    ani_ref ref;
    if (env->Object_GetFieldByName_Ref(controller, "peer", &ref) != ANI_OK) {
        HILOG_ERROR("XComponentController GetXComponentControllerFromAniValue cannot get peer");
        return nullptr;
    }
    ani_object obj = static_cast<ani_object>(ref);
    ani_long ptr;
    auto ret = env->Object_GetFieldByName_Long(obj, "ptr", &ptr);
    if (ret != ANI_OK) {
        HILOG_ERROR("XComponentController GetXComponentControllerFromAniValue cannot get ptr %{public}d", ret);
        return nullptr;
    }
    auto* controllerPeer = reinterpret_cast<NG::GeneratedModifier::XComponentControllerPeerImpl*>(ptr);
    if (controllerPeer == nullptr) {
        HILOG_ERROR("XComponentController GetXComponentControllerFromAniValue controllerPeer is null");
        return nullptr;
    }
    std::shared_ptr<XComponentController> retController = controllerPeer->controller;
    return retController;
}

XComponentControllerErrorCode XComponentController::SetSurfaceCallbackMode(
    napi_env env, napi_value node, SurfaceCallbackMode mode)
{
    CHECK_NULL_RETURN(env, XComponentControllerErrorCode::XCOMPONENT_CONTROLLER_BAD_PARAMETER);
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

XComponentControllerErrorCode XComponentController::SetSurfaceCallbackModeFromAniValue(
    ani_env* env, ani_object node, SurfaceCallbackMode mode)
{
    if (env == nullptr) {
        HILOG_ERROR("XComponentController SetSurfaceCallbackModeFromAniValue env is null");
        return XComponentControllerErrorCode::XCOMPONENT_CONTROLLER_BAD_PARAMETER;
    }
    ani_ref framenodePeerRef;
    if (env->Object_GetFieldByName_Ref(node, "nodePtr_", &framenodePeerRef) != ANI_OK) {
        HILOG_ERROR("XComponentController fail to get nodePtr in node");
        return XComponentControllerErrorCode::XCOMPONENT_CONTROLLER_BAD_PARAMETER;
    }
    ani_object frameNodePeerObj = static_cast<ani_object>(framenodePeerRef);
    ani_class pointerClass;
    env->FindClass("std.core.Long", &pointerClass);
    ani_boolean isPointer;
    ani_status status = env->Object_InstanceOf(frameNodePeerObj, pointerClass, &isPointer);
    if (status != ANI_OK || !isPointer) {
        HILOG_ERROR("XComponentController fail to get frameNodePeerObj value in node");
        return XComponentControllerErrorCode::XCOMPONENT_CONTROLLER_BAD_PARAMETER;
    }
    ani_long frameNodePeerPtr;
    status = env->Object_CallMethodByName_Long(frameNodePeerObj, "toLong", ":l", &frameNodePeerPtr);
    if (status != ANI_OK) {
        HILOG_ERROR("XComponentController fail to unbox frameNodePeerPtr");
        return XComponentControllerErrorCode::XCOMPONENT_CONTROLLER_BAD_PARAMETER;
    }
    auto* frameNodePeer = reinterpret_cast<FrameNodePeer*>(frameNodePeerPtr);
    if (frameNodePeer == nullptr) {
        HILOG_ERROR("XComponentController fail to get frameNodePeer value in builderNode");
        return XComponentControllerErrorCode::XCOMPONENT_CONTROLLER_BAD_PARAMETER;
    }
    OHOS::Ace::NG::FrameNode* frameNode = OHOS::Ace::AceType::RawPtr(frameNodePeer->node);
    return ChangeSurfaceCallbackMode(frameNode, static_cast<char>(mode));
}

XComponentControllerErrorCode XComponentController::SetRenderFitBySurfaceId(
    const std::string& surfaceId, int32_t renderFitNumber, bool isRenderFitNewVersionEnabled)
{
    static SetRenderFitFunc setRenderFitMethod = nullptr;
    if (setRenderFitMethod == nullptr) {
        LIBHANDLE handle = LOADLIB(AceForwardCompatibility::GetAceLibName());
        CHECK_NULL_RETURN(handle, XComponentControllerErrorCode::XCOMPONENT_CONTROLLER_LOAD_LIB_FAILED);
        setRenderFitMethod = reinterpret_cast<SetRenderFitFunc>(LOADSYM(handle, XCOMPONENT_SET_RENDER_FIT_FUNC));
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
        CHECK_NULL_RETURN(handle, XComponentControllerErrorCode::XCOMPONENT_CONTROLLER_LOAD_LIB_FAILED);
        getRenderFitMethod = reinterpret_cast<GetRenderFitFunc>(LOADSYM(handle, XCOMPONENT_GET_RENDER_FIT_FUNC));
        if (getRenderFitMethod == nullptr) {
            FREELIB(handle);
            return XComponentControllerErrorCode::XCOMPONENT_CONTROLLER_LOAD_LIB_FAILED;
        }
    }
    return getRenderFitMethod(surfaceId, renderFitNumber, isRenderFitNewVersionEnabled);
}

XComponentControllerErrorCode XComponentController::GetSurfaceRotationBySurfaceId(
    const std::string& surfaceId, bool& isSurfaceLock)
{
    static GetSurfaceRotationFunc getSurfaceRotationMethod = nullptr;
    if (getSurfaceRotationMethod == nullptr) {
        LIBHANDLE handle = LOADLIB(AceForwardCompatibility::GetAceLibName());
        CHECK_NULL_RETURN(handle, XComponentControllerErrorCode::XCOMPONENT_CONTROLLER_LOAD_LIB_FAILED);
        getSurfaceRotationMethod =
            reinterpret_cast<GetSurfaceRotationFunc>(LOADSYM(handle, XCOMPONENT_GET_SURFACE_ROTATION_FUNC));
        if (getSurfaceRotationMethod == nullptr) {
            FREELIB(handle);
            return XComponentControllerErrorCode::XCOMPONENT_CONTROLLER_LOAD_LIB_FAILED;
        }
    }
    return getSurfaceRotationMethod(surfaceId, isSurfaceLock);
}
} // namespace OHOS::Ace
