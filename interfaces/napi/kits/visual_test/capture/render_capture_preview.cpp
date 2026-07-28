#include "render_capture_preview.h"
#include "file_utils.h"
#include "subscription_manager.h"

#include <chrono>
#include <cstdio>
#include <thread>

#include "base/utils/system_properties.h"

namespace rendercapture {

PreviewRenderCapture& PreviewRenderCapture::Instance()
{
    static PreviewRenderCapture instance;
    return instance;
}

RenderCapture& RenderCapture::Get()
{
    return PreviewRenderCapture::Instance();
}

// ---------------------------------------------------------------------------
// Helpers
// ---------------------------------------------------------------------------

static int64_t NowMs()
{
    auto now = std::chrono::steady_clock::now().time_since_epoch();
    return std::chrono::duration_cast<std::chrono::milliseconds>(now).count();
}

// ---------------------------------------------------------------------------
// Frame capture
// ---------------------------------------------------------------------------

void PreviewRenderCapture::RegisterFrameData(const void* data, int32_t width, int32_t height)
{
    if (data == nullptr || width <= 0 || height <= 0) {
        printf("[RenderCapture] RegisterFrameData: invalid args (data=%p, %dx%d)\n",
               data, width, height);
        return;
    }
    std::lock_guard<std::mutex> lock(frameMutex_);
    size_t size = static_cast<size_t>(width) * static_cast<size_t>(height) * 4;
    bool first = lastFrame_.data.empty();
    lastFrame_.data.assign(static_cast<const uint8_t*>(data),
                           static_cast<const uint8_t*>(data) + size);
    lastFrame_.width = width;
    lastFrame_.height = height;
    if (first) {
        printf("[RenderCapture] frame stream started: %dx%d RGBA (%zu bytes/frame)\n",
               width, height, size);
    }
    hasFrame_ = true;
}

void PreviewRenderCapture::GetScreenSize(int32_t* w, int32_t* h)
{
    if (w == nullptr || h == nullptr) {
        return;
    }
    std::lock_guard<std::mutex> lock(frameMutex_);
    *w = lastFrame_.width;
    *h = lastFrame_.height;
}

// ---------------------------------------------------------------------------
// Stability detection
// ---------------------------------------------------------------------------

uint64_t PreviewRenderCapture::ComputeFrameHash(const uint8_t* data, int32_t width, int32_t height)
{
    if (data == nullptr || width <= 0 || height <= 0) {
        return 0;
    }
    const uint64_t fnvPrime = 1099511628211ULL;
    const uint64_t fnvBasis = 14695981039346656037ULL;
    uint64_t hash = fnvBasis;
    const int stride = 8;
    for (int y = 0; y < height; y += stride) {
        const uint8_t* row = data + static_cast<size_t>(y) * width * 4;
        for (int x = 0; x < width; x += stride) {
            const uint8_t* px = row + static_cast<size_t>(x) * 4;
            hash ^= px[0]; hash *= fnvPrime;
            hash ^= px[1]; hash *= fnvPrime;
            hash ^= px[2]; hash *= fnvPrime;
            hash ^= px[3]; hash *= fnvPrime;
        }
    }
    return hash;
}

void PreviewRenderCapture::RequestRenderStable()
{
    stableFlag_ = false;
    stableRequested_ = true;
    lastHashChangeMs_.store(NowMs());
    printf("[RenderCapture] render stability requested\n");
}

bool PreviewRenderCapture::IsRenderStable()
{
    return stableFlag_.load();
}

void PreviewRenderCapture::CheckRenderStable()
{
    // Read lastFrameTime_ under mutex to avoid data race.
    std::chrono::steady_clock::time_point prevTime;
    {
        std::lock_guard<std::mutex> lock(frameMutex_);
        prevTime = lastFrameTime_;
        if (!lastFrame_.data.empty()) {
            subscriptionManager_.Dispatch("frame", &lastFrame_);
            lastFrameTime_ = std::chrono::steady_clock::now();
        }
    }

    // If no frame for 30 seconds, dispatch an error.
    if (prevTime.time_since_epoch().count() > 0) {
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(
            lastFrameTime_ - prevTime).count();
        if (elapsed > 30) {
            subscriptionManager_.Dispatch("error", nullptr);
        }
    }

    if (!stableRequested_.load()) {
        return;
    }
    if (!hasFrame_.load()) {
        return;
    }
    uint64_t hash = 0;
    {
        std::lock_guard<std::mutex> lock(frameMutex_);
        if (lastFrame_.data.empty()) {
            return;
        }
        hash = ComputeFrameHash(lastFrame_.data.data(), lastFrame_.width, lastFrame_.height);
    }
    if (hash != previousFrameHash_) {
        // Hash changed — reset the stability clock.
        previousFrameHash_ = hash;
        lastHashChangeMs_.store(NowMs());
        return;
    }
    // Hash unchanged — check if stable long enough.
    int64_t elapsed = NowMs() - lastHashChangeMs_.load();
    if (elapsed >= kStableDurationMs) {
        stableFlag_ = true;
        stableRequested_ = false;
        printf("[RenderCapture] render stable after %lld ms (hash=%016lx)\n",
               static_cast<long long>(elapsed), hash);

        // Render is stable — no more frames changing.
        // Both idle and animation-end fire here.
        {
            std::lock_guard<std::mutex> lock(frameMutex_);
            subscriptionManager_.Dispatch("idle", &lastFrame_);
            subscriptionManager_.Dispatch("animation.end", &lastFrame_);
        }

        std::lock_guard<std::mutex> lock(requestMutex_);
        if (!pendingRequests_.empty()) {
            int64_t id = pendingRequests_.front();
            pendingRequests_.pop();
            frameStore_[id] = lastFrame_;
            frameReady_[id] = true;
            printf("[RenderCapture] frame captured for requestId=%lld\n",
                   static_cast<long long>(id));
        }
    }
}

// ---------------------------------------------------------------------------
// Request / Await / Collect
// ---------------------------------------------------------------------------

int64_t PreviewRenderCapture::RequestFrame()
{
    int64_t id = nextRequestId_.fetch_add(1);
    printf("[RenderCapture] frame requested, requestId=%lld\n", static_cast<long long>(id));
    fflush(stdout);

    // Capture immediately if a frame already exists.
    {
        std::lock_guard<std::mutex> lock(frameMutex_);
        printf("[RenderCapture] Request(this=%p): lastFrame_ %s (%dx%d, %zu bytes)\n",
               (void*)this,
               lastFrame_.data.empty() ? "EMPTY" : "HAS DATA",
               lastFrame_.width, lastFrame_.height, lastFrame_.data.size());
        fflush(stdout);
        if (!lastFrame_.data.empty()) {
            std::lock_guard<std::mutex> lock2(requestMutex_);
            frameStore_[id] = lastFrame_;
            frameReady_[id] = true;
            printf("[RenderCapture] frame captured immediately for requestId=%lld\n",
                   static_cast<long long>(id));
            fflush(stdout);
            return id;
        }
    }

    // No frame yet — start stability detection.
    {
        std::lock_guard<std::mutex> lock(requestMutex_);
        pendingRequests_.push(id);
        frameReady_[id] = false;
    }
    RequestRenderStable();
    return id;
}

bool PreviewRenderCapture::AwaitFrame(int64_t requestId, int32_t timeoutMs)
{
    auto start = std::chrono::steady_clock::now();
    while (true) {
        {
            std::lock_guard<std::mutex> lock(requestMutex_);
            auto it = frameReady_.find(requestId);
            if (it != frameReady_.end() && it->second) {
                return true;
            }
        }
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now() - start).count();
        if (elapsed >= timeoutMs) {
            printf("[RenderCapture] AwaitFrame timeout for requestId=%lld after %d ms\n",
                   static_cast<long long>(requestId), timeoutMs);
            return false;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }
}

Frame PreviewRenderCapture::CollectFrame(int64_t requestId)
{
    std::lock_guard<std::mutex> lock(requestMutex_);
    auto it = frameStore_.find(requestId);
    if (it == frameStore_.end()) {
        printf("[RenderCapture] CollectFrame: frame not found for requestId=%lld\n",
               static_cast<long long>(requestId));
        return Frame{};
    }
    Frame result = it->second;
    frameStore_.erase(it);
    frameReady_.erase(requestId);
    printf("[RenderCapture] frame collected for requestId=%lld (%dx%d, %zu bytes)\n",
           static_cast<long long>(requestId), result.width, result.height, result.data.size());
    return result;
}

// ---------------------------------------------------------------------------
// Convenience
// ---------------------------------------------------------------------------

bool PreviewRenderCapture::WaitForIdle(int32_t timeoutMs)
{
    RequestRenderStable();
    int32_t elapsed = 0;
    const int32_t pollInterval = 16;
    const int32_t frameFallbackMs = 400;
    while (!IsRenderStable()) {
        if (elapsed >= timeoutMs) {
            printf("[RenderCapture] WaitForIdle timeout after %d ms\n", timeoutMs);
            return false;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(pollInterval));
        elapsed += pollInterval;
        // Fallback: if hash stability never triggers (single-frame previewer
        // or continuous render loop with minor frame-to-frame variation),
        // accept any frame after 400ms.  The delay is long enough for
        // scrollEdge/scrollPage animations (~250-300ms) to finish.
        if (elapsed >= frameFallbackMs) {
            std::lock_guard<std::mutex> lock(frameMutex_);
            if (!lastFrame_.data.empty()) {
                printf("[RenderCapture] fallback idle after %d ms\n", elapsed);
                return true;
            }
        }
    }
    printf("[RenderCapture] idle after %d ms\n", elapsed);
    return true;
}

void PreviewRenderCapture::SkipFrames(int32_t count)
{
    for (int32_t i = 0; i < count; i++) {
        int64_t requestId = RequestFrame();
        if (!AwaitFrame(requestId, 5000)) {
            printf("[RenderCapture] SkipFrames: timeout at frame %d/%d\n", i + 1, count);
            return;
        }
        CollectFrame(requestId);
    }
    printf("[RenderCapture] skipped %d frames\n", count);
}

// ---------------------------------------------------------------------------
// Touch stubs
// ---------------------------------------------------------------------------

void PreviewRenderCapture::TouchDown(float x, float y)
{
    printf("[RenderCapture] TouchDown(%.0f, %.0f) stub. Requires previewer patch.\n", x, y);
}

void PreviewRenderCapture::TouchMove(float x, float y)
{
    printf("[RenderCapture] TouchMove(%.0f, %.0f) stub. Requires previewer patch.\n", x, y);
}

void PreviewRenderCapture::TouchUp(float x, float y)
{
    printf("[RenderCapture] TouchUp(%.0f, %.0f) stub. Requires previewer patch.\n", x, y);
}

// ---------------------------------------------------------------------------
// Platform queries
// ---------------------------------------------------------------------------

bool PreviewRenderCapture::IsPreviewer()
{
    return true;
}

bool PreviewRenderCapture::IsHeadless()
{
    return OHOS::Ace::SystemProperties::IsHeadlessMode();
}

// ---------------------------------------------------------------------------
// Lifecycle / config
// ---------------------------------------------------------------------------

void PreviewRenderCapture::SetVisualTestDone()
{
    visualTestDone_ = true;
}

bool PreviewRenderCapture::IsVisualTestDone()
{
    return visualTestDone_.load();
}

void PreviewRenderCapture::SetOutputDir(const std::string& dir)
{
    outputDir_ = dir;
}

void PreviewRenderCapture::SetHapDir(const std::string& dir)
{
    hapDir_ = dir;
}

void PreviewRenderCapture::StartIdleDetection()
{
    // No-op on previewer — idle detection is driven by SendPixmap push.
}

void PreviewRenderCapture::RequestRenderStable()
{
    // No-op on previewer.
}

bool PreviewRenderCapture::IsRenderStable()
{
    return stableFlag_.load();
}

Frame PreviewRenderCapture::CopyLastFrame() const
{
    std::lock_guard<std::mutex> lock(frameMutex_);
    return lastFrame_;
}

}  // namespace rendercapture

