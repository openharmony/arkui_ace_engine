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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_RECORDER_EVENT_CONFIG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_RECORDER_EVENT_CONFIG_H

#include <string>
#include <list>
#include <memory>
#include <unordered_map>

#include "base/json/json_util.h"

namespace OHOS::Ace::Recorder {
enum class EventCategory {
    CATEGORY_PAGE,
    CATEGORY_COMPONENT,
    CATEGORY_EXPOSURE,
    CATEGORY_PAGE_PARAM,
};

struct ExposureCfg {
    std::string id;
    double ratio = 0.0;
    int duration = 0;

    bool operator==(const ExposureCfg& exposureCfg) const
    {
        return id == exposureCfg.id;
    }
};

struct ExposureCfgHash {
    size_t operator()(const ExposureCfg& exposureCfg) const
    {
        return std::hash<std::string>()(exposureCfg.id);
    }
};

struct PageCfg {
    std::list<std::string> shareNodes;
    std::list<ExposureCfg> exposureCfgs;
};

using Config = std::unordered_map<std::string, PageCfg>;
using Switch = std::unordered_map<EventCategory, bool>;

class EventConfig final {
public:
    EventConfig();
    ~EventConfig() = default;

    void Init(const std::string& config);
    bool IsEnable() const;
    bool IsCategoryEnable(EventCategory category) const;
    const std::shared_ptr<Config>& GetConfig() const;

private:
    inline void ParseSwitch(const std::unique_ptr<JsonValue>& jsonObj);
    inline void ParseShareNode(const std::unique_ptr<JsonValue>& shareNodeArray, PageCfg& pageCfg);
    inline void ParseExposureCfg(const std::unique_ptr<JsonValue>& exposureCfgArray, PageCfg& pageCfg);
    bool enable_ = false;
    std::shared_ptr<Switch> switches_;

    std::shared_ptr<Config> config_;
};
} // namespace OHOS::Ace::Recorder
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_RECORDER_EVENT_CONFIG_H
