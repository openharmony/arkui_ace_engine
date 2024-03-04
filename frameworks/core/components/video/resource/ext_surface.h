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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_VIDEO_RESOURCE_EXT_SURFACE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_VIDEO_RESOURCE_EXT_SURFACE_H

#include <functional>
#include <utility>
#include "core/common/platform_res_register.h"
#include "core/components/video/resource/resource.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace {

class ACE_EXPORT ExtSurface : public Resource {
    DECLARE_ACE_TYPE(ExtSurface, Resource);
public:

    ExtSurface(const WeakPtr<PipelineBase>& context, ErrorCallback&& onError)
        : Resource("surface", context, std::move(onError)) {}
    ~ExtSurface() override;

    void Create(const std::function<void(int64_t)>& onCreate);
    void CreateExtSurface(const std::function<void(int64_t)>& onCreate);
    void SetBounds(int64_t surfaceId, int32_t left, int32_t top, int32_t width, int32_t height);
    void SetIsFullScreen(bool isFullScreen);
    void SetCreateCallback(std::function<void()>&& callback)
    {
        onSurfaceCreated_ = std::move(callback);
    }
    void SetSurfaceChanged(std::function<void(int32_t, int32_t)>&& callback)
    {
        onSurfaceChanged_ = std::move(callback);
    }

    void SetSurfaceDestroyed(std::function<void()>&& callback)
    {
        onSurfaceDestroyed_ = std::move(callback);
    }

    void* AttachNativeWindow();

private:
    void OnSurfaceCreated();
    void OnSurfaceChanged(int32_t width, int32_t height);
    void OnSurfaceDestroyed();

    std::function<void()> onSurfaceCreated_;
    std::function<void(int32_t, int32_t)> onSurfaceChanged_;
    std::function<void()> onSurfaceDestroyed_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_VIDEO_RESOURCE_EXT_SURFACE_H
