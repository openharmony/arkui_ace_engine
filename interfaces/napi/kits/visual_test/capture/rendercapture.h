#ifndef HEADLESS_RENDER_CAPTURE_RENDERCAPTURE_H
#define HEADLESS_RENDER_CAPTURE_RENDERCAPTURE_H

#include <cstdint>
#include <string>
#include <vector>

namespace rendercapture {

struct Frame {
    std::vector<uint8_t> data;
    int32_t width = 0;
    int32_t height = 0;
};

class SubscriptionManager;

class RenderCapture {
public:
    virtual ~RenderCapture() = default;

    virtual int64_t RequestFrame() = 0;
    virtual bool AwaitFrame(int64_t requestId, int32_t timeoutMs) = 0;
    virtual Frame CollectFrame(int64_t requestId) = 0;

    virtual void SkipFrames(int32_t count) = 0;

    virtual bool WaitForIdle(int32_t timeoutMs) = 0;

    virtual void TouchDown(float x, float y) = 0;
    virtual void TouchMove(float x, float y) = 0;
    virtual void TouchUp(float x, float y) = 0;

    virtual bool IsPreviewer() = 0;
    virtual bool IsHeadless() = 0;
    virtual void GetScreenSize(int32_t* w, int32_t* h) = 0;

    /** Event subscription registry. The NAPI bridge uses this to register JS callbacks. */
    virtual SubscriptionManager& GetSubscriptionManager() = 0;

    /** Signal the render test host to exit. Previewer-only; no-op on device. */
    virtual void SetVisualTestDone() = 0;

    /** Set the output directory for captures and diffs. Called by the host. */
    virtual void SetOutputDir(const std::string& dir) = 0;

    /** Set the HAP directory for golden image lookup. Called on device. */
    virtual void SetHapDir(const std::string& dir) = 0;

    /** Return a thread-safe copy of the most recent frame. */
    virtual Frame CopyLastFrame() const = 0;

    /** Register persist after-layout task for per-frame idle detection. No-op on previewer. */
    virtual void StartIdleDetection() = 0;

    /** Start render stability detection (hash-based). */
    virtual void RequestRenderStable() = 0;

    /** Check if render is stable. */
    virtual bool IsRenderStable() = 0;

    static RenderCapture& Get();
};

}  // namespace rendercapture

#endif  // HEADLESS_RENDER_CAPTURE_RENDERCAPTURE_H
