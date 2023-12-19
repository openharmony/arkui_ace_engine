/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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
#include "core/components_ng/render/adapter/rosen_render_surface.h"

#include "surface_utils.h"
#include "render_service_client/core/ui/rs_surface_node.h"

#include "base/memory/referenced.h"
#include "base/utils/system_properties.h"
#include "base/utils/utils.h"
#include "core/common/ace_engine.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/render/adapter/rosen_render_context.h"
#include "core/components_ng/render/drawing.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
const char* const SURFACE_STRIDE_ALIGNMENT = "8";
constexpr int32_t EXT_SURFACE_DEFAULT_SIZE = 1;
constexpr int32_t MAX_BUFFER_SIZE = 3;
const std::string PATTERN_TYPE_WEB = "WEBPATTERN";
const std::vector<int32_t> DEFAULT_HEIGHT_GEAR { 7998, 7999, 8001, 8002, 8003 };
const std::vector<int32_t> DEFAULT_ORIGN_GEAR { 0, 2000, 4000, 6000, 8000 };
} // namespace
RosenRenderSurface::~RosenRenderSurface()
{
    if (SystemProperties::GetExtSurfaceEnabled() && surfaceDelegate_) {
        surfaceDelegate_->ReleaseSurface();
    } else {
        if (nativeWindow_) {
            DestoryNativeWindow(nativeWindow_);
            nativeWindow_ = nullptr;
        }
        while (!availableBuffers_.empty()) {
            auto bufferNode = availableBuffers_.front();
            bufferNode.reset();
            availableBuffers_.pop();
        }
        CHECK_NULL_VOID(producerSurface_);
        auto* surfaceUtils = SurfaceUtils::GetInstance();
        CHECK_NULL_VOID(surfaceUtils);
        auto ret = surfaceUtils->Remove(producerSurface_->GetUniqueId());
        if (ret != SurfaceError::SURFACE_ERROR_OK) {
            LOGE("remove surface error: %{public}d", ret);
        }
        while (!availableBuffers_.empty()) {
            auto surfaceNode = availableBuffers_.front();
            availableBuffers_.pop();
            consumerSurface_->ReleaseBuffer(surfaceNode->buffer_, surfaceNode->fence_);
        }
    }
}

void RosenRenderSurface::InitSurface()
{
    auto renderContext = renderContext_.Upgrade();
    if (!renderContext && SystemProperties::GetExtSurfaceEnabled()) {
        auto context = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(context);
        auto windowId = context->GetWindowId();
        surfaceDelegate_ = new OHOS::SurfaceDelegate(windowId);
        surfaceDelegate_->CreateSurface();
        if (extSurfaceCallbackInterface_) {
            surfaceDelegate_->AddSurfaceCallback(new ExtSurfaceCallback(extSurfaceCallbackInterface_));
        } else {
            surfaceDelegate_->SetBounds(0, 0, EXT_SURFACE_DEFAULT_SIZE, EXT_SURFACE_DEFAULT_SIZE);
        }
        producerSurface_ = surfaceDelegate_->GetSurface();
    } else {
        CHECK_NULL_VOID(renderContext);
        auto rosenRenderContext = AceType::DynamicCast<NG::RosenRenderContext>(renderContext);
        CHECK_NULL_VOID(rosenRenderContext);
        auto rsNode = rosenRenderContext->GetRSNode();
        CHECK_NULL_VOID(rsNode);
        if (isTexture_) {
            rsNode->SetFrameGravity(OHOS::Rosen::Gravity::RESIZE);
            consumerSurface_ = IConsumerSurface::Create();
            if (consumerSurface_ == nullptr) {
                return;
            }
            sptr<IBufferProducer> producer = consumerSurface_->GetProducer();
            if (producer == nullptr) {
                return;
            }
            producerSurface_ = Surface::CreateSurfaceAsProducer(producer);
            if (producerSurface_ == nullptr) {
                return;
            }
            if (drawBufferListener_ == nullptr) {
                drawBufferListener_ = new DrawBufferListener(WeakClaim(this));
            }
            consumerSurface_->RegisterConsumerListener(drawBufferListener_);
        } else {
            auto surfaceNode = OHOS::Rosen::RSBaseNode::ReinterpretCast<OHOS::Rosen::RSSurfaceNode>(rsNode);
            CHECK_NULL_VOID(surfaceNode);
            producerSurface_ = surfaceNode->GetSurface();
        }
    }
}

