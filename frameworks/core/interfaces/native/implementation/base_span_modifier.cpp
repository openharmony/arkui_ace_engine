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
#include "core/components_ng/pattern/text/span_model_ng.h"
#include "core/components_ng/pattern/text/span_model_static.h"
#include "core/components_ng/pattern/text/image_span_view.h"
#include "core/components_ng/pattern/text/image_span_view_static.h"
#include "core/interfaces/native/utility/validators.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace BaseSpanModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    auto frameNode = SpanModelNG::CreateSpanNode(id, u"");
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
void TextBackgroundStyleImpl(Ark_NativePointer node,
                             const Opt_TextBackgroundStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<TextBackgroundStyle>(*value);
    if (!convValue) {
        // TODO: Reset value
        TextBackgroundStyle textBackgroundStyle;
        SpanModelNG::SetTextBackgroundStyleByBaseSpan(frameNode, textBackgroundStyle);
        return;
    }
    if (AceType::TypeId(frameNode) == SpanNode::TypeId()) {
        SpanModelNG::SetTextBackgroundStyleByBaseSpan(frameNode, *convValue);
    } else {
        ImageSpanView::SetPlaceHolderStyle(frameNode, *convValue);
    }
}
void BaselineOffsetImpl(Ark_NativePointer node,
                        const Opt_LengthMetrics* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvert<Dimension>(*value);
    Validator::ValidateNonPercent(convValue);
    if (AceType::TypeId(frameNode) == SpanNode::TypeId()) {
        SpanModelStatic::SetBaselineOffset(frameNode, convValue);
    } else {
        ImageSpanViewStatic::SetBaselineOffset(frameNode, convValue);
    }
}
} // BaseSpanModifier
const GENERATED_ArkUIBaseSpanModifier* GetBaseSpanModifier()
{
    static const GENERATED_ArkUIBaseSpanModifier ArkUIBaseSpanModifierImpl {
        BaseSpanModifier::ConstructImpl,
        BaseSpanModifier::TextBackgroundStyleImpl,
        BaseSpanModifier::BaselineOffsetImpl,
    };
    return &ArkUIBaseSpanModifierImpl;
}

}
