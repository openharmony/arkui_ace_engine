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
    std::optional<WeakPtr<JSScroller>> parentScroller;
};

using ScrollInfoMap = std::map<WeakPtr<JSScroller>, ScrollInfo>;
using BindInfoMap = std::map<WeakPtr<JSTabsController>, ScrollInfoMap>;

const auto INDEX_ZERO = 0;
const auto INDEX_ONE = 1;
const auto INDEX_TWO = 2;
const auto SHOW_TAB_BAR_DELAY = 2000;
const auto SCROLL_RATIO = 2.0f;

BindInfoMap bindInfoMap_;

void HandleOnTouchEvent(WeakPtr<JSScroller> jsScrollerWeak, const TouchEventInfo& info)
{
    auto touches = info.GetTouches();
    if (touches.empty()) {
        return;
    }
    auto touchType = touches.front().GetTouchType();
    if (touchType != TouchType::DOWN && touchType != TouchType::UP && touchType != TouchType::CANCEL) {
        return;
    }

    for (auto& bindInfo : bindInfoMap_) {
        auto& scrollInfoMap = bindInfo.second;
        auto scrollInfoIter = scrollInfoMap.find(jsScrollerWeak);
        if (scrollInfoIter == scrollInfoMap.end()) {
            continue;
        }
        auto& scrollInfo = scrollInfoIter->second;
        scrollInfo.isTouching = touchType == TouchType::DOWN;
        auto jsTabsController = bindInfo.first.Upgrade();
        if (!jsTabsController) {
            continue;
        }
        auto tabsController = jsTabsController->GetTabsController().Upgrade();
        if (touchType == TouchType::DOWN) {
            if (!scrollInfo.isAtTop && !scrollInfo.isAtBottom && tabsController) {
                tabsController->CancelShowTabBar();
            }
        } else if (touchType == TouchType::UP || touchType == TouchType::CANCEL) {
            if (!scrollInfo.isScrolling && tabsController) {
                tabsController->StartShowTabBar(SHOW_TAB_BAR_DELAY);
            }
        }
    }
}

void HandleOnReachEvent(WeakPtr<JSScroller> jsScrollerWeak, bool isTopEvent)
{
    for (auto& bindInfo : bindInfoMap_) {
        auto& scrollInfoMap = bindInfo.second;
        auto scrollInfoIter = scrollInfoMap.find(jsScrollerWeak);
        if (scrollInfoIter == scrollInfoMap.end()) {
            continue;
        }
        auto& scrollInfo = scrollInfoIter->second;
        if (isTopEvent) {
            scrollInfo.isAtTop = true;
        } else {
            scrollInfo.isAtBottom = true;
        }
    }
}

void HandleOnScrollStartEvent(WeakPtr<JSScroller> jsScrollerWeak)
{
    for (auto& bindInfo : bindInfoMap_) {
        auto& scrollInfoMap = bindInfo.second;
        auto scrollInfoIter = scrollInfoMap.find(jsScrollerWeak);
        if (scrollInfoIter == scrollInfoMap.end()) {
            continue;
        }
        auto& scrollInfo = scrollInfoIter->second;
        scrollInfo.isScrolling = true;
        auto jsTabsController = bindInfo.first.Upgrade();
        if (!jsTabsController) {
            continue;
        }
        auto tabsController = jsTabsController->GetTabsController().Upgrade();
        if (!scrollInfo.isAtTop && !scrollInfo.isAtBottom && !scrollInfo.isTouching && tabsController) {
            tabsController->CancelShowTabBar();
        }
    }
}

void HandleOnScrollStopEvent(WeakPtr<JSScroller> jsScrollerWeak)
{
    for (auto& bindInfo : bindInfoMap_) {
        auto& scrollInfoMap = bindInfo.second;
        auto scrollInfoIter = scrollInfoMap.find(jsScrollerWeak);
        if (scrollInfoIter == scrollInfoMap.end()) {
            continue;
        }
        auto& scrollInfo = scrollInfoIter->second;
        scrollInfo.isScrolling = false;
        auto jsTabsController = bindInfo.first.Upgrade();
        if (!jsTabsController) {
            continue;
        }
        auto tabsController = jsTabsController->GetTabsController().Upgrade();
        if (!scrollInfo.parentScroller.has_value() && !scrollInfo.isTouching && tabsController) {
            // start show tab bar when parent scrollable component stop scroll.
            tabsController->StartShowTabBar(SHOW_TAB_BAR_DELAY);
        }
    }
}

