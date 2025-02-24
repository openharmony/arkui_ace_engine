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

#include "observer.h"

#include "observer_listener.h"

#include "base/utils/utils.h"

namespace OHOS {
namespace Rosen {

std::unordered_map<int64_t, std::shared_ptr<CJObserverListener>> CJObserver::scrollEventListeners_;
std::unordered_map<std::string, std::unordered_map<int64_t, std::shared_ptr<CJObserverListener>>>
    CJObserver::specifiedScrollEventListeners_;

std::unordered_map<int64_t, std::shared_ptr<CJObserverListener>> CJObserver::tabContentUpdateListeners_;
std::unordered_map<std::string, std::unordered_map<int64_t, std::shared_ptr<CJObserverListener>>>
    CJObserver::specifiedTabContentUpdateListeners_;

// Scroll event callbacks
void CJObserver::RegisterScrollEventCallback(int64_t callbackId)
{
    auto listener = std::make_shared<CJObserverListener>();
    auto iter = scrollEventListeners_.find(callbackId);
    if (iter != scrollEventListeners_.end()) {
        return;
    }
    listener->AddCallback(EVENT_SCROLL, callbackId);
    scrollEventListeners_.emplace(callbackId, listener);
}

void CJObserver::RegisterScrollEventCallback(const std::string& id, int64_t callbackId)
{
    auto listener = std::make_shared<CJObserverListener>();
    auto iter = specifiedScrollEventListeners_.find(id);
    if (iter == specifiedScrollEventListeners_.end()) {
        std::unordered_map<int64_t, std::shared_ptr<CJObserverListener>> tmpMap;
        tmpMap[callbackId] = listener;
        listener->AddCallback(EVENT_SCROLL, callbackId);
        specifiedScrollEventListeners_.emplace(id, tmpMap);
        return;
    }
    auto& holder = iter->second;
    if (holder.find(callbackId) != holder.end()) {
        return;
    }
    listener->AddCallback(EVENT_SCROLL, callbackId);
    holder.emplace(callbackId, listener);
}

void CJObserver::UnRegisterScrollEventCallback(int64_t callbackId)
{
    if (callbackId == -1) {
        auto listener = std::make_shared<CJObserverListener>();
        listener->RemoveAllCallback(EVENT_SCROLL);
        scrollEventListeners_.clear();
        return;
    }
    auto iter = scrollEventListeners_.find(callbackId);
    if (iter == scrollEventListeners_.end()) {
        return;
    }
    iter->second->RemoveCallback(EVENT_SCROLL, callbackId);
    scrollEventListeners_.erase(callbackId);
}

void CJObserver::UnRegisterScrollEventCallback(const std::string& id, int64_t callbackId)
{
    if (callbackId == -1) {
        auto listener = std::make_shared<CJObserverListener>();
        listener->RemoveAllCallback(EVENT_SCROLL);
        auto iter = specifiedScrollEventListeners_.find(id);
        if (iter == specifiedScrollEventListeners_.end()) {
            return;
        }
        iter->second.clear();
        return;
    }
    auto iter = specifiedScrollEventListeners_.find(id);
    if (iter == specifiedScrollEventListeners_.end()) {
        return;
    }
    auto& holder = iter->second;
    auto iterWithId = holder.find(callbackId);
    if (iterWithId == holder.end()) {
        return;
    }
    iterWithId->second->RemoveCallback(EVENT_SCROLL, callbackId);
    holder.erase(callbackId);
}

void CJObserver::HandleScrollEventStateChange(
    const std::string& id, int32_t uniqueId, Ace::NG::ScrollEventType eventType, float offset)
{
    for (const auto& pair : scrollEventListeners_) {
        pair.second->OnScrollEventStateChange(id, uniqueId, eventType, offset);
    }

    auto iter = specifiedScrollEventListeners_.find(id);
    if (iter == specifiedScrollEventListeners_.end()) {
        return;
    }

    auto& holder = iter->second;
    for (const auto& pair : holder) {
        pair.second->OnScrollEventStateChange(id, uniqueId, eventType, offset);
    }
}

// TabContent Update callbacks
void CJObserver::RegisterTabContentUpdateCallback(int64_t callbackId)
{
    auto listener = std::make_shared<CJObserverListener>();
    auto iter = tabContentUpdateListeners_.find(callbackId);
    if (iter != tabContentUpdateListeners_.end()) {
        return;
    }
    listener->AddCallback(EVENT_TAB_CONTENT_UPDATE, callbackId);
    tabContentUpdateListeners_.emplace(callbackId, listener);
}

void CJObserver::RegisterTabContentUpdateCallback(const std::string& id, int64_t callbackId)
{
    auto listener = std::make_shared<CJObserverListener>();
    auto iter = specifiedTabContentUpdateListeners_.find(id);
    if (iter == specifiedTabContentUpdateListeners_.end()) {
        std::unordered_map<int64_t, std::shared_ptr<CJObserverListener>> tmpMap;
        tmpMap[callbackId] = listener;
        listener->AddCallback(EVENT_TAB_CONTENT_UPDATE, callbackId);
        specifiedTabContentUpdateListeners_.emplace(id, tmpMap);
        return;
    }
    auto& holder = iter->second;
    if (holder.find(callbackId) != holder.end()) {
        return;
    }
    listener->AddCallback(EVENT_TAB_CONTENT_UPDATE, callbackId);
    holder.emplace(callbackId, listener);
}

void CJObserver::UnRegisterTabContentUpdateCallback(int64_t callbackId)
{
    if (callbackId == -1) {
        auto listener = std::make_shared<CJObserverListener>();
        listener->RemoveAllCallback(EVENT_TAB_CONTENT_UPDATE);
        tabContentUpdateListeners_.clear();
        return;
    }
    auto iter = tabContentUpdateListeners_.find(callbackId);
    if (iter == tabContentUpdateListeners_.end()) {
        return;
    }
    iter->second->RemoveCallback(EVENT_TAB_CONTENT_UPDATE, callbackId);
    tabContentUpdateListeners_.erase(callbackId);
}

void CJObserver::UnRegisterTabContentUpdateCallback(const std::string& id, int64_t callbackId)
{
    if (callbackId == -1) {
        auto listener = std::make_shared<CJObserverListener>();
        listener->RemoveAllCallback(EVENT_TAB_CONTENT_UPDATE);
        auto iter = specifiedTabContentUpdateListeners_.find(id);
        if (iter == specifiedTabContentUpdateListeners_.end()) {
            return;
        }
        iter->second.clear();
        return;
    }
    auto iter = specifiedTabContentUpdateListeners_.find(id);
    if (iter == specifiedTabContentUpdateListeners_.end()) {
        return;
    }
    auto& holder = iter->second;
    auto iterWithId = holder.find(callbackId);
    if (iterWithId == holder.end()) {
        return;
    }
    iterWithId->second->RemoveCallback(EVENT_TAB_CONTENT_UPDATE, callbackId);
    holder.erase(callbackId);
}

void CJObserver::HandleTabContentUpdateStateChange(const Ace::NG::TabContentInfo& tabContentInfo)
{
    for (const auto& pair : tabContentUpdateListeners_) {
        pair.second->OnTabContentUpdateStateChange(tabContentInfo);
    }

    auto iter = specifiedTabContentUpdateListeners_.find(tabContentInfo.id);
    if (iter == specifiedTabContentUpdateListeners_.end()) {
        return;
    }

    auto& holder = iter->second;
    for (const auto& pair : holder) {
        pair.second->OnTabContentUpdateStateChange(tabContentInfo);
    }
}

} // namespace Rosen
} // namespace OHOS