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

#include "core/interfaces/native/implementation/pan_gesture_options_peer.h"
#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG {
struct PanGestureOptionsInfo {
    std::optional<int32_t> fingers;
    std::optional<PanDirection> direction;
    std::optional<float> distance;
    std::optional<bool> isFingerCountLimited;
};

namespace Converter {
template<>
void AssignCast(std::optional<PanGestureOptionsInfo>& dst,
                const Ark_PanGestureHandlerOptions& src)
{
    PanGestureOptionsInfo result;
    result.fingers = Converter::OptConvert<int32_t>(src.fingers);
    result.direction = Converter::OptConvert<PanDirection>(src.direction);
    result.distance = Converter::OptConvert<float>(src.distance);
    result.isFingerCountLimited = Converter::OptConvert<bool>(src.isFingerCountLimited);
    dst = result;
}
}
}

namespace OHOS::Ace::NG::GeneratedModifier {
namespace PanGestureOptionsAccessor {
namespace {
    constexpr int32_t DEFAULT_PAN_FINGERS = 1;
    constexpr int32_t DEFAULT_MAX_PAN_FINGERS = 10;
    Dimension DEFAULT_PAN_DISTANCE = 5.0_vp;
    constexpr auto DEFAULT_PAN_DIRECTION = PanDirection{};
}
void DestroyPeerImpl(Ark_PanGestureOptions peer)
{
    delete peer;
}
Ark_PanGestureOptions CtorImpl(const Opt_PanGestureHandlerOptions* value)
{
    auto peer = new PanGestureOptionsPeer();
    peer->handler = Referenced::MakeRefPtr<PanGestureOption>();
    CHECK_NULL_RETURN(value, peer);
    auto fingers = DEFAULT_PAN_FINGERS;
    auto distance = DEFAULT_PAN_DISTANCE.ConvertToPx();
    auto direction = DEFAULT_PAN_DIRECTION;
    auto isFingerCountLimited = false;
    auto info = Converter::OptConvert<PanGestureOptionsInfo>(*value);
    if (info) {
        direction = info.value().direction.value_or(DEFAULT_PAN_DIRECTION);
        if (info.value().distance) {
            Dimension dimension = LessNotEqual(info.value().distance.value(), 0.0) ?
                DEFAULT_PAN_DISTANCE : Dimension(info.value().distance.value(), DimensionUnit::VP);
            distance = dimension.ConvertToPx();
        }
        fingers = info.value().fingers.value_or(DEFAULT_PAN_FINGERS);
        fingers = fingers <= DEFAULT_PAN_FINGERS ? DEFAULT_PAN_FINGERS : fingers;
        fingers = fingers > DEFAULT_MAX_PAN_FINGERS ? DEFAULT_PAN_FINGERS : fingers;
        isFingerCountLimited = info.value().isFingerCountLimited.value_or(false);
    }

    peer->handler->SetDirection(direction);
    peer->handler->SetDistance(distance);
    peer->handler->SetFingers(fingers);
    peer->handler->SetIsLimitFingerCount(isFingerCountLimited);
    return peer;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<Ark_NativePointer>(&DestroyPeerImpl);
}
void SetDirectionImpl(Ark_PanGestureOptions peer,
                      Ark_PanDirection value)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(peer->handler);
    auto convDirection = Converter::OptConvert<PanDirection>(value);
    peer->handler->SetDirection(convDirection.value_or(DEFAULT_PAN_DIRECTION));
}
void SetDistanceImpl(Ark_PanGestureOptions peer,
                     const Ark_Number* value)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(peer->handler);
    CHECK_NULL_VOID(value);
    auto distance = DEFAULT_PAN_DISTANCE.ConvertToPx();
    auto convDistance = Converter::OptConvert<float>(*value);
    if (convDistance.has_value()) {
        Dimension dimension = LessNotEqual(convDistance.value(), 0.0) ?
            DEFAULT_PAN_DISTANCE : Dimension(convDistance.value(), DimensionUnit::VP);
        distance = dimension.ConvertToPx();
    }
    peer->handler->SetDistance(distance);
}
void SetFingersImpl(Ark_PanGestureOptions peer,
                    const Ark_Number* value)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(peer->handler);
    CHECK_NULL_VOID(value);
    auto convFingers = Converter::OptConvert<int32_t>(*value);
    auto fingers = convFingers.value_or(DEFAULT_PAN_FINGERS);
    fingers = fingers <= DEFAULT_PAN_FINGERS ? DEFAULT_PAN_FINGERS : fingers;
    fingers = fingers > DEFAULT_MAX_PAN_FINGERS ? DEFAULT_PAN_FINGERS : fingers;
    peer->handler->SetFingers(fingers);
}
Ark_PanDirection GetDirectionImpl(Ark_PanGestureOptions peer)
{
    CHECK_NULL_RETURN(peer, Converter::INVALID_ENUM_VAL<Ark_PanDirection>);
    CHECK_NULL_RETURN(peer->handler,  Converter::INVALID_ENUM_VAL<Ark_PanDirection>);
    auto direction = peer->handler->GetDirection();
    return Converter::ArkValue<Ark_PanDirection>(direction, Converter::FC);
}
Ark_Number GetDistanceImpl(Ark_PanGestureOptions peer)
{
    const auto errValue = Converter::ArkValue<Ark_Number>(0);
    CHECK_NULL_RETURN(peer, errValue);
    CHECK_NULL_RETURN(peer->handler, errValue);
    auto distance = peer->handler->GetDistance();
    auto context = PipelineContext::GetCurrentContextSafely();
    CHECK_NULL_RETURN(context, errValue);
    auto distance_new = context->ConvertPxToVp(Dimension(distance, DimensionUnit::PX));
    return Converter::ArkValue<Ark_Number>(distance_new);
}
} // PanGestureOptionsAccessor
const GENERATED_ArkUIPanGestureOptionsAccessor* GetPanGestureOptionsAccessor()
{
    static const GENERATED_ArkUIPanGestureOptionsAccessor PanGestureOptionsAccessorImpl {
        PanGestureOptionsAccessor::DestroyPeerImpl,
        PanGestureOptionsAccessor::CtorImpl,
        PanGestureOptionsAccessor::GetFinalizerImpl,
        PanGestureOptionsAccessor::SetDirectionImpl,
        PanGestureOptionsAccessor::SetDistanceImpl,
        PanGestureOptionsAccessor::SetFingersImpl,
        PanGestureOptionsAccessor::GetDirectionImpl,
        PanGestureOptionsAccessor::GetDistanceImpl,
    };
    return &PanGestureOptionsAccessorImpl;
}

}
