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

#include "third_party/skia/include/codec/SkCodecAnimation.h"
#include "third_party/skia/include/core/SkPixelRef.h"

#include "base/log/log.h"
#include "core/image/image_provider.h"

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
    ACE_DCHECK(context->GetTaskExecutor());
    context->GetTaskExecutor()->PostTask(
        [weak = AceType::WeakClaim(this), weakProvider = imageProvider_, index] {
            auto player = weak.Upgrade();
            if (!player) {
                return;
            }
            auto canvasImage = flutter::CanvasImage::Create();
            sk_sp<SkImage> skImage = player->DecodeFrameImage(index);
            if (skImage) {
                canvasImage->set_image({ skImage, player->unrefQueue_ });
            } else {
                LOGW("cannot get skImage!");
                return;
            }
            auto provider = weakProvider.Upgrade();
            if (provider) {
                provider->OnGPUImageReady(canvasImage);
                return;
            }
            LOGI("Image provider has been released.");
        },
        TaskExecutor::TaskType::IO);
}

sk_sp<SkImage> AnimatedImagePlayer::DecodeFrameImage(const int32_t& index)
{
    SkBitmap bitmap;
    SkImageInfo info = codec_->getInfo().makeColorType(kN32_SkColorType);
    bitmap.allocPixels(info);
    SkCodec::Options options;
    options.fFrameIndex = index;
    const int32_t requiredFrame = frameInfos_[index].fRequiredFrame;
    if (requiredFrame != SkCodec::kNoFrame) {
        if (lastRequiredBitmap_ == nullptr) {
            LOGE("no required frames are cached!");
            return nullptr;
        }
        if (lastRequiredBitmap_->getPixels() &&
            CopyTo(&bitmap, lastRequiredBitmap_->colorType(), *lastRequiredBitmap_)) {
            options.fPriorFrame = requiredFrame;
        }
    }
    if (SkCodec::kSuccess != codec_->getPixels(info, bitmap.getPixels(), bitmap.rowBytes(), &options)) {
        LOGE("Could not getPixels for frame %{public}i:", index);
        return nullptr;
    }
    if (frameInfos_[index].fDisposalMethod == SkCodecAnimation::DisposalMethod::kKeep) {
        lastRequiredBitmap_ = std::make_unique<SkBitmap>(bitmap);
        requiredFrameIndex_ = index;
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

} // namespace OHOS::Ace