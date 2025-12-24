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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_OBSERVER_HANDLER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_OBSERVER_HANDLER_H

#include <functional>
#include <optional>
#include <string>
#include <utility>

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/common/frontend.h"
#include "core/common/container.h"
#include "core/common/window_size_breakpoint.h"
#include "core/components_ng/pattern/navigation/navigation_declaration.h"
#include "core/components_ng/pattern/stage/page_pattern.h"

namespace OHOS::Ace::NG {
enum class NavDestinationState {
    NONE = -1,
    ON_SHOWN = 0,
    ON_HIDDEN = 1,
    ON_APPEAR = 2,
    ON_DISAPPEAR = 3,
    ON_WILL_SHOW = 4,
    ON_WILL_HIDE = 5,
    ON_WILL_APPEAR = 6,
    ON_WILL_DISAPPEAR = 7,
    ON_ACTIVE = 8,
    ON_INACTIVE = 9,
    ON_BACKPRESS = 100,
};

struct NavDestinationInfo {
    std::string navigationId;
    std::string name;
    NavDestinationState state;
    int32_t index;
    napi_value param;
    std::string interopParam;
    std::string navDestinationId;
    NavDestinationMode mode;
    int32_t uniqueId;
    int32_t navigationUniqueId = -1; //Internal use only
    std::optional<SizeF> size;

    NavDestinationInfo() = default;

    NavDestinationInfo(std::string id, std::string name, NavDestinationState state)
        : navigationId(std::move(id)), name(std::move(name)), state(state)
    {}

    NavDestinationInfo(std::string id, std::string name, NavDestinationState state,
        int32_t index, napi_value param, std::string navDesId)
        : navigationId(std::move(id)), name(std::move(name)), state(state),
          index(index), param(param), navDestinationId(std::move(navDesId))
    {}

    NavDestinationInfo(std::string id, std::string name, NavDestinationState state,
        int32_t index, napi_value param, std::string navDesId, NavDestinationMode mode, int32_t uniqueId)
        : navigationId(std::move(id)), name(std::move(name)), state(state),
        index(index), param(param), navDestinationId(std::move(navDesId)), mode(mode), uniqueId(std::move(uniqueId))
    {}

    NavDestinationInfo(std::string id, std::string name, NavDestinationState state, int32_t index, napi_value param,
        std::string navDesId, NavDestinationMode mode, int32_t uniqueId, int32_t navigationUniqueId)
        : navigationId(std::move(id)), name(std::move(name)), state(state), index(index), param(param),
          navDestinationId(std::move(navDesId)), mode(mode),
          uniqueId(std::move(uniqueId)), navigationUniqueId(std::move(navigationUniqueId))
    {}

    NavDestinationInfo(std::string id, std::string name, NavDestinationState state, int32_t index, napi_value param,
                       std::string navDesId, NavDestinationMode mode, int32_t uniqueId, std::optional<SizeF> size)
        : navigationId(std::move(id)),
          name(std::move(name)),
          state(state),
          index(index),
          param(param),
          navDestinationId(std::move(navDesId)),
          mode(mode),
          uniqueId(std::move(uniqueId)),
          size(std::move(size))
    {}

    NavDestinationInfo(std::string id, std::string name, NavDestinationState state, int32_t index, napi_value param,
                       std::string navDesId, NavDestinationMode mode, int32_t uniqueId, int32_t navigationUniqueId,
                       std::optional<SizeF> size)
        : navigationId(std::move(id)),
          name(std::move(name)),
          state(state),
          index(index),
          param(param),
          navDestinationId(std::move(navDesId)),
          mode(mode),
          uniqueId(std::move(uniqueId)),
          navigationUniqueId(std::move(navigationUniqueId)),
          size(std::move(size))
    {}
};

enum class ScrollEventType {
    SCROLL_START = 0,
    SCROLL_STOP = 1,
};

struct ScrollEventInfo {
    std::string id;
    int32_t uniqueId;
    ScrollEventType scrollEvent;
    float offset;
    Ace::Axis axis;

    ScrollEventInfo(std::string id, int32_t uniqueId, ScrollEventType scrollEvent, float offset, Ace::Axis axis)
        : id(std::move(id)), uniqueId(uniqueId), scrollEvent(scrollEvent), offset(offset), axis(axis)
    {}
};

struct NavDestinationSwitchInfo {
    // UIContext
    std::optional<NavDestinationInfo> from;
    std::optional<NavDestinationInfo> to;
    NavigationOperation operation;

