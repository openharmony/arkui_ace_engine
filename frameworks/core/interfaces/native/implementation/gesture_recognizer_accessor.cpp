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
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/interfaces/native/implementation/scrollable_target_info_peer.h"
#include "core/interfaces/native/implementation/gesture_recognizer_peer_impl.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
const GENERATED_ArkUIEventTargetInfoAccessor* GetEventTargetInfoAccessor();
const GENERATED_ArkUIScrollableTargetInfoAccessor* GetScrollableTargetInfoAccessor();
namespace GestureRecognizerAccessor {
void DestroyPeerImpl(Ark_GestureRecognizer peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_GestureRecognizer CtorImpl()
{
    return PeerUtils::CreatePeer<GestureRecognizerPeer>();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_String GetTagImpl(Ark_GestureRecognizer peer)
{
    CHECK_NULL_RETURN(peer, {});
    auto recognizer = peer->GetRecognizer().Upgrade();
    CHECK_NULL_RETURN(recognizer, {});
    auto resOpt = recognizer->GetGestureInfo()->GetTag();
    return Converter::ArkValue<Ark_String>(resOpt.value_or(""), Converter::FC);
}
Ark_GestureControl_GestureType GetTypeImpl(Ark_GestureRecognizer peer)
{
    CHECK_NULL_RETURN(peer, static_cast<Ark_GestureControl_GestureType>(-1));
    auto recognizer = peer->GetRecognizer().Upgrade();
    CHECK_NULL_RETURN(recognizer, static_cast<Ark_GestureControl_GestureType>(-1));
    auto typeName = recognizer->GetRecognizerType();
    return Converter::ArkValue<Ark_GestureControl_GestureType>(typeName);
}
Ark_Boolean IsBuiltInImpl(Ark_GestureRecognizer peer)
{
    CHECK_NULL_RETURN(peer, false);
    auto recognizer = peer->GetRecognizer().Upgrade();
    CHECK_NULL_RETURN(recognizer, false);
    auto gestureInfo = recognizer->GetGestureInfo();
    return Converter::ArkValue<Ark_Boolean>(gestureInfo->IsSystemGesture());
}
void SetEnabledImpl(Ark_GestureRecognizer peer,
                    Ark_Boolean isEnabled)
{
    CHECK_NULL_VOID(peer);
    auto recognizer = peer->GetRecognizer().Upgrade();
    CHECK_NULL_VOID(recognizer);
    recognizer->SetEnabled(Converter::Convert<bool>(isEnabled));
}
Ark_Boolean IsEnabledImpl(Ark_GestureRecognizer peer)
{
    CHECK_NULL_RETURN(peer, false);
    auto recognizer = peer->GetRecognizer().Upgrade();
    CHECK_NULL_RETURN(recognizer, false);
    return Converter::ArkValue<Ark_Boolean>(recognizer->IsEnabled());
}
Ark_GestureRecognizerState GetStateImpl(Ark_GestureRecognizer peer)
{
    CHECK_NULL_RETURN(peer, {});
    auto recognizer = peer->GetRecognizer().Upgrade();
    CHECK_NULL_RETURN(recognizer, {});
    auto state = recognizer->GetGestureState();
    return Converter::ArkValue<Ark_GestureRecognizerState>(state);
}
Ark_EventTargetInfo GetEventTargetInfoImpl(Ark_GestureRecognizer peer)
{
    CHECK_NULL_RETURN(peer, nullptr);
    auto recognizer = peer->GetRecognizer().Upgrade();
    CHECK_NULL_RETURN(recognizer, nullptr);
    auto attachNode = recognizer->GetAttachedNode().Upgrade();
    CHECK_NULL_RETURN(attachNode, GetEventTargetInfoAccessor()->ctor());
    RefPtr<Pattern> pattern;
    if (auto swiperPattern = attachNode->GetPattern<SwiperPattern>()) {
        pattern = swiperPattern;
    } else if (auto scrollablePattern = attachNode->GetPattern<ScrollablePattern>()) {
        pattern = scrollablePattern;
    }
    Ark_EventTargetInfo result{};
    if (pattern) {
        auto scrollableTargetInfoPeer = GetScrollableTargetInfoAccessor()->ctor();
        scrollableTargetInfoPeer->SetPattern(pattern);
        scrollableTargetInfoPeer->id = attachNode->GetInspectorIdValue("");
        result = scrollableTargetInfoPeer;
    } else {
        auto eventTargetInfoPeer = GetEventTargetInfoAccessor()->ctor();
        eventTargetInfoPeer->id = attachNode->GetInspectorIdValue("");
        result = eventTargetInfoPeer;
    }
    return result;
}
Ark_Boolean IsValidImpl(Ark_GestureRecognizer peer)
{
    CHECK_NULL_RETURN(peer, false);
    auto recognizer = peer->GetRecognizer().Upgrade();
    CHECK_NULL_RETURN(recognizer, false);
    return Converter::ArkValue<Ark_Boolean>(recognizer->IsInResponseLinkRecognizers());
}
Ark_Number GetFingerCountImpl(Ark_GestureRecognizer peer)
{
    CHECK_NULL_RETURN(peer, {});
    auto recognizer = AceType::DynamicCast<NG::MultiFingersRecognizer>(peer->GetRecognizer().Upgrade());
    CHECK_NULL_RETURN(recognizer, {});
    return Converter::ArkValue<Ark_Number>(recognizer->GetFingers());
}
Ark_Boolean IsFingerCountLimitImpl(Ark_GestureRecognizer peer)
{
    CHECK_NULL_RETURN(peer, {});
    auto recognizer = AceType::DynamicCast<NG::MultiFingersRecognizer>(peer->GetRecognizer().Upgrade());
    CHECK_NULL_RETURN(recognizer, {});
    return Converter::ArkValue<Ark_Boolean>(recognizer->GetLimitFingerCount());
}
} // GestureRecognizerAccessor
const GENERATED_ArkUIGestureRecognizerAccessor* GetGestureRecognizerAccessor()
{
    static const GENERATED_ArkUIGestureRecognizerAccessor GestureRecognizerAccessorImpl {
        GestureRecognizerAccessor::DestroyPeerImpl,
        GestureRecognizerAccessor::CtorImpl,
        GestureRecognizerAccessor::GetFinalizerImpl,
        GestureRecognizerAccessor::GetTagImpl,
        GestureRecognizerAccessor::GetTypeImpl,
        GestureRecognizerAccessor::IsBuiltInImpl,
        GestureRecognizerAccessor::SetEnabledImpl,
        GestureRecognizerAccessor::IsEnabledImpl,
        GestureRecognizerAccessor::GetStateImpl,
        GestureRecognizerAccessor::GetEventTargetInfoImpl,
        GestureRecognizerAccessor::IsValidImpl,
        GestureRecognizerAccessor::GetFingerCountImpl,
        GestureRecognizerAccessor::IsFingerCountLimitImpl,
    };
    return &GestureRecognizerAccessorImpl;
}

}
