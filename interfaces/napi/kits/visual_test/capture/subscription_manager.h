#ifndef HEADLESS_RENDER_CAPTURE_SUBSCRIPTION_MANAGER_H
#define HEADLESS_RENDER_CAPTURE_SUBSCRIPTION_MANAGER_H

#include <atomic>
#include <cstdint>
#include <functional>
#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>
#include <vector>

namespace rendercapture {

/**
 * Subscription identifier.
 * Opaque integer returned by Add(). Used with Remove().
 */
using SubscriptionId = int32_t;

/**
 * Callback type for event delivery.
 * Called from the JS thread via napi_threadsafe_function.
 *
 * The event string identifies what happened.
 * The data pointer is the event payload (Frame*, SceneError*, etc.).
 * The userdata pointer is the subscription-specific context.
 */
using EventCallback = std::function<void(const std::string& event,
                                          const void* data,
                                          void* userdata)>;

/**
 * A single subscription record.
 *
 * Owned by SubscriptionManager via shared_ptr.
 * The alive flag lets Dispatch skip removed subscriptions
 * without taking the mutex during callback iteration.
 */
struct Subscription {
    SubscriptionId id;
    std::string event;
    EventCallback callback;
    void* userdata = nullptr;
    std::atomic<bool> alive{true};
    int32_t stabilityWindowMs = 0;
    int32_t timeoutMs = 0;
    int64_t createdAt = 0;
};

/**
 * Thread-safe subscription registry.
 *
 * Add/Remove from the JS thread.
 * Dispatch from the render thread (via napi_threadsafe_function).
 *
 * Dispatch takes a snapshot of matching subscriptions under the lock,
 * then calls each alive callback outside the lock.
 * This prevents deadlocks when a callback calls Remove/Add.
 */
class SubscriptionManager {
public:
    SubscriptionManager() = default;
    ~SubscriptionManager() = default;

    SubscriptionManager(const SubscriptionManager&) = delete;
    SubscriptionManager& operator=(const SubscriptionManager&) = delete;

    /**
     * Register a new subscription.
     *
     * Returns an identifier for use with Remove().
     * Thread-safe. Call from JS thread.
     */
    SubscriptionId Add(const std::string& event,
                       EventCallback callback,
                       void* userdata = nullptr,
                       int32_t stabilityWindowMs = 0,
                       int32_t timeoutMs = 0);

    /**
     * Remove a single subscription by id.
     *
     * Sets the alive flag to false.
     * Idempotent. Safe to call from within a callback.
     * Thread-safe. Call from JS thread.
     */
    void Remove(SubscriptionId id);

    /**
     * Deliver an event to all matching subscriptions.
     *
     * Takes a snapshot under the lock, then calls each alive callback
     * outside the lock. Skipped subscriptions (alive == false) are
     * cleaned up lazily.
     *
     * Thread-safe. Call from render thread via napi_threadsafe_function.
     */
    void Dispatch(const std::string& event, const void* data);

    /**
     * Remove all subscriptions.
     *
     * Without argument: remove everything.
     * With event: remove only subscriptions for that event type.
     *
     * Thread-safe. Call from JS thread.
     */
    void RemoveAll(const std::string& event = "");

    /** Number of active subscriptions. For debugging. */
    size_t Count() const;

private:
    std::atomic<int32_t> nextId_{1};
    mutable std::mutex mutex_;
    std::unordered_map<SubscriptionId, std::shared_ptr<Subscription>> subs_;
    std::unordered_map<std::string, std::vector<SubscriptionId>> eventIndex_;
};

}  // namespace rendercapture

#endif  // HEADLESS_RENDER_CAPTURE_SUBSCRIPTION_MANAGER_H
