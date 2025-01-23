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

enum class VisibleAreaChangeTriggerReason : int32_t {
    IDLE = 0,
    VISIBLE_AREA_CHANGE = 1,
    DETACH_FROM_MAINTREE = 2,
    BACKGROUND = 3,
    SELF_INVISIBLE = 4,
    FRAMENODE_DESTROY = 5,
    IS_NOT_ON_MAINTREE = 6,
    ANCESTOR_INVISIBLE = 7,
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

    const RefPtr<GestureEventHub>& GetOrCreateGestureEventHub();

    virtual RefPtr<GestureEventHub> CreateGestureEventHub()
    {
        return MakeRefPtr<GestureEventHub>(WeakClaim(this));
    }

    const RefPtr<GestureEventHub>& GetGestureEventHub() const;
    void SetGestureEventHub(const RefPtr<GestureEventHub>& gestureEventHub);
    const RefPtr<InputEventHub>& GetOrCreateInputEventHub();
    const RefPtr<InputEventHub>& GetInputEventHub() const;
    RefPtr<FocusHub> GetOrCreateFocusHub(FocusType type = FocusType::DISABLE, bool focusable = false,
        FocusStyleType focusStyleType = FocusStyleType::NONE,
        const std::unique_ptr<FocusPaintParam>& paintParamsPtr = nullptr);
    RefPtr<FocusHub> GetOrCreateFocusHub(const FocusPattern& focusPattern);
    RefPtr<FocusHub> GetFocusHub() const;
    void AttachHost(const WeakPtr<FrameNode>& host);
    void OnAttachContext(PipelineContext* context);
    void OnDetachContext(PipelineContext* context);
    RefPtr<FrameNode> GetFrameNode() const;
    GetEventTargetImpl CreateGetEventTargetImpl() const;
    void OnContextAttached();
    void ClearUserOnAppear();
    void SetOnAppear(std::function<void()>&& onAppear);
    void SetJSFrameNodeOnAppear(std::function<void()>&& onAppear);
    void ClearJSFrameNodeOnAppear();
    virtual void FireOnAppear();
    void ClearUserOnDisAppear();
    void SetOnDisappear(std::function<void()>&& onDisappear);
    void SetJSFrameNodeOnDisappear(std::function<void()>&& onDisappear);
    void ClearJSFrameNodeOnDisappear();
    virtual void FireOnDisappear();
    void ClearUserOnAreaChanged();
    void SetOnAreaChanged(OnAreaChangedFunc&& onAreaChanged);
    void FireOnAreaChanged(const RectF& oldRect, const OffsetF& oldOrigin, const RectF& rect, const OffsetF& origin);
    void FireInnerOnAreaChanged(
        const RectF& oldRect, const OffsetF& oldOrigin, const RectF& rect, const OffsetF& origin);
    bool HasOnAreaChanged() const;
    bool HasInnerOnAreaChanged() const;
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
    void SetOnPreDrag(OnPreDragFunc&& onPreDragFunc);
    const OnPreDragFunc& GetOnPreDrag() const;
    void SetOnDragStart(OnDragStartFunc&& onDragStart);

    const OnDragStartFunc& GetOnDragStart() const
    {
        return onDragStart_;
    }

    bool HasOnDragStart() const;
    void SetOnDragEnter(OnDragFunc&& onDragEnter);
    void FireOnDragEnter(const RefPtr<OHOS::Ace::DragEvent>& info, const std::string& extraParams);
    void SetOnDragLeave(OnDragFunc&& onDragLeave);
    void FireOnDragLeave(const RefPtr<OHOS::Ace::DragEvent>& info, const std::string& extraParams);
    void SetOnDragMove(OnDragFunc&& onDragMove);
    void FireOnDragMove(const RefPtr<OHOS::Ace::DragEvent>& info, const std::string& extraParams);
    bool HasOnDragMove() const;
    void SetOnDrop(OnDragFunc&& onDrop);
    void SetOnDragEnd(OnNewDragFunc&& onDragEnd);
    const OnNewDragFunc& GetOnDragEnd() const
    {
        return onDragEnd_;
    }
    bool HasOnDragEnter() const;
    bool HasOnDragLeave() const;
    bool HasOnDragEnd() const;

    virtual bool HasOnItemDragMove()
    {
        return false;
    }

    virtual bool HasOnItemDrop()
    {
        return false;
    }

    void FireOnDrop(const RefPtr<OHOS::Ace::DragEvent>& info, const std::string& extraParams);
    bool HasOnDrop() const;
    bool HasCustomerOnDragEnter() const;
    bool HasCustomerOnDragLeave() const;
    bool HasCustomerOnDragMove() const;
    bool HasCustomerOnDragEnd() const;
    bool HasCustomerOnDrop() const;
    void SetDisableDataPrefetch(bool disableDataPrefetch);
    bool GetDisableDataPrefetch() const;

    virtual std::string GetDragExtraParams(const std::string& extraInfo, const Point& point, DragEventType isStart)
    {
        auto json = JsonUtil::Create(true);
        if (!extraInfo.empty()) {
            json->Put("extraInfo", extraInfo.c_str());
        }
        return json->ToString();
    }

