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
namespace ComponentContentAccessor {
void DestroyPeerImpl(Ark_ComponentContent peer)
{
}
Ark_ComponentContent CtorImpl()
{
    return nullptr;
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void UpdateImpl(Ark_ComponentContent peer,
                const Ark_Object* args)
{
}
void ReuseImpl(Ark_ComponentContent peer,
               const Opt_Object* param)
{
}
void RecycleImpl(Ark_ComponentContent peer)
{
}
void DisposeImpl(Ark_ComponentContent peer)
{
}
void UpdateConfigurationImpl(Ark_ComponentContent peer)
{
}
} // ComponentContentAccessor
const GENERATED_ArkUIComponentContentAccessor* GetComponentContentAccessor()
{
    static const GENERATED_ArkUIComponentContentAccessor ComponentContentAccessorImpl {
        ComponentContentAccessor::DestroyPeerImpl,
        ComponentContentAccessor::CtorImpl,
        ComponentContentAccessor::GetFinalizerImpl,
        ComponentContentAccessor::UpdateImpl,
        ComponentContentAccessor::ReuseImpl,
        ComponentContentAccessor::RecycleImpl,
        ComponentContentAccessor::DisposeImpl,
        ComponentContentAccessor::UpdateConfigurationImpl,
    };
    return &ComponentContentAccessorImpl;
}

}
