/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#include "render_service_client/core/ui/rs_surface_node.h"
#include "surface_utils.h"
#include "transaction/rs_interfaces.h"

#include "base/log/dump_log.h"
#include "core/common/ace_engine.h"
#include "core/components_ng/render/adapter/rosen_render_context.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
#ifdef OHOS_PLATFORM
struct SurfaceBufferNode {
    SurfaceBufferNode(sptr<SurfaceBuffer> buf, sptr<SyncFence> fence, OffsetF orgin)
        : buffer_(std::move(buf)), acquireFence_(std::move(fence)), orgin_(orgin)
    {}
    ~SurfaceBufferNode() noexcept = default;

    sptr<SurfaceBuffer> buffer_;
    sptr<SyncFence> acquireFence_ = SyncFence::INVALID_FENCE;
    sptr<SyncFence> releaseFence_ = SyncFence::INVALID_FENCE;
    OffsetF orgin_ { 0, 0 };
    uint32_t bufferId_ {};
    uint32_t sendTimes_ = 0;
};
#endif

namespace {
const char* const SURFACE_STRIDE_ALIGNMENT = "8";
constexpr int32_t EXT_SURFACE_DEFAULT_SIZE = 1;
constexpr int32_t MAX_BUFFER_SIZE = 3;
const std::string PATTERN_TYPE_WEB = "WEBPATTERN";
const uint32_t ADJUST_WEB_DRAW_LENGTH = 3000;
const uint32_t DEFAULT_WEB_DRAW_LENGTH = 6167;
const std::string SURFACE_WIDTH = "surface_width";
const std::string SURFACE_HEIGHT = "surface_height";
const int32_t SIZE_LIMIT = 5999;
const int32_t PERMITTED_DIFFERENCE = 100;
const int32_t FAILED_LIMIT = 3;
const int32_t WAIT_FENCE_TIME = 5000;

GraphicTransformType ConvertRotation(uint32_t rotation)
{
    GraphicTransformType transform = GraphicTransformType::GRAPHIC_ROTATE_BUTT;
    switch (rotation) {
        case 0:
            transform = GraphicTransformType::GRAPHIC_ROTATE_NONE;
            break;
        case 90:
            transform = GraphicTransformType::GRAPHIC_ROTATE_90;
            break;
        case 180:
            transform = GraphicTransformType::GRAPHIC_ROTATE_180;
            break;
        case 270:
            transform = GraphicTransformType::GRAPHIC_ROTATE_270;
            break;
        default:
            transform = GraphicTransformType::GRAPHIC_ROTATE_NONE;
            break;
    }
    return transform;
}

void ReleaseAllBuffers(
    std::list<std::shared_ptr<SurfaceBufferNode>>& bufferList, const OHOS::sptr<IConsumerSurface>& consumerSurface)
{
    for (const auto& surfaceNode : bufferList) {
        if (surfaceNode) {
            consumerSurface->ReleaseBuffer(surfaceNode->buffer_, surfaceNode->releaseFence_);
        }
    }
    bufferList.clear();
}

void ReleaseAllButLastBuffer(
    std::list<std::shared_ptr<SurfaceBufferNode>>& bufferList, const OHOS::sptr<IConsumerSurface>& consumerSurface)
{
    auto iter = bufferList.begin();
    while (bufferList.size() > 1) {
        auto surfaceNode = *iter;
        if (surfaceNode) {
            consumerSurface->ReleaseBuffer(surfaceNode->buffer_, surfaceNode->releaseFence_);
        }
        iter = bufferList.erase(iter);
    }
}
} // namespace

