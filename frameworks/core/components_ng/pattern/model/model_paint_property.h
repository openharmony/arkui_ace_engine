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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MODEL_MODEL_PAINT_PROPERTY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MODEL_MODEL_PAINT_PROPERTY_H

#include "custom/custom_render_descriptor.h"
#include "custom/shader_input_buffer.h"
#include "data_type/geometry/geometry.h"
#include "data_type/gltf_animation.h"

#include "base/geometry/animatable_float.h"
#include "base/geometry/vec3.h"
#include "core/components_ng/pattern/model/model_light.h"
#include "core/components_ng/pattern/model/model_position.h"
#include "core/components_ng/pattern/model/model_property.h"
#include "core/components_ng/render/paint_property.h"

namespace OHOS::Ace::NG {

class ModelPaintProperty : public PaintProperty {
    DECLARE_ACE_TYPE(ModelPaintProperty, PaintProperty)

public:
    ModelPaintProperty()
    {
        // Initialize model lights to empty vector;
        propModelLights_ = std::vector<RefPtr<ModelLight>> {};
        propModelAnimations_ = std::vector<std::shared_ptr<Render3D::GLTFAnimation>> {};
        propModelGeometries_ = std::vector<std::shared_ptr<Render3D::Geometry>> {};
        propModelImageTexturePaths_ = std::vector<std::string> {};
        propShaderPath_ = std::string {};
        propModelShaderInputBuffer_ = nullptr;
        propModelCustomRender_ = nullptr;
        propModelSource_ = std::string {};
        propModelBackground_ = std::string{};
    };

    ~ModelPaintProperty() override = default;

    RefPtr<PaintProperty> Clone() const override
    {
        auto paintProperty = MakeRefPtr<ModelPaintProperty>();
        paintProperty->UpdatePaintProperty(this);
        paintProperty->propCameraDistance_ = CloneCameraDistance();
        paintProperty->propCameraIsAngular_ = CloneCameraIsAngular();
        paintProperty->propCameraRotation_ = CloneCameraRotation();
        paintProperty->propCameraLookAt_ = CloneCameraLookAt();
        paintProperty->propCameraUp_ = CloneCameraUp();
        paintProperty->propCameraZNear_ = CloneCameraZNear();
        paintProperty->propCameraZFar_ = CloneCameraZFar();
        paintProperty->propCameraFOV_ = CloneCameraFOV();
        paintProperty->propModelLights_ = CloneModelLights();
        paintProperty->propModelAnimations_ = CloneModelAnimations();
        paintProperty->propModelGeometries_ = CloneModelGeometries();
        paintProperty->propModelCustomRender_ = CloneModelCustomRender();
        paintProperty->propShaderPath_ = CloneShaderPath();
        paintProperty->propModelImageTexturePaths_ = CloneModelImageTexturePaths();
        paintProperty->propModelShaderInputBuffer_ = CloneModelShaderInputBuffer();
        paintProperty->propModelSource_ = CloneModelSource();
        paintProperty->propModelBackground_ = CloneModelBackground();
        paintProperty->propModelCameraMove_ = CloneModelCameraMove();
        paintProperty->propRenderHeight_ = CloneRenderHeight();
        paintProperty->propRenderWidth_ = CloneRenderWidth();
        paintProperty->propRenderFrameRate_ = CloneRenderFrameRate();

        paintProperty->needsCameraSetup_ = CloneNeedsCameraSetup();
        paintProperty->needsLightsSetup_ = CloneNeedsLightsSetup();
        paintProperty->needsAnimationsSetup_ = CloneNeedsAnimationsSetup();
        paintProperty->needsGeometriesSetup_ = CloneNeedsGeometriesSetup();
        paintProperty->needsCustomRenderSetup_ = CloneNeedsCustomRenderSetup();
        paintProperty->needsShaderPathSetup_ = CloneNeedsShaderPathSetup();
        paintProperty->needsImageTexturePathsSetup_ = CloneNeedsImageTexturePathsSetup();
        paintProperty->needsShaderInputBufferSetup_ = CloneNeedsShaderInputBufferSetup();
        paintProperty->needsModelSourceSetup_ = CloneNeedsModelSourceSetup();
        paintProperty->needsModelBackgroundSetup_ = CloneNeedsModelBackgroundSetup();
        paintProperty->needsModelCameraMoveSetup_ = CloneNeedsModelCameraMoveSetup();

        return paintProperty;
    }

