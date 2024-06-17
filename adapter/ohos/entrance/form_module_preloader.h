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

#ifndef FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_FORM_MODULE_PRELOADER_H
#define FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_FORM_MODULE_PRELOADER_H

#include <unordered_set>
#include <vector>
#include <map>
#include "core/common/asset_manager_impl.h"

namespace OHOS::Ace {
class FormModulePreloader {
public:
    /**
     * @brief Get a list of components used by cards in the specified bundle.
     * @param bundleName The name of target bundle.
     * @param formModuleList Output, the list of components.
     * @return Returns TRUE on success, FALSE on failure.
     */
    static bool CreateFormModuleList(const std::string& bundleName, std::unordered_set<std::string>& formModuleList,
        const std::map<std::string, std::string>* hapPathMap);
    /**
     * @brief In the card bundle upgrade condition, get the list of newly added components.
     * @param bundleName The name of target bundle.
     * @param formModuleList Output, the list of newly added components.
     * @return Returns TRUE on success, FALSE on failure.
     */
    static bool GetNewFormModuleList(const std::string& bundleName, std::unordered_set<std::string>& formModuleList,
        const std::map<std::string, std::string>* hapPathMap);

private:
    FormModulePreloader() = default;
    ~FormModulePreloader() = default;

    static bool ReadFormModuleList(const std::string& bundleName, std::unordered_set<std::string>& formModuleList,
     const std::map<std::string, std::string>* hapPathMap, bool isReloadCondition);

    static bool ReadFileFromAssetManager(
        const RefPtr<AssetManager>& assetManager, const std::string& fileName, std::string& content);

    static bool ParseComponentCollectionJson(
        const std::string& bundleName, const std::string& content,
        std::unordered_set<std::string>& formModuleList, bool isReloadCondition);

    static bool IsFormEtsFilePath(const std::unordered_set<std::string>& formEtsFilePaths, std::string path);

    static RefPtr<AssetManager> CreateAssetManager(const std::string& hapPath);
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_FORM_MODULE_PRELOADER_H
