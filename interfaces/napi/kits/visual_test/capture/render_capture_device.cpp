#include "render_capture_device.h"
#include "file_utils.h"

#include <chrono>
#include <cstdio>
#include <thread>
#include <unordered_map>

#include "core/pipeline_ng/pipeline_context.h"
#include "core/components_ng/render/adapter/component_snapshot.h"
#include "core/components_ng/render/snapshot_param.h"
#include "base/image/pixel_map.h"
#include "core/common/container.h"
#include <dlfcn.h>

namespace rendercapture {

constexpr int32_t kMaxTouchId = 1024;
static int32_t s_touchId = 0;

DeviceRenderCapture& DeviceRenderCapture::Instance()
{
    static DeviceRenderCapture instance;
    return instance;
}

RenderCapture& RenderCapture::Get()
{
    return DeviceRenderCapture::Instance();
}

// ---------------------------------------------------------------------------
// Hash stability
// ---------------------------------------------------------------------------

static int64_t NowMs()
{
    auto now = std::chrono::steady_clock::now().time_since_epoch();
    return std::chrono::duration_cast<std::chrono::milliseconds>(now).count();
}

uint64_t DeviceRenderCapture::ComputeFrameHash(const uint8_t* data,
                                                int32_t width, int32_t height)
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

void DeviceRenderCapture::RequestRenderStable()
{
    stableFlag_ = false;
    stableRequested_ = true;
    lastHashChangeMs_.store(NowMs());
}

bool DeviceRenderCapture::IsRenderStable()
{
    CheckRenderStable();
    return stableFlag_.load();
}

void DeviceRenderCapture::CheckRenderStable()
{
    if (!stableRequested_.load()) {
        return;
    }
    uint64_t hash = 0;
    {
        std::lock_guard<std::mutex> lock(frameMutex_);
        if (lastFrame_.data.empty()) {
            return;
        }
        hash = ComputeFrameHash(lastFrame_.data.data(),
                                lastFrame_.width, lastFrame_.height);
    }
    if (hash != previousFrameHash_) {
        previousFrameHash_ = hash;
        lastHashChangeMs_.store(NowMs());
        return;
    }
    int64_t elapsed = NowMs() - lastHashChangeMs_.load();
    if (elapsed >= kStableDurationMs) {
        stableFlag_ = true;
        stableRequested_ = false;
        printf("[RenderCapture] device render stable after %lld ms (hash=%016lx)\n",
               static_cast<long long>(elapsed), static_cast<unsigned long>(hash));
        {
            std::lock_guard<std::mutex> lock(frameMutex_);
            subscriptionManager_.Dispatch("idle", &lastFrame_);
            subscriptionManager_.Dispatch("animation.end", &lastFrame_);
        }
        idleCV_.notify_all();
    }
}

// ---------------------------------------------------------------------------
// Frame capture
// ---------------------------------------------------------------------------

Frame DeviceRenderCapture::CaptureFrame()
{
    auto pipeline = OHOS::Ace::NG::PipelineContext::GetCurrentContext();
    if (!pipeline) {
        auto container = OHOS::Ace::Container::Current();
        if (container) {
            pipeline = OHOS::Ace::AceType::DynamicCast<OHOS::Ace::NG::PipelineContext>(
                container->GetPipelineContext());
        }
    }
    if (pipeline) {
        auto root = pipeline->GetRootElement();
        if (root) {
            OHOS::Ace::NG::SnapshotOptions options;
            options.scale = 1.0f;
            options.waitUntilRenderFinished = true;
            auto [code, pixelMap] = OHOS::Ace::NG::ComponentSnapshot::GetSync(
                root, options);
            if (code == 0 && pixelMap) {
                auto acePM = OHOS::Ace::PixelMap::Create(pixelMap);
                if (acePM) {
                    if (!persistTaskRegistered_ && pipeline) {
                        pipeline->AddPersistAfterLayoutTask([this]() {
                            CheckRenderStable();
                        });
                        persistTaskRegistered_ = true;
                    }
                    std::lock_guard<std::mutex> lock(frameMutex_);
                    const uint8_t* src = acePM->GetPixels();
                    int32_t count = acePM->GetByteCount();
                    lastFrame_.data.assign(src, src + count);
                    lastFrame_.width = acePM->GetWidth();
                    lastFrame_.height = acePM->GetHeight();
                    subscriptionManager_.Dispatch("frame", &lastFrame_);
                    CheckRenderStable();
                    return lastFrame_;
                }
            }
        }
    }
    std::lock_guard<std::mutex> lock(frameMutex_);
    return lastFrame_;
}

// ---------------------------------------------------------------------------
// Request / Await / Collect
// ---------------------------------------------------------------------------

int64_t DeviceRenderCapture::RequestFrame()
{
    int64_t id = nextRequestId_.fetch_add(1);
    Frame f = CaptureFrame();
    std::lock_guard<std::mutex> lock(storeMutex_);
    frameStore_[id] = f;
    printf("[RenderCapture] device frame captured, requestId=%lld (%dx%d)\n",
           static_cast<long long>(id), f.width, f.height);
    return id;
}

bool DeviceRenderCapture::AwaitFrame(int64_t requestId, int32_t /*timeoutMs*/)
{
    // Device capture is synchronous — GetSync blocks until rendered.
    // The frame is already stored by RequestFrame.
    std::lock_guard<std::mutex> lock(storeMutex_);
    return frameStore_.find(requestId) != frameStore_.end();
}

Frame DeviceRenderCapture::CollectFrame(int64_t requestId)
{
    std::lock_guard<std::mutex> lock(storeMutex_);
    auto it = frameStore_.find(requestId);
    if (it == frameStore_.end()) {
        return Frame{};
    }
    Frame result = it->second;
    frameStore_.erase(it);
    return result;
}

void DeviceRenderCapture::SkipFrames(int32_t count)
{
    for (int32_t i = 0; i < count; i++) {
        int64_t id = RequestFrame();
        AwaitFrame(id, 5000);
        CollectFrame(id);
    }
    printf("[RenderCapture] skipped %d device frames\n", count);
}

// ---------------------------------------------------------------------------
// Idle wait
// ---------------------------------------------------------------------------

bool DeviceRenderCapture::WaitForIdle(int32_t timeoutMs)
{
    RequestRenderStable();
    std::unique_lock<std::mutex> lock(idleMutex_);
    idleCV_.wait_for(lock, std::chrono::milliseconds(timeoutMs),
                     [this]() { return IsRenderStable(); });
    return IsRenderStable();
}

void DeviceRenderCapture::StartIdleDetection()
{
    if (persistTaskRegistered_) return;
    auto pipeline = OHOS::Ace::NG::PipelineContext::GetCurrentContext();
    if (!pipeline) return;
    pipeline->AddPersistAfterLayoutTask([this]() {
        CheckRenderStable();
    });
    persistTaskRegistered_ = true;
}

// ---------------------------------------------------------------------------
// Touch — dlopen libohinput / dlsym OH_Input_InjectTouchEvent
// ---------------------------------------------------------------------------

namespace {

struct TouchEvent {
    int32_t action;
    int32_t id;
    int32_t displayX;
    int32_t displayY;
};

constexpr int32_t kTouchActionDown = 1;
constexpr int32_t kTouchActionMove = 2;
constexpr int32_t kTouchActionUp = 3;

using InjectTouchFunc = int32_t (*)(const TouchEvent*);

InjectTouchFunc GetInjectTouch()
{
    static InjectTouchFunc fn = []() -> InjectTouchFunc {
        void* lib = dlopen("libohinput.z.so", RTLD_NOW | RTLD_NOLOAD);
        if (!lib) {
            return nullptr;
        }
        auto sym = reinterpret_cast<InjectTouchFunc>(
            dlsym(lib, "OH_Input_InjectTouchEvent"));
        return sym;
    }();
    return fn;
}

void DoTouch(int32_t action, float x, float y)
{
    auto fn = GetInjectTouch();
    if (!fn) {
        printf("[RenderCapture] Touch: libohinput not loaded\n");
        return;
    }
    TouchEvent ev{};
    ev.action = action;
    ev.id = s_touchId;
    ev.displayX = static_cast<int32_t>(x);
    ev.displayY = static_cast<int32_t>(y);
    fn(&ev);
}

}  // namespace

void DeviceRenderCapture::TouchDown(float x, float y)
{
    DoTouch(kTouchActionDown, x, y);
}

void DeviceRenderCapture::TouchMove(float x, float y)
{
    DoTouch(kTouchActionMove, x, y);
}

void DeviceRenderCapture::TouchUp(float x, float y)
{
    DoTouch(kTouchActionUp, x, y);
    s_touchId = (s_touchId + 1) % kMaxTouchId;
}

// ---------------------------------------------------------------------------
// Platform queries
// ---------------------------------------------------------------------------

bool DeviceRenderCapture::IsPreviewer()
{
    return false;
}

bool DeviceRenderCapture::IsHeadless()
{
    return true;
}

void DeviceRenderCapture::GetScreenSize(int32_t* w, int32_t* h)
{
    if (w == nullptr || h == nullptr) {
        return;
    }
    std::lock_guard<std::mutex> lock(frameMutex_);
    *w = lastFrame_.width;
    *h = lastFrame_.height;
}

// ---------------------------------------------------------------------------
// Output / HAP dir
// ---------------------------------------------------------------------------

void DeviceRenderCapture::SetOutputDir(const std::string& dir)
{
    outputDir_ = dir;
}

void DeviceRenderCapture::SetHapDir(const std::string& dir)
{
    hapDir_ = dir;
}

Frame DeviceRenderCapture::CopyLastFrame() const
{
    std::lock_guard<std::mutex> lock(frameMutex_);
    return lastFrame_;
}

}  // namespace rendercapture
