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
namespace IndicatorComponentModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
} // IndicatorComponentModifier
namespace IndicatorComponentInterfaceModifier {
void SetIndicatorComponentOptionsImpl(Ark_NativePointer node,
                                      const Opt_IndicatorComponentController* controller)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
} // IndicatorComponentInterfaceModifier
namespace IndicatorComponentAttributeModifier {
void InitialIndexImpl(Ark_NativePointer node,
                      const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void CountImpl(Ark_NativePointer node,
               const Opt_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void StyleImpl(Ark_NativePointer node,
               const Opt_Union_DotIndicator_DigitIndicator* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void LoopImpl(Ark_NativePointer node,
              const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void VerticalImpl(Ark_NativePointer node,
                  const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
void OnChangeImpl(Ark_NativePointer node,
                  const Opt_Callback_Number_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
}
} // IndicatorComponentAttributeModifier
const GENERATED_ArkUIIndicatorComponentModifier* GetIndicatorComponentModifier()
{
    static const GENERATED_ArkUIIndicatorComponentModifier ArkUIIndicatorComponentModifierImpl {
        IndicatorComponentModifier::ConstructImpl,
        IndicatorComponentInterfaceModifier::SetIndicatorComponentOptionsImpl,
        IndicatorComponentAttributeModifier::InitialIndexImpl,
        IndicatorComponentAttributeModifier::CountImpl,
        IndicatorComponentAttributeModifier::StyleImpl,
        IndicatorComponentAttributeModifier::LoopImpl,
        IndicatorComponentAttributeModifier::VerticalImpl,
        IndicatorComponentAttributeModifier::OnChangeImpl,
    };
    return &ArkUIIndicatorComponentModifierImpl;
}

}
