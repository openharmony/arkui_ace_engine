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

#include <cstddef>

#include "cj_lambda.h"

#include "bridge/declarative_frontend/jsview/models/xcomponent_model_impl.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_controller_ng.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_model.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_model_ng.h"
#include "frameworks/core/components_ng/pattern/xcomponent/xcomponent_pattern.h"

using namespace OHOS::Ace;
using namespace OHOS::FFI;
using namespace OHOS::Ace::NG;
using namespace OHOS::Ace::Framework;

namespace OHOS::Ace {
XComponentModel* XComponentModel::GetInstance()
{
#ifdef NG_BUILD
    static NG::XComponentModelNG instance;
    return &instance;
#else
    if (Container::IsCurrentUseNewPipeline()) {
        static NG::XComponentModelNG instance;
        return &instance;
    } else {
        static Framework::XComponentModelImpl instance;
        return &instance;
    }
#endif
}
} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {
NativeXComponentController::NativeXComponentController() : FFIData()
{
    auto controller = std::make_shared<NG::XComponentControllerNG>();
    CHECK_NULL_VOID(controller);
    SetController(controller);
    LOGI("Native XComponent Controller constructed: %{public}" PRId64, GetID());
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

    XComponentModel::GetInstance()->Create(
        id, static_cast<XComponentType>(xcomponentType), libraryName, controller->GetInnerController());
    XComponentModel::GetInstance()->SetSoPath(libraryName);
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