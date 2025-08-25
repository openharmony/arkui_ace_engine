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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_RENDER_SURFACE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_RENDER_SURFACE_H

#include <cstdint>
#include <stdint.h>

#include "base/geometry/axis.h"
#include "base/memory/ace_type.h"
#include "base/utils/noncopyable.h"
#include "core/components_ng/render/ext_surface_callback_interface.h"
#include "core/components_ng/render/render_context.h"

namespace OHOS::Ace::NG {
// RenderSurface is used for SurfaceNode
class ACE_FORCE_EXPORT RenderSurface : public virtual AceType {
    DECLARE_ACE_TYPE(NG::RenderSurface, AceType);

public:
    RenderSurface() = default;
    ~RenderSurface() override = default;

// under the condition of supporting cross platform and texture rendering,
// it is necessary to dynamically set the rendering type of the surface node.
// the defalut type is RenderSurfaceType::TEXTURE.
#ifdef RENDER_EXTRACT_SUPPORTED
    enum class RenderSurfaceType {
        UNKNOWN = -1,
        SURFACE = 0,
        TEXTURE
    };
    static RefPtr<RenderSurface> Create(const RenderSurfaceType& type = RenderSurfaceType::TEXTURE);
#else
// under the condition of supporting ohos platform
    static RefPtr<RenderSurface> Create();
#endif

    virtual void InitSurface() {}

    virtual void UpdateSurfaceConfig() {}

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

    virtual uint64_t GetUniqueIdNum() const
    {
        return 0;
    }

    virtual void UpdateSurfaceSizeInUserData(uint32_t width, uint32_t height) {}

    virtual void SetExtSurfaceBounds(int32_t left, int32_t top, int32_t width, int32_t height) {}

    virtual bool SetExtSurfaceBoundsSync(int32_t left, int32_t top, int32_t width, int32_t height)
    {
        return true;
    }

    virtual void SetExtSurfaceCallback(const RefPtr<ExtSurfaceCallbackInterface>& extSurfaceCallback) {}

    virtual void SetTransformHint(uint32_t rotation) {}

    virtual void DumpInfo() {}

    virtual void DumpInfo(std::unique_ptr<JsonValue>& json) {}

    virtual void SetIsTexture(bool isTexture) {}

    virtual void SetIsFullScreen(bool isFullScreen) {}

    virtual void SetInstanceId(int32_t instanceId) {}

    virtual void SetSurfaceDefaultSize(int32_t width, int32_t height) {}

    virtual bool IsTexture()
    {
        return false;
    }

    virtual void AttachToGLContext(int64_t textureId, bool isAttach) {}

    virtual void UpdateTextureImage(std::vector<float>& matrix) {}

    virtual void SetWebMessage(OffsetF offset) {}

    virtual void SetWebSlideAxis(Axis axis) {}

    virtual void SetWebOffset(float webOffset) {}

    virtual void SetPatternType(const std::string& type) {}

    virtual void SetBufferUsage(const std::string& usage) {}

    virtual void SetBufferTypeLeak(const std::string& bufferTypeLeak) {}

    virtual void SetSurfaceQueueSize(int32_t queueSize) {}

    virtual void DrawBufferForXComponent(RSCanvas& canvas, float width, float height, float offsetX, float offsetY) {};

    virtual void ReleaseSurfaceBuffers() {}

    virtual void RegisterSurface() const {};

    virtual void UnregisterSurface() const {};

    virtual void Connect() const {};

    virtual void Disconnect() const {};

    virtual void RegisterBufferCallback() {}

    virtual void OnWindowStateChange(bool isShow) {}

    virtual void SetIsNeedSyncGeometryProperties(bool isNeedSyncGeometryProperties) {}

    virtual void SetKeyBoardAvoidRect(RectF keyBoardAvoidRect) {}

    virtual std::string GetPSurfaceName()
    {
        return "";
    }

protected:
    ACE_DISALLOW_COPY_AND_MOVE(RenderSurface);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_RENDER_SURFACE_H
