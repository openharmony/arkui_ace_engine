/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_ACE_ENGINE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_ACE_ENGINE_H

#include <fstream>
#include <memory>
#include <unordered_map>

#include "base/utils/macros.h"
#include "base/utils/noncopyable.h"
#include "core/common/ace_page.h"
#include "core/common/container.h"
#include "core/common/frontend.h"
#include "core/common/watch_dog.h"
#include "core/common/window.h"

namespace OHOS::Ace {

class AcePage;

class ACE_EXPORT AceEngine {
public:
    ~AceEngine() = default;

    void AddContainer(int32_t instanceId, const RefPtr<Container>& container);
    void RemoveContainer(int32_t instanceId);
    RefPtr<Container> GetContainer(int32_t instanceId);
    void RegisterToWatchDog(int32_t instanceId, const RefPtr<TaskExecutor>& taskExecutor);
    static AceEngine& Get();
    void Dump(const std::vector<std::string>& params) const;
    void SetPackageName(const std::string& packageName);
    const std::string& GetPackageName() const;
    void SetPackagePath(const std::string& packagePath);
    const std::string& GetPackagePath() const;
    void SetAssetBasePath(const std::string& assetBasePath);
    const std::set<std::string>& GetAssetBasePath() const;
    RefPtr<Frontend> GetForegroundFrontend() const;
    void SetUid(int32_t uid);
    int32_t GetUid() const;
    void SetProcessName(const std::string& processName);
    const std::string& GetProcessName() const;

private:
    AceEngine();

    std::unordered_map<int32_t, RefPtr<Container>> containerMap_;
    RefPtr<WatchDog> watchDog_;
    std::string packageName_;
    std::string packagePath_;
    std::set<std::string> assetBasePathSet_;
    int32_t uid_;
    std::string processName_;

    ACE_DISALLOW_COPY_AND_MOVE(AceEngine);
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_ACE_ENGINE_H
