#ifndef HEADLESS_RENDER_CAPTURE_RENDER_CAPTURE_PREVIEW_H
#define HEADLESS_RENDER_CAPTURE_RENDER_CAPTURE_PREVIEW_H

#include "rendercapture.h"
#include "subscription_manager.h"

#include <atomic>
#include <chrono>
#include <mutex>
#include <queue>
#include <unordered_map>

namespace rendercapture {

class PreviewRenderCapture : public RenderCapture {
public:
    static PreviewRenderCapture& Instance();

    int64_t RequestFrame() override;
    bool AwaitFrame(int64_t requestId, int32_t timeoutMs) override;
    Frame CollectFrame(int64_t requestId) override;

    void SkipFrames(int32_t count) override;

    bool WaitForIdle(int32_t timeoutMs) override;

    void TouchDown(float x, float y) override;
    void TouchMove(float x, float y) override;
    void TouchUp(float x, float y) override;

    bool IsPreviewer() override;
    bool IsHeadless() override;
    void GetScreenSize(int32_t* w, int32_t* h) override;

    SubscriptionManager& GetSubscriptionManager() override { return subscriptionManager_; }

    void SetVisualTestDone() override;
    void SetOutputDir(const std::string& dir) override;
    void StartIdleDetection() override;
    void RequestRenderStable() override;
    bool IsRenderStable() override;

    /** Whether the render test host should exit. Called by the C-ABI export. */
    bool IsVisualTestDone();
    void SetHapDir(const std::string& dir) override;

    Frame CopyLastFrame() const override;

    /**
     * Called from the render thread every frame with the latest pixel buffer.
     * Thread-safe. Stores the data and advances the stability window.
     */
    void RegisterFrameData(const void* data, int32_t width, int32_t height);

    /**
     * Called from the render thread every frame to advance the stability window.
     * When the frame hash is stable for kStableThreshold consecutive calls,
     * the next pending request is fulfilled.
     */
    void CheckRenderStable();

private:
    PreviewRenderCapture() = default;

    uint64_t ComputeFrameHash(const uint8_t* data, int32_t width, int32_t height);

    void RequestRenderStable();
    bool IsRenderStable();

    mutable std::mutex frameMutex_;
    Frame lastFrame_;
    std::chrono::steady_clock::time_point lastFrameTime_;

    std::atomic<bool> stableFlag_{false};
    std::atomic<bool> stableRequested_{false};
    // Millisecond timestamp of the last hash change.
    std::atomic<int64_t> lastHashChangeMs_{0};
    // Hash must be stable for this many milliseconds before declaring idle.
    static const int kStableDurationMs = 50;
    uint64_t previousFrameHash_ = 0;

    // True after at least one frame has been registered.
    // Prevents idle detection from firing before the first frame.
    std::atomic<bool> hasFrame_{false};

    std::atomic<int64_t> nextRequestId_{1};
    std::queue<int64_t> pendingRequests_;
    std::mutex requestMutex_;
    std::unordered_map<int64_t, Frame> frameStore_;
    std::unordered_map<int64_t, bool> frameReady_;

    SubscriptionManager subscriptionManager_;

    std::string outputDir_ = "./output";
    std::string hapDir_;
    std::atomic<bool> visualTestDone_{false};
};

}  // namespace rendercapture

#endif  // HEADLESS_RENDER_CAPTURE_RENDER_CAPTURE_PREVIEW_H
