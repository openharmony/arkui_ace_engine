/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_PIPELINE_NG_LOAD_COMPLETE_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_PIPELINE_NG_LOAD_COMPLETE_MANAGER_H

#include <memory>
#include <unordered_set>

namespace OHOS::Ace {
namespace NG {
enum class CollectStatus {
    INIT = 0,
    COLLECTING,
    ANALYSIS,
    COMPLETE,
};
class LoadCompleteManager final : public std::enable_shared_from_this<LoadCompleteManager> {
public:
    LoadCompleteManager() = default;
    ~LoadCompleteManager() = default;

    void StartCollect(const std::string& pageUrl);
    void StopCollect();
    void AddLoadComponent(int32_t nodeId);
    void DeleteLoadComponent(int32_t nodeId);
    void CompleteLoadComponent(int32_t nodeId);

private:
    void ResetManagerStatus();
    void ForceFinishCollectTask();
    void TryFinishCollectTask();
    void FinishCollectTask();
    void PostTimeoutTask();
    void TryStopCollect();

    int64_t beginTime_ = 0;
    int32_t nodeNum_ = 0;
    std::string pageUrl_;
    std::unordered_set<int32_t> nodeSet_;
    CollectStatus collectStatus_ = CollectStatus::INIT;
};
} // namespace OHOS::Ace
} // namespace OHOS::Ace::NG
#endif //FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_PIPELINE_NG_LOAD_COMPLETE_MANAGER_H