    NavDestinationSwitchInfo(std::optional<NavDestinationInfo>&& fromInfo, std::optional<NavDestinationInfo>&& toInfo,
        NavigationOperation op)
        : from(std::forward<std::optional<NavDestinationInfo>>(fromInfo)),
          to(std::forward<std::optional<NavDestinationInfo>>(toInfo)), operation(op)
    {}
};

struct RouterPageInfoNG {
    int32_t index;
    std::string name;
    std::string path;
    RouterPageState state;
    std::string pageId;
    std::optional<SizeF> size;

    RouterPageInfoNG(int32_t index, std::string name, std::string path, RouterPageState state,
        std::string pageId)
        : index(index), name(std::move(name)), path(std::move(path)), state(state),
          pageId(std::move(pageId))
    {}
    RouterPageInfoNG(int32_t index, std::string name, std::string path, RouterPageState state,
        std::string pageId, std::optional<SizeF> size)
        : index(index), name(std::move(name)), path(std::move(path)), state(state),
          pageId(std::move(pageId)), size(size)
    {}
};

struct AbilityContextInfo {
    std::string name = "";
    std::string bundleName = "";
    std::string moduleName = "";

    bool IsEqual(const AbilityContextInfo& info) const
    {
        return name == info.name && bundleName == info.bundleName && moduleName == info.moduleName;
    }
};

enum class TabContentState {
    ON_SHOW = 0,
    ON_HIDE = 1,
};

struct TabContentInfo {
    std::string tabContentId;
    int32_t tabContentUniqueId = 0;
    TabContentState state;
    int32_t index = 0;
    std::string id;
    int32_t uniqueId = 0;
    std::optional<int32_t> lastIndex;

    TabContentInfo(std::string tabContentId, int32_t tabContentUniqueId, TabContentState state, int32_t index,
        std::string id, int32_t uniqueId)
        : tabContentId(std::move(tabContentId)), tabContentUniqueId(tabContentUniqueId), state(state), index(index),
        id(std::move(id)), uniqueId(uniqueId)
    {}
};

enum class PanGestureState {
    BEFORE = 0,
    AFTER = 1,
};

struct PanGestureInfo {
    PanGestureState gestureState;
    CurrentCallbackState callbackState;
};

struct TextChangeEventInfo {
    std::string id;
    int32_t uniqueId;
    std::string content;
    TextChangeEventInfo(std::string id, int32_t uniqueId, std::string content)
        : id(std::move(id)), uniqueId(uniqueId), content(std::move(content))
    {}
};

struct SwiperItemInfoNG {
    int32_t uniqueId = -1;
    int32_t index = -1;

