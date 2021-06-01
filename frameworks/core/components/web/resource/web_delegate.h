/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_WEB_RESOURCE_WEB_DELEGATE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_WEB_RESOURCE_WEB_DELEGATE_H

#include <list>

#include "core/components/common/layout/constants.h"
#include "core/components/web/resource/web_resource.h"
#include "core/components/web/web_component.h"

namespace OHOS::Ace {

class WebDelegate : public WebResource {
    DECLARE_ACE_TYPE(WebDelegate, WebResource);

public:
    using CreatedCallback = std::function<void()>;
    using ReleasedCallback = std::function<void(bool)>;
    using EventCallback = std::function<void(const std::string&)>;
    enum class State: char {
        WAITINGFORSIZE,
        CREATING,
        CREATED,
        CREATEFAILED,
        RELEASED,
    };

    WebDelegate() = delete;
    ~WebDelegate() override;
    WebDelegate(const WeakPtr<WebComponent>& webComponent,
        const WeakPtr<PipelineContext>& context, ErrorCallback&& onError, const std::string& type)
        : WebResource(type, context, std::move(onError)),
        webComponent_(webComponent), state_(State::WAITINGFORSIZE) {
        ACE_DCHECK(!type.empty());
    }

    void CreatePlatformResource(const Size& size, const Offset& position,
        const WeakPtr<PipelineContext>& context);
    void CreatePluginResource(const Size& size, const Offset& position,
        const WeakPtr<PipelineContext>& context);
    void AddCreatedCallback(const CreatedCallback& createdCallback);
    void RemoveCreatedCallback();
    void AddReleasedCallback(const ReleasedCallback& releasedCallback);
    void RemoveReleasedCallback();
    void Reload();
    void UpdateUrl(const std::string& url);

private:
    void InitWebEvent();
    void RegisterWebEvent();
    void ReleasePlatformResource();
    void Stop();
    void UnregisterEvent();
    void OnPageStarted(const std::string& param);
    void OnPageFinished(const std::string& param);
    void OnPageError(const std::string& param);
    std::string GetUrlStringParam(const std::string& param, const std::string& name) const;
    void CallWebRouterBack();
    void BindRouterBackMethod();

    WeakPtr<WebComponent> webComponent_;
    std::list<CreatedCallback> createdCallbacks_;
    std::list<ReleasedCallback> releasedCallbacks_;
    EventCallback onPageStarted_;
    EventCallback onPageFinished_;
    EventCallback onPageError_;
    Method reloadMethod_;
    Method updateUrlMethod_;
    Method routerBackMethod_;
    State state_ {State::WAITINGFORSIZE};
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_WEB_RESOURCE_WEB_DELEGATE_H
