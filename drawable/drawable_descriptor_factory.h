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
#ifndef FOUNDATION_ACE_DRAWABLE_DESCRIPTOR_DRAWABLE_DESCRIPTOR_FACTORY_H
#define FOUNDATION_ACE_DRAWABLE_DESCRIPTOR_DRAWABLE_DESCRIPTOR_FACTORY_H

#include "base/marcos.h"

namespace OHOS {
namespace Ace {
namespace Napi {
class DRAWABLE_FORCE_EXPORT DrawableDescriptorFactory {
public:
    using DrawableType = DrawableDescriptor::DrawableType;
    using ResourceManager = Global::Resource::ResourceManager;
    using RState = Global::Resource::RState;

    static std::unique_ptr<DrawableDescriptor> Create(int32_t id, const std::shared_ptr<ResourceManager>& resourceMgr,
        RState& state, DrawableType& drawableType, uint32_t density);

    static std::unique_ptr<DrawableDescriptor> Create(const char* name,
        const std::shared_ptr<ResourceManager>& resourceMgr, RState& state, DrawableType& drawableType,
        uint32_t density);

    static std::unique_ptr<DrawableDescriptor> Create(std::tuple<int32_t, uint32_t, uint32_t>& drawableInfo,
        const std::shared_ptr<ResourceManager>& resourceMgr, RState& state, DrawableType& drawableType);

    static std::unique_ptr<DrawableDescriptor> Create(std::tuple<const char*, uint32_t, uint32_t>& drawableInfo,
        const std::shared_ptr<ResourceManager>& resourceMgr, RState& state, DrawableType& drawableType);

    static std::unique_ptr<DrawableDescriptor> Create(std::pair<std::unique_ptr<uint8_t[]>, size_t>& foregroundInfo,
        std::pair<std::unique_ptr<uint8_t[]>, size_t>& backgroundInfo, std::string& path, DrawableType& drawableType,
        const std::shared_ptr<ResourceManager>& resourceMgr);
};
} // namespace Napi
} // namespace Ace
} // namespace OHOS
#endif // FOUNDATION_ACE_DRAWABLE_DESCRIPTOR_DRAWABLE_DESCRIPTOR_FACTORY_H
