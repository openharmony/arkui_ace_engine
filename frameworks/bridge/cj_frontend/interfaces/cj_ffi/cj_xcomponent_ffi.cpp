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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_xcomponent_ffi.h"
#include "bridge/cj_frontend/runtime/cj_runtime_delegate.h"

#include <cstddef>

#include "base/utils/string_utils.h"
#include "cj_lambda.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_controller_ng.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_model.h"

using namespace OHOS::Ace;
using namespace OHOS::FFI;
using namespace OHOS::Ace::NG;
using namespace OHOS::Ace::Framework;

namespace OHOS::Ace::Framework {
NativeXComponentController::NativeXComponentController() : FFIData()
{
    auto controller = std::make_shared<NG::XComponentControllerNG>();
    CHECK_NULL_VOID(controller);
    SetController(controller);
    LOGI("Native XComponent Controller constructed: %{public}" PRId64, GetID());
}

void NativeXComponentController::SetXComponentControllerOnCreated(
    const WeakPtr<NG::FrameNode>& targetNode, int64_t controllerId)
{
    LOGI("SetXComponentControllerOnCreated: %{public}" PRId64, controllerId);
    auto onSurfaceCreated = [remoteId = controllerId, node = targetNode](
                                const std::string& surfaceId, const std::string& xcomponentId) {
        PipelineContext::SetCallBackNode(node);
        LOGI("CJ XComponent[%{public}s] ControllerOnCreated surfaceId:%{public}s",
            xcomponentId.c_str(), surfaceId.c_str());
        auto func = CJRuntimeDelegate::GetInstance()->GetCJXcompCtrFuncs().atCXComponentControllerOnSurfaceCreated;
        if (!func) {
            LOGE("CJXcompCtr: OnSurfaceCreated is empty.");
            return;
        }
        auto surfaceIdLongInt = StringUtils::StringToLongInt(surfaceId);
        if (surfaceIdLongInt == 0) {
            LOGE("surfaceId is not a long int.");
            return;
        }
        func(remoteId, surfaceIdLongInt);
    };
    XComponentModel::GetInstance()->SetControllerOnCreated(std::move(onSurfaceCreated));
}

void NativeXComponentController::SetXComponentControllerOnChanged(
    const WeakPtr<NG::FrameNode>& targetNode, int64_t controllerId)
{
    LOGI("SetXComponentControllerOnChanged: %{public}" PRId64, controllerId);
    auto onSurfaceChanged = [remoteId = controllerId, node = targetNode](
                                const std::string& surfaceId, const NG::RectF& rect) {
        PipelineContext::SetCallBackNode(node);
        LOGI("CJ XComponent ControllerOnChanged surfaceId:%{public}s", surfaceId.c_str());
        auto func = CJRuntimeDelegate::GetInstance()->GetCJXcompCtrFuncs().atCXComponentControllerOnSurfaceChanged;
        if (!func) {
            LOGE("CJXcompCtr: OnSurfaceChanged is empty.");
            return;
        }
        CJRectResult rectRes { rect.Left(), rect.Top(), rect.Width(), rect.Height() };
        auto surfaceIdLongInt = StringUtils::StringToLongInt(surfaceId);
        if (surfaceIdLongInt == 0) {
            LOGE("surfaceId is not a long int.");
            return;
        }
        func(remoteId, surfaceIdLongInt, rectRes);
    };
    XComponentModel::GetInstance()->SetControllerOnChanged(std::move(onSurfaceChanged));
}

void NativeXComponentController::SetXComponentControllerOnDestroyed(
    const WeakPtr<NG::FrameNode>& targetNode, int64_t controllerId)
{
    LOGI("SetXComponentControllerOnDestroyed: %{public}" PRId64, controllerId);
    auto onSurfaceDestroyed = [remoteId = controllerId, node = targetNode](
                                const std::string& surfaceId, const std::string& xcomponentId) {
        PipelineContext::SetCallBackNode(node);
        LOGI("CJ XComponent[%{public}s] ControllerOnDestroyed surfaceId:%{public}s",
            xcomponentId.c_str(), surfaceId.c_str());
        auto func = CJRuntimeDelegate::GetInstance()->GetCJXcompCtrFuncs().atCXComponentControllerOnSurfaceDestroyed;
        if (!func) {
            LOGE("CJXcompCtr: OnSurfaceDestroyed is empty.");
            return;
        }
        auto surfaceIdLongInt = StringUtils::StringToLongInt(surfaceId);
        if (surfaceIdLongInt == 0) {
            LOGE("surfaceId is not a long int.");
            return;
        }
        func(remoteId, surfaceIdLongInt);
    };
    XComponentModel::GetInstance()->SetControllerOnDestroyed(std::move(onSurfaceDestroyed));
}

void NativeXComponentController::SetXComponentControllerCallback(int64_t controllerId)
{
    LOGI("SetXComponentControllerCallback start");
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    SetXComponentControllerOnCreated(targetNode, controllerId);
    SetXComponentControllerOnChanged(targetNode, controllerId);
    SetXComponentControllerOnDestroyed(targetNode, controllerId);
    LOGI("SetXComponentControllerCallback end");
}

void NativeXComponentController::SetController(const std::shared_ptr<InnerXComponentController>& controller)
{
    controller_ = controller;
}

std::string NativeXComponentController::GetSurfaceId()
{
    return controller_->GetSurfaceId();
}

void NativeXComponentController::SetSurfaceId(const std::string& surfaceId)
{
    CHECK_NULL_VOID(controller_);
    controller_->SetSurfaceId(surfaceId);
}

void NativeXComponentController::SetSurfaceRect(float offsetX, float offsetY, float surfaceWidth, float surfaceHeight)
{
    CHECK_NULL_VOID(controller_);
    controller_->SetIdealSurfaceWidth(surfaceWidth);
    controller_->SetIdealSurfaceHeight(surfaceHeight);
    controller_->SetIdealSurfaceOffsetX(offsetX);
    controller_->SetIdealSurfaceOffsetY(offsetY);
    controller_->UpdateSurfaceBounds();
}

void NativeXComponentController::GetSurfaceOffset(float& offsetX, float& offsetY)
{
    CHECK_NULL_VOID(controller_);
    controller_->GetSurfaceOffset(offsetX, offsetY);
}

void NativeXComponentController::GetSurfaceSize(float& surfaceWidth, float& surfaceHeight)
{
    CHECK_NULL_VOID(controller_);
    controller_->GetSurfaceSize(surfaceWidth, surfaceHeight);
}

void NativeXComponentController::SetIdealSurfaceWidth(float surfaceWidth)
{
    CHECK_NULL_VOID(controller_);
    controller_->SetIdealSurfaceWidth(surfaceWidth);
}
void NativeXComponentController::SetIdealSurfaceHeight(float surfaceHeight)
{
    CHECK_NULL_VOID(controller_);
    controller_->SetIdealSurfaceHeight(surfaceHeight);
}

void NativeXComponentController::SetIdealSurfaceOffsetX(float offsetX)
{
    CHECK_NULL_VOID(controller_);
    controller_->SetIdealSurfaceOffsetX(offsetX);
}

void NativeXComponentController::SetIdealSurfaceOffsetY(float offsetY)
{
    CHECK_NULL_VOID(controller_);
    controller_->SetIdealSurfaceOffsetY(offsetY);
}

void NativeXComponentController::ClearIdealSurfaceOffset(bool isXAxis)
{
    CHECK_NULL_VOID(controller_);
    controller_->ClearIdealSurfaceOffset(isXAxis);
}

void NativeXComponentController::UpdateSurfaceBounds()
{
    CHECK_NULL_VOID(controller_);
    controller_->UpdateSurfaceBounds();
}

void NativeXComponentController::SetSurfaceRotation(bool isLock)
{
    CHECK_NULL_VOID(controller_);
    controller_->SetSurfaceRotation(isLock);
}

bool NativeXComponentController::GetSurfaceRotation()
{
    CHECK_NULL_RETURN(controller_, false);
    return controller_->GetSurfaceRotation();
}

std::shared_ptr<InnerXComponentController> NativeXComponentController::GetInnerController()
{
    return controller_;
}
} // namespace OHOS::Ace::Framework

