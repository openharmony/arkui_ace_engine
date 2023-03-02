/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/image/apng/apng_image_object.h"
#include "core/image/apng/apng_image_decoder.h"

namespace OHOS::Ace {
void ApngImageObject::UploadToGpuForRender(
    const WeakPtr<PipelineBase>& context,
    const UploadSuccessCallback& successCallback,
    const FailedCallback& failedCallback,
    const Size& imageSize,
    bool forceResize,
    bool syncMode)
{
    constexpr float SizeOffset = 0.5f;

    if (!animatedPlayer_ && skData_) {
        int32_t dstWidth = -1;
        int32_t dstHeight = -1;
        if (forceResize) {
            dstWidth = static_cast<int32_t>(imageSize.Width() + SizeOffset);
            dstHeight = static_cast<int32_t>(imageSize.Height() + SizeOffset);
        }

        animatedPlayer_ = MakeRefPtr<APngImagePlayer>(
                imageSource_,
                successCallback,
                context,
                apngDecoder_,
                dstWidth,
                dstHeight);
        ClearData();
    } else if (animatedPlayer_ && forceResize && imageSize.IsValid()) {
        LOGI("apng image player has been constructed, forceResize: %{public}s", imageSize.ToString().c_str());
        int32_t dstWidth = static_cast<int32_t>(imageSize.Width() + SizeOffset);
        int32_t dstHeight = static_cast<int32_t>(imageSize.Height() + SizeOffset);
        animatedPlayer_->SetTargetSize(dstWidth, dstHeight);
    } else if (!animatedPlayer_ && !skData_) {
        LOGE("apng image player is not constructed and image data is null, can not construct animated player!");
    } else if (animatedPlayer_ && !forceResize) {
        LOGI("apng image player has been constructed, do nothing!");
    }
}

bool ApngImageObject::IsApng()
{
    if (skData_ && apngDecoder_) {
        return apngDecoder_->isApng();
    }
    return false;
}
} // namespace OHOS::Ace