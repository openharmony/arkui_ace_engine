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
#include "core/components_ng/render/adapter/render_surface_impl.h"

#include <cstdint>

#include "base/memory/referenced.h"
#include "base/thread/task_executor.h"
#include "base/utils/system_properties.h"
#include "base/utils/utils.h"
#include "core/common/container.h"

namespace OHOS::Ace::NG {

RenderSurfaceImpl::~RenderSurfaceImpl()
{
    if (extSurface_) {
        extSurface_->Release();
    }
}

void RenderSurfaceImpl::InitSurface()
{
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    auto uiTaskExecutor = SingleTaskExecutor::Make(container->GetTaskExecutor(), TaskExecutor::TaskType::UI);
    auto errorCallback = [weak = WeakClaim(this), uiTaskExecutor](const std::string& errorId,
                             const std::string& param) { uiTaskExecutor.PostTask([weak, errorId, param] {}); };
    extSurface_ = AceType::MakeRefPtr<ExtSurface>(container->GetPipelineContext(), errorCallback);

    extSurface_->Create([weak = WeakClaim(this), errorCallback](int64_t id) mutable {
        LOGI("Surface create success id %{public}d", static_cast<int32_t>(id));
        auto surface = weak.Upgrade();
        CHECK_NULL_VOID(surface);
        surface->SetSurfaceId(id);
    });
    extSurface_->SetCreateCallback([weak = WeakClaim(this)]() {
        auto surfaceImpl = weak.Upgrade();
        CHECK_NULL_VOID(surfaceImpl);
        auto callback = surfaceImpl->extSurfaceCallback_;
        CHECK_NULL_VOID(callback);
        callback->ProcessSurfaceCreate();
    });
    extSurface_->SetSurfaceChanged([weak = WeakClaim(this)](int32_t width, int32_t height) {
        auto surfaceImpl = weak.Upgrade();
        CHECK_NULL_VOID(surfaceImpl);
        auto callback = surfaceImpl->extSurfaceCallback_;
        CHECK_NULL_VOID(callback);
        callback->ProcessSurfaceChange(width, height);
    });
}

void RenderSurfaceImpl::UpdateXComponentConfig() {}

void* RenderSurfaceImpl::GetNativeWindow()
{
    return nullptr;
}

void RenderSurfaceImpl::SetRenderContext(const RefPtr<RenderContext>& renderContext)
{
    renderContext_ = WeakClaim(RawPtr(renderContext));
}

void RenderSurfaceImpl::ConfigSurface(uint32_t surfaceWidth, uint32_t surfaceHeight) {}

bool RenderSurfaceImpl::IsSurfaceValid() const
{
    return extSurface_ != nullptr;
}

void RenderSurfaceImpl::CreateNativeWindow() {}

void RenderSurfaceImpl::AdjustNativeWindowSize(uint32_t width, uint32_t height) {}

std::string RenderSurfaceImpl::GetUniqueId() const
{
    return std::to_string(surfaceId_);
}

void RenderSurfaceImpl::SetExtSurfaceBounds(int32_t left, int32_t top, int32_t width, int32_t height)
{
    LOGI("RenderSurfaceImpl::SetExtSurfaceBounds (%{public}d, %{public}d) - (%{public}d x %{public}d)", left, top,
        width, height);
    auto taskExecutor = Container::CurrentTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(
        [surface = extSurface_, id = surfaceId_, left, top, width, height]() {
            if (surface) {
                surface->SetBounds(id, left, top, width, height);
            }
        },
        TaskExecutor::TaskType::PLATFORM);
}

void RenderSurfaceImpl::SetExtSurfaceCallback(const RefPtr<ExtSurfaceCallbackInterface>& extSurfaceCallback)
{
    extSurfaceCallback_ = extSurfaceCallback;
}

void RenderSurfaceImpl::SetIsFullScreen(bool isFullScreen)
{
    LOGI("SetIsFullScreen (%{public}d)", isFullScreen);
    auto taskExecutor = Container::CurrentTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(
        [surface = extSurface_, fullScreen = isFullScreen]() {
            if (surface) {
                surface->SetIsFullScreen(fullScreen);
            }
        },
        TaskExecutor::TaskType::PLATFORM);
}

} // namespace OHOS::Ace::NG
