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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_FOCUS_HANDLER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_EVENT_FOCUS_HANDLER_H

#include "focus_state.h"
#include "core/event/focus_axis_event.h"
#include "core/event/key_event.h"
#include "core/gestures/gesture_event.h"
namespace OHOS::Ace::NG {
#define ACE_DEFINE_FOCUS_EVENT(func, type, name)                               \
public:                                                                        \
    void Set##func(type&& (name))                                              \
    {                                                                          \
        if (!focusCallbackEvents_) {                                           \
            focusCallbackEvents_ = MakeRefPtr<FocusCallbackEvents>();          \
        }                                                                      \
        focusCallbackEvents_->name##_ = std::move(name);                       \
    }                                                                          \
    void Clear##func()                                                         \
    {                                                                          \
        if (focusCallbackEvents_ && focusCallbackEvents_->name##_) {           \
            focusCallbackEvents_->name##_ = nullptr;                           \
        }                                                                      \
    }                                                                          \
    type Get##func()                                                           \
    {                                                                          \
        return focusCallbackEvents_ ? focusCallbackEvents_->name##_ : nullptr; \
    }

enum class FocusIntension : int32_t {
    NONE = 0,
    LEFT,
    UP,
    RIGHT,
    DOWN,
    TAB,
    SHIFT_TAB,
    HOME,
    END,
    SELECT,
    SPACE,
    ESC,
};

struct FocusEvent {
    explicit FocusEvent(const NonPointerEvent& nonPointerEvent)
        : intension(GetFocusIntension(nonPointerEvent)), event(nonPointerEvent)
    {}

    FocusIntension intension;
    const NonPointerEvent& event;
    static FocusIntension GetFocusIntension(const NonPointerEvent& event);
};

class ACE_EXPORT FocusCallbackEvents : public virtual AceType {
    DECLARE_ACE_TYPE(FocusCallbackEvents, AceType)
public:
    FocusCallbackEvents() = default;
    ~FocusCallbackEvents() override = default;

    OnFocusFunc onFocusCallback_;
    OnFocusFunc onJSFrameNodeFocusCallback_;
    OnBlurFunc onBlurCallback_;
    OnBlurFunc onJSFrameNodeBlurCallback_;
    OnKeyConsumeFunc onKeyEventCallback_;
    OnKeyCallbackFunc onJSFrameNodeKeyEventCallback_;
    OnKeyConsumeFunc onKeyPreImeCallback_;
    GestureEventFunc onClickEventCallback_;
    OnFocusAxisEventFunc onFocusAxisEventCallback_;

    WeakPtr<FocusHub> defaultFocusNode_;
    bool isDefaultFocus_ = { false };
    bool isDefaultHasFocused_ = { false };
    bool isDefaultGroupFocus_ = { false };
    bool isDefaultGroupHasFocused_ { false };
    std::optional<bool> isFocusOnTouch_;

    int32_t tabIndex_ = 0;
};

enum class OnKeyEventType : int32_t {
    DEFAULT = 0,
    CONTEXT_MENU = 1,
};

class FocusEventHandler : public virtual FocusState {
    DECLARE_ACE_TYPE(FocusEventHandler, FocusState)
public:
    FocusEventHandler() = default;
    ~FocusEventHandler() override = default;

    void SetOnKeyEventInternal(OnKeyEventFunc&& onKeyEvent, OnKeyEventType type = OnKeyEventType::DEFAULT)
    {
        onKeyEventsInternal_[type] = std::move(onKeyEvent);
    }
    bool FindContextMenuOnKeyEvent(OnKeyEventType type)
    {
        return (onKeyEventsInternal_.find(type) != onKeyEventsInternal_.end());
    }
    bool OnClick(const KeyEvent& event);

protected:
    bool OnFocusEvent(const FocusEvent& event);
    virtual bool HandleFocusTravel(const FocusEvent& event) = 0; // bad design which need to be deleted

    ACE_DEFINE_FOCUS_EVENT(OnFocusCallback, OnFocusFunc, onFocusCallback)
    ACE_DEFINE_FOCUS_EVENT(OnBlurCallback, OnBlurFunc, onBlurCallback)
    ACE_DEFINE_FOCUS_EVENT(JSFrameNodeOnFocusCallback, OnFocusFunc, onJSFrameNodeFocusCallback)
    ACE_DEFINE_FOCUS_EVENT(JSFrameNodeOnBlurCallback, OnBlurFunc, onJSFrameNodeBlurCallback)
    ACE_DEFINE_FOCUS_EVENT(JSFrameNodeOnKeyCallback, OnKeyCallbackFunc, onJSFrameNodeKeyEventCallback)
    ACE_DEFINE_FOCUS_EVENT(OnKeyCallback, OnKeyConsumeFunc, onKeyEventCallback)
    ACE_DEFINE_FOCUS_EVENT(OnKeyPreIme, OnKeyConsumeFunc, onKeyPreImeCallback)
    ACE_DEFINE_FOCUS_EVENT(OnClickCallback, GestureEventFunc, onClickEventCallback)
    ACE_DEFINE_FOCUS_EVENT(OnFocusAxisCallback, OnFocusAxisEventFunc, onFocusAxisEventCallback)

    std::unordered_map<OnKeyEventType, OnKeyEventFunc> onKeyEventsInternal_;
    bool isNodeNeedKey_ { false }; // extension use only
    RefPtr<FocusCallbackEvents> focusCallbackEvents_;

private:
    bool OnFocusEventScope(const FocusEvent& event);
    bool OnFocusEventNode(const FocusEvent& focusEvent);

    bool HandleKeyEvent(const KeyEvent& event, FocusIntension intension);
    bool OnKeyPreIme(KeyEventInfo& info, const KeyEvent& keyEvent);
    bool OnKeyEventNodeInternal(const KeyEvent& keyEvent);
    bool OnKeyEventNodeUser(KeyEventInfo& info, const KeyEvent& keyEvent);
    bool ProcessOnKeyEventInternal(const KeyEvent& event);
    bool HandleFocusAxisEvent(const FocusAxisEvent& event);

    void PrintOnKeyEventUserInfo(const KeyEvent& keyEvent, bool retCallback);
};
} // namespace OHOS::Ace::NG
#endif