    SwiperItemInfoNG(int32_t uniqueId, int32_t index)
        : uniqueId(uniqueId), index(index)
    {}
};

struct SwiperContentInfo {
    std::string id = "";
    int32_t uniqueId = -1;
    std::vector<SwiperItemInfoNG> swiperItemInfos = {};
};

enum class GestureListenerType { TAP = 0, LONG_PRESS, PAN, PINCH, SWIPE, ROTATION, UNKNOWN };

enum class GestureActionPhase { WILL_START = 0, WILL_END = 1, UNKNOWN = 2 };

class ACE_FORCE_EXPORT UIObserverHandler {
public:
    UIObserverHandler() = default;
    ~UIObserverHandler() = default;
    static UIObserverHandler& GetInstance();
    void NotifyNavigationStateChange(const WeakPtr<AceType>& weakPattern, NavDestinationState state);
    void NotifyNavigationStateChangeForAni(const WeakPtr<AceType>& weakPattern, NavDestinationState state);
    void NotifyScrollEventStateChange(const WeakPtr<AceType>& weakPattern, ScrollEventType scrollEvent);
    void NotifyRouterPageStateChange(
        const RefPtr<PageInfo>& pageInfo, RouterPageState state, const std::optional<SizeF>& size);
    void NotifyRouterPageStateChangeForAni(
        const RefPtr<PageInfo>& pageInfo, RouterPageState state, const std::optional<SizeF>& size);
    void NotifyDensityChange(double density);
    void NotifyWillClick(const GestureEvent& gestureEventInfo,
        const ClickInfo& clickInfo, const RefPtr<FrameNode>& frameNode);
    void NotifyDidClick(const GestureEvent& gestureEventInfo,
        const ClickInfo& clickInfo, const RefPtr<FrameNode>& frameNode);
    void NotifyPanGestureStateChange(const GestureEvent& gestureEventInfo,
        const RefPtr<PanRecognizer>& current, const RefPtr<FrameNode>& frameNode,
        const PanGestureInfo& panGestureInfo);
    void NotifyTabContentStateUpdate(const TabContentInfo& info);
    void NotifyTabContentStateUpdateForAni(const TabContentInfo& info);
    void NotifyTabChange(const TabContentInfo& info);
    void NotifyGestureStateChange(NG::GestureListenerType gestureListenerType, const GestureEvent& gestureEventInfo,
        const RefPtr<NGGestureRecognizer>& current, const RefPtr<FrameNode>& frameNode, NG::GestureActionPhase phase);
    std::shared_ptr<NavDestinationInfo> GetNavigationState(const RefPtr<AceType>& node);
    std::shared_ptr<NavDestinationInfo> GetNavDestinationInfo(const RefPtr<UINode>& current);
    std::shared_ptr<NavDestinationInfo> GetNavigationInnerState(const RefPtr<AceType>& node);
    std::shared_ptr<NavDestinationInfo> GetNavigationOuterState(const RefPtr<AceType>& node);
    std::shared_ptr<ScrollEventInfo> GetScrollEventState(const RefPtr<AceType>& node);
    std::shared_ptr<RouterPageInfoNG> GetRouterPageState(const RefPtr<AceType>& node);
    void NotifyNavDestinationSwitch(std::optional<NavDestinationInfo>&& from,
        std::optional<NavDestinationInfo>&& to, NavigationOperation operation);
    void NotifyNavDestinationSwitchForAni(std::optional<NavDestinationInfo>& from,
        std::optional<NavDestinationInfo>& to, NavigationOperation operation);
    void NotifyTextChangeEvent(const TextChangeEventInfo& info);
    void NotifyRouterPageSizeChange(const RefPtr<PageInfo>& pageInfo,
        RouterPageState state, const std::optional<SizeF>& size);
    void NotifyNavDestinationSizeChange(const WeakPtr<AceType>& weakPattern,
        NavDestinationState state, const std::optional<SizeF>& size);
    void NotifySwiperContentUpdate(const SwiperContentInfo& info);
    bool IsSwiperContentObserverEmpty();
    void NotifyWinSizeLayoutBreakpointChangeFunc(int32_t instanceId, const WindowSizeBreakpoint& info);
    using NavigationHandleFunc = void (*)(const NavDestinationInfo& info);
    using ScrollEventHandleFunc = void (*)(const std::string&, int32_t, ScrollEventType, float, Ace::Axis);
    using ScrollEventHandleFuncForAni = std::function<void(const ScrollEventInfo& info)>;
    using RouterPageHandleFunc = void (*)(AbilityContextInfo&, const RouterPageInfoNG&);
    using RouterPageHandleFuncForAni = std::function<void(AbilityContextInfo&, const RouterPageInfoNG&)>;
    using DrawCommandSendHandleFunc = std::function<void()>;
    using LayoutDoneHandleFunc = std::function<void()>;
    using NavDestinationSwitchHandleFunc = void (*)(const AbilityContextInfo&, NavDestinationSwitchInfo&);
    using NavDestinationSwitchHandleFuncForAni = std::function<void(NavDestinationSwitchInfo&)>;
    using WillClickHandleFunc = void (*)(
        AbilityContextInfo&, const GestureEvent&, const ClickInfo&, const RefPtr<FrameNode>&);
    using DidClickHandleFunc = void (*)(
        AbilityContextInfo&, const GestureEvent&, const ClickInfo&, const RefPtr<FrameNode>&);
    using PanGestureHandleFunc = void (*)(AbilityContextInfo&, const GestureEvent&,
        const RefPtr<PanRecognizer>& current, const RefPtr<FrameNode>&, const NG::PanGestureInfo& panGestureInfo);
    using GestureHandleFunc = void (*)(NG::GestureListenerType gestureListenerType,
        const GestureEvent& gestureEventInfo, const RefPtr<NG::NGGestureRecognizer>& current,
        const RefPtr<NG::FrameNode>& frameNode, NG::GestureActionPhase phase);
    using TabContentStateHandleFunc = void (*)(const TabContentInfo&);
    using TabChangeHandleFunc = void (*)(const TabContentInfo&);
    using TabChangeHandleFuncForAni = std::function<void(const TabContentInfo& info)>;
    using NavigationHandleFuncForAni = std::function<void(const NG::NavDestinationInfo& info)>;
    using TabContentHandleFuncForAni = std::function<void(const NG::TabContentInfo& info)>;
    using TextChangeEventHandleFunc = void (*)(const TextChangeEventInfo&);
    using SwiperContentUpdateHandleFunc = void (*)(const SwiperContentInfo&);
    using SwiperContentObservrEmptyFunc = bool (*)();
    using RouterPageSizeChangeHandleFunc = void (*)(const RouterPageInfoNG&);
    using NavDestinationSizeChangeHandleFunc = void (*)(const NavDestinationInfo&);
    using NavDestinationSizeChangeByUniqueIdHandleFunc = void (*)(const NavDestinationInfo&);
    using RouterPageSizeChangeHandleFuncForAni = std::function<void(const RouterPageInfoNG&)>;
    using NavDestinationSizeChangeHandleFuncForAni = std::function<void(const NavDestinationInfo&)>;
    using NavDestinationSizeChangeByUniqueIdHandleFuncForAni = std::function<void(const NavDestinationInfo&)>;
    NavDestinationSwitchHandleFunc GetHandleNavDestinationSwitchFunc();
    NavDestinationSwitchHandleFuncForAni GetHandleNavDestinationSwitchFuncForAni();
    void SetHandleNavigationChangeFunc(NavigationHandleFunc func);
    void SetHandleNavigationChangeFuncForAni(NavigationHandleFuncForAni func);
    void SetHandleScrollEventChangeFunc(ScrollEventHandleFunc func);
    void SetHandleScrollEventChangeFuncForAni(ScrollEventHandleFuncForAni func);
    void SetHandleRouterPageChangeFunc(RouterPageHandleFunc func);
    void SetHandleRouterPageChangeFuncForAni(RouterPageHandleFuncForAni func);
    using DensityHandleFunc = void (*)(AbilityContextInfo&, double);
    using WinSizeLayoutBreakpointHandleFunc = void (*)(int32_t instanceId, const WindowSizeBreakpoint& info);
    using DensityHandleFuncForAni = std::function<void(AbilityContextInfo&, double)>;
    void SetHandleDensityChangeFunc(DensityHandleFunc func);
    void SetHandleDensityChangeFuncForAni(DensityHandleFuncForAni func);
    void SetHandleTabContentUpdateFuncForAni(TabContentHandleFuncForAni func);
    void SetWinSizeLayoutBreakpointChangeFunc(WinSizeLayoutBreakpointHandleFunc func);
    void SetLayoutDoneHandleFunc(DrawCommandSendHandleFunc func);
    void HandleLayoutDoneCallBack();
    void SetDrawCommandSendHandleFunc(LayoutDoneHandleFunc func);
    void HandleDrawCommandSendCallBack();
    void SetHandleNavDestinationSwitchFunc(NavDestinationSwitchHandleFunc func);
    void SetHandleNavDestinationSwitchFuncForAni(NavDestinationSwitchHandleFuncForAni func);
    void SetWillClickFunc(WillClickHandleFunc func);
    void SetDidClickFunc(DidClickHandleFunc func);
    void SetPanGestureHandleFunc(PanGestureHandleFunc func);
    void SetHandleTabContentStateUpdateFunc(TabContentStateHandleFunc func);
    void SetHandleTabChangeFunc(TabChangeHandleFunc func);
    void SetHandleTabChangeFuncForAni(TabChangeHandleFuncForAni func);
    void SetHandleGestureHandleFunc(GestureHandleFunc func);

