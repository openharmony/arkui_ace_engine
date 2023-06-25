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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_RENDERING_CONTEXT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_RENDERING_CONTEXT_H

#include <utility>

#include "include/core/SkImage.h"

#include "core/components_ng/render/canvas_image.h"

namespace OHOS::Ace::NG {
class PixelMapImage : public CanvasImage {
    DECLARE_ACE_TYPE(PixelMapImage, CanvasImage)
public:
    explicit PixelMapImage(RefPtr<PixelMap> pixelMap) : pixelMap_(std::move(pixelMap)) {}

    ~PixelMapImage() override = default;

    int32_t GetWidth() const override;
    int32_t GetHeight() const override;

    RefPtr<PixelMap> GetPixelMap() override
    {
        return pixelMap_;
    }

    void DrawToRSCanvas(
        RSCanvas& canvas, const RSRect& srcRect, const RSRect& dstRect, const BorderRadiusArray& radiusXY) override;

private:
    const RefPtr<PixelMap> pixelMap_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_RENDERING_CONTEXT_H
