/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_EVENT_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_EVENT_HUB_H

#include <list>
#include <utility>

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/noncopyable.h"
#include "core/components_ng/event/focus_hub.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/components_ng/event/input_event_hub.h"
#include "core/components_ng/event/state_style_manager.h"

namespace OHOS::Ace::NG {

class FrameNode;
using OnAreaChangedFunc =
    std::function<void(const RectF& oldRect, const OffsetF& oldOrigin, const RectF& rect, const OffsetF& origin)>;

struct KeyboardShortcut {
    std::string value;
    uint8_t keys = 0;
    std::function<void()> onKeyboardShortcutAction = nullptr;
};

enum class DragFuncType {
    DRAG_ENTER,
    DRAG_LEAVE,
    DRAG_MOVE,
    DRAG_DROP,
    DRAG_END,
};

// The event hub is mainly used to handle common collections of events, such as gesture events, mouse events, etc.
class EventHub : public virtual AceType {
    DECLARE_ACE_TYPE(EventHub, AceType)

public:
    EventHub() = default;
    ~EventHub() override
    {
        keyboardShortcut_.clear();
    };

    const RefPtr<GestureEventHub>& GetOrCreateGestureEventHub()
    {
        if (!gestureEventHub_) {
            gestureEventHub_ = MakeRefPtr<GestureEventHub>(WeakClaim(this));
        }
        return gestureEventHub_;
    }

    const RefPtr<GestureEventHub>& GetGestureEventHub() const
    {
        return gestureEventHub_;
    }

    const RefPtr<InputEventHub>& GetOrCreateInputEventHub()
    {
        if (!inputEventHub_) {
            inputEventHub_ = MakeRefPtr<InputEventHub>(WeakClaim(this));
        }
        return inputEventHub_;
    }

    const RefPtr<InputEventHub>& GetInputEventHub() const
    {
        return inputEventHub_;
    }

    const RefPtr<FocusHub>& GetOrCreateFocusHub(FocusType type = FocusType::DISABLE, bool focusable = false,
        FocusStyleType focusStyleType = FocusStyleType::NONE,
        const std::unique_ptr<FocusPaintParam>& paintParamsPtr = nullptr)
    {
        if (!focusHub_) {
            focusHub_ = MakeRefPtr<FocusHub>(WeakClaim(this), type, focusable);
            focusHub_->SetFocusStyleType(focusStyleType);
            if (paintParamsPtr) {
                focusHub_->SetFocusPaintParamsPtr(paintParamsPtr);
            }
        }
        return focusHub_;
    }

    const RefPtr<FocusHub>& GetFocusHub() const
    {
        return focusHub_;
    }

    void AttachHost(const WeakPtr<FrameNode>& host);

    RefPtr<FrameNode> GetFrameNode() const;

    GetEventTargetImpl CreateGetEventTargetImpl() const;

    void OnContextAttached()
    {
        if (gestureEventHub_) {
            gestureEventHub_->OnContextAttached();
        }
    }

    void ClearUserOnAppear()
    {
        if (onAppear_) {
            onAppear_ = nullptr;
        }
    }

    void SetOnAppear(std::function<void()>&& onAppear)
    {
        onAppear_ = std::move(onAppear);
    }

    void FireOnAppear()
    {
        if (onAppear_) {
            auto pipeline = PipelineBase::GetCurrentContext();
            CHECK_NULL_VOID(pipeline);
            auto taskScheduler = pipeline->GetTaskExecutor();
            CHECK_NULL_VOID(taskScheduler);
            taskScheduler->PostTask(
                [weak = WeakClaim(this)]() {
                    auto eventHub = weak.Upgrade();
                    CHECK_NULL_VOID(eventHub);
                    if (eventHub->onAppear_) {
                        // callback may be overwritten in its invoke so we copy it first
                        auto onAppear = eventHub->onAppear_;
                        onAppear();
                    }
                },
                TaskExecutor::TaskType::UI);
        }
    }

    void ClearUserOnDisAppear()
    {
        if (onDisappear_) {
            onDisappear_ = nullptr;
        }
    }

    void SetOnDisappear(std::function<void()>&& onDisappear)
    {
        onDisappear_ = std::move(onDisappear);
    }

    void FireOnDisappear()
    {
        if (onDisappear_) {
            // callback may be overwritten in its invoke so we copy it first
            auto onDisappear = onDisappear_;
            onDisappear();
        }
    }

    void ClearUserOnAreaChanged()
    {
        if (onAreaChanged_) {
            onAreaChanged_ = nullptr;
        }
    }

