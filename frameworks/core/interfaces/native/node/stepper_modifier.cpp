/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#include "core/interfaces/native/node/stepper_modifier.h"

#include "core/components_ng/pattern/stepper/stepper_model_ng.h"

namespace OHOS::Ace::NG {
void SetStepperOnFinish(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onFinish = reinterpret_cast<std::function<void()>*>(callback);
        StepperModelNG::SetOnFinish(frameNode, std::move(*onFinish));
    } else {
        StepperModelNG::SetOnFinish(frameNode, nullptr);
    }
}

void ResetStepperOnFinish(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    StepperModelNG::SetOnFinish(frameNode, nullptr);
}

void SetStepperOnSkip(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onSkip = reinterpret_cast<std::function<void()>*>(callback);
        StepperModelNG::SetOnSkip(frameNode, std::move(*onSkip));
    } else {
        StepperModelNG::SetOnSkip(frameNode, nullptr);
    }
}

void ResetStepperOnSkip(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    StepperModelNG::SetOnSkip(frameNode, nullptr);
}

void SetStepperOnChange(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onChange = reinterpret_cast<std::function<void(int32_t, int32_t)>*>(callback);
        StepperModelNG::SetOnChange(frameNode, std::move(*onChange));
    } else {
        StepperModelNG::SetOnChange(frameNode, nullptr);
    }
}

void ResetStepperOnChange(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    StepperModelNG::SetOnChange(frameNode, nullptr);
}

void SetStepperOnNext(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onNext = reinterpret_cast<std::function<void(int32_t, int32_t)>*>(callback);
        StepperModelNG::SetOnNext(frameNode, std::move(*onNext));
    } else {
        StepperModelNG::SetOnNext(frameNode, nullptr);
    }
}

void ResetStepperOnNext(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    StepperModelNG::SetOnNext(frameNode, nullptr);
}

void SetStepperOnPrevious(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onPrevious = reinterpret_cast<std::function<void(int32_t, int32_t)>*>(callback);
        StepperModelNG::SetOnPrevious(frameNode, std::move(*onPrevious));
    } else {
        StepperModelNG::SetOnPrevious(frameNode, nullptr);
    }
}

void ResetStepperOnPrevious(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    StepperModelNG::SetOnPrevious(frameNode, nullptr);
}

namespace NodeModifier {
const ArkUIStepperModifier* GetStepperModifier()
{
    static const ArkUIStepperModifier modifier = {
        .setStepperOnFinish = SetStepperOnFinish,
        .resetStepperOnFinish = ResetStepperOnFinish,
        .setStepperOnSkip = SetStepperOnSkip,
        .resetStepperOnSkip = ResetStepperOnSkip,
        .setStepperOnChange = SetStepperOnChange,
        .resetStepperOnChange = ResetStepperOnChange,
        .setStepperOnNext = SetStepperOnNext,
        .resetStepperOnNext = ResetStepperOnNext,
        .setStepperOnPrevious = SetStepperOnPrevious,
        .resetStepperOnPrevious = ResetStepperOnPrevious,
    };

    return &modifier;
}

} // namespace NodeModifier
} // namespace OHOS::Ace::NG
