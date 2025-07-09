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
#include "core/components_ng/pattern/stepper/stepper_item_model_ng.h"
#include "core/interfaces/native/utility/converter.h"

namespace OHOS::Ace::NG::Converter {
}
namespace OHOS::Ace::NG::GeneratedModifier {
namespace StepperItemModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return nullptr;
}
} // StepperItemModifier
namespace StepperItemInterfaceModifier {
void SetStepperItemOptionsImpl(Ark_NativePointer node)
{
    // No implementation is required
}
} // StepperItemInterfaceModifier
namespace StepperItemAttributeModifier {
void PrevLabelImpl(Ark_NativePointer node,
                   const Ark_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::Convert<std::string>(*value);
    StepperItemModelNG::SetPrevLabel(frameNode, convValue);
}
void NextLabelImpl(Ark_NativePointer node,
                   const Ark_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::Convert<std::string>(*value);
    StepperItemModelNG::SetNextLabel(frameNode, convValue);
}
void StatusImpl(Ark_NativePointer node,
                const Opt_ItemState* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
} // StepperItemAttributeModifier
const GENERATED_ArkUIStepperItemModifier* GetStepperItemModifier()
{
    static const GENERATED_ArkUIStepperItemModifier ArkUIStepperItemModifierImpl {
        StepperItemModifier::ConstructImpl,
        StepperItemInterfaceModifier::SetStepperItemOptionsImpl,
        StepperItemAttributeModifier::PrevLabelImpl,
        StepperItemAttributeModifier::NextLabelImpl,
        StepperItemAttributeModifier::StatusImpl,
    };
    return &ArkUIStepperItemModifierImpl;
}

}
