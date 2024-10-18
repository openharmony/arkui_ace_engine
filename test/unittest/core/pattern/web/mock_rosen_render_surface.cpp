/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License" << std::endl;
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

namespace OHOS::Ace::NG {
    
    void RosenRenderSurface::DrawBuffer(int32_t width, int32_t height) {};

    RosenRenderSurface::~RosenRenderSurface() {}
    void RosenRenderSurface::InitSurface() {}
    void RosenRenderSurface::UpdateSurfaceConfig() {}
    void* RosenRenderSurface::GetNativeWindow() { return nullptr; }
    void RosenRenderSurface::SetRenderContext(OHOS::Ace::RefPtr<OHOS::Ace::NG::RenderContext> const&) {}
    void RosenRenderSurface::ConfigSurface(unsigned int, unsigned int) {}
    bool RosenRenderSurface::IsSurfaceValid() const { return false; }
    void RosenRenderSurface::CreateNativeWindow() {}
    void RosenRenderSurface::AdjustNativeWindowSize(unsigned int, unsigned int) {}
    std::string RosenRenderSurface::GetUniqueId() const { return ""; }
    void RosenRenderSurface::UpdateSurfaceSizeInUserData(unsigned int, unsigned int) {}
    void RosenRenderSurface::SetExtSurfaceBounds(int, int, int, int) {}
    void RosenRenderSurface::SetExtSurfaceCallback(
        OHOS::Ace::RefPtr<OHOS::Ace::NG::ExtSurfaceCallbackInterface> const&) {}
    void RosenRenderSurface::SetTransformHint(unsigned int) {}
    void RosenRenderSurface::DumpInfo() {}
    void RosenRenderSurface::SetSurfaceDefaultSize(int, int) {}
    void RosenRenderSurface::DrawBufferForXComponent(OHOS::Ace::Testing::TestingCanvas&, float, float, float, float) {}
    void RosenRenderSurface::ReleaseSurfaceBuffers() {}
    void RosenRenderSurface::RegisterSurface() const {}
    void RosenRenderSurface::UnregisterSurface() const {}
    void RosenRenderSurface::Connect() const {}
    void RosenRenderSurface::Disconnect() const {}
    void RosenRenderSurface::RegisterBufferCallback() {}
}
