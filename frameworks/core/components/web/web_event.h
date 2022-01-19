/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_WEB_WEB_EVENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_WEB_WEB_EVENT_H

namespace OHOS::Ace {
class ACE_EXPORT LoadWebPageFinishEvent : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(LoadWebPageFinishEvent, BaseEventInfo);

public:
    LoadWebPageFinishEvent(const std::string& url) : BaseEventInfo("LoadWebPageFinishEvent"), loadedUrl_(url) {}
    ~LoadWebPageFinishEvent() = default;

    const std::string& GetLoadedUrl() const
    {
        return loadedUrl_;
    }

private:
    std::string loadedUrl_;
};

class ACE_EXPORT LoadWebRequestFocusEvent : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(LoadWebRequestFocusEvent, BaseEventInfo);

public:
    LoadWebRequestFocusEvent(const std::string& url) : BaseEventInfo("LoadWebRequestFocusEvent"), focusUrl_(url) {}
    ~LoadWebRequestFocusEvent() = default;

    const std::string& GetRequestFocus() const
    {
        return "";
    }
private:
    std::string focusUrl_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_WEB_WEB_EVENT_H
