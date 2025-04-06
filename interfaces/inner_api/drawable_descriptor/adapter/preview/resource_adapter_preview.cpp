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

#include <memory>

#include "base/log.h"
#include "base/marcos.h"
#include "base/resource_adapter.h"

namespace OHOS {
namespace Ace {
namespace Drawable {
class ResourceAdapterPreview : public ResourceAdapter {
public:
    ResourceAdapterPreview() = default;
    ~ResourceAdapterPreview() = default;

    void GetMediaData(uint32_t resId, size_t& len, std::unique_ptr<uint8_t[]>& dest) override;
};

std::shared_ptr<ResourceAdapter> ResourceAdapter::CreateResourceAdapter(
    const std::string bundleName, const std::string moduleName)
{
    return nullptr;
}

void ResourceAdapterPreview::GetMediaData(uint32_t resId, size_t& len, std::unique_ptr<uint8_t[]>& dest) {}
} // namespace Drawable
} // namespace Ace
} // namespace OHOS
