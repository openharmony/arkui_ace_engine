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

#include <memory>
#include <mutex>
#ifdef ARKUI_CAPI_UNITTEST
#include "test/unittest/capi/stubs/mock_shader_input_buffer.h"
#include "test/unittest/capi/stubs/mock_custom_render_descriptor.h"
#else
#include "custom/custom_render_descriptor.h"
#include "custom/shader_input_buffer.h"
#include "data_type/constants.h"
#include "data_type/geometry/geometry.h"
#include "data_type/gltf_animation.h"
#include "data_type/light.h"
#include "data_type/position.h"
#endif // ARKUI_CAPI_UNITTEST
#include "base/geometry/animatable_float.h"
#include "base/geometry/quaternion.h"
#include "base/geometry/vec3.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"

#if defined(KIT_3D_ENABLE)
#include "scene_adapter/intf_scene_adapter.h"
#endif

namespace OHOS::Ace {

struct ModelViewContext {
    std::string bundleName_;
    std::string moduleName_;
    Render3D::SurfaceType surfaceType_;
#if defined(KIT_3D_ENABLE)
    std::shared_ptr<Render3D::ISceneAdapter> sceneAdapter_ = nullptr;
#endif
};

class ModelView {
public:
    static ModelView* GetInstance();
    virtual ~ModelView() = default;
    virtual void Create(const ModelViewContext& context) = 0;
    virtual void SetBackground(const std::string& src) = 0;
    virtual void SetModelSource(const std::string& src) = 0;
    virtual void SetHandleCameraMove(bool value) = 0;
    virtual void AddCustomRender(const std::shared_ptr<Render3D::CustomRenderDescriptor>& customRender) = 0;
    virtual void SetRenderWidth(Dimension& width) = 0;
    virtual void SetRenderHeight(Dimension& height) = 0;
    virtual void SetRenderFrameRate(float rate) = 0;
    virtual void SetShader(const std::string& path) = 0;
    virtual void AddShaderImageTexture(const std::string& path) = 0;
    virtual void AddShaderInputBuffer(const std::shared_ptr<Render3D::ShaderInputBuffer>& buffer) = 0;
    virtual std::optional<std::shared_ptr<Render3D::ShaderInputBuffer>> GetShaderInputBuffer() = 0;

private:
    static std::unique_ptr<ModelView> instance_;
    static std::mutex mutex_;
};

} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MODEL_MODEL_VIEW_H
