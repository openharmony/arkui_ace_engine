/*
* Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BRIDGE_CJ_FRONTEND_CJ_FRONTEND_H
#define FOUNDATION_ACE_FRAMEWORKS_BRIDGE_CJ_FRONTEND_CJ_FRONTEND_H

#include "bridge/cj_frontend/frontend/cj_frontend_abstract.h"

namespace OHOS::Ace::Framework {

class CJPageRouter;

class CJFrontend final : public CJFrontendAbstract {
DECLARE_ACE_TYPE(CJFrontend, CJFrontendAbstract);

public:
    void AttachPipelineContext(const RefPtr<PipelineBase>& context) override;

    RefPtr<AcePage> GetStagingPage();

protected:
    friend class CJEventHandler;

    void InternalInitialize() override;

private:
    RefPtr<CJPageRouter> classicRouter_;
    RefPtr<AceEventHandler> handler_;
};

class CJEventHandler final : public AceEventHandler {
public:
    explicit CJEventHandler(WeakPtr<CJFrontend> src): frontend_(std::move(src)) {}

    void HandleAsyncEvent(const EventMarker& eventMarker) override;

    void HandleAsyncEvent(const EventMarker& eventMarker, int32_t param) override;

    void HandleAsyncEvent(const EventMarker& eventMarker, const BaseEventInfo& info) override;

    void HandleAsyncEvent(const EventMarker& eventMarker, const std::shared_ptr<BaseEventInfo>& info) override;

    void HandleAsyncEvent(const EventMarker& eventMarker, const KeyEvent& info) override;

    void HandleAsyncEvent(const EventMarker& eventMarker, const std::string& param) override;

    void HandleSyncEvent(const EventMarker& eventMarker, bool& result) override;

    void HandleSyncEvent(const EventMarker& eventMarker, const BaseEventInfo& info, bool& result) override;

    void HandleSyncEvent(const EventMarker& eventMarker, const KeyEvent& info, bool& result) override;

    void HandleSyncEvent(const EventMarker& eventMarker, const std::string& param, std::string& result) override;

    void HandleSyncEvent(const EventMarker& eventMarker, const std::shared_ptr<BaseEventInfo>& info) override;

    void HandleSyncEvent(const EventMarker& eventMarker, const std::string& componentId, const int32_t nodeId,
            const bool isDestroy) override;

private:
    WeakPtr<CJFrontend> frontend_;
};

}

#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_CJ_FRONTEND_CJ_FRONTEND_H
