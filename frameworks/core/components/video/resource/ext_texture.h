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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_VIDEO_RESOURCE_EXT_TEXTURE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_VIDEO_RESOURCE_EXT_TEXTURE_H

#include "core/common/platform_res_register.h"
#include "core/components/video/resource/resource.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace {
class ACE_EXPORT ExtTexture : public Resource {
    DECLARE_ACE_TYPE(ExtTexture, Resource);
public:
    ExtTexture(const WeakPtr<PipelineBase>& context, ErrorCallback&& onError)
        : Resource("texture", context, std::move(onError)) {}
    ~ExtTexture() override;

    void Create(const std::function<void(int64_t)>& onCreate);
    void CreateTexture(const std::function<void(int64_t)>& onCreate);
    void SetSize(int64_t textureId, int32_t textureWidth, int32_t textureHeight);
    void SetTextureFreshCallback(std::function<void(int32_t, int64_t)>&& callback)
    {
        onTextureRefresh_ = std::move(callback);
    }
    void SetCreateCallback(std::function<void()>&& callback)
    {
        onSurfaceCreated_ = std::move(callback);
    }
    void SetSurfaceChanged(std::function<void(int32_t, int32_t)>&& callback)
    {
        onSurfaceChanged_ = std::move(callback);
    }

    void AttachToGLContext(int64_t textureId, bool isAttach);

    void UpdateTextureImage(std::vector<float>& matrix);

private:
    void OnRefresh(const std::string& param);
    void OnSurfaceCreated();
    void OnSurfaceChanged(int32_t width, int32_t height);

    int64_t textureId_ = INVALID_ID;
    int64_t instanceId_ = INVALID_ID;
    
    std::function<void(int32_t, int64_t)> onTextureRefresh_;
    std::function<void()> onSurfaceCreated_;
    std::function<void(int32_t, int32_t)> onSurfaceChanged_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_VIDEO_RESOURCE_EXT_TEXTURE_H