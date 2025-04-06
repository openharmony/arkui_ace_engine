/*
 * Copyright (C) 2025 Huawei Device Co., Ltd.
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
#ifndef FOUNDATION_ACE_INTERFACE_DRAWABLE_DESCRIPTOR_IMAGE_LOADER_IMAGE_LOADER_H
#define FOUNDATION_ACE_INTERFACE_DRAWABLE_DESCRIPTOR_IMAGE_LOADER_IMAGE_LOADER_H

#include <memory>
#include <string>

#include "base/image_data.h"
#include "base/source_info.h"

namespace OHOS {
namespace Ace {
namespace Drawable {
class ImageLoader {
public:
    ImageLoader() = default;
    virtual ~ImageLoader() = default;
    static std::shared_ptr<ImageLoader> CreateImageLoader(const SrcType& srcType);

    virtual std::shared_ptr<ImageData> LoadImageData(const SourceInfo& src) = 0;
};
} // namespace Drawable
} // namespace Ace
} // namespace OHOS
#endif // FOUNDATION_ACE_INTERFACE_INNERKITS_DRAWABLE_DESCRIPTOR_IMAGE_LOADER_IMAGE_LOADER_H
