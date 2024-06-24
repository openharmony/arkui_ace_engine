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

#if defined(ENABLE_ROSEN_BACKEND) && defined(OHOS_PLATFORM)
#include "core/components_ng/render/adapter/rosen_render_surface.h"
#endif
#ifdef RENDER_EXTRACT_SUPPORTED
#include "core/components_ng/render/adapter/render_texture_impl.h"
#endif
#include "core/components_ng/render/adapter/render_surface_impl.h"
#include "core/components_ng/render/render_surface.h"

namespace OHOS::Ace::NG {
// under the condition of supporting cross platform and texture rendering
#ifdef RENDER_EXTRACT_SUPPORTED
RefPtr<RenderSurface> RenderSurface::Create(const RenderSurfaceType& type)
{
    if (SystemProperties::GetRosenBackendEnabled()) {
        switch (type) {
            case RenderSurfaceType::SURFACE:
                return MakeRefPtr<RenderSurfaceImpl>();
            case RenderSurfaceType::TEXTURE:
                return MakeRefPtr<RenderTextureImpl>();
            default:
                break;
        }
    }
    return MakeRefPtr<RenderSurface>();
}
#else
// under the condition of supporting ohos platform
RefPtr<RenderSurface> RenderSurface::Create()
{
    if (SystemProperties::GetRosenBackendEnabled()) {
#if defined(OHOS_PLATFORM) && defined(ENABLE_ROSEN_BACKEND)
        return MakeRefPtr<RosenRenderSurface>();
#endif
    }
    return MakeRefPtr<RenderSurface>();
}
#endif
} // namespace OHOS::Ace::NG
