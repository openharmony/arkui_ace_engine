/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_RENDER_TEXTURE_IMPL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_RENDER_TEXTURE_IMPL_H

#include <cstdint>

#include "base/memory/referenced.h"
#include "base/utils/noncopyable.h"
#include "core/components/video/resource/ext_texture.h"
#include "core/components_ng/render/ext_surface_callback_interface.h"
#include "core/components_ng/render/render_surface.h"

namespace OHOS::Ace::NG {
class RenderTextureImpl : public RenderSurface {
    DECLARE_ACE_TYPE(RenderTextureImpl, NG::RenderSurface);
public:
    RenderTextureImpl() = default;
    ~RenderTextureImpl() override;

    void InitSurface() override;

    void UpdateSurfaceConfig() override;

    void* GetNativeWindow() override;

    void SetRenderContext(const RefPtr<RenderContext>& renderContext) override;

    void ConfigSurface(uint32_t surfaceWidth, uint32_t surfaceHeight) override;

    bool IsSurfaceValid() const override;

    void CreateNativeWindow() override;

    void AdjustNativeWindowSize(uint32_t width, uint32_t height) override;

    std::string GetUniqueId() const override;

    void SetExtSurfaceBounds(int32_t left, int32_t top, int32_t width, int32_t height) override;

    bool SetExtSurfaceBoundsSync(int32_t left, int32_t top, int32_t width, int32_t height) override;

    void SetExtSurfaceCallback(const RefPtr<ExtSurfaceCallbackInterface>& extSurfaceCallback) override;

    void AttachToGLContext(int64_t textureId, bool isAttach) override;

    void UpdateTextureImage(std::vector<float>& matrix) override;

    void SetIsTexture(bool isTexture) override {}

    void SetIsFullScreen(bool isFullScreen) override {};

    bool IsTexture() override
    {
        return true;
    }

    void SetTextureId(int64_t id)
    {
        textureId_ = id;
    }

    int64_t GetTextureId() const
    {
        return textureId_;
    }

private:
    WeakPtr<NG::RenderContext> renderContext_;
    RefPtr<ExtTexture> extTexture_;
    RefPtr<ExtSurfaceCallbackInterface> extSurfaceCallback_;
    int64_t textureId_ = -1;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_RENDER_SURFACE_IMPL_H