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
namespace ScrollableCommonMethodModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
void ScrollBarImpl(Ark_NativePointer node,
                   const Opt_BarState* value)
{
}
void ScrollBarColorImpl(Ark_NativePointer node,
                        const Opt_Union_Color_Number_String* value)
{
}
void ScrollBarWidthImpl(Ark_NativePointer node,
                        const Opt_Union_Number_String* value)
{
}
void NestedScrollImpl(Ark_NativePointer node,
                      const Opt_NestedScrollOptions* value)
{
}
void EnableScrollInteractionImpl(Ark_NativePointer node,
                                 const Opt_Boolean* value)
{
}
void FrictionImpl(Ark_NativePointer node,
                  const Opt_Union_Number_Resource* value)
{
}
void OnScrollImpl(Ark_NativePointer node,
                  const Opt_Callback_Number_Number_Void* value)
{
}
void OnReachStartImpl(Ark_NativePointer node,
                      const Opt_Callback_Void* value)
{
}
void OnReachEndImpl(Ark_NativePointer node,
                    const Opt_Callback_Void* value)
{
}
void OnScrollStartImpl(Ark_NativePointer node,
                       const Opt_Callback_Void* value)
{
}
void OnScrollStopImpl(Ark_NativePointer node,
                      const Opt_Callback_Void* value)
{
}
void FlingSpeedLimitImpl(Ark_NativePointer node,
                         const Opt_Number* value)
{
}
void ClipContentImpl(Ark_NativePointer node,
                     const Opt_Union_ContentClipMode_RectShape* value)
{
}
void DigitalCrownSensitivityImpl(Ark_NativePointer node,
                                 const Opt_CrownSensitivity* value)
{
}
void BackToTopImpl(Ark_NativePointer node,
                   const Opt_Boolean* value)
{
}
void EdgeEffectImpl(Ark_NativePointer node,
                    const Opt_EdgeEffect* edgeEffect,
                    const Opt_EdgeEffectOptions* options)
{
}
void FadingEdgeImpl(Ark_NativePointer node,
                    const Opt_Boolean* enabled,
                    const Opt_FadingEdgeOptions* options)
{
}
} // ScrollableCommonMethodModifier
const GENERATED_ArkUIScrollableCommonMethodModifier* GetScrollableCommonMethodModifier()
{
    static const GENERATED_ArkUIScrollableCommonMethodModifier ArkUIScrollableCommonMethodModifierImpl {
        ScrollableCommonMethodModifier::ConstructImpl,
        ScrollableCommonMethodModifier::ScrollBarImpl,
        ScrollableCommonMethodModifier::ScrollBarColorImpl,
        ScrollableCommonMethodModifier::ScrollBarWidthImpl,
        ScrollableCommonMethodModifier::NestedScrollImpl,
        ScrollableCommonMethodModifier::EnableScrollInteractionImpl,
        ScrollableCommonMethodModifier::FrictionImpl,
        ScrollableCommonMethodModifier::OnScrollImpl,
        ScrollableCommonMethodModifier::OnReachStartImpl,
        ScrollableCommonMethodModifier::OnReachEndImpl,
        ScrollableCommonMethodModifier::OnScrollStartImpl,
        ScrollableCommonMethodModifier::OnScrollStopImpl,
        ScrollableCommonMethodModifier::FlingSpeedLimitImpl,
        ScrollableCommonMethodModifier::ClipContentImpl,
        ScrollableCommonMethodModifier::DigitalCrownSensitivityImpl,
        ScrollableCommonMethodModifier::BackToTopImpl,
        ScrollableCommonMethodModifier::EdgeEffectImpl,
        ScrollableCommonMethodModifier::FadingEdgeImpl,
    };
    return &ArkUIScrollableCommonMethodModifierImpl;
}

}
