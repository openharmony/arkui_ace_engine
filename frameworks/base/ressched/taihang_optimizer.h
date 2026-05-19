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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_RESSCHED_TAIHANG_OPTIMIZER_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_RESSCHED_TAIHANG_OPTIMIZER_H
#include <atomic>
#include <shared_mutex>
#include <unordered_map>
#include <vector>

#include "base/utils/macros.h"
#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace {
class TaihangOptimizer final : public std::enable_shared_from_this<TaihangOptimizer> {
public:
    TaihangOptimizer() = default;
    ~TaihangOptimizer() = default;
    void Init();
    bool IsInited();
    void SetEnable(bool value);
    bool IsEnable();
    bool CheckSwiperPathValid(const std::string& bundleName, const std::string& pageNames);
    void ComponentPreMake(const std::unordered_map<std::string, std::string> extInfo);
    void HandleSwiperPreMake(const std::unordered_map<std::string, std::string> extInfo);
    void PostSwiperPreMakeTask(RefPtr<NG::FrameNode>& node, int32_t index);
private:
    TaihangOptimizer(const TaihangOptimizer&) = delete;
    TaihangOptimizer& operator=(const TaihangOptimizer&) = delete;
    std::atomic_bool enable_ = false;
    bool isInited_ = false;
    std::shared_mutex processWhiteListMutex_;
    std::unordered_map<std::string, std::vector<std::string>> bundleNameToPages_;
};
} // end namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_RESSCHED_TAIHANG_OPTIMIZER_H