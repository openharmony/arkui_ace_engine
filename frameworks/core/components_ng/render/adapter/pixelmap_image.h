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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_PIXELMAP_IMAGE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_PIXELMAP_IMAGE_H

#include <utility>

#include "base/utils/noncopyable.h"
#include "core/components_ng/render/canvas_image.h"
#include "core/components_ng/render/drawing.h"

namespace OHOS::Ace::NG {

class PixelMapImage : public virtual CanvasImage {
    DECLARE_ACE_TYPE(PixelMapImage, CanvasImage)
public:
    PixelMapImage() = default;
    explicit PixelMapImage(RefPtr<PixelMap> pixelMap) : pixelMap_(std::move(pixelMap)) {}

    ~PixelMapImage() override = default;

    int32_t GetWidth() const override;
    int32_t GetHeight() const override;

    RefPtr<PixelMap> GetPixelMap() const override
    {
        return pixelMap_;
    }

    bool IsHdrPixelMap() override
    {
        return pixelMap_ && pixelMap_->IsHdr();
    }

    void Cache(const std::string& key) override;

    RefPtr<CanvasImage> Clone() override;

    void NotifyDrawCompletion(const std::string& srcInfo, const RefPtr<PixelMap>& pixmap);
    void DrawToRSCanvas(
        RSCanvas& canvas, const RSRect& srcRect, const RSRect& dstRect, const BorderRadiusArray& radiusXY) override;
    void DrawRect(RSCanvas& canvas, const RSRect& srcRect, const RSRect& dstRect) override;
    void DrawRect(RSCanvas& canvas, const RSRect& dstRect);

    bool CheckIfNeedForStretching(
        RSCanvas& canvas, const RSRect& srcRect, const RSRect& dstRect, const BorderRadiusArray& radiusXY);
    bool StretchImageWithSlice(
        RSCanvas& canvas, const RSRect& srcRect, const RSRect& dstRect, const BorderRadiusArray& radiusXY);
    bool StretchImageWithLattice(
        RSCanvas& canvas, const RSRect& srcRect, const RSRect& dstRect, const BorderRadiusArray& radiusXY);

    static RefPtr<CanvasImage> QueryFromCache(const std::string& key);

    bool HasData() const override
    {
        return GetPixelMap();
    }
    static RSMatrix ToDrawingMatrix(const Matrix4& matrix4);

private:
    RefPtr<PixelMap> pixelMap_;

    ACE_DISALLOW_COPY_AND_MOVE(PixelMapImage);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_PIXELMAP_IMAGE_H