RosenRenderSurface::~RosenRenderSurface()
{
    if (SystemProperties::GetExtSurfaceEnabled() && surfaceDelegate_) {
        surfaceDelegate_->ReleaseSurface();
        return;
    }
    if (nativeWindow_) {
        DestoryNativeWindow(nativeWindow_);
        nativeWindow_ = nullptr;
    }
    UnregisterSurface();
    if (isTexture_) {
        Rosen::RSInterfaces::GetInstance().UnregisterSurfaceBufferCallback(getpid(), GetUniqueIdNum());
        std::lock_guard<std::mutex> lock(surfaceNodeMutex_);
        while (!availableBuffers_.empty()) {
            auto surfaceNode = availableBuffers_.front();
            availableBuffers_.pop();
            if (surfaceNode) {
                consumerSurface_->ReleaseBuffer(surfaceNode->buffer_, SyncFence::INVALID_FENCE);
            }
        }
        ReleaseAllBuffers(buffersToDraw_, consumerSurface_);
        ReleaseAllBuffers(buffersToRelease_, consumerSurface_);
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
    RegisterSurface();
}

void RosenRenderSurface::Connect() const
{
    CHECK_NULL_VOID(producerSurface_);
    producerSurface_->Connect();
}

void RosenRenderSurface::Disconnect() const
{
    CHECK_NULL_VOID(producerSurface_);
    producerSurface_->Disconnect();
}

void RosenRenderSurface::RegisterSurface() const
{
    CHECK_NULL_VOID(producerSurface_);
    auto* surfaceUtils = SurfaceUtils::GetInstance();
    CHECK_NULL_VOID(surfaceUtils);
    auto ret = surfaceUtils->Add(producerSurface_->GetUniqueId(), producerSurface_);
    if (ret != SurfaceError::SURFACE_ERROR_OK) {
        LOGE("add surface error: %{public}d", ret);
    }
}

void RosenRenderSurface::UnregisterSurface() const
{
    CHECK_NULL_VOID(producerSurface_);
    auto* surfaceUtils = SurfaceUtils::GetInstance();
    CHECK_NULL_VOID(surfaceUtils);
    auto ret = surfaceUtils->Remove(producerSurface_->GetUniqueId());
    if (ret != SurfaceError::SURFACE_ERROR_OK) {
        LOGE("remove surface error: %{public}d", ret);
    }
}

void RosenRenderSurface::UpdateSurfaceConfig()
{
    CHECK_NULL_VOID(producerSurface_);
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

void RosenRenderSurface::UpdateSurfaceSizeInUserData(uint32_t width, uint32_t height)
{
    CHECK_NULL_VOID(producerSurface_);
    producerSurface_->SetUserData(SURFACE_WIDTH, std::to_string(width));
    producerSurface_->SetUserData(SURFACE_HEIGHT, std::to_string(height));
}

std::string RosenRenderSurface::GetUniqueId() const
{
    if (!producerSurface_) {
        return "";
    }
    return std::to_string(producerSurface_->GetUniqueId());
}

uint64_t RosenRenderSurface::GetUniqueIdNum() const
{
    if (!producerSurface_) {
        return 0;
    }
    return producerSurface_->GetUniqueId();
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

void RosenRenderSurface::SetTransformHint(uint32_t rotation)
{
    auto transform = ConvertRotation(rotation);
    CHECK_NULL_VOID(producerSurface_);
    producerSurface_->SetTransformHint(transform);
}

void RosenRenderSurface::DumpInfo()
{
    DumpLog::GetInstance().AddDesc(
        std::string("UserData[surface_width]: ")
            .append(producerSurface_ ? producerSurface_->GetUserData(SURFACE_WIDTH) : "NoSurface"));
    DumpLog::GetInstance().AddDesc(
        std::string("UserData[surface_height]: ")
            .append(producerSurface_ ? producerSurface_->GetUserData(SURFACE_HEIGHT) : "NoSurface"));
}

void RosenRenderSurface::SetSurfaceDefaultSize(int32_t width, int32_t height)
{
    if (consumerSurface_) {
        consumerSurface_->SetDefaultWidthAndHeight(width, height);
    }
}

void RosenRenderSurface::DrawBuffer(int32_t width, int32_t height)
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
        return;
    }
    bool res = CompareBufferSize(width, height, surfaceNode);
    ACE_SCOPED_TRACE("Web DrawBuffer");
    if (res && isNeedSyncGeometryProperties_) {
        RectF keyBoardAvoidRect = RectF(keyBoardAvoidRect_.GetX(), keyBoardAvoidRect_.GetY(), width, height);
        ACE_SCOPED_TRACE("Web DrawBuffer, SyncGeometryProperties: %s", keyBoardAvoidRect.ToString().c_str());
        rosenRenderContext->SyncGeometryProperties(keyBoardAvoidRect);
        isNeedSyncGeometryProperties_ = false;
    }
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
            Rosen::DrawingSurfaceBufferInfo info { surfaceNode->buffer_, surfaceNode->orgin_.GetX(),
                surfaceNode->orgin_.GetY(), surfaceNode->buffer_->GetSurfaceBufferWidth(),
                surfaceNode->buffer_->GetSurfaceBufferHeight() };
            auto* recordingCanvas = static_cast<RSRecordingCanvas*>(canvas.get());
            CHECK_NULL_VOID(recordingCanvas);
            recordingCanvas->DrawSurfaceBuffer(info);
#endif
        });
    rosenRenderContext->StopRecordingIfNeeded();
