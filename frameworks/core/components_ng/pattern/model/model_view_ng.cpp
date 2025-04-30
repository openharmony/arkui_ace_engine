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

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/model/model_pattern.h"

namespace OHOS::Ace::NG {
void ModelViewNG::Create(const ModelViewContext& context)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    static int staticKey = 0;

    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::MODEL_ETS_TAG, nodeId);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::MODEL_ETS_TAG, nodeId, [&context]() {
            return AceType::MakeRefPtr<ModelPattern>(staticKey++, context);
        });

    stack->Push(frameNode);
    frameNode_ = AceType::WeakClaim(AceType::RawPtr(frameNode));
}

void ModelViewNG::SetBackground(const std::string& value)
{
    ACE_UPDATE_PAINT_PROPERTY(ModelPaintProperty, ModelBackground, value);
}

void ModelViewNG::SetHandleCameraMove(bool value)
{
    ACE_UPDATE_PAINT_PROPERTY(ModelPaintProperty, ModelCameraMove, value);
}

void ModelViewNG::SetModelSource(const std::string& value)
{
    LOGD("MODEL_NG: Model source: %s", value.c_str());
    ACE_UPDATE_PAINT_PROPERTY(ModelPaintProperty, ModelSource, value);
}

void ModelViewNG::AddCustomRender(const std::shared_ptr<Render3D::CustomRenderDescriptor>& customRender)
{
    if (!customRender) {
        return;
    }
    auto frameNode = frameNode_.Upgrade();
    if (!frameNode) {
        LOGE("frameNode is null!");
        return;
    }

    auto paintProperty = frameNode->GetPaintProperty<ModelPaintProperty>();
    if (!paintProperty) {
        LOGE("model paint property is null!");
        return;
    }

    const auto curCustomRender = paintProperty->GetModelCustomRenderValue({ });
    if (!curCustomRender || (curCustomRender->GetUri() != customRender->GetUri())) {
        ACE_UPDATE_PAINT_PROPERTY(ModelPaintProperty, ModelCustomRender, customRender);
    }
}

void ModelViewNG::SetRenderHeight(Dimension& height)
{
    if (LessNotEqual(height.Value(), 0.0)) {
        height.SetValue(1.0);
        LOGE("MODEL_NG: ModelViewNG::SetRenderHeight() heigtScale set default 1.0");
    }
    ACE_UPDATE_PAINT_PROPERTY(ModelPaintProperty, RenderHeight, height.Value());
}

void ModelViewNG::SetRenderWidth(Dimension& width)
{
    if (LessNotEqual(width.Value(), 0.0)) {
        width.SetValue(1.0);
        LOGE("MODEL_NG: ModelViewNG::SetRenderHeight() heigtScale set default 1.0");
    }
    ACE_UPDATE_PAINT_PROPERTY(ModelPaintProperty, RenderWidth, width.Value());
}

void ModelViewNG::SetRenderFrameRate(float rate)
{
    ACE_UPDATE_PAINT_PROPERTY(ModelPaintProperty, RenderFrameRate, rate);
}

void ModelViewNG::SetShader(const std::string& path)
{
    ACE_UPDATE_PAINT_PROPERTY(ModelPaintProperty, ShaderPath, path);
}

void ModelViewNG::AddShaderImageTexture(const std::string& path)
{
    auto frameNode = frameNode_.Upgrade();
    if (!frameNode) {
        LOGE("frameNode is null!");
        return;
    }

    auto paintProperty = frameNode->GetPaintProperty<ModelPaintProperty>();
    if (!paintProperty) {
        LOGE("model paint property is null!");
        return;
    }
    
    const auto& images = paintProperty->GetModelImageTexturePathsValue({ });
    for (auto& image : images) {
        if (image == path) {
            return;
        }
    }

    ACE_UPDATE_PAINT_PROPERTY(ModelPaintProperty, ModelSingleImageTexturePath, path);
}

void ModelViewNG::AddShaderInputBuffer(const std::shared_ptr<Render3D::ShaderInputBuffer>& buffer)
{
    ACE_UPDATE_PAINT_PROPERTY(ModelPaintProperty, ModelShaderInputBuffer, buffer);
}

void ModelViewNG::AddShaderInputBuffer(FrameNode* frameNode, const std::shared_ptr<Render3D::ShaderInputBuffer>& buffer)
{
    ACE_UPDATE_NODE_PAINT_PROPERTY(ModelPaintProperty, ModelShaderInputBuffer, buffer, frameNode);
}

std::optional<std::shared_ptr<Render3D::ShaderInputBuffer>> ModelViewNG::GetShaderInputBuffer()
{
    auto frameNode = frameNode_.Upgrade();
    if (!frameNode) {
        LOGE("frameNode is null!");
        return {};
    }

    auto paintProperty = frameNode->GetPaintProperty<ModelPaintProperty>();
    if (!paintProperty) {
        LOGE("ModelPaintProperty is null");
        return {};
    }

    return paintProperty->CloneModelShaderInputBuffer();
}

} // namespace OHOS::Ace::NG
