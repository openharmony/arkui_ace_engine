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
#include "core/components_ng/render/adapter/rosen_render_surface.h"

#include "foundation/graphic/graphic_2d/interfaces/inner_api/surface/surface_utils.h"
#include "render_service_client/core/ui/rs_surface_node.h"

#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components_ng/render/adapter/rosen_render_context.h"

namespace OHOS::Ace::NG {
namespace {
const char* const SURFACE_STRIDE_ALIGNMENT = "8";
constexpr int32_t SURFACE_QUEUE_SIZE = 5;
} // namespace
RosenRenderSurface::~RosenRenderSurface()
{
    if (producerSurface_) {
        auto* surfaceUtils = SurfaceUtils::GetInstance();
        auto ret = surfaceUtils->Remove(producerSurface_->GetUniqueId());
        if (ret != SurfaceError::SURFACE_ERROR_OK) {
            LOGE("remove surface error: %{public}d", ret);
        }
    }
}

void RosenRenderSurface::InitSurface()
{
    auto renderContext = renderContext_.Upgrade();
    CHECK_NULL_VOID(renderContext);

    auto rosenRenderContext = AceType::DynamicCast<NG::RosenRenderContext>(renderContext);
    auto surfaceNode =
        OHOS::Rosen::RSBaseNode::ReinterpretCast<OHOS::Rosen::RSSurfaceNode>(rosenRenderContext->GetRSNode());
    if (surfaceNode) {
        producerSurface_ = surfaceNode->GetSurface();
    }
}

void RosenRenderSurface::UpdateXComponentConfig()
{
    CHECK_NULL_VOID(producerSurface_);

    auto* surfaceUtils = SurfaceUtils::GetInstance();
    auto ret = surfaceUtils->Add(producerSurface_->GetUniqueId(), producerSurface_);
    if (ret != SurfaceError::SURFACE_ERROR_OK) {
        LOGE("add surface error: %{public}d", ret);
    }

    producerSurface_->SetQueueSize(SURFACE_QUEUE_SIZE);
    producerSurface_->SetUserData("SURFACE_STRIDE_ALIGNMENT", SURFACE_STRIDE_ALIGNMENT);
    producerSurface_->SetUserData("SURFACE_FORMAT", std::to_string(PIXEL_FMT_RGBA_8888));
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
    if (producerSurface_) {
        producerSurface_->SetUserData("SURFACE_WIDTH", std::to_string(surfaceWidth));
        producerSurface_->SetUserData("SURFACE_HEIGHT", std::to_string(surfaceHeight));
    }
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
    if (nativeWindow_) {
        NativeWindowHandleOpt(nativeWindow_, SET_BUFFER_GEOMETRY, width, height);
    } else {
        LOGE("nativeWindow is null");
    }
}

std::string RosenRenderSurface::GetUniqueId() const
{
    return std::to_string(producerSurface_->GetUniqueId());
}

} // namespace OHOS::Ace::NG