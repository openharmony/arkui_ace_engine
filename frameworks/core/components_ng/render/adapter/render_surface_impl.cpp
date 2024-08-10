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
    auto errorCallback = [weak = WeakClaim(this), uiTaskExecutor](
        const std::string& errorId, const std::string& param) {
            uiTaskExecutor.PostTask([weak, errorId, param] {}, "ArkUIInitSurfaceError");
        };
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
    extSurface_->SetSurfaceDestroyed([weak = WeakClaim(this)]() {
        auto surfaceImpl = weak.Upgrade();
        CHECK_NULL_VOID(surfaceImpl);
        auto callback = surfaceImpl->extSurfaceCallback_;
        CHECK_NULL_VOID(callback);
        callback->ProcessSurfaceDestroy();
    });
}

void RenderSurfaceImpl::UpdateSurfaceConfig() {}

void* RenderSurfaceImpl::GetNativeWindow()
{
    return nativeWindow_;
}

void RenderSurfaceImpl::SetRenderContext(const RefPtr<RenderContext>& renderContext)
{
    renderContext_ = WeakClaim(RawPtr(renderContext));
}

void RenderSurfaceImpl::ConfigSurface(uint32_t surfaceWidth, uint32_t surfaceHeight)
{
    if (!extSurface_) {
        return;
    }
    isSetConfigSurface_ = true;

    double x = (lastRect_.Width() - surfaceWidth) / 2 + lastRect_.Left();
    double y = (lastRect_.Height() - surfaceHeight) / 2 + lastRect_.Top();

    extSurface_->SetBounds(surfaceId_, x, y, surfaceWidth, surfaceHeight);

    lastRect_.SetHeight(surfaceHeight);
    lastRect_.SetWidth(surfaceWidth);
}

bool RenderSurfaceImpl::IsSurfaceValid() const
{
    return extSurface_ != nullptr;
}

void RenderSurfaceImpl::CreateNativeWindow()
{
    if (extSurface_) {
        LOGI("RenderSurfaceImpl::CreateNativeWindow called");
        nativeWindow_ = extSurface_->AttachNativeWindow();
    }
}

void RenderSurfaceImpl::AdjustNativeWindowSize(uint32_t width, uint32_t height) {}

std::string RenderSurfaceImpl::GetUniqueId() const
{
    return std::to_string(surfaceId_);
}

bool RenderSurfaceImpl::SetExtSurfaceBoundsSync(int32_t left, int32_t top, int32_t width, int32_t height)
{
    if (extSurface_) {
        Rect rect;
        if (isSetConfigSurface_) {
            double x = (width - lastRect_.Width()) / 2 + left;
            double y = (height - lastRect_.Height()) / 2 + top;

            rect.SetLeft(x);
            rect.SetTop(y);
            rect.SetSize(lastRect_.GetSize());
        } else {
            rect.SetLeft(left);
            rect.SetTop(top);
            rect.SetWidth(width);
            rect.SetHeight(height);
        }
        extSurface_->SetBounds(surfaceId_, rect.Left(), rect.Top(), rect.Width(), rect.Height());
        lastRect_ = rect;
        return true;
    }
    return false;
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
        TaskExecutor::TaskType::PLATFORM, "ArkUISetExtSurfaceBounds");
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
        TaskExecutor::TaskType::PLATFORM, "ArkUISetIsFullScreen");
}

} // namespace OHOS::Ace::NG
