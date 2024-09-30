/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "core/image/animated_image_player.h"

#ifndef USE_ROSEN_DRAWING
#include "include/codec/SkCodecAnimation.h"
#include "include/core/SkPixelRef.h"
#endif

#ifdef USE_ROSEN_DRAWING
#include "core/components_ng/render/drawing.h"
#include "drawing/engine_adapter/skia_adapter/skia_image_info.h"
#endif

namespace OHOS::Ace {

void AnimatedImagePlayer::Pause()
{
    animator_->Pause();
}

void AnimatedImagePlayer::Resume()
{
    animator_->Resume();
}

void AnimatedImagePlayer::RenderFrame(const int32_t& index)
{
    auto context = context_.Upgrade();
    if (!context) {
        LOGW("Context may be destroyed!");
        return;
    }
    auto taskExecutor = context->GetTaskExecutor();
    taskExecutor->PostTask(
        [weak = AceType::WeakClaim(this), index, dstWidth = dstWidth_, dstHeight = dstHeight_, taskExecutor] {
            ACE_SCOPED_TRACE("decode frame %d", index);
            auto player = weak.Upgrade();
            if (!player) {
                return;
            }

#ifndef USE_ROSEN_DRAWING
            sk_sp<SkImage> skImage = player->DecodeFrameImage(index);
            if (dstWidth > 0 && dstHeight > 0) {
                skImage = ImageProvider::ApplySizeToSkImage(skImage, dstWidth, dstHeight);
            }
            if (!skImage) {
                LOGW("animated player cannot get the %{public}d skImage!", index);
                return;
            }
            auto canvasImage = NG::CanvasImage::Create(&skImage);
#else
            std::shared_ptr<RSImage> dImage = player->DecodeFrameImage(index);
            if (dstWidth > 0 && dstHeight > 0) {
                dImage = ImageProvider::ApplySizeToDrawingImage(dImage, dstWidth, dstHeight);
            }
            if (!dImage) {
                LOGW("animated player cannot get the %{public}d dImage!", index);
                return;
            }
            auto canvasImage = NG::CanvasImage::Create(&dImage);
#endif
#ifdef PREVIEW
            player->successCallback_(player->imageSource_, canvasImage);
        },
        TaskExecutor::TaskType::UI, "ArkUIImagePlayerRenderAnimatedFrame");
#else
            taskExecutor->PostTask([callback = player->successCallback_, canvasImage,
                                       source = player->imageSource_] { callback(source, canvasImage); },
                TaskExecutor::TaskType::UI, "ArkUIImageRenderAnimatedFrameSuccess");
        },
        TaskExecutor::TaskType::IO, "ArkUIImagePlayerRenderAnimatedFrame");
#endif
}

#ifndef USE_ROSEN_DRAWING
sk_sp<SkImage> AnimatedImagePlayer::DecodeFrameImage(const int32_t& index)
{
    // first seek in cache
    auto iterator = cachedFrame_.find(index);
    if (iterator != cachedFrame_.end() && iterator->second != nullptr) {
        return SkImage::MakeFromBitmap(*iterator->second);
    }

    SkBitmap bitmap;
    SkImageInfo info = codec_->getInfo().makeColorType(kN32_SkColorType);
    bitmap.allocPixels(info);
    SkCodec::Options options;
    options.fFrameIndex = index;
    const int32_t requiredFrame = frameInfos_[index].fRequiredFrame;
    if (requiredFrame != SkCodec::kNoFrame) {
        if (requiredFrame == lastRequiredFrameIndex_ && lastRequiredBitmap_ && lastRequiredBitmap_->getPixels() &&
            CopyTo(&bitmap, lastRequiredBitmap_->colorType(), *lastRequiredBitmap_)) {
            options.fPriorFrame = requiredFrame;
        } else if (requiredFrame != lastRequiredFrameIndex_) {
            // find requiredFrame in cached frame.
            auto iter = cachedFrame_.find(requiredFrame);
            if (iter != cachedFrame_.end() && iter->second != nullptr &&
                CopyTo(&bitmap, iter->second->colorType(), *iter->second)) {
                options.fPriorFrame = requiredFrame;
            }
        }
    }

    if (SkCodec::kSuccess != codec_->getPixels(info, bitmap.getPixels(), bitmap.rowBytes(), &options)) {
        LOGW("Could not getPixels for frame %{public}d:", index);
        return nullptr;
    }

    if (frameInfos_[index].fDisposalMethod != SkCodecAnimation::DisposalMethod::kRestorePrevious) {
        lastRequiredBitmap_ = std::make_unique<SkBitmap>(bitmap);
        lastRequiredFrameIndex_ = index;
    }

    if (iterator != cachedFrame_.end() && iterator->second == nullptr) {
        iterator->second = std::make_unique<SkBitmap>(bitmap);
    }
    return SkImage::MakeFromBitmap(bitmap);
}

