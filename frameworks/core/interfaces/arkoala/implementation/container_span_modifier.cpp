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
#include "core/components_ng/pattern/text/span_model_ng.h"
#include "core/interfaces/arkoala/utility/converter.h"
#include "core/interfaces/arkoala/utility/validators.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::Converter {
    template<>
    TextBackgroundStyle Convert(const Ark_TextBackgroundStyle& src)
    {
        TextBackgroundStyle dst;
        dst.backgroundColor = Converter::OptConvert<Color>(src.color);
        dst.backgroundRadius = Converter::OptConvert<NG::BorderRadiusProperty>(src.radius);
        if (dst.backgroundRadius.has_value()) {
            Validator::ValidateNonPercent(dst.backgroundRadius->radiusTopLeft);
            Validator::ValidateNonPercent(dst.backgroundRadius->radiusTopRight);
            Validator::ValidateNonPercent(dst.backgroundRadius->radiusBottomLeft);
            Validator::ValidateNonPercent(dst.backgroundRadius->radiusBottomRight);            
        }
        return dst;
    }
}

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ContainerSpanInterfaceModifier {
void SetContainerSpanOptionsImpl(Ark_NativePointer node)
{
    // No implementation is required
}
} // ContainerSpanInterfaceModifier
namespace ContainerSpanAttributeModifier {
void TextBackgroundStyleImpl(Ark_NativePointer node,
                             const Ark_TextBackgroundStyle* style)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(style);
    auto convValue = Converter::Convert<TextBackgroundStyle>(*style);
    SpanModelNG::SetTextBackgroundStyleByBaseSpan(frameNode, convValue);
}
} // ContainerSpanAttributeModifier
const GENERATED_ArkUIContainerSpanModifier* GetContainerSpanModifier()
{
    static const GENERATED_ArkUIContainerSpanModifier ArkUIContainerSpanModifierImpl {
        ContainerSpanInterfaceModifier::SetContainerSpanOptionsImpl,
        ContainerSpanAttributeModifier::TextBackgroundStyleImpl,
    };
    return &ArkUIContainerSpanModifierImpl;
}

}