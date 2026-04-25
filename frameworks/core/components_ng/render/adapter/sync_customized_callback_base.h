/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_SYNC_CUSTOMIZED_CALLBACK_BASE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_SYNC_CUSTOMIZED_CALLBACK_BASE_H

#include <chrono>
#include <condition_variable>
#include <mutex>

#include "base/error/error_code.h"
#include "base/log/log_wrapper.h"
#include "core/components_ng/base/inspector.h"
#include "core/components_ng/render/adapter/component_snapshot.h"
#include "transaction/rs_interfaces.h"

namespace OHOS::Ace::NG {

class SyncCustomizedCallbackBase : public Rosen::SurfaceCaptureCallback {
public:
    SyncCustomizedCallbackBase() = default;
    ~SyncCustomizedCallbackBase() override = default;

    void OnSurfaceCapture(std::shared_ptr<Media::PixelMap> pixelMap) override
    {
        OnSurfaceCaptureWithErrorCode(pixelMap, nullptr, Rosen::CaptureError::CAPTURE_OK);
    }

    void OnSurfaceCaptureHDR(
        std::shared_ptr<Media::PixelMap> pixelMap, std::shared_ptr<Media::PixelMap> hdrPixelMap) override {}

    void OnSurfaceCaptureWithErrorCode(std::shared_ptr<Media::PixelMap> pixelMap,
        std::shared_ptr<Media::PixelMap> pixelMapHDR, Rosen::CaptureError captureErrorCode) override
    {
        errorCode_ = ERROR_CODE_NO_ERROR;
        pixelMap_ = nullptr;

        switch (captureErrorCode) {
            case Rosen::CaptureError::CAPTURE_NO_PERMISSION:
                TAG_LOGW(AceLogTag::ACE_COMPONENT_SNAPSHOT,
                    "Permission verification failed. A non-system application calls a system API.");
                errorCode_ = ERROR_CODE_VERIFICATION_FAILED;
                break;
            case Rosen::CaptureError::CAPTURE_NO_SECURE_PERMISSION:
                TAG_LOGW(
                    AceLogTag::ACE_COMPONENT_SNAPSHOT, "Taking screenshots of other processes, nodes is not allowed.");
                errorCode_ = ERROR_CODE_INTERNAL_ERROR;
                break;
            case Rosen::CaptureError::CAPTURE_NO_NODE:
                TAG_LOGW(AceLogTag::ACE_COMPONENT_SNAPSHOT, "The specified node to capture does not exist.");
                errorCode_ = ERROR_CODE_INTERNAL_ERROR;
                break;
            case Rosen::CaptureError::CAPTURE_CONFIG_WRONG:
                TAG_LOGW(AceLogTag::ACE_COMPONENT_SNAPSHOT, "The capture configuration is invalid.");
                errorCode_ = ERROR_CODE_INTERNAL_ERROR;
                break;
            case Rosen::CaptureError::CAPTURE_PIXELMAP_NULL:
                TAG_LOGW(AceLogTag::ACE_COMPONENT_SNAPSHOT, "The capture pixelmap is null.");
                errorCode_ = ERROR_CODE_INTERNAL_ERROR;
                break;
            case Rosen::CaptureError::CAPTURE_PIXELMAP_COPY_ERROR:
                TAG_LOGW(AceLogTag::ACE_COMPONENT_SNAPSHOT, "Failed to copy pixel data to pixelmap.");
                errorCode_ = ERROR_CODE_INTERNAL_ERROR;
                break;
            case Rosen::CaptureError::CAPTURE_NULL_FAIL:
                TAG_LOGW(AceLogTag::ACE_COMPONENT_SNAPSHOT, "The capture handle is null.");
                errorCode_ = ERROR_CODE_INTERNAL_ERROR;
                break;
            case Rosen::CaptureError::HDR_SET_FAIL:
                TAG_LOGW(AceLogTag::ACE_COMPONENT_SNAPSHOT, "Failed to set HDR parameters.");
                errorCode_ = ERROR_CODE_INTERNAL_ERROR;
                break;

            case Rosen::CaptureError::AUTO_NOT_SUPPORT:
                TAG_LOGW(AceLogTag::ACE_COMPONENT_SNAPSHOT, "The isAuto parameter of the color space or dynamic range "
                                                            "mode is set to true for offscreen node snapshot.");
                errorCode_ = ERROR_CODE_COMPONENT_SNAPSHOT_AUTO_NOT_SUPPORTED;
                break;

            case Rosen::CaptureError::COLOR_SPACE_NOT_SUPPORT:
                TAG_LOGW(AceLogTag::ACE_COMPONENT_SNAPSHOT, "The provided color space is not supported.");
                errorCode_ = ERROR_CODE_COMPONENT_SNAPSHOT_MODE_NOT_SUPPORTED;
                break;
            case Rosen::CaptureError::DYNAMIC_RANGE_NOT_SUPPORT:
                TAG_LOGW(AceLogTag::ACE_COMPONENT_SNAPSHOT, "The provided dynamic range mode is not supported.");
                errorCode_ = ERROR_CODE_COMPONENT_SNAPSHOT_MODE_NOT_SUPPORTED;
                break;

            case Rosen::CaptureError::CAPTURE_OK:
                if (!pixelMap) {
                    TAG_LOGW(AceLogTag::ACE_COMPONENT_SNAPSHOT, "ComponentSnapshotSync Internal error! "
                                                                "The pixelmap returned by the system is null");
                    errorCode_ = ERROR_CODE_INTERNAL_ERROR;
                } else {
                    TAG_LOGI(AceLogTag::ACE_COMPONENT_SNAPSHOT,
                        "ComponentSnapshotSync successful! pixelMap.width=%{public}d pixelMap.height=%{public}d",
                        pixelMap->GetWidth(), pixelMap->GetHeight());
                    pixelMap_ = pixelMap;
                }
                break;

            default:
                TAG_LOGW(AceLogTag::ACE_COMPONENT_SNAPSHOT, "Unknown capture error.");
                errorCode_ = ERROR_CODE_INTERNAL_ERROR;
                break;
        }

        std::unique_lock<std::mutex> lock(mutex_);
        cv_.notify_all();
    }

    virtual std::pair<int32_t, std::shared_ptr<Media::PixelMap>> GetPixelMap(
        std::chrono::duration<int, std::milli> timeout) = 0;

protected:
    mutable std::mutex mutex_;
    std::condition_variable cv_;
    std::shared_ptr<Media::PixelMap> pixelMap_;
    int32_t errorCode_ = ERROR_CODE_NO_ERROR;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_SYNC_CUSTOMIZED_CALLBACK_BASE_H
