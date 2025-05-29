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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WEB_DATA_DETECTOR_ADAPTER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WEB_DATA_DETECTOR_ADAPTER_H

#include <list>
#include <unordered_map>
#include <mutex>

#include "interfaces/inner_api/ace/ai/data_detector_interface.h"

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components/web/web_property.h"

namespace OHOS::Ace::NG {

struct NodeData {
    std::string path;
    std::string text;
};

struct EntityMatch {
    size_t start; // u16
    size_t end; // u16
    std::string entityType;
    std::string clean;
};

struct WebDataDetectorConfig {
    bool enable;
    std::string types;
    std::string color;
    std::string textDecorationStyle;
};

struct AIMenuInfo {
    std::string entityType;
    std::string content;
    std::string outerHTML;
    RectF rect; // refer to web
};

const size_t MAX_CACHE_SIZE = 100;
const size_t MAX_SELECTED_TEXT_SIZE = 255;

using DataDetectorResult = std::vector<EntityMatch>; // for single node

enum class AISupportStatus {
    UNKNOWN = 0,
    UNSUPPORTED,
    SUPPORTED,
};

struct DataDetectorRequestData {
    std::string requestId;
    std::vector<NodeData> nodes;
    std::vector<size_t> detectIds;
    std::vector<std::pair<size_t, size_t> > detectOffsets;
    std::vector<DataDetectorResult> matches;
};

template <typename KeyType, typename ValueType>
class WebDataDetectorCache : public AceType {
    DECLARE_ACE_TYPE(WebDataDetectorCache, AceType);
public:
    explicit WebDataDetectorCache(size_t maxSize) : maxSize_(maxSize) {}

    bool Get(const KeyType& key, ValueType& outValue)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        auto it = cacheMap_.find(key);
        if (it == cacheMap_.end()) {
            return false;
        }

        accessQueue_.splice(accessQueue_.begin(), accessQueue_, it->second.queueIt);
        outValue = it->second.value;
        return true;
    }

    void Put(const KeyType& key, const ValueType& value)
    {
        std::lock_guard<std::mutex> lock(mutex_);

        auto it = cacheMap_.find(key);
        if (it != cacheMap_.end()) {
            it->second.value = value;
            accessQueue_.splice(accessQueue_.begin(), accessQueue_, it->second.queueIt);
            return;
        }

        accessQueue_.push_front(key);
        cacheMap_[key] = {value, accessQueue_.begin()};

        if (cacheMap_.size() > maxSize_) {
            cacheMap_.erase(accessQueue_.back());
            accessQueue_.pop_back();
        }
    }

private:
    struct CacheNode {
        ValueType value;
        typename std::list<KeyType>::iterator queueIt;
    };

    std::unordered_map<KeyType, CacheNode> cacheMap_;
    std::list<KeyType> accessQueue_;
    size_t maxSize_;
    std::mutex mutex_;
};

class WebDataDetectorAdapter : public AceType {
    DECLARE_ACE_TYPE(WebDataDetectorAdapter, AceType);

public:
    explicit WebDataDetectorAdapter(const WeakPtr<Pattern>& pattern, size_t cacheSize = 100);
    ~WebDataDetectorAdapter() override = default;

    void SetPattern(const WeakPtr<Pattern>& pattern)
    {
        pattern_ = pattern;
    }

    bool GetDataDetectorEnable()
    {
        return config_.enable;
    }
    void SetDataDetectorEnable(bool enable);
    void SetDataDetectorConfig(const TextDetectConfig& config);
    void Init();
    void InitJSProxy();
    void ReleaseJSProxy();
    void SetNWebConfig();

    void ProcessRequest(const std::string& jsonStr);

    std::string PrepareDetectText(const std::string& requestId);
    void SendRequestToAI(const std::string& requestId);
    void ParseAIResultByType(std::shared_ptr<DataDetectorRequestData>& requestContext, const std::string& detectType,
        const std::unique_ptr<JsonValue>& jsonValue);
    void HandleResultFromAI(const std::string& requestId, const TextDataDetectResult& result);
    std::string GetResultJsonString(const std::string& requestId);
    void SendResultToJS(const std::string& resultStr);

    static int32_t MatchInOffsets(EntityMatch& match, const std::vector<std::pair<size_t, size_t> >& detectOffsets);

    void ProcessClick(const std::string& jsonStr);
    void InitAIMenu();
    void GetAIMenu();
    bool IsAISupported();
    RectF CalcAIMenuRect(double left, double top, double right, double bottom);
    bool ShowAIMenu(const AIMenuInfo& info);
    void OnClickAIMenuOption(const AIMenuInfo& info, const std::pair<std::string, FuncVariant>& menuOption);
    void OnClickMenuItem(const std::string& action, const AIMenuInfo& info);

    void OnClickAISelectMenuOption(TextDataDetectType type, const std::string& content);
    void DetectSelectedText(const std::string& text);
    static DataDetectorResult ParseAIResultJson(std::unique_ptr<JsonValue>& jsonValue);
    void OnDetectSelectedTextDone(const TextDataDetectResult& result);
    void UpdateAISelectMenu(const std::string& entityType, const std::string& content);

    void CloseAIMenu();
    void CloseOtherMenu();

    void AIPostTask(const std::function<void()>& task, TaskExecutor::TaskType taskType, const std::string& name,
        uint32_t delay = 0);
    bool SetRequestContext(const std::string& requestId, DataDetectorRequestData&& requestData);
    bool RemoveRequestContext(const std::string& requestId);
    void ResetContextMap();
    std::shared_ptr<DataDetectorRequestData> GetRequestContext(const std::string& requestId);

private:

    WeakPtr<Pattern> pattern_;

    // properties
    WebDataDetectorConfig config_ { false, "", "", "" };
    WebDataDetectorConfig newConfig_ { false, "", "", "" };
    bool hasInit_ = false;

    bool initDataDetectorProxy_ = false;

    // cache
    RefPtr<WebDataDetectorCache<std::string, DataDetectorResult>> resultCache_ = nullptr;

    // request context
    std::mutex contextMutex_;
    std::unordered_map<std::string, std::shared_ptr<DataDetectorRequestData> > contextMap_;

    // ai menu
    TextDataDetectResult textDetectResult_;
    bool initAIMenu_ = false;
    AISupportStatus aiSupportStatus_ = AISupportStatus::UNKNOWN;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_WEB_DATA_DETECTOR_ADAPTER_H