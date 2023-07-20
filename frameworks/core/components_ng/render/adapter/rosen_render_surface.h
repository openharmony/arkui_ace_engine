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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_ADAPTER_ROSEN_RENDER_SURFACE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_ADAPTER_ROSEN_RENDER_SURFACE_H

#ifdef OHOS_PLATFORM
#include "ibuffer_consumer_listener.h"
#include "iconsumer_surface.h"
#include "surface.h"
#include "surface_delegate.h"
#include "window.h"
#endif

#include "base/memory/referenced.h"
#include "base/utils/noncopyable.h"
#include "core/components_ng/render/ext_surface_callback_interface.h"
#include "core/components_ng/render/render_surface.h"

namespace OHOS::Ace::NG {
class RosenRenderSurface : public RenderSurface {
    DECLARE_ACE_TYPE(RosenRenderSurface, NG::RenderSurface)
public:
    RosenRenderSurface() = default;
    ~RosenRenderSurface() override;

    void InitSurface() override;

    void UpdateXComponentConfig() override;

    void* GetNativeWindow() override;

    void SetRenderContext(const RefPtr<RenderContext>& renderContext) override;

    void ConfigSurface(uint32_t surfaceWidth, uint32_t surfaceHeight) override;

    bool IsSurfaceValid() const override;

    void CreateNativeWindow() override;

    void AdjustNativeWindowSize(uint32_t width, uint32_t height) override;

    std::string GetUniqueId() const override;

    void SetIsTexture(bool isTexture) override
    {
        isTexture_ = isTexture;
    }
    
    void ConsumeBuffer();

#ifdef OHOS_PLATFORM
    OHOS::sptr<OHOS::Surface> GetSurface() const
    {
        return producerSurface_;
    }
#endif

    void SetExtSurfaceBounds(int32_t left, int32_t top, int32_t width, int32_t height) override;

    void SetExtSurfaceCallback(const RefPtr<ExtSurfaceCallbackInterface>& extSurfaceCallback) override;

private:
#ifdef OHOS_PLATFORM
    OHOS::sptr<OHOS::Surface> producerSurface_ = nullptr;
    OHOS::sptr<IConsumerSurface> consumerSurface_ = nullptr;
    OHOS::sptr<IBufferConsumerListener> drawBufferListener_ = nullptr;
    struct NativeWindow* nativeWindow_ = nullptr;
    sptr<OHOS::SurfaceDelegate> surfaceDelegate_;
#endif
    WeakPtr<NG::RenderContext> renderContext_ = nullptr;
    RefPtr<ExtSurfaceCallbackInterface> extSurfaceCallbackInterface_ = nullptr;
    bool isTexture_ = false;

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
