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
};

namespace Converter {
template<>
void AssignCast(std::optional<PanDirection>& dst, const Ark_PanDirection& src)
{
    dst = PanDirection();
    switch (src) {
        case ARK_PAN_DIRECTION_NONE: dst->type = PanDirection::NONE; break;
        case ARK_PAN_DIRECTION_HORIZONTAL: dst->type = PanDirection::HORIZONTAL; break;
        case ARK_PAN_DIRECTION_LEFT: dst->type = PanDirection::LEFT; break;
        case ARK_PAN_DIRECTION_RIGHT: dst->type = PanDirection::RIGHT; break;
        case ARK_PAN_DIRECTION_VERTICAL: dst->type = PanDirection::VERTICAL; break;
        case ARK_PAN_DIRECTION_UP: dst->type = PanDirection::UP; break;
        case ARK_PAN_DIRECTION_DOWN: dst->type = PanDirection::DOWN; break;
        case ARK_PAN_DIRECTION_ALL: dst->type = PanDirection::ALL; break;
        default: LOGE("Unexpected enum value in Ark_PanDirection: %{public}d", src);
    }
}
template<>
void AssignCast(std::optional<PanGestureOptionsInfo>& dst,
                const Ark_Literal_Number_distance_fingers_PanDirection_direction& src)
{
    PanGestureOptionsInfo result;
    result.fingers = Converter::OptConvert<int32_t>(src.fingers);
    result.direction = Converter::OptConvert<PanDirection>(src.direction);
    result.distance = Converter::OptConvert<float>(src.distance);
    dst = result;
}
}
}

namespace OHOS::Ace::NG::GeneratedModifier {
namespace PanGestureOptionsAccessor {
void DestroyPeerImpl(Ark_PanGestureOptions peer)
{
    CHECK_NULL_VOID(peer);
    peer->handler = nullptr;
    delete peer;
}
Ark_PanGestureOptions CtorImpl(const Opt_Literal_Number_distance_fingers_PanDirection_direction* value)
{
    auto peer = new PanGestureOptionsPeer();
    peer->handler = Referenced::MakeRefPtr<PanGestureOption>();
    CHECK_NULL_RETURN(value, peer);

    auto info = Converter::OptConvert<PanGestureOptionsInfo>(*value);
    if (info) {
        if (info.value().direction) {
            peer->handler->SetDirection(info.value().direction.value());
        }
        if (info.value().distance) {
            peer->handler->SetDistance(info.value().distance.value());
        }
        if (info.value().fingers) {
            peer->handler->SetFingers(info.value().fingers.value());
        }
    }
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
    if (convDirection.has_value()) {
        peer->handler->SetDirection(convDirection.value());
    }
}
void SetDistanceImpl(Ark_PanGestureOptions peer,
                     const Ark_Number* value)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(peer->handler);
    CHECK_NULL_VOID(value);
    auto convDistance = Converter::OptConvert<float>(*value);
    if (convDistance.has_value()) {
        peer->handler->SetDistance(convDistance.value());
    }
}
void SetFingersImpl(Ark_PanGestureOptions peer,
                    const Ark_Number* value)
{
    CHECK_NULL_VOID(peer);
    CHECK_NULL_VOID(peer->handler);
    CHECK_NULL_VOID(value);
    auto convFingers = Converter::OptConvert<int32_t>(*value);
    if (convFingers.has_value()) {
        peer->handler->SetFingers(convFingers.value());
    }
}
Ark_PanDirection GetDirectionImpl(Ark_PanGestureOptions peer)
{
    CHECK_NULL_RETURN(peer, {});
    CHECK_NULL_RETURN(peer->handler, {});
    auto panDirection = peer->handler->GetDirection();
    return Converter::ArkValue<Ark_PanDirection>(panDirection);
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
    };
    return &PanGestureOptionsAccessorImpl;
}

struct PanGestureOptionsPeer {
    virtual ~PanGestureOptionsPeer() = default;
};
}