    bool IsEnabled() const;
    bool IsDeveloperEnabled() const;
    void SetEnabled(bool enabled);
    void SetEnabledInternal(bool enabled);
    // restore enabled value to what developer sets
    void RestoreEnabled();
    // get XTS inspector value
    virtual void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const {}
    virtual void FromJson(const std::unique_ptr<JsonValue>& json) {}
    void MarkModifyDone();
    void SetCurrentUIState(UIState state, bool flag);
    void UpdateCurrentUIState(UIState state);
    void ResetCurrentUIState(UIState state);
    UIState GetCurrentUIState() const;
    bool HasStateStyle(UIState state) const;
    void AddSupportedState(UIState state);
    void SetSupportedStates(UIState state);
    bool IsCurrentStateOn(UIState state);
    void SetKeyboardShortcut(
        const std::string& value, uint8_t keys, const std::function<void()>& onKeyboardShortcutAction);
    void ClearSingleKeyboardShortcut();
    std::vector<KeyboardShortcut>& GetKeyboardShortcut();
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
    void ClearCustomerOnDragStart();
    void ClearCustomerOnDragEnter();
    void ClearCustomerOnDragMove();
    void ClearCustomerOnDragLeave();
    void ClearCustomerOnDrop();
    void ClearCustomerOnDragEnd();
    void FireCustomerOnDragFunc(
        DragFuncType dragFuncType, const RefPtr<OHOS::Ace::DragEvent>& info, const std::string& extraParams = "");
    bool IsFireOnDrop(const RefPtr<OHOS::Ace::DragEvent>& info);
    void HandleInternalOnDrop(const RefPtr<OHOS::Ace::DragEvent>& info, const std::string& extraParams);
    void PostEnabledTask();
    void FireEnabledTask();
    void AddInnerOnAreaChangedCallback(int32_t id, OnAreaChangedFunc&& callback);
    void RemoveInnerOnAreaChangedCallback(int32_t id);
    void ClearOnAreaChangedInnerCallbacks();
    bool HasImmediatelyVisibleCallback();
    void SetDefaultOnDragStart(OnDragStartFunc&& defaultOnDragStart);

    const OnDragStartFunc& GetDefaultOnDragStart() const
    {
        return defaultOnDragStart_;
    }

    bool HasDefaultOnDragStart() const;
    std::vector<double>& GetThrottledVisibleAreaRatios();
    VisibleCallbackInfo& GetThrottledVisibleAreaCallback();
    std::vector<double>& GetVisibleAreaRatios(bool isUser);
    VisibleCallbackInfo& GetVisibleAreaCallback(bool isUser);
    void SetVisibleAreaRatiosAndCallback(
        const VisibleCallbackInfo& callback, const std::vector<double>& radios, bool isUser);
    void CleanVisibleAreaCallback(bool isUser, bool isThrottled = false);
    bool HasVisibleAreaCallback(bool isUser);
    void SetOnAttach(std::function<void()>&& onAttach);
    void ClearOnAttach();
    virtual void FireOnAttach();
    void SetOnDetach(std::function<void()>&& onDetach);
    void ClearOnDetach();
    void ClearOnPreDrag();
    virtual void FireOnDetach();
    void SetOnWillBind(std::function<void(int32_t)>&& onWillBind);
    void ClearOnWillBind();
    virtual void FireOnWillBind(int32_t containerId);
    void SetOnWillUnbind(std::function<void(int32_t)>&& onWillUnbind);
    void ClearOnWillUnbind();
    virtual void FireOnWillUnbind(int32_t containerId);
    void SetOnBind(std::function<void(int32_t)>&& onBind);
    void ClearOnBind();
    virtual void FireOnBind(int32_t containerId);
    void SetOnUnbind(std::function<void(int32_t)>&& onUnbind);
    void ClearOnUnbind();
    virtual void FireOnUnbind(int32_t containerId);
    void ClearStateStyle();
    void OnDetachClear();
    void HandleOnAreaChange(const std::unique_ptr<RectF>& lastFrameRect,
        const std::unique_ptr<OffsetF>& lastParentOffsetToWindow,
        const RectF& currFrameRect, const OffsetF& currParentOffsetToWindow);
    void FireUntriggeredInnerOnAreaChanged(
        const RectF& oldRect, const OffsetF& oldOrigin, const RectF& rect, const OffsetF& origin);
    void FireDrawCompletedNDKCallback(PipelineContext* pipeline);
    void FireLayoutNDKCallback(PipelineContext* pipeline);
    void SetNDKDrawCompletedCallback(std::function<void()>&& callback)
    {
        ndkDrawCompletedCallback_ = std::move(callback);
    }
    void SetNDKLayoutCallback(std::function<void()>&& callback)
    {
        ndkLayoutCallback_ = std::move(callback);
    }
    bool HasNDKDrawCompletedCallback()
    {
        return !!ndkDrawCompletedCallback_;
    }
    

protected:
    virtual void OnModifyDone() {}
    std::function<void()> onAppear_;
    std::function<void()> onJSFrameNodeAppear_;

private:
    WeakPtr<FrameNode> host_;
    RefPtr<GestureEventHub> gestureEventHub_;
    RefPtr<InputEventHub> inputEventHub_;
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
    std::function<void(int32_t)> onWillBind_;
    std::function<void(int32_t)> onWillUnbind_;
    std::function<void(int32_t)> onBind_;
    std::function<void(int32_t)> onUnbind_;

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
    bool disableDataPrefetch_ { false };
    std::vector<KeyboardShortcut> keyboardShortcut_;
    std::vector<int32_t> hasInnerAreaChangeUntriggered_;

    std::vector<double> visibleAreaUserRatios_;
    VisibleCallbackInfo visibleAreaUserCallback_;
    std::vector<double> visibleAreaInnerRatios_;
    VisibleCallbackInfo visibleAreaInnerCallback_;
    std::vector<double> throttledVisibleAreaRatios_;
    VisibleCallbackInfo throttledVisibleAreaCallback_;
    std::function<void()> ndkDrawCompletedCallback_;
    std::function<void()> ndkLayoutCallback_;
    std::function<void()> enabledFunc_;

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
