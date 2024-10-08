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

#include "bridge/declarative_frontend/jsview/js_tabs_feature.h"

#include "bridge/declarative_frontend/jsview/js_scroller.h"
#include "bridge/declarative_frontend/jsview/js_tabs_controller.h"

namespace OHOS::Ace::Framework {
namespace {
struct ScrollInfo {
    bool isTouching = false;
    bool isScrolling = false;
    bool isAtTop = false;
    bool isAtBottom = false;
};

using RelationInfoMap = std::map<WeakPtr<NG::TabsControllerNG>, bool>;
using BindInfoMap = std::map<WeakPtr<JSScroller>, RelationInfoMap>;
using ScrollInfoMap = std::map<WeakPtr<NG::TabsControllerNG>, ScrollInfo>;

const auto INDEX_ZERO = 0;
const auto INDEX_ONE = 1;
const auto INDEX_TWO = 2;
const auto SHOW_TAB_BAR_DELAY = 2000;
const auto SCROLL_RANGE = 36;

BindInfoMap bindInfoMap_;
ScrollInfoMap scrollInfoMap_;

void HandleOnTouchEvent(WeakPtr<JSScroller> jsScrollerWeak, const TouchEventInfo& info)
{
    auto touchType = info.GetTouches().front().GetTouchType();
    if (touchType != TouchType::DOWN && touchType != TouchType::UP && touchType != TouchType::CANCEL) {
        return;
    }
    auto bindInfoIter = bindInfoMap_.find(jsScrollerWeak);
    if (bindInfoIter == bindInfoMap_.end()) {
        return;
    }
    for (auto& bindInfo : bindInfoIter->second) {
        if (!bindInfo.second) {
            // child scroller don't need to respond touch event.
            continue;
        }
        auto scrollInfoIter = scrollInfoMap_.find(bindInfo.first);
        if (scrollInfoIter == scrollInfoMap_.end()) {
            continue;
        }
        auto tabsController = bindInfo.first.Upgrade();
        if (!tabsController) {
            continue;
        }
        auto& scrollInfo = scrollInfoIter->second;
        if (touchType == TouchType::DOWN) {
            scrollInfo.isTouching = true;
            if (!scrollInfo.isAtTop && !scrollInfo.isAtBottom) {
                tabsController->StopShowTabBar();
            }
        } else if (touchType == TouchType::UP || touchType == TouchType::CANCEL) {
            scrollInfo.isTouching = false;
            if (!scrollInfo.isScrolling) {
                tabsController->StartShowTabBar(SHOW_TAB_BAR_DELAY);
            }
        }
    }
}

void HandleOnPanActionEndEvent(WeakPtr<JSScroller> jsScrollerWeak, const GestureEvent& info)
{
    auto velocity = info.GetMainVelocity();
    if (!NearZero(velocity)) {
        return;
    }
    auto bindInfoIter = bindInfoMap_.find(jsScrollerWeak);
    if (bindInfoIter == bindInfoMap_.end()) {
        return;
    }
    for (auto& bindInfo : bindInfoIter->second) {
        auto tabsController = bindInfo.first.Upgrade();
        if (!tabsController) {
            continue;
        }
        tabsController->StartShowTabBar(SHOW_TAB_BAR_DELAY);
    }
}

void HandleOnReachEvent(WeakPtr<JSScroller> jsScrollerWeak, bool isTopEvent)
{
    auto bindInfoIter = bindInfoMap_.find(jsScrollerWeak);
    if (bindInfoIter == bindInfoMap_.end()) {
        return;
    }
    for (auto& bindInfo : bindInfoIter->second) {
        if (!bindInfo.second) {
            // child scroller don't need to respond reach event.
            continue;
        }
        auto scrollInfoIter = scrollInfoMap_.find(bindInfo.first);
        if (scrollInfoIter == scrollInfoMap_.end()) {
            continue;
        }
        if (isTopEvent) {
            scrollInfoIter->second.isAtTop = true;
        } else {
            scrollInfoIter->second.isAtBottom = true;
        }
    }
}

void HandleOnScrollStartEvent(WeakPtr<JSScroller> jsScrollerWeak)
{
    auto bindInfoIter = bindInfoMap_.find(jsScrollerWeak);
    if (bindInfoIter == bindInfoMap_.end()) {
        return;
    }
    for (auto& bindInfo : bindInfoIter->second) {
        if (!bindInfo.second) {
            // child scroller don't need to respond scroll start event.
            continue;
        }
        auto scrollInfoIter = scrollInfoMap_.find(bindInfo.first);
        if (scrollInfoIter == scrollInfoMap_.end()) {
            continue;
        }
        scrollInfoIter->second.isScrolling = true;
    }
}

void HandleOnScrollStopEvent(WeakPtr<JSScroller> jsScrollerWeak)
{
    auto bindInfoIter = bindInfoMap_.find(jsScrollerWeak);
    if (bindInfoIter == bindInfoMap_.end()) {
        return;
    }
    for (auto& bindInfo : bindInfoIter->second) {
        if (!bindInfo.second) {
            // child scroller don't need to respond scroll stop event.
            continue;
        }
        auto scrollInfoIter = scrollInfoMap_.find(bindInfo.first);
        if (scrollInfoIter == scrollInfoMap_.end()) {
            continue;
        }
        auto tabsController = bindInfo.first.Upgrade();
        if (!tabsController) {
            continue;
        }
        scrollInfoIter->second.isScrolling = false;
        if (!scrollInfoIter->second.isTouching) {
            tabsController->StartShowTabBar(SHOW_TAB_BAR_DELAY);
        }
    }
}

void HandleOnDidScrollEvent(
    WeakPtr<JSScroller> jsScrollerWeak, Dimension dimension, ScrollState state, bool isAtTop, bool isAtBottom)
{
    auto bindInfoIter = bindInfoMap_.find(jsScrollerWeak);
    if (bindInfoIter == bindInfoMap_.end()) {
        return;
    }
    for (auto& bindInfo : bindInfoIter->second) {
        auto scrollInfoIter = scrollInfoMap_.find(bindInfo.first);
        if (scrollInfoIter == scrollInfoMap_.end()) {
            continue;
        }
        auto& scrollInfo = scrollInfoIter->second;
        if ((scrollInfo.isAtTop && isAtTop) || (scrollInfo.isAtBottom && isAtBottom)) {
            continue;
        }
        auto tabsController = bindInfo.first.Upgrade();
        if (tabsController) {
            auto ratio = dimension.ConvertToPx() / Dimension(SCROLL_RANGE, DimensionUnit::VP).ConvertToPx();
            tabsController->UpdateTabBarHiddenRatio(ratio);
            if (bindInfo.second && ((!scrollInfo.isAtTop && isAtTop) || (!scrollInfo.isAtBottom && isAtBottom))) {
                tabsController->StartShowTabBar();
            }
        }
        if (bindInfo.second) {
            scrollInfo.isAtTop = isAtTop;
            scrollInfo.isAtBottom = isAtBottom;
        }
    }
}

ScrollerObserver CreateObserver(WeakPtr<JSScroller> jsScrollerWeak)
{
    ScrollerObserver observer;

    auto touchEvent = [jsScrollerWeak](const TouchEventInfo& info) {
        HandleOnTouchEvent(jsScrollerWeak, info);
    };
    observer.onTouchEvent = AceType::MakeRefPtr<NG::TouchEventImpl>(std::move(touchEvent));

    auto panActionEndEvent = [jsScrollerWeak](const GestureEvent& info) {
        HandleOnPanActionEndEvent(jsScrollerWeak, info);
    };
    observer.onPanActionEndEvent = panActionEndEvent;

    auto reachStartEvent = [jsScrollerWeak]() {
        HandleOnReachEvent(jsScrollerWeak, true);
    };
    observer.onReachStartEvent = std::move(reachStartEvent);

    auto reachEndEvent = [jsScrollerWeak]() {
        HandleOnReachEvent(jsScrollerWeak, false);
    };
    observer.onReachEndEvent = std::move(reachEndEvent);

    auto scrollStartEvent = [jsScrollerWeak]() {
        HandleOnScrollStartEvent(jsScrollerWeak);
    };
    observer.onScrollStartEvent = std::move(scrollStartEvent);

    auto scrollStopEvent = [jsScrollerWeak]() {
        HandleOnScrollStopEvent(jsScrollerWeak);
    };
    observer.onScrollStopEvent = std::move(scrollStopEvent);

    auto didScrollEvent = [jsScrollerWeak](Dimension dimension, ScrollState state, bool isAtTop, bool isAtBottom) {
        HandleOnDidScrollEvent(jsScrollerWeak, dimension, state, isAtTop, isAtBottom);
    };
    observer.onDidScrollEvent = std::move(didScrollEvent);

    return observer;
}

void HandleBindTabsToScrollable(
    const JSRef<JSVal>& jsTabsControllerVal, const JSRef<JSVal>& jsScrollerVal, bool isParentScroller)
{
    auto* jsTabsController = JSRef<JSObject>::Cast(jsTabsControllerVal)->Unwrap<JSTabsController>();
    CHECK_NULL_VOID(jsTabsController);
    auto tabsController = jsTabsController->GetTabsController();
    CHECK_NULL_VOID(tabsController);
    auto tabsControllerWeak = AceType::WeakClaim(AceType::RawPtr(tabsController));
    auto* jsScroller = JSRef<JSObject>::Cast(jsScrollerVal)->Unwrap<JSScroller>();
    CHECK_NULL_VOID(jsScroller);
    auto jsScrollerWeak = AceType::WeakClaim(jsScroller);

    if (scrollInfoMap_.find(tabsControllerWeak) == scrollInfoMap_.end()) {
        ScrollInfo scrollInfo;
        scrollInfoMap_[tabsControllerWeak] = scrollInfo;
    }

    RelationInfoMap relationInfoMap;
    auto bindInfoIter = bindInfoMap_.find(jsScrollerWeak);
    if (bindInfoIter == bindInfoMap_.end()) {
        auto observer = CreateObserver(jsScrollerWeak);
        jsScroller->SetObserver(observer);
    } else {
        relationInfoMap = bindInfoIter->second;
        if (relationInfoMap.find(tabsControllerWeak) != relationInfoMap.end()) {
            return;
        }
    }
    relationInfoMap[tabsControllerWeak] = isParentScroller;
    bindInfoMap_[jsScrollerWeak] = relationInfoMap;
}

void HandleUnbindTabsFromScrollable(const JSRef<JSVal>& jsTabsControllerVal, const JSRef<JSVal>& jsScrollerVal)
{
    auto* jsTabsController = JSRef<JSObject>::Cast(jsTabsControllerVal)->Unwrap<JSTabsController>();
    CHECK_NULL_VOID(jsTabsController);
    auto tabsController = jsTabsController->GetTabsController();
    CHECK_NULL_VOID(tabsController);
    auto tabsControllerWeak = AceType::WeakClaim(AceType::RawPtr(tabsController));
    auto* jsScroller = JSRef<JSObject>::Cast(jsScrollerVal)->Unwrap<JSScroller>();
    CHECK_NULL_VOID(jsScroller);
    auto jsScrollerWeak = AceType::WeakClaim(jsScroller);

    auto bindInfoIter = bindInfoMap_.find(jsScrollerWeak);
    if (bindInfoIter == bindInfoMap_.end()) {
        return;
    } else {
        auto relationInfoMap = bindInfoIter->second;
        if (relationInfoMap.find(tabsControllerWeak) == relationInfoMap.end()) {
            return;
        } else {
            relationInfoMap.erase(tabsControllerWeak);
            if (relationInfoMap.empty()) {
                bindInfoMap_.erase(jsScrollerWeak);
            }
        }
    }

    if (scrollInfoMap_.find(tabsControllerWeak) != scrollInfoMap_.end()) {
        auto needRemoveScrollInfo = true;
        for (const auto& bindInfo : bindInfoMap_) {
            if (bindInfo.second.find(tabsControllerWeak) != bindInfo.second.end()) {
                needRemoveScrollInfo = false;
                break;
            }
        }
        if (needRemoveScrollInfo) {
            scrollInfoMap_.erase(tabsControllerWeak);
        }
    }
}

} // namespace

void JSTabsFeature::BindTabsToScrollable(const JSCallbackInfo& info)
{
    if (info.Length() <= INDEX_ONE) {
        return;
    }
    if (!info[INDEX_ZERO]->IsObject() || !info[INDEX_ONE]->IsObject()) {
        return;
    }

    HandleBindTabsToScrollable(info[INDEX_ZERO], info[INDEX_ONE], true);
}

void JSTabsFeature::UnbindTabsFromScrollable(const JSCallbackInfo& info)
{
    if (info.Length() <= INDEX_ONE) {
        return;
    }
    if (!info[INDEX_ZERO]->IsObject() || !info[INDEX_ONE]->IsObject()) {
        return;
    }

    HandleUnbindTabsFromScrollable(info[INDEX_ZERO], info[INDEX_ONE]);
}

void JSTabsFeature::BindTabsToNestedScrollable(const JSCallbackInfo& info)
{
    if (info.Length() <= INDEX_TWO) {
        return;
    }
    if (!info[INDEX_ZERO]->IsObject() || !info[INDEX_ONE]->IsObject() || !info[INDEX_TWO]->IsObject()) {
        return;
    }

    HandleBindTabsToScrollable(info[INDEX_ZERO], info[INDEX_ONE], true);
    HandleBindTabsToScrollable(info[INDEX_ZERO], info[INDEX_TWO], false);
}

void JSTabsFeature::UnbindTabsFromNestedScrollable(const JSCallbackInfo& info)
{
    if (info.Length() <= INDEX_TWO) {
        return;
    }
    if (!info[INDEX_ZERO]->IsObject() || !info[INDEX_ONE]->IsObject() || !info[INDEX_TWO]->IsObject()) {
        return;
    }

    HandleUnbindTabsFromScrollable(info[INDEX_ZERO], info[INDEX_ONE]);
    HandleUnbindTabsFromScrollable(info[INDEX_ZERO], info[INDEX_TWO]);
}

} // namespace OHOS::Ace::Framework
