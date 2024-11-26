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
class InspectorFilter;

using OnAreaChangedFunc =
    std::function<void(const RectF& oldRect, const OffsetF& oldOrigin, const RectF& rect, const OffsetF& origin)>;
using OnPreDragFunc = std::function<void(const PreDragStatus)>;

using OnSizeChangedFunc = std::function<void(const RectF& oldRect, const RectF& rect)>;

struct KeyboardShortcut {
    std::string value;
    uint8_t keys = 0;
    std::function<void()> onKeyboardShortcutAction = nullptr;
    bool IsEqualTrigger(const KeyboardShortcut& other)
    {
        return (keys == other.keys) && (value == other.value);
    }
};

enum class DragFuncType {
    DRAG_ENTER,
    DRAG_LEAVE,
    DRAG_MOVE,
    DRAG_DROP,
    DRAG_END,
};

// The event hub is mainly used to handle common collections of events, such as gesture events, mouse events, etc.
class ACE_FORCE_EXPORT EventHub : public virtual AceType {
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
            gestureEventHub_ = CreateGestureEventHub();
        }
        return gestureEventHub_;
    }

    virtual RefPtr<GestureEventHub> CreateGestureEventHub()
    {
        return MakeRefPtr<GestureEventHub>(WeakClaim(this));
    }

    const RefPtr<GestureEventHub>& GetGestureEventHub() const
    {
        return gestureEventHub_;
    }

    void SetGestureEventHub(const RefPtr<GestureEventHub>& gestureEventHub)
    {
        gestureEventHub_ = gestureEventHub;
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

    const RefPtr<FocusHub>& GetOrCreateFocusHub(const FocusPattern& focusPattern)
    {
        if (!focusHub_) {
            focusHub_ = MakeRefPtr<FocusHub>(WeakClaim(this), focusPattern);
        }
        return focusHub_;
    }

    const RefPtr<FocusHub>& GetFocusHub() const
    {
        return focusHub_;
    }

    void AttachHost(const WeakPtr<FrameNode>& host);
    void OnAttachContext(PipelineContext *context);
    void OnDetachContext(PipelineContext *context);

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

    void SetJSFrameNodeOnAppear(std::function<void()>&& onAppear);

    void ClearJSFrameNodeOnAppear();

    virtual void FireOnAppear();

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

    void SetJSFrameNodeOnDisappear(std::function<void()>&& onDisappear);

    void ClearJSFrameNodeOnDisappear();

    virtual void FireOnDisappear();

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

    void FireInnerOnAreaChanged(
        const RectF& oldRect, const OffsetF& oldOrigin, const RectF& rect, const OffsetF& origin)
    {
        for (auto& innerCallbackInfo : onAreaChangedInnerCallbacks_) {
            if (innerCallbackInfo.second) {
                auto innerOnAreaCallback = innerCallbackInfo.second;
                innerOnAreaCallback(oldRect, oldOrigin, rect, origin);
            }
        }
    }

    bool HasOnAreaChanged() const
    {
        return static_cast<bool>(onAreaChanged_);
    }

    bool HasInnerOnAreaChanged() const
    {
        return !onAreaChangedInnerCallbacks_.empty();
    }

    void SetOnSizeChanged(OnSizeChangedFunc&& onSizeChanged);
    void FireOnSizeChanged(const RectF& oldRect, const RectF& rect);
    bool HasOnSizeChanged() const;

    void AddInnerOnSizeChanged(int32_t id, OnSizeChangedFunc&& onSizeChanged);
    void FireInnerOnSizeChanged(const RectF& oldRect, const RectF& rect);
    bool HasInnerOnSizeChanged() const;
    void ClearInnerOnSizeChanged();

    void SetJSFrameNodeOnSizeChangeCallback(OnSizeChangedFunc&& onSizeChanged);
    void FireJSFrameNodeOnSizeChanged(const RectF& oldRect, const RectF& rect);
    void ClearJSFrameNodeOnSizeChange();
    using OnDragFunc = std::function<void(const RefPtr<OHOS::Ace::DragEvent>&, const std::string&)>;
    using OnNewDragFunc = std::function<void(const RefPtr<OHOS::Ace::DragEvent>&)>;
    using OnDragStartFunc = std::function<DragDropInfo(const RefPtr<OHOS::Ace::DragEvent>&, const std::string&)>;

    void SetOnPreDrag(OnPreDragFunc&& onPreDragFunc)
    {
        onPreDragFunc_ = std::move(onPreDragFunc);
    }

    const OnPreDragFunc& GetOnPreDrag() const
    {
        return onPreDragFunc_;
    }

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
        return static_cast<bool>(onDragStart_) || static_cast<bool>(defaultOnDragStart_);
    }

    void SetOnDragEnter(OnDragFunc&& onDragEnter)
    {
        onDragEnter_ = std::move(onDragEnter);
    }

    void FireOnDragEnter(const RefPtr<OHOS::Ace::DragEvent>& info, const std::string& extraParams);

    void SetOnDragLeave(OnDragFunc&& onDragLeave)
    {
        onDragLeave_ = std::move(onDragLeave);
    }

    void FireOnDragLeave(const RefPtr<OHOS::Ace::DragEvent>& info, const std::string& extraParams);

    void SetOnDragMove(OnDragFunc&& onDragMove)
    {
        onDragMove_ = std::move(onDragMove);
    }

    void FireOnDragMove(const RefPtr<OHOS::Ace::DragEvent>& info, const std::string& extraParams);

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

    bool HasOnDragEnter() const
    {
        return static_cast<bool>(onDragEnter_);
    }

    bool HasOnDragLeave() const
    {
        return static_cast<bool>(onDragLeave_);
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

    void FireOnDrop(const RefPtr<OHOS::Ace::DragEvent>& info, const std::string& extraParams);

    bool HasOnDrop() const
    {
        return onDrop_ != nullptr;
    }

    bool HasCustomerOnDragEnter() const
    {
        return customerOnDragEnter_ != nullptr;
    }

    bool HasCustomerOnDragLeave() const
    {
        return customerOnDragLeave_ != nullptr;
    }

    bool HasCustomerOnDragMove() const
    {
        return customerOnDragMove_ != nullptr;
    }

    bool HasCustomerOnDragEnd() const
    {
        return customerOnDragEnd_ != nullptr;
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

    void SetEnabled(bool enabled);

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
    virtual void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const {}

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
        KeyboardShortcut keyboardShortcut;
        for (auto&& ch : value) {
            keyboardShortcut.value.push_back(static_cast<char>(std::toupper(ch)));
        }
        keyboardShortcut.keys = keys;
        keyboardShortcut.onKeyboardShortcutAction = onKeyboardShortcutAction;

        for (auto& shortCut : keyboardShortcut_) {
            if (shortCut.IsEqualTrigger(keyboardShortcut)) {
                shortCut.onKeyboardShortcutAction = onKeyboardShortcutAction;
                return;
            }
        }
        keyboardShortcut_.emplace_back(keyboardShortcut);
    }

    void ClearSingleKeyboardShortcut()
    {
        if (keyboardShortcut_.size() == 1) {
            keyboardShortcut_.clear();
        }
    }

    std::vector<KeyboardShortcut>& GetKeyboardShortcut()
    {
        return keyboardShortcut_;
    }

    void SetCustomerOnDragFunc(DragFuncType dragFuncType, OnDragFunc&& onDragFunc);

    void SetCustomerOnDragFunc(DragFuncType dragFuncType, OnNewDragFunc&& onDragEnd);

    const OnDragFunc GetCustomerOnDragFunc(DragFuncType dragFuncType) const
    {
        OnDragFunc dragFunc;
        switch (dragFuncType) {
            case DragFuncType::DRAG_ENTER:
                dragFunc = customerOnDragEnter_;
                break;
            case DragFuncType::DRAG_LEAVE:
                dragFunc = customerOnDragLeave_;
                break;
            case DragFuncType::DRAG_MOVE:
                dragFunc = customerOnDragMove_;
                break;
            case DragFuncType::DRAG_DROP:
                dragFunc = customerOnDrop_;
                break;
            default:
                LOGW("unsuport dragFuncType");
                break;
        }
        return dragFunc;
    }

    const OnNewDragFunc& GetCustomerOnDragEndFunc() const
    {
        return customerOnDragEnd_;
    }

    void ClearCustomerOnDragFunc();

    void FireCustomerOnDragFunc(
        DragFuncType dragFuncType, const RefPtr<OHOS::Ace::DragEvent>& info, const std::string& extraParams = "");

    bool IsFireOnDrop(const RefPtr<OHOS::Ace::DragEvent>& info);

    void HandleInternalOnDrop(const RefPtr<OHOS::Ace::DragEvent>& info, const std::string& extraParams);

    void PostEnabledTask();

    void AddInnerOnAreaChangedCallback(int32_t id, OnAreaChangedFunc&& callback);

    void RemoveInnerOnAreaChangedCallback(int32_t id);

    void ClearOnAreaChangedInnerCallbacks();

    bool HasImmediatelyVisibleCallback();

    std::vector<double>& GetThrottledVisibleAreaRatios()
    {
        return throttledVisibleAreaRatios_;
    }

    VisibleCallbackInfo& GetThrottledVisibleAreaCallback()
    {
        return throttledVisibleAreaCallback_;
    }

    std::vector<double>& GetVisibleAreaRatios(bool isUser)
    {
        if (isUser) {
            return visibleAreaUserRatios_;
        } else {
            return visibleAreaInnerRatios_;
        }
    }

    VisibleCallbackInfo& GetVisibleAreaCallback(bool isUser)
    {
        if (isUser) {
            return visibleAreaUserCallback_;
        } else {
            return visibleAreaInnerCallback_;
        }
    }

    void SetVisibleAreaRatiosAndCallback(
        const VisibleCallbackInfo& callback, const std::vector<double>& radios, bool isUser)
    {
        if (isUser) {
            VisibleCallbackInfo* cbInfo =
                (callback.period == 0) ? &visibleAreaUserCallback_ : &throttledVisibleAreaCallback_;
            auto ratioInfo = (callback.period == 0) ? &visibleAreaUserRatios_ : &throttledVisibleAreaRatios_;
            *cbInfo = callback;
            *ratioInfo = radios;
        } else {
            visibleAreaInnerCallback_ = callback;
            visibleAreaInnerRatios_ = radios;
        }
    }

    void CleanVisibleAreaCallback(bool isUser, bool isThrottled = false)
    {
        if (!isUser) {
            visibleAreaInnerRatios_.clear();
            visibleAreaInnerCallback_.callback = nullptr;
        } else if (isThrottled) {
            throttledVisibleAreaRatios_.clear();
            throttledVisibleAreaCallback_.callback = nullptr;
        } else {
            visibleAreaUserRatios_.clear();
            visibleAreaUserCallback_.callback = nullptr;
        }
    }

    void SetDefaultOnDragStart(OnDragStartFunc&& defaultOnDragStart)
    {
        defaultOnDragStart_ = std::move(defaultOnDragStart);
    }

    const OnDragStartFunc& GetDefaultOnDragStart() const
    {
        return defaultOnDragStart_;
    }

    bool HasDefaultOnDragStart() const
    {
        return static_cast<bool>(defaultOnDragStart_);
    }

    bool HasVisibleAreaCallback(bool isUser)
    {
        if (isUser) {
            return static_cast<bool>(visibleAreaUserCallback_.callback);
        } else {
            return static_cast<bool>(visibleAreaInnerCallback_.callback);
        }
    }

    void SetOnAttach(std::function<void()>&& onAttach);
    void ClearOnAttach();
    void FireOnAttach();
    void SetOnDetach(std::function<void()>&& onDetach);
    void ClearOnDetach();
    void FireOnDetach();
    void ClearStateStyle();
    void OnDetachClear();

protected:
    virtual void OnModifyDone() {}
    std::function<void()> onAppear_;
    std::function<void()> onJSFrameNodeAppear_;

private:
    WeakPtr<FrameNode> host_;
    RefPtr<GestureEventHub> gestureEventHub_;
    RefPtr<InputEventHub> inputEventHub_;
    RefPtr<FocusHub> focusHub_;
    RefPtr<StateStyleManager> stateStyleMgr_;

    std::function<void()> onDisappear_;
    std::function<void()> onJSFrameNodeDisappear_;
    OnAreaChangedFunc onAreaChanged_;
    std::unordered_map<int32_t, OnAreaChangedFunc> onAreaChangedInnerCallbacks_;
    OnSizeChangedFunc onSizeChanged_;
    std::unordered_map<int32_t, OnSizeChangedFunc> onSizeChangedInnerCallbacks_;
    OnSizeChangedFunc onJsFrameNodeSizeChanged_;

    std::function<void()> onAttach_;
    std::function<void()> onDetach_;

    OnPreDragFunc onPreDragFunc_;
    OnDragStartFunc onDragStart_;
    OnDragFunc onDragEnter_;
    OnDragFunc onDragLeave_;
    OnDragFunc onDragMove_;
    OnDragFunc onDrop_;
    OnNewDragFunc onDragEnd_;

    OnDragStartFunc defaultOnDragStart_;
    OnDragFunc customerOnDragEnter_;
    OnDragFunc customerOnDragLeave_;
    OnDragFunc customerOnDragMove_;
    OnDragFunc customerOnDrop_;
    OnNewDragFunc customerOnDragEnd_;

    bool enabled_ { true };
    bool developerEnabled_ { true };
    std::vector<KeyboardShortcut> keyboardShortcut_;

    std::vector<double> visibleAreaUserRatios_;
    VisibleCallbackInfo visibleAreaUserCallback_;
    std::vector<double> visibleAreaInnerRatios_;
    VisibleCallbackInfo visibleAreaInnerCallback_;
    std::vector<double> throttledVisibleAreaRatios_;
    VisibleCallbackInfo throttledVisibleAreaCallback_;

    ACE_DISALLOW_COPY_AND_MOVE(EventHub);
};

class TextCommonEvent : public BaseEventInfo {
    DECLARE_RELATIONSHIP_OF_CLASSES(TextCommonEvent, BaseEventInfo)
public:
    TextCommonEvent() : BaseEventInfo("TextCommonEvent") {}
    ~TextCommonEvent() override = default;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_EVENT_HUB_H
