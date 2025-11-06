/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "core/interfaces/native/implementation/nav_destination_scrollable_processor_static.h"

#include "core/interfaces/native/utility/peer_utils.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace {
constexpr float SCROLL_RATIO = 2.0f;

ScrollerObserver CreateObserver(
    WeakPtr<NavDestinationScrollableProcessorStatic> weakProcessor, WeakPtr<ScrollerPeer> weakScroller)
{
    ScrollerObserver observer;
    auto touchEvent = [weakProcessor, weakScroller](const TouchEventInfo& info) {
        auto processor = weakProcessor.Upgrade();
        CHECK_NULL_VOID(processor);
        processor->HandleOnTouchEvent(weakScroller, info);
    };
    observer.onTouchEvent = AceType::MakeRefPtr<NG::TouchEventImpl>(std::move(touchEvent));

    observer.onReachStartEvent = [weakProcessor, weakScroller]() {
        auto processor = weakProcessor.Upgrade();
        CHECK_NULL_VOID(processor);
        processor->HandleOnReachEvent(weakScroller, true);
    };

    observer.onReachEndEvent = [weakProcessor, weakScroller]() {
        auto processor = weakProcessor.Upgrade();
        CHECK_NULL_VOID(processor);
        processor->HandleOnReachEvent(weakScroller, false);
    };

    observer.onScrollStartEvent = [weakProcessor, weakScroller]() {
        auto processor = weakProcessor.Upgrade();
        CHECK_NULL_VOID(processor);
        processor->HandleOnScrollStartEvent(weakScroller);
    };

    observer.onScrollStopEvent = [weakProcessor, weakScroller]() {
        auto processor = weakProcessor.Upgrade();
        CHECK_NULL_VOID(processor);
        processor->HandleOnScrollStopEvent(weakScroller);
    };

    observer.onDidScrollEvent =
        [weakProcessor, weakScroller](Dimension dimension, ScrollSource source, bool isAtTop, bool isAtBottom) {
            auto processor = weakProcessor.Upgrade();
            CHECK_NULL_VOID(processor);
            processor->HandleOnDidScrollEvent(weakScroller, dimension, source, isAtTop, isAtBottom);
        };

    return observer;
}

std::vector<WeakPtr<ScrollerPeer>> ParseScrollerArray(const Opt_Array_Scroller* info)
{
    std::vector<WeakPtr<ScrollerPeer>> scrollers;
    CHECK_NULL_RETURN(info, scrollers);
    if (info->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        return scrollers;
    }
    if (info->value.length == 0) {
        return scrollers;
    }

    auto scrollerArray = info->value.array;
    auto arraySize = info->value.length;
    for (int32_t idx = 0; idx < arraySize; idx++) {
        auto item = scrollerArray[idx];
        scrollers.emplace_back(AceType::WeakClaim(item));
    }
    return scrollers;
}

std::vector<std::pair<WeakPtr<ScrollerPeer>, WeakPtr<ScrollerPeer>>> ParseNestedScrollerArray(
    const Opt_Array_NestedScrollInfo* info)
{
    std::vector<std::pair<WeakPtr<ScrollerPeer>, WeakPtr<ScrollerPeer>>> nestedScrollers;
    CHECK_NULL_RETURN(info, nestedScrollers);
    if (info->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        return nestedScrollers;
    }
    if (info->value.length == 0) {
        return nestedScrollers;
    }

    auto nestedScrollerArray = info->value.array;
    auto arraySize = info->value.length;
    for (int32_t idx = 0; idx < arraySize; idx++) {
        auto parent = nestedScrollerArray[idx].parent;
        auto child = nestedScrollerArray[idx].child;
        nestedScrollers.emplace_back(AceType::WeakClaim(child), AceType::WeakClaim(parent));
    }
    return nestedScrollers;
}
} // namespace

void NavDestinationScrollableProcessorStatic::HandleOnTouchEvent(
    WeakPtr<ScrollerPeer> weakScroller, const TouchEventInfo& info)
{
    const auto& touches = info.GetTouches();
    if (touches.empty()) {
        return;
    }
    auto touchType = touches.front().GetTouchType();
    if (touchType != TouchType::DOWN && touchType != TouchType::UP && touchType != TouchType::CANCEL) {
        return;
    }
    auto navDestPattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(navDestPattern);
    auto it = scrollInfoMap_.find(weakScroller);
    if (it == scrollInfoMap_.end()) {
        return;
    }
    auto& scrollInfo = it->second;
    if (touchType == TouchType::DOWN) {
        scrollInfo.isTouching = true;
        if (!scrollInfo.isAtTop && !scrollInfo.isAtBottom) {
            // If we have started the task of showing titleBar/toolBar delayed task, we need to cancel it.
            navDestPattern->CancelShowTitleAndToolBarTask();
        }
        return;
    }
    scrollInfo.isTouching = false;
    if (scrollInfo.isScrolling) {
        return;
    }
    /**
     * When touching and scrolling stops, it is necessary to check
     * whether the titleBar&toolBar should be restored to its original position.
     */
    auto pipeline = navDestPattern->GetContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->AddAfterLayoutTask([weakPattern = weakPattern_]() {
        auto pattern = weakPattern.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->ResetTitleAndToolBarState();
    });
    pipeline->RequestFrame();
}

