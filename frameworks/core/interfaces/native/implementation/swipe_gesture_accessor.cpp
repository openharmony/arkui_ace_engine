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
#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/peer_utils.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"
#include "swipe_gesture_peer.h"

namespace OHOS::Ace::NG {
namespace {
constexpr int32_t DEFAULT_SWIPE_FINGERS = 1;
constexpr double DEFAULT_SWIPE_SPEED = 100.0;
constexpr auto DEFAULT_SWIPE_DIRECTION = SwipeDirection{};
constexpr bool DEFAULT_IS_LIMIT_FINGER_COUNT = false;

struct SwipeGestureParams {
    int32_t fingers = DEFAULT_SWIPE_FINGERS;
    SwipeDirection direction = DEFAULT_SWIPE_DIRECTION;
    double speed = DEFAULT_SWIPE_SPEED;
    bool isLimitFingerCount = DEFAULT_IS_LIMIT_FINGER_COUNT;
};
} // namespace

namespace Converter {
template<>
SwipeGestureParams Convert(const Ark_SwipeGestureHandlerOptions& src)
{
    SwipeGestureParams dst;
    if (auto fingers = OptConvert<int32_t>(src.fingers)) {
        dst.fingers = *fingers <= DEFAULT_SWIPE_FINGERS ? DEFAULT_SWIPE_FINGERS : *fingers;
    }
    if (auto direction = OptConvert<SwipeDirection>(src.direction)) {
        dst.direction = *direction;
    }
    if (auto speed = OptConvert<double>(src.speed)) {
        dst.speed = LessOrEqual(*speed, 0.0) ? DEFAULT_SWIPE_SPEED : *speed;
    }
    if (auto isLimitFingerCount = OptConvert<bool>(src.isFingerCountLimited)) {
        dst.isLimitFingerCount = *isLimitFingerCount;
    }
    return dst;
}
} // namespace Converter
} // namespace OHOS::Ace::NG

namespace OHOS::Ace::NG::GeneratedModifier {
namespace SwipeGestureAccessor {
void DestroyPeerImpl(Ark_SwipeGesture peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_SwipeGesture ConstructImpl()
{
    return PeerUtils::CreatePeer<SwipeGesturePeer>();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_SwipeGesture $_instantiateImpl(const Callback_SwipeGesture* factory,
                                   const Opt_SwipeGestureHandlerOptions* value)
{
    CHECK_NULL_RETURN(factory, {});
    auto arkCallback = CallbackHelper(*factory);
    auto peer = arkCallback.InvokeWithObtainResult<Ark_SwipeGesture, Callback_SwipeGesture_Void>();
    CHECK_NULL_RETURN(peer, {});
    auto params = Converter::OptConvertPtr<SwipeGestureParams>(value).value_or(SwipeGestureParams());
    peer->gesture = AceType::MakeRefPtr<SwipeGesture>(params.fingers, params.direction, params.speed,
        params.isLimitFingerCount);
    return peer;
}
void OnActionImpl(Ark_SwipeGesture peer,
                  const Callback_GestureEvent_Void* event)
{
    CHECK_NULL_VOID(peer && peer->gesture && event);
    auto onAction = [arkCallback = CallbackHelper(*event)](GestureEvent& info) {
        auto arkEvent = Converter::ArkGestureEventSync(info);
        arkCallback.InvokeSync(arkEvent.ArkValue());
    };
    peer->gesture->SetOnActionId(std::move(onAction));
}
} // SwipeGestureAccessor
const GENERATED_ArkUISwipeGestureAccessor* GetSwipeGestureAccessor()
{
    static const GENERATED_ArkUISwipeGestureAccessor SwipeGestureAccessorImpl {
        SwipeGestureAccessor::DestroyPeerImpl,
        SwipeGestureAccessor::ConstructImpl,
        SwipeGestureAccessor::GetFinalizerImpl,
        SwipeGestureAccessor::$_instantiateImpl,
        SwipeGestureAccessor::OnActionImpl,
    };
    return &SwipeGestureAccessorImpl;
}

}
