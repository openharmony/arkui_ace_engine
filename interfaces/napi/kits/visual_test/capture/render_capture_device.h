#ifndef HEADLESS_RENDER_CAPTURE_RENDER_CAPTURE_DEVICE_H
#define HEADLESS_RENDER_CAPTURE_RENDER_CAPTURE_DEVICE_H

#include "rendercapture.h"
#include "subscription_manager.h"

#include <atomic>
#include <condition_variable>
#include <mutex>

namespace rendercapture {

class DeviceRenderCapture : public RenderCapture {
public:
    static DeviceRenderCapture& Instance();

    int64_t RequestFrame() override;
    bool AwaitFrame(int64_t requestId, int32_t timeoutMs) override;
    Frame CollectFrame(int64_t requestId) override;

    void SkipFrames(int32_t count) override;

    bool WaitForIdle(int32_t timeoutMs) override;
    void StartIdleDetection() override;

    void TouchDown(float x, float y) override;
    void TouchMove(float x, float y) override;
    void TouchUp(float x, float y) override;

    bool IsPreviewer() override;
    bool IsHeadless() override;
    void GetScreenSize(int32_t* w, int32_t* h) override;

    SubscriptionManager& GetSubscriptionManager() override { return subscriptionManager_; }

    void SetVisualTestDone() override {}
    void SetOutputDir(const std::string& dir) override;
    void SetHapDir(const std::string& dir) override;

    Frame CopyLastFrame() const override;

    /** Captures current screen via ComponentSnapshot::GetSync(). */
    Frame CaptureFrame();

    /** Hash-stability check. Called on each poll interval. */
    void CheckRenderStable();

    /** Request render stability detection. */
    void RequestRenderStable() override;

    /** Returns whether render is stable. */
    bool IsRenderStable() override;

    /** Returns whether the persist after-layout task is registered. */
    bool GetPersistTaskRegistered() const { return persistTaskRegistered_; }

    /** Marks the persist after-layout task as registered. */
    void SetPersistTaskRegistered() { persistTaskRegistered_ = true; }

private:
    DeviceRenderCapture() = default;

    uint64_t ComputeFrameHash(const uint8_t* data, int32_t width, int32_t height);

    mutable std::mutex frameMutex_;
    Frame lastFrame_;

    std::atomic<bool> stableFlag_{false};
    std::atomic<bool> stableRequested_{false};
    std::atomic<int64_t> lastHashChangeMs_{0};
    static const int kStableDurationMs = 50;
    uint64_t previousFrameHash_ = 0;

    std::string outputDir_ = "/tmp/output";
    std::string hapDir_;

    std::atomic<int64_t> nextRequestId_{1};
    std::mutex storeMutex_;
    std::unordered_map<int64_t, Frame> frameStore_;

    SubscriptionManager subscriptionManager_;

    bool persistTaskRegistered_ = false;
    std::mutex idleMutex_;
    std::condition_variable idleCV_;
};

}  // namespace rendercapture

#endif  // HEADLESS_RENDER_CAPTURE_RENDER_CAPTURE_DEVICE_H