#endif
}

#ifdef OHOS_PLATFORM
bool RosenRenderSurface::CompareBufferSize(
    int32_t width, int32_t height, std::shared_ptr<SurfaceBufferNode> surfaceNode)
{
    int32_t bufferWidth = surfaceNode->buffer_->GetSurfaceBufferWidth();
    int32_t bufferHeight = surfaceNode->buffer_->GetSurfaceBufferHeight();
    auto pipeline = AceType::DynamicCast<NG::PipelineContext>(PipelineBase::GetCurrentContext());
    CHECK_NULL_RETURN(pipeline, true);
    ACE_SCOPED_TRACE("Web CompareBufferSize (width %d, height %d, bufferWidth %d, bufferHeight %d)"
                     " pipeline freeze status = %d",
        width, height, bufferWidth, bufferHeight, pipeline->IsFreezeFlushMessage());
    if (bufferWidth > SIZE_LIMIT || bufferHeight > SIZE_LIMIT ||
        (abs(height - bufferHeight) < PERMITTED_DIFFERENCE && abs(width - bufferWidth) < PERMITTED_DIFFERENCE)) {
        failTimes_ = 0;
    } else {
        failTimes_++;
        if (failTimes_ <= FAILED_LIMIT) {
            pipeline->SetIsFreezeFlushMessage(true);
            ACE_SCOPED_TRACE("Web SetIsFreezeFlushMessage (width %d, height %d, bufferWidth %d, bufferHeight %d)",
                width, height, bufferWidth, bufferHeight);
            return false;
        }
    }
    return true;
}
#endif

