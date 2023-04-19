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

#include "core/components/scene_viewer/flutter_render_scene_viewer.h"

#include "base/log/ace_trace.h"
#include "graphics_manager.h"
#include "graphics_task.h"

namespace OHOS::Ace {

EGLContext FlutterRenderSceneViewer::GetRenderContext()
{
    auto pipelineContext = GetContext().Upgrade();
    EGLContext eglContext = EGL_NO_CONTEXT;
    pipelineContext->GetTaskExecutor()->PostSyncTask([&eglContext, this] {
        eglContext = eglGetCurrentContext();
    }, TaskExecutor::TaskType::GPU);
    return eglContext;
}

FlutterRenderSceneViewer::FlutterRenderSceneViewer(uint32_t key) : RenderSceneViewer(key)
{
}

RenderLayer FlutterRenderSceneViewer::GetRenderLayer()
{
    if (!offsetLayer_) {
        offsetLayer_ = AceType::MakeRefPtr<Flutter::OffsetLayer>();
    }
    return AceType::RawPtr(offsetLayer_);
}

void FlutterRenderSceneViewer::PrepareTextureLayer(const OHOS::Render3D::TextureInfo& info)
{
    texture_ = std::make_shared<OHOS::Render3D::SkiaTexture>(info.textureId_);
    OHOS::Render3D::GraphicsManager::GetInstance().GetTextureRegistry()->RegisterTexture(
        texture_);

    auto layoutWidth = static_cast<int32_t>(GetLayoutSize().Width());
    auto layoutHeight = static_cast<int32_t>(GetLayoutSize().Height());
    textureLayer_ = AceType::MakeRefPtr<OHOS::Render3D::TextureLayer>(textureInfo_, texture_,
        layoutWidth, layoutHeight);
}

void FlutterRenderSceneViewer::PaintTextureLayer(RenderContext& context, const Offset& offset)
{
    auto layoutWidth = static_cast<int32_t>(GetLayoutSize().Width());
    auto layoutHeight = static_cast<int32_t>(GetLayoutSize().Height());
    if (layoutWidth_ != layoutWidth || layoutHeight_ != layoutHeight) {
        textureLayer_ = AceType::MakeRefPtr<OHOS::Render3D::TextureLayer>(textureInfo_, texture_,
            layoutWidth, layoutHeight);
        layoutWidth_ = layoutWidth;
        layoutHeight_ = layoutHeight;
    }

    textureLayer_->UpdateRenderFinishFuture(renderFinished_);

    if (offsetLayer_ != nullptr) {
        offsetLayer_->AddChildren(textureLayer_);
    }
}

} // namespace OHOS::Ace