    void SetOnAreaChanged(OnAreaChangedFunc&& onAreaChanged)
    {
        onAreaChanged_ = std::move(onAreaChanged);
    }

    void FireOnAreaChanged(const RectF& oldRect, const OffsetF& oldOrigin, const RectF& rect, const OffsetF& origin)
    {
        if (onAreaChanged_) {
            // callback may be overwritten in its invoke so we copy it first
            auto onAreaChanged = onAreaChanged_;
            onAreaChanged(oldRect, oldOrigin, rect, origin);
        }
    }

    bool HasOnAreaChanged() const
    {
        return static_cast<bool>(onAreaChanged_);
    }

    using OnDragFunc = std::function<void(const RefPtr<OHOS::Ace::DragEvent>&, const std::string&)>;
    using OnNewDragFunc = std::function<void(const RefPtr<OHOS::Ace::DragEvent>&)>;
    using OnDragStartFunc = std::function<DragDropInfo(const RefPtr<OHOS::Ace::DragEvent>&, const std::string&)>;
    void SetOnDragStart(OnDragStartFunc&& onDragStart)
    {
        onDragStart_ = std::move(onDragStart);
    }

    const OnDragStartFunc& GetOnDragStart() const
    {
        return onDragStart_;
    }

    bool HasOnDragStart() const
    {
        return static_cast<bool>(onDragStart_);
    }

    void SetOnDragEnter(OnDragFunc&& onDragEnter)
    {
        onDragEnter_ = std::move(onDragEnter);
    }

    void FireOnDragEnter(const RefPtr<OHOS::Ace::DragEvent>& info, const std::string& extraParams)
    {
        if (SystemProperties::GetDebugEnabled()) {
            LOGI("DragDropManager fire onDragEnter");
        }
        if (onDragEnter_) {
            // callback may be overwritten in its invoke so we copy it first
            auto onDragEnter = onDragEnter_;
            onDragEnter(info, extraParams);
        }
    }

    void SetOnDragLeave(OnDragFunc&& onDragLeave)
    {
        onDragLeave_ = std::move(onDragLeave);
    }

    void FireOnDragLeave(const RefPtr<OHOS::Ace::DragEvent>& info, const std::string& extraParams)
    {
        if (SystemProperties::GetDebugEnabled()) {
            LOGI("DragDropManager fire onDragLeave");
        }
        if (onDragLeave_) {
            // callback may be overwritten in its invoke so we copy it first
            auto onDragLeave = onDragLeave_;
            onDragLeave(info, extraParams);
        }
    }

    void SetOnDragMove(OnDragFunc&& onDragMove)
    {
        onDragMove_ = std::move(onDragMove);
    }

    void FireOnDragMove(const RefPtr<OHOS::Ace::DragEvent>& info, const std::string& extraParams)
    {
        if (SystemProperties::GetDebugEnabled()) {
            LOGI("DragDropManager fire onDragMove");
        }
        if (onDragMove_) {
            // callback may be overwritten in its invoke so we copy it first
            auto onDragMove = onDragMove_;
            onDragMove(info, extraParams);
        }
    }

    bool HasOnDragMove() const
    {
        return static_cast<bool>(onDragMove_);
    }

    void SetOnDrop(OnDragFunc&& onDrop)
    {
        onDrop_ = std::move(onDrop);
    }

    void SetOnDragEnd(OnNewDragFunc&& onDragEnd)
    {
        onDragEnd_ = std::move(onDragEnd);
    }

    const OnNewDragFunc& GetOnDragEnd() const
    {
        return onDragEnd_;
    }

    bool HasOnDragEnd() const
    {
        return static_cast<bool>(onDragEnd_);
    }

    virtual bool HasOnItemDragMove()
    {
        return false;
    }

    virtual bool HasOnItemDrop()
    {
        return false;
    }

    void FireOnDrop(const RefPtr<OHOS::Ace::DragEvent>& info, const std::string& extraParams)
    {
        if (SystemProperties::GetDebugEnabled()) {
            LOGI("DragDropManager fire onDrop");
        }
        if (onDrop_) {
            // callback may be overwritten in its invoke so we copy it first
            auto onDrop = onDrop_;
            onDrop(info, extraParams);
        }
    }

    bool HasOnDrop() const
    {
        return onDrop_ != nullptr;
    }

    bool HasCustomerOnDrop() const
    {
        return customerOnDrop_ != nullptr;
    }

