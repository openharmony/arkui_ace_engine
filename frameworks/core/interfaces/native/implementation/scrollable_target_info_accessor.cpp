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
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"

#include "core/interfaces/native/implementation/scrollable_target_info_peer.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ScrollableTargetInfoAccessor {
void DestroyPeerImpl(Ark_ScrollableTargetInfo peer)
{
    CHECK_NULL_VOID(peer);
    peer->DecRefCount();
}
Ark_ScrollableTargetInfo CtorImpl()
{
    auto peer = AceType::MakeRefPtr<ScrollableTargetInfoPeer>();
    peer->IncRefCount();
    return AceType::RawPtr(peer);
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_Boolean IsBeginImpl(Ark_ScrollableTargetInfo peer)
{
    const auto pattern = peer ? peer->GetPattern() : nullptr;
    Ark_Boolean result;
    if (auto scrollablePattern = AceType::DynamicCast<ScrollablePattern>(pattern)) {
        result = Converter::ArkValue<Ark_Boolean>(scrollablePattern->IsAtTop());
    } else if (auto swiperPattern = AceType::DynamicCast<SwiperPattern>(pattern)) {
        result = Converter::ArkValue<Ark_Boolean>(swiperPattern->IsAtStart());
    } else {
        result = Converter::ArkValue<Ark_Boolean>(false);
    }
    return result;
}
Ark_Boolean IsEndImpl(Ark_ScrollableTargetInfo peer)
{
    const auto pattern = peer ? peer->GetPattern() : nullptr;
    Ark_Boolean result;
    if (auto scrollablePattern = AceType::DynamicCast<ScrollablePattern>(pattern)) {
        result = Converter::ArkValue<Ark_Boolean>(scrollablePattern->IsAtBottom());
    } else if (auto swiperPattern = AceType::DynamicCast<SwiperPattern>(pattern)) {
        result = Converter::ArkValue<Ark_Boolean>(swiperPattern->IsAtEnd());
    } else {
        result = Converter::ArkValue<Ark_Boolean>(false);
    }
    return result;
}
} // ScrollableTargetInfoAccessor
const GENERATED_ArkUIScrollableTargetInfoAccessor* GetScrollableTargetInfoAccessor()
{
    static const GENERATED_ArkUIScrollableTargetInfoAccessor ScrollableTargetInfoAccessorImpl {
        ScrollableTargetInfoAccessor::DestroyPeerImpl,
        ScrollableTargetInfoAccessor::CtorImpl,
        ScrollableTargetInfoAccessor::GetFinalizerImpl,
        ScrollableTargetInfoAccessor::IsBeginImpl,
        ScrollableTargetInfoAccessor::IsEndImpl,
    };
    return &ScrollableTargetInfoAccessorImpl;
}

}