void NavDestinationScrollableProcessorStatic::HandleOnReachEvent(WeakPtr<ScrollerPeer> weakScroller, bool isTopEvent)
{
    auto it = scrollInfoMap_.find(weakScroller);
    if (it == scrollInfoMap_.end()) {
        return;
    }
    auto& scrollInfo = it->second;
    if (isTopEvent) {
        scrollInfo.isAtTop = true;
    } else {
        scrollInfo.isAtBottom = true;
    }
}

void NavDestinationScrollableProcessorStatic::HandleOnScrollStartEvent(WeakPtr<ScrollerPeer> weakScroller)
{
    auto it = scrollInfoMap_.find(weakScroller);
    if (it == scrollInfoMap_.end()) {
        return;
    }
    auto navDestPattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(navDestPattern);
    auto& scrollInfo = it->second;
    scrollInfo.isScrolling = true;
    if (!scrollInfo.isAtTop && !scrollInfo.isAtBottom && !scrollInfo.isTouching) {
        // If we have started the task of showing titleBar/toolBar delayed task, we need to cancel it.
        navDestPattern->CancelShowTitleAndToolBarTask();
    }
}

void NavDestinationScrollableProcessorStatic::HandleOnScrollStopEvent(WeakPtr<ScrollerPeer> weakScroller)
{
    auto it = scrollInfoMap_.find(weakScroller);
    if (it == scrollInfoMap_.end()) {
        return;
    }
    auto& scrollInfo = it->second;
    scrollInfo.isScrolling = false;
    if (scrollInfo.isTouching) {
        return;
    }
    /**
     * When touching and scrolling stops, it is necessary to check
     * whether the titleBar&toolBar should be restored to its original position.
     */
    auto navDestPattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(navDestPattern);
    auto pipeline = navDestPattern->GetContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->AddAfterLayoutTask([weakPattern = weakPattern_]() {
        auto pattern = weakPattern.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->ResetTitleAndToolBarState();
    });
    pipeline->RequestFrame();
}

void NavDestinationScrollableProcessorStatic::HandleOnDidScrollEvent(
    WeakPtr<ScrollerPeer> weakScroller, Dimension dimension, ScrollSource source, bool isAtTop, bool isAtBottom)
{
    auto it = scrollInfoMap_.find(weakScroller);
    if (it == scrollInfoMap_.end()) {
        return;
    }
    auto& scrollInfo = it->second;
    if ((scrollInfo.isAtTop && isAtTop) || (scrollInfo.isAtBottom && isAtBottom)) {
        // If we have already scrolled to the top or bottom, just return.
        return;
    }

    auto navDestPattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(navDestPattern);
    auto pipeline = navDestPattern->GetContext();
    CHECK_NULL_VOID(pipeline);
    if (scrollInfo.isScrolling) {
        auto offset = dimension.ConvertToPx() / SCROLL_RATIO;
        if (!(source == ScrollSource::SCROLLER || source == ScrollSource::SCROLLER_ANIMATION) || NonPositive(offset)) {
            /**
             * We will respond to user actions by scrolling up or down. But for the scrolling triggered by developers
             * through the frontend interface, we will only respond to scrolling down.
             */
            pipeline->AddAfterLayoutTask([weakPattern = weakPattern_, offset]() {
                auto pattern = weakPattern.Upgrade();
                CHECK_NULL_VOID(pattern);
                pattern->UpdateTitleAndToolBarHiddenOffset(offset);
            });
            pipeline->RequestFrame();
        }
    }

    auto isChildReachTop = !scrollInfo.isAtTop && isAtTop;
    auto isChildReachBottom = !scrollInfo.isAtBottom && isAtBottom;
    auto isParentAtTop = true;
    auto isParentAtBottom = true;
    if (scrollInfo.parentScroller.has_value()) {
        auto iter = scrollInfoMap_.find(scrollInfo.parentScroller.value());
        isParentAtTop = iter == scrollInfoMap_.end() || iter->second.isAtTop;
        isParentAtBottom = iter == scrollInfoMap_.end() || iter->second.isAtBottom;
    }
    /**
     * For non-nested scrolling component, we need show titleBar&toolBar immediately when scrolled
     * to the top or bottom. But for the nested scrolling components, the titleBar&toolBar can only be show
     * immediately when the parent component also reaches the top or bottom.
     */
    if ((isChildReachTop && isParentAtTop) || (isChildReachBottom && isParentAtBottom)) {
        pipeline->AddAfterLayoutTask([weakPattern = weakPattern_]() {
            auto pattern = weakPattern.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->ShowTitleAndToolBar();
        });
        pipeline->RequestFrame();
    }

    scrollInfo.isAtTop = isAtTop;
    scrollInfo.isAtBottom = isAtBottom;
}

