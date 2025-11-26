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

namespace OHOS::Ace {
namespace Converter = NG::Converter;
namespace NG {
void AssignArkValue(Ark_PositionWithAffinity& dst, const PositionWithAffinity& src)
{
    dst.position = Converter::ArkValue<Ark_Int32>(static_cast<int32_t>(src.position_));
#ifdef WRONG_SDK
    dst.affinity = Converter::ArkValue<Ark_text_Affinity>(src.affinity_);
#endif
}
} // namespace NG
} // namespace OHOS::Ace

namespace OHOS::Ace::NG::GeneratedModifier {
namespace LayoutManagerAccessor {
void DestroyPeerImpl(Ark_LayoutManager peer)
{
    delete peer;
}
Ark_LayoutManager ConstructImpl()
{
    return new LayoutManagerPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Opt_Int32 GetLineCountImpl(Ark_LayoutManager peer)
{
    const auto errValue = Converter::ArkValue<Opt_Int32>(Ark_Empty());
    CHECK_NULL_RETURN(peer, errValue);
    auto handler = peer->handler.Upgrade();
    CHECK_NULL_RETURN(handler, errValue);
    int32_t count = handler->GetLineCount();
    return Converter::ArkValue<Opt_Int32>(count);
}
Opt_PositionWithAffinity GetGlyphPositionAtCoordinateImpl(Ark_LayoutManager peer,
                                                          const Ark_Float64 x,
                                                          const Ark_Float64 y)
{
    CHECK_NULL_RETURN(peer, Converter::ArkValue<Opt_PositionWithAffinity>(Ark_Empty()));
    auto handler = peer->handler.Upgrade();
    CHECK_NULL_RETURN(handler, Converter::ArkValue<Opt_PositionWithAffinity>(Ark_Empty()));
    PositionWithAffinity result = handler->GetGlyphPositionAtCoordinate(
        Converter::Convert<Ark_Float64>(x),
        Converter::Convert<Ark_Float64>(y)
    );
    return Converter::ArkValue<Opt_PositionWithAffinity>(result);
}
Opt_text_LineMetrics GetLineMetricsImpl(Ark_LayoutManager peer,
                                        Ark_Int32 lineNumber)
{
    CHECK_NULL_RETURN(peer, Converter::ArkValue<Opt_text_LineMetrics>(Ark_Empty()));
    auto handler = peer->handler.Upgrade();
    CHECK_NULL_RETURN(handler, Converter::ArkValue<Opt_text_LineMetrics>(Ark_Empty()));
    TextLineMetrics lineMetrics = handler->GetLineMetrics(Converter::Convert<int>(lineNumber));
    return Converter::ArkValue<Opt_text_LineMetrics>(lineMetrics, Converter::FC);
}
Opt_Array_text_TextBox GetRectsForRangeImpl(Ark_LayoutManager peer,
                                            const Ark_TextRange* range,
                                            Ark_text_RectWidthStyle widthStyle,
                                            Ark_text_RectHeightStyle heightStyle)
{
    CHECK_NULL_RETURN(peer, Converter::ArkValue<Opt_Array_text_TextBox>(Ark_Empty()));
    auto handler = peer->handler.Upgrade();
    CHECK_NULL_RETURN(handler, Converter::ArkValue<Opt_Array_text_TextBox>(Ark_Empty()));
    auto textRange = Converter::Convert<TextRange>(*range);
    auto dstHeightStyle = Converter::OptConvert<RectHeightStyle>(heightStyle);
    auto dstWidthStyle = Converter::OptConvert<RectWidthStyle>(widthStyle);
    CHECK_NULL_RETURN(dstHeightStyle.has_value() && dstWidthStyle.has_value(),
        Converter::ArkValue<Opt_Array_text_TextBox>(Ark_Empty()));
    std::vector<NG::ParagraphManager::TextBox> textBoxes =
        handler->GetRectsForRange(textRange.start, textRange.end, dstHeightStyle.value(), dstWidthStyle.value());
    std::vector<Ark_text_TextBox> values;
    for (const NG::ParagraphManager::TextBox& box : textBoxes) {
        auto tempBox = Converter::ArkValue<Ark_text_TextBox>(box, Converter::FC);
        values.push_back(tempBox);
    }
    return Converter::ArkValue<Opt_Array_text_TextBox>(values, Converter::FC);
}
} // LayoutManagerAccessor
const GENERATED_ArkUILayoutManagerAccessor* GetLayoutManagerAccessor()
{
    static const GENERATED_ArkUILayoutManagerAccessor LayoutManagerAccessorImpl {
        LayoutManagerAccessor::DestroyPeerImpl,
        LayoutManagerAccessor::ConstructImpl,
        LayoutManagerAccessor::GetFinalizerImpl,
        LayoutManagerAccessor::GetLineCountImpl,
        LayoutManagerAccessor::GetGlyphPositionAtCoordinateImpl,
        LayoutManagerAccessor::GetLineMetricsImpl,
        LayoutManagerAccessor::GetRectsForRangeImpl,
    };
    return &LayoutManagerAccessorImpl;
}

}
