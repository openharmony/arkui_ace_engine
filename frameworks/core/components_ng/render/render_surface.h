/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_RENDER_SURFACE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_RENDER_SURFACE_H

#include <cstdint>
#include <stdint.h>

#include "base/memory/ace_type.h"
#include "base/utils/noncopyable.h"
#include "core/components_ng/render/ext_surface_callback_interface.h"
#include "core/components_ng/render/render_context.h"

namespace OHOS::Ace::NG {
// RenderSurface is used for SurfaceNode
class RenderSurface : public virtual AceType {
    DECLARE_ACE_TYPE(NG::RenderSurface, AceType)

public:
    RenderSurface() = default;
    ~RenderSurface() override = default;

    static RefPtr<RenderSurface> Create();

    virtual void InitSurface() {}

    virtual void UpdateXComponentConfig() {}

    virtual void* GetNativeWindow()
    {
        return nullptr;
    }

    virtual void SetRenderContext(const RefPtr<RenderContext>& renderContext) {};

    virtual void ConfigSurface(uint32_t surfaceWidth, uint32_t surfaceHeight) {};

    virtual bool IsSurfaceValid() const
    {
        return false;
    }

    virtual void CreateNativeWindow() {};

    virtual void AdjustNativeWindowSize(uint32_t width, uint32_t height) {}

    virtual std::string GetUniqueId() const
    {
        return "";
    }

    virtual void SetExtSurfaceBounds(int32_t left, int32_t top, int32_t width, int32_t height) {}

    virtual bool SetExtSurfaceBoundsSync(int32_t left, int32_t top, int32_t width, int32_t height)
    {
        return true;
    }

    virtual void SetExtSurfaceCallback(const RefPtr<ExtSurfaceCallbackInterface>& extSurfaceCallback) {}

    virtual void SetIsTexture(bool isTexture) {}

    virtual void SetIsFullScreen(bool isFullScreen) {}

    virtual void SetInstanceId(int32_t instanceId) {}

protected:
    ACE_DISALLOW_COPY_AND_MOVE(RenderSurface);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_RENDER_SURFACE_H