    void ResetFlagProperties()
    {
        UpdateNeedsAnimationsSetup(false);
        UpdateNeedsGeometriesSetup(false);
        UpdateNeedsCameraSetup(false);
        UpdateNeedsLightsSetup(false);
        UpdateNeedsCustomRenderSetup(false);
        UpdateNeedsShaderPathSetup(false);
        UpdateNeedsImageTexturePathsSetup(false);
        UpdateNeedsShaderInputBufferSetup(false);
        UpdateNeedsModelSourceSetup(false);
        UpdateNeedsModelBackgroundSetup(false);
        UpdateNeedsModelCameraMoveSetup(false);
    }

    void Reset() override
    {
        PaintProperty::Reset();
        ResetCameraDistance();
        ResetCameraIsAngular();
        ResetCameraRotation();
        ResetCameraLookAt();
        ResetCameraUp();
        ResetCameraZNear();
        ResetCameraZFar();
        ResetCameraFOV();
        ResetModelLights();
        ResetModelSingleLight();
        ResetModelAnimations();
        ResetModelSingleAnimation();
        ResetModelGeometries();
        ResetModelSingleGeometry();
        ResetModelCustomRender();
        ResetShaderPath();
        ResetModelImageTexturePaths();
        ResetModelSingleImageTexturePath();
        ResetModelShaderInputBuffer();
        ResetModelSource();
        ResetModelBackground();
        ResetModelCameraMove();
        ResetRenderHeight();
        ResetRenderWidth();
        ResetRenderFrameRate();
        ResetFlagProperties();
    }

    void ModelLightsAnimationUpdate(const std::vector<RefPtr<ModelLight>>& lights)
    {
        propModelLights_ = lights;
        UpdatePropertyChangeFlag(PROPERTY_UPDATE_RENDER);
        UpdateNeedsLightsSetup(true);
    }

    void OnModelSingleLightUpdate(const RefPtr<ModelLight>& light)
    {
        propModelLights_.value().push_back(light);
        ResetModelSingleLight();
        UpdateNeedsLightsSetup(true);
    }

    void OnModelSingleAnimationUpdate(const std::shared_ptr<Render3D::GLTFAnimation>& animation)
    {
        propModelAnimations_.value().push_back(animation);
        ResetModelSingleAnimation();
        UpdateNeedsAnimationsSetup(true);
    }

    void OnModelSingleGeometryUpdate(const std::shared_ptr<Render3D::Geometry>& geometry)
    {
        propModelGeometries_.value().push_back(geometry);
        ResetModelSingleGeometry();
        UpdateNeedsGeometriesSetup(true);
    }

    void OnModelSingleImageTexturePathUpdate(const std::string& path)
    {
        propModelImageTexturePaths_.value().push_back(path);
        ResetModelSingleImageTexturePath();
        UpdateNeedsImageTexturePathsSetup(true);
    }

    DEFINE_NEEDS_SETUP_FLAG_TRIGGER_PROPERTY(
        CameraDistance, AnimatableFloat, Camera, PROPERTY_UPDATE_RENDER);
    DEFINE_NEEDS_SETUP_FLAG_TRIGGER_PROPERTY(
        CameraIsAngular, bool, Camera, PROPERTY_UPDATE_RENDER);
    DEFINE_NEEDS_SETUP_FLAG_TRIGGER_PROPERTY(
        CameraRotation, Quaternion, Camera, PROPERTY_UPDATE_RENDER);
    DEFINE_NEEDS_SETUP_FLAG_TRIGGER_PROPERTY(
        CameraLookAt, Vec3, Camera, PROPERTY_UPDATE_RENDER);
    DEFINE_NEEDS_SETUP_FLAG_TRIGGER_PROPERTY(
        CameraUp, Vec3, Camera, PROPERTY_UPDATE_RENDER);
    DEFINE_NEEDS_SETUP_FLAG_TRIGGER_PROPERTY(
        CameraZNear, float, Camera, PROPERTY_UPDATE_RENDER);
    DEFINE_NEEDS_SETUP_FLAG_TRIGGER_PROPERTY(
        CameraZFar, float, Camera, PROPERTY_UPDATE_RENDER);
    DEFINE_NEEDS_SETUP_FLAG_TRIGGER_PROPERTY(
        CameraFOV, float, Camera, PROPERTY_UPDATE_RENDER);

