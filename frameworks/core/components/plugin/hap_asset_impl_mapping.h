/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_PLUGIN_HAP_ASSET_IMPL_MAPPING_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_PLUGIN_HAP_ASSET_IMPL_MAPPING_H

#include <sstream>
#include <string>
#include <vector>

#include "core/common/asset_mapping.h"

namespace OHOS::Ace::Plugin {
class HapAssetImplMapping : public AssetMapping {
public:
    explicit HapAssetImplMapping(const std::ostringstream& ostream)
    {
        const std::string& content = ostream.str();
        data_.assign(content.data(), content.data() + content.size());
    }

    ~HapAssetImplMapping() override = default;

    size_t GetSize() const override
    {
        return data_.size();
    }

    const uint8_t* GetAsset() const override
    {
        return data_.data();
    }

private:
    std::vector<uint8_t> data_;
};
} // namespace OHOS::Ace::Plugin
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_PLUGIN_HAP_ASSET_IMPL_MAPPING_H
