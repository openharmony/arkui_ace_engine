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

#ifndef OHOS_ACE_FRAMEWORK_CJ_XCOMPONENT_FFI_H
#define OHOS_ACE_FRAMEWORK_CJ_XCOMPONENT_FFI_H

#include <cstdint>

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_view_abstract_ffi.h"
#include "core/components_ng/pattern/xcomponent/inner_xcomponent_controller.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_pattern.h"

namespace OHOS::Ace::Framework {
class ACE_EXPORT NativeXComponentController : public OHOS::FFI::FFIData {
    DECL_TYPE(NativeXComponentController, OHOS::FFI::FFIData)
public:
    NativeXComponentController();

    std::string GetSurfaceId();
    void SetSurfaceId(const std::string& surfaceId);
    void GetSurfaceSize(float& surfaceWidth, float& surfaceHeight);
    void SetIdealSurfaceWidth(float surfaceWidth);
    void SetIdealSurfaceHeight(float surfaceHeight);
    void SetIdealSurfaceOffsetX(float offsetX);
    void SetIdealSurfaceOffsetY(float offsetY);
    void ClearIdealSurfaceOffset(bool isXAxis);
    void UpdateSurfaceBounds();
    void SetSurfaceRect(float offsetX, float offsetY, float surfaceWidth, float surfaceHeight);
    void StopImageAnalyzer();
    void SetSurfaceRotation(bool isLock);
    bool GetSurfaceRotation();
    void GetSurfaceOffset(float& offsetX, float& offsetY);
    void SetController(const std::shared_ptr<InnerXComponentController>& controller);
    std::shared_ptr<InnerXComponentController> GetInnerController();

private:
    std::shared_ptr<InnerXComponentController> controller_;
};
} // namespace OHOS::Ace::Framework

extern "C" {
struct SurfaceRect {
    float offsetX;
    float offsetY;
    float surfaceWidth;
    float surfaceHeight;
};

CJ_EXPORT void FfiOHOSAceFrameworkXComponentCreate(
    const char* id, int32_t xcomponentType, const char* libraryName, int64_t controllerId);
CJ_EXPORT const char* FfiOHOSAceFrameworkXComponentControllerGetSurfaceId(int64_t selfID);
CJ_EXPORT void FfiOHOSAceFrameworkXComponentControllerSetSurfaceId(int64_t selfID, const char* surfaceId);
CJ_EXPORT void FfiOHOSAceFrameworkXComponentControllerSetSurfaceRotation(int64_t selfID, bool isLock);
CJ_EXPORT bool FfiOHOSAceFrameworkXComponentControllerGetSurfaceRotation(int64_t selfID);
CJ_EXPORT void FfiOHOSAceFrameworkXComponentEnableSecure(bool isSecure);
CJ_EXPORT void FfiOHOSAceFrameworkXComponentSetSurfaceRect(
    int64_t selfID, float offsetX, float offsetY, float surfaceWidth, float surfaceHeight);
CJ_EXPORT SurfaceRect FfiOHOSAceFrameworkXComponentGetSurfaceRect(int64_t selfID);
CJ_EXPORT int64_t FfiOHOSAceFrameworkXComponentControllerCtor();
CJ_EXPORT void FfiOHOSAceFrameworkXComponentOnLoad(void (*Callback)(const char* surfaceId));
CJ_EXPORT void FfiOHOSAceFrameworkXComponentOnDestroy(void (*Callback)(const char* surfaceId));
CJ_EXPORT void FfiOHOSAceFrameworkXComponentGetContext(void (*Callback)(const char* surfaceId));
CJ_EXPORT void FfiOHOSAceFrameworkXComponentOnSurfaceCreated(const char* surfaceId);
CJ_EXPORT void FfiOHOSAceFrameworkXComponentOnSurfaceChanged(const char* surfaceId, SurfaceRect rect);
CJ_EXPORT void FfiOHOSAceFrameworkXComponentOnSurfaceDestroyed(const char* surfaceId);
}

#endif // OHOS_ACE_FRAMEWORK_CJ_PROGRESS_FFI_H