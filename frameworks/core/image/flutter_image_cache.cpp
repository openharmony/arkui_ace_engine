/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "core/image/flutter_image_cache.h"

#include "include/core/SkGraphics.h"
#ifdef USE_ROSEN_DRAWING
#include "drawing/engine_adapter/skia_adapter/skia_data.h"

#include "core/components_ng/render/drawing.h"
#endif
#include "core/components_ng/image_provider/image_object.h"

namespace OHOS::Ace {

RefPtr<ImageCache> ImageCache::Create()
{
    return MakeRefPtr<FlutterImageCache>();
}

void FlutterImageCache::Clear()
{
    std::scoped_lock clearLock(imageCacheMutex_, dataCacheListMutex_, imageDataCacheMutex_);
    cacheList_.clear();
    imageCache_.clear();
    dataCacheList_.clear();
    imageDataCache_.clear();
}

RefPtr<CachedImageData> FlutterImageCache::GetDataFromCacheFile(const std::string& filePath)
{
    std::lock_guard<std::mutex> lock(cacheFileInfoMutex_);
    if (!GetFromCacheFileInner(filePath)) {
        LOGD("file not cached, return nullptr");
        return nullptr;
    }
    auto cacheFileLoader = AceType::MakeRefPtr<FileImageLoader>();
#ifndef USE_ROSEN_DRAWING
    auto data = cacheFileLoader->LoadImageData(ImageSourceInfo(std::string("file:/").append(filePath)));
    return data ? AceType::MakeRefPtr<SkiaCachedImageData>(data) : nullptr;
#else
    auto rsData = cacheFileLoader->LoadImageData(ImageSourceInfo(std::string("file:/").append(filePath)));
    return rsData ? AceType::MakeRefPtr<RosenCachedImageData>(rsData) : nullptr;
#endif
}

void ImageCache::Purge()
{
    SkGraphics::PurgeResourceCache();
}

} // namespace OHOS::Ace