extern "C" {
int64_t FfiOHOSAceFrameworkXComponentControllerCtor()
{
    auto controller = FFIData::Create<NativeXComponentController>();
    if (controller == nullptr) {
        return FFI_ERROR_CODE;
    }
    return controller->GetID();
}

void FfiOHOSAceFrameworkXComponentCreate(
    const char* id, int32_t xcomponentType, const char* libraryName, int64_t controllerId)
{
    auto controller = FFIData::GetData<NativeXComponentController>(controllerId);
    CHECK_NULL_VOID(controller->GetInnerController());
    std::optional<std::string> libraryNameOpt = std::nullopt;

    XComponentModel::GetInstance()->Create(
        id, static_cast<XComponentType>(xcomponentType), libraryNameOpt, controller->GetInnerController());
    controller->SetXComponentControllerCallback(controller->GetID());
}

const char* FfiOHOSAceFrameworkXComponentControllerGetSurfaceId(int64_t selfID)
{
    auto self = FFIData::GetData<NativeXComponentController>(selfID);
    std::string surfaceId = self->GetSurfaceId();
    char* result = strdup(surfaceId.c_str());
    return result;
}

void FfiOHOSAceFrameworkXComponentControllerSetSurfaceId(int64_t selfID, const char* surfaceId)
{
    auto self = FFIData::GetData<NativeXComponentController>(selfID);
    CHECK_NULL_VOID(self);
    self->SetSurfaceId(surfaceId);
}

void FfiOHOSAceFrameworkXComponentControllerSetSurfaceRotation(int64_t selfID, bool isLock)
{
    auto self = FFIData::GetData<NativeXComponentController>(selfID);
    CHECK_NULL_VOID(self);
    self->SetSurfaceRotation(isLock);
}

bool FfiOHOSAceFrameworkXComponentControllerGetSurfaceRotation(int64_t selfID)
{
    auto self = FFIData::GetData<NativeXComponentController>(selfID);
    return self->GetSurfaceRotation();
}

void FfiOHOSAceFrameworkXComponentEnableSecure(bool isSecure)
{
    auto type = XComponentModel::GetInstance()->GetType();
    if (type != XComponentType::SURFACE) {
        return;
    }
    XComponentModel::GetInstance()->EnableSecure(isSecure);
}

void FfiOHOSAceFrameworkXComponentOnLoad(void (*callback)(const char* surfaceId)) {}

void FfiOHOSAceFrameworkXComponentOnDestroy(void (*callback)(const char* surfaceId)) {}

void FfiOHOSAceFrameworkXComponentGetContext(void (*callback)(const char* surfaceId)) {}

void FfiOHOSAceFrameworkXComponentOnSurfaceCreated(const char* surfaceId) {}

void FfiOHOSAceFrameworkXComponentOnSurfaceChanged(const char* surfaceId, SurfaceRect rect) {}

void FfiOHOSAceFrameworkXComponentOnSurfaceDestroyed(const char* surfaceId) {}

void FfiOHOSAceFrameworkXComponentSetSurfaceRect(
    int64_t selfID, float offsetX, float offsetY, float surfaceWidth, float surfaceHeight)
{
    auto self = FFIData::GetData<NativeXComponentController>(selfID);
    CHECK_NULL_VOID(self);
    self->SetSurfaceRect(offsetX, offsetY, surfaceWidth, surfaceHeight);
}

SurfaceRect FfiOHOSAceFrameworkXComponentGetSurfaceRect(int64_t selfID)
{
    float offsetX = 0.0f;
    float offsetY = 0.0f;
    float width = 0.0f;
    float height = 0.0f;
    auto self = FFIData::GetData<NativeXComponentController>(selfID);
    self->GetSurfaceOffset(offsetX, offsetY);
    self->GetSurfaceSize(width, height);
    SurfaceRect rect { offsetX, offsetY, width, height };
    return rect;
}
}