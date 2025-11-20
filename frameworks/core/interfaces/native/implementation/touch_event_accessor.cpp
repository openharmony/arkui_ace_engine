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

namespace OHOS::Ace::NG::Converter {
    template<>
    void AssignCast(std::optional<TouchType>& dst, const Ark_TouchType& src)
    {
        switch (src) {
            case Ark_TouchType::ARK_TOUCH_TYPE_DOWN: dst = TouchType::DOWN; break;
            case Ark_TouchType::ARK_TOUCH_TYPE_UP: dst = TouchType::UP; break;
            case Ark_TouchType::ARK_TOUCH_TYPE_MOVE: dst = TouchType::MOVE; break;
            case Ark_TouchType::ARK_TOUCH_TYPE_CANCEL: dst = TouchType::CANCEL; break;
            default: LOGE("Unexpected enum value in Ark_TouchType: %{public}d", src);
        }
    }
} // namespace OHOS::Ace::NG::Converter

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
Ark_TouchEvent ConstructImpl()
{
    return PeerUtils::CreatePeer<TouchEventPeer>();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void StopPropagationImpl(Ark_TouchEvent peer)
{
    CHECK_NULL_VOID(peer);
    TouchEventInfo* info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    info->SetStopPropagation(true);
}
Opt_Array_HistoricalPoint GetHistoricalPointsImpl(Ark_TouchEvent peer)
{
    auto invalid = Converter::ArkValue<Opt_Array_HistoricalPoint>();
    CHECK_NULL_RETURN(peer, invalid);
    auto info = peer->GetEventInfo();
    CHECK_NULL_RETURN(info, invalid);
    std::list<TouchLocationInfo> history;
    history = info->GetHistory();
    return Converter::ArkValue<Opt_Array_HistoricalPoint>(history, Converter::FC);
}
void PreventDefaultImpl(Ark_TouchEvent peer)
{
    CHECK_NULL_VOID(peer);
    TouchEventInfo* info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    info->SetPreventDefault(true);
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
    CHECK_NULL_VOID(peer);
    auto info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    auto changedTouches = info->GetChangedTouches();
    if (changedTouches.empty()) {
        LOGE("ARKOALA TouchEventAccessor::SetTypeImpl empty list of changed touches.");
        return;
    }
    auto typeValue = Converter::Convert<std::optional<TouchType>>(type).value_or(TouchType::UNKNOWN);
    changedTouches.front().SetTouchType(typeValue);
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
    CHECK_NULL_VOID(peer);
    TouchEventInfo* info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    CHECK_NULL_VOID(touches);
    auto touchList = Converter::Convert<std::list<TouchLocationInfo>>(*touches);
    info->SetTouches(std::move(touchList));
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
    CHECK_NULL_VOID(peer);
    TouchEventInfo* info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    CHECK_NULL_VOID(changedTouches);
    auto touchList = Converter::Convert<std::list<TouchLocationInfo>>(*changedTouches);
    info->SetChangedTouches(std::move(touchList));
}
} // TouchEventAccessor
const GENERATED_ArkUITouchEventAccessor* GetTouchEventAccessor()
{
    static const GENERATED_ArkUITouchEventAccessor TouchEventAccessorImpl {
        TouchEventAccessor::DestroyPeerImpl,
        TouchEventAccessor::ConstructImpl,
        TouchEventAccessor::GetFinalizerImpl,
        TouchEventAccessor::StopPropagationImpl,
        TouchEventAccessor::GetHistoricalPointsImpl,
        TouchEventAccessor::PreventDefaultImpl,
        TouchEventAccessor::GetTypeImpl,
        TouchEventAccessor::SetTypeImpl,
        TouchEventAccessor::GetTouchesImpl,
        TouchEventAccessor::SetTouchesImpl,
        TouchEventAccessor::GetChangedTouchesImpl,
        TouchEventAccessor::SetChangedTouchesImpl,
    };
    return &TouchEventAccessorImpl;
}

}
