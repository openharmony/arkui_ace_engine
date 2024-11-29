/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "core/interfaces/arkoala/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace StyledStringControllerAccessor {
void DestroyPeerImpl(StyledStringControllerPeer* peer)
{
}
StyledStringControllerPeer* CtorImpl()
{
    return new StyledStringControllerPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void SetStyledStringImpl(StyledStringControllerPeer* peer,
                         const Ark_StyledString* styledString)
{
}
Ark_NativePointer GetStyledStringImpl(StyledStringControllerPeer* peer)
{
    return 0;
}
} // StyledStringControllerAccessor
const GENERATED_ArkUIStyledStringControllerAccessor* GetStyledStringControllerAccessor()
{
    static const GENERATED_ArkUIStyledStringControllerAccessor StyledStringControllerAccessorImpl {
        StyledStringControllerAccessor::DestroyPeerImpl,
        StyledStringControllerAccessor::CtorImpl,
        StyledStringControllerAccessor::GetFinalizerImpl,
        StyledStringControllerAccessor::SetStyledStringImpl,
        StyledStringControllerAccessor::GetStyledStringImpl,
    };
    return &StyledStringControllerAccessorImpl;
}

}
