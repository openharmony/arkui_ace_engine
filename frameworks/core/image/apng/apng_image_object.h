/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_IMAGE_APNG_APNG_IMAGE_OBJECT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_IMAGE_APNG_APNG_IMAGE_OBJECT_H

#include "core/image/image_object.h"
#include "apng_image_player.h"

namespace OHOS::Ace {
class ApngImageObject : public ImageObject {
    DECLARE_ACE_TYPE(ApngImageObject, ImageObject);
public:
    using CancelableTask = CancelableCallback<void()>;

    ApngImageObject(
        ImageSourceInfo source,
        const Size& imageSize,
        int32_t frameCount,
        const std::shared_ptr<RSData>& data,
        const RefPtr<PNGImageDecoder>& decoder)
        : ImageObject(source, imageSize, frameCount), drawingData_(data)
    {
        drawingData_ = data;
        apngDecoder_ = decoder;
    }

    void UploadToGpuForRender(
        const WeakPtr<PipelineBase>& context,
        const UploadSuccessCallback& successCallback,
        const FailedCallback& failedCallback,
        const Size& imageSize,
        bool forceResize,
        bool syncMode = false) override;

    bool IsApng();

    void Pause() override
    {
        if (animatedPlayer_) {
            LOGI("animated image Paused");
            animatedPlayer_->Pause();
        }
    }

    void Resume() override
    {
        if (animatedPlayer_) {
            LOGI("animated image Resume");
            animatedPlayer_->Resume();
        }
    }

    void ClearData() override
    {
        skData_ = nullptr;
    }

    RefPtr<ImageObject> Clone() override
    {
        return MakeRefPtr<ApngImageObject>(imageSource_, imageSize_, frameCount_, skData_, apngDecoder_);
    }

private:
    std::shared_ptr<RSData> drawingData_;
    RefPtr<APngImagePlayer> animatedPlayer_;
    RefPtr<PNGImageDecoder> apngDecoder_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_IMAGE_APNG_APNG_IMAGE_OBJECT_H