    using BeforePanStartHandleFuncForAni = std::function<void()>;
    void SetBeforePanStartHandleFuncForAni(BeforePanStartHandleFuncForAni func);
    using AfterPanStartHandleFuncForAni = std::function<void()>;
    void SetAfterPanStartHandleFuncForAni(AfterPanStartHandleFuncForAni func);
    using BeforePanEndHandleFuncForAni = std::function<void()>;
    void SetBeforePanEndHandleFuncForAni(BeforePanEndHandleFuncForAni func);
    using AfterPanEndHandleFuncForAni = std::function<void()>;
    void SetAfterPanEndHandleFuncForAni(AfterPanEndHandleFuncForAni func);

    using WillClickHandleFuncForAni = std::function<void()>;
    void SetWillClickHandleFuncForAni(WillClickHandleFuncForAni func);
    using DidClickHandleFuncForAni = std::function<void()>;
    void SetDidClickHandleFuncForAni(DidClickHandleFuncForAni func);
    void SetHandleTextChangeEventFunc(TextChangeEventHandleFunc&& func);
    void SetSwiperContentUpdateHandleFunc(SwiperContentUpdateHandleFunc&& func);
    void SetSwiperContentObservrEmptyFunc(SwiperContentObservrEmptyFunc&& func);
    void SetRouterPageSizeChangeHandleFunc(RouterPageSizeChangeHandleFunc func);
    void SetNavDestinationSizeChangeHandleFunc(NavDestinationSizeChangeHandleFunc func);
    void SetNavDestinationSizeChangeByUniqueIdHandleFunc(NavDestinationSizeChangeByUniqueIdHandleFunc func);
    void SetRouterPageSizeChangeHandleFuncForAni(RouterPageSizeChangeHandleFuncForAni&& func);
    void SetNavDestinationSizeChangeHandleFuncForAni(NavDestinationSizeChangeHandleFuncForAni&& func);
    void SetNavDestinationSizeChangeByUniqueIdHandleFuncForAni(
        NavDestinationSizeChangeByUniqueIdHandleFuncForAni&& func);
private:
    NavigationHandleFunc navigationHandleFunc_ = nullptr;
    NavigationHandleFuncForAni navigationHandleFuncForAni_ = nullptr;
    ScrollEventHandleFunc scrollEventHandleFunc_ = nullptr;
    ScrollEventHandleFuncForAni scrollEventHandleFuncForAni_ = nullptr;
    RouterPageHandleFunc routerPageHandleFunc_ = nullptr;
    RouterPageHandleFuncForAni routerPageHandleFuncForAni_ = nullptr;
    LayoutDoneHandleFunc layoutDoneHandleFunc_ = nullptr;
    DrawCommandSendHandleFunc drawCommandSendHandleFunc_ = nullptr;
    DensityHandleFunc densityHandleFunc_ = nullptr;
    WinSizeLayoutBreakpointHandleFunc winSizeLayoutBreakpointHandleFunc_ = nullptr;
    DensityHandleFuncForAni densityHandleFuncForAni_ = nullptr;
    NavDestinationSwitchHandleFunc navDestinationSwitchHandleFunc_ = nullptr;
    NavDestinationSwitchHandleFuncForAni navDestinationSwitchHandleFuncForAni_ = nullptr;
    WillClickHandleFunc willClickHandleFunc_ = nullptr;
    DidClickHandleFunc didClickHandleFunc_ = nullptr;
    PanGestureHandleFunc panGestureHandleFunc_ = nullptr;
    TabContentStateHandleFunc tabContentStateHandleFunc_ = nullptr;
    TabContentHandleFuncForAni tabContentHandleFuncForAni_ = nullptr;
    TabChangeHandleFunc tabChangeHandleFunc_ = nullptr;
    TabChangeHandleFuncForAni tabChangeHandleFuncForAni_ = nullptr;
    GestureHandleFunc gestureHandleFunc_ = nullptr;
    TextChangeEventHandleFunc textChangeEventHandleFunc_ = nullptr;
    SwiperContentUpdateHandleFunc swiperContentUpdateHandleFunc_ = nullptr;
    SwiperContentObservrEmptyFunc swiperContentObservrEmptyFunc_ = nullptr;

