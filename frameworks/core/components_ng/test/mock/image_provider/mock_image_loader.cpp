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
#include "mock_image_loader.h"

#include "core/image/image_loader.h"

namespace OHOS::Ace {
RefPtr<MockImageLoader> loader = AceType::MakeRefPtr<MockImageLoader>();
RefPtr<NG::ImageData> ImageLoader::GetImageData(
    const ImageSourceInfo& imageSourceInfo, const WeakPtr<PipelineBase>& context)
{
    if (imageSourceInfo.IsPixmap()) {
        return LoadDecodedImageData(imageSourceInfo, context);
    }
    this->LoadImageData(imageSourceInfo, context);
    return nullptr;
}

RefPtr<ImageLoader> ImageLoader::CreateImageLoader(const ImageSourceInfo& /*imageSourceInfo*/)
{
    return loader;
}

std::string ImageLoader::RemovePathHead(const std::string& uri)
{
    return uri.substr(0);
}

sk_sp<SkData> ImageLoader::LoadDataFromCachedFile(const std::string& /*uri*/)
{
    return nullptr;
}

sk_sp<SkData> ImageLoader::QueryImageDataFromImageCache(const ImageSourceInfo& /*sourceInfo*/)
{
    return nullptr;
}

void ImageLoader::CacheImageDataToImageCache(const std::string& key, const RefPtr<CachedImageData>& imageData) {}

RefPtr<NG::ImageData> ImageLoader::LoadImageDataFromFileCache(const std::string& /*key*/, const std::string& /*suffix*/)
{
    return nullptr;
}
} // namespace OHOS::Ace
