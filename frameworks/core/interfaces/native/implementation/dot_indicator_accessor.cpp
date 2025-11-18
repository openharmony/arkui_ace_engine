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
#include "dot_indicator_peer_impl.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace DotIndicatorAccessor {
void DestroyPeerImpl(Ark_DotIndicator peer)
{
}
Ark_DotIndicator ConstructImpl()
{
    auto peer = PeerUtils::CreatePeer<DotIndicatorPeer>();
    return reinterpret_cast<Ark_DotIndicator>(peer);
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void ItemWidthImpl(Ark_DotIndicator peer,
                   const Opt_Length* value)
{
    CHECK_NULL_VOID(peer);
    auto optItemWidth = Converter::OptConvert<Dimension>(*value);
    peer->SetItemWidth(optItemWidth);
}
void ItemHeightImpl(Ark_DotIndicator peer,
                    const Opt_Length* value)
{
    CHECK_NULL_VOID(peer);
    auto optItemHeight = Converter::OptConvert<Dimension>(*value);
    peer->SetItemHeight(optItemHeight);
}
void SelectedItemWidthImpl(Ark_DotIndicator peer,
                           const Opt_Length* value)
{
    CHECK_NULL_VOID(peer);
    auto optSelectedItemWidth = Converter::OptConvert<Dimension>(*value);
    peer->SetSelectedItemWidth(optSelectedItemWidth);
}
void SelectedItemHeightImpl(Ark_DotIndicator peer,
                            const Opt_Length* value)
{
    CHECK_NULL_VOID(peer);
    auto optSelectedItemHeight = Converter::OptConvert<Dimension>(*value);
    peer->SetSelectedItemHeight(optSelectedItemHeight);
}
void MaskImpl(Ark_DotIndicator peer,
              const Opt_Boolean* value)
{
    CHECK_NULL_VOID(peer);
    auto optMask = Converter::OptConvert<bool>(*value);
    peer->SetMask(optMask);
}
void ColorImpl(Ark_DotIndicator peer,
               const Opt_ResourceColor* value)
{
    CHECK_NULL_VOID(peer);
    auto optColor = Converter::OptConvert<Color>(*value);
    peer->SetColor(optColor);
}
void SelectedColorImpl(Ark_DotIndicator peer,
                       const Opt_ResourceColor* value)
{
    CHECK_NULL_VOID(peer);
    auto optSelectedColor = Converter::OptConvert<Color>(*value);
    peer->SetSelectedColor(optSelectedColor);
}
void MaxDisplayCountImpl(Ark_DotIndicator peer,
                         const Opt_Int32* maxDisplayCount)
{
    CHECK_NULL_VOID(peer);
    auto optMaxDisplayCount = Converter::OptConvert<int32_t>(*maxDisplayCount);
    peer->SetMaxDisplayCount(optMaxDisplayCount);
}
void SpaceImpl(Ark_DotIndicator peer,
               const Opt_LengthMetrics* space)
{
    CHECK_NULL_VOID(peer);
    auto optSpace = Converter::OptConvert<Dimension>(*space);
    peer->SetSpace(optSpace);
}
} // DotIndicatorAccessor
const GENERATED_ArkUIDotIndicatorAccessor* GetDotIndicatorAccessor()
{
    static const GENERATED_ArkUIDotIndicatorAccessor DotIndicatorAccessorImpl {
        DotIndicatorAccessor::DestroyPeerImpl,
        DotIndicatorAccessor::ConstructImpl,
        DotIndicatorAccessor::GetFinalizerImpl,
        DotIndicatorAccessor::ItemWidthImpl,
        DotIndicatorAccessor::ItemHeightImpl,
        DotIndicatorAccessor::SelectedItemWidthImpl,
        DotIndicatorAccessor::SelectedItemHeightImpl,
        DotIndicatorAccessor::MaskImpl,
        DotIndicatorAccessor::ColorImpl,
        DotIndicatorAccessor::SelectedColorImpl,
        DotIndicatorAccessor::MaxDisplayCountImpl,
        DotIndicatorAccessor::SpaceImpl,
    };
    return &DotIndicatorAccessorImpl;
}

struct DotIndicatorPeer {
    virtual ~DotIndicatorPeer() = default;
};
}
