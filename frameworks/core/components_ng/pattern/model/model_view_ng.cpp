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

#include "core/components_ng/pattern/model/model_view_ng.h"

#include "base/geometry/dimension.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/model/model_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::NG {

ModelViewNG::ModelViewNG()
{
    const RefPtr<PipelineBase> pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    if (pipeline) {
        cameraPosition_.SetContextAndCallbacks(pipeline,
            std::bind(&ModelViewNG::PerformCameraUpdate, this));
    } else {
        LOGE("ModelViewNG() pipeline context is null");
    }
}

void ModelViewNG::Create(const std::string& src)
{
    LOGD("MODEL_NG: Create-> src: %s", src.c_str());
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::MODEL_ETS_TAG, nodeId, [&nodeId]() { return AceType::MakeRefPtr<ModelPattern>(nodeId); });
    stack->Push(frameNode);
    frameNode_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
    ACE_UPDATE_LAYOUT_PROPERTY(ModelLayoutProperty, NeedsSceneSetup, false);
    ACE_UPDATE_LAYOUT_PROPERTY(ModelLayoutProperty, ModelSource, src);
    ACE_UPDATE_PAINT_PROPERTY(ModelPaintProperty, ModelLights, {});
    ACE_UPDATE_PAINT_PROPERTY(ModelPaintProperty, ModelAnimations, {});
    ACE_UPDATE_PAINT_PROPERTY(ModelPaintProperty, ModelGeometries, {});
    ACE_UPDATE_PAINT_PROPERTY(ModelPaintProperty, ModelCustomRenders, {});
    ACE_UPDATE_PAINT_PROPERTY(ModelPaintProperty, ModelImageTexturePaths, {});
    ACE_UPDATE_PAINT_PROPERTY(ModelPaintProperty, ModelShaderInputBuffers, {});

    lightsIdx_ = 0;
    if (lights_.empty()) {
        isFirstLightsUpdate_ = true;
    } else {
        isFirstLightsUpdate_ = false;
    }
}

void ModelViewNG::SetBackground(const std::string& value)
{
    LOGD("MODEL_NG: background: %s", value.c_str());
    ACE_UPDATE_LAYOUT_PROPERTY(ModelLayoutProperty, ModelBackground, value);
}

void ModelViewNG::SetHandleCameraMove(bool value)
{
    LOGD("MODEL_NG: cameraMode: %s", value ? "true" : "false");
    ACE_UPDATE_LAYOUT_PROPERTY(ModelLayoutProperty, ModelCameraMove, value);
}

void ModelViewNG::SetTransparent(bool value)
{
    LOGD("MODEL_NG: transparent: %s", value ? "true" : "false");
    ACE_UPDATE_LAYOUT_PROPERTY(ModelLayoutProperty, ModelTransparent, value);
}

void ModelViewNG::SetCameraPosition(AnimatableFloat x, AnimatableFloat y, AnimatableFloat z,
    AnimatableFloat distance, bool isAngular)
{
    LOGD("MODEL_NG: cameraPosition: [%.2f, %.2f %.2f], distance: %.2f",
        x.GetValue(), y.GetValue(), z.GetValue(), distance.GetValue());
    if (NearEqual(cameraPosition_.GetDistance().GetValue(), std::numeric_limits<float>::max())) {
        // Initial update. Set the values directly without the animation if any.
        cameraPosition_.SetDistance(AnimatableFloat(distance.GetValue()));
        cameraPosition_.SetVec(OHOS::Ace::Vec3(x.GetValue(), y.GetValue(), z.GetValue()));
        ACE_UPDATE_PAINT_PROPERTY(ModelPaintProperty, CameraDistance, distance);
        ACE_UPDATE_PAINT_PROPERTY(ModelPaintProperty, CameraPosition, OHOS::Ace::Vec3(x, y, z));
    } else {
        cameraPosition_.SetDistance(distance);
        cameraPosition_.SetVec(OHOS::Ace::Vec3(x, y, z));
    }
    LOGD("MODEL_NG: cameraIsAngular: %s", isAngular ? "true" : "false");
    ACE_UPDATE_PAINT_PROPERTY(ModelPaintProperty, CameraIsAngular, isAngular);
}

void ModelViewNG::SetCameraRotation(Quaternion quat)
{
    LOGD("MODEL_NG: cameraRotation: @quat");
    ACE_UPDATE_PAINT_PROPERTY(ModelPaintProperty, CameraRotation, quat);
}

void ModelViewNG::SetCameraFrustum(float zNear, float zFar, float fovDegrees)
{
    LOGD("MODEL_NG: cameraFrustum");
    ACE_UPDATE_PAINT_PROPERTY(ModelPaintProperty, CameraZNear, zNear);
    ACE_UPDATE_PAINT_PROPERTY(ModelPaintProperty, CameraZFar, zFar);
    ACE_UPDATE_PAINT_PROPERTY(ModelPaintProperty, CameraFOV, fovDegrees);
}

void ModelViewNG::SetCameraLookAt(Vec3 lookAtVec)
{
    LOGD("MODEL_NG: cameraLookAt: @Vec3");
    ACE_UPDATE_PAINT_PROPERTY(ModelPaintProperty, CameraLookAt, lookAtVec);
}

