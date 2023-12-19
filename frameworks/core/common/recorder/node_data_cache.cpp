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
#include "core/common/recorder/node_data_cache.h"

#include <string>

#include "base/json/json_util.h"
#include "base/log/log_wrapper.h"
#include "core/common/container.h"
#include "core/common/recorder/event_recorder.h"

namespace OHOS::Ace::Recorder {
constexpr int32_t PAGE_URL_SUFFIX_LENGTH = 3;

const std::string GetCurrentPageUrl()
{
    CHECK_RUN_ON(UI);
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, "");
    auto frontEnd = container->GetFrontend();
    CHECK_NULL_RETURN(frontEnd, "");
    auto pageUrl = frontEnd->GetCurrentPageUrl();
    // remove .js suffix if exists
    if (StringUtils::EndWith(pageUrl, ".js")) {
        return pageUrl.substr(0, pageUrl.length() - PAGE_URL_SUFFIX_LENGTH);
    }
    return pageUrl;
}

NodeDataCache& NodeDataCache::Get()
{
    static NodeDataCache cache;
    return cache;
}

NodeDataCache::NodeDataCache()
{
    container_ = std::make_shared<NodeDataContainer>();
    mergedConfig_ = std::make_shared<MergedConfig>();
}

void NodeDataCache::OnPageReady()
{
    prePageUrl_ = pageUrl_;
    pageUrl_ = GetCurrentPageUrl();
}

void NodeDataCache::OnPageShow(const std::string& pageUrl)
{
    prePageUrl_ = pageUrl_;
    pageUrl_ = pageUrl;
}

void NodeDataCache::OnBeforePagePop(bool destroy)
{
    if (destroy) {
        Clear(prePageUrl_);
    } else {
        Clear(pageUrl_);
    }
    shouldCollectFull_ = false;
}

void NodeDataCache::UpdateConfig(std::shared_ptr<MergedConfig>&& mergedConfig)
{
    std::unique_lock<std::mutex> lock(cacheLock_);
    mergedConfig_ = mergedConfig;
    shouldCollectFull_ = false;
}

bool NodeDataCache::PutString(const std::string& id, const std::string& value)
{
    if (id.empty() || value.empty() || value.length() > MAX_DATA_LENGTH) {
        return false;
    }
    std::unique_lock<std::mutex> lock(cacheLock_);
    if (pageUrl_.empty()) {
        pageUrl_ = GetCurrentPageUrl();
    }
    auto iter = mergedConfig_->shareNodes.find(pageUrl_);
    if (!shouldCollectFull_ && iter == mergedConfig_->shareNodes.end()) {
        return false;
    }
    if (shouldCollectFull_ || iter->second.find(id) != iter->second.end()) {
        auto iter = container_->find(pageUrl_);
        if (iter == container_->end()) {
            auto pageContainer = std::unordered_map<std::string, std::string>();
            pageContainer.emplace(id, value);
            container_->emplace(pageUrl_, std::move(pageContainer));
        } else {
            if (iter->second.size() >= MAX_SIZE_PER_PAGE) {
                return false;
            }
            iter->second[id] = value;
        }
    }
    return true;
}

bool NodeDataCache::PutBool(const std::string& id, bool value)
{
    std::string strVal = value ? "true" : "false";
    return PutString(id, strVal);
}

bool NodeDataCache::PutInt(const std::string& id, int value)
{
    return PutString(id, std::to_string(value));
}

bool NodeDataCache::PutStringArray(const std::string& id, const std::vector<std::string>& value)
{
    auto jsonArray = JsonUtil::CreateArray(true);
    for (size_t i = 0; i < value.size(); i++) {
        jsonArray->Put(std::to_string(i).c_str(), value.at(i).c_str());
    }
    return PutString(id, jsonArray->ToString());
}

bool NodeDataCache::PutMultiple(const std::string& id, const std::string& name, bool value)
{
    auto json = JsonUtil::Create(true);
    json->Put(KEY_TEXT, name.c_str());
    json->Put(KEY_CHECKED, value);
    return PutString(id, json->ToString());
}

bool NodeDataCache::PutMultiple(const std::string& id, const std::string& name, int index)
{
    auto json = JsonUtil::Create(true);
    json->Put(KEY_TEXT, name.c_str());
    json->Put(KEY_INDEX, index);
    return PutString(id, json->ToString());
}

bool NodeDataCache::PutMultiple(const std::string& id, const std::string& name, const std::vector<std::string>& value)
{
    auto json = JsonUtil::Create(true);
    json->Put(KEY_TEXT, name.c_str());
    auto jsonArray = JsonUtil::CreateArray(false);
    for (size_t i = 0; i < value.size(); i++) {
        jsonArray->Put(std::to_string(i).c_str(), value.at(i).c_str());
    }
    json->Put(KEY_TEXT_ARRAY, jsonArray);
    return PutString(id, json->ToString());
}

void NodeDataCache::GetNodeData(const std::string& pageUrl, std::unordered_map<std::string, std::string>& nodes)
{
    if (pageUrl.empty()) {
        return;
    }
    std::unique_lock<std::mutex> lock(cacheLock_);
    auto iter = container_->find(pageUrl);
    if (iter == container_->end()) {
        return;
    }
    lock.unlock();
    for (auto nodeIter = nodes.begin(); nodeIter != nodes.end(); nodeIter++) {
        auto it = iter->second.find(nodeIter->first);
        if (it != iter->second.end()) {
            nodes[it->first] = it->second;
        }
    }
}

void NodeDataCache::Clear(const std::string& pageUrl)
{
    if (pageUrl.empty()) {
        return;
    }
    std::unique_lock<std::mutex> lock(cacheLock_);
    auto iter = container_->find(pageUrl);
    if (iter != container_->end()) {
        container_->erase(iter);
    }
}

void NodeDataCache::Reset()
{
    std::unique_lock<std::mutex> lock(cacheLock_);
    container_->clear();
    pageUrl_ = "";
    prePageUrl_ = "";
}

void NodeDataCache::GetExposureCfg(const std::string& inspectId, ExposureCfg& cfg)
{
    if (pageUrl_.empty()) {
        pageUrl_ = GetCurrentPageUrl();
    }
    auto iter = mergedConfig_->exposureNodes.find(pageUrl_);
    if (iter == mergedConfig_->exposureNodes.end()) {
        return;
    }
    auto cfgIter = iter->second.find({ inspectId, 0.0, 0 });
    if (cfgIter == iter->second.end()) {
        return;
    }
    cfg.id = cfgIter->id;
    cfg.ratio = cfgIter->ratio;
    cfg.duration = cfgIter->duration;
}
} // namespace OHOS::Ace::Recorder
