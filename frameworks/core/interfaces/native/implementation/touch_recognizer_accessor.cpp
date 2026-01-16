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
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"
#include "core/interfaces/native/implementation/scrollable_target_info_peer.h"
#include "core/interfaces/native/implementation/touch_recognizer_peer.h"
  
namespace OHOS::Ace::NG::GeneratedModifier {
const GENERATED_ArkUIEventTargetInfoAccessor* GetEventTargetInfoAccessor();
const GENERATED_ArkUIScrollableTargetInfoAccessor* GetScrollableTargetInfoAccessor();
  
namespace TouchRecognizerAccessor {
void DestroyPeerImpl(Ark_TouchRecognizer peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_TouchRecognizer ConstructImpl()
{
    return PeerUtils::CreatePeer<TouchRecognizerPeer>();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_EventTargetInfo GetEventTargetInfoImpl(Ark_TouchRecognizer peer)
{
    CHECK_NULL_RETURN(peer, nullptr);
    auto target = peer->target_.Upgrade();
    if (!target) {
        return GetEventTargetInfoAccessor()->construct();
    }
    auto attachNode = target->GetAttachedNode().Upgrade();
    if (!attachNode) {
        return GetEventTargetInfoAccessor()->construct();
    }
    RefPtr<Pattern> pattern;
    if (auto swiperPattern = attachNode->GetPattern<SwiperPattern>()) {
        pattern = swiperPattern;
    } else if (auto scrollablePattern = attachNode->GetPattern<ScrollablePattern>()) {
        pattern = scrollablePattern;
    }
    Ark_EventTargetInfo result{};
    if (pattern) {
        auto scrollableTargetInfoPeer = GetScrollableTargetInfoAccessor()->construct();
        scrollableTargetInfoPeer->SetPattern(pattern);
        scrollableTargetInfoPeer->id = attachNode->GetInspectorIdValue("");
        result = scrollableTargetInfoPeer;
    } else {
        auto eventTargetInfoPeer = GetEventTargetInfoAccessor()->construct();
        eventTargetInfoPeer->id = attachNode->GetInspectorIdValue("");
        eventTargetInfoPeer->isScrollableComponent_ = false;
        result = eventTargetInfoPeer;
    }
    return result;
}
void CancelTouchImpl(Ark_TouchRecognizer peer)
{
    CHECK_NULL_VOID(peer);
    if (peer->fingerIds_.empty()) {
        TAG_LOGW(AceLogTag::ACE_GESTURE, "fingerIds_ is empty.");
        return;
    }
    auto target = peer->target_.Upgrade();
    CHECK_NULL_VOID(target);
    auto node = target->GetAttachedNode().Upgrade();
    CHECK_NULL_VOID(node);
    auto pipeline = node->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto eventManager = pipeline->GetEventManager();
    CHECK_NULL_VOID(eventManager);
    auto& touchTestResult = eventManager->touchTestResults_;
    std::vector<std::pair<int32_t, TouchTestResult::iterator>> legacyTarget;
    for (const auto& fingerId : peer->fingerIds_) {
        if (touchTestResult.find(fingerId) == touchTestResult.end()) {
            continue;
        }
        auto& targetsList = touchTestResult[fingerId];
        auto it = std::find_if(targetsList.begin(), targetsList.end(),
            [&target](const RefPtr<TouchEventTarget>& t) { return t == target; });
        if (it != targetsList.end()) {
            legacyTarget.emplace_back(fingerId, it);
        }
    }
    eventManager->DispatchTouchCancelToRecognizer(OHOS::Ace::AceType::RawPtr(target), legacyTarget);
    peer->fingerIds_.clear();
}
} // TouchRecognizerAccessor
const GENERATED_ArkUITouchRecognizerAccessor* GetTouchRecognizerAccessor()
{
    static const GENERATED_ArkUITouchRecognizerAccessor TouchRecognizerAccessorImpl {
        TouchRecognizerAccessor::DestroyPeerImpl,
        TouchRecognizerAccessor::ConstructImpl,
        TouchRecognizerAccessor::GetFinalizerImpl,
        TouchRecognizerAccessor::GetEventTargetInfoImpl,
        TouchRecognizerAccessor::CancelTouchImpl,
    };
    return &TouchRecognizerAccessorImpl;
}
}