void HandleOnDidScrollEvent(
    WeakPtr<JSScroller> jsScrollerWeak, Dimension dimension, ScrollSource source, bool isAtTop, bool isAtBottom)
{
    for (auto& bindInfo : bindInfoMap_) {
        auto& scrollInfoMap = bindInfo.second;
        auto scrollInfoIter = scrollInfoMap.find(jsScrollerWeak);
        if (scrollInfoIter == scrollInfoMap.end()) {
            continue;
        }
        auto& scrollInfo = scrollInfoIter->second;
        if ((scrollInfo.isAtTop && isAtTop) || (scrollInfo.isAtBottom && isAtBottom)) {
            continue;
        }
        auto jsTabsController = bindInfo.first.Upgrade();
        if (!jsTabsController) {
            scrollInfo.isAtTop = isAtTop;
            scrollInfo.isAtBottom = isAtBottom;
            continue;
        }
        auto tabsController = jsTabsController->GetTabsController().Upgrade();
        if (tabsController) {
            auto offset = dimension.ConvertToPx() / SCROLL_RATIO;
            if (NonPositive(offset) ||
                !(source == ScrollSource::SCROLLER || source == ScrollSource::SCROLLER_ANIMATION)) {
                tabsController->UpdateTabBarHiddenOffset(offset);
            }

            auto isChildReachTop = !scrollInfo.isAtTop && isAtTop;
            auto isChildReachBottom = !scrollInfo.isAtBottom && isAtBottom;
            auto isParentAtTop = true;
            auto isParentAtBottom = true;
            if (scrollInfo.parentScroller.has_value()) {
                auto iter = scrollInfoMap.find(scrollInfo.parentScroller.value());
                isParentAtTop = iter == scrollInfoMap.end() || iter->second.isAtTop;
                isParentAtBottom = iter == scrollInfoMap.end() || iter->second.isAtBottom;
            }
            if ((isChildReachTop && isParentAtTop) || (isChildReachBottom && isParentAtBottom)) {
                tabsController->StartShowTabBar();
            }
        }
        scrollInfo.isAtTop = isAtTop;
        scrollInfo.isAtBottom = isAtBottom;
    }
}

ScrollerObserver CreateObserver(WeakPtr<JSScroller> jsScrollerWeak)
{
    ScrollerObserver observer;

    auto touchEvent = [jsScrollerWeak](const TouchEventInfo& info) {
        HandleOnTouchEvent(jsScrollerWeak, info);
    };
    observer.onTouchEvent = AceType::MakeRefPtr<NG::TouchEventImpl>(std::move(touchEvent));

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

    auto didScrollEvent = [jsScrollerWeak](Dimension dimension, ScrollSource source, bool isAtTop, bool isAtBottom) {
        HandleOnDidScrollEvent(jsScrollerWeak, dimension, source, isAtTop, isAtBottom);
    };
    observer.onDidScrollEvent = std::move(didScrollEvent);

    return observer;
}

void HandleOnChangeEvent(WeakPtr<JSTabsController> jsTabsControllerWeak, int32_t index)
{
    auto bindInfoIter = bindInfoMap_.find(jsTabsControllerWeak);
    if (bindInfoIter == bindInfoMap_.end()) {
        return;
    }
    for (const auto& scrollInfo : bindInfoIter->second) {
        auto jsScroller = scrollInfo.first.Upgrade();
        if (jsScroller) {
            auto scroller = jsScroller->GetController().Upgrade();
            if (scroller) {
                scroller->StopAnimate();
            }
        }
    }
    auto jsTabsController = jsTabsControllerWeak.Upgrade();
    CHECK_NULL_VOID(jsTabsController);
    auto tabsController = jsTabsController->GetTabsController().Upgrade();
    CHECK_NULL_VOID(tabsController);
    tabsController->StartShowTabBar();
}

void HandleBindTabsToScrollable(const JSRef<JSObject>& jsTabsControllerVal, const JSRef<JSObject>& jsScrollerVal,
    const std::optional<JSRef<JSObject>>& parentJsScrollerVal)
{
    auto* jsTabsController = jsTabsControllerVal->Unwrap<JSTabsController>();
    CHECK_NULL_VOID(jsTabsController);
    auto jsTabsControllerWeak = AceType::WeakClaim(jsTabsController);
    auto* jsScroller = jsScrollerVal->Unwrap<JSScroller>();
    CHECK_NULL_VOID(jsScroller);
    auto jsScrollerWeak = AceType::WeakClaim(jsScroller);

    ScrollInfoMap scrollInfoMap;
    auto bindInfoIter = bindInfoMap_.find(jsTabsControllerWeak);
    if (bindInfoIter != bindInfoMap_.end()) {
        scrollInfoMap = bindInfoIter->second;
        if (scrollInfoMap.find(jsScrollerWeak) != scrollInfoMap.end()) {
            return;
        }
    }
    jsTabsController->SetOnChangeImpl([jsTabsControllerWeak](int32_t index) {
        HandleOnChangeEvent(jsTabsControllerWeak, index);
    });
    auto observer = CreateObserver(jsScrollerWeak);
    jsScroller->SetObserver(observer);
    ScrollInfo scrollInfo;
    if (parentJsScrollerVal.has_value()) {
        auto* parentJsScroller = parentJsScrollerVal.value()->Unwrap<JSScroller>();
        if (parentJsScroller) {
            scrollInfo.parentScroller = AceType::WeakClaim(parentJsScroller);
        }
    }
    scrollInfoMap[jsScrollerWeak] = scrollInfo;
    bindInfoMap_[jsTabsControllerWeak] = scrollInfoMap;
}

