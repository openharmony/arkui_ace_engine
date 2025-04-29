/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include "core/interfaces/native/node/stepper_item_modifier.h"

#include "core/components_ng/pattern/stepper/stepper_item_model_ng.h"

namespace OHOS::Ace::NG {
void SetNextLabel(ArkUINodeHandle node, ArkUI_CharPtr value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string rightLabel = value;
    StepperItemModelNG::SetNextLabel(frameNode, rightLabel);
}

void ResetNextLabel(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    StepperItemModelNG::ResetNextLabel(frameNode);
}

void SetPrevLabel(ArkUINodeHandle node, ArkUI_CharPtr value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string leftLabel = value;
    StepperItemModelNG::SetPrevLabel(frameNode, leftLabel);
}

void ResetPrevLabel(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    StepperItemModelNG::ResetPrevLabel(frameNode);
}

void SetStatus(ArkUINodeHandle node, ArkUI_CharPtr value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string labelStatus = value;
    StepperItemModelNG::SetStatus(frameNode, labelStatus);
}

void ResetStatus(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    StepperItemModelNG::ResetStatus(frameNode);
}
namespace NodeModifier {
const ArkUIStepperItemModifier* GetStepperItemModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIStepperItemModifier modifier = {
        .setNextLabel = SetNextLabel,
        .resetNextLabel = ResetNextLabel,
        .setPrevLabel = SetPrevLabel,
        .resetPrevLabel = ResetPrevLabel,
        .setStatus = SetStatus,
        .resetStatus = ResetStatus,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}

const CJUIStepperItemModifier* GetCJUIStepperItemModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUIStepperItemModifier modifier = {
        .setNextLabel = SetNextLabel,
        .resetNextLabel = ResetNextLabel,
        .setPrevLabel = SetPrevLabel,
        .resetPrevLabel = ResetPrevLabel,
        .setStatus = SetStatus,
        .resetStatus = ResetStatus,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}
}
} // namespace OHOS::Ace::NG
