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

#include "loader/resource_image_loader.h"


#include "base/resource_adapter.h"
#include "loader/file_image_loader.h"
#include "utils/resource_manager.h"

namespace OHOS {
namespace Ace {
namespace Drawable {
std::shared_ptr<ImageData> ResourceImageLoader::LoadImageData(const SourceInfo& src)
{
    auto resource = src.GetResource();
    auto resourceAdapter =
        ResourceManager::GetOrCreateResourceAdpter(resource.GetBundleName(), resource.GetModuleName());
    std::unique_ptr<uint8_t[]> data;
    size_t dataLen = 0;
    resourceAdapter->GetMediaData(resource.GetId(), dataLen, data);
    auto imageData = ImageData::Create(data.get(), static_cast<uint32_t>(dataLen));
    return imageData;
}
} // namespace Drawable
} // namespace Ace
} // namespace OHOS