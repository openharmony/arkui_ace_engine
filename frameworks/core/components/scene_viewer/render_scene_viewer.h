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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SCENE_VIEWER_RENDER_SCENE_VIEWER
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SCENE_VIEWER_RENDER_SCENE_VIEWER

#include <EGL/egl.h>

#include "base/geometry/animatable_float.h"
#include "base/geometry/quaternion.h"
#include "base/geometry/vec3.h"
#include "core/components/scene_viewer/scene_viewer_component.h"
#include "core/components/scene_viewer/scene_viewer_touch_handler.h"
#include "core/pipeline/base/render_node.h"
#include "foundation/graphic/graphic_3d/3d_widget_adapter/include/custom/custom_render_descriptor.h"
#include "foundation/graphic/graphic_3d/3d_widget_adapter/include/data_type/constants.h"
#include "foundation/graphic/graphic_3d/3d_widget_adapter/include/data_type/geometry/geometry.h"
#include "foundation/graphic/graphic_3d/3d_widget_adapter/include/data_type/gltf_animation.h"
#include "foundation/graphic/graphic_3d/3d_widget_adapter/include/data_type/position.h"
#include "foundation/graphic/graphic_3d/3d_widget_adapter/include/scene_viewer_adapter.h"
#include "graphics_manager.h"
#include "texture_layer.h"

namespace OHOS::Ace {

class RenderSceneViewer : public RenderNode {
    DECLARE_ACE_TYPE(RenderSceneViewer, RenderNode);

public:
    explicit RenderSceneViewer(uint32_t key);
    ~RenderSceneViewer() override;
    static RefPtr<RenderNode> Create(uint32_t key);

    void Update(const RefPtr<Component>& component) override;
    void PerformLayout() override;
    void Paint(RenderContext& context, const Offset& offset) override;
    void OnPaintFinish() override;

    void OnAttachContext() override
    {
        cameraPosition_.SetContextAndCallbacks(
            context_, std::bind(&RenderSceneViewer::PerformCameraUpdate, this));
        // Lights animation callbacks are added when lights are added.

        auto pipelineContext = GetContext().Upgrade();
        if (!pipelineContext) {
            LOGE("ACE-3D RenderSceneViewer::OnAttachContext() GetContext failed.");
            return;
        }

        surfaceChangeCallbackId_ = pipelineContext->RegisterSurfaceChangedCallback(
            [&](int32_t width, int32_t height, int32_t oldWidth, int32_t oldHeight, WindowSizeChangeReason type) {
            OnSurfaceChanged();
        });

#if MULTI_ECS_UPDATE_AT_ONCE
        OHOS::Render3D::GraphicsManager::GetInstance().AttachContext(context_);
#endif
    }

protected:
    RenderSceneViewer();
    virtual void PaintTextureLayer(RenderContext& context, const Offset& offset) = 0;
    virtual void PrepareTextureLayer(const OHOS::Render3D::TextureInfo& info) = 0;
    virtual OHOS::Render3D::TextureInfo CreateRenderTarget(uint32_t width, uint32_t height) = 0;
    virtual void ClearRenderObject() override;
    virtual EGLContext GetRenderContext() = 0;
    void OnTouchTestHit(
        const Offset& coordinateOffset, const TouchRestrict& touchRestrict, TouchTestResult& result) override;
    void Initialize();
    void HandleEvent(const OHOS::Render3D::SceneViewerTouchEvent& event);
    void RenderWithContext(RenderContext& context, const Offset& offset) override;
    uint32_t GetKey();
    Size GetSize();

    std::string glTFSrc_;
    std::string backgroundSrc_;
    uint32_t textureId_;
    bool animating_ = false;
    std::vector<RefPtr<OHOS::Render3D::SVGeometry>> shapes_;
    std::vector<RefPtr<OHOS::Render3D::SVCustomRenderDescriptor>> customRenders_;
    bool handlesNotReady_ = false;

    // Camera properties.
    float zNear_ = 0.0f;
    float zFar_ = 0.0f;
    float fovDegrees_ = 0.0f;
    // Camera position and rotation.
    OHOS::Render3D::Position cameraPosition_;
    Vec3 cameraLookAtVec_ { 0.0f, 0.0f, 0.0f };
    Vec3 cameraUpVec_ { 0.0f, 1.0f, 0.0f };
    Quaternion cameraRotation_ { 0.0f, 0.0f, 0.0f, 1.0f };
    // Lights.
    std::vector<RefPtr<OHOS::Render3D::SVLight>> lights_;

    OHOS::Render3D::SceneViewerAdapter sceneViewerAdapter_;
    OHOS::Render3D::TextureInfo textureInfo_;
    std::shared_future<void> renderFinished_;

 private:
    void PerformClick();
    void PerformCameraUpdate();
    void PerformLightUpdate();
    void UpdateCameraOnly();
    void UpdateLightOnly();
    void PassGeometries(const std::vector<RefPtr<OHOS::Render3D::SVGeometry>>& geometries);
    void UpdateGLTFAnimations(const std::vector<RefPtr<OHOS::Render3D::GLTFAnimation>>& gltfAnimations);
    bool IsCameraPropertyChanged(const RefPtr<SceneViewerComponent>& svComponent);
    void HandleLightsUpdate(const RefPtr<SceneViewerComponent>& svComponent);
    bool IsLightPropertyChanged(const RefPtr<SceneViewerComponent>& svComponent);
    void PassCustomRenders(const std::vector<RefPtr<OHOS::Render3D::SVCustomRenderDescriptor>>& customRenders);
    void OnSurfaceChanged();

private:
    RefPtr<SceneViewerTouchHandler> touchHandler_;
    Size sceneSize_;
    uint32_t key_;
    bool isClicked_ = false;
    int32_t touchCount_ = 0;
    bool isHandleCameraMove_ = false;
    std::function<void()> onClick_;
    bool needsSceneSetup_ = true;
    bool isTransparent_ = false;
    EGLContext eglContext_ = EGL_NO_CONTEXT;
    bool inited_ = false;
    int surfaceChangeCallbackId_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SCENE_VIEWER_RENDER_SCENE_VIEWER
