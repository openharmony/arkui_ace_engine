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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BRIDGE_CARD_FRONTEND_CARD_FRONTEND_DELEGATE_DECLARATIVE_H
#define FOUNDATION_ACE_FRAMEWORKS_BRIDGE_CARD_FRONTEND_CARD_FRONTEND_DELEGATE_DECLARATIVE_H

#include "frameworks/base/memory/ace_type.h"
#include "frameworks/base/utils/noncopyable.h"
#include "frameworks/bridge/common/accessibility/accessibility_node_manager.h"
#include "frameworks/bridge/declarative_frontend/ng/page_router_manager.h"
#include "frameworks/bridge/declarative_frontend/ng/frontend_delegate_declarative_ng.h"

namespace OHOS::Ace::Framework {
// This is the primary class by which the CardFrontend delegates

using LoadCardCallback = std::function<bool(const std::string&, uint64_t cardId)>;

class CardFrontendDelegateDeclarative : public FrontendDelegateDeclarativeNG {
    DECLARE_ACE_TYPE(CardFrontendDelegateDeclarative, FrontendDelegateDeclarativeNG);

public:
    explicit CardFrontendDelegateDeclarative(const RefPtr<TaskExecutor>& taskExecutor)
        : FrontendDelegateDeclarativeNG(taskExecutor)
    {}
    ~CardFrontendDelegateDeclarative() override;

    void RunCard(const std::string& url, const std::string& params, const std::string& profile, uint64_t cardId);

    void FireCardEvent(const EventMarker& eventMarker, const std::string& params = "");

    void SetLoadCardCallBack(const LoadCardCallback& loadCallback)
    {
        auto pageRouterManager = GetPageRouterManager();
        CHECK_NULL_VOID(pageRouterManager);
        pageRouterManager->SetLoadCardCallback(loadCallback);
    }

    ACE_DISALLOW_COPY_AND_MOVE(CardFrontendDelegateDeclarative);
};
} // namespace OHOS::Ace::Framework

#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_CARD_FRONTEND_CARD_FRONTEND_DELEGATE_DECLARATIVE_H
