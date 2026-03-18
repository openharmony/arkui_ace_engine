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

#include "core/components_ng/pattern/text/span/span_object.h"
#include "core/interfaces/native/implementation/click_event_peer.h"
#include "core/interfaces/native/implementation/gesture_event_peer.h"
#include "core/interfaces/native/implementation/touch_event_peer.h"
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

#include "arkoala_api_generated.h"
#include "gesture_style_peer.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace GestureStyleAccessor {
void DestroyPeerImpl(Ark_GestureStyle peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_GestureStyle ConstructImpl(const Opt_GestureStyleInterface* value)
{
    auto peer = PeerUtils::CreatePeer<GestureStylePeer>();
    auto optValue = Converter::GetOptPtr(value);

    auto onClickOpt = GET_OPT_FIELD(optValue, onClick);
    auto onLongClickOpt = GET_OPT_FIELD(optValue, onLongPress);
    auto onTouchOpt = GET_OPT_FIELD(optValue, onTouch);
    GestureStyle gestureInfo {};
    if (onClickOpt) {
        auto onClick = [arkCallback = CallbackHelper(*onClickOpt)](GestureEvent& info) -> void {
            const auto event = Converter::SyncEvent<Ark_ClickEvent>(info);
            arkCallback.Invoke(event.ArkValue());
        };
        gestureInfo.onClick = std::move(onClick);
    }

    if (onLongClickOpt) {
        auto onLongClick = [arkCallback = CallbackHelper(*onLongClickOpt)](GestureEvent& info) -> void {
            const auto event = Converter::SyncEvent<Ark_GestureEvent>(info);
            arkCallback.Invoke(event.ArkValue());
        };
        gestureInfo.onLongPress = std::move(onLongClick);
    }

    if (onTouchOpt) {
        auto onTouch = [arkCallback = CallbackHelper(*onTouchOpt)](TouchEventInfo& info) -> void {
            Ark_TouchEventProxy proxy = {
                .target = Converter::ArkValue<Ark_EventTarget>(info.GetTarget()),
                .timeStamp = Converter::ArkValue<Ark_Int64>(
                    static_cast<int64_t>(info.GetTimeStamp().time_since_epoch().count())),
                .pressure = Converter::ArkValue<Ark_Float64>(info.GetForce()),
                .tiltX = Converter::ArkValue<Ark_Float64>(static_cast<double>(info.GetTiltX().value_or(0))),
                .tiltY = Converter::ArkValue<Ark_Float64>(static_cast<double>(info.GetTiltY().value_or(0))),
                .sourceTool = Converter::ArkValue<Ark_SourceTool>(info.GetSourceTool()),
                .deviceId = Converter::ArkValue<Opt_Int32>(info.GetDeviceId()),
                .targetDisplayId = Converter::ArkValue<Opt_Int32>(info.GetTargetDisplayId()),
                .type = Converter::ArkValue<Ark_TouchType>(info.GetChangedTouches().front().GetTouchType()),
                .touches = Converter::ArkValue<Array_TouchObject>(info.GetTouches(), Converter::FC),
                .changedTouches = Converter::ArkValue<Array_TouchObject>(info.GetChangedTouches(), Converter::FC),
                .ptr = &info
            };
            arkCallback.InvokeSync(proxy);
        };
        gestureInfo.onTouch = std::move(onTouch);
    }

    peer->span = AceType::MakeRefPtr<GestureSpan>(gestureInfo);
    return peer;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
} // GestureStyleAccessor
const GENERATED_ArkUIGestureStyleAccessor* GetGestureStyleAccessor()
{
    static const GENERATED_ArkUIGestureStyleAccessor GestureStyleAccessorImpl {
        GestureStyleAccessor::DestroyPeerImpl,
        GestureStyleAccessor::ConstructImpl,
        GestureStyleAccessor::GetFinalizerImpl,
    };
    return &GestureStyleAccessorImpl;
}

}
