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
#include "core/interfaces/native/implementation/focus_axis_event_accessor.h"

namespace OHOS::Ace::NG {
namespace Converter {
void AssignArkValue(Ark_AxisModel& dst, const AxisModel& src)
{
    switch (src) {
        case AxisModel::ABS_X: dst = ARK_AXIS_MODEL_ABS_X; break;
        case AxisModel::ABS_Y: dst = ARK_AXIS_MODEL_ABS_Y; break;
        case AxisModel::ABS_Z: dst = ARK_AXIS_MODEL_ABS_Z; break;
        case AxisModel::ABS_RZ: dst = ARK_AXIS_MODEL_ABS_RZ; break;
        case AxisModel::ABS_GAS: dst = ARK_AXIS_MODEL_ABS_GAS; break;
        case AxisModel::ABS_BRAKE: dst = ARK_AXIS_MODEL_ABS_BRAKE; break;
        case AxisModel::ABS_HAT0X: dst = ARK_AXIS_MODEL_ABS_HAT0X; break;
        case AxisModel::ABS_HAT0Y: dst = ARK_AXIS_MODEL_ABS_HAT0Y; break;
        case AxisModel::ABS_RX: dst = ARK_AXIS_MODEL_ABS_RX; break;
        case AxisModel::ABS_RY: dst = ARK_AXIS_MODEL_ABS_RY; break;
        case AxisModel::ABS_THROTTLE: dst = ARK_AXIS_MODEL_ABS_THROTTLE; break;
        case AxisModel::ABS_RUDDER: dst = ARK_AXIS_MODEL_ABS_RUDDER; break;
        case AxisModel::ABS_WHEEL: dst = ARK_AXIS_MODEL_ABS_WHEEL; break;
        case AxisModel::ABS_HAT1X: dst = ARK_AXIS_MODEL_ABS_HAT1X; break;
        case AxisModel::ABS_HAT1Y: dst = ARK_AXIS_MODEL_ABS_HAT1Y; break;
        case AxisModel::ABS_HAT2X: dst = ARK_AXIS_MODEL_ABS_HAT2X; break;
        case AxisModel::ABS_HAT2Y: dst = ARK_AXIS_MODEL_ABS_HAT2Y; break;
        case AxisModel::ABS_HAT3X: dst = ARK_AXIS_MODEL_ABS_HAT3X; break;
        case AxisModel::ABS_HAT3Y: dst = ARK_AXIS_MODEL_ABS_HAT3Y; break;
        default: {
            dst = INVALID_ENUM_VAL<Ark_AxisModel>;
            LOGE("Unexpected enum value in AxisModel: %{public}d", src);
        }
    }
}
} // namespace Converter
} // namespace OHOS::Ace::NG


namespace OHOS::Ace::NG::GeneratedModifier {
namespace FocusAxisEventAccessor {
void DestroyPeerImpl(Ark_FocusAxisEvent peer)
{
    PeerUtils::DestroyPeer(peer);
}
Ark_FocusAxisEvent ConstructImpl()
{
    return PeerUtils::CreatePeer<FocusAxisEventPeer>();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Map_AxisModel_Float64 GetAxisMapImpl(Ark_FocusAxisEvent peer)
{
    CHECK_NULL_RETURN(peer && peer->GetEventInfo(), {});
    auto eventInfo = peer->GetEventInfo();
    return Converter::ArkValue<Map_AxisModel_Float64>(getAxisMapFromInfo(*eventInfo), Converter::FC);
}
void SetAxisMapImpl(Ark_FocusAxisEvent peer,
                    const Map_AxisModel_Float64* axisMap)
{
    LOGW("ARKOALA KeyEventAccessor::SetAxisMapImpl doesn't have sense.");
}
void StopPropagationImpl(Ark_FocusAxisEvent peer)
{
    CHECK_NULL_VOID(peer);
    FocusAxisEventInfo* info = peer->GetEventInfo();
    CHECK_NULL_VOID(info);
    info->SetStopPropagation(true);
}
} // FocusAxisEventAccessor
const GENERATED_ArkUIFocusAxisEventAccessor* GetFocusAxisEventAccessor()
{
    static const GENERATED_ArkUIFocusAxisEventAccessor FocusAxisEventAccessorImpl {
        FocusAxisEventAccessor::DestroyPeerImpl,
        FocusAxisEventAccessor::ConstructImpl,
        FocusAxisEventAccessor::GetFinalizerImpl,
        FocusAxisEventAccessor::GetAxisMapImpl,
        FocusAxisEventAccessor::SetAxisMapImpl,
        FocusAxisEventAccessor::StopPropagationImpl,
    };
    return &FocusAxisEventAccessorImpl;
}

}
