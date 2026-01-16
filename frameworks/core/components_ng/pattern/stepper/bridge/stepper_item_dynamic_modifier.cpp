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

#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/common/dynamic_module_helper.h"
#include "core/components_ng/pattern/stepper/stepper_item_model_ng.h"
#include "core/interfaces/native/node/stepper_item_modifier.h"

#ifndef CROSS_PLATFORM
namespace OHOS::Ace {
StepperItemModel* GetStepperItemModelImpl()
{
    static auto loader = DynamicModuleHelper::GetInstance().GetLoaderByName("stepper-item");
    static StepperItemModel* instance = loader ? reinterpret_cast<StepperItemModel*>(loader->CreateModel()) : nullptr;
    return instance;
}
} // namespace OHOS::Ace
#endif

namespace OHOS::Ace::NG {
namespace {
FrameNode* GetFrameNode(ArkUINodeHandle node)
{
    return node ? reinterpret_cast<FrameNode*>(node) : ViewStackProcessor::GetInstance()->GetMainFrameNode();
}

void CreateModel()
{
    StepperItemModelNG::CreateFrameNode();
}

void SetNextLabel(ArkUINodeHandle node, ArkUI_CharPtr value)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    std::string rightLabel = value;
    StepperItemModelNG::SetNextLabel(frameNode, rightLabel);
}

void ResetNextLabel(ArkUINodeHandle node)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    StepperItemModelNG::ResetNextLabel(frameNode);
}

void SetPrevLabel(ArkUINodeHandle node, ArkUI_CharPtr value)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    std::string leftLabel = value;
    StepperItemModelNG::SetPrevLabel(frameNode, leftLabel);
}

void ResetPrevLabel(ArkUINodeHandle node)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    StepperItemModelNG::ResetPrevLabel(frameNode);
}

void SetStatus(ArkUINodeHandle node, ArkUI_CharPtr value)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    std::string labelStatus = value;
    StepperItemModelNG::SetStatus(frameNode, labelStatus);
}

void ResetStatus(ArkUINodeHandle node)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    StepperItemModelNG::ResetStatus(frameNode);
}

#ifndef CROSS_PLATFORM
void CreateModelImpl()
{
    GetStepperItemModelImpl()->Create();
}

void SetNextLabelImpl(ArkUINodeHandle node, ArkUI_CharPtr value)
{
    CHECK_NULL_VOID(value);
    GetStepperItemModelImpl()->SetNextLabel(value);
}

void SetPrevLabelImpl(ArkUINodeHandle node, ArkUI_CharPtr value)
{
    CHECK_NULL_VOID(value);
    GetStepperItemModelImpl()->SetPrevLabel(value);
}

void SetStatusImpl(ArkUINodeHandle node, ArkUI_CharPtr value)
{
    CHECK_NULL_VOID(value);
    GetStepperItemModelImpl()->SetStatus(value);
}
#endif
} // namespace

const ArkUIStepperItemModifier* GetStepperItemDynamicModifier()
{
    static bool isCurrentUseNewPipeline = Container::IsCurrentUseNewPipeline();
    if (isCurrentUseNewPipeline) {
        CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
        static const ArkUIStepperItemModifier modifier = {
            .createModel = CreateModel,
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
#ifdef CROSS_PLATFORM
    return nullptr;
#else
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIStepperItemModifier modifier = {
        .createModel = CreateModelImpl,
        .setNextLabel = SetNextLabelImpl,
        .resetNextLabel = ResetNextLabel,
        .setPrevLabel = SetPrevLabelImpl,
        .resetPrevLabel = ResetPrevLabel,
        .setStatus = SetStatusImpl,
        .resetStatus = ResetStatus,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
#endif
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
} // namespace OHOS::Ace::NG
