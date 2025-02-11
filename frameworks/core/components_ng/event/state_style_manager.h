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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_STATE_STYLE_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_STATE_STYLE_MANAGER_H

#include <set>

#include "base/geometry/ng/point_t.h"
#include "base/geometry/offset.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/thread/cancelable_callback.h"
#include "core/components_ng/base/ui_node.h"

namespace OHOS::Ace::NG {

class FrameNode;
class TouchEventImpl;
class CustomNodeBase;

using UIState = uint64_t;
inline constexpr UIState UI_STATE_NORMAL = 0;
inline constexpr UIState UI_STATE_PRESSED = 1;
inline constexpr UIState UI_STATE_FOCUSED = 1 << 1;
inline constexpr UIState UI_STATE_DISABLED = 1 << 2;
// used for radio, checkbox, switch.
inline constexpr UIState UI_STATE_SELECTED = 1 << 3;

// StateStyleManager is mainly used to manage the setting and refresh of state styles.
class StateStyleManager : public virtual AceType {
    DECLARE_ACE_TYPE(StateStyleManager, AceType)

public:
    explicit StateStyleManager(WeakPtr<FrameNode> frameNode);
    ~StateStyleManager() override;

    bool HasStateStyle(UIState state) const
    {
        return (supportedStates_ & state) == state;
    }

    UIState GetCurrentUIState() const
    {
        return currentState_;
    }

    // this function should only be called by the frontend parsing layer to add a supported UI state.
    void AddSupportedState(UIState state)
    {
        supportedStates_ = supportedStates_ | state;
        frontendSubscribers_ = frontendSubscribers_ | state;
    }

    void SetSupportedStates(UIState state)
    {
        supportedStates_ = state;
    }

    void AddSupportedUIStateWithCallback(UIState state, std::function<void(uint64_t)> callback, bool isInner)
    {
        if (state == UI_STATE_NORMAL) {
            return;
        }
        if (!HasStateStyle(state)) {
            supportedStates_ = supportedStates_ | state;
        }
        if (isInner) {
            innerStateStyleSubscribers_.first |= state;
            innerStateStyleSubscribers_.second = callback;
        } else {
            userStateStyleSubscribers_.first |= state;
            userStateStyleSubscribers_.second = callback;
        }
    }

    void RemoveSupportedUIState(UIState state, bool isInner)
    {
        if (state == UI_STATE_NORMAL) {
            return;
        }
        if (isInner) {
            innerStateStyleSubscribers_.first &= ~state;
        } else {
            userStateStyleSubscribers_.first &= ~state;
        }
        UIState temp = frontendSubscribers_ | innerStateStyleSubscribers_.first | userStateStyleSubscribers_.first;
        if ((temp & state) != state) {
            supportedStates_ = supportedStates_ & ~state;
        }
    }

    bool IsCurrentStateOn(UIState state) const
    {
        if (state == UI_STATE_NORMAL) {
            return currentState_ == state;
        }
        return (currentState_ & state) == state;
    }

    void SetCurrentUIState(UIState state, bool flag)
    {
        if (flag) {
            currentState_ |= state;
        } else {
            currentState_ &= ~state;
        }
    }

    void UpdateCurrentUIState(UIState state)
    {
        if (!HasStateStyle(state)) {
            return;
        }
        auto temp = currentState_ | state;
        if (temp != currentState_) {
            currentState_ = temp;
            FireStateFunc(state, currentState_, false);
        }
    }

    void ResetCurrentUIState(UIState state)
    {
        if (!HasStateStyle(state)) {
            return;
        }
        if ((currentState_ & state) != state) {
            return;
        }
        auto temp = currentState_ ^ state;
        if (temp != currentState_) {
            currentState_ = temp;
            FireStateFunc(state, currentState_, true);
        }
    }

    bool GetHasScrollingParent() const
    {
        return hasScrollingParent_;
    }

    const RefPtr<TouchEventImpl>& GetPressedListener();
    void HandleTouchDown();
    void HandleTouchUp();

    RefPtr<FrameNode> GetFrameNode() const;

    void ClearStateStyleTask()
    {
        DeletePressStyleTask();
        ResetPressedPendingState();
    }

private:
    void HandleStateChangeInternal(UIState handlingState, UIState currentState, bool isReset);
    void FireStateFunc(UIState handlingState, UIState currentState, bool isReset);

    void PostListItemPressStyleTask(UIState state);
    void PostPressStyleTask(uint32_t delayTime);
    void PostPressCancelStyleTask(uint32_t delayTime);

    void HandleScrollingParent();

    void DeletePressStyleTask()
    {
        if (pressStyleTask_) {
            pressStyleTask_.Cancel();
        }
    }

    void DeletePressCancelStyleTask()
    {
        if (pressCancelStyleTask_) {
            pressCancelStyleTask_.Cancel();
        }
    }

    bool IsPressedStatePending()
    {
        return pressedPendingState_;
    }

    bool IsPressedCancelStatePending()
    {
        return pressedCancelPendingState_;
    }

    void ResetPressedPendingState()
    {
        pressedPendingState_ = false;
    }

    void ResetPressedCancelPendingState()
    {
        pressedCancelPendingState_ = false;
    }

    void PendingPressedState()
    {
        pressedPendingState_ = true;
    }

    void PendingCancelPressedState()
    {
        pressedCancelPendingState_ = true;
    }

    void ResetPressedState()
    {
        ResetCurrentUIState(UI_STATE_PRESSED);
        DeletePressStyleTask();
        ResetPressedPendingState();
    }

    void ResetPressedCancelState()
    {
        DeletePressCancelStyleTask();
        ResetPressedCancelPendingState();
    }

    bool IsOutOfPressedRegion(int32_t sourceType, const Offset& location) const;
    bool IsOutOfPressedRegionWithoutClip(RefPtr<FrameNode> node, int32_t sourceType,
        const Offset& location) const;
    void Transform(PointF& localPointF, const WeakPtr<FrameNode>& node) const;
    void CleanScrollingParentListener();

    void GetCustomNode(RefPtr<CustomNodeBase>& customNode, RefPtr<UINode> node);
    bool GetCustomNodeFromSelf(RefPtr<UINode>& node, RefPtr<CustomNodeBase>& customNode, int32_t nodeId);
    bool GetCustomNodeFromNavgation(RefPtr<UINode>& node, RefPtr<CustomNodeBase>& customNode, int32_t nodeId);

    WeakPtr<FrameNode> host_;
    RefPtr<TouchEventImpl> pressedFunc_;

    UIState supportedStates_ = UI_STATE_NORMAL;
    UIState currentState_ = UI_STATE_NORMAL;
    // manages inner subscription UI state and callbacks.
    std::pair<UIState, std::function<void(uint64_t)>> innerStateStyleSubscribers_ = { UI_STATE_NORMAL, nullptr };
    // manages user subscription UI state and callbacks.
    std::pair<UIState, std::function<void(uint64_t)>> userStateStyleSubscribers_ = { UI_STATE_NORMAL, nullptr };
    // tracks frontend UI state.
    UIState frontendSubscribers_ = UI_STATE_NORMAL;
    
    std::set<int32_t> pointerId_;
    CancelableCallback<void()> pressStyleTask_;
    CancelableCallback<void()> pressCancelStyleTask_;
    bool pressedPendingState_ = false;
    bool pressedCancelPendingState_ = false;
    bool hasScrollingParent_ = false;

    ACE_DISALLOW_COPY_AND_MOVE(StateStyleManager);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_STATE_STYLE_MANAGER_H