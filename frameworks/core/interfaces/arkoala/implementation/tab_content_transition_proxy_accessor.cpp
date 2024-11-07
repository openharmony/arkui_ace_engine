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
namespace TabContentTransitionProxyAccessor {
TabContentTransitionProxyPeer* CtorImpl()
{
    return 0;
}
Ark_NativePointer GetFinalizerImpl()
{
    return 0;
}
void FinishTransitionImpl(TabContentTransitionProxyPeer* peer)
{
}
Ark_Int32 GetFromImpl(TabContentTransitionProxyPeer* peer)
{
    return 0;
}
void SetFromImpl(TabContentTransitionProxyPeer* peer,
                 const Ark_Number* from)
{
}
Ark_Int32 GetToImpl(TabContentTransitionProxyPeer* peer)
{
    return 0;
}
void SetToImpl(TabContentTransitionProxyPeer* peer,
               const Ark_Number* to)
{
}
} // TabContentTransitionProxyAccessor
const GENERATED_ArkUITabContentTransitionProxyAccessor* GetTabContentTransitionProxyAccessor()
{
    static const GENERATED_ArkUITabContentTransitionProxyAccessor TabContentTransitionProxyAccessorImpl {
        TabContentTransitionProxyAccessor::CtorImpl,
        TabContentTransitionProxyAccessor::GetFinalizerImpl,
        TabContentTransitionProxyAccessor::FinishTransitionImpl,
        TabContentTransitionProxyAccessor::GetFromImpl,
        TabContentTransitionProxyAccessor::SetFromImpl,
        TabContentTransitionProxyAccessor::GetToImpl,
        TabContentTransitionProxyAccessor::SetToImpl,
    };
    return &TabContentTransitionProxyAccessorImpl;
}

}