void RosenRenderSurface::ConsumeWebBuffer()
{
#ifdef OHOS_PLATFORM
    ContainerScope scope(instanceId_);
    CHECK_NULL_VOID(consumerSurface_);

    sptr<SurfaceBuffer> surfaceBuffer = nullptr;
    sptr<SyncFence> fence = SyncFence::INVALID_FENCE;
    int64_t timestamp = 0;
    OHOS::Rect damage;

    SurfaceError surfaceErr = consumerSurface_->AcquireBuffer(surfaceBuffer, fence, timestamp, damage);
    if (surfaceErr != SURFACE_ERROR_OK) {
        LOGE("cannot acquire buffer error = %{public}d", surfaceErr);
        return;
    }
    CHECK_NULL_VOID(fence);
    auto errorCode = fence->Wait(WAIT_FENCE_TIME);
    LOGD("RosenRenderSurface::ConsumeWebBuffer, wait Fence ,errorCode : %{public}d", errorCode);
    PostRenderOnlyTaskToUI();

    int32_t bufferWidth = surfaceBuffer->GetSurfaceBufferWidth();
    int32_t bufferHeight = surfaceBuffer->GetSurfaceBufferHeight();
    if (axis_ == Axis::VERTICAL) {
        if (webOffset_ >= 0 || bufferHeight < ADJUST_WEB_DRAW_LENGTH * 2 || bufferHeight >= DEFAULT_WEB_DRAW_LENGTH) {
            orgin_.SetY(0);
        } else {
            int32_t stepStear = bufferHeight - ADJUST_WEB_DRAW_LENGTH * 2;
            orgin_.SetY(stepStear * ADJUST_WEB_DRAW_LENGTH);
        }
    } else if (axis_ == Axis::HORIZONTAL) {
        if (webOffset_ >= 0 || bufferWidth < ADJUST_WEB_DRAW_LENGTH * 2 || bufferWidth >= DEFAULT_WEB_DRAW_LENGTH) {
            orgin_.SetX(0);
        } else {
            int32_t stepStear = bufferWidth - ADJUST_WEB_DRAW_LENGTH * 2;
            orgin_.SetX(stepStear * ADJUST_WEB_DRAW_LENGTH);
        }
    }
    LOGD("ConsumeWebBuffer x : %{public}f, y : %{public}f, width : %{public}d, height : %{public}d", orgin_.GetX(),
        orgin_.GetY(), bufferWidth, bufferHeight);
    ACE_SCOPED_TRACE("RosenRenderSurface::ConsumeWebBuffer, bufferWidth %d, bufferHeight %d, orign_x %f, orign_y %f",
        bufferWidth, bufferHeight, orgin_.GetX(), orgin_.GetY());

    std::shared_ptr<SurfaceBufferNode> surfaceNode = nullptr;
    {
        std::lock_guard<std::mutex> lock(surfaceNodeMutex_);
        if (availableBuffers_.size() >= MAX_BUFFER_SIZE) {
            surfaceNode = availableBuffers_.front();
            availableBuffers_.pop();
            consumerSurface_->ReleaseBuffer(surfaceNode->buffer_, SyncFence::INVALID_FENCE);
        }
        availableBuffers_.push(std::make_shared<SurfaceBufferNode>(surfaceBuffer, fence, orgin_));
    }
#endif
}

void RosenRenderSurface::PostRenderOnlyTaskToUI()
{
    auto task = [weak = renderContext_]() {
        auto renderContext = weak.Upgrade();
        CHECK_NULL_VOID(renderContext);
        auto host = renderContext->GetHost();
        CHECK_NULL_VOID(host);
        host->MarkNeedRenderOnly();
    };
    auto container = AceEngine::Get().GetContainer(instanceId_);
    CHECK_NULL_VOID(container);
    auto context = container->GetPipelineContext();
    CHECK_NULL_VOID(context);
    auto uiTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);
    if (uiTaskExecutor.IsRunOnCurrentThread()) {
        task();
    } else {
        uiTaskExecutor.PostTask(task, "ArkUIMarkNeedRenderOnly");
    }
}

void RosenRenderSurface::ConsumeXComponentBuffer()
{
#ifdef OHOS_PLATFORM
    ContainerScope scope(instanceId_);
    CHECK_NULL_VOID(consumerSurface_);

    sptr<SurfaceBuffer> surfaceBuffer = nullptr;
    sptr<SyncFence> acquireFence = SyncFence::INVALID_FENCE;
    int64_t timestamp = 0;
    OHOS::Rect damage;

    SurfaceError surfaceErr = consumerSurface_->AcquireBuffer(surfaceBuffer, acquireFence, timestamp, damage);
    if (surfaceErr != SURFACE_ERROR_OK || !surfaceBuffer) {
        TAG_LOGW(AceLogTag::ACE_XCOMPONENT, "XComponent cannot acquire buffer error = %{public}d", surfaceErr);
        return;
    }
    if (!isUniRender_.load() && !isShow_.load()) {
        consumerSurface_->ReleaseBuffer(surfaceBuffer, SyncFence::INVALID_FENCE);
        return;
    }
    MarkDirtyIfNeeded();
    auto surfaceNode = std::make_shared<SurfaceBufferNode>(surfaceBuffer, acquireFence, orgin_);
    CHECK_NULL_VOID(surfaceNode);
    surfaceNode->bufferId_ = surfaceBuffer->GetSeqNum();
    InsertSurfaceNode(surfaceNode);
    ACE_SCOPED_TRACE("ConsumeXComponentBuffer[id:%u][sendTimes:%d][size:%u]", surfaceNode->bufferId_,
        surfaceNode->sendTimes_, static_cast<uint32_t>(buffersToDraw_.size()));
#endif
}

