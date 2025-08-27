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
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace LinearIndicatorModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
} // LinearIndicatorModifier
namespace LinearIndicatorInterfaceModifier {
void SetLinearIndicatorOptionsImpl(Ark_NativePointer node,
                                   const Opt_Number* count,
                                   const Opt_LinearIndicatorController* controller)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
} // LinearIndicatorInterfaceModifier
namespace LinearIndicatorAttributeModifier {
void IndicatorStyleImpl(Ark_NativePointer node,
                        const Opt_LinearIndicatorStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void IndicatorLoopImpl(Ark_NativePointer node,
                       const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void OnChangeImpl(Ark_NativePointer node,
                  const Opt_OnLinearIndicatorChangeCallback* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
} // LinearIndicatorAttributeModifier
const GENERATED_ArkUILinearIndicatorModifier* GetLinearIndicatorModifier()
{
    static const GENERATED_ArkUILinearIndicatorModifier ArkUILinearIndicatorModifierImpl {
        LinearIndicatorModifier::ConstructImpl,
        LinearIndicatorInterfaceModifier::SetLinearIndicatorOptionsImpl,
        LinearIndicatorAttributeModifier::IndicatorStyleImpl,
        LinearIndicatorAttributeModifier::IndicatorLoopImpl,
        LinearIndicatorAttributeModifier::OnChangeImpl,
    };
    return &ArkUILinearIndicatorModifierImpl;
}

}
