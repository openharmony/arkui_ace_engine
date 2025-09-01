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
#include "core/components_ng/pattern/stepper/stepper_item_model_static.h"
#include "core/interfaces/native/utility/converter.h"

namespace OHOS::Ace::NG::Converter {
template<>
void AssignCast(std::optional<StepperItemModelStatic::ItemState>& dst, const Ark_ItemState& src)
{
    switch (src) {
        case ARK_ITEM_STATE_NORMAL: dst = StepperItemModelStatic::ItemState::NORMAL; break;
        case ARK_ITEM_STATE_DISABLED: dst = StepperItemModelStatic::ItemState::DISABLED; break;
        case ARK_ITEM_STATE_WAITING: dst = StepperItemModelStatic::ItemState::WAITING; break;
        case ARK_ITEM_STATE_SKIP: dst = StepperItemModelStatic::ItemState::SKIP; break;
        default: LOGE("Unexpected enum value in Ark_ItemState: %{public}d", src);
    }
}
}
namespace OHOS::Ace::NG::GeneratedModifier {
namespace StepperItemModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    auto frameNode = StepperItemModelStatic::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // StepperItemModifier
namespace StepperItemInterfaceModifier {
void SetStepperItemOptionsImpl(Ark_NativePointer node)
{
    // No implementation is required
}
} // StepperItemInterfaceModifier
namespace StepperItemAttributeModifier {
void SetPrevLabelImpl(Ark_NativePointer node,
                      const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    if (value->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        StepperItemModelStatic::ResetPrevLabel(frameNode);
        return;
    }
    auto convValue = Converter::Convert<std::string>(value->value);
    StepperItemModelStatic::SetPrevLabel(frameNode, convValue);
}
void SetNextLabelImpl(Ark_NativePointer node,
                      const Opt_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    if (value->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        StepperItemModelStatic::ResetNextLabel(frameNode);
        return;
    }
    auto convValue = Converter::Convert<std::string>(value->value);
    StepperItemModelStatic::SetNextLabel(frameNode, convValue);
}
void SetStatusImpl(Ark_NativePointer node,
                   const Opt_ItemState* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    if (value->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        StepperItemModelStatic::SetStatus(
            frameNode, StepperItemModelStatic::ITEM_STATE.at(StepperItemModelStatic::ItemState::NORMAL));
        return;
    }
    auto convValue = Converter::OptConvertPtr<StepperItemModelStatic::ItemState>(value);
    if (convValue.has_value()) {
        StepperItemModelStatic::SetStatus(frameNode, StepperItemModelStatic::ITEM_STATE.at(convValue.value()));
    } else {
        StepperItemModelStatic::SetStatus(frameNode, std::nullopt);
    }
}
} // StepperItemAttributeModifier
const GENERATED_ArkUIStepperItemModifier* GetStepperItemModifier()
{
    static const GENERATED_ArkUIStepperItemModifier ArkUIStepperItemModifierImpl {
        StepperItemModifier::ConstructImpl,
        StepperItemInterfaceModifier::SetStepperItemOptionsImpl,
        StepperItemAttributeModifier::SetPrevLabelImpl,
        StepperItemAttributeModifier::SetNextLabelImpl,
        StepperItemAttributeModifier::SetStatusImpl,
    };
    return &ArkUIStepperItemModifierImpl;
}

}
