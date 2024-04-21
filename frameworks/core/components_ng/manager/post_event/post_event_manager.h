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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_POST_EVENT_POST_EVENT_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_POST_EVENT_POST_EVENT_MANAGER_H

#include <map>

#include "base/memory/referenced.h"
#include "core/event/touch_event.h"

namespace OHOS::Ace::NG {

struct PostEventAction {
    RefPtr<NG::UINode> targetNode = nullptr;
    TouchEvent touchEvent;
};

class ACE_FORCE_EXPORT PostEventManager : public virtual AceType {
    DECLARE_ACE_TYPE(PostEventManager, AceType);

public:
    PostEventManager() = default;
    ~PostEventManager() override = default;

    bool PostEvent(const RefPtr<NG::UINode>& uiNode, TouchEvent& touchEvent);

private:
    bool CheckPointValidity(const TouchEvent& touchEvent);
    bool PostDownEvent(const RefPtr<NG::UINode>& targetNode, const TouchEvent& touchEvent);
    bool PostMoveEvent(const RefPtr<NG::UINode>& targetNode, const TouchEvent& touchEvent);
    bool PostUpEvent(const RefPtr<NG::UINode>& targetNode, const TouchEvent& touchEvent);

    void HandlePostEvent(const RefPtr<NG::UINode>& targetNode, const TouchEvent& touchEvent);

    void CheckAndClearPostEventAction(const RefPtr<NG::UINode>& targetNode, int32_t id);

    bool HaveReceiveDownEvent(const RefPtr<NG::UINode>& targetNode, int32_t id);
    bool HaveReceiveUpOrCancelEvent(const RefPtr<NG::UINode>& targetNode, int32_t id);
    std::list<PostEventAction> postEventAction_;
    std::map<int32_t, PostEventAction> lastEventMap_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_POST_EVENT_POST_EVENT_MANAGER_H