void HandleUnbindTabsFromScrollable(const JSRef<JSObject>& jsTabsControllerVal, const JSRef<JSObject>& jsScrollerVal,
    const std::optional<JSRef<JSObject>>& parentJsScrollerVal)
{
    auto* jsTabsController = jsTabsControllerVal->Unwrap<JSTabsController>();
    CHECK_NULL_VOID(jsTabsController);
    auto tabsController = jsTabsController->GetTabsController().Upgrade();
    auto jsTabsControllerWeak = AceType::WeakClaim(jsTabsController);
    auto* jsScroller = jsScrollerVal->Unwrap<JSScroller>();
    CHECK_NULL_VOID(jsScroller);
    auto jsScrollerWeak = AceType::WeakClaim(jsScroller);

    auto bindInfoIter = bindInfoMap_.find(jsTabsControllerWeak);
    if (bindInfoIter == bindInfoMap_.end()) {
        return;
    }
    auto& scrollInfoMap = bindInfoIter->second;
    if (scrollInfoMap.find(jsScrollerWeak) != scrollInfoMap.end()) {
        scrollInfoMap.erase(jsScrollerWeak);
        if (scrollInfoMap.empty()) {
            bindInfoMap_.erase(jsTabsControllerWeak);
        }
        if (tabsController) {
            tabsController->StartShowTabBar();
        }
    }

    if (parentJsScrollerVal.has_value()) {
        // unbind nested scrollable component.
        auto* parentJsScroller = parentJsScrollerVal.value()->Unwrap<JSScroller>();
        CHECK_NULL_VOID(parentJsScroller);
        auto parentJsScrollerWeak = AceType::WeakClaim(parentJsScroller);

        auto needRemoveParent = true;
        for (const auto& scrollInfo : scrollInfoMap) {
            if (scrollInfo.second.parentScroller.has_value() &&
                scrollInfo.second.parentScroller.value() == parentJsScrollerWeak) {
                needRemoveParent = false;
            }
        }
        if (needRemoveParent) {
            scrollInfoMap.erase(parentJsScrollerWeak);
            if (scrollInfoMap.empty()) {
                bindInfoMap_.erase(jsTabsControllerWeak);
            }
            if (tabsController) {
                tabsController->StartShowTabBar();
            }
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

    HandleBindTabsToScrollable(info[INDEX_ZERO], info[INDEX_ONE], std::nullopt);
}

void JSTabsFeature::UnbindTabsFromScrollable(const JSCallbackInfo& info)
{
    if (info.Length() <= INDEX_ONE) {
        return;
    }
    if (!info[INDEX_ZERO]->IsObject() || !info[INDEX_ONE]->IsObject()) {
        return;
    }

    HandleUnbindTabsFromScrollable(info[INDEX_ZERO], info[INDEX_ONE], std::nullopt);
}

void JSTabsFeature::BindTabsToNestedScrollable(const JSCallbackInfo& info)
{
    if (info.Length() <= INDEX_TWO) {
        return;
    }
    if (!info[INDEX_ZERO]->IsObject() || !info[INDEX_ONE]->IsObject() || !info[INDEX_TWO]->IsObject()) {
        return;
    }

    HandleBindTabsToScrollable(info[INDEX_ZERO], info[INDEX_ONE], std::nullopt);
    HandleBindTabsToScrollable(info[INDEX_ZERO], info[INDEX_TWO], info[INDEX_ONE]);
}

void JSTabsFeature::UnbindTabsFromNestedScrollable(const JSCallbackInfo& info)
{
    if (info.Length() <= INDEX_TWO) {
        return;
    }
    if (!info[INDEX_ZERO]->IsObject() || !info[INDEX_ONE]->IsObject() || !info[INDEX_TWO]->IsObject()) {
        return;
    }

    HandleUnbindTabsFromScrollable(info[INDEX_ZERO], info[INDEX_TWO], info[INDEX_ONE]);
}

} // namespace OHOS::Ace::Framework
