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

#include "core/components_ng/render/paint_property.h"

#include "base/geometry/animatable_float.h"
#include "base/geometry/vec3.h"
#include "foundation/graphic/graphic_3d/3d_widget_adapter/include/data_type/geometry/geometry.h"
#include "foundation/graphic/graphic_3d/3d_widget_adapter/include/data_type/gltf_animation.h"
#include "foundation/graphic/graphic_3d/3d_widget_adapter/include/data_type/light.h"

namespace OHOS::Ace::NG {

#define DEFINE_NEEDS_SETUP_FLAG_PROPERTY(name, defaultVal, changeFlag)  \
public:                                                                 \
    bool Needs##name##Setup() const                                     \
    {                                                                   \
        return needs##name##Setup_;                                     \
    }                                                                   \
    void UpdateNeeds##name##Setup(const bool value)                     \
    {                                                                   \
        needs##name##Setup_ = value;                                    \
        if (value) {                                                    \
            UpdatePropertyChangeFlag(changeFlag);                       \
        }                                                               \
    }                                                                   \
    bool CloneNeeds##name##Setup() const                                \
    {                                                                   \
        return needs##name##Setup_;                                     \
    }                                                                   \
private:                                                                \
    bool needs##name##Setup_ = defaultVal;


class ModelPaintProperty : public PaintProperty {
    DECLARE_ACE_TYPE(ModelPaintProperty, PaintProperty)

public:
    ModelPaintProperty() {
        // Initialize model lights to empty vector;
        propModelLights_ = std::vector<RefPtr<OHOS::Render3D::SVLight>> {};
        propModelAnimations_ = std::vector<RefPtr<OHOS::Render3D::GLTFAnimation>> {};
        propModelGeometries_ = std::vector<RefPtr<OHOS::Render3D::SVGeometry>> {};
    };
    ~ModelPaintProperty() override = default;

    RefPtr<PaintProperty> Clone() const override
    {
        auto paintProperty = MakeRefPtr<ModelPaintProperty>();
        paintProperty->UpdatePaintProperty(this);
        paintProperty->propCameraPosition_ = CloneCameraPosition();
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
        paintProperty->needsCameraSetup_ = CloneNeedsCameraSetup();
        paintProperty->needsLightsSetup_ = CloneNeedsLightsSetup();
        paintProperty->needsAnimationsSetup_ = CloneNeedsAnimationsSetup();
        paintProperty->needsGeometriesSetup_ = CloneNeedsGeometriesSetup();
        return paintProperty;
    }

    void ResetFlagProperties()
    {
        UpdateNeedsAnimationsSetup(false);
        UpdateNeedsGeometriesSetup(false);
        UpdateNeedsCameraSetup(false);
        UpdateNeedsLightsSetup(false);
    }

    void Reset() override
    {
        PaintProperty::Reset();
        ResetCameraPosition();
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
        ResetFlagProperties();
    }

    void OnModelSingleLightUpdate(const RefPtr<OHOS::Render3D::SVLight>& light)
    {
        propModelLights_.value().push_back(light);
        LOGD("MODEL_NG: propModelLights_.size() -> %u", GetModelLightsValue().size());
        ResetModelSingleLight();
        UpdateNeedsLightsSetup(true);
    }

    void OnModelSingleAnimationUpdate(const RefPtr<OHOS::Render3D::GLTFAnimation>& animation)
    {
        propModelAnimations_.value().push_back(animation);
        LOGD("MODEL_NG: propModelAnimations_.size() -> %u", GetModelAnimationsValue().size());
        ResetModelSingleAnimation();
        UpdateNeedsAnimationsSetup(true);
    }

    void OnModelSingleGeometryUpdate(const RefPtr<OHOS::Render3D::SVGeometry>& geometry)
    {
        propModelGeometries_.value().push_back(geometry);
        LOGD("MODEL_NG: propModelGeometries_.size() -> %u", GetModelGeometriesValue().size());
        ResetModelSingleGeometry();
        UpdateNeedsGeometriesSetup(true);
    }

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(CameraPosition, OHOS::Ace::Vec3, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(CameraDistance, OHOS::Ace::AnimatableFloat, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(CameraIsAngular, bool, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(CameraRotation, OHOS::Ace::Quaternion, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(CameraLookAt, OHOS::Ace::Vec3, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(CameraUp, OHOS::Ace::Vec3, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(CameraZNear, float, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(CameraZFar, float, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(CameraFOV, float, PROPERTY_UPDATE_RENDER);

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(
        ModelLights, std::vector<RefPtr<OHOS::Render3D::SVLight>>, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP_AND_USING_CALLBACK(
        ModelSingleLight, RefPtr<OHOS::Render3D::SVLight>, PROPERTY_UPDATE_RENDER);

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(
        ModelAnimations, std::vector<RefPtr<OHOS::Render3D::GLTFAnimation>>, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP_AND_USING_CALLBACK(
        ModelSingleAnimation, RefPtr<OHOS::Render3D::GLTFAnimation>, PROPERTY_UPDATE_RENDER);

    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP(
        ModelGeometries, std::vector<RefPtr<OHOS::Render3D::SVGeometry>>, PROPERTY_UPDATE_RENDER);
    ACE_DEFINE_PROPERTY_ITEM_WITHOUT_GROUP_AND_USING_CALLBACK(
        ModelSingleGeometry, RefPtr<OHOS::Render3D::SVGeometry>, PROPERTY_UPDATE_RENDER);

    DEFINE_NEEDS_SETUP_FLAG_PROPERTY(Camera, false, PROPERTY_UPDATE_RENDER);
    DEFINE_NEEDS_SETUP_FLAG_PROPERTY(Lights, false, PROPERTY_UPDATE_RENDER);
    DEFINE_NEEDS_SETUP_FLAG_PROPERTY(Animations, false, PROPERTY_UPDATE_RENDER);
    DEFINE_NEEDS_SETUP_FLAG_PROPERTY(Geometries, false, PROPERTY_UPDATE_RENDER);

private:
    ACE_DISALLOW_COPY_AND_MOVE(ModelPaintProperty);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MODEL_MODEL_PAINT_PROPERTY_H