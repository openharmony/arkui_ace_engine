#include "subscription_manager.h"

#include <chrono>

namespace rendercapture {

SubscriptionId SubscriptionManager::Add(const std::string& event,
                                         EventCallback callback,
                                         void* userdata,
                                         int32_t stabilityWindowMs,
                                         int32_t timeoutMs)
{
    SubscriptionId id = nextId_.fetch_add(1);

    auto sub = std::make_shared<Subscription>();
    sub->id = id;
    sub->event = event;
    sub->callback = std::move(callback);
    sub->userdata = userdata;
    sub->stabilityWindowMs = stabilityWindowMs;
    sub->timeoutMs = timeoutMs;
    sub->createdAt = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::steady_clock::now().time_since_epoch()).count();

    std::lock_guard<std::mutex> lock(mutex_);
    subs_[id] = sub;
    eventIndex_[event].push_back(id);

    return id;
}

void SubscriptionManager::Remove(SubscriptionId id)
{
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = subs_.find(id);
    if (it == subs_.end()) {
        return;
    }
    it->second->alive.store(false);
}

void SubscriptionManager::Dispatch(const std::string& event, const void* data)
{
    // Take a snapshot of matching subscriptions under the lock.
    std::vector<std::shared_ptr<Subscription>> snapshot;
    {
        std::lock_guard<std::mutex> lock(mutex_);
        auto it = eventIndex_.find(event);
        if (it == eventIndex_.end()) {
            return;
        }
        for (SubscriptionId sid : it->second) {
            auto subIt = subs_.find(sid);
            if (subIt != subs_.end()) {
                snapshot.push_back(subIt->second);
            }
        }
    }

    // Call each alive callback outside the lock.
    for (auto& sub : snapshot) {
        if (sub->alive.load() && sub->callback) {
            sub->callback(event, data, sub->userdata);
        }
    }

    // Lazily purge dead entries to prevent unbounded growth.
    {
        std::lock_guard<std::mutex> lock(mutex_);
        auto it = eventIndex_.find(event);
        if (it != eventIndex_.end()) {
            auto& ids = it->second;
            ids.erase(
                std::remove_if(ids.begin(), ids.end(),
                    [this](SubscriptionId sid) {
                        auto subIt = subs_.find(sid);
                        if (subIt != subs_.end() && !subIt->second->alive.load()) {
                            subs_.erase(subIt);
                            return true;
                        }
                        return false;
                    }),
                ids.end());
        }
    }
}

void SubscriptionManager::RemoveAll(const std::string& event)
{
    std::lock_guard<std::mutex> lock(mutex_);

    if (event.empty()) {
        // Mark all subscriptions as inactive.
        for (auto& pair : subs_) {
            pair.second->alive.store(false);
        }
        subs_.clear();
        eventIndex_.clear();
        return;
    }

    // Mark matching subscriptions as inactive.
    auto it = eventIndex_.find(event);
    if (it == eventIndex_.end()) {
        return;
    }
    for (SubscriptionId sid : it->second) {
        auto subIt = subs_.find(sid);
        if (subIt != subs_.end()) {
            subIt->second->alive.store(false);
            subs_.erase(subIt);
        }
    }
    eventIndex_.erase(it);
}

size_t SubscriptionManager::Count() const
{
    std::lock_guard<std::mutex> lock(mutex_);
    size_t count = 0;
    for (const auto& pair : subs_) {
        if (pair.second->alive.load()) {
            count++;
        }
    }
    return count;
}

}  // namespace rendercapture
