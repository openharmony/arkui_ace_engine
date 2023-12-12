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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SCENE_VIEWER_SCENE_VIEWER_COMPONENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SCENE_VIEWER_SCENE_VIEWER_COMPONENT_H

#include <string>

#include "base/geometry/animatable_float.h"
#include "base/geometry/quaternion.h"
#include "base/geometry/vec3.h"
#include "base/utils/utils.h"
#include "core/pipeline/base/element.h"
#include "core/pipeline/base/measurable.h"
#include "foundation/graphic/graphic_3d/3d_widget_adapter/include/custom/custom_render_descriptor.h"
#include "foundation/graphic/graphic_3d/3d_widget_adapter/include/data_type/constants.h"
#include "foundation/graphic/graphic_3d/3d_widget_adapter/include/data_type/geometry/geometry.h"
#include "foundation/graphic/graphic_3d/3d_widget_adapter/include/data_type/gltf_animation.h"
#include "foundation/graphic/graphic_3d/3d_widget_adapter/include/data_type/light.h"
#include "foundation/graphic/graphic_3d/3d_widget_adapter/include/data_type/position.h"

namespace OHOS::Ace {

constexpr double INVALID_DOUBLE = std::numeric_limits<double>::max();

// A component can show glTF model.
class SceneViewerComponent : public RenderComponent, public Measurable {
    DECLARE_ACE_TYPE(SceneViewerComponent, RenderComponent, Measurable);

public:
    SceneViewerComponent() = default;
    ~SceneViewerComponent() override = default;
    RefPtr<Element> CreateElement() override;
    RefPtr<RenderNode> CreateRenderNode() override;

    SceneViewerComponent(const std::string& src)
    {
        gltfSrc_ = src;
    }

    const std::string& GetGltfSrc() const
    {
        return gltfSrc_;
    }

    void SetGltfSrc(const std::string& src)
    {
        gltfSrc_ = src;
    }

    const EventMarker& GetClickedEventId() const
    {
        return clickEventId_;
    }

    void SetClickedEventId(const EventMarker& onClickId)
    {
        clickEventId_ = onClickId;
    }

    void SetHandleCameraMove(bool enabled)
    {
        isHandleCameraMove_ = enabled;
    }

    bool IsHandleCameraMove() const
    {
        return isHandleCameraMove_;
    }

    void SetCameraRotation(Quaternion quat)
    {
        cameraRotation_ = quat;
    }

    const Quaternion GetCameraRotation() const
    {
        return cameraRotation_;
    }

    void SetCameraPosition(AnimatableFloat x, AnimatableFloat y, AnimatableFloat z,
        AnimatableFloat distance, bool isAngular)
    {
        cameraPosition_.Set(x, y, z, distance, isAngular);
    }

    const OHOS::Render3D::Position& GetCameraPosition()
    {
        return cameraPosition_;
    }

    const Vec3 GetCameraPositionVec()
    {
        return cameraPosition_.GetVec();
    }

    const AnimatableFloat GetCameraPosDistance() const
    {
        return cameraPosition_.GetDistance();
    }

    bool GetIsCameraPosInAngles()
    {
        return cameraPosition_.GetIsAngular();
    }

    void SetCameraLookAt(Vec3 lookAtVec)
    {
        cameraLookAtVec_ = lookAtVec;
    }

    const Vec3 GetCameraLookAtVec() const
    {
        return cameraLookAtVec_;
    }

    void SetCameraUp(Vec3 upVec)
    {
        cameraUpVec_ = upVec;
    }

    const Vec3 GetCameraUpVec() const
    {
        return cameraUpVec_;
    }

    void SetCameraFrustum(float zNear, float zFar, float fovDegrees)
    {
        zNear_ = zNear;
        zFar_ = zFar;
        fovDegrees_ = fovDegrees;
    }

    float GetZNear() const
    {
        return zNear_;
    }

    float GetZFar() const
    {
        return zFar_;
    }

    float GetFovDegrees() const
    {
        return fovDegrees_;
    }

    bool IsTransparent() const
    {
        return isTransparent_;
    }

    void SetTransparent(bool enabled)
    {
        isTransparent_ = enabled;
    }

    const std::string& GetBackgroundSrc() const
    {
        return backgroundSrc_;
    }

    void SetBackgroundSrc(const std::string& src)
    {
        backgroundSrc_ = src;
    }

    void AddGeometry(const RefPtr<OHOS::Render3D::SVGeometry>& shape)
    {
        shapes_.push_back(shape);
    }

    std::vector<RefPtr<OHOS::Render3D::SVGeometry>>& GetGeometries()
    {
        return shapes_;
    }

    void AddGLTFAnimation(const RefPtr<OHOS::Render3D::GLTFAnimation>& animation)
    {
        gltfAnimations_.push_back(animation);
    }

    std::vector<RefPtr<OHOS::Render3D::GLTFAnimation>>& GetGLTFAnimations()
    {
        return gltfAnimations_;
    }

    void AddLight(const RefPtr<OHOS::Render3D::SVLight>& light)
    {
        lights_.push_back(light);
    }

    std::vector<RefPtr<OHOS::Render3D::SVLight>>& GetLights()
    {
        return lights_;
    }

    void AddCustomRender(const RefPtr<OHOS::Render3D::SVCustomRenderDescriptor>& customRender)
    {
        customRenders_.push_back(customRender);
    }

    std::vector<RefPtr<OHOS::Render3D::SVCustomRenderDescriptor>>& GetCustomRenders()
    {
        return customRenders_;
    }

private:
    std::string gltfSrc_;
    std::string backgroundSrc_;
    EventMarker clickEventId_;
    // Handle camera move by default.
    bool isHandleCameraMove_ = true;
    bool isTransparent_ = false;

    // Camera properties.
    float zNear_ = 0.5f;
    float zFar_ = 50.0f;
    float fovDegrees_ = 60.0f;
    OHOS::Render3D::Position cameraPosition_;
    Vec3 cameraLookAtVec_ { 0.0f, 0.0f, 0.0f };
    Vec3 cameraUpVec_ { 0.0f, 1.0f, 0.0f };

    // Invalid by default. Either camera of rotation or lookat is used at the end.
    Quaternion cameraRotation_ { INVALID_DOUBLE, INVALID_DOUBLE, INVALID_DOUBLE, INVALID_DOUBLE };

    // Light objects.
    std::vector<RefPtr<OHOS::Render3D::SVLight>> lights_;

    // Geometry
    std::vector<RefPtr<OHOS::Render3D::SVGeometry>> shapes_;

    // GLTF Animations.
    std::vector<RefPtr<OHOS::Render3D::GLTFAnimation>> gltfAnimations_;

    // Shader
    std::vector<RefPtr<OHOS::Render3D::SVCustomRenderDescriptor>> customRenders_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_SCENE_VIEWER_SCENE_VIEWER_COMPONENT_H
