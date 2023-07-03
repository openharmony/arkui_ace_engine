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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MODEL_MODEL_VIEW_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MODEL_MODEL_VIEW_H

#include <mutex>

#include "base/geometry/animatable_float.h"
#include "base/geometry/quaternion.h"
#include "base/geometry/vec3.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "foundation/graphic/graphic_3d/3d_widget_adapter/include/custom/custom_render_descriptor.h"
#include "foundation/graphic/graphic_3d/3d_widget_adapter/include/data_type/constants.h"
#include "foundation/graphic/graphic_3d/3d_widget_adapter/include/data_type/geometry/geometry.h"
#include "foundation/graphic/graphic_3d/3d_widget_adapter/include/data_type/gltf_animation.h"
#include "foundation/graphic/graphic_3d/3d_widget_adapter/include/data_type/light.h"
#include "foundation/graphic/graphic_3d/3d_widget_adapter/include/data_type/position.h"
#include "foundation/graphic/graphic_3d/3d_widget_adapter/include/data_type/shader_input_buffer.h"

namespace OHOS::Ace {

class ModelView {
public:
    static ModelView* GetInstance();
    virtual ~ModelView() = default;
    virtual void Create(const std::string& src) = 0;
    virtual void SetBackground(const std::string& src) = 0;
    virtual void SetHandleCameraMove(bool value) = 0;
    virtual void SetTransparent(bool value) = 0;
    virtual void SetCameraPosition(AnimatableFloat x, AnimatableFloat y, AnimatableFloat z,
        AnimatableFloat distance, bool isAngular) = 0;
    virtual void SetCameraRotation(Quaternion quat) = 0;
    virtual void SetCameraFrustum(float zNear, float zFar, float fovDegrees) = 0;
    virtual void SetCameraLookAt(Vec3 lookAtVec) = 0;
    virtual void SetCameraUp(Vec3 upVec) = 0;
    virtual void AddLight(const RefPtr<OHOS::Render3D::SVLight>& light) = 0;
    virtual void AddGeometry(const RefPtr<OHOS::Render3D::SVGeometry>& shape) = 0;
    virtual void AddGLTFAnimation(const RefPtr<OHOS::Render3D::GLTFAnimation>& animation) = 0;
    virtual void AddCustomRender(const RefPtr<OHOS::Render3D::SVCustomRenderDescriptor>& customRender) = 0;
    virtual void SetWidth(Dimension& width) = 0;
    virtual void SetHeight(Dimension& height) = 0;
    virtual void SetShader(const std::string& path) = 0;
    virtual void AddShaderImageTexture(const std::string& path) = 0;
    virtual void AddShaderInputBuffer(const RefPtr<OHOS::Render3D::ShaderInputBuffer>& buffer) = 0;

private:
    static std::unique_ptr<ModelView> instance_;
    static std::mutex mutex_;
};

} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MODEL_MODEL_VIEW_H
