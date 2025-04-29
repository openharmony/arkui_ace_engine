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
Ark_FocusAxisEvent CtorImpl()
{
    return PeerUtils::CreatePeer<FocusAxisEventPeer>();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Map_AxisModel_Number GetAxisMapImpl(Ark_FocusAxisEvent peer)
{
    CHECK_NULL_RETURN(peer && peer->GetEventInfo(), {});
    auto eventInfo = peer->GetEventInfo();
    return Converter::ArkValue<Map_AxisModel_Number>(getAxisMapFromInfo(*eventInfo), Converter::FC);
}
void SetAxisMapImpl(Ark_FocusAxisEvent peer,
                    const Map_AxisModel_Number* axisMap)
{
    LOGW("ARKOALA KeyEventAccessor::SetAxisMapImpl doesn't have sense.");
}
Callback_Void GetStopPropagationImpl(Ark_FocusAxisEvent peer)
{
    CHECK_NULL_RETURN(peer, {});
    auto callback = CallbackKeeper::DefineReverseCallback<Callback_Void>([peer]() {
        FocusAxisEventInfo* info = peer->GetEventInfo();
        CHECK_NULL_VOID(info);
        info->SetStopPropagation(true);
    });
    return callback;
}
void SetStopPropagationImpl(Ark_FocusAxisEvent peer,
                            const Callback_Void* stopPropagation)
{
    LOGE("FocusAxisEventAccessor::SetStopPropagationImpl we can only GET stopPropagation callback");
}
} // FocusAxisEventAccessor
const GENERATED_ArkUIFocusAxisEventAccessor* GetFocusAxisEventAccessor()
{
    static const GENERATED_ArkUIFocusAxisEventAccessor FocusAxisEventAccessorImpl {
        FocusAxisEventAccessor::DestroyPeerImpl,
        FocusAxisEventAccessor::CtorImpl,
        FocusAxisEventAccessor::GetFinalizerImpl,
        FocusAxisEventAccessor::GetAxisMapImpl,
        FocusAxisEventAccessor::SetAxisMapImpl,
        FocusAxisEventAccessor::GetStopPropagationImpl,
        FocusAxisEventAccessor::SetStopPropagationImpl,
    };
    return &FocusAxisEventAccessorImpl;
}

}