bool AnimatedImagePlayer::CopyTo(SkBitmap* dst, SkColorType dstColorType, const SkBitmap& src)
{
    SkPixmap srcPixmap;
    if (!src.peekPixels(&srcPixmap)) {
        return false;
    }
    SkBitmap tempDstBitmap;
    SkImageInfo dstInfo = srcPixmap.info().makeColorType(dstColorType);
    if (!tempDstBitmap.setInfo(dstInfo)) {
        return false;
    }
    if (!tempDstBitmap.tryAllocPixels()) {
        return false;
    }
    SkPixmap dstPixmap;
    if (!tempDstBitmap.peekPixels(&dstPixmap)) {
        return false;
    }
    if (!srcPixmap.readPixels(dstPixmap)) {
        return false;
    }
    dst->swap(tempDstBitmap);
    return true;
}
#else
std::shared_ptr<RSImage> AnimatedImagePlayer::DecodeFrameImage(const int32_t& index)
{
    // first seek in cache
    auto iterator = cachedFrame_.find(index);
    if (iterator != cachedFrame_.end() && iterator->second != nullptr) {
        auto image = std::shared_ptr<RSImage>();
        if (!image) {
            return nullptr;
        }
        image->BuildFromBitmap(*iterator->second);
        return image;
    }

    RSBitmap bitmap;
    SkImageInfo skImageInfo = codec_->getInfo().makeColorType(kN32_SkColorType);
    auto imageInfo = Rosen::Drawing::SkiaImageInfo::ConvertToRSImageInfo(skImageInfo);
    bitmap.Build(imageInfo);
    SkCodec::Options options;
    options.fFrameIndex = index;
    const int32_t requiredFrame = frameInfos_[index].fRequiredFrame;
    if (requiredFrame != SkCodec::kNoFrame) {
        if (requiredFrame == lastRequiredFrameIndex_ && lastRequiredBitmap_ && lastRequiredBitmap_->GetPixels() &&
            CopyTo(&bitmap, *lastRequiredBitmap_)) {
            options.fPriorFrame = requiredFrame;
        } else if (requiredFrame != lastRequiredFrameIndex_) {
            // find requiredFrame in cached frame.
            auto iter = cachedFrame_.find(requiredFrame);
            if (iter != cachedFrame_.end() && iter->second != nullptr &&
                CopyTo(&bitmap, *iter->second)) {
                options.fPriorFrame = requiredFrame;
            }
        }
    }

    if (SkCodec::kSuccess != codec_->getPixels(skImageInfo, bitmap.GetPixels(), bitmap.GetRowBytes(), &options)) {
        LOGW("Could not getPixels for frame %{public}d:", index);
        return nullptr;
    }

    if (frameInfos_[index].fDisposalMethod != SkCodecAnimation::DisposalMethod::kRestorePrevious) {
        lastRequiredBitmap_ = std::make_unique<RSBitmap>(bitmap);
        lastRequiredFrameIndex_ = index;
    }

    if (iterator != cachedFrame_.end() && iterator->second == nullptr) {
        iterator->second = std::make_unique<RSBitmap>(bitmap);
    }
    auto image = std::make_shared<RSImage>();
    if (!image) {
        return nullptr;
    }
    image->BuildFromBitmap(bitmap);
    return image;
}

bool AnimatedImagePlayer::CopyTo(RSBitmap* dst, const RSBitmap& src)
{
    auto info = src.GetImageInfo();
    dst->Build(info);
    src.CopyPixels(*dst, 0, 0);
    return true;
}
#endif

} // namespace OHOS::Ace
