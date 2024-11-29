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
namespace IPropertySubscriberAccessor {
void DestroyPeerImpl(IPropertySubscriberPeer* peer)
{
}
IPropertySubscriberPeer* CtorImpl()
{
    return new IPropertySubscriberPeer();
}
Ark_NativePointer GetFinalizerImpl()
{
    return reinterpret_cast<void *>(&DestroyPeerImpl);
}
Ark_Int32 IdImpl(IPropertySubscriberPeer* peer)
{
    return 0;
}
void AboutToBeDeletedImpl(IPropertySubscriberPeer* peer,
                          const Opt_IPropertySubscriber* owningView)
{
}
} // IPropertySubscriberAccessor
const GENERATED_ArkUIIPropertySubscriberAccessor* GetIPropertySubscriberAccessor()
{
    static const GENERATED_ArkUIIPropertySubscriberAccessor IPropertySubscriberAccessorImpl {
        IPropertySubscriberAccessor::DestroyPeerImpl,
        IPropertySubscriberAccessor::CtorImpl,
        IPropertySubscriberAccessor::GetFinalizerImpl,
        IPropertySubscriberAccessor::IdImpl,
        IPropertySubscriberAccessor::AboutToBeDeletedImpl,
    };
    return &IPropertySubscriberAccessorImpl;
}

}
