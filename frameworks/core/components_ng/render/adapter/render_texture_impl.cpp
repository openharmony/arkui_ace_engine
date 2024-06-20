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

#include "core/components_ng/render/adapter/render_texture_impl.h"

#include "base/memory/referenced.h"
#include "base/thread/task_executor.h"
#include "base/utils/system_properties.h"
#include "base/utils/utils.h"
#include "core/common/container.h"

namespace OHOS::Ace::NG {
RenderTextureImpl::~RenderTextureImpl()
{
    if (extTexture_) {
        extTexture_->Release();
    }
}

void RenderTextureImpl::InitSurface()
{
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    auto uiTaskExecutor = SingleTaskExecutor::Make(container->GetTaskExecutor(), TaskExecutor::TaskType::UI);
    auto errorCallback = [weak = WeakClaim(this), uiTaskExecutor](
        const std::string& errorId, const std::string& param) {
            uiTaskExecutor.PostTask([weak, errorId, param] {}, "ArkUIInitSurfaceTextureError");
        };
    extTexture_ = AceType::MakeRefPtr<ExtTexture>(container->GetPipelineContext(), errorCallback);

    extTexture_->Create([weak = WeakClaim(this), errorCallback](int64_t id) mutable {
        LOGI("Surface create success id %{public}d", static_cast<int32_t>(id));
        auto surface = weak.Upgrade();
        CHECK_NULL_VOID(surface);
        surface->SetTextureId(id);
    });
    extTexture_->SetTextureFreshCallback([weak = WeakClaim(this)](int32_t instanceId, int64_t textureId) {
        auto surfaceImpl = weak.Upgrade();
        CHECK_NULL_VOID(surfaceImpl);
        auto callback = surfaceImpl->extSurfaceCallback_;
        CHECK_NULL_VOID(callback);
        callback->ProcessTextureRefresh(instanceId, textureId);
    });
    extTexture_->SetCreateCallback([weak = WeakClaim(this)]() {
        auto surfaceImpl = weak.Upgrade();
        CHECK_NULL_VOID(surfaceImpl);
        auto callback = surfaceImpl->extSurfaceCallback_;
        CHECK_NULL_VOID(callback);
        callback->ProcessSurfaceCreate();
    });
    extTexture_->SetSurfaceChanged([weak = WeakClaim(this)](int32_t width, int32_t height) {
        auto surfaceImpl = weak.Upgrade();
        CHECK_NULL_VOID(surfaceImpl);
        auto callback = surfaceImpl->extSurfaceCallback_;
        CHECK_NULL_VOID(callback);
        callback->ProcessSurfaceChange(width, height);
    });
}

void RenderTextureImpl::UpdateSurfaceConfig() {}

void* RenderTextureImpl::GetNativeWindow()
{
    return nullptr;
}

void RenderTextureImpl::SetRenderContext(const RefPtr<RenderContext>& renderContext)
{
    renderContext_ = WeakClaim(RawPtr(renderContext));
}

void RenderTextureImpl::ConfigSurface(uint32_t surfaceWidth, uint32_t surfaceHeight) {}

bool RenderTextureImpl::IsSurfaceValid() const
{
    return extTexture_ != nullptr;
}

void RenderTextureImpl::CreateNativeWindow() {}

void RenderTextureImpl::AdjustNativeWindowSize(uint32_t width, uint32_t height) {}

std::string RenderTextureImpl::GetUniqueId() const
{
    return std::to_string(textureId_);
}

bool RenderTextureImpl::SetExtSurfaceBoundsSync(int32_t left, int32_t top, int32_t width, int32_t height)
{
    return false;
}

void RenderTextureImpl::SetExtSurfaceBounds(int32_t left, int32_t top, int32_t width, int32_t height)
{
    LOGI("RenderTextureImpl::SetExtSurfaceBounds (%{public}d, %{public}d) - (%{public}d x %{public}d)", left, top,
        width, height);
    auto taskExecutor = Container::CurrentTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostTask(
        [surface = extTexture_, id = textureId_, left, top, width, height]() {
            if (surface) {
                surface->SetSize(id, width, height);
            }
        },
        TaskExecutor::TaskType::PLATFORM, "ArkUISetExtTextureSize");
}

void RenderTextureImpl::SetExtSurfaceCallback(const RefPtr<ExtSurfaceCallbackInterface>& extSurfaceCallback)
{
    extSurfaceCallback_ = extSurfaceCallback;
}

void RenderTextureImpl::AttachToGLContext(int64_t textureId, bool isAttach)
{
    if (extTexture_) {
        extTexture_->AttachToGLContext(textureId, isAttach);
    }
}

void RenderTextureImpl::UpdateTextureImage(std::vector<float>& matrix)
{
    if (extTexture_) {
        extTexture_->UpdateTextureImage(matrix);
    }
}
} // namespace OHOS::Ace::NG