void RosenRenderSurface::ReleaseSurfaceBuffers()
{
#ifdef OHOS_PLATFORM
    CHECK_NULL_VOID(producerSurface_);
    producerSurface_->CleanCache();
    CHECK_NULL_VOID(consumerSurface_);
    {
        std::lock_guard<std::mutex> lock(surfaceNodeMutex_);
        if (buffersToDraw_.empty()) {
            ReleaseAllButLastBuffer(buffersToRelease_, consumerSurface_);
        } else {
            ReleaseAllBuffers(buffersToRelease_, consumerSurface_);
            ReleaseAllButLastBuffer(buffersToDraw_, consumerSurface_);
        }
    }
    consumerSurface_->CleanCache();
#endif
}

/**
 * if in uniRender just to markDirty
 * if not, markDirty only when there is no buffer send to RS/RT before
 **/
void RosenRenderSurface::MarkDirtyIfNeeded()
{
    if (isUniRender_.load() || sendCount_.load() < 1) {
        PostRenderOnlyTaskToUI();
    }
}

#ifdef OHOS_PLATFORM
void RosenRenderSurface::InsertSurfaceNode(const std::shared_ptr<SurfaceBufferNode>& surfaceNode)
{
    std::lock_guard<std::mutex> lock(surfaceNodeMutex_);
    if (isUniRender_.load()) {
        auto lastSurfaceNode = buffersToDraw_.empty() ? nullptr : buffersToDraw_.back();
        if (lastSurfaceNode && lastSurfaceNode->sendTimes_ <= 0) {
            ACE_SCOPED_TRACE("ReleaseXComponentBuffer[id:%u][sendTimes:%d]", lastSurfaceNode->bufferId_,
                lastSurfaceNode->sendTimes_);
            consumerSurface_->ReleaseBuffer(lastSurfaceNode->buffer_, SyncFence::INVALID_FENCE);
            buffersToDraw_.pop_back();
        }
    }
    buffersToDraw_.emplace_back(surfaceNode);
}
#endif

void RosenRenderSurface::DrawBufferForXComponent(
    RSCanvas& canvas, float width, float height, float offsetX, float offsetY)
{
#ifdef OHOS_PLATFORM
    auto renderContext = renderContext_.Upgrade();
    CHECK_NULL_VOID(renderContext);
    std::shared_ptr<SurfaceBufferNode> surfaceNode = nullptr;
    {
        std::lock_guard<std::mutex> lock(surfaceNodeMutex_);
        if (isUniRender_.load()) {
            surfaceNode = buffersToDraw_.empty() ? nullptr : buffersToDraw_.back();
        } else {
            if (!buffersToDraw_.empty()) {
                surfaceNode = buffersToDraw_.front();
                buffersToDraw_.pop_front();
                buffersToRelease_.emplace_back(surfaceNode);
            } else if (!buffersToRelease_.empty()) {
                surfaceNode = buffersToRelease_.back();
            }
        }
        if (!surfaceNode) {
            TAG_LOGW(AceLogTag::ACE_XCOMPONENT, "surfaceNode is null");
            return;
        }
        ++surfaceNode->sendTimes_;
    }
    if (!isUniRender_.load()) {
        sendCount_.fetch_add(1);
    }
    auto uid = GetUniqueIdNum();
    if (uid == 0) {
        TAG_LOGW(AceLogTag::ACE_XCOMPONENT, "DrawSurfaceBuffer uid is invalid");
    }
    ACE_SCOPED_TRACE("DrawXComponentBuffer[id:%u][sendTimes:%d][uid:%" PRIu64 "]", surfaceNode->bufferId_,
        surfaceNode->sendTimes_, uid);
    auto& recordingCanvas = static_cast<RSRecordingCanvas&>(canvas);
    auto transform = (Container::LessThanAPITargetVersion(PlatformVersion::VERSION_FIFTEEN) ||
        surfaceNode->buffer_ == nullptr)
        ? GraphicTransformType::GRAPHIC_ROTATE_NONE
        : surfaceNode->buffer_->GetSurfaceBufferTransform();
    Rosen::DrawingSurfaceBufferInfo info { surfaceNode->buffer_, offsetX, offsetY, static_cast<int32_t>(width),
        static_cast<int32_t>(height), getpid(), GetUniqueIdNum(), surfaceNode->acquireFence_, transform };
    recordingCanvas.DrawSurfaceBuffer(info);
#endif
}

