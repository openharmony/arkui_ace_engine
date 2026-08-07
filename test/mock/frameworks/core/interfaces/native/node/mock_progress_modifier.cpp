/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
#include "core/interfaces/native/node/progress_modifier.h"
#include "core/components_ng/pattern/progress/progress_model_ng.h"
#include "core/components_ng/pattern/progress/progress_model_static.h"
#include "core/components_ng/pattern/progress/bridge/progress_custom_modifier.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/progress/progress_pattern.h"
#include "core/components_ng/pattern/progress/progress_paint_property.h"
#include "core/components_ng/pattern/progress/progress_layout_property.h"
namespace OHOS::Ace::NG {
ArkUINodeHandle CreateProgressFrameNode(ArkUI_Uint32 nodeId, ArkUI_Float32 value, ArkUI_Float32 max, ArkUI_Int32 type)
{
    auto frameNode = ProgressModelNG::CreateFrameNode(nodeId, value, max, static_cast<ProgressType>(type));
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode));
}

static void SetBackgroundColorToModelStaticForMock(FrameNode* frameNode,
    const std::optional<Color>& value)
{
    ProgressModelStatic::SetBackgroundColor(frameNode, value);
}

static void SetBuilderFuncToModelNGForMock(FrameNode* frameNode, ProgressMakeCallback&& makeFunc)
{
    ProgressModelNG::SetBuilderFunc(frameNode, std::move(makeFunc));
}

static RefPtr<FrameNode> CreateProgressNodeForLinearIndicator(int32_t nodeId)
{
    auto progressNode = FrameNode::GetOrCreateFrameNode(
        PROGRESS_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<ProgressPattern>(); });
    return progressNode;
}

static void UpdateProgressPropertiesForLinearIndicator(const RefPtr<FrameNode>& targetNode,
    const LinearIndicatorProgressConfig& config)
{
    auto paintProperty = targetNode->GetPaintProperty<NG::ProgressPaintProperty>();
    if (paintProperty) {
        paintProperty->UpdateColor(config.color);
        paintProperty->UpdateBackgroundColor(config.backgroundColor);
        paintProperty->UpdateStrokeRadius(config.strokeRadius);
        if (config.isInitialCreate) {
            paintProperty->UpdateEnableSmoothEffect(false);
        }
    }
    auto layoutProperty = targetNode->GetLayoutProperty<NG::ProgressLayoutProperty>();
    if (layoutProperty) {
        layoutProperty->UpdateStrokeWidth(config.strokeWidth);
        layoutProperty->UpdateLayoutDirection(static_cast<TextDirection>(config.direction));
        if (config.isInitialCreate) {
            layoutProperty->UpdateLayoutWeight(1);
        }
    }
    targetNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

namespace NodeModifier {
const ArkUIProgressModifier* GetProgressModifier()
{
    static const ArkUIProgressModifier modifier = {
        .createProgressFrameNode = CreateProgressFrameNode,
    };
    return &modifier;
}

const ArkUIProgressCustomModifier* GetProgressCustomModifier()
{
    static const ArkUIProgressCustomModifier modifier = {
        .createProgressNode = CreateProgressNodeForLinearIndicator,
        .updateProgressProperties = UpdateProgressPropertiesForLinearIndicator,
        .setBackgroundColorToModelStatic = SetBackgroundColorToModelStaticForMock,
        .setBuilderFuncToModelNG = SetBuilderFuncToModelNGForMock,
    };
    return &modifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
