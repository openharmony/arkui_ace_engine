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

#include "core/components_ng/pattern/stage/page_pattern.h"

namespace OHOS::Ace::Recorder {
constexpr int32_t PAGE_URL_SUFFIX_LENGTH = 3;

std::string GetPageUrlByNode(const RefPtr<NG::FrameNode>& node)
{
    auto pageNode = node->GetPageNode();
    CHECK_NULL_RETURN(pageNode, "");
    auto pagePattern = pageNode->GetPattern<NG::PagePattern>();
    CHECK_NULL_RETURN(pagePattern, "");
    return pagePattern->GetPageUrl();
}

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
    EventRecorder::Get().SetContainerChanged();
}

void NodeDataCache::UpdateConfig(std::shared_ptr<MergedConfig>&& mergedConfig)
{
    std::unique_lock<std::shared_mutex> lock(configMutex_);
    mergedConfig_ = mergedConfig;
    shouldCollectFull_ = false;
}

bool NodeDataCache::PutString(const RefPtr<NG::FrameNode>& node, const std::string& id, const std::string& value)
{
    if (id.empty() || value.empty() || value.length() > MAX_DATA_LENGTH) {
        return false;
    }
    if (mergedConfig_->shareNodes.empty()) {
        return false;
    }
    auto pageUrl = GetPageUrlByNode(node);
    if (pageUrl.empty()) {
        return false;
    }
    std::shared_lock<std::shared_mutex> configLock(configMutex_);
    auto iter = mergedConfig_->shareNodes.find(pageUrl);
    if (!shouldCollectFull_ && iter == mergedConfig_->shareNodes.end()) {
        return false;
    }
    if (shouldCollectFull_ || iter->second.find(id) != iter->second.end()) {
        std::unique_lock<std::shared_mutex> cacheLock(cacheMutex_);
        auto iter = container_->find(pageUrl);
        if (iter == container_->end()) {
            auto pageContainer = std::unordered_map<std::string, std::string>();
            pageContainer.emplace(id, value);
            container_->emplace(pageUrl, std::move(pageContainer));
        } else {
            if (iter->second.size() >= MAX_SIZE_PER_PAGE) {
                return false;
            }
            iter->second[id] = value;
        }
    }
    return true;
}

bool NodeDataCache::PutBool(const RefPtr<NG::FrameNode>& node, const std::string& id, bool value)
{
    std::string strVal = value ? "true" : "false";
    return PutString(node, id, strVal);
}

bool NodeDataCache::PutInt(const RefPtr<NG::FrameNode>& node, const std::string& id, int value)
{
    return PutString(node, id, std::to_string(value));
}

bool NodeDataCache::PutStringArray(
    const RefPtr<NG::FrameNode>& node, const std::string& id, const std::vector<std::string>& value)
{
    auto jsonArray = JsonUtil::CreateArray(true);
    for (size_t i = 0; i < value.size(); i++) {
        jsonArray->Put(std::to_string(i).c_str(), value.at(i).c_str());
    }
    return PutString(node, id, jsonArray->ToString());
}

bool NodeDataCache::PutMultiple(
    const RefPtr<NG::FrameNode>& node, const std::string& id, const std::string& name, bool value)
{
    auto json = JsonUtil::Create(true);
    json->Put(KEY_TEXT, name.c_str());
    json->Put(KEY_CHECKED, value);
    return PutString(node, id, json->ToString());
}

bool NodeDataCache::PutMultiple(
    const RefPtr<NG::FrameNode>& node, const std::string& id, const std::string& name, int index)
{
    auto json = JsonUtil::Create(true);
    json->Put(KEY_TEXT, name.c_str());
    json->Put(KEY_INDEX, index);
    return PutString(node, id, json->ToString());
}

bool NodeDataCache::PutMultiple(const RefPtr<NG::FrameNode>& node, const std::string& id, const std::string& name,
    const std::vector<std::string>& value)
{
    auto json = JsonUtil::Create(true);
    json->Put(KEY_TEXT, name.c_str());
    auto jsonArray = JsonUtil::CreateArray(true);
    for (size_t i = 0; i < value.size(); i++) {
        jsonArray->Put(std::to_string(i).c_str(), value.at(i).c_str());
    }
    json->Put(KEY_TEXT_ARRAY, jsonArray);
    return PutString(node, id, json->ToString());
}

void NodeDataCache::GetNodeData(const std::string& pageUrl, std::unordered_map<std::string, std::string>& nodes)
{
    if (pageUrl.empty()) {
        return;
    }
    std::shared_lock<std::shared_mutex> lock(cacheMutex_);
    auto iter = container_->find(pageUrl);
    if (iter == container_->end()) {
        return;
    }
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
    std::unique_lock<std::shared_mutex> lock(cacheMutex_);
    auto iter = container_->find(pageUrl);
    if (iter != container_->end()) {
        container_->erase(iter);
    }
}

void NodeDataCache::Reset()
{
    std::unique_lock<std::shared_mutex> lock(cacheMutex_);
    container_->clear();
    pageUrl_ = "";
    prePageUrl_ = "";
}

void NodeDataCache::GetExposureCfg(const std::string& pageUrl, const std::string& inspectId, ExposureCfg& cfg)
{
    if (pageUrl.empty()) {
        return;
    }
    std::shared_lock<std::shared_mutex> configLock(configMutex_);
    auto iter = mergedConfig_->exposureNodes.find(pageUrl);
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
