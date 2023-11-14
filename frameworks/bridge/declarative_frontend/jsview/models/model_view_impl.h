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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_MODEL_VIEW_IMPL_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_MODEL_VIEW_IMPL_H

#include "core/components/scene_viewer/scene_viewer_component.h"
#include "core/components_ng/pattern/model/model_view.h"

namespace OHOS::Ace::Framework {

class ModelViewImpl : public OHOS::Ace::ModelView {
public:
    void Create(const std::string& src) override;
    void SetBackground(const std::string& src) override;
    void SetHandleCameraMove(const bool value) override;
    void SetTransparent(const bool value) override;
    void SetCameraPosition(AnimatableFloat x, AnimatableFloat y, AnimatableFloat z,
        AnimatableFloat distance, bool isAngular) override;
    void SetCameraRotation(Quaternion quat) override;
    void SetCameraFrustum(float zNear, float zFar, float fovDegrees) override;
    void SetCameraLookAt(Vec3 lookAtVec) override;
    void SetCameraUp(Vec3 upVec) override;
    void AddLight(const RefPtr<OHOS::Render3D::SVLight>& light) override;
    void AddGeometry(const RefPtr<OHOS::Render3D::SVGeometry>& shape) override;
    void AddGLTFAnimation(const RefPtr<OHOS::Render3D::GLTFAnimation>& animation) override;
    void AddCustomRender(const RefPtr<OHOS::Render3D::SVCustomRenderDescriptor>& customRender) override;
    void SetWidth(Dimension& width) override;
    void SetHeight(Dimension& height) override;
    void SetRenderWidth(Dimension& width) override;
    void SetRenderHeight(Dimension& height) override;
    void SetRenderFrameRate(float rate) override;
    void SetShader(const std::string& path) override;
    void AddShaderImageTexture(const std::string& path) override;
    void AddShaderInputBuffer(const RefPtr<OHOS::Render3D::ShaderInputBuffer>& buffer) override;
};

} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_MODEL_VIEW_IMPL_H
