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

#include "foundation/graphic/graphic_2d/interfaces/inner_api/surface/surface_utils.h"
#include "render_service_client/core/ui/rs_surface_node.h"

#include "base/memory/referenced.h"
#include "base/utils/system_properties.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/render/adapter/rosen_render_context.h"
#include "core/components_ng/render/drawing.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
const char* const SURFACE_STRIDE_ALIGNMENT = "8";
constexpr int32_t SURFACE_QUEUE_SIZE = 5;
constexpr int32_t EXT_SURFACE_DEFAULT_SIZE = 1;
} // namespace
RosenRenderSurface::~RosenRenderSurface()
{
    if (SystemProperties::GetExtSurfaceEnabled() && surfaceDelegate_) {
        surfaceDelegate_->ReleaseSurface();
    } else {
        CHECK_NULL_VOID_NOLOG(producerSurface_);
        auto* surfaceUtils = SurfaceUtils::GetInstance();
        auto ret = surfaceUtils->Remove(producerSurface_->GetUniqueId());
        if (ret != SurfaceError::SURFACE_ERROR_OK) {
            LOGE("remove surface error: %{public}d", ret);
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
                LOGE("Create consumer surface failed.");
                return;
            }
            sptr<IBufferProducer> producer = consumerSurface_->GetProducer();
            if (producer == nullptr) {
                LOGE("Get producer failed.");
                return;
            }
            producerSurface_ = Surface::CreateSurfaceAsProducer(producer);
            if (producerSurface_ == nullptr) {
                LOGE("Create producer surface failed.");
                return;
            }
            if (drawBufferListener_ == nullptr) {
                drawBufferListener_ = new DrawBufferListener(WeakClaim(this));
            }
            consumerSurface_->RegisterConsumerListener(drawBufferListener_);
        } else {
            auto surfaceNode = OHOS::Rosen::RSBaseNode::ReinterpretCast<OHOS::Rosen::RSSurfaceNode>(rsNode);
            CHECK_NULL_VOID_NOLOG(surfaceNode);
            producerSurface_ = surfaceNode->GetSurface();
        }
    }
}

void RosenRenderSurface::UpdateXComponentConfig()
{
    CHECK_NULL_VOID(producerSurface_);

    auto* surfaceUtils = SurfaceUtils::GetInstance();
    auto ret = surfaceUtils->Add(producerSurface_->GetUniqueId(), producerSurface_);
    if (ret != SurfaceError::SURFACE_ERROR_OK) {
        LOGE("add surface error: %{public}d", ret);
    }

    producerSurface_->SetQueueSize(SURFACE_QUEUE_SIZE);
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
    CHECK_NULL_VOID_NOLOG(producerSurface_);
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

void RosenRenderSurface::ConsumeBuffer()
{
    ContainerScope scope(instanceId_);
    CHECK_NULL_VOID(consumerSurface_);
    auto renderContext = renderContext_.Upgrade();
    CHECK_NULL_VOID(renderContext);
    auto rosenRenderContext = DynamicCast<RosenRenderContext>(renderContext);
    CHECK_NULL_VOID(rosenRenderContext);
    auto paintRect = rosenRenderContext->GetPaintRectWithTransform();
    LOGD("paintRect = %{public}s", paintRect.ToString().c_str());
    auto width = static_cast<int32_t>(paintRect.Width());
    auto height = static_cast<int32_t>(paintRect.Height());
    ACE_SCOPED_TRACE("RosenRenderSurface::ConsumeBuffer (%d, %d)", width, height);

    sptr<SurfaceBuffer> surfaceBuffer = nullptr;
    int32_t fence = -1;
    int64_t timestamp = 0;
    OHOS::Rect damage;
    SurfaceError surfaceErr = consumerSurface_->AcquireBuffer(surfaceBuffer, fence, timestamp, damage);
    if (surfaceErr != SURFACE_ERROR_OK) {
        LOGE("cannot acquire buffer error = %{public}d", surfaceErr);
        return;
    }

    rosenRenderContext->StartRecording();
    auto rsNode = rosenRenderContext->GetRSNode();
    CHECK_NULL_VOID(rsNode);
    rsNode->DrawOnNode(
#ifndef USE_ROSEN_DRAWING
        Rosen::RSModifierType::CONTENT_STYLE, [surfaceBuffer, width, height](const std::shared_ptr<SkCanvas>& canvas) {
            Rosen::RSSurfaceBufferInfo info { surfaceBuffer, 0, 0, width, height };
            auto* recordingCanvas = static_cast<Rosen::RSRecordingCanvas*>(canvas.get());
            recordingCanvas->DrawSurfaceBuffer(info);
#else
        Rosen::RSModifierType::CONTENT_STYLE,
        [surfaceBuffer, width, height](const std::shared_ptr<RSCanvas>& canvas) {
            CHECK_NULL_VOID(canvas);
#endif
        });
    rosenRenderContext->StopRecordingIfNeeded();
    auto host = rosenRenderContext->GetHost();
    CHECK_NULL_VOID(host);
    host->MarkNeedRenderOnly();

    surfaceErr = consumerSurface_->ReleaseBuffer(surfaceBuffer, fence);
    if (surfaceErr != SURFACE_ERROR_OK) {
        LOGE("cannot release buffer error = %{public}d", surfaceErr);
        return;
    }
}

void DrawBufferListener::OnBufferAvailable()
{
    LOGD("buffer is available");
    auto renderSurface = renderSurface_.Upgrade();
    CHECK_NULL_VOID(renderSurface);
    renderSurface->ConsumeBuffer();
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
