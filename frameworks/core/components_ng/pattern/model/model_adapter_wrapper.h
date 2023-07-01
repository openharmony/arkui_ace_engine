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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MODEL_MODEL_ADAPTER_WRAPPER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MODEL_MODEL_ADAPTER_WRAPPER_H

#include <EGL/egl.h>

#include "base/geometry/animatable_float.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/geometry/quaternion.h"
#include "base/geometry/vec3.h"
#include "core/components_ng/pattern/model/model_layout_property.h"
#include "core/components_ng/pattern/model/model_paint_property.h"
#include "core/components_ng/pattern/model/model_touch_handler.h"
#include "foundation/graphic/graphic_3d/3d_widget_adapter/include/data_type/scene_viewer_touch_event.h"
#include "foundation/graphic/graphic_3d/3d_widget_adapter/include/ohos/texture_layer.h"
#include "foundation/graphic/graphic_3d/3d_widget_adapter/include/scene_viewer_adapter.h"

namespace OHOS::Ace::NG {
#define MAX_INVALID std::numeric_limits<double>::max()
struct SceneViewerAdapterProperties {
    // Scene properties
    std::string gltfSrc_ = "";
    std::string backgroundSrc_ = "";
    OHOS::Render3D::SceneViewerBackgroundType bgType_ = OHOS::Render3D::SceneViewerBackgroundType::CUBE_MAP;

    // FOV
    float zNear_ = 0.5f;
    float zFar_ = 50.0f;
    float fov_ = 60.0f;

    // Camera properties.
    OHOS::Render3D::Position cameraPosition_;
    Vec3 cameraLookAt_ = Vec3(0.0f, 0.0f, 0.0f);
    Vec3 cameraUp_ = Vec3(0.0f, 1.0f, 0.0f);

    // Invalid by default. Either camera of rotation or lookat is used at the end.
    Quaternion cameraRotation_ = Quaternion(MAX_INVALID,
        MAX_INVALID, MAX_INVALID, MAX_INVALID);

    // Lights
    std::vector<RefPtr<OHOS::Render3D::SVLight>> lights_;
    std::vector<RefPtr<OHOS::Render3D::GLTFAnimation>> animations_;
    std::vector<RefPtr<OHOS::Render3D::SVGeometry>> geometries_;
};

class ModelAdapterWrapper : public virtual AceType {
    DECLARE_ACE_TYPE(ModelAdapterWrapper, AceType)
public:
    using PaintFinishCallback = std::function<void()>;

    ModelAdapterWrapper(uint32_t key);
    ~ModelAdapterWrapper() = default;

    void OnMeasureContent(const RefPtr<ModelLayoutProperty>& modelLayoutProperty, SizeF size);
    void OnPaint(const RefPtr<ModelPaintProperty>& modelPaintProperty);
    void OnPaintFinish();
    void SetPaintFinishCallback(PaintFinishCallback callback);
    bool IsInitialized();
    bool IsReady();
    bool NeedsRepaint();
    SkDrawable* GetDrawable(OffsetF offset);
    std::shared_ptr<OHOS::Render3D::TextureLayer> GetTextureLayer(OffsetF offset);
    bool HandleTouchEvent(const TouchEventInfo& info);

private:
    uint32_t GetKey();
    void Initialize();
    void CreateTextureLayer(const EGLContext& eglContext);
    void UpdateTextureLayer();
    void CreateSceneViewerAdapter(const EGLContext& eglContext);
    void UpdateSceneViewerAdapter(const SceneViewerAdapterProperties& properties);
    SceneViewerAdapterProperties ExtractLayoutProperties(const RefPtr<ModelLayoutProperty>& modelLayoutProperty);
    SceneViewerAdapterProperties ExtractPaintProperties(const RefPtr<ModelPaintProperty>& modelPaintProperty);
    void UnloadScene();
    EGLContext GetRenderContext();
    void DrawFrame();
    void UpdateCamera(const SceneViewerAdapterProperties& properties);
    void UpdateLights(const SceneViewerAdapterProperties& properties);
    void UpdateGLTFAnimations(const SceneViewerAdapterProperties& properties);
    void UpdateGeometries(const SceneViewerAdapterProperties& properties);
    void HandleCameraMove(const OHOS::Render3D::SceneViewerTouchEvent& event);

private:
    uint32_t key_ = -1;
    SizeF size_ { 0.0f, 0.0f };
    PaintFinishCallback callback_ = nullptr;
    bool needsRepaint_ = false;
    bool sceneIsSetUp_ = false;

    std::shared_ptr<OHOS::Render3D::SceneViewerAdapter> sceneViewerAdapter_;
    std::shared_ptr<OHOS::Render3D::TextureInfo> textureInfo_;
    std::shared_ptr<OHOS::Render3D::TextureLayer> textureLayer_;
    RefPtr<ModelTouchHandler> touchHandler_;
    EGLContext eglContext_ = EGL_NO_CONTEXT;
    ACE_DISALLOW_COPY_AND_MOVE(ModelAdapterWrapper);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MODEL_MODEL_ADAPTER_WRAPPER_H
