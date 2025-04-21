/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

#include "drawing/engine_adapter/skia_adapter/skia_data.h"
#include "drawing/engine_adapter/skia_adapter/skia_image_info.h"

#include "core/components_ng/image_provider/adapter/drawing_image_data.h"

#include "core/components_ng/image_provider/image_utils.h"
#include "core/image/image_cache.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t STANDARD_FRAME_DURATION = 100;
constexpr int32_t FORM_REPEAT_COUNT = 1;
constexpr float RESIZE_THRESHOLD = 0.7f;

struct RSDataWrapper {
    std::shared_ptr<RSData> data;
};

inline void RSDataWrapperReleaseProc(const void*, void* context)
{
    RSDataWrapper* wrapper = reinterpret_cast<RSDataWrapper*>(context);
    delete wrapper;
}
} // namespace

RefPtr<CanvasImage> AnimatedImage::Create(
    const RefPtr<DrawingImageData>& data, const ResizeParam& size, const std::string& url)
{
    CHECK_NULL_RETURN(data, nullptr);
    auto rsData = data->GetRSData();
    CHECK_NULL_RETURN(rsData, nullptr);
    RSDataWrapper* wrapper = new RSDataWrapper { rsData };
    auto skData = SkData::MakeWithProc(rsData->GetData(), rsData->GetSize(), RSDataWrapperReleaseProc, wrapper);
    auto codec = SkCodec::MakeFromData(skData);
    CHECK_NULL_RETURN(codec, nullptr);
    if (SystemProperties::GetImageFrameworkEnabled()) {
        auto src = ImageSource::Create(static_cast<const uint8_t*>(rsData->GetData()), rsData->GetSize());
        CHECK_NULL_RETURN(src, nullptr);
        return MakeRefPtr<AnimatedPixmap>(codec, src, size, url);
    }
    return MakeRefPtr<AnimatedRSImage>(std::move(codec), url);
}

AnimatedImage::AnimatedImage(const std::unique_ptr<SkCodec>& codec, std::string url)
    : cacheKey_(std::move(url)), duration_(GenerateDuration(codec)), iteration_(GenerateIteration(codec))
{}

AnimatedImage::~AnimatedImage() = default;

void AnimatedImage::PostPlayTask(uint32_t idx, int iteration)
{
    if (idx == static_cast<uint32_t>(duration_.size())) {
        iteration--;
        idx = 0;
    }
    if (iteration == 0) {
        animationState_ = false;
        return;
    }
    RenderFrame(idx);
    animationState_ = true;
    currentIdx_ = idx;
    iteration_ = iteration;
    currentTask_.Reset([weak = WeakClaim(this), idx, iteration] {
        auto self = weak.Upgrade();
        CHECK_NULL_VOID(self);
        self->PostPlayTask(idx + 1, iteration);
    });
    ImageUtils::PostDelayedTaskToUI(currentTask_, duration_[idx], "ArkUIImageAnimatedPostPlayTask");
}

std::vector<int> AnimatedImage::GenerateDuration(const std::unique_ptr<SkCodec>& codec)
{
    std::vector<int> duration;
    auto info = codec->getFrameInfo();
    for (int32_t i = 0; i < codec->getFrameCount(); ++i) {
        if (info[i].fDuration <= 0) {
            duration.push_back(STANDARD_FRAME_DURATION);
        } else {
            duration.push_back(info[i].fDuration);
        }
    }
    return duration;
}

int AnimatedImage::GenerateIteration(const std::unique_ptr<SkCodec>& codec)
{
    auto iteration = codec->getRepetitionCount() + 1;
    if (iteration == 0) {
        iteration = INT_MAX;
    }
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipeline, 1);
    if (pipeline->IsFormRenderExceptDynamicComponent()) {
        iteration = FORM_REPEAT_COUNT;
    }
    return iteration;
}

void AnimatedImage::ControlAnimation(bool play)
{
    if (play && !animationState_) {
        PostPlayTask(currentIdx_, iteration_);
        return;
    }
    if (!play && animationState_) {
        auto result = currentTask_.Cancel();
        if (result) {
            animationState_ = false;
        }
    }
}

bool AnimatedImage::GetIsAnimating() const
{
    return animationState_;
}

void AnimatedImage::RenderFrame(uint32_t idx)
{
    if (GetCachedFrame(idx)) {
        return;
    }
    ImageUtils::PostToBg(
        [weak = WeakClaim(this), idx] {
            auto self = weak.Upgrade();
            CHECK_NULL_VOID(self);
            self->DecodeFrame(idx);
        },
        "ArkUIImageRenderAnimatedFrame");
}

// runs on Background threads
void AnimatedImage::DecodeFrame(uint32_t idx)
{
    // max number of decoding thread = 2
    if (queueSize_ >= 2) {
        // skip frame
        return;
    }
    ++queueSize_;

    ACE_SCOPED_TRACE("decode %s frame %d", cacheKey_.c_str(), idx);
    std::scoped_lock<std::mutex> lock(decodeMtx_);
    DecodeImpl(idx);

    ImageUtils::PostToUI(
        [weak = WeakClaim(this)] {
            auto self = weak.Upgrade();
            CHECK_NULL_VOID(self && self->redraw_);
            self->redraw_();
        },
        "ArkUIImageDecodeAnimatedFrame");

    CacheFrame(cacheKey_ + std::to_string(idx));
    --queueSize_;
}

