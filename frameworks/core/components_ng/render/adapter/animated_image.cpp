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

#include "core/components_ng/render/adapter/animated_image.h"

#include <mutex>

#include "core/animation/animator.h"
#include "core/animation/picture_animation.h"
#include "core/components_ng/image_provider/adapter/skia_image_data.h"
#include "core/components_ng/image_provider/image_utils.h"
#include "core/image/flutter_image_cache.h"
#include "core/pipeline_ng/pipeline_context.h"
namespace OHOS::Ace::NG {
namespace {
constexpr int32_t STANDARD_FRAME_DURATION = 100;
constexpr int32_t FORM_REPEAT_COUNT = 1;
} // namespace

AnimatedImage::AnimatedImage(std::unique_ptr<SkCodec> codec, const SizeF& size, const std::string& url)
    : SkiaCanvasImage(nullptr), codec_(std::move(codec)), cacheKey_(url + size.ToString()), size_(size)
{
    // set up animator
    int32_t totalDuration = 0;
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    animator_ = MakeRefPtr<Animator>(pipelineContext);
    CHECK_NULL_VOID(animator_);

    auto info = codec_->getFrameInfo();
    for (int32_t i = 0; i < codec_->getFrameCount(); ++i) {
        if (info[i].fDuration <= 0) {
            info[i].fDuration = STANDARD_FRAME_DURATION;
        }
        totalDuration += info[i].fDuration;
    }
    animator_->SetDuration(totalDuration);
    animator_->SetIteration(codec_->getRepetitionCount());
    if (pipelineContext->IsFormRender() && animator_->GetIteration() != 0) {
        animator_->SetIteration(FORM_REPEAT_COUNT);
    }

    // initialize PictureAnimation interpolator
    auto picAnimation = MakeRefPtr<PictureAnimation<uint32_t>>();
    CHECK_NULL_VOID(picAnimation);
    for (int32_t i = 0; i < codec_->getFrameCount(); ++i) {
        picAnimation->AddPicture(static_cast<float>(info[i].fDuration) / totalDuration, i);
    }
    picAnimation->AddListener([weak = WeakClaim(this)](const uint32_t idx) {
        auto self = weak.Upgrade();
        CHECK_NULL_VOID(self);
        self->RenderFrame(idx);
    });
    animator_->AddInterpolator(picAnimation);

    LOGD("animated image setup: duration = %{public}d", totalDuration);
    animator_->Play();
}

sk_sp<SkImage> AnimatedImage::GetCanvasImage() const
{
    return currentFrame_;
}

RefPtr<CanvasImage> AnimatedImage::Create(const RefPtr<ImageData>& data, const SizeF& size, const std::string& url)
{
    auto skData = DynamicCast<SkiaImageData>(data);
    CHECK_NULL_RETURN(skData, nullptr);
    auto codec = SkCodec::MakeFromData(skData->GetSkData());
    CHECK_NULL_RETURN(codec, nullptr);
    return MakeRefPtr<AnimatedImage>(std::move(codec), size, url);
}

void AnimatedImage::RenderFrame(uint32_t idx)
{
    if (!GetCachedFrame(idx)) {
        auto task = [weak = WeakClaim(this), idx] {
            auto self = weak.Upgrade();
            CHECK_NULL_VOID(self);
            self->DecodeFrame(idx);
        };
        ImageUtils::PostToBg(std::move(task));
        return;
    }
    CHECK_NULL_VOID(redraw_);
    redraw_();
}

// Background thread
void AnimatedImage::DecodeFrame(uint32_t idx)
{
    ACE_SCOPED_TRACE("decode frame %d", idx);
    std::scoped_lock<std::mutex> lock(decodeMtx_);

    SkImageInfo imageInfo = codec_->getInfo();
    imageInfo.makeWH(size_.Width(), size_.Height());

    SkBitmap bitmap;

    SkCodec::Options options;
    options.fFrameIndex = idx;

    SkCodec::FrameInfo info {};
    codec_->getFrameInfo(idx, &info);
    if (info.fRequiredFrame != SkCodec::kNoFrame) {
        // frame requires a previous frame as background layer
        options.fPriorFrame = info.fRequiredFrame;
        bitmap = requiredFrame_;
    } else {
        // create from empty layer
        bitmap.allocPixels(imageInfo);
    }

    // decode pixels from codec
    auto res = codec_->getPixels(imageInfo, bitmap.getPixels(), bitmap.rowBytes(), &options);
    CHECK_NULL_VOID(res == SkCodec::kSuccess);

    // next frame will be drawn on top of this one
    if (info.fDisposalMethod != SkCodecAnimation::DisposalMethod::kRestorePrevious) {
        requiredFrame_ = bitmap;
    }

    // save current frame, notify redraw
    currentFrame_ = SkImage::MakeFromBitmap(bitmap);
    ImageUtils::PostToUI([weak = WeakClaim(this)] {
        auto self = weak.Upgrade();
        CHECK_NULL_VOID(self && self->redraw_);
        self->redraw_();
    });

    CacheFrame(idx);
}

void AnimatedImage::ControlAnimation(bool play)
{
    (play) ? animator_->Play() : animator_->Pause();
}

void AnimatedImage::CacheFrame(uint32_t idx)
{
    auto ctx = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(ctx);
    auto cache = ctx->GetImageCache();
    CHECK_NULL_VOID(cache);
    cache->CacheImageNG(cacheKey_ + std::to_string(idx), std::make_shared<CachedImage>(currentFrame_));
}

bool AnimatedImage::GetCachedFrame(uint32_t idx)
{
    auto ctx = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(ctx, false);
    auto cache = ctx->GetImageCache();
    CHECK_NULL_RETURN(cache, false);
    auto image = cache->GetCacheImageNG(cacheKey_ + std::to_string(idx));
    CHECK_NULL_RETURN_NOLOG(image && image->imagePtr, false);
    currentFrame_ = image->imagePtr;
    LOGD("frame cache found src = %{public}s, frame = %{public}d", cacheKey_.c_str(), idx);
    return true;
}
} // namespace OHOS::Ace::NG