void RosenRenderSurface::RegisterBufferCallback()
{
#ifdef OHOS_PLATFORM
    CHECK_EQUAL_VOID(isTexture_, false);
    auto uid = GetUniqueIdNum();
    if (!bufferCallback_) {
        bufferCallback_ = std::make_shared<XComponentSurfaceBufferCallback>(WeakClaim(this));
    }
    if (uid == 0) {
        TAG_LOGW(AceLogTag::ACE_XCOMPONENT, "RegisterBufferCallback uid is invalid");
    }
    Rosen::RSInterfaces::GetInstance().RegisterSurfaceBufferCallback(getpid(), uid, bufferCallback_);
    auto rosenRenderContext = DynamicCast<RosenRenderContext>(renderContext_.Upgrade());
    CHECK_NULL_VOID(rosenRenderContext);
    auto rsNode = rosenRenderContext->GetRSNode();
    CHECK_NULL_VOID(rsNode);
    rsNode->SetExportTypeChangedCallback([weak = WeakClaim(this)](bool isExportTexture) {
        auto renderSurface = weak.Upgrade();
        CHECK_NULL_VOID(renderSurface);
        renderSurface->SetIsUniRender(!isExportTexture);
    });
#endif
}

void RosenRenderSurface::ReleaseSurfaceBufferById(uint32_t bufferId)
{
    std::lock_guard<std::mutex> lock(surfaceNodeMutex_);
    auto iter = buffersToDraw_.begin();
    while (iter != buffersToDraw_.end()) {
        auto surfaceNode = *iter;
        if (!surfaceNode) {
            iter = buffersToDraw_.erase(iter);
        } else if (surfaceNode->bufferId_ == bufferId) {
            // at least reserve one buffer
            auto isLast = (buffersToDraw_.size() == 1);
            ACE_SCOPED_TRACE(
                "ReleaseXComponentBuffer[id:%u][sendTimes:%d][isLast:%d]", bufferId, surfaceNode->sendTimes_, isLast);
            if (--surfaceNode->sendTimes_ <= 0 && !isLast) {
                consumerSurface_->ReleaseBuffer(surfaceNode->buffer_, surfaceNode->releaseFence_);
                buffersToDraw_.erase(iter);
            }
            return;
        } else {
            ++iter;
        }
    }
}

void RosenRenderSurface::SetIsUniRender(bool isUniRender)
{
    if (isUniRender_.load() == isUniRender) {
        return;
    }
    std::lock_guard<std::mutex> lock(surfaceNodeMutex_);
    if (buffersToDraw_.empty()) {
        auto lastSurfaceNode = buffersToRelease_.empty() ? nullptr : buffersToRelease_.back();
        if (lastSurfaceNode) {
            buffersToRelease_.pop_back();
            buffersToDraw_.emplace_back(lastSurfaceNode);
        }
    }
    ReleaseAllBuffers(buffersToRelease_, consumerSurface_);
    ReleaseAllButLastBuffer(buffersToDraw_, consumerSurface_);
    // buffersToDraw_ has 1 buffer at most, so .back() equals .front()
    auto lastSurfaceNode = buffersToDraw_.empty() ? nullptr : buffersToDraw_.back();
    if (lastSurfaceNode) {
        lastSurfaceNode->sendTimes_ = 0;
    }
    sendCount_.store(-1);
    isUniRender_.store(isUniRender);
    PostRenderOnlyTaskToUI();
}

