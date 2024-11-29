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
namespace ControllerHandlerAccessor {
void DestroyPeerImpl(ControllerHandlerPeer* peer)
{
}
ControllerHandlerPeer* CtorImpl()
{
    return new ControllerHandlerPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
void SetWebControllerImpl(ControllerHandlerPeer* peer,
                          const Ark_CustomObject* controller)
{
}
} // ControllerHandlerAccessor
const GENERATED_ArkUIControllerHandlerAccessor* GetControllerHandlerAccessor()
{
    static const GENERATED_ArkUIControllerHandlerAccessor ControllerHandlerAccessorImpl {
        ControllerHandlerAccessor::DestroyPeerImpl,
        ControllerHandlerAccessor::CtorImpl,
        ControllerHandlerAccessor::GetFinalizerImpl,
        ControllerHandlerAccessor::SetWebControllerImpl,
    };
    return &ControllerHandlerAccessorImpl;
}

}
