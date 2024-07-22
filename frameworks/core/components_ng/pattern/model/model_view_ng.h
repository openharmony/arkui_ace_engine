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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MODEL_MODEL_VIEW_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MODEL_MODEL_VIEW_NG_H

#include "core/components_ng/pattern/model/model_light.h"
#include "core/components_ng/pattern/model/model_paint_property.h"
#include "core/components_ng/pattern/model/model_position.h"
#include "core/components_ng/pattern/model/model_view.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT ModelViewNG : public ModelView {
public:
    void Create(const ModelViewContext& context) override;
    void SetBackground(const std::string& value) override;
    void SetModelSource(const std::string& value) override;
    void SetHandleCameraMove(bool value) override;
    void AddCustomRender(const std::shared_ptr<Render3D::CustomRenderDescriptor>& customRender) override;
    void SetRenderWidth(Dimension& width) override;
    void SetRenderHeight(Dimension& height) override;
    void SetRenderFrameRate(float rate) override;
    void SetShader(const std::string& path) override;
    void AddShaderImageTexture(const std::string& path) override;
    void AddShaderInputBuffer(const std::shared_ptr<Render3D::ShaderInputBuffer>& buffer) override;
    std::optional<std::shared_ptr<Render3D::ShaderInputBuffer>> GetShaderInputBuffer() override;

    static void AddShaderInputBuffer(FrameNode* frameNode, const std::shared_ptr<Render3D::ShaderInputBuffer>& buffer);
private:
    // Camera and lights animations are done from the frontend with Animatable types.
    WeakPtr<FrameNode> frameNode_;
    ModelPosition cameraPosition_;
    std::vector<RefPtr<ModelLight>> lights_;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_MODEL_MODEL_VIEW_NG_H