void RosenRenderSurface::UpdateXComponentConfig()
{
    CHECK_NULL_VOID(producerSurface_);

    auto* surfaceUtils = SurfaceUtils::GetInstance();
    CHECK_NULL_VOID(surfaceUtils);
    auto ret = surfaceUtils->Add(producerSurface_->GetUniqueId(), producerSurface_);
    if (ret != SurfaceError::SURFACE_ERROR_OK) {
        TAG_LOGW(AceLogTag::ACE_XCOMPONENT, "XComponent add surface error: %{public}d", ret);
    }

    producerSurface_->SetQueueSize(queueSize_);
    producerSurface_->SetUserData("SURFACE_STRIDE_ALIGNMENT", SURFACE_STRIDE_ALIGNMENT);
    producerSurface_->SetUserData("SURFACE_FORMAT", std::to_string(GRAPHIC_PIXEL_FMT_RGBA_8888));
}

void* RosenRenderSurface::GetNativeWindow()
{
    return nativeWindow_;
}

void RosenRenderSurface::SetRenderContext(const RefPtr<RenderContext>& renderContext)
{
    renderContext_ = WeakClaim(RawPtr(renderContext));
}

void RosenRenderSurface::ConfigSurface(uint32_t surfaceWidth, uint32_t surfaceHeight)
{
    CHECK_NULL_VOID(producerSurface_);
    producerSurface_->SetUserData("SURFACE_WIDTH", std::to_string(surfaceWidth));
    producerSurface_->SetUserData("SURFACE_HEIGHT", std::to_string(surfaceHeight));
}

bool RosenRenderSurface::IsSurfaceValid() const
{
    return producerSurface_ != nullptr;
}

void RosenRenderSurface::CreateNativeWindow()
{
    nativeWindow_ = CreateNativeWindowFromSurface(&producerSurface_);
}

void RosenRenderSurface::AdjustNativeWindowSize(uint32_t width, uint32_t height)
{
    CHECK_NULL_VOID(nativeWindow_);
    NativeWindowHandleOpt(nativeWindow_, SET_BUFFER_GEOMETRY, width, height);
}

std::string RosenRenderSurface::GetUniqueId() const
{
    if (!producerSurface_) {
        return "";
    }
    return std::to_string(producerSurface_->GetUniqueId());
}

void RosenRenderSurface::SetExtSurfaceBounds(int32_t left, int32_t top, int32_t width, int32_t height)
{
    if (SystemProperties::GetExtSurfaceEnabled() && surfaceDelegate_) {
        surfaceDelegate_->SetBounds(left, top, width, height);
    }
}

void RosenRenderSurface::SetExtSurfaceCallback(const RefPtr<ExtSurfaceCallbackInterface>& extSurfaceCallback)
{
    extSurfaceCallbackInterface_ = extSurfaceCallback;
}

void RosenRenderSurface::SetSurfaceDefaultSize(int32_t width, int32_t height)
{
    if (consumerSurface_) {
        consumerSurface_->SetDefaultWidthAndHeight(width, height);
    }
}

