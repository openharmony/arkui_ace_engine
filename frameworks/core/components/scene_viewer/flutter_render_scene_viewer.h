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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SCENE_VIEWER_FLUTTER_RENDER_SCENE_VIEWER
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SCENE_VIEWER_FLUTTER_RENDER_SCENE_VIEWER

#include "core/components/scene_viewer/render_scene_viewer.h"
#include "core/pipeline/base/render_node.h"
#include "core/pipeline/layers/offset_layer.h"
#include "core/pipeline/layers/picture_layer.h"
#include "core/pipeline/layers/texture_layer.h"
#include "foundation/graphic/graphic_3d/3d_widget_adapter/include/android/skia_texture.h"

namespace OHOS::Ace {

class FlutterRenderSceneViewer : public RenderSceneViewer {
    DECLARE_ACE_TYPE(FlutterRenderSceneViewer, RenderSceneViewer);

public:
    explicit FlutterRenderSceneViewer(uint32_t key);
    ~FlutterRenderSceneViewer() override = default;
    void PrepareTextureLayer(const OHOS::Render3D::TextureInfo& info) override;
    void PaintTextureLayer(RenderContext& context, const Offset& offset) override;
    RenderLayer GetRenderLayer() override;

private:
    EGLContext GetRenderContext() override;
    RefPtr<OHOS::Render3D::TextureLayer> textureLayer_;
    RefPtr<Flutter::OffsetLayer> offsetLayer_;
    std::shared_ptr<OHOS::Render3D::SkiaTexture> texture_;
    int32_t layoutWidth_ = 0;
    int32_t layoutHeight_ = 0;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SCENE_VIEWER_FLUTTER_RENDER_SCENE_VIEWER
