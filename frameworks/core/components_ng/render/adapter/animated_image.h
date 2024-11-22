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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_ANIMATED_IMAGE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_ANIMATED_IMAGE_H

#include <atomic>
#include <memory>
#include <utility>

#include "include/codec/SkCodec.h"
#include "include/core/SkImage.h"

#include "base/image/image_source.h"
#ifndef USE_ROSEN_DRAWING
#include "core/components_ng/image_provider/adapter/skia_image_data.h"
#include "core/components_ng/render/adapter/pixelmap_image.h"
#include "core/components_ng/render/adapter/skia_image.h"
#else
#include "core/components_ng/image_provider/adapter/rosen/drawing_image_data.h"
#include "core/components_ng/render/adapter/pixelmap_image.h"
#include "core/components_ng/render/adapter/rosen/drawing_image.h"
#endif

namespace OHOS::Ace::NG {
class AnimatedImage : public virtual CanvasImage {
    DECLARE_ACE_TYPE(AnimatedImage, CanvasImage)
public:
    // initialize animator
    AnimatedImage(const std::unique_ptr<SkCodec>& codec, std::string url);
    ~AnimatedImage() override;

    struct ResizeParam {
        int32_t width = 0;
        int32_t height = 0;
        bool forceResize = false;
        AIImageQuality imageQuality = AIImageQuality::NONE;
    };

#ifndef USE_ROSEN_DRAWING
    static RefPtr<CanvasImage> Create(
        const RefPtr<SkiaImageData>& data, const ResizeParam& size, const std::string& url);
#else
    static RefPtr<CanvasImage> Create(
        const RefPtr<DrawingImageData>& data, const ResizeParam& size, const std::string& url);
#endif
    void ControlAnimation(bool play) override;
    void SetRedrawCallback(std::function<void()>&& callback) override
    {
        redraw_ = std::move(callback);
    }

    bool IsStatic() override
    {
        return false;
    }

    const std::string& GetCacheKey() const
    {
        return cacheKey_;
    }

    bool GetIsAnimating() const;

protected:
    // ensure frames decode serially
    std::mutex decodeMtx_;
    // protect currentFrame_
    mutable std::mutex frameMtx_;

private:
    void RenderFrame(uint32_t idx);

    // runs on Background thread
    void DecodeFrame(uint32_t idx);
    bool GetCachedFrame(uint32_t idx);

    // git animation control
    static int GenerateIteration(const std::unique_ptr<SkCodec>& codec);
    static std::vector<int> GenerateDuration(const std::unique_ptr<SkCodec>& codec);
    void PostPlayTask(uint32_t idx, int iteration);

    virtual void DecodeImpl(uint32_t idx) = 0;
    virtual RefPtr<CanvasImage> GetCachedFrameImpl(const std::string& key)
    {
        return nullptr;
    }
    virtual void UseCachedFrame(RefPtr<CanvasImage>&& image) = 0;
    virtual void CacheFrame(const std::string& key) = 0;

    CancelableCallback<void()> currentTask_;
    const std::string cacheKey_;
    std::vector<int> duration_;
    std::atomic_int32_t queueSize_ = 0;
    std::function<void()> redraw_;
    int iteration_ = 0;
    uint32_t currentIdx_ = 0;
    bool animationState_ = false;

    ACE_DISALLOW_COPY_AND_MOVE(AnimatedImage);
};

// ================================================================================================

#ifndef USE_ROSEN_DRAWING
class AnimatedSkImage : public AnimatedImage, public SkiaImage {
    DECLARE_ACE_TYPE(AnimatedSkImage, AnimatedImage, SkiaImage)
public:
    AnimatedSkImage(std::unique_ptr<SkCodec> codec, std::string url)
        : AnimatedImage(codec, std::move(url)), codec_(std::move(codec))
    {}
    ~AnimatedSkImage() override = default;

    sk_sp<SkImage> GetImage() const override;
#else
class AnimatedRSImage : public AnimatedImage, public DrawingImage {
    DECLARE_ACE_TYPE(AnimatedRSImage, AnimatedImage, DrawingImage)
public:
    AnimatedRSImage(std::unique_ptr<SkCodec> codec, std::string url)
        : AnimatedImage(codec, std::move(url)), codec_(std::move(codec))
    {}
    ~AnimatedRSImage() override = default;

    std::shared_ptr<RSImage> GetImage() const override;

    int32_t GetWidth() const override
    {
        return currentFrame_ ? currentFrame_->GetWidth() : 0;
    }

    int32_t GetHeight() const override
    {
        return currentFrame_ ? currentFrame_->GetHeight() : 0;
    }
#endif

    RefPtr<CanvasImage> Clone() override
    {
        return Claim(this);
    }

private:
    void DecodeImpl(uint32_t idx) override;

    void CacheFrame(const std::string& key) override;
    RefPtr<CanvasImage> GetCachedFrameImpl(const std::string& key) override;
    void UseCachedFrame(RefPtr<CanvasImage>&& image) override;

#ifndef USE_ROSEN_DRAWING
    SkBitmap requiredFrame_;
    std::unique_ptr<SkCodec> codec_;
    sk_sp<SkImage> currentFrame_;

    ACE_DISALLOW_COPY_AND_MOVE(AnimatedSkImage);
#else
    RSBitmap requiredFrame_;
    std::unique_ptr<SkCodec> codec_;
    std::shared_ptr<RSImage> currentFrame_;

    ACE_DISALLOW_COPY_AND_MOVE(AnimatedRSImage);
#endif
};

// ================================================================================================

class AnimatedPixmap : public AnimatedImage, public PixelMapImage {
    DECLARE_ACE_TYPE(AnimatedPixmap, AnimatedImage, PixelMapImage)
public:
    AnimatedPixmap(const std::unique_ptr<SkCodec>& codec, const RefPtr<ImageSource>& src, const ResizeParam& size,
        std::string url);
    ~AnimatedPixmap() override = default;
    RefPtr<PixelMap> GetPixelMap() const override;

    RefPtr<CanvasImage> Clone() override
    {
        return Claim(this);
    }

private:
    void DecodeImpl(uint32_t idx) override;

    void CacheFrame(const std::string& key) override;
    RefPtr<CanvasImage> GetCachedFrameImpl(const std::string& key) override;
    void UseCachedFrame(RefPtr<CanvasImage>&& image) override;

    RefPtr<PixelMap> currentFrame_;
    bool intrSizeInitial_ = true;

    ResizeParam size_;
    const RefPtr<ImageSource> src_;

    ACE_DISALLOW_COPY_AND_MOVE(AnimatedPixmap);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_ANIMATED_IMAGE_H