bool AnimatedImage::GetCachedFrame(uint32_t idx)
{
    auto image = GetCachedFrameImpl(cacheKey_ + std::to_string(idx));
    CHECK_NULL_RETURN(image, false);

    if (!decodeMtx_.try_lock()) {
        // last frame still decoding, skip this frame to avoid blocking UI thread
        return true;
    }
    UseCachedFrame(std::move(image));

    decodeMtx_.unlock();

    if (redraw_) {
        redraw_();
    }
    return true;
}

// ----------------------------------------------------------
// AnimatedSkImage implementation
// ----------------------------------------------------------

std::shared_ptr<RSImage> AnimatedRSImage::GetImage() const
{
    std::scoped_lock<std::mutex> lock(frameMtx_);
    return currentFrame_;
}

void AnimatedRSImage::DecodeImpl(uint32_t idx)
{
    SkImageInfo imageInfo = codec_->getInfo();
    RSBitmap bitmap;

    SkCodec::Options options;
    options.fFrameIndex = static_cast<int32_t>(idx);

    SkCodec::FrameInfo info {};
    codec_->getFrameInfo(idx, &info);
    if (info.fRequiredFrame != SkCodec::kNoFrame) {
        // frame requires a previous frame as background layer
        options.fPriorFrame = info.fRequiredFrame;
        bitmap = requiredFrame_;
    } else {
        // create from empty layer
        auto info = Rosen::Drawing::SkiaImageInfo::ConvertToRSImageInfo(imageInfo);
        bitmap.Build(info);
    }

    // decode pixels from codec
    auto res = codec_->getPixels(imageInfo, bitmap.GetPixels(), bitmap.GetRowBytes(), &options);
    CHECK_NULL_VOID(res == SkCodec::kSuccess);

    // next frame will be drawn on top of this one
    if (info.fDisposalMethod != SkCodecAnimation::DisposalMethod::kRestorePrevious) {
        requiredFrame_ = bitmap;
    }

    // save current frame, notify redraw
    {
        std::scoped_lock<std::mutex> lock(frameMtx_);
        currentFrame_ = std::make_shared<RSImage>();
        currentFrame_->BuildFromBitmap(bitmap);
    }
}

void AnimatedRSImage::CacheFrame(const std::string& key)
{
    auto ctx = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(ctx);
    auto cache = ctx->GetImageCache();
    CHECK_NULL_VOID(cache);
    std::shared_ptr<CachedImage> cacheNode;
    {
        std::scoped_lock<std::mutex> lock(frameMtx_);
        cacheNode = std::make_shared<CachedImage>(currentFrame_);
    }
    cache->CacheImage(key, cacheNode);
}

RefPtr<CanvasImage> AnimatedRSImage::GetCachedFrameImpl(const std::string& key)
{
    return DrawingImage::QueryFromCache(key);
}

void AnimatedRSImage::UseCachedFrame(RefPtr<CanvasImage>&& image)
{
    std::scoped_lock<std::mutex> lock(frameMtx_);
    currentFrame_ = DynamicCast<DrawingImage>(image)->GetImage();
}

// ----------------------------------------------------------
// AnimatedPixmap implementation
// ----------------------------------------------------------
AnimatedPixmap::AnimatedPixmap(
    const std::unique_ptr<SkCodec>& codec, const RefPtr<ImageSource>& src, const ResizeParam& size, std::string url)
    : AnimatedImage(codec, std::move(url)), size_(size), src_(src)
{
    // resizing to a size >= 0.7 [~= sqrt(2) / 2] intrinsic size takes 2x longer to decode while memory usage is 1/2.
    // 0.7 is the balance point.
}

RefPtr<PixelMap> AnimatedPixmap::GetPixelMap() const
{
    std::scoped_lock<std::mutex> lock(frameMtx_);
    return currentFrame_;
}

void AnimatedPixmap::DecodeImpl(uint32_t idx)
{
    if (intrSizeInitial_) {
        auto intrSize = src_->GetImageSize();
        if (intrSize.first * RESIZE_THRESHOLD >= size_.width || intrSize.second * RESIZE_THRESHOLD >= size_.height) {
            size_.forceResize = true;
        }
        intrSizeInitial_ = false;
    }
    RefPtr<PixelMap> frame;
    if (size_.forceResize) {
        frame = src_->CreatePixelMap(idx, { size_.width, size_.height }, size_.imageQuality);
    } else {
        // decode to intrinsic size
        frame = src_->CreatePixelMap(idx, { -1, -1 }, size_.imageQuality);
    }
    std::scoped_lock<std::mutex> lock(frameMtx_);
    currentFrame_ = frame;
}

void AnimatedPixmap::CacheFrame(const std::string& key)
{
    auto ctx = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(ctx);
    auto cache = ctx->GetImageCache();
    CHECK_NULL_VOID(cache);

    std::scoped_lock<std::mutex> lock(frameMtx_);
    cache->CacheImageData(key, MakeRefPtr<PixmapData>(currentFrame_));
}

RefPtr<CanvasImage> AnimatedPixmap::GetCachedFrameImpl(const std::string& key)
{
    return PixelMapImage::QueryFromCache(key);
}

void AnimatedPixmap::UseCachedFrame(RefPtr<CanvasImage>&& image)
{
    std::scoped_lock<std::mutex> lock(frameMtx_);
    currentFrame_ = DynamicCast<PixelMapImage>(image)->GetPixelMap();
}
} // namespace OHOS::Ace::NG
