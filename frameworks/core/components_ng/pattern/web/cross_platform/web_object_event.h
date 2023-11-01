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

class WebScrollObject : public Referenced {
public:
    virtual float GetX(void* object) = 0;
    virtual float GetY(void* object) = 0;
};

class WebScaleChangeObject : public Referenced {
public:
    virtual float GetNewScale(void* object) = 0;
    virtual float GetOldScale(void* object) = 0;
};

class WebResourceResponseObject : public Referenced {
public:
    virtual std::map<std::string, std::string> GetResponseHeader(void* object) = 0;
    virtual std::string GetResponseData(void* object) = 0;
    virtual std::string GetEncoding(void* object) = 0;
    virtual std::string GetMimeType(void* object) = 0;
    virtual std::string GetReason(void* object) = 0;
    virtual int GetStatusCode(void* object) = 0;
};

class WebConsoleMessageObject : public Referenced {
public:
    virtual std::string GetMessage(void* object) = 0;
    virtual int GetMessageLevel(void* object) = 0;
    virtual std::string GetSourceId(void* object) = 0;
    virtual int GetLineNumber(void* object) = 0;
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
    using EventObjectWithBoolReturnCallback = std::function<bool(const std::string&, void *object)>;

    void RegisterObjectEvent(const std::string& eventId, const EventObJectCallback&& eventCallback)
    {
        TAG_LOGD(AceLogTag::ACE_WEB, "Web Register Object Event, %{public}s", eventId.c_str());
        eventObjectMap_[eventId] = std::move(eventCallback);
    }

    void RegisterObjectEventWithBoolReturn(
		const std::string& eventId, const EventObjectWithBoolReturnCallback&& eventCallback)
    {
        LOGI("RegisterObjectEventWithBoolReturn %{public}s", eventId.c_str());
        eventObjectWithBoolReturnMap_[eventId] = std::move(eventCallback);
    }

    void UnRegisterObjectEvent(const std::string& eventId)
    {
        eventObjectMap_.erase(eventId);
    }

    void UnRegisterObjectEventWithBoolReturn(const std::string& eventId)
    {
        eventObjectWithBoolReturnMap_.erase(eventId);
    }

    void OnObjectEvent(const std::string& eventId, const std::string& param, void *jObject)
    {
        auto event = eventObjectMap_.find(eventId);
        if (event != eventObjectMap_.end() && event->second) {
            event->second(param, jObject);
        } else {
            TAG_LOGW(AceLogTag::ACE_WEB, "failed to find object eventId = %{public}s", eventId.c_str());
        }
    }

    bool OnObjectEventWithBoolReturn(const std::string& eventId, const std::string& param, void *jObject)
    {
        LOGI("OnObjectEventWithBoolReturn %{public}s", eventId.c_str());
        auto event = eventObjectWithBoolReturnMap_.find(eventId);
        if (event != eventObjectWithBoolReturnMap_.end() && event->second) {
            return event->second(param, jObject);
        } else {
            LOGW("failed to find object eventIdWithBoolReturn = %{public}s", eventId.c_str());
        }
        return false;
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

    const RefPtr<WebScrollObject>& GetScrollObject()
    {
        return scrollObject_;
    }

    void SetScrollObject(const RefPtr<WebScrollObject>& object)
    {
        scrollObject_ = object;
    }

    const RefPtr<WebScaleChangeObject>& GetScaleChangeObject()
    {
        return scaleChangeObject_;
    }

    void SetScaleChangeObject(const RefPtr<WebScaleChangeObject>& object)
    {
        scaleChangeObject_ = object;
    }

    const RefPtr<WebResourceResponseObject>& GetResourceResponseObject()
    {
        return resourceResponseObject_;
    }

    void SetResourceResponseObject(const RefPtr<WebResourceResponseObject>& object)
    {
        resourceResponseObject_ = object;
    }

    const RefPtr<WebConsoleMessageObject>& GetConsoleMessageObject()
    {
        return consoleMessageObject_;
    }

    void SetConsoleMessageObject(const RefPtr<WebConsoleMessageObject>& object)
    {
        consoleMessageObject_ = object;
    }

private:
    RefPtr<WebResourceRequestObject> resourceRequestObject_;
    RefPtr<WebScrollObject> scrollObject_;
    RefPtr<WebScaleChangeObject> scaleChangeObject_;
    RefPtr<WebResourceErrorObject> resourceErrorObject_;
    RefPtr<WebResourceResponseObject> resourceResponseObject_;
    RefPtr<WebConsoleMessageObject> consoleMessageObject_;
    std::unordered_map<std::string, EventObJectCallback> eventObjectMap_;
    std::unordered_map<std::string, EventObjectWithBoolReturnCallback> eventObjectWithBoolReturnMap_;
};
inline WebObjectEventManager::WebObjectEventManager() = default;
inline WebObjectEventManager::~WebObjectEventManager() = default;
} // namespace OHOS::Ace
#endif