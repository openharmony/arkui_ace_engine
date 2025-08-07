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
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"
#include "layout_manager_peer_impl.h"

namespace OHOS::Ace::NG::Converter {
void AssignArkValue(Ark_TextDirection& dst, const Ace::TextDirection& src)
{
    switch (src) {
        case Ace::TextDirection::LTR: dst = Ark_TextDirection::ARK_TEXT_DIRECTION_LTR; break;
        case Ace::TextDirection::RTL: dst = Ark_TextDirection::ARK_TEXT_DIRECTION_RTL; break;
        default:
            dst = static_cast<Ark_TextDirection>(-1);
            LOGE("Unexpected enum value in Ark_TextDirection: %{public}d", src);
            break;
    }
}
void AssignArkValue(Ark_Rect& dst, const RectF& src)
{
    dst.left = ArkValue<Ark_Number>(src.GetX());
    dst.top = ArkValue<Ark_Number>(src.GetY());
    dst.right = ArkValue<Ark_Number>(src.Right());
    dst.bottom = ArkValue<Ark_Number>(src.Bottom());
}
void AssignArkValue(Ark_TextBox& dst, const ParagraphManager::TextBox& src)
{
    dst.rect = Converter::ArkValue<Ark_Rect>(src.rect_);
    dst.direction = Converter::ArkValue<Ark_TextDirection>(src.direction_);
}
void AssignArkValue(Ark_Affinity& dst, const Ace::TextAffinity& src)
{
    switch (src) {
        case Ace::TextAffinity::UPSTREAM: dst = Ark_Affinity::ARK_AFFINITY_UPSTREAM; break;
        case Ace::TextAffinity::DOWNSTREAM: dst = Ark_Affinity::ARK_AFFINITY_DOWNSTREAM; break;
        default:
            dst = static_cast<Ark_Affinity>(-1);
            LOGE("Unexpected enum value in Ark_Affinity: %{public}d", src);
            break;
    }
}
void AssignArkValue(Ark_PositionWithAffinity& dst, const PositionWithAffinity& src)
{
    dst.position = Converter::ArkValue<Ark_Number>(static_cast<int32_t>(src.position_));
    dst.affinity = Converter::ArkValue<Ark_Affinity>(src.affinity_);
}
void AssignArkValue(Ark_LineMetrics& dst, const TextLineMetrics& src)
{
    dst.startIndex = Converter::ArkValue<Ark_Number>(static_cast<int32_t>(src.startIndex));
    dst.endIndex = Converter::ArkValue<Ark_Number>(static_cast<int32_t>(src.endIndex));
    dst.ascent = Converter::ArkValue<Ark_Number>(src.ascender);
    dst.descent = Converter::ArkValue<Ark_Number>(src.descender);
    dst.height = Converter::ArkValue<Ark_Number>(src.height);
    dst.left = Converter::ArkValue<Ark_Number>(src.x);
    dst.baseline = Converter::ArkValue<Ark_Number>(src.baseline);
    dst.lineNumber = Converter::ArkValue<Ark_Number>(static_cast<int32_t>(src.lineNumber));
    dst.topHeight = Converter::ArkValue<Ark_Number>(src.y);
    // Map_Number_RunMetrics runMetrics not implemented because Ark_RunMetrics is not supported
}
} // namespace OHOS::Ace::NG::Converter
namespace OHOS::Ace::NG::GeneratedModifier {
namespace LayoutManagerAccessor {
void DestroyPeerImpl(Ark_LayoutManager peer)
{
    delete peer;
}
Ark_LayoutManager CtorImpl()
{
    return new LayoutManagerPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_Number GetLineCountImpl(Ark_LayoutManager peer)
{
    const auto errValue = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(peer, errValue);
    auto handler = peer->handler.Upgrade();
    CHECK_NULL_RETURN(handler, errValue);
    int32_t count = handler->GetLineCount();
    return Converter::ArkValue<Ark_Number>(count);
}
Ark_PositionWithAffinity GetGlyphPositionAtCoordinateImpl(Ark_LayoutManager peer,
                                                          const Ark_Number* x,
                                                          const Ark_Number* y)
{
    CHECK_NULL_RETURN(peer && x && y, {});
    auto handler = peer->handler.Upgrade();
    CHECK_NULL_RETURN(handler, {});
    PositionWithAffinity result = handler->GetGlyphPositionAtCoordinate(
        Converter::Convert<int32_t>(*x),
        Converter::Convert<int32_t>(*y)
    );
    return Converter::ArkValue<Ark_PositionWithAffinity>(result);
}
Ark_LineMetrics GetLineMetricsImpl(Ark_LayoutManager peer,
                                   const Ark_Number* lineNumber)
{
    CHECK_NULL_RETURN(peer && lineNumber, {});
    auto handler = peer->handler.Upgrade();
    CHECK_NULL_RETURN(handler, {});
    TextLineMetrics result = handler->GetLineMetrics(Converter::Convert<int32_t>(*lineNumber));
    LOGE("LayoutManagerAccessor::GetLineMetricsImpl Map_Number_RunMetrics not implemented"
        "because Ark_RunMetrics is not supported");
    return Converter::ArkValue<Ark_LineMetrics>(result);
}
Array_TextBox GetRectsForRangeImpl(Ark_LayoutManager peer,
                                   const Ark_TextRange* range,
                                   Ark_RectWidthStyle widthStyle,
                                   Ark_RectHeightStyle heightStyle)
{
    CHECK_NULL_RETURN(peer, {});
    CHECK_NULL_RETURN(range, {});
    auto handler = peer->handler.Upgrade();
    CHECK_NULL_RETURN(handler, {});
    auto start = Converter::Convert<int32_t>(range->start.value);
    auto end = Converter::Convert<int32_t>(range->end.value);
    auto heightSt = Converter::OptConvert<RectHeightStyle>(heightStyle);
    auto widthSt = Converter::OptConvert<RectWidthStyle>(widthStyle);
    std::vector<ParagraphManager::TextBox> rects;
    rects = handler->GetRectsForRange(
        start,
        end,
        heightSt.value_or(RectHeightStyle::TIGHT),
        widthSt.value_or(RectWidthStyle::TIGHT));
    return Converter::ArkValue<Array_TextBox>(rects, Converter::FC);
}
} // LayoutManagerAccessor
const GENERATED_ArkUILayoutManagerAccessor* GetLayoutManagerAccessor()
{
    static const GENERATED_ArkUILayoutManagerAccessor LayoutManagerAccessorImpl {
        LayoutManagerAccessor::DestroyPeerImpl,
        LayoutManagerAccessor::CtorImpl,
        LayoutManagerAccessor::GetFinalizerImpl,
        LayoutManagerAccessor::GetLineCountImpl,
        LayoutManagerAccessor::GetGlyphPositionAtCoordinateImpl,
        LayoutManagerAccessor::GetLineMetricsImpl,
        LayoutManagerAccessor::GetRectsForRangeImpl,
    };
    return &LayoutManagerAccessorImpl;
}

}
