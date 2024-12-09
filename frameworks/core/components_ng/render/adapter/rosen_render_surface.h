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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_ADAPTER_ROSEN_RENDER_SURFACE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_ADAPTER_ROSEN_RENDER_SURFACE_H

#ifdef OHOS_PLATFORM
#include "ibuffer_consumer_listener.h"
#include "iconsumer_surface.h"
#include "surface.h"
#include "surface/window.h"
#include "surface_delegate.h"
#include "transaction/rs_render_service_client.h"
#endif

#include "base/memory/referenced.h"
#include "base/utils/noncopyable.h"
#include "core/components_ng/render/drawing.h"
#include "core/components_ng/render/ext_surface_callback_interface.h"
#include "core/components_ng/render/render_surface.h"

namespace OHOS::Ace::NG {
constexpr int32_t SURFACE_QUEUE_SIZE = 5;
#ifdef OHOS_PLATFORM
struct SurfaceBufferNode;
#endif

class RosenRenderSurface : public RenderSurface {
    DECLARE_ACE_TYPE(RosenRenderSurface, NG::RenderSurface)
public:
    RosenRenderSurface() = default;
    ~RosenRenderSurface() override;

    void InitSurface() override;

    void UpdateSurfaceConfig() override;

    void* GetNativeWindow() override;

    void SetRenderContext(const RefPtr<RenderContext>& renderContext) override;

    void ConfigSurface(uint32_t surfaceWidth, uint32_t surfaceHeight) override;

    bool IsSurfaceValid() const override;

    void CreateNativeWindow() override;

    void AdjustNativeWindowSize(uint32_t width, uint32_t height) override;

    std::string GetUniqueId() const override;

    uint64_t GetUniqueIdNum() const;

    void SetIsTexture(bool isTexture) override
    {
        isTexture_ = isTexture;
    }

    void SetInstanceId(int32_t instanceId) override
    {
        instanceId_ = instanceId;
    }

    void SetSurfaceDefaultSize(int32_t width, int32_t height) override;

    void ConsumeXComponentBuffer();

    void ConsumeWebBuffer();

    void SetWebMessage(OffsetF offset) override
    {
        orgin_ = offset;
    }

    void SetPatternType(const std::string& type) override
    {
        patternType_ = type;
    }

    std::string GetPatternType() const
    {
        return patternType_;
    }

    void SetWebSlideAxis(Axis axis) override
    {
        axis_ = axis;
    }

    void SetWebOffset(float webOffset) override
    {
        webOffset_ = webOffset;
    }

    void SetSurfaceQueueSize(int32_t queueSize = SURFACE_QUEUE_SIZE) override
    {
        queueSize_ = queueSize;
    }

    void DrawBuffer(int32_t width = -1, int32_t height = -1);

    void DrawBufferForXComponent(RSCanvas& canvas, float width, float height, float offsetX, float offsetY) override;

#ifdef OHOS_PLATFORM
    OHOS::sptr<OHOS::Surface> GetSurface() const
    {
        return producerSurface_;
    }

    bool CompareBufferSize(int32_t width, int32_t height, std::shared_ptr<SurfaceBufferNode> surfaceNode);

    void SetIsNeedSyncGeometryProperties(bool isNeedSyncGeometryProperties) override
    {
        isNeedSyncGeometryProperties_ = isNeedSyncGeometryProperties;
    }

    void SetKeyBoardAvoidRect(RectF keyBoardAvoidRect) override
    {
        keyBoardAvoidRect_ = keyBoardAvoidRect;
    }

#endif

    void ReleaseSurfaceBuffers() override;

    void UpdateSurfaceSizeInUserData(uint32_t width, uint32_t height) override;

    void SetExtSurfaceBounds(int32_t left, int32_t top, int32_t width, int32_t height) override;

    void SetExtSurfaceCallback(const RefPtr<ExtSurfaceCallbackInterface>& extSurfaceCallback) override;

    void SetTransformHint(uint32_t rotation) override;

    void RegisterSurface() const override;

    void UnregisterSurface() const override;

    void Connect() const override;

    void Disconnect() const override;

    void DumpInfo() override;

