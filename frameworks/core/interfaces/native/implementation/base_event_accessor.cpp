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
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace BaseEventAccessor {
void DestroyPeerImpl(Ark_BaseEvent peer)
{
}
Ark_BaseEvent ConstructImpl()
{
    return {};
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_EventTarget GetTargetImpl(Ark_BaseEvent peer)
{
    return {};
}
void SetTargetImpl(Ark_BaseEvent peer,
                   const Ark_EventTarget* target)
{
}
Ark_Number GetTimestampImpl(Ark_BaseEvent peer)
{
    return {};
}
void SetTimestampImpl(Ark_BaseEvent peer,
                      const Ark_Number* timestamp)
{
}
Ark_SourceType GetSourceImpl(Ark_BaseEvent peer)
{
    return {};
}
void SetSourceImpl(Ark_BaseEvent peer,
                   Ark_SourceType source)
{
}
Opt_Number GetAxisHorizontalImpl(Ark_BaseEvent peer)
{
    return {};
}
void SetAxisHorizontalImpl(Ark_BaseEvent peer,
                           const Opt_Number* axisHorizontal)
{
}
Opt_Number GetAxisVerticalImpl(Ark_BaseEvent peer)
{
    return {};
}
void SetAxisVerticalImpl(Ark_BaseEvent peer,
                         const Opt_Number* axisVertical)
{
}
Ark_Number GetPressureImpl(Ark_BaseEvent peer)
{
    return {};
}
void SetPressureImpl(Ark_BaseEvent peer,
                     const Ark_Number* pressure)
{
}
Ark_Number GetTiltXImpl(Ark_BaseEvent peer)
{
    return {};
}
void SetTiltXImpl(Ark_BaseEvent peer,
                  const Ark_Number* tiltX)
{
}
Ark_Number GetTiltYImpl(Ark_BaseEvent peer)
{
    return {};
}
void SetTiltYImpl(Ark_BaseEvent peer,
                  const Ark_Number* tiltY)
{
}
Opt_Number GetRollAngleImpl(Ark_BaseEvent peer)
{
    return {};
}
void SetRollAngleImpl(Ark_BaseEvent peer,
                      const Opt_Number* rollAngle)
{
}
Ark_SourceTool GetSourceToolImpl(Ark_BaseEvent peer)
{
    return {};
}
void SetSourceToolImpl(Ark_BaseEvent peer,
                       Ark_SourceTool sourceTool)
{
}
Opt_ModifierKeyStateGetter GetGetModifierKeyStateImpl(Ark_BaseEvent peer)
{
    return {};
}
void SetGetModifierKeyStateImpl(Ark_BaseEvent peer,
                                const Opt_ModifierKeyStateGetter* getModifierKeyState)
{
}
Opt_Number GetDeviceIdImpl(Ark_BaseEvent peer)
{
    return {};
}
void SetDeviceIdImpl(Ark_BaseEvent peer,
                     const Opt_Number* deviceId)
{
}
Opt_Number GetTargetDisplayIdImpl(Ark_BaseEvent peer)
{
    return {};
}
void SetTargetDisplayIdImpl(Ark_BaseEvent peer,
                            const Opt_Number* targetDisplayId)
{
}
} // BaseEventAccessor
const GENERATED_ArkUIBaseEventAccessor* GetBaseEventAccessor()
{
    static const GENERATED_ArkUIBaseEventAccessor BaseEventAccessorImpl {
        BaseEventAccessor::DestroyPeerImpl,
        BaseEventAccessor::ConstructImpl,
        BaseEventAccessor::GetFinalizerImpl,
        BaseEventAccessor::GetTargetImpl,
        BaseEventAccessor::SetTargetImpl,
        BaseEventAccessor::GetTimestampImpl,
        BaseEventAccessor::SetTimestampImpl,
        BaseEventAccessor::GetSourceImpl,
        BaseEventAccessor::SetSourceImpl,
        BaseEventAccessor::GetAxisHorizontalImpl,
        BaseEventAccessor::SetAxisHorizontalImpl,
        BaseEventAccessor::GetAxisVerticalImpl,
        BaseEventAccessor::SetAxisVerticalImpl,
        BaseEventAccessor::GetPressureImpl,
        BaseEventAccessor::SetPressureImpl,
        BaseEventAccessor::GetTiltXImpl,
        BaseEventAccessor::SetTiltXImpl,
        BaseEventAccessor::GetTiltYImpl,
        BaseEventAccessor::SetTiltYImpl,
        BaseEventAccessor::GetRollAngleImpl,
        BaseEventAccessor::SetRollAngleImpl,
        BaseEventAccessor::GetSourceToolImpl,
        BaseEventAccessor::SetSourceToolImpl,
        BaseEventAccessor::GetGetModifierKeyStateImpl,
        BaseEventAccessor::SetGetModifierKeyStateImpl,
        BaseEventAccessor::GetDeviceIdImpl,
        BaseEventAccessor::SetDeviceIdImpl,
        BaseEventAccessor::GetTargetDisplayIdImpl,
        BaseEventAccessor::SetTargetDisplayIdImpl,
    };
    return &BaseEventAccessorImpl;
}

}
