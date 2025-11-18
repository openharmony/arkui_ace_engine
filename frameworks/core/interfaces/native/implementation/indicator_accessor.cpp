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
#include "core/interfaces/native/utility/peer_utils.h"
#include "indicator_peer_impl.h"
#include "dot_indicator_peer_impl.h"
#include "digit_indicator_peer_impl.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace IndicatorAccessor {
void DestroyPeerImpl(Ark_Indicator peer)
{
}
Ark_Indicator ConstructImpl()
{
    auto peer = PeerUtils::CreatePeer<IndicatorPeer>();
    return reinterpret_cast<Ark_Indicator>(peer);
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void LeftImpl(Ark_Indicator peer,
              const Opt_Length* value)
{
    CHECK_NULL_VOID(peer);
    auto optLeft = Converter::OptConvert<Dimension>(*value);
    peer->SetLeft(optLeft);
}
void TopImpl(Ark_Indicator peer,
             const Opt_Length* value)
{
    CHECK_NULL_VOID(peer);
    auto optTop = Converter::OptConvert<Dimension>(*value);
    peer->SetTop(optTop);
}
void RightImpl(Ark_Indicator peer,
               const Opt_Length* value)
{
    CHECK_NULL_VOID(peer);
    auto optRight = Converter::OptConvert<Dimension>(*value);
    peer->SetRight(optRight);
}
void Bottom0Impl(Ark_Indicator peer,
                 const Opt_Length* value)
{
    CHECK_NULL_VOID(peer);
    auto optBottom = Converter::OptConvert<Dimension>(*value);
    peer->SetBottom(optBottom);
}
void Bottom1Impl(Ark_Indicator peer,
                 const Opt_Union_LengthMetrics_Length* bottom,
                 Ark_Boolean ignoreSize)
{
    CHECK_NULL_VOID(peer);
    Converter::VisitUnion(*bottom,
        [peer](const Ark_LengthMetrics& bottom) {
            auto optBottom = Converter::OptConvert<Dimension>(bottom);
            peer->SetBottom(optBottom);
        },
        [peer](const Ark_Length& bottom) {
            auto optBottom = Converter::OptConvert<Dimension>(bottom);
            peer->SetBottom(optBottom);
        },
        [](){});
    auto hasIgnoreSize = Converter::OptConvert<bool>(ignoreSize);
    peer->SetBottomIgnoreSize(hasIgnoreSize);
}
void StartImpl(Ark_Indicator peer,
               const Opt_LengthMetrics* value)
{
    CHECK_NULL_VOID(peer);
    auto optStart = Converter::OptConvert<Dimension>(*value);
    peer->SetStart(optStart);
}
void EndImpl(Ark_Indicator peer,
             const Opt_LengthMetrics* value)
{
    CHECK_NULL_VOID(peer);
    auto optEnd = Converter::OptConvert<Dimension>(*value);
    peer->SetEnd(optEnd);
}
Ark_DotIndicator DotImpl()
{
    auto peer = PeerUtils::CreatePeer<DotIndicatorPeer>();
    return reinterpret_cast<Ark_DotIndicator>(peer);
}
Ark_DigitIndicator DigitImpl()
{
    auto peer = PeerUtils::CreatePeer<DigitIndicatorPeer>();
    return reinterpret_cast<Ark_DigitIndicator>(peer);
}
} // IndicatorAccessor
const GENERATED_ArkUIIndicatorAccessor* GetIndicatorAccessor()
{
    static const GENERATED_ArkUIIndicatorAccessor IndicatorAccessorImpl {
        IndicatorAccessor::DestroyPeerImpl,
        IndicatorAccessor::ConstructImpl,
        IndicatorAccessor::GetFinalizerImpl,
        IndicatorAccessor::LeftImpl,
        IndicatorAccessor::TopImpl,
        IndicatorAccessor::RightImpl,
        IndicatorAccessor::Bottom0Impl,
        IndicatorAccessor::Bottom1Impl,
        IndicatorAccessor::StartImpl,
        IndicatorAccessor::EndImpl,
        IndicatorAccessor::DotImpl,
        IndicatorAccessor::DigitImpl,
    };
    return &IndicatorAccessorImpl;
}

struct IndicatorPeer {
    virtual ~IndicatorPeer() = default;
};
}
