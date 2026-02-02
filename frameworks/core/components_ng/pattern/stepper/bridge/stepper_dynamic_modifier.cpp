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
#include "core/components_ng/pattern/stepper/stepper_model_ng.h"
#include "core/interfaces/arkoala/arkoala_api.h"

#ifndef CROSS_PLATFORM
namespace OHOS::Ace {
StepperModel* GetStepperModelImpl()
{
    static auto loader = DynamicModuleHelper::GetInstance().GetLoaderByName("stepper");
    static StepperModel* instance = loader ? reinterpret_cast<StepperModel*>(loader->CreateModel()) : nullptr;
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

void CreateModel(ArkUI_Uint32 index)
{
    StepperModelNG::CreateFrameNode(index);
}

void SetStepperOnFinish(ArkUINodeHandle node, void* callback)
{
    FrameNode* frameNode = GetFrameNode(node);
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
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    StepperModelNG::SetOnFinish(frameNode, nullptr);
}

void SetStepperOnSkip(ArkUINodeHandle node, void* callback)
{
    FrameNode* frameNode = GetFrameNode(node);
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
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    StepperModelNG::SetOnSkip(frameNode, nullptr);
}

void SetStepperOnChange(ArkUINodeHandle node, void* callback)
{
    FrameNode* frameNode = GetFrameNode(node);
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
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    StepperModelNG::SetOnChange(frameNode, nullptr);
}

void SetStepperOnNext(ArkUINodeHandle node, void* callback)
{
    FrameNode* frameNode = GetFrameNode(node);
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
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    StepperModelNG::SetOnNext(frameNode, nullptr);
}

void SetStepperOnPrevious(ArkUINodeHandle node, void* callback)
{
    FrameNode* frameNode = GetFrameNode(node);
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
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    StepperModelNG::SetOnPrevious(frameNode, nullptr);
}

void SetStepperOnChangeEvent(ArkUINodeHandle node, void* callback)
{
    FrameNode* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onChange = reinterpret_cast<std::function<void(int32_t)>*>(callback);
        StepperModelNG::SetOnChangeEvent(frameNode, std::move(*onChange));
    }
}

#ifndef CROSS_PLATFORM
void CreateModelImpl(ArkUI_Uint32 index)
{
    GetStepperModelImpl()->Create(index);
}

void SetStepperOnFinishImpl(ArkUINodeHandle node, void* callback)
{
    CHECK_NULL_VOID(callback);
    auto onFinish = reinterpret_cast<std::function<void()>*>(callback);
    GetStepperModelImpl()->SetOnFinish(std::move(*onFinish));
}

void SetStepperOnSkipImpl(ArkUINodeHandle node, void* callback)
{
    CHECK_NULL_VOID(callback);
    auto onSkip = reinterpret_cast<std::function<void()>*>(callback);
    GetStepperModelImpl()->SetOnSkip(std::move(*onSkip));
}

void SetStepperOnChangeImpl(ArkUINodeHandle node, void* callback)
{
    CHECK_NULL_VOID(callback);
    auto onChange = reinterpret_cast<std::function<void(int32_t, int32_t)>*>(callback);
    GetStepperModelImpl()->SetOnChange(std::move(*onChange));
}

void SetStepperOnNextImpl(ArkUINodeHandle node, void* callback)
{
    CHECK_NULL_VOID(callback);
    auto onNext = reinterpret_cast<std::function<void(int32_t, int32_t)>*>(callback);
    GetStepperModelImpl()->SetOnNext(std::move(*onNext));
}

void SetStepperOnPreviousImpl(ArkUINodeHandle node, void* callback)
{
    CHECK_NULL_VOID(callback);
    auto onPrevious = reinterpret_cast<std::function<void(int32_t, int32_t)>*>(callback);
    GetStepperModelImpl()->SetOnPrevious(std::move(*onPrevious));
}

void SetStepperOnChangeEventImpl(ArkUINodeHandle node, void* callback) {}
#endif
} // namespace

const ArkUIStepperModifier* GetStepperDynamicModifier()
{
    static bool isCurrentUseNewPipeline = Container::IsCurrentUseNewPipeline();
    if (isCurrentUseNewPipeline) {
        CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
        static const ArkUIStepperModifier modifier = {
            .createModel = CreateModel,
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
            .setStepperOnChangeEvent = SetStepperOnChangeEvent,
        };
        CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

        return &modifier;
    }
#ifdef CROSS_PLATFORM
    return nullptr;
#else
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIStepperModifier modifier = {
        .createModel = CreateModelImpl,
        .setStepperOnFinish = SetStepperOnFinishImpl,
        .resetStepperOnFinish = ResetStepperOnFinish,
        .setStepperOnSkip = SetStepperOnSkipImpl,
        .resetStepperOnSkip = ResetStepperOnSkip,
        .setStepperOnChange = SetStepperOnChangeImpl,
        .resetStepperOnChange = ResetStepperOnChange,
        .setStepperOnNext = SetStepperOnNextImpl,
        .resetStepperOnNext = ResetStepperOnNext,
        .setStepperOnPrevious = SetStepperOnPreviousImpl,
        .resetStepperOnPrevious = ResetStepperOnPrevious,
        .setStepperOnChangeEvent = SetStepperOnChangeEventImpl,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
#endif
}

} // namespace OHOS::Ace::NG
