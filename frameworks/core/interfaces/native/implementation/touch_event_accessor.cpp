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
#include "core/interfaces/native/implementation/touch_event_peer.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace TouchEventAccessor {
void DestroyPeerImpl(TouchEventPeer* peer)
{
    delete peer;
}
Ark_NativePointer CtorImpl()
{
    return new TouchEventPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void GetHistoricalPointsImpl(TouchEventPeer* peer)
{
    CHECK_NULL_VOID(peer);
    auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    std::list<TouchLocationInfo> history;
    history = info->GetHistory();
    LOGE("TouchEventAccessor::GetHistoricalPointsImpl - wrong return");
}
Ark_NativePointer GetTypeImpl(TouchEventPeer* peer)
{
    CHECK_NULL_RETURN(peer, nullptr);
    auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, nullptr);
    const std::list<TouchLocationInfo>& changeTouch = info->GetChangedTouches();
    auto type = Ark_TouchType::ARK_TOUCH_TYPE_CANCEL; // default value is not defined in documentation.
    if (changeTouch.size() > 0) {
        type = Converter::ArkValue<Ark_TouchType>(changeTouch.front().GetTouchType());
    }
    LOGE("TouchEventAccessor::GetTypeImpl - wrong return");
    return nullptr;
}
void SetTypeImpl(TouchEventPeer* peer,
                 Ark_TouchType type)
{
    LOGE("TouchEventAccessor::SetTypeImpl we can only GET event type");
}
void SetTouchesImpl(TouchEventPeer* peer,
                    const Array_TouchObject* touches)
{
    LOGE("TouchEventAccessor::SetTouchesImpl we can only add new touches. "
        "We can not set touches array");
}
void SetChangedTouchesImpl(TouchEventPeer* peer,
                           const Array_TouchObject* changedTouches)
{
    LOGE("TouchEventAccessor::SetChangedTouchesImpl we can only add new changedTouches. "
        "We can not set changedTouches array");
}
void SetStopPropagationImpl(TouchEventPeer* peer,
                            const Callback_Void* stopPropagation)
{
    LOGE("TouchEventAccessor::SetStopPropagationImpl wen can only GET stopPropagation callback");
}
void SetPreventDefaultImpl(TouchEventPeer* peer,
                           const Callback_Void* preventDefault)
{
    LOGE("TouchEventAccessor::SetPreventDefaultImpl wen can only GET preventDefault callback");
}
} // TouchEventAccessor
const GENERATED_ArkUITouchEventAccessor* GetTouchEventAccessor()
{
    static const GENERATED_ArkUITouchEventAccessor TouchEventAccessorImpl {
        TouchEventAccessor::DestroyPeerImpl,
        TouchEventAccessor::CtorImpl,
        TouchEventAccessor::GetFinalizerImpl,
        TouchEventAccessor::GetHistoricalPointsImpl,
        TouchEventAccessor::GetTypeImpl,
        TouchEventAccessor::SetTypeImpl,
        TouchEventAccessor::SetTouchesImpl,
        TouchEventAccessor::SetChangedTouchesImpl,
        TouchEventAccessor::SetStopPropagationImpl,
        TouchEventAccessor::SetPreventDefaultImpl,
    };
    return &TouchEventAccessorImpl;
}

}
