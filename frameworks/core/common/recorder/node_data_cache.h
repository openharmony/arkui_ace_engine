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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_RECORDER_DATA_CACHE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_RECORDER_DATA_CACHE_H

#include <list>
#include <memory>
#include <shared_mutex>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "base/utils/noncopyable.h"
#include "core/common/recorder/event_config.h"
#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::Recorder {
constexpr int32_t MAX_SIZE_PER_PAGE = 50;

constexpr int32_t MAX_DATA_LENGTH = 100;

std::string GetPageUrlByNode(const RefPtr<NG::FrameNode>& node);

const std::string GetCurrentPageUrl();

using NodeDataContainer = std::unordered_map<std::string, std::unordered_map<std::string, std::string>>;

struct MergedConfig {
    std::unordered_map<std::string, std::unordered_set<std::string>> shareNodes;
    std::unordered_map<std::string, std::unordered_set<ExposureCfg, ExposureCfgHash>> exposureNodes;
};

class NodeDataCache final {
public:
    static NodeDataCache& Get();

    void OnPageReady();

    void OnPageShow(const std::string& pageUrl);

    void OnBeforePagePop(bool destroy = false);

    void UpdateConfig(std::shared_ptr<MergedConfig>&& mergedConfig);

    bool PutString(const RefPtr<NG::FrameNode>& node, const std::string& id, const std::string& value);

    bool PutBool(const RefPtr<NG::FrameNode>& node, const std::string& id, bool value);

    bool PutInt(const RefPtr<NG::FrameNode>& node, const std::string& id, int value);

    bool PutStringArray(
        const RefPtr<NG::FrameNode>& node, const std::string& id, const std::vector<std::string>& value);

    bool PutMultiple(const RefPtr<NG::FrameNode>& node, const std::string& id, const std::string& name, bool value);

    bool PutMultiple(const RefPtr<NG::FrameNode>& node, const std::string& id, const std::string& name, int index);

    bool PutMultiple(const RefPtr<NG::FrameNode>& node, const std::string& id, const std::string& name,
        const std::vector<std::string>& value);

    void GetNodeData(const std::string& pageUrl, std::unordered_map<std::string, std::string>& nodes);

    void Clear(const std::string& pageUrl);

    void GetExposureCfg(const std::string& pageUrl, const std::string& inspectId, ExposureCfg& cfg);

    bool ShouldCollectData() const
    {
        return shouldCollectFull_;
    }

    bool IsShareNodeEmpty() const
    {
        return mergedConfig_->shareNodes.empty();
    }

private:
    NodeDataCache();
    ~NodeDataCache() = default;

    void Reset();

    std::shared_ptr<NodeDataContainer> container_;

    std::shared_ptr<MergedConfig> mergedConfig_;

    std::shared_mutex configMutex_;

    std::shared_mutex cacheMutex_;

    std::string pageUrl_;

    std::string prePageUrl_;

    bool shouldCollectFull_ = true;

    ACE_DISALLOW_COPY_AND_MOVE(NodeDataCache);
};
} // namespace OHOS::Ace::Recorder
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_RECORDER_DATA_CACHE_H
