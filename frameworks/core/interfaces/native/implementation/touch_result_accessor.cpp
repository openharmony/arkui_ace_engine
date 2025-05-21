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
namespace TouchResultAccessor {
void DestroyPeerImpl(Ark_TouchResult peer)
{
}
Ark_TouchResult CtorImpl()
{
    return nullptr;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_TouchTestStrategy GetStrategyImpl(Ark_TouchResult peer)
{
    return {};
}
void SetStrategyImpl(Ark_TouchResult peer,
                     Ark_TouchTestStrategy strategy)
{
}
Opt_String GetIdImpl(Ark_TouchResult peer)
{
    return {};
}
void SetIdImpl(Ark_TouchResult peer,
               const Opt_String* id)
{
}
} // TouchResultAccessor
const GENERATED_ArkUITouchResultAccessor* GetTouchResultAccessor()
{
    static const GENERATED_ArkUITouchResultAccessor TouchResultAccessorImpl {
        TouchResultAccessor::DestroyPeerImpl,
        TouchResultAccessor::CtorImpl,
        TouchResultAccessor::GetFinalizerImpl,
        TouchResultAccessor::GetStrategyImpl,
        TouchResultAccessor::SetStrategyImpl,
        TouchResultAccessor::GetIdImpl,
        TouchResultAccessor::SetIdImpl,
    };
    return &TouchResultAccessorImpl;
}

}
