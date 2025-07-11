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
#include "core/components_ng/pattern/text/span_model_ng.h"
#include "core/components_ng/pattern/text/span_model_static.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/validators.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ContainerSpanModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    auto spanNode = SpanModelStatic::CreateContainerSpanNode(id);
    CHECK_NULL_RETURN(spanNode, nullptr);
    spanNode->IncRefCount();
    return AceType::RawPtr(spanNode);
}
} // ContainerSpanModifier
namespace ContainerSpanInterfaceModifier {
void SetContainerSpanOptionsImpl(Ark_NativePointer node)
{
    // No implementation is required
}
} // ContainerSpanInterfaceModifier
namespace ContainerSpanAttributeModifier {
void TextBackgroundStyleImpl(Ark_NativePointer node,
                             const Opt_TextBackgroundStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<TextBackgroundStyle>(*value);
    if (!convValue) {
        // TODO: Reset value
        return;
    }
    SpanModelNG::SetTextBackgroundStyleByBaseSpan(frameNode, *convValue);
}
} // ContainerSpanAttributeModifier
const GENERATED_ArkUIContainerSpanModifier* GetContainerSpanModifier()
{
    static const GENERATED_ArkUIContainerSpanModifier ArkUIContainerSpanModifierImpl {
        ContainerSpanModifier::ConstructImpl,
        ContainerSpanInterfaceModifier::SetContainerSpanOptionsImpl,
        ContainerSpanAttributeModifier::TextBackgroundStyleImpl,
    };
    return &ArkUIContainerSpanModifierImpl;
}

}
