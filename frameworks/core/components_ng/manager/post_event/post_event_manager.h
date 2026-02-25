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
#include "core/event/mouse_event.h"
#include "core/event/touch_event.h"

namespace OHOS::Ace::NG {

struct PostEventAction {
    RefPtr<NG::UINode> targetNode = nullptr;
    TouchEvent touchEvent;
};

struct PostMouseEventAction {
    RefPtr<NG::UINode> targetNode = nullptr;
    MouseEvent mouseEvent;
};

struct PostAxisEventAction {
    RefPtr<NG::UINode> targetNode = nullptr;
    AxisEvent axisEvent;
};

struct MouseEventState {
    bool hasPress = false;
    bool hasReleaseOrCancel = false;
    bool hasWindowEnter = false;
    bool hasWindowLeaveOrCancel = false;
};

enum class PostInputEventType : uint8_t { TOUCH = 0, MOUSE = 1, AXIS = 2 };

class ACE_FORCE_EXPORT PostEventManager : public virtual AceType {
    DECLARE_ACE_TYPE(PostEventManager, AceType);

public:
    PostEventManager() = default;
    ~PostEventManager() override = default;

    bool PostEvent(const RefPtr<NG::UINode>& uiNode, TouchEvent& touchEvent);
    bool PostTouchEvent(const RefPtr<NG::UINode>& uiNode, TouchEvent&& touchEvent);
    bool PostMouseEvent(const RefPtr<NG::UINode>& uiNode, MouseEvent&& mouseEvent);
    bool PostAxisEvent(const RefPtr<NG::UINode>& uiNode, AxisEvent&& axisEvent);
    void SetPassThroughResult(bool passThroughResult);
    RefPtr<FrameNode> GetPostTargetNode();

private:
    bool CheckPointValidity(const TouchEvent& touchEvent);
    bool PostDownEvent(const RefPtr<NG::UINode>& targetNode, const TouchEvent& touchEvent);
    bool PostMoveEvent(const RefPtr<NG::UINode>& targetNode, const TouchEvent& touchEvent);
    bool PostUpEvent(const RefPtr<NG::UINode>& targetNode, const TouchEvent& touchEvent);
    bool CheckTouchEvent(
        const RefPtr<NG::UINode>& targetNode, const TouchEvent& touchEvent, const int32_t instanceId = -1);
    bool CheckMouseEvent(
        const RefPtr<NG::UINode>& targetNode, const MouseEvent& mouseEvent, const int32_t instanceId = -1);
    bool CheckAxisEvent(
        const RefPtr<NG::UINode>& targetNode, const AxisEvent& axisEvent, const int32_t instanceId = -1);
    void ClearPostInputActions(
        const RefPtr<NG::UINode>& targetNode, int32_t id, PostInputEventType type = PostInputEventType::TOUCH);
    void ClearMouseWindowAction(const RefPtr<NG::UINode>& targetNode, int32_t id);

    // Helper methods for CheckMouseEvent
    MouseEventState CollectMouseEventState(const RefPtr<NG::UINode>& targetNode, int32_t id);
    bool HandleMousePressEvent(const MouseEventState& state, const RefPtr<NG::UINode>& targetNode, int32_t id,
        const int32_t instanceId);
    bool HandleMouseReleaseEvent(const MouseEventState& state, int32_t id);
    bool HandleMouseWindowEnterEvent(const MouseEventState& state, const RefPtr<NG::UINode>& targetNode, int32_t id,
        const int32_t instanceId);
    bool HandleMouseWindowLeaveEvent(const MouseEventState& state, int32_t id);

    void HandlePostEvent(const RefPtr<NG::UINode>& targetNode, const TouchEvent& touchEvent);

    void CheckAndClearPostEventAction(const RefPtr<NG::UINode>& targetNode, int32_t id);

    bool HaveReceiveDownEvent(const RefPtr<NG::UINode>& targetNode, int32_t id);
    bool HaveReceiveUpOrCancelEvent(const RefPtr<NG::UINode>& targetNode, int32_t id);
    std::list<PostEventAction> postEventAction_;
    std::list<PostEventAction> postInputEventAction_;
    std::list<PostMouseEventAction> postMouseEventWindowAction_;
    std::list<PostMouseEventAction> postMouseEventAction_;
    std::list<PostAxisEventAction> postAxisEventAction_;
    std::map<int32_t, PostEventAction> lastEventMap_;
    WeakPtr<FrameNode> targetNode_;
    bool passThroughResult_ = false;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_POST_EVENT_POST_EVENT_MANAGER_H