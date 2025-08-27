/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/model/model_paint_property.h"
#include "core/components_ng/base/view_abstract.h"
#ifdef ARKUI_CAPI_UNITTEST
#include "test/unittest/capi/stubs/mock_shader_input_buffer.h"
#include "test/unittest/capi/stubs/mock_custom_render_descriptor.h"
#include "test/unittest/capi/stubs/mock_model_pattern.h"
#else
#include "core/components_ng/pattern/model/model_pattern.h"
#endif // ARKUI_CAPI_UNITTEST

namespace OHOS::Ace::NG {

// void ModelViewNG::SetModelViewContext(FrameNode* frameNode, const ModelViewContext& context)
// {
//     auto pattern = frameNode->GetPattern<ModelPattern>();
//     pattern->SetModelViewContext(context);
// }


// RefPtr<FrameNode> ModelViewNG::CreateFrameNode(int32_t nodeId)
// {
//     static uint32_t staticKey = 0;
//     auto frameNode = FrameNode::GetOrCreateFrameNode(
//         V2::MODEL_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<ModelPattern>(staticKey++); });
//     return frameNode;
// }

// void ModelViewNG::SetBackground(FrameNode* frameNode, const std::string& value)
// {
//     ACE_UPDATE_NODE_PAINT_PROPERTY(ModelPaintProperty, ModelBackground, value, frameNode);
// }

// void ModelViewNG::SetRenderHeight(FrameNode* frameNode, const std::optional<Dimension>& height)
// {
//     Dimension value;
//     if (height) {
//         value = height.value();
//     } else {
//         value.SetValue(1.0);
//     }
//     ACE_UPDATE_NODE_PAINT_PROPERTY(ModelPaintProperty, RenderHeight, value.Value(), frameNode);
// }

// void ModelViewNG::SetRenderWidth(FrameNode* frameNode, const std::optional<Dimension>& width)
// {
//     Dimension value;
//     if (width) {
//         value = width.value();
//     } else {
//         value.SetValue(1.0);
//     }
//     ACE_UPDATE_NODE_PAINT_PROPERTY(ModelPaintProperty, RenderWidth, value.Value(), frameNode);
// }

// void ModelViewNG::SetShader(FrameNode* frameNode, const std::string& path)
// {
//     ACE_UPDATE_NODE_PAINT_PROPERTY(ModelPaintProperty, ShaderPath, path, frameNode);
// }

// void ModelViewNG::AddShaderImageTexture(FrameNode* frameNode, const std::string& path)
// {
//     auto paintProperty = frameNode->GetPaintProperty<ModelPaintProperty>();
//     if (!paintProperty) {
//         LOGE("model paint property is null!");
//         return;
//     }

//     const auto& images = paintProperty->GetModelImageTexturePathsValue({ });
//     for (auto& image : images) {
//         if (image == path) {
//             return;
//         }
//     }

//     ACE_UPDATE_NODE_PAINT_PROPERTY(ModelPaintProperty, ModelSingleImageTexturePath, path, frameNode);
// }

// void ModelViewNG::AddCustomRender(FrameNode* frameNode,
//                                   const std::shared_ptr<Render3D::CustomRenderDescriptor>& customRender)
// {
//     if (!customRender) {
//         return;
//     }

//     auto paintProperty = frameNode->GetPaintProperty<ModelPaintProperty>();
//     if (!paintProperty) {
//         LOGE("model paint property is null!");
//         return;
//     }

//     const auto curCustomRender = paintProperty->GetModelCustomRenderValue({ });
//     if (!curCustomRender || (curCustomRender->GetUri() != customRender->GetUri())) {
//         ACE_UPDATE_PAINT_PROPERTY(ModelPaintProperty, ModelCustomRender, customRender);
//     }
// }
// void ModelViewNG::AddShaderInputBuffer(FrameNode* frameNode, const std::shared_ptr<Render3D::ShaderInputBuffer>& buffer)
// {
//     ACE_UPDATE_NODE_PAINT_PROPERTY(ModelPaintProperty, ModelShaderInputBuffer, buffer, frameNode);
// }
}