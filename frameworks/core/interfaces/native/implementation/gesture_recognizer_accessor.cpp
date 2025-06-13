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
    if (peer) {
        delete peer;
    }
}
Ark_GestureRecognizer CtorImpl()
{
    return new GestureRecognizerPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_String GetTagImpl(Ark_GestureRecognizer peer)
{
    CHECK_NULL_RETURN(peer && peer->GetRecognizer(), {});
    auto resOpt = peer->GetRecognizer()->GetGestureInfo()->GetTag();
    return Converter::ArkValue<Ark_String>(resOpt.value_or(""), Converter::FC);
}
Ark_GestureControl_GestureType GetTypeImpl(Ark_GestureRecognizer peer)
{
    CHECK_NULL_RETURN(peer && peer->GetRecognizer(), static_cast<Ark_GestureControl_GestureType>(-1));
    auto typeName = peer->GetRecognizer()->GetRecognizerType();
    return Converter::ArkValue<Ark_GestureControl_GestureType>(typeName);
}
Ark_Boolean IsBuiltInImpl(Ark_GestureRecognizer peer)
{
    CHECK_NULL_RETURN(peer && peer->GetRecognizer(), false);
    auto gestureInfo = peer->GetRecognizer()->GetGestureInfo();
    return Converter::ArkValue<Ark_Boolean>(gestureInfo->IsSystemGesture());
}
void SetEnabledImpl(Ark_GestureRecognizer peer,
                    Ark_Boolean isEnabled)
{
    CHECK_NULL_VOID(peer && peer->GetRecognizer());
    peer->GetRecognizer()->SetEnabled(Converter::Convert<bool>(isEnabled));
}
Ark_Boolean IsEnabledImpl(Ark_GestureRecognizer peer)
{
    CHECK_NULL_RETURN(peer && peer->GetRecognizer(), false);
    return Converter::ArkValue<Ark_Boolean>(peer->GetRecognizer()->IsEnabled());
}
Ark_GestureRecognizerState GetStateImpl(Ark_GestureRecognizer peer)
{
    CHECK_NULL_RETURN(peer && peer->GetRecognizer(), {});
    auto state = peer->GetRecognizer()->GetGestureState();
    return {};
}
Ark_EventTargetInfo GetEventTargetInfoImpl(Ark_GestureRecognizer peer)
{
    CHECK_NULL_RETURN(peer, nullptr);
    auto attachNode = peer->GetRecognizer() ? peer->GetRecognizer()->GetAttachedNode().Upgrade() : nullptr;
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
    CHECK_NULL_RETURN(peer && peer->GetRecognizer(), false);
    return Converter::ArkValue<Ark_Boolean>(peer->GetRecognizer()->IsInResponseLinkRecognizers());
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
    };
    return &GestureRecognizerAccessorImpl;
}
}
