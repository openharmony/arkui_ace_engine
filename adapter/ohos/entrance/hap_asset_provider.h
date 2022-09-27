/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_HAP_ASSET_PROVIDER_H
#define FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_HAP_ASSET_PROVIDER_H

#include <mutex>
#include <string>
#include <vector>

#include "base/resource/asset_manager.h"
#include "base/utils/macros.h"
#include "core/common/flutter/flutter_asset_manager.h"

#include "flutter/fml/mapping.h"
#include "runtime_extractor.h"

namespace OHOS::Ace {

class ACE_EXPORT HapAssetProvider : public FlutterAssetProvider {
    DECLARE_ACE_TYPE(HapAssetProvider, FlutterAssetProvider);

public:
    HapAssetProvider() = default;
    ~HapAssetProvider() override = default;

    bool Initialize(const std::string& hapPath, const std::vector<std::string>& assetBasePaths);

    std::unique_ptr<fml::Mapping> GetAsMapping(const std::string& assetName) const override;

    bool IsValid() const override;

    std::string GetAssetPath(const std::string& assetName) override;

    void GetAssetList(const std::string& path, std::vector<std::string>& assetList) override;

private:
    mutable std::mutex mutex_;
    std::string hapPath_;
    std::shared_ptr<AbilityRuntime::RuntimeExtractor> runtimeExtractor_;
    std::vector<std::string> assetBasePaths_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_HAP_ASSET_PROVIDER_H