    BeforePanStartHandleFuncForAni beforePanStartHandleFuncForAni_ = nullptr;
    AfterPanStartHandleFuncForAni afterPanStartHandleFuncForAni_ = nullptr;
    BeforePanEndHandleFuncForAni beforePanEndHandleFuncForAni_ = nullptr;
    AfterPanEndHandleFuncForAni afterPanEndHandleFuncForAni_ = nullptr;

    WillClickHandleFuncForAni willClickHandleFuncForAni_ = nullptr;
    DidClickHandleFuncForAni didClickHandleFuncForAni_ = nullptr;

    RouterPageSizeChangeHandleFunc routerPageSizeChangeHandleFunc_ = nullptr;
    NavDestinationSizeChangeHandleFunc navDestinationSizeChangeHandleFunc_ = nullptr;
    NavDestinationSizeChangeByUniqueIdHandleFunc navDestinationSizeChangeByUniqueIdHandleFunc_ = nullptr;
    RouterPageSizeChangeHandleFuncForAni routerPageSizeChangeHandleFuncForAni_;
    NavDestinationSizeChangeHandleFuncForAni navDestinationSizeChangeHandleFuncForAni_;
    NavDestinationSizeChangeByUniqueIdHandleFuncForAni navDestinationSizeChangeByUniqueIdHandleFuncForAni_;

    napi_value GetUIContextValue();
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_OBSERVER_HANDLER_H
