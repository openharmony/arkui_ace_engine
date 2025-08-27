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

#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/utility/validators.h"
#include "arkoala_api_generated.h"
#include "core/interfaces/native/implementation/baseline_offset_style_peer.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace BaselineOffsetStyleAccessor {
void DestroyPeerImpl(Ark_BaselineOffsetStyle peer)
{
    delete peer;
}
Ark_BaselineOffsetStyle CtorImpl(Ark_LengthMetrics value)
{
    std::optional<Dimension> offset;
    Dimension defaultOffset = Dimension(0, DimensionUnit::VP);
    if (value) {
        offset = Converter::OptConvert<Dimension>(value);
        Validator::ValidateNonPercent(offset);
    }
    RefPtr<BaselineOffsetSpan> span = AceType::MakeRefPtr<BaselineOffsetSpan>(offset.value_or(defaultOffset));
    return new BaselineOffsetStylePeer{ .span = span };
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_Number GetBaselineOffsetImpl(Ark_BaselineOffsetStyle peer)
{
    CHECK_NULL_RETURN(peer, {});
    CHECK_NULL_RETURN(peer->span, {});
    auto value = Converter::ArkValue<Ark_Number>(peer->span->GetBaselineOffset().ConvertToVp());
    return value;
}
} // BaselineOffsetStyleAccessor
const GENERATED_ArkUIBaselineOffsetStyleAccessor* GetBaselineOffsetStyleAccessor()
{
    static const GENERATED_ArkUIBaselineOffsetStyleAccessor BaselineOffsetStyleAccessorImpl {
        BaselineOffsetStyleAccessor::DestroyPeerImpl,
        BaselineOffsetStyleAccessor::CtorImpl,
        BaselineOffsetStyleAccessor::GetFinalizerImpl,
        BaselineOffsetStyleAccessor::GetBaselineOffsetImpl,
    };
    return &BaselineOffsetStyleAccessorImpl;
}

}
