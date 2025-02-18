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

#include "application_context.h"
#include "resource_manager.h"

#include "base/log.h"
#include "base/marcos.h"
#include "base/resource_adapter.h"

namespace OHOS {
namespace Ace {
namespace Drawable {
class ResourceAdapterImpl : public ResourceAdapter {
public:
    explicit ResourceAdapterImpl(const std::shared_ptr<Global::Resource::ResourceManager>& manager)
        : resourceManager_(manager)
    {}

    void GetMediaData(uint32_t resId, size_t& len, std::unique_ptr<uint8_t[]>& dest) override;

private:
    std::shared_ptr<Global::Resource::ResourceManager> resourceManager_;
};

std::shared_ptr<ResourceAdapter> ResourceAdapter::CreateResourceAdapter(
    const std::string bundleName, const std::string moduleName)
{
    auto context = AbilityRuntime::Context::GetApplicationContext();
    auto currentContext = context->CreateModuleContext(bundleName, moduleName);
    auto manager = currentContext->GetResourceManager();
    return std::make_shared<ResourceAdapterImpl>(manager);
}

void ResourceAdapterImpl::GetMediaData(uint32_t resId, size_t& len, std::unique_ptr<uint8_t[]>& dest)
{
    if (resourceManager_) {
        auto state = resourceManager_->GetMediaDataById(resId, len, dest);
        if (state != Global::Resource::SUCCESS) {
            HILOGE("get media data error, id = %{public}d", resId);
        }
    }
}
} // namespace Drawable
} // namespace Ace
} // namespace OHOS