    DEFINE_NEEDS_SETUP_FLAG_TRIGGER_PROPERTY(
        ModelBackground, std::string, ModelBackground, PROPERTY_UPDATE_RENDER);
    DEFINE_NEEDS_SETUP_FLAG_TRIGGER_PROPERTY(
        ModelTransparent, bool, ModelBackground, PROPERTY_UPDATE_RENDER);
    DEFINE_NEEDS_SETUP_FLAG_TRIGGER_PROPERTY(ModelSource, std::string, ModelSource, PROPERTY_UPDATE_RENDER);
    DEFINE_NEEDS_SETUP_FLAG_TRIGGER_PROPERTY(
        ShaderPath, std::string, ShaderPath, PROPERTY_UPDATE_RENDER);
    DEFINE_NEEDS_SETUP_FLAG_TRIGGER_PROPERTY(RenderWidth, float, RenderWidth, PROPERTY_UPDATE_RENDER);
    DEFINE_NEEDS_SETUP_FLAG_TRIGGER_PROPERTY(RenderHeight, float, RenderHeight, PROPERTY_UPDATE_RENDER);
    DEFINE_NEEDS_SETUP_FLAG_TRIGGER_PROPERTY(RenderFrameRate, float, RenderFrameRate, PROPERTY_UPDATE_RENDER);
    DEFINE_NEEDS_SETUP_FLAG_TRIGGER_PROPERTY(
        ModelCustomRender, std::shared_ptr<Render3D::CustomRenderDescriptor>, CustomRender,
        PROPERTY_UPDATE_RENDER);
    DEFINE_NEEDS_SETUP_FLAG_TRIGGER_PROPERTY(
        ModelShaderInputBuffer, std::shared_ptr<Render3D::ShaderInputBuffer>, ShaderInputBuffer,
        PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(
        ModelLights, std::vector<RefPtr<ModelLight>>, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP_AND_USING_CALLBACK(
        ModelSingleLight, RefPtr<ModelLight>, PROPERTY_UPDATE_RENDER);

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(
        ModelAnimations, std::vector<std::shared_ptr<Render3D::GLTFAnimation>>, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP_AND_USING_CALLBACK(
        ModelSingleAnimation, std::shared_ptr<Render3D::GLTFAnimation>, PROPERTY_UPDATE_RENDER);

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(
        ModelGeometries, std::vector<std::shared_ptr<Render3D::Geometry>>, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP_AND_USING_CALLBACK(
        ModelSingleGeometry, std::shared_ptr<Render3D::Geometry>, PROPERTY_UPDATE_RENDER);

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(
        ModelImageTexturePaths, std::vector<std::string>, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP_AND_USING_CALLBACK(
        ModelSingleImageTexturePath, std::string, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(ModelCameraMove, bool, PROPERTY_UPDATE_RENDER);

    DEFINE_NEEDS_SETUP_FLAG_PROPERTY(Camera, false, PROPERTY_UPDATE_RENDER);
    DEFINE_NEEDS_SETUP_FLAG_PROPERTY(Lights, false, PROPERTY_UPDATE_RENDER);
    DEFINE_NEEDS_SETUP_FLAG_PROPERTY(Animations, false, PROPERTY_UPDATE_RENDER);
    DEFINE_NEEDS_SETUP_FLAG_PROPERTY(Geometries, false, PROPERTY_UPDATE_RENDER);
    DEFINE_NEEDS_SETUP_FLAG_PROPERTY(CustomRender, false, PROPERTY_UPDATE_RENDER);
    DEFINE_NEEDS_SETUP_FLAG_PROPERTY(ShaderPath, false, PROPERTY_UPDATE_RENDER);
    DEFINE_NEEDS_SETUP_FLAG_PROPERTY(ImageTexturePaths, false, PROPERTY_UPDATE_RENDER);
    DEFINE_NEEDS_SETUP_FLAG_PROPERTY(ShaderInputBuffer, false, PROPERTY_UPDATE_RENDER);
    DEFINE_NEEDS_SETUP_FLAG_PROPERTY(ModelSource, false, PROPERTY_UPDATE_RENDER);
    DEFINE_NEEDS_SETUP_FLAG_PROPERTY(RenderWidth, false, PROPERTY_UPDATE_RENDER);
    DEFINE_NEEDS_SETUP_FLAG_PROPERTY(RenderHeight, false, PROPERTY_UPDATE_RENDER);
    DEFINE_NEEDS_SETUP_FLAG_PROPERTY(RenderFrameRate, false, PROPERTY_UPDATE_RENDER);
    DEFINE_NEEDS_SETUP_FLAG_PROPERTY(ModelBackground, false, PROPERTY_UPDATE_RENDER);
    DEFINE_NEEDS_SETUP_FLAG_PROPERTY(ModelCameraMove, false, PROPERTY_UPDATE_RENDER);

private:
    ACE_DISALLOW_COPY_AND_MOVE(ModelPaintProperty);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MODEL_MODEL_PAINT_PROPERTY_H
