/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

#include "base/memory/referenced.h"
#include "base/utils/system_properties.h"
#include "base/utils/utils.h"
#include "core/components_ng/render/adapter/rosen_render_context.h"

namespace OHOS::Ace::NG {
RosenRenderSurface::~RosenRenderSurface()
{
}

void RosenRenderSurface::InitSurface()
{
}

void RosenRenderSurface::UpdateSurfaceConfig()
{
}

void* RosenRenderSurface::GetNativeWindow()
{
    return nullptr;
}

void RosenRenderSurface::SetRenderContext(const RefPtr<RenderContext>& renderContext)
{
}

void RosenRenderSurface::ConfigSurface(uint32_t surfaceWidth, uint32_t surfaceHeight)
{
}

bool RosenRenderSurface::IsSurfaceValid() const
{
    return false;
}

void RosenRenderSurface::CreateNativeWindow()
{
}

void RosenRenderSurface::AdjustNativeWindowSize(uint32_t width, uint32_t height)
{
}

std::string RosenRenderSurface::GetUniqueId() const
{
    return "";
}

void RosenRenderSurface::SetExtSurfaceBounds(int32_t left, int32_t top, int32_t width, int32_t height)
{
}

void RosenRenderSurface::SetExtSurfaceCallback(const RefPtr<ExtSurfaceCallbackInterface>& extSurfaceCallback)
{
}

void RosenRenderSurface::SetTransformHint(uint32_t rotation)
{
}

void RosenRenderSurface::SetSurfaceDefaultSize(int32_t width, int32_t height) {}

void RosenRenderSurface::ConsumeWebBuffer() {}

void DrawBuffer() {}

void ConsumeXComponentBuffer() {}

void RosenRenderSurface::DrawBufferForXComponent(
    RSCanvas& canvas, float width, float height, float offsetX, float offsetY)
{}

void RosenRenderSurface::ReleaseSurfaceBuffers() {}

void RosenRenderSurface::UpdateSurfaceSizeInUserData(uint32_t width, uint32_t height) {}

void RosenRenderSurface::DumpInfo() {}

void RosenRenderSurface::RegisterSurface() const {}

void RosenRenderSurface::UnregisterSurface() const {}

void RosenRenderSurface::Connect() const {}

void RosenRenderSurface::Disconnect() const {}

uint64_t RosenRenderSurface::GetUniqueIdNum() const
{
    return 0;
}

void RosenRenderSurface::RegisterBufferCallback() {}

} // namespace OHOS::Ace::NG