void NavDestinationScrollableProcessorStatic::BindToScrollable(const Opt_Array_Scroller* info)
{
    needUpdateBindingRelation_ = true;
    incommingScrollers_.clear();
    std::vector<WeakPtr<ScrollerPeer>> scrollers = ParseScrollerArray(info);
    for (const auto& scroller : scrollers) {
        incommingScrollers_.emplace(scroller);
    }
}

void NavDestinationScrollableProcessorStatic::BindToNestedScrollable(const Opt_Array_NestedScrollInfo* info)
{
    needUpdateBindingRelation_ = true;
    incommingNestedScrollers_.clear();
    auto nestedScrollers = ParseNestedScrollerArray(info);
    for (const auto& scrollerPair : nestedScrollers) {
        incommingNestedScrollers_.emplace(scrollerPair.second, std::nullopt);
        incommingNestedScrollers_.emplace(scrollerPair.first, scrollerPair.second);
    }
}

void NavDestinationScrollableProcessorStatic::UpdateBindingRelation()
{
    if (!needUpdateBindingRelation_) {
        return;
    }
    needUpdateBindingRelation_ = false;

    // mark all scroller need unbind.
    for (auto& pair : scrollInfoMap_) {
        pair.second.needUnbind = true;
    }

    CombineIncomingScrollers();
    // If the bindingRelation has changed or there is no bindingRelation, then we need show titleBar&toolBar again.
    bool needShowBar = false;
    if (BuildNewBindingRelation()) {
        needShowBar = true;
    }
    if (RemoveUnneededBindingRelation()) {
        needShowBar = true;
    }
    if (scrollInfoMap_.empty()) {
        needShowBar = true;
    }
    if (!needShowBar) {
        return;
    }
    auto pattern = weakPattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    pattern->ShowTitleAndToolBar();
}

void NavDestinationScrollableProcessorStatic::CombineIncomingScrollers()
{
    for (auto& scroller : incommingScrollers_) {
        NestedScrollersStatic nestedScroller(scroller, std::nullopt);
        auto it = incommingNestedScrollers_.find(nestedScroller);
        if (it != incommingNestedScrollers_.end()) {
            continue;
        }
        incommingNestedScrollers_.emplace(nestedScroller);
    }
    incommingScrollers_.clear();
}

bool NavDestinationScrollableProcessorStatic::BuildNewBindingRelation()
{
    bool buildNewRelation = false;
    for (auto& scrollers : incommingNestedScrollers_) {
        auto it = scrollInfoMap_.find(scrollers.child);
        if (it != scrollInfoMap_.end()) {
            it->second.needUnbind = false;
            it->second.parentScroller = scrollers.parent;
            continue;
        }

        auto jsScroller = scrollers.child.Upgrade();
        if (!jsScroller) {
            continue;
        }
        auto observer = CreateObserver(WeakClaim(this), scrollers.child);
        jsScroller->AddObserver(observer, nodeId_);
        ScrollInfo info;
        info.parentScroller = scrollers.parent;
        info.needUnbind = false;
        scrollInfoMap_.emplace(scrollers.child, info);
        buildNewRelation = true;
    }
    incommingNestedScrollers_.clear();
    return buildNewRelation;
}

bool NavDestinationScrollableProcessorStatic::RemoveUnneededBindingRelation()
{
    bool unbindRelation = false;
    auto infoIter = scrollInfoMap_.begin();
    for (; infoIter != scrollInfoMap_.end();) {
        if (!infoIter->second.needUnbind) {
            ++infoIter;
            continue;
        }

        auto jsScroller = infoIter->first.Upgrade();
        if (jsScroller) {
            jsScroller->RemoveObserver(nodeId_);
        }
        infoIter = scrollInfoMap_.erase(infoIter);
        unbindRelation = true;
    }
    return unbindRelation;
}

void NavDestinationScrollableProcessorStatic::UnbindAllScrollers()
{
    needUpdateBindingRelation_ = true;
    incommingScrollers_.clear();
    incommingNestedScrollers_.clear();
    UpdateBindingRelation();
}
} // OHOS::Ace::NG::GeneratedModifier