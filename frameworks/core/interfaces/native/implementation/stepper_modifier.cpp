/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/stepper/stepper_model_ng.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/validators.h"
#include "core/interfaces/native/utility/callback_helper.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace StepperModifier {
Ark_NativePointer ConstructImpl()
{
    return 0;
}
} // StepperModifier
namespace StepperInterfaceModifier {
void SetStepperOptionsImpl(Ark_NativePointer node,
                           const Opt_Literal_Number_index* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<int> convValue;
    auto arkConvValue = value ? Converter::OptConvert<Ark_Literal_Number_index>(*value) : std::nullopt;
    if (arkConvValue.has_value()) {
        convValue = Converter::OptConvert<int>(arkConvValue->index);
        Validator::ValidateNonNegative(convValue);
    }
    StepperModelNG::SetIndex(frameNode, convValue);
}
} // StepperInterfaceModifier
namespace StepperAttributeModifier {
void OnFinishImpl(Ark_NativePointer node,
                  const Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onFinish = [arkCallback = CallbackHelper(*value)]() { arkCallback.Invoke(); };
    StepperModelNG::SetOnFinish(frameNode, std::move(onFinish));
}
void OnSkipImpl(Ark_NativePointer node,
                const Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onSkip = [arkCallback = CallbackHelper(*value)]() { arkCallback.Invoke(); };
    StepperModelNG::SetOnSkip(frameNode, std::move(onSkip));
}
void OnChangeImpl(Ark_NativePointer node,
                  const Callback_Number_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onChange = [arkCallback = CallbackHelper(*value)](int32_t prevIndex, int32_t index) {
        arkCallback.Invoke(Converter::ArkValue<Ark_Number>(prevIndex), Converter::ArkValue<Ark_Number>(index));
    };
    StepperModelNG::SetOnChange(frameNode, std::move(onChange));
}
void OnNextImpl(Ark_NativePointer node,
                const Callback_Number_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onNext = [arkCallback = CallbackHelper(*value)](int32_t index, int32_t pendingIndex) {
        arkCallback.Invoke(Converter::ArkValue<Ark_Number>(index), Converter::ArkValue<Ark_Number>(pendingIndex));
    };
    StepperModelNG::SetOnNext(frameNode, std::move(onNext));
}
void OnPreviousImpl(Ark_NativePointer node,
                    const Callback_Number_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto onPrevious = [arkCallback = CallbackHelper(*value)](int32_t index, int32_t pendingIndex) {
        arkCallback.Invoke(Converter::ArkValue<Ark_Number>(index), Converter::ArkValue<Ark_Number>(pendingIndex));
    };
    StepperModelNG::SetOnPrevious(frameNode, std::move(onPrevious));
}
} // StepperAttributeModifier
const GENERATED_ArkUIStepperModifier* GetStepperModifier()
{
    static const GENERATED_ArkUIStepperModifier ArkUIStepperModifierImpl {
        StepperModifier::ConstructImpl,
        StepperInterfaceModifier::SetStepperOptionsImpl,
        StepperAttributeModifier::OnFinishImpl,
        StepperAttributeModifier::OnSkipImpl,
        StepperAttributeModifier::OnChangeImpl,
        StepperAttributeModifier::OnNextImpl,
        StepperAttributeModifier::OnPreviousImpl,
    };
    return &ArkUIStepperModifierImpl;
}

}
