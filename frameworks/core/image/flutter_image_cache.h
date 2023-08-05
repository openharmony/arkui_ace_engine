/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_IMAGE_FLUTTER_IMAGE_CACHE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_IMAGE_FLUTTER_IMAGE_CACHE_H

#include <utility>

#include "core/components_ng/render/canvas_image.h"
#include "core/image/image_cache.h"
#include "core/image/image_object.h"

namespace OHOS::Ace {

struct CachedImage {
#ifndef USE_ROSEN_DRAWING
    explicit CachedImage(const sk_sp<SkImage>& image) : imagePtr(image) {}
    sk_sp<SkImage> imagePtr;
#else
    explicit CachedImage(const std::shared_ptr<RSImage>& image) : imagePtr(image) {}
    std::shared_ptr<RSImage> imagePtr;
#endif
    uint32_t uniqueId = 0;
};

#ifndef USE_ROSEN_DRAWING
struct SkiaCachedImageData : public CachedImageData {
    DECLARE_ACE_TYPE(SkiaCachedImageData, CachedImageData);

public:
    explicit SkiaCachedImageData(const sk_sp<SkData>& data) : imageData(data) {}
    ~SkiaCachedImageData() override = default;
#else
struct RosenCachedImageData : public CachedImageData {
    DECLARE_ACE_TYPE(RosenCachedImageData, CachedImageData);

public:
    explicit RosenCachedImageData(const std::shared_ptr<RSData>& data) : imageData(data) {}
    ~RosenCachedImageData() override = default;
#endif

    size_t GetSize() override
    {
#ifndef USE_ROSEN_DRAWING
        return imageData ? imageData->size() : 0;
#else
        return imageData ? imageData->GetSize() : 0;
#endif
    }

    const uint8_t* GetData() override
    {
#ifndef USE_ROSEN_DRAWING
        return imageData ? imageData->bytes() : nullptr;
#else
        return imageData ? static_cast<const uint8_t*>(imageData->GetData()) : nullptr;
#endif
    }

#ifndef USE_ROSEN_DRAWING
    sk_sp<SkData> imageData;
#else
    std::shared_ptr<RSData> imageData;
#endif
};

class FlutterImageCache : public ImageCache {
    DECLARE_ACE_TYPE(FlutterImageCache, ImageCache);

public:
    FlutterImageCache() = default;
    ~FlutterImageCache() override = default;
    void Clear() override;
    RefPtr<CachedImageData> GetDataFromCacheFile(const std::string& filePath) override;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_IMAGE_FLUTTER_IMAGE_CACHE_H
