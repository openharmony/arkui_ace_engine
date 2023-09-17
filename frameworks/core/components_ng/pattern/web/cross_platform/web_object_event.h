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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_WEB_CORS_WEB_OBJECT_EVENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_WEB_CORS_WEB_OBJECT_EVENT_H

#include <string>
#include <unordered_map>

#include "base/json/json_util.h"
#include "base/log/log.h"
#include "base/memory/referenced.h"
#include "base/utils/macros.h"
#include "base/utils/noncopyable.h"
#include "base/utils/singleton.h"

namespace OHOS::Ace {
class WebResourceRequestObject : public Referenced {
public:
    virtual std::map<std::string, std::string> GetRequestHeader(void* object) = 0;
    virtual std::string GetRequestUrl(void* object) = 0;
    virtual std::string GetMethod(void* object) = 0;
    virtual bool IsRequestGesture(void* object) = 0;
    virtual bool IsMainFrame(void* object) = 0;
    virtual bool IsRedirect(void* object) = 0;
};

class WebResourceErrorObject : public Referenced {
public:
    virtual std::string GetErrorInfo(void* object) = 0;
    virtual int GetErrorCode(void* object) = 0;
};

class WebObjectEventManager : public Singleton<WebObjectEventManager> {
    DECLARE_SINGLETON(WebObjectEventManager)
public:
    using EventObJectCallback = std::function<void(const std::string&, void *object)>;

    void RegisterObjectEvent(const std::string& eventId, const EventObJectCallback&& eventCallback)
    {
        LOGI("RegisterObjectEvent  %{public}s", eventId.c_str());
        eventObjectMap_[eventId] = std::move(eventCallback);
    }

    void UnRegisterObjectEvent(const std::string& eventId)
    {
        eventObjectMap_.erase(eventId);
    }

    void OnObjectEvent(const std::string& eventId, const std::string& param, void *jObject)
    {
        LOGI("OnObjectEvent  %{public}s", eventId.c_str());
        auto event = eventObjectMap_.find(eventId);
        if (event != eventObjectMap_.end() && event->second) {
            event->second(param, jObject);
        } else {
            LOGW("failed to find object eventId = %{public}s", eventId.c_str());
        }
    }

    const RefPtr<WebResourceRequestObject>& GetResourceRequestObject()
    {
        return resourceRequestObject_;
    }

    void SetResourceRequestObject(const RefPtr<WebResourceRequestObject>& object)
    {
        resourceRequestObject_ = object;
    }

    const RefPtr<WebResourceErrorObject>& GetResourceErrorObject()
    {
        return resourceErrorObject_;
    }

    void SetResourceErrorObject(const RefPtr<WebResourceErrorObject>& object)
    {
        resourceErrorObject_ = object;
    }

private:
    RefPtr<WebResourceRequestObject> resourceRequestObject_;
    RefPtr<WebResourceErrorObject> resourceErrorObject_;
    std::unordered_map<std::string, EventObJectCallback> eventObjectMap_;
};
inline WebObjectEventManager::WebObjectEventManager() = default;
inline WebObjectEventManager::~WebObjectEventManager() = default;
} // namespace OHOS::Ace
#endif