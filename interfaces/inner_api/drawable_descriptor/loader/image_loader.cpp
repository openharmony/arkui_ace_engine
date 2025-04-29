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

#include "loader/image_loader.h"

#include <memory>

#include "loader/resource_image_loader.h"

namespace OHOS {
namespace Ace {
namespace Drawable {
std::shared_ptr<ImageLoader> ImageLoader::CreateImageLoader(const SrcType& srcType)
{
    switch (srcType) {
        case SrcType::RESOURCE:
            return std::make_shared<ResourceImageLoader>();
        case SrcType::UNSUPPORTED:
        case SrcType::PIXMAP:
        default:
            return nullptr;
    }
}
} // namespace Drawable
} // namespace Ace
} // namespace OHOS
