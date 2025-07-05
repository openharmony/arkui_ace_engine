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

#include "core/components_ng/pattern/scrollable/scroller_observer_manager.h"

namespace OHOS::Ace {
void ScrollerObserverManager::AddObserver(const ScrollerObserver& obs, int32_t id)
{
    observers_.emplace(id, obs);
}

void ScrollerObserverManager::RemoveObserver(int32_t id)
{
    auto it = observers_.find(id);
    if (it != observers_.end()) {
        observers_.erase(it);
    }
}

void ScrollerObserverManager::HandleOnTouchEvent(TouchEventInfo& info)
{
    for (const auto& pair : observers_) {
        if (pair.second.onTouchEvent) {
            (*pair.second.onTouchEvent)(info);
        }
    }
}

void ScrollerObserverManager::HandleOnReachEvent(bool end)
{
    for (const auto& pair : observers_) {
        if (end) {
            if (pair.second.onReachEndEvent) {
                pair.second.onReachEndEvent();
            }
        } else {
            if (pair.second.onReachStartEvent) {
                pair.second.onReachStartEvent();
            }
        }
    }
}

void ScrollerObserverManager::HandleOnScrollStartEvent()
{
    for (const auto& pair : observers_) {
        if (pair.second.onScrollStartEvent) {
            pair.second.onScrollStartEvent();
        }
    }
}

void ScrollerObserverManager::HandleOnScrollStopEvent()
{
    for (const auto& pair : observers_) {
        if (pair.second.onScrollStopEvent) {
            pair.second.onScrollStopEvent();
        }
    }
}

void ScrollerObserverManager::HandleOnDidScrollEvent(
    Dimension dimension, ScrollSource source, bool isAtTop, bool isAtBottom)
{
    for (const auto& pair : observers_) {
        if (pair.second.onDidScrollEvent) {
            pair.second.onDidScrollEvent(dimension, source, isAtTop, isAtBottom);
        }
    }
}

void ScrollerObserverManager::HandleOnScrollerAreaChangeEvent(
    Dimension dimension, ScrollSource source, bool isAtTop, bool isAtBottom)
{
    for (const auto& pair : observers_) {
        if (pair.second.onScrollerAreaChangeEvent) {
            pair.second.onScrollerAreaChangeEvent(dimension, source, isAtTop, isAtBottom);
        }
    }
}

void ScrollerObserverManager::HandleOnWillScrollEventEx(
    ScrollFrameResult& result, ScrollState state, ScrollSource source)
{
    for (const auto& pair : observers_) {
        if (pair.second.onWillScrollEventEx) {
            pair.second.onWillScrollEventEx(result, state, source);
        }
    }
}
} // namespace OHOS::Ace::NG
