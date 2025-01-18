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
#include "core/interfaces/native/node/node_component3d_modifier.h"

#include "frameworks/core/components_ng/pattern/model/model_view_ng.h"

namespace OHOS::Ace::NG {
namespace {
void SetShaderInputBuffer(ArkUINodeHandle node, ArkUI_Float32* buffer, ArkUI_Int32 size)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (size <= 0) {
        return;
    }
    std::shared_ptr<OHOS::Render3D::ShaderInputBuffer> bufferArray = nullptr;
    // same shader input buffer would be rejected to update for nearEqual check
    bufferArray = std::make_shared<OHOS::Render3D::ShaderInputBuffer>();
    if (!bufferArray->Alloc(size)) {
        return;
    }
    for (int32_t i = 0; i < size; i++) {
        bufferArray->Update(buffer[i], i);
    }
    ModelViewNG::AddShaderInputBuffer(frameNode, bufferArray);
}

void ResetShaderInputBuffer(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::shared_ptr<OHOS::Render3D::ShaderInputBuffer> bufferArray = nullptr;
    // same shader input buffer would be rejected to update for nearEqual check
    bufferArray = std::make_shared<OHOS::Render3D::ShaderInputBuffer>();
    ModelViewNG::AddShaderInputBuffer(frameNode, bufferArray);
}
} // namespace

namespace NodeModifier {
const ArkUIComponent3DModifier* GetComponent3DModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIComponent3DModifier modifier = {
        .setShaderInputBuffer = SetShaderInputBuffer,
        .resetShaderInputBuffer = ResetShaderInputBuffer,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}

const CJUIComponent3DModifier* GetCJUIComponent3DModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUIComponent3DModifier modifier = {
        .setShaderInputBuffer = SetShaderInputBuffer,
        .resetShaderInputBuffer = ResetShaderInputBuffer,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
