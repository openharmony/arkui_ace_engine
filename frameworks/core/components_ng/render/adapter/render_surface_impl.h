/*
 * Copyright (c) 2023-2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_RENDER_SURFACE_IMPL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_RENDER_SURFACE_IMPL_H

#include <cstdint>

#include "base/memory/referenced.h"
#include "base/utils/noncopyable.h"
#include "core/components/video/resource/ext_surface.h"
#include "core/components_ng/render/ext_surface_callback_interface.h"
#include "core/components_ng/render/render_surface.h"

namespace OHOS::Ace::NG {

class RenderSurfaceImpl : public RenderSurface {
    DECLARE_ACE_TYPE(RenderSurfaceImpl, NG::RenderSurface)
public:
    RenderSurfaceImpl() = default;
    ~RenderSurfaceImpl() override;

    void InitSurface() override;

    void UpdateSurfaceConfig() override;

    void* GetNativeWindow() override;

    void SetRenderContext(const RefPtr<RenderContext>& renderContext) override;

    void ConfigSurface(uint32_t surfaceWidth, uint32_t surfaceHeight) override;

    bool IsSurfaceValid() const override;

    void CreateNativeWindow() override;

    void AdjustNativeWindowSize(uint32_t width, uint32_t height) override;

    std::string GetUniqueId() const override;

    void SetSurfaceId(int64_t id)
    {
        surfaceId_ = id;
    }

    int64_t GetSurfaceId() const
    {
        return surfaceId_;
    }

    void SetExtSurfaceBounds(int32_t left, int32_t top, int32_t width, int32_t height) override;

    bool SetExtSurfaceBoundsSync(int32_t left, int32_t top, int32_t width, int32_t height) override;

    void SetExtSurfaceCallback(const RefPtr<ExtSurfaceCallbackInterface>& extSurfaceCallback) override;

    void SetIsFullScreen(bool isFullScreen) override;
#ifdef RENDER_EXTRACT_SUPPORTED
    void SetSurfaceRotation(bool isLock);

    void SetSurfaceRect(float positionX, float positionY, float width, float height);
#endif
private:
    WeakPtr<NG::RenderContext> renderContext_;
    RefPtr<ExtSurface> extSurface_;
    RefPtr<ExtSurfaceCallbackInterface> extSurfaceCallback_;
    int64_t surfaceId_ = -1;
    void* nativeWindow_ = nullptr;
    bool isSetConfigSurface_ = false;
    Rect lastRect_;

    ACE_DISALLOW_COPY_AND_MOVE(RenderSurfaceImpl);
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_RENDER_SURFACE_IMPL_H
