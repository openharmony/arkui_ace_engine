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
#include "core/components_ng/image_provider/adapter/image_decoder.h"
#include "core/components_ng/render/adapter/pixelmap_image.h"

namespace OHOS::Ace::NG {

ImageDecoder::ImageDecoder(const RefPtr<ImageObject>& objW, const SizeF& targetSize, bool forceResize) {}

RefPtr<CanvasImage> ImageDecoder::MakeDrawingImage()
{
    return MakeRefPtr<DrawingImage>(nullptr);
}

RefPtr<CanvasImage> ImageDecoder::MakePixmapImage(AIImageQuality imageQuality, bool isHdrDecoderNeed)
{
    return MakeRefPtr<PixelMapImage>(nullptr);
}

} // namespace OHOS::Ace::NG