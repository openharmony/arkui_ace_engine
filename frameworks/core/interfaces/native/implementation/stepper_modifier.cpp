/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/stepper/stepper_model_static.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/validators.h"
#include "core/interfaces/native/utility/callback_helper.h"

namespace OHOS::Ace::NG {
namespace {
std::optional<int32_t> ProcessBindableIndex(FrameNode* frameNode, const Opt_Union_I32_Bindable& value)
{
    std::optional<int32_t> result;
    Converter::VisitUnion(value,
        [&result](const Ark_Int32& src) {
            result = Converter::Convert<int32_t>(src);
        },
        [&result, frameNode](const Ark_Bindable_I32& src) {
            result = Converter::Convert<float>(src.value);
            WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
            auto onEvent = [arkCallback = CallbackHelper(src.onChange), weakNode](int32_t value) {
                PipelineContext::SetCallBackNode(weakNode);
                arkCallback.Invoke(Converter::ArkValue<Ark_Int32>(value));
            };
            StepperModelStatic::SetOnChangeEvent(frameNode, std::move(onEvent));
        },
        [] {});
    return result;
}
} // namespace
} // namespace OHOS::Ace::NG

namespace OHOS::Ace::NG::GeneratedModifier {
namespace StepperModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    auto frameNode = StepperModelStatic::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // StepperModifier
namespace StepperInterfaceModifier {
void SetStepperOptionsImpl(Ark_NativePointer node,
                           const Opt_StepperOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    auto convValue = optValue ? ProcessBindableIndex(frameNode, optValue->index) : std::nullopt;
    Validator::ValidateNonNegative(convValue);
    StepperModelStatic::SetIndex(frameNode, convValue);
}
} // StepperInterfaceModifier
namespace StepperAttributeModifier {
void SetOnFinishImpl(Ark_NativePointer node,
                     const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        StepperModelStatic::SetOnFinish(frameNode, nullptr);
        return;
    }
    auto onFinish = [arkCallback = CallbackHelper(*optValue)]() { arkCallback.Invoke(); };
    StepperModelStatic::SetOnFinish(frameNode, std::move(onFinish));
}
void SetOnSkipImpl(Ark_NativePointer node,
                   const Opt_Callback_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        StepperModelStatic::SetOnSkip(frameNode, nullptr);
        return;
    }
    auto onSkip = [arkCallback = CallbackHelper(*optValue)]() { arkCallback.Invoke(); };
    StepperModelStatic::SetOnSkip(frameNode, std::move(onSkip));
}
void SetOnChangeImpl(Ark_NativePointer node,
                     const Opt_Callback_I32_I32_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        StepperModelStatic::SetOnChange(frameNode, nullptr);
        return;
    }
    auto onChange = [arkCallback = CallbackHelper(*optValue)](int32_t prevIndex, int32_t index) {
        arkCallback.Invoke(Converter::ArkValue<Ark_Int32>(prevIndex), Converter::ArkValue<Ark_Int32>(index));
    };
    StepperModelStatic::SetOnChange(frameNode, std::move(onChange));
}
void SetOnNextImpl(Ark_NativePointer node,
                   const Opt_Callback_I32_I32_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        StepperModelStatic::SetOnNext(frameNode, nullptr);
        return;
    }
    auto onNext = [arkCallback = CallbackHelper(*optValue)](int32_t index, int32_t pendingIndex) {
        arkCallback.Invoke(Converter::ArkValue<Ark_Int32>(index), Converter::ArkValue<Ark_Int32>(pendingIndex));
    };
    StepperModelStatic::SetOnNext(frameNode, std::move(onNext));
}
void SetOnPreviousImpl(Ark_NativePointer node,
                       const Opt_Callback_I32_I32_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        StepperModelStatic::SetOnPrevious(frameNode, nullptr);
        return;
    }
    auto onPrevious = [arkCallback = CallbackHelper(*optValue)](int32_t index, int32_t pendingIndex) {
        arkCallback.Invoke(Converter::ArkValue<Ark_Int32>(index), Converter::ArkValue<Ark_Int32>(pendingIndex));
    };
    StepperModelStatic::SetOnPrevious(frameNode, std::move(onPrevious));
}
} // StepperAttributeModifier
const GENERATED_ArkUIStepperModifier* GetStepperModifier()
{
    static const GENERATED_ArkUIStepperModifier ArkUIStepperModifierImpl {
        StepperModifier::ConstructImpl,
        StepperInterfaceModifier::SetStepperOptionsImpl,
        StepperAttributeModifier::SetOnFinishImpl,
        StepperAttributeModifier::SetOnSkipImpl,
        StepperAttributeModifier::SetOnChangeImpl,
        StepperAttributeModifier::SetOnNextImpl,
        StepperAttributeModifier::SetOnPreviousImpl,
    };
    return &ArkUIStepperModifierImpl;
}

}
