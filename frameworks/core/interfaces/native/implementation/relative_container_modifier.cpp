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
#include "core/interfaces/arkoala/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace RelativeContainerModifier {
Ark_NativePointer ConstructImpl()
{
    return 0;
}
} // RelativeContainerModifier
namespace RelativeContainerInterfaceModifier {
void SetRelativeContainerOptionsImpl(Ark_NativePointer node)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(undefined);
    //auto convValue = Converter::OptConvert<type>(undefined); // for enums
    //RelativeContainerModelNG::SetSetRelativeContainerOptions(frameNode, convValue);
}
} // RelativeContainerInterfaceModifier
namespace RelativeContainerAttributeModifier {
void GuideLineImpl(Ark_NativePointer node,
                   const Array_GuideLineStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //RelativeContainerModelNG::SetGuideLine(frameNode, convValue);
}
void Barrier0Impl(Ark_NativePointer node,
                  const Array_BarrierStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //RelativeContainerModelNG::SetBarrier0(frameNode, convValue);
}
void Barrier1Impl(Ark_NativePointer node,
                  const Array_LocalizedBarrierStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //RelativeContainerModelNG::SetBarrier1(frameNode, convValue);
}
} // RelativeContainerAttributeModifier
const GENERATED_ArkUIRelativeContainerModifier* GetRelativeContainerModifier()
{
    static const GENERATED_ArkUIRelativeContainerModifier ArkUIRelativeContainerModifierImpl {
        RelativeContainerModifier::ConstructImpl,
        RelativeContainerInterfaceModifier::SetRelativeContainerOptionsImpl,
        RelativeContainerAttributeModifier::GuideLineImpl,
        RelativeContainerAttributeModifier::Barrier0Impl,
        RelativeContainerAttributeModifier::Barrier1Impl,
    };
    return &ArkUIRelativeContainerModifierImpl;
}

}
