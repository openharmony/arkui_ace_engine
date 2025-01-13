/*
 * Copyright (C) 2024 Huawei Device Co., Ltd.
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
#ifndef FOUNDATION_ACE_INTERFACE_INNERKITS_DRAWABLE_DESCRIPTOR_IMAGE_LOADER_IMAGE_LOADER_H
#define FOUNDATION_ACE_INTERFACE_INNERKITS_DRAWABLE_DESCRIPTOR_IMAGE_LOADER_IMAGE_LOADER_H

#include <memory>
#include "image_define.h"
#include "../base/image_source.h"

namespace OHOS::Ace::Napi {
class ImageLoader {
public:
    ImageLoader() = default;
    virtual ~ImageLoader() = default;
    virtual std::shared_ptr<ImageSource> LoadImageData(const SourceInfo& src) = 0;
    std::shared_ptr<ImageSource> GetImageData(const SourceInfo);
    // helper functions
    static std::string RemovePathHead(const std::string& uri);
};
} // namespace OHOS::Ace::Napi

#endif // FOUNDATION_ACE_INTERFACE_INNERKITS_DRAWABLE_DESCRIPTOR_IMAGE_LOADER_IMAGE_LOADER_H