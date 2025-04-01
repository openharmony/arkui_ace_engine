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

#include <unordered_set>

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/implementation/touch_event_peer.h"

namespace {
const std::unordered_set<std::string> g_touchPreventDefPattern = { "Checkbox", "CheckboxGroup", "Rating",
    "Radio", "Toggle", "Hyperlink" };
}

namespace OHOS::Ace::NG::GeneratedModifier {
namespace TouchEventAccessor {
void DestroyPeerImpl(Ark_TouchEvent peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_TouchEvent CtorImpl()
{
    return PeerUtils::CreatePeer<TouchEventPeer>();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Array_HistoricalPoint GetHistoricalPointsImpl(Ark_TouchEvent peer)
{
    CHECK_NULL_RETURN(peer, {});
    auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, {});
    std::list<TouchLocationInfo> history;
    history = info->GetHistory();
    return Converter::ArkValue<Array_HistoricalPoint>(history, Converter::FC);
}
Ark_TouchType GetTypeImpl(Ark_TouchEvent peer)
{
    const auto errValue = static_cast<Ark_TouchType>(-1);
    CHECK_NULL_RETURN(peer, errValue);
    TouchEventInfo* info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, errValue);
    auto changedTouches = info->GetChangedTouches();
    if (changedTouches.empty()) {
        LOGE("ARKOALA TouchEventAccessor::GetTypeImpl empty list of changed touches.");
        return errValue;
    }
    return Converter::ArkValue<Ark_TouchType>(changedTouches.front().GetTouchType());
}
void SetTypeImpl(Ark_TouchEvent peer,
                 Ark_TouchType type)
{
    LOGE("TouchEventAccessor::SetTypeImpl we can only GET event type");
}
Array_TouchObject GetTouchesImpl(Ark_TouchEvent peer)
{
    CHECK_NULL_RETURN(peer, {});
    auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, {});
    const std::list<TouchLocationInfo>& touchList = info->GetTouches();
    return Converter::ArkValue<Array_TouchObject>(touchList, Converter::FC);
}
void SetTouchesImpl(Ark_TouchEvent peer,
                    const Array_TouchObject* touches)
{
    LOGE("TouchEventAccessor::SetTouchesImpl we can only add new touches. "
        "We can not set touches array");
}
Array_TouchObject GetChangedTouchesImpl(Ark_TouchEvent peer)
{
    CHECK_NULL_RETURN(peer, {});
    auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, {});
    const std::list<TouchLocationInfo>& touchList = info->GetChangedTouches();
    return Converter::ArkValue<Array_TouchObject>(touchList, Converter::FC);
}
void SetChangedTouchesImpl(Ark_TouchEvent peer,
                           const Array_TouchObject* changedTouches)
{
    LOGE("TouchEventAccessor::SetChangedTouchesImpl we can only add new changedTouches. "
        "We can not set changedTouches array");
}
Callback_Void GetStopPropagationImpl(Ark_TouchEvent peer)
{
    CHECK_NULL_RETURN(peer, {});
    auto callback = CallbackKeeper::DefineReverseCallback<Callback_Void>([peer]() {
        TouchEventInfo* info = peer->GetEventInfo();
        CHECK_NULL_VOID(info);
        info->SetStopPropagation(true);
    });
    return callback;
}
void SetStopPropagationImpl(Ark_TouchEvent peer,
                            const Callback_Void* stopPropagation)
{
    LOGE("TouchEventAccessor::SetStopPropagationImpl wen can only GET stopPropagation callback");
}
Callback_Void GetPreventDefaultImpl(Ark_TouchEvent peer)
{
    CHECK_NULL_RETURN(peer, {});
    auto callback = CallbackKeeper::DefineReverseCallback<Callback_Void>([peer]() {
        TouchEventInfo* info = peer->GetEventInfo();
        CHECK_NULL_VOID(info);
        auto patternName = info->GetPatternName();
        if (g_touchPreventDefPattern.find(patternName.c_str()) == g_touchPreventDefPattern.end()) {
            LOGE("ARKOALA Component does not support prevent function.");
            return;
        }
        info->SetPreventDefault(true);
    });
    return callback;
}
void SetPreventDefaultImpl(Ark_TouchEvent peer,
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
        TouchEventAccessor::GetTouchesImpl,
        TouchEventAccessor::SetTouchesImpl,
        TouchEventAccessor::GetChangedTouchesImpl,
        TouchEventAccessor::SetChangedTouchesImpl,
        TouchEventAccessor::GetStopPropagationImpl,
        TouchEventAccessor::SetStopPropagationImpl,
        TouchEventAccessor::GetPreventDefaultImpl,
        TouchEventAccessor::SetPreventDefaultImpl,
    };
    return &TouchEventAccessorImpl;
}

}
