/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/text/span/span_object.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/validators.h"

#include "core/interfaces/native/implementation/line_spacing_style_peer.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace LineSpacingStyleAccessor {
void DestroyPeerImpl(Ark_LineSpacingStyle peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_LineSpacingStyle ConstructImpl(const Ark_LengthMetrics* lineSpacing,
                                   const Opt_LineSpacingOptions* options)
{
    auto peer = PeerUtils::CreatePeer<LineSpacingStylePeer>();
    Dimension spacing = Dimension(0, DimensionUnit::VP);
    if (lineSpacing) {
        auto spacingOpt = Converter::OptConvert<Dimension>(*lineSpacing);
        Validator::ValidateNonPercent(spacingOpt);
        Validator::ValidateNonNegative(spacingOpt);
        spacing = spacingOpt.value_or(Dimension(0, DimensionUnit::VP));
    }
    std::optional<LineSpacingOptions> lineSpacingOptions;
    auto value = Converter::OptConvertPtr<Ark_LineSpacingOptions>(options);
    if (value) {
        LineSpacingOptions optionObject;
        optionObject.onlyBetweenLines = Converter::OptConvert<bool>(value->onlyBetweenLines);
        lineSpacingOptions = optionObject;
    }
    peer->span = AceType::MakeRefPtr<LineSpacingSpan>(spacing, lineSpacingOptions);
    return peer;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_Float64 GetLineSpacingImpl(Ark_LineSpacingStyle peer)
{
    Ark_Float64 ret = Converter::ArkValue<Ark_Float64>(0);
    CHECK_NULL_RETURN(peer, ret);
    CHECK_NULL_RETURN(peer->span, ret);
    return Converter::ArkValue<Ark_Float64>(peer->span->GetLineSpacing().ConvertToVp());
}
Opt_LineSpacingOptions GetOptionsImpl(Ark_LineSpacingStyle peer)
{
    auto invalidValue = Converter::ArkValue<Opt_LineSpacingOptions>();
    CHECK_NULL_RETURN(peer, invalidValue);
    CHECK_NULL_RETURN(peer->span, invalidValue);
    auto optValue = peer->span->GetLineSpacingOptions();
    if (optValue.has_value() && optValue.value().onlyBetweenLines.has_value()) {
        Ark_LineSpacingOptions value;
        value.onlyBetweenLines = Converter::ArkValue<Opt_Boolean>(optValue.value().onlyBetweenLines.value());
        return Converter::ArkValue<Opt_LineSpacingOptions>(value);
    }
    return invalidValue;
}
} // LineSpacingStyleAccessor
const GENERATED_ArkUILineSpacingStyleAccessor* GetLineSpacingStyleAccessor()
{
    static const GENERATED_ArkUILineSpacingStyleAccessor LineSpacingStyleAccessorImpl {
        LineSpacingStyleAccessor::DestroyPeerImpl,
        LineSpacingStyleAccessor::ConstructImpl,
        LineSpacingStyleAccessor::GetFinalizerImpl,
        LineSpacingStyleAccessor::GetLineSpacingImpl,
        LineSpacingStyleAccessor::GetOptionsImpl,
    };
    return &LineSpacingStyleAccessorImpl;
}
}