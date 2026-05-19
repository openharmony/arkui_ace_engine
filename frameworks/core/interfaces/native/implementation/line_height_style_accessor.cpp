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

#include "arkoala_api_generated.h"
#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/validators.h"
#include "frameworks/core/components_ng/pattern/text/span/span_object.h"
#include "frameworks/core/interfaces/native/implementation/length_metrics_peer.h"
#include "frameworks/core/interfaces/native/utility/callback_helper.h"
#include "frameworks/core/interfaces/native/utility/reverse_converter.h"

#include "line_height_style_peer.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace LineHeightStyleAccessor {
void DestroyPeerImpl(Ark_LineHeightStyle peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_LineHeightStyle Construct0Impl(const Ark_LengthMetrics* lineHeight)
{
    auto peer = PeerUtils::CreatePeer<LineHeightStylePeer>();
    Dimension height = Converter::OptConvert<Dimension>(*lineHeight).value_or(Dimension());
    peer->span = AceType::MakeRefPtr<LineHeightSpan>(height);
    return peer;
}
Ark_LineHeightStyle Construct1Impl(const Ark_LengthMetrics* lineHeight,
                                   Ark_Float64 lineHeightMultiple)
{
    auto peer = PeerUtils::CreatePeer<LineHeightStylePeer>();
    Dimension height = Dimension(0, DimensionUnit::VP);
    if (lineHeight) {
        auto heightOpt = Converter::OptConvert<Dimension>(*lineHeight);
        Validator::ValidateNonPercent(heightOpt);
        height = heightOpt.value_or(Dimension(0, DimensionUnit::VP));
    }
    auto multiple = Converter::OptConvert<double>(lineHeightMultiple);
    if (multiple.has_value() && LessNotEqual(multiple.value(), 0.0)) {
        multiple.reset();
    }
    peer->span = AceType::MakeRefPtr<LineHeightSpan>(height, multiple);
    return peer;
}

Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_Float64 GetLineHeightImpl(Ark_LineHeightStyle peer)
{
    Ark_Float64 invalid = Converter::ArkValue<Ark_Float64>(0);
    CHECK_NULL_RETURN(peer, invalid);
    CHECK_NULL_RETURN(peer->span, invalid);
    return Converter::ArkValue<Ark_Float64>(peer->span->GetLineHeight().ConvertToVp());
}
Opt_Float64 GetLineHeightMultipleImpl(Ark_LineHeightStyle peer)
{
    Opt_Float64 invalid = Converter::ArkValue<Opt_Float64>();
    CHECK_NULL_RETURN(peer, invalid);
    CHECK_NULL_RETURN(peer->span, invalid);
    auto multiple = peer->span->GetLineHeightMultiple();
    return Converter::ArkValue<Opt_Float64>(multiple);
}
} // LineHeightStyleAccessor
const GENERATED_ArkUILineHeightStyleAccessor* GetLineHeightStyleAccessor()
{
    static const GENERATED_ArkUILineHeightStyleAccessor LineHeightStyleAccessorImpl {
        LineHeightStyleAccessor::DestroyPeerImpl,
        LineHeightStyleAccessor::Construct0Impl,
        LineHeightStyleAccessor::Construct1Impl,
        LineHeightStyleAccessor::GetFinalizerImpl,
        LineHeightStyleAccessor::GetLineHeightImpl,
        LineHeightStyleAccessor::GetLineHeightMultipleImpl,
    };
    return &LineHeightStyleAccessorImpl;
}

}