void ModelViewNG::SetCameraUp(Vec3 upVec)
{
    LOGD("MODEL_NG: cameraUp: @Vec3");
    ACE_UPDATE_PAINT_PROPERTY(ModelPaintProperty, CameraUp, upVec);
}

void ModelViewNG::AddLight(const RefPtr<OHOS::Render3D::SVLight>& light)
{
    LOGD("MODEL_NG: light: @light");
    if (isFirstLightsUpdate_) {
        // Set the animation callback.
        RefPtr<PipelineBase> pipeline = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(pipeline);
        if (pipeline) {
            light->SetContextAndCallback(pipeline,
                std::bind(&ModelViewNG::PerformLightUpdate, this));
        } else {
            LOGE("ModelViewNG() pipeline context is null");
        }
        lights_.push_back(light);
        ACE_UPDATE_PAINT_PROPERTY(ModelPaintProperty, ModelSingleLight, light);
    } else {
        lightsIdx_++;
        // Update the corresponding light proepties.
        auto currentLight = lights_.at(lightsIdx_-1);
        currentLight->SetLightType(light->GetLightType());
        currentLight->SetIntensity(light->GetLightIntensity());
        currentLight->SetColor(light->GetLightColor());
        currentLight->SetLightShadow(light->GetLightShadow());
        currentLight->SetPosition(light->GetPosition());
        currentLight->SetRotation(light->GetRotation());
        ACE_UPDATE_PAINT_PROPERTY(ModelPaintProperty, ModelSingleLight, currentLight);
    }
}

void ModelViewNG::AddGeometry(const RefPtr<OHOS::Render3D::SVGeometry>& shape)
{
    LOGD("MODEL_NG: AddGeometry @shape %s", shape->GetName().c_str());
    ACE_UPDATE_PAINT_PROPERTY(ModelPaintProperty, ModelSingleGeometry, shape);
}

void ModelViewNG::AddGLTFAnimation(const RefPtr<OHOS::Render3D::GLTFAnimation>& animation)
{
    LOGD("MODEL_NG: AddGLTFAnimation @animation");
    ACE_UPDATE_PAINT_PROPERTY(ModelPaintProperty, ModelSingleAnimation, animation);
}

void ModelViewNG::AddCustomRender(const RefPtr<OHOS::Render3D::SVCustomRenderDescriptor>& customRender)
{
    LOGD("MODEL_NG: AddCustomRender");
    ACE_UPDATE_PAINT_PROPERTY(ModelPaintProperty, ModelSingleCustomRender, customRender);
}

void ModelViewNG::SetWidth(Dimension& width)
{
    LOGD("MODEL_NG: ModelViewNG::SetWidth() %f", width.Value());
    if (LessNotEqual(width.Value(), 0.0)) {
        width.SetValue(0.0);
    }
    ViewAbstract::SetWidth(CalcLength(width));
}

void ModelViewNG::SetHeight(Dimension& height)
{
    LOGD("MODEL_NG: ModelViewNG::SetHeight() %f", height.Value());
    if (LessNotEqual(height.Value(), 0.0)) {
        height.SetValue(0.0);
    }
    ViewAbstract::SetHeight(CalcLength(height));
}

void ModelViewNG::SetShader(const std::string& path)
{
    LOGD("ModelViewNG::SetShader() path: %s", path.c_str());
    ACE_UPDATE_PAINT_PROPERTY(ModelPaintProperty, ShaderPath, path);
}

void ModelViewNG::AddShaderImageTexture(const std::string& path)
{
    LOGD("ModelViewNG::AddShaderImageTexture() path: %s", path.c_str());
    ACE_UPDATE_PAINT_PROPERTY(ModelPaintProperty, ModelSingleImageTexturePath, path);
}

void ModelViewNG::AddShaderInputBuffer(const RefPtr<OHOS::Render3D::ShaderInputBuffer>& buffer)
{
    LOGD("ModelViewNG::AddShaderInputBuffer() size: %d", buffer->GetSize());
    ACE_UPDATE_PAINT_PROPERTY(ModelPaintProperty, ModelSingleShaderInputBuffer, buffer);
}

void ModelViewNG::PerformCameraUpdate()
{
    LOGD("ModelViewNG::PerformCameraUpdate() position: %f, %f, %f, distance: %f", cameraPosition_.GetX(),
        cameraPosition_.GetY(), cameraPosition_.GetZ(), cameraPosition_.GetDistance().GetValue());
    auto frameNode = frameNode_.Upgrade();
    if (!frameNode) {
        LOGE("frameNode is null!");
        return;
    }

    auto paintProperty = frameNode->GetPaintProperty<ModelPaintProperty>();
    if (paintProperty) {
        paintProperty->UpdateCameraDistance(cameraPosition_.GetDistance());
        paintProperty->UpdateCameraPosition(cameraPosition_.GetVec());
        frameNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    } else {
        LOGE("ModelPaintProperty is null");
    }
}

void ModelViewNG::PerformLightUpdate()
{
    auto frameNode = frameNode_.Upgrade();
    if (!frameNode) {
        LOGE("frameNode is null!");
        return;
    }

    auto paintProperty = frameNode->GetPaintProperty<ModelPaintProperty>();
    if (!paintProperty) {
        LOGE("ModelPaintProperty is null");
        return;
    }
    paintProperty->ModelLightsAnimationUpdate(lights_);
    frameNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

} // namespace OHOS::Ace::NG