#ifdef OHOS_PLATFORM
void RosenRenderSurface::ReleaseSurfaceBufferForRT(const Rosen::FinishCallbackRet& ret)
{
    auto surfaceBufferIds = ret.surfaceBufferIds;
    if (surfaceBufferIds.empty()) {
        return;
    }
    auto releaseFences = ret.releaseFences;
    if (surfaceBufferIds.size() != releaseFences.size()) {
        TAG_LOGW(AceLogTag::ACE_XCOMPONENT, "SurfaceBufferCallback OnFinish size not match");
    }
    auto idIter = surfaceBufferIds.begin();
    auto fenceIter = releaseFences.begin();
    std::lock_guard<std::mutex> lock(surfaceNodeMutex_);
    for (; idIter != surfaceBufferIds.end() && fenceIter != releaseFences.end(); ++idIter, ++fenceIter) {
        auto iter = buffersToRelease_.begin();
        while (iter != buffersToRelease_.end()) {
            auto surfaceNode = *iter;
            if (!surfaceNode) {
                iter = buffersToRelease_.erase(iter);
            } else if (surfaceNode->bufferId_ == *idIter) {
                sendCount_.fetch_sub(1);
                surfaceNode->releaseFence_ = *fenceIter;
                auto isLast = buffersToDraw_.empty() ? (buffersToRelease_.size() == 1) : false;
                ACE_SCOPED_TRACE("ReleaseXComponentBuffer[id:%u][sendTimes:%d][isLast:%d]", surfaceNode->bufferId_,
                    surfaceNode->sendTimes_, isLast);
                if (--surfaceNode->sendTimes_ <= 0 && !isLast) {
                    consumerSurface_->ReleaseBuffer(surfaceNode->buffer_, surfaceNode->releaseFence_);
                    buffersToRelease_.erase(iter);
                }
                break;
            } else {
                ++iter;
            }
        }
    }
    if (!buffersToDraw_.empty()) {
        PostRenderOnlyTaskToUI();
    }
}
#endif

void RosenRenderSurface::OnWindowStateChange(bool isShow)
{
    if (isUniRender_.load()) {
        return;
    }
    if (isShow_.load() == isShow) {
        return;
    }
    ACE_SCOPED_TRACE("RenderSurface::OnWindowState[isShow:%d]", isShow);
    isShow_.store(isShow);
    if (!isShow) {
        CHECK_NULL_VOID(consumerSurface_);
        std::lock_guard<std::mutex> lock(surfaceNodeMutex_);
        if (buffersToDraw_.empty()) {
            ReleaseAllButLastBuffer(buffersToRelease_, consumerSurface_);
            sendCount_.store(
                buffersToRelease_.empty() ? -1 : static_cast<int32_t>(buffersToRelease_.front()->sendTimes_ - 1));
        } else {
            ReleaseAllBuffers(buffersToRelease_, consumerSurface_);
            ReleaseAllButLastBuffer(buffersToDraw_, consumerSurface_);
            sendCount_.store(-1);
        }
    }
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

#ifdef OHOS_PLATFORM
void XComponentSurfaceBufferCallback::OnFinish(const Rosen::FinishCallbackRet& ret)
{
    ACE_SCOPED_TRACE(
        "SurfaceBufferCallback::OnFinish[uid:%" PRIu64 "][size:%zu]", ret.uid, ret.surfaceBufferIds.size());
    auto renderSurface = renderSurface_.Upgrade();
    CHECK_NULL_VOID(renderSurface);
    if (ret.uid != renderSurface->GetUniqueIdNum()) {
        return;
    }
    if (ret.isUniRender) {
        for (const auto& bufferId : ret.surfaceBufferIds) {
            renderSurface->ReleaseSurfaceBufferById(bufferId);
        }
    } else {
        renderSurface->ReleaseSurfaceBufferForRT(ret);
    }
}
#endif

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