    void ReleaseSurfaceBufferById(uint32_t bufferId);

#ifdef OHOS_PLATFORM
    void ReleaseSurfaceBufferForRT(const Rosen::FinishCallbackRet& ret);
#endif

    void RegisterBufferCallback() override;

    void SetIsUniRender(bool isUniRender);

    void PostRenderOnlyTaskToUI();

    void OnWindowStateChange(bool isShow) override;

private:
    void MarkDirtyIfNeeded();

#ifdef OHOS_PLATFORM
    void InsertSurfaceNode(const std::shared_ptr<SurfaceBufferNode>& surfaceNode);
#endif

    std::mutex surfaceNodeMutex_;
    bool isNeedSyncGeometryProperties_ = false;
    RectF keyBoardAvoidRect_;
    OffsetF orgin_ { 0, 0 };
    std::string patternType_;
    int32_t queueSize_ = SURFACE_QUEUE_SIZE;
    Axis axis_ = Axis::NONE;
    float webOffset_ = 0.0;
#ifdef OHOS_PLATFORM
    OHOS::sptr<OHOS::Surface> producerSurface_ = nullptr;
    OHOS::sptr<IConsumerSurface> consumerSurface_ = nullptr;
    OHOS::sptr<IBufferConsumerListener> drawBufferListener_ = nullptr;
    struct NativeWindow* nativeWindow_ = nullptr;
    sptr<OHOS::SurfaceDelegate> surfaceDelegate_;
    std::queue<std::shared_ptr<SurfaceBufferNode>> availableBuffers_;
    std::list<std::shared_ptr<SurfaceBufferNode>> buffersToDraw_;
    std::list<std::shared_ptr<SurfaceBufferNode>> buffersToRelease_;
    std::shared_ptr<Rosen::SurfaceBufferCallback> bufferCallback_;
    int32_t failTimes_ = 0;
#endif
    WeakPtr<NG::RenderContext> renderContext_ = nullptr;
    RefPtr<ExtSurfaceCallbackInterface> extSurfaceCallbackInterface_ = nullptr;
    bool isTexture_ = false;
    int32_t instanceId_;

    std::atomic_bool isShow_ = true;
    std::atomic_bool isUniRender_ = true;
    std::atomic_int32_t sendCount_ = -1;

    ACE_DISALLOW_COPY_AND_MOVE(RosenRenderSurface);
};

#ifdef OHOS_PLATFORM
class DrawBufferListener : public IBufferConsumerListener {
public:
    explicit DrawBufferListener(const WeakPtr<NG::RosenRenderSurface>& renderSurface) : renderSurface_(renderSurface) {}
    ~DrawBufferListener() override = default;
    void OnBufferAvailable() override;

private:
    WeakPtr<NG::RosenRenderSurface> renderSurface_;
};

class XComponentSurfaceBufferCallback : public Rosen::SurfaceBufferCallback {
public:
    explicit XComponentSurfaceBufferCallback(const WeakPtr<NG::RosenRenderSurface>& renderSurface)
        : renderSurface_(renderSurface)
    {}
    virtual ~XComponentSurfaceBufferCallback() = default;
    void OnFinish(const Rosen::FinishCallbackRet& ret) override;
    void OnAfterAcquireBuffer(const Rosen::AfterAcquireBufferRet& ret) override {}

private:
    WeakPtr<NG::RosenRenderSurface> renderSurface_;
};
#endif

#ifdef OHOS_PLATFORM
class ExtSurfaceCallback : public OHOS::SurfaceDelegate::ISurfaceCallback {
public:
    explicit ExtSurfaceCallback(const WeakPtr<ExtSurfaceCallbackInterface>& interface) : weakInterface_(interface) {}

    ~ExtSurfaceCallback() override = default;

    void OnSurfaceCreated(const sptr<Surface>& surface) override;

    void OnSurfaceChanged(const sptr<Surface>& surface, int32_t width, int32_t height) override;

    void OnSurfaceDestroyed() override;

private:
    WeakPtr<ExtSurfaceCallbackInterface> weakInterface_;
};
#endif
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_ADAPTER_ROSEN_RENDER_SURFACE_H
