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
#include "line_height_style_peer.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace LineHeightStyleAccessor {
void DestroyPeerImpl(Ark_LineHeightStyle peer)
{
    CHECK_NULL_VOID(peer);
    delete peer;
}
Ark_LineHeightStyle CtorImpl(Ark_LengthMetrics lineHeight)
{
    auto peer = new LineHeightStylePeer();
    Dimension height = Converter::OptConvert<Dimension>(lineHeight).value_or(Dimension());
    peer->span = AceType::MakeRefPtr<LineHeightSpan>(height);
    return peer;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_Number GetLineHeightImpl(Ark_LineHeightStyle peer)
{
    Ark_Number ret = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(peer, ret);
    CHECK_NULL_RETURN(peer->span, ret);
    return Converter::ArkValue<Ark_Number>(peer->span->GetLineHeight().ConvertToPx());
}
} // LineHeightStyleAccessor
const GENERATED_ArkUILineHeightStyleAccessor* GetLineHeightStyleAccessor()
{
    static const GENERATED_ArkUILineHeightStyleAccessor LineHeightStyleAccessorImpl {
        LineHeightStyleAccessor::DestroyPeerImpl,
        LineHeightStyleAccessor::CtorImpl,
        LineHeightStyleAccessor::GetFinalizerImpl,
        LineHeightStyleAccessor::GetLineHeightImpl,
    };
    return &LineHeightStyleAccessorImpl;
}

}