    virtual std::string GetDragExtraParams(const std::string& extraInfo, const Point& point, DragEventType isStart)
    {
        auto json = JsonUtil::Create(true);
        if (!extraInfo.empty()) {
            json->Put("extraInfo", extraInfo.c_str());
        }
        return json->ToString();
    }

    bool IsEnabled() const
    {
        return enabled_;
    }

    bool IsDeveloperEnabled() const
    {
        return developerEnabled_;
    }

    void SetEnabled(bool enabled)
    {
        enabled_ = enabled;
        developerEnabled_ = enabled;
    }

    void SetEnabledInternal(bool enabled)
    {
        enabled_ = enabled;
    }

    // restore enabled value to what developer sets
    void RestoreEnabled()
    {
        enabled_ = developerEnabled_;
    }

    // get XTS inspector value
    virtual void ToJsonValue(std::unique_ptr<JsonValue>& json) const {}

    virtual void FromJson(const std::unique_ptr<JsonValue>& json) {}

    void MarkModifyDone();

    void SetCurrentUIState(UIState state, bool flag);

    void UpdateCurrentUIState(UIState state)
    {
        if (stateStyleMgr_) {
            stateStyleMgr_->UpdateCurrentUIState(state);
        }
    }

    void ResetCurrentUIState(UIState state)
    {
        if (stateStyleMgr_) {
            stateStyleMgr_->ResetCurrentUIState(state);
        }
    }

    UIState GetCurrentUIState() const
    {
        return stateStyleMgr_ ? stateStyleMgr_->GetCurrentUIState() : UI_STATE_NORMAL;
    }

    bool HasStateStyle(UIState state) const
    {
        if (stateStyleMgr_) {
            return stateStyleMgr_->HasStateStyle(state);
        }
        return false;
    }

    void AddSupportedState(UIState state);

    void SetSupportedStates(UIState state);

    bool IsCurrentStateOn(UIState state);

    void SetKeyboardShortcut(
        const std::string& value, uint8_t keys, const std::function<void()>& onKeyboardShortcutAction)
    {
        if (value.empty() && keys == 0) {
            if (keyboardShortcut_.size() == 1) {
                keyboardShortcut_.clear();
            }
            return;
        }
        KeyboardShortcut keyboardShortcut;
        for (auto&& ch : value) {
            keyboardShortcut.value.push_back(static_cast<char>(std::toupper(ch)));
        }
        keyboardShortcut.keys = keys;
        keyboardShortcut.onKeyboardShortcutAction = onKeyboardShortcutAction;
        keyboardShortcut_.emplace_back(keyboardShortcut);
    }

    std::vector<KeyboardShortcut>& GetKeyboardShortcut()
    {
        return keyboardShortcut_;
    }

    void SetCustomerOnDragFunc(DragFuncType dragFuncType, OnDragFunc&& onDragFunc);

    void SetCustomerOnDragFunc(DragFuncType dragFuncType, OnNewDragFunc&& onDragEnd);

    void FireCustomerOnDragFunc(DragFuncType dragFuncType, const RefPtr<OHOS::Ace::DragEvent>& info,
        const std::string& extraParams = "");

    bool IsFireOnDrop(const RefPtr<OHOS::Ace::DragEvent>& info);

    void HandleInternalOnDrop(const RefPtr<OHOS::Ace::DragEvent>& info, const std::string& extraParams);

protected:
    virtual void OnModifyDone() {}

private:
    WeakPtr<FrameNode> host_;
    RefPtr<GestureEventHub> gestureEventHub_;
    RefPtr<InputEventHub> inputEventHub_;
    RefPtr<FocusHub> focusHub_;
    RefPtr<StateStyleManager> stateStyleMgr_;

    std::function<void()> onAppear_;
    std::function<void()> onDisappear_;
    OnAreaChangedFunc onAreaChanged_;

    OnDragStartFunc onDragStart_;
    OnDragFunc onDragEnter_;
    OnDragFunc onDragLeave_;
    OnDragFunc onDragMove_;
    OnDragFunc onDrop_;
    OnNewDragFunc onDragEnd_;

    OnDragFunc customerOnDragEnter_;
    OnDragFunc customerOnDragLeave_;
    OnDragFunc customerOnDragMove_;
    OnDragFunc customerOnDrop_;
    OnNewDragFunc customerOnDragEnd_;

    bool enabled_ { true };
    bool developerEnabled_ { true };
    std::vector<KeyboardShortcut> keyboardShortcut_;

    ACE_DISALLOW_COPY_AND_MOVE(EventHub);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_EVENT_HUB_H