// ---------------------------------------------------------------------------
// Render-thread hook (called by the previewer every frame)
// ---------------------------------------------------------------------------

extern "C" __attribute__((visibility("default"))) void RenderCapture_OnFrameData(
    const void* data, int32_t width, int32_t height)
{
    printf("[RenderCapture] OnFrameData called: %dx%d data=%p\n", width, height, data);
    fflush(stdout);
    rendercapture::PreviewRenderCapture::Instance().RegisterFrameData(data, width, height);
    printf("[RenderCapture] OnFrameData: frame stored, checking stable\n");
    fflush(stdout);
    rendercapture::PreviewRenderCapture::Instance().CheckRenderStable();
    printf("[RenderCapture] OnFrameData: done\n");
    fflush(stdout);
}

// ---------------------------------------------------------------------------
// Scroll-end hook (called by ace_engine ScrollPattern when scroll stops)
// ---------------------------------------------------------------------------

extern "C" __attribute__((visibility("default"))) void VisualTest_OnScrollEnd(
    float /*finalX*/, float /*finalY*/)
{
    printf("[RenderCapture] VisualTest_OnScrollEnd called\n");
    fflush(stdout);

    auto& instance = rendercapture::PreviewRenderCapture::Instance();
    auto frame = instance.CopyLastFrame();
    if (!frame.data.empty()) {
        instance.GetSubscriptionManager().Dispatch("scroll.end", &frame);
    }
    printf("[RenderCapture] VisualTest_OnScrollEnd: dispatched scroll.end\n");
    fflush(stdout);
}

extern "C" __attribute__((visibility("default"))) void VisualTest_SetOutputDir(
    const char* dir)
{
    rendercapture::PreviewRenderCapture::Instance().SetOutputDir(
        dir ? std::string(dir) : std::string());
}

extern "C" __attribute__((visibility("default"))) bool VisualTest_IsDone()
{
    return rendercapture::PreviewRenderCapture::Instance().IsVisualTestDone();
}
