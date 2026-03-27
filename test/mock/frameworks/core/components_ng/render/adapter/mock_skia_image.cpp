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

#include "core/components_ng/render/adapter/drawing_image.h"

namespace OHOS::Ace::NG {

RefPtr<CanvasImage> DrawingImage::Clone()
{
    return Claim(this);
}

RefPtr<PixelMap> DrawingImage::GetPixelMap() const
{
    return nullptr;
}

void DrawingImage::Cache(const std::string& key) {}

RefPtr<CanvasImage> DrawingImage::QueryFromCache(const std::string& key)
{
    return nullptr;
}

void DrawingImage::DrawToRSCanvas(
    RSCanvas& canvas, const RSRect& srcRect, const RSRect& dstRect, const BorderRadiusArray& radiusXY)
{}

void DrawingImage::DrawRect(RSCanvas& canvas, const RSRect& srcRect, const RSRect& dstRect) {}

int32_t DrawingImage::GetWidth() const
{
    return {};
}

int32_t DrawingImage::GetHeight() const
{
    return {};
}

} // namespace OHOS::Ace::NG
