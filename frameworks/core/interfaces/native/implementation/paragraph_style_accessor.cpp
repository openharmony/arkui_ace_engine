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
#include "frameworks/core/components_ng/pattern/text/span/span_object.h"
#include "frameworks/core/interfaces/native/implementation/length_metrics_peer.h"
#include "frameworks/core/interfaces/native/utility/callback_helper.h"
#include "frameworks/core/interfaces/native/utility/reverse_converter.h"
#include "paragraph_style_peer.h"

namespace OHOS::Ace::NG::Converter {
template<>
LeadingMarginSize Convert(const Ark_Tuple_Dimension_Dimension& src)
{
    return LeadingMarginSize(Convert<Dimension>(src.value0), Convert<Dimension>(src.value1));
}
template<>
OHOS::Ace::SpanParagraphStyle Convert(const Ark_ParagraphStyleInterface& src)
{
    OHOS::Ace::SpanParagraphStyle ret;
    ret.align = Converter::OptConvert<OHOS::Ace::TextAlign>(src.textAlign);
    ret.maxLines = Converter::OptConvert<int32_t>(src.maxLines);
    ret.wordBreak = Converter::OptConvert<OHOS::Ace::WordBreak>(src.wordBreak);
    ret.textOverflow = Converter::OptConvert<OHOS::Ace::TextOverflow>(src.overflow);
    ret.textIndent = Converter::OptConvert<OHOS::Ace::Dimension>(src.textIndent);

    Converter::VisitUnion(src.leadingMargin,
        [&ret](const Ark_LengthMetrics& metrics) {
            LeadingMargin margin;
            margin.size = LeadingMarginSize(metrics->value, metrics->value);
            ret.leadingMargin = margin;
        },
        [&ret](const Ark_LeadingMarginPlaceholder& inMargin) {
            ret.leadingMargin = {
                .size = Convert<LeadingMarginSize>(inMargin.size),
                .pixmap = Convert<RefPtr<PixelMap>>(inMargin.pixelMap),
            };
        },
        []() {});
    return ret;
}
} // namespace OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ParagraphStyleAccessor {
void DestroyPeerImpl(Ark_ParagraphStyle peer)
{
    CHECK_NULL_VOID(peer);
    delete peer;
}
Ark_ParagraphStyle CtorImpl(const Opt_ParagraphStyleInterface* value)
{
    auto peer = new ParagraphStylePeer();
    CHECK_NULL_RETURN(value, peer);

    SpanParagraphStyle paragraph = Converter::OptConvert<SpanParagraphStyle>(*value).value_or(SpanParagraphStyle());
    peer->span = AceType::MakeRefPtr<ParagraphStyleSpan>(paragraph);

    return peer;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_TextAlign GetTextAlignImpl(Ark_ParagraphStyle peer)
{
    Ark_TextAlign ret = Ark_TextAlign::ARK_TEXT_ALIGN_START;
    CHECK_NULL_RETURN(peer, ret);
    CHECK_NULL_RETURN(peer->span, ret);
    ret = Converter::ArkValue<Ark_TextAlign>(peer->span->GetParagraphStyle().align.value_or(TextAlign::START));
    return ret;
}
Ark_Number GetTextIndentImpl(Ark_ParagraphStyle peer)
{
    Ark_Number ret = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(peer, ret);
    CHECK_NULL_RETURN(peer->span, ret);
    auto style = peer->span->GetParagraphStyle();
    if (style.textIndent) {
        return Converter::ArkValue<Ark_Number>(style.textIndent->ConvertToPx());
    }
    return ret;
}
Ark_Number GetMaxLinesImpl(Ark_ParagraphStyle peer)
{
    Ark_Number ret = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(peer, ret);
    CHECK_NULL_RETURN(peer->span, ret);
    auto style = peer->span->GetParagraphStyle();
    if (style.maxLines) {
        return Converter::ArkValue<Ark_Number>(style.maxLines.value());
    }
    return ret;
}
Ark_TextOverflow GetOverflowImpl(Ark_ParagraphStyle peer)
{
    Ark_TextOverflow ret = Ark_TextOverflow::ARK_TEXT_OVERFLOW_NONE;
    CHECK_NULL_RETURN(peer, ret);
    CHECK_NULL_RETURN(peer->span, ret);
    auto style = peer->span->GetParagraphStyle();
    if (style.textOverflow) {
        return Converter::ArkValue<Ark_TextOverflow>(style.textOverflow.value());
    }
    return ret;
}
Ark_WordBreak GetWordBreakImpl(Ark_ParagraphStyle peer)
{
    Ark_WordBreak ret = Ark_WordBreak::ARK_WORD_BREAK_NORMAL;
    CHECK_NULL_RETURN(peer, ret);
    CHECK_NULL_RETURN(peer->span, ret);
    auto style = peer->span->GetParagraphStyle();
    if (style.wordBreak) {
        return Converter::ArkValue<Ark_WordBreak>(style.wordBreak.value());
    }
    return ret;
}
Ark_Union_Number_LeadingMarginPlaceholder GetLeadingMarginImpl(Ark_ParagraphStyle peer)
{
    CHECK_NULL_RETURN(peer, {});
    CHECK_NULL_RETURN(peer->span, {});
    auto style = peer->span->GetParagraphStyle();
    std::optional<NG::LeadingMargin>& leadingMargin = style.leadingMargin;
    if (leadingMargin) {
        return Converter::ArkUnion<Ark_Union_Number_LeadingMarginPlaceholder,
            Ark_LeadingMarginPlaceholder>(*leadingMargin);
    }
    return {};
}
} // ParagraphStyleAccessor
const GENERATED_ArkUIParagraphStyleAccessor* GetParagraphStyleAccessor()
{
    static const GENERATED_ArkUIParagraphStyleAccessor ParagraphStyleAccessorImpl {
        ParagraphStyleAccessor::DestroyPeerImpl,
        ParagraphStyleAccessor::CtorImpl,
        ParagraphStyleAccessor::GetFinalizerImpl,
        ParagraphStyleAccessor::GetTextAlignImpl,
        ParagraphStyleAccessor::GetTextIndentImpl,
        ParagraphStyleAccessor::GetMaxLinesImpl,
        ParagraphStyleAccessor::GetOverflowImpl,
        ParagraphStyleAccessor::GetWordBreakImpl,
        ParagraphStyleAccessor::GetLeadingMarginImpl,
    };
    return &ParagraphStyleAccessorImpl;
}

}
