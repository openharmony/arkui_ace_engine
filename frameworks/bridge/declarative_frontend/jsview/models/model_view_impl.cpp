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

#include "bridge/declarative_frontend/jsview/models/model_view_impl.h"

#include "base/geometry/dimension.h"
#include "bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/components_ng/base/view_abstract_model.h"

namespace OHOS::Ace::Framework {

#define GET_COMPONENT_OR_RETURN()                                                  \
    auto top = ViewStackProcessor::GetInstance()->GetMainComponent();              \
    auto svComponent = AceType::DynamicCast<OHOS::Ace::SceneViewerComponent>(top); \
    if (!svComponent) {                                                            \
        LOGE("%s Component is not SceneViewComponent", __func__);                  \
        return;                                                                    \
    }                                                                              \
    svComponent

void ModelViewImpl::Create(const std::string& src)
{
    auto svComponent = AceType::MakeRefPtr<OHOS::Ace::SceneViewerComponent>();
    svComponent->SetGltfSrc(src);

    ViewStackProcessor::GetInstance()->Push(svComponent);
}

void ModelViewImpl::SetBackground(const std::string& value)
{
    GET_COMPONENT_OR_RETURN()->SetBackgroundSrc(value);
}

void ModelViewImpl::SetHandleCameraMove(const bool value)
{
    GET_COMPONENT_OR_RETURN()->SetHandleCameraMove(value);
}

void ModelViewImpl::SetTransparent(const bool value)
{
    GET_COMPONENT_OR_RETURN()->SetTransparent(value);
}

void ModelViewImpl::SetCameraPosition(
    AnimatableFloat x, AnimatableFloat y, AnimatableFloat z, AnimatableFloat distance, bool isAngular)
{
    GET_COMPONENT_OR_RETURN()->SetCameraPosition(x, y, z, distance, isAngular);
}

void ModelViewImpl::SetCameraRotation(Quaternion quat)
{
    GET_COMPONENT_OR_RETURN()->SetCameraRotation(quat);
}

void ModelViewImpl::SetCameraFrustum(float zNear, float zFar, float fovDegrees)
{
    GET_COMPONENT_OR_RETURN()->SetCameraFrustum(zNear, zFar, fovDegrees);
}

void ModelViewImpl::SetCameraLookAt(Vec3 lookAtVec)
{
    GET_COMPONENT_OR_RETURN()->SetCameraLookAt(lookAtVec);
}

void ModelViewImpl::SetCameraUp(Vec3 upVec)
{
    GET_COMPONENT_OR_RETURN()->SetCameraUp(upVec);
}

void ModelViewImpl::AddLight(const RefPtr<OHOS::Render3D::SVLight>& light)
{
    GET_COMPONENT_OR_RETURN()->AddLight(light);
}

void ModelViewImpl::AddGeometry(const RefPtr<OHOS::Render3D::SVGeometry>& shape)
{
    GET_COMPONENT_OR_RETURN()->AddGeometry(shape);
}

void ModelViewImpl::AddGLTFAnimation(const RefPtr<OHOS::Render3D::GLTFAnimation>& animation)
{
    GET_COMPONENT_OR_RETURN()->AddGLTFAnimation(animation);
}

void ModelViewImpl::AddCustomRender(const RefPtr<OHOS::Render3D::SVCustomRenderDescriptor>& customRender)
{
    GET_COMPONENT_OR_RETURN()->AddCustomRender(customRender);
}

void ModelViewImpl::SetWidth(Dimension& width)
{
    /*
    Model's texture width & height to be updated in the backend during animation via RenderNode.
    So Async animation shall be disabled.
    */
    auto* stack = ViewStackProcessor::GetInstance();
    auto option = stack->GetImplicitAnimationOption();
    option.SetAllowRunningAsynchronously(false);
    stack->SetImplicitAnimationOption(option);
    if (LessNotEqual(width.Value(), 0.0)) {
        width.SetValue(0.0);
    }
    ViewAbstractModel::GetInstance()->SetWidth(width);
}

void ModelViewImpl::SetHeight(Dimension& height)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto option = stack->GetImplicitAnimationOption();
    option.SetAllowRunningAsynchronously(false);
    stack->SetImplicitAnimationOption(option);
    if (LessNotEqual(height.Value(), 0.0)) {
        height.SetValue(0.0);
    }
    ViewAbstractModel::GetInstance()->SetHeight(height);
}

void ModelViewImpl::SetRenderHeight(Dimension& height) {}

void ModelViewImpl::SetRenderWidth(Dimension& width) {}

void ModelViewImpl::SetRenderFrameRate(float rate) {}

void ModelViewImpl::SetShader(const std::string& path) {}

void ModelViewImpl::AddShaderImageTexture(const std::string& path) {}

void ModelViewImpl::AddShaderInputBuffer(const RefPtr<OHOS::Render3D::ShaderInputBuffer>& buffer) {}

} // namespace OHOS::Ace::Framework
