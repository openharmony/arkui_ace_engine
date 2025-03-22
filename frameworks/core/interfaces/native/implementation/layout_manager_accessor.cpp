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

namespace OHOS::Ace::NG::GeneratedModifier {
namespace LayoutManagerAccessor {
void DestroyPeerImpl(Ark_LayoutManager peer)
{
    CHECK_NULL_VOID(peer);
    peer->handler = nullptr;
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
    LOGE("LayoutManagerAccessor::GetLineMetricsImpl Incorrect return value type.");
    return {};
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
    LOGE("LayoutManagerAccessor::GetRectsForRangeImpl No return value specified.");
    return {};
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
