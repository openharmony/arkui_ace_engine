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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SCENE_VIEWER_ROSEN_RENDER_SCENE_VIEWER
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SCENE_VIEWER_ROSEN_RENDER_SCENE_VIEWER

#include "core/components/scene_viewer/render_scene_viewer.h"
#include "core/pipeline/base/render_node.h"

namespace OHOS::Ace {

class RosenRenderSceneViewer : public RenderSceneViewer {
    DECLARE_ACE_TYPE(RosenRenderSceneViewer, RenderSceneViewer);

public:
    explicit RosenRenderSceneViewer(uint32_t key);
    ~RosenRenderSceneViewer() override = default;
    void PrepareTextureLayer(const OHOS::Render3D::TextureInfo& info) override;
    OHOS::Render3D::TextureInfo CreateRenderTarget(uint32_t width, uint32_t height) override;
    EGLContext GetRenderContext() override;
    void PaintTextureLayer(RenderContext& context, const Offset& offset) override;

private:
    std::shared_ptr<Render3D::TextureLayer> textureLayer_;
    uint32_t width_ = 0;
    uint32_t height_ = 0;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SCENE_VIEWER_ROSEN_RENDER_SCENE_VIEWER
