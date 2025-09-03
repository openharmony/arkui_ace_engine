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

#include "core/interfaces/native/utility/converter.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/pattern/divider/divider_model_ng.h"
#include "arkoala_api_generated.h"
#include "core/components_ng/pattern/divider/divider_model_ng_static.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace DividerModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    auto frameNode = DividerModelNG::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // DividerModifier
namespace DividerInterfaceModifier {
void SetDividerOptionsImpl(Ark_NativePointer node)
{
    // Nothing to implement
}
} // DividerInterfaceModifier

namespace DividerAttributeModifier {
void VerticalImpl(Ark_NativePointer node,
                  const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<bool>(*value);
    if (!convValue) {
        // TODO: Reset value
        return;
    }
    DividerModelNG::SetVertical(frameNode, *convValue);
}

void ColorImpl(Ark_NativePointer node,
               const Opt_ResourceColor* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    DividerModelNGStatic::SetDividerColor(frameNode, Converter::OptConvert<Color>(*value));
}

void StrokeWidthImpl(Ark_NativePointer node,
                     const Opt_Union_Number_String* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::OptConvert<Dimension>(*value);
    if (optValue && (optValue.value().Unit() == DimensionUnit::PERCENT)) {
        optValue.reset();
    }
    DividerModelNGStatic::StrokeWidth(frameNode, optValue);
}

void LineCapImpl(Ark_NativePointer node,
                 const Opt_LineCapStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    DividerModelNGStatic::LineCap(frameNode, Converter::OptConvert<LineCap>(*value));
}

} // DividerAttributeModifier
const GENERATED_ArkUIDividerModifier* GetDividerModifier()
{
    static const GENERATED_ArkUIDividerModifier ArkUIDividerModifierImpl {
        DividerModifier::ConstructImpl,
        DividerInterfaceModifier::SetDividerOptionsImpl,
        DividerAttributeModifier::VerticalImpl,
        DividerAttributeModifier::ColorImpl,
        DividerAttributeModifier::StrokeWidthImpl,
        DividerAttributeModifier::LineCapImpl,
    };
    return &ArkUIDividerModifierImpl;
}

}
