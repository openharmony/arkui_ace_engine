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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_CANVAS_IMAGE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_CANVAS_IMAGE_H

#include <memory>

#include "base/geometry/ng/rect_t.h"
#include "base/image/pixel_map.h"
#include "base/memory/ace_type.h"
#include "base/utils/noncopyable.h"
#include "core/components/common/properties/decoration.h"
#include "core/components_ng/render/drawing_forward.h"

namespace OHOS::Ace::NG {
using BorderRadiusArray = std::array<PointF, 4>;
struct ImagePaintConfig {
    RectF srcRect_;
    RectF dstRect_;
    std::shared_ptr<std::vector<float>> colorFilter_ = nullptr;
    std::shared_ptr<BorderRadiusArray> borderRadiusXY_ = nullptr;
    float scaleX_ = 1.0f;
    float scaleY_ = 1.0f;
    ImageRenderMode renderMode_ = ImageRenderMode::ORIGINAL;
    ImageInterpolation imageInterpolation_ = ImageInterpolation::NONE;
    ImageRepeat imageRepeat_ = ImageRepeat::NO_REPEAT;
    ImageFit imageFit_ = ImageFit::COVER;
    bool flipHorizontally_ = false;
    bool isSvg_ = false;
    std::vector<ObscuredReasons> obscuredReasons_;
};

// CanvasImage is interface for drawing image.
class CanvasImage : public virtual AceType {
    DECLARE_ACE_TYPE(CanvasImage, AceType)

public:
    CanvasImage() = default;
    ~CanvasImage() override = default;
    virtual void DrawToRSCanvas(
        RSCanvas& canvas, const RSRect& srcRect, const RSRect& dstRect, const BorderRadiusArray& radiusXY) = 0;

    static RefPtr<CanvasImage> Create(void* rawImage);
    static RefPtr<CanvasImage> Create();
    static RefPtr<CanvasImage> Create(const RefPtr<PixelMap>& pixelMap);

    virtual RefPtr<PixelMap> GetPixelMap() const
    {
        return nullptr;
    }

    virtual int32_t GetWidth() const = 0;
    virtual int32_t GetHeight() const = 0;

    virtual RefPtr<CanvasImage> Clone()
    {
        return Claim(this);
    }

    // cache this CanvasImage
    virtual void Cache(const std::string& key) {}

    void SetPaintConfig(const ImagePaintConfig& config)
    {
        paintConfig_ = std::make_unique<ImagePaintConfig>(config);
    }

    void SetIsDrawAnimate(bool isDrawAnimate)
    {
        isDrawAnimate_ = isDrawAnimate;
    }

    inline ImagePaintConfig& GetPaintConfig()
    {
        if (!paintConfig_) {
            paintConfig_ = std::make_unique<ImagePaintConfig>();
        }
        return *paintConfig_;
    }

    virtual bool IsStatic()
    {
        return true;
    }
    virtual void SetRedrawCallback(std::function<void()>&& callback) {}

    virtual void ControlAnimation(bool play) {}

    virtual void SetRawCompressData(void* dataPtr, int32_t w, int32_t h) {}

protected:
    bool isDrawAnimate_ = false;

private:
    std::unique_ptr<ImagePaintConfig> paintConfig_;

    ACE_DISALLOW_COPY_AND_MOVE(CanvasImage);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_CANVAS_IMAGE_H