void RosenRenderSurface::DrawBuffer()
{
#ifdef OHOS_PLATFORM
    auto renderContext = renderContext_.Upgrade();
    CHECK_NULL_VOID(renderContext);
    auto rosenRenderContext = DynamicCast<RosenRenderContext>(renderContext);
    CHECK_NULL_VOID(rosenRenderContext);
    std::shared_ptr<SurfaceBufferNode> surfaceNode = nullptr;
    {
        std::lock_guard<std::mutex> lock(surfaceNodeMutex_);

        if (availableBuffers_.size() >= 1) {
            surfaceNode = availableBuffers_.back();
        }
    }
    if (!surfaceNode) {
        LOGE("RosenRenderSurface::surfaceNode is null");
        return;
    }
    ACE_SCOPED_TRACE("Web DrawBuffer");
    rosenRenderContext->StartRecording();
    auto rsNode = rosenRenderContext->GetRSNode();
    CHECK_NULL_VOID(rsNode);
    rsNode->DrawOnNode(
#ifndef USE_ROSEN_DRAWING
        Rosen::RSModifierType::CONTENT_STYLE, [surfaceNode](const std::shared_ptr<SkCanvas>& canvas) {
            CHECK_NULL_VOID(canvas);
            Rosen::RSSurfaceBufferInfo info { surfaceNode->buffer_, surfaceNode->orgin_.GetX(),
                surfaceNode->orgin_.GetY(), surfaceNode->buffer_->GetSurfaceBufferWidth(),
                surfaceNode->buffer_->GetSurfaceBufferHeight() };
            auto* recordingCanvas = static_cast<Rosen::RSRecordingCanvas*>(canvas.get());
            CHECK_NULL_VOID(recordingCanvas);
            recordingCanvas->DrawSurfaceBuffer(info);
#else
        Rosen::RSModifierType::CONTENT_STYLE,
        [surfaceNode](const std::shared_ptr<RSCanvas>& canvas) {
            CHECK_NULL_VOID(canvas);
            Rosen::DrawingSurfaceBufferInfo info {surfaceNode->buffer_, surfaceNode->orgin_.GetX(),
                surfaceNode->orgin_.GetY(), surfaceNode->buffer_->GetSurfaceBufferWidth(),
                surfaceNode->buffer_->GetSurfaceBufferHeight()};
            auto* recordingCanvas = static_cast<Rosen::Drawing::RecordingCanvas*>(canvas.get());
            CHECK_NULL_VOID(recordingCanvas);
            recordingCanvas->DrawSurfaceBuffer(info);
#endif
        });
    rosenRenderContext->StopRecordingIfNeeded();
#endif
}

void RosenRenderSurface::ConsumeWebBuffer()
{
#ifdef OHOS_PLATFORM
    ContainerScope scope(instanceId_);
    CHECK_NULL_VOID(consumerSurface_);

    sptr<SurfaceBuffer> surfaceBuffer = nullptr;
    int32_t fence = -1;
    int64_t timestamp = 0;
    OHOS::Rect damage;

    SurfaceError surfaceErr = consumerSurface_->AcquireBuffer(surfaceBuffer, fence, timestamp, damage);
    if (surfaceErr != SURFACE_ERROR_OK) {
        LOGE("cannot acquire buffer error = %{public}d", surfaceErr);
        return;
    }
    int32_t bufferHeight = surfaceBuffer->GetSurfaceBufferHeight();
    auto renderContext = renderContext_.Upgrade();
    CHECK_NULL_VOID(renderContext);
    auto task = [renderContext]() {
        auto rosenRenderContext = DynamicCast<RosenRenderContext>(renderContext);
        CHECK_NULL_VOID(rosenRenderContext);
        auto host = rosenRenderContext->GetHost();
        CHECK_NULL_VOID(host);
        host->MarkNeedRenderOnly();
    };
    PostTaskToUI(std::move(task));

    if (std::count(DEFAULT_HEIGHT_GEAR.begin(), DEFAULT_HEIGHT_GEAR.end(), bufferHeight)) {
        auto iterator = std::find(DEFAULT_HEIGHT_GEAR.begin(), DEFAULT_HEIGHT_GEAR.end(), bufferHeight);
        int32_t index = iterator - DEFAULT_HEIGHT_GEAR.begin();
        if (index >= static_cast<int32_t>(DEFAULT_HEIGHT_GEAR.size())) {
            LOGE("surfaceBuffer'height out of range");
            return;
        }
        orgin_.SetY(DEFAULT_ORIGN_GEAR[index]);
    }

    std::shared_ptr<SurfaceBufferNode> surfaceNode = nullptr;
    {
        std::lock_guard<std::mutex> lock(surfaceNodeMutex_);
        if (availableBuffers_.size() >= MAX_BUFFER_SIZE) {
            surfaceNode = availableBuffers_.front();
            availableBuffers_.pop();
            consumerSurface_->ReleaseBuffer(surfaceNode->buffer_, surfaceNode->fence_);
        }
        availableBuffers_.push(std::make_shared<SurfaceBufferNode>(surfaceBuffer, fence, orgin_));
    }
#endif
}

void RosenRenderSurface::PostTaskToUI(const std::function<void()>&& task) const
{
    CHECK_NULL_VOID(task);
    auto container = AceEngine::Get().GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    auto context = container->GetPipelineContext();
    CHECK_NULL_VOID(context);
    auto taskExecutor = context->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(task, TaskExecutor::TaskType::UI);
}

void RosenRenderSurface::ConsumeXComponentBuffer()
{
#ifdef OHOS_PLATFORM
    ContainerScope scope(instanceId_);
    CHECK_NULL_VOID(consumerSurface_);

    sptr<SurfaceBuffer> surfaceBuffer = nullptr;
    int32_t fence = -1;
    int64_t timestamp = 0;
    OHOS::Rect damage;

    SurfaceError surfaceErr = consumerSurface_->AcquireBuffer(surfaceBuffer, fence, timestamp, damage);
    if (surfaceErr != SURFACE_ERROR_OK) {
        TAG_LOGW(AceLogTag::ACE_XCOMPONENT, "XComponent cannot acquire buffer error = %{public}d", surfaceErr);
        return;
    }
    auto renderContext = renderContext_.Upgrade();
    auto host = renderContext->GetHost();
    CHECK_NULL_VOID(host);
    auto task = [host]() { host->MarkNeedRenderOnly(); };
    PostTaskToUI(std::move(task));

    std::shared_ptr<SurfaceBufferNode> surfaceNode = nullptr;
    {
        std::lock_guard<std::mutex> lock(surfaceNodeMutex_);
        if (availableBuffers_.size() >= MAX_BUFFER_SIZE) {
            surfaceNode = availableBuffers_.front();
            availableBuffers_.pop();
            surfaceErr = consumerSurface_->ReleaseBuffer(surfaceNode->buffer_, surfaceNode->fence_);
            if (surfaceErr != SURFACE_ERROR_OK) {
                TAG_LOGW(AceLogTag::ACE_XCOMPONENT, "XComponent release buffer error = %{public}d", surfaceErr);
            }
        }
        availableBuffers_.push(std::make_shared<SurfaceBufferNode>(surfaceBuffer, fence, orgin_));
    }
#endif
}

void RosenRenderSurface::DrawBufferForXComponent(RSCanvas& canvas, float width, float height)
{
#ifdef OHOS_PLATFORM
    auto renderContext = renderContext_.Upgrade();
    CHECK_NULL_VOID(renderContext);
    std::shared_ptr<SurfaceBufferNode> surfaceNode = nullptr;
    {
        std::lock_guard<std::mutex> lock(surfaceNodeMutex_);

        if (!availableBuffers_.empty()) {
            surfaceNode = availableBuffers_.back();
        }
    }
    if (!surfaceNode) {
        TAG_LOGW(AceLogTag::ACE_XCOMPONENT, "surfaceNode is null");
        return;
    }
    ACE_SCOPED_TRACE("XComponent DrawBuffer");
    auto rsCanvas = canvas.GetImpl<RSSkCanvas>();
    CHECK_NULL_VOID(rsCanvas);
#ifndef USE_ROSEN_DRAWING
    auto* skCanvas = rsCanvas->ExportSkCanvas();
    CHECK_NULL_VOID(skCanvas);
    auto* recordingCanvas = static_cast<OHOS::Rosen::RSRecordingCanvas*>(skCanvas);
    CHECK_NULL_VOID(recordingCanvas);
    Rosen::RSSurfaceBufferInfo info { surfaceNode->buffer_, 0, 0, static_cast<int32_t>(width),
        static_cast<int32_t>(height) };
    recordingCanvas->DrawSurfaceBuffer(info);
#else
    auto& recordingCanvas = static_cast<Rosen::Drawing::RecordingCanvas&>(canvas);
    Rosen::DrawingSurfaceBufferInfo info {surfaceNode->buffer_, 0, 0, static_cast<int32_t>(width),
        static_cast<int32_t>(height)};
    recordingCanvas.DrawSurfaceBuffer(info);
#endif
#endif
}

void DrawBufferListener::OnBufferAvailable()
{
    auto renderSurface = renderSurface_.Upgrade();
    CHECK_NULL_VOID(renderSurface);
    if (renderSurface->GetPatternType() == PATTERN_TYPE_WEB) {
        renderSurface->ConsumeWebBuffer();
    } else {
        renderSurface->ConsumeXComponentBuffer();
    }
}

void ExtSurfaceCallback::OnSurfaceCreated(const sptr<Surface>& /* surface */)
{
    auto interface = weakInterface_.Upgrade();
    if (interface) {
        interface->ProcessSurfaceCreate();
    }
}

void ExtSurfaceCallback::OnSurfaceChanged(const sptr<Surface>& /* surface */, int32_t width, int32_t height)
{
    auto interface = weakInterface_.Upgrade();
    if (interface) {
        interface->ProcessSurfaceChange(width, height);
    }
}

void ExtSurfaceCallback::OnSurfaceDestroyed()
{
    auto interface = weakInterface_.Upgrade();
    if (interface) {
        interface->ProcessSurfaceDestroy();
    }
}
} // namespace OHOS::Ace::NG
