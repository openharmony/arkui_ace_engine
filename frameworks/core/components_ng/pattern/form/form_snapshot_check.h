/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FORM_FORM_CHECK_CALLBACK_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FORM_FORM_CHECK_CALLBACK_H

#include "transaction/rs_render_service_client.h"
#include "base/log/log_wrapper.h"
#include "core/components/form/resource/form_manager_delegate.h"
#include "form_snapshot_util.h"

namespace OHOS::Ace::NG {

class FormSnapshotCheck : public Rosen::SurfaceCaptureCallback {
public:
    explicit FormSnapshotCheck(const WeakPtr<FormManagerDelegate>& delegate) : weakFormDelegate_(delegate) {}
    ~FormSnapshotCheck() override = default;
    void OnSurfaceCapture(std::shared_ptr<Media::PixelMap> pixelMap) override
    {
        if (!pixelMap) {
            TAG_LOGE(AceLogTag::ACE_FORM, "FormSnapshotCheck::OnSurfaceCapture pixelmap is nullptr");
            return;
        }
        auto formManagerBridge = weakFormDelegate_.Upgrade();
        if (!formManagerBridge) {
            TAG_LOGE(AceLogTag::ACE_FORM, "FormSnapshotCheck::OnSurfaceCapture formManagerBridge is nullptr");
            return;
        }
        int32_t ratio = FormSnapshotUtil::GetNonTransparentRatio(pixelMap);
        formManagerBridge->SendNonTransparencyRatio(ratio);
    }
    void OnSurfaceCaptureHDR(
        std::shared_ptr<Media::PixelMap> pixelMap, std::shared_ptr<Media::PixelMap> hdrPixelMap) override
    {}

private:
    WeakPtr<FormManagerDelegate> weakFormDelegate_ = nullptr;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FORM_FORM_CHECK_CALLBACK_H
