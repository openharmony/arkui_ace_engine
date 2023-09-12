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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_IMAGE_SK_IMAGE_CACHE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_IMAGE_SK_IMAGE_CACHE_H

#include <utility>

#include "include/core/SkImage.h"

#include "core/image/image_cache.h"

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

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_IMAGE_SK_IMAGE_CACHE_H
