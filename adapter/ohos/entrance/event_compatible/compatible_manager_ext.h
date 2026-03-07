/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef ADAPTER_OHOS_ENTRANCE_EVENT_COMPATIBLE_COMPATIBLE_MANAGER_EXT_H
#define ADAPTER_OHOS_ENTRANCE_EVENT_COMPATIBLE_COMPATIBLE_MANAGER_EXT_H

#include <map>
#include <mutex>
#include <string>

#include "datashare_helper.h"
#include "singleton.h"
namespace OHOS::Ace::NG {

struct CompatibleInfo {
    CompatibleInfo() {};
    explicit CompatibleInfo(bool mouseTransform) : mouseTransform(mouseTransform) {};
    ~CompatibleInfo() {};
    int32_t inputMode = 0;
    int32_t mode = -1;
    bool mouseTransform = true;
};

class CompatibleManagerExt : public DelayedSingleton<CompatibleManagerExt> {
public:
    CompatibleManagerExt() = default;
    ~CompatibleManagerExt() = default;
    int32_t GetCompatibleinputMode(const std::string& bundleName);
    CompatibleInfo GetCompatibleMouseTransform(const std::string& bundleName);

private:
    static std::shared_ptr<DataShare::DataShareHelper> CreateDataShareHelper();
    bool ReleaseDataShareHelper(std::shared_ptr<DataShare::DataShareHelper>& helper);
    std::string GetSettingsDataStringValue();
    bool ParseJsonToMap(const std::string& jsonStr, std::map<std::string, CompatibleInfo>& compatibleMap);
    std::string GetSettingsModeStringValue();
    bool ParseSettingJsonToMap(const std::string& jsonStr, std::map<std::string, int32_t>& compatibleMap);
    bool isSettingsDataLoaded_ = false;
    std::mutex compatibleInfoMapMutex_;
    std::map<std::string, CompatibleInfo> compatibleInfoMap_;
    std::map<std::string, int32_t> compatibleSettingInfoMap_;
    int32_t GetCurrentActiveUserId();
};
} // namespace OHOS::Ace::NG
#endif // FRAMEWORKS_CORE_EVENT_COMPATIBLE_COMPATIBLE_MANAGER_EXT_H
