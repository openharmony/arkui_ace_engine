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
Opt_TextAlign GetTextAlignImpl(Ark_ParagraphStyle peer)
{
    auto invalid = Converter::ArkValue<Opt_TextAlign>();
    CHECK_NULL_RETURN(peer, invalid);
    CHECK_NULL_RETURN(peer->span, invalid);
    return Converter::ArkValue<Opt_TextAlign>(peer->span->GetParagraphStyle().align);
}
Opt_Number GetTextIndentImpl(Ark_ParagraphStyle peer)
{
    auto invalid = Converter::ArkValue<Opt_Number>();
    CHECK_NULL_RETURN(peer, invalid);
    CHECK_NULL_RETURN(peer->span, invalid);
    auto style = peer->span->GetParagraphStyle();
    if (style.textIndent) {
        return Converter::ArkValue<Opt_Number>(style.textIndent->ConvertToPx());
    }
    return invalid;
}
Opt_Number GetMaxLinesImpl(Ark_ParagraphStyle peer)
{
    auto invalid = Converter::ArkValue<Opt_Number>();
    CHECK_NULL_RETURN(peer, invalid);
    CHECK_NULL_RETURN(peer->span, invalid);
    auto style = peer->span->GetParagraphStyle();
    return Converter::ArkValue<Opt_Number>(style.maxLines);
}
Opt_TextOverflow GetOverflowImpl(Ark_ParagraphStyle peer)
{
    auto invalid = Converter::ArkValue<Opt_TextOverflow>();
    CHECK_NULL_RETURN(peer, invalid);
    CHECK_NULL_RETURN(peer->span, invalid);
    auto style = peer->span->GetParagraphStyle();
    return Converter::ArkValue<Opt_TextOverflow>(style.textOverflow);
}
Opt_WordBreak GetWordBreakImpl(Ark_ParagraphStyle peer)
{
    auto invalid = Converter::ArkValue<Opt_WordBreak>();
    CHECK_NULL_RETURN(peer, invalid);
    CHECK_NULL_RETURN(peer->span, invalid);
    auto style = peer->span->GetParagraphStyle();
    return Converter::ArkValue<Opt_WordBreak>(style.wordBreak);
}
Opt_Union_Number_LeadingMarginPlaceholder GetLeadingMarginImpl(Ark_ParagraphStyle peer)
{
    auto invalid = Converter::ArkValue<Opt_Union_Number_LeadingMarginPlaceholder>();
    CHECK_NULL_RETURN(peer, invalid);
    CHECK_NULL_RETURN(peer->span, invalid);
    auto style = peer->span->GetParagraphStyle();
    return Converter::ArkUnion<Opt_Union_Number_LeadingMarginPlaceholder,
        Ark_LeadingMarginPlaceholder>(style.leadingMargin);
}
Opt_Number GetParagraphSpacingImpl(Ark_ParagraphStyle peer)
{
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
        ParagraphStyleAccessor::GetParagraphSpacingImpl,
    };
    return &ParagraphStyleAccessorImpl;
}

}
