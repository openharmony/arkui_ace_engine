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

#include "image_object.h"

#ifdef USE_ROSEN_DRAWING
#include "drawing/engine_adapter/skia_adapter/skia_data.h"
#endif

namespace OHOS::Ace {
class AnimatedImageObject : public ImageObject {
    DECLARE_ACE_TYPE(AnimatedImageObject, ImageObject);
public:
#ifndef USE_ROSEN_DRAWING
    AnimatedImageObject(
        ImageSourceInfo source,
        const Size& imageSize,
        int32_t frameCount,
        const sk_sp<SkData>& data)
        : ImageObject(source, imageSize, frameCount), skData_(data)
    {}
#else
    AnimatedImageObject(
        ImageSourceInfo source,
        const Size& imageSize,
        int32_t frameCount,
        const std::shared_ptr<RSData>& data)
        : ImageObject(source, imageSize, frameCount), drawingData_(data)
    {}
#endif

    ~AnimatedImageObject() override = default;

    void UploadToGpuForRender(
        const WeakPtr<PipelineBase>& context,
        const UploadSuccessCallback& successCallback,
        const FailedCallback& failedCallback,
        const Size& imageSize,
        bool forceResize,
        bool syncMode = false) override;

    void Pause() override
    {
        if (animatedPlayer_) {
            LOGI("animatied image Paused");
            animatedPlayer_->Pause();
        }
    }

    void Resume() override
    {
        if (animatedPlayer_) {
            LOGI("animatied image Resume");
            animatedPlayer_->Resume();
        }
    }

    void ClearData() override
    {
#ifndef USE_ROSEN_DRAWING
        skData_ = nullptr;
#else
        drawingData_ = nullptr;
#endif
    }

    RefPtr<ImageObject> Clone() override
    {
#ifndef USE_ROSEN_DRAWING
        return MakeRefPtr<AnimatedImageObject>(imageSource_, imageSize_, frameCount_, skData_);
#else
        return MakeRefPtr<AnimatedImageObject>(imageSource_, imageSize_, frameCount_, drawingData_);
#endif
    }

private:
#ifndef USE_ROSEN_DRAWING
    sk_sp<SkData> skData_;
#else
    std::shared_ptr<RSData> drawingData_;
#endif
    RefPtr<AnimatedImagePlayer> animatedPlayer_;
};

void AnimatedImageObject::UploadToGpuForRender(
    const WeakPtr<PipelineBase>& context,
    const UploadSuccessCallback& successCallback,
    const FailedCallback& failedCallback,
    const Size& imageSize,
    bool forceResize,
    bool syncMode)
{
    constexpr float SizeOffset = 0.5f;
#ifndef USE_ROSEN_DRAWING
    if (!animatedPlayer_ && skData_) {
        auto codec = SkCodec::MakeFromData(skData_);
#else
    if (!animatedPlayer_ && drawingData_) {
        auto skData = SkData::MakeWithoutCopy(drawingData_->GetData(), drawingData_->GetSize());
        auto codec = SkCodec::MakeFromData(skData);
#endif
        int32_t dstWidth = -1;
        int32_t dstHeight = -1;
        if (forceResize) {
            dstWidth = static_cast<int32_t>(imageSize.Width() + SizeOffset);
            dstHeight = static_cast<int32_t>(imageSize.Height() + SizeOffset);
        }
        animatedPlayer_ = MakeRefPtr<AnimatedImagePlayer>(
            imageSource_,
            successCallback,
            context,
            std::move(codec),
            dstWidth,
            dstHeight);
        ClearData();
    } else if (animatedPlayer_ && forceResize && imageSize.IsValid()) {
        LOGI("animated player has been constructed, forceResize: %{private}s", imageSize.ToString().c_str());
        int32_t dstWidth = static_cast<int32_t>(imageSize.Width() + SizeOffset);
        int32_t dstHeight = static_cast<int32_t>(imageSize.Height() + SizeOffset);
        animatedPlayer_->SetTargetSize(dstWidth, dstHeight);
#ifndef USE_ROSEN_DRAWING
    } else if (!animatedPlayer_ && !skData_) {
#else
    } else if (!animatedPlayer_ && !drawingData_) {
#endif
        LOGE("animated player is not constructed and image data is null, can not construct animated player!");
    } else if (animatedPlayer_ && !forceResize) {
        LOGI("animated player has been constructed, do nothing!");
    }
}

#ifndef USE_ROSEN_DRAWING
RefPtr<ImageObject> CreateAnimatedImageObject(ImageSourceInfo source, const Size& imageSize, int32_t frameCount,
    const sk_sp<SkData>& data)
#else
RefPtr<ImageObject> CreateAnimatedImageObject(ImageSourceInfo source, const Size& imageSize, int32_t frameCount,
    const std::shared_ptr<RSData>& data)
#endif
{
    return Referenced::MakeRefPtr<AnimatedImageObject>(source, imageSize, frameCount, data);
}
}