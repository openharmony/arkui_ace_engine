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
void AssignArkValue(Ark_text_TextDirection& dst, const Ace::TextDirection& src)
{
    switch (src) {
        case Ace::TextDirection::LTR: dst = ARK_TEXT_TEXT_DIRECTION_LTR; break;
        case Ace::TextDirection::RTL: dst = ARK_TEXT_TEXT_DIRECTION_RTL; break;
        default:
            dst = static_cast<Ark_text_TextDirection>(-1);
            LOGE("Unexpected enum value in Ark_text_TextDirection: %{public}d", src);
            break;
    }
}
void AssignArkValue(Ark_text_Affinity& dst, const Ace::TextAffinity& src)
{
    switch (src) {
        case Ace::TextAffinity::UPSTREAM: dst = ARK_TEXT_AFFINITY_UPSTREAM; break;
        case Ace::TextAffinity::DOWNSTREAM: dst = ARK_TEXT_AFFINITY_DOWNSTREAM; break;
        default:
            dst = static_cast<Ark_text_Affinity>(-1);
            LOGE("Unexpected enum value in Ark_text_Affinity: %{public}d", src);
            break;
    }
}
void AssignArkValue(Ark_text_LineMetrics& dst, const TextLineMetrics& src)
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

namespace NG {
void AssignArkValue(Ark_common2D_Rect& dst, const RectF& src)
{
    dst.left = Converter::ArkValue<Ark_Number>(src.GetX());
    dst.top = Converter::ArkValue<Ark_Number>(src.GetY());
    dst.right = Converter::ArkValue<Ark_Number>(src.Right());
    dst.bottom = Converter::ArkValue<Ark_Number>(src.Bottom());
}
void AssignArkValue(Ark_text_TextBox& dst, const ParagraphManager::TextBox& src)
{
    dst.rect = Converter::ArkValue<Ark_common2D_Rect>(src.rect_);
    dst.direction = Converter::ArkValue<Ark_text_TextDirection>(src.direction_);
}
void AssignArkValue(Ark_PositionWithAffinity& dst, const PositionWithAffinity& src)
{
    dst.position = Converter::ArkValue<Ark_Number>(static_cast<int32_t>(src.position_));
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
} // LayoutManagerAccessor
const GENERATED_ArkUILayoutManagerAccessor* GetLayoutManagerAccessor()
{
    static const GENERATED_ArkUILayoutManagerAccessor LayoutManagerAccessorImpl {
        LayoutManagerAccessor::DestroyPeerImpl,
        LayoutManagerAccessor::ConstructImpl,
        LayoutManagerAccessor::GetFinalizerImpl,
        LayoutManagerAccessor::GetLineCountImpl,
        LayoutManagerAccessor::GetGlyphPositionAtCoordinateImpl,
    };
    return &LayoutManagerAccessorImpl;
}

}
