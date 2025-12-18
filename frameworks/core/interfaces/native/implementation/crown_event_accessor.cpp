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
namespace CrownEventAccessor {
void DestroyPeerImpl(Ark_CrownEvent peer)
{
}
Ark_CrownEvent ConstructImpl()
{
    return {};
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void StopPropagationImpl(Ark_CrownEvent peer)
{
}
Ark_Int64 GetTimestampImpl(Ark_CrownEvent peer)
{
    return {};
}
void SetTimestampImpl(Ark_CrownEvent peer,
                      Ark_Int64 timestamp)
{
}
Ark_Float64 GetAngularVelocityImpl(Ark_CrownEvent peer)
{
    return {};
}
void SetAngularVelocityImpl(Ark_CrownEvent peer,
                            Ark_Float64 angularVelocity)
{
}
Ark_Float64 GetDegreeImpl(Ark_CrownEvent peer)
{
    return {};
}
void SetDegreeImpl(Ark_CrownEvent peer,
                   Ark_Float64 degree)
{
}
Ark_CrownAction GetActionImpl(Ark_CrownEvent peer)
{
    return {};
}
void SetActionImpl(Ark_CrownEvent peer,
                   Ark_CrownAction action)
{
}
} // CrownEventAccessor
const GENERATED_ArkUICrownEventAccessor* GetCrownEventAccessor()
{
    static const GENERATED_ArkUICrownEventAccessor CrownEventAccessorImpl {
        CrownEventAccessor::DestroyPeerImpl,
        CrownEventAccessor::ConstructImpl,
        CrownEventAccessor::GetFinalizerImpl,
        CrownEventAccessor::StopPropagationImpl,
        CrownEventAccessor::GetTimestampImpl,
        CrownEventAccessor::SetTimestampImpl,
        CrownEventAccessor::GetAngularVelocityImpl,
        CrownEventAccessor::SetAngularVelocityImpl,
        CrownEventAccessor::GetDegreeImpl,
        CrownEventAccessor::SetDegreeImpl,
        CrownEventAccessor::GetActionImpl,
        CrownEventAccessor::SetActionImpl,
    };
    return &CrownEventAccessorImpl;
}

}
