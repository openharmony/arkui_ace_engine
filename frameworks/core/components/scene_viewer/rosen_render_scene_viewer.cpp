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

#include "core/components/scene_viewer/rosen_render_scene_viewer.h"

#include "base/log/ace_trace.h"
#include "core/pipeline/base/rosen_render_context.h"
#include "graphics_manager.h"
#include "graphics_task.h"
#include "include/core/SkFont.h"
#include "include/core/SkMatrix.h"
#include "include/core/SkTextBlob.h"
#include "render_service_client/core/ui/rs_ui_director.h"
#include "render_service_client/core/ui/rs_ui_share_context.h"

namespace OHOS::Ace {

RosenRenderSceneViewer::RosenRenderSceneViewer(uint32_t key) : RenderSceneViewer(key)
{
    auto pipelineContext = GetContext().Upgrade();
    if (pipelineContext == nullptr) {
        LOGE("SceneViewer get pipeline context error");
        return;
    }

    const auto &rsUIDirector = pipelineContext->GetRSUIDirector();
    if (rsUIDirector == nullptr) {
        LOGE("SceneView RosenRender RSUIDirector null");
        return;
    }
}

void RosenRenderSceneViewer::PrepareTextureLayer(const OHOS::Render3D::TextureInfo& info)
{
    textureLayer_ = std::make_shared<OHOS::Render3D::TextureLayer>(info);
}

void RosenRenderSceneViewer::PaintTextureLayer(RenderContext& context, const Offset& offset)
{
    textureLayer_->UpdateRenderFinishFuture(renderFinished_);
    textureLayer_->SetOffset(offset.GetX(), offset.GetY());
    ACE_FUNCTION_TRACE();
    auto skCanvas = static_cast<RosenRenderContext*>(&context)->GetCanvas();
    if (skCanvas == nullptr) {
        LOGE("SceneView RosenRenderSceneView::PaintTexture skCanvas is null");
        return;
    }

    skCanvas->drawDrawable(textureLayer_.get());
    (void)(context);
}

EGLContext RosenRenderSceneViewer::GetRenderContext()
{
    auto ret = EGL_NO_CONTEXT;
    auto pipeline_context = GetContext().Upgrade();
    if (pipeline_context == nullptr) {
        LOGE("SceneView RosenRender piplineContext null");
        return ret;
    }

    ret = Rosen::RSUIShareContext::GetInstance().GetRsRenderContext();
    LOGD("RenderContext %p", ret);
    return ret;
}
} // namespace OHOS::Ace
