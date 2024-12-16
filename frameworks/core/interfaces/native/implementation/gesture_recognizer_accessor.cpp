/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/interfaces/native/implementation/scrollable_target_info_peer.h"
#include "gesture_recognizer_peer_impl.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
const GENERATED_ArkUIEventTargetInfoAccessor* GetEventTargetInfoAccessor();
const GENERATED_ArkUIScrollableTargetInfoAccessor* GetScrollableTargetInfoAccessor();
namespace GestureRecognizerAccessor {
void DestroyPeerImpl(GestureRecognizerPeer* peer)
{
    if (peer) {
        delete peer;
    }
}
Ark_NativePointer CtorImpl()
{
    return new GestureRecognizerPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void GetTagImpl(GestureRecognizerPeer* peer)
{
    LOGE("ARKOALA GestureRecognizerAccessor.GetTagImpl -> Incorrect return value!");
}
Ark_NativePointer GetTypeImpl(GestureRecognizerPeer* peer)
{
    CHECK_NULL_RETURN(peer && peer->GetRecognizer(), nullptr);
    Ark_NativePointer ret = nullptr;
    auto typeName = peer->GetRecognizer()->GetRecognizerType();
    ret = reinterpret_cast<Ark_NativePointer>(&typeName);
    LOGE("ARKOALA GestureRecognizerAccessor.GetTypeImpl not implemented -> incorrect return value!");
    return ret;
}
Ark_Boolean IsBuiltInImpl(GestureRecognizerPeer* peer)
{
    CHECK_NULL_RETURN(peer && peer->GetRecognizer(), false);
    auto gestureInfo = peer->GetRecognizer()->GetGestureInfo();
    return Converter::ArkValue<Ark_Boolean>(gestureInfo->IsSystemGesture());
}
void SetEnabledImpl(GestureRecognizerPeer* peer,
                    Ark_Boolean isEnabled)
{
    CHECK_NULL_VOID(peer && peer->GetRecognizer());
    peer->GetRecognizer()->SetEnabled(Converter::Convert<bool>(isEnabled));
}
Ark_Boolean IsEnabledImpl(GestureRecognizerPeer* peer)
{
    CHECK_NULL_RETURN(peer && peer->GetRecognizer(), false);
    return Converter::ArkValue<Ark_Boolean>(peer->GetRecognizer()->IsEnabled());
}
Ark_NativePointer GetStateImpl(GestureRecognizerPeer* peer)
{
    CHECK_NULL_RETURN(peer && peer->GetRecognizer(), nullptr);
    Ark_NativePointer ret = nullptr;
    auto state = peer->GetRecognizer()->GetGestureState();
    ret = reinterpret_cast<Ark_NativePointer>(&state);
    return ret;
}
Ark_NativePointer GetEventTargetInfoImpl(GestureRecognizerPeer* peer)
{
    CHECK_NULL_RETURN(peer, nullptr);
    auto attachNode = peer->GetRecognizer() ? peer->GetRecognizer()->GetAttachedNode().Upgrade() : nullptr;
    CHECK_NULL_RETURN(attachNode, reinterpret_cast<Ark_NativePointer>(GetEventTargetInfoAccessor()->ctor()));
    RefPtr<Pattern> pattern;
    if (auto swiperPattern = attachNode->GetPattern<SwiperPattern>()) {
        pattern = swiperPattern;
    } else if (auto scrollablePattern = attachNode->GetPattern<ScrollablePattern>()) {
        pattern = scrollablePattern;
    }
    Ark_NativePointer result;
    if (pattern) {
        auto scrollableTargetInfoPeer = reinterpret_cast<ScrollableTargetInfoPeer*>(
            GetScrollableTargetInfoAccessor()->ctor());
        scrollableTargetInfoPeer->SetPattern(pattern);
        scrollableTargetInfoPeer->id = attachNode->GetInspectorIdValue("");
        result = reinterpret_cast<Ark_NativePointer>(scrollableTargetInfoPeer);
    } else {
        auto eventTargetInfoPeer = reinterpret_cast<EventTargetInfoPeer*>(
            GetEventTargetInfoAccessor()->ctor());
        eventTargetInfoPeer->id = attachNode->GetInspectorIdValue("");
        result = reinterpret_cast<Ark_NativePointer>(eventTargetInfoPeer);
    }
    return result;
}
Ark_Boolean IsValidImpl(GestureRecognizerPeer* peer)
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
